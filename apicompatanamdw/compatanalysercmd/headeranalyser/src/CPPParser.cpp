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
* Description:  
*
*/
#include <stdio.h>

#include <stdlib.h>
#include "CmdGlobals.h"
#ifdef __WIN__
#include <windows.h>
#include <direct.h>
#else
#include <errno.h>
#endif


#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include "CPPParser.h"
#include "XMLModuleErrorHandler.h"
#include "HAException.h"
#include "BBCFileUtils.h"
#include "Utils.h"
#include "XMLUtils.h"

XERCES_CPP_NAMESPACE_USE

const int KMaxFilenameLength = 512;
const int KMaxDirLength=1024;

// The C++ parser executable
#ifdef __WIN__
static const char* GCCXML_COMMAND = "ha_gccxml_cc1plus ";
#else
static const char* GCCXML_COMMAND = "./ha_gccxml_cc1plus ";
#endif

// Parameters to parser 
// 
//static const char* GCCXML_DEFINE = " -D_DEBUG -D__wchar_t=wchar_t -D_UNICODE -D__SYMBIAN32__ -D__SERIES60_30__ -D__SERIES60_3X__ -D__GCC32__ -D__EPOC32__ -D__GCC32__ -D__MARM__ -D__GCCXML__ -D__MARM_ARM4__ -D__MARM_ARMV5__ -D__EXE__  -UWIN32  -U__i386__ -U_WIN32 -U__WIN32__";
static const char* GCCXML_DEFINE = " -D_DEBUG -D_UNICODE -D__SYMBIAN32__ -D__SERIES60_30__ -D__SERIES60_3X__ -D__GCC32__ -D__GNUC__ -D__EPOC32__ -D__GCC32__ -D__MARM__ -D__GCCXML__ -D__MARM_ARM4__ -D__MARM_ARMV5__ -D__EXE__  -UWIN32  -U__i386__ -U_WIN32 -U__WIN32__";

static const char* GCCXML_OPTIONS = " -E -g -nostdinc -Wall -Wno-ctor-dtor-privacy -Wno-unknown-pragmas -fshort-wchar -quiet -w ";

// Output file define
static const char* GCCXML_OUTPUT = " -o ";

static const char* GCCXML_INCLUDEPATH = " -I ";

// XML output file define
static const char* GCCXML_XML_OUTPUT = " -fxml=";

static const char* GCCXML_MACRO_OUTPUT = " -dD ";

#ifdef __WIN__
// Error code when file remove fails
const int KErrorRemoveFailed=0;
static const char* GCCXML_COMP_OPTIONS = " -fpreprocessed -g -nostdinc -Wall -Wno-ctor-dtor-privacy -Wno-unknown-pragmas -fshort-wchar -quiet -w -o nul";
#else
static const char* GCCXML_COMP_OPTIONS = " -fpreprocessed -g -nostdinc -Wall -Wno-ctor-dtor-privacy -Wno-unknown-pragmas -fshort-wchar -quiet -w -o /dev/null";
#endif


// ----------------------------------------------------------------------------
// CPPParser::GenerateCompilationCmd
// Generate command for compilation
// ----------------------------------------------------------------------------
//
string CPPParser::GenerateCompilationCmd(const string& currentDir,const string& epocRoot,const string& inputFile,const string& outputFile)
{    
    string cmdline;
    if (currentDir != "")
    {
        cmdline = currentDir + "\"" + DIR_SEPARATOR + "\"";
    }
    cmdline += GCCXML_COMMAND;
    cmdline += GCCXML_COMP_OPTIONS;    
    cmdline += GCCXML_XML_OUTPUT + string("\"") + outputFile + string("\" \"");

	
    cmdline += inputFile + string("\"")+ string(" 2>\"") + iCompErrFile + string("\"");
	
    //cout << "-------COMPILATION-----------------------\n";
    //cout << cmdline << endl;
    //cout << "-----------------------------------------\n";
    return cmdline;

}


