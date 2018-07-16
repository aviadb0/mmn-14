#ifndef WORD_GENERATOR_H
#define WORD_GENERATOR_H

#include "FileContextUtils.h"
#include "FileContextDefenition.h"
#include "constants.h"

/*
	enum for decide which operand type is the operand are, source or destination
*/
typedef enum {
	src,
	dst
} OperandType;

/*
	this method generates machine codes for words in the FileContext
*/
void generateWordsInMemory(FileContext* FileContext, int* words);

/*
this method calculate a word based on the Op and the src\dest address
*/
int calcWord(Op* op, int destinationAddress, int sourceAddress, int op1Address, int op2Address);

/*
this method checks if the op type is regist
*/
int isRegist(Op* op);

/*
this method handles the special case of two register operands sharing a single memory word
*/
int generateWordForRegisters(char src_reg[3], char dst_reg[3]);

/*
this method generates a word from an operand and a filecontext only jump related
*/
void generateWordWithOperandAddressingForJump(int* words, FileContext* FileContext, Operand* operand, OperandType type, int* wordsIndex);

/*
this method generates a word from an operand and a filecontext only not jump related
*/
void generateWordWithOperandAddressingForNotJump(int* words, FileContext* FileContext, Operand* operand, OperandType type, int* wordsIndex);

/*
this method calculate a word based on an operand anf filecontext when the operand is represent memory
*/
int handleMemoryOperandType(Operand *operand, FileContext *fileContext);

/*
this method calculate a word based on an operand anf filecontext when the operand is represent Immediate
*/
int handleImmediateOperandType(Operand *operand);

/*
this method calculate a word based on an operand anf filecontext when the operand is represent regist
*/
int handleRegistOperandType(Operand *operand, OperandType type);

/*
	creating memory word for non matrix
*/
int generateWordForNonJumpOp(Operand* operand, FileContext* FileContext, OperandType type);

/*
This method calculate word based on the fact that we work on a null Symbol when jump operation
*/
int calcWordForNullSymbolWhenJumpOp();

/*
This method calculate word for label based on the fact that we work on a non null Symbol when jump operation
*/
int calcWordForNotNullSymbolWhenJumpOp(Symbol *symbol);

/*
general method for building a word from an Op struct
*/
int buildWordFromOp(Op* op);

/*
this method generates a word from an operand and a filecontext only Address related
*/
void generateWordWithOperandAddressing(int* words, FileContext* FileContext, Operand* operand, OperandType type, int* words_idx);

/*
this method generates jump operand label word based on the operand and the filecontext
*/
int generateJumpOperandWord(Operand* operand, FileContext* FileContext);

/*
	this method calculate a word based on an parameter and filecontext when the parameter is represent memory
*/
int handleJumpMemoryParameterType(char *label, FileContext *fileContext);

/*
	this method generates a word from parameter1 in jump
*/
int generateWordForJumpParameter1(Operand *op, FileContext* FileContext);

/*
	this method generates a word from parameter2 in jump
*/
int generateWordForJumpParameter2(Operand *op, FileContext* FileContext);

#endif

