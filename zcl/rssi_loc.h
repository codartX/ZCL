#ifndef _RSSI_LOC_H
#define _RSSI_LOC_H

typedef enum _zcl_general_rssi_loc_attr_id_e {
    //Location Info Attribute Set
    ZCL_GEN_RSSI_LOC_ATTR_ID_LOCATION_TYPE            = 0x0000,
    ZCL_GEN_RSSI_LOC_ATTR_ID_LOCATION_METHOD          = 0x0001,
    ZCL_GEN_RSSI_LOC_ATTR_ID_LOCATION_AGE             = 0x0002,
    ZCL_GEN_RSSI_LOC_ATTR_ID_QUALITY_MEASURE          = 0x0003,
    ZCL_GEN_RSSI_LOC_ATTR_ID_NUMBER_OF_DEVICES        = 0x0004,
   //Location Settings Attribute Set
    ZCL_GEN_RSSI_LOC_ATTR_ID_COORDINATE1              = 0x0010,
    ZCL_GEN_RSSI_LOC_ATTR_ID_COORDINATE2              = 0x0011,
    ZCL_GEN_RSSI_LOC_ATTR_ID_COORDINATE3              = 0x0012,
    ZCL_GEN_RSSI_LOC_ATTR_ID_POWER                    = 0x0013,
    ZCL_GEN_RSSI_LOC_ATTR_ID_PATH_LOSS_EXPONENT       = 0x0014,
    ZCL_GEN_RSSI_LOC_ATTR_ID_REPORTING_PERIOD         = 0x0015,
    ZCL_GEN_RSSI_LOC_ATTR_ID_CALCULATION_PERIOD       = 0x0016,
    ZCL_GEN_RSSI_LOC_ATTR_ID_NUMBER_RSSI_MEASUREMENTS = 0x0017,
} zcl_general_rssi_loc_attr_id_e;

#endif
