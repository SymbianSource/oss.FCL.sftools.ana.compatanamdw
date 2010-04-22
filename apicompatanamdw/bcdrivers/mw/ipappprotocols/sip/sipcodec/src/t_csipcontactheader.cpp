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


#include "t_csipcontactheader.h"
#include <stdlib.h>
#include "T_SIPUtil.h"
#include <utf.h>
#include "t_csipaddress.h"
#include <s32file.h>

/*@{*/
_LIT(KCmdDestroy,                               "~");
_LIT(KCmdNewL,                                  "NewL");
_LIT(KCmdNewLC,                                 "NewLC");
_LIT(KCmdDecodeL,                               "DecodeL");
_LIT(KCmdCompare,                               "==");
_LIT(KCmdStar,                                  "Star");
_LIT(KCmdExpiresParameter,                      "ExpiresParameter");
_LIT(KCmdSetExpiresParameterL,                  "SetExpiresParameterL");
_LIT(KCmdQParameter,                            "QParameter");
_LIT(KCmdSetQParameterL,                        "SetQParameterL");
_LIT(KCmdSIPAddress,                            "SIPAddress");
_LIT(KCmdSetSIPAddressL,                        "SetSIPAddressL");
_LIT(KCmdInternalizeValueL,                     "InternalizeValueL");

//Fields
_LIT(KFldSIPAddress,                            "sipaddress");
_LIT(KFldSIPContactHeader,                      "sipcontactheader");
_LIT(KFldParamValue,                            "paramvalue");
_LIT(KFldExpected,                              "expected");
_LIT(KFldTReal,                                 "treal");
_LIT(KFldBeConst,                               "beconst");
_LIT(KFldFileName,                              "filename");  

// Logging
_LIT(KLogError,                                 "Error=%d");
_LIT(KLogMissingParameter,                      "Missing parameter '%S'");
_LIT(KLogNotExpectedValue,                      "Not expected value, actual=%d, expect=%d");
_LIT(KLogNotExpectedValueReal,                  "Not expected value, actual=%f, expect=%f");

_LIT(KFormatFieldNumber,                        "%S%d");

CT_DataSIPContactHeader::CT_DataSIPContactHeader()
: CT_DataSIPParameterHeaderBase(), iSIPContactHeader (NULL), iIsOwner(ETrue)
    {
    
    }

CT_DataSIPContactHeader::~CT_DataSIPContactHeader()
    {
    DestroyData();    
    }

void CT_DataSIPContactHeader::ConstructL()
    {
    
    }

