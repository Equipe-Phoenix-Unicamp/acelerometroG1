/*
 * MMA8451.c
 *
 *  Created on: Sep 3, 2014
 *      Author: Carlos
 */
#include "LEDR.h"
#include "LEDG.h"
#include "LEDB.h"
#include "CI2C1.h"
#include "MMA8451.h"

#define MMA8451_CTRL_REG_1 0x2A

#define MMA8451_ACTIVE_BIT_MASK 0X01
#define MMA8451_F_READ_BIT_MASK 0X02

#define MMA8451_OUT_X_MSB 0x01
#define MMA8451_OUT_X_LSB 0x02
#define MMA8451_OUT_Y_MSB 0x03
#define MMA8451_OUT_Y_LSB 0x04
#define MMA8451_OUT_Z_MSB 0x05
#define MMA8451_OUT_Z_LSB 0x06

static MMA8451_TDataState deviceData;

uint8_t MMA8451_ReadReg(uint8_t addr, uint8_t *data, short dataSize)
{
	uint8_t res;
	
	res = CI2C1_MasterSendBlock(deviceData.handle, &addr, 1U, LDD_I2C_NO_SEND_STOP);
	if (res!=ERR_OK)
	{
		return ERR_FAILED;
	}
	while(!deviceData.dataTransmittedFlg){}
	deviceData.dataTransmittedFlg = FALSE;
	
	res = CI2C1_MasterReceiveBlock(deviceData.handle, data, dataSize, LDD_I2C_SEND_STOP);
	if (res!=ERR_OK)
	{
		return ERR_FAILED;
	}
	while(!deviceData.dataReceivedFlg){}
	deviceData.dataReceivedFlg = FALSE;
	return ERR_OK;
}

uint8_t MMA8451_WriteReg(uint8_t addr, uint8_t val)
{
	uint8_t buf[2], res;
	
	buf[0] = addr;
	buf[1] = val;
	
	res = CI2C1_MasterSendBlock(deviceData.handle, &buf, 2U, LDD_I2C_SEND_STOP);
	if (res== ERR_OK)
	{
		while (!deviceData.dataTransmittedFlg){}
		deviceData.dataTransmittedFlg = FALSE;
		return ERR_OK;
	}	
	
	return res;
}

static int8_t xyz[3];

float x_antigo[3] = {0,0,0};
float y_antigo[3] = {0,0,0};
float z_antigo[3] = {0,0,0};

float saida_atual[3] = {0,0,0};

float x_filtrado[3] = {0,0,0};
float y_filtrado[3] = {0,0,0};
float z_filtrado[3] = {0,0,0};

void MMA8451_Run(void)
{
	uint8_t res;
	
	LEDR_On();
	LEDG_On();
	LEDB_On();
	float teste[100];
	int i;
	for (i = 0; i< 100;i ++)
	{
		teste[i] = 0;
	}
	float media, soma;
	int h;
	deviceData.handle = CI2C1_Init(&deviceData);
	res = MMA8451_WriteReg(MMA8451_CTRL_REG_1, MMA8451_F_READ_BIT_MASK|MMA8451_ACTIVE_BIT_MASK);
	if (res == ERR_OK)
	{
		for (;;)
		{
			res = MMA8451_ReadReg(MMA8451_OUT_X_MSB, (uint8_t*)&xyz, 3);
			LEDR_Put(xyz[0]>40 || xyz[0]<-40);
			LEDG_Put(xyz[1]>40 || xyz[1]<-40);
			LEDB_Put(xyz[2]>40 || xyz[2]<-40);
			printf("[%5d %5d %5d]\t", xyz[0], xyz[1], xyz[2]);
			for (h = 0; h < 99; h++)
			{
				teste[h] = teste[h+1];
			}
			teste[99] = (float)xyz[0];
			soma = 0;
			for (h = 0; h < 100; h++)
			{
				soma += teste[h];
			}
			media = soma/100.0;
			
			printf("[%9.9f]\n", media);
			//WAIT1_Waitms(1);
			/*
			saida_atual[0] = 2.45*xyz[0] + 7.349*x_antigo[0] + 7.349*x_antigo[1] + 2.45*x_antigo[2] + 2925*10000*x_filtrado[0] - 295*100000*x_filtrado[1] + 9752*1000*x_filtrado[2];
			saida_atual[1] = 2.45*0.0000001*xyz[1] + 7.349*0.0000001*y_antigo[0] + 7.349*0.0000001*y_antigo[1] + 2.45*0.0000001*y_antigo[2] + 2.925*y_filtrado[0] - 2.95*y_filtrado[1] + 0.9752*y_filtrado[2];
			saida_atual[2] = 2.45*0.0000001*xyz[2] + 7.349*0.0000001*z_antigo[0] + 7.349*0.0000001*z_antigo[1] + 2.45*0.0000001*z_antigo[2] + 2.925*z_filtrado[0] - 2.950*z_filtrado[1] +0.9752*z_filtrado[2];
			
			x_filtrado[2] = x_filtrado[1];
			x_filtrado[1] = x_filtrado[0];
			x_filtrado[0] = saida_atual[0];
			
			y_filtrado[2] = y_filtrado[1];
			y_filtrado[1] = y_filtrado[0];
			y_filtrado[0] = saida_atual[1];
						
			z_filtrado[2] = z_filtrado[1];
			z_filtrado[1] = z_filtrado[0];
			z_filtrado[0] = saida_atual[2];
			
			x_antigo[2] = x_antigo[1];
			x_antigo[1] = x_antigo[0];
			x_antigo[0] = xyz[0];
			
			y_antigo[2] = y_antigo[1];
			y_antigo[1] = y_antigo[0];
			y_antigo[0] = xyz[1];
						
			z_antigo[2] = z_antigo[1];
			z_antigo[1] = z_antigo[0];
			z_antigo[0] = xyz[2];
									
			x_antigo[2] = x_antigo[1];
			x_antigo[1] = x_antigo[0];
			x_antigo[0] = xyz[0];
			//printf("[%f]\t", (float)1/10000000);
			printf("[%7.2f %7.2f %7.2f]\n", saida_atual[0], saida_atual[1], saida_atual[2]);
			*/
			
		}
	}
	/*else if(res == ERR_DISABLED)
	{
		printf("ERR_DISABLED\n");
	}
	else if(res == ERR_SPEED)
	{
		printf("ERR_SPEED\n");	
	}
	else if(res == ERR_BUSY)
	{
		printf("ERR_BUSY\n");	
	}
	else 
	{
		printf("Uat?\n");
	}
	while(1)
	{
		//printf("Hello World!\n");
	}*/
	CI2C1_Deinit(deviceData.handle);
	LEDR_Off();
	LEDG_Off();
	LEDB_Off();
}
