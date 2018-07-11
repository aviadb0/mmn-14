#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "LogUtils.h"

/*
	Write to the console if there is an error/warning
*/
void writeErrorOrWarningToLog(int isError, int line, char* errorParameters, ...)
{
	va_list parameters;
	if (isError) {
		fprintf(stderr, "line #%d error: ", line);
	}
	else if(!isError) {
		fprintf(stderr, "line #%d warning: ", line);
	}
	else {
		fprintf(stderr, "symbol error: ");
	}

	va_start(parameters, errorParameters);
	vfprintf(stderr, errorParameters, parameters);
	va_end(parameters);
	fputc(ENTER, stderr);
}

/*
	Write to the console if there is an error/warning when there is no line known
*/
void writeErrorOrWarningToLogWithNoLineNumber(int isError, char* errorParameters, ...) {
	va_list parameters;

	if (isError) {
		fprintf(stderr, "error: ");
	}
	else if (!isError) {
		fprintf(stderr, "warning: ");
	}
	else {
		fprintf(stderr, "symbol: ");
	}

	va_start(parameters, errorParameters);
	vfprintf(stderr, errorParameters, parameters);
	va_end(parameters);
	fputc(ENTER, stderr);
}
