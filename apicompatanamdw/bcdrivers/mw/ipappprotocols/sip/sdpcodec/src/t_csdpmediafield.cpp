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
* This contains CT_DataSdpMediaField
*/


#include "t_csdpmediafield.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <sdpcodecstringpool.h>

/*@{*/
_LIT(KCmdDestroy,           "~");
_LIT(KCmdNewL,              "NewL");
_LIT(KCmdNewLC,             "NewLC");


//Fields
_LIT(KFldMedia,                 "Media");
_LIT(KFldPort,                  "Port");
_LIT(KFldProtocol,              "Protocol");
_LIT(KFldFormatList,            "FormatList");

_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");


CT_DataSdpMediaField::CT_DataSdpMediaField()
:   CDataWrapperBase(), iSdpMediaField(NULL), iIsOwner(ETrue)
    {
    }

CT_DataSdpMediaField::~CT_DataSdpMediaField()
	{
	DestroyData();
	}

void CT_DataSdpMediaField::ConstructL()
	{
	}

CT_DataSdpMediaField* CT_DataSdpMediaField::NewL()
    {
	CT_DataSdpMediaField* self = new (ELeave)CT_DataSdpMediaField;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

TAny* CT_DataSdpMediaField::GetObject()
	{
	return iSdpMediaField;
	}

void CT_DataSdpMediaField::SetObjectL(TAny* aAny)
	{
	iSdpMediaField = static_cast<CSdpMediaField*>(aAny);
	}

void CT_DataSdpMediaField::DisownObjectL()
	{
	iSdpMediaField = NULL;
	iIsOwner = EFalse;
	}

TBool CT_DataSdpMediaField::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
	{
	TBool ret = ETrue;

	if ( aCommand==KCmdNewL )
		{
		DoCmdNewL(aSection);
		}
    else if ( aCommand==KCmdNewLC )
        {
        DoCmdNewLC(aSection);
        }
    else if ( aCommand==KCmdDestroy )
        {
        DoCmdDestructor(aSection);
        }
	else
		{
		ret = EFalse;
		}
	return ret;
    }

void CT_DataSdpMediaField::DoCmdNewL(const TTEFSectionName& aSection)
	{
	TBool dataOK = ETrue;
    RStringF media;
    TUint port;
    RStringF protocol;
    TPtrC strFormatList;
    if(!CT_SIPUtil::GetStringFFromConfigL(*this, aSection, KFldMedia, SdpCodecStringPool::StringPoolL(), media))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldMedia());
        dataOK = EFalse;
        }
    if(!GetTUintFromConfig(aSection, KFldPort, port))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldPort());
        dataOK = EFalse;
        }
    if(!CT_SIPUtil::GetStringFFromConfigL(*this, aSection, KFldProtocol, SdpCodecStringPool::StringPoolL(), protocol))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldProtocol());
        dataOK = EFalse;
        }
    if(!GetStringFromConfig(aSection, KFldFormatList, strFormatList))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldFormatList());
        dataOK = EFalse;
        }
    
    if(dataOK == EFalse)
        {
        SetBlockResult(EFail);
        return;
        }
    
    TBuf8<KMaxTestExecuteCommandLength> formatList;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(formatList, strFormatList);
    INFO_PRINTF1(_L("call CSdpMediaField::NewL(RStringF,TUint,RStringF,const TDesC8 &)"));
    TRAPD(err, iSdpMediaField = CSdpMediaField::NewL(media, port, protocol, formatList));
    
    media.Close();
    protocol.Close();
 	
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
	}

void CT_DataSdpMediaField::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    TBool dataOK = ETrue;
    RStringPool pool;
    RStringF media;
    TUint port;
    RStringF protocol;
    TPtrC strFormatList;
    if(!CT_SIPUtil::GetStringFFromConfigL(*this, aSection, KFldMedia, pool, media))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldMedia());
        dataOK = EFalse;
        }
    if(!GetTUintFromConfig(aSection, KFldPort, port))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldPort());
        dataOK = EFalse;
        }
    if(!CT_SIPUtil::GetStringFFromConfigL(*this, aSection, KFldProtocol, pool, protocol))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldProtocol());
        dataOK = EFalse;
        }
    if(!GetStringFromConfig(aSection, KFldFormatList, strFormatList))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldFormatList());
        dataOK = EFalse;
        }
    
    if(dataOK == EFalse)
        {
        SetBlockResult(EFail);
        return;
        }
    
    TBuf8<KMaxTestExecuteCommandLength> formatList;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(formatList, strFormatList);
    INFO_PRINTF1(_L("call CSdpMediaField::NewLC(RStringF,TUint,RStringF,const TDesC8 &)"));
    TRAPD(err, iSdpMediaField = CSdpMediaField::NewLC(media, port, protocol, formatList); CleanupStack::Pop(iSdpMediaField));
    
    media.Close();
    protocol.Close();
    pool.Close();
    
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void CT_DataSdpMediaField::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
	{
	INFO_PRINTF1(_L("call CSdpMediaField::~CSdpMediaField()"));
	DestroyData();
	}

void CT_DataSdpMediaField::DestroyData()
	{
	if(iIsOwner && iSdpMediaField)
	    {
	    delete iSdpMediaField;
	    iSdpMediaField = NULL;
	    }
	}

void CT_DataSdpMediaField::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

