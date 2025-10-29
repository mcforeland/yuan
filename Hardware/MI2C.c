#include "stm32f10x.h"                  // Device header
#include "MI2C.h"
#include "Delay.h"
//IO初始化
void MI2C_Init(void)
{
		/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOB的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);						//将PB10和PB11引脚初始化为开漏输出
	
	GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);
}

//写数据线
void MI2C_W_SDA(uint8_t BitV)
{
		GPIO_WriteBit(GPIO_SDA_PORT,GPIO_SDA_PIN,BitV);
	  Delay_us(10);
}
//写时钟线
void MI2C_W_SCK(uint8_t BitV)
{
	  GPIO_WriteBit(GPIO_SCK_PORT,GPIO_SCK_PIN,BitV);
	  Delay_us(10);
}

//读数据线
uint8_t MI2C_R_SDA(void)
{
		uint8_t Data;
	  Data = GPIO_ReadInputDataBit(GPIO_SDA_PORT,GPIO_SDA_PIN);
	  Delay_us(10);
	  return Data;
}
//起始位
void App_I2C_Start(void)
{
	  MI2C_W_SDA(1);
		MI2C_W_SCK(1);
	  MI2C_W_SDA(0);
		MI2C_W_SCK(0);
}
//停止位
void App_I2C_Stop(void)
{
	
	  MI2C_W_SDA(0);
		MI2C_W_SCK(1);
		MI2C_W_SDA(1);
}

//写1Byte数据
void App_I2C_WriteByte(uint8_t Data)
{
	 for(int i=0;i<8;i++)
	 {
			MI2C_W_SDA((0x80>>i)&Data);
		  MI2C_W_SCK(1);
		  MI2C_W_SCK(0);
	 }
}

//read 1Byte Data
uint8_t App_I2C_ReadByte(void)
{
		uint8_t Byte = 0x00;
	  MI2C_W_SDA(1);
	  for(int i=0;i<8;i++)
		{
			 MI2C_W_SCK(1);
			 if(MI2C_R_SDA()==1)
			 {
					Byte = Byte|(0x80>>i);
			 }
			 MI2C_W_SCK(0);
		}
		return Byte;
}

//发送应答
void App_I2C_SendAck(uint8_t BitAck)
{
		MI2C_W_SDA(BitAck);
	  MI2C_W_SCK(1);
	  MI2C_W_SCK(0);
}

//接收应答
uint8_t App_I2C_ReceiveAck(void)
{
	  uint8_t Data=0;
		MI2C_W_SDA(1);//主机释放总线
	  MI2C_W_SCK(1);
		Data = MI2C_R_SDA();
	  MI2C_W_SCK(0);
	  return Data;
}