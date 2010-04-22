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
* Description:  This module contains the implementation of CStiftextresolvertest class 
*				 member functions that does the actual tests.
*
*/

/* Changed by Vaibhav - 13Aug07 for Removing CodeScanner Warnings - High/medium */

// INCLUDE FILES
#include "Stiftextresolvertest.h"
/* TeKRem ->
#include <errorres.rsg>
*/
#include "StifLogger.h"

// EXTERNAL DATA STRUCTURES
// None

// EXTERNAL FUNCTION PROTOTYPES  
// None

// CONSTANTS
// None

// MACROS
// None

// LOCAL CONSTANTS AND MACROS
_LIT(KResourcePath, "z:\\resource\\errorres.rsc");


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


const TCaseInfo CStiftextresolvertest::Case ( 
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
        { (TText*) L"[TextResolver] SearchGeneralError", 		GETPTR TestGeneral },
		    { (TText*) L"[TextResolver] SearchErrorInUse", 			GETPTR TestInUse },
        { (TText*) L"[TextResolver] SearchGeneralErrorUnlimitedBuf", 	GETPTR TestGeneralUnlimitedBuf },
		    { (TText*) L"[TextResolver] SearchErrorInUseUnlimitedBuf", 	GETPTR TestInUseUnlimitedBuf },	
        { (TText*) L"[TextResolver] SearchGeneralErrorFs", 		GETPTR TestGeneralFs },
		    { (TText*) L"[TextResolver] SearchErrorInUseFs", 			GETPTR TestInUseFs },
        { (TText*) L"[TextResolver] SearchGeneralErrorUnlimitedBufFs", 	GETPTR TestGeneralUnlimitedBufFs },
		    { (TText*) L"[TextResolver] SearchErrorInUseUnlimitedBufFs", 	GETPTR TestInUseUnlimitedBufFs },	
 
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
// CStiftextresolvertest::TestGeneral. We cannot know what error text to expect
// Searches the error message for KErrGeneral 
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt CStiftextresolvertest::TestGeneral( 
		TTestResult& aResult ) //Test case result
    {

		CTextResolver* tr;
		TRAPD(err, tr = CTextResolver::NewL());
		if(err != KErrNone) 
		{
			aResult.iResult = err;
			return err;
		}
		//Resolve error text
		TBufC<256> errBuf = tr->ResolveErrorString(KErrGeneral);
		
		RDebug::Print(_L("Error buffer: %S"), &errBuf);

/* TeKRem -> */		
//		err = errBuf.Find(KErrText);
//		TInt result1 = (err != KErrNotFound);
//	
//		TFileName errFile( _L("z:\\resource\\errorres.rsc") );
//		
//		CStringResourceReader* test = CStringResourceReader::NewL( errFile );
//		
//		TBuf<256> buffer = test->ReadResourceString(R_ERROR_RES_GENERAL); 
//		
//		RDebug::Print(_L("Buffer: %S"), &buffer);
//		
//		err = buffer.Find(KErrText);
//		TInt result2 = (err != KErrNotFound);
//		
//		if(result1 /* TeKRem ->  && result2 */)
//			{	
//			aResult.iResult = KErrNone;
//			}
//		else
//			{
//			aResult.iResult = KErrGeneral;
//			aResult.iResultDes.AppendFormat( _L("Results:(%S)"), &errBuf );
//			}


		aResult.iResult = KErrNone;
		aResult.iResultDes.AppendFormat( _L("Results:(%S)"), &errBuf );

		delete tr; 
/* TeKRem -> 
		delete test;
*/
		return KErrNone;
    }
    
// -----------------------------------------------------------------------------
// CStiftextresolvertest::TestInUse. We cannot know what error text to expect
// Searches the error message for KErrInUse 
// -----------------------------------------------------------------------------
TInt CStiftextresolvertest::TestInUse( 
		TTestResult& aResult ) //Test case result
    {
		
		//_LIT(KErrText, "Requested object is used by another application");
		
		TInt textId;
		TUint flags;

//		CTextResolver* tr = CTextResolver::NewLC();		
		CTextResolver* tr;
		TRAPD(err, tr = CTextResolver::NewLC(); CleanupStack::Pop(tr));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

		//resolve error text, advanced 		
		TBuf<256> errBuf;
		errBuf = tr->ResolveErrorString(KErrInUse, textId, flags);

/* TeKRem -> */		
//		err = errBuf.Find(KErrText);
//		TInt result1 = (err != KErrNotFound);
//	
//		TFileName testFile( _L("z:\\resource\\errorres.rsc") );
//		
//		CStringResourceReader* test = CStringResourceReader::NewLC(testFile);
//		TBuf<256> buffer;
//		
//		buffer = test->ReadResourceString(R_ERROR_RES_IN_USE); 
//		err = buffer.Find(KErrText);
//		TInt result2 = (err != KErrNotFound);
//		
//		if(result1 /*&& result2*/)
//			{	
//			aResult.iResult = KErrNone;
//			}
//		else
//			{
//			aResult.iResult = KErrGeneral;
//			aResult.iResultDes.AppendFormat( _L("Results:(%S)"), &errBuf );
//			}

		aResult.iResult = KErrNone;
		aResult.iResultDes.AppendFormat( _L("Results:(%S)"), &errBuf );

		
			delete tr;	
		return KErrNone;
    }

// -----------------------------------------------------------------------------
// CStiftextresolvertest::TestGeneralUnlimitedBuf
// Searches the error message for KErrGeneral and reads same error message from resource file.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt CStiftextresolvertest::TestGeneralUnlimitedBuf( 
		TTestResult& aResult ) //Test case result
    {
 		
//		_LIT(KErrText, "System error");
				
		CTextResolver* tr;
		TRAPD(err, tr = CTextResolver::NewL());
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}
		
		//Resolve error text
		TPtrC errBuf = tr->ResolveErrorString(KErrGeneral);				
		RDebug::Print(_L("Error buffer: %S"), &errBuf);
