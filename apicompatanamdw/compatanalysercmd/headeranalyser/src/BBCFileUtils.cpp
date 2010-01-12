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

#include "CmdGlobals.h"
#ifdef __WIN__
#pragma warning(disable:4786)
#endif

#include <fstream>
#include <stdlib.h>
#include <string>
#include <map>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef __WIN__
#include <io.h>
#include <windows.h>
#else
#include <unistd.h>
#include <glob.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <unistd.h>
#define _MAX_PATH MAXPATHLEN

#endif
#include "BBCFileUtils.h"
#include "HAException.h"
#include "Utils.h"
#include "XMLUtils.h"


// ----------------------------------------------------------------------------
// BBCFileUtils::BBCFileUtils
// ----------------------------------------------------------------------------
//
BBCFileUtils::BBCFileUtils(string basedir)
{
    iBaseDir = basedir;
}

// ----------------------------------------------------------------------------
// BBCFileUtils::~BBCFileUtils
// ----------------------------------------------------------------------------
//
BBCFileUtils::~BBCFileUtils()
{
}

typedef int intptr_t;

// ----------------------------------------------------------------------------
// BBCFileUtils::getFilesInDir
// ----------------------------------------------------------------------------
//
list<pair<string, string> > BBCFileUtils::getFilesInDir(string wildcard, string aRelPath)
{
    // START -- Support for multiple header directories
    list<pair<string, string> > ret;
    list<pair<string, string> > dirs = BBCFileUtils::extractFilenames(iBaseDir);
    list<pair<string, string> >::iterator dirbegin = dirs.begin();
    for(; dirbegin != dirs.end(); dirbegin++)
    {
    // END -- Support for multiple header directories
        string basedir = BBCFileUtils::getFullPath(dirbegin->first);
        if (aRelPath != "")
        {
            iWildcard = basedir + DIR_SEPARATOR + aRelPath + DIR_SEPARATOR + wildcard;
        } else
        {
            iWildcard = basedir + DIR_SEPARATOR + wildcard;
        }
    
    // search for all files which were specified in wildcard string
#ifdef __WIN__
        _finddata_t finddata;
        intptr_t searchsession =_findfirst(iWildcard.c_str(),&finddata);
        int found = -1;
        if (searchsession > 0)
        {
            found = 0;
        }
        while (found == 0)
        {
            string path;
            if (aRelPath != "")
            {
                path = DIR_SEPARATOR + aRelPath + DIR_SEPARATOR + string(finddata.name);
            } else
            {
                path = DIR_SEPARATOR + string(finddata.name);
            }
            string fullpath = basedir + path;
            if (isValidFilename(fullpath))
            {
                pair<string, string> tempval(path, toLowerCaseWin(path));
                ret.push_back(tempval);
            }
            found = _findnext(searchsession, &finddata);
        }
        _findclose(searchsession);
#else
        glob_t p_glob;
      
        glob(iWildcard.c_str() , 0, NULL, &p_glob);    
        for (unsigned int i = 0; i < p_glob.gl_pathc; i++ )
        {
            string path = p_glob.gl_pathv[i];
            if (isValidFilename(path))
            {
                path = StripPath(path);
                if (aRelPath != "")
                {
                    path = aRelPath + DIR_SEPARATOR + path;
                }
                path = DIR_SEPARATOR + path;
                pair<string, string> tempval(path, toLowerCaseWin(path));
                ret.push_back(tempval);
            }
        }  
        globfree(&p_glob);
#endif
    }
    return ret;
}

