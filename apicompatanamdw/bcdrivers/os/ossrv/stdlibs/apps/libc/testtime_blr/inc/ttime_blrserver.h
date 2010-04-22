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
*  Name        : ttime_blrserver.h
*  Part of     : testtime_blr
*
*  Description : ?Description
*  Version:   0.5
*
  
*/

#ifndef __TTIME_BLRSERVER_H__
#define __TTIME_BLRSERVER_H__

#include <f32file.h>
#include <test/TestExecuteServerBase.h>

class CTimeBlrTestServer : public CTestServer
	{
public:
	static CTimeBlrTestServer* NewL();
	virtual CTestStep* CreateTestStep(const TDesC& aStepName);
	};

#endif // 