CT_DataSIPContactHeader* CT_DataSIPContactHeader::NewL()
    {
    CT_DataSIPContactHeader* self = new (ELeave) CT_DataSIPContactHeader();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

TAny* CT_DataSIPContactHeader::GetObject()
    {
    return iSIPContactHeader;
    }

void CT_DataSIPContactHeader::SetObjectL(TAny* aAny)
    {
    iSIPContactHeader = static_cast<CSIPContactHeader*>(aAny);
    
    }

void CT_DataSIPContactHeader::DisownObjectL()
    {
    iSIPContactHeader = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPContactHeader::DestroyData()
    {
    if(iIsOwner && iSIPContactHeader != NULL)
        {
        delete iSIPContactHeader;
        iSIPContactHeader = NULL;
        iIsOwner = EFalse;
        }   
    }

void CT_DataSIPContactHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPContactHeader::~CSIPContactHeader()"));
    DestroyData();
    }

CSIPHeaderBase* CT_DataSIPContactHeader::GetSIPHeaderBase() const
    {
    return iSIPContactHeader;
    }

TBool CT_DataSIPContactHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
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
    else if (aCommand==KCmdCompare)
        {
        DoCmdCompare(aSection);
        }
    else if (aCommand==KCmdStar)
        {
        DoCmdStar(aSection);
        }
    else if (aCommand==KCmdExpiresParameter)
        {
        DoCmdExpiresParameter(aSection);
        }
    else if (aCommand==KCmdSetExpiresParameterL)
        {
        DoCmdSetExpiresParameterL(aSection);
        }
    else if (aCommand==KCmdQParameter)
        {
        DoCmdQParameter(aSection);
        }
    else if (aCommand==KCmdSetQParameterL)
        {
        DoCmdSetQParameterL(aSection);
        }
    else if (aCommand==KCmdSIPAddress)
        {
        DoCmdSIPAddress(aSection);
        }
    else if (aCommand==KCmdSetSIPAddressL)
        {
        DoCmdSetSIPAddressL(aSection);
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

void CT_DataSIPContactHeader::DoCmdNewL(const TTEFSectionName& aSection)
    {
    CSIPAddress* datsipaddr = NULL;
    if(!CT_SIPUtil::GetSIPAddressL(*this, aSection, KFldSIPAddress, datsipaddr))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPAddress());
        SetBlockResult(EFail);
        return;
        }
    INFO_PRINTF1(_L("execute CSIPContactHeader::NewL(CSIPAddress*)"));
    TRAPD(err, iSIPContactHeader = CSIPContactHeader::NewL(datsipaddr));
    if(err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    
    TPtrC name;
    if (GetStringFromConfig(aSection, KFldSIPAddress, name))
        {
        CT_DataSIPAddress* wrapper = static_cast<CT_DataSIPAddress*>(GetDataWrapperL(name));
        wrapper->SetIsOwner(EFalse);
        }
    }

void CT_DataSIPContactHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    CSIPAddress* datsipaddr = NULL;
    if(!CT_SIPUtil::GetSIPAddressL(*this, aSection, KFldSIPAddress, datsipaddr))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPAddress());
        SetBlockResult(EFail);
        return;
        }
    INFO_PRINTF1(_L("execute CSIPContactHeader::NewLC(CSIPAddress*)"));
    TRAPD(err, iSIPContactHeader = CSIPContactHeader::NewLC(datsipaddr); CleanupStack::Pop(iSIPContactHeader));
    if(err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    
    TPtrC name;
    if (GetStringFromConfig(aSection, KFldSIPAddress, name))
        {
        CT_DataSIPAddress* wrapper = static_cast<CT_DataSIPAddress*>(GetDataWrapperL(name));
        wrapper->SetIsOwner(EFalse);
        }
    }

