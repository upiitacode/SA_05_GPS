#include "timedclock.h"

TimedClock::TimedClock(Time& time){
	this->setTime(time);
}

void TimedClock::onEvent(void){
	this->tick();
}
