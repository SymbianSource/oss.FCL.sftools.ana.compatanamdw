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
* Description:  Test case for requirement HABC010_01
*
*/




#include "forced.h"


class SomeC
{
public:

    SomeC();
    ~SomeC();

    void SomeFunc();
};

class HATC010_01
{
public:

   // Test that changing access of member variable to more restrictive is reported:
   int a;
    
   // Test that removing public member variable is reported:
   int removePublic;

   // Test that adding a member is reported:

};



