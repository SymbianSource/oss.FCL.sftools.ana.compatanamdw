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
* Description:  This module contains the implementation of Cvibractrltest class 
*				 member functions that does the actual tests.
*
*/

// INCLUDE FILES
/* Changed by Vaibhav - 13Aug07 for Removing CodeScanner Warnings - High/medium */

#include "Vibractrltest.h"
#include <vibractrl.h>

#include <e32svr.h>

//#include <vibraInternalCRKeys.h>


// EXTERNAL DATA STRUCTURES
// None

// EXTERNAL FUNCTION PROTOTYPES  
// None

// CONSTANTS
// None

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
// CVibrawrapper::CVibrawrapper
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
CVibrawrapper::CVibrawrapper() : iVibra(NULL) // : iSD1(this)//, iSD2(this) 
{
	// Reserving memory..
}


// -----------------------------------------------------------------------------
// CVibrawrapper::NewL
// Two-phased constructor.
// 
// -----------------------------------------------------------------------------
CVibrawrapper* CVibrawrapper::NewL(TBool NotifUsed) 
{
	CVibrawrapper* wrap = new (ELeave) CVibrawrapper();
	CleanupStack::PushL( wrap );
	wrap->ConstructL(NotifUsed);
	CleanupStack::Pop();
	return wrap;
}

// -----------------------------------------------------------------------------
// CVibrawrapper::ConstructL
// Symbian 2nd phase constructor can leave.
// 
// -----------------------------------------------------------------------------
void CVibrawrapper::ConstructL(TBool NotifUsed)
{

	myTestScheduler = new CActiveScheduler;
	myTestScheduler->Install(myTestScheduler);
    iVibraModeState = CVibraControl::EVibraModeUnknown;
	
	if(NotifUsed)
		iVibra = VibraFactory::NewL(this);
	else
		iVibra = VibraFactory::NewL();	

}

// -----------------------------------------------------------------------------
// CVibrawrapper::VibraModeStatus
// Notifies if VibraModeStatus has been changed.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
void CVibrawrapper::VibraModeStatus(CVibraControl::TVibraModeState aStatus)
{
	RDebug::Print(_L("CVibraWrapper - VibraModeStatus indication: %d"), aStatus);
	iVibraModeState = aStatus;
	CActiveScheduler::Stop();	
}

// -----------------------------------------------------------------------------
// CVibrawrapper::VibraRequestStatus
// Notifies what is the status of VibraRequest.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
void CVibrawrapper::VibraRequestStatus(CVibraControl::TVibraRequestStatus aStatus)
{
	RDebug::Print(_L("CVibraWrapper - VibraRequestStatus: %d"), aStatus);
	iStatusReceived = true;
	iStatus = aStatus;
}

// Destructor
CVibrawrapper::~CVibrawrapper() 
{
	delete myTestScheduler;
	delete iVibra;
    iVibra = NULL;

}
// -----------------------------------------------------------------------------
// Cvibractrltest::Case
// Returns a test case by number.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
// 
const TCaseInfo Cvibractrltest::Case ( 
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
			{(TText*) L"[Vibractrl] Vibra Status Request",										GETPTR CheckRequestStatus},
			{(TText*) L"[Vibractrl] Vibra No Status Request",									GETPTR CheckRequestStatusWithNoNotif},
			{(TText*) L"[Vibractrl] Vibra Duration 0s",											GETPTR StartVibraIndef},
			{(TText*) L"[Vibractrl] Vibra Duration 0s, Intensity 70",							GETPTR StartVibraIndefI},
			{(TText*) L"[Vibractrl] Vibra Duration 5s",											GETPTR StartVibra5s},
			{(TText*) L"[Vibractrl] Vibra Duration 5s, Intensity 70",							GETPTR StartVibra5sI},
			{(TText*) L"[Vibractrl] Vibra Duration 5s, Intensity -70",							GETPTR StartVibra5sNI},
			{(TText*) L"[Vibractrl] Vibra Duration 5s, Intensity 110",							GETPTR StartVibra5sOI},
			{(TText*) L"[Vibractrl] Vibra Duration 5s, Intensity -110",							GETPTR StartVibra5sNOI},	
			{(TText*) L"[Vibractrl] Vibra Duration 5s, Intensity 0",								GETPTR StartVibra5sZI},						
			{(TText*) L"[Vibractrl] Vibra Stop After 2s Without Intensity",						GETPTR StopVibra},
			{(TText*) L"[Vibractrl] Vibra Stop After 2s With Intensity",							GETPTR StopVibraI},
			{(TText*) L"[Vibractrl] Restart Vibra With Duration",								GETPTR ReStartVibra},
			{(TText*) L"[Vibractrl] Restart Vibra With Duration And Intensity",					GETPTR ReStartVibraI},		
			{(TText*) L"[Vibractrl] Restart Vibra With Intensity",								GETPTR ReStartVibraIonL},
			{(TText*) L"[Vibractrl] Restart Vibra With No Intensity",							GETPTR ReStartVibraIonF},
			{(TText*) L"[Vibractrl] Restop Vibra",												GETPTR ReStopVibra},
			{(TText*) L"[Vibractrl] Restop Vibra, Parallel",										GETPTR ReStopVibra2},
			{(TText*) L"[Vibractrl] Vibra Setting On",											GETPTR VibraSettingOn},
			{(TText*) L"[Vibractrl] Vibra Setting Off",											GETPTR VibraSettingOff}			
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
// Cvibractrltest::CheckRequestStatus
// Starts and stops vibra and checks that request statuses are notified.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cvibractrltest::CheckRequestStatus( 
		TTestResult& aResult) // Test case result
{
	TBool retVal1;
	TBool retVal2;
	TInt error;
	
	iLogger->Log(_L("VibraCtrlTest::CheckRequestStatus"));

	CVibrawrapper* wrapper; 
	TRAPD(err, wrapper = CVibrawrapper::NewL(true));	
	if(err != KErrNone)
	{
		aResult.iResult = err;
		return err;
	}

	wrapper->iStatusReceived = false;

	aResult.iResultDes.Append( _L("Start vibra request:") );
	TRAP(error, wrapper->iVibra->StartVibraL(30000));

	if (KErrNone != error)
		{

		iLogger->Log(_L("StartVibraL() TRAP error."));		
		aResult.iResultDes.Copy( _L("Starting vibra failed.") );
		aResult.iResult = error;

		}
	else
		{

		iLogger->Log(_L("StartVibraL(30000)"));
		CheckRequest(wrapper->iStatus, aResult);
		retVal1 = wrapper->iStatusReceived;
		wrapper->iStatusReceived = false;
		aResult.iResultDes.Append( _L("Stop vibra request") );
		TRAP(error, wrapper->iVibra->StopVibraL());

		if (KErrNone != error) 	
			{
			iLogger->Log(_L("StopVibraL() TRAP error."));
			aResult.iResultDes.Copy( _L("Stopping vibra failed.") );
			}
		else
			{
			
			iLogger->Log(_L("StopVibraL() status: "));
			CheckRequest(wrapper->iStatus, aResult);
			retVal2 = wrapper->iStatusReceived;

				if(retVal1 && retVal2)
					{
					aResult.iResult = KErrNone;
					iLogger->Log(_L("CheckRequestStatus PASS"));
					}
				else
					{
					aResult.iResult = KErrGeneral;
					iLogger->Log(_L("CheckRequestStatus FAIL"));
					aResult.iResultDes.Copy( _L("Vibra status not received.") );
					}			
			}
		}

	delete wrapper;

	return KErrNone;
}

