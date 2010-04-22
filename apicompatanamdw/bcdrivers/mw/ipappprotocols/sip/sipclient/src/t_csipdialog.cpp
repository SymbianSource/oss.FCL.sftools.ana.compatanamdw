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


// This contains CT_DataSIPDialog
#include "t_csipdialog.h"
#include <utf.h>
#include <s32file.h>
#include <uri8.h> 
#include <sipregistrationcontext.h>
#include "T_SIPUtil.h"
#include <sipdialogassocbase.h> 
#include <sipinvitedialogassoc.h> 
#include <sipsubscribedialogassoc.h> 
#include "t_csipcallidheader.h"
#include "t_csipfromheader.h"
#include "t_csiptoheader.h"
#include "t_csipconnection.h"


/*@{*/
_LIT(KCallIdL,                      "CallIdL");
_LIT(KCmdConnection,                "Connection");
_LIT(KCmdFromHeader,                "FromHeader");
_LIT(KCmdIsAssociated,              "IsAssociated");
_LIT(KCmdRegistrationContext,       "RegistrationContext");
_LIT(KCmdRemoteURI,                 "RemoteURI");
_LIT(KCmdSIPDialogAssociations,     "SIPDialogAssociations");
_LIT(KCmdState,                     "State");
_LIT(KCmdToHeader,                  "ToHeader");
_LIT(KCmdOperatorEqualL,            "==");

// Fields 
_LIT(KFldSIPFromHeader,             "sipFromHeader");
_LIT(KFldSIPToHeader,               "sipToHeader");
_LIT(KFldSIPDialogAssoc,            "sipDialogAssoc");
_LIT(KFldSIPState,                  "sipState");
_LIT(KFldSIPCallIDHeader,           "sipCallIDHeader");
_LIT(KFldSIPDialog,                 "sipDialog");
_LIT(KFldExpected,                  "expected");
_LIT(KFldModifiable,                "modifiable");
_LIT(KFldSIPInviteDialogAssoc,      "sipInviteDlg");
_LIT(KFldSIPSubscribeDialogAssoc,   "sipSubscribeDlg");



// Error
_LIT(KLogError,                     "Error=%d");
_LIT(KMissingParameter,             "missing parameter '%S'");
//Info

CT_DataSIPDialog* CT_DataSIPDialog::NewL()
    {
    CT_DataSIPDialog* self = new (ELeave) CT_DataSIPDialog();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;    
    }

CT_DataSIPDialog::CT_DataSIPDialog()
: CDataWrapperBase(), iSIPDialog(NULL), iIsOwner(ETrue)
    {
    }

void CT_DataSIPDialog::ConstructL()
    {
    }

TAny* CT_DataSIPDialog::GetObject()
    {
    return iSIPDialog;
    }

void CT_DataSIPDialog::SetObjectL(TAny* aAny)
    {
    iSIPDialog = static_cast<CSIPDialog*>(aAny);
    }

void CT_DataSIPDialog::DisownObjectL()
    {
    iSIPDialog = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPDialog::DestroyData()
    {
    if(iIsOwner && iSIPDialog)
        {
        delete iSIPDialog;
        iSIPDialog = NULL;
        iIsOwner = EFalse;
        }
    }
TBool CT_DataSIPDialog::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
    {
    TBool ret = ETrue;
    if (aCommand == KCallIdL)
        {
        DoCmdCallIdL(aSection);
        }
    else if(aCommand == KCmdConnection)
        {
        DoCmdConnection(aSection);
        }
    else if(aCommand == KCmdFromHeader)
        {
        DoCmdFromHeader(aSection);
        }
    else if(aCommand == KCmdIsAssociated)
        {
        DoCmdIsAssociated(aSection);
        }
    else if(aCommand == KCmdRegistrationContext)
        {
        DoCmdRegistrationContext(aSection);
        } 
    else if(aCommand == KCmdRemoteURI)
        {
        DoCmdRemoteURI();
        }  
    else if(aCommand == KCmdSIPDialogAssociations)
        {
        DoCmdSIPDialogAssociations(aSection);
        }  
    else if(aCommand == KCmdState)
        {
        DoCmdState(aSection);
        }  
    else if(aCommand == KCmdToHeader)
        {
        DoCmdToHeader(aSection);
        }  
    else if(aCommand == KCmdOperatorEqualL)
        {
        DoCmdOperatorEqualL(aSection);
        }  
    else
        {
        ret = EFalse;
        }
    return ret;
    }

void CT_DataSIPDialog::DoCmdCallIdL(const TTEFSectionName& aSection)
    {
    TPtrC name;    
    if (!GetStringFromConfig(aSection, KFldSIPCallIDHeader, name))
        {
        ERR_PRINTF2(KMissingParameter, &KFldSIPCallIDHeader());
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("execute CSIPDialog::CallIdL()"));
        const CSIPCallIDHeader* sipCallIDHeader = NULL;
        TRAPD(err, sipCallIDHeader = &(iSIPDialog->CallIdL()));
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            SetDataObjectL(name,(void*)sipCallIDHeader);
            CT_DataSIPCallIDHeader* wrapper = static_cast<CT_DataSIPCallIDHeader*>(GetDataWrapperL(name));
            wrapper->SetIsOwner(EFalse);
            }
        }       
    }

