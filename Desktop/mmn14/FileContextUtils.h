#ifndef FILE_CONTEXT_UTILS_H
#define FILE_CONTEXT_UTILS_H

#include "FileContextDefenition.h"

/*
	Add operation to the file context
*/
void addOperation(FileContext* FileContext, Op operation);

/*
	Add entry to the file context
*/
void addEntry(FileContext* FileContext, char label[MAXIMUM_LABEL_LENGTH + 1]);


/*
check if only exists in FileContext
*/
int isExternExistsInFileContext(char label[MAXIMUM_LABEL_LENGTH + 1], FileContext* FileContext);

/*
	get symbol form the file context based on search the label
*/
Symbol* getSymbolFromFileContext(char label[MAXIMUM_LABEL_LENGTH + 1], FileContext* FileContext);

/*
check if entry exists in FileContext
*/
int isEntryExistInFileContext(char label[MAXIMUM_LABEL_LENGTH + 1], FileContext* FileContext);

/*
	Add extern to the file context
*/
void addExtern(FileContext* FileContext, char label[MAXIMUM_LABEL_LENGTH + 1]);

/*
	Add symbol to the file context
*/
void addSymbol(FileContext* FileContext, char label[MAXIMUM_LABEL_LENGTH + 1], SymbolType type);


/*
	Checks if extern or label are exists in FileContext
*/
int isLabelOrExternExistInFileContext(char label[MAXIMUM_LABEL_LENGTH + 1], FileContext* FileContext);

/*
	check if label exists in FileContext
*/
int isLabelExistInFileContext(char label[MAXIMUM_LABEL_LENGTH + 1], FileContext* FileContext);

/*
	this method add an Entry to the Entry Table
*/
void addEntryTable(FileContext *fileContext, Entry entry);

/*
	this method add an Extern to the Extern Table
*/
void addExternTable(FileContext *fileContext, Extern Extern);

#endif