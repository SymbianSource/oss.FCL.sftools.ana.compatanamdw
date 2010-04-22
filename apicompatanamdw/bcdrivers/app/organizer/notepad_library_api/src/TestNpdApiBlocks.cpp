/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/



// [INCLUDE FILES] - do not remove
#include <e32svr.h>
#include <e32cmn.h>
#include <f32file.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include "TestNpdApi.h"


// CONSTANTS
//const ?type ?constant_var = ?constant;

// LOCAL CONSTANTS AND MACROS
//const ?type ?constant_var = ?constant;
//#define ?macro_name ?macro_def

// ============================= LOCAL FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// ?function_name ?description.
// ?description
// Returns: ?value_1: ?description
//          ?value_n: ?description_line1
//                    ?description_line2
// -----------------------------------------------------------------------------
//
/*
?type ?function_name(
    ?arg_type arg,  // ?description
    ?arg_type arg)  // ?description
    {

    ?code  // ?comment

    // ?comment
    ?code
    }
*/

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestNpdApi::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestNpdApi::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestNpdApi::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestNpdApi::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestFetchTemplate", CTestNpdApi::FetchTemplate ),
        ENTRY( "TestFetchMemo", CTestNpdApi::FetchMemo ),
        ENTRY( "TestNoOfTemplates", CTestNpdApi::NoOfTemplates ),
        ENTRY( "SaveFileAsMemoUsingFileName", CTestNpdApi::SaveFileAsMemoUsingFileName ),
        ENTRY( "SaveFileAsMemoUsingHandle", CTestNpdApi::SaveFileAsMemoUsingHandle ),
        ENTRY( "TestAddContent", CTestNpdApi::AddContent ),
        ENTRY( "Model", CTestNpdApi::Model ),                
        //ADD NEW ENTRY HERE
        // [test cases entries] - Do not remove

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

//Funcs Defns
// -----------------------------------------------------------------------------
// CTestNpdApi::FetchTemplate
// -----------------------------------------------------------------------------
TInt CTestNpdApi::FetchTemplate( CStifItemParser& aItem )
    {
			HBufC* retData = CNotepadApi::FetchTemplateL();
			if( retData )
				{
					delete retData;
					return KErrNone;
				}
				return KErrGeneral;
		}

// -----------------------------------------------------------------------------
// CTestNpdApi::FetchMemo
// -----------------------------------------------------------------------------
TInt CTestNpdApi::FetchMemo( CStifItemParser& aItem )
    {
			HBufC* retData = CNotepadApi::FetchMemoL();
			if( retData )
				{
					delete retData;
					return KErrNone;
				}
				return KErrGeneral;
		}

// -----------------------------------------------------------------------------
// CTestNpdApi::NoOfTemplates
// -----------------------------------------------------------------------------
TInt CTestNpdApi::NoOfTemplates( CStifItemParser& aItem )
    {
			TInt noOfTmplts = CNotepadApi::NumberOfTemplates();
			//By default there will be a 10 templates, so verifying for more than 0
			if ( noOfTmplts >= 0 )
				{
					return KErrNone;
				}
			return KErrGeneral;
		}

// -----------------------------------------------------------------------------
// CTestNpdApi::SaveFileAsMemoUsingFileName
// -----------------------------------------------------------------------------
TInt CTestNpdApi::SaveFileAsMemoUsingFileName( CStifItemParser& aItem )
    {
    	TInt err = 0;
    	TInt encoding;
    	aItem.GetNextInt(encoding);
			
			//Verifying parameter for correct value
			if ( (encoding != 0) && (encoding != 1) )
				{
				iLog->Log( _L("Wrong parameter, please give either 0 or 1(encoding)") );	
				return KErrGeneral;
				}
			
    	TFileName fileName;
			fileName.Append(KExampleFilePath);
			//If 0, no encoding
			if(encoding == 0)
				{
					TRAP(err, CNotepadApi::SaveFileAsMemoL(fileName));
				}
			else
				{
					TRAP(err, CNotepadApi::SaveFileAsMemoL(fileName, KCharacterSetIdentifierIso88591));			
				}

			if(err == KErrNone)
				{ 
					return KErrNone;
				}
				return err;
		}

// -----------------------------------------------------------------------------
// CTestNpdApi::SaveFileAsMemoUsingHandle
// -----------------------------------------------------------------------------
TInt CTestNpdApi::SaveFileAsMemoUsingHandle( CStifItemParser& aItem )
    {
    	TInt err = 0;
    	TInt encoding;
    	aItem.GetNextInt(encoding);
    	
			//Verifying parameter for correct value
			if ( (encoding != 0) && (encoding != 1) )
				{
				iLog->Log( _L("Wrong parameter, please give either 0 or 1(encoding)") );	
				return KErrGeneral;
				}
    	
    	TFileName fileName;
			fileName.Append( KExampleFilePath );
			
			RFile data;
	    RFs session;
	    User::LeaveIfError( session.Connect() );
	    CleanupClosePushL( session );
	    User::LeaveIfError( data.Open( session, fileName, EFileRead ) );
	    CleanupClosePushL( data );
			
			//If 0, no encoding
			if(encoding == 0)
				{
					TRAP(err, CNotepadApi::SaveFileAsMemoL(data));			
				}
			else
				{
					TRAP(err, CNotepadApi::SaveFileAsMemoL(data, KCharacterSetIdentifierIso88591));			
				}

			CleanupStack::PopAndDestroy( &data );  //data, 
    	CleanupStack::PopAndDestroy( &session );  //session
    	
			if(err == KErrNone)
				{ 
					return KErrNone;
				}
				return err;
		}

// -----------------------------------------------------------------------------
// CTestNpdApi::AddContent
// -----------------------------------------------------------------------------
TInt CTestNpdApi::AddContent( CStifItemParser& aItem )
    {
    	_LIT( KNote, "Saving this text as Notes/Memo");
			TRAPD(err, CNotepadApi::AddContentL( KNote ));		
			//Just verifying the error code
			if(err == KErrNone)
				{ 
					return KErrNone;
				}
				return err;
		}

// -----------------------------------------------------------------------------
// CTestNpdApi::Model
// -----------------------------------------------------------------------------
TInt CTestNpdApi::Model( CStifItemParser& aItem )
    {
    	
    	CNotepadApi* ptrToNpd = CNotepadApi::NewL();	
    	//Not testing the ProbeMemoL() function, but just using to test Model() function.
    	TInt key = 327;
    	ptrToNpd->ProbeMemoL(key);
		  CNotepadModel* retData = ptrToNpd->Model();
			//deleting the pointer as it is not used anymore.
			delete ptrToNpd;
			//Verifying the pointer, is exist means model() is created properly
			if( retData )
				{					
					return KErrNone;
				}
				return KErrGeneral;
		}

// -----------------------------------------------------------------------------
// CTestNpdApi::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt CTestNpdApi::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  [End of File] - Do not remove