// ----------------------------------------------------------------------------
// CPPParser::GeneratePreprocessCmd
// Generate GCXML command for prepocessing
// ----------------------------------------------------------------------------
//
string CPPParser::GeneratePreprocessCmd(const string& currentDir,const string& epocRoot,const string& inputFile,const string& outputFile,
                             vector<string>& aHeaders )
{
    string cmdline;

    if (currentDir != "")
    {
        cmdline = currentDir + DIR_SEPARATOR;
    }
    cmdline += GCCXML_COMMAND;

    list<pair<string, string> > includes = BBCFileUtils::extractFilenames(epocRoot);
    list<pair<string, string> >::iterator listbegin = includes.begin();
    list<pair<string, string> >::iterator listend = includes.end();
    for(; listbegin != listend; listbegin++)
    {
        cmdline += GCCXML_INCLUDEPATH + string("\"") + listbegin->first + string("\"");
    }

    if ( !aHeaders.empty() )
    {
        int size = (int)aHeaders.size();
        int i = 0;

        for(;i < size; i++)
        {
            string headerfile = aHeaders.at(i);

            cmdline += GCCXML_INCLUDEPATH + string("\"") + headerfile + string("\"");
        }
    }

    cmdline += GCCXML_DEFINE;
    cmdline += GCCXML_OPTIONS;
    cmdline += GCCXML_OUTPUT + string("\"") + outputFile + string("\" \"");
    cmdline += inputFile + string("\"");

    //cout << "-------- PREPROCESS COMMAND --------------" << endl;
    //cout << cmdline << endl;
    //cout << "------------------------------------------" << endl;
    
    return cmdline;

}

// ----------------------------------------------------------------------------
// CPPParser::GenerateMacroExtract
// Generate commanf or macro extract
// ----------------------------------------------------------------------------
//
string CPPParser::GenerateMacroExtract(const string& currentDir,const string& epocRoot,const string& inputFile,const string& outputFile,
                             vector<string>& aHeaders )
{
    string cmdline;

    if (currentDir != "")
    {
        cmdline = currentDir + DIR_SEPARATOR;
    }
    cmdline += GCCXML_COMMAND;

    list<pair<string, string> > includes = BBCFileUtils::extractFilenames(epocRoot);
    list<pair<string, string> >::iterator listbegin = includes.begin();
    list<pair<string, string> >::iterator listend = includes.end();
    for(; listbegin != listend; listbegin++)
    {
        cmdline += GCCXML_INCLUDEPATH + string("\"") + listbegin->first + string("\"");
    }

    if ( !aHeaders.empty() )
    {
        int size = (int)aHeaders.size();
        int i = 0;

        for(;i < size; i++)
        {
            string headerfile = aHeaders.at(i);
            cmdline += GCCXML_INCLUDEPATH + string("\"") + headerfile + string("\"");
        }
    }

    cmdline += GCCXML_DEFINE;
    cmdline += GCCXML_OPTIONS;

    cmdline += GCCXML_MACRO_OUTPUT;
    cmdline += GCCXML_OUTPUT + string("\"") + outputFile + string("\" \"");
  
    cmdline += inputFile + string("\"")+ string(" 2>\"") + iCompErrFile + string("\"");
	
    //cout << "-----------------------------------------\n";
    //cout << cmdline << endl;
    //cout << "-----------------------------------------\n";
    return cmdline;

}

// ----------------------------------------------------------------------------
// CPPParser::CPPParser
// Constructor
// ----------------------------------------------------------------------------
//
CPPParser::CPPParser(string epocroot) 
  : iInputFilename(), iOutputFilename(), iXMLOutputPath(),
    iEpocRoot(epocroot), iDOMParser(NULL), iDOMDoc(NULL),
    iDOMRootElement(NULL), iCompErrFile()
{
 
}


// ----------------------------------------------------------------------------
// CPPParser::~CPPParser
// Destructor
// ----------------------------------------------------------------------------
//
CPPParser::~CPPParser() 
{
    if (iDOMParser != NULL)
    {
        iDOMParser->resetDocumentPool();
        iDOMParser->release();
        iDOMParser = NULL;
    }
}


