/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description:  Test case for requirement HABC003
*
*/


/**
 * Baseline platform header file for HeaderAnalyser 
 * test case HATC003
 */
#ifndef HATC003BASE_H
#define HATC003BASE_H

class HATC003BASE_class1
{
public:
    IMPORT_C HATC003BASE_class1();
    IMPORT_C virtual ~HATC003BASE_class1();
};

class HATC003BASE_class2
{
public:
    IMPORT_C HATC003BASE_class2();
    IMPORT_C virtual ~HATC003BASE_class2();
};

class HATC003BASE_class3
{
public:
    IMPORT_C HATC003BASE_class3();
    IMPORT_C virtual ~HATC003BASE_class3();
};

class HATC003BASE_class5
{
public:
    IMPORT_C HATC003BASE_class5();
    IMPORT_C virtual ~HATC003BASE_class5();
protected:
    virtual int GetValue();
    virtual void SetValue(const int& a);
    virtual void RemoveThis();
};

#endif