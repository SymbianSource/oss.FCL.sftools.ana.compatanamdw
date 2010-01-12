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
* Description:  Test case for requirement HABC008
*
*/

#ifndef HATC008_H
#define HATC008_H

class HATC008_PublicEnums
{
public:

    // Test that removing the enumeration raises an issue:
    /*enum removeThis
    {
        v1,
        v2
    };*/

    // Test that adding enum to the end does not raise an issue:
    enum enum1 {
        valueForThis = 0,
        valueForThat,
        valueForThisAndThat
    };

    // Test that adding enum to the middle do raise an issue:
    enum enum2 {
        value1 = 1,
        value2,
        value3, // This is added
        value4
    };

    // Test that removing a value raises an issue:
    enum enum3 {
        firstValue = 0,
        secondValue
        //thirdAndRemovedValue
    };

    // Test that changing value of enumeration raises an issue
    enum enum4 {
        mondayValue = 1, // was mondayValue = 0
        tuesdayValue
    };

    // Test that changing the order of enumeration values raises an issue:
    enum enum5 {
        wednesday,
        thursday,
        friday        
    };

    
protected:
    // Test that changing the access to more restrictive raises an issue:
    enum enum6 {
        publicOrProtected
    };
};

class HATC008_ProtectedEnums
{
public:

    HATC008_ProtectedEnums();
    ~HATC008_ProtectedEnums();

protected:
    // Test that removing the enumeration raises an issue:
    /*enum removeThis
    {
        v1,
        v2
    };*/

    // Test that adding enum to the end does not raise an issue:
    enum enum1 {
        valueForThis = 0,
        valueForThat,
        valueForThisAndThat
    };

    // Test that adding enum to the middle do raise an issue:
    enum enum2 {
        value1 = 1,
        value2,
        value3, // This is added
        value4
    };

    // Test that removing a value raises an issue:
    enum enum3 {
        firstValue = 0,
        secondValue
        //thirdAndRemovedValue
    };

    // Test that changing value of enumeration raises an issue
    enum enum4 {
        mondayValue = 1, // was mondayValue = 0
        tuesdayValue
    };

    // Test that changing the order of enumeration values raises an issue:
    enum enum5 {
        wednesday,
        thursday,
        friday        
    };

    
private:
    // Test that changing the access to more restrictive raises an issue:
    enum enum6 {
        publicOrProtected
    };
};

class HATC008_ProtectedEnums2
{
private:

    HATC008_ProtectedEnums2();
    ~HATC008_ProtectedEnums2();

protected:
    // Test that removing the enumeration raises an issue:
    /*enum removeThis
    {
        v1,
        v2
    };*/

    // Test that adding enum to the end does not raise an issue:
    enum enum1 {
        valueForThis = 0,
        valueForThat,
        valueForThisAndThat
    };

    // Test that adding enum to the middle do raise an issue:
    enum enum2 {
        value1 = 1,
        value2,
        value3, // This is added
        value4
    };

    // Test that removing a value raises an issue:
    enum enum3 {
        firstValue = 0,
        secondValue
        //thirdAndRemovedValue
    };

    // Test that changing value of enumeration raises an issue
    enum enum4 {
        mondayValue = 1, // was mondayValue = 0
        tuesdayValue
    };

    // Test that changing the order of enumeration values raises an issue:
    enum enum5 {
        wednesday,
        thursday,
        friday        
    };

    
private:
    // Test that changing the access to more restrictive raises an issue:
    enum enum6 {
        publicOrProtected
    };
};

class HATC008_PrivateEnums
{
public:
    IMPORT_C HATC008_PrivateEnums();
    IMPORT_C ~HATC008_PrivateEnums();

    inline void InlinedFunction();

private:

    // Test that removing a value from private enumeration when there is 
    // a public inline function raises an issue:
    enum enum1
    {        
        //val1,
        val2
    };

    // Test that removing a private enumeration when there is 
    // a public inline function raises an issue:
    /*enum enum2
    {
        val3
    };*/
};

#endif