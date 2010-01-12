#
# Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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

BOOSTHOME = C:\Apps\boost_1_33_1
XERCESHOME = C:\Apps\xerces-c-src_2_7_0

CPP  = g++
CC   = gcc
RES  = 
OBJ  = ../obj/la.o ../obj/la_analysis.o ../obj/la_functionanalysis.o ../obj/la_getters.o ../obj/la_otherfunc.o ../obj/la_utils.o ../obj/static_mutex.o ../obj/w32_regex_traits.o ../obj/icu.o ../obj/wc_regex_traits.o ../obj/usinstances.o ../obj/cpp_regex_traits.o ../obj/regex_traits_defaults.o ../obj/wide_posix_api.o ../obj/posix_api.o ../obj/fileiter.o ../obj/cregex.o ../obj/c_regex_traits.o ../obj/winstances.o ../obj/regex_raw_buffer.o ../obj/regex_debug.o ../obj/regex.o ../obj/instances.o $(RES)
LINKOBJ  = ../obj/la.o ../obj/la_analysis.o ../obj/la_functionanalysis.o ../obj/la_getters.o ../obj/la_otherfunc.o ../obj/la_utils.o ../obj/static_mutex.o ../obj/w32_regex_traits.o ../obj/icu.o ../obj/wc_regex_traits.o ../obj/usinstances.o ../obj/cpp_regex_traits.o ../obj/regex_traits_defaults.o ../obj/wide_posix_api.o ../obj/posix_api.o ../obj/fileiter.o ../obj/cregex.o ../obj/c_regex_traits.o ../obj/winstances.o ../obj/regex_raw_buffer.o ../obj/regex_debug.o ../obj/regex.o ../obj/instances.o $(RES)
LIBS = -L$(XERCESHOME)/lib -lxerces-c  
INCS = -I../inc -I$(BOOSTHOME) -I$(XERCESHOME)/src -I../inc
CXXINCS = -I../inc -I$(BOOSTHOME) -I$(XERCESHOME)/src -I../inc 
BIN  = ../bin/la
CXXFLAGS = $(CXXINCS) -pedantic -Wall -Wextra -Wno-long-long
CFLAGS = $(INCS) -std=c99 -pedantic -Wall -Wextra -Wno-long-long
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before ../bin/la all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "../bin/la" $(LIBS)

../obj/la.o: ../src/la.cpp
	$(CPP) -c ../src/la.cpp -o ../obj/la.o $(CXXFLAGS)

../obj/la_analysis.o: ../src/la_analysis.cpp
	$(CPP) -c ../src/la_analysis.cpp -o ../obj/la_analysis.o $(CXXFLAGS)

../obj/la_functionanalysis.o: ../src/la_functionanalysis.cpp
	$(CPP) -c ../src/la_functionanalysis.cpp -o ../obj/la_functionanalysis.o $(CXXFLAGS)

../obj/la_getters.o: ../src/la_getters.cpp
	$(CPP) -c ../src/la_getters.cpp -o ../obj/la_getters.o $(CXXFLAGS)

../obj/la_otherfunc.o: ../src/la_otherfunc.cpp
	$(CPP) -c ../src/la_otherfunc.cpp -o ../obj/la_otherfunc.o $(CXXFLAGS)

../obj/la_utils.o: ../src/la_utils.cpp
	$(CPP) -c ../src/la_utils.cpp -o ../obj/la_utils.o $(CXXFLAGS)

../obj/static_mutex.o: $(BOOSTHOME)/libs/regex/src/static_mutex.cpp
	$(CPP) -c $(BOOSTHOME)/libs/regex/src/static_mutex.cpp -o ../obj/static_mutex.o $(CXXFLAGS)

../obj/w32_regex_traits.o: $(BOOSTHOME)/libs/regex/src/w32_regex_traits.cpp
	$(CPP) -c $(BOOSTHOME)/libs/regex/src/w32_regex_traits.cpp -o ../obj/w32_regex_traits.o $(CXXFLAGS)

