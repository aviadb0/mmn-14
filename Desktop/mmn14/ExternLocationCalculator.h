#ifndef EXTERN_LOCATION_CALCULATOR_H
#define EXTERN_LOCATION_CALCULATOR_H

#include "FileContextDefenition.h"

/*
	check if op source is memory type
*/
int isOpSourceIsMemory(int sourceExists, Op *op, Extern *ext);

/*
	calculating extern location
*/
void calcExternLocation(FileContext* FileContext);

/*
	check if op destination is memory type
*/
int isOpDestIsMemory(Op *op, Extern *ext);


#endif
