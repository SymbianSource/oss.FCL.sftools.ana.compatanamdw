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
* Description:  Header file of LibraryAnalyser
*
*/


#ifndef __LA_HPP__
#define __LA_HPP__


#if (defined(_MSC_VER) && (_MSC_VER < 1400))
  #error "ERROR: Minimum supported version of Visual C++ is 8.0 (2005)."
#endif

#ifdef _MSC_VER
  #pragma message("IMPORTANT: You can use Visual C++ to aid development, but please compile the releasable executable with MinGW/MSYS !!!")
  #pragma warning(disable:4267) // 'var' : conversion from 'size_t' to 'type', possible loss of data
  #pragma warning(disable:4996) // 'function': was declared deprecated
  #define _CRT_SECURE_NO_DEPRECATE
  #ifndef WIN32
    #error "ERROR: Only Win32 target supported!"
  #endif
#endif


#include <algorithm>
#include <string>
#include <cctype>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <time.h>
#include <sys/stat.h>
#include <stdio.h>
#include <boost/regex.hpp>

#ifdef _MSC_VER
  #include <direct.h>
  #define S_ISDIR(m)  ((m) & S_IFDIR)
#else
  #include <dirent.h>
#endif

using namespace std;

#define LA_VERSION "3.3.3"
#define LA_DATE "15th February 2010"
#define LA_REPORT_FORMAT_VERSION "1.1"
#define TEMP_FILENAME "la-temp.txt"
#define REPORT_TAB_CHAR '\t'

#ifdef WIN32
  #define DIR_SEPARATOR "\\"
  #define DIR_SEPARATOR2 '\\'
  #define GCC_NM_EXE "nm.exe"
  #define GCCE_NM_EXE "arm-none-symbianelf-nm.exe"
  #define GCCE_READELF_EXE "arm-none-symbianelf-readelf.exe"
  #define GCCE_CFILT_EXE "arm-none-symbianelf-c++filt.exe"
  #define RVCT_ARMAR_EXE "armar.exe"
  #define RVCT_FROMELF_EXE "fromelf.exe"
  #define CERR_TO_NULL "2>NUL"
  #define DIR_COMMAND "dir /b"
#else
  #define DIR_SEPARATOR "/"
  #define DIR_SEPARATOR2 '/'
  #define GCC_NM_EXE "nm"
  #define GCCE_NM_EXE "arm-none-symbianelf-nm"
  #define GCCE_READELF_EXE "arm-none-symbianelf-readelf"
  #define GCCE_CFILT_EXE "arm-none-symbianelf-c++filt"
  #define RVCT_ARMAR_EXE "armar"
  #define RVCT_FROMELF_EXE "fromelf"
  #define CERR_TO_NULL "2>/dev/null"
  #define DIR_COMMAND "ls --format=single-column"
  #define _mkdir(X) mkdir(X, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
  #define _rmdir rmdir
  #define _unlink unlink
  #define _popen popen
  #define _pclose pclose
#endif


enum ReportIssues 
{
    ISSUE_ONLY_IN_BASELINEDIR = 1,
    ISSUE_ONLY_IN_CURRENTDIR,
    ISSUE_MOVED,
    ISSUE_REMOVED,
    ISSUE_INSERTED,
    ISSUE_MODIFIED,
    ISSUE_ADDED,
	DLL_TARGET_TYPE_CHANGED,
	DLL_UID2_CHANGED,
	DLL_UID3_CHANGED,
	DLL_SID_CHANGED,
  	DLL_CAPABILITY_CHANGED,
	DLL_CURRENT_MISSING,
    DLL_BASELINE_MISSING
};

enum TypeOfSeverity
{
	CONFIRMED_BC_BREAK = 1,
	POSSIBLE_BC_BREAK,
	CONFIRMED_SC_BREAK,
	POSSIBLE_SC_BREAK,
	CONFIRMED_BC_AND_SC_BREAK,
	POSSIBLE_BC_SC_BREAK,
	CONFIRMED_BC_POSSIBLE_SC_BREAK,
	POSSIBLE_BC_CONFIRMED_SC_BREAK,
	BC_INFORMATIVE,
	SC_INFORMATIVE,
	BC_SC_INFORMATIVE,
	NO_BREAK
};

