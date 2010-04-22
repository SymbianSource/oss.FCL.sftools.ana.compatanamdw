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
* This contains CT_DataSdpOriginField
*/


#include "t_csdporiginfield.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <stringpool.h>
#include <sdpcodecstringpool.h>

/*@{*/
_LIT(KCmdDestroy,           "~");
_LIT(KCmdNewL,              "NewL");
_LIT(KCmdNewLC,             "NewLC");


//Fields
_LIT(KFldUserName,          "UserName");
_LIT(KFldSessionId,         "SessionId");
_LIT(KFldSessionVersion,    "SessionVersion");
_LIT(KFldNetType,           "NetType");
_LIT(KFldAddressType,       "AddressType");
_LIT(KFldAddress,           "Address");

_LIT(KLogError,             "Error=%d");
_LIT(KLogMissingParameter,  "Missing parameter '%S'");


CT_DataSdpOriginField::CT_DataSdpOriginField()
:   CDataWrapperBase(), iSdpOriginField(NULL), iIsOwner(ETrue)
    {
    }

CT_DataSdpOriginField::~CT_DataSdpOriginField()
	{
	DestroyData();
	}

void CT_DataSdpOriginField::ConstructL()
	{
	}

CT_DataSdpOriginField* CT_DataSdpOriginField::NewL()
    {
	CT_DataSdpOriginField* self = new (ELeave)CT_DataSdpOriginField;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

TAny* CT_DataSdpOriginField::GetObject()
	{
	return iSdpOriginField;
	}

void CT_DataSdpOriginField::SetObjectL(TAny* aAny)
	{
	iSdpOriginField = static_cast<CSdpOriginField*>(aAny);
	}

void CT_DataSdpOriginField::DisownObjectL()
	{
	iSdpOriginField = NULL;
	iIsOwner = EFalse;
	}

TBool CT_DataSdpOriginField::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
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

void CT_DataSdpOriginField::DoCmdNewL(const TTEFSectionName& aSection)
	{
	TBool dataOK = ETrue;
	TPtrC strUserName;
	TInt sessionId;
	TInt sessionVersion;
	TPtrC strAddress;
	if(!GetStringFromConfig(aSection, KFldUserName, strUserName))
	    {
	    ERR_PRINTF2(KLogMissingParameter, &KFldUserName());
	    dataOK = EFalse;
	    }
	if(!GetIntFromConfig(aSection, KFldSessionId, sessionId))
	    {
	    ERR_PRINTF2(KLogMissingParameter, &KFldSessionId());
	    dataOK = EFalse;
	    }
    if (!GetIntFromConfig(aSection, KFldSessionVersion, sessionVersion))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSessionVersion());
        dataOK = EFalse;
        }
    if (!GetStringFromConfig(aSection, KFldAddress, strAddress))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldAddress());
        dataOK = EFalse;
        }
    if(dataOK == EFalse)
        {
        SetBlockResult(EFail);
        return;
        }
    TBuf8<KMaxTestExecuteCommandLength> userName;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(userName, strUserName);
    TBool hasNetType = EFalse;
    TBool hasAddressType = EFalse;
    RStringF netType;
    RStringF addressType;
    if(CT_SIPUtil::GetStringFFromConfigL(*this, aSection, KFldNetType, SdpCodecStringPool::StringPoolL(), netType))
        {
        hasNetType = ETrue;
        }
    if(CT_SIPUtil::GetStringFFromConfigL(*this, aSection, KFldAddressType, SdpCodecStringPool::StringPoolL(), addressType))
        {
        hasAddressType = ETrue;
        }
    if(!hasNetType && !hasAddressType)
        {
        INFO_PRINTF1(_L("call CSdpOriginField::NewL(const TDesC8 &,TInt64,TInt64,TInetAddr &)"));
        TInetAddr inetAddr;
        inetAddr.Input(strAddress);
        TRAPD(err, iSdpOriginField = CSdpOriginField::NewL(userName, sessionId, sessionVersion, inetAddr));
        if (KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    else if(hasNetType && hasAddressType)
        {
        TBuf8<KMaxTestExecuteCommandLength> address;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(address, strAddress);
        INFO_PRINTF1(_L("call CSdpOriginField::NewL(const TDesC8 &,TInt64,TInt64,RStringF,RStringF,const TDesC8 &)"));
        TRAPD(err, iSdpOriginField = CSdpOriginField::NewL(userName, sessionId, sessionVersion, netType, addressType, address));
        if (KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    else if(hasNetType && !hasAddressType)
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldAddressType());
        SetBlockResult(EFail);
        }
    else if(!hasNetType && hasAddressType)
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldNetType());
        SetBlockResult(EFail);
        }
    netType.Close();
    addressType.Close();
    }

