#include "PanelDriver.h"

PanelDriver::PanelDriver(DataShifter& dataShifter){
	this->dataShifter = & dataShifter;
	dataShifter.shiftColumnData(0,0,0);
	clearAll();
	currentColumn = 0;
}

uint16_t PanelDriver::getData(int row, int column){
	return data[row][column];
}

void PanelDriver::setData(int row, int column, uint16_t data){
	this->data[row][column] = data;
}

void PanelDriver::tick(void){
	dataShifter->shiftColumnData(currentColumn,data[0][currentColumn],
			data[1][currentColumn]);
	currentColumn = (currentColumn + 1) % COLUMNS;
}

void PanelDriver::clearAll(void){
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLUMNS; j++){
			data[i][j] = 0;
		}
	}
}
