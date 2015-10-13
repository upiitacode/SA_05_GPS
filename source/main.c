#include "stm32f30x.h"                  // Device header
#include "serial_stdio.h"
#include "retarget_stm32f3.h"
#include <string.h>
/*Led PB13, Button PC13*/

void delay_ms(int delay_time);
void led_init(void);
void shiftRegister_pinWrite(uint16_t pin,char value);
void shiftRegister_data(const char * pData, int nBytes);

Serial_t USART2_Serial={USART2_getChar,USART2_sendChar};

#define SR_CLK GPIO_Pin_10
#define SR_DATA GPIO_Pin_14
#define SR_LOAD GPIO_Pin_15

#define DISP_14_SEG_A (0x1 << 2)
#define DISP_14_SEG_B (0x1 << 1)
#define DISP_14_SEG_C (0x1 << 15)
#define DISP_14_SEG_D (0x1 << 14)
#define DISP_14_SEG_E (0x1 << 9)
#define DISP_14_SEG_F (0x1 << 7)
#define DISP_14_SEG_G (0x1 << 5)
#define DISP_14_SEG_H (0x1 << 4)
#define DISP_14_SEG_J (0x1 << 13)
#define DISP_14_SEG_K (0x1 << 12)
#define DISP_14_SEG_L (0x1 << 11)
#define DISP_14_SEG_M (0x1 << 10)
#define DISP_14_SEG_N (0x1 << 3)
#define DISP_14_SEG_P (0x1 << 6)

#define DISP_14_0 (DISP_14_SEG_A | DISP_14_SEG_B | DISP_14_SEG_C | DISP_14_SEG_D | DISP_14_SEG_E | DISP_14_SEG_F)
#define DISP_14_1 (DISP_14_SEG_B | DISP_14_SEG_C)
#define DISP_14_2 (DISP_14_SEG_A | DISP_14_SEG_B | DISP_14_SEG_J | DISP_14_SEG_N | DISP_14_SEG_E | DISP_14_SEG_D)
#define DISP_14_3 (DISP_14_SEG_A | DISP_14_SEG_B | DISP_14_SEG_J | DISP_14_SEG_N | DISP_14_SEG_C | DISP_14_SEG_D)
#define DISP_14_4 (DISP_14_SEG_F | DISP_14_SEG_B | DISP_14_SEG_J | DISP_14_SEG_N | DISP_14_SEG_C)
#define DISP_14_5 (DISP_14_SEG_A | DISP_14_SEG_F | DISP_14_SEG_J | DISP_14_SEG_N | DISP_14_SEG_C | DISP_14_SEG_D)
#define DISP_14_5 (DISP_14_SEG_A | DISP_14_SEG_F | DISP_14_SEG_J | DISP_14_SEG_N | DISP_14_SEG_C | DISP_14_SEG_D)
#define DISP_14_6 (DISP_14_SEG_A | DISP_14_SEG_F | DISP_14_SEG_J | DISP_14_SEG_N | DISP_14_SEG_C | DISP_14_SEG_D | DISP_14_SEG_E)
#define DISP_14_7 (DISP_14_SEG_A | DISP_14_SEG_B | DISP_14_SEG_C)
#define DISP_14_8 (DISP_14_SEG_A | DISP_14_SEG_B | DISP_14_SEG_C | DISP_14_SEG_D | DISP_14_SEG_E | DISP_14_SEG_F | DISP_14_SEG_J | DISP_14_SEG_N)
#define DISP_14_9 (DISP_14_SEG_A | DISP_14_SEG_B | DISP_14_SEG_C | DISP_14_SEG_D | DISP_14_SEG_F | DISP_14_SEG_J | DISP_14_SEG_N)

