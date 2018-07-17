#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "LineUtils.h"
#include "Parser.h"
#include "FileContextUtils.h"
#include "GeneralUtils.h"
#include "LineUtils.h"
#include "LogUtils.h"
#include "OperationData.h"

/*
	this method parse a line data starter
*/
int parseLineDataStrater(int doesLabelExistInLine, FileContext *FileContext, char* label, Line line) {
	if ((doesLabelExistInLine && !addLabelToFileContext(FileContext, label, data, line.lineNum))
		|| !processLineData(line, FileContext)) {
		return FALSE;
	}
	return TRUE;
}

/*
	this method process the extern part line and updates the FileContext
*/
int processExtern(Line line, FileContext* FileContext)
{
	char externLabel[MAXIMUM_LABEL_LENGTH + 1];

	line.str += strlen(EXTERN_SYMBOL_START);
	line.str = trimString(line.str);

	if (!tryGetLabel(line, externLabel)) {
		writeErrorOrWarningToLog(1, line.lineNum, "invalid label in extern");
		return FALSE;
	}
	if (isLabelOrExternExistInFileContext(externLabel, FileContext)) {
		writeErrorOrWarningToLog(1, line.lineNum, "extern label '%s' already exists", externLabel);
		return FALSE;
	}

	addExtern(FileContext, externLabel);
	return TRUE;
}

/* 
	this method parse the asm line (and uses many methods to parse correctly)
	parse line, returns TRUE if success to parse the line to asm and return FALSE if not
*/
int parseAsmLine(Line line, FileContext* FileContext)
{
	int operationIndex, doesLabelExistInLine = FALSE, doesErrorAccourd = FALSE;
	char label[MAXIMUM_LABEL_LENGTH + 1];

	if (isEmptyLine(line.str) || isCommentLine(line.str)) {
		return TRUE;
	}
	if (isLineStartWithLabel(line, label, &doesErrorAccourd)) {
		doesLabelExistInLine = TRUE;
		line.str += strlen(label) + 1;
	}
	if (doesErrorAccourd) {
		return FALSE;
	}

	line.str = trimString(line.str);

	if (startsWithAString(line.str)) {
		return parseLineStringStrater(doesLabelExistInLine, FileContext, label, line);
	} else if (startsWithAData(line.str)) {
		return parseLineDataStrater(doesLabelExistInLine, FileContext, label, line);
	} else if (isLineStartsWithEntry(line.str)) {
		return processFileContextEntry(line, FileContext);
	} else if (startsWithAExtern(line.str)) {
		return processExtern(line, FileContext);
	} else if (isLineStartsWithOp(line.str, &operationIndex)) {
		Op generated;
		if (!createOperation(line, FileContext, operationIndex, &generated) ||
			(doesLabelExistInLine && !addLabelToFileContext(FileContext, label, code, line.lineNum))) {
			return FALSE;
		}
		addOperation(FileContext, generated); /*insert the operation to table*/
		FileContext->instructionCounter += FileContext->operationData->operationsTable[FileContext->operationData->operationsCounter - 1].binary_size; /*increase IC by the number of words*/
	} else {
		writeErrorOrWarningToLog(1, line.lineNum, "invalid command");
		return FALSE;
	}

	return TRUE;
}

/*
	checks if the data capacity is equals to the data count and retruns a boolean accordinly
*/
int isDataCapacityEqualsToDataCount(FileContext *fileContext) {
	return fileContext->data_count == fileContext->data_capacity;
}

