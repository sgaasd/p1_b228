#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "Drive");

    ros::NodeHandle n;
    ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/teleop", 1);

    geometry_msgs::Twist cmd_vel_message;
    cmd_vel_message.angular.z = 0.0;
    cmd_vel_message.linear.x = 0.50;

    ros::Rate loop_rate(2);
    while (ros::ok())
{
        cmd_vel_message.angular.z = cmd_vel_message.angular.z * 1.00;
        cmd_vel_message.linear.x = cmd_vel_message.linear.x * 1.00;
        cmd_vel_pub.publish(cmd_vel_message);
        loop_rate.sleep();
}
    return 0;
}