// ----------------------------------------------------------------------------
// BBCFileUtils::getFilesInDir
// ----------------------------------------------------------------------------
//
list<pair<string,string> > BBCFileUtils::getFilesInDir(list<pair<string, string> >& fileset, string aRelPath, list<pair<string, string> >& aFoundfiles)
{
    // START -- Support for multiple header directories
    list<pair<string, string> > ret;
    list<pair<string, string> > notfound;
    list<pair<string, string> > dirs = BBCFileUtils::extractFilenames(iBaseDir);
    list<pair<string, string> >::iterator dirbegin = dirs.begin();
    for(; dirbegin != dirs.end(); dirbegin++)
    {
        // END -- Support for multiple header directories
        string basedir = BBCFileUtils::getFullPath(dirbegin->first);
        if (aRelPath != "")
        {
            iWildcard = basedir + DIR_SEPARATOR + aRelPath + DIR_SEPARATOR + WILDCARD_ALLFILES;
        } else
        {
            iWildcard = basedir + DIR_SEPARATOR + WILDCARD_ALLFILES;
        }
    

    // Search for all files which were specified in wildcard string
#ifdef __WIN__
        _finddata_t finddata;
        intptr_t searchsession =_findfirst(iWildcard.c_str(),&finddata);
        int found = -1;
        if (searchsession > 0)
        {
            found = 0;
        }
        while (found == 0)
        {
            string filename = DIR_SEPARATOR + string(finddata.name);
            if (aRelPath != "")
            {
                filename = DIR_SEPARATOR + aRelPath + filename;
            }
            string fullpath = basedir + filename;
            // Check if path is pointing to a file
            if (isValidFilename(fullpath))
            {
                list<pair<string, string> >::iterator file = FindFromList(toLowerCaseWin(filename), fileset, ERightValue);
                if (file == fileset.end() && aRelPath != "")
                {
                    file = FindFromList(toLowerCaseWin(finddata.name), fileset, ERightValue);
                }
                if (file != fileset.end())
                {
                    pair<string, string> tempval;
                    tempval.first = filename;
                    tempval.second = toLowerCaseWin(filename);
                    ret.push_back(tempval);
                    aFoundfiles.push_back(*file);
                    fileset.erase(file);
                } else if (aRelPath == "")
                {
                    pair<string, string> tempvar(filename, toLowerCaseWin(filename));
                    notfound.push_back(tempvar);
                } else
                {
                    list<pair<string, string> >::iterator alreadyfound = FindFromList(toLowerCaseWin(finddata.name), aFoundfiles, ERightValue);
                    if (alreadyfound != aFoundfiles.end())
                    {
                        cout << "Warning: More than one files matches for the given filename '" << finddata.name;
                        cout << "' in the file set, only the first file is used." << endl;
                        aFoundfiles.erase(alreadyfound);
                    }
                }
            }
            found = _findnext(searchsession, &finddata);
        }
        _findclose(searchsession);
#else
        glob_t p_glob;
      
        int result = glob(iWildcard.c_str() , 0, NULL, &p_glob);    
        if (result == 0)
        {
            for ( unsigned int i = 0; i < p_glob.gl_pathc; i++ )
            {
                string path = p_glob.gl_pathv[i];
                // Check if path is pointing to a file
                if (isValidFilename(path))
                {
                    string filename = DIR_SEPARATOR + StripPath(path);
                    string pathfile = "";

                    if (aRelPath != "")
                    {
                        pathfile = DIR_SEPARATOR + aRelPath + filename;
                    } else
                    {
                        pathfile = filename;
                    }
                    list<pair<string, string> >::iterator file = FindFromList(toLowerCaseWin(pathfile), fileset,ERightValue);
                    if (file == fileset.end() && aRelPath != "")
                    {
                        file = FindFromList(toLowerCaseWin(filename.substr(1)), fileset,ERightValue);
                    }
                    if (file != fileset.end())
                    {
                        pair<string, string> tempval;
                        tempval.first = pathfile;
                        tempval.second = toLowerCaseWin(pathfile);
                        ret.push_back(tempval);
                        aFoundfiles.push_back(*file);
                        fileset.erase(file);
                    } else if (aRelPath == "")
                    {
                        pair<string, string> tempvar(pathfile, toLowerCaseWin(pathfile));
                        notfound.push_back(tempvar);
                    } else
                    {
                        list<pair<string, string> >::iterator alreadyfound = FindFromList(toLowerCaseWin(filename.substr(1)), aFoundfiles,ERightValue);
                        if (alreadyfound != aFoundfiles.end())
                        {
                            cout << "Warning: More than one files matches for the given filename '" << filename.substr(1);
                            cout << "' in the file set, only the first file is used.";
                            aFoundfiles.erase(alreadyfound);
                        }
                    }
                }
            }
            globfree(&p_glob);
        }
#endif
    }
    if (notfound.size() != 0)
    {
        list<pair<string, string> >::iterator file = notfound.begin();
        list<pair<string, string> >::iterator fileend = notfound.end();
        for(; file != fileend; file++)
        {
            string filename = file->second.substr(1);
            list<pair<string, string> >::iterator file = FindFromList(filename, fileset, ERightValue);
            if (file != fileset.end())
            {
                pair<string, string> tempval;
                tempval.first = DIR_SEPARATOR + file->first;
                tempval.second = DIR_SEPARATOR + file->second;
                ret.push_back(tempval);
                aFoundfiles.push_back(*file);
                fileset.erase(file);
            } else
            {
                list<pair<string, string> >::iterator alreadyfound = FindFromList(filename, aFoundfiles, ERightValue);
                if (alreadyfound != aFoundfiles.end())
                {
                    cout << "Warning: More than one files matches for the given filename '" << filename;
                    cout << "' in the file set, only the first file is used." << endl;
                    aFoundfiles.erase(alreadyfound);
                }
            }
        }
    }
    ret.sort();
    return ret;
}

