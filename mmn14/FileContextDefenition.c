#include "FileContextDefenition.h"

const Op operationsTable[] = {
	{ MOV_OPERATION, 2,  IMMEDIATE_MEMORY_REGISTER, MEMORY_REGISTER, 	   0 },
	{ CMP_OPERATION, 2,  IMMEDIATE_MEMORY_REGISTER, IMMEDIATE_MEMORY_REGISTER, 1 },
	{ ADD_OPERATION, 2,  IMMEDIATE_MEMORY_REGISTER, MEMORY_REGISTER,	   2 },
	{ SUB_OPERATION, 2,  IMMEDIATE_MEMORY_REGISTER, MEMORY_REGISTER, 	   3 },
	{ NOT_OPERATION, 1,  ADDRESSING_NONE,           MEMORY_REGISTER, 	   4 },
	{ CLR_OPERATION, 1,  ADDRESSING_NONE,           MEMORY_REGISTER, 	   5 },
	{ LEA_OPERATION, 2,  memory,                    MEMORY_REGISTER, 	   6 },
	{ INC_OPERATION, 1,  ADDRESSING_NONE,           MEMORY_REGISTER, 	   7 },
	{ DEC_OPERATION, 1,  ADDRESSING_NONE, 		MEMORY_REGISTER, 	   8 },
	{ JMP_OPERATION, 1,  ADDRESSING_NONE, 		MEMORY_JUMP_REGISTER, 	   9 },
	{ BNE_OPERATION, 1,  ADDRESSING_NONE, 		MEMORY_JUMP_REGISTER, 	  10 },
	{ RED_OPERATION, 1,  ADDRESSING_NONE, 		MEMORY_REGISTER, 	  11 },
	{ PRN_OPERATION, 1,  ADDRESSING_NONE,  		IMMEDIATE_MEMORY_REGISTER,12 },
	{ JSR_OPERATION, 1,  ADDRESSING_NONE, 		MEMORY_JUMP_REGISTER, 	  13 },
	{ RTS_OPERATION, 0,  ADDRESSING_NONE, 		ADDRESSING_NONE, 	  14 },
	{ STOP_OPERATION,0,  ADDRESSING_NONE, 		ADDRESSING_NONE, 	  15 }
};

const int operationsCounter = sizeof(operationsTable) / sizeof(operationsTable[0]);

/*
	add op to Operation table
*/
void addOperationTable(FileContext *fileContext, Op operation) {
	if (fileContext->operationData->operationsCounter == fileContext->operationData->op_capacity) {
		fileContext->operationData->op_capacity = fileContext->operationData->op_capacity * 2;		/*exceed the current capacity - increse the capacity*/																		 \
			fileContext->operationData->operationsTable = realloc(fileContext->operationData->operationsTable, sizeof(*(fileContext->operationData->operationsTable)) * fileContext->operationData->op_capacity);
	}

	fileContext->operationData->operationsTable[fileContext->operationData->operationsCounter++] = operation; /*insert the operation*/
}

/*
	free the File Context resources
*/
void freeFileContextResources(FileContext* fileContext) {
	free(fileContext->operationData->operationsTable);
	free(fileContext->data_table);
	free(fileContext->symbolData->symbolsTable);
	free(fileContext->symbolData);
	free(fileContext->externData->externTable);
	free(fileContext->externData);
	free(fileContext->entryData->entryTable);
	free(fileContext->entryData);
}

/*
	initialize the File Context resources
*/
void initContextResources(FileContext* fileContext) {
	fileContext->operationData = malloc((sizeof(int*) * 2) + (sizeof(Op*) * 1));

	fileContext->operationData->operationsCounter = 0;
	fileContext->operationData->op_capacity = INITIAL_CAPACITY;
	fileContext->operationData->operationsTable = malloc(sizeof(*(fileContext->operationData->operationsTable)) * INITIAL_CAPACITY);

	fileContext->data_count = 0;
	fileContext->data_capacity = INITIAL_CAPACITY;
	fileContext->data_table = malloc(sizeof(*(fileContext->data_table)) * INITIAL_CAPACITY);


	fileContext->symbolData = malloc((sizeof(int*) * 2) + (sizeof(Symbol*) * 1));
	fileContext->symbolData->symbolCount = 0;
	fileContext->symbolData->symbolCapacity = INITIAL_CAPACITY;
	fileContext->symbolData->symbolsTable = malloc(sizeof(*(fileContext->symbolData->symbolsTable)) * INITIAL_CAPACITY);

	fileContext->externData = malloc((sizeof(int*) * 2) + (sizeof(Extern*) * 1));
	fileContext->externData->externCount = 0;
	fileContext->externData->externCapacity = INITIAL_CAPACITY;
	fileContext->externData->externTable = malloc(sizeof(*(fileContext->externData->externTable)) * INITIAL_CAPACITY);

	fileContext->entryData = malloc((sizeof(int*) * 2) + (sizeof(Entry*) * 1));
	fileContext->entryData->entryTable = malloc(sizeof(*(fileContext->entryData->entryTable)) * INITIAL_CAPACITY);
	fileContext->entryData->entryCounter = 0;
	fileContext->entryData->entryCapacity = INITIAL_CAPACITY;
}



/*
	add symbol to symbol table
*/
void addSymbolTable(FileContext *fileContext, Symbol symbol) {
	if (fileContext->symbolData->symbolCount == fileContext->symbolData->symbolCapacity) {
		fileContext->symbolData->symbolCapacity = fileContext->symbolData->symbolCapacity * 2;																						 \
			fileContext->symbolData->symbolsTable = realloc(fileContext->symbolData->symbolsTable, sizeof(*(fileContext->symbolData->symbolsTable)) * fileContext->symbolData->symbolCapacity);
	}

	fileContext->symbolData->symbolsTable[fileContext->symbolData->symbolCount++] = symbol;
	
}
