#ifndef _TIME_H
#define _TIME_H

typedef enum _zcl_general_time_attr_id_e {
    ZCL_GEN_TIME_ATTR_ID_TIME              = 0x0000,
    ZCL_GEN_TIME_ATTR_ID_TIME_STATUS       = 0x0001,
    ZCL_GEN_TIME_ATTR_ID_TIME_ZONE         = 0x0002,
    ZCL_GEN_TIME_ATTR_ID_DST_START         = 0x0003,
    ZCL_GEN_TIME_ATTR_ID_DST_END           = 0x0004,
    ZCL_GEN_TIME_ATTR_ID_DST_SHIFT         = 0x0005,
    ZCL_GEN_TIME_ATTR_ID_STANDARD_TIME     = 0x0006,
    ZCL_GEN_TIME_ATTR_ID_LOCAL_TIME        = 0x0007,
    ZCL_GEN_TIME_ATTR_ID_LAST_SET_TIME     = 0x0008,
    ZCL_GEN_TIME_ATTR_ID_VALID_UNTIL_TIME  = 0x0009,
} zcl_general_time_attr_id_e;

#endif
