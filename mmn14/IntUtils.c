#include "IntUtils.h"

#include "GeneralUtils.h"

/*
	This function converts the text to weird 2 base.
*/
char* convertIntToBase2(int value, char buf[MAX_BASE2_INT_LEN + 1])

{
	int base = OUTPUT_BASE,i = 0;
	value = value & MAX_BASE2_VALUE; /* to zero all the bits after 14 bits */
	while (value) {
		buf[i++] = (value % base) + BASE2_ZERO_VALUE;
		value = value / base;
	}
	for (;i < MAX_BASE2_INT_LEN;)
	{
			buf[i++] = BASE2_ZERO_VALUE;
	}
	buf[i] = BACKSLACH_ZERO;
	reverseString(buf); /*reverse to correct the order */
	return buf;
}