// ----------------------------------------------------------------------------
// CPPParser::parse
// Please, note that iOutputFilename is changed internally in different 
// function calls.
// ----------------------------------------------------------------------------
//
DOMNode* CPPParser::parse(const vector<string>& aFilenames, string aVersion, string aPath, list<string>& notRemovedFiles)
{   
    DOMNode* ret = NULL;

    int err = 0;
    headervector headers;
    string cppfilename = generateTempCPPFile(aFilenames, aVersion, headers );

    string extensionStripped = BBCFileUtils::StripFilenameExtension(cppfilename);
    iOriginalFilename = BBCFileUtils::StripPath(extensionStripped);
	iCompErrFile = iTempDir + DIR_SEPARATOR + iOriginalFilename + "-" + aVersion + "-comperr.txt";
    try
    {
        err = PreprocessH(cppfilename, aVersion, headers);        
    } catch (HAException error)
    {
#if !defined(_DEBUG) && !defined(DEBUG)
        RemoveFile(cppfilename, notRemovedFiles);
        RemoveFile(iMacroFilename, notRemovedFiles);
#endif
        throw error;
    }
    RemoveFile(cppfilename, notRemovedFiles);
    string prefilename = iOutputFilename;
    HandleExports(iOutputFilename, aVersion);
    string pre2filename = iOutputFilename;
    try
    {
        err = ConvertHToXML(iOutputFilename, aVersion);
    } catch (HAException error)
    {
#if !defined(_DEBUG) && !defined(DEBUG)
        RemoveFile(prefilename, notRemovedFiles);
        RemoveFile(pre2filename, notRemovedFiles);
        RemoveFile(iMacroFilename, notRemovedFiles);
#endif
        throw error;
    }
    if (err == 0)
    {
        err = ExtractDOMFromXML(iOutputFilename);
        ret = iDOMRootElement;
    }
    headers.clear();
    RemoveFile(prefilename, notRemovedFiles);
    RemoveFile(pre2filename, notRemovedFiles);
#if !defined(_DEBUG) && !defined(DEBUG)
    RemoveFile(iOutputFilename, notRemovedFiles);
#endif

    return ret;
}


// ----------------------------------------------------------------------------
// CPPParser::RemoveFile
// Remove given file
// ----------------------------------------------------------------------------
//
void CPPParser::RemoveFile(string file, list<string>& notRemovedFiles)
{       
    int success;
/*#ifdef __WIN__
    success = DeleteFile(file.c_str());
    if (success == KErrorRemoveFailed)
    {
        unsigned long int errorcode = GetLastError();
        if (errorcode != ERROR_FILE_NOT_FOUND)
        {
            notRemovedFiles.push_back(file);
        }
    }
#else
    success = unlink(file.c_str());
    if (success == -1)
    {
        if (errno != ENOENT)
        {
            notRemovedFiles.push_back(file);
        }
    }
#endif*/
	REMOVE_FILE_FUNCTION
}


// ----------------------------------------------------------------------------
// CPPParser::GenerateMacroExtract
// Converts a header file with given filename to an XML file
// (with same base filename and extension .xml).
//
// Throw an exception on error
// ----------------------------------------------------------------------------
//
int CPPParser::ConvertHToXML(string aFilename, string aVersion) 
{
    int ret = 0;
    string oFilename;
    string iFilename;
    string tempOFilename;

    iFilename = aFilename;
    tempOFilename = BBCFileUtils::StripPath(BBCFileUtils::StripFilenameExtension(iFilename));

    oFilename = iTempDir + DIR_SEPARATOR + iOriginalFilename + "-" + aVersion + ".xml";
    char currentDir[KMaxDirLength];
    getcwd(currentDir,KMaxDirLength);
    #ifdef USE_INCLUDED_GCC_DISTRIBUTION
        string cmdline = GenerateCompilationCmd(currentDir, iEpocRoot, iFilename, oFilename);
    #else
    string empty("");
        string cmdline = GenerateCompilationCmd(empty, iEpocRoot, iFilename, oFilename);
    #endif

    ret = system(cmdline.c_str());
    iXMLOutputPath = iTempDir;
    iOutputFilename = oFilename;
    iInputFilename = iFilename;
    if (ret != 0) 
    {
        throw(HAException("GCCXML Error, please see above for more information"));
    }
    return ret;
}

