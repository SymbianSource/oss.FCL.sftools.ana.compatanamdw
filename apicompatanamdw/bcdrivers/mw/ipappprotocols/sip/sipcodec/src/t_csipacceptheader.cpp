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
*
*/


#include "t_csipacceptheader.h"
#include <stdlib.h>
#include "T_SIPUtil.h"
#include <utf.h>
#include <s32file.h>

/*@{*/
_LIT(KCmdDestroy,                               "~");
_LIT(KCmdNewL,                                  "NewL");
_LIT(KCmdNewLC,                                 "NewLC");
_LIT(KCmdDecodeL,                               "DecodeL");
_LIT(KCmdIsEmpty,                               "IsEmpty");
_LIT(KCmdMediaType,                             "MediaType");
_LIT(KCmdSetMediaTypeL,                         "SetMediaTypeL");
_LIT(KCmdMediaSubtype,                          "MediaSubtype");
_LIT(KCmdSetMediaSubtypeL,                      "SetMediaSubtypeL");
_LIT(KCmdQParameter,                            "QParameter");
_LIT(KCmdSetQParameterL,                        "SetQParameterL");
_LIT(KCmdInternalizeValueL,                     "InternalizeValueL");

//Fields
_LIT(KFldMediaSubtype,                          "mediasubtype");
_LIT(KFldMediaType,                             "mediatype");
_LIT(KFldParamValue,                            "paramvalue");
_LIT(KFldExpected,                              "expected");
_LIT(KFldTReal,                                 "treal");
_LIT(KFldFileName,                              "filename");                      

// Logging
_LIT(KLogError,                                 "Error=%d");
_LIT(KLogMissingParameter,                      "Missing parameter '%S'");
_LIT(KLogNotExpectedValue,                      "Not expected value, actual=%S, expect=%S");
_LIT(KLogNotExpectedValueReal,                  "Not expected value, actual=%f, expect=%f");

CT_DataSIPAcceptHeader::CT_DataSIPAcceptHeader()
: CT_DataSIPParameterHeaderBase(), iSIPAcceptHeader(NULL), iIsOwner(ETrue)
    {
    
    }

CT_DataSIPAcceptHeader::~CT_DataSIPAcceptHeader()
    {
    DestroyData();    
    }

void CT_DataSIPAcceptHeader::ConstructL()
    {
    
    }

CT_DataSIPAcceptHeader* CT_DataSIPAcceptHeader::NewL()
    {
    CT_DataSIPAcceptHeader* self = new (ELeave) CT_DataSIPAcceptHeader();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

TAny* CT_DataSIPAcceptHeader::GetObject()
    {
    return iSIPAcceptHeader;
    }

void CT_DataSIPAcceptHeader::SetObjectL(TAny* aAny)
    {
    iSIPAcceptHeader = static_cast<CSIPAcceptHeader*>(aAny);
    
    }

void CT_DataSIPAcceptHeader::DisownObjectL()
    {
    iSIPAcceptHeader = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPAcceptHeader::DestroyData()
    {
    if(iIsOwner && iSIPAcceptHeader != NULL)
        {
        delete iSIPAcceptHeader;
        iSIPAcceptHeader = NULL;
        iIsOwner = EFalse;
        }   
    }

void CT_DataSIPAcceptHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPAcceptHeader::~CSIPAcceptHeader()"));
    DestroyData();
    }

CSIPHeaderBase* CT_DataSIPAcceptHeader::GetSIPHeaderBase() const
    {
    return iSIPAcceptHeader;
    }

TBool CT_DataSIPAcceptHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
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
    else if(aCommand == KCmdIsEmpty)
        {
        DoCmdIsEmpty(aSection);
        }
    else if( aCommand == KCmdMediaType )
        {
        DoCmdMediaType(aSection);
        }
    else if( aCommand == KCmdSetMediaTypeL )
        {
        DoCmdSetMediaTypeL(aSection);
        }
    else if( aCommand == KCmdMediaSubtype )
        {
        DoCmdMediaSubtype(aSection);
        }
    else if( aCommand == KCmdSetMediaSubtypeL )
        {
        DoCmdSetMediaSubtypeL(aSection);
        }
    else if (aCommand==KCmdQParameter)
        {
        DoCmdQParameter(aSection);
        }
    else if (aCommand==KCmdSetQParameterL)
        {
        DoCmdSetQParameterL(aSection);
        }
    else if (aCommand==KCmdInternalizeValueL)
        {
        DoCmdInternalizeValueL(aSection);
        }
    else
        {
        ret = CT_DataSIPParameterHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);;
        }
    return ret;
    }

