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
* This contains CT_DataSupportedHeader
*/


#include "t_csipsupportedheader.h"
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
_LIT(KFldSupportedHeader, "supportedheader");
//Fields
_LIT(KFldValue,                 "value");
_LIT(KFldFileName,              "filename");

_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");

_LIT(KFormatFieldNumber, "%S%d");

CT_DataSupportedHeader::CT_DataSupportedHeader()
:   CT_DataSIPTokenHeaderBase(), iSIPSupportedHeader(NULL), iIsOwner(EFalse)
    {
    }

CT_DataSupportedHeader::~CT_DataSupportedHeader()
	{
	DestroyData();
	}

void CT_DataSupportedHeader::ConstructL()
	{
	}

CT_DataSupportedHeader* CT_DataSupportedHeader::NewL()
    {
    CT_DataSupportedHeader* self = new (ELeave)CT_DataSupportedHeader();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

CSIPHeaderBase* CT_DataSupportedHeader::GetSIPHeaderBase() const
    {
    return iSIPSupportedHeader;
    }

CSIPTokenHeaderBase* CT_DataSupportedHeader::GetSIPTokenHeaderBase()const
    {
    return iSIPSupportedHeader;
    }

TAny* CT_DataSupportedHeader::GetObject()
	{
	return iSIPSupportedHeader;
	}

void CT_DataSupportedHeader::SetObjectL(TAny* aAny)
	{
	iSIPSupportedHeader = static_cast<CSIPSupportedHeader*>(aAny);
	}

void CT_DataSupportedHeader::DisownObjectL()
	{
	iSIPSupportedHeader = NULL;
	iIsOwner = EFalse;
	}

TBool CT_DataSupportedHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
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

void CT_DataSupportedHeader::DoCmdNewL(const TTEFSectionName& aSection)
	{
	RStringF value;
    if (!CT_SIPUtil::GetStringF(*this, aSection, KFldValue, value))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldValue);
        SetBlockResult(EFail);
        }
    else
        {      
        INFO_PRINTF1(_L("call CSIPSupportedHeader::NewL(RStringF aValue)"));
        TRAPD(err, iSIPSupportedHeader = CSIPSupportedHeader::NewL(value)); 
    
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        iIsOwner = err == KErrNone;
        }
	}

void CT_DataSupportedHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    RStringF value;
    if (!CT_SIPUtil::GetStringF(*this, aSection, KFldValue, value))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldValue);
        SetBlockResult(EFail);
        } 
    else
        {
        INFO_PRINTF1(_L("call CSIPSupportedHeader::NewLC(RStringF aValue)"));
        TRAPD(err, iSIPSupportedHeader = CSIPSupportedHeader::NewLC(value); CleanupStack::Pop(iSIPSupportedHeader)); 
    
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        iIsOwner = err == KErrNone;
        }
    }

void CT_DataSupportedHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
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
        INFO_PRINTF1(_L("call CSIPSupportedHeader::DecodeL(const TDesC8&)"));
        RPointerArray<CSIPSupportedHeader> ret;
        TRAPD(err, ret = CSIPSupportedHeader::DecodeL(value));

        if (KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            return;
            }
            
        TInt cnt = ret.Count();
        INFO_PRINTF2(_L("%d CSIPSupportedHeader objects got from DecodeL()"), cnt);
        TBool moreData = ETrue;
        TBuf<KMaxTestExecuteNameLength> tempStore;
        TInt index = 1;
        while (moreData && index <= cnt)
            {
            TPtrC name;
            tempStore.Format(KFormatFieldNumber, &KFldSupportedHeader, index);
            if (GetStringFromConfig(aSection, tempStore, name))
                {
                SetDataObjectL(name, ret[index - 1]);
                CT_DataSupportedHeader* wrapper = (CT_DataSupportedHeader*)GetDataWrapperL(name);
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

void CT_DataSupportedHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
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
        
        INFO_PRINTF1(_L("call CSIPSupportedHeader::InternalizeValueL(RReadStream&)"));
        TRAPD(err, iSIPSupportedHeader = (CSIPSupportedHeader*)CSIPSupportedHeader::InternalizeValueL(readstrm));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        iIsOwner = err == KErrNone;
        CleanupStack::PopAndDestroy(2);
        }
    }

void CT_DataSupportedHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
	{
	INFO_PRINTF1(_L("call CSIPSupportedHeader::~CSIPSupportedHeader()"));
	DestroyData();
	}

void CT_DataSupportedHeader::DestroyData()
	{
	if(iIsOwner)
	    {
	    delete iSIPSupportedHeader;
	    iSIPSupportedHeader = NULL;
	    iIsOwner = EFalse;
	    }
	}

void CT_DataSupportedHeader::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

