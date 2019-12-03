#include <ros/ros.h>
#include <kobuki_msgs/ButtonEvent.h>
#include <iostream>
#include <geometry_msgs/Twist.h>
using namespace std;

ros::Publisher cmd_vel_pub;

geometry_msgs::Twist ButtMsg(float x, float z){
    geometry_msgs::Twist cmd_vel_message;
    cmd_vel_message.angular.z = z;
    cmd_vel_message.linear.x = x;
    cout << cmd_vel_message << endl;
    return cmd_vel_message;
}

void ButtonCallback(const kobuki_msgs::ButtonEvent::ConstPtr& msg){ 
    bool Pressed = msg->state;
    int Button = msg->button;

    if (Pressed=true){
        switch (Button){
            case 0:
                cmd_vel_pub.publish(ButtMsg(0.5, 0.5));
            break; 
            case 1:
                cmd_vel_pub.publish(ButtMsg(0.0, -0.5));
            break;  
            case 2: 
                cmd_vel_pub.publish(ButtMsg(0.0, 0.5));
            break;
        } 
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
