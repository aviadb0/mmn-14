#ifndef SMALL_COMPONENT_DEFENITION_H
#define SMALL_COMPONENT_DEFENITION_H

#include <stdlib.h>
#include <inttypes.h>
#include "constants.h"
#include "Entry.h"
#include "Symbol.h"
#include "Extern.h"
#include "OperationData.h"

/*
	Line struct is a small but unique component in the system, it holds the line number (from the file) and the line representation
	in a string (before we parse this line)
*/
typedef struct Line {
	char* str;
	int lineNum;
} Line;

#endif