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
* This contains CT_DataSIPAddress
*/


#include "t_csipaddress.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <s32file.h>

/*@{*/
_LIT(KCmdDestroy,           "~");
_LIT(KCmdNewL,              "NewL");
_LIT(KCmdNewLC,             "NewLC");
_LIT(KCmdDecodeL,           "DecodeL");
_LIT(KCmdDisplayName,       "DisplayName");
_LIT(KCmdSetDisplayNameL,   "SetDisplayNameL");
_LIT(KCmdUri8,              "Uri8");
_LIT(KCmdSetUri8L,          "SetUri8L");
_LIT(KCmdInternalizeL,      "InternalizeL");
_LIT(KCmdExternalizeL,      "ExternalizeL");
_LIT(KCmdURI,               "URI");
_LIT(KCmdCompare,           "Compare");
_LIT(KCmdToTextLC,          "ToTextLC");

//Fields
_LIT(KFldUri8,              "uri8");
_LIT(KFldDisplayName,       "displayname");
_LIT(KFldSIPAddress,        "sipaddress");
_LIT(KFldAOR,               "aor");
_LIT(KFldUseAngleBrackets,  "useanglebrackets");
_LIT(KFldFileName,          "filename");
_LIT(KFldExpected,          "expected");

_LIT(KLogError,             "Error=%d");
_LIT(KLogMissingParameter,  "Missing parameter '%S'");
_LIT(KLogNotExpectedValue,  "Not expected value, actual=%d, expect=%d");
_LIT(KLogNotExpectedValue1, "Not expected value, actual=%S, expect=%S");

CT_DataSIPAddress::CT_DataSIPAddress()
:   CDataWrapperBase(), iSIPAddress(NULL), iIsOwner(ETrue)
    {
    }

CT_DataSIPAddress::~CT_DataSIPAddress()
	{
	DestroyData();
	}

void CT_DataSIPAddress::ConstructL()
	{
	}

