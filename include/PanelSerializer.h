#ifndef _PANELSERIALIZER_H
#define _PANELSERIALIZER_H

#include "PanelCharacterMap.h"
#include "PanelDriver.h"
#include "serial_stream.h"

class PanelSerializer : public Serial_stream{
	private:
		PanelDriverInterface* panelDriver;
		DisplayCharacterMap* characterMap;
		int lastColumn;
		int lastRow;
	public:
		PanelSerializer(PanelDriverInterface& panelDriver, DisplayCharacterMap& characterMap);
		virtual char getChar(void);
		virtual void sendChar(char data);
};

#endif// _PANELSERIALIZER_H
