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
* This contains CT_DataContentEncodingHeader
*/


#include "t_csipcontentencodingheader.h"
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
_LIT(KFldContentEncodingHeader, "contentencodingheader");
//Fields
_LIT(KFldValue,                 "value");
_LIT(KFldFileName,              "filename");

_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");

_LIT(KFormatFieldNumber, "%S%d");

CT_DataContentEncodingHeader::CT_DataContentEncodingHeader()
:   CT_DataSIPTokenHeaderBase(), iSIPContentEncodingHeader(NULL), iIsOwner(EFalse)
    {
    }

CT_DataContentEncodingHeader::~CT_DataContentEncodingHeader()
	{
	DestroyData();
	}

void CT_DataContentEncodingHeader::ConstructL()
	{
	}

CT_DataContentEncodingHeader* CT_DataContentEncodingHeader::NewL()
    {
    CT_DataContentEncodingHeader* self = new (ELeave)CT_DataContentEncodingHeader();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

CSIPHeaderBase* CT_DataContentEncodingHeader::GetSIPHeaderBase() const
    {
    return iSIPContentEncodingHeader;
    }

CSIPTokenHeaderBase* CT_DataContentEncodingHeader::GetSIPTokenHeaderBase()const
    {
    return iSIPContentEncodingHeader;
    }

TAny* CT_DataContentEncodingHeader::GetObject()
	{
	return iSIPContentEncodingHeader;
	}

void CT_DataContentEncodingHeader::SetObjectL(TAny* aAny)
	{
	iSIPContentEncodingHeader = static_cast<CSIPContentEncodingHeader*>(aAny);
	}

void CT_DataContentEncodingHeader::DisownObjectL()
	{
	iSIPContentEncodingHeader = NULL;
	iIsOwner = EFalse;
	}

TBool CT_DataContentEncodingHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
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

void CT_DataContentEncodingHeader::DoCmdNewL(const TTEFSectionName& aSection)
	{
	RStringF value;
    if (!CT_SIPUtil::GetStringF(*this, aSection, KFldValue, value))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldValue);
        SetBlockResult(EFail);
        }
    else
        {      
        INFO_PRINTF1(_L("call CSIPContentEncodingHeader::NewL(RStringF aValue)"));
        TRAPD(err, iSIPContentEncodingHeader = CSIPContentEncodingHeader::NewL(value)); 
    
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        iIsOwner = err == KErrNone;
        }
	}

void CT_DataContentEncodingHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    RStringF value;
    if (!CT_SIPUtil::GetStringF(*this, aSection, KFldValue, value))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldValue);
        SetBlockResult(EFail);
        } 
    else
        {
        INFO_PRINTF1(_L("call CSIPContentEncodingHeader::NewLC(RStringF aValue)"));
        TRAPD(err, iSIPContentEncodingHeader = CSIPContentEncodingHeader::NewLC(value); CleanupStack::Pop(iSIPContentEncodingHeader)); 
    
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        iIsOwner = err == KErrNone;
        }
    }

void CT_DataContentEncodingHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
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
        INFO_PRINTF1(_L("call CSIPContentEncodingHeader::DecodeL(const TDesC8&)"));
        RPointerArray<CSIPContentEncodingHeader> ret;
        TRAPD(err, ret = CSIPContentEncodingHeader::DecodeL(value));

        if (KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            return;
            }
            
        TInt cnt = ret.Count();
        INFO_PRINTF2(_L("%d CSIPContentEncodingHeader objects got from DecodeL()"), cnt);
        TBool moreData = ETrue;
        TBuf<KMaxTestExecuteNameLength> tempStore;
        TInt index = 1;
        while (moreData && index <= cnt)
            {
            TPtrC name;
            tempStore.Format(KFormatFieldNumber, &KFldContentEncodingHeader, index);
            if (GetStringFromConfig(aSection, tempStore, name))
                {
                SetDataObjectL(name, ret[index - 1]);
                CT_DataContentEncodingHeader* wrapper = (CT_DataContentEncodingHeader*)GetDataWrapperL(name);
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

void CT_DataContentEncodingHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
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
        
        INFO_PRINTF1(_L("call CSIPContentEncodingHeader::InternalizeValueL(RReadStream&)"));
        TRAPD(err, iSIPContentEncodingHeader = (CSIPContentEncodingHeader*)CSIPContentEncodingHeader::InternalizeValueL(readstrm));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        iIsOwner = err == KErrNone;
        CleanupStack::PopAndDestroy(2);
        }
    }

void CT_DataContentEncodingHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
	{
	INFO_PRINTF1(_L("call CSIPContentEncodingHeader::~CSIPContentEncodingHeader()"));
	DestroyData();
	}

void CT_DataContentEncodingHeader::DestroyData()
	{
	if(iIsOwner)
	    {
	    delete iSIPContentEncodingHeader;
	    iSIPContentEncodingHeader = NULL;
	    iIsOwner = EFalse;
	    }
	}

void CT_DataContentEncodingHeader::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

