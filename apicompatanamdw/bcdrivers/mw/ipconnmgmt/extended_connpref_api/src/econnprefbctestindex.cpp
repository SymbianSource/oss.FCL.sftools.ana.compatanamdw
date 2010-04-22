/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:
* This file contains hardcoded module implementation.
*
*/


#include "econnprefbc.h"

// -----------------------------------------------------------------------------
// CEConnPrefBc::Case
// Returns a test case by number.
//
// This function contains an array of all available test cases i.e pair of case
// name and test function. If case specified by parameter aCaseNumber is found
// from array, then that item is returned.
//
// The reason for this rather complicated function is to specify all the test
// cases only in one place. It is not necessary to understand how function
// pointers to class member functions works when adding new test cases. See
// function body for instructions how to add new test case.
// -----------------------------------------------------------------------------
//
const TCaseInfo CEConnPrefBc::Case( const TInt aCaseNumber ) const
    {
    /**
    * To add new test cases, implement new test case function and add new
    * line to KCases array. Specify the name of the case and the function
    * doing the test case.
    * In practice, do following
    * 1) Make copy of existing test case function and change its name and
    *    functionality. Note that the function must be added to connmonbc.cpp
    *    file and to connmonbc.h header file.
    *
    * 2) Add entry to following KCases array either by using:
    *
    * 2.1: FUNCENTRY or ENTRY macro
    * ENTRY macro takes two parameters: test case name and test case function
    * name.
    *
    * FUNCENTRY macro takes only test case function name as a parameter and
    * uses that as a test case name and test case function name.
    *
    * Or
    *
    * 2.2: OOM_FUNCENTRY or OOM_ENTRY macro. Note that these macros are used
    * only with OOM (Out-Of-Memory) testing!
    *
    * OOM_ENTRY macro takes five parameters: test case name, test case
    * function name, TBool which specifies is method supposed to be run using
    * OOM conditions, TInt value for first heap memory allocation failure and
    * TInt value for last heap memory allocation failure.
    *
    * OOM_FUNCENTRY macro takes test case function name as a parameter and uses
    * that as a test case name, TBool which specifies is method supposed to be
    * run using OOM conditions, TInt value for first heap memory allocation
    * failure and TInt value for last heap memory allocation failure.
    */

    static TCaseInfoInternal const KCases[] =
        {
        // NOTE: When compiled to GCCE, there must be Classname:: declaration
        // in front of the method name, e.g. CConnMonBc::PrintTest. Otherwise
        // the compiler gives errors.

        ENTRY( "Ecpbc Construction", CEConnPrefBc::TEcpbcConstuction ),
        ENTRY( "Ecpbc Snap Purpose", CEConnPrefBc::TEcpbcSnapPurpose ),
        ENTRY( "Ecpbc Snap Id", CEConnPrefBc::TEcpbcSnapId ),
        ENTRY( "Ecpbc Iap Id", CEConnPrefBc::TEcpbcIapId ),
        ENTRY( "Ecpbc Bearer Set", CEConnPrefBc::TEcpbcBearerSet ),
        ENTRY( "Ecpbc Note Behaviour", CEConnPrefBc::TEcpbcNoteBehaviour ),
        ENTRY( "Ecpbc Disconnect Dialog", CEConnPrefBc::TEcpbcDisconnectDialog ),
        ENTRY( "Ecpbc Connection Selection Dialog", CEConnPrefBc::TEcpbcConnSelectionDialog ),
        ENTRY( "Ecpbc Forced Roaming", CEConnPrefBc::TEcpbcForcedRoaming ),
        };

    // Verify that case number is valid
    if ( (TUint)aCaseNumber >= sizeof( KCases ) / sizeof( TCaseInfoInternal ) )
        {
        // Invalid case, construct empty object
        TCaseInfo empty( (const TText*) L"" );
        empty.iMethod = NULL;
        empty.iIsOOMTest = EFalse;
        empty.iFirstMemoryAllocation = 0;
        empty.iLastMemoryAllocation = 0;
        return empty;
        }

    // Construct TCaseInfo object and return it
    TCaseInfo tmp( KCases[aCaseNumber].iCaseName );
    tmp.iMethod = KCases[aCaseNumber].iMethod;
    tmp.iIsOOMTest = KCases[aCaseNumber].iIsOOMTest;
    tmp.iFirstMemoryAllocation = KCases[aCaseNumber].iFirstMemoryAllocation;
    tmp.iLastMemoryAllocation = KCases[aCaseNumber].iLastMemoryAllocation;
    return tmp;
    }

// End of file
