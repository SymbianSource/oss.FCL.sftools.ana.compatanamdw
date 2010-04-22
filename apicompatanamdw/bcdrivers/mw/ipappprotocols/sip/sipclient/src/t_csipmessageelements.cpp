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

#include "t_csipmessageelements.h"
#include "t_csipcontenttypeheader.h"
#include "t_csipheaderbase.h"
#include "T_SIPUtil.h"
#include <sipmessageelements.h>
#include <sipcontenttypeheader.h>
#include <utf.h>

// Command
_LIT(KCmdContent,           "Content");
_LIT(KCmdContentType,       "ContentType");
_LIT(KCmdExtractContent,    "ExtractContent");
_LIT(KCmdNewL,              "NewL");
_LIT(KCmdNewLC,             "NewLC");
_LIT(KCmdSetContentL,       "SetContentL");
_LIT(KCmdSetUserHeadersL,   "SetUserHeadersL");
_LIT(KCmdUserHeaders,       "UserHeaders");
_LIT(KCmdDestructor,        "~");

// Field
_LIT(KFldExpected, "expected");
_LIT(KFldContent, "content");
_LIT(KFldContentTypeHeader, "contenttypeheader");

_LIT(KFormatFieldNumber,                        "%S%d");

// Error
_LIT(KLogError, "Error=%d");
_LIT(KMissingParameter, "missing parameter '%S'");

