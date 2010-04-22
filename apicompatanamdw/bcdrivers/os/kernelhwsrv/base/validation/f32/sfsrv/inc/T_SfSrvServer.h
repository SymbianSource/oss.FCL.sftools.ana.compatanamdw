/*
* Copyright (c) 2007-2008 Nokia Corporation and/or its subsidiary(-ies).
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

/**
@test
@internalComponent

This contains CT_SfSrvServer
*/

#ifndef __T_SFSRV_SERVER_H__
#define __T_SFSRV_SERVER_H__

#include <testblockcontroller.h>
#include <testserver2.h>

#include "T_FsData.h"
#include "T_FileData.h"
#include "T_FormatData.h"
#include "T_FileManData.h"


_LIT(KRFs, 					"RFs");
_LIT(KRFile,				"RFile");
_LIT(KRFormat,				"RFormat");
_LIT(KCFileMan, 			"CFileMan");

class CT_SfSrvServer : public CTestServer2
	{
private:
	class CT_SfSrvBlock : public CTestBlockController
		{
	public:
		inline CT_SfSrvBlock();
		inline ~CT_SfSrvBlock();

		inline CDataWrapper*	CreateDataL(const TDesC& aData);
		};

public:
	static CT_SfSrvServer* NewL();
	inline ~CT_SfSrvServer();

	inline CTestBlockController*	CreateTestBlock();

protected:
	inline CT_SfSrvServer();
	};

#include "T_SfSrvServer.inl"

#endif // __T_SFSRV_SERVER_H__
