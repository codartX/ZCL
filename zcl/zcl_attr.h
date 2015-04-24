#ifndef _ZCL_ATTR_H
#define _ZCL_ATTR_H

#include <stdint.h>
#include <stdbool.h>
#include "net/uip.h"

typedef enum _zcl_attr_type_e {
    //NULL
    ZCL_ATTR_TYPE_NO_DATA               = 0x00,
    //General data
    ZCL_ATTR_TYPE_8BIT                  = 0x08, 
    ZCL_ATTR_TYPE_16BIT                 = 0x09, 
    ZCL_ATTR_TYPE_24BIT                 = 0x0a, 
    ZCL_ATTR_TYPE_32BIT                 = 0x0b, 
    ZCL_ATTR_TYPE_40BIT                 = 0x0c, 
    ZCL_ATTR_TYPE_48BIT                 = 0x0d, 
    ZCL_ATTR_TYPE_56BIT                 = 0x0e, 
    ZCL_ATTR_TYPE_64BIT                 = 0x0f, 
    //Logical
    ZCL_ATTR_TYPE_BOOL                  = 0x10, 
    //Bitmap
    ZCL_ATTR_TYPE_8BIT_BITMAP           = 0x18, 
    ZCL_ATTR_TYPE_16BIT_BITMAP          = 0x19, 
    ZCL_ATTR_TYPE_24BIT_BITMAP          = 0x1a, 
    ZCL_ATTR_TYPE_32BIT_BITMAP          = 0x1b, 
    ZCL_ATTR_TYPE_40BIT_BITMAP          = 0x1c, 
    ZCL_ATTR_TYPE_48BIT_BITMAP          = 0x1d, 
    ZCL_ATTR_TYPE_56BIT_BITMAP          = 0x1e, 
    ZCL_ATTR_TYPE_64BIT_BITMAP          = 0x1f, 
    //Unsigned integer
    ZCL_ATTR_TYPE_UINT8                 = 0x20, 
    ZCL_ATTR_TYPE_UINT16                = 0x21, 
    ZCL_ATTR_TYPE_UINT24                = 0x22, 
    ZCL_ATTR_TYPE_UINT32                = 0x23, 
    ZCL_ATTR_TYPE_UINT40                = 0x24, 
    ZCL_ATTR_TYPE_UINT48                = 0x25, 
    ZCL_ATTR_TYPE_UINT56                = 0x26, 
    ZCL_ATTR_TYPE_UINT64                = 0x27, 
    //Signed integer
    ZCL_ATTR_TYPE_INT8                  = 0x28, 
    ZCL_ATTR_TYPE_INT16                 = 0x29, 
    ZCL_ATTR_TYPE_INT24                 = 0x2a, 
    ZCL_ATTR_TYPE_INT32                 = 0x2b, 
    ZCL_ATTR_TYPE_INT40                 = 0x2c, 
    ZCL_ATTR_TYPE_INT48                 = 0x2d, 
    ZCL_ATTR_TYPE_INT56                 = 0x2e, 
    ZCL_ATTR_TYPE_INT64                 = 0x2f, 
    //Enumeration
    ZCL_ATTR_TYPE_ENUM_8BIT             = 0x30, 
    ZCL_ATTR_TYPE_ENUM_16BIT            = 0x31, 
    //Floating point
    ZCL_ATTR_TYPE_SEMI_PRECISION        = 0x38, 
    ZCL_ATTR_TYPE_SINGLE_PRECISION      = 0x39, 
    ZCL_ATTR_TYPE_DOUBLE_PRECISION      = 0x3a, 
    //String
    ZCL_ATTR_TYPE_OCTECT_STRING         = 0x41, 
    ZCL_ATTR_TYPE_CHARACTER_STRING      = 0x42, 
    ZCL_ATTR_TYPE_LONG_OCTECT_STRING    = 0x43, 
    ZCL_ATTR_TYPE_LONG_CHARACTER_STRING = 0x44, 
    //Ordered sequence
    ZCL_ATTR_TYPE_ARRAY                 = 0x48, 
    ZCL_ATTR_TYPE_STRUCTURE             = 0x4c, 
    //Collection
    ZCL_ATTR_TYPE_SET                   = 0x50, 
    ZCL_ATTR_TYPE_BAG                   = 0x51, 
    //Time
    ZCL_ATTR_TYPE_TIME_OF_DAY           = 0xe0, 
    ZCL_ATTR_TYPE_DATE                  = 0xe1, 
    ZCL_ATTR_TYPE_UTCTIME               = 0xe2, 
    //Identifier
    ZCL_ATTR_TYPE_CLUSTER_ID            = 0xe8,
    ZCL_ATTR_TYPE_ATTRIBUTE_ID          = 0xe9,
    ZCL_ATTR_TYPE_BACNET_OID            = 0xea,
    //Miscellaneous
    ZCL_ATTR_TYPE_IEEE_ADDRESS          = 0xf0,
    ZCL_ATTR_TYPE_128BIT_SECURITY_KEY   = 0xf1,
    
    //Unknown
    ZCL_ATTR_TYPE_UNKNOWN               = 0xff,
} zcl_attr_type_e;

typedef enum _zcl_attr_access_e {
    ZCL_ATTR_ACCESS_READ_ONLY  = 0x00,
    ZCL_ATTR_ACCESS_READ_WRITE = 0x01,
} zcl_attr_access_e;

typedef enum _zcl_attr_mandatory_e {
    ZCL_ATTR_MANDATORY_TRUE  = 0x01,
    ZCL_ATTR_MANDATORY_FALSE = 0x00,
} zcl_attr_mandatory_e;

typedef struct _zcl_attr_report_cfg_t {
    struct _zcl_attr_report_cfg_t *next;
    uip_ipaddr_t  ipaddr;
    uint8_t       dir;
    uint16_t      min_report_interval; 
    uint16_t      max_report_interval; 
    uint16_t      timeout_period; 
    //no uint64_t...
    long int      reportable_change;
    struct etimer timer;
} zcl_attr_report_cfg_t;

typedef struct _zcl_attr_t {
    uint16_t id;
    uint8_t  type;
    uint8_t  access;
    uint8_t  mandatory;//if bool, compiler fail-.-
    void     *data;
    uint32_t data_size;//For cal size of array, structure, set, bag, etc.. easier
    uint8_t  (*update_cb)(struct _zcl_attr_t *attr, void *data, uint32_t len); 
    zcl_attr_report_cfg_t *report_cfg_list;
} zcl_attr_t;

uint8_t zcl_set_attr_value(zcl_attr_t *attr, void *data, uint32_t data_size);

int32_t zcl_attr_data_size(uint8_t data_type);

bool zcl_attr_data_type_analog(uint8_t data_type);

zcl_attr_report_cfg_t *zcl_attr_report_cfg_entry_calloc();

void zcl_attr_report_cfg_entry_free(zcl_attr_report_cfg_t *entry);

uint8_t zcl_attr_add_report_entry(zcl_attr_t *attr, zcl_attr_report_cfg_t *entry);

uint8_t zcl_attr_remove_report_entry(zcl_attr_t *attr, uip_ipaddr_t *ipaddr);

#endif
