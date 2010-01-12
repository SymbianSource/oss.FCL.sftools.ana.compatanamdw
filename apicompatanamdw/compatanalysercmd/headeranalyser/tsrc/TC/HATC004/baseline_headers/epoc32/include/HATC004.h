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
#ifndef HATC004_H
#define HATC004_H

#include "HATC004BASE.h"
/**
 * HATC004_class1
 * Tests that the adding of virtual function is reported.
 */
class HATC004_class1
{
public:
    HATC004_class1();
    virtual ~HATC004_class1();
};

/**
 * HATC004_class2
 * Tests that the removing of virtual table is reported.
 */
class HATC004_class2
{
public:
    HATC004_class2();
    virtual ~HATC004_class2();
};

/**
 * HATC004_class3
 * Tests that the removing of virtual function is reported.
 */
class HATC004_class3
{
public:
    HATC004_class3();
    virtual ~HATC004_class3();

protected:
    virtual int GetValue();
};

/**
 * HATC004_class4
 * Tests that changing the order of virtual functions is reported.
 */
class HATC004_class4
{
public:
    HATC004_class4();
    virtual ~HATC004_class4();

protected:
    virtual int GetValue1();
    virtual int GetValue2();    
};

/**
 * HATC004_class5
 * Tests that changes in the base classes virtual tables are reported.
 */
class HATC004_class5 : public HATC004BASE_class1, public HATC004BASE_class2
{
public:
    IMPORT_C HATC004_class5();
    IMPORT_C ~HATC004_class5();
};

/**
 * HATC004_class6
 * Tests that changes in the base classes virtual tables are reported.
 */
class HATC004_class6 : public HATC004BASE_class6, public HATC004BASE_class5
{
public:
    IMPORT_C HATC004_class6();
    IMPORT_C ~HATC004_class6();
};


#endif