// -----------------------------------------------------------------------------
// Cvibractrltest::CheckRequestStatusWithNoNotif
// Creates vibra with no notif and checks that request statuses are not notified.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cvibractrltest::CheckRequestStatusWithNoNotif( 
		TTestResult& aResult ) // Test case result
{
	TBool retVal1;
	TBool retVal2;

	TInt error;

	iLogger->Log(_L("VibraCtrlTest::CheckRequestStatusWithNoNotif"));

	CVibrawrapper* wrapper;
	TRAPD(err, wrapper = CVibrawrapper::NewL(false));	
	if(err != KErrNone)
	{
		aResult.iResult = err;
		return err;
	}


	wrapper->iStatusReceived = false;

	TRAP(error, wrapper->iVibra->StartVibraL(30000));
	
	if (KErrNone != error) 	
		{
		aResult.iResult = error;
		iLogger->Log(_L("StartVibraL() TRAP error."));
		aResult.iResultDes.Copy( _L("Starting vibra failed.") );
		}
	else
		{

		retVal1 = wrapper->iStatusReceived;
		
		wrapper->iStatusReceived = false;

		TRAP(error, wrapper->iVibra->StopVibraL());

		if (KErrNone != error) 	
			{
			iLogger->Log(_L("StopVibraL() TRAP error. "));
			aResult.iResultDes.Copy( _L("Stopping vibra failed.") );
			aResult.iResult = error;
			}
		else
			{
				retVal2 = wrapper->iStatusReceived;
	
				if(!retVal1 && !retVal2)
					{
					aResult.iResult = KErrNone;
					iLogger->Log(_L("CheckRequestStatusWithNoNotif PASS"));					
					}
				else
					{
					aResult.iResult = KErrGeneral;					
					iLogger->Log(_L("statusReceived after stopVibra: %d"), error);
					aResult.iResultDes.Copy( _L("Notification received!.") );
					}
			}

		}

	delete wrapper;

	return KErrNone;
}
    


// -----------------------------------------------------------------------------
// Cvibractrltest::StartVibraIndef
// Runs vibra indefinitely w/o intensity, but it should stop after a specific
// time period specified in shareddata/cenrep.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cvibractrltest::StartVibraIndef( 
		TTestResult& aResult ) // Test case result
{
     
	TInt retVal1;
	TInt retVal2;
	TInt retVal3;
	
	iLogger->Log(_L("VibraCtrlTest::StartVibraIndef"));

	CVibrawrapper* wrapper;
	TRAPD(err, wrapper = CVibrawrapper::NewL(true));	
	if(err != KErrNone)
	{
		aResult.iResult = err;
		return err;
	}

	// trap StartVibraL and use possible return value to log.
	TRAP(retVal1, wrapper->iVibra->StartVibraL(0));

	if (KErrNone != retVal1) 
		{
		aResult.iResult = retVal1;					
		iLogger->Log(_L("StartVibraIndef - StartVibraL() TRAP error."));
		aResult.iResultDes.Copy( _L("Starting vibra failed!.") );
		}
	else
		{
		// check that vibra has started
		retVal2 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestOK);

		// delay for waiting vibra to stop
		TRAP(err, CTestScheduler::StartAndStopL(20000));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

		// check that vibra has stopped
		retVal3 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestStopped);

		// check return values for passing or failing test case
		if(KErrNone == retVal1 && KErrNone == retVal2 && KErrNone == retVal3)
			{
			aResult.iResult = KErrNone;
			iLogger->Log(_L("StartVibraIndef PASS"));			
			}
		else
			{
			aResult.iResult = KErrGeneral;
			iLogger->Log(_L("StartVibraIndef FAIL"));
			// error reason summary
			aResult.iResultDes.AppendFormat( _L("StartVibraIndef - check that vibra has stopped: status: %d"), wrapper->iStatus );
			}	
		}

	delete wrapper;

	return KErrNone;    
}


// -----------------------------------------------------------------------------
// Cvibractrltest::StartVibraIndefI
// Runs vibra indefinitely w/ intensity 60, but it should stop after a specific
// time period specified in shareddata/cenrep.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cvibractrltest::StartVibraIndefI( 
		TTestResult& aResult ) // Test case result
{
     
	TInt retVal1;
	TInt retVal2;
	TInt retVal3;

	iLogger->Log(_L("VibraCtrlTest::StartVibraIndefI"));

	CVibrawrapper* wrapper;
	TRAPD(err, wrapper = CVibrawrapper::NewL(true));	
	if(err != KErrNone)
	{
		aResult.iResult = err;
		return err;
	}

	// trap StartVibraL and use possible return value to log.
	TRAP(retVal1, wrapper->iVibra->StartVibraL(0,60));
	if (KErrNone != retVal1) 
		{	
		iLogger->Log(_L("StartVibraIndefI - StartVibraL() TRAP error."));
		aResult.iResult = retVal1;
		aResult.iResultDes.Copy( _L("Starting vibra failed!.") );
		}
	else
		{

		// check that vibra has started
		retVal2 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestOK);

		// delay for waiting vibra to stop
		TRAP(err, CTestScheduler::StartAndStopL(20000));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

		// check that vibra has stopped
		retVal3 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestStopped);

			// check return values for passing or failing test case
			if(KErrNone == retVal1 && KErrNone == retVal2 && KErrNone == retVal3)
				{
				aResult.iResult = KErrNone;
				iLogger->Log(_L("StartVibraIndefI PASS"));				
				}
			else
				{
				aResult.iResult = KErrGeneral;
				iLogger->Log(_L("StartVibraIndefI FAIL"));				
				aResult.iResultDes.AppendFormat( _L("StartVibraIndef - check that vibra has stopped: status: %d"), wrapper->iStatus );
				}		
		}
	
	delete wrapper;

	return KErrNone;    
}
// -----------------------------------------------------------------------------
// Cvibractrltest::StartVibra5s
// Runs vibra for 5 seconds and checks it has ended
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cvibractrltest::StartVibra5s( 
		TTestResult& aResult ) // Test case result
{
     
	TInt retVal1;
	TInt retVal2;
	TInt retVal3;

	iLogger->Log(_L("VibraCtrlTest::StartVibra5s")); RDebug::Print(_L("VibraCtrlTest::StartVibra5s"));

	CVibrawrapper* wrapper;
	TRAPD(err, wrapper = CVibrawrapper::NewL(true));	
	if(err != KErrNone)
	{
		aResult.iResult = err;
		return err;
	}

	// trap StartVibraL and use possible return value to log.
	TRAP(retVal1, wrapper->iVibra->StartVibraL(5000));

	if (KErrNone != retVal1) 
		{
		aResult.iResult = retVal1;
		iLogger->Log(_L("StartVibra5s - StartVibraL() TRAP error."));
		aResult.iResultDes.Copy( _L("Starting vibra failed!.") );
		}
	else
		{
		// check that vibra has started
		retVal2 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestOK);
		// delay for waiting vibra to stop
		TRAP(err, CTestScheduler::StartAndStopL(6000));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}
		// check that vibra has stopped
		retVal3 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestStopped);

		// check return values for passing or failing test case
		if(KErrNone == retVal1 && KErrNone == retVal2 && KErrNone == retVal3)
			{
			aResult.iResult = KErrNone;
			iLogger->Log(_L("StartVibra5s PASS"));
			}
		else
			{
			aResult.iResult = KErrGeneral;
			iLogger->Log(_L("StartVibra5s FAIL"));
			// error reason summary
			aResult.iResultDes.AppendFormat( _L("StartVibra5s - StartVibraL: %d, after 6s delay: %d"), retVal2, retVal3 );
			}	
		}

	delete wrapper;

	return KErrNone;    
}