enum ExitStates 
{
    EXIT_NORMAL = 0,
    EXIT_INVALID_ARGUMENT,
    EXIT_WRONG_USAGE,
    EXIT_BASELINEDIR_NOT_FOUND,
    EXIT_CURRENTDIR_NOT_FOUND,
    EXIT_TOOLCHAIN_NOT_FOUND_FROM_PATH,
    EXIT_PATH_VARIABLE_NOT_FOUND,
    EXIT_TEMP_VARIABLE_NOT_FOUND,
    EXIT_TEMP_DIRECTORY_DOES_NOT_EXIST,
    EXIT_ONLY_SUPPORTED_IN_WIN32,
    EXIT_TOOLCHAIN_NOT_FOUND,
    EXIT_CFILT_NOT_FOUND,
    EXIT_CANNOT_WRITE_TO_TEMP_FILE,
    EXIT_SET_FILE_NOT_FOUND,
    EXIT_CANNOT_OPEN_SET_FILE,
    EXIT_CANNOT_WRITE_TO_REPORT_FILE,
    EXIT_GCC_NOT_SUPPORTED,
	  EXIT_CANNOT_OPEN_FILE,
	  EXIT_BASELINEDLLDIR_NOT_FOUND,
    EXIT_CURRENTDLLDIR_NOT_FOUND
};


struct ordinal
{
    unsigned int funcpos;
    string funcname;
    
    ordinal(unsigned int fp, string fn) 
    {
       funcpos = fp;
       funcname = fn;
    }
};

struct issue
{
    unsigned int i_typeid;
    string i_funcname;
    string i_newfuncname;
    unsigned int i_funcpos;
    unsigned int i_newfuncpos;
	string i_BC_severity;
	string i_SC_severity;
	
};

struct dll_issue
{
	string l_dllname;
	vector<unsigned int> i_list_typeid;
};


// global variables
extern bool _cl_use_gcc;
extern bool _cl_use_gcce;
extern bool _cl_use_rvct;
extern bool _cl_use_libs;
extern bool _cl_print_debug;

extern string _cl_baselinelibdir;
extern string _cl_currentlibdir;
extern string _cl_baselineversion;
extern string _cl_currentversion;
extern string _cl_reportfile;
extern string _cl_toolsdir;
extern string _cl_tempdir;
extern string _cl_cfiltloc;
extern string _cl_set;
extern string _cl_baselinedlldir;
extern string _cl_currentdlldir;

extern string _gcc_nm_location;
extern string _gcce_nm_location;
extern string _gcce_readelf_location;
extern string _gcce_cfilt_location;
extern string _rvct_armar_location;
extern string _rvct_fromelf_location;
extern string _rvct_cfilt_location;
extern string _tempfile_location;
extern string _lib_extension;
extern string _toolchain_name;
extern string _baselinedllfile;
extern string _currentdllfile;

extern vector<string> _lib_files_baseline;
extern vector<string> _lib_files_current;
extern vector<string> _lib_dirs_baseline;
extern vector<string> _lib_dirs_current;
extern vector<string> _dll_dirs_baseline;
extern vector<string> _dll_dirs_current;
extern vector<dll_issue> _dll_issuelist;

#define DLL_ENTRY_SIZE 5
#define UID1_OFFSET           0x00
#define UID2_OFFSET           0x04
#define UID3_OFFSET           0x08
#define SID_OFFSET            0x80
#define CAPABILITY_OFFSET     0x88


extern ofstream _reportf; 
extern struct tm* _timenow;

// from oc_otherfunc.cpp
void ParseCommandLineParameters(int argc, char* argv[]);
void ShowCommandLineOptionsAndExit();
void DoInitialChecksAndPreparations();
void GetListsOfImportLibraries();
void FilterListsOfImportLibraries();
void DoPreAnalysisChecks();
void GetToolsPathFromEnvironmentVariable();
void GetTempPathFromEnvironmentVariable();
void GetFileNamesFromDirectory(const vector<string>& directory, const string& filter, vector<string>& resultset);
void DoFinalTasks();
void CreateDllDataFile(string dllDataFile, vector<string>& dllPath, string type);
void GetDllDataFiles();
    
