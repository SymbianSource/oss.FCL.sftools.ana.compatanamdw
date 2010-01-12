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

#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include <sstream>
#include <locale>
#include <map>
#include <vector>
#include "Utils.h"
#include "HAException.h"
#include "BBCFileUtils.h"
#include "XMLUtils.h"

using namespace std;

// ----------------------------------------------------------------------------
// itoa
// Convert integer to string
// ----------------------------------------------------------------------------
//
string itoa(int value, string& str, int radix)
{
  ostringstream ostr;
  ostr << value;
  str = ostr.str();
  return str;
}

// ----------------------------------------------------------------------------
// ltoa
// Convert long integer to string
// ----------------------------------------------------------------------------
//
string ltoa(long value, string& str, int radix)
{
    ostringstream ostr;
    ostr << value;
    str = ostr.str();
    return str;
}


// ----------------------------------------------------------------------------
// FindFromList
// Find value from list
// ----------------------------------------------------------------------------
//
list<string>::iterator FindFromList(const string& aValue, list<string>& aList, bool(*comparator)(const string&, const string&, bool), bool comparatorparam)
{
    list<string>::iterator begin = aList.begin();
    list<string>::iterator end = aList.end();
    bool found = false;
    while(begin != end && found == false)
    {
        if (comparator != 0 && (*comparator)(*begin, aValue, comparatorparam))
        {
            found = true;
        } else if (comparator == 0 && *begin == aValue)
        {
            found = true;
        }
        else
        {
            begin++;
        }
    }

    return begin;
}

// ----------------------------------------------------------------------------
// FindFromList
// Find value from list
// ----------------------------------------------------------------------------
//
list<pair<string,string> >::iterator FindFromList(const string& aValue, list<pair<string,string> >& aList, bool(*comparator)(const string&, const string&, bool), bool comparatorparam)
{
    list<pair<string,string> >::iterator begin = aList.begin();
    list<pair<string,string> >::iterator end = aList.end();
    bool found = false;
    while(begin != end && found == false)
    {
		if (comparator != 0 && (*comparator)(begin->first, aValue, comparatorparam))
        {
            found = true;
		} else if (comparator == 0 && begin->first == aValue)
        {
            found = true;
        }
        else
        {
            begin++;
        }
    }

    return begin;
}
// ----------------------------------------------------------------------------
// FindFromList
// Find value from list
// 
// ----------------------------------------------------------------------------
//
list<pair<string, string> >::iterator FindFromList(const string& aValue, list<pair<string, string> >& aList, TValue compareTo, bool(*comparator)(const pair<string,string>&, const string&, bool), bool comparatorparam,bool comparewholeString)
{
    list<pair<string, string> >::iterator begin = aList.begin();
	list<pair<string, string> >::iterator begin1 = aList.begin();
    list<pair<string, string> >::iterator end = aList.end();
	
    bool found = false;
	while(comparewholeString == true && begin1 != end && found == false)
	{// First check both the file matches or not
		if(aValue.compare(begin1->second)== 0 )
			found = true;
	 // Now compare base file with  current file after sperating sub dirs of currrent file each time  
		else if(compareWholeFileStrings(aValue,begin1->second) == true )
		     found = true;
		else
			begin1++;

		if(found == true)
			return begin1;		
	}
    while(begin != end && found == false)
    {
        if (comparator != 0 && (*comparator)(*begin, aValue, comparatorparam))
        {
            found = true;
        } else if (comparator == 0 && compareTo == ELeftValue && begin->first == aValue)
        {
            found = true;
        } else if (comparator == 0 && compareTo == ERightValue && begin->second == aValue)
        {
            found = true;
        }
        else
        {
            begin++;
        }
    }

    return begin;
}

