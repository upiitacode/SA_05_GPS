#ifndef _TIMER_15_H
#define _TIMER_15_H

#include "eventListener.h"

class Timer15{
	private:
		static EventListener*  eventListener;
	public:
		Timer15(int period_ms,EventListener& eventListener);
		void hardware_init(int period_ms);
		static void postEvent(void);
};

#endif // _TIMER_15_H
