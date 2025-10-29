#ifndef _VL53L0X_H_
#define _VL53L0X_H_

//#include "main.h"
#include <stdbool.h>
#include "stm32f10x.h"                  // Device header




#define VL53L0X_DEFAULT_I2C_ADDR1 0x29  ///< The fixed I2C addres
#define VL53L0X_DEFAULT_I2C_ADDR2 0x30  ///< The fixed I2C addres

#define SYSRANGE_START                              0x00

#define SYSTEM_THRESH_HIGH                          0x0C
#define SYSTEM_THRESH_LOW                           0x0E

#define SYSTEM_SEQUENCE_CONFIG                      0x01
#define SYSTEM_RANGE_CONFIG                         0x09
#define SYSTEM_INTERMEASUREMENT_PERIOD              0x04

#define SYSTEM_INTERRUPT_CONFIG_GPIO                0x0A

#define GPIO_HV_MUX_ACTIVE_HIGH                     0x84

#define SYSTEM_INTERRUPT_CLEAR                      0x0B

#define RESULT_INTERRUPT_STATUS                     0x13
#define RESULT_RANGE_STATUS                         0x14

#define RESULT_CORE_AMBIENT_WINDOW_EVENTS_RTN       0xBC
#define RESULT_CORE_RANGING_TOTAL_EVENTS_RTN        0xC0
#define RESULT_CORE_AMBIENT_WINDOW_EVENTS_REF       0xD0
#define RESULT_CORE_RANGING_TOTAL_EVENTS_REF        0xD4
#define RESULT_PEAK_SIGNAL_RATE_REF                 0xB6

#define ALGO_PART_TO_PART_RANGE_OFFSET_MM           0x28

#define I2C_SLAVE_DEVICE_ADDRESS                    0x8A

#define MSRC_CONFIG_CONTROL                         0x60

#define PRE_RANGE_CONFIG_MIN_SNR                    0x27
#define PRE_RANGE_CONFIG_VALID_PHASE_LOW            0x56
#define PRE_RANGE_CONFIG_VALID_PHASE_HIGH           0x57
#define PRE_RANGE_MIN_COUNT_RATE_RTN_LIMIT          0x64

#define FINAL_RANGE_CONFIG_MIN_SNR                  0x67
#define FINAL_RANGE_CONFIG_VALID_PHASE_LOW          0x47
#define FINAL_RANGE_CONFIG_VALID_PHASE_HIGH         0x48
#define FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT 0x44

#define PRE_RANGE_CONFIG_SIGMA_THRESH_HI            0x61
#define PRE_RANGE_CONFIG_SIGMA_THRESH_LO            0x62

#define PRE_RANGE_CONFIG_VCSEL_PERIOD               0x50
#define PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI          0x51
#define PRE_RANGE_CONFIG_TIMEOUT_MACROP_LO          0x52

#define SYSTEM_HISTOGRAM_BIN                        0x81
#define HISTOGRAM_CONFIG_INITIAL_PHASE_SELECT       0x33
#define HISTOGRAM_CONFIG_READOUT_CTRL               0x55

#define FINAL_RANGE_CONFIG_VCSEL_PERIOD             0x70
#define FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI        0x71
#define FINAL_RANGE_CONFIG_TIMEOUT_MACROP_LO        0x72
#define CROSSTALK_COMPENSATION_PEAK_RATE_MCPS       0x20

#define MSRC_CONFIG_TIMEOUT_MACROP                  0x46

#define SOFT_RESET_GO2_SOFT_RESET_N                 0xBF
#define IDENTIFICATION_MODEL_ID                     0xC0
#define IDENTIFICATION_REVISION_ID                  0xC2

#define OSC_CALIBRATE_VAL                           0xF8

#define GLOBAL_CONFIG_VCSEL_WIDTH                   0x32
#define GLOBAL_CONFIG_SPAD_ENABLES_REF_0            0xB0
#define GLOBAL_CONFIG_SPAD_ENABLES_REF_1            0xB1
#define GLOBAL_CONFIG_SPAD_ENABLES_REF_2            0xB2
#define GLOBAL_CONFIG_SPAD_ENABLES_REF_3            0xB3
#define GLOBAL_CONFIG_SPAD_ENABLES_REF_4            0xB4
#define GLOBAL_CONFIG_SPAD_ENABLES_REF_5            0xB5

#define GLOBAL_CONFIG_REF_EN_START_SELECT           0xB6
#define DYNAMIC_SPAD_NUM_REQUESTED_REF_SPAD         0x4E
#define DYNAMIC_SPAD_REF_EN_START_OFFSET            0x4F
#define POWER_MANAGEMENT_GO1_POWER_FORCE            0x80

#define VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV           0x89

#define ALGO_PHASECAL_LIM                           0x30
#define ALGO_PHASECAL_CONFIG_TIMEOUT                0x30




//д��1���ֽ�����
void VL53L0X_WriteByte(uint8_t add,uint8_t reg,uint8_t data);
//д��2���ֽ�����
void VL53L0X_WriteByte_16Bit(uint8_t add,uint8_t reg,uint16_t data);
//д��4���ֽ�����
void VL53L0X_WriteByte_32Bit(uint8_t add,uint8_t reg,uint32_t data);

