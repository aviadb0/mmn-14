#ifndef SYMBOL_DEFENITION_H
#define SYMBOL_DEFENITION_H

#include "constants.h"

typedef enum SymbolType {
	code,
	data
} SymbolType;

/*
	represent a Symbol in the system, contatins the symbol name and its location and type
*/
typedef struct Symbol {
	char name[MAXIMUM_LABEL_LENGTH + 1];
	int location;
	SymbolType type;
} Symbol;

/*
	this is a syhmbol table in the system, we save all the symbol while parsing the asm file
*/
typedef struct SymbolData {
	Symbol* symbolsTable;
	int symbolCount;
	int symbolCapacity;
} SymbolData;

#endif