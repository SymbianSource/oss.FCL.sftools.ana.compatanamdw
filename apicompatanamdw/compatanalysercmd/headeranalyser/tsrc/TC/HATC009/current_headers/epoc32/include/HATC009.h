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
    virtual ~SomeC();

    virtual void SomeFunc();
};

class HATC009_01
{
private:
   // Test that changing access of member variable to more restrictive is reported:
   int a;

public:

   // Test that removing public member variable is reported:
   //int removePublic;

   // Test that adding a member is reported:
   int newMember;
};

class HATC009_02
{
public:
    // Test that changing the size of member is reported:
    int mArray[31];

    // Test that changing the offset of member is reported:
    int a;

    // Test that changing the type of member is reported:
    struct {
        struct { int aa; int bb; int cc; } a;
        int b;
    } sB;

    SomeC mS;
};

class HATC009_03
{
public:
    IMPORT_C HATC009_03();
    IMPORT_C ~HATC009_03();

private:

   // Test that changing access of member variable to more restrictive is reported:
   int a;

protected:
   // Test that removing protected member variable is reported, when class is derivable:
   //int removeProtected;

   // Test that adding a member is reported:
   char* newMember;
};

class HATC009_04
{
private:
    IMPORT_C HATC009_04();
    IMPORT_C ~HATC009_04();

private:

   // Test that changing access of member variable to more restrictive 
   // is not reported when member no accessible:
   int abc;
protected:
   // Test that removing protected member variable is not reported, when class is not derivable:
   //int removeProtected;

   // Test that adding a member to non-instantiable class is not reported:
   char newMember[128];
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
   //int removedMember;
};

#endif
