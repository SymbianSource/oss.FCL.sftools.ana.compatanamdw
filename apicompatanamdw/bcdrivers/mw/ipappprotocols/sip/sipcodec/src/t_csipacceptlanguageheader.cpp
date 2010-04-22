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
* This contains CT_DataSIPAcceptLanguageHeader
*/


#include "t_csipacceptlanguageheader.h"
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
_LIT(KCmdInternalizeValueL,     "InternalizeValueL");
_LIT(KCmdLanguageRange,         "LanguageRange");
_LIT(KCmdSetLanguageRangeL,     "SetLanguageRangeL");
_LIT(KCmdQParameter,            "QParameter");
_LIT(KCmdSetQParameterL,        "SetQParameterL");
//Fields
_LIT(KFldValue,                 "value");
_LIT(KFldAcceptLanguageHeader,  "acceptlanguageheader");
_LIT(KFldExpected,              "expected");
_LIT(KFldFileName,              "filename");
_LIT(KFldLanguageRange,         "LanguageRange");
_LIT(KFldQParameter,            "QParameter");


_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");
_LIT(KLogNotExpectedValueReal,  "Not expected value, actual=%f, expect=%f");

_LIT(KFormatFieldNumber, "%S%d");

CT_DataSIPAcceptLanguageHeader::CT_DataSIPAcceptLanguageHeader()
:   CT_DataSIPParameterHeaderBase(), iSIPAcceptLanguageHeader(NULL), iIsOwner(EFalse)
    {
    }

CT_DataSIPAcceptLanguageHeader::~CT_DataSIPAcceptLanguageHeader()
	{
	DestroyData();
	}

void CT_DataSIPAcceptLanguageHeader::ConstructL()
	{
	}

CT_DataSIPAcceptLanguageHeader* CT_DataSIPAcceptLanguageHeader::NewL()
    {
    CT_DataSIPAcceptLanguageHeader* self = new (ELeave)CT_DataSIPAcceptLanguageHeader();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

CSIPHeaderBase* CT_DataSIPAcceptLanguageHeader::GetSIPHeaderBase() const
    {
    return iSIPAcceptLanguageHeader;
    }

TAny* CT_DataSIPAcceptLanguageHeader::GetObject()
	{
	return iSIPAcceptLanguageHeader;
	}

void CT_DataSIPAcceptLanguageHeader::SetObjectL(TAny* aAny)
	{
	iSIPAcceptLanguageHeader = static_cast<CSIPAcceptLanguageHeader*>(aAny);
	}

void CT_DataSIPAcceptLanguageHeader::DisownObjectL()
	{
	iSIPAcceptLanguageHeader = NULL;
	iIsOwner = EFalse;
	}

TBool CT_DataSIPAcceptLanguageHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
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
     else if (aCommand==KCmdLanguageRange)
        {
        DoCmdLanguageRange(aSection); 
        }
     else if (aCommand==KCmdSetLanguageRangeL)
        {
        DoCmdSetLanguageRangeL(aSection);
        }
     else if (aCommand==KCmdQParameter)
        {
        DoCmdQParameter(aSection);
        }
     else if (aCommand==KCmdSetQParameterL)
        {
        DoCmdSetQParameterL(aSection);
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

void CT_DataSIPAcceptLanguageHeader::DoCmdNewL(const TTEFSectionName& aSection)
	{
	TPtrC language;
    if( !GetStringFromConfig(aSection, KFldLanguageRange, language) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldLanguageRange);        
        SetBlockResult(EFail);
        }   
    else
        {
        TBuf8<KMaxTestExecuteCommandLength> lan;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(lan, language);
        
        INFO_PRINTF1(_L("call CSIPAcceptLanguageHeader::NewL()"));
        TRAPD(err, iSIPAcceptLanguageHeader = CSIPAcceptLanguageHeader::NewL(lan)); 
    
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        iIsOwner = err == KErrNone;
        }
	}

void CT_DataSIPAcceptLanguageHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    TPtrC language;
    if( !GetStringFromConfig(aSection, KFldLanguageRange, language) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldLanguageRange);        
        SetBlockResult(EFail);
        }  
    else
        {
        TBuf8<KMaxTestExecuteCommandLength> lan;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(lan, language);
        
        INFO_PRINTF1(_L("call CSIPAcceptLanguageHeader::NewLC()"));
        TRAPD(err, iSIPAcceptLanguageHeader = CSIPAcceptLanguageHeader::NewLC(lan); CleanupStack::Pop(iSIPAcceptLanguageHeader)); 
    
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        iIsOwner = err == KErrNone;
        }
    }

void CT_DataSIPAcceptLanguageHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
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
        INFO_PRINTF1(_L("call CSIPAcceptLanguageHeader::DecodeL(const TDesC8&)"));
        RPointerArray<CSIPAcceptLanguageHeader> ret;
        TRAPD(err, ret = CSIPAcceptLanguageHeader::DecodeL(value));

        if (KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            return;
            }

        TInt cnt = ret.Count();
        INFO_PRINTF2(_L("%d CSIPAcceptLanguageHeader objects got from DecodeL()"), cnt);
        TBool moreData = ETrue;
        TBuf<KMaxTestExecuteNameLength> tempStore;
        TInt index = 1;
        while (moreData && index <= cnt)
            {
            TPtrC name;
            tempStore.Format(KFormatFieldNumber, &KFldAcceptLanguageHeader, index);
            if (GetStringFromConfig(aSection, tempStore, name))
                {
                SetDataObjectL(name, ret[index - 1]);
                CT_DataSIPAcceptLanguageHeader* wrapper = (CT_DataSIPAcceptLanguageHeader*)GetDataWrapperL(name);
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


void CT_DataSIPAcceptLanguageHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
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
        
        INFO_PRINTF1(_L("call CSIPAcceptLanguageHeader::InternalizeValueL(RReadStream&)"));
        TRAPD(err, iSIPAcceptLanguageHeader = (CSIPAcceptLanguageHeader*)CSIPAcceptLanguageHeader::InternalizeValueL(readstrm));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        iIsOwner = err == KErrNone;
        CleanupStack::PopAndDestroy(2);
        }
    }

void CT_DataSIPAcceptLanguageHeader::DoCmdLanguageRange(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPAcceptLanguageHeader::LanguageRange()"));
    
    const TDesC8& language = iSIPAcceptLanguageHeader->LanguageRange();
    
    TBuf<KMaxTestExecuteCommandLength> str;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(str, language);
    INFO_PRINTF2(_L("The actual language-range is: %S "), &str);
    
    TPtrC expected;
    if(GetStringFromConfig(aSection, KFldExpected, expected))
        {
        if(expected != str)
            {
            ERR_PRINTF2(_L("The expected language-range is: %S"), &expected);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPAcceptLanguageHeader::DoCmdSetLanguageRangeL(const TTEFSectionName& aSection)
    {
    TPtrC str;
    if(!GetStringFromConfig(aSection, KFldLanguageRange, str))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldLanguageRange());
        SetBlockResult(EFail);
        return;
        }
    
    TBuf8<KMaxTestExecuteCommandLength> language;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(language, str);
    
    INFO_PRINTF1(_L("call CSIPAcceptLanguageHeader::SetLanguageRangeL(const TDesC8 &)"));
    
    TRAPD(err, iSIPAcceptLanguageHeader->SetLanguageRangeL(language));
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }       
    }

void CT_DataSIPAcceptLanguageHeader::DoCmdQParameter(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPAcceptLanguageHeader::QParameter()"));
    
    TReal ret = iSIPAcceptLanguageHeader->QParameter();
    INFO_PRINTF2(_L("q Parameter = %f"), ret);
    
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

void CT_DataSIPAcceptLanguageHeader::DoCmdSetQParameterL(const TTEFSectionName& aSection)
    {
    TReal qParameter = 0;
    if( CT_SIPUtil::GetTRealFromConfig(*this, aSection, KFldQParameter, qParameter) )
        {
        INFO_PRINTF1(_L("call CSIPAcceptLanguageHeader::SetQParameterL(TReal)"));
        TRAPD(err,iSIPAcceptLanguageHeader->SetQParameterL(qParameter));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }   
        }
    else
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldQParameter);
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPAcceptLanguageHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
	{
	INFO_PRINTF1(_L("call CSIPAcceptLanguageHeader::~CSIPAcceptLanguageHeader()"));
	DestroyData();
	}

void CT_DataSIPAcceptLanguageHeader::DestroyData()
	{
	if(iIsOwner)
	    {
	    delete iSIPAcceptLanguageHeader;
	    iSIPAcceptLanguageHeader = NULL;
	    iIsOwner = EFalse;
	    }
	}

void CT_DataSIPAcceptLanguageHeader::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

