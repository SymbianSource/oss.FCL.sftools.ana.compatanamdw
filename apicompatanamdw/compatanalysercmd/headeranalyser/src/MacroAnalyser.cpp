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

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include "Utils.h"
#include "TChange.h"
#include "HAException.h"

using namespace std;

#include "MacroAnalyser.h"

// ----------------------------------------------------------------------------
// MacroAnalyser::MacroAnalyser
// ----------------------------------------------------------------------------
//
MacroAnalyser::MacroAnalyser(string filebase, string filecurrent, vector<string> basebundle, vector<string> currentbundle)
:iBaseFile(filebase), iCurrentFile(filecurrent), iBaseBundle(basebundle), iCurrentBundle(currentbundle)
{
}

// ----------------------------------------------------------------------------
// MacroAnalyser::~MacroAnalyser
// ----------------------------------------------------------------------------
//
MacroAnalyser::~MacroAnalyser(void)
{
}

// ----------------------------------------------------------------------------
// MacroAnalyser::Analyse
// ----------------------------------------------------------------------------
//
void MacroAnalyser::Analyse(list<string>& aMacroFiles)
{  
    ifstream basefile(iBaseFile.c_str(), ios::in);
    ifstream currentfile(iCurrentFile.c_str(), ios::in);

    map<string, list<pair<pair<string, string>,string> > > baseline;
    map<string, list<pair<pair<string, string>,string> > > current;
    
    baseline = parseMacros(basefile, iBaseBundle, &iRemoved, true);
    current = parseMacros(currentfile, iCurrentBundle);
    
    vector<string>::iterator curbegin = iCurrentBundle.begin();
    vector<string>::iterator curend = iCurrentBundle.end();
    vector<string>::iterator basebegin = iBaseBundle.begin();
    vector<string>::iterator baseend = iBaseBundle.end();
    map<string, TChange<list<pair<string,string> > > >::iterator removedbegin;
    for(;curbegin != curend; curbegin++)
    {
        string curfilename = *curbegin;
        string basefilename;
        if( basebegin != iBaseBundle.end() )
        {
            basefilename = *basebegin;
        }
        else
        {
            continue;
        }
        removedbegin = iRemoved.find(basefilename);
        if (removedbegin != iRemoved.end())
        {
            map<string, list<pair<pair<string, string>,string> > >::iterator cur = current.find(curfilename);
            if (cur == current.end())       // We need to check if there is a list with given filename
                                            // because they aren't created in situation where there isn't any macros
            {                               // specific to that file or the include guard for the file is duplicated.
                list<pair<pair<string, string>,string> > tempvar;
                pair<string, list<pair<pair<string, string>,string> > > tempvar2(curfilename, tempvar);
                pair<map<string, list<pair<pair<string, string>,string> > >::iterator, bool > pos = current.insert(tempvar2);
                if (pos.second == true)
                {
                    cur = pos.first;
                } else
                {                           // this shouldn't be happening
                    throw HAException("Problems ahead.");
                }
            }
            map<string, list<pair<pair<string, string>,string> > >::iterator base = baseline.find(basefilename);
            findDuplicates(basefilename,curfilename,base->second, cur->second, removedbegin->second, iBaseDuplicates, iCurrentDuplicates);
            
			//maintain a cache list of files with macros
			if(base->second.size() > 0)
				aMacroFiles.push_back(toLowerCaseWin(base->first));
			if(cur->second.size() > 0)
				aMacroFiles.push_back(toLowerCaseWin(cur->first));
			
			// After next loop we will have in list only those which has been either removed or changed
            list<pair<pair<string, string>,string> >::iterator begin = cur->second.begin();
            list<pair<pair<string, string>,string> >::iterator end = cur->second.end();
            for(;begin != end; begin++)
            {
				list<pair<string,string> >::iterator place = FindFromList(begin->first.first, removedbegin->second.GetValue());
                if (place != removedbegin->second.GetValue().end())
                {
                    removedbegin->second.GetValue().erase(place);  // we found macro with same name so we can remove it
                    list<pair<pair<string, string>,string> > baselist = base->second;
					list<pair<pair<string, string>,string> >::iterator found = FindFromList(begin->first.first, baselist, ELeftValue);
                    if (found != baselist.end())
                    {
						if (found->first.second != begin->first.second)
                        {   // Contents of macro are different so we need to add the macro to changed list
                            pair<pair<string,string>,string> changes;
							changes.first.first = found->first.second;
							changes.first.second = begin->first.second;
							changes.second = begin->second;
							pair<string, pair<pair<string, string>,string> > param(begin->first.first,changes);
                            map<string, TChange<map<string, pair<pair<string, string>,string> > > >::iterator file = iChanged.find(basefilename);
                            if (file != iChanged.end())
                            {
                                file->second.GetValue().insert(param);
                            } else
                            {
                                map<string, pair<pair<string, string>,string> > tempvar;
                                tempvar.insert(param);
                                TChange<map<string, pair<pair<string, string>,string> > > tempvar2(basefilename, curfilename, tempvar);
                                pair<string, TChange<map<string, pair<pair<string, string>,string> > > > tempvar3(basefilename, tempvar2);
                                iChanged.insert(tempvar3);
                            }
                        }
                    }
                }
            }
            removedbegin->second.SetCurrent(curfilename);
        }
        basebegin++;
    }  
}

