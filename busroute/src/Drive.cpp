#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>

float PosX = 0;
float PosY = 0;
float PrePosX;
float PrePosY;
float dist = 0;
float driven = 0;


class Something
{
public:
    void operator()(const nav_msgs::Odometry::ConstPtr& msg)
    {
        PosX = msg->pose.pose.position.x;
        PosY = msg->pose.pose.position.y;
        std::cout << "Ha " << std::endl;
    }
    void callback(const nav_msgs::Odometry::ConstPtr& msg)
    {
        PosX = msg->pose.pose.position.x;
        PosY = msg->pose.pose.position.y;
        std::cout << "Ha " << std::endl;
    }
};


void chatterCallback(const nav_msgs::Odometry::ConstPtr& msg){
    PosX = msg->pose.pose.position.x;
    PosY = msg->pose.pose.position.y;
    ROS_INFO( "Hello from ROS ");
//    std::cout << "mha" << std::endl;
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "Drive");

    std::cout << "Hvor langt skal den køre?" << std::endl;
    std::cin >> dist; // odom_sub

    ros::NodeHandle n;

    ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1);
    
    ros::Subscriber odom_sub = n.subscribe("odom", 1, chatterCallback);
    //boost::shared_ptr<Something> something = boost::make_shared<Something>();
    // ros::Subscriber odom_sub = n.subscribe("odom", 1, &Something::callback, something );


    while (ros::ok)
    {  
        // chatterCallback();
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


        std::cout << driven << " out of " << dist << " driven." << std::endl;

        //std::cout << PrePosX << ", " << PrePosY << std::endl;
    }
    
    return 0;

}