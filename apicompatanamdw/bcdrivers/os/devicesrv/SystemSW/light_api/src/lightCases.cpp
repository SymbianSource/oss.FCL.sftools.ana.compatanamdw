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
* Description:  ?Description
*
*/

/* Changed by Vaibhav - 13Aug07 for Removing CodeScanner Warnings - High/medium */


// INCLUDE FILES
#include <e32math.h>
#include "light.h"
#include <HWRMLight.h>

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
// Clight::Case
// Returns a test case by number.
//
// This function contains an array of all available test cases 
// i.e pair of case name and test function. If case specified by parameter
// aCaseNumber is found from array, then that item is returned.
// 
// The reason for this rather complicated function is to specify all the
// test cases only in one place. It is not necessary to understand how
// function pointers to class member functions works when adding new test
// cases. See function body for instructions how to add new test case.
// -----------------------------------------------------------------------------
//
const TCaseInfo Clight::Case ( 
    const TInt aCaseNumber ) const 
     {

    /**
    * To add new test cases, implement new test case function and add new 
    * line to KCases array specify the name of the case and the function 
    * doing the test case
    * In practice, do following
    * 1) Make copy of existing test case function and change its name
    *    and functionality. Note that the function must be added to 
    *    light.cpp file and to light.h 
    *    header file.
    *
    * 2) Add entry to following KCases array either by using:
    *
    * 2.1: FUNCENTRY or ENTRY macro
    * ENTRY macro takes two parameters: test case name and test case 
    * function name.
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
        // To add new test cases, add new items to this array
        ENTRY( "[Light] LightOffAndOn", LightOffAndOn ),
        ENTRY( "[Light] LightOffAndOnWithDuration", LightOffAndOn2 ),
        ENTRY( "[Light] LightOffAndOnWithDurationAndIntensity", LightOffAndOn3 ),
        ENTRY( "[Light] LightOffAndBlink", LightOffAndBlink ),
        ENTRY( "[Light] LightOffAndBlinkWithDuration", LightOffAndBlink2 ),
        ENTRY( "[Light] LightOffAndBlinkAllParam", LightOffAndBlink3 ),
        ENTRY( "[Light] LightOffWithDurationAndBlink", LightOffAndBlink4 ),
        // Example how to use OOM functionality
        //OOM_ENTRY( "Loop test with OOM", LoopTest, ETrue, 2, 3),
        //OOM_FUNCENTRY( PrintTest, ETrue, 1, 3 ),
        };

    // Verify that case number is valid
    if( (TUint) aCaseNumber >= sizeof( KCases ) / 
                               sizeof( TCaseInfoInternal ) )
        {
        // Invalid case, construct empty object
        TCaseInfo null( (const TText*) L"" );
        null.iMethod = NULL;
        null.iIsOOMTest = EFalse;
        null.iFirstMemoryAllocation = 0;
        null.iLastMemoryAllocation = 0;
        return null;
        } 

    // Construct TCaseInfo object and return it
    TCaseInfo tmp ( KCases[ aCaseNumber ].iCaseName );
    tmp.iMethod = KCases[ aCaseNumber ].iMethod;
    tmp.iIsOOMTest = KCases[ aCaseNumber ].iIsOOMTest;
    tmp.iFirstMemoryAllocation = KCases[ aCaseNumber ].iFirstMemoryAllocation;
    tmp.iLastMemoryAllocation = KCases[ aCaseNumber ].iLastMemoryAllocation;
    return tmp;

    }

// -----------------------------------------------------------------------------
// Clight::PrintTest
// Simple printing to UI test.
// -----------------------------------------------------------------------------
//
TInt Clight::PrintTest( 
    TTestResult& aResult )
    {
     /* Simple print test */
    _LIT( KPrintTest, "PrintTest" );
    _LIT( KEnter, "Enter" );
    _LIT( KOnGoing, "On-going" );
    _LIT( KExit, "Exit" );

    TestModuleIf().Printf( 0, KPrintTest, KEnter );
           
    TestModuleIf().Printf( 1, KPrintTest, KOnGoing );
    
    TestModuleIf().Printf( 0, KPrintTest, KExit );

    // Test case passed

    // Sets test case result and description(Maximum size is KStifMaxResultDes)
    _LIT( KDescription, "PrintTest passed" );
    aResult.SetResult( KErrNone, KDescription );

    // Case was executed
    return KErrNone;

    }