// ----------------------------------------------------------------------------
// BBCFileUtils::setTemp
// Set temp dir
// ----------------------------------------------------------------------------
//
void BBCFileUtils::setTemp(const string& aTempDir)
{
    iTempDir = aTempDir;
}


// ----------------------------------------------------------------------------
// BBCFileUtils::getFilesInDir
// Calculates quite unique fingerprint for a string.
// ----------------------------------------------------------------------------
//
unsigned int BBCFileUtils::quickHash(string str)
{
    int ret = 0;
    unsigned int len = (unsigned int)str.length();
    for (unsigned int i = 0; i < len; i++)
    {
        ret += (i+1) * str.at(i);
    }
    return ret;
}


// ----------------------------------------------------------------------------
// BBCFileUtils::trimFilenames
// 
// ----------------------------------------------------------------------------
//
/*
string BBCFileUtils::trimFilenames(string aFilenameList)
{
    string ret("");
    unsigned int i = 0;
    for (; i < aFilenameList.length(); i++)
    {
        char ch = aFilenameList.at(i);
        if (ch != ';')
        {
            ret += ch;
        } else 
        {
            ret += ' ';
        }
    }
    return ret;
}
*/
// ----------------------------------------------------------------------------
// BBCFileUtils::extractFilenames
// Extract filenames to string list 
// ----------------------------------------------------------------------------
//
list<pair<string, string> > BBCFileUtils::extractFilenames(string aFilenameList)
{
    size_t i = 0;
    list<pair<string, string> > ret;
    string current("");
    for (; i < aFilenameList.length(); i++)
    {
        char ch = aFilenameList.at(i);
        if (ch != ';')
        {
            current += ch;
        } else
        {
            pair<string, string> tempvar(current, toLowerCaseWin(current));
            ret.push_back(tempvar);
            current = "";
        }

    }
    if (current.length() > 0)
    {
        pair<string, string> tempvar(current, toLowerCaseWin(current));
        ret.push_back(tempvar);
    }
    return ret;
}

// ----------------------------------------------------------------------------
// BBCFileUtils::isValidFilename
// Check if the given filename is valid
// ----------------------------------------------------------------------------
//
bool BBCFileUtils::isValidFilename(const string& aFilename)
{
    bool valid = true;
    if (aFilename.length() < 1)
    {
        valid = false;
    }
    struct stat stats;
    int fSuccess = stat(aFilename.c_str(), &stats);
    // Check if path is pointing to a directory
    if (fSuccess == -1)
    {
        valid = false;
    } else if ((stats.st_mode & S_IFDIR) != 0)
    {
        valid = false;
    }

    return valid;
}

// ----------------------------------------------------------------------------
// BBCFileUtils::isValidDirectory
// Check if the given path is valid directory
// ----------------------------------------------------------------------------
//
bool BBCFileUtils::isValidDirectory(const string& aPath)
{
    bool valid = true;
    if (aPath.length() < 1)
    {
        valid = false;
    }
    struct stat stats;
    int fSuccess = stat(aPath.c_str(), &stats);
    // Check if path is pointing to a directory
    if (fSuccess == -1)
    {
        valid = false;
    } else if ((stats.st_mode & S_IFDIR) == 0)
    {
        valid = false;
    }

    return valid;
}

