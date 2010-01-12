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


#ifndef __BBC_FILE_UTILS_H__
#define __BBC_FILE_UTILS_H__
#include "CmdGlobals.h"
#ifdef __WIN__
#pragma warning(disable:4786)
#endif
#include <vector>
#include <string>
#include <map>
#include <list>

using namespace std;

/**
* Class includes file handling methods
*/ 
class BBCFileUtils
{
public:
    /**
    * Contructor
    * @param  basedir 
    */ 
    BBCFileUtils(string basedir);

    /**
    * Destructor
    */ 
    ~BBCFileUtils();

public:
    /**
    * Gets all the filenames matching the given wildcard in a directory
    * @param wildcard Search pattern for the files.
    * @param aRelPath Search location.
    * @return List of the filenames (pairs).
    */ 
    list<pair<string, string> > getFilesInDir(string wildcard, string aRelPath);

    /**
    * Gets all the filenames matching a file set in a directory
    * @param fileset List of filenames to be searched.
    * @param aRelPath Search location.
    * @param aFoundfiles list of files found
    * @return List of the filenames (pairs).
    */ 
    list<pair<string, string> > getFilesInDir(list<pair<string, string> >& fileset, string aRelPath, list<pair<string, string> >& aFoundfiles);

    /**
    * Calculates a quick but relatively unique fingerprint for a string.
    * Used in tempfile name generation. Collisions may occur, but it's 
    * not highly probable.
    * @param str filename + version
    * @return hash value
    */ 
    static unsigned int quickHash(string str);

    /**
    * Extract Filenames
    * Converts a ';' (semicolon) separated filename list to a string list.
    *
    * @param aFilenameList list of file names to search for
    * @return list pair of files
    */ 
    static list<pair<string, string> > extractFilenames(string aFilenameList);

    /**
    * Gets subdirectories in a directory
    * @param aRelPath Relative path to the directory from where the subdirectories are searched.
    * @param aExcludes Subdirectories to be excluded from the results
    * @return List of subdirectories found.
    */ 
    list<pair<string, string> > getDirsInDir(string aRelPath, list<pair<string, string> >& aExcludes);

    /**
    * Trims the given filename string (changes ';' to ' ' [whitespace])
    * and prefixes each filename entry with the base directory name 
    * (if required)
    * @param aFilenameList String containing the filenames separated with ';'.
    * @return String containing the trimmed filenames
    */ 
    string trimFilenames(string aFilenameList);

    /**
    * Checks if the given filename is valid.
    * @param aFilename Name of the file to be checked.
    * @return true, if the given string is a valid filename
    */ 
    static bool isValidFilename(const string& aFilename);

    /**
    * Check if the given path is a valid directory.
    * @param aPath Path to be checked
    * @return true, if the given string is a valid directory path
    */ 
    static bool isValidDirectory(const string& aPath);

    /**
    * Set temporary directory
    * @param aTempDir Temp directory name
    */ 
    void setTemp(const string& aTempDir);

    /**
    * Get full path name
    * @param aPath Path to be parsed
    * @return Full path name
    * @exception throws an exception if the path cannot be solved.
    */ 
    static string getFullPath(const string& aPath);

    /**
    * Strips off the file extension
    * @param aFileName Whole name of the file
    * @return Filename without the extension
    */ 
    static string  StripFilenameExtension(string aFileName);

    /**
    * Strips off the path
    * @param aAbsFilename Filename containing the path
    * @return Path from the given filename
    */ 
    static string StripPath(const string& aAbsFilename);

    // -- Support for multiple header directories -- Return type changed to list
    static list<pair<string, bool> > MergeDirs(const string& rootDir, const string& subDir);

    static bool FileExists(const string& fileName);

    /**
    * Function to read the compilation error output from a file and append to a string.
    * @param filename Filename containing the error output
    * @return string having error output
    */     
	static string getCompilationError(string filename);
	
	static string& TrimRight(string& s);
    static string& TrimLeft(string& s);
    static string& TrimAll(string& s);

private:
#ifdef __UNIX__
    /**
    * Finds and return absolute path of the given relative path
    * @param aRelPath path to check
    * @param aAbsPath returnned absolute path
    * @return true if absolute path is found
    */ 
    static bool absolutePath(const string& aRelPath, string& aAbsPath);
#endif

private:
    //! count of files
    int             iFileCount;
    //! Vector of base/current files
    vector<string>  iFiles;
    //! the whole path + wildcard given
    string          iWildcard;
    //! base directory
    string          iBaseDir;
    //! temporary directory
    string          iTempDir;
    //! Dump file (not used)
    string          iDumpfile;

    static map<string, bool> fileExistsCache;
};

#endif
