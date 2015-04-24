#ifndef _LEVEL_CTRL_H
#define _LEVEL_CTRL_H

typedef enum _zcl_general_level_ctrl_attr_id_e {
    ZCL_GEN_LEVEL_CTRL_ATTR_ID_CURRENT_LEVEL            = 0x0000,
    ZCL_GEN_LEVEL_CTRL_ATTR_ID_REMAINING_TIME           = 0x0001,
    ZCL_GEN_LEVEL_CTRL_ATTR_ID_ON_OFF_TRANSITION_TIME   = 0x0010,
    ZCL_GEN_LEVEL_CTRL_ATTR_ID_ON_LEVEL                 = 0x0011,
} zcl_general_level_ctrl_attr_id_e;

#endif
