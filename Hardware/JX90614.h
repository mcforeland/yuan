#ifndef _JX90614_H
#define _JX90614_H
#include "stm32f10x.h"                  // Device header
#include "MI2C.h"
#include "Serial.h"

void JX90164_WriteReg(uint8_t Address,uint8_t data);
uint8_t JX90164_ReadReg(uint8_t Address);
void JX90164_Init(void);
void JX90164_Get_T_Data(int32_t* Temp);

#endif 