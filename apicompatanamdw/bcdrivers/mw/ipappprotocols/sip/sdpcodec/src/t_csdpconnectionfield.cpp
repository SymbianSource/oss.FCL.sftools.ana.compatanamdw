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
* This contains CT_DataSdpConnectionField
*/


#include "t_csdpconnectionfield.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <sdpcodecstringpool.h>

/*@{*/
_LIT(KCmdDestroy,           "~");
_LIT(KCmdNewL,              "NewL");
_LIT(KCmdNewLC,             "NewLC");


//Fields
_LIT(KFldAddress,           "Address");
_LIT(KFldTTL,               "TTL");
_LIT(KFldNumOfAddress,      "NumOfAddress");
_LIT(KFldNetType,           "NetType");
_LIT(KFldAddressType,       "AddressType");

_LIT(KLogError,             "Error=%d");
_LIT(KLogMissingParameter,  "Missing parameter '%S'");


CT_DataSdpConnectionField::CT_DataSdpConnectionField()
:   CDataWrapperBase(), iSdpConnectionField(NULL), iIsOwner(ETrue)
    {
    }

CT_DataSdpConnectionField::~CT_DataSdpConnectionField()
	{
	DestroyData();
	}

void CT_DataSdpConnectionField::ConstructL()
	{
	}

CT_DataSdpConnectionField* CT_DataSdpConnectionField::NewL()
    {
	CT_DataSdpConnectionField* self = new (ELeave)CT_DataSdpConnectionField;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

TAny* CT_DataSdpConnectionField::GetObject()
	{
	return iSdpConnectionField;
	}

void CT_DataSdpConnectionField::SetObjectL(TAny* aAny)
	{
	iSdpConnectionField = static_cast<CSdpConnectionField*>(aAny);
	}

void CT_DataSdpConnectionField::DisownObjectL()
	{
	iSdpConnectionField = NULL;
	iIsOwner = EFalse;
	}

TBool CT_DataSdpConnectionField::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
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

void CT_DataSdpConnectionField::DoCmdNewL(const TTEFSectionName& aSection)
	{
	TPtrC strAddress;
    if (!GetStringFromConfig(aSection, KFldAddress, strAddress))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldAddress());
        SetBlockResult(EFail);
        return;;
        }
    TBool hasNetType = EFalse;
    TBool hasAddressType = EFalse;
    RStringF netType;
    RStringF addressType;
    if (CT_SIPUtil::GetStringFFromConfigL(*this, aSection, KFldNetType, 
            SdpCodecStringPool::StringPoolL(), netType))
        {
        hasNetType = ETrue;
        }
    if (CT_SIPUtil::GetStringFFromConfigL(*this, aSection, KFldAddressType,
            SdpCodecStringPool::StringPoolL(), addressType))
        {
        hasAddressType = ETrue;
        }
    if (!hasNetType && !hasAddressType)
        {
        INFO_PRINTF1(_L("call CSdpConnectionField::NewL(const TInetAddr &,TInt,TUint)"));
        TInetAddr inetAddr;
        inetAddr.Input(strAddress);
        TInt ttl = KErrNotFound;
        TUint numOfAddress = KDefaultNumOfAddress;
        (void)GetIntFromConfig(aSection, KFldTTL, ttl);
        (void)GetTUintFromConfig(aSection, KFldNumOfAddress, numOfAddress);
        TRAPD(err, iSdpConnectionField = CSdpConnectionField::NewL(inetAddr, ttl, numOfAddress));
        if (KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    else if (hasNetType && hasAddressType)
        {
        TBuf8<KMaxTestExecuteCommandLength> address;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(address, strAddress);
        INFO_PRINTF1(_L("call CSdpConnectionField::NewL(RStringF,RStringF,const TDesC8 &)"));
        TRAPD(err, iSdpConnectionField = CSdpConnectionField::NewL(netType, addressType, address));
        if (KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    else if (hasNetType && !hasAddressType)
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldAddressType());
        SetBlockResult(EFail);
        }
    else if (!hasNetType && hasAddressType)
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldNetType());
        SetBlockResult(EFail);
        }
    netType.Close();
    addressType.Close();
	}

void CT_DataSdpConnectionField::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    TPtrC strAddress;
     if (!GetStringFromConfig(aSection, KFldAddress, strAddress))
         {
         ERR_PRINTF2(KLogMissingParameter, &KFldAddress());
         SetBlockResult(EFail);
         return;;
         }
     TBool hasNetType = EFalse;
     TBool hasAddressType = EFalse;
     RStringF netType;
     RStringF addressType;
     if (CT_SIPUtil::GetStringFFromConfigL(*this, aSection, KFldNetType, 
             SdpCodecStringPool::StringPoolL(), netType))
         {
         hasNetType = ETrue;
         }
     if (CT_SIPUtil::GetStringFFromConfigL(*this, aSection, KFldAddressType,
             SdpCodecStringPool::StringPoolL(), addressType))
         {
         hasAddressType = ETrue;
         }
     if (!hasNetType && !hasAddressType)
         {
         INFO_PRINTF1(_L("call CSdpConnectionField::NewLC(const TInetAddr &,TInt,TUint)"));
         TInetAddr inetAddr;
         inetAddr.Input(strAddress);
         TInt ttl = KErrNotFound;
         TUint numOfAddress = KDefaultNumOfAddress;
         (void)GetIntFromConfig(aSection, KFldTTL, ttl);
         (void)GetTUintFromConfig(aSection, KFldNumOfAddress, numOfAddress);
         TRAPD(err, iSdpConnectionField = CSdpConnectionField::NewLC(inetAddr, ttl, numOfAddress); CleanupStack::Pop(iSdpConnectionField));
         if (KErrNone != err)
             {
             ERR_PRINTF2(KLogError, err);
             SetError(err);
             }
         }
     else if (hasNetType && hasAddressType)
         {
         TBuf8<KMaxTestExecuteCommandLength> address;
         CnvUtfConverter::ConvertFromUnicodeToUtf8(address, strAddress);
         INFO_PRINTF1(_L("call CSdpConnectionField::NewLC(RStringF,RStringF,const TDesC8 &)"));
         TRAPD(err, iSdpConnectionField = CSdpConnectionField::NewLC(netType, addressType, address); CleanupStack::Pop(iSdpConnectionField));
         if (KErrNone != err)
             {
             ERR_PRINTF2(KLogError, err);
             SetError(err);
             }
         }
     else if (hasNetType && !hasAddressType)
         {
         ERR_PRINTF2(KLogMissingParameter, &KFldAddressType());
         SetBlockResult(EFail);
         }
     else if (!hasNetType && hasAddressType)
         {
         ERR_PRINTF2(KLogMissingParameter, &KFldNetType());
         SetBlockResult(EFail);
         }
     netType.Close();
     addressType.Close();
    }

void CT_DataSdpConnectionField::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
	{
	INFO_PRINTF1(_L("call CSdpConnectionField::~CSdpConnectionField()"));
	DestroyData();
	}

void CT_DataSdpConnectionField::DestroyData()
	{
	if(iIsOwner && iSdpConnectionField)
	    {
	    delete iSdpConnectionField;
	    iSdpConnectionField = NULL;
	    }
	}

void CT_DataSdpConnectionField::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

