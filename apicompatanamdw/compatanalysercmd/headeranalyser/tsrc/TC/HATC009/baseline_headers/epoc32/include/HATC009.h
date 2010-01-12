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
* Description:  Test case for requirement HABC009
*
*/

#ifndef HATC009_H
#define HATC009_H

class SomeC
{
public:

    SomeC();
    ~SomeC();

    void SomeFunc();
};

class HATC009_01
{
public:

   // Test that changing access of member variable to more restrictive is reported:
   int a;
    
   // Test that removing public member variable is reported:
   int removePublic;

   // Test that adding a member is reported:

};

class HATC009_02
{
public:
    // Test that changing the type of member is reported:
    int mArray[32];

    // Test that changing the offset of member is reported:
    int a;

    // Test that changing the type of member is reported:
    struct {
        int a;
        int b;
    } sB;

    SomeC mS;
};

class HATC009_03
{
public:
    IMPORT_C HATC009_03();
    IMPORT_C ~HATC009_03();

protected:

   // Test that changing access of member variable to more restrictive is reported:
   int a;
    
   // Test that removing protected member variable is reported, when class is derivable:
   int removeProtected;

   // Test that adding a member is reported:

};

class HATC009_04
{
private:
    IMPORT_C HATC009_04();
    IMPORT_C ~HATC009_04();

protected:

   // Test that changing access of member variable to more restrictive 
   // is not reported when member no accessible:
   int abc;
    
   // Test that removing protected member variable is not reported, when class is not derivable:
   int removeProtected;

   // Test that adding a member is reported:

};

class HATC009_05
{
public:
    IMPORT_C HATC009_05();
    IMPORT_C ~HATC009_05();

protected:
    inline void InlinedFunction();

private:

   // Test that removing private member is reported when there are accessible inline function:
   int removedMember;
};

#endif