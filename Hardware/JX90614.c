#include "stm32f10x.h"                  // Device header
#include "MI2C.h"
#include "Serial.h"
#include "JX90614.h"
#include "JX90614_reg.h"
#include "math.h"
#define JX90164_ADDRESS 0x7F


void JX90164_WriteReg(uint8_t Address,uint8_t data)
{
		App_I2C_Start();
	  App_I2C_WriteByte(JX90164_ADDRESS<<1);
	  App_I2C_ReceiveAck();
	  App_I2C_WriteByte(Address);
	  App_I2C_ReceiveAck();
	  App_I2C_WriteByte(data);
	  App_I2C_ReceiveAck();
	  App_I2C_Stop();
}

uint8_t JX90164_ReadReg(uint8_t Address)
{
	  uint8_t data;
		App_I2C_Start();
	  App_I2C_WriteByte(JX90164_ADDRESS<<1);
	  App_I2C_ReceiveAck();
	  App_I2C_WriteByte(Address);
	  App_I2C_ReceiveAck();
	
	
	  App_I2C_Start();
	  App_I2C_WriteByte(JX90164_ADDRESS<<1 | (0x01));
	  App_I2C_ReceiveAck();
	  data = App_I2C_ReadByte();
		App_I2C_SendAck(1);
	  App_I2C_Stop();
		
	  return data;
}

void JX90164_Init(void)
{
	  MI2C_Init();
		JX90164_WriteReg(CMD,0x00);
	  JX90164_WriteReg(CMD,0x08);
	  //JX90164_WriteReg(CMD,0x00);
}


void JX90164_Get_T_Data(int32_t* Temp)
{
		uint8_t DataH,DataC,DataL;
	  uint8_t Flag = 0x00;
	  Flag = JX90164_ReadReg(Data_ready);
	 
	  DataH = JX90164_ReadReg(DATA1_MSB);
	  DataC = JX90164_ReadReg(DATA1_CSB);
	  DataL = JX90164_ReadReg(DATA1_LSB);
	  *Temp = (DataH<<16)|(DataC<<8)|(DataL);
}
