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
*
*/
/* Changed by Vaibhav - 13Aug07 for Removing CodeScanner Warnings - High/medium */

#include "Textresolvert.h"


#include <TextResolver.h>

/*
-------------------------------------------------------------------------------

    Class: CTestModuleDemo

    Method: Case

    Description: Returns a test case by number.

    This function contains an array of all available test cases 
    i.e pair of case name and test function. If case specified by parameter
    aCaseNumber is found from array, then that item is returned.

    The reason for this rather complicated function is to specify all the
    test cases only in one place. It is not necessary to understand how
    function pointers to class member functions works when adding new test
    cases. See function body for instructions how to add new test case.
    
    Parameters:    const TInt aCaseNumber :in:      Test case number

    Return Values: const TCaseInfo Struct containing case name & function

    Errors/Exceptions: None

    Status: Proposal
    
-------------------------------------------------------------------------------
*/ 
const TCaseInfo Ctextresolvert::Case ( const TInt aCaseNumber ) const 
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
        { (TText*) L"C1 test",			 GETPTR c1_test },
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


TInt Ctextresolvert::c1_test( TTestResult& aResult )
    {
 	  
		CTextResolver* tr;
		TRAPD(err, tr = CTextResolver::NewL());
		if(err != KErrNone)
		return err;
		
		TDesC errString = tr->ResolveError(KErrGeneral);
		//TBufC<256> buf(errString);
		
		delete tr; 

		return test(true);
    }
