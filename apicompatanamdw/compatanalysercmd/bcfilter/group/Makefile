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

XERCESHOME = C:/Apps/xerces-c-src_2_7_0

CPP  = g++
CC   = gcc
RES  = 
OBJ  = ../obj/bcfilter.o $(RES)
LINKOBJ  = ../obj/bcfilter.o $(RES)
LIBS = -L$(XERCESHOME)/lib -lxerces-c  
INCS =  -I$(XERCESHOME)/src -I../inc
CXXINCS =  -I$(XERCESHOME)/src -I../inc
BIN  = ../bin/bcfilter
CXXFLAGS = $(CXXINCS)  
CFLAGS = $(INCS)  
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before ../bin/bcfilter all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "../bin/bcfilter" $(LIBS)

../obj/bcfilter.o: ../src/bcfilter.cpp
	$(CPP) -c ../src/bcfilter.cpp -o ../obj/bcfilter.o $(CXXFLAGS)
