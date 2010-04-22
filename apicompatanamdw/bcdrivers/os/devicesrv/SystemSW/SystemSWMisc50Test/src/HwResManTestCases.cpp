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
        ENTRY( "[Vibra] Vibra with overlapping pulse", &CHwResManTest::StartVibra_OverlapPulse ),
        ENTRY( "[Vibra] Vibra with overlapping pulses", &CHwResManTest::StartVibra_OverlapPulses ),
        ENTRY( "[Vibra] Vibra pulse with overlapping pulses", &CHwResManTest::Pulse_OverlapPulses ),
        ENTRY( "[Vibra] Vibra pulses (loop)", &CHwResManTest::Sequential_Pulses ),
        ENTRY( "[Vibra] Vibra unsupported pulse intensity", &CHwResManTest::unsupported_Pulse_Intensity ),
        ENTRY( "[Vibra] Vibra pulse status checks", &CHwResManTest::Pulse_notallowed ),
        ENTRY( "[Vibra] Vibra reserve, start, pulse", &CHwResManTest::Reserve_Start_Pulse_Vibra ),
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
// CHwResManTest::PrintTest
// Simple printing to UI test.
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::PrintTest( 
    TTestResult& aResult )    
    {
     /* Simple print test */
    TestModuleIf().Printf( 0, _L("PrintTest"),  _L("Enter"));
           
    TestModuleIf().Printf( 1, _L("PrintTest"),  _L("On-going") );
    
    TestModuleIf().Printf( 0, _L("PrintTest"),  _L("Exit"));

    // Test case passed
    
	// Sets test case result and description(Maximum size is KStifMaxResultDes)
    aResult.SetResult( KErrNone, _L("PrintTest passed") );
    
    // Case was executed
    return KErrNone;
    
    }


    
