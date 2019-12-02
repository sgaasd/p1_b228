#include <ros/ros.h>
#include <kobuki_msgs/ButtonEvent.h>
#include <iostream>
using namespace std;

void ButtonCallback(const kobuki_msgs::ButtonEvent::ConstPtr& msg){ 
    bool B0Pressed = msg->state;
    bool B1Pressed = msg->state;
    bool B2Pressed = msg->state;
    int B0 = msg->button;
    int B1 = msg->button;
    int B2 = msg->button;
    
    if (B0Pressed == true && B0 == 0){
        std::cout << "B0 = " << B0Pressed << std::endl;

    }
    else if (B1Pressed == true && B1 == 1){
        std::cout << "B1 = " << B1Pressed << std::endl;
    }
    else if (B2Pressed == true && B2 == 2){
        std::cout << "B2 = " << B2Pressed << std::endl;
    }
    else {
        std::cout << "Du har ikke trykket på en knap" << std::endl;
    }
}


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "Buttons");
    ros::NodeHandle n;
    ros::Subscriber Button_sub = n.subscribe("mobile_base/events/button", 10, ButtonCallback);


    ros::spin();
    return 0;
}
