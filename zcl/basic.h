#ifndef _BASIC_H
#define _BASIC_H

#include "zcl.h"

typedef enum _zcl_general_basic_attr_id_e {
    //Basic Device Info Attribute Set
    ZCL_GEN_BASIC_ATTR_ID_ZCL_VERSION   = 0x0000,
    ZCL_GEN_BASIC_ATTR_ID_APP_VERSION   = 0x0001,
    ZCL_GEN_BASIC_ATTR_ID_STACK_VERSION = 0x0002,
    ZCL_GEN_BASIC_ATTR_ID_HW_VERSION    = 0x0003,
    ZCL_GEN_BASIC_ATTR_ID_MFR_NAME      = 0x0004,
    ZCL_GEN_BASIC_ATTR_ID_MODEL_ID      = 0x0005,
    ZCL_GEN_BASIC_ATTR_ID_DATE_CODE     = 0x0006,
    ZCL_GEN_BASIC_ATTR_ID_PWR_SRC       = 0x0007,
    //Basic Device Setting Attribute Set
    ZCL_GEN_BASIC_ATTR_ID_LOC_DESC      = 0x0010,
    ZCL_GEN_BASIC_ATTR_ID_PHY_ENV       = 0x0011,
    ZCL_GEN_BASIC_ATTR_ID_DEV_ENABLED   = 0x0012,
    ZCL_GEN_BASIC_ATTR_ID_ALARM_MASK    = 0x0013,
    ZCL_GEN_BASIC_ATTR_ID_DIS_LOC_CFG   = 0x0014,
} zcl_general_basic_attr_id_e;

typedef enum _zcl_general_basic_power_src_attr_value_e {
    ZCL_GEN_BASIC_POWER_SRC_ATTR_VALUE_UNKNOWN               = 0x00,
    ZCL_GEN_BASIC_POWER_SRC_ATTR_VALUE_MAINS_SINGLE_PHASE    = 0x01,
    ZCL_GEN_BASIC_POWER_SRC_ATTR_VALUE_MAINS_THREE_PHASE     = 0x02,
    ZCL_GEN_BASIC_POWER_SRC_ATTR_VALUE_BATTERY               = 0x03,
    ZCL_GEN_BASIC_POWER_SRC_ATTR_VALUE_DC_SOURCE             = 0x04,
    ZCL_GEN_BASIC_POWER_SRC_ATTR_VALUE_EMERG_MAINS_CONST     = 0x05,
    ZCL_GEN_BASIC_POWER_SRC_ATTR_VALUE_EMERG_MAINS_TRANSFER  = 0x06,
} zcl_general_basic_power_src_attr_value_e;

#define ZCL_GEN_BASIC_FLAG_ZCL_VER      0x00000001 
#define ZCL_GEN_BASIC_FLAG_APP_VER      0x00000002 
#define ZCL_GEN_BASIC_FLAG_STACK_VER    0x00000004 
#define ZCL_GEN_BASIC_FLAG_HW_VER       0x00000008 
#define ZCL_GEN_BASIC_FLAG_MFR_NAME     0x00000010 
#define ZCL_GEN_BASIC_FLAG_MODEL_ID     0x00000020 
#define ZCL_GEN_BASIC_FLAG_DATE_CODE    0x00000040 
#define ZCL_GEN_BASIC_FLAG_POWER_SRC    0x00000080 
#define ZCL_GEN_BASIC_FLAG_LOC_DESC     0x00000100 
#define ZCL_GEN_BASIC_FLAG_PHY_ENV      0x00000200 
#define ZCL_GEN_BASIC_FLAG_DEV_ENABLED  0x00000400 
#define ZCL_GEN_BASIC_FLAG_ALARM_MASK   0x00000800 
#define ZCL_GEN_BASIC_FLAG_DIS_LOC_CFG  0x00001000 

typedef enum _zcl_general_basic_phy_env_attr_value_e {
    ZCL_GEN_BASIC_PHY_ENV_ATTR_VALUE_UNSPEFCIFIED          = 0x00,
    ZCL_GEN_BASIC_PHY_ENV_ATTR_VALUE_UNKNOWN               = 0xff,
} zcl_general_basic_phy_env_attr_value_e;

typedef enum _zcl_general_basic_dev_enabled_attr_value_e {
    ZCL_GEN_BASIC_DEV_ENABLED_ATTR_VALUE_DISABLED          = 0x00,
    ZCL_GEN_BASIC_DEV_ENABLED_ATTR_VALUE_ENABLED           = 0x01,
} zcl_general_basic_dev_enabled_attr_value_e;

#define ZCL_GEN_BASIC_ALARM_MASK_HW_FAULT    0x00
#define ZCL_GEN_BASIC_ALARM_MASK_SW_FAULT    0x01

#define ZCL_GEN_BASIC_DIS_LOC_CFG_RESET_MASK      0x01
#define ZCL_GEN_BASIC_DIS_LOC_CFG_DEV_CFG_MASK    0x02

typedef struct _zcl_general_basic_data_t {
    uint32_t flag;
    uint8_t  zcl_version;
    uint8_t  app_version;
    uint8_t  stack_version;
    uint8_t  hw_version;
    uint8_t  mfr_name[ZCL_MAX_STR_SIZE]; 
    uint8_t  model_id[ZCL_MAX_STR_SIZE]; 
    uint8_t  date_code[ZCL_MAX_STR_SIZE/2]; 
    uint8_t  power_src; 
    uint8_t  loc_desc[ZCL_MAX_STR_SIZE/2]; 
    uint8_t  phy_env;
    uint8_t  device_enabled;
    uint8_t  alarm_mask;
    uint8_t  disable_local_config;
} zcl_general_basic_data_t;

typedef struct _zcl_cluster_basic_t {
    zcl_cluster_t cluster_type;
    zcl_general_basic_data_t data;
} zcl_cluster_basic_t;

uint32_t zcl_general_basic_cluster_init(zcl_cluster_basic_t *basic_cluster);

void set_general_basic_loc_desc_update_cb(uint8_t (*cb)(struct _zcl_attr_t *attr, void *data, uint32_t len));

void set_general_basic_phy_env_update_cb(uint8_t (*cb)(struct _zcl_attr_t *attr, void *data, uint32_t len));

void set_general_basic_dev_enabled_update_cb(uint8_t (*cb)(struct _zcl_attr_t *attr, void *data, uint32_t len));

void set_general_basic_alarm_mask_update_cb(uint8_t (*cb)(struct _zcl_attr_t *attr, void *data, uint32_t len));

void set_general_basic_dis_loc_cfg_update_cb(uint8_t (*cb)(struct _zcl_attr_t *attr, void *data, uint32_t len));

#endif
