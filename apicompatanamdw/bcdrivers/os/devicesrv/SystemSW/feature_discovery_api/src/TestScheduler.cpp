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


#include "TestScheduler.h"


CTestScheduler *CTestScheduler::singleton = 0;


// -----------------------------------------------------------------------------
// ?classname::?classname
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
void CTestScheduler::WaitForAnyRequest()
{
	User::WaitForAnyRequest();
}


// -----------------------------------------------------------------------------
// ?classname::?classname
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
void CTestScheduler::Error(TInt anError) const
{
	Stop();
}


// -----------------------------------------------------------------------------
// ?classname::?classname
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
TBool CTestScheduler::StartAndStop(TInt aMillisecs)
{
	// initialize timer and start scheduler
	singleton->iTimeout->Start(aMillisecs);
	CActiveScheduler::Start();

	// if not timed, then timer must be cancelled
	if (!singleton->iTimeout->Timed())
	{
		singleton->iTimeout->Cancel();
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


// -----------------------------------------------------------------------------
// ?classname::?classname
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
void CTestScheduler::ConstructSchedulerL()
{
	if (singleton)
		User::Leave(KErrGeneral); // trying to instantate singleton twice!
	singleton = this;

	CActiveScheduler::Install(this);
	iTimeout = new(ELeave) CTimeout;
}


// -----------------------------------------------------------------------------
// ?classname::?classname
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
CTestScheduler::CTestScheduler()
{
	iTimeout = 0;
}


// -----------------------------------------------------------------------------
// ?classname::?classname
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
CTestScheduler::~CTestScheduler()
{
	singleton = 0;
	delete iTimeout;
}



//CTIMEOUT


// -----------------------------------------------------------------------------
// ?classname::?classname
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
void CTimeout::Start(TInt aTimeoutInMilliSecs)
{
	iTimer.After(iStatus, 1000 * aTimeoutInMilliSecs);
	iTimed = FALSE;
	SetActive();
}


// -----------------------------------------------------------------------------
// ?classname::?classname
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
void CTimeout::DoCancel()
{
	iTimer.Cancel();
}


// -----------------------------------------------------------------------------
// ?classname::?classname
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
void CTimeout::RunL()
{
	iTimed = TRUE;
	CActiveScheduler::Stop();
}


// -----------------------------------------------------------------------------
// ?classname::?classname
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
CTimeout::CTimeout()
:CActive(0)
{
	iTimer.CreateLocal();
	CActiveScheduler::Add(this);
}


// -----------------------------------------------------------------------------
// ?classname::?classname
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
CTimeout::~CTimeout()
{
	Cancel();
	iTimer.Close();
}