../obj/icu.o: $(BOOSTHOME)/libs/regex/src/icu.cpp
	$(CPP) -c $(BOOSTHOME)/libs/regex/src/icu.cpp -o ../obj/icu.o $(CXXFLAGS)

../obj/wc_regex_traits.o: $(BOOSTHOME)/libs/regex/src/wc_regex_traits.cpp
	$(CPP) -c $(BOOSTHOME)/libs/regex/src/wc_regex_traits.cpp -o ../obj/wc_regex_traits.o $(CXXFLAGS)

../obj/usinstances.o: $(BOOSTHOME)/libs/regex/src/usinstances.cpp
	$(CPP) -c $(BOOSTHOME)/libs/regex/src/usinstances.cpp -o ../obj/usinstances.o $(CXXFLAGS)

../obj/cpp_regex_traits.o: $(BOOSTHOME)/libs/regex/src/cpp_regex_traits.cpp
	$(CPP) -c $(BOOSTHOME)/libs/regex/src/cpp_regex_traits.cpp -o ../obj/cpp_regex_traits.o $(CXXFLAGS)

../obj/regex_traits_defaults.o: $(BOOSTHOME)/libs/regex/src/regex_traits_defaults.cpp
	$(CPP) -c $(BOOSTHOME)/libs/regex/src/regex_traits_defaults.cpp -o ../obj/regex_traits_defaults.o $(CXXFLAGS)

../obj/wide_posix_api.o: $(BOOSTHOME)/libs/regex/src/wide_posix_api.cpp
	$(CPP) -c $(BOOSTHOME)/libs/regex/src/wide_posix_api.cpp -o ../obj/wide_posix_api.o $(CXXFLAGS)

../obj/posix_api.o: $(BOOSTHOME)/libs/regex/src/posix_api.cpp
	$(CPP) -c $(BOOSTHOME)/libs/regex/src/posix_api.cpp -o ../obj/posix_api.o $(CXXFLAGS)

../obj/fileiter.o: $(BOOSTHOME)/libs/regex/src/fileiter.cpp
	$(CPP) -c $(BOOSTHOME)/libs/regex/src/fileiter.cpp -o ../obj/fileiter.o $(CXXFLAGS)

../obj/cregex.o: $(BOOSTHOME)/libs/regex/src/cregex.cpp
	$(CPP) -c $(BOOSTHOME)/libs/regex/src/cregex.cpp -o ../obj/cregex.o $(CXXFLAGS)

../obj/c_regex_traits.o: $(BOOSTHOME)/libs/regex/src/c_regex_traits.cpp
	$(CPP) -c $(BOOSTHOME)/libs/regex/src/c_regex_traits.cpp -o ../obj/c_regex_traits.o $(CXXFLAGS)

../obj/winstances.o: $(BOOSTHOME)/libs/regex/src/winstances.cpp
	$(CPP) -c $(BOOSTHOME)/libs/regex/src/winstances.cpp -o ../obj/winstances.o $(CXXFLAGS)

../obj/regex_raw_buffer.o: $(BOOSTHOME)/libs/regex/src/regex_raw_buffer.cpp
	$(CPP) -c $(BOOSTHOME)/libs/regex/src/regex_raw_buffer.cpp -o ../obj/regex_raw_buffer.o $(CXXFLAGS)

../obj/regex_debug.o: $(BOOSTHOME)/libs/regex/src/regex_debug.cpp
	$(CPP) -c $(BOOSTHOME)/libs/regex/src/regex_debug.cpp -o ../obj/regex_debug.o $(CXXFLAGS)

../obj/regex.o: $(BOOSTHOME)/libs/regex/src/regex.cpp
	$(CPP) -c $(BOOSTHOME)/libs/regex/src/regex.cpp -o ../obj/regex.o $(CXXFLAGS)

../obj/instances.o: $(BOOSTHOME)/libs/regex/src/instances.cpp
	$(CPP) -c $(BOOSTHOME)/libs/regex/src/instances.cpp -o ../obj/instances.o $(CXXFLAGS)
