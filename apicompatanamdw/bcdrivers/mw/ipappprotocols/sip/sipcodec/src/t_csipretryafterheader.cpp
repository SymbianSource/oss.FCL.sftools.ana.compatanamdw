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
* This contains CT_DataSIPRetryAfterHeader
*/


#include "t_csipretryafterheader.h"
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
_LIT(KCmdComment,               "Comment");
_LIT(KCmdSetDurationParamL,     "SetDurationParamL");
_LIT(KCmdDurationParam,         "DurationParam");
_LIT(KCmdRetryAfter,            "RetryAfter");
_LIT(KCmdSetRetryAfter,         "SetRetryAfter");
//Fields
_LIT(KFldValue,                 "value");
_LIT(KFldExpected,              "expected");
_LIT(KFldFileName,              "filename");
_LIT(KFldRetryAfter,            "RetryAfter");
_LIT(KFldDurationParam,         "DurationParam");


_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");
_LIT(KLogNotExpectedValue,      "Not expected value, actual=%d, expect=%d");


CT_DataSIPRetryAfterHeader::CT_DataSIPRetryAfterHeader()
:   CT_DataSIPParameterHeaderBase(), iSIPRetryAfterHeader(NULL), iIsOwner(EFalse)
    {
    }

CT_DataSIPRetryAfterHeader::~CT_DataSIPRetryAfterHeader()
	{
	DestroyData();
	}

void CT_DataSIPRetryAfterHeader::ConstructL()
	{
	}

CT_DataSIPRetryAfterHeader* CT_DataSIPRetryAfterHeader::NewL()
    {
    CT_DataSIPRetryAfterHeader* self = new (ELeave)CT_DataSIPRetryAfterHeader();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

CSIPHeaderBase* CT_DataSIPRetryAfterHeader::GetSIPHeaderBase() const
    {
    return iSIPRetryAfterHeader;
    }

TAny* CT_DataSIPRetryAfterHeader::GetObject()
	{
	return iSIPRetryAfterHeader;
	}

void CT_DataSIPRetryAfterHeader::SetObjectL(TAny* aAny)
	{
	iSIPRetryAfterHeader = static_cast<CSIPRetryAfterHeader*>(aAny);
	}

void CT_DataSIPRetryAfterHeader::DisownObjectL()
	{
	iSIPRetryAfterHeader = NULL;
	iIsOwner = EFalse;
	}

TBool CT_DataSIPRetryAfterHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
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
     else if (aCommand==KCmdRetryAfter)
        {
        DoCmdRetryAfter(aSection); 
        }
     else if (aCommand==KCmdSetRetryAfter)
        {
        DoCmdSetRetryAfter(aSection);
        }
     else if (aCommand==KCmdComment)
        {
        DoCmdComment(aSection);
        }
     else if (aCommand==KCmdSetDurationParamL)
        {
        DoCmdSetDurationParamL(aSection);
        }
     else if (aCommand==KCmdDurationParam)
        {
        DoCmdDurationParam(aSection);
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

void CT_DataSIPRetryAfterHeader::DoCmdNewL(const TTEFSectionName& aSection)
	{
	TUint retryAfter;
    if( !GetTUintFromConfig(aSection, KFldRetryAfter, retryAfter) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldRetryAfter);        
        SetBlockResult(EFail);
        }   
    else
        {      
        INFO_PRINTF1(_L("call CSIPRetryAfterHeader::NewL(TUint aRetryAfter)"));
        TRAPD(err, iSIPRetryAfterHeader = CSIPRetryAfterHeader::NewL(retryAfter)); 
    
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        iIsOwner = err == KErrNone;
        }
	}

void CT_DataSIPRetryAfterHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    TUint retryAfter;
    if( !GetTUintFromConfig(aSection, KFldRetryAfter, retryAfter) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldRetryAfter);        
        SetBlockResult(EFail);
        }  
    else
        {
        INFO_PRINTF1(_L("call CSIPRetryAfterHeader::NewLC(TUint aRetryAfter)"));
        TRAPD(err, iSIPRetryAfterHeader = CSIPRetryAfterHeader::NewLC(retryAfter); CleanupStack::Pop(iSIPRetryAfterHeader)); 
    
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        iIsOwner = err == KErrNone;
        }
    }

