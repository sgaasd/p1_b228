#include <ros/ros.h>
#include <kobuki_msgs/WheelDropEvent.h
using namespace std;



int main(int argc, char *argv[]){

    ros::init(argc, argv, "WheelDrop");
    ros::NodeHandle n;
    ros::Subscriber WheelDrop_sub = n.subscribe("/mobile_base/events/wheel_drop", 1, WheelDrop_callBack);");

    ros::spin();
    return 0;
}