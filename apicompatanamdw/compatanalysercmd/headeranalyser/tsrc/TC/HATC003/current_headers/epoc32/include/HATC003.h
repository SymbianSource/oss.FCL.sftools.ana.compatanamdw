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
 * Current platform header file for HeaderAnalyser 
 * test case HATC003
 */

#ifndef HATC003_H
#define HATC003_H

#include "HATC003BASE.h"

/**
 * HATC003_class1
 * Tests that the change in virtuality of inheritance is reported.
 */
class HATC003_class1 : public virtual HATC003BASE_class1
{
public:
    IMPORT_C HATC003_class1();
    IMPORT_C virtual ~HATC003_class1();
};

/**
 * HATC003_class2
 * Tests that the removal of a base class reported.
 */
class HATC003_class2 : public HATC003BASE_class1
{
public:
    IMPORT_C HATC003_class2();
    IMPORT_C virtual ~HATC003_class2();
};

/**
 * HATC003_class3
 * Tests that the removal of a base class reported.
 */
class HATC003_class3 
{
public:
    IMPORT_C HATC003_class3();
    IMPORT_C virtual ~HATC003_class3();
};

/**
 * HATC003_class4
 * Tests that the addition of a base class reported.
 */
class HATC003_class4 : public HATC003BASE_class4
{
public:
    IMPORT_C HATC003_class4();
    IMPORT_C virtual ~HATC003_class4();
};

/**
 * HATC003_class5
 * Tests that changing the order of base classes is reported.
 */
class HATC003_class5 : public HATC003BASE_class2, public HATC003BASE_class1
{
public:
    IMPORT_C HATC003_class5();
    IMPORT_C virtual ~HATC003_class5();
};

/**
 * HATC003_class6
 * Tests that changing the virtual table of base class is reported.
 */
class HATC003_class6 : public HATC003BASE_class5
{
public:
    IMPORT_C HATC003_class6();
    IMPORT_C virtual ~HATC003_class6();
};

#endif