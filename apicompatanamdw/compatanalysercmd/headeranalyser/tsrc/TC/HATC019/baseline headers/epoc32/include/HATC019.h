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
 * Current platform header file for HeaderAnalyser 
 * test case HATC011
 */

#ifndef HATC019_H
#define HATC019_H

#include "HATC019BASE.h"

/**
 * HATC019_class1
 * Tests that the removal of the member field is reported.
 */
class HATC019_class1
{
public:
    IMPORT_C HATC019_class1();
    IMPORT_C ~HATC019_class1();
private:
    // int a; removed
};

/**
 * HATC019_class2
 * Tests that the addition of the member field is reported.
 */
class HATC019_class2
{
public:
    IMPORT_C HATC019_class2();
    IMPORT_C ~HATC019_class2();
private:
    int a;
    int b;
};

/**
 * HATC019_class3
 * Tests that the size change in base class is reported.
 */
class HATC019_class3 : public HATC019BASE_class1
{
public:

    IMPORT_C HATC019_class3();
    IMPORT_C virtual ~HATC019_class3();
};

/**
 * HATC019_class4
 * Tests that the size change in base class is reported.
 */
class HATC019_class4 : public HATC019BASE_class2
{
public:

    IMPORT_C HATC019_class4();    

	HATC010* ivar;
};
#endif