void CT_DataSdpOriginField::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    TBool dataOK = ETrue;
     TPtrC strUserName;
     TInt sessionId;
     TInt sessionVersion;
     TPtrC strAddress;
     if(!GetStringFromConfig(aSection, KFldUserName, strUserName))
         {
         ERR_PRINTF2(KLogMissingParameter, &KFldUserName());
         dataOK = EFalse;
         }
     if(!GetIntFromConfig(aSection, KFldSessionId, sessionId))
         {
         ERR_PRINTF2(KLogMissingParameter, &KFldSessionId());
         dataOK = EFalse;
         }
     if (!GetIntFromConfig(aSection, KFldSessionVersion, sessionVersion))
         {
         ERR_PRINTF2(KLogMissingParameter, &KFldSessionVersion());
         dataOK = EFalse;
         }
     if (!GetStringFromConfig(aSection, KFldAddress, strAddress))
         {
         ERR_PRINTF2(KLogMissingParameter, &KFldAddress());
         dataOK = EFalse;
         }
     if(dataOK == EFalse)
         {
         SetBlockResult(EFail);
         return;
         }
     TBuf8<KMaxTestExecuteCommandLength> userName;
     CnvUtfConverter::ConvertFromUnicodeToUtf8(userName, strUserName);
     TBool hasNetType = EFalse;
     TBool hasAddressType = EFalse;
     RStringF netType;
     RStringF addressType;
     if(CT_SIPUtil::GetStringFFromConfigL(*this, aSection, KFldNetType, SdpCodecStringPool::StringPoolL(), netType))
         {
         hasNetType = ETrue;
         }
     if(CT_SIPUtil::GetStringFFromConfigL(*this, aSection, KFldAddressType, SdpCodecStringPool::StringPoolL(), addressType))
         {
         hasAddressType = ETrue;
         }
     if(!hasNetType && !hasAddressType)
         {
         INFO_PRINTF1(_L("call CSdpOriginField::NewLC(const TDesC8 &,TInt64,TInt64,TInetAddr &)"));
         TInetAddr inetAddr;
         inetAddr.Input(strAddress);
         TRAPD(err, iSdpOriginField = CSdpOriginField::NewLC(userName, sessionId, sessionVersion, inetAddr); CleanupStack::Pop(iSdpOriginField));
         if (KErrNone != err)
             {
             ERR_PRINTF2(KLogError, err);
             SetError(err);
             }
         }
     else if(hasNetType && hasAddressType)
         {
         TBuf8<KMaxTestExecuteCommandLength> address;
         CnvUtfConverter::ConvertFromUnicodeToUtf8(address, strAddress);
         INFO_PRINTF1(_L("call CSdpOriginField::NewLC(const TDesC8 &,TInt64,TInt64,RStringF,RStringF,const TDesC8 &)"));
         TRAPD(err, iSdpOriginField = CSdpOriginField::NewLC(userName, sessionId, sessionVersion, netType, addressType, address); CleanupStack::Pop(iSdpOriginField));
         if (KErrNone != err)
             {
             ERR_PRINTF2(KLogError, err);
             SetError(err);
             }
         }
     else if(hasNetType && !hasAddressType)
         {
         ERR_PRINTF2(KLogMissingParameter, &KFldAddressType());
         SetBlockResult(EFail);
         }
     else if(!hasNetType && hasAddressType)
         {
         ERR_PRINTF2(KLogMissingParameter, &KFldNetType());
         SetBlockResult(EFail);
         }
     netType.Close();
     addressType.Close();
    }

void CT_DataSdpOriginField::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
	{
	INFO_PRINTF1(_L("call CSdpOriginField::~CSdpOriginField()"));
	DestroyData();
	}

void CT_DataSdpOriginField::DestroyData()
	{
	if(iIsOwner && iSdpOriginField)
	    {
	    delete iSdpOriginField;
	    iSdpOriginField = NULL;
	    }
	}

void CT_DataSdpOriginField::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

