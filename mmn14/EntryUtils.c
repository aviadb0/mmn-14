#include <string.h>

#include "EntryUtils.h"
#include "LogUtils.h"

/*
	this method calculate the relative location of the symbol in the filecontext.
 	return the memory location.
*/
int calcRelativeLocation(Symbol *symbol, FileContext *fileContext) {
	int temp;

	if (symbol->type == code) {  /* symbol is code - symbol contains the IC location */
		temp = symbol->location;
	}
	else { /* symbol is data - symbol contains the DC location (that starts after the IC location) */
		temp = fileContext->instructionCounter + symbol->location;
	}

	return temp + BASE_MEM_ADDR; /* the location in the memory */
}

/*
	this method validates that all declared .entry actually exists in the code.
 	returns TRUE if error occurred.
*/
int validateThatEntryExistsInFileContext(FileContext* FileContext)
{
	int errorExists = FALSE;
	int i, j;
	for (i = 0; i < FileContext->entryData->entryCounter; i++) {
		int foundEntry = FALSE;
		for (j = 0; j < FileContext->symbolData->symbolCount; j++) { /* check all the symbol table */
			Symbol* symbol = &FileContext->symbolData->symbolsTable[j];
			if (!strcmp(FileContext->entryData->entryTable[i].label, symbol->name))
			{  /* found match */
				FileContext->entryData->entryTable[i].lastLocation = calcRelativeLocation(symbol, FileContext); /* insert the location of the declare */
				foundEntry = TRUE;
				break;
			}
		}
		if (!foundEntry)  /* no match */
		{
			writeErrorOrWarningToLogWithNoLineNumber(2, "there is an entry '%s' that dont have a matching label in FileContext", FileContext->entryData->entryTable[i].label);
			errorExists = TRUE;
		}
	}

	return errorExists;
}
