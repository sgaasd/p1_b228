#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

/* Declaration of function, so they can be called in main */
bool DriveToGoal(double xGoal, double yGoal);
char choose();

/* Coordinates of locations on the map, whare the robot shall drive between*/
double xB228 = 1.181052;
double yB228 = 0.033761;

double xPrinterRum = 2.200309;
double yPrinterRum = 6.166436;

double xRum = 00.00;
double yRum = 00.00;

double xRum1 = 00.00;
double yRum1 = 00.00;


/* Declare goalReached. its used to print out a message when goal is reached */
bool GoalReached = false;

int main(int argc, char** argv){

/* Initelizing ros */    
    ros::init(argc, argv, "MoveGoalV2_node");
    ros::NodeHandle n;
    ros::spinOnce();

/* User input to where the robot shall move to */
    char choice = 'q';
	
/* Sends the choosen coordinates to the function 'DriveToGoal' */
    do{
         choice = choose();
        if (choice == '0'){
            GoalReached = DriveToGoal(xB228, yB228);
        }
        else if (choice == '1'){
            GoalReached = DriveToGoal(xPrinterRum, yPrinterRum);
        }
        else if (choice == '2'){
            GoalReached = DriveToGoal(xRum, yRum);
        }
        else if (choice == '3'){
            GoalReached = DriveToGoal(xRum1, yRum1);
        }
        if (choice != 'q'){
            if (GoalReached){
                ROS_INFO("The Distination has been reached");
                ros::spinOnce();
            }
            else{
                ROS_INFO("The distination has NOT been reached");
            } 
        }  
    } while (choice != 'q');
    
    return 0;
}

bool DriveToGoal(double xGoal, double yGoal){
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

    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
        ROS_INFO("The distination has been reached");
        return true;
    }
    else
    {
        ROS_INFO("The distination cannot be reached");
        return false;
    }
}

char choose(){
    char choice='q';
	std::cout<<"|-------------------------------|"<<std::endl;
	std::cout<<"|PRESS A NUMBER EQUAL TO THE LOCATION OF THE DISTINATION - OR 'q' TO EXIT:"<<std::endl;
	std::cout<<"|'0': B228 "<<std::endl;
	std::cout<<"|'1': Printer rum "<<std::endl;
    std::cout<<"|'2': RUM "<<std::endl;
	std::cout<<"|'3': RUM1 "<<std::endl;
	std::cout<<"|'q': Quit "<<std::endl;
	std::cout<<"|-------------------------------|"<<std::endl;
	std::cout<<"|DISTINATION? (END BY PRESSING 'ENTER')";
	std::cin>>choice;

	return choice;
}

