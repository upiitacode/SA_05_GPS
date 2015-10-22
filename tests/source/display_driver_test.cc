#include "gmock/gmock.h"
#include <vector>

using ::testing::Eq;
using ::testing::NiceMock;
using ::testing::Each;
using ::testing::ElementsAreArray;
using ::std::vector;

class DataShifter{
	public:
		virtual ~DataShifter(){};
		virtual void shiftColumnData(int column,
				uint16_t row0Data,
				uint16_t row1Data) = 0;
};

class MockDataShifter : public DataShifter{
	public:
		MOCK_METHOD3(shiftColumnData, void(int column,
				uint16_t row0Data,
				uint16_t row1Data));
};

class DisplayDriver{
	public:
		static const int ROWS = 2;
		static const int COLUMNS = 8;

	private:
		DataShifter* dataShifter;
		uint16_t data[ROWS][COLUMNS];
		int currentColumn;

		void clearAllData(void);

	public:
		DisplayDriver(DataShifter& dataShifter);
		uint16_t getData(int row, int column);
		void setData(int row, int column, uint16_t data);
		void tick(void);
};


DisplayDriver::DisplayDriver(DataShifter& dataShifter){
	this->dataShifter = & dataShifter;
	dataShifter.shiftColumnData(0,0,0);
	clearAllData();
	currentColumn = 0;
}

uint16_t DisplayDriver::getData(int row, int column){
	return data[row][column];
}

void DisplayDriver::setData(int row, int column, uint16_t data){
	this->data[row][column] = data;
}

void DisplayDriver::tick(void){
	dataShifter->shiftColumnData(currentColumn,data[0][currentColumn],data[1][currentColumn]);
	currentColumn++;
}

void DisplayDriver::clearAllData(void){
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLUMNS; j++){
			data[i][j] = 0;
		}
	}
}

void copyAllData(DisplayDriver& displayDriver, vector<uint16_t>& dataRow0, vector<uint16_t>& dataRow1){
	for(int j = 0; j < DisplayDriver::COLUMNS; j++){
		dataRow0[j] = displayDriver.getData(0,j);
		dataRow1[j] = displayDriver.getData(1,j);
	}
}

TEST(DisplayDriverTest, ThatScreenIsBlankedOnCreation){
	MockDataShifter dataShifter;
	EXPECT_CALL(dataShifter,shiftColumnData(0,0,0));
	DisplayDriver displayDriver(dataShifter);
}

TEST(DisplayDriverTest, DataBufferIsClearedOnCreation){
	NiceMock<MockDataShifter> dataShifter;
	DisplayDriver displayDriver(dataShifter);
	vector<uint16_t> dataRow0(DisplayDriver::COLUMNS,-1);
	vector<uint16_t> dataRow1(DisplayDriver::COLUMNS,-1);

	copyAllData(displayDriver, dataRow0, dataRow1);
	EXPECT_THAT(dataRow0,Each(0));
	EXPECT_THAT(dataRow1,Each(0));
}

TEST(DisplayDriverTest, DataCanBeSavedIntoBuffer){
	NiceMock<MockDataShifter> dataShifter;
	DisplayDriver displayDriver(dataShifter);
	vector<uint16_t> dataRow0(DisplayDriver::COLUMNS,-1);
	vector<uint16_t> dataRow1(DisplayDriver::COLUMNS,-1);

	const int row0 = 0;
	const int row1 = 1;
	const int column0 = 5;
	const int column1 = 7;
	const uint16_t data0 = 546;
	const uint16_t data1 = 34;

	displayDriver.setData(row0,column0,data0);
	displayDriver.setData(row1,column1,data1);

	EXPECT_THAT(displayDriver.getData(row0,column0), Eq(data0));
	EXPECT_THAT(displayDriver.getData(row1,column1), Eq(data1));
}

TEST(DisplayDriverTest, WhenFirstTickIsGeneratedTheFirstColumnIsShifted){
	NiceMock<MockDataShifter> dataShifter;
	DisplayDriver displayDriver(dataShifter);

	const uint16_t data0 = 546;
	const uint16_t data1 = 856;
	displayDriver.setData(0,0,data0);
	displayDriver.setData(1,0,data1);

	EXPECT_CALL(dataShifter, shiftColumnData(0,data0,data1));
	displayDriver.tick();
}

TEST(DisplayDriverTest, AfterFourTicksThe4thColumnIsShifted){
	NiceMock<MockDataShifter> dataShifter;
	DisplayDriver displayDriver(dataShifter);

	const uint16_t data0 = 546;
	const uint16_t data1 = 856;
	const uint16_t column = 3;

	displayDriver.setData(0, column, data0);
	displayDriver.setData(1, column, data1);
	displayDriver.tick();
	displayDriver.tick();
	displayDriver.tick();

	EXPECT_CALL(dataShifter, shiftColumnData(column,data0,data1));
	displayDriver.tick();
}
