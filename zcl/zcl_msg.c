#include <string.h>
#include "zcl.h"
#include "zcl_msg.h"
#include "zcl_cluster.h"

uint8_t seq_num;

uint8_t zcl_get_seq_num()
{
    return seq_num++;
}

uint32_t zcl_get_attr_value_size(zcl_attr_t *attr, uint8_t *data, uint32_t max_len)
{
    uint32_t size = 0;

    switch (attr->type) {
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
        case ZCL_ATTR_TYPE_OCTECT_STRING:          
        case ZCL_ATTR_TYPE_CHARACTER_STRING:       
            return *(uint8_t *)data;
        case ZCL_ATTR_TYPE_LONG_OCTECT_STRING:     
        case ZCL_ATTR_TYPE_LONG_CHARACTER_STRING:  
            return *(uint16_t *)data;
        case ZCL_ATTR_TYPE_ARRAY:                  
        case ZCL_ATTR_TYPE_STRUCTURE:              
        case ZCL_ATTR_TYPE_SET:                    
        case ZCL_ATTR_TYPE_BAG:                    
        case ZCL_ATTR_TYPE_128BIT_SECURITY_KEY:   
            return 16;
        default: 
            return 0;
    }

}

static uint32_t zcl_cmd_read_attr(uint8_t *data, uint32_t len, 
                                  zcl_cluster_t *cluster, 
                                  uint8_t *resp, uint32_t resp_len)
{
    zcl_header_t *zcl_header = NULL;
    zcl_attr_t *attr = NULL;
    uint8_t *payload = NULL, *resp_ptr = resp;
    uint16_t attr_id = 0;

    memcpy(resp_ptr, data, sizeof(zcl_header_t));
    resp_ptr += sizeof(zcl_header_t);
    zcl_header = (zcl_header_t *)resp_ptr;
    zcl_header->fcf.dir = ZCL_FCF_DIR_SERVER_TO_CLIENT;
    zcl_header->cmd_id = ZCL_GENERAL_CMD_READ_ATTR_RESP; 
   
    payload = data + sizeof(zcl_header_t);
    while((payload - data) < len) {
        if ((resp_len - (resp_ptr - resp)) < 3) {
            break;
        }
        attr_id = *((uint16_t *)payload); 
        attr = zcl_cluster_find_attr(cluster, attr_id); 
        *((uint16_t *)resp_ptr) = attr_id; 
        resp_ptr += 2;
        if (attr) {
            if ((resp_len - (resp_ptr - resp) - 1) < attr->data_size) {
                *(uint8_t *)resp_ptr = ZCL_STATUS_INSUFF_SPACE; 
                resp_ptr += 1;
                break;
            } else {
                *(uint8_t *)resp_ptr = ZCL_STATUS_SUCCESS; 
                resp_ptr += 1;
                *(uint8_t *)resp_ptr = attr->type;; 
                resp_ptr += 1;
                memcpy(resp_ptr, attr->data, attr->data_size);
                resp_ptr += attr->data_size;
            }
        } else {
            *(uint8_t *)resp_ptr = ZCL_STATUS_UNSUP_ATTR; 
            resp_ptr += 1;
        }

        payload += 2; 
    }

    return (resp_ptr - resp);
}

