#include <ros/ros.h>
#include <kobuki_msgs/BumperEvent.h>

void BumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg){
    int bump = msg->state;
    
    
    if (bump ==1)
    {
         std::cout << "bumper er trykket" << std::endl;
    }
    else {
        std::cout << "bumper er ikke trykket" << std::endl;
    }
}



int main(int argc, char *argv[])
{
    ros::init(argc, argv, "Bumper");
    ros::NodeHandle n;
ros::Subscriber Bumper_sub = n.subscribe("mobile_base/events/bumper", 1, BumperCallback);
   
    
    
    return 0;
}