void CT_DataSIPContactHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
    {
    TPtrC temp;
    if( !GetStringFromConfig(aSection, KFldParamValue, temp) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldParamValue);
        SetBlockResult(EFail);
        }
    else
        {
        TBuf8<KMaxTestExecuteCommandLength> value;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(value, temp);
        INFO_PRINTF1(_L("call CSIPContactHeader::DecodeL(const TDesC8&)"));
        RPointerArray<CSIPContactHeader> ret;
        TRAPD(err, ret = CSIPContactHeader::DecodeL(value));

        if (KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            return;
            }
        
        TInt cnt = ret.Count();
        INFO_PRINTF2(_L("%d CSIPContactHeader objects got from DecodeL()"), cnt);
        TBool moreData = ETrue;
        TBuf<KMaxTestExecuteNameLength> tempStore;
        TInt index = 1;
        while (moreData && index <= cnt)
            {
            TPtrC name;
            tempStore.Format(KFormatFieldNumber, &KFldSIPContactHeader, index);
            if (GetStringFromConfig(aSection, tempStore, name))
                {
                SetDataObjectL(name, ret[index - 1]);
                CT_DataSIPContactHeader* wrapper = (CT_DataSIPContactHeader*)GetDataWrapperL(name);
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

void CT_DataSIPContactHeader::DoCmdCompare(const TTEFSectionName& aSection)
    {
    TPtrC  datcontactheader;
    CSIPContactHeader* contacthd;
    if(!GetStringFromConfig(aSection, KFldSIPContactHeader, datcontactheader) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPContactHeader);
        SetBlockResult(EFail);
        return;
        }
    else
        {
        contacthd = static_cast<CSIPContactHeader*>(GetDataObjectL(datcontactheader));
        }
    INFO_PRINTF1(_L("execute CSIPContactHeader::==(const CSIPContactHeader&)")); 
    TBool ret = (*iSIPContactHeader == *contacthd);
    TBool expected;
    if( GetBoolFromConfig(aSection, KFldExpected, expected) )
        {
        if(!ret != !expected)
            {
            ERR_PRINTF3(KLogNotExpectedValue, (TInt)ret, (TInt)expected);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPContactHeader::DoCmdStar(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("execute CSIPContactHeader::Star()")); 
    TBool ret=iSIPContactHeader->Star();
    INFO_PRINTF2(_L("Check the address is set to a STAR: %d"), ret);
    TBool expected = ETrue;
    if( GetBoolFromConfig(aSection, KFldExpected, expected) )
        {
        if(!ret != !expected)
            {
            ERR_PRINTF3(KLogNotExpectedValue, (TInt)ret, (TInt)expected);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPContactHeader::DoCmdExpiresParameter(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("execute CSIPContactHeader::ExpiresParameter()")); 
    TInt ret=iSIPContactHeader->ExpiresParameter();
    INFO_PRINTF2(_L("The valude of the expires parameter is : %d"), ret);
    TInt expected;
    if( GetIntFromConfig(aSection, KFldExpected, expected) )
        {
        if(ret != expected)
            {
            ERR_PRINTF3(KLogNotExpectedValue, ret, expected);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPContactHeader::DoCmdSetExpiresParameterL(const TTEFSectionName& aSection)
    {
    TInt expiresparam;
    if( !GetIntFromConfig(aSection, KFldParamValue, expiresparam) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldParamValue);
        SetBlockResult(EFail);
        return;
        }
    INFO_PRINTF1(_L("execute CSIPContactHeader::SetExpiresParameterL(TInt)")); 
    TRAPD(err, iSIPContactHeader->SetExpiresParameterL(expiresparam));
    if(err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void CT_DataSIPContactHeader::DoCmdQParameter(const TTEFSectionName& aSection)
    {
    TReal retTReal;
    TReal expected;

    INFO_PRINTF1(_L("execute CSIPContactHeader::QParameter()")); 
    retTReal = iSIPContactHeader->QParameter();
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

void CT_DataSIPContactHeader::DoCmdSetQParameterL(const TTEFSectionName& aSection)
    {
    TReal dattreal;
    if(!CT_SIPUtil::GetTRealFromConfig(*this, aSection, KFldTReal, dattreal) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldTReal);
        SetBlockResult(EFail);
        return;
        }    
    INFO_PRINTF1(_L("execute CSIPContactHeader::SetQParameterL(TReal)")); 
    TRAPD(err, iSIPContactHeader->SetQParameterL(dattreal));
    if(err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void CT_DataSIPContactHeader::DoCmdSIPAddress(const TTEFSectionName& aSection)
    {
    TBool beconst=EFalse;
    TPtrC dataddrName;
    if (!GetStringFromConfig(aSection, KFldSIPAddress, dataddrName))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPAddress);
        SetBlockResult(EFail);
        return;
        }
    GetBoolFromConfig(aSection, KFldBeConst, beconst);
    if(beconst)
        {
        const CSIPAddress *retSIPAddress = NULL;
        INFO_PRINTF1(_L("execute CSIPContactHeader::SIPAddress() const CSIPAddress *SIPAddress() const"));
        retSIPAddress = iSIPContactHeader->SIPAddress();
        SetDataObjectL(dataddrName, (CSIPAddress*)retSIPAddress);
        }
    else
        {
        CSIPAddress *retSIPAddress = NULL;
        INFO_PRINTF1(_L("execute CSIPContactHeader::SIPAddress() CSIPAddress *SIPAddress()"));
        retSIPAddress = iSIPContactHeader->SIPAddress();
        SetDataObjectL(dataddrName, retSIPAddress);
        }
    SetIsOwner(EFalse);
    }

void CT_DataSIPContactHeader::DoCmdSetSIPAddressL(const TTEFSectionName& aSection)
    {
    CSIPAddress* datsipaddr = NULL;
    if(!CT_SIPUtil::GetSIPAddressL(*this, aSection, KFldSIPAddress, datsipaddr))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPAddress());
        SetBlockResult(EFail);
        return;
        }
    INFO_PRINTF1(_L("execute CSIPContactHeader::SetSIPAddressL(CSIPAddress*)"));
    TRAPD(err, iSIPContactHeader->SetSIPAddressL(datsipaddr));
    if(err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void CT_DataSIPContactHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
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
        INFO_PRINTF1(_L("execute CSIPContactHeader::InternalizeValueL(RReadStream &)"));
        TRAPD(err, iSIPContactHeader = (CSIPContactHeader*)CSIPContactHeader::InternalizeValueL(readstrm));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        // Cleanup
        CleanupStack::PopAndDestroy(2, readstore);
        }
    }

void CT_DataSIPContactHeader::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }
