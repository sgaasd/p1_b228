#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>

float PosX = 0;
float PosY = 0;
float PrePosX;
float PrePosY;
float dist;
float driven = 0;

void chatterCallback(const nav_msgs::Odometry::ConstPtr& msg){
    PosX = msg->pose.pose.position.x;
    PosY = msg->pose.pose.position.y;
    dist = sqrt(((PosX*PosX)+(PosY*PosY)));
    std::cout << dist << std::endl;
    if(dist < 1){
        
    }
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "Drive");

    std::cout << "Hvor langt skal den køre?" << std::endl;
    std::cin >> dist;

    ros::NodeHandle n;
    ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/teleop", 1);

    ros::Subscriber odom_sub = n.subscribe("odom", 1, chatterCallback);

    std::cout << PrePosX << ", " << PrePosY << std::endl;

    geometry_msgs::Twist cmd_vel_message;
    cmd_vel_message.angular.z = 0.0;
    cmd_vel_message.linear.x = 0.50;

    ros::Rate loop_rate(10);
    ros::spin();
}