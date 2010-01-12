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
* Description:  Test case for requirement HABC005
*
*/


/**
 * Baseline platform header file for HeaderAnalyser 
 * test case HATC005
 */

#ifndef HATC005_H
#define HATC005_H

/**
 * HATC005_class1
 */
class HATC005_class1
{
public:
    IMPORT_C HATC005_class1();
    IMPORT_C virtual ~HATC005_class1();
    static const int publicVar1;
    static const int publicVar2;
    
protected:

    static const int protectedVar1;
    static const int protectedVar2;

private:

    static const int privateVar1;
    static const int privateVar2;
};

const int HATC005_class1::publicVar1 = 1;
const int HATC005_class1::publicVar2 = 2;
const int HATC005_class1::protectedVar1 = 3;
const int HATC005_class1::protectedVar2 = 4;
const int HATC005_class1::privateVar1 = 5;
const int HATC005_class1::privateVar2 = 6;

/**
 * HATC005_class2
 */
class HATC005_class2
{
public:    
    static const int publicVar1;
    static const int publicVar2;
    
protected:

    static const int protectedVar1;
    static const int protectedVar2;

private:
    HATC005_class2();
    ~HATC005_class2();
    static const int privateVar1;
    static const int privateVar2;
};

const int HATC005_class2::publicVar1 = 1;
const int HATC005_class2::publicVar2 = 2;
const int HATC005_class2::protectedVar1 = 3;
const int HATC005_class2::protectedVar2 = 4;
const int HATC005_class2::privateVar1 = 5;
const int HATC005_class2::privateVar2 = 6;

/**
 * HATC005_class3
 */
class HATC005_class3
{
public: 
    IMPORT_C HATC005_class3();
    IMPORT_C ~HATC005_class3();
        
protected:
    
    inline void ProtectedInlineFunction();
    static const int protectedVar1;

private:    
    static const int privateVar1;
    static const int privateVar2;
    static const char privateVar3;    
};

const int HATC005_class3::protectedVar1 = 4;
const int HATC005_class3::privateVar1 = 5;
const int HATC005_class3::privateVar2 = 6;
const char HATC005_class3::privateVar3 = 99;

#endif