#include "PanelSerializer.h"

PanelSerializer::PanelSerializer(PanelDriverInterface& panelDriver, DisplayCharacterMap& characterMap){
	this->panelDriver = &panelDriver;
	this->characterMap = &characterMap;
	this->lastColumn  = 7;
	this->lastRow  = 0;
}

char PanelSerializer::getChar(void){
	return 0;
}

void PanelSerializer::sendChar(char data){
	if(data == '\f'){
		panelDriver->clearAll();
		this->lastColumn = 7;
		this->lastRow = 0;
	}else if(data == '\n'){
		this->lastColumn = 7;
		this->lastRow = 1;
	}else{
		panelDriver->setData(lastRow,lastColumn,characterMap->map(data));
		this->lastColumn--;
		if(lastColumn < 0){
			this->lastColumn = 7;
			if(lastRow < 1) this->lastRow++;
		}
	}
}
