#include "IntUtils.h"

#include "GeneralUtils.h"



/*

	Util to convert an int with padded zeros to buffer in Base 2

*/

char* convertIntToBase2(int value, char buf[MAX_BASE2_INT_LEN + 1], int padZeros)

{

	int base = OUTPUT_BASE,i = 0;

	value = value & MAX_BASE2_VALUE;



	while (value) {

		buf[i++] = (value % base) + BASE2_ZERO_VALUE;

		value = value / base;

	}

	if (padZeros) {

		for (; i < MAX_BASE2_INT_LEN; )

		{

			buf[i++] = BASE2_ZERO_VALUE;

		}

	}

	buf[i] = BACKSLACH_ZERO;

	reverseString(buf);

	return buf;

}
