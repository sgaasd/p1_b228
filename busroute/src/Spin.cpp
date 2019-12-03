#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
using namespace std;

//Publisher varible is initialised 
ros::Publisher cmd_vel_pub;

//A function for defining cmd_vel_message is created  
geometry_msgs::Twist SafetyMsg(float x, float z){
    geometry_msgs::Twist cmd_vel_message;
    cmd_vel_message.angular.z = z;
    cmd_vel_message.linear.x = x;
    cout << cmd_vel_message << endl;
    return cmd_vel_message;
}

//The function with for the Wheel Drop. With pointers to Wheel and State 
    void SpinCallBack(){
        ros::Rate loop_rate(21);
        for(int i=0; i<=84; i++){ 
            cmd_vel_pub.publish(SafetyMsg(0.0, (6.2831853072 / 4))); //Turns 360 degrees
            loop_rate.sleep();
            }
        cout << "I am ready" << endl;
        
        exit(1);
    }   

int main(int argc, char *argv[]){

    ros::init(argc, argv, "Spin");
    ros::NodeHandle n;

    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1);

    SpinCallBack(); 

    return 0; 
}



