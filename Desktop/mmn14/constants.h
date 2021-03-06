#ifndef CONSTANTS_DEFENITION_H
#define CONSTANTS_DEFENITION_H

/*
	This is the main constants defenition of the project
	all the constants related to the project is here
*/

#define AS_SUFFIX ".as"
#define ARE_ABSOLUTE 0
#define ARE_EXTERNAL 1
#define ARE_RELOCATABLE 2
#define ADDR_IMMEDIATE 0
#define ADDRESSING_BIT_WIDTH 2
#define ARE_BIT_WIDTH 2
#define ADDR_MEMORY 1
#define ADDRESSING_NONE none
#define ADD_OPERATION "add"
#define ADDR_MATRIX 2
#define ADDR_REGISTER 3
#define ADDRESSING_ALL immediate | memory | matrix | regist
#define BASE4_FIRST_TWO_DIGIT 4
#define BASE_MEM_ADDR 100
#define BASE4_ZERO_VALUE 'a'
#define BITS_IN_BYTE 8
#define BNE_OPERATION "bne"
#define BOTH_REGIST 2
#define BACKSLASH_T '\t'
#define BACKSLACH_ZERO '\0'
#define BACKSLASH '\"'
#define CLR_OPERATION "clr"
#define COMMENT_CHAR ';'
#define CMP_OPERATION "cmp"
#define DOT '.'
#define DEFAULT_MATRIX_VALUE 0
#define DEC_OPERATION "dec"
#define DATA_SYMBOL_START ".data"
#define DATA_SYMBOL_START_SEPERATOR ','
#define EXTERN_SYMBOL_START ".extern"
#define ENT_SUFFIX ".ent"
#define ENTRY_SYMBOL_START ".entry"
#define ENTER '\n'
#define EXT_SUFFIX ".ext"
#define FALSE 0
#define INITIAL_CAPACITY 8
#define IMMEDIATE "immediate"
#define INC_OPERATION "inc"
#define IMMEDIATE_CHAR '#'
#define JUMP_START '('
#define JUMP_END ')'
#define JMP_OPERATION "jmp"
#define JSR_OPERATION "jsr"
#define JUMP_PARAMETERS 2
#define JUMP "jump"
#define LABEL_END ':'
#define LEA_OPERATION "lea"
#define MAXIMUM_DATA_LENGTH 8191
#define MEM_WORD_BITS 10
#define MAX_LINE 80
#define MAX_OP_LEN 4
#define MOV_OPERATION "mov"
#define MAXIMUM_LABEL_LENGTH 31
#define MAXIMUM_OPERATION_LENGTH 80
#define MAXIMUM_DATA_NUMBER -8192
#define MAX_BASE4_INT_LEN 5
#define MINIMUM_NUMBER -8192
#define MAXIMUM_NUMBER 8191
#define MEMORY "memory"
#define MATRIX "matrix"
#define MAZ_AMOUNT_CODE_LINES 25
#define MAX_BASE4_VALUE 1023
#define MATRIX_SYMBOL_START ".mat"
#define MEMORY_REGISTER_MATRIX memory | regist | matrix
#define MINUS '-'
#define MATRIX_DIMENSION_START '['
#define MATRIX_DIMENSION_END ']'
#define MINUS_CHAR '-'
#define NOT_OPERATION "not"
#define OB_SUFFIX ".ob"
#define OUTPUT_BASE 4
#define OPCODE_BIT_WIDTH 4
#define OPERAND_DELIM ','
#define PLUS '+'
#define PLUS_CHAR '+'
#define PRN_OPERATION "prn"
#define RTS_OPERATION "rts"
#define REGISTER "register"
#define REGISTER_MIN '0'
#define REGISTER_CHAR 'r'
#define REGISTER_LEN 2
#define REGISTER_MAX '7'
#define RED_OPERATION "red"
#define REGISTER_BIT_WIDTH 4
#define SUB_OPERATION "sub"
#define STRING_SYMBOL_START ".string"
#define STOP_OPERATION "stop"
#define TRUE 1
#define TYPE_UNKNOWN -1
#define UNK "unknown"
#define WRITE "w"

#endif
