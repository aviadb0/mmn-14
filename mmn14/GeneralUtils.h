#ifndef GENERAL_UTILS_H
#define GENERAL_UTILS_H

#include <stdlib.h>
#include <stdarg.h>

#include "FileContextDefenition.h"

/*
	remove all spaces
*/
char* trimString(char* str);

/*
	trying get label
*/
int tryGetLabel(Line line, char label[MAXIMUM_LABEL_LENGTH + 1]);

/*
	trying get label - the char * edition (no Line in parameters for immediate use)
*/
int tryGetLabelForJumpParameters(char * line, char label[MAXIMUM_LABEL_LENGTH + 1]);
/*
	init the op struct
*/
void initOp(char *line, char* op);

/*
	returns TRUE if the line starts with Op
*/
int isLineStartsWithOp(char* line, int* operationIndex);

/*
	check if the line starts with condition
*/
int getIsLineStartsWithOpCondition(char *line, int i);


/*
	check if the source and the destination are regist
*/
int isOpSourceAndDestAreRegist(Op *op);

/*
	returning the address and name
*/
char* getAddressNameFromAddress(Addressing addr);

/*
	calculating the binary operation size
*/
int calcOperationBinarySize(Op* op);

/*
	adding the locatino to Extern
*/
void addLocationToExtern(Extern* ext, int location);

/*
	creating operation
*/
int createOperation(Line line, FileContext* FileContext, int operationIndex, Op* generated);

/*
	return address type
*/
int getAddressType(Addressing method);

/* Skips the chars of the num. returns pointer to the right pos. Null if failed*/
char * skipNum(char *line);

/*
	reversing string
*/
void reverseString(char* str);

/*return true if num is between MINIMUM_NUMBER &  MAXIMUM_NUMBER */
int isNumInRange(int num);

/*
	check if the dest is jump
*/
int isOpDestIsJump(Op *op);
/*
	return address type of the parameter in jump
*/
int getAddressTypeJumpOp(int type);
/*
 * return true if in line there are chars that are not space (garbage chars).
 */
int checkLineForGarbageChars(char *line);

/*
 * return true if the label is a saved word (register or operation)
 */
int checkLabelForSavedWords(char *label);

/*
 * return true if the label is an operation
 */
int checkIsOperation(char *label);

#endif
