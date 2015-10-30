#include "timer_15.h"
#include "stm32f30x.h"                  // Device header

EventListener* Timer15::eventListener; 

Timer15::Timer15(int period_ms, EventListener& eventListener){
	this->eventListener = &eventListener; 
	this->hardware_init(period_ms);
}

void Timer15::postEvent(void){
	eventListener->onEvent();
}

void Timer15::hardware_init(int period_us){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15,ENABLE);
	TIM_TimeBaseInitTypeDef myTimer;
	TIM_TimeBaseStructInit(&myTimer);
	myTimer.TIM_CounterMode=TIM_CounterMode_Down;
	myTimer.TIM_Prescaler=(64-1);//CountFreq=(64MHz/Prescaler+1)=1MHz
	myTimer.TIM_ClockDivision=TIM_CKD_DIV1;
	myTimer.TIM_Period=period_us;
	TIM_TimeBaseInit(TIM15,&myTimer);
	
	TIM_InternalClockConfig(TIM15);
	
	TIM_ITConfig(TIM15,TIM_IT_Update,ENABLE);
	NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn);
	TIM_Cmd(TIM15,ENABLE);
}

extern "C"
{
	void TIM1_BRK_TIM15_IRQHandler(void){
		TIM_ClearITPendingBit(TIM15,TIM_IT_Update);
		Timer15::postEvent();
	}
}