// -----------------------------------------------------------------------------
// CHwResManTest::PrintTest
// Another printing to UI test.
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::LoopTest( TTestResult& aResult )
    {
     
    /* Simple print and wait loop */
    TestModuleIf().Printf( 0, _L("State"),  _L("Looping"));
    for( TInt i=0; i<10; i++)
        {
        TestModuleIf().Printf( 1, _L("Running"),  _L("%d"), i);
        User::After( 1000000 );
        }
    TestModuleIf().Printf( 0, _L("State"),  _L("Finished"));

    // Test case passed
    
	// Sets test case result and description(Maximum size is KStifMaxResultDes)
    aResult.SetResult( KErrNone, _L("LoopTest passed") );
    
    // Case was executed
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CHwResManTest::HWRMTest
// StartVibra_OverlapPulse.
// Try to request vibration and overlapping pulse request.
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::StartVibra_OverlapPulse( TTestResult& aResult )
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
	
    /* Init notification values */
    InitTestVariables();

	/* Set vibra on in profile */
	error = iSession->Set(KVibraCtrlProfileVibraEnabled, 1);	
	
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
	        /* Set us observing feedback mode changes */
	        myVibra->SetFeedbackObserver( this );
        	/* Set feedback vibra on in profile */
        	error = iSession->Set(KVibraCtrlProfileFeedbackEnabled, 1);	

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
			    
			    error = PulseTestVibra(myVibra);
			    
        	    if (error == KErrNone)
        	    {
    			    /* Wait 1 second */
    			    CTestScheduler::StartAndStopL(1000);
    			    
    			    // Check vibra status again, status won't get updated if not changed,
    			    // so that is why we actually check it has not changed.
    				if (!statusUpdated)
    				{
        			    /* Init status and mode values */
        			    InitTestVariables();			    

        			    /* Wait 4 seconds */
        			    TRAP(err, CTestScheduler::StartAndStopL(4000));
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
        			    	aResult.SetResult( KErrGeneral, _L("3rd Vibra status update failed") );
        				}
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
			    	aResult.SetResult( error, _L("PulseVibraL returned something else than KErrNone") );
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
	
    // Case is executed. 
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CHwResManTest::HWRMTest
// StartVibra_OverlapPulses.
// Try to request vibration and overlapping pulse requests.
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::StartVibra_OverlapPulses( TTestResult& aResult )
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
	
    /* Init notification values */
    InitTestVariables();

	/* Set vibra on in profile */
	error = iSession->Set(KVibraCtrlProfileVibraEnabled, 1);	
	
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
	    error = RunTestVibra(myVibra,5000,10);
	    	    
	    if (error == KErrNone)
	    {
	        /* Set us observing feedback mode changes */
	        myVibra->SetFeedbackObserver( this );
        	/* Set feedback vibra on in profile */
        	error = iSession->Set(KVibraCtrlProfileFeedbackEnabled, 1);	

		    /* Wait 1 second */
		    CTestScheduler::StartAndStopL(1000);		    
		    
		    if (statusUpdated && myStatus == CHWRMVibra::EVibraStatusOn)
		    {
			    /* Init status and mode values */
			    InitTestVariables();			    
			    
			    /* Request 600 ms pulse with intensity 50 */
			    error = PulseTestVibra(myVibra, 600, 50 );
			    
        	    if (error == KErrNone)
        	    {
    			    /* Wait 100 ms */
    			    TRAP(err, CTestScheduler::StartAndStopL(100));
			    if(err != KErrNone)
			    {
			    	aResult.iResult = err;
			    	return err;
			    }
    			    
    			    // Check vibra status again, status won't get updated if not changed,
    			    // so that is why we actually check it has not changed.
    				if (!statusUpdated)
    				{
        			    /* Init status and mode values */
        			    InitTestVariables();

        			    /* Request 200 ms pulse with intensity 100 */
        			    error = PulseTestVibra(myVibra, 200, 100 );

                	    if (error == KErrNone)
                	    {
            			    /* Wait 100 ms */
            			    TRAP(err, CTestScheduler::StartAndStopL(100));
			    						if(err != KErrNone)
			    						{
			    							aResult.iResult = err;
			    							return err;
			    						}
            			    
            			    // Check vibra status again, status won't get updated if not changed,
            			    // so that is why we actually check it has not changed.
            				if (!statusUpdated)
            				{
                			    /* Init status and mode values */
                			    InitTestVariables();

                			    /* Wait 4 seconds */
                			    TRAP(err, CTestScheduler::StartAndStopL(4000));
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
                			    	aResult.SetResult( KErrGeneral, _L("4th Vibra status update failed") );
                				}
            				}
            				else
            				{
            			    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
            			    	aResult.SetResult( KErrGeneral, _L("3rd Vibra status update failed") );
            				}
                	    }
        				else
        				{
        			    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
        			    	aResult.SetResult( error, _L("2nd PulseVibraL returned something else than KErrNone") );
        				}
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
			    	aResult.SetResult( error, _L("1st PulseVibraL returned something else than KErrNone") );
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
	
    // Case is executed. 
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CHwResManTest::HWRMTest
// Pulse_OverlapPulses.
// Try to request vibra pulse and overlapping pulses with it.
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::Pulse_OverlapPulses( TTestResult& aResult )
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
	
    /* Init notification values */
    InitTestVariables();

	/* Set vibra on in profile */
	error = iSession->Set(KVibraCtrlProfileFeedbackEnabled, 1);	
	
	// delay so that notification is received
	TRAP(err, CTestScheduler::StartAndStopL(1000));
	if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}
	
    /* Set us observing feedback mode changes */
    myVibra->SetFeedbackObserver( this );
    
	/* Get vibra mode (EvibraModeON / EVibraModeOFF / EVibraModeUnknown */
	mode = myVibra->VibraFeedbackSettings();
	
	if (mode == CHWRMVibra::EVibraFeedbackModeON)
	{
	    // Vibra status does not get updated for pulse requests (when real pulse command
	    // configured to be processed by plugin via KHWRMInternalSettingsDeviceSupportsPulse), 
	    // because otherwise short pulses
	    // a) would bring quite a lot of overhead when publishing vibra on/off status very frequently
	    // b) in addition to publishing status, hwrm should keep timers active just for publishing status
			
	    /* Pulse vibra for 5 seconds */
	    error = PulseTestVibra(myVibra,5000,10);
	    	    
	    if (error == KErrNone)
	    {
		    /* Wait 1 second */
		    TRAP(err,CTestScheduler::StartAndStopL(1000)); 
			    if(err != KErrNone)
			    {
			    	aResult.iResult = err;
			    	return err;
			    }
		    
		    // Status updated in case of pulse-command not supported (configuration) and
		    // not updated when pulse-command supported. That is why status not monitored.
		    //if (!statusUpdated)
		    {
			    /* Init status and mode values */
			    InitTestVariables();			    
			    
			    // Following alike pulses are created within two seconds
			    // Vibra may not be stopped after 1600 ms, because initial request is for 5 second
			    // __________ (1000 ms, 100)
			    //   ______________ (1400 ms, 30)
			    //     __________ (1000 ms, 80)
			    //       __ (200 ms, 50)
			    //       ______ (600 ms, 60)
			    
			    error = PulseTestVibra(myVibra, 1000, 100 );
        	    if (error == KErrNone)
        	    {
    			    TRAP(err, CTestScheduler::StartAndStopL(200));
				    if(err != KErrNone)
				    {
				    	aResult.iResult = err;
				    	return err;
				    }

    			    error = PulseTestVibra(myVibra, 1400, 30 );
            	    if (error == KErrNone)
            	    {
        			    TRAP(err, CTestScheduler::StartAndStopL(200));
					    if(err != KErrNone)
					    {
					    	aResult.iResult = err;
					    	return err;
					    }

        			    error = PulseTestVibra(myVibra, 1000, 80 );
                	    if (error == KErrNone)
                	    {
            			   TRAP(err, CTestScheduler::StartAndStopL(200));
						    if(err != KErrNone)
						    {
						    	aResult.iResult = err;
						    	return err;
						    }

            			    error = PulseTestVibra(myVibra, 200, 50 );
            			    TInt error2 = PulseTestVibra(myVibra, 600, 60 );
                    	    if (error == KErrNone && error2 == KErrNone)
                    	    {
                			    /* Wait two seconds */
                			    TRAP(err, CTestScheduler::StartAndStopL(2000));
							    if(err != KErrNone)
							    {
							    	aResult.iResult = err;
							    	return err;
							    }
                			    
                			    // Check vibra status again, status should have not get updated,
                			    // because initial pulse request should still keep vibra active.
                				//if (!statusUpdated)
                				{
                    			    /* Init status and mode values */
                    			    InitTestVariables();

                    			    /* Wait two more seconds */
                    			   TRAP(err, CTestScheduler::StartAndStopL(2000));
								    if(err != KErrNone)
								    {
								    	aResult.iResult = err;
								    	return err;
								    }

                    			    // No matter how pulse requests are being configured to be handled,
                    			    // vibra status must be stopped by now
                    				if (myVibra->VibraStatus() == CHWRMVibra::EVibraStatusStopped)
                    				{
                    					/* Test successful */
                    					aResult.SetResult( KErrNone, _L("") );
                    				}
                    				else
                    				{
                    			    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
                    			    	aResult.SetResult( KErrGeneral, _L("Vibra not stopped") );
                    				}
                				}
                    		    //else
                    		    //{
                    		    //	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
                    		    //	aResult.SetResult( KErrGeneral, _L("2nd Vibra status update failed") );
                    		    //}
                    	    }
                    	    else
                    	    {
                    	        if (error != KErrNone)
                    	    	    aResult.SetResult( error, _L("5th PulseVibraL returned error") );
                    	        if (error2 != KErrNone)
                    	    	    aResult.SetResult( error2, _L("6th PulseVibraL returned error") );
                    	    }    	
                	    }
                	    else
                	    {
                	    	aResult.SetResult( error, _L("4th PulseVibraL returned something else than KErrNone") );
                	    }    	
            	    }
            	    else
            	    {
            	    	aResult.SetResult( error, _L("3rd PulseVibraL returned something else than KErrNone") );
            	    }    	
        	    }
        	    else
        	    {
        	    	aResult.SetResult( error, _L("2nd PulseVibraL returned something else than KErrNone") );
        	    }    	
		    }
		    //else
		    //{
		    //	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		    //	aResult.SetResult( KErrGeneral, _L("1st Vibra status update failed") );
		    //}
	    }
	    else
	    {
	    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
	    	aResult.SetResult( error, _L("PulseVibraL returned something else than KErrNone") );
	    }    	
	    
	}
	else if(mode == CHWRMVibra::EVibraFeedbackModeOFF)
	{
		/* Vibra is OFF in profile*/
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( KErrGeneral, _L("Vibra feedback is OFF in user profile / Central Repository") );
	}
	else
	{
		/* Something went wrong */
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( KErrGeneral, _L("Cannot get Vibra feedback mode") );    	
	}
	
	/* Delete vibra */
	delete myVibra;
	
    // Case is executed. 
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CHwResManTest::HWRMTest
// Sequential_Pulses.
// Try to request vibra pulses frequently in sequence.
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::Sequential_Pulses( TTestResult& aResult )
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
	
    /* Init notification values */
    InitTestVariables();

	/* Set vibra on in profile */
	error = iSession->Set(KVibraCtrlProfileFeedbackEnabled, 1);	
	
	// delay so that notification is received
	TRAP(err, CTestScheduler::StartAndStopL(1000));
    if(err != KErrNone)
    {
    	aResult.iResult = err;
    	return err;
    }
	
    /* Set us observing feedback mode changes */
    myVibra->SetFeedbackObserver( this );
    
	/* Get vibra mode (EvibraModeON / EVibraModeOFF / EVibraModeUnknown */
	mode = myVibra->VibraFeedbackSettings();
	
	if (mode == CHWRMVibra::EVibraFeedbackModeON)
	{
	    // Vibra status does not get updated for pulse requests (when real pulse command
	    // configured to be processed by plugin via KHWRMInternalSettingsDeviceSupportsPulse), 
	    // because otherwise short pulses
	    // a) would bring quite a lot of overhead when publishing vibra on/off status very frequently
	    // b) in addition to publishing status, hwrm should keep timers active just for publishing status
			
		TInt intensity = 0;
		
		for(TInt i=0;i<20;i++)
		{
			InitTestVariables();
			
			intensity = intensity + 5; /* Intensity is incresed by 5% for each loop */
			
		    error = PulseTestVibra(myVibra, 100, intensity);
		    	    
		    if (error == KErrNone)
		    {
			    TRAP(err, CTestScheduler::StartAndStopL(200));		    
			    if(err != KErrNone)
			    {
			    	aResult.iResult = err;
			    	return err;
			    }

		    }
		    else
		    {
		    	aResult.SetResult( error, _L("StartVibraL returned something else than KErrNone") );
		    	break;
		    }    				
		}
		
		if(error == KErrNone )
		{
    		TRAP(err, CTestScheduler::StartAndStopL(1000));
		    if(err != KErrNone)
		    {
		    	aResult.iResult = err;
		    	return err;
		    }
    		
    	    // No matter how pulse requests are being configured to be handled,
    	    // vibra status must be stopped by now
    		if (myVibra->VibraStatus() == CHWRMVibra::EVibraStatusStopped)
    		{
    			/* Test successful */
    			aResult.SetResult( KErrNone, _L("") );
    		}
    	    else
    	    {
    	    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
    	    	aResult.SetResult( KErrGeneral, _L("Vibra not stopped") );
    	    }
	    }
	    else
	    {
	    	iLog->Log(_L("PulseVibraL returned something else than KErrArgument"));
	    	aResult.SetResult( error, _L("PulseVibraL returned something else than KErrArgument") );
	    }
	}
	else if(mode == CHWRMVibra::EVibraFeedbackModeOFF)
	{
		/* Vibra is OFF in profile*/
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( KErrGeneral, _L("Vibra feedback is OFF in user profile / Central Repository") );
	}
	else
	{
		/* Something went wrong */
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( KErrGeneral, _L("Cannot get Vibra feedback mode") );    	
	}
	
	/* Delete vibra */
	delete myVibra;
	
    // Case is executed. 
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CHwResManTest::HWRMTest
// unsupported_Pulse_Intensity.
// Try to request vibra pulse with incorrect intensity.
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::unsupported_Pulse_Intensity( TTestResult& aResult )
    {
     
    CHWRMVibra* myVibra;
    TInt error = KErrNone;
    TInt error2 = KErrNone;
    TInt error3 = KErrNone;
    TInt mode;
	// CRepository* iSession;
    
    /* Create Vibra */
    TRAPD(err, myVibra = CHWRMVibra::NewL(this));
    if(err != KErrNone)
    {
    	aResult.iResult = err;
    	return err;
    }
	
    /* Init notification values */
    InitTestVariables();

	/* Set vibra on in profile */
	error = iSession->Set(KVibraCtrlProfileFeedbackEnabled, 1);	
	
	// delay so that notification is received
	TRAP(err, CTestScheduler::StartAndStopL(1000));
    if(err != KErrNone)
    {
    	aResult.iResult = err;
    	return err;
    }
	
    /* Set us observing feedback mode changes */
    myVibra->SetFeedbackObserver( this );
    
	/* Get vibra mode (EvibraModeON / EVibraModeOFF / EVibraModeUnknown */
	mode = myVibra->VibraFeedbackSettings();
	
	if (mode == CHWRMVibra::EVibraFeedbackModeON)
	{
	    error = PulseTestVibra(myVibra, 100, -100);
	    error2 = PulseTestVibra(myVibra, 100, 0);
	    error3 = PulseTestVibra(myVibra, 100, 101);
	    	    
	    if (error == KErrArgument || error2 == KErrArgument && error3 == KErrArgument)
	    {
			/* Test successful */
			aResult.SetResult( KErrNone, _L("") );
	    }
	    else
	    {
	    	aResult.SetResult( error, _L("PulseVibraL returned something else than KErrArgument") );
	    }    				
	}
	else if(mode == CHWRMVibra::EVibraFeedbackModeOFF)
	{
		/* Vibra is OFF in profile*/
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( KErrGeneral, _L("Vibra feedback is OFF in user profile / Central Repository") );
	}
	else
	{
		/* Something went wrong */
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( KErrGeneral, _L("Cannot get Vibra feedback mode") );    	
	}
	
	/* Delete vibra */
	delete myVibra;
	
    // Case is executed. 
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CHwResManTest::HWRMTest
// Pulse_notallowed.
// Try to request pulse when not allowed.
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::Pulse_notallowed( TTestResult& aResult )
    {
    CHWRMVibra* myVibra;
    TInt error = KErrNone;
    TInt mode;
    
    /* Create Vibra */
    TRAPD(err, myVibra = CHWRMVibra::NewL(this));
    if(err != KErrNone)
    {
    	aResult.iResult = err;
    	return err;
    }
	
    /* Init notification values */
    InitTestVariables();

	/* Set vibra feedback off in profile */
	error = iSession->Set(KVibraCtrlProfileFeedbackEnabled, 0);	
	
	// delay so that notification is received
	TRAP(err, CTestScheduler::StartAndStopL(1000));
    if(err != KErrNone)
    {
    	aResult.iResult = err;
    	return err;
    }
	
	/* Get vibra feedback mode */
	mode = myVibra->VibraFeedbackSettings();
	
	if (mode == CHWRMVibra::EVibraFeedbackModeOFF)
	{
		/* Try pulse vibra */
		error = PulseTestVibra(myVibra,1000,50);
			
	    if (error == KErrAccessDenied)
	    {
        	/* Set vibra feedback on in profile */
        	iSession->Set(KVibraCtrlProfileFeedbackEnabled, 1);	
        	
        	// wait until feedback mode changed
        	TRAP(err, CTestScheduler::StartAndStopL(1000));
		    if(err != KErrNone)
		    {
		    	aResult.iResult = err;
		    	return err;
		    }

        	error = PulseTestVibra(myVibra,1000,50);

        	// delay so that pulse is observed (before session closed)
        	TRAP(err, CTestScheduler::StartAndStopL(2000));
		    if(err != KErrNone)
		    {
		    	aResult.iResult = err;
		    	return err;
		    }
        	
    	    if (error == KErrNone)
    	    {
				/* Test successful */
				aResult.SetResult( KErrNone, _L("") );
    	    }
    	    else
    	    {
    	    	aResult.SetResult( error, _L("PulseVibraL returned something else than KErrNone") );
    	    }
	    }
	    else
	    {
	    	aResult.SetResult( error, _L("PulseVibraL returned something else than KErrAccessDenied") );
	    }
	}
	else if(mode == CHWRMVibra::EVibraFeedbackModeON)
	{
		/* Vibra is OFF in profile*/
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( KErrGeneral, _L("Vibra is ON in user profile / Central Repository") );
	}
	else
	{
		/* Something went wrong */
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
		aResult.SetResult( KErrGeneral, _L("Cannot get Vibra mode") );    	
	}
	
	/* Delete vibras */
	RunReleaseVibra(myVibra);
	delete myVibra;
	
    // Case is executed. 
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CHwResManTest::HWRMTest
// Reserve_Start_Pulse_Vibra.
// Try to reserver vibra and concurrently request normal and pulse vibration.
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::Reserve_Start_Pulse_Vibra( TTestResult& aResult )
    {
    CHWRMVibra* myVibra;
    CHWRMVibra* myVibra2;
    TInt error = KErrNone;
    TInt mode, mode2;
    
    /* Create Vibra */
    TRAPD(err, myVibra = CHWRMVibra::NewL(this));
    if(err != KErrNone)
    {
    	aResult.iResult = err;
    	return err;
    }

    /* Create another Vibra */
    myVibra2 = CHWRMVibra::NewLC(this);
    CleanupStack::Pop(myVibra2);
	
    /* Init notification values */
    InitTestVariables();

	/* Set vibra on in profile */
	error = iSession->Set(KVibraCtrlProfileVibraEnabled, 1);	
	
	// delay so that notification is received
	TRAP(err, CTestScheduler::StartAndStopL(1000));
    if(err != KErrNone)
    {
    	aResult.iResult = err;
    	return err;
    }
	
	/* Get vibra mode (EvibraModeON / EVibraModeOFF / EVibraModeUnknown */
	mode = myVibra->VibraSettings();
	mode2 = myVibra->VibraFeedbackSettings();
	
	if (mode == CHWRMVibra::EVibraModeON && mode2 == CHWRMVibra::EVibraFeedbackModeON)
	{
		/* Reserve vibra */
		error = RunReserveVibra(myVibra, EFalse, ETrue);
			
	    if (error == KErrNone)
	    {
    	    /* Start vibra for 5 seconds */
    	    error = RunTestVibra(myVibra,5000);
    	    	    
    	    if (error == KErrNone)
    	    {
    	        /* Set us observing feedback mode changes */
    	        myVibra2->SetFeedbackObserver( this );
            	/* Set feedback vibra on in profile */
            	error = iSession->Set(KVibraCtrlProfileFeedbackEnabled, 1);	

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
    			    
    			    error = PulseTestVibra(myVibra2);
    			    
            	    if (error == KErrNone)
            	    {
        			    /* Wait 1 second */
        			    TRAP(err, CTestScheduler::StartAndStopL(1000));
					    if(err != KErrNone)
					    {
					    	aResult.iResult = err;
					    	return err;
					    }
        			    
        			    // Check vibra status again, status won't get updated if not changed,
        			    // so that is why we actually check it has not changed.
        				if (!statusUpdated)
        				{
            			    /* Init status and mode values */
            			    InitTestVariables();			    

            			    /* Wait 4 seconds */
            			    TRAP(err, CTestScheduler::StartAndStopL(4000));
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
            			    	aResult.SetResult( KErrGeneral, _L("3rd Vibra status update failed") );
            				}
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
    			    	aResult.SetResult( error, _L("PulseVibraL returned something else than KErrNone") );
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
	    else
	    {
	    	iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Mode from notifier:%d"), statusUpdated, myStatus, mode, myMode);
	    	aResult.SetResult( error, _L("ReserveVibraL returned something else than KErrNone") );
	    }
	}
	else
	{
		/* Something went wrong */
		iLog->Log(_L("Status bit:%d, Vibra status:%d, Vibra mode:%d, Vibra feedback mode:%d, Mode from notifier:%d"), 
		    statusUpdated, myStatus, mode, mode2, myMode);
		aResult.SetResult( KErrGeneral, _L("Cannot get Vibra mode") );    	
	}
	
	/* Delete vibras */
	RunReleaseVibra(myVibra);
	delete myVibra;
	delete myVibra2;
	
    // Case is executed. 
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CHwResManTest::HWRMTest
// Reserve_Vibra.
// Try to reserve vibra.
// -----------------------------------------------------------------------------
//
//  End of File
