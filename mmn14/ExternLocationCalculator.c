#include <stdio.h>
#include <string.h>

#include "ExternLocationCalculator.h"
#include "GeneralUtils.h"
#include "WordsGenerator.h"
#include "LogUtils.h"

/*
	check if op source is memory type
*/
int isOpSourceIsMemory(int sourceExists, Op *op, Extern *ext) {
	return sourceExists && op->src.type == memory && strcmp(op->src.data.label, ext->label) == 0;
}

/*
	calculating extern location
*/
void calcExternLocation(FileContext* FileContext)
{
	int i;
	for (i = 0; i < FileContext->externData->externCount; i++)
	{
		Extern* ext = &FileContext->externData->externTable[i];
		int location = BASE_MEM_ADDR, j;

		for (j = 0; j < FileContext->operationData->operationsCounter; j++)
		{
			int destinationLocation, sourceLocation, sourceExists;
			Op* op = &FileContext->operationData->operationsTable[j];

			if (!op->operands) {
				continue;
			}
			if (op->operands == 1)
			{
				sourceExists = FALSE;
				destinationLocation = location + 1;
			}
			else if (op->operands == 2)
			{
				sourceExists = TRUE;
				destinationLocation = location + 2;
				sourceLocation = location + 1;
				if (op->src.type == matrix) {
					destinationLocation++;
				}
			}
			if (isOpDestIsMemory(op, ext)) {
				addLocationToExtern(ext, destinationLocation);
			}
			if (isOpSourceIsMemory(sourceExists, op, ext)) {
				addLocationToExtern(ext, sourceLocation);
			}

			location += op->binary_size;
		}
	}
}


/*
	check if op destination is memory type
*/
int isOpDestIsMemory(Op *op, Extern *ext) {
	return op->dst.type == memory && strcmp(op->dst.data.label, ext->label) == 0;
}



