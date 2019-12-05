#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

bool moveToGoal(double xGoal, double yGoal);

bool goalReached = false;

int main(int argc, char** argv){

/* Initelizing ros */    
    ros::init(argc, argv, "test_goal_node");
    ros::NodeHandle n;
    ros::spin();


/* User input to where the robot shall move to */
    char choice = 'q';
	
/* Sends the choosen coordinates to the function 'DriveToGoal' */
   
    return 0;
}


bool moveToGoal(double xGoal, double yGoal){
/* Setting up the publsher - 'move_base' server through a 'SimpleActionClient' */
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);


    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
        ROS_INFO("The distination has been reached --------- test");
        return true;
    }
    else
    {
        ROS_ERROR("The distination cannot be reached");
        return false;
    }
}