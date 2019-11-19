#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <math.h>

ros::Publisher cmd_vel_pub;

class move{
    public:

        float dist1;

        void distance(float distance){
            dist1 = distance;
        }

        void publis(const nav_msgs::Odometry::ConstPtr& msg){
            float PosX = msg->pose.pose.position.x;
            float PosY = msg->pose.pose.position.y;
            float driven = sqrt(PosX*PosX + PosY*PosY);

            std::cout << "Driven: " << driven << std::endl;
            std::cout << "1" << std::endl;

            if (driven < dist1){
                
                std::cout << "2" << std::endl;
                
                geometry_msgs::Twist cmd_vel_message;

                std::cout << "3" << std::endl;

                cmd_vel_message.angular.z = 0.0;
                cmd_vel_message.linear.x = 0.05;

                std::cout << "4" << std::endl;

                cmd_vel_pub.publish(cmd_vel_message);

                std::cout << "5" << std::endl;
        
            } else {
                geometry_msgs::Twist cmd_vel_message;
                cmd_vel_message.angular.z = 0.0;
                cmd_vel_message.linear.x = 0.00;
                cmd_vel_pub.publish(cmd_vel_message);
            }
        
        }
    private:
        
        
};

int main(int argc, char *argv[])
{
    float dist;
    ros::init(argc, argv, "Drive");

    std::cout << "Hvor langt skal den køre?" << std::endl;
    std::cin >> dist;

    ros::NodeHandle n;

    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1);
    
    move something;

    std::cout << "Jeg er nu før publishing og subscriber" << std::endl;

    something.dist1 = dist;

    ros::Subscriber odom_sub = n.subscribe("odom", 1, &move::publis, &something);
    
    std::cout << "Jeg er forbi publishing"  << std::endl;

    ros::spin();

    return 0;
}