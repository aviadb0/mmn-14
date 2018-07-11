#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "GeneralUtils.h"
#include "FileContextDefenition.h"
#include "WordsGenerator.h"
#include "FileUtils.h"
#include "LogUtils.h"
#include "Parser.h"
#include "OperationData.h"


/*
	is line start with condition
*/
int getIsLineStartsWithOpCondition(char *line, int i) {
	return i < MAX_OP_LEN && !(line[i] == ' ' || line[i] == BACKSLASH_T);
}

/*
	check if the line strats with a matrix
*/
int isMatrixStart(char *line, int* num) {
	return line[0] == MATRIX_DIMENSION_START && isLineStartsWithANumber(line + 1, num);
}


/*
	check if the line starts with matrix dimension
*/
int isLineStartWithMatrixDim(char* line, int* num)
{
        char* endOfDimension;
	if (!isMatrixStart(line,num)) {
		return FALSE;
	}

	endOfDimension = strchr(line, MATRIX_DIMENSION_END);
	if (endOfDimension == NULL) {
		return FALSE;
	}
	
	while (++line != endOfDimension)
	{
		if (checkLineEndBackslashT(line))
			return FALSE;
	}
	return TRUE;

}

/*
	check if the source and the destination are regist
*/
int isOpSourceAndDestAreRegist(Op *op) {
	return op->operands == 2 && op->src.type == regist && op->dst.type == regist;
}

/*
	creating operation - return false if failed
*/
int createOperation(Line line, FileContext* FileContext, int operationIndex, Op* generated)
{
	Op operation = operationsTable[operationIndex];
	int counter;

	*generated = operation;
	line.str += strlen(operation.name);
	line.str = trimString(line.str);

	counter = getNumberOpsInLine(line.str); /*find the number of operand in line*/

	if (counter != operation.operands) {  /*wrong num of ops*/
		writeErrorOrWarningToLog(1, line.lineNum, "error in number of operands for the operation '%s', was %d but should be %d", operation.name, counter, operation.operands);
		return FALSE;
	}

	if (counter) {
		Operand destination, source;
		if (counter == 2) { /*operation with 2 operands - get source operand*/
			if (!createOperationerand(line, &source)) {
				return FALSE;
			}
			if (!(source.type & operation.allowed_src_addressing)) { /*check the addressing type*/
				writeErrorOrWarningToLog(1, line.lineNum, "error in addressing %s for source operand in op '%s'", getAddressNameFromAddress(source.type), operation.name);
				return FALSE;
			}
			generated->src = source;
			line.str = strchr(line.str, OPERAND_DELIM) + 1;
			line.str = trimString(line.str);
		}
		if (!createOperationerand(line, &destination)) { /*get dest operand*/
			return FALSE;
		}
		if (!(destination.type & operation.allowed_dst_addressing)) { /*check the addressing type*/
			writeErrorOrWarningToLog(1, line.lineNum, "error in addressing %s for destination operand in op '%s'", getAddressNameFromAddress(destination.type), operation.name);
			return FALSE;
		}
		generated->dst = destination;
	}

	generated->binary_size = calcOperationBinarySize(generated);

	return TRUE;
}

/*
	init the op struct
*/
void initOp(char *line, char* op) {
	int i;
	for (i = 0; getIsLineStartsWithOpCondition(line, i); i++) {
		op[i] = line[i];
	}

	op[i] = BACKSLACH_ZERO;
}

/*
	returning the address and name
*/
char* getAddressNameFromAddress(Addressing addr)
{
	switch (addr)
	{
	case immediate:
		return IMMEDIATE;
	case memory:
		return MEMORY;
	case jump:
		return JUMP;
	case regist:
		return REGISTER;
	default:
		return UNK;
	}
}

/*
	check if the line end with backslash t
*/
int checkLineEndBackslashT(char *line) {
	return !isdigit(*line) && !(*line == ' ' || *line == BACKSLASH_T);
}

/*
	trying get label
*/
int tryGetLabel(Line line, char label[MAXIMUM_LABEL_LENGTH + 1])
{
	char* origLine = line.str;
	int label_len = 0;

	if (!isalpha(*line.str)) {
		return FALSE;
	}

	while (*line.str && isalnum(*line.str)) {
		label_len++;
		line.str++;
	}
	if (label_len > MAXIMUM_LABEL_LENGTH) {
		return FALSE;
	}

	strncpy(label, origLine, label_len);
	label[label_len] = BACKSLACH_ZERO;
	return TRUE;
}


