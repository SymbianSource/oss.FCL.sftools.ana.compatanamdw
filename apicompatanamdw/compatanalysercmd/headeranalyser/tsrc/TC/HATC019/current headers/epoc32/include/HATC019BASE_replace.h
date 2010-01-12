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
* Description:  Test case for requirement HABC019
*
*/


/**
 * Current platform header file for HeaderAnalyser 
 * test case HATC019BASE
 */

#ifndef HATC019BASE_H
#define HATC019BASE_H

#include "forced.h"
/**
 * HATC019_class1
 * Tests that the size change in base class is reported.
 */
class HATC019BASE_class1
{
public:
    IMPORT_C HATC019BASE_class1();
    IMPORT_C virtual ~HATC019BASE_class1();
private:
    //int a; removed
};

/**
 * HATC019_class1
 * Tests that the size change in base class is reported.
 * (Virtual table added).
 */
class HATC019BASE_class2
{
public:
    IMPORT_C HATC019BASE_class2();
    IMPORT_C virtual ~HATC019BASE_class2();
private:
    int a;
};

#endif
