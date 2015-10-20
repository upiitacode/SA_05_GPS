#include "retarget_stm32f3.h"
#include "stm32f30x.h"
#include "timer_15.h"
#include "Clock.h"
#include "timedclock.h"

void delay_ms(int delay_time){
	for(int i = 0; i < delay_time; i++){
	}
}

int main(){
	//System configuration
	Time myTime(15,4,5,0);
	TimedClock clock(myTime);
	Timer15 timer15(1000, clock);
	Serial_stream* serial = new SerialUSART2(9600);

	//User application
	serial->printf("Hello World\n");
	while(1){
		clock.getTime(myTime);
		serial->printf("Hora = %02d:%02d:%02d\n", myTime.hours, myTime.minutes, myTime.seconds);
		delay_ms(0x8FFFF);
	}
}
