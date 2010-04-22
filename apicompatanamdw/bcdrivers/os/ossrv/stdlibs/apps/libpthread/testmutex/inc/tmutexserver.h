/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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


 /*
* ==============================================================================
*  Name        : tmutexserver.h
*  Part of     : testmutexserver
*
*  Description : ?Description
*  Version:   0.5
*
  
*/

#ifndef __TMUTEXSERVER_H__
#define __TMUTEXSERVER_H__

#include <f32file.h>
#include <test/TestExecuteServerBase.h>

class CMutexTestServer : public CTestServer
	{
public:
	static CMutexTestServer* NewL();
	virtual CTestStep* CreateTestStep(const TDesC& aStepName);
	RFs& Fs() {return iFs;}

private:
	RFs iFs;
	};

#endif // 
