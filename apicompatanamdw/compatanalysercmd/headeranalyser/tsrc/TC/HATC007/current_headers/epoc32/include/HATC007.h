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
* Description:  Test case for requirement HABC007
*
*/


#ifndef HATC007_H
#define HATC007_H

#include "HATC007_1.h"
/**
 * Current platform header file for HeaderAnalyser 
 * test case HATC007
 */
/**
 * struct hatc007_struct1. This struct tests that the removed typedef is reported.
 */
// REMOVED: hatc007_struct1

/**
 * struct hatc007_struct2. This tests that the changed typedef is reported.
 */
struct hatc007_struct2
{
    struct {
        int a;
        int b;
    } ab;
    char chArr[79]; // array size changed from 80 --> 79
    char* str;
    int i;
};

typedef hatc007_struct2 ST2_TYPE, *pST2_TYPE;

/**
 * struct hatc007_struct3. This tests that the changed typedef is reported.
 */
typedef struct
{
    char* str2;
    char* str;
    int i;
} hatc007_struct3, *phatc007_struct3;

typedef hatc007_class_templ<int> ST4_TYPE;
class hatc007_class_testing_incomplete_type
{
private:
    // Changed to pointer. This causes gccxml to parse 
    // hatc007_class_templ as of incomplete type.
    ST4_TYPE* iSt4; 
    int b;
};

/**
 * struct hatc007_struct5. This tests that changing only the name of the struct, 
 * which is used as a type of a typedef, is reported.
 */
struct hatc007_struct5_name_changed
{
    char arr1[32];
    char arr2[64];
    int i;
    int j;    
};

typedef hatc007_struct5_name_changed ST5_TYPE;

/**
 * Following typedef tests that the changed function pointer in typedef is changed.
 */
typedef char (HATC007_func1)(float, char, char);
typedef int (HATC007_func2)(float, int, char);
class HATC007_class1
{
public:
    IMPORT_C HATC007_class1();
    IMPORT_C ~HATC007_class1();
    IMPORT_C virtual HATC007_func1* GetFunc1Pointer();    
    IMPORT_C virtual HATC007_func2* GetFunc2Pointer();    
};

/**
 * HATC007_class2
 * Following typedefs inside a class test that access changes are reported correctly.
 */
class HATC007_class2
{
public:
    IMPORT_C HATC007_class2();
    IMPORT_C virtual ~HATC007_class2();
    typedef char* pProtectedStr1; // Moved here from protected
    
protected:
    typedef char* pPublicStr; // Moved here from public
    typedef char* pPrivateStr;// Moved here from private

private:
    typedef char* pProtectedStr2; // Moved here from protetected
    
};

#endif