// -----------------------------------------------------------------------------
// Cvibractrltest::StartVibra5sI
// Runs vibra for 5 seconds with intensity 70 and checks it has ended
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cvibractrltest::StartVibra5sI( 
		TTestResult& aResult ) // Test case result
{
     
	TInt retVal1;
	TInt retVal2;
	TInt retVal3;

	iLogger->Log(_L("VibraCtrlTest::StartVibra5sI")); RDebug::Print(_L("VibraCtrlTest::StartVibra5sI"));

	CVibrawrapper* wrapper;
	TRAPD(err, wrapper = CVibrawrapper::NewL(true));	
	if(err != KErrNone)
	{
		aResult.iResult = err;
		return err;
	}

	// trap StartVibraL and use possible return value to log.
	TRAP(retVal1, wrapper->iVibra->StartVibraL(5000,70));
	if (KErrNone != retVal1) 
		{
		aResult.iResult = retVal1;
		iLogger->Log(_L("StartVibra5sI - StartVibraL() TRAP error."));
		aResult.iResultDes.Copy( _L("Starting vibra failed!.") );
		}
	else
		{

		// check that vibra has started
		retVal2 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestOK);

		// delay for waiting vibra to stop
		TRAP(err, CTestScheduler::StartAndStopL(6000));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

		// check that vibra has stopped
		retVal3 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestStopped);

			// check return values for passing or failing test case
			if(KErrNone == retVal1 && KErrNone == retVal2 && KErrNone == retVal3)
				{
				aResult.iResult = KErrNone;
				iLogger->Log(_L("StartVibra5sI PASS"));
				}
			else
				{
				aResult.iResult = KErrGeneral;
				iLogger->Log(_L("StartVibra5sI FAIL"));
				// error reason summary
				aResult.iResultDes.AppendFormat( _L("StartVibra5sI - StartVibraL: %d, after 6s delay: %d"), retVal2, retVal3 );
				}		
		}
	
	delete wrapper;

	return KErrNone;    
}


// -----------------------------------------------------------------------------
// Cvibractrltest::StartVibra5sNI
// Runs vibra for 5 seconds with intensity -70 and checks it has ended
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cvibractrltest::StartVibra5sNI( 
		TTestResult& aResult ) // Test case result
{
     
	TInt retVal1;
	TInt retVal2;
	TInt retVal3;

	iLogger->Log(_L("VibraCtrlTest::StartVibra5sNI")); RDebug::Print(_L("VibraCtrlTest::StartVibra5sNI"));

	CVibrawrapper* wrapper;
	TRAPD(err, wrapper = CVibrawrapper::NewL(true));	
	if(err != KErrNone)
	{
		aResult.iResult = err;
		return err;
	}

	// trap StartVibraL and use possible return value to log.
	TRAP(retVal1, wrapper->iVibra->StartVibraL(5000,-70));
	if (KErrNone != retVal1) 
		{
		aResult.iResult = retVal1;
		iLogger->Log(_L("StartVibra5sNI - StartVibraL() TRAP error."));
		aResult.iResultDes.Copy( _L("Starting vibra failed!.") );
		}
	else
		{

		// check that vibra has started
		retVal2 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestOK);

		// delay for waiting vibra to stop
		TRAP(err, CTestScheduler::StartAndStopL(6000));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

		// check that vibra has stopped
		retVal3 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestStopped);

			// check return values for passing or failing test case
			if(KErrNone == retVal1 && KErrNone == retVal2 && KErrNone == retVal3)
				{
				aResult.iResult = KErrNone;
				iLogger->Log(_L("StartVibra5sNI PASS"));
				}
			else
				{
				aResult.iResult = KErrGeneral;
				iLogger->Log(_L("StartVibra5sNI FAIL"));
				// error reason summary
				aResult.iResultDes.AppendFormat( _L("StartVibra5sNI - StartVibraL: %d, after 6s delay: %d"), retVal2, retVal3 );
				}
		}
		
	delete wrapper;

	return KErrNone;    
}


// -----------------------------------------------------------------------------
// Cvibractrltest::StartVibra5sOI
// Runs vibra for 5 seconds with intensity 110 and checks it has ended
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cvibractrltest::StartVibra5sOI( 
		TTestResult& aResult ) // Test case result
{
     
	TInt retVal1;
	TInt retVal2;
	TInt retVal3;

	iLogger->Log(_L("VibraCtrlTest::StartVibra5sOI")); RDebug::Print(_L("VibraCtrlTest::StartVibra5sOI"));

	CVibrawrapper* wrapper;
	TRAPD(err, wrapper = CVibrawrapper::NewL(true));	
	if(err != KErrNone)
	{
		aResult.iResult = err;
		return err;
	}

	// trap StartVibraL and use possible return value to log.
	TRAP(retVal1, wrapper->iVibra->StartVibraL(5000,110));
	// test case checks that StartVibraL returns KErrArgument with illegal intensity
	if (KErrArgument != retVal1) 
		{
		aResult.iResult = retVal1;
		iLogger->Log(_L("StartVibra5sOI - StartVibraL() unexpected TRAP result."));
		aResult.iResultDes.Copy( _L("Unexpected return value received.") );
		}
	else
		{

		// check that vibra is stopped
		retVal2 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestFail);

		// Delay for next step
		TRAP(err, CTestScheduler::StartAndStopL(6000));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

		// check that vibra has stopped
		retVal3 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestFail);

		// check return values for passing or failing test case
			if(KErrArgument == retVal1 && KErrNone == retVal2 && KErrNone == retVal3)
				{
				aResult.iResult = KErrNone;
				iLogger->Log(_L("StartVibra5sOI PASS"));
				}
			else
				{
				aResult.iResult = KErrGeneral;
				iLogger->Log(_L("StartVibra5sOI FAIL"));
				// error reason summary
				aResult.iResultDes.AppendFormat( _L("StartVibra5sOI - StartVibraL: %d, after 6s delay: %d"), retVal2, retVal3 );
				}
		}
		
	delete wrapper;

	return KErrNone;    
}

