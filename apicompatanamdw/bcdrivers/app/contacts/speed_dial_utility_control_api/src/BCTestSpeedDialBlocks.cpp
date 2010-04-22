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
#include <StifParser.h>
#include <Stiftestinterface.h>
#include "BCTestSpeedDial.h"

#include <spdiacontrol.h>
#include <cpbkcontactengine.h> 
#include <f32file.h>
// EXTERNAL DATA STRUCTURES
//extern  ?external_data;

// EXTERNAL FUNCTION PROTOTYPES  
//extern ?external_function( ?arg_type,?arg_type );

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def

// LOCAL CONSTANTS AND MACROS
//const ?type ?constant_var = ?constant;
//#define ?macro_name ?macro_def

// MODULE DATA STRUCTURES
//enum ?declaration
//typedef ?declaration

// LOCAL FUNCTION PROTOTYPES
//?type ?function_name( ?arg_type, ?arg_type );

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;

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
// CBCTestSpeedDial::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CBCTestSpeedDial::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CBCTestSpeedDial::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CBCTestSpeedDial::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        //ENTRY( "ExampleForTestSpdialL", CBCTestSpeedDial::ExampleForTestSpdialL ),
        ENTRY( "TestNewL", CBCTestSpeedDial::TestNewL ),
        ENTRY( "TestNewL2", CBCTestSpeedDial::TestNewL2 ),
        ENTRY( "TestAssignDialNumberL", CBCTestSpeedDial::TestAssignDialNumberL ),
        ENTRY( "TestExecuteLD", CBCTestSpeedDial::TestExecuteLD ),
        ENTRY( "TestDialNumberL", CBCTestSpeedDial::TestDialNumberL ),
        ENTRY( "TestVoiceMailL", CBCTestSpeedDial::TestVoiceMailL ),
        ENTRY( "TestPbkEngine", CBCTestSpeedDial::TestPbkEngine ),
        ENTRY( "TestIndex", CBCTestSpeedDial::TestIndex ),
        ENTRY( "TestNumber", CBCTestSpeedDial::TestNumber ),
        ENTRY( "TestContactId", CBCTestSpeedDial::TestContactId ),
        ENTRY( "TestPhoneDialNumber", CBCTestSpeedDial::TestPhoneDialNumber ),
        ENTRY( "TestPhoneNumber", CBCTestSpeedDial::TestPhoneNumber )
        //ADD NEW ENTRY HERE
        // [test cases entries] - Do not remove

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CBCTestSpeedDial::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CBCTestSpeedDial::ExampleForTestSpdialL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KBCTestSpeedDial, "BCTestSpeedDial" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, KBCTestSpeedDial, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KBCTestSpeedDial, 
                                KParam, i, &string );
        i++;
        }

    return KErrNone;

    }


TInt CBCTestSpeedDial::TestNewL( CStifItemParser& aItem )
	{
	
    // Print to UI
    _LIT( KBCConnSettingsUITest, "BCTestSpeedDial" );
    _LIT( KNew, "In NewL" );
    //TestModuleIf().Printf( 0, KBCConnSettingsUITest, KNew );

    // Print to log file
    //iLog->Log( KNew );

    TInt err = KErrNone;
    CSpdiaControl* spd = NULL;
    TRAP( err, spd =  CSpdiaControl::NewL() );
    delete spd;
    
    return err;
	}

TInt CBCTestSpeedDial::TestNewL2( CStifItemParser& aItem )
	{

	//RFs session;
	//User::LeaveIfError(session.Connect());					
	CPbkContactEngine* pbk = CPbkContactEngine::NewL( &iSession );	
	
	TInt err = KErrNone;
	CSpdiaControl* spd = NULL;
    TRAP( err, spd =  CSpdiaControl::NewL(*pbk) );	 
    delete spd;
    
    delete pbk;
    pbk = 0;
  
    return err;
	}

TInt CBCTestSpeedDial::TestAssignDialNumberL( CStifItemParser& aItem )
	{
//	RFs session;
//	User::LeaveIfError( session.Connect() );
	CPbkContactEngine* pbk = CPbkContactEngine::NewL( &iSession );
	CSpdiaControl* spd = CSpdiaControl::NewL();
	
	TRAPD( err, spd->AssignDialNumberL(5) );

	delete spd;
    spd = 0;
    delete pbk;
    pbk = 0;
        
    return err;
	}

TInt CBCTestSpeedDial::TestExecuteLD( CStifItemParser& aItem )
	{
//  	RFs session;
//	User::LeaveIfError(session.Connect());
	CPbkContactEngine* pbk = CPbkContactEngine::NewL(&iSession);
	CSpdiaControl* spd = CSpdiaControl::NewL(*pbk);
	
	TInt result;
	TRAPD(err,result = spd->ExecuteLD(1, 1));
			
  	spd = 0;
    delete pbk;
    pbk = 0;	        
    //session.Close();
    
    return err;
	}

