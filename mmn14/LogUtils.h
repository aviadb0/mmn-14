#ifndef LOG_UTILS_H
#define LOG_UTILS_H

#include "constants.h"

/*
	Write to the console if there is an error/warning
*/
void writeErrorOrWarningToLog(int isError, int line, char* errorParameters, ...);

/*
	Write to the console if there is an error/warning when there is no line known
*/
void writeErrorOrWarningToLogWithNoLineNumber(int isError, char* errorParameters, ...);

#endif
