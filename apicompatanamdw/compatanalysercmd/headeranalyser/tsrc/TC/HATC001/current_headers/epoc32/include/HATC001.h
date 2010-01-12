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
* Description:  Test case for requirement HABC001
*
*/


/**
 * Current platform header file for HeaderAnalyser 
 * test case HATC001
 */
#ifndef HATC001_H
#define HATC001_H

#include "HATC001BASE.h"

// class HATC001_class1 removed

// class HATC001_class2 removed

/**
 * HATC001_class3
 * This class tests that removing a class declared inside another
 * class is reported correctly.
 */
class HATC001_class3
{
public:
    IMPORT_C HATC001_class3();
    IMPORT_C virtual ~HATC001_class3();
    IMPORT_C int GetValue();
    //class MyPublic removed    
protected:
    //class MyProtected removed
private:
    //class MyPrivate removed
};

/**
 * HATC001_class4
 * This class tests that removing a class declared inside another
 * class is reported correctly. 
 * Note: this class contains protected inline function and it is 
 * derivable.
 */
class HATC001_class4
{
public:
    IMPORT_C HATC001_class4();
    IMPORT_C virtual ~HATC001_class4();    
    //class MyPublic removed    
protected:
    inline int GetValue();
    //class MyProtected removed
private:
    //class MyPrivate removed
};

/**
 * HATC001_class5
 * This class tests that removing a class declared inside another
 * class is reported correctly. 
 * Note: this class contains protected inline function and it
 * is not derivable.
 */
class HATC001_class5
{
public:     
    // class MyPublic removed
    int a;
protected:
    inline int GetValue();
    // class MyProtected removed
private:
    HATC001_class5();
    ~HATC001_class5();
    // class MyPrivate removed
};

/** HATC001_class6
 * Reference to an object of this class is used as an argument
 * in HATC001_class7.
 * This test case tests that the incomplete type of class will be reported.
 * Declaration is changed to forward declaration.
 */
class HATC001_class6;

/** HATC001_class7
 * Uses HATC001_class6
 */
class HATC001_class7
{
public:
    IMPORT_C HATC001_class7();
    IMPORT_C ~HATC001_class7();

    IMPORT_C void SetValue(HATC001_class6& aC6);
};

/**
 * HATC001_class8
 * Tests that changes in access of the class is reported correctly.
 */
class HATC001_class8
{
public:
    class myProtected2
    {
        myProtected2();
        ~myProtected2();
        int b;
    };
    
protected:
    class myPublic1
    {
        myPublic1();
        ~myPublic1();
        int a;
    };

    class myPrivate1
    {
        myPrivate1();
        ~myPrivate1();
        int c;
    };
    
private:
    class myProtected1
    {
        myProtected1();
        ~myProtected1();
        int b;
    };
};

/**
 * HATC001_class9
 * Tests that virtual inheritance is reported.
 */
class HATC001_class9 : public virtual HATC001BASE_class1
{
public:
    HATC001_class9();
    virtual ~HATC001_class9();
    virtual void SetValue(int a);
};
#endif
