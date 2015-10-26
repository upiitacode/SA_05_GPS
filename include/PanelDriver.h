#ifndef _PANELDRIVER_H
#define _PANELDRIVER_H

#include <stdint.h>
#include "DataShifter.h"

class PanelDriverInterface{
	public:
		~PanelDriverInterface(){};
		virtual uint16_t getData(int row, int column) = 0;
		virtual void setData(int row, int column, uint16_t data) = 0;
		virtual void clearAll(void) = 0;
};

class PanelDriver : public PanelDriverInterface{
	public:
		static const int ROWS = 2;
		static const int COLUMNS = 8;

	private:
		DataShifter* dataShifter;
		uint16_t data[ROWS][COLUMNS];
		int currentColumn;
	public:
		PanelDriver(DataShifter& dataShifter);
		virtual uint16_t getData(int row, int column);
		virtual void setData(int row, int column, uint16_t data);
		void tick(void);
		virtual void clearAll(void);
};

#endif //_PANELDRIVER_H
