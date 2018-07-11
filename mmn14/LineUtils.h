#ifndef LINE_UTILS_H
#define LINE_UTILS_H

#include "FileContextDefenition.h"

/*
	check if the line is comment
*/
int isCommentLine(char* line);

/*
	check if the line strats with a matrix
*/
int startsWithAMatrix(char* line);

/*
	check if the line is empty
*/
int isEmpryLine(char* line);

/*
	check if the line strats with a string
*/
int startsWithAString(char* line);

/*
	check if the line starts with data
*/
int startsWithAData(char* line);

/*
	check if the line is starts with label
*/
int isLineStartWithLabel(Line line, char label[MAXIMUM_LABEL_LENGTH + 1], int* has_err);

/*
	check if the line strats with extern
*/
int startsWithAExtern(char* line);

#endif