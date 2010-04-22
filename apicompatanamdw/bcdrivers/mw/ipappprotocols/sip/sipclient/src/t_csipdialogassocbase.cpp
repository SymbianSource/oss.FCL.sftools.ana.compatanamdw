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
 * This contains CT_DataSIPDialogAssocBase
 */


#include "t_csipdialogassocbase.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <sipclienttransaction.h>
#include "t_csipdialog.h"
#include "t_csipmessageelements.h"


/*@{*/
_LIT(KCmdDialog,                                          "Dialog");
_LIT(KCmdSendNonTargetRefreshRequestL,                    "SendNonTargetRefreshRequestL");
_LIT(KCmdType,                                            "Type");
_LIT(KCmdIsNonTargetRefreshRequest,                       "IsNonTargetRefreshRequest");

//Fields 
_LIT(KFldBeConst,                                         "beconst");
_LIT(KFldSIPDialog,                                       "sipdialog");
_LIT(KFldRStringFMethod,                                  "stringfmethod");
_LIT(KFldSIPMessageElements,                              "sipmessageelements");
_LIT(KFldExpected,                                        "expected");
_LIT(KFldSIPClientTransaction,                            "ClientTransaction");

// Logging
_LIT(KLogError,                                           "Error=%d");
_LIT(KLogMissingParameter,                                "Missing parameter '%S'");
_LIT(KLogNotExpectedValue,                                "Not expected value, actual=%d, expect=%d");

CT_DataSIPDialogAssocBase::CT_DataSIPDialogAssocBase() :
CDataWrapperBase()
    {
    }

TBool CT_DataSIPDialogAssocBase::DoCommandL(const TTEFFunction& aCommand,
        const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
    {
    TBool ret = ETrue;

    if (aCommand == KCmdDialog)
        {
        DoCmdDialog(aSection);
        }
    else if (aCommand == KCmdSendNonTargetRefreshRequestL)
        {
        DoCmdSendNonTargetRefreshRequestL(aSection);
        }
    else if (aCommand == KCmdType)
        {
        DoCmdType(aSection);
        }
    else if (aCommand == KCmdIsNonTargetRefreshRequest)
        {
        DoCmdIsNonTargetRefreshRequest(aSection);
        }
    else
        {
        ret = EFalse;
        }       
    return ret;
    }

void CT_DataSIPDialogAssocBase::DoCmdDialog(const TTEFSectionName& aSection)
    {
    TBool beconst=EFalse;
    TPtrC datsipdialog;
    if (!GetStringFromConfig(aSection, KFldSIPDialog, datsipdialog))
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSIPDialog);
        SetBlockResult(EFail);
        return;
        }
    GetBoolFromConfig(aSection, KFldBeConst, beconst);
    if(beconst)
        {
        const CSIPDialog *sipdialog = NULL;
        INFO_PRINTF1(_L("call CSIPDialogAssocBase::Dialog() const"));
        sipdialog=&(((const CSIPDialogAssocBase*)GetSIPDialogAssocBase())->Dialog());
        CT_DataSIPDialog* wrapper = static_cast<CT_DataSIPDialog*>(GetDataWrapperL(datsipdialog));
        wrapper->SetIsOwner(EFalse);
        SetDataObjectL(datsipdialog, (CSIPDialog*)sipdialog);
        }
    else
        {
        CSIPDialog *sipdialog = NULL;
        INFO_PRINTF1(_L("call CSIPDialogAssocBase::Dialog();"));        
        sipdialog=&(((CSIPDialogAssocBase*)GetSIPDialogAssocBase())->Dialog());
        CT_DataSIPDialog* wrapper = static_cast<CT_DataSIPDialog*>(GetDataWrapperL(datsipdialog));
        wrapper->SetIsOwner(EFalse);
        SetDataObjectL(datsipdialog, sipdialog);
        }     
    }

void CT_DataSIPDialogAssocBase::DoCmdSendNonTargetRefreshRequestL(const TTEFSectionName& aSection)
    {
    RStringF strfmethod;
    RStringPool pool;
    TPtrC datMessageElmts;
    TPtrC datClientTransctn;
    CSIPClientTransaction* clientTransaction = NULL;
    if (!CT_SIPUtil::GetStringFFromConfigL(*this, aSection, KFldRStringFMethod, pool, strfmethod))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldRStringFMethod());
        SetBlockResult(EFail);
        return;
        }
    if (!GetStringFromConfig(aSection, KFldSIPMessageElements , datMessageElmts)) 
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSIPMessageElements);
        SetBlockResult(EFail);
        return;
        }
    CSIPMessageElements* messageElmts = static_cast<CSIPMessageElements*>(GetDataObjectL(datMessageElmts));
    INFO_PRINTF1(_L("call CSIPDialogAssocBase::SendNonTargetRefreshRequestL(RStringF,CSIPMessageElements*)"));
    TRAPD(err, clientTransaction = GetSIPDialogAssocBase()->SendNonTargetRefreshRequestL(strfmethod, messageElmts));
    strfmethod.Close();
    pool.Close();
    CT_DataSIPMessageElements* wrapper = static_cast<CT_DataSIPMessageElements*>(GetDataWrapperL(datMessageElmts));
    wrapper->SetIsOwner(EFalse);
    if(err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    else if(GetStringFromConfig(aSection, KFldSIPClientTransaction, datClientTransctn))
        {
        SetDataObjectL(datClientTransctn, clientTransaction);
        } 
    else
        {
        delete clientTransaction;
        }
    }

void CT_DataSIPDialogAssocBase::DoCmdType(const TTEFSectionName& aSection)
    {
    TPtrC expectedRstrF;
    INFO_PRINTF1(_L("call CSIPDialogAssocBase::Type()"));
    RStringF  retstrf = GetSIPDialogAssocBase()->Type();
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

void CT_DataSIPDialogAssocBase::DoCmdIsNonTargetRefreshRequest(const TTEFSectionName& aSection)
    {
    TBool expectedret = EFalse;
    RStringF strfmethod;
    
    if (!CT_SIPUtil::GetStringF(*this, aSection, KFldRStringFMethod, strfmethod))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldRStringFMethod());
        SetBlockResult(EFail);
        return;
        }
    INFO_PRINTF1(_L("call CSIPDialogAssocBase::IsNonTargetRefreshRequest(RStringF)"));
    TBool ret = GetSIPDialogAssocBase()->IsNonTargetRefreshRequest(strfmethod);  
    INFO_PRINTF2(_L("Tests if the request is a non target refresh request: %d"), (TInt)ret);
    if( GetBoolFromConfig(aSection, KFldExpected, expectedret) )
        {
        if(!ret != !expectedret)
            {
            ERR_PRINTF3(KLogNotExpectedValue, (TInt)ret, (TInt)expectedret);
            SetBlockResult(EFail);
            }
        }
    }
