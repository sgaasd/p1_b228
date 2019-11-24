#include <ros/ros.h>
#include <kobuki_msgs/CliffEvent.h>
#include <geometry_msgs/Twist.h>
#include <math.h>
using namespace std;

//Publisher varible is initialised 
ros::Publisher cmd_vel_pub;

//A function for defining cmd_vel_message is created  
geometry_msgs::Twist CliffMsg(float x, float z){
    geometry_msgs::Twist cmd_vel_message;
    cmd_vel_message.angular.z = z;
    cmd_vel_message.linear.x = x;
    cout << cmd_vel_message << endl;
    return cmd_vel_message;
}

//The function CliffCallBack tells if the cliss sensor is activated and which side 
void CliffCallback(const kobuki_msgs::CliffEvent::ConstPtr& msg){
    geometry_msgs::Twist cmd_vel_message;
    bool cliffs = msg->state;
    int sensors = msg->sensor;
    ros::Rate loop_rate(21);
    //The function should only should only start if the Cliss sensor is activated 
    if (cliffs == 1) {
        //The robot should make different turns depending on which sensor is activated 
        switch (sensors){
            //If the sensor on the left side is pressed the robot will turn right
            case 0:
                for(int i=0; i<=42; i++){
                    cmd_vel_pub.publish(CliffMsg(0.0, -0.4));
                    loop_rate.sleep();
                }
            break;
            //If the sensor on the middle is activated the robot will turn left 
            case 1:
                for(int i=0; i<=42; i++){
                    cmd_vel_pub.publish(CliffMsg(0.0, 0.6));
                    loop_rate.sleep();
                }
            break;
            //If the sensor on the right side is pressed the robot will turn left 
            case 2:
                for(int i=0; i<=42; i++){
                    cmd_vel_pub.publish(CliffMsg(0.0, 0.4));
                    loop_rate.sleep();
                }
            break;
        }
    }
}   

int main(int argc, char *argv[])
{
    //DriveStop_node is initialised
    ros::init(argc, argv, "Cliff");

    //NodeHandle is defined 
    ros::NodeHandle n;

    //cmd_vel_pub is defined 
    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/safety_controller", 1);
    //Subcribing to "/mobile_base/events/cliff". 
    //Evertime an advertisment is made on the topic "/mobile_base/events/cliff" run "CliffCallBack"
    ros::Subscriber Cliff_sub = n.subscribe("/mobile_base/events/cliff", 1, CliffCallback);

    //The program has run continuously 
    ros::spin();
    return 0;
}