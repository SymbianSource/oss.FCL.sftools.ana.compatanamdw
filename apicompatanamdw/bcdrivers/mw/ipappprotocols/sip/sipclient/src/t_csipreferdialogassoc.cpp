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


// This contains CT_DataSIPReferDialogAssoc

#include "t_csipreferdialogassoc.h"
#include "t_csiprefertoheader.h"
#include "t_csipfromheader.h"
#include "t_csiptoheader.h"
#include "t_csipcontactheader.h"
#include "t_csipmessageelements.h"
#include "T_SIPUtil.h"
#include <utf.h> 
#include <sipprofile.h>

/*@{*/
_LIT(KCmdNewL,					"NewL");
_LIT(KCmdNewLC,                 "NewLC");
_LIT(KCmdSendReferL,            "SendReferL");
_LIT(KCmdReferTo,               "ReferTo");
_LIT(KCmdDestructor,            "~");

_LIT(KFldSIPDialog,             "sipdialog");
_LIT(KFldSIPConnection,         "sipconnection");
_LIT(KFldSIPReferToHeader,      "siprefertoheader");
_LIT(KFldSIPFromHeader,         "sipfromheader");
_LIT(KFldSIPToHeader,           "siptoheader");
_LIT(KFldSIPContactHeader,      "sipcontactheader");
_LIT(KFldUri8,                  "uri8");
_LIT(KFldSIPClientTransaction,  "sipclienttransaction"); 
_LIT(KFldSIPMessageElements,    "sipmessageelements");
_LIT(KFldSIPRegistrationContext,"sipregistrationcontext");

_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");
/*}@*/


CT_DataSIPReferDialogAssoc*  CT_DataSIPReferDialogAssoc::NewL()
    {
    CT_DataSIPReferDialogAssoc* self = new (ELeave) CT_DataSIPReferDialogAssoc();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;    
    }

CT_DataSIPReferDialogAssoc::~CT_DataSIPReferDialogAssoc()
    {
    DestroyData();
    }

CT_DataSIPReferDialogAssoc::CT_DataSIPReferDialogAssoc()
:   CT_DataSIPDialogAssocBase(), iSIPReferDialogAssoc(NULL), iIsOwner(ETrue)
	{
	}

void CT_DataSIPReferDialogAssoc::ConstructL()
    {
    }

TAny* CT_DataSIPReferDialogAssoc::GetObject()
    {
    return iSIPReferDialogAssoc;
    }

void CT_DataSIPReferDialogAssoc::SetObjectL(TAny* aAny)
    {
    iSIPReferDialogAssoc = static_cast<CSIPReferDialogAssoc*>(aAny);
    }

void CT_DataSIPReferDialogAssoc::DisownObjectL()
    {
    iSIPReferDialogAssoc = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPReferDialogAssoc::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

void CT_DataSIPReferDialogAssoc::DestroyData()
    {
    if (iIsOwner)
        {
        delete iSIPReferDialogAssoc;
        iSIPReferDialogAssoc = NULL;
        iIsOwner = EFalse;
        }
    }

CSIPDialogAssocBase* CT_DataSIPReferDialogAssoc::GetSIPDialogAssocBase() const
    {
    return iSIPReferDialogAssoc;
    }

/**
Delegates the commands to a function

* @internalComponent
* @param aCommand Current command
* @param aSection Current ini file command section
* @param aAsyncErrorIndex index of command for SetAsyncError()
* @return TBool Returns whether the command was executed or not
*/
TBool CT_DataSIPReferDialogAssoc::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
	{
	TBool	retVal = ETrue;

    if( aCommand == KCmdNewL )
        {
        DoCmdNewL(aSection);
        }
    else if( aCommand == KCmdNewLC )
        {
        DoCmdNewLC(aSection);
        }
    else if( aCommand == KCmdSendReferL )
        {
        DoCmdSendReferL(aSection);
        }
    else if( aCommand == KCmdReferTo)
        {
        DoCmdReferToL(aSection);
        }
    else if( aCommand == KCmdDestructor)
        {
        DoCmdDestructor(aSection);
        }
	else
		{
		retVal = CT_DataSIPDialogAssocBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);;
		}
	return retVal;  
	}

