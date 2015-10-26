#ifndef _PANELSHIFTERB_H
#define _PANELSHIFTERB_H

#include "DataShifter.h"

class PanelShifterB : public DataShifter{
	public:
		PanelShifterB(void);
		virtual void shiftColumnData(int column,
				uint16_t row0Data,
				uint16_t row1Data);
};

#endif// _PANELSHIFTERB_H