// ----------------------------------------------------------------------------
// MacroAnalyser::FindMacro
// ----------------------------------------------------------------------------
//
pair<string, string> MacroAnalyser::FindMacro(string aLine)
{
    pair<string, string> ret;
    string::size_type pos = aLine.find_first_of(" \t");
    while(pos != string::npos && (aLine.at(pos) == ' ' || aLine.at(pos) == '\t') )
        pos++;
    string::size_type param_pos = pos ;
    pos = aLine.find_first_of(" \t(",param_pos);
    string value;
    if (pos != string::npos && aLine.at(pos) == '(')
    {
        pos = aLine.find(')',pos);
        if(pos !=string::npos )
            pos++;
    }
    if (pos != string::npos && pos < aLine.size())
    {   // only if there is stuff after name of macro we put it to value
        size_t value_pos = (unsigned int)pos + 1;
        value = aLine.substr(value_pos);
        value = trimWhiteSpace(value);
        if (value.size() != 0)
        {
            value_pos = value.find_first_not_of(" \t");
            if (value_pos != string::npos && value_pos != 0)
            {
                value = value.substr(value_pos);
            }
        }
    } else
    {   // otherwise we put empty value
        value = "";
    }

    string param = aLine.substr(param_pos, pos - param_pos);
    ret = pair<string,string>(param,value);
    return ret;
}

// ----------------------------------------------------------------------------
// MacroAnalyser::getRemoved
// ----------------------------------------------------------------------------
//
map<string, TChange<list<pair<string,string> > > >& MacroAnalyser::getRemoved()
{
    return iRemoved;
}

// ----------------------------------------------------------------------------
// MacroAnalyser::FindMacro
// readParameters should be called so that first is called baseline command
// and after that current command, otherwise it doesn't work
// ----------------------------------------------------------------------------
//
map<string, TChange<map<string, pair<pair<string, string>,string> > > >& MacroAnalyser::getChanged()
{
    return iChanged;
}

// ----------------------------------------------------------------------------
// MacroAnalyser::getBaseDuplicates
// ----------------------------------------------------------------------------
//
map<string, vector<pair<string,string> > >& MacroAnalyser::getBaseDuplicates()
{
    return iBaseDuplicates;
}

// ----------------------------------------------------------------------------
// MacroAnalyser::getCurrentDuplicates
// ----------------------------------------------------------------------------
//
map<string, vector<pair<string,string> > >& MacroAnalyser::getCurrentDuplicates()
{
    return iCurrentDuplicates;
}