CT_DataSIPMessageElements* CT_DataSIPMessageElements::NewL()
    {
    CT_DataSIPMessageElements* self = new (ELeave) CT_DataSIPMessageElements();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

CT_DataSIPMessageElements::~CT_DataSIPMessageElements()
    {
    DestroyData();
    }

CT_DataSIPMessageElements::CT_DataSIPMessageElements() :
    CDataWrapperBase(), iMsgElems(NULL), iIsOwner(ETrue)
    {
    }

void CT_DataSIPMessageElements::ConstructL()
    {

    }

void CT_DataSIPMessageElements::DestroyData()
    {
    if (iIsOwner)
        {
        delete iMsgElems;
        iMsgElems = NULL;
        iIsOwner = EFalse;
        }
    }

void CT_DataSIPMessageElements::DoCmdDestructor()
    {
    INFO_PRINTF1(_L("call CSIPClientTransaction::~CSIPMessageElements()"));
    DestroyData();
    }

TBool CT_DataSIPMessageElements::DoCommandL(const TTEFFunction& aCommand,
        const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
    {
    TBool ret = ETrue;
    if (aCommand == KCmdContent)
        {
        DoCmdContent(aSection);
        }
    else if (aCommand == KCmdContentType)
        {
        DoCmdContentTypeL(aSection);
        }
    else if (aCommand == KCmdExtractContent)
        {
        DoCmdExtractContent(aSection);
        }
    else if (aCommand == KCmdNewL)
        {
        DoCmdNewL(aSection);
        }
    else if (aCommand == KCmdNewLC)
        {
        DoCmdNewLC(aSection);
        }
    else if (aCommand == KCmdSetContentL)
        {
        DoCmdSetContentL(aSection);
        }
    else if (aCommand == KCmdSetUserHeadersL)
        {
        DoCmdSetUserHeadersL(aSection);
        }
    else if (aCommand == KCmdUserHeaders)
        {
        DoCmdUserHeaders(aSection);
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

TAny* CT_DataSIPMessageElements::GetObject()
    {
    return iMsgElems;
    }

void CT_DataSIPMessageElements::SetObjectL(TAny* aAny)
    {
    DestroyData();
    iMsgElems = static_cast<CSIPMessageElements*> (aAny);
    }

void CT_DataSIPMessageElements::DisownObjectL()
    {
    iMsgElems = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPMessageElements::DoCmdContent(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("execute CSIPMessageElements::Content()"));
    const TPtrC8 val = iMsgElems->Content();

    TPtrC expected;
    if (GetStringFromConfig(aSection, KFldExpected, expected))
        {
        TBuf<KMaxTestExecuteCommandLength> actual;
        CnvUtfConverter::ConvertToUnicodeFromUtf8(actual, val);
        if (expected.Compare(actual) != 0)
            {
            ERR_PRINTF3(_L("actual value is not as expected, expected: %S, actual: %S"), &expected, &actual);
            SetBlockResult(EFail);
            }
        }
    else{
        INFO_PRINTF2(_L("Content: %S"), &val);
        }
    }

void CT_DataSIPMessageElements::DoCmdContentTypeL(
        const TTEFSectionName& aSection)
    {
    TPtrC name;
    if (GetStringFromConfig(aSection, KFldContentTypeHeader, name))
        {
        INFO_PRINTF1(_L("execute CSIPMessageElements::ContentType()"));
        const CSIPContentTypeHeader* actual = iMsgElems->ContentType();
        if (actual != NULL)
            {
            CT_DataSIPContentTypeHeader* wrapper = static_cast<CT_DataSIPContentTypeHeader*>(GetDataWrapperL(name));
            wrapper->SetIsOwner(EFalse);
            SetDataObjectL(name, (void*) actual);
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldContentTypeHeader());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPMessageElements::DoCmdExtractContent(
        const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("execute CSIPMessageElements::ExtractContent()"));
    HBufC8* val = iMsgElems->ExtractContent();

    TPtrC expected;
    if (GetStringFromConfig(aSection, KFldExpected, expected))
        {
        TBuf<KMaxTestExecuteCommandLength> actual;
        CnvUtfConverter::ConvertToUnicodeFromUtf8(actual, val->Des());
        if (expected.Compare(actual) != 0)
            {
            ERR_PRINTF3(_L("actual value is not as expected, expected: %S, actual: %S"), &expected, &actual);
            SetBlockResult(EFail);
            }
        }
    delete val;
    }

void CT_DataSIPMessageElements::DoCmdNewL(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("execute CSIPMessageElements::NewL()"));
    TRAPD(err, iMsgElems = CSIPMessageElements::NewL());
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

void CT_DataSIPMessageElements::DoCmdNewLC(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("execute CSIPMessageElements::NewLC()"));
    TRAPD(err, iMsgElems = CSIPMessageElements::NewLC(); CleanupStack::Pop(iMsgElems));
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

void CT_DataSIPMessageElements::DoCmdSetContentL(
        const TTEFSectionName& aSection)
    {
    TPtrC val;
    HBufC8* content = NULL;
    CSIPContentTypeHeader* contentTypeHdr = NULL;
    TInt err = KErrNone;

    // Ignore the returned values so that negative cases can be designed.
    (void)CT_SIPUtil::GetSIPContentTypeHeaderFromConfigL(*this, aSection, KFldContentTypeHeader, contentTypeHdr);
    
    if(CT_SIPUtil::iContent)
        {
        content = CT_SIPUtil::iContent;
        }
    else
        {
        (void)GetStringFromConfig(aSection, KFldContent, val);
        if (val.Length() != 0)
            {
            // For positive cases.
            TBuf8<KMaxTestExecuteCommandLength> val8;
            CnvUtfConverter::ConvertFromUnicodeToUtf8(val8, val);
            TRAP(err, content = HBufC8::NewL(val8.Length()));
            if (err != KErrNone)
                {
                ERR_PRINTF2(KLogError, err);
                SetError(err);
                return;
                }
            (*content) = val8;
            }
        }
    
    INFO_PRINTF1(_L("execute CSIPMessageElements::SetContentL(HBufC8*, CSIPContentTypeHeader*)"));
    TRAP(err, iMsgElems->SetContentL(content, contentTypeHdr));
    if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    else
        {
        CT_SIPUtil::iContent = NULL;
        
        TPtrC name;
        if (GetStringFromConfig(aSection, KFldContentTypeHeader, name))
            {
            CT_DataSIPContentTypeHeader* wrapper = static_cast<CT_DataSIPContentTypeHeader*>(GetDataWrapperL(name));
            wrapper->SetIsOwner(EFalse);
            }
        }
    }

void CT_DataSIPMessageElements::DoCmdSetUserHeadersL(
        const TTEFSectionName& aSection)
    {
    RPointerArray<CSIPHeaderBase> array;

    (void)CT_SIPUtil::GetSIPHeadersL(*this, aSection, KFldContentTypeHeader, array);
    INFO_PRINTF1(_L("execute CSIPMessageElements::SetUserHeadersL(RPointerArray<CSIPHeaderBase> &)"));
    TRAPD(err, iMsgElems->SetUserHeadersL(array));
    if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    else
        {
        // Transfer ownership
        TBool moreData = ETrue;
        TBuf<KMaxTestExecuteNameLength>  tempStore;
        TInt index;
        TPtrC name;
        for (index = 1; moreData; ++index)
            {
            TPtrC name;
            tempStore.Format(KFormatFieldNumber, &KFldContentTypeHeader, index);
            if (!GetStringFromConfig(aSection, tempStore, name))
                {
                moreData = EFalse;
                }
            else
                {
                CT_DataSIPHeaderBase* wrapper = static_cast<CT_DataSIPHeaderBase*> (GetDataWrapperL(name));
                wrapper->SetIsOwner(EFalse);
                }
            }
        }
    array.Close();
    }

void CT_DataSIPMessageElements::DoCmdUserHeaders(
        const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("execute CSIPMessageElements::UserHeaders()"));
    const RPointerArray<CSIPHeaderBase>* actual = &(iMsgElems->UserHeaders());
    
    // TODO: Maybe need to verify the whole array.
    TInt cnt = actual->Count();
    TBuf<KMaxTestExecuteCommandLength> tempName;
    for (TInt i = 0; i < cnt; ++i)
        {
        CnvUtfConverter::ConvertToUnicodeFromUtf8(tempName, (*actual)[i]->Name().DesC());
        INFO_PRINTF3(_L("CSIPHeaderBase [%d]: Name = %S"), i, &tempName);
        }
    }

void CT_DataSIPMessageElements::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }

//
//TBool CT_DataSIPMessageElements::CompareSIPContentTypeHeader(const CSIPContentTypeHeader& aActual, const CSIPContentTypeHeader& aExpected)
//    {
//    if    (aActual.MediaSubtype().Compare(aExpected.MediaSubtype()) != 0
//            || aActual.MediaType().Compare(aExpected.MediaType()) != 0
//            /*|| aActual.Name() != aExpected.Name()*/)
//        {
//        ERR_PRINTF1(_L("actual value is not as expected"));
////        ERR_PRINTF3(_L("expected Name: %S, actual Name: %S"), aExpected.Name(), aActual.Name());
//        ERR_PRINTF3(_L("expected MediaType: %S, actual MediaType: %S"), &(aExpected.MediaType()), &(aActual.MediaType()));
//        ERR_PRINTF3(_L("expected MediaSubtype: %S, actual MediaSubtype: %S"), &(aExpected.MediaSubtype()), &(aActual.MediaSubtype()));
//        return EFalse;
//        }
//    else
//        {
//        return ETrue;
//        }
//    }
