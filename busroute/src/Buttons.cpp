#include <ros/ros.h>
#include <kobuki_msgs/ButtonEvent.h>
#include <iostream>
#include <geometry_msgs/Twist.h>
using namespace std;

ros::Publisher cmd_vel_pub;

void ButtonCallback(const kobuki_msgs::ButtonEvent::ConstPtr& msg){ 
    bool Pressed = msg->state;
    int Button = msg->button;
    
    if (Pressed == true && Button == 0){
        std::cout << "B0 = " << Pressed << std::endl;
        std::cin >> Button;
        if (Button == 0){
            geometry_msgs::Twist cmd_vel_message;
            cmd_vel_message.angular.z = 0.5;
            cmd_vel_message.linear.x = 0.5;
    
        }
    }
    else if (Pressed == true && Button == 1){
        std::cout << "B1 = " << Pressed << std::endl;
        std::cin >> Button;
        if (Button == 1){
            geometry_msgs::Twist cmd_vel_message;
            cmd_vel_message.angular.z = 0.0;
            cmd_vel_message.linear.x = -0.5;    
        }
    }
    else if (Pressed == true && Button == 2){
        std::cout << "B2 = " << Pressed << std::endl;
        std::cin >> Button;
        if (Button == 2){
            geometry_msgs::Twist cmd_vel_message;
            cmd_vel_message.angular.z = 0.0;
            cmd_vel_message.linear.x = 0.5;    
        }
    }    
    else {
        std::cout << "Du har ikke trykket på en knap" << std::endl;
    }
}


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "Buttons");
    ros::NodeHandle n;
    ros::Subscriber Button_sub = n.subscribe("mobile_base/events/button", 10, ButtonCallback);

    ros::NodeHandle nh;
    cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1);

    ros::spin();
    return 0;
}
