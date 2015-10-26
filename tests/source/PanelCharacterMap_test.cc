#include "gmock/gmock.h"
using ::testing::Eq;

#include "PanelCharacterMap.h"

TEST(ASCIICharacterMapTest, ThatUppercaseAreMappedToUppercase){
	ASCIICharacterMap ascii;
	EXPECT_THAT(ascii.map('A'), Eq(DISP_14_A));
	EXPECT_THAT(ascii.map('Z'), Eq(DISP_14_Z));
}

TEST(ASCIICharacterMapTest, ThatLowercaseAreMappedToUppercase){
	ASCIICharacterMap ascii;
	EXPECT_THAT(ascii.map('a'), Eq(DISP_14_A));
	EXPECT_THAT(ascii.map('z'), Eq(DISP_14_Z));
}

TEST(ASCIICharacterMapTest, ThatDigitsAreMapedToDigits){
	ASCIICharacterMap ascii;
	EXPECT_THAT(ascii.map('0'), Eq(DISP_14_0));
	EXPECT_THAT(ascii.map('9'), Eq(DISP_14_9));
}

TEST(ASCIICharacterMapTest, ThatSpacesAreMapedToEmpty){
	ASCIICharacterMap ascii;
	EXPECT_THAT(ascii.map(' '), Eq(DISP_14_SPACE));
}
