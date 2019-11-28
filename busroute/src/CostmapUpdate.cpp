#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
using namespace std;

ros::Publisher nav_msg; 

int main(int argc, char *argv[]){

    ros::init(argc, argv, "CostmapUpdate");
    ros::NodeHandle n;

    nav_msg=n.advertise<nav_msgs::OccupancyGrid>("/move_base/global_costmap/costmap",1);

    return 0;
}