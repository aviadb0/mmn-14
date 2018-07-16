cmake_minimum_required(VERSION 3.10)
project(mmn14 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(mmn14
        constants.h
        Entry.h
        EntryUtils.c
        EntryUtils.h
        Extern.h
        ExternLocationCalculator.c
        ExternLocationCalculator.h
        FileContextDefenition.c
        FileContextDefenition.h
        FileContextUtils.c
        FileContextUtils.h
        FileUtils.c
        FileUtils.h
        GeneralUtils.c
        GeneralUtils.h
        IntUtils.c
        IntUtils.h
        LineUtils.c
        LineUtils.h
        LogUtils.c
        LogUtils.h
        main.c
        OperationData.h
        Parser.c
        Parser.h
        SmallComponentDefenitions.h
        Symbol.h
        WordsGenerator.c
        WordsGenerator.h)
