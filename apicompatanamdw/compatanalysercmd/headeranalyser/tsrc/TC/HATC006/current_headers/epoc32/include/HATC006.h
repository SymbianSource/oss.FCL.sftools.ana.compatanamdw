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
* Description:  Test case for requirement HABC006
*
*/


/**
 * Current platform header file for HeaderAnalyser 
 * test case HATC006
 */
#ifndef HATC006_H
#define HATC006_H

/**
 * HATC006_class1
 * Tests that removed and changed exported functions are reported.
 */
class HATC006_class1
{
public:
    IMPORT_C HATC006_class1();
    IMPORT_C virtual ~HATC006_class1();

    IMPORT_C void ExpPublicFunc1(/*REMOVED: int a*/);
    // REMOVED: IMPORT_C int ExpPublicFunc2();

protected:
    IMPORT_C void ExpProtectedFunc1(/*REMOVED: int a*/);
    // REMOVED: IMPORT_C int ExpProtectedFunc2();

private:
    IMPORT_C void ExpPrivateFunc1(/*REMOVED: int a*/);
    // REMOVED: IMPORT_C int ExpPrivateFunc2();
};

/**
 * HATC006_class2
 * Tests that removed and changed inline functions are reported.
 */
class HATC006_class2
{
public:
    IMPORT_C HATC006_class2();
    IMPORT_C virtual ~HATC006_class2();

    inline void InlPublicFunc1(/*REMOVED: int a*/);
    // REMOVED: inline int InlPublicFunc2();

protected:
    inline void InlProtectedFunc1(/*REMOVED: int a*/);
    // REMOVED: inline int InlProtectedFunc2();

private:
    inline void InlPrivateFunc1(/*REMOVED: int a*/);
    // REMOVED: inline int InlPrivateFunc2();
};

/**
 * HATC006_class3
 * Tests that removed and changed protected and private exported 
 * functions are reported when the class is not derivable, but 
 * has public inline functions.
 */
class HATC006_class3
{
public:    
    IMPORT_C ~HATC006_class3();
    inline void InlPublicFunc1(int a);    
protected:
    IMPORT_C void ExpProtectedFunc1(/*REMOVED: int a*/);
    //REMOVED: IMPORT_C int ExpProtectedFunc2();    
private:
    HATC006_class3();
    IMPORT_C void ExpPrivateFunc1(/*REMOVED: int a*/);
    //REMOVED: IMPORT_C int ExpPrivateFunc2();    
};

/**
 * HATC006_class4
 * Tests that removed and changed protected and private inline 
 * functions are reported when the class is derivable and does
 * not have any public inline functions.
 */
class HATC006_class4
{
public:
    IMPORT_C HATC006_class4();    
    IMPORT_C virtual ~HATC006_class4();    
protected:
    inline void InlProtectedFunc1(/*REMOVED: int a*/);
    // REMOVED: inline int InlProtectedFunc2();
private:
    inline void InlPrivateFunc1(/*REMOVED: int a*/);
    // REMOVED: inline int InlPrivateFunc2();
};

/**
 * HATC006_class5
 * Tests that addition of exported non-virtual or inline function
 * is not reported. Also tests that changing the order of exported
 * non-virtual or inline functions is not repored.
 */
class HATC006_class5
{
public:

    IMPORT_C HATC006_class5();
    IMPORT_C virtual ~HATC006_class5();

    IMPORT_C int ExpPublicFunc2(); // Order changed
    IMPORT_C void ExpPublicFunc1(int a); // Order changed

    IMPORT_C int ExpPublicFunc3(); // Added
    
    inline int InlPublicFunc2(); // Order changed
    inline void InlPublicFunc1(int a); // Order changed
    inline int InlPublicFunc3(); // Added
    
protected:

    IMPORT_C int ExpProtectedFunc2(); // Order changed
    IMPORT_C void ExpProtectedFunc1(int a); // Order changed
    IMPORT_C int ExpProtectedFunc3(); // Added
    
    inline int InlProtectedFunc2(); // Order changed
    inline void InlProtectedFunc1(int a); // Order changed
    inline int InlProtectedFunc3(); // Added
    
private:

    IMPORT_C int ExpPrivateFunc2(); // Order changed
    IMPORT_C void ExpPrivateFunc1(int a); // Order changed
    IMPORT_C int ExpPrivateFunc3(); // Added
    
    inline int InlPrivateFunc2(); // Order changed
    inline void InlPrivateFunc1(int a); // Order changed
    inline int InlPrivateFunc3(); // Added  
};

/**
 * HATC006_class6
 * Tests that const qualifier can be added to function and to its parameters.
 * Tests also that function return value can be changed from const to non-const.
 */
class HATC006_class6
{
public:
    IMPORT_C HATC006_class6();
    IMPORT_C ~HATC006_class6();    

    // Test that adding const qualifier to parameters is not reported:
    IMPORT_C void TestFunc1(int const* const* const aPtrPtr, int const * const aPtr, int const& aRef);

    // Test that removing const qualifier from parameter is reported:
    IMPORT_C void TestFunc2( int const** const aPtrPtr );

    // Test that removing const qualifier from parameter is reported:
    IMPORT_C void TestFunc3( int& aRef );

    // Test that adding const qualifier to function is not reported:
    IMPORT_C void TestFunc4() const;

    // Test that removing const qualifier from function is reported:
    IMPORT_C void TestFunc5();

    // Test that adding const qualifier to function pointer parameter is reported:    
    IMPORT_C void TestFunc6( int (*pF) (int const&) );

    // Test that removing const qualifier from function pointer parameter is reported:
    IMPORT_C void TestFunc7( int (*pF) (int&) );

    // Test that removing const qualifier from return value is not reported:
    IMPORT_C int& TestFunc8();

    // Test that adding const qualifier to return value is reported:
    IMPORT_C int const& TestFunc9();
    
};

#endif