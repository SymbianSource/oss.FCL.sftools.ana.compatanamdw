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


 /*
* ==============================================================================
*  Name        : tmsgqueueserver.h
*  Part of     : testmsgqueue
*
*  Description : ?Description
*  Version:   0.5
*
  
*/

#ifndef __TMSGQUEUESERVER_H__
#define __TMSGQUEUESERVER_H__

#include <f32file.h>
#include <test/TestExecuteServerBase.h>

class CMsgqueueTestServer : public CTestServer
	{
public:
	static CMsgqueueTestServer* NewL();
	virtual CTestStep* CreateTestStep(const TDesC& aStepName);
	RFs& Fs() {return iFs;}
	~CMsgqueueTestServer();
	CMsgqueueTestServer();
	//void ConstructL(const TDesC& aName)
	//	{
		// do nothing
	//	}

private:
	RFs iFs;
	};

#endif // 
