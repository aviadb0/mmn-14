#include <string.h>

#include "FileContextUtils.h"

/*
	Add operation to the file context
*/
void addOperation(FileContext* FileContext, Op operation)
{
	addOperationTable(FileContext, operation);
}

/*
	get symbol form the file context based on search the label
*/
Symbol* getSymbolFromFileContext(char label[MAXIMUM_LABEL_LENGTH + 1], FileContext * FileContext)
{
	int i;
	for (i = 0; i < FileContext->symbolData->symbolCount;) {
		Symbol* sym = &FileContext->symbolData->symbolsTable[i++];
		if (!strcmp(label, sym->name)) {
			return sym;
		}
	}

	return NULL;
}

/*
	check if entry exists in FileContext
*/
int isEntryExistInFileContext(char label[MAXIMUM_LABEL_LENGTH + 1], FileContext * FileContext)
{
	int i;
	for (i = 0; i < FileContext->entryData->entryCounter; ) {
		if (!strcmp(FileContext->entryData->entryTable[i++].label, label)) {
			return TRUE;
		}
	}

	return FALSE;
}

/*
	Checks if extern or label are exists in FileContext
*/
int isLabelOrExternExistInFileContext(char label[MAXIMUM_LABEL_LENGTH + 1], FileContext* FileContext)
{
	if (isLabelExistInFileContext(label, FileContext) || isExternExistsInFileContext(label, FileContext)) {
		return TRUE;
	}

	return FALSE;
}

/*
	Add symbol to the file context
*/
void addSymbol(FileContext* FileContext, char label[MAXIMUM_LABEL_LENGTH + 1], SymbolType type)
{
	Symbol symbol;
	strcpy(symbol.name, label);
	if (type == data) {
		symbol.location = FileContext->data_count;
	}
	else if (type == code) {
		symbol.location = FileContext->instructionCounter;
	}

	symbol.type = type;
	addSymbolTable(FileContext, symbol);
}

/*
	this method add an Extern to the Extern Table
*/
void addExternTable(FileContext *fileContext, Extern Extern) {
	if (fileContext->externData->externCount == fileContext->externData->externCapacity) {
		fileContext->externData->externCapacity = fileContext->externData->externCapacity * 2;
			fileContext->externData->externTable = realloc(fileContext->externData->externTable, sizeof(*(fileContext->externData->externTable)) * fileContext->externData->externCapacity);
	}

	fileContext->externData->externTable[fileContext->externData->externCount++] = Extern;
}

/*
	Add extern to the file context
*/
void addExtern(FileContext* FileContext, char label[MAXIMUM_LABEL_LENGTH + 1])
{
	int *location;
	Extern extr;
	strcpy(extr.label, label);
	if ((location = malloc(INITIAL_CAPACITY * sizeof(int)))) {
		extr.locations = location;
	}
	extr.locations_capacity = INITIAL_CAPACITY;
	extr.locations_count = 0;

	addExternTable(FileContext, extr);
}

/*
	check if label exists in FileContext
*/
int isLabelExistInFileContext(char label[MAXIMUM_LABEL_LENGTH + 1], FileContext * FileContext)
{
	int i;
	for (i = 0; i < FileContext->symbolData->symbolCount; ) {
		if (!strcmp(label, FileContext->symbolData->symbolsTable[i++].name)) {
			return TRUE;
		}
	}

	return FALSE;
}

/*
	this method add an Entry to the Entry Table
*/
void addEntryTable(FileContext *fileContext, Entry entry) {
	if (fileContext->entryData->entryCounter == fileContext->entryData->entryCapacity) {
		fileContext->entryData->entryCapacity = fileContext->entryData->entryCapacity * 2;
		fileContext->entryData->entryTable = realloc(fileContext->entryData->entryTable, sizeof(*(fileContext->entryData->entryTable)) * fileContext->entryData->entryCapacity);
	}

	fileContext->entryData->entryTable[fileContext->entryData->entryCounter++] = entry;
}

/*
	Add entry to the file context
*/
void addEntry(FileContext * FileContext, char label[MAXIMUM_LABEL_LENGTH + 1])
{
	Entry entry;
	strcpy(entry.label, label);

	addEntryTable(FileContext, entry);
}

/*
	check if only exists in FileContext
*/
int isExternExistsInFileContext(char label[MAXIMUM_LABEL_LENGTH + 1], FileContext * FileContext)
{
	int i;
	for (i = 0; i < FileContext->externData->externCount; ) {
		if (!strcmp(label, FileContext->externData->externTable[i++].label)) {
			return TRUE;
		}
	}

	return FALSE;
}