#define DISP_14_A (DISP_14_SEG_A | DISP_14_SEG_B | DISP_14_SEG_C | DISP_14_SEG_E | DISP_14_SEG_F | DISP_14_SEG_J | DISP_14_SEG_N)
#define DISP_14_B (DISP_14_SEG_A | DISP_14_SEG_B | DISP_14_SEG_C | DISP_14_SEG_D | DISP_14_SEG_G | DISP_14_SEG_L | DISP_14_SEG_J)
#define DISP_14_C (DISP_14_SEG_A | DISP_14_SEG_D | DISP_14_SEG_E | DISP_14_SEG_F)
#define DISP_14_D (DISP_14_SEG_A | DISP_14_SEG_B | DISP_14_SEG_C | DISP_14_SEG_D | DISP_14_SEG_G | DISP_14_SEG_L)
#define DISP_14_E (DISP_14_SEG_A | DISP_14_SEG_E | DISP_14_SEG_F | DISP_14_SEG_D | DISP_14_SEG_J | DISP_14_SEG_N)
#define DISP_14_F (DISP_14_SEG_A | DISP_14_SEG_E | DISP_14_SEG_F | DISP_14_SEG_J | DISP_14_SEG_N)
#define DISP_14_G (DISP_14_SEG_A | DISP_14_SEG_C | DISP_14_SEG_E | DISP_14_SEG_F | DISP_14_SEG_D | DISP_14_SEG_J)
#define DISP_14_H (DISP_14_SEG_B | DISP_14_SEG_C | DISP_14_SEG_E | DISP_14_SEG_F | DISP_14_SEG_J | DISP_14_SEG_N)
#define DISP_14_I (DISP_14_SEG_A | DISP_14_SEG_D | DISP_14_SEG_G | DISP_14_SEG_L)
#define DISP_14_J (DISP_14_SEG_B | DISP_14_SEG_C | DISP_14_SEG_D | DISP_14_SEG_E)
#define DISP_14_K (DISP_14_SEG_F | DISP_14_SEG_E | DISP_14_SEG_N | DISP_14_SEG_H | DISP_14_SEG_K)
#define DISP_14_L (DISP_14_SEG_F | DISP_14_SEG_E | DISP_14_SEG_D)
#define DISP_14_M (DISP_14_SEG_E | DISP_14_SEG_F | DISP_14_SEG_P | DISP_14_SEG_H | DISP_14_SEG_B | DISP_14_SEG_C)
#define DISP_14_N (DISP_14_SEG_E | DISP_14_SEG_F | DISP_14_SEG_P | DISP_14_SEG_K | DISP_14_SEG_B | DISP_14_SEG_C)
#define DISP_14_O (DISP_14_SEG_A | DISP_14_SEG_B | DISP_14_SEG_C | DISP_14_SEG_D | DISP_14_SEG_E | DISP_14_SEG_F)
#define DISP_14_P (DISP_14_SEG_A | DISP_14_SEG_B | DISP_14_SEG_E | DISP_14_SEG_F | DISP_14_SEG_J | DISP_14_SEG_N)
#define DISP_14_Q (DISP_14_SEG_A | DISP_14_SEG_B | DISP_14_SEG_C | DISP_14_SEG_D | DISP_14_SEG_E | DISP_14_SEG_F | DISP_14_SEG_K)
#define DISP_14_R (DISP_14_SEG_A | DISP_14_SEG_B | DISP_14_SEG_E | DISP_14_SEG_F | DISP_14_SEG_J | DISP_14_SEG_N | DISP_14_SEG_K)
#define DISP_14_S (DISP_14_SEG_A | DISP_14_SEG_P | DISP_14_SEG_J | DISP_14_SEG_C | DISP_14_SEG_D)
#define DISP_14_T (DISP_14_SEG_A | DISP_14_SEG_G | DISP_14_SEG_L)
#define DISP_14_U (DISP_14_SEG_B | DISP_14_SEG_C | DISP_14_SEG_D | DISP_14_SEG_E | DISP_14_SEG_F)
#define DISP_14_V (DISP_14_SEG_F | DISP_14_SEG_E | DISP_14_SEG_M | DISP_14_SEG_H)
#define DISP_14_W (DISP_14_SEG_E | DISP_14_SEG_F | DISP_14_SEG_M | DISP_14_SEG_K | DISP_14_SEG_B | DISP_14_SEG_C)
#define DISP_14_X (DISP_14_SEG_M | DISP_14_SEG_K | DISP_14_SEG_P | DISP_14_SEG_H)
#define DISP_14_Y (DISP_14_SEG_P | DISP_14_SEG_H | DISP_14_SEG_L)
#define DISP_14_Z (DISP_14_SEG_A | DISP_14_SEG_H | DISP_14_SEG_M | DISP_14_SEG_D)

#define DISP_14_SPACE (0x0000)
#define DISP_14_MINUS (0x0000)
#define DISP_14_PLUS (0x0000)

const uint16_t DISP_CharMap[] = {DISP_14_A, DISP_14_B, DISP_14_C, DISP_14_D, DISP_14_E, DISP_14_F, DISP_14_G, DISP_14_H, DISP_14_I, DISP_14_J, DISP_14_K, DISP_14_L, DISP_14_M, DISP_14_N, DISP_14_O, DISP_14_P, DISP_14_Q, DISP_14_R, DISP_14_S, DISP_14_T, DISP_14_U, DISP_14_V, DISP_14_W, DISP_14_X, DISP_14_Y, DISP_14_Z};

	void panel_disp_char(char column,const uint16_t row0_char,const uint16_t row1_char){
	char dataToShift[] = {0x00,0x00,0x00,0x00,0x00,0xFF};
	dataToShift[4]=column;
	dataToShift[0]=((row1_char >> 8)&(0xFF));
	dataToShift[1]=((row1_char >> 0)&(0xFF));
	dataToShift[2]=((row0_char >> 8)&(0xFF));
	dataToShift[3]=((row0_char >> 0)&(0xFF));
	shiftRegister_data(dataToShift,6);
}

char myData[] = {0xFF,0xFF,0xFF,0xFF,0x00,0xFF};
char myBuffer[80];  
int main(){
	USART2_init(9600);
	led_init();
	serial_printf(USART2_Serial,"\nSystem ready\n");
	while(1){
		for(int i = 0; i< 26; i++){
			panel_disp_char(3,DISP_CharMap[i],DISP_14_SPACE);
			serial_gets(USART2_Serial,myBuffer,80);
		}
	}
}

#define SHIFT_DELAY 2

void shiftRegister_data(const char * pData, int nBytes){
	char byteData;
	for(int j = 0; j < nBytes; j++){
		byteData = pData[j];
		for(int i = 7; i >= 0; i--){
			shiftRegister_pinWrite(SR_CLK, 0);
			delay_ms(SHIFT_DELAY);
			shiftRegister_pinWrite(SR_DATA,((byteData>>i) & 0x1));
			delay_ms(SHIFT_DELAY);
			shiftRegister_pinWrite(SR_CLK, 1);
			delay_ms(SHIFT_DELAY);
		}
	}
	shiftRegister_pinWrite(SR_LOAD, 0);
	delay_ms(SHIFT_DELAY);
	shiftRegister_pinWrite(SR_LOAD, 1);
	delay_ms(SHIFT_DELAY);
}



void shiftRegister_pinWrite(uint16_t pin,char value){
	if((pin  == SR_CLK) || (pin  == SR_DATA) || (pin  == SR_LOAD)){
		BitAction pin_state = (value)?Bit_SET:Bit_RESET; 
		GPIO_WriteBit(GPIOB,pin,pin_state);
	}
}

void led_init(void){
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

void delay_ms(int delay_time){
	for(int i = 0; i < 7340*delay_time; i++){
	}
}