void CT_DataSIPDialog::DoCmdConnection(const TTEFSectionName& aSection)
    {
    TPtrC name;
    TBool modifiable = EFalse;
    if(!GetStringFromConfig(aSection, KCmdConnection, name))
        {
        ERR_PRINTF2(KMissingParameter, &KCmdConnection());
        SetBlockResult(EFail);
        }
    else
        {
        (void)GetBoolFromConfig(aSection, KFldModifiable, modifiable);
        
        INFO_PRINTF1(_L("execute CSIPDialog::Connection()"));
        const CSIPConnection * pConnection = NULL;
        if (modifiable)
            {
            pConnection = iSIPDialog->Connection();
            }
        else
            {
            pConnection = ((const CSIPDialog*) iSIPDialog)->Connection();
            }
        SetDataObjectL(name, (void*)pConnection);
        CT_DataSIPConnection* wrapper = static_cast<CT_DataSIPConnection*>(GetDataWrapperL(name));
        wrapper->SetIsOwner(EFalse);
        }
    }

void CT_DataSIPDialog::DoCmdFromHeader(const TTEFSectionName& aSection)
    {
    TPtrC name;    
    if (!GetStringFromConfig(aSection, KFldSIPFromHeader, name))
        {
        ERR_PRINTF2(KMissingParameter, &KFldSIPFromHeader());
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("execute CSIPDialog::FromHeader()"));
        const CSIPFromHeader* sipFromHeader = NULL;
        TRAPD(err, sipFromHeader = &(iSIPDialog->FromHeader()));
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            SetDataObjectL(name,(void*)sipFromHeader);
            CT_DataSIPFromHeader* wrapper = static_cast<CT_DataSIPFromHeader*>(GetDataWrapperL(name));
            wrapper->SetIsOwner(EFalse);
            }
        }    
    }

void CT_DataSIPDialog::DoCmdIsAssociated(const TTEFSectionName& aSection)
    {
    TBool isAssociated = EFalse;
    TBool expected = EFalse;
    CSIPDialogAssocBase *dialogAssoc = NULL;
    TPtrC name;
    
    if (!GetStringFromConfig(aSection, KFldSIPDialogAssoc, name))
        {
        ERR_PRINTF2(KMissingParameter, &KFldSIPDialogAssoc());
        SetBlockResult(EFail);
        }
    else
        {
        dialogAssoc = static_cast<CSIPDialogAssocBase*> (GetDataObjectL(name));
        INFO_PRINTF1(_L("execute CSIPDialog::IsAssociated()"));
        isAssociated=iSIPDialog->IsAssociated(*dialogAssoc);
        INFO_PRINTF2(_L("isAssociated value is, isAssociated: %d"),isAssociated);
        if(GetBoolFromConfig(aSection, KFldExpected, expected))
            {
            if (!expected != !isAssociated)
                {
                ERR_PRINTF3(_L("actual value is not as expected, expected: %d, isAssociated: %d"), expected, isAssociated);
                SetBlockResult(EFail);
                }
            }
        }    
    }