// -----------------------------------------------------------------------------
// Cvibractrltest::StartVibra5sNOI
// Runs vibra for 5 seconds with intensity -110 and checks it has ended
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cvibractrltest::StartVibra5sNOI( 
		TTestResult& aResult ) // Test case result
{
     
	TInt retVal1;
	TInt retVal2;
	TInt retVal3;

	iLogger->Log(_L("VibraCtrlTest::StartVibra5sNOI")); RDebug::Print(_L("VibraCtrlTest::StartVibra5sNOI"));

	CVibrawrapper* wrapper;
	TRAPD(err, wrapper = CVibrawrapper::NewL(true));	
	if(err != KErrNone)
	{
		aResult.iResult = err;
		return err;
	}

	// trap StartVibraL and use possible return value to log.
	TRAP(retVal1, wrapper->iVibra->StartVibraL(5000,-110));
	// test case checks that StartVibraL returns KErrArgument with illegal intensity
	if (KErrArgument != retVal1) 
		{
		aResult.iResult = retVal1;
		iLogger->Log(_L("StartVibra5sNOI - StartVibraL() unexpected TRAP result."));
		aResult.iResultDes.Copy( _L("Unexpected return value received.") );
		}
	else
		{

		// checks that vibra is stopped
		retVal2 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestFail);

		// Delay for next step
		TRAP(err, CTestScheduler::StartAndStopL(6000));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

		// check that vibra has stopped
		retVal3 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestFail);

			// check return values for passing or failing test case
			if(KErrArgument == retVal1 && KErrNone == retVal2 && KErrNone == retVal3)
				{
				aResult.iResult = KErrNone;
				iLogger->Log(_L("StartVibra5sNOI PASS"));
				}
			else
				{
				aResult.iResult = KErrGeneral;
				iLogger->Log(_L("StartVibra5sNOI FAIL"));
				// error reason summary
				aResult.iResultDes.AppendFormat( _L("StartVibra5sNOI - StartVibraL: %d, after 6s delay: %d"), retVal2, retVal3 );
				}
		}

	delete wrapper;

	return KErrNone;    
}


// -----------------------------------------------------------------------------
// Cvibractrltest::StartVibra5sZI
// Runs vibra for 5 seconds with intensity 0 and checks it has ended
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cvibractrltest::StartVibra5sZI( 
		TTestResult& aResult ) // Test case result
{
     
	TInt retVal1;
	TInt retVal2;
	TInt retVal3;

	iLogger->Log(_L("VibraCtrlTest::StartVibra5sZI"));  RDebug::Print(_L("VibraCtrlTest::StartVibra5sZI"));

	CVibrawrapper* wrapper;
	TRAPD(err, wrapper = CVibrawrapper::NewL(true));	
	if(err != KErrNone)
	{
		aResult.iResult = err;
		return err;
	}

	// trap StartVibraL and use possible return value to log.
	TRAP(retVal1, wrapper->iVibra->StartVibraL(5000,0));
	if (KErrNone != retVal1) 
		{
		aResult.iResult = retVal1;
		iLogger->Log(_L("StartVibra5sZI - StartVibraL() unexpected TRAP result."));
		aResult.iResultDes.Copy( _L("Starting vibra failed.") );
		}
	else
		{

		// check that vibra is not started
		retVal2 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestStopped);

		// Delay for next step
		TRAP(err, CTestScheduler::StartAndStopL(6000));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

		// check that vibra has stopped
		retVal3 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestStopped);

			// check return values for passing or failing test case
			if(KErrNone == retVal1 && KErrNone == retVal2 && KErrNone == retVal3)
				{
				aResult.iResult = KErrNone;
				iLogger->Log(_L("StartVibra5sZI PASS"));
				}
			else
				{
				aResult.iResult = KErrGeneral;
				iLogger->Log(_L("StartVibra5sZI FAIL"));
				// error reason summary
				aResult.iResultDes.AppendFormat( _L("StartVibra5sZI - StartVibraL: %d, after 6s delay: %d"), retVal2, retVal3 );
				}
		
		}
		
	delete wrapper;

	return KErrNone;    
}


// -----------------------------------------------------------------------------
// Cvibractrltest::StopVibra
// Runs vibra for 5 seconds, stops vibra after 2s and checks it has ended
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cvibractrltest::StopVibra( 
		TTestResult& aResult ) // Test case result
{
     
	TInt retVal1;
	TInt retVal2;
	TInt retVal3;
	TInt retVal4;

	iLogger->Log(_L("VibraCtrlTest::StopVibra")); RDebug::Print(_L("VibraCtrlTest::StopVibra"));

	CVibrawrapper* wrapper;
	TRAPD(err, wrapper = CVibrawrapper::NewL(true));	
	if(err != KErrNone)
	{
		aResult.iResult = err;
		return err;
	}

	// trap StartVibraL and use possible return value to log.
	TRAP(retVal1, wrapper->iVibra->StartVibraL(5000));

	if (KErrNone != retVal1) 
		{
		aResult.iResult = retVal1;
		iLogger->Log(_L("StopVibra - StartVibraL() unexpected TRAP result."));
		aResult.iResultDes.Copy( _L("Starting vibra failed.") );
		}
	else
		{

		// check that vibra has started
		retVal2 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestOK);

		// Delay for next step
		TRAP(err, CTestScheduler::StartAndStopL(2000));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

		// trap StopVibraL and use possible return value to log.
		TRAP(retVal3, wrapper->iVibra->StopVibraL());

			if (KErrNone != retVal3) 
				{
				aResult.iResult = retVal3;
				iLogger->Log(_L("StopVibra - StopVibraL() unexpected TRAP result."));
				aResult.iResultDes.Copy( _L("Stopping vibra failed.") );
				}
			else
				{

				// check that vibra has stopped
				retVal4 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestStopped);

				// check return values for passing or failing test case
				if(KErrNone == retVal1 && KErrNone == retVal2 && KErrNone == retVal3 && KErrNone == retVal4)
					{
					aResult.iResult = KErrNone;
					iLogger->Log(_L("StopVibra PASS"));
					}
				else
					{
					aResult.iResult = KErrGeneral;
					iLogger->Log(_L("StopVibra FAIL"));
					// error reason summary
					aResult.iResultDes.AppendFormat( _L("StopVibra - StartVibraL: %d, after StopVibraL: %d"), retVal2, retVal4 );
					}
				}
		}
		
	delete wrapper;

	return KErrNone;    
}


