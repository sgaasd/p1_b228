//Necessary libraries for the program are included 
#include <ros/ros.h>
#include <kobuki_msgs/BumperEvent.h>
#include <geometry_msgs/Twist.h>
#include <math.h>
using namespace std;

//Publisher varible is initialised 
ros::Publisher cmd_vel_pub;

//A function for defining cmd_vel_message is created  
geometry_msgs::Twist BumpMsg(float x, float z){
    geometry_msgs::Twist cmd_vel_message;
    cmd_vel_message.angular.z = z;
    cmd_vel_message.linear.x = x;
    cout << cmd_vel_message << endl;
    return cmd_vel_message;
}

//The function BumperCallBack tells if the bumper is pressed and which side 
void BumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg){
    geometry_msgs::Twist cmd_vel_message;
    bool hit = msg->state;
    int bump = msg->bumper;
    ros::Rate loop_rate(21);
    //The function should only should only start if the bumper is pressed 
    if (hit == 1) {
        //The robot should make different turns depending on which bumper is pressed 
        switch (bump){
            //If the bumper on the left side is pressed the robot will turn right
            case 0:
                for(int i=0; i<=42; i++){ 
                    cmd_vel_pub.publish(BumpMsg(-0.2, 0.0));
                    loop_rate.sleep();
                }
                for(int i=0; i<=42; i++){
                    cmd_vel_pub.publish(BumpMsg(0.0, -0.3));
                    loop_rate.sleep();
                }
            break;
            //If the bumper on the middle is pressed the robot will turn left 
            case 1:
                for(int i=0; i<=42; i++){ 
                    cmd_vel_pub.publish(BumpMsg(-0.2, 0.0));
                    loop_rate.sleep();
                }
                for(int i=0; i<=42; i++){
                    cmd_vel_pub.publish(BumpMsg(0.0, 0.3));
                    loop_rate.sleep();
                }
            break;
            //If the bumper on the right side is pressed the robot will turn left 
            case 2:
                for(int i=0; i<=42; i++){ 
                    cmd_vel_pub.publish(BumpMsg(-0.2, 0.0));
                    loop_rate.sleep();
                }
                for(int i=0; i<=42; i++){
                    cmd_vel_pub.publish(BumpMsg(0.0, 0.3));
                    loop_rate.sleep();
                }
            break;
        }
    }
}   

int main(int argc, char *argv[])
{
    //DriveStop_node is initialised
    ros::init(argc, argv, "DriveStop");

    //NodeHandle is defined 
    ros::NodeHandle n;

    //cmd_vel_pub is defined 
    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/safety_controller", 1);
    //Subcribing to "mobile_base/events/bumper". 
    //Evertime an advertisment is made on the topic "mobile_base/events/bumper" run "BumperCallBack"
    ros::Subscriber Bumper_sub = n.subscribe("mobile_base/events/bumper", 1, BumperCallback);

    //The program has run continuously 
    ros::spin();
    return 0;
}
