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
* Description:  Test case for requirement HABC004
*
*/


/**
 * Baseline platform header file for HeaderAnalyser 
 * test case HATC004
 */
#ifndef HATC004BASE_H
#define HATC004BASE_H

/**
 * HATC004BASE_class1
 */
class HATC004BASE_class1
{
public:
    HATC004BASE_class1();
    virtual ~HATC004BASE_class1();
protected:
    virtual int GetVal();
};

/**
 * HATC004BASE_class2
 */
class HATC004BASE_class2
{
    public:
    HATC004BASE_class2();
    virtual ~HATC004BASE_class2();
protected:
    virtual int GetValue();
    virtual void SetValue(int i);
};

/**
 * HATC004BASE_class3
 */
class HATC004BASE_class3
{
public:
    HATC004BASE_class3();
    virtual ~HATC004BASE_class3();

protected:
    virtual void RemoveThis();
};

/**
 * HATC004BASE_class4
 */
class HATC004BASE_class4 : public HATC004BASE_class3
{
public:
    HATC004BASE_class4();
    virtual ~HATC004BASE_class4();
};

/**
 * HATC004BASE_class5
 */
class HATC004BASE_class5 : public HATC004BASE_class4, public HATC004BASE_class2
{
public:
    HATC004BASE_class5();
    virtual ~HATC004BASE_class5();
};

/**
 * HATC004BASE_class6
 */
class HATC004BASE_class6
{
public:
    HATC004BASE_class6();
    virtual ~HATC004BASE_class6();
};

#endif