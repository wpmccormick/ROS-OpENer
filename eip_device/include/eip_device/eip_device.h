#ifndef EIP_DEVICE_H
#define EIP_DEVICE_H

#include <iostream>
#include <string>
#include<memory>

using namespace std;

extern "C" {
  #include "opener_ros/trace.h"
  #include "opener_ros/opener_api.h"
  #include "opener_ros/cip/cipcommon.h"
  #include "opener_ros/trace.h"
  #include "opener_ros/ports/POSIX/networkconfig.h"
  #include "opener_ros/utils/doublylinkedlist.h"
  #include "opener_ros/cip/cipconnectionobject.h"
  #include "opener_ros/cip/appcontype.h"
  #include "opener_ros/cip/cipidentity.h"
  #include "opener_ros/ports/generic_networkhandler.h"
}

#include <eip_device/EipDataToPLC.h>
#include <eip_device/EipDataFmPLC.h>

extern EipUint8 g_assembly_data064[32]; /* Input */
extern EipUint8 g_assembly_data096[32]; /* Output */
extern EipUint8 g_assembly_data097[10]; /* Config */
extern EipUint8 g_assembly_data09A[32]; /* Explicit */

class EipDevice
{
public:
  void toplcCallback(const eip_device::EipDataToPLC::ConstPtr& msg);

  eip_device::EipDataToPLC data_toplc;
  eip_device::EipDataFmPLC data_fmplc;
};

#endif // EIP_DEVICE_H


