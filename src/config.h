/*
 * config.h
 *
 *  Created on: 4 Mar, 2016
 *      Author: Fernando
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define NUMBER_SENSORS 3 //2Sensores + 1Reloj

#define LONG_TRAMA_DATOS 50

typedef enum{
	PULSOMETRO,
	BASCULA,
	GPS
}CONFIG_SENSORS;

typedef enum{
	BPM,
	KG,
	GRADOS_N,
	GRADOS_S
}CONFIG_UNITS;

#endif /* CONFIG_H_ */
