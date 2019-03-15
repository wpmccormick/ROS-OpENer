#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/capability.h>
#include <sys/capability.h>

#include "generic_networkhandler.h"
#include "opener_api.h"
#include "cipcommon.h"
#include "trace.h"
#include "networkconfig.h"
#include "doublylinkedlist.h"
#include "cipconnectionobject.h"

#include <ros/ros.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "eip_device");
    ros::NodeHandle nh;

    ROS_INFO("Hello world!");
}
