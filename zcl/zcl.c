#include "contiki-net.h"
#include "net/uip.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "zcl.h"
#include "zcl_msg.h"
#include "device.h"

#include "net/uip-debug.h"

#define ZCL_MAX_BUF_SIZE    1024

#define UIP_IP_BUF   ((struct uip_ip_hdr *)&uip_buf[UIP_LLH_LEN])

static struct uip_udp_conn *server_conn;

static zcl_cluster_t **dev_cluster_list;

static uint8_t buf[ZCL_MAX_BUF_SIZE];

void set_dev_cluster_list(zcl_cluster_t **cluster_list)
{
    dev_cluster_list = cluster_list;
}

zcl_cluster_t *zcl_find_cluster(uint16_t cluster_id)
{
    uint8_t i;

    if (dev_cluster_list) {
        for (i = 0; dev_cluster_list[i]; i++) {
            if (dev_cluster_list[i]->cluster_id == cluster_id) {
                return dev_cluster_list[i];
            }
        }
    }

    return NULL; 
}

static void
udp_handler(void)
{
    uint32_t resp_len = 0;

    if(uip_newdata()) {
        PRINTF("Server received data from ");
        PRINT6ADDR(&UIP_IP_BUF->srcipaddr);
        PRINTF("\n");

        resp_len = zcl_msg_handler(&UIP_IP_BUF->srcipaddr, (uint8_t *)uip_appdata, uip_datalen(), 
                                   buf, ZCL_MAX_BUF_SIZE);
   
        if (resp_len) {
            uip_ipaddr_copy(&server_conn->ripaddr, &UIP_IP_BUF->srcipaddr);
            uip_udp_packet_send(server_conn, buf, resp_len);
            uip_create_unspecified(&server_conn->ripaddr);
        }
    }
}

PROCESS(zcl_process, "ZCL Process");

PROCESS_THREAD(zcl_process, ev, data)
{
#if UIP_CONF_ROUTER
    uip_ipaddr_t ipaddr;
#endif /* UIP_CONF_ROUTER */

    PROCESS_BEGIN();
    PRINTF("ZCL UDP server started\n");

#if UIP_CONF_ROUTER
    uip_ip6addr(&ipaddr, 0xaaaa, 0, 0, 0, 0, 0, 0, 0);
    uip_ds6_set_addr_iid(&ipaddr, &uip_lladdr);
    uip_ds6_addr_add(&ipaddr, 0, ADDR_AUTOCONF);
#endif /* UIP_CONF_ROUTER */

    //print_local_addresses();

    if (dev_zcl_init() != ZCL_SUCCESS) {
        PRINTF("Device init fail!\n");
        PROCESS_EXIT();
    }

    server_conn = udp_new(NULL, UIP_HTONS(ZCL_UDP_CLIENT_PORT), NULL);
    if(server_conn == NULL) {
        PRINTF("No UDP connection available, exiting the process!\n");
        PROCESS_EXIT();
    }
    udp_bind(server_conn, UIP_HTONS(ZCL_UDP_SERVER_PORT));

    while(1) {
        PROCESS_YIELD();
        if(ev == tcpip_event) {
            udp_handler();
        }
    }

    PROCESS_END();
}