void CT_DataSIPDialog::DoCmdRegistrationContext(const TTEFSectionName& aSection)
    {
    TInt contextId;
    TInt expected;

    INFO_PRINTF1(_L("execute CSIPDialog::RegistrationContext()"));      
    const MSIPRegistrationContext* sipRegistrationContext = iSIPDialog->RegistrationContext();
    contextId = sipRegistrationContext->ContextId();
    INFO_PRINTF2(_L("contextId value is, contextId: %d"),contextId);
    if(GetIntFromConfig(aSection, KFldExpected, expected))
        {
        if (contextId != expected)
            {
            ERR_PRINTF3(_L("actual value is not as expected, expected: %d, isAssociated: %d"), expected, contextId);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPDialog::DoCmdRemoteURI()
    {
    INFO_PRINTF1(_L("execute CSIPDialog::RemoteURI()"));
    const CUri8 &uri8 = iSIPDialog->RemoteURI();
    HBufC *fulluri = uri8.Uri().DisplayFormL(EUriComplete);
    INFO_PRINTF2(_L("Remote Uri is,fulluri: %s "),fulluri);
    }

void CT_DataSIPDialog::DoCmdSIPDialogAssociations(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("execute CSIPDialog::SIPDialogAssociations()"));
    const RPointerArray<CSIPDialogAssocBase> *actual = &(iSIPDialog->SIPDialogAssociations());

    TInt cnt = actual->Count();
    TBuf<KMaxTestExecuteCommandLength> tempName;
    TPtrC wrappername;
    for (TInt i = 0; i < cnt; ++i)
        {
        CnvUtfConverter::ConvertToUnicodeFromUtf8(tempName, (*actual)[i]->Type().DesC());
        INFO_PRINTF3(_L("CSIPDialogAssocBase [%d]: Type = %S"), i, &tempName);
        if(tempName.Compare(_L("INVITE"))==0)
            {
            if(GetStringFromConfig(aSection,KFldSIPInviteDialogAssoc,wrappername))
                {
                CSIPInviteDialogAssoc* invite = dynamic_cast<CSIPInviteDialogAssoc*>((*actual)[i]);
                SetDataObjectL(wrappername, invite);
                }
            }
        else if(tempName.Compare(_L("SUBSCRIBE"))==0)
            {
            if(GetStringFromConfig(aSection,KFldSIPSubscribeDialogAssoc,wrappername))
                {
                CSIPSubscribeDialogAssoc* subscribe = dynamic_cast<CSIPSubscribeDialogAssoc*>((*actual)[i]);
                SetDataObjectL(wrappername, subscribe);
                }
            }
        else
            {
            INFO_PRINTF2(KMissingParameter, &tempName);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPDialog::DoCmdState(const TTEFSectionName& aSection)
    {
    CSIPDialog::TState state;
    CSIPDialog::TState expected;
    TPtrC ptrstate;    

    INFO_PRINTF1(_L("execute CSIPDialog::State()"));
    state=iSIPDialog->State();
    INFO_PRINTF2(_L("state value is, state: %d"),state);
    if(CT_SIPUtil::GetSIPDialogState(*this, aSection, KFldSIPState, expected))
        {
        if(state != expected)
            {
            ERR_PRINTF3(_L("actual value is not as expected, expected: %d, state: %d"), expected, state);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPDialog::DoCmdToHeader(const TTEFSectionName& aSection)
    {
    TPtrC name;    
    if (!GetStringFromConfig(aSection, KFldSIPToHeader, name))
        {
        ERR_PRINTF2(KMissingParameter, &KFldSIPToHeader());
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("execute CSIPDialog::ToHeader()"));
        const CSIPToHeader* sipToHeader = NULL;
        TRAPD(err, sipToHeader = &(iSIPDialog->ToHeader()));
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            SetDataObjectL(name,(void*)sipToHeader);
            CT_DataSIPToHeader* wrapper = static_cast<CT_DataSIPToHeader*>(GetDataWrapperL(name));
            wrapper->SetIsOwner(EFalse);
            }
        }  
    }

void CT_DataSIPDialog::DoCmdOperatorEqualL(const TTEFSectionName& aSection)
    {
    CSIPDialog* sipDialog;
    TPtrC name;
    if (!GetStringFromConfig(aSection, KFldSIPDialog, name))
        {
        ERR_PRINTF2(KMissingParameter, &KFldSIPDialog());
        SetBlockResult(EFail);
        }
    else
        {
        sipDialog = static_cast<CSIPDialog*> (GetDataObjectL(name));
        INFO_PRINTF1(_L("execute CSIPDialog::operator==(const CSIPDialog &aDialog)"));
        TBool actual = (*iSIPDialog) == (*sipDialog);
        INFO_PRINTF2(_L("operator==() = %d"), actual);        
        TBool expected;
        if (GetBoolFromConfig(aSection, KFldExpected, expected))
            {
            if (!expected != !actual)
                {
                ERR_PRINTF3(_L("actual value is not as expected, expected: %d, actual: %d"), expected, actual);
                SetBlockResult(EFail);
                }
            }
        }
    }

CT_DataSIPDialog::~CT_DataSIPDialog()
    {
    DestroyData();
    }
    
void CT_DataSIPDialog::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }    