// ----------------------------------------------------------------------------
// CPPParser::GenerateMacroExtract
// Generate temporary CPP-file
// ----------------------------------------------------------------------------
//
int CPPParser::DumpMacros(string mdumpfile, string ifile, vector<string>& headers)
{
    int ret = 0;
    string cmdbuf;
    char currentDir[KMaxDirLength];
    getcwd(currentDir,KMaxDirLength);
    #ifdef USE_INCLUDED_GCC_DISTRIBUTION
        cmdbuf = GenerateMacroExtract(currentDir, iEpocRoot, ifile, mdumpfile, headers);
    #else
        string empty("");
        cmdbuf = GenerateMacroExtract(empty, iEpocRoot, ifile, mdumpfile,headers);
    #endif

    ret = system(cmdbuf.c_str());
    return ret;
}


// ----------------------------------------------------------------------------
// CPPParser::ExtractDOMFromXML
// Reads in and parses an XML file with given filename.
// ----------------------------------------------------------------------------
//
int CPPParser::ExtractDOMFromXML(const string& aXMLFilename)
{    
    int ret = 0;

    if (iDOMParser != NULL) {
        iDOMParser->resetDocumentPool();
        iDOMParser->release();
		iDOMParser = NULL;		
    }

    return ParseXMLFile(aXMLFilename, iDOMParser, iDOMDoc, iDOMRootElement);
}

// ----------------------------------------------------------------------------
// CPPParser::setBaselineDir
// ----------------------------------------------------------------------------
//
void CPPParser::setBaselineDir(string aRoot)
{
    iEpocRoot = aRoot;
}


// ----------------------------------------------------------------------------
// CPPParser::PreprocessH
// ----------------------------------------------------------------------------
//
int CPPParser::PreprocessH(string aFilename, string aVersion, vector<string>& headers )
{
    int ret = 0;
    string oFilename;
    string iFilename;

    string tempOFilename;

    iFilename = aFilename;
    tempOFilename = iOriginalFilename;
    
    oFilename = iTempDir + DIR_SEPARATOR + tempOFilename + "-" + aVersion + ".pre";
    iMacroFilename = iTempDir + DIR_SEPARATOR + iOriginalFilename + "-" + aVersion + "-macros.txt";
    ret = DumpMacros(iMacroFilename, iFilename,headers);
    if (ret != 0) 
    {
        throw(HAException("GCCXML Error, please see above for more information"));
    }

    char currentDir[KMaxDirLength];
     getcwd(currentDir,KMaxDirLength);

    #ifdef USE_INCLUDED_GCC_DISTRIBUTION
        string cmdline = GeneratePreprocessCmd(currentDir,iEpocRoot,iFilename,oFilename, headers);
    #else
    string empty("");
        string cmdline = GeneratePreprocessCmd(empty,iEpocRoot,iFilename,oFilename, headers);
    #endif

    ret = system(cmdline.c_str());
    if (ret != 0) 
    {
        throw(HAException("GCCXML Error, please see above for more information"));
    }
    iXMLOutputPath = iTempDir;
    iOutputFilename = oFilename;
    iInputFilename = iFilename;
    return ret;
}

