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
    cout << cmd_vel_message << endl;
    return cmd_vel_message;
}
//wd shall be true as default
bool wd=false;

//A class called safety is created that contains the different functions 
class Safety_CallBack {
    public: 

        //The function with for the Wheel Drop. With pointers to Wheel and State 
        void WheelDrop_callBack(const kobuki_msgs::WheelDropEvent::ConstPtr& msg){
            bool wheels = msg->wheel;
            bool wheel_state = msg->state;
            bool wd = wheel_state;
   
            //iF the wheel drop is activated the the robot will stop and exit the program. 
            if (wd == true){
                cmd_vel_pub.publish(SafetyMsg(0.0, 0.0));   
                ROS_FATAL("ERROR");
                exit(1);
                }
            }       

        //The functino for the Cliff is created 
        void CliffCallback(const kobuki_msgs::CliffEvent::ConstPtr& msg){
        geometry_msgs::Twist cmd_vel_message;
        bool cliffs = msg->state;
        int sensors = msg->sensor;
        //The robot has 2 second for each state 
        ros::Rate loop_rate(21);
            if (cliffs == 1 && wd == false) {
                //The robot should make different turns depending on which sensor is activated 
                switch (sensors){
                    //If the sensor on the left side is pressed the robot will turn right 90 degrees
                    case 0:
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(SafetyMsg(-0.2, 0.0));
                        loop_rate.sleep();
                    }
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(SafetyMsg(0.0, -(1.5707963268 / 2)));
                        loop_rate.sleep();
                    }
                    break;
                    //If the sensor on the middle is activated the robot will turn left 90 degrees
                    case 1:
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(SafetyMsg(-0.2, 0.0));
                        loop_rate.sleep();
                    }
                    for(int i=0; i<=42; i++){
                        cmd_vel_pub.publish(SafetyMsg(0.0, (1.5707963268 / 2)));
                        loop_rate.sleep();
                    }
                    break;
                    //If the sensor on the right side is pressed the robot will turn left 90 degrees
                     case 2:
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(SafetyMsg(-0.2, 0.0));
                        loop_rate.sleep();
                    }
                    for(int i=0; i<=42; i++){
                        cmd_vel_pub.publish(SafetyMsg(0.0, (1.5707963268 / 2)));
                        loop_rate.sleep();
                    }
                    break;
                }
            }
               
        }
        //The function BumperCallBack tells if the bumper is pressed and which side 
        void BumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg){
        geometry_msgs::Twist cmd_vel_message;
        bool hit = msg->state;
        int bump = msg->bumper;
        ros::Rate loop_rate(21);
        if(hit == 1 && wd==false) {
            //The robot should make different turns depending on which bumper is pressed 
            switch (bump){
                //If the bumper on the left side is pressed the robot will turn right 90 degrees
                case 0:
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(SafetyMsg(-0.2, 0.0));
                        loop_rate.sleep();
                    }
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(SafetyMsg(0.0, -(1.5707963268 / 2)));
                        loop_rate.sleep();
                    }
                    break;
                //If the bumper on the middle is pressed the robot will turn left 90 degrees
                case 1:
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(SafetyMsg(-0.2, 0.0));
                        loop_rate.sleep();
                    }
                    for(int i=0; i<=42; i++){
                        cmd_vel_pub.publish(SafetyMsg(0.0, (1.5707963268 / 2)));
                        loop_rate.sleep();
                    }
                    break;
                //If the bumper on the right side is pressed the robot will turn left 90 degrees
                case 2:
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(SafetyMsg(-0.2, 0.0));
                        loop_rate.sleep();
                    }
                    for(int i=0; i<=42; i++){
                        cmd_vel_pub.publish(SafetyMsg(0.0, (1.5707963268 / 2)));
                        loop_rate.sleep();
                    }
                    break;
            }
        }
           
    }
    private:
};

int main(int argc, char *argv[]){

    ros::init(argc, argv, "Safety");
    ros::NodeHandle n;
    //cmd_vel_pub is defined 
    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/safety_controller", 1);

    Safety_CallBack something;

    ros::Subscriber WheelDrop_sub = n.subscribe("/mobile_base/events/wheel_drop", 1, &Safety_CallBack::WheelDrop_callBack, &something);
    //Subcribing to "/mobile_base/events/cliff". 
    //Evertime an advertisment is made on the topic "/mobile_base/events/cliff" run "CliffCallBack"
    ros::Subscriber Cliff_sub = n.subscribe("/mobile_base/events/cliff", 1, &Safety_CallBack::CliffCallback, &something);
    //Subcribing to "mobile_base/events/bumper". 
    //Evertime an advertisment is made on the topic "mobile_base/events/bumper" run "BumperCallBack"
    ros::Subscriber Bumper_sub = n.subscribe("mobile_base/events/bumper", 1, &Safety_CallBack::BumperCallback, &something);

    //The program has run continuously 
    ros::spin();
    return 0;
}
