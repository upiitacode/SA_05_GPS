#include "SerialShifter.h"
#include "delay.h"
#include "stm32f30x.h"                  // Device header

#define SHIFT_DELAY 2
#define SR_CLK GPIO_Pin_10
#define SR_DATA GPIO_Pin_14
#define SR_LOAD GPIO_Pin_15

void _SerialShifter_Shiftdata(const char * pData, int nBytes);
void _SerialShifter_pinWrite(uint16_t pin,char value);

void SerialShifter_init(void){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	GPIO_InitTypeDef myGPIO;
	GPIO_StructInit(&myGPIO);
	myGPIO.GPIO_Pin=GPIO_Pin_15|GPIO_Pin_14|GPIO_Pin_10;
	myGPIO.GPIO_Mode=GPIO_Mode_OUT;
	myGPIO.GPIO_OType=GPIO_OType_OD;
	myGPIO.GPIO_PuPd=GPIO_PuPd_NOPULL;
	myGPIO.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&myGPIO);
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_SET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_14,Bit_SET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_15,Bit_SET);
}

void SerialShifter_shiftToPanel(char column,const uint16_t row0_char,const uint16_t row1_char){
	char dataToShift[] = {0x00,0x00,0x00,0x00,0x00,0xFF};
	dataToShift[4]=column;
	dataToShift[0]=((row1_char >> 8)&(0xFF));
	dataToShift[1]=((row1_char >> 0)&(0xFF));
	dataToShift[2]=((row0_char >> 8)&(0xFF));
	dataToShift[3]=((row0_char >> 0)&(0xFF));
	_SerialShifter_Shiftdata(dataToShift,6);
}

void _SerialShifter_Shiftdata(const char * pData, int nBytes){
	char byteData;
	for(int j = 0; j < nBytes; j++){
		byteData = pData[j];
		for(int i = 7; i >= 0; i--){
			_SerialShifter_pinWrite(SR_CLK, 0);
			delay_ms(SHIFT_DELAY);
			_SerialShifter_pinWrite(SR_DATA,((byteData>>i) & 0x1));
			delay_ms(SHIFT_DELAY);
			_SerialShifter_pinWrite(SR_CLK, 1);
			delay_ms(SHIFT_DELAY);
		}
	}
	_SerialShifter_pinWrite(SR_LOAD, 0);
	delay_ms(SHIFT_DELAY);
	_SerialShifter_pinWrite(SR_LOAD, 1);
	delay_ms(SHIFT_DELAY);
}



void _SerialShifter_pinWrite(uint16_t pin,char value){
	if((pin  == SR_CLK) || (pin  == SR_DATA) || (pin  == SR_LOAD)){
		BitAction pin_state = (value)?Bit_SET:Bit_RESET; 
		GPIO_WriteBit(GPIOB,pin,pin_state);
	}
}