// ----------------------------------------------------------------------------
// BBCFileUtils::getFullPath
// Check if the given path is valid directory
// ----------------------------------------------------------------------------
//
string BBCFileUtils::getFullPath(const string& aPath)
{
    string ret;

#ifdef __WIN__
    char temppath[_MAX_PATH+2];
    char * filepart = NULL;
    GetFullPathName(aPath.c_str(), _MAX_PATH, temppath, &filepart);
    ret = temppath;
#else
    string path = aPath;
    string filename;
    struct stat statinfo;

    if ( 0 != stat(aPath.c_str(),&statinfo) )
    {
    filename = StripPath(aPath.c_str());
    path = aPath.substr(0,aPath.size()-filename.size());
    }

    if (path.size() == 0)
    {
        path = ".";
    }

    if ( !absolutePath(path,ret) )
    {
            throw HAException("Internal error: Error parsing path.");
    }

    if (filename.size())
    {
    ret += DIR_SEPARATOR;
    ret += filename;
    }
#endif
    
    return ret;
}


#ifdef __UNIX__
// ----------------------------------------------------------------------------
// BBCFileUtils::absolutePath
// Get full path
// ----------------------------------------------------------------------------
//
bool BBCFileUtils::absolutePath(const string& aRelpath, string& aAbspath)
{
    char* base = new char[_MAX_PATH+1];
    char* home;
    getcwd(base, _MAX_PATH);
    home = getenv("HOME");
    aAbspath = base;
    if (aRelpath.length() == 0)
    {
        aAbspath = "";
        return false;
    }
    vector<string> splittedabspath = splitString(aAbspath, '/');
    vector<string> splittedrelpath = splitString(aRelpath, '/');
    vector<string> splittedhomepath = splitString(home, '/');
    int longest;
    if (splittedabspath.size() > splittedhomepath.size())
    {
        longest = splittedabspath.size();
    } else
    {
        longest = splittedhomepath.size();
    }
    splittedabspath.reserve(longest + splittedrelpath.size());
    if (splittedrelpath.at(0) == "")
    {
        splittedabspath.clear();
        if (splittedrelpath.at(1) == "")
        {
            splittedabspath.push_back("");
            splittedabspath.push_back("");
        }
    }
    if (splittedrelpath.at(0) == "~")
    {
        splittedabspath = splittedhomepath;
        splittedrelpath.erase(splittedrelpath.begin());
    }
    vector<string>::iterator dir = splittedrelpath.begin();
    vector<string>::iterator dirend = splittedrelpath.end();
    for(; dir != dirend; dir++)
    {
        string dirstr = *dir;
        if (dirstr == "")
        {
            // Do nothing
        } else if (dirstr == ".")
        {
            // Do nothing
        } else if (dirstr == "..")
        {
            if (splittedabspath.size() > 1)
            {
                splittedabspath.pop_back();
            }
        } else
        {
            if (dirstr.find_first_not_of('.') == string::npos)
            {
              throw HAException("Illegal directory: '" + dirstr + "'\n");
            }
            splittedabspath.push_back(dirstr);
        }
    }
    dir = splittedabspath.begin();
    dirend = splittedabspath.end();
    if (dir != dirend && *dir == "")
    {
        dir++;
    }
    aAbspath = "";
    for(; dir != dirend; dir++)
    {
        aAbspath += '/';
        aAbspath += *dir;
    }
    return true;
}
#endif


