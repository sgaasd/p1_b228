#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <kobuki_msgs/WheelDropEvent.h>
#include <kobuki_msgs/CliffEvent.h>
#include <kobuki_msgs/BumperEvent.h>
using namespace std;

//Publisher varible is initialised 
ros::Publisher cmd_vel_pub;

//A function for defining cmd_vel_message is created  
geometry_msgs::Twist SafetyMsg(float x, float z){
    geometry_msgs::Twist cmd_vel_message;
    cmd_vel_message.angular.z = z;
    cmd_vel_message.linear.x = x;
    return cmd_vel_message;
}

//"WheelDrop" shall be false as default
bool wheelDrop=false;

//A class called Safety_CallBack, that contains the different functions, is created 
class Safety_CallBack {
    public: 

        //The function for the Wheel Drop. With pointers that passes the data from the each wheels state from the robot 
        void WheelDropCallBack(const kobuki_msgs::WheelDropEvent::ConstPtr& msg){
            bool wheels = msg->wheel;
            bool wheelState = msg->state;
            bool wheelDrop = wheelState;
   
            //if the wheel drop is activated the robot will stop and exit ROS. 
            if (wheelDrop == true){
                cmd_vel_pub.publish(SafetyMsg(0.0, 0.0));   
                ROS_FATAL("Robot has been lifted - Exiting ROS ");
                exit(1);
                }
            }       

        //The function for the Cliff sensor is created. With poniter that passes data from each sensor and it's state
        void CliffCallback(const kobuki_msgs::CliffEvent::ConstPtr& msg){
        geometry_msgs::Twist cmd_vel_message;
        bool cliffs = msg->state;
        int sensors = msg->sensor;
        //The robot has 2 second for each state.  
        ros::Rate loop_rate(21);
            //The robot should make different turns depending on which sensor is activated 
            if (cliffs == 1 && wheelDrop == false) {
                switch (sensors){
                    //If the sensor on the left side is pressed the robot will first drive backwards and turn right
                    case 0:
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(SafetyMsg(-0.2, 0.0));
                        loop_rate.sleep();
                    }
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(SafetyMsg(0.0, -(0.75)));
                        loop_rate.sleep();
                    }
                    break;
                    //If the sensor on the middle is activated the robot will drive backwards and turn left 
                    case 1:
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(SafetyMsg(-0.2, 0.0));
                        loop_rate.sleep();
                    }
                    for(int i=0; i<=42; i++){
                        cmd_vel_pub.publish(SafetyMsg(0.0, (0.75)));
                        loop_rate.sleep();
                    }
                    break;
                    //If the sensor on the right side is pressed the robot will drive backwards and turn left
                     case 2:
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(SafetyMsg(-0.2, 0.0));
                        loop_rate.sleep();
                    }
                    for(int i=0; i<=42; i++){
                        cmd_vel_pub.publish(SafetyMsg(0.0, (0.75)));
                        loop_rate.sleep();
                    }
                    break;
                }
            }
               
        }
        //The function BumperCallBack tells if the bumper is pressed and which side is pressed
        void BumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg){
        geometry_msgs::Twist cmd_vel_message;
        bool hit = msg->state;
        int bump = msg->bumper;
        ros::Rate loop_rate(21);
        if(hit == 1 && wheelDrop==false) {
            //The robot should make different turns depending on which bumper is pressed 
            switch (bump){
                //If the bumper on the left side is pressed the robot will first drive backwards and turn right
                case 0:
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(SafetyMsg(-0.2, 0.0));
                        loop_rate.sleep();
                    }
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(SafetyMsg(0.0, -(0.75)));
                        loop_rate.sleep();
                    }
                    break;
                //If the bumper on the middle is pressed the robot will drive backwards and turn left
                case 1:
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(SafetyMsg(-0.2, 0.0));
                        loop_rate.sleep();
                    }
                    for(int i=0; i<=42; i++){
                        cmd_vel_pub.publish(SafetyMsg(0.0, (0.75)));
                        loop_rate.sleep();
                    }
                    break;
                //If the bumper on the right side is pressed the robot will drive backwards and turn left
                case 2:
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(SafetyMsg(-0.2, 0.0));
                        loop_rate.sleep();
                    }
                    for(int i=0; i<=42; i++){
                        cmd_vel_pub.publish(SafetyMsg(0.0, (0.75)));
                        loop_rate.sleep();
                    }
                    break;
            }
        }
           
    }
    private:
};

int main(int argc, char *argv[]){

    //Initelizing ros   
    ros::init(argc, argv, "Safety");
    ros::NodeHandle n;
    
    //cmd_vel_pub is defined 
    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/safety_controller", 1);

    //To call the class it needs to be declared 
    Safety_CallBack safetyClass;

    //Subcribing to "/mobile_base/events/cliff". 
    //Evertime an advertisment is made on the topic "/mobile_base/events/cliff" run "WheelDropCallBack"
    ros::Subscriber WheelDrop_sub = n.subscribe("/mobile_base/events/wheel_drop", 1, &Safety_CallBack::WheelDropCallBack, &safetyClass);
    
    //Subcribing to "/mobile_base/events/cliff". 
    //Evertime an advertisment is made on the topic "/mobile_base/events/cliff" run "CliffCallBack"
    ros::Subscriber Cliff_sub = n.subscribe("/mobile_base/events/cliff", 1, &Safety_CallBack::CliffCallback, &safetyClass);
    
    //Subcribing to "mobile_base/events/bumper". 
    //Evertime an advertisment is made on the topic "mobile_base/events/bumper" run "BumperCallBack"
    ros::Subscriber Bumper_sub = n.subscribe("mobile_base/events/bumper", 1, &Safety_CallBack::BumperCallback, &safetyClass);

    //The program has run continuously 
    ros::spin();

    return 0;
}
