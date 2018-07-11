#ifndef ENTRY_H
#define ENTRY_H
#include "constants.h"

/*
	Entry strut, it wrappes label array (represent label in the system)
*/
typedef struct Entry {
	int lastLocation;
	char label[MAXIMUM_LABEL_LENGTH + 1];
} Entry;

/*
	EntryData wrappes an Entry struct and encapsulate an entry counter and an entry capacity
	so we build this struct after parsing a line from the file and analyze the data on it.
*/
typedef struct EntryData {
	Entry* entryTable;
	int entryCounter;
	int entryCapacity;
} EntryData;

#endif