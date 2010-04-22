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


#ifndef TDLSERVER_H
#define TDLSERVER_H

#include <f32file.h>
#include <test/TestExecuteServerBase.h>

class CTestDlByNameServer : public CTestServer
	{
public:
	static CTestDlByNameServer* NewL();
	virtual CTestStep* CreateTestStep(const TDesC& aStepName);

	};

#endif // TDLSERVER_H
