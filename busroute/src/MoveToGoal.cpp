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
    //Coordinates in Grouproom B228.
    double xB228 = 1.181052;
    double yB228 = 0.033761;
    double zB228 = 0.0;
    double wB228 = 1.0;
    

    //Coordinates in Printerroom on second floor.
    double xPrinterRoom = 2.200309;
    double yPrinterRoom = 6.166436;
    double zPrinterRoom = 0.0;
    double wPrinterRoom = 1.0;

    //Coordinates outside of Technicroom on second floor.
    double xTechnicRoom = -2.259303;
    double yTechnicRoom = -11.05786;
    double zTechnicRoom = 0.0;
    double wTechnicRoom = 1.0;

    //defining the Goal coordinates.
    double xGoal = 0.0;
    double yGoal = 0.0;
    double zGoal = 0.0;
    double wGoal = 1.0;

//A function "light" is created 
void light(int led, int color);

//The function "ButtonCallBack" passes the data for each button on the robot 
void ButtonCallback(const kobuki_msgs::ButtonEvent::ConstPtr& msg){
    bool Pressed = msg->state;
    int Button = msg->button;

    //Each button is asgined a specific distination 
    if (Pressed == true){
        if (Button == 0){
            //The coordinates stored in "xB228" and "yB228" is passed over to Goal coordinates.
            xGoal = xB228;
            yGoal = yB228;
            zGoal = zB228;
            wGoal = wB228;
            ROS_INFO("Going to B228");
        }
        else if (Button == 1){
            //The coordinates stored in "xPrinterRoom" and "yPrinterRoom" is passed over to Goal coordinates.
            xGoal = xPrinterRoom;
            yGoal = yPrinterRoom;
            zGoal = zPrinterRoom;
            wGoal = wPrinterRoom;
            ROS_INFO("Going to Printer Room");
        }
        else if (Button == 2){
            //The coordinates stored in "xPrinterRoom" and "yPrinterRoom" is passed over to Goal coordinates.
            xGoal = xTechnicRoom;
            yGoal = yTechnicRoom;
            zGoal = zTechnicRoom;
            wGoal = wTechnicRoom;
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
        
        //Moving the robot towards its distination point 
        goal.target_pose.pose.position.x = xGoal;
        goal.target_pose.pose.position.y = yGoal;

        goal.target_pose.pose.orientation.z = zGoal;
        goal.target_pose.pose.orientation.w = wGoal;

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
    ros::init(argc, argv, "MoveToGoal_node");
    ros::NodeHandle n;
    
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

//Function for controling the light
void light(int led, int color){
    //Defining the variable led_message to the type kobuki_msgs::Led
    kobuki_msgs::Led led_message;
    //defining a interger variable, which will be used in the following switch.
    int asignedColor;
    //Switch statement for asigning a color to the ingeger variable "asignedColor"
    switch (color){
        case 's':
            //If the variable "color" has the value "s", the color is set to NULL (which translate to the led turned off)
            asignedColor = 0;
            break;

        case 'g':
            //If the variable "color" has the value "g", the color is set to GREEN.
            asignedColor = 1;
            break;

        case 'o':
            //If the variable "color" has the value "o", the color is set to ORANGE.
            asignedColor = 2;
            break;

        case 'r':
            //If the variable "color" has the value "r", the color is set to RED.
            asignedColor = 3;
            break;
            
        default:
            //A ERROR message will appear if none of the above cases is true. 
            ROS_ERROR("The asigned value is not a known color");
            break;
    }
    //The value in "asignedColor" is passed to "led_message.value".
    led_message.value = asignedColor;

    //Switch statement for activating a Led 1 or Led 2.
    switch(led){
        case 1:
            //If the variable "led" has the value 1, the Led 1 will light up, with the asigned color from the switch above.
            led1_pub.publish(led_message);
            break;
        case 2:
            //If the variable "led" has the value 2, the Led 2 will light up, with the asigned color from the switch above.
            led2_pub.publish(led_message);
            break;

        default:
            //A ERROR message will appear if none of the above cases is true. 
            ROS_ERROR("The asigned led is not a known led");
            break;    
    }
}