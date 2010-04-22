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


#include "t_csiptimestampheader.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <s32file.h>
#include <sipcseqheader.h>
#include <stdlib.h>

/*@{*/
_LIT(KCmdDestructor,            "~");
_LIT(KCmdConstructorL,          "CSIPTimestampHeader");
_LIT(KCmdDecodeL,               "DecodeL");
_LIT(KCmdTimestamp,             "Timestamp");
_LIT(KCmdSetTimestamp,          "SetTimestamp");
_LIT(KCmdHasDelay,              "HasDelay");
_LIT(KCmdSetDelay,              "SetDelay");
_LIT(KCmdDelay,                 "Delay");
_LIT(KCmdInternalizeValueL,     "InternalizeValueL");

//Fields
_LIT(KFldTimestamp,             "timestamp");
_LIT(KFldDelay,                 "delay");
_LIT(KFldValue,                 "value");
_LIT(KFldSIPTimestampHeader,    "timestampheader");
_LIT(KFldExpected,              "expected");
_LIT(KFldFileName,              "filename");

_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");
_LIT(KLogNotExpectedValue,      "Not expected value, actual=%d, expect=%d");
_LIT(KLogNotExpectedValueReal,  "Not expected value, actual=%f, expect=%f");

CT_DataSIPTimestampHeader::CT_DataSIPTimestampHeader()
:   CT_DataSIPHeaderBase(), iSIPTimestampHeader(NULL), iIsOwner(ETrue)
    {
    }

CT_DataSIPTimestampHeader::~CT_DataSIPTimestampHeader()
	{
	DestroyData();
	}

void CT_DataSIPTimestampHeader::ConstructL()
	{
	}

