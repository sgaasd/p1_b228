/*#include <ros/ros.h>
#include <kobuki_msgs/WheelDropEvent.h
using namespace std;



int main(int argc, char *argv[]){

    ros::init(argc, argv, "WheelDrop");
    ros::NodeHandle n;
    ros::Subscriber WheelDrop_sub = n.subscribe("/mobile_base/events/wheel_drop", 1, WheelDrop_callBack);");

    ros::spin();
    return 0;
}*/

#include <ros/ros.h>
#include <kobuki_msgs/BumperEvent.h>
using namespace std;

void BumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg){
    bool hit = msg->state;
    int bump = msg->bumper;
        if (hit==1)
        {

            cout << "Bumper " << bump << " er trykket" << endl;
        }
        else {
            cout << "bumper er ikke trykket" << endl;
        }
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "Bumper");
    ros::NodeHandle n;
    ros::Subscriber Bumper_sub = n.subscribe("mobile_base/events/bumper", 10, BumperCallback);

    ros::spin();
    return 0;
}