// ----------------------------------------------------------------------------
// FindFromList
// Find value from list
// 
// ----------------------------------------------------------------------------
//
list<pair<pair<string, string>,string> >::iterator FindFromList(const string& aValue, list<pair<pair<string, string>,string> >& aList, TValue compareTo, bool(*comparator)(const pair<string,string>&, const string&, bool), bool comparatorparam,bool comparewholeString)
{
    list<pair<pair<string, string>,string> >::iterator begin = aList.begin();
	list<pair<pair<string, string>,string> >::iterator begin1 = aList.begin();
	list<pair<pair<string, string>,string> >::iterator end = aList.end();
	
    bool found = false;
	while(comparewholeString == true && begin1 != end && found == false)
	{// First check both the file matches or not
		if(aValue.compare(begin1->first.second)== 0 )
			found = true;
	 // Now compare base file with  current file after sperating sub dirs of currrent file each time  
		else if(compareWholeFileStrings(aValue,begin1->first.second) == true )
		     found = true;
		else
			begin1++;

		if(found == true)
			return begin1;		
	}
    while(begin != end && found == false)
    {
		if (comparator != 0 && (*comparator)(begin->first, aValue, comparatorparam))
        {
            found = true;
		} else if (comparator == 0 && compareTo == ELeftValue && begin->first.first == aValue)
        {
            found = true;
		} else if (comparator == 0 && compareTo == ERightValue && begin->first.second == aValue)
        {
            found = true;
        }
        else
        {
            begin++;
        }
    }

    return begin;
}

// ----------------------------------------------------------------------------
// trimWhiteSpace
// Remove any white space from given string
// startpos and endpos are optional parameters, defining the string under consideration
// returns a NULL, if the input is empty or contains only '\t' or '\n' or ' '
// ----------------------------------------------------------------------------
//
string trimWhiteSpace(string& aString, string::size_type aStartpos, string::size_type aEndpos)
{
	string ret = aString.substr( aStartpos, aEndpos);

	string::size_type startpos = ret.find_first_not_of(" \t\n\r",aStartpos);
	string::size_type endpos = ret.find_last_not_of(" \t\n\r");

	//if the string is empty, either NULL or only newline character, return a NULL string
	if( string::npos == startpos || KEmpty == ret)
		return "";
	//else return the substr without whitespace at start and end of given string
	else
		return ret.substr( startpos, endpos - startpos + 1);
}


// ----------------------------------------------------------------------------
// printToString 
// Substitute for printf 
// ----------------------------------------------------------------------------
//
#if 0
string printToString(string& aControlString, list<string> params)
{
    istringstream input(aControlString);
    ostringstream output;
    string ret;
    char ch;
    list<string>::iterator paramlist = params.begin();
    list<string>::iterator paramend = params.end();
    while(input.get(ch))
    {
        if (ch == '%')
        {
            char newch = '\0';
            input.get(newch);
            if (newch != '\0')
            {
                switch(newch)
                {
                case '%':
                    output << ch;
                    break;
                case 's':
                case 'd':
                case 'f':
                    {
                        string temp;
                        if (paramlist == paramend)
                        {
                            throw HAException("Syntax error: Not enough parameters for given control string.");
                        }
                        temp = *paramlist;
                        output << temp;
                        paramlist++;
                        break;
                    }
                default:
                    output << ch << newch;
                }
            } else
            {
                output << ch;
            }
        } else
        {
            output << ch;
        }
    }
    ret = output.str();
    return ret;
}
#endif
// ----------------------------------------------------------------------------
// getLine 
// Get line from input stream
// ----------------------------------------------------------------------------
//
string getLine(istream& aInput)
{
    string line = KEmpty;
    char ch = 0;
    while(aInput.get(ch) && ch != '\n')
    {
        if (line == KEmpty)
        {
            line = "";
        }
        line += ch;
    }
    if (ch == '\n' && line == KEmpty)
    {
        line = "";
    }
    return line;
}


// ----------------------------------------------------------------------------
// parseCommandlineParameters 
// ----------------------------------------------------------------------------
//
list<string> parseCommandlineParameters(string args)
{
    istringstream input(args);
    char ch;
    string str;
    bool careForSpace = true;
    bool strSpace = false;
    bool whitespace = true;
    list<string> parmlist;
    while (input.get(ch))
    {
        if (ch == ' ' && careForSpace == true)
        {
            if (whitespace == false)
            {
                parmlist.push_back(str);
            }
            str = "";
            whitespace = false;
            careForSpace = false;
        }else if (ch == ' ' && strSpace == false)
        {
            // Do nothing
        }else if (ch == '"')
        {
            if (strSpace == false)
            {
                careForSpace = false;
                strSpace = true;
            } else
            {
                careForSpace = true;
                strSpace = false;
            }
            whitespace = false;
        } else if (ch == '\n')
        {
            throw HAException("Syntax error: Newline not accepted in parameter list.");
        } else
        {
            if (careForSpace == false && strSpace == false)
            {
                careForSpace = true;
            }
            str += ch;
            whitespace = false;
        }
    }
    if (strSpace == true)
    {
        throw HAException("Syntax error: End of string before ending quotation mark.");
    }
    if (str.length() != 0)
    {
        parmlist.push_back(str);
    }
    return parmlist;
}


