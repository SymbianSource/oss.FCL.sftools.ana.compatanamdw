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

#include <siprequestelements.h>
#include <sipmessageelements.h>
#include <sipcontenttypeheader.h>
#include <sipfromheader.h>
#include <siptoheader.h>
#include <sipcseqheader.h>
#include <stringpool.h>
#include <utf.h>
#include <uri8.h>

#include "t_csiprequestelements.h"
#include "t_csipcseqheader.h"
#include "t_csiptoheader.h"
#include "t_csipfromheader.h"
#include "t_csipmessageelements.h"
#include "T_SIPUtil.h"

// Command
_LIT(KCmdCSeqHeader,                        "CSeqHeader");
_LIT(KCmdFromHeader,                        "FromHeader");
_LIT(KCmdMessageElements,                   "MessageElements");
_LIT(KCmdMethod,                            "Method");
_LIT(KCmdNewL,                              "NewL");
_LIT(KCmdNewLC,                             "NewLC");
_LIT(KCmdRemoteUri,                         "RemoteUri");
_LIT(KCmdSetFromHeaderL,                    "SetFromHeaderL");
_LIT(KCmdSetMethodL,                       "SetMethodL");
_LIT(KCmdSetRemoteUriL,                      "SetRemoteUriL");
_LIT(KCmdSetToHeaderL,                      "SetToHeaderL");
_LIT(KCmdToHeader,                            "ToHeader");
_LIT(KCmdDestructor,                         "~");

// Field
_LIT(KFldExpected,              "expected");
_LIT(KFldUri,                   "uri");
_LIT(KFldToHeader,               "tohdr");
_LIT(KFldFromHeader,               "fromhdr");
_LIT(KFldMethod,               "method");
_LIT(KFldModifiable,               "modifiable");
_LIT(KFldMessageElements,       "msgelems");
_LIT(KFldSeqHeader,             "seqhdr");

// Error
_LIT(KLogError, "Error=%d");
_LIT(KMissingParameter, "missing parameter '%S'");

