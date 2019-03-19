#ifndef EIP_DEVICE_H
#define EIP_DEVICE_H

#include <iostream>
#include <string>

using namespace std;

extern "C" {
  #include "opener_ros/trace.h"
  #include "opener_ros/opener_api.h"
  #include "opener_ros/cip/cipcommon.h"
  #include "opener_ros/trace.h"
  #include "opener_ros/ports/generic_networkhandler.h"
  #include "opener_ros/ports/POSIX/networkconfig.h"
  #include "opener_ros/utils/doublylinkedlist.h"
  #include "opener_ros/cip/cipconnectionobject.h"
  #include "opener_ros/cip/appcontype.h"
  #include "opener_ros/cip/cipidentity.h"
}


class eip_device
{
public:
  eip_device(char* iface) {char* interface_name(char* iface);}

  char* iterface_name;

};

#endif // EIP_DEVICE_H