// ----------------------------------------------------------------------------
// CPPParser::HandleExports
// ----------------------------------------------------------------------------
//
int CPPParser::HandleExports(string aFilename, string aVersion)
{
    int ret = 0;
    string ofilename = aFilename + ".2";
    
    ifstream input(aFilename.c_str(), ios::in);
    ofstream output(ofilename.c_str(), ios::out);
    iOutputFilename = ofilename;
    char c;
    string toflush = "";
    unsigned int matches = 0;
    string tofind = STR_EXPORT_HACK;
    string attribstr = STR_ATTRIBUTE_STR;
    string outputBuffer;
    outputBuffer.reserve(PREPROCESS_BUFFERSIZE);
    int state = EStateSearching;
    bool purevirtual = false;
    bool possiblepurevirtual = false;
    while (input.get(c))
    {
        if (outputBuffer.length() >= PREPROCESS_BUFFERSIZE)
        {
            output << outputBuffer;
            outputBuffer = "";
        }
        if (state == EStateSearching)
        {
            if (c == tofind.at(matches))
            {
                matches++;
                toflush += c;
            } else 
            {
                matches = 0;
                if (!toflush.empty())
                {
                    outputBuffer += toflush;
                    toflush = "";
                }
                outputBuffer += c;
            }
            if (matches == tofind.length())
            {
                toflush = "";
                state = EStateReplacing;
                matches = 0;
            }
        } else if (state == EStateReplacing)
        {
            if (c == '=')
            {
                if (possiblepurevirtual == true && !toflush.empty())
                {
                    outputBuffer += toflush;
                    toflush = "";
                }
                possiblepurevirtual = true;
                toflush += c;
            } else if (possiblepurevirtual == true && c!= ';')
            {
                if (c == ' ')
                {
                    toflush += c;
                } else if (c == '\t')
                {
                    toflush += c;
                } else if (c == '0')
                {
                    toflush += c;
                    purevirtual = true;
                } else
                {
                    outputBuffer += toflush;
                    outputBuffer += c;
                    toflush = "";
                    possiblepurevirtual = false;
                    purevirtual = false;
                }
            } else if (c == ';')
            {
                state = EStateSearching;
                if (purevirtual)
                {
                } else if (possiblepurevirtual)
                {
                    outputBuffer += toflush;
                    toflush = "";
                }

                outputBuffer += " ";
                outputBuffer += attribstr;
                if (!toflush.empty())
                {
                    outputBuffer += " ";
                    outputBuffer += toflush;
                    toflush = "";
                }
                possiblepurevirtual = false;
                purevirtual = false;
                outputBuffer += ';';
            } else
            {
                outputBuffer += c;
            }
        } else if (state == EStateReplaceDone)
        {

        }

    }
    if (outputBuffer.length() != 0)
    {
        output << outputBuffer;
    }
    return ret;
}


// ----------------------------------------------------------------------------
// CPPParser::ReplaceExport
// ----------------------------------------------------------------------------
//
#if 0
int CPPParser::ReplaceExport(string line, string& processedline)
{
    int ret = 0;
    if (processedline.length() == 0)
    {
        string tofind = STR_EXPORT_HACK;
        size_t idx = line.find(tofind);
        if (idx != string::npos)
        {
            unsigned int start = (unsigned int)idx + tofind.length();
            int len = (int)line.length() - start;
            string sub = line.substr(start+1, len-1);
            int insertidx = (int)sub.rfind("=0;");

            if (insertidx < 0)
            {
                insertidx = (int)sub.rfind("= 0;");
                if (insertidx < 0)
                {
                    insertidx = (int)sub.rfind(';');
                }
            }
            if (insertidx > 0)
            {
                sub.insert(insertidx, " __attribute((gccxml(\"exported\")))");
            } else 
            {
                ret = 1;
            }
            processedline.append(sub);
        } else
        {
            if (processedline.find("};") != string::npos )
            {
                processedline.append(line);
                ret = 0;
            }
        }
    } else
    {
        string sub = line;
        int insertidx = (int)sub.rfind("=0;");

        if (insertidx < 0)
        {
            insertidx = (int)sub.rfind("= 0;");
            if (insertidx < 0)
            {
                insertidx = (int)sub.rfind(';');
            }
        }
        if (insertidx > 0)
        {
            sub.insert(insertidx, " __attribute((gccxml(\"exported\")))");
            ret = 0;
        } else 
        {
            ret = 1;
        }
        processedline = "";
        processedline.append(sub);
    }
    return ret;
}
#endif