// ----------------------------------------------------------------------------
// MacroAnalyser::parseMacros
// ----------------------------------------------------------------------------
//
map<string, list<pair<pair<string, string>,string> > > MacroAnalyser::parseMacros(ifstream& aFile, vector<string>& bundlefiles, map<string, TChange<list<pair<string,string> > > >* aRemoved, bool aAddToRemoved)
{
    // ret, is the file and related set of macros returned by the function
    map<string, list<pair<pair<string, string>,string> > > ret;
    vector<pair<string, string> > files;
    vector<string>::iterator bundlefile = bundlefiles.begin();
    vector<string>::iterator bundleend = bundlefiles.end();
    for(; bundlefile != bundleend; bundlefile++)
    {
        pair<string, string> bothcase(toLowerCaseWin(*bundlefile), *bundlefile);
        files.push_back(bothcase);
    }
    // Read macrofiles as lines
    string cline;
    string levelname = "";
    bool isbundle = false;
    while((cline = getLine(aFile)) != KEmpty)
    {
        string line = cline;
		char tempNo[6];
		string lineNo;
        unsigned int length = (unsigned int)line.length();
        if (length > 6 && line.at(0) == '#' && line.at(1) == ' ')
        {   // we may have found a file descriptor: '# xx "path/to/file.h"' or
            // '# xx "path/to/file.h" 1' or '# xx "path/to/file.h" 2'
            unsigned int index;
			int count = 0;
            for(index = 2; index < length; index++)
            {
                char ch = line.at(index);
                if (ch < '0' || ch > '9')
					break;
				else
				{
					tempNo[count] = ch;
					count++;
				}
            }
			tempNo[count] = '\0';
			lineNo.copy(tempNo,strlen(tempNo));
            index++;
            if (index < length)
            {
                unsigned int index2 = index + 1;
                for(; index2 < length; index2++)
                {
                    char ch = line.at(index2);
                    if (ch == '"') break;
                }
                if (length > index2 + 1)
                {
                    levelname = line.substr(index + 1, index2 - index - 1);
                } else
                {
                    levelname = line.substr(index + 1, length - index - 2);
                }
                string correctedname = "";
                string::size_type start = 0;
                string::size_type pos = levelname.find_first_of("\\/");
                while(pos != string::npos)
                {
                    correctedname += levelname.substr(start, pos - start);
                    correctedname += DIR_SEPARATOR;
                    start = pos + 1;
                    pos = levelname.find_first_of("\\/", start);
                }
                // found the levelname; filename
                correctedname += levelname.substr(start);
                levelname = toLowerCaseWin(correctedname);

                vector<pair<string, string> >::iterator begin = files.begin();
                vector<pair<string, string> >::iterator end = files.end();
                
                isbundle = false;
                for(; begin != end; begin++)
                {
                    if (begin->first == levelname)
                    {
                        isbundle = true;
                        levelname = begin->second;
                        break;
                    }
                }
            }
        }
        else if (isbundle == true && length > 8 && line.substr(0, 8) == "#define ")
        {   // we found preprocessor directive #define
            pair<string,string> macro = FindMacro(line);
            // 'ret' contains the set of files and associated macros to be returned from function
            map<string, list<pair<pair<string, string>,string> > >::iterator found = ret.find(levelname);
            bool exist = false;
            if( found != ret.end())
            {
				list< pair<pair<string, string>,string> >::iterator start = found->second.begin();
				list< pair<pair<string, string>,string> >::iterator end = found->second.end();
				
                // check if this macro is already defined, within this file(levelname)
                while(start != end)
                {
					if( macro.first == start->first.first )
                    exist = true;
                    start++;
                }
            }
            // if macro not found, add it to the list of macros associated with the current file
            if( !exist )
            {
				pair<pair<string,string>,string> tempVal(macro,tempNo);
				// if file already defined, only add the macro
                if (found != ret.end())
                {
					found->second.push_back(tempVal);
                }
                // else add both filename and asssociated macro
                else
                {				
                    list<pair<pair<string, string>,string> > values;
					values.push_back(tempVal);
                    pair<string, list<pair<pair<string, string>,string> > > newfile(levelname, values);
                    ret.insert(newfile);
                }
                // perform the same test as above on aRemoved data structure
                // this will be used for finding any duplicate macro definitions
                if (aAddToRemoved == true)
                {
					pair<string,string> temp(macro.first,tempNo);
                    map<string, TChange<list<pair<string,string> > > >::iterator found2 = aRemoved->find(levelname);
                    if (found2 != aRemoved->end())
                    {
                        found2->second.GetValue().push_back(temp);
                    } else
                    {
                        list<pair<string,string> > values;
                        values.push_back(temp);
                        TChange<list<pair<string,string> > > tempvar(levelname, values);
                        pair<string, TChange<list<pair<string,string> > > > newfile(levelname, tempvar);
                        aRemoved->insert(newfile);
                    }
                }
             } //if(!exist)
        }
    }
    return ret;
}

