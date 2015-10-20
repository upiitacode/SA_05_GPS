#include "retarget_stm32f3.h"
#include "stm32f30x.h"
#include "timer_15.h"
#include "Clock.h"

void led_init(void);

class MainApp : public EventListener{
	private:
		Clock* clock;
	public:
		MainApp(Clock& clock){
			led_init();
			this->clock = &clock;
		}
		virtual void onEvent(void){
			GPIOB->ODR = (~GPIOB->ODR) & (0x01 << 13);
			clock->tick();
		}
};

void delay_ms(int delay_time){
	for(int i = 0; i < delay_time; i++){
	}
}
int main(){
	//System configuration
	Clock clock;
	Time myTime(15,4,5,0);
	clock.setTime(myTime);
	MainApp app(clock);
	Timer15 timer15(1000, app);
	Serial_stream* serial = new SerialUSART2(9600);

	//User application
	serial->printf("Hello World\n");
	while(1){
		clock.getTime(myTime);
		serial->printf("Hora = %02d:%02d:%02d\n", myTime.hours, myTime.minutes, myTime.seconds);
		delay_ms(0xFFFF);
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
