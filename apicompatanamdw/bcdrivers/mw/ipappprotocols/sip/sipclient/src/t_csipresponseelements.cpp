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

#include <sipresponseelements.h>
#include <sipmessageelements.h>
#include <sipfromheader.h>
#include <siptoheader.h>
#include <sipcseqheader.h>
#include <stringpool.h>
#include <utf.h>
#include <uri8.h>
#include <sipstrings.h>

#include "t_csipresponseelements.h"
#include "t_csipcseqheader.h"
#include "t_csipfromheader.h"
#include "t_csipmessageelements.h"
#include "T_SIPUtil.h"

// Command
_LIT(KCmdCSeqHeader,                "CSeqHeader");
_LIT(KCmdFromHeader,                "FromHeader");
_LIT(KCmdMessageElements,           "MessageElements");
_LIT(KCmdNewL,                      "NewL");
_LIT(KCmdNewLC,                     "NewLC");
_LIT(KCmdReasonPhrase,              "ReasonPhrase");
_LIT(KCmdSetReasonPhraseL,          "SetReasonPhraseL");
_LIT(KCmdSetStatusCodeL,            "SetStatusCodeL");
_LIT(KCmdStatusCode,                "StatusCode");
_LIT(KCmdToHeader,                  "ToHeader");
_LIT(KCmdDestructor,                "~");

// Field
_LIT(KFldExpected,              "expected");
_LIT(KFldStatusCode,                   "statuscode");
_LIT(KFldToHeader,               "tohdr");
_LIT(KFldFromHeader,               "fromhdr");
_LIT(KFldReasonPhrase,               "reasonphrase");
_LIT(KFldModifiable,            "modifiable");
_LIT(KFldSeqHeader,            "seqhdr");
_LIT(KFldMessageElements,       "msgelems");

// Error
_LIT(KLogError, "Error=%d");
_LIT(KMissingParameter, "missing parameter '%S'");

