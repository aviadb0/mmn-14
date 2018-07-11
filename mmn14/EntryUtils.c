#include <string.h>

#include "EntryUtils.h"
#include "LogUtils.h"

/*
	this method calculate the relative location of the symbol in the filecontext
*/
int calcRelativeLocation(Symbol *symbol, FileContext *fileContext) {
	int temp;

	if (symbol->type == code) {
		temp = symbol->location;
	}
	else {
		temp = fileContext->instructionCounter + symbol->location;
	}

	return temp + BASE_MEM_ADDR;
}

/*
	this method validates that all declared .entry actually exists in the code
*/
int validateThatEntryExistsInFileContext(FileContext* FileContext)
{
	int errorExists = FALSE;
	int i, j;
	for (i = 0; i < FileContext->entryData->entryCounter; i++) {
		int foundError = FALSE;
		for (j = 0; j < FileContext->symbolData->symbolCount; j++) {
			Symbol* symbol = &FileContext->symbolData->symbolsTable[j];
			if (!strcmp(FileContext->entryData->entryTable[i].label, symbol->name))
			{
				FileContext->entryData->entryTable[i].lastLocation = calcRelativeLocation(symbol, FileContext);
				foundError = TRUE;
				break;
			}
		}
		if (!foundError)
		{
			writeErrorOrWarningToLogWithNoLineNumber(2, "there is an entry '%s' that dont have a matching label in FileContext", FileContext->entryData->entryTable[i].label);
			errorExists = TRUE;
		}
	}

	return errorExists;
}
