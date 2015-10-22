#ifndef _GPIOPIN_H
#define _GPIOPIN_H
class GPIOPin{
	public:
		virtual ~GPIOPin(){}
		virtual int read(void) = 0;
		virtual void write(int) = 0;
};
#endif// _GPIOPIN_H
