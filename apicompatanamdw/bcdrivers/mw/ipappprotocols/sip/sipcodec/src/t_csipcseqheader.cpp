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
* This contains CT_DataSIPCSeqHeader
*/


#include "t_csipcseqheader.h"
#include "T_SIPUtil.h"
#include <stringpool.h>
#include <utf.h>
#include <s32file.h>
/*@{*/
_LIT(KCmdDestroy,                               "~");
_LIT(KCmdNewL,                                  "NewL");
_LIT(KCmdNewLC,                                 "NewLC");
_LIT(KCmdDecodeL,                               "DecodeL");
_LIT(KCmdSeq,                                   "Seq");
_LIT(KCmdSetSeq,                                "SetSeq");
_LIT(KCmdMethod,                                "Method");
_LIT(KCmdSetMethodL,                             "SetMethodL");
_LIT(KCmdInternalizeValueL,                     "InternalizevalueL");

//Fields
_LIT(KFldSeqNumb,                               "seqnumb");
_LIT(KFldRStringFMethod,                        "stringfmethod");
_LIT(KFldParamValue,                            "paramvalue");
_LIT(KFldExpected,                              "expected");
_LIT(KFldFileName,                              "filename");
_LIT(KFldSIPHeaderBase,                         "sipheaderbase");
_LIT(KFldSIPCSeqHeader,                         "sipcseqheader");

// Logging
_LIT(KLogError,                                 "Error=%d");
_LIT(KLogMissingParameter,                      "Missing parameter '%S'");
_LIT(KLogNotExpectedValue,                      "Not expected value, actual=%d, expect=%d");

CT_DataSIPCSeqHeader::CT_DataSIPCSeqHeader()
: CT_DataSIPHeaderBase(), iSIPCSeqHeader (NULL), iIsOwner(ETrue)
    {
    
    }

CT_DataSIPCSeqHeader::~CT_DataSIPCSeqHeader()
    {
    DestroyData();    
    }

void CT_DataSIPCSeqHeader::ConstructL()
    {
    
    }

CT_DataSIPCSeqHeader* CT_DataSIPCSeqHeader::NewL()
    {
    CT_DataSIPCSeqHeader* self = new (ELeave) CT_DataSIPCSeqHeader();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

TAny* CT_DataSIPCSeqHeader::GetObject()
    {
    return iSIPCSeqHeader;
    }

void CT_DataSIPCSeqHeader::SetObjectL(TAny* aAny)
    {
    iSIPCSeqHeader = static_cast<CSIPCSeqHeader*>(aAny);
    
    }

void CT_DataSIPCSeqHeader::DisownObjectL()
    {
    iSIPCSeqHeader = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPCSeqHeader::DestroyData()
    {
    if(iIsOwner && iSIPCSeqHeader != NULL)
        {
        delete iSIPCSeqHeader;
        iSIPCSeqHeader = NULL;
        iIsOwner = EFalse;
        }   
    }

void CT_DataSIPCSeqHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPCSeqHeader::~CSIPCSeqHeader()"));
    DestroyData();
    }

CSIPHeaderBase* CT_DataSIPCSeqHeader::GetSIPHeaderBase() const
    {
    return iSIPCSeqHeader;
    }

TBool CT_DataSIPCSeqHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
    {
    TBool ret=ETrue;
    if ( aCommand==KCmdDestroy )
        {
        DoCmdDestructor(aSection);
        }
    else if (aCommand==KCmdNewL)
        {
        DoCmdNewL(aSection);
        }
    else if (aCommand==KCmdNewLC)
        {
        DoCmdNewLC(aSection);
        }
    else if (aCommand==KCmdDecodeL)
        {
        DoCmdDecodeL(aSection);
        }
    else if (aCommand==KCmdSeq)
        {
        DoCmdSeq(aSection);
        }
    else if (aCommand==KCmdSetSeq)
        {
        DoCmdSetSeq(aSection);
        }
    else if (aCommand==KCmdMethod)
        {
        DoCmdMethod(aSection);
        }
    else if (aCommand==KCmdSetMethodL)
        {
        DoCmdSetMethodL(aSection);
        }
    else if (aCommand==KCmdInternalizeValueL)
        {
        DoCmdInternalizeValueL(aSection);
        }
    else
        {
        ret = CT_DataSIPHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);;
        }
    return ret;
    }

void CT_DataSIPCSeqHeader::DoCmdNewL(const TTEFSectionName& aSection)
    {
    TUint seqnumb;
    RStringF strfmethod;
    if (!GetTUintFromConfig(aSection,KFldSeqNumb, seqnumb))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSeqNumb());
        SetBlockResult(EFail);
        return;
        }
    if (!CT_SIPUtil::GetStringF(*this, aSection, KFldRStringFMethod, strfmethod))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldRStringFMethod());
        SetBlockResult(EFail);
        return;
        }
    INFO_PRINTF1(_L("execute CSIPCSeqHeader::NewL(TUint, RStringF)"));
    TRAPD(err, iSIPCSeqHeader = CSIPCSeqHeader::NewL(seqnumb,strfmethod));
    strfmethod.Close();
    if(err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    else
        {
        iIsOwner = ETrue;
        }
    }
    
