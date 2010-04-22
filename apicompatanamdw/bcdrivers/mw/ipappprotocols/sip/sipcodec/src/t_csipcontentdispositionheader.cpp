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
* This contains CT_DataSIPContentDispositionHeader
*/


#include "t_csipcontentdispositionheader.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <s32file.h>

/*@{*/
_LIT(KCmdDestructor,            "~");
_LIT(KCmdNewL,                  "NewL");
_LIT(KCmdNewLC,                 "NewLC");
_LIT(KCmdDecodeL,               "DecodeL");
_LIT(KCmdDispType,              "DispType");
_LIT(KCmdSetDispType,           "SetDispTypeL");
_LIT(KCmdInternalizeValueL,     "InternalizeValueL");

//Fields
_LIT(KFldValue,                 "value");
_LIT(KFldType,                  "type");
_LIT(KFldExpected,              "expected");
_LIT(KFldFileName,              "filename");


_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");
_LIT(KLogNotExpectedValue,      "Not expected value, actual=%S, expect=%S");


CT_DataSIPContentDispositionHeader::CT_DataSIPContentDispositionHeader()
:   CT_DataSIPParameterHeaderBase(), iSIPContentDispositionHeader(NULL), iIsOwner(EFalse)
    {
    }

CT_DataSIPContentDispositionHeader::~CT_DataSIPContentDispositionHeader()
	{
	DestroyData();
	}

void CT_DataSIPContentDispositionHeader::ConstructL()
	{
	}

CT_DataSIPContentDispositionHeader* CT_DataSIPContentDispositionHeader::NewL()
    {
	CT_DataSIPContentDispositionHeader* self = new (ELeave)CT_DataSIPContentDispositionHeader();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

CSIPHeaderBase* CT_DataSIPContentDispositionHeader::GetSIPHeaderBase() const
    {
    return iSIPContentDispositionHeader;
    }

TAny* CT_DataSIPContentDispositionHeader::GetObject()
	{
	return iSIPContentDispositionHeader;
	}

void CT_DataSIPContentDispositionHeader::SetObjectL(TAny* aAny)
	{
	iSIPContentDispositionHeader = static_cast<CSIPContentDispositionHeader*>(aAny);
	}

void CT_DataSIPContentDispositionHeader::DisownObjectL()
	{
	iSIPContentDispositionHeader = NULL;
	iIsOwner = EFalse;
	}

TBool CT_DataSIPContentDispositionHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
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
    else if ( aCommand==KCmdDispType )
        {
        DoCmdDispType(aSection);
        }
    else if ( aCommand==KCmdSetDispType )
        {
        DoCmdSetDispTypeL(aSection);
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

void CT_DataSIPContentDispositionHeader::DoCmdNewL(const TTEFSectionName& aSection)
	{
	TPtrC value;
	if (!GetStringFromConfig(aSection, KFldValue, value))
	    {
	    ERR_PRINTF2(KLogMissingParameter, &KFldValue);
	    SetBlockResult(EFail);
	    return;
	    }
	
	TBuf8<KMaxTestExecuteCommandLength> value8;
	CnvUtfConverter::ConvertFromUnicodeToUtf8(value8, value);
	INFO_PRINTF1(_L("call CSIPContentDispositionHeader::NewL(const TDesC8&)"));
	TRAPD(err, iSIPContentDispositionHeader = CSIPContentDispositionHeader::NewL(value8)); 

    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    iIsOwner = err == KErrNone;
	}

void CT_DataSIPContentDispositionHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    TPtrC value;
    if (!GetStringFromConfig(aSection, KFldValue, value))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldValue);
        SetBlockResult(EFail);
        return;
        }
    
    TBuf8<KMaxTestExecuteCommandLength> value8;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(value8, value);
    INFO_PRINTF1(_L("call CSIPContentDispositionHeader::NewLC(const TDesC8&)"));
    TRAPD(err, iSIPContentDispositionHeader = CSIPContentDispositionHeader::NewLC(value8); CleanupStack::Pop(iSIPContentDispositionHeader)); 

    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    iIsOwner = err == KErrNone;
    }

void CT_DataSIPContentDispositionHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
    {
    TPtrC temp;
    if (!GetStringFromConfig(aSection, KFldValue, temp))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldValue);
        SetBlockResult(EFail);
        return;
        }

    TBuf8<KMaxTestExecuteCommandLength> value;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(value, temp);
    INFO_PRINTF1(_L("call CSIPContentDispositionHeader::DecodeL(const TDesC8&)"));
    TRAPD(err, iSIPContentDispositionHeader = CSIPContentDispositionHeader::DecodeL(value));

    if (KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        return;
        }
    iIsOwner = err == KErrNone;
    }

void CT_DataSIPContentDispositionHeader::DoCmdDispType(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPContentDispositionHeader::DispType()"));
    const TDesC8& actual8 = iSIPContentDispositionHeader->DispType();
    TBuf<KMaxTestExecuteNameLength> actual;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(actual, actual8);
    INFO_PRINTF2(_L("DispType() = %S"), &actual);
    
    TPtrC expected;
    if(GetStringFromConfig(aSection, KFldExpected, expected) )
        {
        if(actual.Compare(expected) != 0)
            {
            ERR_PRINTF3(KLogNotExpectedValue, &actual, &expected);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPContentDispositionHeader::DoCmdSetDispTypeL(const TTEFSectionName& aSection)
    {
    TPtrC type;
    if(!GetStringFromConfig(aSection, KFldType, type) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldType);
        SetBlockResult(EFail);
        return;
        }
    
    TBuf8<KMaxTestExecuteNameLength> type8;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(type8, type);
    INFO_PRINTF1(_L("call CSIPContentDispositionHeader::SetDispTypeL(const TDesC8&)"));
    TRAPD(err, iSIPContentDispositionHeader->SetDispTypeL(type8));
    if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void CT_DataSIPContentDispositionHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
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
        
        INFO_PRINTF1(_L("call CSIPContentDispositionHeader::InternalizeValueL(RReadStream&)"));
        TRAPD(err, iSIPContentDispositionHeader = (CSIPContentDispositionHeader*)CSIPContentDispositionHeader::InternalizeValueL(readstrm));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        iIsOwner = err == KErrNone;
        CleanupStack::PopAndDestroy(2);
        }
    }

void CT_DataSIPContentDispositionHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
	{
	INFO_PRINTF1(_L("call CSIPContentDispositionHeader::~CSIPContentDispositionHeader()"));
	DestroyData();
	}

void CT_DataSIPContentDispositionHeader::DestroyData()
	{
	if(iIsOwner)
	    {
	    delete iSIPContentDispositionHeader;
	    iSIPContentDispositionHeader = NULL;
	    iIsOwner = EFalse;
	    }
	}

void CT_DataSIPContentDispositionHeader::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

