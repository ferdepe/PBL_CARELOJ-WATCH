/*
 * lwip_tcp.h
 *
 *  Created on: 1 Xuñ, 2016
 *      Author: fer
 */

#ifndef LWIP_TCP_H_
#define LWIP_TCP_H_

#include "config.h"

int HAL_LWIP_TCP_init(void);
void HAL_LWIP_TCP_setBuffEnvio(char *in_str,int len);
int HAL_LWIP_TCP_launchClient(void);
void HAL_LWIP_TCP_refreshIO(void);

#endif /* LWIP_TCP_H_ */
