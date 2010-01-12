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
 * test case HATC002BASE
 */

#ifndef HATC002BASE_H
#define HATC002BASE_H

/**
 * HATC002_class1
 * Tests that the size change in base class is reported.
 */
class HATC002BASE_class1
{
public:
    IMPORT_C HATC002BASE_class1();
    IMPORT_C virtual ~HATC002BASE_class1();
private:
    //int a; removed
};

/**
 * HATC002_class1
 * Tests that the size change in base class is reported.
 * (Virtual table added).
 */
class HATC002BASE_class2
{
public:
    IMPORT_C HATC002BASE_class2();
    IMPORT_C virtual ~HATC002BASE_class2();
private:
    int a;
};

#endif
