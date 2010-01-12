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


#ifndef __ANALYSERPARAMS_H__
#define __ANALYSERPARAMS_H__

#ifdef __WIN__
#pragma warning(disable:4786)
#endif

#include <string>
#include <map>

using namespace std;

/**
* AnalyserParams is used as a container for parameters given from commandline 
* and internal parameters.
*/
class AnalyserParams
{
public:
    /**
    * Check if the parameter exist
    * @param aParm param to check
    * @return true/false
    */  
    bool parameterExists(const string& aParm);

    /**
    * Check if the parameter is given
    * @param aParm param to check
    * @return true if the parameter is given
    */  
    bool givenParameter(const string& aParm);

    /**
    * Store the parameter
    * @param parm parameter to store
    * @param val parameter value
    * @param aFromCmdline (true if the parameter is read from the commandline)
    */  
    void storeParameter(string parm, string val, bool aFromCmdline = false);

    /**
    * Get given parameter
    * @param parm given parameter 
    * @return value of the give parameter
    */  
    string getParameter(const string& parm);

    /**
    * Get given parameters from the parameter map
    * @return map of given parameters
    */  
    const map <string, string> getGivenParameters();

private:
    //! map of Header analyser parameters
    map<string,pair<string,bool> > iParameters;
};
#endif
