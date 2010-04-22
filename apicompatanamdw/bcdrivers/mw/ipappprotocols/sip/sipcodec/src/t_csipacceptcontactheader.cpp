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
* This contains CT_DataSIPAcceptContactHeader
*/


#include "t_csipacceptcontactheader.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <s32file.h>
#include <sipcseqheader.h>
#include <stdlib.h>

/*@{*/
_LIT(KCmdDestructor,            "~");
_LIT(KCmdNewL,                  "NewL");
_LIT(KCmdNewLC,                 "NewLC");
_LIT(KCmdDecodeL,               "DecodeL");
_LIT(KCmdCompare,               "==");
_LIT(KCmdInternalizeValueL,     "InternalizeValueL");

//Fields
_LIT(KFldValue,                 "value");
_LIT(KFldAcceptContactHeader,   "acceptcontactheader");
_LIT(KFldExpected,              "expected");
_LIT(KFldFileName,              "filename");


_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");
_LIT(KLogNotExpectedValue,      "Not expected value, actual=%d, expect=%d");

_LIT(KFormatFieldNumber, "%S%d");

CT_DataSIPAcceptContactHeader::CT_DataSIPAcceptContactHeader()
:   CT_DataSIPParameterHeaderBase(), iSIPAcceptContactHeader(NULL), iIsOwner(EFalse)
    {
    }

CT_DataSIPAcceptContactHeader::~CT_DataSIPAcceptContactHeader()
	{
	DestroyData();
	}

void CT_DataSIPAcceptContactHeader::ConstructL()
	{
	}

CT_DataSIPAcceptContactHeader* CT_DataSIPAcceptContactHeader::NewL()
    {
	CT_DataSIPAcceptContactHeader* self = new (ELeave)CT_DataSIPAcceptContactHeader();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

CSIPHeaderBase* CT_DataSIPAcceptContactHeader::GetSIPHeaderBase() const
    {
    return iSIPAcceptContactHeader;
    }

TAny* CT_DataSIPAcceptContactHeader::GetObject()
	{
	return iSIPAcceptContactHeader;
	}

void CT_DataSIPAcceptContactHeader::SetObjectL(TAny* aAny)
	{
	iSIPAcceptContactHeader = static_cast<CSIPAcceptContactHeader*>(aAny);
	}

void CT_DataSIPAcceptContactHeader::DisownObjectL()
	{
	iSIPAcceptContactHeader = NULL;
	iIsOwner = EFalse;
	}

TBool CT_DataSIPAcceptContactHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
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
    else if ( aCommand==KCmdCompare )
        {
        DoCmdCompare(aSection);
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
        ret = CT_DataSIPParameterHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
        }
	
	return ret;
    }

void CT_DataSIPAcceptContactHeader::DoCmdNewL(const TTEFSectionName& /*aSection*/)
	{
	INFO_PRINTF1(_L("call CSIPAcceptContactHeader::NewL()"));
	TRAPD(err, iSIPAcceptContactHeader = CSIPAcceptContactHeader::NewL()); 

    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    iIsOwner = err == KErrNone;
	}

void CT_DataSIPAcceptContactHeader::DoCmdNewLC(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPAcceptContactHeader::NewLC()"));
    TRAPD(err, iSIPAcceptContactHeader = CSIPAcceptContactHeader::NewLC(); CleanupStack::Pop(iSIPAcceptContactHeader)); 

    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    iIsOwner = err == KErrNone;
    }

void CT_DataSIPAcceptContactHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
    {
    TPtrC temp;
    if( !GetStringFromConfig(aSection, KFldValue, temp) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldValue);
        SetBlockResult(EFail);
        }
    else
        {
        TBuf8<KMaxTestExecuteCommandLength> value;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(value, temp);
        INFO_PRINTF1(_L("call CSIPAcceptContactHeader::DecodeL(const TDesC8&)"));
        RPointerArray<CSIPAcceptContactHeader> ret;
        TRAPD(err, ret = CSIPAcceptContactHeader::DecodeL(value));

        if (KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            return;
            }

        TInt cnt = ret.Count();
        INFO_PRINTF2(_L("%d CSIPAcceptContactHeader objects got from DecodeL()"), cnt);
        TBool moreData = ETrue;
        TBuf<KMaxTestExecuteNameLength> tempStore;
        TInt index = 1;
        while (moreData && index <= cnt)
            {
            TPtrC name;
            tempStore.Format(KFormatFieldNumber, &KFldAcceptContactHeader, index);
            if (GetStringFromConfig(aSection, tempStore, name))
                {
                SetDataObjectL(name, ret[index - 1]);
                CT_DataSIPAcceptContactHeader* wrapper = (CT_DataSIPAcceptContactHeader*)GetDataWrapperL(name);
                wrapper->SetIsOwner(ETrue);
                ++index;
                }
            else
                {
                moreData = EFalse;
                }
            }
        // Destroy unstored ones.
        for (--index; index < cnt; ++index)
            {
            delete ret[index];
            }
        ret.Close();
        }
    }

void CT_DataSIPAcceptContactHeader::DoCmdCompare(const TTEFSectionName& aSection)
    {
    CSIPHeaderBase* hdr = NULL;
    if (!CT_SIPUtil::GetSIPHeaderBaseL(*this, aSection, KFldAcceptContactHeader, hdr))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldAcceptContactHeader);
        SetBlockResult(EFail);
        return;
        }
    
    INFO_PRINTF1(_L("call CSIPAcceptContactHeader::operator ==(const CSIPAcceptContactHeader &)"));
    TBool ret = *iSIPAcceptContactHeader == *(CSIPAcceptContactHeader*)hdr;
    INFO_PRINTF2(_L("operator ==() = %d"), ret);
    
    TBool expected;
    if(GetBoolFromConfig(aSection, KFldExpected, expected) )
        {
        if(!ret != !expected)
            {
            ERR_PRINTF3(KLogNotExpectedValue, ret, expected);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPAcceptContactHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
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
        
        INFO_PRINTF1(_L("call CSIPAcceptContactHeader::InternalizeValueL(RReadStream&)"));
        TRAPD(err, iSIPAcceptContactHeader = (CSIPAcceptContactHeader*)CSIPAcceptContactHeader::InternalizeValueL(readstrm));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        iIsOwner = err == KErrNone;
        CleanupStack::PopAndDestroy(2);
        }
    }

void CT_DataSIPAcceptContactHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
	{
	INFO_PRINTF1(_L("call CSIPAcceptContactHeader::~CSIPAcceptContactHeader()"));
	DestroyData();
	}

void CT_DataSIPAcceptContactHeader::DestroyData()
	{
	if(iIsOwner)
	    {
	    delete iSIPAcceptContactHeader;
	    iSIPAcceptContactHeader = NULL;
	    iIsOwner = EFalse;
	    }
	}

void CT_DataSIPAcceptContactHeader::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

