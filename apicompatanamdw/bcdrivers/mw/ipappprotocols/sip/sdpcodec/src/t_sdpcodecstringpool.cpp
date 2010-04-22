/*
* Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* This contains CT_DataSdpCodecStringPool
*/


#include "t_sdpcodecstringpool.h"

/*@{*/
_LIT(KCmdOpenL,              "OpenL");
_LIT(KCmdClose,              "Close");

_LIT(KLogError,             "Error=%d");

CT_DataSdpCodecStringPool::CT_DataSdpCodecStringPool()
:   CDataWrapperBase()
    {
    }

CT_DataSdpCodecStringPool::~CT_DataSdpCodecStringPool()
	{

	}

void CT_DataSdpCodecStringPool::ConstructL()
	{
	}

CT_DataSdpCodecStringPool* CT_DataSdpCodecStringPool::NewL()
    {
	CT_DataSdpCodecStringPool* self = new (ELeave)CT_DataSdpCodecStringPool;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

TAny* CT_DataSdpCodecStringPool::GetObject()
	{
	return NULL;
	}

TBool CT_DataSdpCodecStringPool::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
	{
	TBool ret = ETrue;

	if ( aCommand==KCmdOpenL )
		{
		DoCmdOpenL();
		}
    else if ( aCommand==KCmdClose )
        {
        DoCmdClose();
        }
	else
		{
		ret = EFalse;
		}
	return ret;
    }

void CT_DataSdpCodecStringPool::DoCmdOpenL()
	{
	INFO_PRINTF1(_L("call SdpCodecStringPool::OpenL()"));
	TRAPD(err, SdpCodecStringPool::OpenL());
	
    if (KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void CT_DataSdpCodecStringPool::DoCmdClose()
    {
    INFO_PRINTF1(_L("call SdpCodecStringPool::Close()"));
    TRAPD(err, SdpCodecStringPool::Close());
    }


