#include "gmock/gmock.h"
#include "PanelDriver.h"
#include <vector>

using ::testing::Eq;
using ::testing::NiceMock;
using ::testing::Each;
using ::testing::ElementsAreArray;
using ::std::vector;

class MockDataShifter : public DataShifter{
	public:
		MOCK_METHOD3(shiftColumnData, void(int column,
				uint16_t row0Data,
				uint16_t row1Data));

};


void copyAllData(PanelDriver& panelDriver, vector<uint16_t>& dataRow0, vector<uint16_t>& dataRow1){
	for(int j = 0; j < PanelDriver::COLUMNS; j++){
		dataRow0[j] = panelDriver.getData(0,j);
		dataRow1[j] = panelDriver.getData(1,j);
	}
}

TEST(PanelDriver, ThatScreenIsBlankedOnCreation){
	MockDataShifter dataShifter;
	EXPECT_CALL(dataShifter,shiftColumnData(0,0,0));
	PanelDriver panelDriver(dataShifter);
}

TEST(PanelDriver, DataBufferIsClearedOnCreation){
	NiceMock<MockDataShifter> dataShifter;
	PanelDriver panelDriver(dataShifter);
	vector<uint16_t> dataRow0(PanelDriver::COLUMNS,-1);
	vector<uint16_t> dataRow1(PanelDriver::COLUMNS,-1);

	copyAllData(panelDriver, dataRow0, dataRow1);
	EXPECT_THAT(dataRow0,Each(0));
	EXPECT_THAT(dataRow1,Each(0));
}

TEST(PanelDriver, DataCanBeSavedIntoBuffer){
	NiceMock<MockDataShifter> dataShifter;
	PanelDriver panelDriver(dataShifter);
	vector<uint16_t> dataRow0(PanelDriver::COLUMNS,-1);
	vector<uint16_t> dataRow1(PanelDriver::COLUMNS,-1);

	const int row0 = 0;
	const int row1 = 1;
	const int column0 = 5;
	const int column1 = 7;
	const uint16_t data0 = 546;
	const uint16_t data1 = 34;

	panelDriver.setData(row0,column0,data0);
	panelDriver.setData(row1,column1,data1);

	EXPECT_THAT(panelDriver.getData(row0,column0), Eq(data0));
	EXPECT_THAT(panelDriver.getData(row1,column1), Eq(data1));
}

TEST(PanelDriver, WhenFirstTickIsGeneratedTheFirstColumnIsShifted){
	NiceMock<MockDataShifter> dataShifter;
	PanelDriver panelDriver(dataShifter);

	const uint16_t data0 = 546;
	const uint16_t data1 = 856;
	panelDriver.setData(0,0,data0);
	panelDriver.setData(1,0,data1);

	EXPECT_CALL(dataShifter, shiftColumnData(0,data0,data1));
	panelDriver.tick();
}

TEST(PanelDriver, AfterFourTicksThe4thColumnIsShifted){
	NiceMock<MockDataShifter> dataShifter;
	PanelDriver panelDriver(dataShifter);

	const uint16_t data0 = 546;
	const uint16_t data1 = 856;
	const uint16_t column = 3;

	panelDriver.setData(0, column, data0);
	panelDriver.setData(1, column, data1);
	panelDriver.tick();
	panelDriver.tick();
	panelDriver.tick();

	EXPECT_CALL(dataShifter, shiftColumnData(column,data0,data1));
	panelDriver.tick();
}

TEST(PanelDriver, AfterLastTickTheFirstColumnIsShifted){
	NiceMock<MockDataShifter> dataShifter;
	PanelDriver panelDriver(dataShifter);

	const uint16_t data0 = 546;
	const uint16_t data1 = 856;
	const uint16_t column = 0;

	panelDriver.setData(0, column, data0);
	panelDriver.setData(1, column, data1);
	for(int i = 0; i < (PanelDriver::COLUMNS); i++){
		panelDriver.tick();
	}

	EXPECT_CALL(dataShifter, shiftColumnData(column,data0,data1));
	panelDriver.tick();
}
