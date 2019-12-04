#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
using namespace std;

//Publisher varible is initialised 
ros::Publisher cmd_vel_pub;

//A function for defining cmd_vel_message is created  
geometry_msgs::Twist SafetyMsg(float z){
    geometry_msgs::Twist cmd_vel_message;
    cmd_vel_message.angular.z = z;
    cout << cmd_vel_message << endl;
    return cmd_vel_message;
}

//The function with for the Wheel Drop. With pointers to Wheel and State 
    void SpinCallBack(){
        //ros::Duration(10.0).sleep();
        ros::Rate loop_rate(21);
        for(int i=0; i<=300; i++){ 
            cmd_vel_pub.publish(SafetyMsg(-0.6)); 
            loop_rate.sleep();
            }
        cout << "I am ready" << endl;
    }   

int main(int argc, char *argv[]){

    ros::init(argc, argv, "Spin");
    ros::NodeHandle n;

    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/navi", 1);
    
    SpinCallBack();
    return 0; 
}