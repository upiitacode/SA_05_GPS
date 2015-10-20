Timer -> Clock
	OverFlowEvent


Class Clock : public EventHanler{
	public:
		onEvent(void){
			this->tick();
		}
};

Class PeriodicClock : public EventHandler, public Clock{
	pubilc:

}

Class Timer(){
	public:
		virtual void setTimeBase(int uS);
		virtual void start(void);
		virtual void stop(void);
		void registerEventHandler(EventHandler& newEventHandler);
		void unregisterEventHandler(EventHandler& newEventHandler);
	protected:
		void publishEvents(void);
		boolean isRunning;
}

void main(){
	Time initialTime(12,0,0,0);
	TimedClock clock(initialTime);

	GPIO_3Pin displayPins;
	TimedDisplayDriver displayDriver(displayPins,1000);

	Timer2 timer2;
	timer2.setTimeBase(1000);
	timer2.registerEvntHandler(displayDriver);
	timer2.registerEvntHandler(clock);
	timer2.start();
}

void App(){
}

TimedDisplay
showDate();
showTime();

EventTriggeredClock

class AlarmClock :public EventTriggeredClock{
	public:
		addAlarm(Alarm newAlarm);

}

Class EventListener{
	public:
		virtual void onEvent(void) = 0;
};

class DisplayDriver : public EventListener{
	public:
		PIOPin* PinCLK;
		GPIOPin* PinDATA;
		GPIOPin* PinLOAD;
		uint16_t displayData[2][20];
		int nextToShift;
		int size;
	public:
	DisplayDriver(Timer timer, GPIO PinCLK, GPIO PinDATA, GPIO_PinLOAD){
		timer.addEventListener(this);
	}

	void setDisplayData(int row,int column, uint16_t data){
		displayData[row][column] = data;
	}

	@overrides
	void onEnvent(void){
		shiftColumn(nextToShift, displayData[0][nextToShift], displayData[1][nextToShift]);
		nextToShift = (nextToShift+1)%size;
	}

	void shiftColumn(int column, uint16_t row0Data, uint16_t rowData);
		//some code
	}
};

class ASCII_Display : public serial_output{
	// lots of defines
	private:
		int cursor_colum;
		int cursor_row;
	public:
	public:
		void sendChar(char c){
			cursor_row++;
			if(c == '\n'){
				cursor_row++;
			}
		}

		void clearDisplay(void){
		}
};
