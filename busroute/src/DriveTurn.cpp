#define _USE_MATH_DEFINES
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <math.h>
#include <tf/transform_datatypes.h>

void drive(const nav_msgs::Odometry::ConstPtr& msg);

ros::Publisher cmd_vel_pub;

float dist1;
float angle1;
float angle2;
float dist2;
float grader;

float PrePosX = 0;
float PrePosY = 0;
float PrePosZ = 0;
float PrePosX1 = 0;
float PrePosY1 = 0;

bool CorSet = false;
bool CorSet1 = false;

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

// Dette er nyt til at omregne quaternion til euler angle
//https://answers.ros.org/question/50113/transform-quaternion/
//https://gist.github.com/marcoarruda/f931232fe3490b7fa20dbb38da1195ac

    tf::Quaternion q(msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
    tf::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);
    std::cout << "Roll: " << roll << ", Pitch: " << pitch << ", Yaw: " << yaw << std::endl;
// her slutter omregningen og yaw bruges nede i if statement

    if(CorSet == false) {
        PrePosX = msg->pose.pose.position.x;
        PrePosY = msg->pose.pose.position.y;
        CorSet = true;
    }
    if(CorSet1 == false) {
        PrePosX1 = msg->pose.pose.position.x;
        PrePosY1 = msg->pose.pose.position.y;
        CorSet1 = true;
    }

    float PosX = msg->pose.pose.position.x-PrePosX;
    float PosY = msg->pose.pose.position.y-PrePosY;
    float PosZ = msg->pose.pose.orientation.z-PrePosZ;
    float driven1 = sqrt(PosX*PosX + PosY*PosY);
<<<<<<< HEAD
    float AngleZ = msg->pose.pose.orientation.z;
  
    float driven2 = dist2 + dist1;
=======
    double AngleZ = msg->pose.pose.orientation.z;

    float PosX1 = msg->pose.pose.position.x-PrePosX1;
    float PosY1 = msg->pose.pose.position.y-PrePosY1;
 float driven2 = sqrt(PosX1*PosX1 + PosY1*PosY1);
>>>>>>> e32dabc568d3c91df27b17ddd696d66575d9b978
    
    ros::Rate loop_rate(1);
    
    std::cout << CorSet << std::endl;
   
    geometry_msgs::Twist cmd_vel_message;
    
    if (driven1 < dist1){       
        cmd_vel_message.angular.z = 0.0;
        cmd_vel_message.linear.x = 0.05;
        cmd_vel_pub.publish(cmd_vel_message);
        std::cout << "Coordinates1: " << PosX << ", " << PosY << std::endl;
    } 
    else {
        cmd_vel_message.angular.z = 0.0;
        cmd_vel_message.linear.x = 0.00;
        cmd_vel_pub.publish(cmd_vel_message);

        angle1 = (((grader * M_PI) / 180) / 2);
        angle2 = ((grader * M_PI) / 180);
<<<<<<< HEAD
        
<<<<<<< HEAD
            for (int i=0; i=2; i++){
                cmd_vel_message.angular.z = 0.38;
                cmd_vel_message.linear.x = 0.00;
                cmd_vel_pub.publish(cmd_vel_message);
                std::cout << "Angle in radians " << PosZ << std::endl;
                }
                cmd_vel_message.angular.z = 0.0;
                cmd_vel_pub.publish(cmd_vel_message);

            if (driven1 < driven2){       
=======
            if(PosZ < angle1){
            cmd_vel_message.angular.z = 0.38;
            cmd_vel_message.linear.x = 0.00;
            cmd_vel_pub.publish(cmd_vel_message);
            std::cout << "Angle in radians posZ " << PosZ << std::endl;
            std::cout << "Angle in radians angle2 " << angle2 << std::endl;
            std::cout << "Angle in radians angle1 " << angle1 << std::endl;
            }
            if(PosZ > angle2){
        CorSet = false;
=======

// if statement hvor yaw bliver større og større indtil den rammer angle 2
        if(yaw < angle2){
        cmd_vel_message.angular.z = 0.10;
        cmd_vel_message.linear.x = 0.00;
        cmd_vel_pub.publish(cmd_vel_message);
        std::cout << "Angle in radians posZ " << PosZ << std::endl;
        std::cout << "Angle in radians yaw " << yaw << std::endl;
        std::cout << "Angle in radians angle2 " << angle2 << std::endl;
        std::cout << "Angle in radians angle1 " << angle1 << std::endl;
        CorSet1 = false;
        }
        else{
>>>>>>> 4061d02ac4ddffddcda927069c6143d81cd9b1e4
            cmd_vel_message.angular.z = 0.00;
            cmd_vel_message.linear.x = 0.00;
            cmd_vel_pub.publish(cmd_vel_message);
            
            
            if (driven2 < dist2){
                cmd_vel_message.angular.z = 0.00;
                cmd_vel_message.linear.x = 0.05;
                cmd_vel_pub.publish(cmd_vel_message);
                std::cout << "driven1 " << driven1 << "driven2 " << driven2 << std::endl;
            }
<<<<<<< HEAD
           /* if (driven1 < driven2){       
>>>>>>> db3ae3ada26cbf2be264d2e98d0012095e1c8b92
            cmd_vel_message.angular.z = 0.0;
            cmd_vel_message.linear.x = 0.05;
            cmd_vel_pub.publish(cmd_vel_message);
            }
           else {
                cmd_vel_message.angular.z = 0.0;
=======
            else{
                cmd_vel_message.angular.z = 0.00;
>>>>>>> 4061d02ac4ddffddcda927069c6143d81cd9b1e4
                cmd_vel_message.linear.x = 0.00;
                cmd_vel_pub.publish(cmd_vel_message);
                CorSet = true;
                CorSet1 = true;
                std::exit;
            }
                
                
        }
          
    }    
    
}
