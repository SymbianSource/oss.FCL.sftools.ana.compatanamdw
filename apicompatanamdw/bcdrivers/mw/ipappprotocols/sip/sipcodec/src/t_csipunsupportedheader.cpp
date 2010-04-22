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
* This contains CT_DataUnsupportedHeader
*/


#include "t_csipunsupportedheader.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <s32file.h>
#include <stdlib.h>

/*@{*/
_LIT(KCmdDestructor,            "~");
_LIT(KCmdNewL,                  "NewL");
_LIT(KCmdNewLC,                 "NewLC");
_LIT(KCmdDecodeL,               "DecodeL");
_LIT(KCmdInternalizeValueL,     "InternalizeValueL");
_LIT(KFldUnsupportedHeader,     "unsupportedheader");
//Fields
_LIT(KFldValue,                 "value");
_LIT(KFldFileName,              "filename");

_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");

_LIT(KFormatFieldNumber, "%S%d");

CT_DataUnsupportedHeader::CT_DataUnsupportedHeader()
:   CT_DataSIPTokenHeaderBase(), iSIPUnsupportedHeader(NULL), iIsOwner(EFalse)
    {
    }

CT_DataUnsupportedHeader::~CT_DataUnsupportedHeader()
	{
	DestroyData();
	}

void CT_DataUnsupportedHeader::ConstructL()
	{
	}

CT_DataUnsupportedHeader* CT_DataUnsupportedHeader::NewL()
    {
    CT_DataUnsupportedHeader* self = new (ELeave)CT_DataUnsupportedHeader();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

CSIPHeaderBase* CT_DataUnsupportedHeader::GetSIPHeaderBase() const
    {
    return iSIPUnsupportedHeader;
    }

CSIPTokenHeaderBase* CT_DataUnsupportedHeader::GetSIPTokenHeaderBase()const
    {
    return iSIPUnsupportedHeader;
    }

TAny* CT_DataUnsupportedHeader::GetObject()
	{
	return iSIPUnsupportedHeader;
	}

void CT_DataUnsupportedHeader::SetObjectL(TAny* aAny)
	{
	iSIPUnsupportedHeader = static_cast<CSIPUnsupportedHeader*>(aAny);
	}

void CT_DataUnsupportedHeader::DisownObjectL()
	{
	iSIPUnsupportedHeader = NULL;
	iIsOwner = EFalse;
	}

TBool CT_DataUnsupportedHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
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
        ret = CT_DataSIPTokenHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
        }
	
	return ret;
    }

void CT_DataUnsupportedHeader::DoCmdNewL(const TTEFSectionName& aSection)
	{
	RStringF value;
    if (!CT_SIPUtil::GetStringF(*this, aSection, KFldValue, value))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldValue);
        SetBlockResult(EFail);
        }
    else
        {      
        INFO_PRINTF1(_L("call CSIPUnsupportedHeader::NewL(RStringF aValue)"));
        TRAPD(err, iSIPUnsupportedHeader = CSIPUnsupportedHeader::NewL(value)); 
    
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        iIsOwner = err == KErrNone;
        }
	}

void CT_DataUnsupportedHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    RStringF value;
    if (!CT_SIPUtil::GetStringF(*this, aSection, KFldValue, value))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldValue);
        SetBlockResult(EFail);
        } 
    else
        {
        INFO_PRINTF1(_L("call CSIPUnsupportedHeader::NewLC(RStringF aValue)"));
        TRAPD(err, iSIPUnsupportedHeader = CSIPUnsupportedHeader::NewLC(value); CleanupStack::Pop(iSIPUnsupportedHeader)); 
    
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        iIsOwner = err == KErrNone;
        }
    }

void CT_DataUnsupportedHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
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
        INFO_PRINTF1(_L("call CSIPUnsupportedHeader::DecodeL(const TDesC8&)"));
        RPointerArray<CSIPUnsupportedHeader> ret;
        TRAPD(err, ret = CSIPUnsupportedHeader::DecodeL(value));

        if (KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            return;
            }
            
        TInt cnt = ret.Count();
        INFO_PRINTF2(_L("%d CSIPUnsupportedHeader objects got from DecodeL()"), cnt);
        TBool moreData = ETrue;
        TBuf<KMaxTestExecuteNameLength> tempStore;
        TInt index = 1;
        while (moreData && index <= cnt)
            {
            TPtrC name;
            tempStore.Format(KFormatFieldNumber, &KFldUnsupportedHeader, index);
            if (GetStringFromConfig(aSection, tempStore, name))
                {
                SetDataObjectL(name, ret[index - 1]);
                CT_DataUnsupportedHeader* wrapper = (CT_DataUnsupportedHeader*)GetDataWrapperL(name);
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

void CT_DataUnsupportedHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
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
        
        INFO_PRINTF1(_L("call CSIPUnsupportedHeader::InternalizeValueL(RReadStream&)"));
        TRAPD(err, iSIPUnsupportedHeader = (CSIPUnsupportedHeader*)CSIPUnsupportedHeader::InternalizeValueL(readstrm));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        iIsOwner = err == KErrNone;
        CleanupStack::PopAndDestroy(2);
        }
    }

void CT_DataUnsupportedHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
	{
	INFO_PRINTF1(_L("call CSIPUnsupportedHeader::~CSIPUnsupportedHeader()"));
	DestroyData();
	}

void CT_DataUnsupportedHeader::DestroyData()
	{
	if(iIsOwner)
	    {
	    delete iSIPUnsupportedHeader;
	    iSIPUnsupportedHeader = NULL;
	    iIsOwner = EFalse;
	    }
	}

void CT_DataUnsupportedHeader::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

