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


#ifndef __CPP_PARSER_H__
#define __CPP_PARSER_H__
#include "CmdGlobals.h"
#ifdef __WIN__
#pragma warning(disable:4786)
#endif

#include <xercesc/dom/DOM.hpp>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "CmdGlobals.h"

using namespace std;

typedef vector<string> headervector;

XERCES_CPP_NAMESPACE_USE


/**
* The CPPParser provides interface for the GCCXML program for C++ parsing functionality
* It produces a XML document that the HeaderAnalyser interface receives as a input 
* for BBC analysis. The result of the analysis from the HeaderAnalysis is also 
* a XML document.
*/ 
class CPPParser {

// Construction / destruction
public:

    /**
    * Constructor
    * @param epocroot root of the platform headers( baseline or current) 
    */
    CPPParser(string epocroot);

    /**
    * Destructor
    */
    ~CPPParser();

// Interface methods
public:
    
    /**
    * Parse the filename vectors into XML and eventually into a DOM format
    * @param aFilenames vector of filename to parse
    * @param aVersion version string 
    * @param aPath header path
    * @param notRemovedFiles list of not removed files  
    * @return pointer to DOMnode
    */
    DOMNode* parse(const vector<string>& aFilenames, string aVersion, string aPath, list<string>& notRemovedFiles);
    
    /**
    * Set baseline directory
    * @param aDir header path
    */   
    void setBaselineDir(string aDir);

    /**
    * Set forced headers.Specifies a file which is always included
    * first in generated temporary cpp file.
    * @param aHeaders fors
    */   
    void setForcedHeaders(const string& aHeaders);
        
    /**
    * Set temporary directory to member variable
    * @param aTempDir reference to temp directory name 
    */
    void setTemp(const string& aTempDir);
        
    /**
    * Get macro filename
    * @return name of the file containing all macros found
    */
    string getMacroFilename();

    /**
    * Get compilation error file
    * @return compilation error file
    */
    string getCompErrFile();

    /**
    * Remove file
    * @param file filename to remove
    * @param notRemovedFiles list of files that couldn't get removed
    */
    static void RemoveFile(string file, list<string>& notRemovedFiles);


// Helper functions
private:
    /**
    * Converts a header file with given filename to an XML file
    * (with same base filename and extension .xml).
    *
    * @param aAbsFilename filename to convert
    * @param aVersion version string
    * @return 0 if the conversion succeeded
    * @exception Throw an exception on error 
    */
    int ConvertHToXML(string aAbsFilename, string aVersion);

    /**
    * Reads in and parses an XML file with given filename. Set the 
    * pointer to the document root (DOM Tree root).
    *
    * @param aAbsFilename  XML filename to parse
    * @return 0 if the parse succeeded
    */
    int ExtractDOMFromXML(const string& aAbsFilename);

    /**
    * Dump macros file
    * @param mdumpfile nacro dumpfile
    * @param ifile 
    * @param headers list of headers
    * @return 0 if success
    */
    int DumpMacros(string mdumpfile, string ifile, vector<string>& headers);
        
    /**
    * Preprocess header file
    * @param aAbsFilename filename to remove
    * @param aVersion version name to parse
    * @param aHeaders vector of headers to preprocess
    * @return 0, if success
    */
    int PreprocessH(string aAbsFilename, string aVersion, vector<string>& aHeaders );
    
    /**
    * Opens header file as input, write findings to output file
    * @param aFilename input filename
    * @param aVersion version name to handle
    * @return 0 if success
    */
    int HandleExports(string aFilename, string aVersion);

    /**
    * Replace exports
    * @param line line to process from input file
    * @param processedline line processed
    * @return
    */
    //int ReplaceExport(string line, string& processedline);

    /**
    * Generate temporary CPP-file
    * @param aFiles filename to remove
    * @param aVersion
    * @param aHeaders
    * @return
    */
    string generateTempCPPFile(const vector<string>& aFiles, string aVersion, vector<string>& aHeaders );

    /**
    * Get value of environment variable
    * @param aEnvVarName variable to get
    * @return value of the variable
    * @exception throw axeption if the variable vaue isn't found
    */
    char* getEnv(char* aEnvVarName);

    /**
    * Append headers to file
    * @param aHeaders reference to headerpaths
    * @param aFile the header file which the path is taken from
    */
    void AppendHeader( vector<string>& aHeaders, string aFile );

    /**
    * Generate GCXML command for prepocessing
    * @param currentDir current directory
    * @param epocRoot epocroot directory
    * @param inputFile to parser
    * @param outputFile to parser
    * @param aHeaders reference to headerpaths
    * @return commandline string to start parser
    */
    string GeneratePreprocessCmd(const string& currentDir,const string& epocRoot,const string& inputFile,
                             const string& outputFile, vector<string>& aHeaders );

    /**
    * Generate GCXML command for prepocessing
    * @param currentDir current directory
    * @param epocRoot epocroot directory
    * @param inputFile to parser
    * @param outputFile to parser
    * @return commandline string to start parser
    */
    string GenerateCompilationCmd(const string& currentDir,const string& epocRoot,const string& inputFile,
                             const string& outputFile);

    /**
    * Generate macro extraction command
    * @param currentDir current directory
    * @param epocRoot root directory of headers
    * @param inputFile to parser
    * @param outputFile to parser
    * @param aHeaders reference to headerpaths
    * @return commandline string to start parser
    */
    string GenerateMacroExtract(const string& currentDir,const string& epocRoot,const string& inputFile,const string& outputFile,
                             vector<string>& aHeaders );

// Instance variables
private:
    //! File name for input
    string                          iInputFilename;

    //! File name for output
    string                          iOutputFilename;

    //! Path where the XML output goes
    string                          iXMLOutputPath;

    //! EPOC root path
    string                          iEpocRoot;

    //! Working file
    string                          iOriginalFilename;

    //! String consisting of forced headers
    string                          iForcedHeaders;

    //! Name of the temporary directory
    string                          iTempDir;

    //! Name of the macrofile
    string							iMacroFilename;
    
	//! Compilation error text
    string							iCompErrFile;

    //! Pointer to DOMBuilder
    XERCES_CPP_NAMESPACE_QUALIFIER DOMBuilder*      iDOMParser;

    //! Pointer to DOMDocument
    XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument*     iDOMDoc;

    //! Pointer to DOM root node
    XERCES_CPP_NAMESPACE_QUALIFIER DOMNode*         iDOMRootElement;
};
#endif
