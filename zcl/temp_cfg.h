#ifndef _TEMP_CFG_H
#define _TEMP_CFG_H

typedef enum _zcl_general_temp_cfg_attr_id_e {
    //Device Temperature Info Attribute Set
    ZCL_GEN_TEMP_CFG_ATTR_ID_CUR_TEMP                   = 0x0000,
    ZCL_GEN_TEMP_CFG_ATTR_ID_MIN_TEMP_EXP               = 0x0001,
    ZCL_GEN_TEMP_CFG_ATTR_ID_MAX_TEMP_EXP               = 0x0002,
    ZCL_GEN_TEMP_CFG_ATTR_ID_OVER_TEMP_TOTAL_DWELL      = 0x0003,
    //Device Temperature Settings Attribute Set
    ZCL_GEN_TEMP_CFG_ATTR_ID_DEV_TEMP_ALARM_MASK        = 0x0010,
    ZCL_GEN_TEMP_CFG_ATTR_ID_LOW_TEMP_TH                = 0x0011,
    ZCL_GEN_TEMP_CFG_ATTR_ID_HIGH_TEMP_TH               = 0x0012,
    ZCL_GEN_TEMP_CFG_ATTR_ID_LOW_TEMP_DWELL_TRIP_POINT  = 0x0013,
    ZCL_GEN_TEMP_CFG_ATTR_ID_HIGH_TEMP_DWELL_TRIP_POINT = 0x0014,

} zcl_general_temp_cfg_attr_id_e;

#endif
