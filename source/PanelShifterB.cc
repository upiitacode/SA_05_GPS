#include "PanelShifterB.h"
#include "SerialShifter.h"

PanelShifterB::PanelShifterB(void){
	SerialShifter_init();	
}

void PanelShifterB::shiftColumnData(int column, uint16_t row0Data, uint16_t row1Data){
	SerialShifter_shiftToPanel(column, row0Data, row1Data);
}
