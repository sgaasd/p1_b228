#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
//#include <kobuki_msgs/Sound.h>
#include <sound_play/sound_play.h>

std::string path_to_sounds;

/* Declaration of function, so they can be called in main */
bool moveToGoal(double xGoal, double yGoal);
char choose();

/* Coordinates of locations on the map, whare the robot shall drive between*/
double xB228 = 1.181052;
double yB228 = 0.033761;

double xPrinterRoom = 2.200309;
double yPrinterRoom = 6.166436;

double xInfrontPrinterRoom = -0.619093;
double yInfrontPrinterRoom = 8.019430;

double xTechnicRoom = -2.259303;
double yTechnicRoom = -11.05786;

double xEndOfHall = -0.429280;
double yEndOFHall = -47.44047;

double xCornerDoor = 3.352420;
double yCornerDoor = -44.9245;


/* Declare goalReached. its used to print out a message when goal is reached */
bool goalReached = false;

int main(int argc, char** argv){

/* Initelizing ros */    
    ros::init(argc, argv, "MoveGoalV2_node");
    ros::NodeHandle n;
    sound_play::SoundClient sc;
    ros::spinOnce();
    path_to_sounds = "/home/ros/p1ws/src/p1_b228/busroute/sounds/";

/* User input to where the robot shall move to */
    char choice = 'q';
	
/* Sends the choosen coordinates to the function 'DriveToGoal' */
    do{
        choice = choose();

        switch (choice)
        {
        case '0':
            goalReached = moveToGoal(xB228, yB228);
            ROS_INFO("Moving to B228");
            break;
        case '1':
            goalReached = moveToGoal(xPrinterRoom, yPrinterRoom);
            ROS_INFO("Moving to Printer Room");
            break;
        case '2':
            goalReached = moveToGoal(xInfrontPrinterRoom, yInfrontPrinterRoom);
            ROS_INFO("Moving to In fromt of printer room");
            break;
        case '3':
            goalReached = moveToGoal(xTechnicRoom, yTechnicRoom);
            ROS_INFO("Moving to Technic room");
            break;
        case '4':
            goalReached = moveToGoal(xEndOfHall, yEndOFHall);
            ROS_INFO("Moving to End of hall");
            break;
        case '5':
            goalReached = moveToGoal(xCornerDoor, yCornerDoor);
            ROS_INFO("Moving to Corner Door");
            break;
        
        default:
            ROS_ERROR("Input a number between 0-5");
            break;
        }
        if (choice!='q'){
         if (goalReached){
            ROS_INFO("Congratulations!");
            ros::spinOnce();
            sc.playWave(path_to_sounds+"toaster_oven_ding.wav");
         }else{
            ROS_INFO("Hard Luck!");
            sc.playWave(path_to_sounds+"short_buzzer.wav");
         }
      }
    }while (choice != 'q');
    return 0;
}

bool moveToGoal(double xGoal, double yGoal){
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
        return true;
    }
    else
    {
        ROS_ERROR("The distination cannot be reached");
        return false;
    }
}

char choose(){
    char choice='q';
	std::cout<<"|------------------------------------------------------------------------|"<<std::endl;
	std::cout<<"|PRESS A NUMBER EQUAL TO THE LOCATION OF THE DISTINATION - OR 'q' TO EXIT:"<<std::endl;
	std::cout<<"|'0': B228 "<<std::endl;
	std::cout<<"|'1': Printer room "<<std::endl;
    std::cout<<"|'2': Infront Printer Room "<<std::endl;
    std::cout<<"|'3': Technic Room "<<std::endl;
    std::cout<<"|'4': End Of Hall "<<std::endl;
	std::cout<<"|'5': Corner Door "<<std::endl;
	std::cout<<"|'q': Quit "<<std::endl;
	std::cout<<"|------------------------------------------------------------------------|"<<std::endl;
	std::cout<<"|DISTINATION? (END BY PRESSING 'ENTER')";
	std::cin>>choice;

	return choice;
}