/*
	trying get label - the char * edition (no Line in parameters for immediate use)
*/
int tryGetLabelCharEdition(char * line, char label[MAXIMUM_LABEL_LENGTH + 1])
{
	char* origLine = line;
	int label_len = 0;

	if (!isalpha(*line)) {
		return FALSE;
	}

	while (*line && isalnum(*line)) {
		label_len++;
		line++;
	}
	if (label_len > MAXIMUM_LABEL_LENGTH) {
		return FALSE;
	}

	strncpy(label, origLine, label_len);
	label[label_len] = BACKSLACH_ZERO;
	return TRUE;
}

/*
	check if the destination is matrix
*/
int isOpDestIsMatrix(Op *op) {
	return op->operands >= 1 && op->dst.type == matrix;
}

/*
	check if the source is matrix
*/
int isOpSourceIsMatrix(Op *op) {
	return op->operands == 2 && op->src.type == matrix;
}

/*
	check if the dest is jump
*/
int isOpDestIsJump(Op *op) {
	return op->operands == 1 && op->dst.type == jump;
}

/*
	calculating the binary operation size
*/
int calcOperationBinarySize(Op* op)
{
	int extra_size = 0;
	if (isOpSourceAndDestAreRegist(op)) { /* check if 2 registers - 2 binary words*/
		return BOTH_REGIST; /* return 2*/
	}
	if (isOpDestIsJump(op)) {
		if(op->dst.data.jump_data.op1Type == isRegister && op->dst.data.jump_data.op1Type)
		{
			extra_size++; /* both parameters are registers - 1 word */
		}
		else
		{
			extra_size+=JUMP_PARAMETERS;  /* else - 2 word for each parametr */
		}
	}
	return 1 + op->operands + extra_size;
}

/*
	returns TRUE if the line strats with Op
*/
int isLineStartsWithOp(char* line, int* operationIndex)
{
	char op[MAX_OP_LEN + 1];
	int i;

	initOp(line, op);

	for (i = 0; i < operationsCounter; i++)
	{
		if (!strcmp(op, operationsTable[i].name)) {
			*operationIndex = i;
			return TRUE;
		}
	}

	return FALSE;
}

/*
	adding the locatino to Extern
*/
void addLocationToExtern(Extern* _extern, int location)
{
	if (_extern->locations_count == _extern->locations_capacity)
	{
		_extern->locations_capacity *= 2;
		_extern->locations = realloc(_extern->locations, _extern->locations_capacity);
	}
	_extern->locations[_extern->locations_count] = location;
	_extern->locations_count++;
}

/*
	remove all spaces
*/
char* trimString(char* str)
{
	while (isspace(*str)) {
		str++;
	}

	return str;
}

/*
	return address type
*/
int getAddressType(Addressing addressType)
{
	if (addressType == immediate) {
		return ADDR_IMMEDIATE;
	} else if (addressType == memory) {
		return ADDR_MEMORY;
	} else if (addressType == matrix) {
		return ADDR_MATRIX;
	}
	else if (addressType == regist) {
		return ADDR_REGISTER;
	}

	return TYPE_UNKNOWN;
}

/*
	reversing string
*/
void reverseString(char * str)
{
	if (str) {
		char * end = str + strlen(str) - 1;
		#   define XOR_SWAP(a,b) do\
			{\
			  a ^= b;\
			  b ^= a;\
			  a ^= b;\
			} while (0)

		while (str < end) {
			XOR_SWAP(*str, *end);
			str++;
			end--;
		}

		#   undef XOR_SWAP
	}
}

/* Skips the chars of the num (include the char of immediate). returns pointer to the right pos. Null if failed*/
char *skipNum(char *line)
{
	int i=0, len = strlen(line);
	if(line[i] == IMMEDIATE_CHAR)
		i++;
	if(line[i] == MINUS || line[i] == PLUS)
		i++;
	while(i<len && isdigit(line[i]))
	{
		i++;
	}
	return &line[i];
}
/*return true if num is between MINIMUM_NUMBER &  MAXIMUM_NUMBER */
int isNumInRange(int num)
{
	return (num > MINIMUM_NUMBER && num < MAXIMUM_NUMBER);
}