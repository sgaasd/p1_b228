#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>

float PosX = 0;
float PosY = 0;
float PrePosX;
float PrePosY;
float dist = 0;
float driven = 0;

class something
{
public:
   void operator(const nav_msgs::Odometry::ConstPtr& msg)
};


void chatterCallback(const nav_msgs::Odometry::ConstPtr& msg){
    PosX = msg->pose.pose.position.x;
    PosY = msg->pose.pose.position.y;
    std::cout << "mha" << std::endl;
    }

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "Drive");

    std::cout << "Hvor langt skal den køre?" << std::endl;
    std::cin >> dist;

    ros::NodeHandle n;

    ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/teleop", 1);
    
    ros::Subscriber odom_sub = n.subscribe("odom", 1, something());


    while (ros::ok)
    {  
        //chatterCallback();
        driven = sqrt(((PosX*PosX)+(PosY*PosY)));

            if(driven < dist){
            geometry_msgs::Twist cmd_vel_message;
            cmd_vel_message.linear.x = 0.05;
            cmd_vel_pub.publish(cmd_vel_message);
        } else {
            geometry_msgs::Twist cmd_vel_message;
            cmd_vel_message.linear.x = 0.05;
            cmd_vel_pub.publish(cmd_vel_message);
        }

<<<<<<< HEAD
    geometry_msgs::Twist cmd_vel_message;
    cmd_vel_message.angular.z = 0.0;
    cmd_vel_message.linear.x = 0.25;

//1 meter --> x = 0.25 --> for_loop = 40
//1 meter --> x = 0.50 --> for_loop = 20
//1 meter --> x = 1 --> for_loop = loop_rate

    ros::Rate loop_rate(10);
<<<<<<< HEAD
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
=======
    ros::spin();
>>>>>>> 6d913cffa8e11ab219bfa56f3492e78f2cd486f6
=======
        std::cout << driven << " out of " << dist << " driven." << std::endl;

        //std::cout << PrePosX << ", " << PrePosY << std::endl;
    }
    
    return 0;

>>>>>>> a5fedaa876cdabb6f708866e5089eacec9fa7792
}