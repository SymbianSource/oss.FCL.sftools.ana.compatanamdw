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


#ifndef __COMMAND_FILE_H__
#define __COMMAND_FILE_H__
#include "CmdGlobals.h"
#ifdef __WIN__
#pragma warning(disable:4786)
#endif
#include <string>

using namespace std;

/**
* The CommandFile class is a utility class for the CommandLine class,
* so that the CommandLine class can represent the given parameters 
* in a unified way given in a command line or a command file. This 
* class utilizes command file parsing if needed. 
*/
class CommandFile
{
public:
    /**
    * Constructor
    * @param filename command filename
    */
    CommandFile(string filename);

    /**
    * Destructor
    */
    ~CommandFile();

public:

    /**
    * Get Header analyser commandline parameters
    * @return pointer to commandline params
    */
    char**  getCommandBuffer();

    /**
    * Get command buffer length
    * @return command buffer length
    */
    size_t  commandBufferLength();

    /**
    * Replace tab charecters in file
    * @param filename file to which characters are replaced
    */
    //void replaceTabs(string filename);

private:
    /**
    * Reads parameters from the command file. Basically works just as 
    * CommandLine's equivalent function
    * @param filename command filename
    * @exception an exception is thrown in case the file can't be opened.
    */
    void readCommandFile(string filename);

private:
    //! command buffer length
    size_t   iCmdBufLen;

    //! Command filename (eg. Commandfile.txt)
    string  iFilename;

    //! Pointer to commandline parameters
    char**  iCmdBuf;
};

#endif
