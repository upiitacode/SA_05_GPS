#ifndef _PANELDRIVER_H
#define _PANELDRIVER_H

#include <stdint.h>
#include "DataShifter.h"

class PanelDriver{
	public:
		static const int ROWS = 2;
		static const int COLUMNS = 8;

	private:
		DataShifter* dataShifter;
		uint16_t data[ROWS][COLUMNS];
		int currentColumn;

		void clearAllData(void);

	public:
		PanelDriver(DataShifter& dataShifter);
		uint16_t getData(int row, int column);
		void setData(int row, int column, uint16_t data);
		void tick(void);
};

#endif //_PANELDRIVER_H
