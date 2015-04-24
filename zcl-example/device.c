#include <string.h>
#include "device.h"
#include "basic.h"
#include "zcl.h"

static zcl_cluster_basic_t basic_cluster;

static zcl_cluster_t *zcl_cluster_list[] =
{
    (zcl_cluster_t *)(&basic_cluster),
    NULL
};

static uint8_t dev_zcl_basic_cluster_custom_init(zcl_cluster_basic_t *basic_cluster)
{
    uint8_t retval = ZCL_FAIL;

    retval = zcl_general_basic_cluster_init(basic_cluster); 
    if (retval == ZCL_FAIL) {
        return ZCL_FAIL;
    }

    return ZCL_SUCCESS;
}

uint8_t dev_zcl_init()
{
    uint8_t retval = ZCL_FAIL;

    retval = dev_zcl_basic_cluster_custom_init(&basic_cluster);
    if (retval == ZCL_FAIL) {
        return ZCL_FAIL;
    }

    set_dev_cluster_list(zcl_cluster_list); 
    
    return ZCL_SUCCESS;
}
