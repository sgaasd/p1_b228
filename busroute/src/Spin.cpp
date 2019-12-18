#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

/*Publisher varible is declared */
ros::Publisher cmd_vel_pub;

/*A function for defining cmd_vel_message is created*/
geometry_msgs::Twist SpinMsg(float z){
    geometry_msgs::Twist cmd_vel_message;
    cmd_vel_message.angular.z = z;
    return cmd_vel_message;
}
    /*The function "SpinCallBack" tells the robot to turn around it self*/
    void SpinCallBack(){
        /*loop rate is set to 8, and the for loop wil run for 200 iterations. 
        This makes the robot spin approximately 2 turns on its own axis.*/
        ros::Rate loop_rate(8);
        for(int i=0; i<=200; i++){ 
            cmd_vel_pub.publish(SpinMsg(-0.6)); 
            loop_rate.sleep();
            }
        ROS_INFO("The robot is ready");
    }   

int main(int argc, char *argv[]){

    /*Initializing the node "Spin"*/
    ros::init(argc, argv, "Spin");
    ros::NodeHandle n;

    /*cmd_vel_pub is initialized*/
    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/navi", 1);
    
    /*Calls the function "SpinCallBack"*/
    SpinCallBack();
    
    return 0; 
}
