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

#define MAX_ARRAY_COUNT 200

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
	string flush = "";
	unsigned int matches = 0;
	string tofind = STR_EXPORT_HACK;
	string attribstr = STR_ATTRIBUTE_STR;
	string outputBuffer;
	outputBuffer.reserve(PREPROCESS_BUFFERSIZE);
	int state = EStateSearching;
	char stackArray[MAX_ARRAY_COUNT] = {'\0'};
	int arryPos = 0;
	
	string isClass = "class";
	string isEnum = "enum";
	string isStruct = "struct";
	string isUnion = "union";
	string isInline = "inline";

	unsigned int clsPos = 0;
	unsigned int enmPos = 0;
	unsigned int strctPos = 0;
	unsigned int inlinePos = 0;
	unsigned int unionPos = 0;
	char arraychar = '\0';

	unsigned int bufPos = 0;
	
	string temp;
	string buf;
	
	bool possibleVirtualFunc = false;
	bool virtualFunc = false;
	bool ignorecheck = false;
	while (input.get(c))
	{
		ignorecheck = false;
		if (outputBuffer.length() >= PREPROCESS_BUFFERSIZE)
		{
			output << outputBuffer;
			outputBuffer = "";
		}
       // Get the bufferpos
		bufPos = (unsigned int)outputBuffer.length()-1;

		// delete buf (class\enum\struct) entry if next letter is not space
 		if ( buf.length() > 0 && state == EStateReplacing && (c != ' ' && c != '\t' && int(c) != 10))
		{
			buf = "";
		}
		if( c == isClass.at(clsPos))
		{
			if( clsPos == 0 ) // searching for class keyword with space before and after
			{
				if(outputBuffer == "" || outputBuffer.at(bufPos) == ' ' || outputBuffer.at(bufPos) == '\t'
					|| int(outputBuffer.at(bufPos)) == 10 || int(outputBuffer.at(bufPos)) == 32 )
					clsPos++;
			}
			else
				clsPos++;
		}			
			
		else
			clsPos = 0;
		if (clsPos == isClass.length()) // keyword found 
		{
			clsPos = 0;
			buf = isClass;
			ignorecheck = true; // in the current iteration don't match buf string with class\enum\struct keyword
			                    // as keyword may be part of some word like " classification" 
		}

		if( c == isUnion.at(unionPos))
		{
			if( unionPos == 0 ) // searching for union keyword with space before and after
			{
				if(outputBuffer == "" || outputBuffer.at(bufPos) == ' ' || outputBuffer.at(bufPos) == '\t'
					|| int(outputBuffer.at(bufPos)) == 10 || int(outputBuffer.at(bufPos)) == 32 )
					unionPos++;
			}
			else
				unionPos++;
		}			
			
		else
			unionPos = 0;
		if (unionPos == isUnion.length()) // keyword found 
		{
			unionPos = 0;
			buf = isUnion;
			ignorecheck = true; // in the current iteration don't match buf string with class\enum\struct\union keyword
			                    // as keyword may be part of some word like " classification" 
		}

		if(c == isStruct.at(strctPos))// searching for struct keyword with space before and after
		{
			if( strctPos == 0 )
			{
				if(outputBuffer == "" || outputBuffer.at(bufPos) == ' ' || outputBuffer.at(bufPos) == '\t'
					|| int(outputBuffer.at(bufPos)) == 10 )
					strctPos++;
			}
			else
				strctPos++;
		}
		else
			strctPos = 0;

		if(strctPos == isStruct.length())
		{
			strctPos = 0;
			buf = isStruct;
			ignorecheck = true; // in the current iteration don't match buf string with class\enum\struct keyword
			                    // as keyword may be part of some word like " structural" 
		}

		if(c == isEnum.at(enmPos) )// searching for enum keyword with space before and after
		{
			if( enmPos == 0 )
			{
				if(outputBuffer == "" || outputBuffer.at(bufPos) == ' ' || outputBuffer.at(bufPos) == '\t'
					|| int(outputBuffer.at(bufPos)) == 10 )
					enmPos++;
			}
			else
				enmPos++;
		}
		else
			enmPos = 0;

		if( enmPos == isEnum.length())
		{
			enmPos = 0;
			buf = isEnum;
			ignorecheck = true;// in the current iteration don't match buf string with class\enum\struct keyword
			                    // as keyword may be part of some word like " enumuration" 
		}

		if (state == EStateSearching)
		{
			memset(stackArray,'\0',MAX_ARRAY_COUNT);
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
				
				if(buf.length() > 0 && ignorecheck == false && (c != ' ' && c != '\t' 
					&& int(c) != 10 ))
				{
					buf = "";
					arraychar = '\0';
				}
			}
			if (matches == tofind.length())
			{
				toflush = "";
				state = EStateReplacing; // export keyword match found, so make the stae as replacing
				matches = 0;
			}
		} else if (state == EStateReplacing)
		{  
			// under a exported class,for a function the exported keyword is present,it should be deleted.
			if (c == tofind.at(matches))
			{
				matches++;
				toflush += c;
				if (matches == tofind.length())
				{
					toflush = "";
					matches = 0;					
				}
				continue;
			} else 
			{
				matches = 0;
				if (!toflush.empty())
				{
					outputBuffer += toflush;
					toflush = "";
				}		
			}
			
		
			if(c == isInline.at(inlinePos))
			{
				if( inlinePos == 0 )// searching for inline keyword with space before and after
				{
					if(outputBuffer == "" || outputBuffer.at(bufPos) == ' ' || outputBuffer.at(bufPos) == '\t'
						|| int(outputBuffer.at(bufPos)) == 10 )
						inlinePos++;
				}
				else
					inlinePos++;
			}		
			else
				inlinePos = 0;
			
			if( inlinePos == isInline.length())
			{
				inlinePos = 0;
				buf = isInline;

			}

			if ( buf.length() > 0 && (c == ' ' || c == '\t' || int(c) == 10))
			{
				if (buf == isClass)
				{
					arraychar = 'c';
				}
				if (buf == isStruct )
				{
					arraychar = 's';
				}
				if (buf == isEnum)
				{
					arraychar = 'e';
				}
				if(buf == isUnion)
				{
					arraychar = 'u';
				}
				if(buf == isInline) 
				{
					stackArray[arryPos] = 'i'; // place inline keyword in stack
					arryPos++;
				}
				
				buf = "";
				if(temp.length() > 0) 
					temp = "";
			}
			else if (c == '{')
			{
				// place the keyword in stack for class\enum\struct
				if(arraychar != '\0')
				{
					stackArray[arryPos] = arraychar;
					arraychar = '\0';
					arryPos++;
				}				
				stackArray[arryPos] = c;				
                arryPos++;

				if(temp.length() > 0) 
					temp = "";
			}
			else if(c== '}')
			{
				temp = "";
				bool ignore = false;
				// can be end of class\enum\struct				
				for (int i = arryPos-1; i >= 0; i-- )
				{

					if (stackArray[i] == '{' ) 
					{
						if( stackArray[i-1] != 'c' && stackArray[i-1] != 's' 
							&& stackArray[i-1] != 'e' && stackArray[i-1] != 'u')
							// check if the function is inline
						{

							ignore = true;
							break;
						}
					}
				}
				if(ignore == false)
					temp = c;
				
				stackArray[arryPos] = c;
                arryPos++;

				if(temp == "")
				{
					int openbraceCount = 0;
					int closebracecount = 0;

					// if it is end of a function then delete the entry from stack
					// and it is ofcourse not a exported function, 
					//will definitely be a inline function with or without "inline" keyword
					bool deleteEntry = false;
					int setpos = 0;
					// get the pos after class\struct\enum started
					for(int i = arryPos; i >= 0; i--)
					{
						if(stackArray[i] == '{')
						{
							deleteEntry = true;
							if (stackArray[i-1] == 'c' || stackArray[i-1] == 's' 
								|| stackArray[i-1] == 'e' || stackArray[i-1] == 'u')
							{
								setpos = i+1;								
								break;
							}							
						}
					}
					// find the end pos of the non exported function by matching the open and close flower brace count.
					if(deleteEntry)
					{
						deleteEntry = false;
						for(int i = setpos; i <= arryPos; i++ )
						{						
							if(stackArray[i] == '{')
								openbraceCount++;
							else if(stackArray[i] == '}')
								closebracecount++;
						}
						if(openbraceCount > 0 && openbraceCount == closebracecount )
						{
							deleteEntry = true;// need to delete the non exported function entry from stack now
						}
					}
					// noe delete the non exported entry and re arrange the stack
					if(deleteEntry)
					{
						for(int pos = setpos; pos <= arryPos; pos++ )
							stackArray[pos] = '\0';

						arryPos = setpos;
					}
				}
				
			}
			else if ( (c == '=' && stackArray[arryPos-1] == ')') ||
                      (c == '0' && stackArray[arryPos-1] == '=') ||
					  (c == '(' || c == ')' )||
					  ( possibleVirtualFunc == true ||virtualFunc == true)
					 ) // can be a virtual function or normal function which might be exported
			{
				if(temp.length() > 0) 
					temp = "";

				if( (possibleVirtualFunc == true && (  c!= '0' && c != ' ' && c != '\t' && int(c) != 10) ) ||
					(virtualFunc == true && (c!= ';' && c != ' ' && c != '\t' && int(c) != 10)) )
				{ // if other than space and '0', then set posVirtual func to false
					// or if other than space and ';', then set Virtual func to false
					outputBuffer += flush;
					outputBuffer += c;
					flush = "";
					possibleVirtualFunc = false;
					virtualFunc = false;
					continue;
				}

				else if( c == '=') // possible virtual function
				{
					flush = c;
					possibleVirtualFunc = true;
					virtualFunc = false;
					stackArray[arryPos] = c;
					arryPos++;
					continue;
				}
				else if (possibleVirtualFunc == true)
				{				
					flush += c;
					if ( c == '0')
					{
						virtualFunc = true; // pure virtual function
						possibleVirtualFunc = false;
						stackArray[arryPos] = c;
						arryPos++;
					}					
					continue;
				}
				else if (c == '(' || c == ')')
				{
					flush = "";
					stackArray[arryPos] = c;
					arryPos++;
				}
				
			} 
			
			if (c == ';')
			{
				arraychar = '\0';
				// first check for inline function and delete the entry from stack for this func
				bool isinline = false;
				bool nonExpFun = false;
				bool removeEntry = false;

				for (int i = arryPos-1; i >= 0; i-- )
				{
					if ( stackArray[i] == 'i') // inline function with inline keyword
						isinline = true;
					
					else if (stackArray[i] == '{')// check if the function is inline
					{
						if (stackArray[i-1] != 'c' && stackArray[i-1] != 's' 
							  && stackArray[i-1] != 'e' && stackArray[i-1] != 'u')
							nonExpFun = true;
					}
				}

				// end of struct/class/enum
				if (stackArray[arryPos-1] == '}' && temp == "}"   ) 
				{
					//if(!isinline && !nonExpFun)
					{
					int cnt = arryPos-1;
					bool flag = false;
					for (int i = cnt; i>=0; i--)
					{
						if (stackArray[i] == 'c' || stackArray[i] == 's' 
							   || stackArray[i] == 'e' || stackArray[i] == 'u')
						{
							flag = true;
						}	
						stackArray[i] = '\0';		
						arryPos--;
						if( flag )	
						{
							break;
						}
					}
					outputBuffer += c;
					temp = "";

					if(stackArray[0] == '\0') // check if exported class\struct is ended .. 
						                      // set state to searching and continue;
						state = EStateSearching;
					continue;
					}
				}				
				
				if(stackArray[arryPos-1] == '('&& nonExpFun == false && isinline == false) 
					// not function, can be a for loop, so reset the stackArray ...
				{				
					outputBuffer += c;
					removeEntry = true;
				}
				else if(stackArray[arryPos-1] == ')'  ) 
					// some exported function can be "abcd( xyz(0), pqr(0))"
				{	
					if( nonExpFun == false && isinline == false )
					{
						outputBuffer += " ";
						outputBuffer += attribstr;
					}
					outputBuffer += c;	
					if (nonExpFun == false)
					removeEntry = true;
				}			
				else if( (stackArray[arryPos-1] == '0' && stackArray[arryPos-2] == '=' && virtualFunc == true) )
				{ // can be a virtual function or normal function which is definitely exported
					if(!isinline && !nonExpFun)
					{
						outputBuffer += " ";
						outputBuffer += attribstr;
						outputBuffer += " ";
					}					
					outputBuffer += flush;					
					outputBuffer += c;
					flush = "";
					if(nonExpFun == false)
						removeEntry = true;
					virtualFunc = false;
				}
				else	
				{
					outputBuffer += c;
				}

				if(removeEntry == true)
				{
					int cnt = arryPos-1;
					bool flag = false;
					for (int i = cnt; i>=0; i--)
					{
						if (stackArray[i] == '{' && 
							(stackArray[i-1] == 'c' || stackArray[i-1] == 's' 
							|| stackArray[i-1] == 'e' || stackArray[i-1] == 'u') )
							flag = true;

						if(flag == false)
						{
							stackArray[i] = '\0';	
							arryPos--;
						}
					}
				}
	
				if(stackArray[0] == '\0')
					state = EStateSearching;				
			} 
			else
			{
				if(  virtualFunc == true )
				{
					outputBuffer += flush;					
					flush = "";
                    virtualFunc = false;
				}
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
