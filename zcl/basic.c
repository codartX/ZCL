#include <string.h>
#include "basic.h"

zcl_attr_t zcl_general_basic_cluster_attrs[] = {
    {ZCL_GEN_BASIC_ATTR_ID_ZCL_VERSION   , ZCL_ATTR_TYPE_UINT8,            ZCL_ATTR_ACCESS_READ_ONLY,  true,  NULL, 1, NULL, {0}},  
    {ZCL_GEN_BASIC_ATTR_ID_APP_VERSION   , ZCL_ATTR_TYPE_UINT8,            ZCL_ATTR_ACCESS_READ_ONLY,  false, NULL, 1, NULL, {0}},
    {ZCL_GEN_BASIC_ATTR_ID_STACK_VERSION , ZCL_ATTR_TYPE_UINT8,            ZCL_ATTR_ACCESS_READ_ONLY,  false, NULL, 1, NULL, {0}},
    {ZCL_GEN_BASIC_ATTR_ID_HW_VERSION    , ZCL_ATTR_TYPE_UINT8,            ZCL_ATTR_ACCESS_READ_ONLY,  false, NULL, 1, NULL, {0}},
    {ZCL_GEN_BASIC_ATTR_ID_MFR_NAME      , ZCL_ATTR_TYPE_CHARACTER_STRING, ZCL_ATTR_ACCESS_READ_ONLY,  false, NULL, 0, NULL, {0}},
    {ZCL_GEN_BASIC_ATTR_ID_MODEL_ID      , ZCL_ATTR_TYPE_CHARACTER_STRING, ZCL_ATTR_ACCESS_READ_ONLY,  false, NULL, 0, NULL, {0}},
    {ZCL_GEN_BASIC_ATTR_ID_DATE_CODE     , ZCL_ATTR_TYPE_CHARACTER_STRING, ZCL_ATTR_ACCESS_READ_ONLY,  false, NULL, 0, NULL, {0}},
    {ZCL_GEN_BASIC_ATTR_ID_PWR_SRC       , ZCL_ATTR_TYPE_ENUM_8BIT,        ZCL_ATTR_ACCESS_READ_ONLY,  true,  NULL, 1, NULL, {0}},
    {ZCL_GEN_BASIC_ATTR_ID_LOC_DESC      , ZCL_ATTR_TYPE_CHARACTER_STRING, ZCL_ATTR_ACCESS_READ_WRITE, false, NULL, 0, NULL, {0}},
    {ZCL_GEN_BASIC_ATTR_ID_PHY_ENV       , ZCL_ATTR_TYPE_ENUM_8BIT,        ZCL_ATTR_ACCESS_READ_WRITE, false, NULL, 1, NULL, {0}},
    {ZCL_GEN_BASIC_ATTR_ID_DEV_ENABLED   , ZCL_ATTR_TYPE_BOOL,             ZCL_ATTR_ACCESS_READ_WRITE, false, NULL, 1, NULL, {0}},
    {ZCL_GEN_BASIC_ATTR_ID_ALARM_MASK    , ZCL_ATTR_TYPE_ENUM_8BIT,        ZCL_ATTR_ACCESS_READ_WRITE, false, NULL, 1, NULL, {0}},
    {ZCL_GEN_BASIC_ATTR_ID_DIS_LOC_CFG   , ZCL_ATTR_TYPE_ENUM_8BIT,        ZCL_ATTR_ACCESS_READ_WRITE, false, NULL, 1, NULL, {0}},
};

void set_general_basic_loc_desc_update_cb(uint8_t (*cb)(struct _zcl_attr_t *attr, void *data, uint32_t len))
{
    zcl_general_basic_cluster_attrs[8].update_cb = cb; 
    return;
}

void set_general_basic_phy_env_update_cb(uint8_t (*cb)(struct _zcl_attr_t *attr, void *data, uint32_t len))
{
    zcl_general_basic_cluster_attrs[9].update_cb = cb; 
    return;
}

void set_general_basic_dev_enabled_update_cb(uint8_t (*cb)(struct _zcl_attr_t *attr, void *data, uint32_t len))
{
    zcl_general_basic_cluster_attrs[10].update_cb = cb; 
    return;

}

void set_general_basic_alarm_mask_update_cb(uint8_t (*cb)(struct _zcl_attr_t *attr, void *data, uint32_t len))
{
    zcl_general_basic_cluster_attrs[11].update_cb = cb; 
    return;

}

void set_general_basic_dis_loc_cfg_update_cb(uint8_t (*cb)(struct _zcl_attr_t *attr, void *data, uint32_t len))
{
    zcl_general_basic_cluster_attrs[12].update_cb = cb; 
    return;
}

uint32_t zcl_general_basic_cluster_init(zcl_cluster_basic_t *basic_cluster)
{
    if (!basic_cluster) {
        return ZCL_FAIL;
    } 

    basic_cluster->cluster_type.cluster_id = ZCL_CLUSTER_ID_GENERAL_BASIC; 

    basic_cluster->cluster_type.attr_list = zcl_general_basic_cluster_attrs;

    basic_cluster->cluster_type.spec_handler = NULL;

    //Mandatory attribute
    basic_cluster->data.flag = ZCL_GEN_BASIC_FLAG_ZCL_VER | ZCL_GEN_BASIC_FLAG_POWER_SRC;  
    //Set attribute value to default
    basic_cluster->data.zcl_version          = 0x01;
    basic_cluster->data.app_version          = 0x00;
    basic_cluster->data.stack_version        = 0x00;
    basic_cluster->data.hw_version           = 0x00;
    basic_cluster->data.mfr_name[0]          = '\0';
    basic_cluster->data.model_id[0]          = '\0';
    basic_cluster->data.date_code[0]         = '\0';
    basic_cluster->data.power_src            = 0x00;
    basic_cluster->data.loc_desc[0]          = '\0';
    basic_cluster->data.phy_env              = 0x00;
    basic_cluster->data.device_enabled       = 0x01;
    basic_cluster->data.alarm_mask           = 0x00;
    basic_cluster->data.disable_local_config = 0x00;

    //Init attr data ptr
    basic_cluster->cluster_type.attr_list[0].data = (void *)&basic_cluster->data.zcl_version;  
    basic_cluster->cluster_type.attr_list[1].data = (void *)&basic_cluster->data.app_version;  
    basic_cluster->cluster_type.attr_list[2].data = (void *)&basic_cluster->data.stack_version;  
    basic_cluster->cluster_type.attr_list[3].data = (void *)&basic_cluster->data.hw_version;  
    basic_cluster->cluster_type.attr_list[4].data = (void *)&basic_cluster->data.mfr_name;  
    basic_cluster->cluster_type.attr_list[5].data = (void *)&basic_cluster->data.model_id;  
    basic_cluster->cluster_type.attr_list[6].data = (void *)&basic_cluster->data.date_code;  
    basic_cluster->cluster_type.attr_list[7].data = (void *)&basic_cluster->data.power_src;  
    basic_cluster->cluster_type.attr_list[8].data = (void *)&basic_cluster->data.loc_desc;  
    basic_cluster->cluster_type.attr_list[9].data = (void *)&basic_cluster->data.phy_env;  
    basic_cluster->cluster_type.attr_list[10].data = (void *)&basic_cluster->data.device_enabled;  
    basic_cluster->cluster_type.attr_list[11].data = (void *)&basic_cluster->data.alarm_mask;  
    basic_cluster->cluster_type.attr_list[12].data = (void *)&basic_cluster->data.disable_local_config;  

    return ZCL_SUCCESS;
}

