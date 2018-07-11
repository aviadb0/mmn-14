#ifndef EXTERN_H
#define EXTERN_H
#include "constants.h"

/*
	Extern struct, represent an extern line from the file, we save a few things to represent an extern from the asm file:
	locations and the label itself
*/
typedef struct Extern {
	int locations_count;
	char label[MAXIMUM_LABEL_LENGTH + 1];
	int locations_capacity;
	int* locations;
} Extern;

/*
	ExternData represent the whole externs in the asm file, after we parsed them into Extern struct
*/
typedef struct ExternData {
	Extern* externTable;
	int externCount;
	int externCapacity;
} ExternData;

#endif