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
#include <map>
#include "HAException.h"
#include "AnalyserParams.h"


using namespace std;


// ----------------------------------------------------------------------------
// AnalyserParams::parameterExists
// Return true, if the parameter parameter is given
// ----------------------------------------------------------------------------
//
bool AnalyserParams::parameterExists(const string& aParm)
{
    bool ret = false;
    map<string, pair<string, bool> >::iterator mapitem = iParameters.find(aParm);
    if (mapitem != iParameters.end())
    {
        ret = true;
    }
    return ret;
}

// ----------------------------------------------------------------------------
// AnalyserParams::givenParameter
// Return true, if the parameter parameter is given
// ----------------------------------------------------------------------------
//
bool AnalyserParams::givenParameter(const string& aParm)
{
    bool ret = false;
    map<string, pair<string, bool> >::iterator mapitem = iParameters.find(aParm);
    if (mapitem != iParameters.end())
    {
        ret = mapitem->second.second;
    }
    return ret;
}

// ----------------------------------------------------------------------------
// AnalyserParams::storeParameter
// Store given parameter to parameter map
// ----------------------------------------------------------------------------
//
void AnalyserParams::storeParameter(string aParm, string aVal, bool aFromCmdline)
{
    pair<string, pair<string, bool> >parameter(aParm,pair<string, bool>(aVal,aFromCmdline));
    map<string, pair<string, bool> >::iterator mapitem = iParameters.find(aParm);
    bool isValidParm = mapitem == iParameters.end() ? false : true;
    if (!isValidParm)
    {
        iParameters.insert(parameter);
    }
    else
    {
        if (((*mapitem).second).second == true) 
        {
            (*mapitem).second = pair<string,bool>(aVal,true);
        }
        else 
        {
            (*mapitem).second = pair<string,bool>(aVal,aFromCmdline);
        }
    }
}

// ----------------------------------------------------------------------------
// AnalyserParams::getParameter
// Store given parameter value
// ----------------------------------------------------------------------------
//
string AnalyserParams::getParameter(const string& aParm)
{
    map<string, pair<string, bool> >::iterator mapitem = iParameters.find(aParm);
    bool isValidParm = mapitem == iParameters.end() ? false : true;
    if (!isValidParm)
    {
        string excstr = "No such parameter: ";
        excstr += aParm;
        throw HAException(excstr);
    }
    return (mapitem->second).first;
}

// ----------------------------------------------------------------------------
// AnalyserParams::getGivenParameters
// ----------------------------------------------------------------------------
//
const map <string, string> AnalyserParams::getGivenParameters()
{
    map<string, string> givenparams;
    map<string, pair<string, bool> >::iterator begin = iParameters.begin();
    map<string, pair<string, bool> >::iterator end = iParameters.end();
    map<string, pair<string, bool> >::iterator find;
    map<string, pair<string, bool> >::iterator endfind = iParameters.end();
    while(begin != end)
    {
        string param = (*begin).first;
        pair<string, bool> values = (*begin).second;
        string val;
        if(values.second == true)
        {
            val = values.first;
            if (param == BASELINEDIR)
            {
                find =  iParameters.find(BASELINE);
                if (find != iParameters.end())
                {
                    val += DIR_SEPARATOR;
                    val += ((*find).second).first;
                }
            }
            if (param == BASELINE)
            {
                find =  iParameters.find(BASELINEDIR);
                val = ((*find).second).first;
                val += DIR_SEPARATOR;
                val += values.first;
            }
            if (param == CURRENT)
            {
                find =  iParameters.find(CURRENTDIR);
                val = ((*find).second).first;
                val += DIR_SEPARATOR;
                val += values.first;
            }
            givenparams.insert(pair<string,string>(param,val));
        }
        ++begin;
    }
    return givenparams;
}
