#include "retarget_stm32f3.h"                  // Device header
#include "stm32f30x.h"                  // Device header
#include "timer_15.h"

void led_init(void);

class MainApp : public EventListener{
	public:
		MainApp(void){
			led_init();
		}
		virtual void onEvent(void){
			GPIOB->ODR = (~GPIOB->ODR) & (0x01 << 13);
		}
};

int main(){
	//System configuration
	MainApp app;
	Timer15 timer15(500, app);
	Serial_stream* serial = new SerialUSART2(9600);

	//User application
	serial->printf("Hello World\n");
	while(1){
	}
}

void led_init(void){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	GPIO_InitTypeDef myGPIO;
	GPIO_StructInit(&myGPIO);
	myGPIO.GPIO_Pin=GPIO_Pin_13;
	myGPIO.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_Init(GPIOB,&myGPIO);
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
}
