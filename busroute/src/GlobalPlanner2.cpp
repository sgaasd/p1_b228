#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>


#include "GlobalPlanner2.h"
#include <pluginlib/class_list_macros.h>
//register this planner as a BaseGlobalPlanner plugin
PLUGINLIB_EXPORT_CLASS(RAstar_planner::RAstarPlannerROS, nav_core::BaseGlobalPlanner)

int value;
int mapSize;
bool* OGM;
static const float INFINIT_COST = INT_MAX; //!< cost of non connected nodes
float infinity = std::numeric_limits< float >::infinity();
float tBreak; //coefficient for breaking ties
ofstream MyExcelFile ("RA_result.xlsx", ios::trunc);

int clock_gettime(clockid_t clk_id, struct timespect *tp);


void RAstarPlannerROS::initialize(std::string name, costmap_2d::Costmap2DROS* costmap_ros)
{
    if (!initialized_)
    {
        costmap_ros = costmap_ros;
        costmap_ = costmap_ros_->getCostmap();
    }
}