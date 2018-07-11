#include "IntUtils.h"
#include "GeneralUtils.h"

/*
	Util to convert an int with padded zeros to buffer in Base64
*/
char* convertIntToBase64(int value, char buf[MAX_BASE4_INT_LEN + 1], int padZeros)
{
	int base = OUTPUT_BASE,i = 0;
	value = value & MAX_BASE4_VALUE;

	while (value) {
		buf[i++] = (value % base) + BASE4_ZERO_VALUE;
		value = value / base;
	}
	if (padZeros) {
		for (; i < MAX_BASE4_INT_LEN; )
		{
			buf[i++] = BASE4_ZERO_VALUE;
		}
	}
	buf[i] = BACKSLACH_ZERO;
	reverseString(buf);
	return buf;
}
