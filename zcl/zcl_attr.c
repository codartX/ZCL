#include <string.h>
#include <stdlib.h>
#include "zcl_attr.h"
#include "zcl_msg.h"
#include "zcl.h"

int32_t zcl_attr_data_size(uint8_t data_type)
{
    int32_t size = -1;

    switch (data_type) {
        case ZCL_ATTR_TYPE_8BIT:                   
        case ZCL_ATTR_TYPE_BOOL:                   
        case ZCL_ATTR_TYPE_8BIT_BITMAP:            
        case ZCL_ATTR_TYPE_UINT8:                  
        case ZCL_ATTR_TYPE_INT8:                   
        case ZCL_ATTR_TYPE_ENUM_8BIT:              
            return 1;
        case ZCL_ATTR_TYPE_16BIT:                  
        case ZCL_ATTR_TYPE_16BIT_BITMAP:           
        case ZCL_ATTR_TYPE_UINT16:                 
        case ZCL_ATTR_TYPE_INT16:                  
        case ZCL_ATTR_TYPE_ENUM_16BIT:             
        case ZCL_ATTR_TYPE_SEMI_PRECISION:         
        case ZCL_ATTR_TYPE_CLUSTER_ID:            
        case ZCL_ATTR_TYPE_ATTRIBUTE_ID:          
            return 2;
        case ZCL_ATTR_TYPE_24BIT:                  
        case ZCL_ATTR_TYPE_24BIT_BITMAP:           
        case ZCL_ATTR_TYPE_UINT24:                 
        case ZCL_ATTR_TYPE_INT24:                  
            return 3;
        case ZCL_ATTR_TYPE_32BIT:                  
        case ZCL_ATTR_TYPE_32BIT_BITMAP:           
        case ZCL_ATTR_TYPE_UINT32:                 
        case ZCL_ATTR_TYPE_INT32:                  
        case ZCL_ATTR_TYPE_SINGLE_PRECISION:       
        case ZCL_ATTR_TYPE_TIME_OF_DAY:            
        case ZCL_ATTR_TYPE_DATE:                   
        case ZCL_ATTR_TYPE_UTCTIME:                
        case ZCL_ATTR_TYPE_BACNET_OID:            
            return 4;
        case ZCL_ATTR_TYPE_40BIT:                  
        case ZCL_ATTR_TYPE_40BIT_BITMAP:           
        case ZCL_ATTR_TYPE_UINT40:                 
        case ZCL_ATTR_TYPE_INT40:                  
            return 5;
        case ZCL_ATTR_TYPE_48BIT:                  
        case ZCL_ATTR_TYPE_48BIT_BITMAP:           
        case ZCL_ATTR_TYPE_UINT48:                 
        case ZCL_ATTR_TYPE_INT48:                  
            return 6;
        case ZCL_ATTR_TYPE_56BIT:                  
        case ZCL_ATTR_TYPE_56BIT_BITMAP:           
        case ZCL_ATTR_TYPE_UINT56:                 
        case ZCL_ATTR_TYPE_INT56:                  
            return 7;
        case ZCL_ATTR_TYPE_64BIT:                  
        case ZCL_ATTR_TYPE_64BIT_BITMAP:           
        case ZCL_ATTR_TYPE_UINT64:                 
        case ZCL_ATTR_TYPE_INT64:                  
        case ZCL_ATTR_TYPE_DOUBLE_PRECISION:       
        case ZCL_ATTR_TYPE_IEEE_ADDRESS:          
            return 8;
        case ZCL_ATTR_TYPE_128BIT_SECURITY_KEY:   
            return 16;
        default: 
            return -1;
    }
}

uint8_t zcl_set_attr_value(zcl_attr_t *attr, void *data, uint32_t size)
{
    uint8_t retval = ZCL_STATUS_SUCCESS;

    if (!attr) {
        return 0;
    }

    if (attr->update_cb) {
        retval = attr->update_cb(attr, data, size);
    }

    if (retval == ZCL_STATUS_SUCCESS) {
        memcpy(attr->data, data, size);
        attr->data_size = size;
    }

    return retval;
}

bool zcl_attr_data_type_analog(uint8_t data_type)
{
    if ((data_type >= ZCL_ATTR_TYPE_UINT8 && data_type <= ZCL_ATTR_TYPE_INT64) ||
        (data_type >= ZCL_ATTR_TYPE_SEMI_PRECISION && data_type <= 0x3f)||
        (data_type >= ZCL_ATTR_TYPE_TIME_OF_DAY && data_type <= 0xe7)) {
        return true;
    } else {
        return false;
    }
}

zcl_attr_report_cfg_t *zcl_attr_report_cfg_entry_calloc()
{
    zcl_attr_report_cfg_t *entry = NULL;

    entry = (zcl_attr_report_cfg_t *)malloc(sizeof(zcl_attr_report_cfg_t));
    if (entry) {
        memset(entry, 0x0, sizeof(zcl_attr_report_cfg_t));
        return entry;
    }

    return NULL;
}

void zcl_attr_report_cfg_entry_free(zcl_attr_report_cfg_t *entry)
{
    free(entry); 
    return;
}

uint8_t zcl_attr_add_report_entry(zcl_attr_t *attr, zcl_attr_report_cfg_t *entry)
{
    if (!attr || !entry) {
        return ZCL_FAIL; 
    }
 
    if (attr->report_cfg_list->next) { 
        entry->next = attr->report_cfg_list->next;
    }

    attr->report_cfg_list = entry;

    return ZCL_SUCCESS; 
}

uint8_t zcl_attr_remove_report_entry(zcl_attr_t *attr, uip_ipaddr_t *ipaddr)
{
    zcl_attr_report_cfg_t *node = NULL, *pre_node = NULL;

    if (!attr || !ipaddr) {
        return ZCL_FAIL; 
    }
 
    node = attr->report_cfg_list;

    while (node) {
        if (!memcmp(&node->ipaddr, ipaddr, sizeof(uip_ipaddr_t))) {
            if (pre_node == NULL) {
                attr->report_cfg_list = node->next;
            } else {
                pre_node->next = node->next;
            }
            zcl_attr_report_cfg_entry_free(node); 
            break;
        }
        pre_node = node;
        node = node->next;
    }
 
    return ZCL_SUCCESS; 
}
