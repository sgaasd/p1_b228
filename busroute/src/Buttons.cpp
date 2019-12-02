#include <ros/ros.h>
#include <kobuki_msgs/ButtonEvent.h>
#include <iostream>
using namespace std;

void ButtonCallback(const kobuki_msgs::ButtonEvent::ConstPtr& msg){
    bool pressed = msg->state
    //Button0
    //Button1
    //Button2
    std::cout << state << std::endl;
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "Buttons");
    ros::NodeHandle n;
    ros::Subscriber Button_sub = n.subscribe("mobile_base/events/button", 10, ButtonCallback);


    ros::spin();
    return 0;
}


/*

        //The function BumperCallBack tells if the bumper is pressed and which side 
        void BumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg){
        geometry_msgs::Twist cmd_vel_message;
        bool hit = msg->state;
        int bump = msg->bumper;
        ros::Rate loop_rate(21);
        if(hit == 1 && wd==false) {
            //The robot should make different turns depending on which bumper is pressed 
            switch (bump){
                //If the bumper on the left side is pressed the robot will turn right
                case 0:
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(SafetyMsg(-0.2, 0.0));
                        loop_rate.sleep();
                    }
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(SafetyMsg(0.0, -0.3));
                        loop_rate.sleep();
                    }
                    break;
                //If the bumper on the middle is pressed the robot will turn left 
                case 1:
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(SafetyMsg(-0.2, 0.0));
                        loop_rate.sleep();
                    }
                    for(int i=0; i<=42; i++){
                        cmd_vel_pub.publish(SafetyMsg(0.0, 0.4));
                        loop_rate.sleep();
                    }
                    break;
                //If the bumper on the right side is pressed the robot will turn left 
                case 2:
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(SafetyMsg(-0.2, 0.0));
                        loop_rate.sleep();
                    }
                    for(int i=0; i<=42; i++){
                        cmd_vel_pub.publish(SafetyMsg(0.0, 0.4));
                        loop_rate.sleep();
                    }
                    break;
*/