// ----------------------------------------------------------------------------
// BBCFileUtils::getDirsInDir
// Get subdirectories in directory
// ----------------------------------------------------------------------------
//
list<pair<string, string> > BBCFileUtils::getDirsInDir(string aRelPath, list<pair<string, string> >& aExcludes)
{
    // STRAT -- Support for multiple header directories
    list<pair<string, string> > ret;
    list<pair<string, string> > dirs = BBCFileUtils::extractFilenames(iBaseDir);
    list<pair<string, string> >::iterator dirbegin = dirs.begin();
    for(; dirbegin != dirs.end(); dirbegin++)
    {
    // END -- Support for multiple header directories
        string basedir = BBCFileUtils::getFullPath(dirbegin->first);
   
        if (aRelPath != "")
        {
            iWildcard = basedir + DIR_SEPARATOR + aRelPath + DIR_SEPARATOR + WILDCARD_ALLFILES;
        } else
        {
            iWildcard = basedir + DIR_SEPARATOR + WILDCARD_ALLFILES;
        }

        // search for all files which were specified in wildcard string
#ifdef __WIN__
        _finddata_t finddata;
        intptr_t searchsession =_findfirst(iWildcard.c_str(),&finddata);
        int found = -1;
        if (searchsession > 0)
        {
            found = 0;
        }
        while (found == 0)
        {
            string filename = finddata.name;
            if (filename == "." || filename == "..")
            {
                // Do Nothing
            } else
            {
                if (aRelPath != "")
                {
                    filename = aRelPath + DIR_SEPARATOR + filename;
                }
                string fullpath = basedir + DIR_SEPARATOR + filename;
                //  Check if path is pointing to a directory
                if (isValidDirectory(fullpath))
                {
                    list<pair<string, string> >::const_iterator filereplace = FindFromList(toLowerCaseWin(filename), aExcludes, ERightValue);
                    if (filereplace == aExcludes.end())
                    {
                        filereplace = FindFromList(toLowerCaseWin(finddata.name), aExcludes, ERightValue);
                    }
                    if (filereplace == aExcludes.end())
                    {
                        pair<string, string> tempvar(filename, toLowerCaseWin(filename));
                        ret.push_back(tempvar);
                    }
                }
            }
            found = _findnext(searchsession, &finddata);
        }
        _findclose(searchsession);
#else
        //Wildcard.c_str());
        glob_t p_glob;
      
        int result = glob(iWildcard.c_str() , GLOB_ONLYDIR, NULL, &p_glob);
        if (result == 0)
        {
            for ( unsigned int i = 0; i < p_glob.gl_pathc; i++ )
            {
                string path = p_glob.gl_pathv[i];
                if (path.at(path.length() - 1) == '/')
                {
                    path.resize(path.length() - 1);
                }
                // Check if path is pointing to a directory
                if (isValidDirectory(path))
                {
                    string dirname = BBCFileUtils::StripPath(path);
                    path = dirname;
                    if (aRelPath != "")
                    {
                        path = aRelPath + DIR_SEPARATOR + dirname;
                    }
                    list<pair<string, string> >::const_iterator filereplace = FindFromList(toLowerCaseWin(path), aExcludes,ERightValue);
                    if (filereplace == aExcludes.end())
                    {
                        filereplace = FindFromList(toLowerCaseWin(dirname), aExcludes,ERightValue);
                    }
                    if (filereplace == aExcludes.end())
                    {
                        pair<string, string> tempvar(path, toLowerCaseWin(path));
                        ret.push_back(tempvar);
                    }
                }
            }  
            globfree(&p_glob);
        }

#endif
    }
    return ret;
}


// ----------------------------------------------------------------------------
// BBCFileUtils::StripPath
// Strip off path
// ----------------------------------------------------------------------------
//
string BBCFileUtils::StripPath(const string& aFilename) 
{
    size_t pos = aFilename.find_last_of("\\/");

    if (pos != string::npos) 
    {
        return string(aFilename.begin()+pos+1, aFilename.end());
    }
    return aFilename;
}

// ----------------------------------------------------------------------------
// BBCFileUtils::StripFilenameExtension
// Strip off filename extension
// ----------------------------------------------------------------------------
//
string BBCFileUtils::StripFilenameExtension(string aFilename) 
{
    string ret(aFilename);
    size_t pos = ret.find_last_of("\\/.");
    if (pos != string::npos)
    {
        string::iterator begin = ret.begin() + pos;
        string::iterator end = ret.end();
        if (*begin == '.')
            ret.erase(begin,end);
    }
    return ret;
}
/**
 * This function first splits strings in vectors. Then it finds the
 * first part, the common part and the last part of the directories
 * and combines them.
 */
 // Changes done to this function to Support for multiple header directories. Return type changed to list.
