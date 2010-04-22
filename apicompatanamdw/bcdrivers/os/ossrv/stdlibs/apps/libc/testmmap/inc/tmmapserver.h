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
*  Name        : tmmapserver.h
*  Part of     : testmmap
*
*  Description : ?Description
*  Version:   0.5
*
  
*/

#ifndef __TPROGNAMESERVER_H__
#define __TPROGNAMESERVER_H__

#include <f32file.h>
#include <test/TestExecuteServerBase.h>

class CMmapTestServer : public CTestServer
	{
public:
	static CMmapTestServer* NewL();
	virtual CTestStep* CreateTestStep(const TDesC& aStepName);
	RFs& Fs() {return iFs;}

private:
	RFs iFs;
	};

#endif // 