// -----------------------------------------------------------------------------
// Cvibractrltest::StopVibraI
// Runs vibra for 5 seconds with intensity 70, stops vibra after 2s and checks it has ended
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cvibractrltest::StopVibraI( 
		TTestResult& aResult ) // Test case result
{
     
	TInt retVal1;
	TInt retVal2;
	TInt retVal3;
	TInt retVal4;

	iLogger->Log(_L("VibraCtrlTest::StopVibraI")); RDebug::Print(_L("VibraCtrlTest::StopVibraI"));

	CVibrawrapper* wrapper;
	TRAPD(err, wrapper = CVibrawrapper::NewL(true));	
	if(err != KErrNone)
	{
		aResult.iResult = err;
		return err;
	}

	// trap StartVibraL and use possible return value to log.
	TRAP(retVal1, wrapper->iVibra->StartVibraL(5000,70));
	if (KErrNone != retVal1) 
		{	
		aResult.iResult = retVal1;
		iLogger->Log(_L("StopVibraI - StartVibraL() unexpected TRAP result."));
		aResult.iResultDes.Copy( _L("Starting vibra failed.") );
		}
	else
		{

		// check that vibra has started
		retVal2 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestOK);

		// Delay for next step
		TRAP(err, CTestScheduler::StartAndStopL(2000));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

		// trap StopVibraL and use possible return value to log.
		TRAP(retVal3, wrapper->iVibra->StopVibraL());

		if (KErrNone != retVal3) 
			{
			aResult.iResult = retVal3;
			iLogger->Log(_L("StopVibraI - StopVibraL() unexpected TRAP result."));
			aResult.iResultDes.Copy( _L("Stopping vibra failed.") );
			}
		else
			{
				// check that vibra has stopped
				retVal4 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestStopped);

				// check return values for passing or failing test case
				if(KErrNone == retVal1 && KErrNone == retVal2 && KErrNone == retVal3 && KErrNone == retVal4)
					{
					aResult.iResult = KErrNone;
					iLogger->Log(_L("StopVibraI PASS"));
					}
				else
					{
					aResult.iResult = KErrGeneral;
					iLogger->Log(_L("StopVibraI FAIL"));
					// error reason summary
					aResult.iResultDes.AppendFormat( _L("StopVibraI - StartVibraL: %d, after StopVibraL: %d"), retVal2, retVal4 );
					}
			}
		}
	
	
	delete wrapper;

	return KErrNone;    
}


// -----------------------------------------------------------------------------
// Cvibractrltest::ReStartVibra
// Runs vibra for 10 seconds, restarts vibra after 1s to run for 1s and checks it has ended after that 1 second.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cvibractrltest::ReStartVibra( 
		TTestResult& aResult ) // Test case result
{
     
	TInt retVal1, retVal2, retVal3, retVal4, retVal5;

	iLogger->Log(_L("VibraCtrlTest::ReStartVibra")); RDebug::Print(_L("VibraCtrlTest::ReStartVibra"));

//	CVibrawrapper* wrapper = CVibrawrapper::NewL(true);	
	CVibrawrapper* wrapper;
	TRAPD(err, wrapper = CVibrawrapper::NewL(true));	
	if(err != KErrNone)
	{
		aResult.iResult = err;
		return err;
	}

	// trap StartVibraL and use possible return value to log.
	TRAP(retVal1, wrapper->iVibra->StartVibraL(10000));
	if (KErrNone != retVal1) 
		{
		aResult.iResult = retVal1;
		iLogger->Log(_L("ReStartVibra - StartVibraL() unexpected TRAP result."));
		aResult.iResultDes.Copy( _L("Starting vibra failed.") );
		}
	else
		{

		// check that vibra has started
		retVal2 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestOK);

		// Delay for next step
		TRAP(err, CTestScheduler::StartAndStopL(1000));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

		// trap StartVibraL and use possible return value to log.
		TRAP(retVal3, wrapper->iVibra->StartVibraL(1000));
		if (KErrNone != retVal3) 
			{
			aResult.iResult = retVal3;
			iLogger->Log(_L("ReStartVibra - StartVibraL() unexpected TRAP result."));
			aResult.iResultDes.Copy( _L("Starting vibra failed.") );
			}
		else
			{

			// check that vibra is still running
			retVal4 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestOK);

			// delay for waiting vibra to stop
				TRAP(err, CTestScheduler::StartAndStopL(2000));
				if(err != KErrNone)
				{
					aResult.iResult = err;
					return err;
				}

			// check that vibra has stopped
			retVal5 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestStopped);

			// check return values for passing or failing test case
			if(KErrNone == retVal1 && KErrNone == retVal2 && KErrNone == retVal3 && KErrNone == retVal4 && KErrNone == retVal5)
				{
				aResult.iResult = KErrNone;
				iLogger->Log(_L("ReStartVibra PASS"));
				}
			else
				{
				aResult.iResult = KErrGeneral;
				iLogger->Log(_L("ReStartVibra FAIL"));
				// error reason summary
				aResult.iResultDes.AppendFormat( _L("ReStartVibra - StartVibraL: %d, after ReStart: %d, and after stopped: %d"), retVal2, retVal4, retVal5 );
				}
			}
		
		}
		
	delete wrapper;

	return KErrNone;    
}


// -----------------------------------------------------------------------------
// Cvibractrltest::ReStartVibraI
// Runs vibra for 10 seconds w/ intensity 70, restarts vibra after 1s to run for
// 1s w/ intensity -70 and checks it has ended after that 1 second.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cvibractrltest::ReStartVibraI( 
		TTestResult& aResult ) // Test case result
{
     
	TInt retVal1, retVal2, retVal3, retVal4, retVal5;

	iLogger->Log(_L("VibraCtrlTest::ReStartVibraI")); RDebug::Print(_L("VibraCtrlTest::ReStartVibraI"));

//	CVibrawrapper* wrapper = CVibrawrapper::NewL(true);	
	CVibrawrapper* wrapper;
	TRAPD(err, wrapper = CVibrawrapper::NewL(true));	
	if(err != KErrNone)
	{
		aResult.iResult = err;
		return err;
	}

	// trap StartVibraL and use possible return value to log.
	TRAP(retVal1, wrapper->iVibra->StartVibraL(10000,70));
	if (KErrNone != retVal1) 
		{
		aResult.iResult = retVal1;
		iLogger->Log(_L("ReStartVibraI - StartVibraL() unexpected TRAP result."));
		aResult.iResultDes.Copy( _L("Starting vibra failed.") );
		}
	else
		{

		// check that vibra has started
		retVal2 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestOK);

		// Delay for next step
		TRAP(err, CTestScheduler::StartAndStopL(1000));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

		// trap StartVibraL and use possible return value to log.
		TRAP(retVal3, wrapper->iVibra->StartVibraL(1000,-30));
		
		if (KErrNone != retVal3) 
			{
			aResult.iResult = retVal3;
			iLogger->Log(_L("ReStartVibraI - StartVibraL() unexpected TRAP result."));
			aResult.iResultDes.Copy( _L("Starting vibra failed.") );
			}
		else
			{

				// check that vibra is still running
				retVal4 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestOK);

				// delay for waiting vibra to stop
				TRAP(err, CTestScheduler::StartAndStopL(2000));
				if(err != KErrNone)
				{
					aResult.iResult = err;
					return err;
				}

				// check that vibra has stopped
				retVal5 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestStopped);


				// check return values for passing or failing test case
				if(KErrNone == retVal1 && KErrNone == retVal2 && KErrNone == retVal3 && KErrNone == retVal4 && KErrNone == retVal5)
					{
					aResult.iResult = KErrNone;
					iLogger->Log(_L("ReStartVibraI PASS"));
					}
				else
					{
					aResult.iResult = KErrGeneral;
					iLogger->Log(_L("ReStartVibraI FAIL"));
					// error reason summary
					aResult.iResultDes.AppendFormat( _L("ReStartVibraI - StartVibraL: %d, after ReStart: %d, and after stopped: %d"), retVal2, retVal4, retVal5 );
					}
			}	

		}
		
	delete wrapper;

	return KErrNone;    
}


