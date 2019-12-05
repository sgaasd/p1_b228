#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <math.h>

void drive(const nav_msgs::Odometry::ConstPtr& msg);

ros::Publisher cmd_vel_pub;

float dist;

float PrePosX = 0;
float PrePosY = 0;

bool CorSet = false;

int main(int argc, char *argv[])
{
    beginning:
    std::cout << "Hvor langt skal den køre?" << std::endl;
    std::cin >> dist;

    ros::init(argc, argv, "Drive_function");

    ros::NodeHandle n;

    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1);
    
    ros::Subscriber odom_sub = n.subscribe("odom", 1, drive);

    /*if (CorSet == 0) {

    }   */
    
    ros::spin();

    return 0;
}

void drive(const nav_msgs::Odometry::ConstPtr& msg){

    if(CorSet == false) {
        PrePosX = msg->pose.pose.position.x;
        PrePosY = msg->pose.pose.position.y;
        CorSet = true;
    }

    float PosX = msg->pose.pose.position.x-PrePosX;
    float PosY = msg->pose.pose.position.y-PrePosY;
    float driven = sqrt(PosX*PosX + PosY*PosY);
    
    std::cout << CorSet << std::endl;
    std::cout << "Coordinates: " << PosX << ", " << PosY << std::endl;
    geometry_msgs::Twist cmd_vel_message;
    if (driven < dist){       
        cmd_vel_message.angular.z = 0.0;
        cmd_vel_message.linear.x = 0.05;
        cmd_vel_pub.publish(cmd_vel_message);
    } else {
        cmd_vel_message.angular.z = 0.0;
        cmd_vel_message.linear.x = 0.00;
        cmd_vel_pub.publish(cmd_vel_message);
        CorSet = false;
    }

}