void CT_DataSIPAcceptHeader::DoCmdNewL(const TTEFSectionName& aSection)
    {
    TBool dataOK = ETrue;    
    TPtrC temp;
    if( !GetStringFromConfig(aSection, KFldMediaType, temp) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldMediaType);        
        dataOK = EFalse;
        }    
    TPtrC temp1;
    if( !GetStringFromConfig(aSection, KFldMediaSubtype, temp1) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldMediaSubtype);
        dataOK = EFalse;
        }
    
    if(!dataOK)
        {
        SetBlockResult(EFail);
        }
    else
        {
        TBuf8<KMaxTestExecuteCommandLength> mediatype;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(mediatype, temp);
        TBuf8<KMaxTestExecuteCommandLength> mediasubtype;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(mediasubtype, temp1);                
        INFO_PRINTF1(_L("call CSIPAcceptHeader::NewL(const TDesC8&, const TDesC8&)"));
        TRAPD(err, iSIPAcceptHeader = CSIPAcceptHeader::NewL(mediatype, mediasubtype));
        
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
    }

void CT_DataSIPAcceptHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    TBool dataOK = ETrue;    
    TPtrC temp;
    if( !GetStringFromConfig(aSection, KFldMediaType, temp) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldMediaType);        
        dataOK = EFalse;
        }    
    TPtrC temp1;
    if( !GetStringFromConfig(aSection, KFldMediaSubtype, temp1) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldMediaSubtype);
        dataOK = EFalse;
        }
    
    if(!dataOK)
        {
        SetBlockResult(EFail);
        }
    else
        {
        TBuf8<KMaxTestExecuteCommandLength> mediatype;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(mediatype, temp);
        TBuf8<KMaxTestExecuteCommandLength> mediasubtype;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(mediasubtype, temp1);                
        INFO_PRINTF1(_L("call CSIPAcceptHeader::NewLC(const TDesC8&, const TDesC8&)"));
        TRAPD(err, iSIPAcceptHeader = CSIPAcceptHeader::NewLC(mediatype, mediasubtype); CleanupStack::Pop(iSIPAcceptHeader));
        
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
    }

