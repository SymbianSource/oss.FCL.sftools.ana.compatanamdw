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
*  Name        : tstdlibserver.h
*  Part of     : teststdlib
*
*  Description : ?Description
*  Version:   0.5
*
  
*/

#ifndef __TSTDLIBSERVER_H__
#define __TSTDLIBSERVER_H__

#include <f32file.h>
#include <test/TestExecuteServerBase.h>

class CStdlibTestServer : public CTestServer
	{
public:
	static CStdlibTestServer* NewL();
	virtual CTestStep* CreateTestStep(const TDesC& aStepName);
	RFs& Fs() {return iFs;}

private:
	RFs iFs;
	};

#endif // 
