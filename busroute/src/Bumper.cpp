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
