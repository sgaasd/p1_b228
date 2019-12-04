#include <ros/ros.h>
#include <kobuki_msgs/ButtonEvent.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <kobuki_msgs/Led.h>
//#include <sound_play/sound_play.h>

//std::string path_to_sounds;
//sound_play::SoundClient sc;

ros::Publisher led1_pub;
ros::Publisher led2_pub;

/* Coordinates of locations on the map, whare the robot shall drive between*/
double xB228 = 1.181052;
double yB228 = 0.033761;

double xPrinterRoom = 2.200309;
double yPrinterRoom = 6.166436;

double xTechnicRoom = -2.259303;
double yTechnicRoom = -11.05786;

double xGoal = 0.0;
double yGoal = 0.0;

/* Declare goalReached. its used to print out a message when goal is reached */
bool goalReached = false;

void light(int a, int b);

void ButtonCallback(const kobuki_msgs::ButtonEvent::ConstPtr& msg){
    bool Pressed = false;
    int Button = 5;
    Pressed = msg->state;
    Button = msg->button;
    //path_to_sounds = "/home/ros/p1ws/src/p1_b228/busroute/sounds/";
    ROS_INFO("buttoncallback startet");
    if (Pressed == true){
        ROS_INFO("kører if statemant");
        
        if (Button == 0)
        {
            xGoal = xB228;
            yGoal = yB228;
            ROS_INFO("B228 i  if");
        }
        else if (Button == 1)
        {
            xGoal = xPrinterRoom;
            yGoal = yPrinterRoom;
            ROS_INFO("printerrum i  if");
        }
        else if (Button == 2)
        {
            xGoal = xTechnicRoom;
            yGoal = yTechnicRoom;
            ROS_INFO("Teknikrum i  if");
        }
         
    
/* Setting up the publsher - 'move_base' server through a 'SimpleActionClient' */
        actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);

/* Setting a timer, so the 'action server' can come up , and it will wait for mak. 5 sec.*/
        while (!ac.waitForServer(ros::Duration(5.0))){
            ROS_INFO("Program waitin for the 'move_base action server' to post");
        }

        move_base_msgs::MoveBaseGoal goal;

/* Declaring the coordiantes used in this node to reference to the absolute coordinates nemed in the "map" file */
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();
ROS_INFO("lige før den sender xGoal og yGoal");
/* Moving the robot towards its distination point */
        goal.target_pose.pose.position.x = xGoal;
        goal.target_pose.pose.position.y = yGoal;
        goal.target_pose.pose.position.z = 00.00;

        goal.target_pose.pose.orientation.x = 00.00;
        goal.target_pose.pose.orientation.y = 00.00;
        goal.target_pose.pose.orientation.z = 00.00;
        goal.target_pose.pose.orientation.w = 1.00;

        ROS_INFO("Moving towards the distination");
        ac.sendGoal(goal);
        light(1, 'o');
        light(2, 'o');

        ac.waitForResult();

        if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
            ROS_INFO("The distination has been reached");
            light(1, 'g');
            light(2, 'g');
            //sc.playWave(path_to_sounds+"toaster_oven_ding.wav");
        
        }
        else{
        ROS_ERROR("The distination cannot be reached");
        light(1, 'r');
        light(2, 'r');
        //sc.playWave(path_to_sounds+"short_buzzer.wav");
        
        }
    }
}

int main(int argc, char** argv){

/* Initelizing ros */    
    ros::init(argc, argv, "MoveToGoal_fin_node");
    ros::NodeHandle n;

    std::cout << "noden er startet" << std::endl;
    std::cout << "B228 kordinater" << xB228 << "|||||" << yB228 << std::endl;
    
    led1_pub = n.advertise<kobuki_msgs::Led>("/mobile_base/commands/led1", 1);
    led2_pub = n.advertise<kobuki_msgs::Led>("/mobile_base/commands/led2", 1);
    ros::Subscriber Button_sub = n.subscribe("mobile_base/events/button", 1, ButtonCallback);
    ros::spin();
    return 0;
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