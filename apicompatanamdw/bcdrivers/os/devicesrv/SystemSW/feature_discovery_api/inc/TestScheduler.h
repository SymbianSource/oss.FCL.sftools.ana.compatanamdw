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
* Description:   Custom ActiveScheduler for test client
              If any of the active scheduler's active objects does not provide a RunError() function,
			  then a CActiveScheduler derived class must be defined and an implementation of the Error()
              function provided to perform the cleanup required.*
*/


#ifndef TC_TESTSCHEDULER_H
#define TC_TESTSCHEDULER_H


#include <e32base.h>
#include <e32std.h>
//#include "tc_log.h"

// Activeobject that is used to break scheduling on timeout
class CTimeout : public CActive
{
	RTimer iTimer;
	TBool  iTimed;

public:

	// returns true if timeout has expired
	TBool Timed() const
	{
		return iTimed;
	}

	// start waiting, and timeout in aTimeout milliseconds.
	void Start(TInt aTimeoutInMilliSecs); 

	virtual void DoCancel();
	virtual void RunL();

	CTimeout();
	~CTimeout();
};

// Controls the handling of asynchronous requests as represented by active objects.
class CTestScheduler : public CActiveScheduler
{
	CTimeout *iTimeout;
	static CTestScheduler *singleton;
	
public:

	virtual void WaitForAnyRequest();
	
	// Handles the result of a leave occurring in an active object's RunL() function.
	virtual void Error(TInt anError) const;

	// start scheduler for given amount of time
	static TBool StartAndStop(TInt aMillisecs);
	

//	void ConstructSchedulerL();

	CTestScheduler();
	virtual ~CTestScheduler();
protected:

	void ConstructSchedulerL();
	
};











#endif // TC_CTESTSCHEDULER_H