// -----------------------------------------------------------------------------
// Cvibractrltest::ReStartVibraIonL
// Runs vibra for 10 seconds, restarts vibra after 1s to run for
// 1s w/ intensity -40 and checks it has ended after that 1 second.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cvibractrltest::ReStartVibraIonL( 
		TTestResult& aResult ) // Test case result
{
     
	TInt retVal1, retVal2, retVal3, retVal4, retVal5;

	iLogger->Log(_L("VibraCtrlTest::ReStartVibraIonL")); RDebug::Print(_L("VibraCtrlTest::ReStartVibraIonL"));

//	CVibrawrapper* wrapper = CVibrawrapper::NewL(true);	
	CVibrawrapper* wrapper;
	TRAPD(err, wrapper = CVibrawrapper::NewL(true));	
	if(err != KErrNone)
	{
		aResult.iResult = err;
		return err;
	}

	// trap StartVibraL and use possible return value to log.
	TRAP(retVal1, wrapper->iVibra->StartVibraL(10000));
	if (KErrNone != retVal1) 
		{
		aResult.iResult = retVal1;
		iLogger->Log(_L("ReStartVibraIonL - StartVibraL() unexpected TRAP result."));
		aResult.iResultDes.Copy( _L("Starting vibra failed.") );
		}
	else
		{

		// check that vibra has started
		retVal2 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestOK);

		// Delay for next step
		TRAP(err, CTestScheduler::StartAndStopL(1000));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

		// trap StartVibraL and use possible return value to log.
		TRAP(retVal3, wrapper->iVibra->StartVibraL(1000,-40));

		if (KErrNone != retVal3) 
			{
			aResult.iResult = retVal3;
			iLogger->Log(_L("ReStartVibraIonL - StartVibraL() unexpected TRAP result."));
			aResult.iResultDes.Copy( _L("Starting vibra failed.") );
			}
		else
			{

			// check that vibra is still running
			retVal4 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestOK);

			// delay for waiting vibra to stop
				TRAP(err, CTestScheduler::StartAndStopL(2000));
				if(err != KErrNone)
				{
					aResult.iResult = err;
					return err;
				}

			// check that vibra has stopped
			retVal5 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestStopped);


			// check return values for passing or failing test case
			if(KErrNone == retVal1 && KErrNone == retVal2 && KErrNone == retVal3 && KErrNone == retVal4 && KErrNone == retVal5)
				{
				aResult.iResult = KErrNone;
				iLogger->Log(_L("ReStartVibraIonL PASS"));
				}
			else
				{
				aResult.iResult = KErrGeneral;
				iLogger->Log(_L("ReStartVibraIonL FAIL"));
				// error reason summary
				aResult.iResultDes.AppendFormat( _L("ReStartVibraIonL - StartVibraL: %d, after ReStart: %d, and after stopped: %d"), retVal2, retVal4, retVal5 );
				}	
			}
		}
		
	delete wrapper;

	return KErrNone;    
}


// -----------------------------------------------------------------------------
// Cvibractrltest::ReStartVibraIonF
// Runs vibra for 10 seconds w/ intensity 70, restarts vibra after 1s to run for
// 1s w/o intensity and checks it has ended after that 1 second.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cvibractrltest::ReStartVibraIonF( 
		TTestResult& aResult ) // Test case result
{
     
	TInt retVal1, retVal2, retVal3, retVal4, retVal5;

	iLogger->Log(_L("VibraCtrlTest::ReStartVibraIonF")); RDebug::Print(_L("VibraCtrlTest::ReStartVibraIonF"));

	CVibrawrapper* wrapper;
	TRAPD(err, wrapper = CVibrawrapper::NewL(true));	
	if(err != KErrNone)
	{
		aResult.iResult = err;
		return err;
	}

	// trap StartVibraL and use possible return value to log.
	TRAP(retVal1, wrapper->iVibra->StartVibraL(10000,70));

	if (KErrNone != retVal1) 
		{
		aResult.iResult = retVal1;
		iLogger->Log(_L("ReStartVibraIonF - StartVibraL() unexpected TRAP result."));
		aResult.iResultDes.Copy( _L("Starting vibra failed.") );
		}
	else
		{

		// check that vibra has started
		retVal2 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestOK);

		// Delay for next step
		TRAP(err, CTestScheduler::StartAndStopL(1000));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

		// trap StartVibraL and use possible return value to log.
		TRAP(retVal3, wrapper->iVibra->StartVibraL(1000));

		if (KErrNone != retVal3) 
			{
			aResult.iResult = retVal3;
			iLogger->Log(_L("ReStartVibraIonF - StartVibraL() unexpected TRAP result."));
			aResult.iResultDes.Copy( _L("Starting vibra failed.") );
			}
		else
			{
			// check that vibra is still running
			retVal4 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestOK);

			// delay for waiting vibra to stop
			TRAP(err, CTestScheduler::StartAndStopL(2000));
			if(err != KErrNone)
			{
				aResult.iResult = err;
				return err;
			}

			// check that vibra has stopped
			retVal5 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestStopped);


			// check return values for passing or failing test case
			if(KErrNone == retVal1 && KErrNone == retVal2 && KErrNone == retVal3 && KErrNone == retVal4 && KErrNone == retVal5)
				{
				aResult.iResult = KErrNone;
				iLogger->Log(_L("ReStartVibraIonF PASS"));
				}
			else
				{
				aResult.iResult = KErrGeneral;
				iLogger->Log(_L("ReStartVibraIonF FAIL"));
				// error reason summary
				aResult.iResultDes.AppendFormat( _L("ReStartVibraIonF - StartVibraL: %d, after ReStart: %d, and after stopped: %d"), retVal2, retVal4, retVal5 );
				}		
			}
		}
	
	delete wrapper;

	return KErrNone;    
}


// -----------------------------------------------------------------------------
// Cvibractrltest::ReStopVibra
// Just runs StopVibraL twice to see that nothing crashes
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cvibractrltest::ReStopVibra( 
		TTestResult& aResult ) // Test case result
{
     
	TInt retVal1, retVal2, retVal3;

	iLogger->Log(_L("VibraCtrlTest::ReStopVibra")); RDebug::Print(_L("VibraCtrlTest::ReStopVibra"));

//	CVibrawrapper* wrapper = CVibrawrapper::NewL(true);	
	CVibrawrapper* wrapper;
	TRAPD(err, wrapper = CVibrawrapper::NewL(true));	
	if(err != KErrNone)
	{
		aResult.iResult = err;
		return err;
	}

	RDebug::Print(_L("VibraCtrlTest::ReStopVibra - Stopping first time..."));
	
	// trap StopVibraL and use possible return value to log.
	TRAP(retVal1, wrapper->iVibra->StopVibraL());

	if (KErrNone != retVal1) 
		{
		aResult.iResult = retVal1;
		iLogger->Log(_L("ReStopVibra - StopVibraL() unexpected TRAP result."));
		aResult.iResultDes.Copy( _L("Starting vibra failed.") );
		}
	else
		{

		RDebug::Print(_L("VibraCtrlTest::ReStopVibra - Stopped first time."));
		
		// delay for waiting vibra to stop
		TRAP(err, CTestScheduler::StartAndStopL(2000));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

		RDebug::Print(_L("VibraCtrlTest::ReStopVibra - Stopping second time..."));

		// trap StopVibraL and use possible return value to log.
		TRAP(retVal2, wrapper->iVibra->StopVibraL());

		if (KErrNone != retVal2) 
			{
			aResult.iResult = retVal2;
			iLogger->Log(_L("ReStopVibra - StopVibraL()-2 unexpected TRAP result."));
			aResult.iResultDes.Copy( _L("Stopping vibra failed.") );
			}
		else
			{

			RDebug::Print(_L("VibraCtrlTest::ReStopVibra - Stopped second time."));

			// check that vibra is stopped
			retVal3 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestStopped);

			// check return values for passing or failing test case
			if(KErrNone == retVal1 && KErrNone == retVal2 && KErrNone == retVal3)
				{
				aResult.iResult = KErrNone;
				iLogger->Log(_L("ReStopVibra PASS"));
				}
			else
				{
				aResult.iResult = KErrGeneral;
				iLogger->Log(_L("ReStopVibra FAIL"));
				// error reason summary
				aResult.iResultDes.AppendFormat( _L("ReStopVibra - StopVibraL: %d, after ReStop: %d, and after stopped: %d"), retVal1, retVal2, retVal3 );
				}
			}

		}
		
	delete wrapper;

	return KErrNone;    
}