void CT_DataSIPAcceptHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
    {
    delete iSIPAcceptHeader;
    iSIPAcceptHeader = NULL;
    
    TPtrC strVal;
    if (!GetStringFromConfig(aSection, KFldParamValue, strVal))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldParamValue());
        SetBlockResult(EFail);
        return;
        }
    TBuf8<KMaxTestExecuteCommandLength> val;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(val, strVal);
    INFO_PRINTF1(_L("execute CSIPAcceptHeader::DecodeL(const TDesC8&)"));
    TRAPD(err, iSIPAcceptHeader = CSIPAcceptHeader::DecodeL(val)[0]);
    if(err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void CT_DataSIPAcceptHeader::DoCmdIsEmpty(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPAcceptHeader::IsEmpty()"));
    TBool ret = iSIPAcceptHeader->IsEmpty();
    INFO_PRINTF2(_L("Actual IsEmpty: %d"), ret);
    
    TBool expected = EFalse;
    if(GetBoolFromConfig(aSection, KFldExpected, expected))
        {
        if(ret != expected)
            {
            INFO_PRINTF2(_L("expected IsEmpty: %d"), expected);
            SetBlockResult(EFail);
            }
        }
    }
void CT_DataSIPAcceptHeader::DoCmdMediaType(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPAcceptHeader::MediaType()"));
    const TPtrC8 ret = iSIPAcceptHeader->MediaType();
    TBuf<KMaxTestExecuteCommandLength> temp1;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(temp1, ret);
    INFO_PRINTF2(_L("MediaType: %S"), &temp1);
    
    TPtrC temp;
    if( GetStringFromConfig(aSection, KFldExpected, temp) )
        {
        TBuf8<KMaxTestExecuteCommandLength> expected;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(expected, temp);
        if(ret != expected)
            {
            ERR_PRINTF3(KLogNotExpectedValue, &temp1, &temp);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPAcceptHeader::DoCmdSetMediaTypeL(const TTEFSectionName& aSection)
    {
    TPtrC temp;
    if( !GetStringFromConfig(aSection, KFldMediaType, temp) )
        {        
        ERR_PRINTF2(KLogMissingParameter, &KFldMediaType);
        SetBlockResult(EFail);
        }
    else
        {
        TBuf8<KMaxTestExecuteCommandLength> mediatype;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(mediatype, temp);
        INFO_PRINTF1(_L("call CSIPAcceptHeader::SetMediaTypeL(const TDesC8&)"));
        TRAPD(err, iSIPAcceptHeader->SetMediaTypeL(mediatype));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    }

void CT_DataSIPAcceptHeader::DoCmdMediaSubtype(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPAcceptHeader::MediaSubtype()"));
    const TPtrC8 ret = iSIPAcceptHeader->MediaSubtype();
    TBuf<KMaxTestExecuteCommandLength> temp1;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(temp1, ret);
    INFO_PRINTF2(_L("MediaSubtype: %S"), &temp1);
    
    TPtrC temp;
    if( GetStringFromConfig(aSection, KFldExpected, temp) )
        {
        TBuf8<KMaxTestExecuteCommandLength> expected;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(expected, temp);
        if(ret != expected)
            {
            ERR_PRINTF3(KLogNotExpectedValue, &temp1, &temp);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPAcceptHeader::DoCmdSetMediaSubtypeL(const TTEFSectionName& aSection)
    {
    TPtrC temp;
    if( !GetStringFromConfig(aSection, KFldMediaSubtype, temp) )
        {        
        ERR_PRINTF2(KLogMissingParameter, &KFldMediaSubtype);
        SetBlockResult(EFail);
        }
    else
        {
        TBuf8<KMaxTestExecuteCommandLength> mediasubtype;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(mediasubtype, temp);
        INFO_PRINTF1(_L("call CSIPAcceptHeader::SetMediaSubtypeL(const TDesC8&)"));
        TRAPD(err, iSIPAcceptHeader->SetMediaSubtypeL(mediasubtype));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    }

void CT_DataSIPAcceptHeader::DoCmdQParameter(const TTEFSectionName& aSection)
    {
    TReal retTReal;
    TReal expected;

    INFO_PRINTF1(_L("execute CSIPAcceptHeader::QParameter()")); 
    retTReal = iSIPAcceptHeader->QParameter();
    INFO_PRINTF2(_L("The valude of the q parameter is : %f"), retTReal);
    if (CT_SIPUtil::GetTRealFromConfig(*this, aSection, KFldExpected, expected))
        {
        if(!CT_SIPUtil::CompareTReal(retTReal, expected ))
            {
            ERR_PRINTF3(KLogNotExpectedValueReal, retTReal, expected);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPAcceptHeader::DoCmdSetQParameterL(const TTEFSectionName& aSection)
    {
    TReal dattreal;
    if(!CT_SIPUtil::GetTRealFromConfig(*this, aSection, KFldTReal, dattreal) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldTReal);
        SetBlockResult(EFail);
        return;
        }    
    INFO_PRINTF1(_L("execute CSIPAcceptHeader::SetQParameterL(TReal)")); 
    TRAPD(err, iSIPAcceptHeader->SetQParameterL(dattreal));
    if(err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void CT_DataSIPAcceptHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
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
        
        INFO_PRINTF1(_L("call CSIPAcceptHeader::InternalizeValueL(RReadStream&)"));
        TRAPD(err, iSIPAcceptHeader = (CSIPAcceptHeader*)CSIPAcceptHeader::InternalizeValueL(readstrm));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        
        CleanupStack::PopAndDestroy(2);
        }
    }

void CT_DataSIPAcceptHeader::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }
