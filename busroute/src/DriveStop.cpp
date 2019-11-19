#include <ros/ros.h>
#include <kobuki_msgs/BumperEvent.h>
#include <geometry_msgs/Twist.h>
#include <math.h>
using namespace std;

ros::Publisher cmd_vel_pub;

class move{
    public:
        void BumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg){
            geometry_msgs::Twist cmd_vel_message;
            bool hit = msg->state;
            int bump = msg->bumper;
            ros::Rate loop_rate(1);
            if (hit == 1) {
                cmd_vel_message.angular.z = 0.00;
                cmd_vel_message.linear.x = -0.10;
                cmd_vel_pub.publish(cmd_vel_message);
                cout << cmd_vel_message << endl;
                loop_rate.sleep();
                cmd_vel_message.angular.z = 0.78;
                cmd_vel_message.linear.x = 0.00;
                cmd_vel_pub.publish(cmd_vel_message);
                cout << cmd_vel_message << endl;
                }
        }   
};

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "DriveStop");

    ros::NodeHandle n;

    move something;

    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/safety_controller", 1);
    ros::Subscriber Bumper_sub = n.subscribe("mobile_base/events/bumper", 1, &move::BumperCallback, &something);

    ros::spin();
    return 0;
}