void CT_DataSIPReferDialogAssoc::DoCmdNewL(const TTEFSectionName& aSection)
    {
    CSIPReferToHeader* refertoheader = NULL;
    if( !CT_SIPUtil::GetSIPReferToHeaderL(*this, aSection, KFldSIPReferToHeader, refertoheader) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSIPReferToHeader);
        SetBlockResult(EFail);
        }
    else
        {
        CSIPDialog* sipdialog = NULL;
        if( CT_SIPUtil::GetSIPDialogL(*this, aSection, KFldSIPDialog, sipdialog) )
            {
            INFO_PRINTF1(_L("call CSIPReferDialogAssoc::NewL(CSIPDialog&, CSIPReferToHeader*)"));
            TRAPD(err, iSIPReferDialogAssoc = CSIPReferDialogAssoc::NewL(*sipdialog, refertoheader));
            
            if(KErrNone != err)
                {
                ERR_PRINTF2(KLogError, err);
                SetError(err);
                }
            if(refertoheader != NULL)
                {
                TPtrC wrappername;
                (void) GetStringFromConfig(aSection, KFldSIPReferToHeader, wrappername);
                CT_DataSIPReferToHeader* wrapper = static_cast<CT_DataSIPReferToHeader*>(GetDataWrapperL(wrappername));
                wrapper->SetIsOwner(EFalse);
                }
            }
        else
            {
            CSIPConnection* conn = NULL;
            if( !CT_SIPUtil::GetSIPConnectionL(*this, aSection, KFldSIPConnection, conn) )
                {
                ERR_PRINTF2(KLogMissingParameter, KFldSIPConnection);
                SetBlockResult(EFail);
                return;
                }

            CUri8* uri = NULL;
            // Ignore the return value so that we can design negative cases.
            (void)CT_SIPUtil::GetUri8L(*this, aSection, KFldUri8, uri);
            
            TBool noErrors = EFalse;
            CSIPFromHeader* fromheader = NULL;
            
            CSIPToHeader* toheader = NULL;
            (void) CT_SIPUtil::GetSIPToHeaderL(*this, aSection, KFldSIPToHeader, toheader);
            
            CSIPContactHeader* contactheader = NULL;
            (void) CT_SIPUtil::GetSIPContactHeaderL(*this, aSection, KFldSIPContactHeader, contactheader);

            CSIPProfile* context = NULL;
            if( !CT_SIPUtil::GetSIPProfile(*this, aSection, KFldSIPRegistrationContext, context) )
                {                
                (void) CT_SIPUtil::GetSIPFromHeaderL(*this, aSection, KFldSIPFromHeader, fromheader);
                
                INFO_PRINTF1(_L("call CSIPReferDialogAssoc::NewL(CSIPConnection&, CSIPFromHeader*, CUri8*, CSIPReferToHeader*, CSIPToHeader*aTo=0, CSIPContactHeader*aContact=0)"));
                TRAPD(err, iSIPReferDialogAssoc = CSIPReferDialogAssoc::NewL(*conn, fromheader, 
                        uri, refertoheader, toheader, contactheader));
                
                if(KErrNone != err)
                    {
                    ERR_PRINTF2(KLogError, err);
                    SetError(err);
                    }
                else
                    {
                    noErrors = ETrue;
                    }
                }
            else
                {
                if( !CT_SIPUtil::GetSIPFromHeaderL(*this, aSection, KFldSIPFromHeader, fromheader) )
                    {
                    ERR_PRINTF2(KLogMissingParameter, KFldSIPFromHeader);
                    SetBlockResult(EFail);
                    }
                else
                    {
                    INFO_PRINTF1(_L("call CSIPReferDialogAssoc::NewL(CSIPConnection&, CUri8*, const MSIPRegistrationContext&, CSIPReferToHeader*, CSIPFromHeader*aFrom=0, CSIPToHeader*aTo=0, CSIPContactHeader*aContact=0)"));
                    TRAPD(err, iSIPReferDialogAssoc = CSIPReferDialogAssoc::NewL(*conn, uri, *context, 
                            refertoheader, fromheader, toheader, contactheader));
                    
                    if(KErrNone != err)
                        {
                        ERR_PRINTF2(KLogError, err);
                        SetError(err);
                        }
                    else
                        {
                        noErrors = ETrue;
                        }
                    }
                }
            
            if(noErrors)
                {
                if(refertoheader != NULL)
                    {
                    TPtrC wrappername;
                    (void) GetStringFromConfig(aSection, KFldSIPReferToHeader, wrappername);
                    CT_DataSIPReferToHeader* wrapper = static_cast<CT_DataSIPReferToHeader*>(GetDataWrapperL(wrappername));
                    wrapper->SetIsOwner(EFalse);
                    }
                
                if(fromheader != NULL)
                    {
                    TPtrC wrappername;
                    (void) GetStringFromConfig(aSection, KFldSIPFromHeader, wrappername);
                    CT_DataSIPFromHeader* wrapper = static_cast<CT_DataSIPFromHeader*>(GetDataWrapperL(wrappername));
                    wrapper->SetIsOwner(EFalse);
                    }
                
                if(toheader != NULL)
                    {
                    TPtrC wrappername;
                    (void) GetStringFromConfig(aSection, KFldSIPToHeader, wrappername);
                    CT_DataSIPToHeader* wrapper = static_cast<CT_DataSIPToHeader*>(GetDataWrapperL(wrappername));
                    wrapper->SetIsOwner(EFalse);
                    }
                
                if(contactheader != NULL)
                    {
                    TPtrC wrappername;
                    (void) GetStringFromConfig(aSection, KFldSIPContactHeader, wrappername);
                    CT_DataSIPContactHeader* wrapper = static_cast<CT_DataSIPContactHeader*>(GetDataWrapperL(wrappername));
                    wrapper->SetIsOwner(EFalse);
                    }
                }
            }
        }
    }

