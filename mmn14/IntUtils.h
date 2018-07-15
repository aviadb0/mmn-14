#ifndef INT_UTILS_H
#define INT_UTILS_H

#include "constants.h"

/*
	Util to convert an int with padded zeros to buffer in Base 2
*/
char* convertIntToBase2(int value, char buf[MAX_BASE2_INT_LEN + 1], int pad_zeroes);

#endif
