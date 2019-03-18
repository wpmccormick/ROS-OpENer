#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/capability.h>
#include <sys/capability.h>


#include <ros/ros.h>

#include "eip_device.h"

/******************************************************************************/
/** @brief Signal handler function for ending stack execution
 *
 * @param signal the signal we received
 */
void LeaveStack(int signal);

/******************************************************************************/
/** @brief Signal handler function for ending stack execution
 *
 * @param signal the signal we received
 */
void *executeEventLoop();

/*****************************************************************************/
/** @brief Flag indicating if the stack should end its execution
 */
int g_end_stack = 0;

int main(int argc, char **argv)
{

  cap_t capabilities;
  cap_value_t capabilies_list[1];

  capabilities = cap_get_proc();
  if (NULL == capabilities) {
    printf("Could not get capabilities\n");
    exit(0);
  }

  capabilies_list[0] = CAP_NET_RAW;
  if (-1
      == cap_set_flag(capabilities, CAP_EFFECTIVE, 1, capabilies_list,
                      CAP_SET) ) {
    cap_free(capabilities);
    printf("Could not set CAP_NET_RAW capability\n");
    exit(0);
  }

  if (-1 == cap_set_proc(capabilities) ) {
    cap_free(capabilities);
    printf("Could not push CAP_NET_RAW capability to process\n");
    exit(0);
  }

  if (-1 == cap_free(capabilities) ) {
    printf("Could not free capabilites value\n");
    exit(0);
  }

  if (argc != 2) {
    printf("Wrong number of command line parameters!\n");
    printf("The correct command line parameters are:\n");
    printf("./OpENer interfacename\n");
    printf("    e.g. ./OpENer eth1\n");
    exit(0);
  } else {
    DoublyLinkedListInitialize(&connection_list,
                               CipConnectionObjectListArrayAllocator,
                               CipConnectionObjectListArrayFree);
    /* fetch Internet address info from the platform */
    if (kEipStatusError == ConfigureNetworkInterface(argv[1]) ) {
      printf("Network interface %s not found.\n", argv[1]);
      exit(0);
    }
    ConfigureDomainName();
    ConfigureHostName();

    ConfigureMacAddress(argv[1]);
  }

  /* for a real device the serial number should be unique per device */
  SetDeviceSerialNumber(123456789);

  /* unique_connection_id should be sufficiently random or incremented and stored
   *  in non-volatile memory each time the device boots.
   */
  EipUint16 unique_connection_id = rand();

  /* Setup the CIP Layer */
  CipStackInit(unique_connection_id);

  ros::init(argc, argv, "eip_device_node");
  ros::NodeHandle nh;

  ROS_INFO("Hello world!");

  /* Setup Network Handles */
  if (kEipStatusOk == NetworkHandlerInitialize() ) {
    g_end_stack = 0;
    executeEventLoop();
    /* clean up network state */
    NetworkHandlerFinish();
  }
  /* close remaining sessions and connections, cleanup used data */
  ShutdownCipStack();

  return -1;
}

void LeaveStack(int signal) {
  (void) signal;       /* kill unused parameter warning */
  OPENER_TRACE_STATE("got signal HUP\n");
  g_end_stack = 1;
}

void *executeEventLoop() {
  /* The event loop. Put other processing you need done continually in here */
  while (1 != g_end_stack) {
    if (kEipStatusOk != NetworkHandlerProcessOnce() ) {
      OPENER_TRACE_ERR("Error in NetworkHandler loop! Exiting OpENer!\n");
      break;
    }
  }
}