// -----------------------------------------------------------------------------
// Cvibractrltest::ReStopVibra2
// Just runs StopVibraL twice to see that nothing crashes
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cvibractrltest::ReStopVibra2( 
		TTestResult& aResult ) // Test case result
{
     
	TInt retVal1, retVal2, retVal3;

	iLogger->Log(_L("VibraCtrlTest::ReStopVibra")); RDebug::Print(_L("VibraCtrlTest::ReStopVibra"));

//	CVibrawrapper* wrapper = CVibrawrapper::NewL(true);	
	CVibrawrapper* wrapper;
	TRAPD(err, wrapper = CVibrawrapper::NewL(true));	
	if(err != KErrNone)
	{
		aResult.iResult = err;
		return err;
	}

	// trap StopVibraL and use possible return value to log.
	TRAP(retVal1, wrapper->iVibra->StopVibraL());

	if (KErrNone != retVal1) 
		{
		aResult.iResult = retVal1;
		iLogger->Log(_L("ReStopVibra2 - StopVibraL() unexpected TRAP result."));
		aResult.iResultDes.Copy( _L("Stopping vibra failed.") );
		}
	else
		{
	
		// delay for waiting vibra to stop
		TRAP(err, CTestScheduler::StartAndStopL(2000));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}
			
		// trap StopVibraL and use possible return value to log.
		TRAP(retVal2, wrapper->iVibra->StopVibraL());

		if (KErrNone != retVal2) 
			{
			aResult.iResult = retVal2;
			iLogger->Log(_L("ReStopVibra2 - StopVibraL()-2 unexpected TRAP result."));
			aResult.iResultDes.Copy( _L("Stopping vibra failed.") );
			}
		else
			{

			// check that vibra is stopped
			retVal3 = LogStatus(wrapper->iStatus, CVibraControl::EVibraRequestStopped);

			// check return values for passing or failing test case
			if(KErrNone == retVal1 && KErrNone == retVal2 && KErrNone == retVal3)
				{
				aResult.iResult = KErrNone;
				iLogger->Log(_L("ReStopVibra2 PASS"));				
				}
			else
				{
				aResult.iResult = KErrGeneral;
				iLogger->Log(_L("ReStopVibra2 FAIL"));
				// error reason summary
				aResult.iResultDes.AppendFormat( _L("ReStopVibra2 - StopVibraL: %d, after ReStop: %d, and after stopped: %d"), retVal1, retVal2, retVal3 );
				}
			}		

		}

	delete wrapper;

	return KErrNone;    
}

// -----------------------------------------------------------------------------
// Cvibractrltest::VibraSettingOn
// Sets VibraMode on in profile and then gets the current vibra mode.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cvibractrltest::VibraSettingOn( 
		TTestResult& aResult ) // Test case result
{
	iLogger->Log(_L("VibraCtrlTest::VibraSettingOn")); RDebug::Print(_L("VibraCtrlTest::VibraSettingOn"));

	aResult.iResult = KErrGeneral;

	CVibrawrapper* wrapper;
	TRAPD(err, wrapper = CVibrawrapper::NewL(true));	
	if(err != KErrNone)
	{
		aResult.iResult = err;
		return err;
	}

	// Save current vibramode in profile.
	CVibraControl::TVibraModeState oldMode = CVibraControl::EVibraModeUnknown;
	oldMode = wrapper->iVibra->VibraSettings();
    
    // Set vibra mode ON
    /*
    TProfileToneSettings settings; // = profileTones.ToneSettings();
    settings.iVibratingAlert = ETrue;
    */
    iRepository->Set(KVibraCtrlProfileVibraEnabled, 1 );

	// Stop this funcion and check for incoming notifications for the next 20 seconds.
	// Notification handler has CTestScheduler::Stop that returns the process here
	// when an incoming message has been received and handled.
		TRAP(err, CTestScheduler::StartAndStopL(10000));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

	// Read current profile setting.
	CVibraControl::TVibraModeState vibraMode = CVibraControl::EVibraModeUnknown;
	vibraMode = wrapper->iVibra->VibraSettings();

	// Read current wrapper setting (should have been updated at setint via notify)
	CVibraControl::TVibraModeState vibraMode2 = CVibraControl::EVibraModeUnknown;
	vibraMode2 = wrapper->iVibraModeState;


	// If the mode was on before the test started, no notification should ever have come
	// and vibraMode2 should remain Unknown.
    // or 
	// Check that both getter and wrapper return it OK.
	if( (  CVibraControl::EVibraModeON == oldMode
		&& CVibraControl::EVibraModeON == vibraMode
		&& CVibraControl::EVibraModeUnknown == vibraMode2)
		||
		(  CVibraControl::EVibraModeOFF == oldMode
		&& CVibraControl::EVibraModeON == vibraMode
		&& CVibraControl::EVibraModeON == vibraMode2) )

    {
		aResult.iResult = KErrNone;
		iLogger->Log(_L("VibraMode is ON"));
    }
    else 
    {
		aResult.iResult = KErrGeneral;
		if( CVibraControl::EVibraModeOFF == vibraMode )
			iLogger->Log(_L("Getter error -> VibraMode is OFF"));
		else
			iLogger->Log(_L("Getter error -> VibraMode is unknown"));
		if( CVibraControl::EVibraModeOFF == vibraMode2 )
			iLogger->Log(_L("Wrapper error -> VibraMode is OFF"));
		else
			iLogger->Log(_L("Wrapper error -> VibraMode is unknown"));
    }

    // Restore Vibramode to profile
	//if (CVibraControl::EVibraModeON == oldMode)
	//	{
	//	settings.iVibratingAlert = ETrue;
	//	}
	//else
	//	{
	//	settings.iVibratingAlert = EFalse;
	//	}
  //
  //  User::LeaveIfError( iRepository->Set(KVibraCtrlProfileVibraEnabled, settings.iVibratingAlert) );

    delete wrapper;
	return KErrNone;
}


