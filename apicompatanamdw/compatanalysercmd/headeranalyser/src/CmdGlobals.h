/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description:  Global defines
*
*/


#ifndef __CMD_GLOBALS__
#define __CMD_GLOBALS__

// Program parameter defines
#define BASELINE "baseline"
#define CURRENT "current"
#define BASELINEDIR "baselinedir"
#define CURRENTDIR "currentdir"
#define REPORTFILE "reportfile"
#define BASELINEVERSION "baselineversion"
#define CURRENTVERSION "currentversion"
#define COMMANDFILE "commandfile"
#define RECURSIVE "recursive"
#define EPOCROOT "epocroot"
#define FNPARENTNODENAME "headerfilenames"
#define FNNODENAME "headerfile"
#define FILEREPLACE "replace"
#define BASELINEPLAT "baseplatformheaders"
#define CURRENTPLAT "currentplatformheaders"
#define BUNDLESIZE "bundlesize"
#define TEMPDIR "temp"
#define HEADERSET "set"
#define BASEFORCEDHEADERSFILE "forcebaseinclude"
#define CURRENTFORCEDHEADERSFILE "forcecurrentinclude"
#define DOCURL "docurl"
#define DISCARDDIRS "excludedirs"
#define BASEPLATFORMDATA "baseplatformdata"
#define CURRENTPLATFORMDATA "currentplatformdata"
#define USETHREAD "usethread"

#define RH_EXTENSION ".rh"
#define WILDCARD_DEFAULT "*.h;*.hrh;*.rsg;*.mbg;*.hpp;*.pan;*.rh"

#define TRIMXML "trimxml"
#if defined(_DEBUG) || defined(DEBUG)
#define COMMANDLINETEST "cmdtest"
#endif

#define MAX_THREAD_COUNT 3
#define MAX_THREAD_COUNT2 3
#define PLATFORM_BUNDLESIZE 20

#define PREPROCESS_BUFFERSIZE 5000000
// Maximum bundle size
#define MAX_BUNDLESIZE        9999
// Warning size of bundle
#define BUNDLESIZE_WARNING    100
#define STR_ATTRIBUTE_STR "__attribute((gccxml(\"exported\")))"


// uncomment USE_INCLUDED_GCC_DISTRIBUTION if you want to use a GCCXML distribution that 
// is found in the working directory
//#define USE_INCLUDED_GCC_DISTRIBUTION

// uncomment USE_CUSTOM_GCC_DISTRIBUTION if you want to use a GCCXML distribution that
// is found from PATH environment variable
#define USE_CUSTOM_GCC_DISTRIBUTION

//#define PROCESS_MULTIPLE

// Which environment we're compiling for
#if defined(_WIN32) || defined(WIN32)
#define __WIN__
#define DIR_SEPARATOR '\\'
#define WILDCARD_ALLFILES "*.*"
#define XMLCHAR XMLCh
#define XMLLITERAL(a) (const XMLCh*)a

#define ANALYSER_REPORT_DIR_SIZE 2
#define ANALYSER_HEADER_MAX_LENGTH 3
#define ANALYSER_HEADER_SIZE 2

#define ACCESS _access
#define APPEND_DIR_SEPARATOR '\\\\'

#define GET_FULLY_QUALIFIED_NAME ret.second = KXMLClassString
#define TO_LOWER_CASE ret = strlwr(tempvar)
#define TO_UPPER_CASE ret = strupr(tempvar)
#define REMOVE_FILE_FUNCTION success = DeleteFile(file.c_str());\
        if (success == KErrorRemoveFailed){\
			unsigned long int errorcode = GetLastError();\
			if (errorcode != ERROR_FILE_NOT_FOUND){\
				notRemovedFiles.push_back(file);}}

#else
#define __UNIX__
#define DIR_SEPARATOR '/'
#define WILDCARD_ALLFILES "*"
#define XMLCHAR char
#define XMLLITERAL(a) a

#define ANALYSER_REPORT_DIR_SIZE 0
#define ANALYSER_HEADER_MAX_LENGTH 1
#define ANALYSER_HEADER_SIZE 0

#define ACCESS access
#define APPEND_DIR_SEPARATOR '/'

#define GET_FULLY_QUALIFIED_NAME  if (!GClassString)\
        {GClassString = XMLString::transcode(KXMLClassString);}\
        ret.second = GClassString

#define TO_LOWER_CASE for(unsigned int i = 0; i < len; i++)\
                      {tempvar[i] = std::tolower(tempvar[i]);}\
                        ret = tempvar

#define TO_UPPER_CASE for(unsigned int i = 0; i < len; i++)\
        {tempvar[i] = std::toupper(tempvar[i]);}\
         ret = tempvar
#define REMOVE_FILE_FUNCTION success = unlink(file.c_str());\
		 if (success == -1){\
			if (errno != ENOENT){\
				notRemovedFiles.push_back(file); }}

#define REMOVE_COMPILATION_ERROR_FILE string filename = "rm compilation_error.txt";\
		                              system(filename.c_str());
#endif

#ifdef __WIN__
#pragma warning(disable:4786)
#pragma warning(disable:4503)
#endif


#define PARSING_ERRORS_LETHAL

#define USE_CPP_HACK

#define APPEND_DIRECTORIES_TO_FILENAMES

enum parserstate 
{
    EStateSearching = 0,
    EStateReplacing,
    EStateReplaceDone
};

// Parameter types
// How parameters are set
enum parmtype
{
    EParmEnvironment = 0,
    EParmCommandFile,
    EParmCommandLine
};

// How to trim strings
enum trimtype
{
    ETrimNone = 0,
    ETrimWhitespaces = 1,
    ETrimNewlines = 2
};

#define STR_EXPORT_HACK "__THIS_IS_EXPORTED__"

#if (_MSC_VER >= 1300) && (WINVER < 0x0500)
//VC7 or later, building with pre-VC7 runtime libraries
extern "C" long _ftol( double ); //defined by VC6 C libs
extern "C" inline long _ftol2( double dblSource ) { return _ftol( dblSource ); }
#endif

#endif