// ----------------------------------------------------------------------------
// MacroAnalyser::findDuplicates
// ----------------------------------------------------------------------------
//
bool MacroAnalyser::findDuplicates(const string& basefilename, const string& currentfilename, list<pair<pair<string, string>,string> >& aBaseline, list<pair<pair<string, string>,string> >& aCurrent, TChange<list<pair<string,string> > >& aRemovedList, map<string, vector<pair<string,string> > >& baselinedup, map<string, vector<pair<string,string> > >& currentdup)
{
    bool ret = false;
    map<pair<string,string>, int> dups;
    list<pair<pair<string, string>,string> >::iterator begin = aBaseline.begin();
    list<pair<pair<string, string>,string> >::iterator end = aBaseline.end();
    bool found = false;
    while(begin != end)
    {
        found = false;
        list<pair<pair<string, string>,string> >::iterator duplicates = begin;
        duplicates++;
		string original = begin->first.first;
		pair<string,string> original1(original,begin->second);
        while(duplicates != end)
        {
			if (original == duplicates->first.first)
            {
                found = true;
                pair<pair<string,string>, int> tempvar(original1, 1);
                dups.insert(tempvar);
                duplicates = aBaseline.erase(duplicates);
            } else
            {
                duplicates++;
            }
        }
        if(found)
        {
            ret = true;
            aRemovedList.GetValue().remove(original1);
            begin = aBaseline.erase(begin);
        } 
		    begin++;
    }

    if (dups.size() != 0)
    {
        vector<pair<string,string> > values;
        values.reserve(dups.size());
        map<pair<string,string>, int>::iterator dupsbegin = dups.begin();
        map<pair<string,string>, int>::iterator dupsend = dups.end();
        for(; dupsbegin != dupsend; dupsbegin++)
        {
            values.push_back(dupsbegin->first);
        }
        pair<string, vector<pair<string,string> > > tempvar(basefilename, values);
        baselinedup.insert(tempvar);
    }

    dups.clear();
    begin = aCurrent.begin();
    end = aCurrent.end();
    while(begin != end)
    {
        found = false;
        list<pair<pair<string, string>,string> >::iterator duplicates = begin;
        duplicates++;
		string original = begin->first.first;
		pair<string,string> original1(original,begin->second);
        while(duplicates != end)
        {
			if (original == duplicates->first.first)
            {
                found = true;
                pair<pair<string,string>, int> tempvar(original1, 1);
                dups.insert(tempvar);
                duplicates = aCurrent.erase(duplicates);
            } else
            {
                duplicates++;
            }
        }
        if (found == true)
        {
            ret = true;
            begin = aCurrent.erase(begin);
        } else
        {
            begin++;
        }
    }

    if (dups.size() != 0)
    {
        vector<pair<string,string> > values;
        values.reserve(dups.size());
        map<pair<string,string>, int>::iterator dupsbegin = dups.begin();
        map<pair<string,string>, int>::iterator dupsend = dups.end();
        for(; dupsbegin != dupsend; dupsbegin++)
        {
			string macroname = dupsbegin->first.first;
			pair<string,string> tempVal (macroname,dupsbegin->first.second);
            begin = aBaseline.begin();
            end = aBaseline.end();
            for(; begin != end; begin++)
            {   // we have to remove all macros, which have duplicates in current, from baseline
                // so that there won't be unnecessary warnings of removed macros
                if (begin->first.first == macroname)
                {
                    aBaseline.erase(begin);
                    break;
                }
            }
            values.push_back(tempVal);
        }
        pair<string, vector<pair<string,string> > > tempvar(currentfilename, values);
        currentdup.insert(tempvar);
    }
    return ret;
}