// -----------------------------------------------------------------------------
// ?classname::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
?type ?classname::?member_function(
   ?arg_type arg,
   ?arg_type arg )
   {

   ?code

   }
*/
// -----------------------------------------------------------------------------
// Clight::LightOffAndOn
// Set primary display on and off
// -----------------------------------------------------------------------------
//
TInt Clight::LightOffAndOn( TTestResult& aResult )
    {
    TInt iErrVal = KErrNone;
    
    //create light instance
    CHWRMLight* iMyLight;
    TRAPD(err, iMyLight = CHWRMLight::NewL(this));
    if(err != KErrNone)
    {
    	return err;
    }

	  TRAP(iErrVal, iMyLight->LightOffL(CHWRMLight::EPrimaryDisplay));	
		TRAP(err, CTestScheduler::StartAndStopL(100));
		if(err != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		delete iMyLight;
		iMyLight = NULL;
		return err;
		}
		
	  if(iErrVal != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		delete iMyLight;
		iMyLight = NULL;	
		return KErrNone;
		}

 	  //set light on for default intensity and infinite duration
	  TRAP(iErrVal, iMyLight->LightOnL(CHWRMLight::EPrimaryDisplay));	
		TRAP(err, CTestScheduler::StartAndStopL(100));
		if(err != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		delete iMyLight;
		iMyLight = NULL;
		return err;
		}
	  if(iErrVal != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOnL leave") );
		delete iMyLight;
		iMyLight = NULL;	
		return KErrNone;
		}

    delete iMyLight;   
		iMyLight = NULL;	
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// Clight::LightOffAndOn
// Set primary display on and off
// -----------------------------------------------------------------------------
//
TInt Clight::LightOffAndOn2( TTestResult& aResult )
    {
    TInt iErrVal = KErrNone;
    
    //create light instance
    CHWRMLight* iMyLight;
    TRAP(iErrVal, iMyLight = CHWRMLight::NewL(this));
	  if(iErrVal != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		return KErrNone;
		}

	  TRAP(iErrVal, iMyLight->LightOffL(CHWRMLight::EPrimaryDisplay));	
		TRAPD(err, CTestScheduler::StartAndStopL(100));
		if(err != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		delete iMyLight;
		iMyLight = NULL;
		return err;
		}
	  if(iErrVal != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		delete iMyLight;
		iMyLight = NULL;	
		return iErrVal;
		}

 	  //set light on for default intensity and infinite duration
	  TRAP(iErrVal, iMyLight->LightOnL(CHWRMLight::EPrimaryDisplay, 1000));		
		TRAP(err, CTestScheduler::StartAndStopL(1000));
		if(err != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		delete iMyLight;
		iMyLight = NULL;
		return err;
		}
	  if(iErrVal != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOnL leave") );
		delete iMyLight;
		iMyLight = NULL;	
		return KErrNone;
		}

    delete iMyLight;   
		iMyLight = NULL;	
    return KErrNone;
    
    }
// -----------------------------------------------------------------------------
// Clight::LightOffAndOn
// Set primary display on and off
// -----------------------------------------------------------------------------
//
TInt Clight::LightOffAndOn3( TTestResult& aResult )
    {
    TInt iErrVal = KErrNone;
    
    //create light instance
    CHWRMLight* iMyLight;
    TRAP(iErrVal, iMyLight = CHWRMLight::NewL(this));
	  if(iErrVal != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		return iErrVal;
		}

	  TRAP(iErrVal, iMyLight->LightOffL(CHWRMLight::EPrimaryDisplay));		
		TRAPD(err, CTestScheduler::StartAndStopL(100));
		if(err != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		delete iMyLight;
		iMyLight = NULL;
		return err;
		}
	  if(iErrVal != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		delete iMyLight;
		iMyLight = NULL;	
		return KErrNone;
		}

 	  //set light on for default intensity and infinite duration
	  TRAP(iErrVal, iMyLight->LightOnL(CHWRMLight::EPrimaryDisplay, 1000, 30, ETrue));	
		TRAP(err, CTestScheduler::StartAndStopL(1000));
		if(err != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		delete iMyLight;
		iMyLight = NULL;
		return err;
		}
	  if(iErrVal != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOnL leave") );
		delete iMyLight;
		iMyLight = NULL;	
		return KErrNone;
		}

    delete iMyLight;   
		iMyLight = NULL;	
    return KErrNone;
    
    }    
// -----------------------------------------------------------------------------
// Clight::LightOffAndBlink
// Set primary display on and off
// -----------------------------------------------------------------------------
//
TInt Clight::LightOffAndBlink( TTestResult& aResult )
    {
    TInt iErrVal = KErrNone;
    
    //create light instance
    CHWRMLight* iMyLight;
    TRAP(iErrVal, iMyLight = CHWRMLight::NewL(this));
	  if(iErrVal != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		return iErrVal;
		}
    

	  TRAP(iErrVal, iMyLight->LightOffL(CHWRMLight::EPrimaryDisplay));
		TRAPD(err, CTestScheduler::StartAndStopL(100));
		if(err != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		delete iMyLight;
		iMyLight = NULL;
		return err;
		}
	  if(iErrVal != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		delete iMyLight;
		iMyLight = NULL;	
		return KErrNone;
		}

 	  //set light blink for default intensity and infinite duration
	  TRAP(iErrVal, iMyLight->LightBlinkL(CHWRMLight::EPrimaryDisplay));	
		TRAP(err, CTestScheduler::StartAndStopL(100));
		if(err != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		delete iMyLight;
		iMyLight = NULL;
		return err;
		}
	  if(iErrVal != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightBlinkL leave") );
		delete iMyLight;
		iMyLight = NULL;	
		return KErrNone;
		}

    delete iMyLight;   
		iMyLight = NULL;	
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// Clight::LightOffAndBlink
// Set primary display on and off
// -----------------------------------------------------------------------------
//
TInt Clight::LightOffAndBlink2( TTestResult& aResult )
    {
    TInt iErrVal = KErrNone;
    
    //create light instance
    CHWRMLight* iMyLight;
    TRAP(iErrVal, iMyLight = CHWRMLight::NewL(this));
	  if(iErrVal != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		return iErrVal;
		}

	  TRAP(iErrVal, iMyLight->LightOffL(CHWRMLight::EPrimaryDisplay));
		TRAPD(err, CTestScheduler::StartAndStopL(100));
		if(err != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		delete iMyLight;
		iMyLight = NULL;
		return err;
		}
	  if(iErrVal != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		delete iMyLight;
		iMyLight = NULL;	
		return KErrNone;
		}

 	  //set light blink for default intensity and infinite duration
	  TRAP(iErrVal, iMyLight->LightBlinkL(CHWRMLight::EPrimaryDisplay, 1000));
		TRAP(err, CTestScheduler::StartAndStopL(1000));
		if(err != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		delete iMyLight;
		iMyLight = NULL;
		return err;
		}
	  if(iErrVal != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightBlinkL leave") );
		delete iMyLight;
		iMyLight = NULL;	
		return KErrNone;
		}

    delete iMyLight;   
		iMyLight = NULL;	
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// Clight::LightOffAndBlink
// Set primary display on and off
// -----------------------------------------------------------------------------
//
TInt Clight::LightOffAndBlink3( TTestResult& aResult )
    {
    TInt iErrVal = KErrNone;
    
    //create light instance
    CHWRMLight* iMyLight;
    TRAP(iErrVal, iMyLight = CHWRMLight::NewL(this));
 	  if(iErrVal != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		return iErrVal;
		}
   

	  TRAP(iErrVal, iMyLight->LightOffL(CHWRMLight::EPrimaryDisplay));
		TRAPD(err, CTestScheduler::StartAndStopL(100));
		if(err != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		delete iMyLight;
		iMyLight = NULL;
		return err;
		}
	  if(iErrVal != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		delete iMyLight;
		iMyLight = NULL;	
		return KErrNone;
		}

 	  //set light blink for default intensity and infinite duration
	  TRAP(iErrVal, iMyLight->LightBlinkL(CHWRMLight::EPrimaryDisplay, 5000, 1000, 1000, 85 ));
		TRAP(err, CTestScheduler::StartAndStopL(5000));
		if(err != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		delete iMyLight;
		iMyLight = NULL;
		return err;
		}
	  if(iErrVal != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightBlinkL leave") );
		delete iMyLight;
		iMyLight = NULL;	
		return KErrNone;
		}

    delete iMyLight;   
		iMyLight = NULL;	
    return KErrNone;
    
    }
    
// -----------------------------------------------------------------------------
// Clight::LightOffAndBlink
// Set primary display on and off
// -----------------------------------------------------------------------------
//
TInt Clight::LightOffAndBlink4( TTestResult& aResult )
    {
    TInt iErrVal = KErrNone;
    
    //create light instance
    CHWRMLight* iMyLight;
    TRAP(iErrVal, iMyLight = CHWRMLight::NewL(this));
	  if(iErrVal != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		return iErrVal;
		}

	  TRAP(iErrVal, iMyLight->LightOffL(CHWRMLight::EPrimaryDisplay, 2000));		
		TRAPD(err, CTestScheduler::StartAndStopL(2000));
		if(err != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		delete iMyLight;
		iMyLight = NULL;
		return err;
		}
	  if(iErrVal != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		delete iMyLight;
		iMyLight = NULL;	
		return KErrNone;
		}

 	  //set light blink for default intensity and infinite duration
	  TRAP(iErrVal, iMyLight->LightBlinkL(CHWRMLight::EPrimaryDisplay, 1000));
		TRAP(err, CTestScheduler::StartAndStopL(1000));
		if(err != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightOffL leave") );
		delete iMyLight;
		iMyLight = NULL;
		return err;
		}
	  if(iErrVal != KErrNone)
		{
		aResult.SetResult( iErrVal, _L("LightBlinkL leave") );
		delete iMyLight;
		iMyLight = NULL;	
		return KErrNone;
		}

    delete iMyLight;   
		iMyLight = NULL;	
    return KErrNone;
    
    }
        
// -----------------------------------------------------------------------------
// Clight::LightStatusChanged
// 
// -----------------------------------------------------------------------------
//
void Clight::LightStatusChanged( TInt aTarget, CHWRMLight::TLightStatus aStatus)
{

	iTarget = aTarget;
	iStatus = aStatus;
	        
  switch ( aStatus )
      {
      case CHWRMLight::ELightOn:
          iLog->Log(_L("Light state changed: ELightOn"));
         
          break;
      case CHWRMLight::ELightOff:
          iLog->Log(_L("Light state changed: ELightOff"));
         
          break;
      case CHWRMLight::ELightBlink:
          iLog->Log(_L("Light state changed: ELightBlink"));
         
          break;
      case CHWRMLight::ELightStatusUnknown:
          iLog->Log(_L("Light state changed: ELightStatusUnknown"));
         
          break;
      default:
          iLog->Log(_L("Light state changed: UNDEFINED !!!"));
         
          break;
      }
}

// ========================== OTHER EXPORTED FUNCTIONS =========================

// -----------------------------------------------------------------------------
// ?function_name implements...
// ?implementation_description.
// Returns: ?value_1: ?description
//          ?value_n: ?description
//                    ?description
// -----------------------------------------------------------------------------
//
/*
?type  ?function_name(
    ?arg_type arg,  // ?description
    ?arg_type arg )  // ?description
    {

    ?code

    }
*/
//  End of File
