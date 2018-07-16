#include <string.h>
#include <ctype.h>

#include "LineUtils.h"
#include "constants.h"
#include "LogUtils.h"
#include "GeneralUtils.h"
#include "FileUtils.h"

/*
	check if the line is comment
*/
int isCommentLine(char* line) {
	return line[0] == COMMENT_CHAR;
}

/*
	check if the line is empty
*/
int isEmpryLine(char* line)
{
	char* first_nonspace = trimString(line);
	if (*first_nonspace == BACKSLACH_ZERO)
		return TRUE;
	return FALSE;
}

/*
	check if the line strats with extern
*/
int startsWithAExtern(char* line)
{
	return strstr(line, EXTERN_SYMBOL_START) == line;
}


/*
	check if the line is starts with label
*/
int isLineStartWithLabel(Line line, char label[MAXIMUM_LABEL_LENGTH + 1], int* errorExists)
{
	char* origLine;
	int label_len = 0;

	if (strchr(line.str, LABEL_END) == NULL) {
		return FALSE;
	}

	origLine = line.str;
	if (!isalpha(*line.str))
	{
		if (isspace(*line.str)) {
			writeErrorOrWarningToLog(1,line.lineNum, "label not start correctly. Label must start with a letter");
		}
		else {
			writeErrorOrWarningToLog(1,line.lineNum, "label not start correctly. Label must start with a letter");
		}
		*errorExists = TRUE;
		return FALSE;
	}

	while (*line.str && isalnum(*line.str))
	{
		label_len++;
		line.str++;
	}
	if (*line.str == LABEL_END)
	{
		int operationIndex;
		if (label_len > MAXIMUM_LABEL_LENGTH)
		{
			writeErrorOrWarningToLog(1, line.lineNum, "The label is bigger then the max length: %d", MAXIMUM_LABEL_LENGTH);
			*errorExists = TRUE;
			return FALSE;
		}
		strncpy(label, origLine, label_len);
		label[label_len] = '\0';

		if (isLineStartsWithRegister(label)) {
			writeErrorOrWarningToLog(1, line.lineNum, "label can't be a register name");
			*errorExists = TRUE;
			return FALSE;
		}

		if (isLineStartsWithOp(label, &operationIndex) && label[strlen(operationsTable[operationIndex].name)] == '\0')
		{
			writeErrorOrWarningToLog(1,line.lineNum, "label can't be an op name");
			*errorExists = TRUE;
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

/*
	check if the line strats with a string
*/
int startsWithAString(char* line)
{
	return strstr(line, STRING_SYMBOL_START) == line;
}

/*
	check if the line starts with data
*/
int startsWithAData(char* line)
{
	return strstr(line, DATA_SYMBOL_START) == line;
}