CT_DataSIPResponseElements* CT_DataSIPResponseElements::NewL()
    {
    CT_DataSIPResponseElements* self = new (ELeave) CT_DataSIPResponseElements();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

CT_DataSIPResponseElements::~CT_DataSIPResponseElements()
    {
    DestroyData();
    }

CT_DataSIPResponseElements::CT_DataSIPResponseElements() :
    CDataWrapperBase(),iRespElems(NULL), iIsOwner(ETrue)
    {
    }

void CT_DataSIPResponseElements::ConstructL()
    {

    }

void CT_DataSIPResponseElements::DestroyData()
    {
    if (iIsOwner)
        {
        delete iRespElems;
        iRespElems = NULL;
        iIsOwner = EFalse;
        }    
    }

TBool CT_DataSIPResponseElements::DoCommandL(const TTEFFunction& aCommand,
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
    else if (aCommand == KCmdNewL)
        {
        DoCmdNewL(aSection);
        }
    else if (aCommand == KCmdNewLC)
        {
        DoCmdNewLC(aSection);
        }
    else if (aCommand == KCmdReasonPhrase)
        {
        DoCmdReasonPhrase(aSection);
        }
    else if (aCommand == KCmdSetReasonPhraseL)
        {
        DoCmdSetReasonPhraseL(aSection);
        }
    else if (aCommand == KCmdSetStatusCodeL)
        {
        DoCmdSetStatusCodeL(aSection);
        }
    else if (aCommand == KCmdStatusCode)
        {
        DoCmdStatusCode(aSection);
        }
    else if (aCommand == KCmdToHeader)
        {
        DoCmdToHeader(aSection);
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

TAny* CT_DataSIPResponseElements::GetObject()
    {
    return iRespElems;
    }

void CT_DataSIPResponseElements::SetObjectL(TAny* aAny)
    {
    DestroyData();
    iRespElems = static_cast<CSIPResponseElements*> (aAny);
    }

void CT_DataSIPResponseElements::DisownObjectL()
    {
    iRespElems = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPResponseElements::DoCmdCSeqHeaderL(
        const TTEFSectionName& aSection)
    {
    TPtrC name;
    if (GetStringFromConfig(aSection, KFldSeqHeader, name))
        {
        INFO_PRINTF1(_L("execute CSIPResponseElements::CSeqHeader()"));
        const CSIPCSeqHeader* actual = iRespElems->CSeqHeader();
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

void CT_DataSIPResponseElements::DoCmdFromHeaderL(
        const TTEFSectionName& aSection)
    {
    TPtrC name;
    if (GetStringFromConfig(aSection, KFldFromHeader, name))
        {
        INFO_PRINTF1(_L("execute CSIPResponseElements::FromHeader()"));
        const CSIPFromHeader* actual = iRespElems->FromHeader();
        if (actual != NULL)
            {
            CT_DataSIPFromHeader* wrapper = static_cast<CT_DataSIPFromHeader*>(GetDataWrapperL(name));
            wrapper->SetIsOwner(EFalse);
            SetDataObjectL(name, (void*) actual);

            CSIPFromHeader* expected;
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
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldSeqHeader());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPResponseElements::DoCmdMessageElements(
        const TTEFSectionName& aSection)
    {
    TPtrC name;
    if (GetStringFromConfig(aSection, KFldMessageElements, name))
        {
        INFO_PRINTF1(_L("execute CSIPResponseElements::MessageElements()"));
        TBool modifiable = EFalse;
        const CSIPMessageElements* pMsgElems;
        (void) GetBoolFromConfig(aSection, KFldModifiable, modifiable);
        if (modifiable)
            {
            pMsgElems = &(iRespElems->MessageElements());
            }
        else
            {
            pMsgElems = &(((const CSIPResponseElements*) iRespElems)->MessageElements());
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

void CT_DataSIPResponseElements::DoCmdNewL(const TTEFSectionName& aSection)
    {
    TUint statusCode;
    if (GetTUintFromConfig(aSection, KFldStatusCode, statusCode))
        {
        RStringF reason;
        TPtrC reasonString;
        _LIT(KFldReasonPhraseString,               "reasonphrasestring");
        if (CT_SIPUtil::GetStringF(*this, aSection, KFldReasonPhrase, reason))
            {
            INFO_PRINTF1(_L("execute CSIPResponseElements::NewL(TUint, RStringF)"));
            TRAPD(err, iRespElems = CSIPResponseElements::NewL(statusCode, reason));
            if (err != KErrNone)
                {
                ERR_PRINTF2(KLogError, err);
                SetError(err);
                }
            else
                {
                iIsOwner = ETrue;
                }
            reason.Close();
            }
        else if (GetStringFromConfig(aSection, KFldReasonPhraseString, reasonString))
            {
            TBuf8<KMaxTestExecuteCommandLength> val8;
            CnvUtfConverter::ConvertFromUnicodeToUtf8(val8, reasonString);
            reason = SIPStrings::Pool().OpenFStringL( val8 );
            INFO_PRINTF1(_L("execute CSIPResponseElements::NewL(TUint, RStringF)"));
            TRAPD(err, iRespElems = CSIPResponseElements::NewL(statusCode, reason));
            if (err != KErrNone)
                {
                ERR_PRINTF2(KLogError, err);
                SetError(err);
                }
            else
                {
                iIsOwner = ETrue;
                }
            reason.Close();
            }
        else
            {
            ERR_PRINTF2(KMissingParameter, &KFldReasonPhrase());
            SetBlockResult(EFail);
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldStatusCode());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPResponseElements::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    TUint statusCode;
    if (GetTUintFromConfig(aSection, KFldStatusCode, statusCode))
        {
        RStringF reason;
        if (CT_SIPUtil::GetStringF(*this, aSection, KFldReasonPhrase, reason))
            {
            INFO_PRINTF1(_L("execute CSIPResponseElements::NewLC(TUint, RStringF)"));
            TRAPD(err, iRespElems = CSIPResponseElements::NewLC(statusCode, reason); CleanupStack::Pop(iRespElems));
            if (err != KErrNone)
                {
                ERR_PRINTF2(KLogError, err);
                SetError(err);
                }
            else
                {
                iIsOwner = ETrue;
                }
            reason.Close();
            }
        else
            {
            ERR_PRINTF2(KMissingParameter, &KFldReasonPhrase());
            SetBlockResult(EFail);
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldStatusCode());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPResponseElements::DoCmdReasonPhrase(
        const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("execute CSIPResponseElements::ReasonPhrase()"));
    RStringF actual = iRespElems->ReasonPhrase();
    TBuf<KMaxTestExecuteCommandLength> actual16;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(actual16, actual.DesC());
    actual.Close();
    INFO_PRINTF2(_L("Reason Phrase: %S"), &actual16);
    
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

void CT_DataSIPResponseElements::DoCmdSetReasonPhraseL(
        const TTEFSectionName& aSection)
    {
    RStringF reason;
    if (CT_SIPUtil::GetStringF(*this, aSection, KFldReasonPhrase, reason))
        {
        INFO_PRINTF1(_L("execute CSIPResponseElements::SetReasonPhraseL(RStringF)"));
        TRAPD(err, iRespElems->SetReasonPhraseL(reason));
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        reason.Close();
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldReasonPhrase());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPResponseElements::DoCmdSetStatusCodeL(
        const TTEFSectionName& aSection)
    {
    TUint statusCode;
    if (GetTUintFromConfig(aSection, KFldStatusCode, statusCode))
        {
        INFO_PRINTF1(_L("execute CSIPResponseElements::SetStatusCodeL(TUint)"));
        TRAPD(err, iRespElems->SetStatusCodeL(statusCode));
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldStatusCode());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPResponseElements::DoCmdStatusCode(
         const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("execute CSIPResponseElements::StatusCode()"));
    TUint actual = iRespElems->StatusCode();
    INFO_PRINTF2(_L("Status Code: %u"), actual);

    TUint expected;
    if (GetTUintFromConfig(aSection, KFldExpected, expected))
        {
        if (actual != expected)
            {
            ERR_PRINTF3(_L("actual value is not as expected, expected: %u, actual: %u"), expected, actual);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPResponseElements::DoCmdToHeader(
        const TTEFSectionName& aSection)
    {
    TPtrC name;
    if (GetStringFromConfig(aSection, KFldToHeader, name))
        {
        INFO_PRINTF1(_L("execute CSIPResponseElements::ToHeader()"));
        const CSIPToHeader* actual = iRespElems->ToHeader();
        if (actual != NULL)
            {
            CT_DataSIPFromHeader* wrapper = static_cast<CT_DataSIPFromHeader*>(GetDataWrapperL(name));
            wrapper->SetIsOwner(EFalse);
            SetDataObjectL(name, (void*) actual);

            CSIPToHeader* expected;
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
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldToHeader());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPResponseElements::DoCmdDestructor()
    {
    INFO_PRINTF1(_L("call CSIPResponseElements::~CSIPResponseElements()"));
    DestroyData();
    }

void CT_DataSIPResponseElements::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }
