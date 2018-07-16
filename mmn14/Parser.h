#ifndef PARSER_H
#define PARSER_H

#include "FileContextDefenition.h"
#include "FileUtils.h"

/*
	this method parse a line string starter
*/
int parseLineStringStrater(int doesLabelExistInLine, FileContext *FileContext, char* label, Line line);

/*
	this method parse a line data starter
*/
int parseLineDataStrater(int doesLabelExistInLine, FileContext *FileContext, char* label, Line line);

/*
	this method parse a line matrix starter
*/
int parseLineMatrixStrater(int doesLabelExistInLine, FileContext *FileContext, char* label, Line line);

/*
	this method parse the asm line (and uses many methods to parse correctly)
	parse line, returns TRUE if success to parse the line to asm and return FALSE if not
*/
int parseAsmLine(Line line, FileContext* FileContext);

/*
	this method process line string and return FALSE if its null or not good, it updates the FileContext table and returns TRUE
*/
int processString(Line line, FileContext* FileContext);

/*
	checks if the data capacity is equals to the data count and retruns a boolean accordinly
*/
int isDataCapacityEqualsToDataCount(FileContext *fileContext);

/*
	this method process the line data and updates the FileContexts accordinly
*/
int processLineData(Line line, FileContext* FileContext);

/*
	this method process the line matrix and updates the FileContexts accordinly
*/
int processFileContextMatrix(Line line, FileContext* FileContext);

/*
	this method check the dim1 of the matrix
*/
int checkMatrixDim1(Line *line, int *dimension1);

/*
	this method check the dim2 of the matrix
*/
int checkMatrixDim2(Line *line, int *dimension2);

/*
	this method checks if the value is in range of data member length
*/
int isValueInRange(int value);

/*
	this method updates the file context data capacity
*/
void updateFileContext(FileContext *FileContext);

/*
	this method process the FileContext Entry
*/
int processFileContextEntry(Line line, FileContext* FileContext);

/*
	this method checks the after label and return boolean value
*/
int checkAfterLabel(char afterLabel);


/*
	this method process the extern part line and updates the FileContext
*/
int processExtern(Line line, FileContext* FileContext);


/*
	This method get operand type from the line
*/
Addressing getOperandType(Line line);

/*
	this method returns boolean TRUE if it successed to
    build an operand based on the line,
    False otherwise.
    Check for garbage chars after the last operand with the flag - checkForGarbage.
*/
int createOperand(Line line, Operand* operand, int checkForGarbage);

/*
	this method add a label to the FileContext and updates it, return Boolean for success/failure
*/
int addLabelToFileContext(FileContext* FileContext, char label[MAXIMUM_LABEL_LENGTH + 1], SymbolType type, int lineNum);

/*
    Skips the chars of the num. returns pointer to the right pos. Null if failed
 */
char * skipNum(char *line);

#endif
