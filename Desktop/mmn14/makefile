assembler: main.o FileUtils.o GeneralUtils.o FileContextUtils.o IntUtils.o LineUtils.o LogUtils.o EntryUtils.o ExternLocationCalculator.o FileContextDefenition.o Parser.o WordsGenerator.o
	gcc -g -ansi -Wall -pedantic main.o FileUtils.o GeneralUtils.o FileContextUtils.o IntUtils.o LineUtils.o LogUtils.o EntryUtils.o ExternLocationCalculator.o FileContextDefenition.o Parser.o WordsGenerator.o -o assembler

main.o: main.c FileUtils.h FileContextDefenition.h GeneralUtils.h
	gcc -c -ansi -Wall -pedantic main.c -o main.o

FileUtils.o: FileUtils.c FileUtils.h Parser.h EntryUtils.h WordsGenerator.h GeneralUtils.h IntUtils.h ExternLocationCalculator.h LogUtils.h
	gcc -c -ansi -Wall -pedantic FileUtils.c -o FileUtils.o
	
GeneralUtils.o: GeneralUtils.c GeneralUtils.h FileContextDefenition.h WordsGenerator.h FileUtils.h LogUtils.h Parser.h
	gcc -c -ansi -Wall -pedantic GeneralUtils.c -o GeneralUtils.o
	
FileContextUtils.o: FileContextUtils.c FileContextUtils.h
	gcc -c -ansi -Wall -pedantic FileContextUtils.c -o FileContextUtils.o
	
IntUtils.o: IntUtils.c IntUtils.h GeneralUtils.h
	gcc -c -ansi -Wall -pedantic IntUtils.c -o IntUtils.o
	
LineUtils.o: LineUtils.c LineUtils.h constants.h LogUtils.h GeneralUtils.h FileUtils.h
	gcc -c -ansi -Wall -pedantic LineUtils.c -o LineUtils.o
	
LogUtils.o: LogUtils.c LogUtils.h
	gcc -c -ansi -Wall -pedantic LogUtils.c -o LogUtils.o
	
EntryUtils.o: EntryUtils.c EntryUtils.h LogUtils.h
	gcc -c -ansi -Wall -pedantic -pedantic EntryUtils.c -o EntryUtils.o
	
ExternLocationCalculator.o: ExternLocationCalculator.c ExternLocationCalculator.h GeneralUtils.h WordsGenerator.h LogUtils.h
	gcc -c -ansi -Wall -pedantic ExternLocationCalculator.c -o ExternLocationCalculator.o

FileContextDefenition.o: FileContextDefenition.c FileContextDefenition.h
	gcc -c -ansi -Wall -pedantic FileContextDefenition.c -o FileContextDefenition.o
	
Parser.o: Parser.c LineUtils.h Parser.h FileContextUtils.h GeneralUtils.h LineUtils.h LogUtils.h
	gcc -c -ansi -Wall -pedantic Parser.c -o Parser.o
	
WordsGenerator.o: WordsGenerator.c WordsGenerator.h GeneralUtils.h
	gcc -c -ansi -Wall -pedantic WordsGenerator.c -o WordsGenerator.o

