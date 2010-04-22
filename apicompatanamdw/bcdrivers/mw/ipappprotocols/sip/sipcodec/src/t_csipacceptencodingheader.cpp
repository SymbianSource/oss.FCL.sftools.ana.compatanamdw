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
* This contains CT_DataSIPAcceptEncodingHeader
*/


#include "t_csipacceptencodingheader.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <s32file.h>
#include <stdlib.h>

/*@{*/
_LIT(KCmdDestructor,            "~");
_LIT(KCmdNewL,                  "NewL");
_LIT(KCmdNewLC,                 "NewLC");
_LIT(KCmdDecodeL,               "DecodeL");
_LIT(KCmdCodings,               "Codings");
_LIT(KCmdSetCodingsL,           "SetCodingsL");
_LIT(KCmdQParameter,            "QParameter");
_LIT(KCmdSetQParameterL,        "SetQParameterL");
_LIT(KCmdInternalizeValueL,     "InternalizeValueL");

//Fields
_LIT(KFldCodings,               "codings");
_LIT(KFldAcceptEncodingHeader,  "sipacceptencodingheader");
_LIT(KFldExpected,              "expected");
_LIT(KFldFileName,              "filename");
_LIT(KFldValue,                 "value");
_LIT(KFldQParameter,            "qparameter");

_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");
_LIT(KLogNotExpectedValue,      "Not expected value, actual=%d, expect=%d");
_LIT(KLogNotExpectedValueReal,  "Not expected value, actual=%f, expect=%f");
_LIT(KLogNotExpectedValueString,  "Not expected value, actual=%S, expect=%S");

_LIT(KFormatFieldNumber, "%S%d");

CT_DataSIPAcceptEncodingHeader::CT_DataSIPAcceptEncodingHeader()
:   CT_DataSIPParameterHeaderBase(), iSIPAcceptEncodingHeader(NULL), iIsOwner(EFalse)
    {
    }

CT_DataSIPAcceptEncodingHeader::~CT_DataSIPAcceptEncodingHeader()
	{
	DestroyData();
	}

void CT_DataSIPAcceptEncodingHeader::ConstructL()
	{
	}

CT_DataSIPAcceptEncodingHeader* CT_DataSIPAcceptEncodingHeader::NewL()
    {
	CT_DataSIPAcceptEncodingHeader* self = new (ELeave)CT_DataSIPAcceptEncodingHeader();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

CSIPHeaderBase* CT_DataSIPAcceptEncodingHeader::GetSIPHeaderBase() const
    {
    return iSIPAcceptEncodingHeader;
    }

TAny* CT_DataSIPAcceptEncodingHeader::GetObject()
	{
	return iSIPAcceptEncodingHeader;
	}

void CT_DataSIPAcceptEncodingHeader::SetObjectL(TAny* aAny)
	{
	iSIPAcceptEncodingHeader = static_cast<CSIPAcceptEncodingHeader*>(aAny);
	}

void CT_DataSIPAcceptEncodingHeader::DisownObjectL()
	{
	iSIPAcceptEncodingHeader = NULL;
	iIsOwner = EFalse;
	}

TBool CT_DataSIPAcceptEncodingHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
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
    else if ( aCommand==KCmdCodings )
        {
        DoCmdCodings(aSection);
        }
    else if ( aCommand==KCmdSetCodingsL )
        {
        DoCmdSetCodingsL(aSection);
        }
    else if ( aCommand==KCmdQParameter )
        {
        DoCmdQParameter(aSection);
        }
    else if ( aCommand==KCmdSetQParameterL )
        {
        DoCmdSetQParameterL(aSection);
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

void CT_DataSIPAcceptEncodingHeader::DoCmdNewL(const TTEFSectionName& aSection)
	{
	TPtrC temp;
    if( !GetStringFromConfig(aSection, KFldCodings, temp) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldCodings);
        SetBlockResult(EFail);
        return;
        }

	TBuf8<KMaxTestExecuteCommandLength> codings;
	CnvUtfConverter::ConvertFromUnicodeToUtf8(codings, temp);
	INFO_PRINTF1(_L("call CSIPAcceptEncodingHeader::NewL(const TDesC8&)"));
	TRAPD(err, iSIPAcceptEncodingHeader = CSIPAcceptEncodingHeader::NewL(codings)); 

    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    iIsOwner = err == KErrNone;
	}

void CT_DataSIPAcceptEncodingHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {

    TPtrC temp;
    if( !GetStringFromConfig(aSection, KFldCodings, temp) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldCodings);
        SetBlockResult(EFail);
        return;
        }

    TBuf8<KMaxTestExecuteCommandLength> codings;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(codings, temp);
    INFO_PRINTF1(_L("call CSIPAcceptEncodingHeader::NewL(const TDesC8&)"));
    TRAPD(err, iSIPAcceptEncodingHeader = CSIPAcceptEncodingHeader::NewLC(codings); CleanupStack::Pop(iSIPAcceptEncodingHeader)); 

    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    iIsOwner = err == KErrNone;
    }

void CT_DataSIPAcceptEncodingHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
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
        INFO_PRINTF1(_L("call CSIPAcceptEncodingHeader::DecodeL(const TDesC8&)"));
        RPointerArray<CSIPAcceptEncodingHeader> ret;
        TRAPD(err, ret = CSIPAcceptEncodingHeader::DecodeL(value));

        if (KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            return;
            }
        
        TInt cnt = ret.Count();
        INFO_PRINTF2(_L("%d CSIPAcceptEncodingHeader objects got from DecodeL()"), cnt);
        TBool moreData = ETrue;
        TBuf<KMaxTestExecuteNameLength> tempStore;
        TInt index = 1;
        while (moreData && index <= cnt)
            {
            TPtrC name;
            tempStore.Format(KFormatFieldNumber, &KFldAcceptEncodingHeader, index);
            if (GetStringFromConfig(aSection, tempStore, name))
                {
                SetDataObjectL(name, ret[index - 1]);
                CT_DataSIPAcceptEncodingHeader* wrapper = (CT_DataSIPAcceptEncodingHeader*)GetDataWrapperL(name);
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

void CT_DataSIPAcceptEncodingHeader::DoCmdCodings(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call const TDesC8& CSIPAcceptEncodingHeader::Codings()"));    //TBuf8<KMaxTestExecuteCommandLength> actual = iSIPAcceptEncodingHeader->Codings();
    TBuf<KMaxTestExecuteCommandLength> actual;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(actual, iSIPAcceptEncodingHeader->Codings());
    INFO_PRINTF2(_L("Actual codings: %S"), &actual);
    
    TPtrC expected;
    if (GetStringFromConfig(aSection, KFldExpected, expected))
        {
        if(actual != expected)
            {
            ERR_PRINTF3(KLogNotExpectedValueString, &actual, &expected);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPAcceptEncodingHeader::DoCmdSetCodingsL(const TTEFSectionName& aSection)
    {
    TPtrC temp;
    if (!GetStringFromConfig(aSection, KFldCodings, temp))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldCodings);
        SetBlockResult(EFail);
        return;
        }
    
    TBuf8<KMaxTestExecuteCommandLength> codings;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(codings, temp);
    INFO_PRINTF1(_L("call CSIPAcceptEncodingHeader::SetCodingsL(const TDesC8&)"));
    TRAPD(err, iSIPAcceptEncodingHeader->SetCodingsL(codings)); 
    if (KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        return;
        }
    }

void CT_DataSIPAcceptEncodingHeader::DoCmdQParameter(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPAcceptEncodingHeader::QParameter()"));
    TReal ret = iSIPAcceptEncodingHeader->QParameter();
    INFO_PRINTF2(_L("QParameter = %f"), ret);
    
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

void CT_DataSIPAcceptEncodingHeader::DoCmdSetQParameterL(const TTEFSectionName& aSection)
    {
    TReal qParameter;
    if(!CT_SIPUtil::GetTRealFromConfig(*this, aSection, KFldQParameter, qParameter))
        {        
        ERR_PRINTF2(KLogMissingParameter, &KFldQParameter);
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPAcceptEncodingHeader::SetQParameter(TReal)"));
        iSIPAcceptEncodingHeader->SetQParameterL(qParameter);
        }
    }

void CT_DataSIPAcceptEncodingHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
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
        
        INFO_PRINTF1(_L("call CSIPAcceptEncodingHeader::InternalizeValueL(RReadStream&)"));
        TRAPD(err, iSIPAcceptEncodingHeader = (CSIPAcceptEncodingHeader*)CSIPAcceptEncodingHeader::InternalizeValueL(readstrm));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        iIsOwner = err == KErrNone;
        CleanupStack::PopAndDestroy(2);
        }
    }

void CT_DataSIPAcceptEncodingHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
	{
	INFO_PRINTF1(_L("call CSIPAcceptEncodingHeader::~CSIPAcceptEncodingHeader()"));
	DestroyData();
	}

void CT_DataSIPAcceptEncodingHeader::DestroyData()
	{
	if(iIsOwner && (iSIPAcceptEncodingHeader != NULL))
	    {
	    delete iSIPAcceptEncodingHeader;
	    iSIPAcceptEncodingHeader = NULL;
	    iIsOwner = EFalse;
	    }
	}

void CT_DataSIPAcceptEncodingHeader::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

