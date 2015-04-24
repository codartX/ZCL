#ifndef _ZCL_CLUSTER_H
#define _ZCL_CLUSTER_H

#include "zcl_attr.h"

typedef enum _zcl_cluster_id_e {
    //General 0x0000 - 0x00ff
    ZCL_CLUSTER_ID_GENERAL_BASIC                                        = 0x0000,
    ZCL_CLUSTER_ID_GENERAL_POWER_CONFIG                                 = 0x0001,
    ZCL_CLUSTER_ID_GENERAL_DEVICE_TEMP_CONFIG                           = 0x0002,
    ZCL_CLUSTER_ID_GENERAL_IDENTIFY                                     = 0x0003,
    ZCL_CLUSTER_ID_GENERAL_GROUPS                                       = 0x0004,
    ZCL_CLUSTER_ID_GENERAL_SCENES                                       = 0x0005,
    ZCL_CLUSTER_ID_GENERAL_ON_OFF                                       = 0x0006,
    ZCL_CLUSTER_ID_GENERAL_ON_OFF_SWITCH_CONFIG                         = 0x0007,
    ZCL_CLUSTER_ID_GENERAL_LEVEL_CONTROL                                = 0x0008,
    ZCL_CLUSTER_ID_GENERAL_ALARMS                                       = 0x0009,
    ZCL_CLUSTER_ID_GENERAL_TIME                                         = 0x000a,
    ZCL_CLUSTER_ID_GENERAL_RSSI_LOC                                     = 0x000b,
    ZCL_CLUSTER_ID_GENERAL_ANALOG_INPUT                                 = 0x000c,
    ZCL_CLUSTER_ID_GENERAL_ANALOG_OUTPUT                                = 0x000d,
    ZCL_CLUSTER_ID_GENERAL_ANALOG_VALUE                                 = 0x000e,
    ZCL_CLUSTER_ID_GENERAL_BINARY_INPUT                                 = 0x000f,
    ZCL_CLUSTER_ID_GENERAL_BINARY_OUTPUT                                = 0x0010,
    ZCL_CLUSTER_ID_GENERAL_BINARY_VALUE                                 = 0x0011,
    ZCL_CLUSTER_ID_GENERAL_MULTISTATE_INPUT                             = 0x0012,
    ZCL_CLUSTER_ID_GENERAL_MULTISTATE_OUTPUT                            = 0x0013,
    ZCL_CLUSTER_ID_GENERAL_MULTISTATE_VALUE                             = 0x0014,
    ZCL_CLUSTER_ID_GENERAL_COMMISSIONING                                = 0x0015,
    //Closures
    ZCL_CLUSTER_ID_CLOSURES_SHADE_CONFIG                                = 0x0100,
    ZCL_CLUSTER_ID_CLOSURES_DOOR_LOCK                                   = 0x0101,
    //HVAC
    ZCL_CLUSTER_ID_HVAC_PUMP_CONFIG_AND_CTRL                            = 0x0200,
    ZCL_CLUSTER_ID_HVAC_THERMOSTAT                                      = 0x0201,
    ZCL_CLUSTER_ID_HVAC_FAN_CTRL                                        = 0x0202,
    ZCL_CLUSTER_ID_HVAC_DEHUMIDIFICATION_CTRL                           = 0x0203,
    ZCL_CLUSTER_ID_HVAC_THERMOSTAT_UI_CONFIG                            = 0x0204,
    //Lighting
    ZCL_CLUSTER_ID_LIGHTING_COLOR_CTRL                                  = 0x0300,
    ZCL_CLUSTER_ID_LIGHTING_BALLAST_CONFIG                              = 0x0301,
    //Measurement and Sensing
    ZCL_CLUSTER_ID_MEASUREMENT_SENSING_ILLUMINANCE_MEASUREMENT          = 0x0400,
    ZCL_CLUSTER_ID_MEASUREMENT_SENSING_ILLUMINANCE_LEVEL_SENSING        = 0x0401,
    ZCL_CLUSTER_ID_MEASUREMENT_SENSING_TEMP_MEASUREMENT                 = 0x0402,
    ZCL_CLUSTER_ID_MEASUREMENT_SENSING_PRESSURE_MEASUREMENT             = 0x0403,
    ZCL_CLUSTER_ID_MEASUREMENT_SENSING_FLOW_MEASUREMENT                 = 0x0404,
    ZCL_CLUSTER_ID_MEASUREMENT_SENSING_RELATIVE_HUMIDITY_MEASUREMENT    = 0x0405,
    ZCL_CLUSTER_ID_MEASUREMENT_SENSING_OCCUPANCY_SENSING                = 0x0406,
    //Security and Safety
    ZCL_CLUSTER_ID_SECURITY_SAFETY_IAS_ZONE                             = 0x0500,
    ZCL_CLUSTER_ID_SECURITY_SAFETY_IAS_ACE                              = 0x0501,
    ZCL_CLUSTER_ID_SECURITY_SAFETY_IAS_WD                               = 0x0502,
    //Protocol Interfaces
    ZCL_CLUSTER_ID_PROTOCOL_INTERFACE_GENERIC_TUNNEL                    = 0x0600,
    ZCL_CLUSTER_ID_PROTOCOL_INTERFACE_BACNET_PROTOCOL_TUNNEL            = 0x0601,
    ZCL_CLUSTER_ID_PROTOCOL_INTERFACE_ANALOG_INPUT                      = 0x0602,
    ZCL_CLUSTER_ID_PROTOCOL_INTERFACE_ANALOG_INPUT_EXT                  = 0x0603,
    ZCL_CLUSTER_ID_PROTOCOL_INTERFACE_ANALOG_OUTPUT                     = 0x0604,
    ZCL_CLUSTER_ID_PROTOCOL_INTERFACE_ANALOG_OUTPUT_EXT                 = 0x0605,
    ZCL_CLUSTER_ID_PROTOCOL_INTERFACE_ANALOG_VALUE                      = 0x0606,
    ZCL_CLUSTER_ID_PROTOCOL_INTERFACE_ANALOG_VALUE_EXT                  = 0x0607,
    ZCL_CLUSTER_ID_PROTOCOL_INTERFACE_BINARY_INPUT                      = 0x0608,
    ZCL_CLUSTER_ID_PROTOCOL_INTERFACE_BINARY_INPUT_EXT                  = 0x0609,
    ZCL_CLUSTER_ID_PROTOCOL_INTERFACE_BINARY_OUTPUT                     = 0x060a,
    ZCL_CLUSTER_ID_PROTOCOL_INTERFACE_BINARY_OUTPUT_EXT                 = 0x060b,
    ZCL_CLUSTER_ID_PROTOCOL_INTERFACE_BINARY_VALUE                      = 0x060c,
    ZCL_CLUSTER_ID_PROTOCOL_INTERFACE_BINARY_VALUE_EXT                  = 0x060d,
    ZCL_CLUSTER_ID_PROTOCOL_INTERFACE_MULTISTATE_INPUT                  = 0x060e,
    ZCL_CLUSTER_ID_PROTOCOL_INTERFACE_MULTISTATE_INPUT_EXT              = 0x060f,
    ZCL_CLUSTER_ID_PROTOCOL_INTERFACE_MULTISTATE_OUTPUT                 = 0x0610,
    ZCL_CLUSTER_ID_PROTOCOL_INTERFACE_MULTISTATE_OUTPUT_EXT             = 0x0611,
    ZCL_CLUSTER_ID_PROTOCOL_INTERFACE_MULTISTATE_VALUE                  = 0x0612,
    ZCL_CLUSTER_ID_PROTOCOL_INTERFACE_MULTISTATE_VALUE_EXT              = 0x0613,
} zcl_cluster_id_e;

typedef struct _zcl_cluster_t {
    uint16_t cluster_id;
    zcl_attr_t *attr_list;
    uint32_t (*spec_handler)(uip_ipaddr_t *src_ip, uint8_t *data, uint32_t len, 
                             struct _zcl_cluster_t *cluster, uint8_t *resp, uint32_t resp_len); 
} zcl_cluster_t;

zcl_attr_t *zcl_cluster_find_attr(zcl_cluster_t *cluster, uint16_t attr_id);

#endif
