#ifndef INT_UTILS_H
#define INT_UTILS_H

#include "constants.h"

/*
	Util to convert an int with padded zeros to buffer in Base64
*/
char* convertIntToBase64(int value, char buf[MAX_BASE4_INT_LEN + 1], int pad_zeroes);

#endif