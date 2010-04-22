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
*  Name        : tdouble_blrserver.h
*  Part of     : testdouble_blr
*
*  Description : ?Description
*  Version:   0.5
*
  
*/

#ifndef __TDOUBLE_BLRSERVER_H__
#define __TDOUBLE_BLRSERVER_H__

#include <f32file.h>
#include <test/TestExecuteServerBase.h>

class CTDouble_blrTestServer : public CTestServer
	{
public:
	static CTDouble_blrTestServer* NewL();
	virtual CTestStep* CreateTestStep(const TDesC& aStepName);
	RFs& Fs() {return iFs;}

private:
	RFs iFs;
	};

#endif // 
