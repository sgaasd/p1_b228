#include <ros/ros.h>
#include <kobuki_msgs/Led.h>
#include <string>
#include <actionlib_msgs/GoalStatusArray.h>

void light(int a, int b);
void showStatus(const actionlib_msgs::GoalStatusArray::ConstPtr& msg);


ros::Publisher led1_pub;
ros::Publisher led2_pub;


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "Drive_function");
    ros::NodeHandle n;

    led1_pub = n.advertise<kobuki_msgs::Led>("/mobile_base/commands/led1", 1);
    led2_pub = n.advertise<kobuki_msgs::Led>("/mobile_base/commands/led2", 1);

    ros::Subscriber odom_sub = n.subscribe("/move_base/status", 1, showStatus);

}

void showStatus(const actionlib_msgs::GoalStatusArray::ConstPtr& msg){
    int a = msg->status_list.status;
    switch (a)
    {
    case 1:
        light(1, g);
        break;
    
    case 2:
        light(1, g);
        break;

    case 3:
        light(1, g);
        break;

    case 4:
        light(1, g);
        break;

    case 5:
        light(1, g);
        break;

    case 6:
        light(1, g);
        break;

    case 7:
        light(1, g);
        break;
    
    case 8:
        light(1, g);
        break;
    
    case 9:
        light(1, g);
        break;

    default:
        std::cout << a << " er ikke en valid status!"<< std::endl;
        break;
    
    }

}

void light(int a, char b){
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
            std::cout << "led " << a << "eksisterer ikke!" std::endl;
            break;    
    }
}