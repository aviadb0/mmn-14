#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "FileUtils.h"
#include "Parser.h"
#include "EntryUtils.h"
#include "WordsGenerator.h"
#include "GeneralUtils.h"
#include "IntUtils.h"
#include "ExternLocationCalculator.h"
#include "LogUtils.h"
#include "OperationData.h"

/*
	check if the line exists
*/
int lineExists(char* lineContent, FILE *file) {
	if (strchr(lineContent, ENTER) == NULL && !feof(file)) {
		return TRUE;
	}

	return FALSE;
}

/*
	check if there is line to read
*/
int thereIsReadableLine(char tempLine[MAX_LINE], FILE *file) {
	return fgets(tempLine, MAX_LINE, file) != NULL;
}

/*
	get number of operatinos in line
*/
int getNumberOpsInLine(char* line)
{
	int count = 0;
	char *isParentheses = strchr(line, JUMP_START);
	char *temp = strchr(line, OPERAND_DELIM);
	while (temp != NULL) {
		count++;
		temp = strchr(temp + 1, OPERAND_DELIM); /* find next ',' */
	}
	if (!count) { /* no operands */
		return trimString(line)[0] == BACKSLACH_ZERO ? 0 : 1;
	}
	if(isParentheses != NULL && count) /* jump type - ',' into the operand */
		count--;
	return ++count;
}

int isLineStartsWithEntry(char* line)
{
	return strstr(line, ENTRY_SYMBOL_START) == line;
}

/*
	this method returns TRUE if the op is in memory type and label dont exist in fileContext
*/
int isOpMemoryAndLabelDontExist(Operand *op, FileContext *fileContext) {
	if (op->type == memory &&
		!isLabelOrExternExistInFileContext(op->data.label, fileContext)) /* check if the label exist */
        return TRUE;
	if(op->type == jump) { /* check if the label exist for jump */
        if(!isLabelOrExternExistInFileContext(op->data.jump_data.label, fileContext)) /* check first label */
            return TRUE;
        if(op->data.jump_data.op1Type == isLabel &&
                !isLabelOrExternExistInFileContext(op->data.jump_data.op1Label, fileContext))/* check first parameter */
            return TRUE;
        if(op->data.jump_data.op2Type == isLabel &&
           !isLabelOrExternExistInFileContext(op->data.jump_data.op2Label, fileContext))/* check first parameter */
            return TRUE;
    }
    return FALSE;
}

/*
	this method validate that all the labels in operations are declared. return TRUE if error occured
*/
int validateUsedLabelsDeclared(FileContext* FileContext)
{
	int existsError = FALSE, i;
	for (i = 0; i < FileContext->operationData->operationsCounter; i++)
	{
		Op* op = &FileContext->operationData->operationsTable[i];
		if (!op->operands) { /* no operand -no labels */
			continue;
		}
		if (op->operands == 1)
		{
			if (isOpMemoryAndLabelDontExist(&(op->dst),FileContext)) { /* check for labels and check if declared */
				writeErrorOrWarningToLogWithNoLineNumber(2, "label '%s' used but not declared", op->dst.data.label);
				existsError = TRUE;
			}
		}
		else { /* 2 operands */
			if (isOpMemoryAndLabelDontExist(&(op->dst), FileContext)) { /* check for labels and check if declared */
				writeErrorOrWarningToLogWithNoLineNumber(2, "label '%s' used but not declared", op->dst.data.label);
				existsError = TRUE;
			}
			if (isOpMemoryAndLabelDontExist(&(op->src),FileContext)) {
				writeErrorOrWarningToLogWithNoLineNumber(2, "label '%s' used but not declared", op->src.data.label);
				existsError = TRUE;
			}
		}
	}
	return existsError;
}


/*
	reurns TRUE if line start with number
*/
int isLineStartsWithANumber(char* line, int* num)
{
	*num = atoi(line);

	return *num != 0 || line[0] == '0' ? TRUE : FALSE;
}

/*
	init FileContext
*/
void initFileContext(FileContext* FileContext)
{
	FileContext->errorCounter = 0;
	FileContext->instructionCounter = 0;

	initContextResources(FileContext);
}

/*
	freeFileContextMemory
*/
void freeFileContextMemory(FileContext* fileContext)
{
	int i;
	for (i = 0; i < fileContext->externData->externCount; ) {
		free(fileContext->externData->externTable[i++].locations);
	}

	freeFileContextResources(fileContext);
}

/*
	opening the file from filePath
*/
FILE* openFile(char *filePath) {
	FILE* file;
	int fileFullNameLength = strlen(filePath) + strlen(AS_SUFFIX) + 1;
	char* fileFullName = malloc(fileFullNameLength);

	/* malloc failed! */
	if (fileFullName == NULL) {
		free(fileFullName);
		return NULL;
	}
	else {
		strcpy(fileFullName, filePath); /* add the suffix ".as" to file name */
		strcat(fileFullName, AS_SUFFIX);
		if (!(file = fopen(fileFullName, "r")))
		{ /* open file failed! */
			printf("error! can't open file %s\n",fileFullName);
			free(fileFullName);
			return NULL;
		}
		free(fileFullName);
		return file;
	}
}

/*
	this method updates the label locations of the file context
*/
void updateLabelLocations(FileContext* FileContext)
{
	int i;
	for (i = 0; i < FileContext->symbolData->symbolCount; i++)
	{
		FileContext->symbolData->symbolsTable[i].location += BASE_MEM_ADDR;  /* calculate the loc by adding the base memory loc*/
		if (FileContext->symbolData->symbolsTable[i].type == data) { /* check id data - add the IC counter*/
			FileContext->symbolData->symbolsTable[i].location += FileContext->instructionCounter;
		}
	}
}