CT_DataSIPTimestampHeader* CT_DataSIPTimestampHeader::NewL()
    {
	CT_DataSIPTimestampHeader* self = new (ELeave)CT_DataSIPTimestampHeader();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

CSIPHeaderBase* CT_DataSIPTimestampHeader::GetSIPHeaderBase() const
    {
    return iSIPTimestampHeader;
    }

TAny* CT_DataSIPTimestampHeader::GetObject()
	{
	return iSIPTimestampHeader;
	}

void CT_DataSIPTimestampHeader::SetObjectL(TAny* aAny)
	{
	iSIPTimestampHeader = static_cast<CSIPTimestampHeader*>(aAny);
	}

void CT_DataSIPTimestampHeader::DisownObjectL()
	{
	iSIPTimestampHeader = NULL;
	iIsOwner = EFalse;
	}

TBool CT_DataSIPTimestampHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
	{
	TBool ret = ETrue;

	if ( aCommand==KCmdConstructorL )
		{
		DoCmdConstructorL(aSection);
		}
    else if ( aCommand==KCmdDecodeL )
        {
        DoCmdDecodeL(aSection);
        }
    else if ( aCommand==KCmdTimestamp )
        {
        DoCmdTimestamp(aSection);
        }
    else if ( aCommand==KCmdSetTimestamp )
        {
        DoCmdSetTimestamp(aSection);
        }
    else if ( aCommand==KCmdHasDelay )
        {
        DoCmdHasDelay(aSection);
        }
    else if ( aCommand==KCmdSetDelay )
        {
        DoCmdSetDelay(aSection);
        }
    else if ( aCommand==KCmdDelay )
        {
        DoCmdDelay(aSection);
        }
    else if ( aCommand==KCmdInternalizeValueL )
        {
        DoCmdInternalizeValueL(aSection);
        }
    else if (aCommand==KCmdDestructor)
        {
        DoCmdDestructor(aSection);
        }
    else
        {
        ret = CT_DataSIPHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
        }
	
	return ret;
    }

void CT_DataSIPTimestampHeader::DoCmdConstructorL(const TTEFSectionName& aSection)
	{
	TReal timestamp = 0.0;

	if(!CT_SIPUtil::GetTRealFromConfig(*this, aSection, KFldTimestamp, timestamp) )
	    {
	    ERR_PRINTF2(KLogMissingParameter, &KFldTimestamp);
	    SetBlockResult(EFail);
	    return;
	    }
	
	INFO_PRINTF1(_L("call CSIPTimestampHeader::CSIPTimestampHeader(TReal)"));
	TRAPD(err, iSIPTimestampHeader = new (ELeave) CSIPTimestampHeader(timestamp)); 

    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    else
        {
        iIsOwner = ETrue;
        }
	}

void CT_DataSIPTimestampHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
    {
    TPtrC temp;
    if( !GetStringFromConfig(aSection, KFldValue, temp) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldValue);
        SetBlockResult(EFail);
        }
    else
        {
        TPtrC wrapperName;
        if( !GetStringFromConfig(aSection, KFldSIPTimestampHeader, wrapperName) )
            {
            ERR_PRINTF2(KLogMissingParameter, &KFldSIPTimestampHeader);
            SetBlockResult(EFail);
            }
        else
            {
            TBuf8<KMaxTestExecuteCommandLength> value;
            CnvUtfConverter::ConvertFromUnicodeToUtf8(value, temp);
            INFO_PRINTF1(_L("call CSIPTimestampHeader::DecodeL(const TDesC8&)"));
            CSIPTimestampHeader* ret = NULL;
            TRAPD(err, ret = CSIPTimestampHeader::DecodeL(value));
            
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

void CT_DataSIPTimestampHeader::DoCmdTimestamp(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPTimestampHeader::Timestamp()"));
    TReal ret = iSIPTimestampHeader->Timestamp();
    INFO_PRINTF2(_L("Timestamp = %f"), ret);
    
    TReal expected;
    if( CT_SIPUtil::GetTRealFromConfig(*this, aSection, KFldExpected, expected) )
        {
        if(!CT_SIPUtil::CompareTReal(ret, expected))
            {
            ERR_PRINTF3(KLogNotExpectedValueReal, ret, expected);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPTimestampHeader::DoCmdSetTimestamp(const TTEFSectionName& aSection)
    {
    TReal timestamp;
    if(!CT_SIPUtil::GetTRealFromConfig(*this, aSection, KFldTimestamp, timestamp))
        {        
        ERR_PRINTF2(KLogMissingParameter, &KFldTimestamp());
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPTimestampHeader::SetTimestamp(TReal)"));
        iSIPTimestampHeader->SetTimestamp(timestamp);
        }
    }

void CT_DataSIPTimestampHeader::DoCmdHasDelay(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPTimestampHeader::HasDelay()"));
    TBool ret = iSIPTimestampHeader->HasDelay();
    INFO_PRINTF2(_L("HasDelay = %d"), ret);
    
    TBool expected;
    if( GetBoolFromConfig(aSection, KFldExpected, expected) )
        {
        if(!ret != !expected)
            {
            ERR_PRINTF3(KLogNotExpectedValue, ret, expected);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPTimestampHeader::DoCmdSetDelay(const TTEFSectionName& aSection)
    {
    TReal delay = 0;
    if( CT_SIPUtil::GetTRealFromConfig(*this, aSection, KFldDelay, delay) )
        {
        INFO_PRINTF1(_L("call CSIPTimestampHeader::SetDelay(TReal)"));
        iSIPTimestampHeader->SetDelay(delay);
        }
    else
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldDelay);
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPTimestampHeader::DoCmdDelay(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPTimestampHeader::Delay()"));
    TReal ret = iSIPTimestampHeader->Delay();
    INFO_PRINTF2(_L("Delay = %f"), ret);
    
    TReal expected;
    if(CT_SIPUtil::GetTRealFromConfig(*this, aSection, KFldExpected, expected))
        {
        if(!CT_SIPUtil::CompareTReal(ret, expected))
            {
            ERR_PRINTF3(KLogNotExpectedValueReal, ret, expected);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPTimestampHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
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
        
        INFO_PRINTF1(_L("call CSIPTimestampHeader::InternalizeValueL(RReadStream&)"));
        TRAPD(err, iSIPTimestampHeader = (CSIPTimestampHeader*)CSIPTimestampHeader::InternalizeValueL(readstrm));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        
        CleanupStack::PopAndDestroy(2);
        }
    }

void CT_DataSIPTimestampHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
	{
	INFO_PRINTF1(_L("call CSIPTimestampHeader::~CSIPTimestampHeader()"));
	DestroyData();
	}

void CT_DataSIPTimestampHeader::DestroyData()
	{
	if(iIsOwner)
	    {
	    delete iSIPTimestampHeader;
	    iSIPTimestampHeader = NULL;
	    iIsOwner = EFalse;
	    }
	}

void CT_DataSIPTimestampHeader::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

