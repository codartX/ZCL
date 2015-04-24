#ifndef _PWR_CFG_H
#define _PWR_CFG_H

typedef enum _zcl_general_pwr_cfg_attr_id_e {
    //Mains Info Attribute Set
    ZCL_GEN_PWR_CFG_ATTR_ID_MAINS_VOLT                  = 0x0000,
    ZCL_GEN_PWR_CFG_ATTR_ID_MAINS_FREQ                  = 0x0001,
    //Mains Settings Attribute Set
    ZCL_GEN_PWR_CFG_ATTR_ID_MAINS_ALARM_MASK            = 0x0010,
    ZCL_GEN_PWR_CFG_ATTR_ID_MAINS_VOLT_MIN_TH           = 0x0011,
    ZCL_GEN_PWR_CFG_ATTR_ID_MAINS_VOLT_MAX_TH           = 0x0012,
    ZCL_GEN_PWR_CFG_ATTR_ID_MAINS_VOLT_DWELL_TRIP_POINT = 0x0013,
    //Battery Info Attribute Set
    ZCL_GEN_PWR_CFG_ATTR_ID_BATTERY_VOLT                = 0x0020,
    //Battery Settings Attribute Set
    ZCL_GEN_PWR_CFG_ATTR_ID_BATTERY_MFR                 = 0x0030,
    ZCL_GEN_PWR_CFG_ATTR_ID_BATTERY_SIZE                = 0x0030,
    ZCL_GEN_PWR_CFG_ATTR_ID_BATTERY_AHR_RATING          = 0x0030,
    ZCL_GEN_PWR_CFG_ATTR_ID_BATTERY_QUANTITY            = 0x0030,
    ZCL_GEN_PWR_CFG_ATTR_ID_BATTERY_RATED_VOLT          = 0x0030,
    ZCL_GEN_PWR_CFG_ATTR_ID_BATTERY_ALARM_MASK          = 0x0030,
    ZCL_GEN_PWR_CFG_ATTR_ID_BATTERY_VOLT_MIN_TH         = 0x0030,
} zcl_general_pwr_cfg_attr_id_e; 

#endif