// ----------------------------------------------------------------------------
// CPPParser::getEnv
// ----------------------------------------------------------------------------
//
char* CPPParser::getEnv(char* aEnvVarName)
{
    char* ret = getenv(aEnvVarName);
    if (ret == NULL)
    {
        string s("Environment variable not defined: ");
        s += aEnvVarName;
        throw(new HAException(s));
    }
    return ret;
}

// ----------------------------------------------------------------------------
// CPPParser::generateTempCPPFile
// ----------------------------------------------------------------------------
//
string CPPParser::generateTempCPPFile(const vector<string>& aFiles, string aVersion, vector<string>& aHeaders)
{
    string headers = "";
    
	if (!iForcedHeaders.empty())
    {
        // START -- Support for multiple forced headers
        list<pair<string, string> > fheaders = BBCFileUtils::extractFilenames(iForcedHeaders);
        list<pair<string, string> >::iterator fheadersbegin = fheaders.begin();
        
        for(; fheadersbegin != fheaders.end(); fheadersbegin++)
        {
            headers += "#include \"";
            headers += fheadersbegin->first;
            headers += "\"\n";           
        } 
		// END -- Support for multiple forced headers
    }
    
    size_t filecount = aFiles.size();
    int filehash = 0;
    string ret = "";
    for (unsigned int i = 0; i < filecount; i++)
    {
        // Append header folder to include vector
        //string& hdr = aFiles.at(i);
        AppendHeader( aHeaders, aFiles.at(i) );

        string fn = aFiles.at(i);
        headers += "#include \"";
        headers += fn;
        headers += "\"\n";
        fn += "-";
        fn += aVersion;
        filehash += BBCFileUtils::quickHash(fn);
    }
    string temp;
    itoa(filehash, temp, 10);
    ret = iTempDir + DIR_SEPARATOR + temp + ".cpp";

    ofstream output(ret.c_str(), ios::out);
    output << headers;
    output.close();
    return ret;
}

// ----------------------------------------------------------------------------
// CPPParser::setForcedHeaders
// ----------------------------------------------------------------------------
//
void CPPParser::setForcedHeaders(const string& aHeaders)
{
    iForcedHeaders = aHeaders;
}

// ----------------------------------------------------------------------------
// CPPParser::setTemp
// Set temp file
// ----------------------------------------------------------------------------
//
void CPPParser::setTemp(const string& aTempDir)
{
    iTempDir = aTempDir;
}

// ----------------------------------------------------------------------------
// CPPParser::getMacroFilename
// Returns macro filename
// ----------------------------------------------------------------------------
//
string CPPParser::getMacroFilename()
{
    return iMacroFilename;
}

// ----------------------------------------------------------------------------
// CPPParser::getCompErrFile
// Returns compilation error filename
// ----------------------------------------------------------------------------
//
string CPPParser::getCompErrFile()
{
    return iCompErrFile;
}

// ----------------------------------------------------------------------------
// CPPParser::AppendHeader
// ----------------------------------------------------------------------------
//
void CPPParser::AppendHeader( vector<string>& aHeaders, string aFile )
{
    string onlyFolder = aFile;

    string::size_type idx = onlyFolder.rfind(DIR_SEPARATOR);

    // for other separation formats
    if (idx != string::npos)
    {
        onlyFolder.erase( idx );
    }

    if (onlyFolder.size() == ANALYSER_HEADER_SIZE)
    {
        onlyFolder += APPEND_DIR_SEPARATOR;
    }

    bool notFound = true;
    unsigned int size = (unsigned int)aHeaders.size();

    for(unsigned int g = 0; g < size ; g++ )
    {
        if( aHeaders.at(g) == onlyFolder )
        {
            notFound = false;
            size = (unsigned int)aHeaders.size();
        }		
    }

    if( notFound )
    {
        aHeaders.push_back( onlyFolder );
    }
}