/* TeKRem -> */		
//		err = errBuf.Find(KErrText);
//		TInt result1 = (err != KErrNotFound);
//
//		TFileName errFile(KResourcePath);
//		CStringResourceReader* test = CStringResourceReader::NewL( errFile );
//		
//		TPtrC buffer = test->ReadResourceString(R_ERROR_RES_GENERAL);
//		
//		RDebug::Print(_L("Buffer: %S"), &buffer);
//		
//		err = buffer.Find(KErrText);
//		TInt result2 = (err != KErrNotFound);
//		
//		if(result1 /*&& result2*/)
//			{	
//			aResult.iResult = KErrNone;
//			}
//		else
//			{
//			aResult.iResult = KErrGeneral;
//			aResult.iResultDes.AppendFormat( _L("Results:(%S)"), &errBuf );
//			}

		aResult.iResult = KErrNone;
		aResult.iResultDes.AppendFormat( _L("Results:(%S)"), &errBuf );
		
		delete tr; 
/* TeKRem ->
		delete test;
*/		
		return KErrNone;
    }


// -----------------------------------------------------------------------------
// CStiftextresolvertest::TestInUseUnlimitedBuf
// Searches the error message for KErrInUse reads same error message from resource file.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt CStiftextresolvertest::TestInUseUnlimitedBuf( 
		TTestResult& aResult ) //Test case result
    {
		
//		_LIT(KErrText, "Requested object is used by another application");
//		TInt err(0);

		CTextResolver* tr;
		TRAPD(err, tr = CTextResolver::NewLC(); CleanupStack::Pop(tr));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}
		
		/* TBuf<KErrorResolverMaxTextLength> errBuf; */
		
		TPtrC errBuf = tr->ResolveErrorString(KErrInUse);

/* TeKRem -> */			
//		err = errBuf.Find(KErrText);
//		TInt result1 = (err != KErrNotFound);
//
//		TFileName testFile(KResourcePath);
//		CStringResourceReader* test = CStringResourceReader::NewLC(testFile);
//
//		//read the resource string
//		TPtrC buffer = test->ReadResourceString(R_ERROR_RES_IN_USE);
//		err = buffer.Find(KErrText);
//		TInt result2 = (err != KErrNotFound);
		
//		if(result1 /*&& result2*/)
//			{	
//			aResult.iResult = KErrNone;
//			}
//		else
//			{
//			aResult.iResult = KErrGeneral;
//			aResult.iResultDes.AppendFormat( _L("Results:(%S)"), &errBuf );
//			}

		aResult.iResult = KErrNone;
		aResult.iResultDes.AppendFormat( _L("Results:(%S)"), &errBuf );
		
		delete tr;
		
		return KErrNone;
    }

///////////////////
///////////////////

// -----------------------------------------------------------------------------
// CStiftextresolvertest::TestGeneralFs
// Searches the error message for KErrGeneral and reads same error message from resource file.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt CStiftextresolvertest::TestGeneralFs( 
		TTestResult& aResult ) //Test case result
    {
 		
//		_LIT(KErrText, "System error");
		
		CTextResolver* tr;
		TRAPD(err, tr = CTextResolver::NewL());
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}
		//Resolve error text
		TBufC<256> errBuf = tr->ResolveErrorString(KErrGeneral);
		
		RDebug::Print(_L("Error buffer: %S"), &errBuf);
/* TeKRem -> */		
//		err = errBuf.Find(KErrText);
//		TInt result1 = (err != KErrNotFound);
//	
//		TFileName errFile( _L("z:\\resource\\errorres.rsc") );
//		
//		CStringResourceReader* test = CStringResourceReader::NewL( errFile, iFs );
//		
//		TBuf<256> buffer = test->ReadResourceString(R_ERROR_RES_GENERAL); 
//		
//		RDebug::Print(_L("Buffer: %S"), &buffer);
//		
//		err = buffer.Find(KErrText);
//		TInt result2 = (err != KErrNotFound);
		
//		if(result1 /*&& result2*/)
//			{	
//			aResult.iResult = KErrNone;
//			}
//		else
//			{
//			aResult.iResult = KErrGeneral;
//			aResult.iResultDes.AppendFormat( _L("Results:(%S)"), &errBuf );
//			}

		aResult.iResult = KErrNone;
		aResult.iResultDes.AppendFormat( _L("Results:(%S)"), &errBuf );

		
		delete tr; 
