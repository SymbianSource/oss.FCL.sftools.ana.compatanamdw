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
* Description:  Test case for requirement HABC002
*
*/


/**
 * Baseline platform header file for HeaderAnalyser 
 * test case HATC002
 */

#ifndef HATC002_H
#define HATC002_H

#include "HATC002BASE.h"

/**
 * HATC002_class1
 * Tests that the removal of the member field is reported.
 */
class HATC002_class1
{
public:
    IMPORT_C HATC002_class1();
    IMPORT_C ~HATC002_class1();
private:
    int a;
};

/**
 * HATC002_class2
 * Tests that the addition of the member field is reported.
 */
class HATC002_class2
{
public:
    IMPORT_C HATC002_class2();
    IMPORT_C ~HATC002_class2();
private:
    int a;
};

/**
 * HATC002_class3
 * Tests that the size change in base class is reported.
 */
class HATC002_class3 : public HATC002BASE_class1
{
public:

    IMPORT_C HATC002_class3();
    IMPORT_C virtual ~HATC002_class3();
};

/**
 * HATC002_class4
 * Tests that the size change in base class is reported.
 */
class HATC002_class4 : public HATC002BASE_class2
{
public:

    IMPORT_C HATC002_class4();    
};

#endif