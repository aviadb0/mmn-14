#ifndef OPERATION_DATA_DEFENITION_H
#define OPERATION_DATA_DEFENITION_H

#include "constants.h"

/*
	Addressing struct gives as the relative command op (if its matrix\memory etc..)
*/
typedef enum Addressing {
	none = 0,
	immediate = 1 << 0,
	jump = 1 << 2,
	memory = 1 << 1,
	regist = 1 << 3
} Addressing;


typedef enum jumpOp {
	isNumber = 0,
	isRegister = 1,
	isLabel = 2
} jumpOp;
/*
	Operand struct represent a full Operand in the system, every operand has: Address,label etc..
*/
typedef struct Operand {
	Addressing type;
	union {
		char reg[3];
		int number : 13;
		char label[MAXIMUM_LABEL_LENGTH + 1];
		struct {
			char label[MAXIMUM_LABEL_LENGTH + 1];
			jumpOp op1Type;
			char op1Label[MAXIMUM_LABEL_LENGTH + 1];
			int register1;
			int num1;
			jumpOp op2Type;
			char op2Label[MAXIMUM_LABEL_LENGTH + 1];
			int register2;
			int num2;
			int final_data : 15;
		} jump_data;
	} data;
} Operand;



/*
	Op struct is represent a full Op in the system, it contains the Operand struct and the sizes and addresssing for the whole line
	and not only one parameter like Operand struct
*/
typedef struct Op {
	char* name;
	int operands;
	int allowed_src_addressing;
	int allowed_dst_addressing;
	int op_code;
	Operand src;
	Operand dst;
	int binary_size;
} Op;

/*
	OpData holds all the operatinos in the file (we parsed them and build this table)
*/
typedef struct OpData {
	Op* operationsTable;
	int operationsCounter;
	int op_capacity;
} OpData;

#endif