// ----------------------------------------------------------------------------
// isNum 
// Return if the given string is number
// ----------------------------------------------------------------------------
//
bool isNum(string str)
{
    istringstream strnum(str);
    char ch;
    bool ret = false;
    while(strnum.get(ch))
    {
        ret = (0 != isdigit(ch));
        if (ret == false)
        {
            break;
        }
    }
    return ret;
}

// ----------------------------------------------------------------------------
// isAlpha 
// Return if the given string is alphan
// ----------------------------------------------------------------------------
//
bool isAlpha(string str)
{
    istringstream strnum(str);
    char ch;
    bool ret = false;
    while(strnum.get(ch))
    {
        ret = (0 != isalpha(ch));
        if (ret == false)
        {
            break;
        }
    }
    return ret;
}

// ----------------------------------------------------------------------------
// isAlphaNum 
// Return if the given string is alphanumeric
// ----------------------------------------------------------------------------
//
bool isAlphaNum(string str)
{
    istringstream strnum(str);
    char ch;
    bool ret = false;
    while(strnum.get(ch))
    {
        ret = (0 != isalnum(ch));
        if (ret == false)
        {
            break;
        }
    }
    return ret;
}

// ----------------------------------------------------------------------------
// toLowerCaseWin 
// Convert given string to lower case
// ----------------------------------------------------------------------------
//
string toLowerCaseWin(string aString)
{
    string ret;
    char* tempvar;
    unsigned int len = (unsigned int)aString.length();

    tempvar = new char[len + 1];
    strcpy(tempvar, aString.c_str());
#ifdef __WIN__
   TO_LOWER_CASE;
#else
   ret=tempvar;
#endif
	delete[] tempvar;
    return ret;
}

// ----------------------------------------------------------------------------
// toLowerCaseW
// Convert given string to lower case
// ----------------------------------------------------------------------------
//
string toLowerCase(string aString)
{
    string ret;
    char* tempvar;
    unsigned int len = (unsigned int)aString.length();

    tempvar = new char[len + 1];
    strcpy(tempvar, aString.c_str());

    TO_LOWER_CASE;

    delete[] tempvar;
    return ret;
}

// ----------------------------------------------------------------------------
// toUpperCase 
// Convert given string to upper case
// ----------------------------------------------------------------------------
//
string toUpperCase(string aString)
{
    string ret;
    char* tempvar;
    unsigned int len = (unsigned int)aString.length();

    tempvar = new char[len + 1];
    strcpy(tempvar, aString.c_str());
/*
#ifdef __WIN__
    ret = strupr(tempvar);
#else
    for(unsigned int i = 0; i < len; i++)
    {
      tempvar[i] = std::toupper(tempvar[i]);
    }
    ret = tempvar;
#endif
*/
    TO_UPPER_CASE;
    return ret;
}

// ----------------------------------------------------------------------------
// splitString 
// Split string
// ----------------------------------------------------------------------------
//
vector<string> splitString(const string& str, char separator)
{
    vector<string> ret;
    string::size_type pos = str.find(separator);
    unsigned int lastpos = 0;
    while(pos != string::npos)
    {
        ret.push_back(str.substr(lastpos, pos - lastpos));
        lastpos = (unsigned int)pos + 1;
        pos = str.find(separator, lastpos);
    }
    if (!str.empty())
    {
        ret.push_back(str.substr(lastpos, pos));
    }
    return ret;
}