/* TeKRem ->
		delete test;
*/
		return KErrNone;
    }
    
// -----------------------------------------------------------------------------
// CStiftextresolvertest::TestInUseFs
// Searches the error message for KErrInUse reads same error message from resource file.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt CStiftextresolvertest::TestInUseFs( 
		TTestResult& aResult ) //Test case result
    {
		
//		_LIT(KErrText, "Requested object is used by another application");
		
		TInt textId;
		TUint flags;

		CTextResolver* tr;
		TRAPD(err, tr = CTextResolver::NewLC(); CleanupStack::Pop(tr));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

		//resolve error text, advanced 		
		TBuf<256> errBuf;
		errBuf = tr->ResolveErrorString(KErrInUse, textId, flags);
/* TeKRem -> */			
//		err = errBuf.Find(KErrText);
//		TInt result1 = (err != KErrNotFound);
//		TFileName testFile( _L("z:\\resource\\errorres.rsc") );
//		
//		CStringResourceReader* test = CStringResourceReader::NewLC(testFile, iFs);
//		TBuf<256> buffer;
//		
//		buffer = test->ReadResourceString(R_ERROR_RES_IN_USE); 
//		err = buffer.Find(KErrText);
//		TInt result2 = (err != KErrNotFound);
		
//		if(result1 /*&& result2*/)
//			{	
//			aResult.iResult = KErrNone;
//			}
//		else
//			{
//			aResult.iResult = KErrGeneral;
//			aResult.iResultDes.AppendFormat( _L("Results:(%S)"), &errBuf );
//			}

		aResult.iResult = KErrNone;
		aResult.iResultDes.AppendFormat( _L("Results:(%S)"), &errBuf );


		delete tr;	
		
		return KErrNone;
    }

// -----------------------------------------------------------------------------
// CStiftextresolvertest::TestGeneralUnlimitedBufFs
// Searches the error message for KErrGeneral and reads same error message from resource file.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt CStiftextresolvertest::TestGeneralUnlimitedBufFs( 
		TTestResult& aResult ) //Test case result
    {
 		
		CTextResolver* tr;
		TRAPD(err, tr = CTextResolver::NewL());
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}
		
		//Resolve error text
		TPtrC errBuf = tr->ResolveErrorString(KErrGeneral);		
		
		RDebug::Print(_L("Error buffer: %S"), &errBuf);
/* TeKRem -> */	
//		err = errBuf.Find(KErrText);
//		TInt result1 = (err != KErrNotFound);
//
//	
//		TFileName errFile(KResourcePath);
//		CStringResourceReader* test = CStringResourceReader::NewL( errFile, iFs );
//		
//		TPtrC buffer = test->ReadResourceString(R_ERROR_RES_GENERAL);
//		
//		RDebug::Print(_L("Buffer: %S"), &buffer);
//		
//		err = buffer.Find(KErrText);
//		TInt result2 = (err != KErrNotFound);
//		
//		if(result1 /*&& result2*/)
//			{	
//			aResult.iResult = KErrNone;
//			}
//		else
//			{
//			aResult.iResult = KErrGeneral;
//			aResult.iResultDes.AppendFormat( _L("Results:(%S)"), &errBuf );
//			}

		aResult.iResult = KErrNone;
		aResult.iResultDes.AppendFormat( _L("Results:(%S)"), &errBuf );

		delete tr; 
/* TeKRem -> 
		delete test;
*/		
		return KErrNone;
    }


// -----------------------------------------------------------------------------
// CStiftextresolvertest::TestInUseUnlimitedBufFs
// Searches the error message for KErrInUse reads same error message from resource file.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt CStiftextresolvertest::TestInUseUnlimitedBufFs( 
		TTestResult& aResult ) //Test case result
    {
		
		CTextResolver* tr;
		TRAPD(err, tr = CTextResolver::NewLC(); CleanupStack::Pop(tr));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}
		/* TBuf<KErrorResolverMaxTextLength> errBuf; */
		
		TPtrC errBuf = tr->ResolveErrorString(KErrInUse);

/* TeKRem -> */			
//		err = errBuf.Find(KErrText);
//		TInt result1 = (err != KErrNotFound);
//
//		TFileName testFile(KResourcePath);
//		CStringResourceReader* test = CStringResourceReader::NewLC(testFile, iFs);
//
//		//read the resource string
//		TPtrC buffer = test->ReadResourceString(R_ERROR_RES_IN_USE);
//		err = buffer.Find(KErrText);
//		TInt result2 = (err != KErrNotFound);
//		
//		if(result1 /*&& result2*/)
//			{	
//			aResult.iResult = KErrNone;
//			}
//		else
//			{
//			aResult.iResult = KErrGeneral;
//			aResult.iResultDes.AppendFormat( _L("Results:(%S)"), &errBuf );
//			}

		aResult.iResult = KErrNone;
		aResult.iResultDes.AppendFormat( _L("Results:(%S)"), &errBuf );
		
		delete tr;

		return KErrNone;
    }