CT_DataSIPAddress* CT_DataSIPAddress::NewL()
    {
	CT_DataSIPAddress* self = new (ELeave)CT_DataSIPAddress;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

TAny* CT_DataSIPAddress::GetObject()
	{
	return iSIPAddress;
	}

void CT_DataSIPAddress::SetObjectL(TAny* aAny)
	{
	iSIPAddress = static_cast<CSIPAddress*>(aAny);
	}

void CT_DataSIPAddress::DisownObjectL()
	{
	iSIPAddress = NULL;
	iIsOwner = EFalse;
	}

TBool CT_DataSIPAddress::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
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
    else if ( aCommand==KCmdDecodeL )
        {
        DoCmdDecodeL(aSection);
        }
    else if ( aCommand==KCmdDisplayName )
        {
        DoCmdDisplayName(aSection);
        }
    else if ( aCommand==KCmdSetDisplayNameL )
        {
        DoCmdSetDisplayNameL(aSection);
        }
    else if ( aCommand==KCmdUri8 )
        {
        DoCmdUri8(aSection);
        }
    else if ( aCommand==KCmdSetUri8L )
        {
        DoCmdSetUri8L(aSection);
        }
    else if ( aCommand==KCmdInternalizeL )
        {
        DoCmdInternalizeL(aSection);
        }
    else if ( aCommand==KCmdExternalizeL )
        {
        DoCmdExternalizeL(aSection);
        }
    else if ( aCommand==KCmdURI )
        {
        DoCmdURI(aSection);
        }
    else if ( aCommand==KCmdCompare )
        {
        DoCmdCompare(aSection);
        }
    else if ( aCommand==KCmdToTextLC )
        {
        DoCmdToTextLC(aSection);
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

void CT_DataSIPAddress::DoCmdNewL(const TTEFSectionName& aSection)
	{
	TInt err = KErrNone;
	CUri8* uri = NULL;
    CSIPAddress* sipaddr = NULL;
	if( CT_SIPUtil::GetUri8L(*this, aSection, KFldUri8, uri) )
	    {
	    TPtrC temp;
	    if( GetStringFromConfig(aSection, KFldDisplayName, temp) )
	        {
	        TBuf8<KMaxTestExecuteCommandLength> displayname;
	        CnvUtfConverter::ConvertFromUnicodeToUtf8(displayname, temp);
	        INFO_PRINTF1(_L("call CSIPAddress::NewL(const TDesC8&, CUri8*)"));
	        TRAP(err, iSIPAddress = CSIPAddress::NewL(displayname, uri)); 
	        }
	    else
	        {
	        INFO_PRINTF1(_L("call CSIPAddress::NewL(CUri8*)"));
	        TRAP(err, iSIPAddress = CSIPAddress::NewL(uri)); 
	        }
	    }
	else if(CT_SIPUtil::GetSIPAddressL(*this, aSection, KFldSIPAddress, sipaddr))
	    {
	    INFO_PRINTF1(_L("call CSIPAddress::NewL(const CSIPAddress&)"));
        TRAP(err, iSIPAddress = CSIPAddress::NewL(*sipaddr)); 
	    }
	else
	    {
        ERR_PRINTF1(KLogMissingParameter);
        SetBlockResult(EFail);
        return;
	    }
	
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
	}

void CT_DataSIPAddress::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    TInt err = KErrNone;
    CUri8* uri = NULL;
    CSIPAddress* sipaddr = NULL;
    if( CT_SIPUtil::GetUri8L(*this, aSection, KFldUri8, uri) )
        {
        TPtrC temp;
        if( GetStringFromConfig(aSection, KFldDisplayName, temp) )
            {
            TBuf8<KMaxTestExecuteCommandLength> displayname;
            CnvUtfConverter::ConvertFromUnicodeToUtf8(displayname, temp);
            INFO_PRINTF1(_L("call CSIPAddress::NewLC(const TDesC8&, CUri8*)"));
            TRAP(err, iSIPAddress = CSIPAddress::NewLC(displayname, uri); CleanupStack::Pop()); 
            }
        else
            {
            INFO_PRINTF1(_L("call CSIPAddress::NewLC(CUri8*)"));
            TRAP(err, iSIPAddress = CSIPAddress::NewLC(uri); CleanupStack::Pop()); 
            }
        }
    else if( CT_SIPUtil::GetSIPAddressL(*this, aSection, KFldSIPAddress, sipaddr) )
        {
        INFO_PRINTF1(_L("call CSIPAddress::NewLC(Cconst CSIPAddress&)"));
        TRAP(err, iSIPAddress = CSIPAddress::NewLC(*sipaddr); CleanupStack::Pop()); 
        }
    else
        {
        ERR_PRINTF1(KLogMissingParameter);
        SetBlockResult(EFail);
        return;
        }
    
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void CT_DataSIPAddress::DoCmdDecodeL(const TTEFSectionName& aSection)
    {
    TPtrC temp;
    if( !GetStringFromConfig(aSection, KFldAOR, temp) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldAOR);
        SetBlockResult(EFail);
        }
    else
        {
        TPtrC wrapperName;
        if( !GetStringFromConfig(aSection, KFldSIPAddress, wrapperName) )
            {
            ERR_PRINTF2(KLogMissingParameter, &KFldSIPAddress);
            SetBlockResult(EFail);
            }
        else
            {
            TBuf8<KMaxTestExecuteCommandLength> aor;
            CnvUtfConverter::ConvertFromUnicodeToUtf8(aor, temp);
            INFO_PRINTF1(_L("call CSIPAddress::DecodeL(const TDesC8&)"));
            CSIPAddress* ret = NULL;
            TRAPD(err, ret = CSIPAddress::DecodeL(aor));
            
            if(KErrNone != err)
                {
                ERR_PRINTF2(KLogError, err);
                SetError(err);
                }
            else
                {
                SetDataObjectL(wrapperName, ret);
                }
            }
        }
    }

void CT_DataSIPAddress::DoCmdDisplayName(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPAddress::DisplayName()"));
    const TDesC8& ret = iSIPAddress->DisplayName();
    
    TPtrC temp;
    if( GetStringFromConfig(aSection, KFldExpected, temp) )
        {
        TBuf8<KMaxTestExecuteCommandLength> expected;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(expected, temp);
        if(ret != expected)
            {
            TBuf<KMaxTestExecuteCommandLength> temp1;
            CnvUtfConverter::ConvertToUnicodeFromUtf8(temp1, ret);
            ERR_PRINTF3(KLogNotExpectedValue1, &temp1, &temp);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPAddress::DoCmdSetDisplayNameL(const TTEFSectionName& aSection)
    {
    TPtrC temp;
    if( !GetStringFromConfig(aSection, KFldDisplayName, temp) )
        {        
        ERR_PRINTF2(KLogMissingParameter, &KFldDisplayName);
        SetBlockResult(EFail);
        }
    else
        {
        TBuf8<KMaxTestExecuteCommandLength> displayname;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(displayname, temp);
        INFO_PRINTF1(_L("call CSIPAddress::SetDisplayNameL(const TDesC8&)"));
        TRAPD(err, iSIPAddress->SetDisplayNameL(displayname));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    }

void CT_DataSIPAddress::DoCmdUri8(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPAddress::Uri8()"));
    const CUri8& ret = iSIPAddress->Uri8();
    
    CUri8* expected;
    if( CT_SIPUtil::GetUri8L(*this, aSection, KFldSIPAddress, expected) )
        {
        if(ret.Uri().UriDes() != expected->Uri().UriDes())
            {
            TBuf<KMaxTestExecuteCommandLength> temp;
            CnvUtfConverter::ConvertToUnicodeFromUtf8(temp, expected->Uri().UriDes());
            TBuf<KMaxTestExecuteCommandLength> temp1;
            CnvUtfConverter::ConvertToUnicodeFromUtf8(temp1, ret.Uri().UriDes());
            ERR_PRINTF3(KLogNotExpectedValue1, &temp1, &temp);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPAddress::DoCmdSetUri8L(const TTEFSectionName& aSection)
    {
    CUri8* uri;
    if( CT_SIPUtil::GetUri8L(*this, aSection, KFldSIPAddress, uri) )
        {
        INFO_PRINTF1(_L("call CSIPAddress::SetUri8L(CUri8*)"));
        TRAPD(err, iSIPAddress->SetUri8L(uri));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    }

void CT_DataSIPAddress::DoCmdToTextLC(const TTEFSectionName& aSection)
    {
    TBool useAngleBrackets = EFalse;
    (void)GetBoolFromConfig(aSection, KFldUseAngleBrackets, useAngleBrackets);
    INFO_PRINTF1(_L("call CSIPAddress::ToTextLC(TBool aUseAngleBrackets=EFalse))"));
    HBufC8* ret = NULL;
    TRAPD(err, ret = iSIPAddress->ToTextLC(useAngleBrackets); CleanupStack::Pop());
    
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    else
        {
        TPtrC temp;
        if( GetStringFromConfig(aSection, KFldExpected, temp) )
            {
            TBuf8<KMaxTestExecuteCommandLength> expected;
            CnvUtfConverter::ConvertFromUnicodeToUtf8(expected, temp);
            if(ret->Des() != expected)
                {
                TBuf<KMaxTestExecuteCommandLength> temp1;
                CnvUtfConverter::ConvertToUnicodeFromUtf8(temp1, ret->Des());
                ERR_PRINTF3(KLogNotExpectedValue1, &temp1, &temp);
                SetBlockResult(EFail);
                }
            }
        }
    
    delete ret;
    }

void CT_DataSIPAddress::DoCmdInternalizeL(const TTEFSectionName& aSection)
    {
    TPtrC datFileName;
    if( !GetStringFromConfig(aSection, KFldFileName, datFileName) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldFileName);
        SetBlockResult(EFail);
        }
    else
        {
        CDirectFileStore*   readstore = CDirectFileStore::OpenL(FileServer(), datFileName, EFileStream | EFileRead);
        CleanupStack::PushL(readstore);
        TStreamId           headerid = readstore->Root();
        RStoreReadStream    readstrm;

        readstrm.OpenL(*readstore, headerid);
        CleanupClosePushL(readstrm);
        
        INFO_PRINTF1(_L("call CSIPAddress::InternalizeL(RReadStream&)"));
        TRAPD(err, iSIPAddress = CSIPAddress::InternalizeL(readstrm));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        
        CleanupStack::PopAndDestroy(2);
        }
    }

void CT_DataSIPAddress::DoCmdExternalizeL(const TTEFSectionName& aSection)
    {
    TPtrC datFileName;
    if( !GetStringFromConfig(aSection, KFldFileName, datFileName) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldFileName);
        SetBlockResult(EFail);
        }
    else
        {
        CDirectFileStore* writestore = CDirectFileStore::ReplaceL(FileServer(), datFileName, EFileStream | EFileWrite);
        CleanupStack::PushL(writestore);        
        writestore->SetTypeL(TUidType(KDirectFileStoreLayoutUid));
        RStoreWriteStream writestrm;
        CleanupClosePushL(writestrm);
        TStreamId headerid = writestrm.CreateL(*writestore);
        writestore->SetRootL(headerid);
        
        INFO_PRINTF1(_L("call CSIPAddress::ExternalizeL(RWriteStream&)"));
        TRAPD(err, iSIPAddress->ExternalizeL(writestrm));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        
        CleanupStack::PopAndDestroy(2);
        }
    }

void CT_DataSIPAddress::DoCmdURI(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPAddress::URI()"));
    // For internal use only
    }

// operator==()
void CT_DataSIPAddress::DoCmdCompare(const TTEFSectionName& aSection) 
    {
    CSIPAddress* sipaddr = NULL;
    if( !CT_SIPUtil::GetSIPAddressL(*this, aSection, KFldSIPAddress, sipaddr) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPAddress);
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPAddress::==(const CSIPAddress&)")); 
        TBool ret = (*iSIPAddress == *sipaddr);
        
        TBool expected;
        if( GetBoolFromConfig(aSection, KFldExpected, expected) )
            {
            if(ret != expected)
                {
                ERR_PRINTF3(KLogNotExpectedValue, (TInt)ret, (TInt)expected);
                SetBlockResult(EFail);
                }
            }
        }
    }

void CT_DataSIPAddress::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
	{
	INFO_PRINTF1(_L("call CSIPAddress::~CSIPAddress()"));
	DestroyData();
	}

void CT_DataSIPAddress::DestroyData()
	{
	if(iIsOwner && iSIPAddress)
	    {
	    delete iSIPAddress;
	    iSIPAddress = NULL;
	    }
	}

void CT_DataSIPAddress::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

