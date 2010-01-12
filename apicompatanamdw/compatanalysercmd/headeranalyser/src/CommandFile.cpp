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
#include <vector>

#include "CommandFile.h"
#include "HAException.h"
#include "Utils.h"

using namespace std;


// ----------------------------------------------------------------------------
// CommandFile::CommandFile
// File name is gien as parameter
// 
// ----------------------------------------------------------------------------
//
CommandFile::CommandFile(string aFilename) : iCmdBufLen(0), iCmdBuf(NULL)
{
    iFilename = aFilename;
}


// ----------------------------------------------------------------------------
// CommandFile::CommandFile
// ----------------------------------------------------------------------------
//
CommandFile::~CommandFile()
{
    if (iCmdBuf != NULL)
    {
        for (unsigned int i = 0; i < iCmdBufLen; i++)
        {
            delete [] iCmdBuf[i];
        }
        delete [] iCmdBuf;
        iCmdBuf = NULL;
    }
}


// ----------------------------------------------------------------------------
// CommandFile::getCommandBuffer
// ----------------------------------------------------------------------------
//
char** CommandFile::getCommandBuffer()
{
    readCommandFile(iFilename);
    return iCmdBuf;
}


// ----------------------------------------------------------------------------
// CommandFile::commandBufferLength
// 
// ----------------------------------------------------------------------------
//
size_t CommandFile::commandBufferLength()
{
    return iCmdBufLen;
}


// ----------------------------------------------------------------------------
// CommandFile::readCommandFile
// Reads parameters from the command file. 
// ----------------------------------------------------------------------------
//
void CommandFile::readCommandFile(string filename)
{
#if ( defined(_DEBUG) || defined(DEBUG) ) && !defined(NO_DBG)
    cout << "Reading command file\n";
#endif
    ifstream input(filename.c_str(), ios::in);
    if (!input.is_open())
    {
        throw HAException("Cannot open command file");
    }
    char c;
    string str;
    unsigned long linecount = 1;
    bool careForSpace = true;
    bool strSpace = false;
    bool whitespace = true;
    vector<string> parmlist;
    parmlist.push_back("padding");
    while (input.get(c))
    {
        if (c == ' ' && careForSpace == true)
        {
            if (whitespace == false)
            {
                parmlist.push_back(str);
            }
            str = "";
            whitespace = false;
            careForSpace = false;
        }else if (c == ' ' && strSpace == false)
        {
        }else if (c == '\\' || c == '/')
        {
            str += DIR_SEPARATOR;
        }else if (c == '"')
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
        }else if (c != '\n')
        {
            if (careForSpace == false && strSpace == false)
            {
                careForSpace = true;
            }
            str += c;
            whitespace = false;
        } else 
        {
            if (strSpace == true)
            {
                string line;
                ltoa(linecount, line, 10);
                throw HAException("Syntax error: New line has come before ending quotation mark(\"). Line: " + line);
            }
            if (str.length() != 0)
            {
                parmlist.push_back(str);
            }
            linecount++;
            str = "";
            whitespace = true;
        }
    }
    if (str.length() != 0)
    {
        parmlist.push_back(str);
    }

    // Store parameter information
    size_t elementcount = parmlist.size();
    iCmdBufLen = elementcount;
    if (iCmdBuf)
    {
        delete iCmdBuf;
        iCmdBuf = NULL;
    }
    iCmdBuf = new char*[elementcount];

    // Copy the parameter list from vector to char** 
    // (in order to be compatible with CommandLine::parse())
    for (unsigned int i = 0; i < parmlist.size(); i++)
    {
		size_t charcount = parmlist.at(i).length();
  
        iCmdBuf[i] = new char[charcount+1];
        const char* cbuf = parmlist.at(i).c_str();
    unsigned int j = 0;
        for(j = 0; j < charcount; j++)
        {
            iCmdBuf[i][j] = cbuf[j];
        }
        iCmdBuf[i][j] = '\0';
    }
}
