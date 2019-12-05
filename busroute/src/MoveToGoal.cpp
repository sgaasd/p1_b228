#include <ros/ros.h>
#include <kobuki_msgs/ButtonEvent.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <kobuki_msgs/Led.h>
using namespace std; 

//Publisher varibles are initialised 
ros::Publisher led1_pub;
ros::Publisher led2_pub;

//Coordinates of locations on the map, where the robot shall drive between
double xB228 = 1.181052;
double yB228 = 0.033761;

double xPrinterRoom = 2.200309;
double yPrinterRoom = 6.166436;

double xTechnicRoom = -2.259303;
double yTechnicRoom = -11.05786;

double xGoal = 0.0;
double yGoal = 0.0;

//Declare goalReached. it is used to print out a message when goal is reached
bool goalReached = false;

//A function "light is" created 
void light(int a, int b);

//The function "ButtonCallBack" passes the data for each button on the robot 
void ButtonCallback(const kobuki_msgs::ButtonEvent::ConstPtr& msg){
    bool Pressed = false;       //hvad er det her? 
    int Button = 5;             //hvad er det her? 
    Pressed = msg->state;
    Button = msg->button;
    //Each button is given a desitination 
    if (Pressed == true){
        if (Button == 0){
            xGoal = xB228;
            yGoal = yB228;
            ROS_INFO("Going to B228");
        }
        else if (Button == 1){
            xGoal = xPrinterRoom;
            yGoal = yPrinterRoom;
            ROS_INFO("Going to Printer Room");
        }
        else if (Button == 2){
            xGoal = xTechnicRoom;
            yGoal = yTechnicRoom;
            ROS_INFO("Going to Technic Room");
        }
    
        //Setting up the publsher - 'move_base' server through a 'SimpleActionClient'
        actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);

        //Setting a timer, so the 'action server' can come up , and it will wait for mak. 5 sec.
        while (!ac.waitForServer(ros::Duration(5.0))){
            ROS_INFO("Program waitin for the 'move_base action server' to post");
        }

        move_base_msgs::MoveBaseGoal goal;

        //Declaring the coordiantes used in this node to reference to the absolute coordinates nemed in the "map" file 
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();
        ROS_INFO("lige før den sender xGoal og yGoal");
        //Moving the robot towards its distination point 
        goal.target_pose.pose.position.x = xGoal;
        goal.target_pose.pose.position.y = yGoal;
        goal.target_pose.pose.position.z = 00.00;

        goal.target_pose.pose.orientation.x = 00.00;
        goal.target_pose.pose.orientation.y = 00.00;
        goal.target_pose.pose.orientation.z = 00.00;
        goal.target_pose.pose.orientation.w = 1.00;

        //If the robot is miving rowards its distination its lights will turn yelleow and red 
        ROS_INFO("Moving towards the distination");
        ac.sendGoal(goal);
        light(1, 'o');
        light(2, 'r');

        ac.waitForResult();

        //If the robot has reached its goal its lights will turn green 
        if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
            ROS_INFO("The distination has been reached");
            light(1, 'g');
            light(2, 'g');
        
        }
        //If the robot cannot reacg its goal the lights will turn red
        else{
        ROS_ERROR("The distination cannot be reached");
        light(1, 'r');
        light(2, 'r');
        }
    }
}

int main(int argc, char** argv){

    //Initelizing ros    
    ros::init(argc, argv, "MoveToGoal_fin_node");
    ros::NodeHandle n;

    cout << "noden er startet" << endl;
    cout << "B228 kordinater" << xB228 << "|||||" << yB228 << endl; //hvorfor? 
    
    //"led1_pub" & "led2_pub" is defined 
    led1_pub = n.advertise<kobuki_msgs::Led>("/mobile_base/commands/led1", 1);
    led2_pub = n.advertise<kobuki_msgs::Led>("/mobile_base/commands/led2", 1);

    //Subcribing to "mobile_base/events/button". 
    //Evertime an advertisment is made on the topic "mobile_base/events/button" run "ButtonCallBack"
    ros::Subscriber Button_sub = n.subscribe("mobile_base/events/button", 1, ButtonCallback);

    //The program has run continuously 
    ros::spin();

    return 0;
}

void light(int a, int b){               //emil? 
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
        cout << b << " er ikke en mulig farve" << endl;
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
            cout << "led " << a << "eksisterer ikke!" << endl;
            break;    
    }
}