int ret(int i, FileContext *fileContext, int j, Extern *_extern) {
	return i == fileContext->externData->externCount - 1 && j == _extern->locations_count - 1;
}

/*
	this method handle the case there is no error when running asm file by calcing the extern location
*/
int handleNoErrorWhenRunningAsmFileCase1(FileContext *fileContext) {
	int lineError;
	lineError = validateThatEntryExistsInFileContext(fileContext); /* check if all the entry exist in file */
	calcExternLocation(fileContext); /* calc the extern location and insert locations into extern table */
	lineError += validateUsedLabelsDeclared(fileContext); /* check if all labels are declared */

	return lineError;
}

void outputEntryFile(FileContext* FileContext, char* file)
{
	FILE* entryFile;
	int i;
	char* fileFullName;

	if (!FileContext->entryData->entryCounter) {
		return;
	}

	fileFullName = malloc(strlen(file) + strlen(ENT_SUFFIX) + 1);
	strcpy(fileFullName, file);
	strcat(fileFullName, ENT_SUFFIX);
	entryFile = fopen(fileFullName, "w");
	free(fileFullName);

	for (i = 0; i < FileContext->entryData->entryCounter; i++)
	{
		Entry* entry = &FileContext->entryData->entryTable[i];
		fprintf(entryFile, "%s %d", entry->label,entry->lastLocation);
		if (i < FileContext->entryData->entryCounter - 1) {
			fprintf(entryFile, "\n");
		}
	}

	fclose(entryFile);
}

int isLineStartsWithRegister(char* line)
{
	return line[0] == REGISTER_CHAR && line[1] >= REGISTER_MIN && line[1] <= REGISTER_MAX && !isalnum(line[2]);
}

/*
	output object file
*/
void outputObjectFile(FileContext* FileContext, char* file)
{
	int i;
	int* words = malloc(sizeof(int)* (FileContext->instructionCounter + FileContext->data_count));
	char* fileFullName = malloc(strlen(file) + strlen(OB_SUFFIX) + 1);
	FILE* objectFile;

	strcpy(fileFullName, file);
	strcat(fileFullName, OB_SUFFIX); /* add ".ob" suffix */
	objectFile = fopen(fileFullName, "w");

	generateWordsInMemory(FileContext, words);  /* complete the list of the words */

	fprintf(objectFile, "\t%d %d\n",
		FileContext->instructionCounter,FileContext->data_count);  /* print to file the num of instructions and data words */

	for (i = 0; i < (FileContext->instructionCounter + FileContext->data_count); i++)
	{
		char wordBuffer[MAX_BASE2_INT_LEN + 1];

		words[i] &= ((1 << MEM_WORD_BITS) - 1);  /* to zero all the bits after MEM_WORD_BITS (here 14) for printing */
		fprintf(objectFile, "%c%d %s",'0',i + BASE_MEM_ADDR,convertIntToBase2(words[i], wordBuffer));  /* print the word */
		if (i < FileContext->instructionCounter + FileContext->data_count - 1) {
			fprintf(objectFile, "\n");  /* add \n if not the end */
		}
	}

	free(words);
	fclose(objectFile);
}

/*
	this method handle the case there is no error when running asm file by calcing the extern location
*/
void handleNoErrorWhenRunningAsmFileCase2(FileContext *fileContext, char *filePath) {
	updateLabelLocations(fileContext);
	outputExternFile(fileContext, filePath);
	outputEntryFile(fileContext, filePath);
	outputObjectFile(fileContext, filePath);
}

/*
	run assembly file by parsing it, compile it and validate it and then run it via sub methods of the system
*/
void runAsmFile(FILE *file, char *filePath)
{
	Line finalLine;
	int lineError = FALSE, lineNumber = 0;
	char tempLine[MAX_LINE], *tempPtr=tempLine;
	FileContext FileContext;
	initFileContext(&FileContext);

	/* going thruoh the file */
	while (thereIsReadableLine(tempLine, file)) {
		tempPtr = trimString(tempLine);
		finalLine.str = tempPtr;
		finalLine.lineNum = ++lineNumber;
		if (lineExists(tempLine, file)) { /* newline is not exist in line*/
			while (fgetc(file) != EOF);
		}
		/* if hit, there is an error in the line! */
		if (lineError)
			parseAsmLine(finalLine, &FileContext);
		else
			lineError = !parseAsmLine(finalLine, &FileContext);
	}

	if (!lineError) {
		if (!handleNoErrorWhenRunningAsmFileCase1(&FileContext)) {
			handleNoErrorWhenRunningAsmFileCase2(&FileContext, filePath);
		}
	}
	
	freeFileContextMemory(&FileContext);
	fclose(file);
}

/*
	output extern file    CHECK
*/
void outputExternFile(FileContext* FileContext, char* file)
{
	FILE* externFile;
	char* fileFullName;
	int i, j;

	if (!FileContext->externData->externCount) {
		return;
	}
		
	fileFullName = malloc(strlen(file) + strlen(EXT_SUFFIX) + 1);
	strcpy(fileFullName, file);
	strcat(fileFullName, EXT_SUFFIX);
	externFile = fopen(fileFullName, "w");
	free(fileFullName);

	for (i = 0; i < FileContext->externData->externCount; i++) {
		Extern* _extern = &FileContext->externData->externTable[i];


		for (j = 0; j < _extern->locations_count; j++)
		{
			fprintf(externFile, "%s %d", _extern->label,*_extern->locations);
			if (!ret(i, FileContext, j, _extern)) {
				fprintf(externFile, "\n");
			}
		}
	}

	fclose(externFile);
}
