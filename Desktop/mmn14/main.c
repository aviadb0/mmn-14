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
		file = openFile(argv[i]);
		runAsmFile(file, argv[i]);
	}

	return 0;
}
