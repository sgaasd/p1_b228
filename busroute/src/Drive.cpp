#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>

int dist(){

}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "Drive");

    ros::NodeHandle n;
    ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/teleop", 1);

        //    ros::Subscriber odom_sub = n.subscribe("odom", 100, dist);

    geometry_msgs::Twist cmd_vel_message;
    cmd_vel_message.angular.z = 0.0;
    cmd_vel_message.linear.x = 0.25;

//1 meter --> x = 0.25 --> for_loop = 40
//1 meter --> x = 0.50 --> for_loop = 20
//1 meter --> x = 1 --> for_loop = loop_rate

    ros::Rate loop_rate(10);
    for (int i = 0; i < 40; i++)
{

        cmd_vel_message.angular.z = cmd_vel_message.angular.z * 1.00;
        cmd_vel_message.linear.x = cmd_vel_message.linear.x * 1.00;
        cmd_vel_pub.publish(cmd_vel_message);
        loop_rate.sleep();
}

        cmd_vel_message.angular.z = cmd_vel_message.angular.z * 0.00;
        cmd_vel_message.linear.x = cmd_vel_message.linear.x * 0.00;
        cmd_vel_pub.publish(cmd_vel_message);
        loop_rate.sleep();
    ros::spinOnce();
}