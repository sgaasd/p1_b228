#include <ros/ros.h>
#include <kobuki_msgs/ButtonEvent.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
//#include <sound_play/sound_play.h>

//std::string path_to_sounds;

/* Declaration of function, so they can be called in main */
//bool ButtonCallback(const kobuki_msgs::ButtonEvent::ConstPtr& msg);

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



void ButtonCallback(const kobuki_msgs::ButtonEvent::ConstPtr& msg){
    bool Pressed = msg->state;
    int Button = msg->button;
    if (Pressed==true){
        switch (Button){
            case 0:
                xGoal = xB228;
                yGoal = yB228;
            break; 
            case 1:
                xGoal = xPrinterRoom;
                yGoal = yPrinterRoom;
            break;  
            case 2: 
                xGoal = xTechnicRoom;
                yGoal = yTechnicRoom;
            break;
        } 
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

    ac.waitForResult();

    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
        ROS_INFO("The distination has been reached");
        //return true;
    }
    else
    {
        ROS_ERROR("The distination cannot be reached");
        //return false;
    }
}

int main(int argc, char** argv){

/* Initelizing ros */    
    ros::init(argc, argv, "MoveToGoal_fin_node");
    ros::NodeHandle n;
    //sound_play::SoundClient sc;
    ros::spin();
    //path_to_sounds = "/home/ros/p1ws/src/p1_b228/busroute/sounds/";

    ros::Subscriber Button_sub = n.subscribe("mobile_base/events/button", 10, ButtonCallback);

    return 0;
}
