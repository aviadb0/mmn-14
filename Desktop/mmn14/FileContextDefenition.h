#ifndef FILE_CONTEXT_DEFENITION_H
#define FILE_CONTEXT_DEFENITION_H

#include <stdlib.h>
#include <inttypes.h>
#include "constants.h"
#include "SmallComponentDefenitions.h"
#include "Extern.h"
#include "OperationData.h"

/*
	the main struct in the program, its represent the asm file content
	it contains: Extern table, Operation table, Symbol table, Entry table and the InstructionCounter etc..
*/
typedef struct FileContext {
	ExternData *externData;
	OpData *operationData;
	SymbolData *symbolData;
	EntryData *entryData;
	int instructionCounter;
	int errorCounter;
	int* data_table;
	int data_count; 
	int data_capacity;
} FileContext;

/*
	initialize the File Context resources
*/
void initContextResources(FileContext* fileContext);

/*
	free the File Context resources
*/
void freeFileContextResources(FileContext* fileContext);

/*
	add op to Operation table
*/
void addOperationTable(FileContext *fileContext, Op operation);

/*
	add symbol to symbol table
*/
void addSymbolTable(FileContext *fileContext, Symbol symbol);


extern const Op operationsTable[];
extern const int operationsCounter;

#endif