static uint32_t zcl_cmd_write_attr(uint8_t *data, uint32_t len, 
                                   zcl_cluster_t *cluster, 
                                   uint8_t *resp, uint32_t resp_len)
{
    zcl_header_t *zcl_header = NULL;
    zcl_attr_t *attr = NULL;
    uint8_t *payload = NULL, *resp_ptr = resp;
    uint16_t attr_id = 0;
    uint8_t status = ZCL_STATUS_SUCCESS;
    uint32_t data_size = 0;

    memcpy(resp_ptr, data, sizeof(zcl_header_t));
    resp_ptr += sizeof(zcl_header_t);
    zcl_header = (zcl_header_t *)resp_ptr;
    zcl_header->fcf.dir = ZCL_FCF_DIR_SERVER_TO_CLIENT;
    zcl_header->cmd_id = ZCL_GENERAL_CMD_WRITE_ATTR_RESP; 
   
    payload = data + sizeof(zcl_header_t);
    while((payload - data) < len) {
        if ((resp_len - (resp_ptr - resp)) < 3) {
            break;
        }
        attr_id = *((uint16_t *)payload); 
        payload += 2;
        attr = zcl_cluster_find_attr(cluster, attr_id); 
        if (attr) {
            if (attr->type != *(uint8_t *)payload) {
                status = ZCL_STATUS_INVALID_TYPE; 
            } else {
                if (data_size = zcl_get_attr_value_size(attr, payload, len - (payload - data))) {
                    status = zcl_set_attr_value(attr, payload, data_size);
                } else {
                    status = ZCL_STATUS_INVALID_VALUE;
                }
            }
        } else {
            status = ZCL_STATUS_UNSUP_ATTR; 
        }

        *((uint8_t *)resp_ptr) = status; 
        resp_ptr += 1;
        *((uint16_t *)resp_ptr) = attr_id; 
        resp_ptr += 2;

        if (status == ZCL_STATUS_UNSUP_ATTR) {
            continue;
        } else if (data_size == 0) {
            break;
        } else {
            payload += data_size;
        }

        data_size = 0;
    }

    return (resp_ptr - resp);
}

static uint32_t zcl_parse_report_record(uip_ipaddr_t *src_ip, zcl_cluster_t *cluster, 
                                        uint8_t *data, uint32_t max_len, uint8_t *status)
{
    zcl_attr_t *attr = NULL;
    uint8_t *data_ptr = data;
    uint8_t dir, data_size;
    uint16_t attr_id;
    zcl_attr_report_cfg_t *entry = NULL;

    if (max_len > 3) {
        dir = *data_ptr++;
        attr_id = *(uint16_t *)data_ptr;
        data_ptr += 2;
    } else {
        *status = ZCL_STATUS_INVALID_FIELD;
        return 0;
    }

    attr = zcl_cluster_find_attr(cluster, attr_id); 
    if (!attr) {
        *status = ZCL_STATUS_UNSUP_ATTR;
        return 0;
    }

    if (attr->type != *data_ptr) {
        *status = ZCL_STATUS_INVALID_TYPE;
        return 0;
    }
    data_ptr++;

    if (dir == 0x00) {
        if (zcl_attr_data_type_analog(attr->type)) {
            entry = zcl_attr_report_cfg_entry_calloc();
            if (!entry) {
                *status = ZCL_STATUS_INSUFF_SPACE;
                return 0;
            }
            memcpy(&entry->ipaddr, src_ip, sizeof(uip_ipaddr_t));                        
            entry->dir = dir;
            entry->min_report_interval = *data_ptr++;
            entry->max_report_interval = *data_ptr++;
            data_size = zcl_attr_data_size(attr->type);
            memcpy(entry->reportable_change, data_ptr, data_size);
            data_ptr += data_size; 
            return data_ptr - data;
        } else {
            *status = ZCL_STATUS_UNREPORTABLE_ATTR;
            return 0;
        }
 
    } else if (dir == 0x01) {
        entry = zcl_attr_report_cfg_entry_calloc();
        if (!entry) {
            *status = ZCL_STATUS_INSUFF_SPACE;
            return 0;
        }
        memcpy(&entry->ipaddr, src_ip, sizeof(uip_ipaddr_t));                        
        entry->timeout_period = *(uint32_t *)data_ptr; 
        data_ptr += 4;
        return data_ptr - data;
    } else {
        return 0;
    }
} 

