/*
 * MMA8451.h
 *
 *  Created on: Sep 3, 2014
 *      Author: Carlos
 */

#ifndef MMA8451_H_
#define MMA8451_H_

#include "PE_Types.h"
#include "PE_LDD.h"

typedef struct {
	volatile bool dataReceivedFlg;
	volatile bool dataTransmittedFlg;
	LDD_TDeviceData *handle;
} MMA8451_TDataState;

void MMA8451_Run(void);

#endif /* MMA8451_H_ */