void CT_DataSIPRetryAfterHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
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
        INFO_PRINTF1(_L("call CSIPRetryAfterHeader::DecodeL(const TDesC8&)"));
        TRAPD(err, iSIPRetryAfterHeader = CSIPRetryAfterHeader::DecodeL(value));

        if (KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            iIsOwner = ETrue;
            }
        }
    }

void CT_DataSIPRetryAfterHeader::DoCmdSetRetryAfter(const TTEFSectionName& aSection)
    {
    TUint retryAfter;
    if(!GetTUintFromConfig(aSection, KFldRetryAfter, retryAfter))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldRetryAfter());
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPRetryAfterHeader::SetRetryAfter(TUint aValue)"));
        
        iSIPRetryAfterHeader->SetRetryAfter(retryAfter);
        }        
    }
    
void CT_DataSIPRetryAfterHeader::DoCmdRetryAfter(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPRetryAfterHeader::RetryAfter()"));

    TUint retryAfter = iSIPRetryAfterHeader->RetryAfter();

    INFO_PRINTF2(_L("The actual Retry-After value is: %d "), retryAfter);

    TUint expected;
    if(GetTUintFromConfig(aSection, KFldExpected, expected))
        {
        if(expected != retryAfter)
            {
            ERR_PRINTF3(KLogNotExpectedValue, retryAfter, expected);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPRetryAfterHeader::DoCmdComment(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPRetryAfterHeader::Comment()"));

    const TDesC8 &comment = iSIPRetryAfterHeader->Comment();

    TBuf<KMaxTestExecuteCommandLength> str;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(str, comment);
    INFO_PRINTF2(_L("The actual comment value is: %S "), &str);

    TPtrC expected;
    if(GetStringFromConfig(aSection, KFldExpected, expected))
        {
        if(expected.Compare(str)!=0)
            {
            ERR_PRINTF2(_L("The expected Retry-After value is: %S"), &expected);
            SetBlockResult(EFail);
            }
        }
    }
    
void CT_DataSIPRetryAfterHeader::DoCmdDurationParam(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPRetryAfterHeader::DurationParam()"));
    
    TInt ret = iSIPRetryAfterHeader->DurationParam();
    INFO_PRINTF2(_L("the actual duration Parameter = %d"), ret);
    
    TInt expected;
    if(GetIntFromConfig(aSection, KFldExpected, expected))
        {
        if(ret != expected)
            {
            ERR_PRINTF3(KLogNotExpectedValue, ret, expected);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPRetryAfterHeader::DoCmdSetDurationParamL(const TTEFSectionName& aSection)
    {
    TInt dur = 0;
    if( GetIntFromConfig(aSection, KFldDurationParam, dur) )
        {
        INFO_PRINTF1(_L("call CSIPRetryAfterHeader::SetDurationParamL(TInt aDurationParam)"));
        TRAPD(err, iSIPRetryAfterHeader->SetDurationParamL(dur));
        
        if (KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    else
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldDurationParam);
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPRetryAfterHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
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
        
        INFO_PRINTF1(_L("call CSIPRetryAfterHeader::InternalizeValueL(RReadStream&)"));
        TRAPD(err, iSIPRetryAfterHeader = (CSIPRetryAfterHeader*)CSIPRetryAfterHeader::InternalizeValueL(readstrm));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        iIsOwner = err == KErrNone;
        CleanupStack::PopAndDestroy(2);
        }
    }

void CT_DataSIPRetryAfterHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
	{
	INFO_PRINTF1(_L("call CSIPRetryAfterHeader::~CSIPRetryAfterHeader()"));
	DestroyData();
	}

void CT_DataSIPRetryAfterHeader::DestroyData()
	{
	if(iIsOwner)
	    {
	    delete iSIPRetryAfterHeader;
	    iSIPRetryAfterHeader = NULL;
	    iIsOwner = EFalse;
	    }
	}

void CT_DataSIPRetryAfterHeader::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

