#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_datatypes.h>
//#include <duration.h>

using namespace std;

//Publisher varible is initialised 
ros::Publisher cmd_vel_pub;

//void SpinCallBack(const nav_msgs::Odometry::ConstPtr& msg);



//A function for defining cmd_vel_message is created  
geometry_msgs::Twist SafetyMsg(float z){
    geometry_msgs::Twist cmd_vel_message;
    cmd_vel_message.angular.z = z;
    cout << cmd_vel_message << endl;
    return cmd_vel_message;
}

//The function with for the Wheel Drop. With pointers to Wheel and State 
    void SpinCallBack(const nav_msgs::Odometry::ConstPtr& msg){
        ros::Duration(10.0).sleep();
        tf::Quaternion q(msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
        tf::Matrix3x3 m(q);
        double roll, pitch, yaw;
        m.getRPY(roll, pitch, yaw);

        ros::Rate loop_rate(1);
        cout << yaw << endl;

        if (yaw < 180){
            cmd_vel_pub.publish(SafetyMsg(1.0));
             cout << yaw << endl;
        }
        loop_rate.sleep();

            /*    ros::Duration four_seconds(4.0);
        ros::Rate loop_rate(21);
        for(int i=0; i<=84; i++){ 
            cmd_vel_pub.publish(SafetyMsg((6.2831853072 / 4))); //Turns 360 degrees
            loop_rate.sleep();
            }*/
        cout << "I am ready" << endl;

        exit(1);
    }   

int main(int argc, char *argv[]){

    ros::init(argc, argv, "Spin");
    ros::NodeHandle n;

    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1);
    ros::Subscriber odom_sub = n.subscribe("odom", 1, SpinCallBack);



    return 0; 
}