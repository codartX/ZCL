#ifndef _ZCL_H
#define _ZCL_H

#include "contiki-net.h"
#include "zcl_cluster.h"

PROCESS_NAME(zcl_process);

#define ZCL_VERSION    0x01

#define ZCL_UDP_SERVER_PORT    6666
#define ZCL_UDP_CLIENT_PORT    6667

#define ZCL_MAX_STR_SIZE    32

#define ZCL_SUCCESS    1
#define ZCL_FAIL       0

void set_dev_cluster_list(zcl_cluster_t **cluster_list);

zcl_cluster_t *zcl_find_cluster(uint16_t cluster_id);

#endif
