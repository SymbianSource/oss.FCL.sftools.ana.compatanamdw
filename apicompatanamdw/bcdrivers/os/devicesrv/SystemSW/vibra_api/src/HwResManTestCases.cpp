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
#include "HwResManTest.h"

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
// CHwResManTest::Case
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
const TCaseInfo CHwResManTest::Case ( 
    const TInt aCaseNumber ) const 
     {

    /**
    * To add new test cases, implement new test case function and add new 
    * line to KCases array specify the name of the case and the function 
    * doing the test case
    * In practice, do following
    * 1) Make copy of existing test case function and change its name
    *    and functionality. Note that the function must be added to 
    *    HwResManTest.cpp file and to HwResManTest.h 
    *    header file.
    * 2) Add entry to following KCases array either by using FUNCENTRY or 
    *    ENTRY macro. 
    * ENTRY macro takes two parameters: test case name and test case 
    * function name.
    * FUNCENTRY macro takes only test case function name as a parameter and uses
    * that as a test case name and test case function name.
    */
    
    static TCaseInfoInternal const KCases[] =
        {
        // To add new test cases, add new items to this array
        //FUNCENTRY( PrintTest ),
        ENTRY( "[Vibra] Check status", Check_status ),
        ENTRY( "[Vibra] Duration 5s", StartVibra_5s ),
        ENTRY( "[Vibra] Duration infinite", StartVibra_infinite ),
        ENTRY( "[Vibra] Duration bigger than KVibraCtrlMaxTime", StartVibra_KVibraCtrlMaxTime ),
        ENTRY( "[Vibra] Set vibra when not allowed", StartVibra_notallowed ),        
        ENTRY( "[Vibra] Start (looped)", StartVibra_loop ),
        ENTRY( "[Vibra] Start and stop (looped)", StartVibra_loop2 ),
        ENTRY( "[Vibra] Start infinite and stop (looped)", StartVibra_loop3 ),
        ENTRY( "[Vibra] Unsupported vibra intensity", unsupported_Vibra_Intensity ),
        ENTRY( "[Vibra] Unsupported vibra duration", unsupported_Vibra_Duration ),
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
// CHwResManTest::HWRMTest
// Check_status.
// Basic functionality. Create vibra instance. Set vibra mode on and check vibra status
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::Check_status( TTestResult& aResult )
    {
     
    CHWRMVibra* myVibra;
    TInt error = KErrNone;
    TInt mode;
    CHWRMVibra::TVibraStatus status;
	// CRepository* iSession;
	    
    /* Init notification values */
    InitTestVariables();
    
    /* Create Vibra */
	  TRAPD(err,  myVibra = CHWRMVibra::NewL(this));
	  if(err != KErrNone)
	  {
	  	aResult.iResult = err;
	  	return err;
	  }
	
	//uusi repository
	// iSession = CRepository::NewL(KCRUidVibraCtrl);

	//asetetaan arvo keywordille (= set vibra on in profile)
	iSession->Set(KVibraCtrlProfileVibraEnabled, 1);	
	
	// delay so that notification is received
	TRAP(err,  CTestScheduler::StartAndStopL(1000));
	if(err != KErrNone)
	{
		aResult.iResult = err;
	 	return err;
	}
	
	/* Get vibra mode (EvibraModeON / EVibraModeOFF / EVibraModeUnknown */
	mode = myVibra->VibraSettings();
	
	if (mode == CHWRMVibra::EVibraModeON)
	{
		/* Vibra is set on in user profile / Central Repository */
			
	    status = myVibra->VibraStatus();
	    
	    if (status == CHWRMVibra::EVibraStatusStopped) 
	    {
	    
		    /* Start vibra for 3 seconds */
		    error = RunTestVibra(myVibra,3000, 100);
		    	    
		    if (error == KErrNone)
		    {
			    /* Wait 1 second */
					TRAP(err,  CTestScheduler::StartAndStopL(1000));
					if(err != KErrNone)
					{
						aResult.iResult = err;
					 	return err;
					}
		    
			    status = myVibra->VibraStatus();
			    
			    if (statusUpdated && myStatus == CHWRMVibra::EVibraStatusOn && status == CHWRMVibra::EVibraStatusOn)
			    {
				    /* Init status and mode values */
				    InitTestVariables();			    
				    
				    /* Wait 3 seconds */
						TRAP(err,  CTestScheduler::StartAndStopL(3000));
						if(err != KErrNone)
						{
							aResult.iResult = err;
						 	return err;
						}
					    
				    /* Check vibra status again */
					if (statusUpdated && myStatus == CHWRMVibra::EVibraStatusStopped)
					{
						/* Test successful */
						aResult.SetResult( KErrNone, _L("") );
					}
						
					else
					{
				    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
				    	aResult.SetResult( KErrGeneral, _L("2nd Vibra status update failed") );
					}
			    }
			    else
			    {
			    	iLog->Log(_L("Status bit:%d, Vibra status1:%d, status2:%d Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, status, mode, myMode);
			    	aResult.SetResult( KErrGeneral, _L("1st Vibra status update failed") );
			    }
		    }
		    else
		    {
		    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		    	aResult.SetResult( error, _L("StartVibraL returned something else than KErrNone") );
		    }    	
	    }
	    else
	    {
	    	// Wrong vibra status
	    	
	    }
	}
	else if(mode == CHWRMVibra::EVibraModeOFF)
	{
		/* Vibra is OFF in profile*/
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( KErrNotSupported, _L("Vibra is OFF in user profile / Central Repository") );
	}
	else
	{
		/* Something went wrong */
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( error, _L("Cannot get Vibra mode") );    	
	}
	
	/* Delete vibra */
	delete myVibra;
	
	/* Delete cenrep session */
	// delete iSession;

    // Case is executed. 
    return KErrNone;
    
    }




// -----------------------------------------------------------------------------
// CHwResManTest::HWRMTest
// StartVibra_5s.
// Basic functionality. Start vibra for 5 seconds then check that vibra status
// is "Stopped" 
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::StartVibra_5s( TTestResult& aResult )
    {
     
    CHWRMVibra* myVibra;
    TInt error = KErrNone;
    TInt mode;
	// CRepository* iSession;
    
    /* Create Vibra */
    TRAPD(err, myVibra = CHWRMVibra::NewL(this));
    if(err != KErrNone)
    {
    	aResult.iResult = err;
    	return err;
    }
	
	//uusi repository
	// iSession = CRepository::NewL(KCRUidVibraCtrl);

    /* Init notification values */
    InitTestVariables();

	//asetetaan arvo keywordille (= set vibra on in profile)
	iSession->Set(KVibraCtrlProfileVibraEnabled, 1);	
	
	// delay so that notification is received
	TRAP(err,  CTestScheduler::StartAndStopL(1000));
	if(err != KErrNone)
	{
		aResult.iResult = err;
	 	return err;
	}
	
	/* Get vibra mode (EvibraModeON / EVibraModeOFF / EVibraModeUnknown */
	mode = myVibra->VibraSettings();
	
	if (mode == CHWRMVibra::EVibraModeON)
	{
		/* Vibra is set on in user profile / Central Repository */
			
	    /* Start vibra for 5 seconds */
	    error = RunTestVibra(myVibra,5000);
	    	    
	    if (error == KErrNone)
	    {
		    /* Wait 1 second */
			    TRAP(err, CTestScheduler::StartAndStopL(1000));		    
			    if(err != KErrNone)
			    {
			    	aResult.iResult = err;
			    	return err;
			    }
		    
		    if (statusUpdated && myStatus == CHWRMVibra::EVibraStatusOn)
		    {
			    /* Init status and mode values */
			    InitTestVariables();			    
			    
			    /* Wait 5 seconds */
			    TRAP(err, CTestScheduler::StartAndStopL(5000));		    
			    if(err != KErrNone)
			    {
			    	aResult.iResult = err;
			    	return err;
			    }
			    
			    /* Check vibra status again */
				if (statusUpdated && myStatus == CHWRMVibra::EVibraStatusStopped)
				{
					/* Test successful */
					aResult.SetResult( KErrNone, _L("") );
				}
					
				else
				{
			    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
			    	aResult.SetResult( KErrGeneral, _L("2nd Vibra status update failed") );
				}
		    }
		    else
		    {
		    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		    	aResult.SetResult( KErrGeneral, _L("1st Vibra status update failed") );
		    }
	    }
	    else
	    {
	    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
	    	aResult.SetResult( error, _L("StartVibraL returned something else than KErrNone") );
	    }    	
	    
	}
	else if(mode == CHWRMVibra::EVibraModeOFF)
	{
		/* Vibra is OFF in profile*/
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( KErrNotSupported, _L("Vibra is OFF in user profile / Central Repository") );
	}
	else
	{
		/* Something went wrong */
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( error, _L("Cannot get Vibra mode") );    	
	}
	
	/* Delete vibra */
	delete myVibra;
	
	/* Delete cenrep session */
	// delete iSession;

    // Case is executed. 
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CHwResManTest::HWRMTest
// StartVibra_infinite.
// Basic functionality. Start vibra for infinite time then check that vibra status
// is "On". Then stop and check that status is "Stopped" 
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::StartVibra_infinite( TTestResult& aResult )
    {
     
    CHWRMVibra* myVibra;
    TInt error = KErrNone;
    TInt mode;
	// CRepository* iSession;
	    
    /* Init notification values */
    InitTestVariables();
    
    /* Create Vibra */
    TRAPD(err, myVibra = CHWRMVibra::NewL(this));
    if(err != KErrNone)
    {
    	aResult.iResult = err;
    	return err;
    }
	
	//uusi repository
	// iSession = CRepository::NewL(KCRUidVibraCtrl);

    /* Init notification values */
    InitTestVariables();

	//asetetaan arvo keywordille (= set vibra on in profile)
	iSession->Set(KVibraCtrlProfileVibraEnabled, 1);	
	
	// delay so that notification is received
	TRAP(err,  CTestScheduler::StartAndStopL(1000));
	if(err != KErrNone)
	{
		aResult.iResult = err;
	 	return err;
	}
	
	/* Get vibra mode (EvibraModeON / EVibraModeOFF / EVibraModeUnknown */
	mode = myVibra->VibraSettings();
	
	if (mode == CHWRMVibra::EVibraModeON)
	{
		/* Vibra is set on in user profile / Central Repository */
			
	    /* Start vibra infinite */
	    error = RunTestVibra(myVibra,0,99);
	    	    
	    if (error == KErrNone)
	    {
		    /* Wait 1 second */
			    TRAP(err, CTestScheduler::StartAndStopL(5000));
			    if(err != KErrNone)
			    {
			    	aResult.iResult = err;
			    	return err;
			    }
		    
		    if (statusUpdated && myStatus == CHWRMVibra::EVibraStatusOn)
		    {
			    /* Init status and mode values */
			    InitTestVariables();			    
			    
					TRAP(err,  CTestScheduler::StartAndStopL(1999));
					if(err != KErrNone)
					{
						aResult.iResult = err;
					 	return err;
					}
			    
			    TRAP(error, myVibra->StopVibraL());
			    
			    TRAP(err, CTestScheduler::StartAndStopL(500));
			    if(err != KErrNone)
			    {
			    	aResult.iResult = err;
			    	return err;
			    }
			    
			    /* Check vibra status again */
				if (error == KErrNone && statusUpdated && myStatus == CHWRMVibra::EVibraStatusStopped)
				{
					/* Test successful */
					aResult.SetResult( KErrNone, _L("") );
				}
					
				else
				{
			    	iLog->Log(_L("Error:%d Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), error, statusUpdated, myStatus, mode, myMode);
			    	aResult.SetResult( KErrGeneral, _L("2nd Vibra status update failed") );
				}
		    }
		    else
		    {
		    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		    	aResult.SetResult( KErrGeneral, _L("1st Vibra status update failed") );
		    }
	    }
	    else
	    {
	    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
	    	aResult.SetResult( error, _L("StartVibraL returned something else than KErrNone") );
	    }    	
	    
	}
	else if(mode == CHWRMVibra::EVibraModeOFF)
	{
		/* Vibra is OFF in profile*/
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( KErrNotSupported, _L("Vibra is OFF in user profile / Central Repository") );
	}
	else
	{
		/* Something went wrong */
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( error, _L("Cannot get Vibra mode") );    	
	}
	
	/* Delete vibra */
	delete myVibra;
	
	/* Delete cenrep session */
	// delete iSession;

    // Case is executed. 
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CHwResManTest::HWRMTest
// StartVibra_KVibraCtrlMaxTime.
// Start vibra for bigger than maximum duration value.
// Check that vibra status is "Stopped" when maximum value is reached
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::StartVibra_KVibraCtrlMaxTime( TTestResult& aResult )
    {
     
    CHWRMVibra* myVibra;
    TInt error = KErrNone;
    TInt mode;
    TInt maxTime;
	// CRepository* iSession;
	    
    /* Init notification values */
    InitTestVariables();
    
    /* Create Vibra */
    TRAPD(err, myVibra = CHWRMVibra::NewL(this));
    if(err != KErrNone)
    {
    	aResult.iResult = err;
    	return err;
    }
	
	//Create new repository session
	// iSession = CRepository::NewL(KCRUidVibraCtrl);

    /* Init notification values */
    InitTestVariables();

	 //asetetaan arvo keywordille (= set vibra on in profile)
	 iSession->Set(KVibraCtrlProfileVibraEnabled, 1);	
	
	// delay so that notification is received
    TRAP(err, CTestScheduler::StartAndStopL(1000));
    if(err != KErrNone)
    {
    	aResult.iResult = err;
    	return err;
    }
	
	//haetaan vibran maksimiaika
	iSession->Get(KVibraCtrlMaxTime, maxTime);
	
	/* Get vibra mode (EvibraModeON / EVibraModeOFF / EVibraModeUnknown */
	mode = myVibra->VibraSettings();
	
	if (mode == CHWRMVibra::EVibraModeON)
	{
		/* Vibra is set on in user profile / Central Repository */

	    /* Start vibra for maxTime + 1 */
	    error = RunTestVibra(myVibra,maxTime+1000);
	    	    
	    if (error == KErrNone)
	    {
			/* Duration value is out of range */
			
	    TRAP(err, CTestScheduler::StartAndStopL(1000));
	    if(err != KErrNone)
	    {
	    	aResult.iResult = err;
	    	return err;
	    }
			    
		    /* Check vibra status */
			if (statusUpdated && myStatus == CHWRMVibra::EVibraStatusOn)
			{
				InitTestVariables();
				
				TRAP(err,  CTestScheduler::StartAndStopL(maxTime));
				if(err != KErrNone)
				{
					aResult.iResult = err;
				 	return err;
				}
				/* Notification of Stopped vibra should be received by now */
				
				if (statusUpdated && myStatus == CHWRMVibra::EVibraStatusStopped)
				{
					aResult.SetResult( KErrNone, _L("") );
				}			
				else
				{
			    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
			    	aResult.SetResult( KErrGeneral, _L("2nd Vibra status update failed") );
				}	
			}
			else
			{
		    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		    	aResult.SetResult( KErrGeneral, _L("1st Vibra status update failed") );
			}	
				
	    }
	    else
	    {
	    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
	    	aResult.SetResult( KErrGeneral, _L("Start Vibra returned wrong error") );
	    }
	}
	else if(mode == CHWRMVibra::EVibraModeOFF)
	{
		/* Vibra is OFF in profile*/
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( KErrGeneral, _L("Vibra is OFF in user profile / Central Repository") );
	}
	else
	{
		/* Something went wrong */
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		error = KErrGeneral;
		aResult.SetResult( KErrGeneral, _L("Cannot get Vibra mode") );    	
	}
	
	/* Delete vibra */
	delete myVibra;
	
	/* Delete cenrep session */
	// delete iSession;

    // Case is executed. 
    return KErrNone;
    
    }


 // -----------------------------------------------------------------------------
// CHwResManTest::HWRMTest
// StartVibra_notallowed
// Error case. Try to start vibra when vibra mode is off.
// Vibra return KErrAccessDenied.
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::StartVibra_notallowed( TTestResult& aResult )
    {
     
    CHWRMVibra* myVibra;
    TInt error = KErrNone;
    TInt mode;
    // CRepository* iSession;
	
    /* Init notification values */
    InitTestVariables();
    
    /* Create Vibra */
    TRAPD(err, myVibra = CHWRMVibra::NewL(this));
    if(err != KErrNone)
    {
    	aResult.iResult = err;
    	return err;
    }
	
	//uusi repository
	// iSession = CRepository::NewL(KCRUidVibraCtrl);

	// set vibra Off in profile
	iSession->Set(KVibraCtrlProfileVibraEnabled, 0);	
	// delay so that notification is received
  TRAP(err, CTestScheduler::StartAndStopL(1000));
  if(err != KErrNone)
  {
   	aResult.iResult = err;
   	return err;
  }
	/* Get vibra mode (EvibraModeON / EVibraModeOFF / EVibraModeUnknown */
	mode = myVibra->VibraSettings();
	
	if (statusUpdated && myStatus == CHWRMVibra::EVibraStatusNotAllowed && mode == CHWRMVibra::EVibraModeOFF  && myMode == CHWRMVibra::EVibraModeOFF)
	{
		InitTestVariables();
		iSession->Set(KVibraCtrlProfileVibraEnabled, 1);
	  TRAP(err, CTestScheduler::StartAndStopL(100));
	  if(err != KErrNone)
	  {
	   	aResult.iResult = err;
	   	return err;
	  }
		mode = myVibra->VibraSettings();
		
		if (statusUpdated && myStatus == CHWRMVibra::EVibraStatusStopped && mode == CHWRMVibra::EVibraModeON && myMode == CHWRMVibra::EVibraModeON)
		{
			InitTestVariables();
			iSession->Set(KVibraCtrlProfileVibraEnabled, 0);
		  TRAP(err, CTestScheduler::StartAndStopL(100));
		  if(err != KErrNone)
		  {
		   	aResult.iResult = err;
		   	return err;
		  }
			mode = myVibra->VibraSettings();
			
			if (statusUpdated && myStatus == CHWRMVibra::EVibraStatusNotAllowed && mode == CHWRMVibra::EVibraModeOFF  && myMode == CHWRMVibra::EVibraModeOFF)
			{
				InitTestVariables();
				iSession->Set(KVibraCtrlProfileVibraEnabled, 1);
			  TRAP(err, CTestScheduler::StartAndStopL(100));
			  if(err != KErrNone)
			  {
			   	aResult.iResult = err;
			   	return err;
			  }
				mode = myVibra->VibraSettings();
				
				if (statusUpdated && myStatus == CHWRMVibra::EVibraStatusStopped && mode == CHWRMVibra::EVibraModeON && myMode == CHWRMVibra::EVibraModeON)
				{
					InitTestVariables();
					iSession->Set(KVibraCtrlProfileVibraEnabled, 0);
				  TRAP(err, CTestScheduler::StartAndStopL(100));
				  if(err != KErrNone)
				  {
				   	aResult.iResult = err;
				   	return err;
				  }
					mode = myVibra->VibraSettings();
					
					if (statusUpdated && myStatus == CHWRMVibra::EVibraStatusNotAllowed && mode == CHWRMVibra::EVibraModeOFF && myMode == CHWRMVibra::EVibraModeOFF)
					{
						InitTestVariables();
						error = RunTestVibra(myVibra,4000);
						
						if ( error == KErrAccessDenied)
						{	
							/* OK! Starting vibra should fail */
							InitTestVariables();
						  TRAP(err, CTestScheduler::StartAndStopL(1000));
						  if(err != KErrNone)
						  {
						   	aResult.iResult = err;
						   	return err;
						  }
							iSession->Set(KVibraCtrlProfileVibraEnabled, 1);
						  TRAP(err, CTestScheduler::StartAndStopL(100));
						  if(err != KErrNone)
						  {
						   	aResult.iResult = err;
						   	return err;
						  }
							mode = myVibra->VibraSettings();
							
							if (mode == CHWRMVibra::EVibraModeON && myMode == CHWRMVibra::EVibraModeON)
							{	
								InitTestVariables();
								
							  TRAP(err, CTestScheduler::StartAndStopL(5000));
							  if(err != KErrNone)
							  {
							   	aResult.iResult = err;
							   	return err;
							  }
								
								/* Try to start vibra */
								error = RunTestVibra(myVibra,5000);
								
							  TRAP(err, CTestScheduler::StartAndStopL(100));
							  if(err != KErrNone)
							  {
							   	aResult.iResult = err;
							   	return err;
							  }
								mode = myVibra->VibraSettings();
								
								if (error == KErrNone && statusUpdated && myStatus == CHWRMVibra::EVibraStatusOn && mode == CHWRMVibra::EVibraModeON && myMode == CHWRMVibra::EVibraModeUnknown) // unknown because it is not changed
								{
									/* Vibra start should succeed */
									InitTestVariables();
									
									/* Set vibra off in profile while vibra is still running */
									
									iSession->Set(KVibraCtrlProfileVibraEnabled, 0);				
								  TRAP(err, CTestScheduler::StartAndStopL(200));
								  if(err != KErrNone)
								  {
								   	aResult.iResult = err;
								   	return err;
								  }
									mode = myVibra->VibraSettings();
																				 
								    if (statusUpdated && myStatus == CHWRMVibra::EVibraStatusNotAllowed && mode == CHWRMVibra::EVibraModeOFF && myMode == CHWRMVibra::EVibraModeOFF)
								    {
								    	/* Set vibra status on */
								    	InitTestVariables();
									    iSession->Set(KVibraCtrlProfileVibraEnabled, 1);				
										  TRAP(err, CTestScheduler::StartAndStopL(100));
										  if(err != KErrNone)
										  {
										   	aResult.iResult = err;
										   	return err;
										  }
									    mode = myVibra->VibraSettings();
									    
									    if (statusUpdated && myStatus == CHWRMVibra::EVibraStatusStopped && mode == CHWRMVibra::EVibraModeON && myMode == CHWRMVibra::EVibraModeON)
								    	{
								    		aResult.SetResult( KErrNone, _L("") );
								    		
								    		//InitTestVariables();
								    		
								    		/* Wait 5 seconds */
								    		//CTestScheduler::StartAndStopL(5000);
								    		
								    		//mode = myVibra->VibraSettings();
								    									    		
								    		//if (statusUpdated && myStatus == CHWRMVibra::EVibraStatusStopped && mode == CHWRMVibra::EVibraModeON && myMode == CHWRMVibra::EVibraModeUnknown)
								    		//{
								    			//iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
								    		//	aResult.SetResult( KErrNone, _L("") );	
								    		//}
								    		//else
								    		//{
								    		//	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
								    		//	aResult.SetResult( KErrGeneral, _L("Vibra status/mode update failed 8") );
						
								    		//}
								    		
								    	}
									    else
									    {
									    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
									    	aResult.SetResult( KErrGeneral, _L("Vibra status/mode update failed 6") );
									    }
									    	    
								    }
								    else
								    {
								    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
								    	aResult.SetResult( KErrGeneral, _L("Vibra status/mode update failed 7") );
								    }									
								}
								else
								{
									iLog->Log(_L("Error:%d, Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), error, statusUpdated, myStatus, mode, myMode);
									aResult.SetResult( KErrGeneral, _L("Vibra status/mode not OK") );	
						
								}							
								
							}
							else
							{
								iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
								aResult.SetResult( KErrGeneral, _L("Vibra status/mode update failed1") );
							}
							
						}
						else
						{
							iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
							aResult.SetResult( KErrGeneral, _L("Start Vibra returned wrong error") );
						}		
					}
					else
					{
						iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
						aResult.SetResult( KErrGeneral, _L("Vibra status/mode update failed2") );
					}
					
				}
				else
				{
					iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
					aResult.SetResult( KErrGeneral, _L("Vibra status/mode update failed3") );
				}
								
			}
			else
			{
				iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
				aResult.SetResult( KErrGeneral, _L("Vibra status/mode update failed4") );
			}
				
		}
		else
		{
			iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
			aResult.SetResult( KErrGeneral, _L("Vibra status/mode update failed5") );
		}
							    		
	}
	else if(mode == CHWRMVibra::EVibraModeON)
	{
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( KErrGeneral, _L("Wrong vibra mode") );
	}
	else
	{
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( KErrGeneral, _L("Cannot get Vibra mode") );    	
	}
	
	/* Delete vibra */
	delete myVibra;
	
	/* Delete cenrep session */
	// delete iSession;

    // Case is executed. 
    return KErrNone;
    
    }



// -----------------------------------------------------------------------------
// CHwResManTest::HWRMTest
// StartVibra_loop.
// Start vibra several times.
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::StartVibra_loop( TTestResult& aResult )
    {
     
    CHWRMVibra* myVibra;
    TInt error = KErrNone;
    TInt mode;
    TInt i;
    TInt intensity = -61;
    // CRepository* iSession;
	    
    /* Init notification values */
    InitTestVariables();
    aResult.SetResult( KErrNone, _L("") );
    
    /* Create Vibra */
		TRAPD(err, myVibra = CHWRMVibra::NewL(this));
		if(err != KErrNone)
		{
		 	aResult.iResult = err;
		 	return err;
		}
	
	//uusi repository
	// iSession = CRepository::NewL(KCRUidVibraCtrl);

	// set vibra Off in profile
	iSession->Set(KVibraCtrlProfileVibraEnabled, 0);	
	
	// delay so that notification is received
	TRAP(err, CTestScheduler::StartAndStopL(1000));
	if(err != KErrNone)
	{
	 	aResult.iResult = err;
	 	return err;
	}

	/* Get vibra mode (EvibraModeON / EVibraModeOFF / EVibraModeUnknown */
	mode = myVibra->VibraSettings();
	
	if (mode == CHWRMVibra::EVibraModeOFF)
	{	
		
	    /* Init notification values */
	    InitTestVariables();

		//asetetaan arvo keywordille (= set vibra on in profile)
		iSession->Set(KVibraCtrlProfileVibraEnabled, 1);	
		
		// delay so that notification is received
		TRAP(err, CTestScheduler::StartAndStopL(1000));
		if(err != KErrNone)
		{
		 	aResult.iResult = err;
		 	return err;
		}
		
		/* Get vibra mode (EvibraModeON / EVibraModeOFF / EVibraModeUnknown */
		mode = myVibra->VibraSettings();
		
		if (mode == CHWRMVibra::EVibraModeON)
		{
			/* Vibra is set on in user profile / Central Repository */
			
			/* Loop vibra five times (start vibra for 2 seconds and call again after 1s delay */
			for(i=0;i<4;i++)
			{
				intensity = intensity + 20; /* Intensity is increased by 20% for each loop */
				
				InitTestVariables();
			    
			    //CleanupStack::PushL(myVibra);
			    
			    /* Start vibra */
			    error = RunTestVibra(myVibra,4000, intensity);
			    	    
			    if (error == KErrNone)
			    {
						TRAP(err, CTestScheduler::StartAndStopL(2500));
						if(err != KErrNone)
						{
						 	aResult.iResult = err;
						 	return err;
						}
				    
				    if (CHWRMVibra::EVibraStatusOn != myVibra->VibraStatus())
					{
				    	iLog->Log(_L("Loop:%d Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), i, statusUpdated, myStatus, mode, myMode);
				    	aResult.SetResult( KErrGeneral, _L("Vibra status update failed") );
				    	break;
				    }
				    
			    }
			    else if(error == KErrNotSupported)
			    {
			    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
						iLog->Log(_L("StartVibraL returned with KErrNotSupported for intensity:%d"),intensity);
			    }
			    else
			    {
			    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
			    	aResult.SetResult( error, _L("StartVibraL returned something else than KErrNone") );
			    	break;
			    }    				
				
			}
			
			TRAP(err, CTestScheduler::StartAndStopL(2000));
			if(err != KErrNone)
			{
			 	aResult.iResult = err;
			 	return err;
			}
			
			/* Vibra should be stopped by now */
			
		    if (!statusUpdated || myStatus == CHWRMVibra::EVibraStatusOn)
		    {
		    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		    	aResult.SetResult( KErrGeneral, _L("2nd Vibra status update failed") );
		    	error = KErrGeneral;
		    }
		    
		}
		else if(mode == CHWRMVibra::EVibraModeOFF)
		{
			/* Vibra is OFF in profile*/
			iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
			aResult.SetResult( KErrGeneral, _L("Vibra is OFF in user profile / Central Repository") );
		}
		else
		{
			/* Something went wrong */
			iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
			aResult.SetResult( KErrGeneral, _L("Cannot get Vibra mode") );    	
		}

	}
	else
	{
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( KErrGeneral, _L("Vibra mode change failed") );	
	}
	
	/* Delete vibra */
	delete myVibra;
	
	/* Delete cenrep session */
	// delete iSession;

    // Case is executed. 
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CHwResManTest::HWRMTest
// StartVibra_loop.
// Start and stop vibra several times.
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::StartVibra_loop2( TTestResult& aResult )
    {
     
    CHWRMVibra* myVibra;
    TInt error = KErrNone;
    TInt mode;
    TInt i;
    TInt intensity = 100;
    // CRepository* iSession;
	
    /* Init notification values */
    InitTestVariables();
    aResult.SetResult( KErrNone, _L("") );
    
    /* Create Vibra */
		TRAPD(err, myVibra = CHWRMVibra::NewL(this));
		if(err != KErrNone)
		{
		 	aResult.iResult = err;
		 	return err;
		}
	
	//uusi repository
	// iSession = CRepository::NewL(KCRUidVibraCtrl);

	// set vibra Off in profile
	iSession->Set(KVibraCtrlProfileVibraEnabled, 0);	
	
	// delay so that notification is received
	TRAP(err,  CTestScheduler::StartAndStopL(1000));
	if(err != KErrNone)
	{
		aResult.iResult = err;
	 	return err;
	}

	/* Get vibra mode (EvibraModeON / EVibraModeOFF / EVibraModeUnknown */
	mode = myVibra->VibraSettings();
		
	if (mode == CHWRMVibra::EVibraModeOFF)
	{	
		
	    /* Init notification values */
	    InitTestVariables();

		//asetetaan arvo keywordille (= set vibra on in profile)
		iSession->Set(KVibraCtrlProfileVibraEnabled, 1);	
		
		// delay so that notification is received
		TRAP(err, CTestScheduler::StartAndStopL(1000));
		if(err != KErrNone)
		{
		 	aResult.iResult = err;
		 	return err;
		}
		
		/* Get vibra mode (EvibraModeON / EVibraModeOFF / EVibraModeUnknown */
		mode = myVibra->VibraSettings();
		
		if (mode == CHWRMVibra::EVibraModeON)
		{
			/* Vibra is set on in user profile / Central Repository */
			
			for(i=0;i<5;i++)
			{
				InitTestVariables();
				
				intensity = intensity - 30; /* Intensity is decresed by 30% for each loop */
				
			    error = RunTestVibra(myVibra,3000, intensity);
			    	    
			    if (error == KErrNone)
			    {
						TRAP(err, CTestScheduler::StartAndStopL(1000));
						if(err != KErrNone)
						{
						 	aResult.iResult = err;
						 	return err;
						}
				    
				    TRAP(error, myVibra->StopVibraL());
				    
						TRAP(err, CTestScheduler::StartAndStopL(1000));
						if(err != KErrNone)
						{
						 	aResult.iResult = err;
						 	return err;
						}
				    
				    if (error != KErrNone || /* !statusUpdated* ||*/ myStatus != CHWRMVibra::EVibraStatusStopped)
				    {
				    	aResult.SetResult( KErrGeneral, _L("Vibra stopping failed") );
				    	break;
				    }
				    	    
				    
			    }
			    else if(error == KErrNotSupported)
			    {
			    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
						iLog->Log(_L("StartVibraL returned with KErrNotSupported for intensity:%d"),intensity);
			    }   
			    else
			    {
			    	aResult.SetResult( error, _L("StartVibraL returned something else than KErrNone") );
			    	break;
			    }    				
				
			}
			
			TRAP(err, CTestScheduler::StartAndStopL(2000));
			if(err != KErrNone)
			{
			 	aResult.iResult = err;
			 	return err;
			}
			
			/* Vibra should be stopped by now */
			
		    if (!statusUpdated || myStatus == CHWRMVibra::EVibraStatusOn)
		    {
		    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		    	aResult.SetResult( KErrGeneral, _L("2nd Vibra status update failed") );
		    }
		    
		}
		else if(mode == CHWRMVibra::EVibraModeOFF)
		{
			/* Vibra is OFF in profile*/
			iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
			aResult.SetResult( KErrGeneral, _L("Vibra is OFF in user profile / Central Repository") );
		}
		else
		{
			/* Something went wrong */
			iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
			aResult.SetResult( KErrGeneral, _L("Cannot get Vibra mode") );    	
		}

	}
	else
	{
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( KErrGeneral, _L("Vibra mode change failed") );	
	}
	
	/* Delete vibra */
	delete myVibra;
	
	/* Delete cenrep session */
	// delete iSession;

    // Case is executed. 
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CHwResManTest::HWRMTest
// StartVibra_loop_infinite.
// Start and stop vibra several times with 0 duration.
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::StartVibra_loop3( TTestResult& aResult )
    {
     
    CHWRMVibra* myVibra;
    TInt error = KErrNone;
    TInt mode;
    TInt i;
    TInt intensity = 111;
    // CRepository* iSession;
	
    /* Init notification values */
    InitTestVariables();
    
    /* Create Vibra */
		TRAPD(err, myVibra = CHWRMVibra::NewL(this));
		if(err != KErrNone)
		{
		 	aResult.iResult = err;
		 	return err;
		}
	
	/* New repository session */
	// iSession = CRepository::NewL(KCRUidVibraCtrl);

	/* set vibra Off in profile */
	iSession->Set(KVibraCtrlProfileVibraEnabled, 0);	
	
	/* delay so that notification is received */
	TRAP(err, CTestScheduler::StartAndStopL(1000));
	if(err != KErrNone)
	{
	 	aResult.iResult = err;
	 	return err;
	}

	/* Get vibra mode (EvibraModeON / EVibraModeOFF / EVibraModeUnknown */
	mode = myVibra->VibraSettings();
		
	if (mode == CHWRMVibra::EVibraModeOFF)
	{	
		
	    /* Init notification values */
	    InitTestVariables();

		//asetetaan arvo keywordille (= set vibra on in profile)
		iSession->Set(KVibraCtrlProfileVibraEnabled, 1);	
		
		// delay so that notification is received
		TRAP(err, CTestScheduler::StartAndStopL(1000));
		if(err != KErrNone)
		{
		 	aResult.iResult = err;
		 	return err;
		}
		
		//haetaan saman keywordin arvo
		//iSession->Get(KVibraCtrlProfileVibraEnabled, iValue);
		
		/* Get vibra mode (EvibraModeON / EVibraModeOFF / EVibraModeUnknown */
		mode = myVibra->VibraSettings();
		
		if (mode == CHWRMVibra::EVibraModeON)
		{
			/* Vibra is set on in user profile / Central Repository */
			
			for(i=0;i<10;i++)
			{
				InitTestVariables();
				
				intensity = intensity - 11; /* Intensity is decresed by 11% for each loop */
				
			    error = RunTestVibra(myVibra,0, intensity);
			    	    
			    if (error == KErrNone)
			    {
						TRAP(err, CTestScheduler::StartAndStopL(500));
						if(err != KErrNone)
						{
						 	aResult.iResult = err;
						 	return err;
						}
				    
				    TRAP(error, myVibra->StopVibraL());
				    
						TRAP(err, CTestScheduler::StartAndStopL(100));
						if(err != KErrNone)
						{
						 	aResult.iResult = err;
						 	return err;
						}
				    
				    if (error != KErrNone || !statusUpdated || myStatus != CHWRMVibra::EVibraStatusStopped)
				    {
				    	aResult.SetResult( KErrNone, _L("Vibra stopping failed") );
				    	break;
				    }				    
			    }
			    else if(error == KErrNotSupported)
			    {
			    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
						iLog->Log(_L("StartVibraL returned with KErrNotSupported for intensity:%d"),intensity);
			    }  
			    else
			    {
			    	aResult.SetResult( error, _L("StartVibraL returned something else than KErrNone") );
			    	break;
			    }    				
				
			}
			
			TRAP(err, CTestScheduler::StartAndStopL(2000));
			if(err != KErrNone)
			{
			 	aResult.iResult = err;
			 	return err;
			}
			
			/* Vibra should be stopped by now */
			
		    if (!statusUpdated || myStatus == CHWRMVibra::EVibraStatusOn)
		    {
		    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		    	aResult.SetResult( KErrGeneral, _L("2nd Vibra status update failed") );
		    }
		    
		}
		else if(mode == CHWRMVibra::EVibraModeOFF)
		{
			/* Vibra is OFF in profile */
			iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
			aResult.SetResult( KErrGeneral, _L("Vibra is OFF in user profile / Central Repository") );
		}
		else
		{
			/* Something went wrong */
			iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
			aResult.SetResult( KErrGeneral, _L("Cannot get Vibra mode") );    	
		}

	}
	else
	{
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( KErrGeneral, _L("Vibra mode change failed") );	
	}
		
	/* Delete vibra */
	delete myVibra;
	
	/* Delete cenrep session */
	// delete iSession;

    // Case is executed. 
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CHwResManTest::HWRMTest
// StartVibra_unsupported_Vibra_Intensity.
// Try to set unsupported intensity.
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::unsupported_Vibra_Intensity( TTestResult& aResult )
    {
    
    CHWRMVibra* myVibra;
    TInt error = KErrNone;
    TInt mode;
    // CRepository* iSession;
	
    /* Init notification values */
    InitTestVariables();
    
    /* Create Vibra */
		TRAPD(err, myVibra = CHWRMVibra::NewL(this));
		if(err != KErrNone)
		{
		 	aResult.iResult = err;
		 	return err;
		}
	
	/* New repository session */
	// iSession = CRepository::NewL(KCRUidVibraCtrl);

	//asetetaan arvo keywordille (= set vibra on in profile)
	iSession->Set(KVibraCtrlProfileVibraEnabled, 1);	
	
	// delay so that notification is received
	TRAP(err, CTestScheduler::StartAndStopL(1000));
	if(err != KErrNone)
	{
	 	aResult.iResult = err;
	 	return err;
	}
	
	/* Get vibra mode (EvibraModeON / EVibraModeOFF / EVibraModeUnknown */
	mode = myVibra->VibraSettings();
	
	if (mode == CHWRMVibra::EVibraModeON)
	{
		/* Vibra is set on in user profile / Central Repository */

		InitTestVariables();

	    error = RunTestVibra(myVibra,0, KHWRMVibraMaxIntensity+1);
	    
	    /* 
	    	If Intensity is 
	    */
	       
	    if (error == KErrArgument)
	    {
		    
		    error = RunTestVibra(myVibra,0, KHWRMVibraMinIntensity-1);
		    
		    if (error == KErrArgument)
	    	{
	    		aResult.SetResult( KErrNone, _L("") );
	    	}
	    	else
	    	{
	    		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
	    		aResult.SetResult( KErrGeneral, _L("StartVibraL KHWRMVibraMinIntensity-1") );
	    	}
	    }
	    else
	    {
	    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
	    	aResult.SetResult( KErrGeneral, _L("StartVibraL KHWRMVibraMaxIntensity+1") );
	    }    				
	    
	}
	else if(mode == CHWRMVibra::EVibraModeOFF)
	{
		/* Vibra is OFF in profile*/
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( KErrGeneral, _L("Vibra is OFF in user profile / Central Repository") );
	}
	else
	{
		/* Something went wrong */
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( KErrGeneral, _L("Cannot get Vibra mode") );    	
	}


		
	/* Delete vibra */
	delete myVibra;
	
	/* Delete cenrep session */
	// delete iSession;

    // Case is executed. 
    return KErrNone;    
    }
       
       
// -----------------------------------------------------------------------------
// CHwResManTest::HWRMTest
// StartVibra_unsupported_Vibra_Duration.
// Try to set unsupported duration.
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::unsupported_Vibra_Duration( TTestResult& aResult )
    {
    
    CHWRMVibra* myVibra;
    TInt error = KErrNone;
    TInt mode, maxTime;
    // CRepository* iSession;
	
    /* Init notification values */
    InitTestVariables();
    
    /* Create Vibra */
		TRAPD(err, myVibra = CHWRMVibra::NewL(this));
		if(err != KErrNone)
		{
		 	aResult.iResult = err;
		 	return err;
		}

	/* New repository session */
	// iSession = CRepository::NewL(KCRUidVibraCtrl);

	//asetetaan arvo keywordille (= set vibra on in profile)
	iSession->Set(KVibraCtrlProfileVibraEnabled, 1);	
	
	//haetaan vibran maksimiaika
	iSession->Get(KVibraCtrlMaxTime, maxTime);
	
	// delay so that notification is received
	TRAP(err, CTestScheduler::StartAndStopL(1000));
	if(err != KErrNone)
	{
	 	aResult.iResult = err;
	 	return err;
	}
	
	/* Get vibra mode (EvibraModeON / EVibraModeOFF / EVibraModeUnknown */
	mode = myVibra->VibraSettings();
	
	if (mode == CHWRMVibra::EVibraModeON)
	{
		/* Vibra is set on in user profile / Central Repository */

		InitTestVariables();

	    error = RunTestVibra(myVibra,KHWRMVibraMaxDuration + 1, KHWRMVibraMaxIntensity);
	       
	    if (error == KErrArgument)
	    {
		    
		    error = RunTestVibra(myVibra,-1, KHWRMVibraMinIntensity);
		    
		    if (error == KErrArgument)
	    	{
	    		aResult.SetResult( KErrNone, _L("") );
	    	}
	    	else
	    	{
	    		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
	    		aResult.SetResult( KErrGeneral, _L("StartVibraL negative duration") );
	    	}
	    }
	    else
	    {
	    	iLog->Log(_L("Error:%d, Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"),error, statusUpdated, myStatus, mode, myMode);
	    	aResult.SetResult( KErrGeneral, _L("StartVibraL KHWRMVibraMaxDuration + 1") );
	    }    				
	    
	}
	else if(mode == CHWRMVibra::EVibraModeOFF)
	{
		/* Vibra is OFF in profile*/
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( KErrGeneral, _L("Vibra is OFF in user profile / Central Repository") );
	}
	else
	{
		/* Something went wrong */
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( KErrGeneral, _L("Cannot get Vibra mode") );    	
	}

	/* Delete vibra */
	delete myVibra;
	
	/* Delete cenrep session */
	// delete iSession;

    // Case is executed. 
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
