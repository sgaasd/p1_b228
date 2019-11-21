#define _USE_MATH_DEFINES
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <math.h>

void drive(const nav_msgs::Odometry::ConstPtr& msg);


ros::Publisher cmd_vel_pub;

float dist1;
double angle1;
double angle2;
float dist2;
double grader;

float PrePosX = 0;
float PrePosY = 0;
double PrePosZ = 0;

bool CorSet = false;

int main(int argc, char *argv[])
{
    beginning:
    std::cout << "Hvor langt skal den først køre?" << std::endl;
    std::cin >> dist1;

    std::cout << "Hvor mange grader skal den dreje med?" << std::endl;
    std::cin >> grader;

    std::cout << "Hvor langt skal den til sidst køre?" << std::endl;
    std::cin >> dist2;

    ros::init(argc, argv, "Drive_Turn");

    ros::NodeHandle n;

    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1);
    
    ros::Subscriber odom_sub1 = n.subscribe("odom", 1, drive);
   
   
    
    ros::spin();

    return 0;
}

void drive(const nav_msgs::Odometry::ConstPtr& msg){

    if(CorSet == false) {
        PrePosX = msg->pose.pose.position.x;
        PrePosY = msg->pose.pose.position.y;
        PrePosZ = msg->pose.pose.orientation.z;
        CorSet = true;
    }

    float PosX = msg->pose.pose.position.x-PrePosX;
    float PosY = msg->pose.pose.position.y-PrePosY;
    double PosZ = msg->pose.pose.orientation.z-PrePosZ;
    float driven1 = sqrt(PosX*PosX + PosY*PosY);
    double AngleZ = msg->pose.pose.orientation.z;
  
    float driven2 = dist2 + dist1;
    
    
    std::cout << CorSet << std::endl;
    std::cout << "Coordinates1: " << PosX << ", " << PosY << std::endl;
    geometry_msgs::Twist cmd_vel_message;
    
    if (driven1 < dist1){       
        cmd_vel_message.angular.z = 0.0;
        cmd_vel_message.linear.x = 0.05;
        cmd_vel_pub.publish(cmd_vel_message);
    } 
    else {
        cmd_vel_message.angular.z = 0.0;
        cmd_vel_message.linear.x = 0.00;
        cmd_vel_pub.publish(cmd_vel_message);

        angle1 = (((grader * M_PI) / 180) / 2);
        angle2 = ((grader * M_PI) / 180);
        
            for (int i=0; i=2; i++){
                cmd_vel_message.angular.z = 0.38;
                cmd_vel_message.linear.x = 0.00;
                cmd_vel_pub.publish(cmd_vel_message);
                std::cout << "Angle in radians " << PosZ << std::endl;
                }
            
            if (driven1 < driven2){       
            cmd_vel_message.angular.z = 0.0;
            cmd_vel_message.linear.x = 0.05;
            cmd_vel_pub.publish(cmd_vel_message);
            }
           else {
                cmd_vel_message.angular.z = 0.0;
                cmd_vel_message.linear.x = 0.00;
                cmd_vel_pub.publish(cmd_vel_message);
                CorSet = false;
            }
        }
        
    
}
/*
void turn(const nav_msgs::Odometry::ConstPtr& msg){
    if(CorSet == false) {
        PrePosX = msg->pose.pose.position.x;
        PrePosY = msg->pose.pose.position.y;
        CorSet = true;
    }

    float PosX = msg->pose.pose.position.x-PrePosX;
    float PosY = msg->pose.pose.position.y-PrePosY;
    float driven1 = sqrt(PosX*PosX + PosY*PosY);

    

}

void drive2(const nav_msgs::Odometry::ConstPtr& msg){

    if(CorSet == false) {
        PrePosX = msg->pose.pose.position.x;
        PrePosY = msg->pose.pose.position.y;
        CorSet = true;
    }

    float PosX = msg->pose.pose.position.x-PrePosX;
    float PosY = msg->pose.pose.position.y-PrePosY;
    float driven1 = sqrt(PosX*PosX + PosY*PosY);

    //float driven2 = (driven1 + dist1);
    
    std::cout << CorSet << std::endl;
    std::cout << "Coordinates2: " << PosX << ", " << PosY << std::endl;
    geometry_msgs::Twist cmd_vel_message;
    
    float driven2 = dist2 + dist1;

     if (driven1 < driven2){       
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
*/