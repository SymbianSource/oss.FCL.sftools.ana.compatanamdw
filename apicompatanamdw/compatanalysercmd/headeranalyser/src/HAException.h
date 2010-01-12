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


#ifndef __HAEXCEPTION_H__
#define __HAEXCEPTION_H__
#include "CmdGlobals.h"
#ifdef __WIN__
#pragma warning(disable:4786)
#endif
#include <string>
using namespace std;

class HAException 
{
public:
    /**
    * Set error message to member variable    
    * @param message error message to set
    */ 
    HAException(string message);

    /**
    * Return error message previously set
    * @return error message
    */ 
    string errorMessage();

private:
    //! Severity level of the error
    int     iSeverity;
    //! Error message to return
    string  iErrorMessage;
};

#endif