CT_DataSIPRequestElements* CT_DataSIPRequestElements::NewL()
    {
    CT_DataSIPRequestElements* self = new (ELeave) CT_DataSIPRequestElements();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

CT_DataSIPRequestElements::~CT_DataSIPRequestElements()
    {
    SIPStrings::Close();
    DestroyData();
    }

CT_DataSIPRequestElements::CT_DataSIPRequestElements() :
      CDataWrapperBase(),iReqElems(NULL), iIsOwner(ETrue)
    {
    }

void CT_DataSIPRequestElements::ConstructL()
    {
    SIPStrings::OpenL();
    iPool = SIPStrings::Pool();
    }

void CT_DataSIPRequestElements::DestroyData()
    {
    if (iIsOwner)
        {
        delete iReqElems;
        iReqElems = NULL;
        iIsOwner = EFalse;
        }    
    }

void CT_DataSIPRequestElements::DoCmdDestructor()
    {
    INFO_PRINTF1(_L("call CSIPRequestElements::~CSIPRequestElements()"));
    DestroyData();
    }

TBool CT_DataSIPRequestElements::DoCommandL(const TTEFFunction& aCommand,
        const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
    {
    TBool ret = ETrue;
    if (aCommand == KCmdCSeqHeader)
        {
        DoCmdCSeqHeaderL(aSection);
        }
    else if (aCommand == KCmdFromHeader)
        {
        DoCmdFromHeaderL(aSection);
        }
    else if (aCommand == KCmdMessageElements)
        {
        DoCmdMessageElements(aSection);
        }
    else if (aCommand == KCmdMessageElements)
        {
        DoCmdMessageElements(aSection);
        }
    else if (aCommand == KCmdMethod)
        {
        DoCmdMethod(aSection);
        }
    else if (aCommand == KCmdNewL)
        {
        DoCmdNewL(aSection);
        }
    else if (aCommand == KCmdNewLC)
        {
        DoCmdNewLC(aSection);
        }
    else if (aCommand == KCmdRemoteUri)
        {
        DoCmdRemoteUri(aSection);
        }
    else if (aCommand == KCmdSetFromHeaderL)
        {
        DoCmdSetFromHeaderL(aSection);
        }
    else if (aCommand == KCmdSetMethodL)
        {
        DoCmdSetMethodL(aSection);
        }
    else if (aCommand == KCmdSetRemoteUriL)
        {
        DoCmdSetRemoteUriL(aSection);
        }
    else if (aCommand == KCmdSetToHeaderL)
        {
        DoCmdSetToHeaderL(aSection);
        }
    else if (aCommand == KCmdToHeader)
        {
        DoCmdToHeaderL(aSection);
        }
    else if (aCommand == KCmdDestructor)
        {
        DoCmdDestructor();
        }
    else
        {
        ret = EFalse;
        }
    return ret;
    }

TAny* CT_DataSIPRequestElements::GetObject()
    {
    return iReqElems;
    }

void CT_DataSIPRequestElements::SetObjectL(TAny* aAny)
    {
    DestroyData();
    iReqElems = static_cast<CSIPRequestElements*> (aAny);
    }

void CT_DataSIPRequestElements::DisownObjectL()
    {
    iReqElems = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPRequestElements::DoCmdCSeqHeaderL(
        const TTEFSectionName& aSection)
    {
    TPtrC name;
    if (GetStringFromConfig(aSection, KFldSeqHeader, name))
        {
        INFO_PRINTF1(_L("execute CSIPRequestElements::CSeqHeader()"));
        const CSIPCSeqHeader* actual = iReqElems->CSeqHeader();
        if (actual != NULL)
            {
            CT_DataSIPCSeqHeader* wrapper = static_cast<CT_DataSIPCSeqHeader*> (GetDataWrapperL(name));
            wrapper->SetIsOwner(EFalse);
            SetDataObjectL(name, (void*) actual);

            CSIPCSeqHeader* expected;
            if (CT_SIPUtil::GetSIPSeqHeaderL(*this, aSection, KFldExpected,
                    expected))
                {
                if (actual->Seq() != expected->Seq() || actual->Method()
                        != expected->Method() || actual->Name()
                        != expected->Name())
                    {
                    TBuf<KMaxTestExecuteCommandLength> actualName;
                    TBuf<KMaxTestExecuteCommandLength> actualMethod;
                    TBuf<KMaxTestExecuteCommandLength> expectedName;
                    TBuf<KMaxTestExecuteCommandLength> expectedMethod;
                    CnvUtfConverter::ConvertToUnicodeFromUtf8(actualName,
                            actual->Name().DesC());
                    CnvUtfConverter::ConvertToUnicodeFromUtf8(actualMethod,
                            actual->Method().DesC());
                    CnvUtfConverter::ConvertToUnicodeFromUtf8(expectedName,
                            expected->Name().DesC());
                    CnvUtfConverter::ConvertToUnicodeFromUtf8(expectedMethod,
                            expected->Method().DesC());
                    ERR_PRINTF1(_L("actual value is not as expected"));
                    ERR_PRINTF3(_L("expected Name: %S, actual Name: %S"), &expectedName, &actualName);
                    ERR_PRINTF3(_L("expected Method: %S, actual Method: %S"), &expectedMethod, &actualMethod);
                    ERR_PRINTF3(_L("expected Seq: %u, actual Seq: %u"), expected->Seq(), actual->Seq());
                    SetBlockResult(EFail);
                    }
                }
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldSeqHeader());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPRequestElements::DoCmdFromHeaderL(
        const TTEFSectionName& aSection)
    {
    TPtrC name;
     INFO_PRINTF1(_L("execute CSIPRequestElements::FromHeader()"));
     CSIPFromHeader* expected;
     const CSIPFromHeader* actual = iReqElems->FromHeader();
     if (CT_SIPUtil::GetSIPFromHeaderL(*this, aSection, KFldExpected,
             expected))
         {
         if (actual->Name() != expected->Name())
             {
             TBuf<KMaxTestExecuteCommandLength> actualName;
             TBuf<KMaxTestExecuteCommandLength> expectedName;
             CnvUtfConverter::ConvertToUnicodeFromUtf8(actualName,
                     actual->Name().DesC());
             CnvUtfConverter::ConvertToUnicodeFromUtf8(expectedName,
                     expected->Name().DesC());
             ERR_PRINTF3(_L("actual value is not as expected, expected: %S, actual: %S"), &expectedName, &actualName);
             SetBlockResult(EFail);
             }
         }
     if (GetStringFromConfig(aSection, KFldFromHeader, name))
         {
         if (actual != NULL)
             {
             CT_DataSIPFromHeader* wrapper = static_cast<CT_DataSIPFromHeader*>(GetDataWrapperL(name));
             wrapper->SetIsOwner(ETrue);
             SetDataObjectL(name, (void*) actual);
             }
         }
    }

void CT_DataSIPRequestElements::DoCmdMessageElements(
        const TTEFSectionName& aSection)
    {
    TPtrC name;
    if (GetStringFromConfig(aSection, KFldMessageElements, name))
        {
        INFO_PRINTF1(_L("execute CSIPRequestElements::MessageElements()"));
        TBool modifiable = EFalse;
        const CSIPMessageElements* pMsgElems;
        (void) GetBoolFromConfig(aSection, KFldModifiable, modifiable);
        if (modifiable)
            {
            pMsgElems = &(iReqElems->MessageElements());
            }
        else
            {
            pMsgElems = &(((const CSIPRequestElements*) iReqElems)->MessageElements());
            }
        if (pMsgElems != NULL)
            {
            CT_DataSIPMessageElements* wrapper = static_cast<CT_DataSIPMessageElements*>(GetDataWrapperL(name));
            wrapper->SetIsOwner(EFalse);
            SetDataObjectL(name, (void*)pMsgElems);
            }
        //TODO
        // How to verify?
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldMessageElements());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPRequestElements::DoCmdMethod(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("execute CSIPRequestElements::Method()"));
    RStringF actual = iReqElems->Method();
    TBuf<KMaxTestExecuteCommandLength> actual16;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(actual16, actual.DesC());
    INFO_PRINTF2(_L("Method: %S"), &actual16);
    
    TPtrC expected;
    if (GetStringFromConfig(aSection, KFldExpected, expected))
        {

        if (expected.Compare(actual16) != 0)
            {
            ERR_PRINTF3(_L("actual value is not as expected, expected: %S, actual: %S"), &expected, &actual16);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPRequestElements::DoCmdNewL(const TTEFSectionName& aSection)
    {
    CUri8* rmtUri;

    if (!CT_SIPUtil::GetUri8L(*this, aSection, KFldUri, rmtUri))
        {
        ERR_PRINTF2(KMissingParameter, &KFldUri());
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("execute CSIPRequestElements::NewL(CUri8 *)"));
        TRAPD(err, iReqElems = CSIPRequestElements::NewL(rmtUri));
        if (err != KErrNone)
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

void CT_DataSIPRequestElements::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    CUri8* rmtUri;

    if (!CT_SIPUtil::GetUri8L(*this, aSection, KFldUri, rmtUri))
        {
        ERR_PRINTF2(KMissingParameter, &KFldUri());
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("execute CSIPRequestElements::NewLC(CUri8 *)"));
        TRAPD(err, iReqElems = CSIPRequestElements::NewLC(rmtUri); CleanupStack::Pop(iReqElems));
        if (err != KErrNone)
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

void CT_DataSIPRequestElements::DoCmdRemoteUri(
        const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("execute CSIPRequestElements::RemoteUri()"));
    const CUri8* actual = &(iReqElems->RemoteUri());
    
    TBuf<KMaxTestExecuteCommandLength> actual16;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(actual16, actual->Uri().UriDes());
    INFO_PRINTF2(_L("actual remote uri = %S"), &actual16);
    
    TPtrC expected;
    if (GetStringFromConfig(aSection, KFldExpected, expected))
        {
        if (expected.Compare(actual16) != 0)
            {
            ERR_PRINTF3(_L("actual value is not as expected, expected: %S, actual: %S"), &expected, &actual16);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPRequestElements::DoCmdSetFromHeaderL(
        const TTEFSectionName& aSection)
    {
    CSIPFromHeader* from;

    if (!CT_SIPUtil::GetSIPFromHeaderL(*this, aSection, KFldFromHeader, from))
        {
        ERR_PRINTF2(KMissingParameter, &KFldFromHeader());
        SetBlockResult(EFail);        
        }
    else
        {
        INFO_PRINTF1(_L("execute CSIPRequestElements::SetFromHeaderL(CSIPFromHeader *)"));
        TRAPD(err, iReqElems->SetFromHeaderL(from));
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            TPtrC name;
            if (GetStringFromConfig(aSection, KFldFromHeader, name))
                {
                CT_DataSIPFromHeader* wrapper = static_cast<CT_DataSIPFromHeader*>(GetDataWrapperL(name));
                wrapper->SetIsOwner(EFalse);
                }
            }
        }
    }

void CT_DataSIPRequestElements::DoCmdSetMethodL(
        const TTEFSectionName& aSection)
    {
    RStringF method;
    //RStringPool pool;
    //pool.OpenL();
    if (CT_SIPUtil::GetStringF(*this, aSection, KFldMethod, method))
        {
        INFO_PRINTF1(_L("execute CSIPRequestElements::SetMethodL(RStringF)"));
        TRAPD(err, iReqElems->SetMethodL(method));
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        //method.Close();
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldMethod());
        SetBlockResult(EFail);
        }
    //pool.Close();
    }

void CT_DataSIPRequestElements::DoCmdSetRemoteUriL(
        const TTEFSectionName& aSection)
    {
    CUri8* rmtUri;
    
    if (!CT_SIPUtil::GetUri8L(*this, aSection, KFldUri, rmtUri))
        {
        ERR_PRINTF2(KMissingParameter, &KFldUri());
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("execute CSIPRequestElements::SetRemoteUriL(CUri8 *)"));
        TRAPD(err, iReqElems->SetRemoteUriL(rmtUri));
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    }

void CT_DataSIPRequestElements::DoCmdSetToHeaderL(
        const TTEFSectionName& aSection)
    {
    CSIPToHeader* to;

    if (!CT_SIPUtil::GetSIPToHeaderL(*this, aSection, KFldToHeader, to))
        {
        ERR_PRINTF2(KMissingParameter, &KFldToHeader());
        SetBlockResult(EFail);        
        }
    else
        {
        INFO_PRINTF1(_L("execute CSIPRequestElements::SetToHeaderL(CSIPToHeader *)"));
        TRAPD(err, iReqElems->SetToHeaderL(to));
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            TPtrC name;
            if (GetStringFromConfig(aSection, KFldToHeader, name))
                {
                CT_DataSIPToHeader* wrapper = static_cast<CT_DataSIPToHeader*>(GetDataWrapperL(name));
                wrapper->SetIsOwner(EFalse);
                }
            }
        }
    }

void CT_DataSIPRequestElements::DoCmdToHeaderL(const TTEFSectionName& aSection)
    {
    TPtrC name;
    INFO_PRINTF1(_L("execute CSIPRequestElements::ToHeader()"));
    CSIPToHeader* expected;
    const CSIPToHeader* actual = iReqElems->ToHeader();
    if (CT_SIPUtil::GetSIPToHeaderL(*this, aSection, KFldExpected,
            expected))
        {
        if (actual->Name() != expected->Name())
            {
            TBuf<KMaxTestExecuteCommandLength> actualName;
            TBuf<KMaxTestExecuteCommandLength> expectedName;
            CnvUtfConverter::ConvertToUnicodeFromUtf8(actualName,
                    actual->Name().DesC());
            CnvUtfConverter::ConvertToUnicodeFromUtf8(expectedName,
                    expected->Name().DesC());
            ERR_PRINTF3(_L("actual value is not as expected, expected: %S, actual: %S"), &expectedName, &actualName);
            SetBlockResult(EFail);
            }
        }
    if (GetStringFromConfig(aSection, KFldToHeader, name))
        {
        if (actual != NULL)
            {
            CT_DataSIPToHeader* wrapper = static_cast<CT_DataSIPToHeader*>(GetDataWrapperL(name));
            wrapper->SetIsOwner(ETrue);
            SetDataObjectL(name, (void*) actual);
            }
        }
    }

void CT_DataSIPRequestElements::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }
