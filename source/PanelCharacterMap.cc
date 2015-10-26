#include "PanelCharacterMap.h"

const uint16_t ASCIICharacterMap::Alpha[26] = {DISP_14_A, DISP_14_B, DISP_14_C, DISP_14_D, DISP_14_E, DISP_14_F, DISP_14_G, DISP_14_H, DISP_14_I, DISP_14_J, DISP_14_K, DISP_14_L, DISP_14_M, DISP_14_N, DISP_14_O, DISP_14_P, DISP_14_Q, DISP_14_R, DISP_14_S, DISP_14_T, DISP_14_U, DISP_14_V, DISP_14_W, DISP_14_X, DISP_14_Y, DISP_14_Z};

const uint16_t ASCIICharacterMap::Digit[10] = {DISP_14_0, DISP_14_1, DISP_14_2, DISP_14_3, DISP_14_4, DISP_14_5, DISP_14_6, DISP_14_7, DISP_14_8, DISP_14_9};

uint16_t ASCIICharacterMap::map(char c){
	if(isupper(c)){
		return Alpha[c-'A'];
	}else if(islower(c)){
		return Alpha[c-'a'];
	}else if(isdigit(c)){
		return Digit[c-'0'];
	}else if(isblank(c)){
		return DISP_14_SPACE;
	}
	return DISP_14_SPACE;
}
