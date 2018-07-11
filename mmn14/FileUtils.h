#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <stdio.h>

#include "FileContextDefenition.h"
#include "constants.h"


/*
	opening the file from filePath
*/
FILE* openFile(char *file);

/*
	run assembly file by parsing it, compile it and validate it and then run it via sub methods of the system
*/
void runAsmFile(FILE *file, char *filePath);

/*
	get number of operatinos in line
*/
int getNumberOpsInLine(char* line);

/*
	output object file
*/
void outputObjectFile(FileContext* FileContext, char* file);

/*
	this method handle the case there is no error when running asm file by calcing the extern location
*/
int handleNoErrorWhenRunningAsmFileCase1(FileContext *fileContext);

/*
	this methid returns TRUE if the op is in memory type and label dont exist in fileContext
*/
int isOpMemoryAndLabelDontExist(Op *op, FileContext *fileContext);

/*
	is line exists
*/
int lineExists(char* lineContent, FILE *file);

/*
	init FileContext
*/
void initFileContext(FileContext* FileContext);

/*
	freeFileContextMemory
*/
void freeFileContextMemory(FileContext* FileContext);

/*
	this method updates the label locations of the file context
*/
void updateLabelLocations(FileContext* FileContext);

/*
	output extern file
*/
void outputExternFile(FileContext* FileContext, char* file);

/*
	output entry file
*/
void outputEntryFile(FileContext* FileContext, char* file);

/*
	this method handle the case there is no error when running asm file by calcing the extern location
*/
void handleNoErrorWhenRunningAsmFileCase2(FileContext *fileContext, char *filePath);
/*
	check if the line starts with an entry
*/
int isLineStartsWithEntry(char* line);

/*
	check if the line is readable
*/
int thereIsReadableLine(char tempLine[MAX_LINE], FILE *file);

/*
	check if the line starts with a number
*/
int isLineStartsWithANumber(char* line, int* num);

int validateUsedLabelsDeclared(FileContext* FileContext);

/*
	check if the line starts with a register
*/
int isLineStartsWithRegister(char* line);

#endif
 
