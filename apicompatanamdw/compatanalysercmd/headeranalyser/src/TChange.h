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


#ifndef __TCHANGE_H__
#define __TCHANGE_H__

#include <string>
#include <list>
#include <utility>

using namespace std;

/**
* This template is used for making it a little easier to keep information about 
* which files the value is associated, namely base and current files. 
* At the moment used only in MacroAnalyser.
*/
template <class KTvalue> class TChange
{
public:
    TChange(string aBase, KTvalue aValue);
    TChange(string aBase, string aCurrent, KTvalue aValue);
    ~TChange(void);
    string GetBase();
    string GetCurrent();
    KTvalue& GetValue();
    void SetBase(string aBase);
    void SetCurrent(string aCurrent);
    void SetValue(KTvalue aValue);
private:
    pair<list<string>, KTvalue> iValue;
};

template <class KTvalue> TChange<KTvalue>::TChange(string aBase, KTvalue aValue)
{
    iValue.first.push_back(aBase);
    iValue.second = aValue;
}

template <class KTvalue> TChange<KTvalue>::TChange(string aBase, string aCurrent, KTvalue aValue)
{
    iValue.first.push_back(aBase);
    iValue.first.push_back(aCurrent);
    iValue.second = aValue;
}

template <class KTvalue> TChange<KTvalue>::~TChange(void)
{
}

template <class KTvalue> string TChange<KTvalue>::GetBase()
{
    return iValue.first.front();
}

template <class KTvalue> string TChange<KTvalue>::GetCurrent()
{
    string ret;
    if (iValue.first.size() == 2)
    {
        ret = iValue.first.back();
    } else
    {
        ret = "";
    }

    return ret;
}

template <class KTvalue> KTvalue& TChange<KTvalue>::GetValue()
{
    return iValue.second;
}

template <class KTvalue> void TChange<KTvalue>::SetBase(string aBase)
{
    iValue.first.pop_front();
    iValue.first.push_front(aBase);
}

template <class KTvalue> void TChange<KTvalue>::SetCurrent(string aCurrent)
{
    if (iValue.first.size() == 2)
    {
        iValue.first.pop_back();
        iValue.first.push_back(aCurrent);
    } else
    {
        iValue.first.push_back(aCurrent);
    }
}

template <class KTvalue> void TChange<KTvalue>::SetValue(KTvalue aValue)
{
    iValue.second = aValue;
}

#endif