TInt CBCTestSpeedDial::TestDialNumberL( CStifItemParser& aItem )
	{
//  	RFs session;
//	User::LeaveIfError(session.Connect());
	CPbkContactEngine* pbk = CPbkContactEngine::NewL(&iSession);
	CSpdiaControl* spd = CSpdiaControl::NewL(*pbk);
	TBuf<100> voice;
	TRAPD(err,spd->DialNumberL(5,voice));
	
	delete spd;
    spd = 0;
    delete pbk;
    pbk = 0;	        
    //session.Close();
    
    return err;
	}

TInt CBCTestSpeedDial::TestVoiceMailL( CStifItemParser& aItem )
	{
//	RFs session;
//	User::LeaveIfError(session.Connect());
	CPbkContactEngine* pbk = CPbkContactEngine::NewL(&iSession);
	CSpdiaControl* spd = CSpdiaControl::NewL(*pbk);
	TBuf<100> voice;
	

	TRAPD( err,spd->VoiceMailL(voice) );	

	delete spd;
	spd = 0;
	delete pbk;
	pbk = 0;	        
	//session.Close();
	
	return err;
	}

TInt CBCTestSpeedDial::TestPbkEngine( CStifItemParser& aItem )
	{
//	RFs session;
//	User::LeaveIfError(session.Connect());
	CPbkContactEngine* pbk = CPbkContactEngine::NewL(&iSession);
	CSpdiaControl* spd = CSpdiaControl::NewL(*pbk);
	CPbkContactEngine* ptest = spd->PbkEngine();
	
	TInt reValue = KErrNone;
	
	if ( !ptest )
		{
		reValue =  KErrAbort;
		}
	
	  delete spd;
    spd = 0;
    delete pbk;
    pbk = 0;	        
    //session.Close();
    
    return reValue;
	
	}

TInt CBCTestSpeedDial::TestIndex( CStifItemParser& aItem )
	{

	//CPbkContactEngine* pbk = CPbkContactEngine::NewL(&iSession);
	CSpdiaControl* spd = CSpdiaControl::NewL();
	TRAPD( err, spd->Index(5) );

	delete spd;
  spd = 0;
    
  return err;
	
	}

TInt CBCTestSpeedDial::TestNumber( CStifItemParser& aItem )
	{
//  	RFs session;
//	User::LeaveIfError(session.Connect());
	CPbkContactEngine* pbk = CPbkContactEngine::NewL(&iSession);
	CSpdiaControl* spd = CSpdiaControl::NewL(*pbk);
	
	TInt err = KErrNone;
	TRAP( err, spd->Number(5); )
	delete spd;
    spd = 0;
    delete pbk;
    pbk = 0;
    //session.Close();
    if ( err == KErrNotFound || err == KErrNone )
    	{
    	return KErrNone;
    	}
    else
    	{
    	return err;
    	}

	}

TInt CBCTestSpeedDial::TestContactId( CStifItemParser& aItem )
	{
//	RFs session;
//	User::LeaveIfError(session.Connect());
	CPbkContactEngine* pbk = CPbkContactEngine::NewL(&iSession);
	CSpdiaControl* spd = CSpdiaControl::NewL(*pbk);
	//TContactItemId contact = spd->ContactId(4);	
	
	TInt err = KErrNone;
	TRAP( err, spd->ContactId(4) );	
	delete spd;
    spd = 0;
    delete pbk;
    pbk = 0;
    //session.Close();

	return err;
		
	}

TInt CBCTestSpeedDial::TestPhoneDialNumber( CStifItemParser& aItem )
	{
//  	RFs session;
//	User::LeaveIfError(session.Connect());
	CPbkContactEngine* pbk = CPbkContactEngine::NewL(&iSession);
	CSpdiaControl* spd = CSpdiaControl::NewL(*pbk);
	TDesC telnum = spd->PhoneDialNumber(5);	
	
	delete spd;
    spd = 0;
    delete pbk;
    pbk = 0;
    //session.Close();
	if(&telnum)
		{        		
		return KErrNone;	
		}
	else
		{
		return KErrNotFound;
		}			

	}

TInt CBCTestSpeedDial::TestPhoneNumber( CStifItemParser& aItem )
	{
//	RFs session;
//	User::LeaveIfError(session.Connect());
	CPbkContactEngine* pbk = CPbkContactEngine::NewL(&iSession);
	CSpdiaControl* spd = CSpdiaControl::NewL(*pbk);
	TDesC telnum = spd->PhoneNumber(5);	
	delete spd;
	spd = 0;
	delete pbk;
	pbk = 0;
	//session.Close();
	if(&telnum)
		{        		
		return KErrNone;	
		}
	else
		{
		return KErrNotFound;
		}
	}

TInt CBCTestSpeedDial::DeleteSelf( CStifItemParser& aItem )
	{
	if ( iControl )
		{
		delete iControl;
		iControl = NULL;
		}
	return KErrNone;
	}

// -----------------------------------------------------------------------------
// CBCTestSpeedDial::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt CBCTestSpeedDial::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  [End of File] - Do not remove
