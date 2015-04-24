#ifndef _SCENES_H
#define _SCENES_H

typedef enum _zcl_general_scenes_attr_id_e {
    //Scene Management Info Attribute Set
    ZCL_GEN_SCENES_ATTR_ID_SCENE_COUNT              = 0x0000,
    ZCL_GEN_SCENES_ATTR_ID_CUR_SCENE                = 0x0001,
    ZCL_GEN_SCENES_ATTR_ID_CUR_GROUP                = 0x0002,
    ZCL_GEN_SCENES_ATTR_ID_SCENE_VALID              = 0x0003,
    ZCL_GEN_SCENES_ATTR_ID_NAME_SUPPORT             = 0x0004,
    ZCL_GEN_SCENES_ATTR_ID_LAST_CONFIGURED_BY       = 0x0005,
   
} zcl_general_scenes_attr_id_e; 

#endif
