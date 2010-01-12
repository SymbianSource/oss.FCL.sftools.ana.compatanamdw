/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies). 
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  Main entry of LibraryAnalyser 
*
*/


#include "la.hpp"

// init globals
bool _cl_use_gcc = false;
bool _cl_use_gcce = false;
bool _cl_use_rvct = false;
bool _cl_use_libs = false;
bool _cl_print_debug = false;

string _cl_baselinelibdir = "";
string _cl_currentlibdir = "";
string _cl_baselineversion = "";
string _cl_currentversion = "";
string _cl_reportfile = "";
string _cl_toolsdir = "";
string _cl_tempdir = "";
string _cl_cfiltloc = "";
string _cl_set = "";
string _cl_baselinedlldir = "";
string _cl_currentdlldir = "";

string _gcc_nm_location = "";
string _gcce_nm_location = "";
string _gcce_readelf_location = "";
string _gcce_cfilt_location = "";
string _rvct_armar_location = "";
string _rvct_fromelf_location = "";
string _rvct_cfilt_location = "";
string _petran_location = "";
string _dumpsis_location = "";
string _tempfile_location = "";
string _lib_extension = "";
string _toolchain_name = "";
string _baselinedllfile = "";
string _currentdllfile = "";

vector<string> _lib_files_baseline;
vector<string> _lib_files_current;

vector<string> _lib_dirs_baseline;
vector<string> _lib_dirs_current;
vector<string> _dll_dirs_baseline;
vector<string> _dll_dirs_current;

vector<dll_issue> _dll_issuelist;

ofstream _reportf; 
struct tm* _timenow;

int _CRT_glob = 0; // globbing not supported

// ----------------------------------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    // parse command line arguments
    ParseCommandLineParameters(argc, argv);
    
    // init the environment
    DoInitialChecksAndPreparations();
    
    // get list of .lib / .dso files
    GetListsOfImportLibraries();
    
    // filter import library lists based on -set parameter
    FilterListsOfImportLibraries();
    
    // do more checks before starting the actual analysis
    DoPreAnalysisChecks();

    GetDllDataFiles();

    // write header of the report
    WriteReportHeader();

    // generate issue list and write it to the report
    GenerateAndWriteIssueList();
    
    // write footer of the report
    WriteReportFooter();
    
    // do some final tasks before we can quit
    DoFinalTasks();
 
	return EXIT_NORMAL;
}

// ----------------------------------------------------------------------------------------------------------