list<pair<string, bool> > BBCFileUtils::MergeDirs(const string& rootDirs, const string& subDir)
{
    // START -- Support for multiple header directories --
    list<pair<string, bool> > retu;
    list<pair<string, string> > dirs = BBCFileUtils::extractFilenames(rootDirs);
    list<pair<string, string> >::iterator dirbegin = dirs.begin();
    for(; dirbegin != dirs.end(); dirbegin++)
    {
        string ret;
        string rootDir = BBCFileUtils::getFullPath(dirbegin->first);
    // END -- Support for multiple header directories --
        vector<string> rootVector(splitString(rootDir, DIR_SEPARATOR));
        vector<string> subVector(splitString(subDir, DIR_SEPARATOR));

        vector<string>::iterator rootIt = rootVector.begin();
        vector<string>::iterator subIt = subVector.begin();

        bool commonFound = false;

        while( rootIt != rootVector.end() || subIt != subVector.end() )
        {
            string fixedRoot;
            string fixedSub;

            if( rootIt != rootVector.end() )
            {
                fixedRoot = *rootIt;
                toLower(fixedRoot);
            }

            if( subIt != subVector.end() )
            {
                fixedSub = *subIt;
                toLower(fixedSub);
            }

            if( rootIt != rootVector.end() && 
                subIt != subVector.end() )
            {            
                if( fixedRoot != fixedSub )
                {
                    if( ret.size() > 0 )
                        ret += DIR_SEPARATOR;

                    if( commonFound == false )
                    {
                        ret += fixedRoot;
                        ++rootIt;
                    }
                    else
                    {
                        ret += fixedSub;
                        ++subIt;
                    }                
                }
                else if( fixedRoot == fixedSub )
                {
                    if( ret.size() > 0 )
                        ret += DIR_SEPARATOR;
                    ret += fixedSub;
            
                    ++subIt;
                    ++rootIt;            
                    commonFound = true;
                }
            }
            else if( subIt != subVector.end() )
            {
                if( ret.size() > 0 )
                    ret += DIR_SEPARATOR;
                ret += fixedSub;

                ++subIt;
            }
            else
            {
                break;
            }
        }
#ifndef __WIN__
        ret=DIR_SEPARATOR+ret;
#endif
        // START -- Support for multiple header directories --
        pair<string, bool> tempvar(ret, subIt == subVector.end());
        retu.push_back(tempvar);
    }
    return retu;
        // END -- Support for multiple header directories --
}
map<string, bool> BBCFileUtils::fileExistsCache = map<string, bool>();
bool BBCFileUtils::FileExists(const string& fileName)
{    
    map<string, bool>::const_iterator i = fileExistsCache.find(fileName);
    if( i != fileExistsCache.end() )
    {
        return i->second;
    }
    fstream fin;
    fin.open(fileName.c_str(),ios::in);
    bool fileExists = fin.is_open();
    fin.close();
    fileExistsCache.insert(pair<string, bool>(fileName, fileExists));
    return fileExists;
}

string BBCFileUtils::getCompilationError(string filename)
{
	//Add compilation error to the report						
	std::ifstream file(filename.c_str());
	string templine;
	string compilationError;
	int size =0;
	int characterLimit = 2000;
	// Keep the character count of total line to be displayed in report to 2000.
	while(size <= characterLimit && std::getline(file,templine))
	{
		int index;
		string replaceFrom = "\'";
		string replaceTo = "`";
		size += templine.size();
		if(size > characterLimit)
			compilationError.append(".........");
		else
		{
			//Replace if any "'" with "`" , to work properly with stylesheet.
			if((index = (int)templine.find(replaceFrom))!= string::npos)
				templine.replace(index,replaceFrom.size(),replaceTo);
			compilationError.append(templine);
			compilationError.append("\n");


		}
	}

	return compilationError;
}

// ----------------------------------------------------------------------------------------------------------

string& BBCFileUtils::TrimRight(string& s)
{
	int pos(s.size());
	for (; pos && (s[pos-1]==' ' || s[pos-1]=='\t' || s[pos-1]=='\r'); --pos);
	s.erase(pos, s.size()-pos);
	return s;
}

// ----------------------------------------------------------------------------------------------------------

string& BBCFileUtils::TrimLeft(string& s)
{
	int pos(0);
	for (; s[pos]==' ' || s[pos]=='\t' || s[pos]=='\r'; ++pos);
	s.erase(0, pos);
	return s;
}

// ----------------------------------------------------------------------------------------------------------

string& BBCFileUtils::TrimAll(string& s)
{
	return TrimLeft(TrimRight(s));
}