/*
	this method process line string and return FALSE if its null or not good, it updates the FileContext table and returns TRUE
*/
int processString(Line line, FileContext* FileContext)
{
	char *stringFinal, *string;
	int stringLength;

	line.str = strchr(line.str, BACKSLASH);
	if (line.str == NULL) {
		writeErrorOrWarningToLog(1, line.lineNum, "improper string formatting");
		return FALSE;
	}
	line.str++;
	stringFinal = strchr(line.str, BACKSLASH);
	if (stringFinal == NULL)
	{
		writeErrorOrWarningToLog(1, line.lineNum, "string not terminated with %c", BACKSLASH);
		return FALSE;
	}
	if (stringFinal == line.str)
	{
		writeErrorOrWarningToLog(1,line.lineNum, "empty string");
		return FALSE;
	}
	stringLength = stringFinal - line.str;
	string = malloc(stringLength + 1);
	strncpy(string, line.str, stringLength);
	string[stringLength] = '\0';
	/* copying the string to data_table, while incrementing DC */
	while (*string)
	{
		if (isDataCapacityEqualsToDataCount(FileContext)) {
			FileContext->data_capacity *= 2;
			FileContext->data_table = realloc(FileContext->data_table, sizeof(*(FileContext->data_table)) * FileContext->data_capacity);
		}
		FileContext->data_table[FileContext->data_count++] = *string;
		string++;
	}

	if (isDataCapacityEqualsToDataCount(FileContext)) {
		FileContext->data_capacity *= 2;																					
		FileContext->data_table = realloc(FileContext->data_table, sizeof(*(FileContext->data_table)) * FileContext->data_capacity);
	}
	FileContext->data_table[FileContext->data_count++] = BACKSLACH_ZERO;

	return TRUE;
}

/*
	this method parse a line string starter
*/
int parseLineStringStrater(int doesLabelExistInLine, FileContext *FileContext, char* label, Line line) {
	if ((doesLabelExistInLine && !addLabelToFileContext(FileContext, label, data, line.lineNum))
		|| !processString(line, FileContext)) {
		return FALSE;
	}
	return TRUE;
}

/*
	this method process the line data and updates the FileContexts accordinly
*/
int processLineData(Line line, FileContext* FileContext)
{
	int num;
	line.str += strlen(DATA_SYMBOL_START);
	do
	{
		line.str++; /* skipping space in first number, ',' in next */
		if (!isLineStartsWithANumber(line.str, &num))
		{
			writeErrorOrWarningToLog(1,line.lineNum, "invalid number");
			return FALSE;
		}
		if (num > MAXIMUM_DATA_LENGTH || num < MAXIMUM_DATA_NUMBER)
		{
			writeErrorOrWarningToLog(1, line.lineNum, "number %d not in range %d to %d", num, MAXIMUM_DATA_NUMBER, MAXIMUM_DATA_LENGTH);
			return FALSE;
		}
		if (isDataCapacityEqualsToDataCount(FileContext)) {
			FileContext->data_capacity *= 2;
			FileContext->data_table = realloc(FileContext->data_table, sizeof(*(FileContext->data_table)) * FileContext->data_capacity);
		}
		FileContext->data_table[FileContext->data_count++] = num;
	} while ((line.str = strchr(line.str, DATA_SYMBOL_START_SEPERATOR)));
	return TRUE;
}

/*
	this method checks if the value is in range of data member length
*/
int isValueInRange(int value) {
	return value > MAXIMUM_DATA_LENGTH || value < MAXIMUM_DATA_NUMBER;
}

/*
	this method updates the file context data capacity
*/
void updateFileContext(FileContext *FileContext) {
	FileContext->data_capacity *= 2;
	FileContext->data_table = realloc(FileContext->data_table, sizeof(*(FileContext->data_table)) * FileContext->data_capacity);
}

/*
	this method add a label to the FileContext and updates it, return Boolean for success/failure
*/
int addLabelToFileContext(FileContext* FileContext, char label[MAXIMUM_LABEL_LENGTH + 1], SymbolType type, int lineNum)
{
	if (isLabelOrExternExistInFileContext(label, FileContext)) {
		writeErrorOrWarningToLog(1, lineNum, "label '%s' already exists", label);
		return FALSE;
	}

	addSymbol(FileContext, label, type);
	return TRUE;
}

