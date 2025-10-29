#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "mpu6050.h"
#include "MI2C.h"
#include "Serial.h"

#include "JX90614.h"
#include "math.h"
#include "vl53l0x.h"
int32_t Temp;
int32_t realT;
uint8_t data_sda;
uint8_t data_sck;

uint32_t millis(void);

uint16_t L=0;
uint16_t R=0;
// current uptime for 1kHz systick timer. will rollover after 49 days. hopefully we won't care.
volatile uint32_t sysTickUptime = 0;
uint32_t millis(void)
{
    return sysTickUptime;
}
//888
void vl53l0x_gpio_Init(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启GPIOA的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOB的时钟
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
}

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Serial_Init();
	MI2C_Init();
	vl53l0x_gpio_Init();
	GPIO_WriteBit(GPIOB,GPIO_Pin_14,Bit_SET);//使能第一个vl53l0x
	GPIO_WriteBit(GPIOA,GPIO_Pin_7,Bit_RESET);//
	Delay_ms(200);
	//OLED_ShowString(2,2,"vl53l0x_1=");
	if(!VL53L0X_Init(VL53L0X_DEFAULT_I2C_ADDR1,true))
	{
		printf("Failed to detect and initialize sensor!\n");
//		while(1)
//		{

//		}
	}	

	VL53L0X_setAddress(VL53L0X_DEFAULT_I2C_ADDR1,VL53L0X_DEFAULT_I2C_ADDR2);

	GPIO_WriteBit(GPIOA,GPIO_Pin_7,Bit_SET);
	Delay_ms(200);

	if(!VL53L0X_Init(VL53L0X_DEFAULT_I2C_ADDR1,true))
	{
		printf("Failed to detect and initialize sensor!\n");
//		while(1)
//		{

//		}
	}	

	while (1)
	{
		L = VL53L0X_readRangeSingleMillimeters(VL53L0X_DEFAULT_I2C_ADDR2);
		printf("vl53l0x_1=%d\r\n", L);  
		OLED_ShowString(2,2,"vl53l0x_1=");
		OLED_ShowNum(2,12,L,4);
			
		R= VL53L0X_readRangeSingleMillimeters(VL53L0X_DEFAULT_I2C_ADDR1);
		printf("vl53l0x_2=%d\r\n", R);
		OLED_ShowString(5,2,"vl53l0x_2=");
		OLED_ShowNum(5,12,R,4);
		Delay_ms(500);
	}
}
