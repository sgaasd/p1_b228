#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <math.h>

void drive(const nav_msgs::Odometry::ConstPtr& msg);

ros::Publisher cmd_vel_pub;
float dist;

int main(int argc, char *argv[])
{
    std::cout << "Hvor langt skal den køre?" << std::endl;
    std::cin >> dist;

    ros::init(argc, argv, "Drive_function");

    ros::NodeHandle n;

    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1);
    
    ros::Subscriber odom_sub = n.subscribe("odom", 1, drive);
    
    ros::spin();

    return 0;
}

void drive(const nav_msgs::Odometry::ConstPtr& msg){

    float PosX = msg->pose.pose.position.x;
    float PosY = msg->pose.pose.position.y;
    float driven = sqrt(PosX*PosX + PosY*PosY);
    
    std::cout << "Driven: " << driven << std::endl;
    geometry_msgs::Twist cmd_vel_message;
    if (driven < dist){       
        cmd_vel_message.angular.z = 0.0;
        cmd_vel_message.linear.x = 0.05;
        cmd_vel_pub.publish(cmd_vel_message);
    } else {
        cmd_vel_message.angular.z = 0.0;
        cmd_vel_message.linear.x = 0.00;
        cmd_vel_pub.publish(cmd_vel_message);
    }

}