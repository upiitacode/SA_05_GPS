#ifndef _TIMEDCLOCK_H
#define _TIMEDCLOCK_H

#include "eventListener.h"
#include "Clock.h"
#include "timedclock.h"

class TimedClock : public EventListener, public Clock{
	public:
		TimedClock(Time& time);
		virtual void onEvent(void);
};

#endif // _TIMEDCLOCK_H 
