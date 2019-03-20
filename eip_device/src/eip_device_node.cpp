#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/capability.h>
#include <sys/capability.h>


#include <ros/ros.h>

#include "eip_device.h"

extern EipUint8 g_assembly_data064[32]; /* Input */
extern EipUint8 g_assembly_data096[32]; /* Output */
extern EipUint8 g_assembly_data097[10]; /* Config */
extern EipUint8 g_assembly_data09A[32]; /* Explicit */


/******************************************************************************/
/** @brief Signal handler function for ending stack execution
 *
 * @param signal the signal we received
 */
void LeaveStack(int signal);

/*****************************************************************************/
/** @brief Flag indicating if the stack should end its execution
 */
int g_end_stack = 0;

int main(int argc, char **argv)
{
  cap_t capabilities;
  cap_value_t capabilies_list[1];

  ros::init(argc, argv, "eip_device");
  ros::NodeHandle nh("~");

  bool debug;
  nh.param<bool>("debug", debug, true);
  ROS_INFO_STREAM("debug is: " << debug);

  while (debug)
  {
    sleep(1);
    nh.getParam("debug", debug);
  }

  ROS_INFO("Starting eip_device!");

  ros::Time::init();

  double freq;
  nh.param<double>("frequency", freq, 1);
  ros::Rate throttle(freq);

  // get sensor config from params
  string device;
  nh.param<std::string>("device", device, "eth0");
  ROS_INFO_STREAM("Using Ethernet device: " << device);


  ROS_INFO("Getting Ethernet port capabilities");

  capabilities = cap_get_proc();
  if (NULL == capabilities) {
    ROS_ERROR("Could not get capabilities");
    exit(0);
  }

  capabilies_list[0] = CAP_NET_RAW;
  if (-1 == cap_set_flag(capabilities, CAP_EFFECTIVE, 1, capabilies_list, CAP_SET) ) {
    cap_free(capabilities);
    ROS_ERROR("Could not set CAP_NET_RAW capability");
    exit(0);
  }

  if (-1 == cap_set_proc(capabilities) ) {
    cap_free(capabilities);
    ROS_ERROR("Could not push CAP_NET_RAW capability to process");
    exit(0);
  }

  if (-1 == cap_free(capabilities) ) {
    ROS_ERROR("Could not free capabilites value");
    exit(0);
  }

  DoublyLinkedListInitialize(&connection_list,
                             CipConnectionObjectListArrayAllocator,
                             CipConnectionObjectListArrayFree);
  /* fetch Internet address info from the platform */
  if (kEipStatusError == ConfigureNetworkInterface(device.c_str()) ) {
    ROS_ERROR("Network interface %s not found.\n", device.c_str());
    exit(0);
  }
  ConfigureDomainName();
  ConfigureHostName();

  ConfigureMacAddress(device.c_str());

  /* for a real device the serial number should be unique per device */
  SetDeviceSerialNumber(123456789);

  /* unique_connection_id should be sufficiently random or incremented and stored
   *  in non-volatile memory each time the device boots.
   */
  EipUint16 unique_connection_id = rand();

  /* Setup the CIP Layer */
  CipStackInit(unique_connection_id);

  if (kEipStatusOk == NetworkHandlerInitialize() )
  {
    g_end_stack = 0;
  }
  else
  {
    ROS_ERROR("Error initializing NetworkHandler! Exiting eip_device!");
    exit(0);
  }

  ROS_INFO("Starting Process Loop");
  int EipStatus = kEipStatusOk;

  while(ros::ok() && (1 != g_end_stack) && (EipStatus == kEipStatusOk))
  {
    /* Setup Network Handles */
    /* The event loop. Put other processing you need done continually in here */
    EipStatus = NetworkHandlerProcessOnce();
    if (EipStatus != kEipStatusOk)
    {
      ROS_ERROR_STREAM("Error in NetworkHandler loop! Exiting eip_device! -- " << EipStatus );
      break;
    }

    ros::spinOnce();

    throttle.sleep();

  }

  /* clean up network state */
  ROS_INFO("Finish network handler");
  NetworkHandlerFinish();

  ROS_INFO("Shutdown CIP Stack");
  /* close remaining sessions and connections, cleanup used data */
  ShutdownCipStack();

  return g_end_stack;
}

void LeaveStack(int signal) {
  (void) signal;       /* kill unused parameter warning */
  OPENER_TRACE_STATE("got signal HUP\n");
  ROS_INFO("HUP Signal!");
  g_end_stack = 1;
}

