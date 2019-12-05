#include <ros/ros.h>
#include <kobuki_msgs/Led.h>
#include <string>
#include <actionlib_msgs/GoalStatusArray.h>
#include <actionlib_msgs/GoalStatus.h>
#include <actionlib_msgs/GoalID.h>
#include "std_msgs/Header.h"
#include <geometry_msgs/PoseStamped.h>

void light(int a, int b);
void showStatus(const actionlib_msgs::GoalStatusArray::ConstPtr& msg);
void StatusPublisher(const actionlib_msgs::GoalStatusArray::ConstPtr& status);
void setSeq(const geometry_msgs::PoseStamped::ConstPtr& msg);

int seq = 0;

ros::Publisher led1_pub;
ros::Publisher led2_pub;
ros::Publisher status_pub;

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "Drive_function");
    ros::NodeHandle n;
    led1_pub = n.advertise<kobuki_msgs::Led>("/mobile_base/commands/led1", 1);
    led2_pub = n.advertise<kobuki_msgs::Led>("/mobile_base/commands/led2", 1);
    status_pub = n.advertise<actionlib_msgs::GoalStatusArray>("/move_base/status", 1);
    ros::Subscriber status_sub = n.subscribe("/move_base/status", 1, showStatus);
    ros::Subscriber seq_sub = n.subscribe("/move_base_simple/goal", 1, setSeq);
    ros::spin();
}

void setSeq(const geometry_msgs::PoseStamped::ConstPtr& msg){
    int seq = msg->header.seq;
    std::cout << "seq = " << seq << std::endl;
}

void showStatus(const actionlib_msgs::GoalStatusArray::ConstPtr& msg){
    if (msg->status_list.empty() == 1){
        std::cout << "statuslist er tom!" << std::endl;
        light(1, 'o');
        light(2, 'o');
    } else {
        
        actionlib_msgs::GoalStatus goalStatus = msg->status_list[seq];
        int x = goalStatus.status;

        switch (x)
        {
        case 0: //PENDING
            light(1, 'o');
            light(2, 's');
            break;

        case 1: //ACTIVE
            light(1, 'r');
            light(2, 'o');
            break;
        
        case 2: //PREEMPTED
            light(1, 'r');
            light(2, 'r');
            break;

        case 3: //SUCCEEDED
            light(1, 'g');
            light(2, 'o');
            break;

        case 4: //ABORTED
            light(1, 'r');
            light(2, 'r');
            break;

        case 5: //REJECTED
            light(1, 'r');
            light(2, 'o');
            break;

        case 6: //PREEMPTING
            light(1, 'r');
            light(2, 'r');
            break;

        case 7: //RECALLING
            light(1, 'o');
            light(2, 'r');
            break;
        
        case 8: //RECALLED
            light(1, 'o');
            light(2, 'o');
            break;
        
        case 9: //LOST
            light(1, 'r');
            light(2, 'r');
            break;

        default:
            std::cout << x << " er ikke en valid status!"<< std::endl;
            break;
        
        }
    
    }
}

void light(int a, int b){
    kobuki_msgs::Led led_message;
    int c;
    switch (b){
    case 's':
        c = 0;
        break;
    
    case 'g':
        c = 1;
        break;
    
    case 'o':
        c = 2;
        break;
    
    case 'r':
        c = 3;
        break;
        
    default:
        std::cout << b << " er ikke en mulig farve" << std::endl;
        break;
    }

    led_message.value = c;
    
    switch(a){
        case 1:
            led1_pub.publish(led_message);
            break;
        case 2:
            led2_pub.publish(led_message);
            break;

        default:
            std::cout << "led " << a << "eksisterer ikke!" << std::endl;
            break;    
    }
}
