#include "gmock/gmock.h"
using ::testing::Eq;
using ::testing::NiceMock;
using ::testing::ReturnArg;
using ::testing::Return;
using ::testing::_;

#include "PanelCharacterMap.h"
#include "PanelDriver.h"

class MockCharacterMap : public DisplayCharacterMap{
	public:
		MOCK_METHOD1(map, uint16_t(char c));
};

class MockPanelDriver : public PanelDriverInterface{
	public:
		MOCK_METHOD2(getData, uint16_t(int,int));
		MOCK_METHOD3(setData, void(int,int,uint16_t));
		MOCK_METHOD0(clearAll, void(void));
};

class PanelSerializer{
	private:
		PanelDriverInterface* panelDriver;
		DisplayCharacterMap* characterMap;
		int lastColumn;
		int lastRow;
	public:
		PanelSerializer(PanelDriverInterface& panelDriver, DisplayCharacterMap& characterMap){
			this->panelDriver = &panelDriver;
			this->characterMap = &characterMap;
			this->lastColumn  = 7;
			this->lastRow  = 0;
		}
		virtual char getChar(void){
			return 0;
		}
		virtual void sendChar(char data){
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
};

TEST(PanelSerializerTest, ThatGetCharReturnsZero){
	MockPanelDriver panelDriver;
	NiceMock<MockCharacterMap> characterMap;
	PanelSerializer panelSerial(panelDriver, characterMap);
	EXPECT_THAT(panelSerial.getChar(), Eq(0));
}

TEST(PanelSerializerTest, FirstDataIsSendEndOfRow){
	const char sentChar = 'x';
	MockPanelDriver panelDriver;
	NiceMock<MockCharacterMap> characterMap;
	PanelSerializer panelSerial(panelDriver, characterMap);

	ON_CALL(characterMap,map(_))
		.WillByDefault(ReturnArg<0>());
	EXPECT_CALL(panelDriver, setData(0,7,sentChar));
	panelSerial.sendChar(sentChar);
	EXPECT_CALL(panelDriver, setData(0,6,sentChar));
	panelSerial.sendChar(sentChar);
}

TEST(PanelSerializerTest, LasDataOfRowIsSentStart){
	const char sentCharOther = 'x';
	const char sentCharLast = 'u';
	NiceMock<MockPanelDriver> panelDriver;
	NiceMock<MockCharacterMap> characterMap;
	PanelSerializer panelSerial(panelDriver, characterMap);

	ON_CALL(characterMap,map(_))
		.WillByDefault(ReturnArg<0>());

	for(int i = 0; i < 7; i++){
		panelSerial.sendChar(sentCharOther);
	}

	EXPECT_CALL(panelDriver, setData(0,0,sentCharLast));
	panelSerial.sendChar(sentCharLast);
}

TEST(PanelSerializerTest, AfterLastOfFirstRowIsSentLastOfSencondRowIsSent){
	const char sentCharOther = 'x';
	const char sentCharLast = 'u';
	NiceMock<MockPanelDriver> panelDriver;
	NiceMock<MockCharacterMap> characterMap;
	PanelSerializer panelSerial(panelDriver, characterMap);

	ON_CALL(characterMap,map(_))
		.WillByDefault(ReturnArg<0>());

	for(int i = 0; i < 8; i++){
		panelSerial.sendChar(sentCharOther);
	}

	EXPECT_CALL(panelDriver, setData(1,7,sentCharLast));
	panelSerial.sendChar(sentCharLast);
}

TEST(PanelSerializerTest, WhenFileIsSentCursorIsReset){
	const char sentCharOther = 'x';
	const char sentCharLast = 'u';
	const char newLine = '\f';
	NiceMock<MockPanelDriver> panelDriver;
	NiceMock<MockCharacterMap> characterMap;
	PanelSerializer panelSerial(panelDriver, characterMap);

	ON_CALL(characterMap,map(_))
		.WillByDefault(ReturnArg<0>());

	for(int i = 0; i < 4; i++){
		panelSerial.sendChar(sentCharOther);
	}

	EXPECT_CALL(panelDriver, clearAll());
	panelSerial.sendChar(newLine);

	EXPECT_CALL(panelDriver, setData(0,7,sentCharLast));
	panelSerial.sendChar(sentCharLast);
}

TEST(PanelSerializerTest, WhenNewLineCursorGoesToNextRow){
	const char sentCharOther = 'x';
	const char sentCharLast = 'u';
	const char newLine = '\n';
	NiceMock<MockPanelDriver> panelDriver;
	NiceMock<MockCharacterMap> characterMap;
	PanelSerializer panelSerial(panelDriver, characterMap);

	ON_CALL(characterMap,map(_))
		.WillByDefault(ReturnArg<0>());

	for(int i = 0; i < 4; i++){
		panelSerial.sendChar(sentCharOther);
	}

	panelSerial.sendChar(newLine);

	EXPECT_CALL(panelDriver, setData(1,7,sentCharLast));
	panelSerial.sendChar(sentCharLast);
}


TEST(PanelSerializerTest, DataIsMapped){
	const char sentCharOther = 'x';
	const char sentCharLast = 'u';
	const char newLine = '\n';
	NiceMock<MockPanelDriver> panelDriver;
	NiceMock<MockCharacterMap> characterMap;
	PanelSerializer panelSerial(panelDriver, characterMap);

	ON_CALL(characterMap,map(_))
		.WillByDefault(Return('0'));

	for(int i = 0; i < 4; i++){
		panelSerial.sendChar(sentCharOther);
	}

	panelSerial.sendChar(newLine);

	EXPECT_CALL(panelDriver, setData(1,7,'0'));
	panelSerial.sendChar(sentCharLast);
}
