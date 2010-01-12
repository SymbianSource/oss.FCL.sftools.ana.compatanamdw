#
# Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
# This component and the accompanying materials are made available
# under the terms of the License "Eclipse Public License v1.0"
# which accompanies this distribution, and is available
# at the URL "http://www.eclipse.org/legal/epl-v10.html".
#
# Initial Contributors:
# Nokia Corporation - initial contribution.
#
# Contributors:
#
# Description: 
#

XERCESHOME = ./xerces-c-src

# All include directories must be listed here
# (normal GCC include directories, Xerces include directory, project's 
# include directory)
INCLUDES = -I $(INCLUDE) -I- -I $(XERCESHOME)/src -I .

# External libraries
# (normal GCC libs, Xerces libraries [should be build-dependent whether 
# to use debug or release libs])
# LIBS = -lxerces-c-src_2_7_0 

#LIBS= -lpthread

XLIBS=-L$(XERCESHOME)/lib -lxerces-c -lxerces-depdom

# C++ interpreter / linker to use, and all the required switches (library dirs)
CC = g++
CFLAGS = $(INCLUDES) $(LIBS) -Wall -DNO_DBG -fpermissive
#CFLAGS = $(INCLUDES) $(LIBS) -ggdb -Wall -D_DEBUG -DDEBUG -DNO_DBG
XCFLAGS = $(INCLUDES) $(XLIBS) -Wall -DNO_DBG -fpermissive
#XCFLAGS = $(INCLUDES) $(XLIBS) -ggdb -Wall -D_DEBUG -DDEBUG -DNO_DBG

# default output is an executable file called "ha". See 
# test.cpp for functional description.
default: HeaderAnalyser

HeaderAnalyser: Analyser.o BBCFileUtils.o CommandFile.o CommandLine.o CPPParser.o HAException.o XMLStringConst.o XMLModuleErrorHandler.o Utils.o XMLUtils.o ReportGenerator.o Issues.o AnalyserParams.o BBCAnalyser.o HANodeIterator.o ReportIssue.o NodeIndex.o MacroAnalyser.o Test.o
	$(CC) Analyser.o BBCFileUtils.o CommandFile.o CommandLine.o CPPParser.o HAException.o XMLStringConst.o XMLModuleErrorHandler.o Utils.o XMLUtils.o ReportGenerator.o Issues.o AnalyserParams.o BBCAnalyser.o HANodeIterator.o ReportIssue.o NodeIndex.o MacroAnalyser.o Test.o $(XCFLAGS) -o ha 

BBCAnalyser.o: BBCAnalyser.h BBCAnalyser.cpp
	$(CC) $(CFLAGS) -c BBCAnalyser.cpp

BBCFileUtils.o: BBCFileUtils.cpp BBCFileUtils.h
	$(CC) $(CFLAGS) -c BBCFileUtils.cpp

Analyser.o: Analyser.cpp Analyser.h CPPParser.h CommandLine.h CmdGlobals.h CommandFile.h BBCFileUtils.h HAException.h
	$(CC) $(CFLAGS) -c Analyser.cpp

AnalyserParams.o: AnalyserParams.h AnalyserParams.cpp
	$(CC) $(CFLAGS) -c AnalyserParams.cpp

CommandFile.o: CommandFile.cpp CommandFile.h
	$(CC) $(CFLAGS) -c CommandFile.cpp

CommandLine.o: CommandLine.cpp CommandLine.h HAException.h CmdGlobals.h CommandFile.h
	$(CC) $(CFLAGS) -c CommandLine.cpp

CPPParser.o: CPPParser.cpp CPPParser.h XMLModuleErrorHandler.h HAException.h CmdGlobals.h
	$(CC) $(CFLAGS) -c CPPParser.cpp

HAException.o: HAException.cpp HAException.h
	$(CC) $(CFLAGS) -c HAException.cpp

XMLModuleErrorHandler.o: XMLModuleErrorHandler.cpp XMLModuleErrorHandler.h
	$(CC) $(CFLAGS) -c XMLModuleErrorHandler.cpp

Utils.o: Utils.cpp Utils.h
	$(CC) $(CFLAGS) -c Utils.cpp

ReportGenerator.o: ReportGenerator.h ReportGenerator.cpp
	$(CC) $(CFLAGS) -c ReportGenerator.cpp

XMLModule.o: XMLModule.h XMLModule.cpp
	$(CC) $(CFLAGS) -c XMLModule.cpp

XMLStringConst.o: XMLStringConst.h XMLStringConst.cpp
	$(CC) $(CFLAGS) -c XMLStringConst.cpp

XMLUtils.o: XMLUtils.h XMLUtils.cpp
	$(CC) $(CFLAGS) -c XMLUtils.cpp

Issues.o: Issues.h Issues.cpp
	$(CC) $(CFLAGS) -c Issues.cpp

ReportIssue.o: ReportIssue.h ReportIssue.cpp
	$(CC) $(CFLAGS) -c ReportIssue.cpp

HANodeIterator.o: HANodeIterator.h HANodeIterator.cpp
	$(CC) $(CFLAGS) -c HANodeIterator.cpp

NodeIndex.o: NodeIndex.h NodeIndex.cpp
	$(CC) $(CFLAGS) -c NodeIndex.cpp

MacroAnalyser.o: MacroAnalyser.h MacroAnalyser.cpp
	$(CC) $(CFLAGS) -c MacroAnalyser.cpp

Test.o: Test.cpp
	$(CC) $(CFLAGS) -c Test.cpp

clean:
	rm -f ha *.o *~