static uint32_t zcl_cmd_config_report(uip_ipaddr_t *src_ip, uint8_t *data, uint32_t len, 
                                      zcl_cluster_t *cluster, uint8_t *resp, uint32_t resp_len)
{
    zcl_header_t *zcl_header = NULL;
    zcl_attr_t *attr = NULL;
    uint8_t *payload = NULL, *resp_ptr = resp;
    uint16_t attr_id = 0;
    uint8_t status = ZCL_STATUS_SUCCESS;
    uint32_t data_size = 0;

    memcpy(resp_ptr, data, sizeof(zcl_header_t));
    resp_ptr += sizeof(zcl_header_t);
    zcl_header = (zcl_header_t *)resp_ptr;
    zcl_header->fcf.dir = ZCL_FCF_DIR_SERVER_TO_CLIENT;
    zcl_header->cmd_id = ZCL_GENERAL_CMD_CONFIG_REPORT_RESP; 
   
    payload = data + sizeof(zcl_header_t);
    while((payload - data) < len) {
        data_size = zcl_parse_report_record(src_ip, cluster, payload, 
                                            len - (payload - data), &status);
        *((uint8_t *)resp_ptr) = status; 
        resp_ptr += 1;
        //direction
        *((uint8_t *)resp_ptr) = *(uint8_t *)payload; 
        resp_ptr += 1;
        *((uint16_t *)resp_ptr) = attr_id; 
        resp_ptr += 2;
        if (data_size) {
            payload += data_size; 
        } else {
            break;
        }
    }

    return (resp_ptr - resp);
}

uint32_t zcl_cmd_report_attr(uip_ipaddr_t *dst_ip, zcl_cluster_t *cluster, 
                              zcl_attr_t *attr, uint8_t *buf, uint32_t buf_maxlen)
{


}

static uint32_t zcl_cmd_handler(uip_ipaddr_t *src_ip, uint8_t *data, uint32_t len, 
                                zcl_cluster_t *cluster, uint8_t *resp, uint32_t resp_len)
{
    zcl_header_t *zcl_header = NULL;

    zcl_header = (zcl_header_t *)data;
   
    switch (zcl_header->cmd_id) {
        case ZCL_GENERAL_CMD_READ_ATTR:              
            return zcl_cmd_read_attr(data, len, cluster, resp, resp_len);
        case ZCL_GENERAL_CMD_READ_ATTR_RESP:         
            break;
        case ZCL_GENERAL_CMD_WRITE_ATTR:             
            return zcl_cmd_write_attr(data, len, cluster, resp, resp_len);
        case ZCL_GENERAL_CMD_WRITE_ATTR_RESP:        
            break;
        case ZCL_GENERAL_CMD_WRITE_ATTR_UNDIV:       
            break;
        case ZCL_GENERAL_CMD_WRITE_ATTR_NO_RESP:     
            zcl_cmd_write_attr(data, len, cluster, resp, resp_len);
            return 0;
        case ZCL_GENERAL_CMD_CONFIG_REPORT:          
            return zcl_cmd_config_report(src_ip, data, len, cluster, resp, resp_len);
        case ZCL_GENERAL_CMD_CONFIG_REPORT_RESP:     
            break;
        case ZCL_GENERAL_CMD_READ_REPORT_CONFIG:     
            break;
        case ZCL_GENERAL_CMD_READ_REPORT_CONFIG_RESP:
            break;
        case ZCL_GENERAL_CMD_REPORT_ATTR:            
            break;
        case ZCL_GENERAL_CMD_DEFAULT_RESP:           
            break;
        case ZCL_GENERAL_CMD_DISC_ATTR:              
            break;
        case ZCL_GENERAL_CMD_DISC_ATTR_RESP:         
            break;
        default:
            return 0;
    }

    return 0;
}

uint32_t zcl_msg_handler(uip_ipaddr_t *src_ip, uint8_t *data, uint32_t len, 
                         uint8_t *resp, uint32_t resp_len)
{
    zcl_header_t *zcl_header = NULL;
    zcl_cluster_t *cluster = NULL;

    if (!data || !(len > sizeof(zcl_header_t)) || 
        !resp || !(resp_len > sizeof(zcl_header_t))) {
        return 0;
    }
 
    zcl_header = (zcl_header_t *)data;

    cluster = zcl_find_cluster(zcl_header->cluster_id);

    if (cluster) {
        if (zcl_header->fcf.frame_type == ZCL_FCF_FRAME_TYPE_GENERAL) {
            return zcl_cmd_handler(src_ip, data, len, cluster, resp, resp_len);
        } else {
            return cluster->spec_handler(src_ip, data, len, cluster, resp, resp_len);
        }
    }

    return 0;
}

