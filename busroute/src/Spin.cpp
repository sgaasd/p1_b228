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

    //The function "SpinCallBack" tells the robot to turn around it self 
    void SpinCallBack(){
        //ros::Duration(10.0).sleep();
        ros::Rate loop_rate(1);
        for(int i=0; i<=21; i++){ 
            cmd_vel_pub.publish(SafetyMsg(-0.6)); 
            loop_rate.sleep();
            }
        cout << "I am ready" << endl;
    }   

int main(int argc, char *argv[]){

    //Initelizing ros   
    ros::init(argc, argv, "Spin");
    ros::NodeHandle n;

    //cmd_vel_pub is defined 
    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/navi", 1000);
    

    //Calls the function "SpinCallBack"
    SpinCallBack();
    
    return 0; 
}