// ----------------------------------------------------------------------------
// compareFiles 
// ----------------------------------------------------------------------------
//
bool compareFiles(const string& tocompare, const string& comparestr, bool tryfilename)
{
    bool ret = false;
    string tocomp(tocompare);
    string compstr(comparestr);
    toLower(tocomp);
    toLower(compstr);
    
    if (tocomp.compare(compstr) == 0)
    {
        ret = true;
    } else if (tryfilename == false)
    {
        // Do nothing
    } else
    {
        if (compstr == BBCFileUtils::StripPath(compstr))
        {
            tocomp = BBCFileUtils::StripPath(tocomp);
            if (tocomp.compare(compstr) == 0)
            {
                ret = true;
            }
        }
    }
    return ret;
}

// ----------------------------------------------------------------------------
// compareFiles 
// ----------------------------------------------------------------------------
//
bool compareFiles(const pair<string, string>& tocompare, const string& comparestr, bool tryfilename)
{
    bool ret = false;
    //string tempvar(tocompare.second);
    if (tocompare.second.compare(comparestr) == 0)
    {
        ret = true;
    } else if (tryfilename == false)
    {
        // Do nothing
    } else
    {
        if (rightmostDirSeparatorIndex(comparestr) == string::npos || rightmostDirSeparatorIndex(comparestr) == 0)
        {
            string tempcomparestr(BBCFileUtils::StripPath(comparestr));
            string tempvar(BBCFileUtils::StripPath(tocompare.second));           
            if (tempvar.compare(tempcomparestr) == 0)
            {
                ret = true;
            }
        }
    }
    return ret;
}


// ----------------------------------------------------------------------------
// rightmostDirSeparatorIndex 
// Return the index of the rightmost directory separator
// ----------------------------------------------------------------------------
//
string::size_type rightmostDirSeparatorIndex(const string& aFilename)
{
    string::size_type idx = aFilename.rfind(DIR_SEPARATOR);
    return idx;
}
// ----------------------------------------------------------------------------
// replaceChar 
// Replaces all occurences of the character by another one.
// Example: 
// <code>
// string myStr("c:/temp/config.txt");
// replaceChar(myStr, '/', '\\');
// std::cout << myStr << std::endl;
// </code>
// Above example will print out the following string:
// c:\temp\config.txt
// ----------------------------------------------------------------------------
//
void replaceChar(string& str, char replaceFrom, char replaceTo)
{
    if( str.length() > 0 )
    {        
        string::size_type index = 0;
        while( (index = str.find(replaceFrom, index)) != string::npos )
        {     
            str.replace(index,1,1,replaceTo);
        }
    }
}


// ----------------------------------------------------------------------------
// removeBase 
// Remove base part from a string
// ----------------------------------------------------------------------------
//
string removeBase(string aString, string aBase)
{  
    string::size_type pos = toLowerCaseWin(aString).find(toLowerCaseWin(aBase),0);
    if ( pos == string::npos )
        return NULL;
    return aString.substr(aBase.length());
}

// ----------------------------------------------------------------------------
// trimLeadingDirSeparator 
// Remove any leading directory separators from a string
// ----------------------------------------------------------------------------
//
string trimLeadingDirSeparator(string aString)
{
    int pos = 0;       
    while ( aString[pos] == '\\' || aString[pos] == '/' )
        ++pos;
    if ( (aString.length() - pos) > 255 )
        return NULL;
    return aString.substr(pos);
}
//------------------------------------------------------------------
//compareWholeFileStrings 
// Comare base file with current file after excluding sub dirs each time until string ends
// return true if base string matches with current string anytime after excluding sub dirs.Else false.
//------------------------------------------------------------------

bool compareWholeFileStrings(const string& aBasestr,const string& aCurstr)
{
	bool ret = false;
	char separator = DIR_SEPARATOR;
	unsigned int lastpos = 0;
	string tmpStr;
    string::size_type pos = aCurstr.find(separator);
	while(pos != string::npos && ret == false)
	{
		tmpStr.clear();
		lastpos = (unsigned int)pos + 1;
		pos = aCurstr.find(separator, lastpos);
		if(pos!= string::npos)
		{
			tmpStr.append(aCurstr.substr(pos, string::npos));
			if(tmpStr.compare(aBasestr) == 0)
				ret = true;
		}
	}
	return ret;
}