void CT_DataSIPReferDialogAssoc::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    CSIPReferToHeader* refertoheader = NULL;
    if( !CT_SIPUtil::GetSIPReferToHeaderL(*this, aSection, KFldSIPReferToHeader, refertoheader) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPReferToHeader);
        SetBlockResult(EFail);
        }
    else
        {
        CSIPDialog* sipdialog = NULL;
        if( CT_SIPUtil::GetSIPDialogL(*this, aSection, KFldSIPDialog, sipdialog) )
            {
            INFO_PRINTF1(_L("call CSIPReferDialogAssoc::NewLC(CSIPDialog&, CSIPReferToHeader*)"));
            TRAPD(err, iSIPReferDialogAssoc = CSIPReferDialogAssoc::NewLC(*sipdialog, refertoheader); CleanupStack::Pop());
            
            if(KErrNone != err)
                {
                ERR_PRINTF2(KLogError, err);
                SetError(err);
                }
            if(refertoheader != NULL)
                {
                TPtrC wrappername;
                (void) GetStringFromConfig(aSection, KFldSIPReferToHeader, wrappername);
                CT_DataSIPReferToHeader* wrapper = static_cast<CT_DataSIPReferToHeader*>(GetDataWrapperL(wrappername));
                wrapper->SetIsOwner(EFalse);
                }
            }
        else
            {
            CSIPConnection* conn = NULL;
            if( !CT_SIPUtil::GetSIPConnectionL(*this, aSection, KFldSIPConnection, conn) )
                {
                ERR_PRINTF2(KLogMissingParameter, KFldSIPConnection);
                SetBlockResult(EFail);
                return;
                }

            CUri8* uri = NULL;

            // Ignore the return value so that we can design negative cases.
            (void)CT_SIPUtil::GetUri8L(*this, aSection, KFldUri8, uri);
            
            TBool noErrors = EFalse;
            CSIPFromHeader* fromheader = NULL;
            
            CSIPToHeader* toheader = NULL;
            (void) CT_SIPUtil::GetSIPToHeaderL(*this, aSection, KFldSIPToHeader, toheader);
            
            CSIPContactHeader* contactheader = NULL;
            (void) CT_SIPUtil::GetSIPContactHeaderL(*this, aSection, KFldSIPContactHeader, contactheader);

            CSIPProfile* context = NULL;
            if( !CT_SIPUtil::GetSIPProfile(*this, aSection, KFldSIPRegistrationContext, context) )
                {                
                (void) CT_SIPUtil::GetSIPFromHeaderL(*this, aSection, KFldSIPFromHeader, fromheader);
                
                INFO_PRINTF1(_L("call CSIPReferDialogAssoc::NewLC(CSIPConnection&, CSIPFromHeader*, CUri8*, CSIPReferToHeader*, CSIPToHeader*aTo=0, CSIPContactHeader*aContact=0)"));
                TRAPD(err, iSIPReferDialogAssoc = CSIPReferDialogAssoc::NewLC(*conn, fromheader, 
                        uri, refertoheader, toheader, contactheader); CleanupStack::Pop());
                
                if(KErrNone != err)
                    {
                    ERR_PRINTF2(KLogError, err);
                    SetError(err);
                    }
                else
                    {
                    noErrors = ETrue;
                    }
                }
            else
                {
                if( !CT_SIPUtil::GetSIPFromHeaderL(*this, aSection, KFldSIPFromHeader, fromheader) )
                    {
                    ERR_PRINTF2(KLogMissingParameter, KFldSIPFromHeader);
                    SetBlockResult(EFail);
                    }
                else
                    {
                    INFO_PRINTF1(_L("call CSIPReferDialogAssoc::NewLC(CSIPConnection&, CUri8*, const MSIPRegistrationContext&, CSIPReferToHeader*, CSIPFromHeader*aFrom=0, CSIPToHeader*aTo=0, CSIPContactHeader*aContact=0)"));
                    TRAPD(err, iSIPReferDialogAssoc = CSIPReferDialogAssoc::NewLC(*conn, uri, *context, 
                            refertoheader, fromheader, toheader, contactheader); CleanupStack::Pop());
                    
                    if(KErrNone != err)
                        {
                        ERR_PRINTF2(KLogError, err);
                        SetError(err);
                        }
                    else
                        {
                        noErrors = ETrue;
                        }
                    }
                }
            
            if(noErrors)
                {
                if(refertoheader != NULL)
                    {
                    TPtrC wrappername;
                    (void) GetStringFromConfig(aSection, KFldSIPReferToHeader, wrappername);
                    CT_DataSIPReferToHeader* wrapper = static_cast<CT_DataSIPReferToHeader*>(GetDataWrapperL(wrappername));
                    wrapper->SetIsOwner(EFalse);
                    }
                
                if(fromheader != NULL)
                    {
                    TPtrC wrappername;
                    (void) GetStringFromConfig(aSection, KFldSIPFromHeader, wrappername);
                    CT_DataSIPFromHeader* wrapper = static_cast<CT_DataSIPFromHeader*>(GetDataWrapperL(wrappername));
                    wrapper->SetIsOwner(EFalse);
                    }
                
                if(toheader != NULL)
                    {
                    TPtrC wrappername;
                    (void) GetStringFromConfig(aSection, KFldSIPToHeader, wrappername);
                    CT_DataSIPToHeader* wrapper = static_cast<CT_DataSIPToHeader*>(GetDataWrapperL(wrappername));
                    wrapper->SetIsOwner(EFalse);
                    }
                
                if(contactheader != NULL)
                    {
                    TPtrC wrappername;
                    (void) GetStringFromConfig(aSection, KFldSIPContactHeader, wrappername);
                    CT_DataSIPContactHeader* wrapper = static_cast<CT_DataSIPContactHeader*>(GetDataWrapperL(wrappername));
                    wrapper->SetIsOwner(EFalse);
                    }
                }
            }
        }
    }

