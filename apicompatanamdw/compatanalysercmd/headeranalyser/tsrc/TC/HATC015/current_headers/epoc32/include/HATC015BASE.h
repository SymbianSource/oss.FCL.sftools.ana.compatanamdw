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
* Description:  Test case for requirement HABC015
*
*/


/**
 * Current platform header file for HeaderAnalyser 
 * test case HATC015BASE
 */

#ifndef HATC015BASE_H
#define HATC015BASE_H

#include "forced.h"
/**
 * HATC015_class1
 * Tests that the size change in base class is reported.
 */
class HATC015BASE_class1
{
public:
    IMPORT_C HATC015BASE_class1();
    IMPORT_C virtual ~HATC015BASE_class1();
private:
    //int a; removed
};

/**
 * HATC015_class1
 * Tests that the size change in base class is reported.
 * (Virtual table added).
 */
class HATC015BASE_class2
{
public:
    IMPORT_C HATC015BASE_class2();
    IMPORT_C virtual ~HATC015BASE_class2();
private:
    int a;
};

#endif
