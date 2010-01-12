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


#ifndef __UTILS_H__
#define __UTILS_H__

#ifdef __WIN__
#pragma warning(disable:4786)
#endif

#include <stdio.h>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <stdarg.h>

using namespace std;

#define _X(s) XMLString::transcode(s)
#define _XX(s) XMLString::release(&s)

#define __FUN_MANGLED__ "__MANGLED__"

// Mostly used for implementation of headeranalyser
enum TValue
    { 
    ELeftValue = 0,
    ERightValue 
    };

// Used for implementation of testing program for headeranalyser
const string KEmpty = "_DEADBEEF_DEADBEEF_";


/**
* Convert integer to string
* @param value value to convert
* @param str reference to string where to convert
* @param radix numeric base into which to convert
* @return number converted to string
*/ 
string itoa(int value, string& str, int radix);

/**
* Convert long to string
* @param value value to convert
* @param str reference to string where to convert
* @param radix numeric base into which to convert
* @return number converted to string
*/ 
string ltoa(long value, string& str, int radix);

/**
* Find from list
* @param aValue value to find
* @param aList where to find
* @param comparator comparator funtion
* @param comparatorparam true, if comparator is used 
* @return string list
*/ 
list<string>::iterator FindFromList(const string& aValue, list<string>& aList, bool(*comparator)(const string&,const string&,bool)=0, bool comparatorparam=true);

/**
* Find from list of paired string
* @param aValue value to find
* @param aList where to find
* @param comparator comparator funtion
* @param comparatorparam true, if comparator is used 
* @return string list
*/ 
list<pair<string, string> >::iterator FindFromList(const string& aValue, list<pair<string,string> >& aList, bool(*comparator)(const string&,const string&,bool)=0, bool comparatorparam=true);

/**
* Find from list
* @param aValue value to find
* @param aList where to find
* @param compareTo compare left or right value
* @param comparator comparator funtion
* @param comparatorparam true, if comparator is used 
* @return string list
*/ 
list<pair<string, string> >::iterator FindFromList(const string& aValue, list<pair<string, string> >& aList, TValue compareTo, bool(*comparator)(const pair<string,string>&, const string&,bool)=0, bool comparatorparam=true, bool comparewholeString=false);

/**
* Find from list of paired string
* @param aValue value to find
* @param aList where to find
* @param compareTo compare left or right value
* @param comparator comparator funtion
* @param comparatorparam true, if comparator is used 
* @return string list
*/ 
list<pair<pair<string, string>,string> >::iterator FindFromList(const string& aValue, list<pair<pair<string, string>,string> >& aList, TValue compareTo, bool(*comparator)(const pair<string,string>&, const string&,bool)=0, bool comparatorparam=true, bool comparewholeString=false);
/**
* Convert integer to string
* @param aString string to convert
* @return lowercase string
*/ 
string toLowerCaseWin(string aString);

/**
* Convert integer to string
* @param aString string to convert
* @return lowercase string
*/ 
string toLowerCase(string aString);

/**
* Convert integer to string
* @param aString string to convert
* @return uppercase string 
*/ 
string toUpperCase(string aString);

/**
* Compare files
* @param tocompare to which to compare
* @param comparestr what to compare
* @param tryfilename if this is true, bare filenames are compared to each other
* @return true if match found
*/ 
bool compareFiles(const string& tocompare, const string& comparestr, bool tryfilename = true);

/**
* Compare files
* @param tocompare to which to compare
* @param comparestr what to compare
* @param tryfilename if this is true, bare filenames are compared to each other
* @return true if match found
*/ 
bool compareFiles(const pair<string, string>& tocompare, const string& comparestr, bool tryfilename = true);

/**
* Return the index of the rightmost directory separator in
* the given string
*
* @param aFilename filename to search for
* @return index
*/ 
string::size_type rightmostDirSeparatorIndex(const string& aFilename);

/**
* Removes leading and trailing whitespace from given string between start and 
* end position and returns that trimmed string (without parts outside specified 
* scope).
*
* @param aString value
* @param aStartpos where to start trimming
* @param aEndpos where to end trimming
* @return trimmed string
*/ 
string trimWhiteSpace(string& aString, string::size_type aStartpos = 0, string::size_type aEndpos = string::npos);


/**
* Get line from input stream
* @param aInput value
* @return line as string
*/ 
string getLine(istream& aInput);


/**
* Parses commandline parameters
* @param args commandline arguments as string
* @return command line parameters as list
*/ 
//list<string> parseCommandlineParameters(string args);


/**
* Check if the given string is numeric
* @param str string to check
* @return true, if string is numeric
*/ 
bool isNum(string str);


/**
* Check if the given string is alpha
* @param str string to check
* @return true, if string is alpha 
*/ 
bool isAlpha(string str);


/**
* Check if the given string is alphanumeric
* @param str string to check
* @return true, if string is alphanumeric
*/ 
bool isAlphaNum(string str);


/**
* Split string
* @param str string to split
* @param separator separator char
* @return splitted string
*/ 
vector<string> splitString(const string& str, char separator=' ');


/**
* Trims white space
* @param aControlString format string
* @return  formated string
*/ 
//string printToString(string& aControlString, ...);


/**
* Trims white space
* @param aControlString format string
* @param params list of params to format
* @return formatted string
*/ 
string printToString(string& aControlString, list<string> params);

/**
* Replaces all occurences of the given character in a string by another one.
* @param str reference to the string, which should be converted.
* @param replaceFrom character that should be replaced by another.
* @param replaceTo The replacing character.
*/
void replaceChar(string& str, char replaceFrom, char replaceTo);

/**
* Remove base part from a string
* @param aString string to be processed
* @param aBase string to be removed
* @return string with base part removed
*/
string removeBase(string aString, string aBase);

/**
* Remove any leading directory separators from a string
* @param aString string to be trimmed
* @return leading directory separator trimmed string
*/
string trimLeadingDirSeparator(string aString);

/**
* Comare base file with current file
* after excluding sub dirs each time until string ends
* @param aBasestr base file string
* @param aCurstr base file string
* @return true if base string matches with current string anytime after 
*  excluding sub dirs.Else false.
*/
bool compareWholeFileStrings(const string& aBasestr,const string& aCurstr);

#define KEY_STRUCT "struct "
#define KEY_ENUM "enum"
#define KEY_MACRO "#define "

#endif