void CT_DataSIPCSeqHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    TUint seqnumb;
    RStringF strfmethod;
    if (!GetTUintFromConfig(aSection,KFldSeqNumb, seqnumb))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSeqNumb());
        SetBlockResult(EFail);
        return;
        }
    if (!CT_SIPUtil::GetStringF(*this, aSection, KFldRStringFMethod, strfmethod))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldRStringFMethod());
        SetBlockResult(EFail);
        return;
        }
    INFO_PRINTF1(_L("execute CSIPCSeqHeader::NewLC(TUint, RStringF)"));
    TRAPD(err, iSIPCSeqHeader = CSIPCSeqHeader::NewLC(seqnumb,strfmethod); CleanupStack::Pop(iSIPCSeqHeader));
    strfmethod.Close();
    if(err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    else
        {
        iIsOwner = ETrue;
        }
    }
void CT_DataSIPCSeqHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
    {
    TPtrC strVal;
    TPtrC wrppsipcseq;
	
    if (!GetStringFromConfig(aSection, KFldParamValue, strVal))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldParamValue());
        SetBlockResult(EFail);
        return;
        }
    if (!GetStringFromConfig(aSection, KFldSIPCSeqHeader, wrppsipcseq))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPCSeqHeader());
        SetBlockResult(EFail);
        return;
        }
    TBuf8<KMaxTestExecuteCommandLength> val;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(val, strVal);
    INFO_PRINTF1(_L("execute CSIPCSeqHeader::DecodeL(const TDesC8)"));
    TRAPD(err, iSIPCSeqHeader = CSIPCSeqHeader::DecodeL(val));
    if(err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }

    }

void CT_DataSIPCSeqHeader::DoCmdSeq(const TTEFSectionName& aSection)
    {
    TUint retValue, expctValue;
    INFO_PRINTF1(_L("execute CSIPCSeqHeader::Seq()"));
    retValue = iSIPCSeqHeader->Seq();
    INFO_PRINTF2(_L("The current sequence number is : %d"), retValue);
    if (GetTUintFromConfig(aSection,KFldExpected, expctValue))
        {
        if(expctValue != retValue)
            {
            ERR_PRINTF3(KLogNotExpectedValue, (TInt)retValue, (TInt)expctValue);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPCSeqHeader::DoCmdSetSeq(const TTEFSectionName& aSection)
    {
    TUint seqnumb;
    if (!GetTUintFromConfig(aSection,KFldSeqNumb, seqnumb))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSeqNumb());
        SetBlockResult(EFail);
        return;
        }
    INFO_PRINTF1(_L("execute CSIPCSeqHeader::SetSeq(TUint)"));
    iSIPCSeqHeader->SetSeq(seqnumb);
    }

void CT_DataSIPCSeqHeader::DoCmdMethod(const TTEFSectionName& aSection)
    {
    TPtrC expectedRstrF;
    INFO_PRINTF1(_L("execute CSIPCSeqHeader::Method()"));
    RStringF  retstrf = iSIPCSeqHeader->Method();
    TBuf<KMaxTestExecuteCommandLength> retstrf16;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(retstrf16, retstrf.DesC());
    INFO_PRINTF2(_L("Method: %S"), &retstrf16);
    if (GetStringFromConfig(aSection, KFldExpected, expectedRstrF))
        {
        if (expectedRstrF.Compare(retstrf16) != 0)
            {
            ERR_PRINTF3(_L("actual value is not as expected, expected: %S, actual: %S"), &expectedRstrF, &retstrf16);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPCSeqHeader::DoCmdSetMethodL(const TTEFSectionName& aSection)
    {   
    RStringF strfmethod;
    if (!CT_SIPUtil::GetStringF(*this, aSection, KFldRStringFMethod, strfmethod))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldRStringFMethod());
        SetBlockResult(EFail);
        return;
        }
    INFO_PRINTF1(_L("execute CSIPCSeqHeader::SetMethodL(RStringF)"));    
    TRAPD(err, iSIPCSeqHeader->SetMethodL(strfmethod));
    strfmethod.Close();
    if(err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void CT_DataSIPCSeqHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
    {
    TPtrC datFileName;
    if ( !GetStringFromConfig(aSection, KFldFileName, datFileName) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldFileName());
        SetBlockResult(EFail);
        return;
        }
    else
        {
        CDirectFileStore*   readstore = CDirectFileStore::OpenL(FileServer(), datFileName, EFileStream | EFileRead);
        CleanupStack::PushL(readstore);
        TStreamId           headerid = readstore->Root();
        RStoreReadStream    readstrm;
        
        readstrm.OpenL(*readstore, headerid);
        CleanupClosePushL(readstrm);
        // Execute command and log parameters
        INFO_PRINTF1(_L("execute CSIPCSeqHeader::InternalizeValueL(RReadStream &)"));
        TRAPD(err, iSIPCSeqHeader = (CSIPCSeqHeader*)CSIPCSeqHeader::InternalizeValueL(readstrm));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        // Cleanup
        CleanupStack::PopAndDestroy(2, readstore);
        }
    }

void CT_DataSIPCSeqHeader::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }
