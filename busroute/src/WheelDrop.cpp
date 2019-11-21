#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <kobuki_msgs/WheelDropEvent.h>
using namespace std;

//Publisher varible is initialised 
ros::Publisher cmd_vel_pub;

//pressed defineres som en global variable 
bool pressed;

//A function for defining cmd_vel_message is created  
geometry_msgs::Twist WheelMsg(float x, float z){
    geometry_msgs::Twist cmd_vel_message;
    cmd_vel_message.linear.x = x;
    cmd_vel_message.angular.z = z;
    cout << cmd_vel_message << endl;
    return cmd_vel_message;
}

//Funktion for pressed og wheel. Her får de deres værdier 
void WheelDrop_callBack(const kobuki_msgs::WheelDropEvent::ConstPtr& msg){
    bool wheel = msg->wheel;
    pressed = msg->state;
}


        /*if (pressed == 1) {
        //The robot should make different turns depending on which bumper is pressed 
        switch (wheel){
            //If the bumper on the left side is pressed the robot will turn right
            case 0:
                for(int i=0; i<=42; i++){ 
                    cmd_vel_pub.publish(WheelMsg(0.0));
                    loop_rate.sleep();
                }
            break;
            //If the bumper on the middle is pressed the bumper will turn left 
            case 1:
                for(int i=0; i<=42; i++){ 
                    cmd_vel_pub.publish(WheelMsg(0.0));
                    loop_rate.sleep();
                }
            break;
            //If the bumper on the right side is pressed the bumper will turn left 
        }
    }*/
//}

int main(int argc, char *argv[]){

    ros::init(argc, argv, "WheelDrop");
    ros::NodeHandle n;
    //cmd_vel_pub is defined 
    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/safety_controller", 1);
    ros::Subscriber WheelDrop_sub = n.subscribe("/mobile_base/events/wheel_drop", 1, WheelDrop_callBack);
    
    //Et forsøg på at få den til at virke 
    ros::Rate loop_rate(21);
    if(pressed==1){
        cmd_vel_pub.publish(WheelMsg(0.0, 0.0));
    }

    ros::spin();
    return 0;
}