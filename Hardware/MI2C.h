#ifndef _MI2C_H
#define _MI2C_H

#include "stm32f10x.h"                  // Device header
#define GPIO_SDA_PORT  GPIOB
#define GPIO_SDA_PIN   GPIO_Pin_11
#define GPIO_SCK_PORT  GPIOB
#define GPIO_SCK_PIN   GPIO_Pin_10


void MI2C_Init(void);
void MI2C_W_SDA(uint8_t BitV);
void MI2C_W_SCK(uint8_t BitV);
uint8_t MI2C_R_SDA(void);
void App_I2C_Start(void);
void App_I2C_Stop(void);
void App_I2C_WriteByte(uint8_t Data);
uint8_t App_I2C_ReadByte(void);
void App_I2C_SendAck(uint8_t BitAck);
uint8_t App_I2C_ReceiveAck(void);

#endif