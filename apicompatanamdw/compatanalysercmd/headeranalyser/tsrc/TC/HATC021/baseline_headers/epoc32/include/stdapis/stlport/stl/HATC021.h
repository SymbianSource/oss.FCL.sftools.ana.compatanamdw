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
* Description:  Test case for requirement HABC021
*
*/


/**
 * Current platform header file for HeaderAnalyser 
 * test case HATC021
 */

#ifndef HATC021_H
#define HATC021_H

#include "HATC021BASE.h"

/**
 * HATC021_class1
 * Tests that the removal of the member field is reported.
 */
class HATC021_class1
{
public:
    IMPORT_C HATC021_class1();
    IMPORT_C ~HATC021_class1();
private:
    // int a; removed
};

/**
 * HATC021_class2
 * Tests that the addition of the member field is reported.
 */
class HATC021_class2
{
public:
    IMPORT_C HATC021_class2();
    IMPORT_C ~HATC021_class2();
private:
    int a;
    int b;
};

/**
 * HATC021_class3
 * Tests that the size change in base class is reported.
 */
class HATC021_class3 : public HATC021BASE_class1
{
public:

    IMPORT_C HATC021_class3();
    IMPORT_C virtual ~HATC021_class3();
};

/**
 * HATC021_class4
 * Tests that the size change in base class is reported.
 */
class HATC021_class4 : public HATC021BASE_class2
{
public:

    IMPORT_C HATC021_class4();    

	HATC010* ivar;
};
#endif