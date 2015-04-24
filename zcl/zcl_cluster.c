#include <string.h>
#include "zcl_cluster.h"

zcl_attr_t *zcl_cluster_find_attr(zcl_cluster_t *cluster, uint16_t attr_id)
{
    uint8_t i = 0;

    while (cluster->attr_list[i]) {
        if (cluster->attr_list[i].id == attr_id) {
            return &(cluster->attr_list[i]);
        } 
        i++;
    }  

    return NULL;
}