/*
	this method process the FileContext Entry
*/
int processFileContextEntry(Line line, FileContext* FileContext)
{
	char entryLbl[MAXIMUM_LABEL_LENGTH + 1];
	line.str += strlen(ENTRY_SYMBOL_START);
	line.str = trimString(line.str);

	if (!tryGetLabel(line, entryLbl)) {
		writeErrorOrWarningToLog(1, line.lineNum, "invalid label in entry");
		return FALSE;
	}
	if (isEntryExistInFileContext(entryLbl, FileContext)) {
		writeErrorOrWarningToLog(1, line.lineNum, "entry label '%s' already exists", entryLbl);
		return FALSE;
	}

	addEntry(FileContext, entryLbl);
	return TRUE;
}

/*
	this method checks the after label and return boolean value
*/
int checkAfterLabel(char afterLabel) {
	return isspace(afterLabel) || afterLabel == '\0' || afterLabel == OPERAND_DELIM;
}

/*
	This method get operand type from the line
*/
Addressing getOperandType(Line line) {
	char label[MAXIMUM_LABEL_LENGTH + 1];

	if (line.str[0] == IMMEDIATE_CHAR) {
		return immediate;
	}
	if (isLineStartsWithRegister(line.str)) {
		return regist;
	}
	if (tryGetLabel(line, label)) {
		char afterLabel = line.str[strlen(label)];
		if (afterLabel == JUMP_START) {
			return jump;
		}
		else if (checkAfterLabel(afterLabel)) {
			return memory;
		}
	}

	return none;
}

