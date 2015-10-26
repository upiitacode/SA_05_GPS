#ifndef _SERIALSHIFTER_H
#define _SERIALSHIFTER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

void SerialShifter_init(void);
void SerialShifter_shiftToPanel(char column, const uint16_t row0_char, const uint16_t row1_char);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif// _SERIALSHIFTER_H
