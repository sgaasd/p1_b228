#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <kobuki_msgs/Led.h>

void light(const nav_msgs::Odometry::ConstPtr& msg);

ros::Publisher led1_pub;
ros::Publisher led2_pub;

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "light_function");

    ros::NodeHandle n;

    led1_pub = n.advertise<kobuki_msgs::Led>("/mobile_base/commands/led1", 1);
    led2_pub = n.advertise<kobuki_msgs::Led>("/mobile_base/commands/led2", 1);
    
    ros::Subscriber led_sub = n.subscribe("led", 1, light);
    
    ros::spin();

    return 0;
}

void light(const nav_msgs::Odometry::ConstPtr& msg){

    kobuki_msgs::Led led_message;
    led1_pub.publish(led_message);
}