// -----------------------------------------------------------------------------
// Cvibractrltest::VibraSettingOff
// Sets VibraMode off in profile and then gets the current vibra mode.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cvibractrltest::VibraSettingOff( 
		TTestResult& aResult ) // Test case result
{

	aResult.iResult = KErrGeneral;

	iLogger->Log(_L("VibraCtrlTest::VibraSettingOff")); RDebug::Print(_L("VibraCtrlTest::VibraSettingOff"));

	CVibrawrapper* wrapper;
	TRAPD(err, wrapper = CVibrawrapper::NewL(true));	
	if(err != KErrNone)
	{
		aResult.iResult = err;
		return err;
	}

	// Save current vibramode in profile.
	CVibraControl::TVibraModeState oldMode = CVibraControl::EVibraModeUnknown;
	oldMode = wrapper->iVibra->VibraSettings();
    
    // Set vibra mode OFF
  /*
    TProfileToneSettings settings; // = profileTones.ToneSettings();
    settings.iVibratingAlert = EFalse;
  */
  iRepository->Set(KVibraCtrlProfileVibraEnabled, 0 );

	// Stop this funcion and check for incoming notifications for the next 20 seconds.
	// Notification handler has CTestScheduler::Stop that returns the process here
	// when an incoming message has been received and handled.
		TRAP(err, CTestScheduler::StartAndStopL(10000));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

	// Read current profile setting.
	CVibraControl::TVibraModeState vibraMode = CVibraControl::EVibraModeUnknown;
	vibraMode = wrapper->iVibra->VibraSettings();

	// Read current wrapper setting (should have been updated at setint via notify)
	CVibraControl::TVibraModeState vibraMode2 = CVibraControl::EVibraModeUnknown;
	vibraMode2 = wrapper->iVibraModeState;

	// If the mode was off before the test started, no notification should ever have come
	// and vibraMode2 should remain Unknown.
	// or
	// Check that both getter and wrapper return it OK.
	if( (  CVibraControl::EVibraModeOFF == oldMode
		&& CVibraControl::EVibraModeOFF == vibraMode
		&& CVibraControl::EVibraModeUnknown == vibraMode2)
		||
		(  CVibraControl::EVibraModeON == oldMode
		&& CVibraControl::EVibraModeOFF == vibraMode
		&& CVibraControl::EVibraModeOFF == vibraMode2) )
    {
		aResult.iResult = KErrNone;
		iLogger->Log(_L("VibraMode is OFF"));
    }
    else 
    {
		aResult.iResult = KErrGeneral;
		if( CVibraControl::EVibraModeON == vibraMode )
			{
			iLogger->Log(_L("Getter error -> VibraMode is On"));
			RDebug::Print(_L("Getter error -> VibraMode is On"));
			}
		else
			iLogger->Log(_L("Getter error -> VibraMode is unknown"));
		if( CVibraControl::EVibraModeON == vibraMode2 )
			{
			iLogger->Log(_L("Wrapper error -> VibraMode is On"));
			RDebug::Print(_L("Wrapper error -> VibraMode is On"));
			}
		else
			iLogger->Log(_L("Wrapper error -> VibraMode is unknown"));
    }

    // Restore Vibramode to profile
	//if (CVibraControl::EVibraModeON == oldMode)
	//	{
	//	settings.iVibratingAlert = ETrue;
	//	}
	//else
	//	{
	//	settings.iVibratingAlert = EFalse;
	//	}
  //  User::LeaveIfError( iRepository->Set(KVibraCtrlProfileVibraEnabled, settings.iVibratingAlert) );

    delete wrapper;
	return KErrNone;
}

// -----------------------------------------------------------------------------
// Cvibractrltest::CheckRequest
// -----------------------------------------------------------------------------
void Cvibractrltest::CheckRequest(CVibraControl::TVibraRequestStatus Status, TTestResult& aResult)
{
	switch ( Status )
			{
		case CVibraControl::EVibraRequestOK:
			aResult.iResultDes.Append(_L("OK\n"));
			iLogger->Log(_L("EVibraRequestOK"));
			break;
		case CVibraControl::EVibraRequestFail:
			aResult.iResultDes.Append(_L("fail\n"));
			iLogger->Log(_L("EVibraRequestFail"));
			break;
		case CVibraControl::EVibraRequestNotAllowed:
			aResult.iResultDes.Append(_L("vibra set off in user profile"));
			iLogger->Log(_L("EVibraRequestNotAllowed\n"));
			break;
		case CVibraControl::EVibraRequestStopped:
			aResult.iResultDes.Append(_L("stopped\n"));
			iLogger->Log(_L("EVibraRequestNotAllowed"));
			break;
		case CVibraControl::EVibraRequestUnableToStop:
			aResult.iResultDes.Append(_L("unable to stop\n"));
			iLogger->Log(_L("EVibraRequestNotAllowed"));
			break;
		case CVibraControl::EVibraRequestUnknown:
			aResult.iResultDes.Append(_L("unknown\n"));
			iLogger->Log(_L("EVibraRequestNotAllowed"));
			break;
		default:
			aResult.iResultDes.Append(_L("not received\n"));
			iLogger->Log(_L("EVibraRequestNotAllowed"));
			break;
			}
}

// -----------------------------------------------------------------------------
// Cvibractrltest::LogStatus
// -----------------------------------------------------------------------------
TInt Cvibractrltest::LogStatus(CVibraControl::TVibraRequestStatus Status, CVibraControl::TVibraRequestStatus okStatus)
{

	TInt retval(KErrNone);
	
	if (okStatus == Status)
		{
		//aResult.iResultDes.Append(_L("OK\n"));
		iLogger->Log(_L("VibraCtrltest iStatus OK"));
		retval = KErrNone;		
		}
	else
		{
		switch ( Status )
				{
			case CVibraControl::EVibraRequestOK:
				RDebug::Print(_L("EVibraRequestOK"));
				iLogger->Log(_L("EVibraRequestOK"));				
				break;
			case CVibraControl::EVibraRequestFail:
				RDebug::Print(_L("EVibraRequestFail"));
				iLogger->Log(_L("EVibraRequestFail"));				
				break;
			case CVibraControl::EVibraRequestNotAllowed:
				RDebug::Print(_L("EVibraRequestNotAllowed - Vibra off in user profile\n"));
				iLogger->Log(_L("EVibraRequestNotAllowed\n"));				
				break;
			case CVibraControl::EVibraRequestStopped:
				RDebug::Print(_L("EVibraRequestStopped"));
				iLogger->Log(_L("EVibraRequestStopped"));				
				break;
			case CVibraControl::EVibraRequestUnableToStop:
				RDebug::Print(_L("EVibraRequestUnableToStop"));
				iLogger->Log(_L("EVibraRequestUnableToStop"));				
				break;
			case CVibraControl::EVibraRequestUnknown:
				RDebug::Print(_L("EVibraRequestUnknown"));
				iLogger->Log(_L("EVibraRequestUnknown"));
				break;
			default:
				RDebug::Print(_L("EVibraRequestDefaultErrorInSwitch"));
				iLogger->Log(_L("EVibraRequestDefaultErrorInSwitch"));				
				break;
				}		

				retval = KErrGeneral;
		}

	return retval;

}

// ================= OTHER EXPORTED FUNCTIONS =================================

// End of File
