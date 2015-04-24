#ifndef _ZCL_MSG_H
#define _ZCL_MSG_H

#include <stdint.h>

typedef enum _zcl_status_e {
    ZCL_STATUS_SUCCESS                  = 0x00,
    ZCL_STATUS_FAIL                     = 0x01,
    ZCL_STATUS_MALFORMED_CMD            = 0x80,
    ZCL_STATUS_UNSUP_CLUST_CMD          = 0x81,
    ZCL_STATUS_UNSUP_GEN_CMD            = 0x82,
    ZCL_STATUS_UNSUP_MANUF_CLUST_CMD    = 0x83,
    ZCL_STATUS_UNSUP_MANUF_GEN_CMD      = 0x84,
    ZCL_STATUS_INVALID_FIELD            = 0x85,
    ZCL_STATUS_UNSUP_ATTR               = 0x86,
    ZCL_STATUS_INVALID_VALUE            = 0x87,
    ZCL_STATUS_READ_ONLY                = 0x88,
    ZCL_STATUS_INSUFF_SPACE             = 0x89,
    ZCL_STATUS_DUPE_EXISTS              = 0x8a,
    ZCL_STATUS_NOT_FOUND                = 0x8b,
    ZCL_STATUS_UNREPORTABLE_ATTR        = 0x8c,
    ZCL_STATUS_INVALID_TYPE             = 0x8d,
    ZCL_STATUS_HW_FAIL                  = 0xc0,
    ZCL_STATUS_SW_FAIL                  = 0xc1,
    ZCL_STATUS_CALIB_ERR                = 0xc2,
    ZCL_STATUS_DISC_COMPLETE            = 0x01,
    ZCL_STATUS_DISC_INCOMPLETE          = 0x00, 
} zcl_status_e;

typedef enum _zcl_fcf_frame_type_e {
    ZCL_FCF_FRAME_TYPE_GENERAL      = 0,
    ZCL_FCF_FRAME_TYPE_CLUSTER_SPEC = 1,
} zcl_fcf_frame_type_e;

typedef enum _zcl_general_cmd_e {
    ZCL_GENERAL_CMD_READ_ATTR               = 0x00,
    ZCL_GENERAL_CMD_READ_ATTR_RESP          = 0x01,
    ZCL_GENERAL_CMD_WRITE_ATTR              = 0x02,
    ZCL_GENERAL_CMD_WRITE_ATTR_RESP         = 0x03,
    ZCL_GENERAL_CMD_WRITE_ATTR_UNDIV        = 0x04,
    ZCL_GENERAL_CMD_WRITE_ATTR_NO_RESP      = 0x05,
    ZCL_GENERAL_CMD_CONFIG_REPORT           = 0x06,
    ZCL_GENERAL_CMD_CONFIG_REPORT_RESP      = 0x07,
    ZCL_GENERAL_CMD_READ_REPORT_CONFIG      = 0x08,
    ZCL_GENERAL_CMD_READ_REPORT_CONFIG_RESP = 0x09,
    ZCL_GENERAL_CMD_REPORT_ATTR             = 0x0a,
    ZCL_GENERAL_CMD_DEFAULT_RESP            = 0x0b,
    ZCL_GENERAL_CMD_DISC_ATTR               = 0x0c,
    ZCL_GENERAL_CMD_DISC_ATTR_RESP          = 0x0d,
} zcl_general_cmd_e;

typedef enum _zcl_fcf_dir_e {
    ZCL_FCF_DIR_CLIENT_TO_SERVER = 0x0,
    ZCL_FCF_DIR_SERVER_TO_CLIENT = 0x1,
} zcl_fcf_dir_e;

//Frame Control Field
typedef struct _zcl_fcf_t {
    uint8_t frame_type:2;
    uint8_t mfr_spec:1;
    uint8_t dir:1;
    uint8_t dis_def_resp:1;
    uint8_t reserved:3;
} zcl_fcf_t;

typedef struct _zcl_header_t {
    uint8_t   cluster_id;//need specify cluster id in header, in zigbee it is in sub-app layer 
    zcl_fcf_t fcf;
    uint16_t  mft_code;
    uint8_t   seq;
    uint8_t   cmd_id;
    uint8_t   payload[0];
} zcl_header_t;

uint32_t zcl_get_attr_value_size(zcl_attr_t *attr, uint8_t *data, uint32_t max_len);

uint32_t zcl_msg_handler(uip_ipaddr_t *src_ip, uint8_t *data, uint32_t len, 
                         uint8_t *resp, uint32_t resp_len);

#endif