void CT_DataSIPReferDialogAssoc::DoCmdSendReferL(const TTEFSectionName& aSection)
    {
    TPtrC wrapperName;
    if( !GetStringFromConfig(aSection, KFldSIPClientTransaction, wrapperName) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSIPClientTransaction);
        SetBlockResult(EFail);
        }
    else
        {
        CSIPMessageElements* elems = NULL;
        (void*) CT_SIPUtil::GetSIPMessageElements(*this, aSection, KFldSIPMessageElements, elems);
        INFO_PRINTF1(_L("call CSIPReferDialogAssoc::SendReferL(CSIPMessageElements*)"));
        const CSIPClientTransaction* ret = NULL;
        TRAPD(err, ret = iSIPReferDialogAssoc->SendReferL(elems));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            } 
        else
            {
            if(elems != NULL)
                {
                (void)GetStringFromConfig(aSection, KFldSIPMessageElements, wrapperName);
                CT_DataSIPMessageElements* data = static_cast<CT_DataSIPMessageElements*>(GetDataWrapperL(wrapperName));
                data->SetIsOwner(EFalse);
                }
            SetDataObjectL(wrapperName, (CSIPClientTransaction*)ret);
            }
        }
    }

void CT_DataSIPReferDialogAssoc::DoCmdReferToL(const TTEFSectionName& aSection)
    {

    TPtrC wrapperName;
    if( !GetStringFromConfig(aSection, KFldSIPReferToHeader, wrapperName) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSIPReferToHeader);
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPReferDialogAssoc::ReferTo()"));
        const CSIPReferToHeader& ret = iSIPReferDialogAssoc->ReferTo();
        
        CT_DataSIPReferToHeader* wrapper = static_cast<CT_DataSIPReferToHeader*>(GetDataWrapperL(wrapperName));
        wrapper->SetIsOwner(EFalse);
        SetDataObjectL(wrapperName, (void*)&ret);
        }
    }

void CT_DataSIPReferDialogAssoc::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPReferDialogAssoc::~CSIPReferDialogAssoc()"));
    DestroyData();
    }