/*
	this method returns boolean TRUE if it successed to
 build an operand based on the line,
 False otherwise.
 Check for garbage chars after the last operand with the flag - checkForGarbage.
*/
int createOperand(Line line, Operand* operand, int checkForGarbage)
{
	Addressing type = getOperandType(line);
	operand->type = type;
	if (type == none)
	{
		writeErrorOrWarningToLog(1,line.lineNum, "invalid addressing type");
		return FALSE;
	}
	if (type == immediate)
	{
		int num;
		/*skipping # char*/
		line.str += sizeof(char);
		if (!isLineStartsWithANumber(line.str, &num))
		{
			writeErrorOrWarningToLog(1, line.lineNum, "invalid number");
			return FALSE;
		}
		if (!isNumInRange(num))
		{
			writeErrorOrWarningToLog(1, line.lineNum, "number %d not in range %d to %d", num, MINIMUM_NUMBER, MAXIMUM_NUMBER);
			return FALSE;
		}
		if(checkForGarbage) /* flag is True, checking for garbage */
		{
			char *temp;
			temp = skipNum(line.str);
			if (checkLineForGarbageChars(temp)) /*check for garbage chars after the command*/
			{
				writeErrorOrWarningToLog(1, line.lineNum, "there are garbage chars after the command");
				return FALSE;
			}
		}
		operand->data.number = num;
		return TRUE;
	}
	else if (type == regist)
	{
		operand->data.reg[0] = line.str[0];
		operand->data.reg[1] = line.str[1];
		operand->data.reg[2] = '\0';
		if(checkForGarbage) /* flag is True, checking for garbage */
		{
			if (checkLineForGarbageChars(&line.str[2])) /*check for garbage chars after the register*/
			{
				writeErrorOrWarningToLog(1, line.lineNum, "there are garbage chars after the command");
				return FALSE;
			}
		}
		return TRUE;
	}
	else if (type == memory)
	{
		tryGetLabel(line, operand->data.label);
		if(checkForGarbage) /* flag is True, checking for garbage */
		{
			if (checkLineForGarbageChars(&line.str[strlen(operand->data.label)])) /*check for garbage chars after the label*/
			{
				writeErrorOrWarningToLog(1, line.lineNum, "there are garbage chars after the command");
				return FALSE;
			}
		}
		return TRUE;
	}
	else if (type == jump)
	{
		int num, isLabelFlag = 0;
		char tmp[MAXIMUM_OPERATION_LENGTH + 1];
		char label[MAXIMUM_LABEL_LENGTH + 1];
		char* temp_line = tmp;
		tryGetLabel(line, operand->data.label);
		strcpy(temp_line, line.str);
		temp_line += strlen(operand->data.label);
		temp_line += 1; /*for '(' char*/
		/*first operand*/
		if (!isLineStartsWithRegister(temp_line) && !(temp_line[0] == IMMEDIATE_CHAR && isLineStartsWithANumber(temp_line+1,&num)) &&
			!(isLabelFlag = tryGetLabelCharEdition(temp_line,label))) /*check first operand - is num/register/label*/
		{
			writeErrorOrWarningToLog(1, line.lineNum, "invalid operand");
			return FALSE;
		}
		if (isLineStartsWithRegister(temp_line) && !isalnum(temp_line[REGISTER_LEN])) /*first operand is register*/
		{
			operand->data.jump_data.register1 = temp_line[1] - '0';
			operand->data.jump_data.op1Type = isRegister;
			temp_line += REGISTER_LEN;
		}
		else if (isLabelFlag) /*first operand is label*/
		{
			strcpy(operand->data.jump_data.op1Label, label);
			operand->data.jump_data.op1Type = isLabel;
			temp_line += strlen(operand->data.jump_data.op1Label);
		}
		else /*first operand is num*/
		{
			if (!isNumInRange(num))
			{
				writeErrorOrWarningToLog(1, line.lineNum, "number %d not in range %d to %d", num, MINIMUM_NUMBER, MAXIMUM_NUMBER);
				return FALSE;
			}
			operand->data.jump_data.num1 = num;
			operand->data.jump_data.op1Type = isNumber;
			temp_line = skipNum(temp_line); /* skip the chars of the number */
		}
		if(temp_line[0] != OPERAND_DELIM) /*check if ',' after op1*/
		{
			writeErrorOrWarningToLog(1, line.lineNum, "wrong format of jump - no ',' after first parameter");
			return FALSE;
		}
		temp_line++; /*for ',' char*/
		/*second operand*/
		if (!isLineStartsWithRegister(temp_line) && !(temp_line[0] == IMMEDIATE_CHAR && isLineStartsWithANumber(temp_line+1,&num))
			&& !(isLabelFlag =tryGetLabelCharEdition(temp_line,label)))/*check second operand - is num/register/label*/
		{
		    if (isspace(temp_line[0])) { /* space between parameters */
                writeErrorOrWarningToLog(1, line.lineNum, "space disallowed between jump operators");
		    }
		    else {
                writeErrorOrWarningToLog(1, line.lineNum, "invalid operand");
                return FALSE;
		    }
		}
		if (isLineStartsWithRegister(temp_line) && !isalnum(temp_line[REGISTER_LEN])) /*second operand is register*/
		{
			operand->data.jump_data.register2 = temp_line[1] - '0';
			operand->data.jump_data.op2Type = isRegister;
			temp_line += REGISTER_LEN;
		}
		else if (isLabelFlag) /*second operand is label*/
		{
			strcpy(operand->data.jump_data.op2Label, label);
			operand->data.jump_data.op2Type = isLabel;
			temp_line += strlen(operand->data.jump_data.op2Label);
		}
		else /*second operand is num*/
		{
			if (!isNumInRange(num))
			{
				writeErrorOrWarningToLog(1, line.lineNum, "number %d not in range %d to %d", num, MINIMUM_NUMBER, MAXIMUM_NUMBER);
				return FALSE;
			}
			operand->data.jump_data.num2 = num;
			operand->data.jump_data.op2Type = isNumber;
			temp_line = skipNum(temp_line);
		}
		if(temp_line[0]!= JUMP_END) /*check if ')' after op2*/
		{
			writeErrorOrWarningToLog(1, line.lineNum, "wrong format of jump - no ')' right after the second parameter");
			return FALSE;
		}
		temp_line++; /* for ')' */
		if(checkForGarbage) /* flag is True, checking for garbage */
		{
			if (checkLineForGarbageChars(temp_line)) /*check for garbage chars after the ')' */
			{
				writeErrorOrWarningToLog(1, line.lineNum, "there are garbage chars after the command");
				return FALSE;
			}
		}
		return TRUE;
	}
	return FALSE;
}