// from oc_utils.cpp
void MakeSureTrailingDirectoryMarkerExists(string& path);
bool FileExists(const string& path);
bool DirectoryExists(const string& path);
bool RemoveFile(const string& path);
string LowerCase(const string& s);
string Int2Str(int value);
int Str2Int(const string& s);
void MkDirAll(const string& path);
string& TrimRight(string& s);
string& TrimLeft(string& s);
string& TrimAll(string& s);
int StringICmp(const string& s1, const string& s2);
int StringICmpFileNamesWithoutExtension(const string& s1, const string& s2);
void InsertQuotesToFilePath(string& s);
bool ExecuteCommand(const string& command, vector<string>& resultset);
const string getFilename( const string& path);
vector<string> splitString(const string& str, char separator);
const string getPlatform(const string& path);
string CharToHex(char* buf);
string HexValueAt(fstream& f, const int offset);

// from oc_getters.cpp
void GetSymbolTableWithNM(const string& nm_location, const string& lib_directory, vector<string>& symbol_table);
void GetSymbolTableWithReadelf(const string& readelf_location, const string& cfilt_location, const string& lib_directory, vector<string>& symbol_table);
void GetSymbolTableWithArmar(const string& armar_location, const string& cfilt_location, const string& lib_directory, vector<string>& symbol_table);
void GetSymbolTableWithFromelf(const string& fromelf_location, const string& cfilt_location, const string& lib_directory, vector<string>& symbol_table);
void ConvertOrdinalListIntoSymbolTable(const vector<ordinal>& ordinals, vector<string>& symbol_table, const string& lib_path);
void DemangleOrdinalsInSymbolTable(const string& cfilt_location, vector<string>& symbol_table);
bool OrdinalCompare(const ordinal& left, const ordinal& right);

// from oc_analysis.cpp
void WriteReportHeader();
void GenerateAndWriteIssueList();
void WriteReportFooter();
void AppendToIssueListCaseMoved(vector<issue>& issueList, const string& funcname, int funcpos, int newfuncpos,TypeOfSeverity severity);
void AppendToIssueListCaseRemoved(vector<issue>& issueList, const string& funcname, int funcpos,TypeOfSeverity severity);
void AppendToIssueListCaseInserted(vector<issue>& issueList, const string& newfuncname, int newfuncpos,TypeOfSeverity severity);
void AppendToIssueListCaseModified(vector<issue>& issueList, const string& funcname, const string& newfuncname, int funcpos,TypeOfSeverity severity);
void AppendToIssueListCaseAdded(vector<issue>& issueList, const string& newfuncname, int newfuncpos,TypeOfSeverity severity);
bool IssueCompare(const issue& left, const issue& right);
void WriteXMLLineOpenClosed(ofstream& f, unsigned int tabstops, const string& element, const string& data);
void WriteXMLLineOpeningTag(ofstream& f, unsigned int tabstops, const string& element);
void WriteXMLLineClosingTag(ofstream& f, unsigned int tabstops, const string& element);
void WriteXMLIssueOnlyInBaselineDir(ofstream& f, const string& libname, dll_issue& dllIssue);
void WriteXMLIssueOnlyInCurrentDir(ofstream& f, const string& libname);
void WriteIssueListToXML(ofstream& f, const string& libname, const string& curlibname,vector<issue>& issue_list, dll_issue& dllIssue);

// from oc_functionanalysis.cpp
TypeOfSeverity AreFunctionsCompatible(const string& baselineFunc, const string& currentFunc);
void getSeverityString(TypeOfSeverity severity, string& bc_severity, string& sc_severity);

//------------------------------------ For executable analysis -------------------------------------------- 
//file parsing and comparison between baseline and current xml file with executable info
void ParseAndCompareDLLXmlFiles(const string& abaselineXmlFile,const string& acurrentXmlFile,
								vector<string> lib_files_baseline);

//Function to fill Executable issue with name and typeid corresponding to feature breaks ( i.e UID1,UID2,UID3,SID,capability)
void fillDllIssue ( char* dllMember ,  unsigned int& typeId);

//Function to initialize struct exe_issue
void intializeDllIssue(dll_issue& aIssue);

// Function to parse hex value and change it to decimal value (unsigned long)
int parseHex(const char* hex);

// Get DLL break type info in a string depending on type id
string GetDllBreakTypeInfoString(int typeID);


#endif // __LA_HPP__
