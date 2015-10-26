#include "serial_stream_stm32f3.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "stm32f30x.h"                  // Device header
#include "PanelShifterB.h"
#include "PanelDriver.h"

void tarea1(void const * arguments); //tarea 1
osThreadId  tarea1ID;	//identificador del hilo tarea 1
osThreadDef (tarea1,osPriorityNormal,1,0);// macro para definir tareas (aputandor de la funcion, prioridad,?,?)

void tarea2(void const * arguments); //tarea 2
osThreadId  tarea2ID;	//identificador del hilo  tarea 2
osThreadDef (tarea2,osPriorityNormal,1,0);// macro para definir tareas (aputandor de la funcion, prioridad,?,?)

void tarea1Init(void);//funcion que iniciliza la tarea1
void tarea2Init(void);//funcion que iniciliza la tarea1

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

PanelDriver* panelDriver;

int main(){
	//System configuration
	Serial_stream* serial = new SerialUSART2(9600);
	SystemCoreClockUpdate();
	serial->printf("Starting System\n");
	serial->printf("ProcessorSpeed: %dHz\n",(int)SystemCoreClock);

	PanelShifterB panel;
	panelDriver = new PanelDriver(panel);


	//User application
	serial->printf("Initializing kernel...");
	osKernelInitialize();
	serial->printf("done\n");
	serial->printf("Setting threads...");
	tarea1Init();
	tarea2Init();
	serial->printf("done\n");
	serial->printf("starting kernel...");
	osKernelStart();
	serial->printf("done\n");
	serial->printf("System ready, Runnig at thread \"main\"\n");

	for(int i = 0; i < 8; i++){
		panelDriver->setData(0,i,DISP_CharMap[i]);
		panelDriver->setData(1,i,DISP_CharMap[i+8]);
	}

	while(1){
		osDelay(100);
	}
}

void tarea1Init(void){
	tarea1ID= osThreadCreate(osThread(tarea1),NULL);
}

void tarea2Init(void){
	tarea2ID= osThreadCreate(osThread(tarea2),NULL);
}

void led_init(void){
	//Turn on the GPIOB peripherial
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	//Configure PB13  as push pull ouput an set the output to high
	GPIOB->MODER &=~(GPIO_MODER_MODER13);
	GPIOB->MODER |=GPIO_MODER_MODER13_0;//output
	GPIOB->ODR |= GPIO_ODR_13;
}

void tarea1(void const * arguments){
	led_init();
	while(1){
		GPIO_WriteBit(GPIOB,GPIO_Pin_13,Bit_SET);
		osDelay(500);
		GPIO_WriteBit(GPIOB,GPIO_Pin_13,Bit_RESET);
		osDelay(500);
	}
}

void tarea2(void const * arguments){
	while(1){
		panelDriver->tick();	
	}
}
