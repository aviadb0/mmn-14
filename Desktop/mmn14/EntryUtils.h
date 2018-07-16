#ifndef ENTRY_UTILS_H
#define ENTRY_UTILS_H

#include "FileContextDefenition.h"
#include "GeneralUtils.h"


/*
	this method validates that all declared .entry actually exists in the code
*/
int validateThatEntryExistsInFileContext(FileContext* FileContext);
/*
	this method calculate the relative location of the symbol in the filecontext
*/
int calcRelativeLocation(Symbol *symbol, FileContext *fileContext);

#endif
