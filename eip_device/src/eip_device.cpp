#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/capability.h>
#include <sys/capability.h>

extern "C" {
	#include "opener_ros/ports/generic_networkhandler.h"
	#include "opener_ros/opener_api.h"
	#include "opener_ros/cip/cipcommon.h"
	#include "opener_ros/trace.h"
	#include "opener_ros/ports/POSIX/networkconfig.h"
	#include "opener_ros/utils/doublylinkedlist.h"
	#include "opener_ros/cip/cipconnectionobject.h"
}

#include <ros/ros.h>

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

    ros::init(argc, argv, "eip_device");
    ros::NodeHandle nh;

    ROS_INFO("Hello world!");
}
