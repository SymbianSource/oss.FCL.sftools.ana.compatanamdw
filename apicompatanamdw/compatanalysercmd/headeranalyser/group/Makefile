#
# Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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

XERCESHOME = C:/Apps/xerces-c-src_2_7_0
BOOSTHOME = C:/APPS/boost_1_33_1

CPP  = g++
CC   = gcc
RES  = 
OBJ  = ../obj/Analyser.o ../obj/BBCFileUtils.o ../obj/CommandFile.o ../obj/CommandLine.o ../obj/CPPParser.o ../obj/HAException.o ../obj/XMLStringConst.o ../obj/XMLModuleErrorHandler.o ../obj/Utils.o ../obj/XMLUtils.o ../obj/ReportGenerator.o ../obj/Issues.o ../obj/AnalyserParams.o ../obj/BBCAnalyser.o ../obj/HANodeIterator.o ../obj/ReportIssue.o ../obj/NodeIndex.o ../obj/MacroAnalyser.o ../obj/ha.o ../obj/NodeTypeComparator.o ../obj/PlatformData.o $(RES)
LINKOBJ  = ../obj/Analyser.o ../obj/BBCFileUtils.o ../obj/CommandFile.o ../obj/CommandLine.o ../obj/CPPParser.o ../obj/HAException.o ../obj/XMLStringConst.o ../obj/XMLModuleErrorHandler.o ../obj/Utils.o ../obj/XMLUtils.o ../obj/ReportGenerator.o ../obj/Issues.o ../obj/AnalyserParams.o ../obj/BBCAnalyser.o ../obj/HANodeIterator.o ../obj/ReportIssue.o ../obj/NodeIndex.o ../obj/MacroAnalyser.o ../obj/ha.o ../obj/NodeTypeComparator.o ../obj/PlatformData.o $(RES)
LIBS = -L$(XERCESHOME)/lib -lxerces-c $(BOOSTHOME)/lib/boost_thread-gcc-mt-1_33_1.lib
INCS =  -I$(XERCESHOME)/src -I$(BOOSTHOME)
CXXINCS =  -I$(XERCESHOME)/src -I$(BOOSTHOME)
BIN  = ../bin/ha
CXXFLAGS = $(CXXINCS) 
CFLAGS = $(INCS)
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before ../bin/ha all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "../bin/ha" $(LIBS)

../obj/BBCAnalyser.o: ../src/BBCAnalyser.cpp
	$(CPP) -c ../src/BBCAnalyser.cpp -o ../obj/BBCAnalyser.o $(CXXFLAGS)

../obj/BBCFileUtils.o: ../src/BBCFileUtils.cpp
	$(CPP) -c ../src/BBCFileUtils.cpp -o ../obj/BBCFileUtils.o $(CXXFLAGS)

../obj/Analyser.o: ../src/Analyser.cpp
	$(CPP) -c ../src/Analyser.cpp -o ../obj/Analyser.o $(CXXFLAGS)

../obj/AnalyserParams.o: ../src/AnalyserParams.cpp
	$(CPP) -c ../src/AnalyserParams.cpp -o ../obj/AnalyserParams.o $(CXXFLAGS)

../obj/CommandFile.o: ../src/CommandFile.cpp
	$(CPP) -c ../src/CommandFile.cpp -o ../obj/CommandFile.o $(CXXFLAGS)

../obj/CommandLine.o: ../src/CommandLine.cpp
	$(CPP) -c ../src/CommandLine.cpp -o ../obj/CommandLine.o $(CXXFLAGS)

../obj/CPPParser.o: ../src/CPPParser.cpp
	$(CPP) -c ../src/CPPParser.cpp -o ../obj/CPPParser.o $(CXXFLAGS)

../obj/HAException.o: ../src/HAException.cpp
	$(CPP) -c ../src/HAException.cpp -o ../obj/HAException.o $(CXXFLAGS)

../obj/XMLModuleErrorHandler.o: ../src/XMLModuleErrorHandler.cpp
	$(CPP) -c ../src/XMLModuleErrorHandler.cpp -o ../obj/XMLModuleErrorHandler.o $(CXXFLAGS)

../obj/Utils.o: ../src/Utils.cpp
	$(CPP) -c ../src/Utils.cpp -o ../obj/Utils.o $(CXXFLAGS)

../obj/ReportGenerator.o: ../src/ReportGenerator.cpp
	$(CPP) -c ../src/ReportGenerator.cpp -o ../obj/ReportGenerator.o $(CXXFLAGS)

../obj/XMLModule.o: ../src/XMLModule.cpp
	$(CPP) -c ../src/XMLModule.cpp -o ../obj/XMLModule.o $(CXXFLAGS)

../obj/XMLStringConst.o: ../src/XMLStringConst.cpp
	$(CPP) -c ../src/XMLStringConst.cpp -o ../obj/XMLStringConst.o $(CXXFLAGS)

../obj/XMLUtils.o: ../src/XMLUtils.cpp
	$(CPP) -c ../src/XMLUtils.cpp -o ../obj/XMLUtils.o $(CXXFLAGS)

../obj/Issues.o: ../src/Issues.cpp
	$(CPP) -c ../src/Issues.cpp -o ../obj/Issues.o $(CXXFLAGS)

../obj/ReportIssue.o: ../src/ReportIssue.cpp
	$(CPP) -c ../src/ReportIssue.cpp -o ../obj/ReportIssue.o $(CXXFLAGS)

../obj/HANodeIterator.o: ../src/HANodeIterator.cpp
	$(CPP) -c ../src/HANodeIterator.cpp -o ../obj/HANodeIterator.o $(CXXFLAGS)

../obj/NodeIndex.o: ../src/NodeIndex.cpp
	$(CPP) -c ../src/NodeIndex.cpp -o ../obj/NodeIndex.o $(CXXFLAGS)

../obj/MacroAnalyser.o: ../src/MacroAnalyser.cpp
	$(CPP) -c ../src/MacroAnalyser.cpp -o ../obj/MacroAnalyser.o $(CXXFLAGS)

../obj/ha.o: ../src/ha.cpp
	$(CPP) -c ../src/ha.cpp -o ../obj/ha.o $(CXXFLAGS)

../obj/NodeTypeComparator.o: ../src/NodeTypeComparator.cpp
	$(CPP) -c ../src/NodeTypeComparator.cpp -o ../obj/NodeTypeComparator.o $(CXXFLAGS)

../obj/PlatformData.o: ../src/PlatformData.cpp
	$(CPP) -c ../src/PlatformData.cpp -o ../obj/PlatformData.o $(CXXFLAGS)
