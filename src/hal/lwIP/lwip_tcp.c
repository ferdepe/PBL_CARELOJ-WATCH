/*
 * lwip_tcp.c
 *
 *  Created on: 1 Xuñ, 2016
 *      Author: fer
 */

#include <stdio.h>
#include <string.h>
#include "lwip_tcp.h"
#include "xparameters.h"
#include "netif/xadapter.h"
#include "lwip/err.h"
#include "lwip/tcp.h"
#include "config.h"

#define PLATFORM_EMAC_BASEADDR XPAR_XEMACPS_0_BASEADDR

/* missing declaration in lwIP */
void lwip_init();
err_t recv_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
err_t connection_establisted(void *arg, struct tcp_pcb *newpcb, err_t err);

//static
extern struct netif host_netif;
struct netif *time_netif;

char recv_buffer[1024];
static char env_buffer[1024];
static int len_env;

struct ip_addr ipaddr, netmask, gw;


int end;

int HAL_LWIP_TCP_init(void){
	/* the mac address of the board. this should be unique per board */
	unsigned char mac_ethernet_address[] = { 0x00, 0x0a, 0x35, 0x00, 0x01, 0x02 };

	time_netif = &host_netif;

	/* initliaze IP addresses to be used */
	IP4_ADDR(&ipaddr,  10, 0,   2, 16);
	IP4_ADDR(&netmask, 255, 255, 0,  0);
	IP4_ADDR(&gw,      10, 0,   0,  1);

	lwip_init();

	/* Add network9 interface to the netif_list, and set it as default */
	if (!xemac_add(&host_netif, &ipaddr, &netmask,
						&gw, mac_ethernet_address,
						PLATFORM_EMAC_BASEADDR)) {
		return -1;
	}
	netif_set_default(&host_netif);

	/* specify that the network if is up */
	netif_set_up(&host_netif);

	return 0;
}

void HAL_LWIP_TCP_setBuffEnvio(char *in_str,int len){
	//dataToSend.valuesRegister[0]=a;
	len_env = len;
	memcpy(env_buffer,in_str,len_env);
}

int HAL_LWIP_TCP_launchClient(void){
	struct tcp_pcb *pcb;
	err_t err;
	unsigned port = 7;

	int retval = 0;
	struct ip_addr ipaddr, netmask, gw;

	/* create new TCP PCB structure */
	pcb = tcp_new();
	if (!pcb) {
		xil_printf("Error creating PCB. Out of Memory\n\r");
		return -1;
	}

	/* bind to specified @port */
	err = tcp_bind(pcb, IP_ADDR_ANY, port);
	if (err != ERR_OK) {
		xil_printf("Unable to bind to port %d: err = %d\n\r", port, err);
		return -2;
	}

	/* we do not need any arguments to callback functions */
	tcp_arg(pcb, NULL);

	/* set the receive callback for this connection */
	tcp_recv(pcb, recv_callback);
	//tcp_err(pcb,err_callback);

	IP4_ADDR(&ipaddr,  10, 0,   2, 15);
	IP4_ADDR(&netmask, 255, 255, 0,  0);
	IP4_ADDR(&gw,      10, 0,   0,  1);
	retval = tcp_connect(pcb, (ip_addr_t *)(&ipaddr), 5000, connection_establisted);
	xil_printf("TCP time service client started %d\n\r", port);

	return retval;
}

void HAL_LWIP_TCP_refreshIO(void){
	xemacif_input(&host_netif);
}

//LOCALES
err_t recv_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err){
	char *pc;
	char env[sizeof(DATAMANAGEMENT_DATA_SEND)];
	int i = 0;
	int len = 0;
	/* do not read the packet if we are not in ESTABLISHED state */
	if (!p) {
		tcp_close(tpcb);
		tcp_recv(tpcb, NULL);
		return ERR_OK;
	}


	/* indicate that the packet has been received */
	tcp_recved(tpcb, p->len);
	pc = (char *)p->payload;
	len = p->tot_len;//len = p->len;

	for (i=0; i<len; i++)recv_buffer[i]= pc[i];

	recv_buffer[len] ='\0';

	xil_printf("%d",err);
	xil_printf("Data: %s\n\r",recv_buffer);

	/* PRUEBA STRUCT */

	//memcpy(env,&dataToSend,sizeof(DATAMANAGEMENT_DATA_SEND));

	/* free the received pbuf */
	if ((tcp_sndbuf(tpcb) > p->len) && (strcmp(recv_buffer,"@c") == 0)) {
			err = tcp_write(tpcb, env_buffer, len_env, 1);
		} else
			xil_printf("no space in tcp_sndbuf\n\r");
	pbuf_free(p);
	//cont = 1;
	return ERR_OK;
}

err_t connection_establisted(void *arg, struct tcp_pcb *newpcb, err_t err)
{
    xil_printf("\nConnection callback is called \n");
   return err;
}
