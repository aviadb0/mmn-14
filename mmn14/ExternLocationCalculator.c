#include <stdio.h>
#include <string.h>

#include "ExternLocationCalculator.h"
#include "GeneralUtils.h"
#include "WordsGenerator.h"
#include "LogUtils.h"
#include "OperationData.h"

/*
	check if op source is memory type
*/
int isOpSourceIsMemory(int sourceExists, Op *op, Extern *ext) {
	return sourceExists && op->src.type == memory && strcmp(op->src.data.label, ext->label) == 0;
}

/*
	calculating extern location - start from 100
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
				location++;  /* for the first word */
				continue;
			}
			if (op->operands == 1)
			{
				sourceExists = FALSE; /* just dest exist */
				destinationLocation = location + 1; /* first line in memory for the first word */
				if (op->dst.type == jump) /*check if jump - jump can be 3 labels */
				{
					if(strcmp(op->dst.data.jump_data.label, ext->label) == 0) {
						addLocationToExtern(ext, destinationLocation);
					}
					destinationLocation++; /* the pos of the next word */
					if(op->dst.data.jump_data.op1Type == isLabel &&
					   strcmp(op->dst.data.jump_data.op1Label, ext->label) == 0) { /* check first parameter */
						addLocationToExtern(ext, destinationLocation);
					}
					destinationLocation++; /* the pos of the next word */
					if(op->dst.data.jump_data.op2Type == isLabel &&
					   strcmp(op->dst.data.jump_data.op2Label, ext->label) == 0) { /* check second parameter */
						addLocationToExtern(ext, destinationLocation);
					}
					location += op->binary_size;
					continue;
				}
			}
			else if (op->operands == 2)
			{
				sourceExists = TRUE;
				destinationLocation = location + 2;
				sourceLocation = location + 1;

			}
			if (isOpDestIsMemory(op, ext)) {  /* check if dest is a label */
				addLocationToExtern(ext, destinationLocation);
			}
			if (isOpSourceIsMemory(sourceExists, op, ext)) { /* check if src op is a label */
				addLocationToExtern(ext, sourceLocation);
			}

			location += op->binary_size; /* jump to the memory line for next operation */
		}
	}
}


/*
	check if op destination is memory type
*/
int isOpDestIsMemory(Op *op, Extern *ext) {
	return op->dst.type == memory && strcmp(op->dst.data.label, ext->label) == 0;
}



