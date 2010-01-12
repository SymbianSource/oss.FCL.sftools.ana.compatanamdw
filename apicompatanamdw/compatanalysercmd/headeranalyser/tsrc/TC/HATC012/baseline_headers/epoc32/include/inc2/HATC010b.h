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
* Description:  Test case for requirement HABC010_02
*
*/

#ifndef HATC010_02_H
#define HATC010_02_H

#include "HATC010c.hrh"
#include "forced.h"

class HATC010_02
{
public:
    IMPORT_C HATC010_02();
    IMPORT_C ~HATC010_02();

protected:

   // Test that changing access of member variable to more restrictive is reported:
   int a;
    
   // Test that removing protected member variable is reported, when class is derivable:
   int removeProtected;

   // Test that adding a member is reported:
};


#endif