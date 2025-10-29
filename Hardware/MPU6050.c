#include "stm32f10x.h"                  // Device header
#include "mpu6050.h"
#include "MI2C.h"
#include "mpu6050_reg.h"
#include "Serial.h"
#define MPU6050_ADDRESS  0xD0   //定义外设地址


//指定地址写
void MPU6050_WriteReg(uint8_t Address,uint8_t data)
{
		App_I2C_Start();
	  App_I2C_WriteByte(MPU6050_ADDRESS);
	  App_I2C_ReceiveAck();
	  App_I2C_WriteByte(Address);
	  App_I2C_ReceiveAck();
	  App_I2C_WriteByte(data);
	  App_I2C_ReceiveAck();
	  App_I2C_Stop();
}
//指定地址读
uint8_t MPU6050_ReadReg(uint8_t Address)
{
	  uint8_t data;
		App_I2C_Start();
	  App_I2C_WriteByte(MPU6050_ADDRESS);
	  App_I2C_ReceiveAck();
	  App_I2C_WriteByte(Address);
	  App_I2C_ReceiveAck();
	
	
	  App_I2C_Start();
	  App_I2C_WriteByte(MPU6050_ADDRESS | (0x01));
	  App_I2C_ReceiveAck();
	  data = App_I2C_ReadByte();
		App_I2C_SendAck(1);
	  App_I2C_Stop();
		
	  return data;
}

void MPU6050_Init(void)
{
		MI2C_Init();
		MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);
		MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
		MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);
		MPU6050_WriteReg(MPU6050_CONFIG, 0x06);
		MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
		MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
}
//获取设备ID
uint8_t MPU6050_GetID(void)
{
		return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}
//获取数据
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
											int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
		uint8_t DataH, DataL;
	  DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
		DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	  *AccX = (DataH<<8)|DataL;
	  
	  
		DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
		DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	  *AccY = (DataH<<8)|DataL;
	
		DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
		DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	  *AccZ = (DataH<<8)|DataL;
	
	  DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
		DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	  *GyroX = (DataH<<8)|DataL;
	
	  DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
		DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	  *GyroY = (DataH<<8)|DataL;
	
	  DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
		DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	  *GyroZ = (DataH<<8)|DataL;
		
//		Serial_Printf("%.3f %.3f %.3f\n",*AccX,*AccY,*AccZ);
//		Serial_Printf("%.3f %.3f %.3f\n",*GyroX,*GyroY,*GyroZ);
}