//��ȡ1���ֽ�����
uint8_t VL53L0X_ReadByte(uint8_t add,uint8_t reg);
//��ȡ2���ֽ�����
uint16_t VL53L0X_ReadBytee_16Bit(uint8_t add,uint16_t reg);
//�Ӵ�������ָ���Ĵ�����ʼ����ȡ�����������ֽڣ�����ŵ������������С�
void VL53L0X_readMulti(uint8_t add,uint8_t reg,  uint8_t * dst, uint8_t count);
//�Ӹ�����������д�������������ֽڵ�����������ָ���ļĴ�����ʼ��
void VL53L0X_writeMulti(uint8_t add,uint8_t reg, uint8_t * src, uint8_t count);

//�޸��豸��ַ
void VL53L0X_setAddress(uint8_t add,uint8_t new_addr);
//��ʼ������
uint8_t VL53L0X_Init(uint8_t add,bool io_2v8);

//VL53L0Xʱ����У�Time-of-Flight��ToF�����������÷����źŵ���������
uint8_t setSignalRateLimit(uint8_t add,float limit_Mcps);

//�趨����������һ�β�������Ҫ��ʱ�䣬��Ϊ������ʱ��Ԥ�㡱��measurement timing budget����
//���Ԥ��ʱ�䱻ϸ�ֳɶ���Ӳ��裬ÿ���Ӳ��趼��Ҫһ����ʱ�䣬�ú�����Ŀ����ȷ�������Ӳ������ʱ�䲻�����趨��Ԥ�㡣
//�ϳ���ʱ��Ԥ�㣺���Եõ�����ȷ�Ĳ��������
bool VL53L0X_setMeasurementTimingBudget(uint8_t add,uint32_t budget_us);

//��ȡ��������ǰ���õĲ���ʱ��Ԥ�㣬��λ��΢�루us����
uint32_t VL53L0X_getMeasurementTimingBudget(uint8_t add);

//��VL53L0X Time-of-Flight (ToF) ���봫�����л�ȡVCSEL����ֱǻ�淢�伤���������������ڣ���λ��PCLKs��
//����һ�����ڲ����������ļ���Դ��
uint8_t VL53L0X_getVcselPulsePeriod(uint8_t add,uint8_t type);


//�����������ģʽ��
//���period_ms��0��δ��������ô��ʹ������back-to-backģʽ�������������ܿ���������в�������
//����ṩ��period_ms����ô��ʹ��������ʱģʽ������������ݸ����ļ�����ڣ����룩���в�����
void VL53L0X_startContinuous(uint8_t add,uint32_t period_ms);



//��VL53L0X ToF���봫�����л�ȡ����SPAD��������ѩ�������ܣ��Ĳο�������������Ϣ��
uint16_t VL53L0X_readRangeSingleMillimeters(uint8_t add);

//ͨ���봫������ͨ�Žӿڣ��ض��ض�ȡ��д�뵽ĳЩ�Ĵ���������ȡ�ο�SPAD����Ϣ��
bool VL53L0X_getSpadInfo(uint8_t add,uint8_t * count, bool * type_is_aperture);

//��VL53L0X ToF���봫�������ض��Ĵ����ж�ȡ��ֵ����ΪMCLKs����ʱ�����ڣ��еĳ�ʱ��
uint16_t VL53L0X_decodeTimeout(uint16_t reg_val);

//���볬ʱֵ�Թ��洢��VL53L0X�ļĴ����С�
uint32_t VL53L0X_timeoutMclksToMicroseconds(uint16_t timeout_period_mclks, uint8_t vcsel_period_pclks);


//��������Ӹ����ĳ�ʱֵ����MCLKsΪ��λ�������һ�����Դ洢�ڴ������Ĵ����е�16λֵ��
uint16_t VL53L0X_decodeTimeout(uint16_t reg_val);
//д��VL53L0X����������Ӧ�Ĵ��������ó�ʱ
uint16_t VL53L0X_encodeTimeout(uint32_t timeout_mclks);



//��һ����ʱֵ����ʱ�����ڣ�MCLKs��ת��Ϊ΢�룬ͬʱ���ǵ�һ��������VCSEL����ֱǻ���淢�伤���������ڣ���PCLKsΪ��λ����
uint32_t VL53L0X_timeoutMclksToMicroseconds(uint16_t timeout_period_mclks, uint8_t vcsel_period_pclks);

//��������Ӹ����ĳ�ʱֵ����΢��Ϊ��λ����VCSEL���ڣ���PCLKsΪ��λ���������ʱֵ��MCLKs��ʾ��
uint32_t VL53L0X_timeoutMicrosecondsToMclks(uint32_t timeout_period_us, uint8_t vcsel_period_pclks);

//�������ִ��һ�����εĲο�У׼����ͨ�����ڳ�ʼ����������ı�ĳЩ���ú���еġ�
//��ͨ�������� vhv_init_byte ����һ�����������ȴ�������ɣ�Ȼ������жϲ�ֹͣ������
bool VL53L0X_performSingleRefCalibration(uint8_t add,uint8_t vhv_init_byte);





//�ú������ص�������������������ģʽʱ�ľ���������Ժ���Ϊ��λ����
uint16_t VL53L0X_readRangeContinuousMillimeters(uint8_t add);
//ִ�е��β��������ز����ľ���ֵ���Ժ���Ϊ��λ����
uint16_t VL53L0X_readRangeSingleMillimeters(uint8_t add);










#endif // _TOFLIB_H

