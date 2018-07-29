/*
 * This program is an assembler, which compiles files written in assembly
 * to machine code represented in weird 2 base.
 *
 * This is a solution for maman 14, in the course "lab in system
 * programming", semester 2018B
 *
 * Written by:
 *		I. Moti David ID 204399422 
 *		II. Aviad Brown, ID: 308401447
 * 
 *
 * July 2018
 */



#include <stdio.h>
#include <stdlib.h>

#include "FileUtils.h"
#include "FileContextDefenition.h"
#include "GeneralUtils.h"

int main(int argc, char** argv)
{
        int i;
	if (argc < 2) {
		fprintf(stderr, "argument is missing..\n");
		return 1;
	}

	fprintf(stderr, "Start parsing files..\n");
	for (i = 1; i < argc; i++) 
	{
	        FILE* file;
		fprintf(stderr, "Path: %s\n", argv[i]);
		if (!(file = openFile(argv[i])))
			continue; /* cant open file */
		runAsmFile(file, argv[i]); /* parse the file */
	}

	return 0;
}
