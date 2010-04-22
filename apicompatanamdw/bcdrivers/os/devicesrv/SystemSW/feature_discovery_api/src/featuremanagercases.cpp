/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  This module contains the implementation of Cfeaturemanagertest class 
*				 member functions that does the actual tests.
*
*/

// INCLUDE FILES
#include <e32svr.h>

#include "FeatureManagerTest.h"
#include "FeatDiscovery.h"


// EXTERNAL DATA STRUCTURES
// None

// EXTERNAL FUNCTION PROTOTYPES  
// None

// CONSTANTS
const TInt KTestFeatureSupported = 15;      // id of __BT_AUDIO, enabled since 2.8
const TInt KTestFeatureNotSupported = 14;   // id of __MROUTER, disabled before 2.8
const TInt KTestFeatureDummy = 99999;       // dummy id, is not defined in 3.x


// MACROS
// None

// LOCAL CONSTANTS AND MACROS
// None

// MODULE DATA STRUCTURES
// None

// LOCAL FUNCTION PROTOTYPES
// None

// FORWARD DECLARATIONS
// None

// ==================== LOCAL FUNCTIONS =======================================


// ================= MEMBER FUNCTIONS =========================================

// -----------------------------------------------------------------------------
// Cfinditemenginetest::Case
// Returns a test case by number.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
// 
const TCaseInfo Cfeaturemanagertest::Case ( 
		const TInt aCaseNumber ) const //test case number
     {

    // To add new test cases, implement new test case function and add new 
    // line to KCases array specify the name of the case and the function 
    // doing the test case
    // In practice, do following
    // 1) Make copy of existing function and change it name
    // 2) Duplicate the last line in cases array 
    // 3) Change case name and function name in case array

    static TCaseInfoInternal const KCases[] =
        {
  
        // To add new test cases, add new items to this array

		{ (TText*) L"[CFeatureDiscovery] FeatureSupported", GETPTR FeaturesSupportedStatic},
		{ (TText*) L"[CFeatureDiscovery] FeaturesSupported_NewL", GETPTR FeaturesSupportedNewL},
		{ (TText*) L"[CFeatureDiscovery] FeaturesSupported_NewLC", GETPTR FeaturesSupportedNewLC},
		};

    // Verify that case number is valid
    if( (TUint) aCaseNumber >= sizeof( KCases ) / 
                               sizeof( TCaseInfoInternal ) )
        {

        // Invalid case, construct empty object
        TCaseInfo null( (const TText*) L"" );
        null.iMethod = NULL;
        return null;

        } 

    // Construct TCaseInfo object and return it 
    TCaseInfo tmp ( KCases[ aCaseNumber ].iCaseName );
    tmp.iMethod = KCases[ aCaseNumber ].iMethod;
    return tmp;
     
    }
    

// -----------------------------------------------------------------------------
// Cfeaturemanagertest::FeaturesSupported
// This test case fetches information about whether features are supported by using
// the static feature of CFeatureDiscovery::IsFeatureSupportedL.
// -----------------------------------------------------------------------------
//
TInt Cfeaturemanagertest::FeaturesSupportedStatic( TTestResult& aResult ) //test results
{
        TBool isSupported( EFalse );
        TBool notSupported( ETrue );
        TBool dummySupported( ETrue );
        
        
		//using the static way
		TRAPD( err1, isSupported = CFeatureDiscovery::IsFeatureSupportedL( KTestFeatureSupported ) );
		TRAPD( err2, notSupported = CFeatureDiscovery::IsFeatureSupportedL( KTestFeatureNotSupported ) );
		TRAPD( err3, dummySupported = CFeatureDiscovery::IsFeatureSupportedL( KTestFeatureDummy ) );
		
		if ( err1 == KErrNone && err2 == KErrNone && err3 == KErrNone )
		{
    		if ( test( isSupported && !notSupported && !dummySupported ) == KErrNone  )
    			{
    			aResult.iResult = KErrNone;	
    			}
    		else 
    			{
    			aResult.iResult = KErrNotSupported;
    			}
        }
        else
        {
            aResult.iResult = KErrGeneral;      
        }
        
        //return from the test case
		return KErrNone;

}


// -----------------------------------------------------------------------------
// Cfeaturemanagertest::FeaturesSupportedNewLTest
// This test case fetches information about whether features are supported
// by using an object of CFeatureDiscovery::NewL
// -----------------------------------------------------------------------------
//
TInt Cfeaturemanagertest::FeaturesSupportedNewL( TTestResult& aResult ) //test results
{		
        TBool isSupported( EFalse );
        TBool notSupported( ETrue );
        TBool dummySupported( ETrue );
        
        CFeatureDiscovery* testFeat = CFeatureDiscovery::NewL();

		isSupported = testFeat->IsSupported( KTestFeatureSupported );
		notSupported = testFeat->IsSupported( KTestFeatureNotSupported );
        dummySupported = testFeat->IsSupported( KTestFeatureDummy );

		if ( test( isSupported && !notSupported && !dummySupported ) == KErrNone )
			{
			aResult.iResult = KErrNone;
			}
		else
			{
			aResult.iResult = KErrNotSupported;

			}

		delete testFeat;

		return KErrNone;

}


// -----------------------------------------------------------------------------
// Cfeaturemanagertest::FeaturesSupportedNewLCTest
// This test case fetches information about whether features are supported
// by using an object of CFeatureDiscovery::NewL
// -----------------------------------------------------------------------------
//
TInt Cfeaturemanagertest::FeaturesSupportedNewLC( TTestResult& aResult ) //test results
{		

        TBool isSupported( EFalse );
        TBool notSupported( ETrue );
        TBool dummySupported( ETrue );
        
        CFeatureDiscovery* testFeat = CFeatureDiscovery::NewLC();

		isSupported = testFeat->IsSupported( KTestFeatureSupported );
		notSupported = testFeat->IsSupported( KTestFeatureNotSupported );
        dummySupported = testFeat->IsSupported( KTestFeatureDummy );

		if ( test( isSupported && !notSupported && !dummySupported ) == KErrNone )
			{
			aResult.iResult = KErrNone;
			}
		else
			{
			aResult.iResult = KErrNotSupported;
			}

		CleanupStack::PopAndDestroy( testFeat );

		return KErrNone;

}

// ================= OTHER EXPORTED FUNCTIONS =================================


// End of File
