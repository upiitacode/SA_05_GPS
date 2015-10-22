#ifndef	_DATASHIFTER_H
#define	_DATASHIFTER_H

#include <stdint.h>

class DataShifter{
	public:
		virtual ~DataShifter(){};
		virtual void shiftColumnData(int column,
				uint16_t row0Data,
				uint16_t row1Data) = 0;
};

#endif // _DATASHIFTER_H
