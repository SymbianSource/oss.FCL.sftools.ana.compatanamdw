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


#include "t_csiprackheader.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <s32file.h>
#include <sipcseqheader.h>

/*@{*/
_LIT(KCmdDestructor,        "~");
_LIT(KCmdNewL,              "NewL");
_LIT(KCmdNewLC,             "NewLC");
_LIT(KCmdDecodeL,           "DecodeL");
_LIT(KCmdMethod,            "Method");
_LIT(KCmdSetMethodL,        "SetMethodL");
_LIT(KCmdSeq,               "Seq");
_LIT(KCmdSetSeq,            "SetSeq");
_LIT(KCmdCSeqNum,           "CSeqNum");
_LIT(KCmdSetCSeqNum,        "SetCSeqNum");
_LIT(KCmdInternalizeValueL, "InternalizeValueL");

//Fields
_LIT(KFldSeq,               "seq");
_LIT(KFldMethod,            "method");
_LIT(KFldSeqHeader,         "seqheader");
_LIT(KFldSeqNum,            "seqnum");
_LIT(KFldValue,             "value");
_LIT(KFldSIPRAckHeader,     "rackheader");
_LIT(KFldExpected,          "expected");
_LIT(KFldFileName,          "filename");

_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");
_LIT(KLogNotExpectedValue,      "Not expected value, actual=%d, expect=%d");
_LIT(KLogNotExpectedValueDes,   "Not expected value, actual=%S, expect=%S");

CT_DataSIPRAckHeader::CT_DataSIPRAckHeader()
:   CT_DataSIPHeaderBase(), iSIPRAckHeader(NULL), iIsOwner(ETrue)
    {
    }

CT_DataSIPRAckHeader::~CT_DataSIPRAckHeader()
	{
	DestroyData();
	}

void CT_DataSIPRAckHeader::ConstructL()
	{
	}

CT_DataSIPRAckHeader* CT_DataSIPRAckHeader::NewL()
    {
	CT_DataSIPRAckHeader* self = new (ELeave)CT_DataSIPRAckHeader();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

CSIPHeaderBase* CT_DataSIPRAckHeader::GetSIPHeaderBase() const
    {
    return iSIPRAckHeader;
    }

TAny* CT_DataSIPRAckHeader::GetObject()
	{
	return iSIPRAckHeader;
	}

void CT_DataSIPRAckHeader::SetObjectL(TAny* aAny)
	{
	iSIPRAckHeader = static_cast<CSIPRAckHeader*>(aAny);
	}

void CT_DataSIPRAckHeader::DisownObjectL()
	{
	iSIPRAckHeader = NULL;
	iIsOwner = EFalse;
	}

TBool CT_DataSIPRAckHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
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
    else if ( aCommand==KCmdMethod )
        {
        DoCmdMethod(aSection);
        }
    else if ( aCommand==KCmdSetMethodL )
        {
        DoCmdSetMethodL(aSection);
        }
    else if ( aCommand==KCmdSeq )
        {
        DoCmdSeq(aSection);
        }
    else if ( aCommand==KCmdSetSeq )
        {
        DoCmdSetSeq(aSection);
        }
    else if ( aCommand==KCmdCSeqNum )
        {
        DoCmdCSeqNum(aSection);
        }
    else if ( aCommand==KCmdSetCSeqNum )
        {
        DoCmdSetCSeqNumL(aSection);
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

void CT_DataSIPRAckHeader::DoCmdNewL(const TTEFSectionName& aSection)
	{
	TInt err = KErrNone;
	TUint seq = 0;
	TUint seqnum = 0;
	RStringF method;
    CSIPCSeqHeader* seqheader = NULL;
	if(!GetTUintFromConfig(aSection, KFldSeq, seq) )
	    {
	    ERR_PRINTF2(KLogMissingParameter, &KFldSeq);
	    SetBlockResult(EFail);
	    return;
	    }
	if (!GetTUintFromConfig(aSection, KFldSeqNum, seqnum) && !CT_SIPUtil::GetSIPSeqHeaderL(*this, aSection, KFldSeqHeader, seqheader))
	    {
        ERR_PRINTF2(KLogMissingParameter, _L("seqnum or seqheader"));
        SetBlockResult(EFail);
        return;	    
	    }
	if (!CT_SIPUtil::GetStringF(*this, aSection, KFldMethod, method))
	    {
        ERR_PRINTF2(KLogMissingParameter, &KFldMethod);
        SetBlockResult(EFail);
        return;  
	    }
	
	if (seqheader != NULL)
	    {
	    seqnum = seqheader->Seq();
	    }
	
	INFO_PRINTF1(_L("call CSIPRAckHeader::NewL(TUint, TUint, RStringF)"));
	TRAP(err, iSIPRAckHeader = CSIPRAckHeader::NewL(seq, seqnum, method)); 

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

void CT_DataSIPRAckHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    TInt err = KErrNone;
    TUint seq = 0;
    TUint seqnum = 0;
    RStringF method;
    CSIPCSeqHeader* seqheader = NULL;
    if(!GetTUintFromConfig(aSection, KFldSeq, seq) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSeq);
        SetBlockResult(EFail);
        return;
        }
    if (!GetTUintFromConfig(aSection, KFldSeqNum, seqnum) && !CT_SIPUtil::GetSIPSeqHeaderL(*this, aSection, KFldSeqHeader, seqheader))
        {
        ERR_PRINTF2(KLogMissingParameter, _L("seqnum or seqheader"));
        SetBlockResult(EFail);
        return;     
        }
    if (!CT_SIPUtil::GetStringF(*this, aSection, KFldMethod, method))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldMethod);
        SetBlockResult(EFail);
        return;  
        }
    
    if (seqheader != NULL)
        {
        seqnum = seqheader->Seq();
        }
    
    INFO_PRINTF1(_L("call CSIPRAckHeader::NewLC(TUint, TUint, RStringF)"));
    TRAP(err, iSIPRAckHeader = CSIPRAckHeader::NewLC(seq, seqnum, method); CleanupStack::Pop(iSIPRAckHeader)); 

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

void CT_DataSIPRAckHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
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
        if( !GetStringFromConfig(aSection, KFldSIPRAckHeader, wrapperName) )
            {
            ERR_PRINTF2(KLogMissingParameter, &KFldSIPRAckHeader);
            SetBlockResult(EFail);
            }
        else
            {
            TBuf8<KMaxTestExecuteCommandLength> value;
            CnvUtfConverter::ConvertFromUnicodeToUtf8(value, temp);
            INFO_PRINTF1(_L("call CSIPRAckHeader::DecodeL(const TDesC8&)"));
            CSIPRAckHeader* ret = NULL;
            TRAPD(err, ret = CSIPRAckHeader::DecodeL(value));
            
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

void CT_DataSIPRAckHeader::DoCmdMethod(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPRAckHeader::Method()"));
    RStringF ret = iSIPRAckHeader->Method();
    
    TPtrC expected;
    if( GetStringFromConfig(aSection, KFldExpected, expected) )
        {
        TBuf<KMaxTestExecuteCommandLength> actual;
        CnvUtfConverter::ConvertToUnicodeFromUtf8(actual, ret.DesC());
        if(actual.Compare(expected) != 0)
            {
            ERR_PRINTF3(KLogNotExpectedValueDes, &actual, &expected);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPRAckHeader::DoCmdSetMethodL(const TTEFSectionName& aSection)
    {
    RStringF method;
    if(!CT_SIPUtil::GetStringF(*this, aSection, KFldMethod, method))
        {        
        ERR_PRINTF2(KLogMissingParameter, &KFldMethod());
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPRAckHeader::SetMethodL(RStringF)"));
        TRAPD(err, iSIPRAckHeader->SetMethodL(method));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    }

void CT_DataSIPRAckHeader::DoCmdSeq(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPRAckHeader::Seq()"));
    TUint ret = iSIPRAckHeader->Seq();
    
    TUint expected;
    if( GetTUintFromConfig(aSection, KFldExpected, expected) )
        {
        if(ret != expected)
            {
            ERR_PRINTF3(KLogNotExpectedValue, ret, expected);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPRAckHeader::DoCmdSetSeq(const TTEFSectionName& aSection)
    {
    TUint seq = 0;
    if( GetTUintFromConfig(aSection, KFldSeq, seq) )
        {
        INFO_PRINTF1(_L("call CSIPRAckHeader::SetSeq(TUint)"));
        iSIPRAckHeader->SetSeq(seq);
        }
    else
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSeq);
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPRAckHeader::DoCmdCSeqNum(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPRAckHeader::CSeqNum()"));
    TUint ret = iSIPRAckHeader->CSeqNum();
    
    TUint expected;
    if( GetTUintFromConfig(aSection, KFldExpected, expected) )
        {
        if(ret != expected)
            {
            ERR_PRINTF3(KLogNotExpectedValue, ret, expected);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPRAckHeader::DoCmdSetCSeqNumL(const TTEFSectionName& aSection)
    {
    TUint seqnum = 0;
    CSIPCSeqHeader* seqheader = NULL;

    if (!GetTUintFromConfig(aSection, KFldSeqNum, seqnum) && !CT_SIPUtil::GetSIPSeqHeaderL(*this, aSection, KFldSeqHeader, seqheader))
        {
        ERR_PRINTF2(KLogMissingParameter, _L("seqnum or seqheader"));
        SetBlockResult(EFail);
        return;     
        }
    if (seqheader != NULL)
        {
        seqnum = seqheader->Seq();
        }
    INFO_PRINTF1(_L("call CSIPRAckHeader::SetCSeqNum(TUint)"));
    iSIPRAckHeader->SetCSeqNum(seqnum);    
    }

void CT_DataSIPRAckHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
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
        
        INFO_PRINTF1(_L("call CSIPRAckHeader::InternalizeValueL(RReadStream&)"));
        TRAPD(err, iSIPRAckHeader = (CSIPRAckHeader*)CSIPRAckHeader::InternalizeValueL(readstrm));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        
        CleanupStack::PopAndDestroy(2);
        }
    }

void CT_DataSIPRAckHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
	{
	INFO_PRINTF1(_L("call CSIPRAckHeader::~CSIPRAckHeader()"));
	DestroyData();
	}

void CT_DataSIPRAckHeader::DestroyData()
	{
	if(iIsOwner)
	    {
	    delete iSIPRAckHeader;
	    iSIPRAckHeader = NULL;
	    iIsOwner = EFalse;
	    }
	}

void CT_DataSIPRAckHeader::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

