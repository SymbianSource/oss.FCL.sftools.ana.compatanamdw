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


#include "T_SIPUtil.h"
#include "t_csip.h"
#include "t_csipprofileregistry.h"
#include "t_csipprofileregistrybase.h"
#include <sipprofile.h> 

/*@{*/
_LIT(KCmdDestroy,							"~");
_LIT(KCmdNewL,								"NewL");
_LIT(KCmdNewLC,								"NewLC");
_LIT(KCmdSIP,								"SIP");
_LIT(KCmdConnectionL,						"ConnectionL");
_LIT(KCmdEnableL,							"EnableL");
_LIT(KCmdDisable,							"Disable");
_LIT(KCmdIsEnabled,							"IsEnabled");

//Fields 
_LIT(KFldSip, 								"sip");
_LIT(KFldExpected,							"expected");
_LIT(KFldSipProfile, 						"profile");
_LIT(KFldSipConnection,						"sipconnection");

//Error
_LIT(KLogError,								"Error=%d");
_LIT(KLogMissingParameter,					"Missing parameter '%S'");
_LIT(KLogNotExpectedValue,                  "Not expected value, actual=%d, expect=%d");

CT_DataSIPProfileRegistry*	CT_DataSIPProfileRegistry::NewL()
	{
	CT_DataSIPProfileRegistry* self=new (ELeave)CT_DataSIPProfileRegistry;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	
}

CT_DataSIPProfileRegistry::~CT_DataSIPProfileRegistry()
    {
	DestroyData();
    }

TBool CT_DataSIPProfileRegistry::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
	{
	TBool ret=ETrue;
	
	if ( aCommand==KCmdDestroy )
		{
		DoCmdDestructor(aSection);
		}
	else if ( aCommand==KCmdNewL )
		{
		DoCmdNewL(aSection);
		}
	else if ( aCommand==KCmdNewLC )
		{
		DoCmdNewLC(aSection);
		}
	else if ( aCommand==KCmdSIP )
		{
		DoCmdSIPL(aSection);
		}
	else if ( aCommand==KCmdConnectionL )
		{
		DoCmdConnectionL(aSection);
		}
	else if ( aCommand==KCmdEnableL )
		{
		DoCmdEnableL(aSection);
		}
	else if ( aCommand==KCmdDisable )
		{
		DoCmdDisableL(aSection);
		}
	else if ( aCommand==KCmdIsEnabled )
		{
		DoCmdIsEnabledL(aSection);
		}
	
	else 
		{
		ret=CT_DataSIPProfileRegistryBase::DoCommandL(aCommand,aSection,aAsyncErrorIndex);
		}

	return ret;	
	}

TAny* CT_DataSIPProfileRegistry::GetObject()
	{
	return iSIPProfileRegistry;
	}

void CT_DataSIPProfileRegistry::SetObjectL(TAny* aAny)
	{
	iSIPProfileRegistry=static_cast<CSIPProfileRegistry*>(aAny);
	}

void CT_DataSIPProfileRegistry::DisownObjectL()
	{
	iSIPProfileRegistry=NULL;
	}

void CT_DataSIPProfileRegistry::DestroyData()
	{
	delete iSIPProfileRegistry;
	iSIPProfileRegistry=NULL;	    
	}

CT_DataSIPProfileRegistry::CT_DataSIPProfileRegistry() 
:	CT_DataSIPProfileRegistryBase(), iSIPProfileRegistry(NULL)
	{
	}

void CT_DataSIPProfileRegistry::ConstructL()
	{
	}

CSIPProfileRegistryBase* CT_DataSIPProfileRegistry::GetSIPProfileRegistryBase() const
	{
	return iSIPProfileRegistry;
	}

void CT_DataSIPProfileRegistry::DoCmdConnectionL(const TTEFSectionName& aSection)
	{
    CSIPProfile* sp = NULL;
    if( !CT_SIPUtil::GetSIPProfile(*this, aSection, KFldSipProfile, sp) )
		{
		ERR_PRINTF2(KLogMissingParameter, KFldSipProfile);
		SetBlockResult(EFail);        
		}
	else
		{
        INFO_PRINTF1(_L("call CSIPProfileRegistry::ConnectionL(const CSIPProfile&)"));
        CSIPConnection* sipconnect = NULL;
        TRAPD(err, sipconnect = iSIPProfileRegistry->ConnectionL(*sp));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            TPtrC datSipConnection;
            if( !GetStringFromConfig(aSection, KFldSipConnection, datSipConnection) )
                {
                ERR_PRINTF2(KLogMissingParameter, KFldSipConnection);
                SetBlockResult(EFail);
                }
            else
                {
                SetDataObjectL(datSipConnection, sipconnect);
                }
            }
        }
	}

void CT_DataSIPProfileRegistry::DoCmdDisableL(const TTEFSectionName& aSection)
	{
    CSIPProfile* sp = NULL;
    if( !CT_SIPUtil::GetSIPProfile(*this, aSection, KFldSipProfile, sp) )
		{
		ERR_PRINTF2(KLogMissingParameter, KFldSipProfile);
		SetBlockResult(EFail);
		}
	else
		{
		if( !CT_SIPUtil::GetEvent(*this, aSection, KFldExpected, iExpected))
            {
            ERR_PRINTF2(KLogMissingParameter, KFldExpected);
            SetBlockResult(EFail);
            }
        else
            {
            INFO_PRINTF1(_L("call CSIPProfileRegistry::Disable(const CSIPProfile&)"));
            TInt err = iSIPProfileRegistry->Disable(*sp);            
            if(KErrNone != err)
                {
                ERR_PRINTF2(KLogError, err);
                SetError(err);
                }
            else
                {
                iCheckEvent = ETrue;
                IncOutstanding();
                }
            }
		}	
	}

void CT_DataSIPProfileRegistry::DoCmdEnableL(const TTEFSectionName& aSection)
	{
    CSIPProfile* sp = NULL;
    if( !CT_SIPUtil::GetSIPProfile(*this, aSection, KFldSipProfile, sp) )
		{
		ERR_PRINTF2(KLogMissingParameter, KFldSipProfile);
		SetBlockResult(EFail);
		}
	else
		{
        if( !CT_SIPUtil::GetEvent(*this, aSection, KFldExpected, iExpected))
            {
            ERR_PRINTF2(KLogMissingParameter, KFldExpected);
            SetBlockResult(EFail);
            }
        else
            {
            INFO_PRINTF1(_L("call CSIPProfileRegistry::EnableL(const CSIPProfile&, MSIPConnectionObserver&)"));
            TRAPD(err, iSIPProfileRegistry->EnableL(*sp, *this));            
            if(KErrNone != err)
                {
                ERR_PRINTF2(KLogError, err);
                SetError(err);
                }
            else
                {
                iCheckEvent = ETrue;
                IncOutstanding();
                }
            }
		}
	}

void CT_DataSIPProfileRegistry::DoCmdIsEnabledL(const TTEFSectionName& aSection)
	{
    CSIPProfile* sp = NULL;
    if( !CT_SIPUtil::GetSIPProfile(*this, aSection, KFldSipProfile, sp) )
		{
		ERR_PRINTF2(KLogMissingParameter, KFldSipProfile);
		SetBlockResult(EFail);
		}
	else
		{
		INFO_PRINTF1(_L("call CSIPProfileRegistry::IsEnabled(const CSIPProfile&)"));
		TBool ret = iSIPProfileRegistry->IsEnabled(*sp);        
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
	}

void CT_DataSIPProfileRegistry::DoCmdNewL(const TTEFSectionName& aSection)
	{    
    CSIP* sip = NULL;
    if( !CT_SIPUtil::GetSIP(*this, aSection, KFldSip, sip) )
		{
		ERR_PRINTF2(KLogMissingParameter, KFldSip);
		SetBlockResult(EFail);
		}
	else{
		INFO_PRINTF1(_L("call CSIPProfileRegistry::NewL(CSIP&, MSIPProfileRegistryObserver&)"));
		TRAPD(err, iSIPProfileRegistry = CSIPProfileRegistry::NewL(*sip, *this));
		if(KErrNone != err)
			{
			ERR_PRINTF2(KLogError, err);
			SetError(err);
			}
		}
	}

void CT_DataSIPProfileRegistry::DoCmdNewLC(const TTEFSectionName& aSection)
	{
    CSIP* sip = NULL;
    if( !CT_SIPUtil::GetSIP(*this, aSection, KFldSip, sip) )
		{
		ERR_PRINTF2(KLogMissingParameter, KFldSip);
		SetBlockResult(EFail);
		}
	else{
		INFO_PRINTF1(_L("call CSIPProfileRegistry::NewLC(CSIP&, MSIPProfileRegistryObserver&)"));
		TRAPD(err, iSIPProfileRegistry = CSIPProfileRegistry::NewLC(*sip, *this); CleanupStack::Pop(););
		if(KErrNone != err)
			{
			ERR_PRINTF2(KLogError, err);
			SetError(err);
			}		
		}
	}

void CT_DataSIPProfileRegistry::DoCmdSIPL(const TTEFSectionName& aSection)
	{
	INFO_PRINTF1(_L("call CSIPProfileRegistry::SIP()"));
	CSIP& sip = iSIPProfileRegistry->SIP();

	TPtrC datSip;
	if( !GetStringFromConfig(aSection, KFldSip, datSip) )
		{
		ERR_PRINTF2(KLogMissingParameter, KFldSip);
		SetBlockResult(EFail);
		}
	else
		{
		CT_DataSIP* wrapper = static_cast<CT_DataSIP*>(GetDataWrapperL(datSip));
		wrapper->SetIsOwner(EFalse);
		SetDataObjectL(datSip, &sip);
		}
	}

void CT_DataSIPProfileRegistry::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
	{
	INFO_PRINTF1(_L("call CSIPProfileRegistry::~CSIPProfileRegistry()"));
	DestroyData();
	}

void CT_DataSIPProfileRegistry::IncomingRequest (CSIPServerTransaction* /*aTransaction*/)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::IncomingRequest(CSIPServerTransaction*)"));    
    }

void CT_DataSIPProfileRegistry::IncomingRequest (CSIPServerTransaction* /*aTransaction*/, CSIPDialog& /*aDialog*/)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::IncomingRequest(CSIPServerTransaction*, CSIPDialog&)"));
    }

void CT_DataSIPProfileRegistry::IncomingResponse (CSIPClientTransaction& /*aTransaction*/)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::IncomingResponse(CSIPClientTransaction&)"));
    }

void CT_DataSIPProfileRegistry::IncomingResponse (CSIPClientTransaction& /*aTransaction*/, CSIPDialogAssocBase& /*aDialogAssoc*/)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::IncomingResponse(CSIPClientTransaction&, CSIPDialogAssocBase&)"));
    }

void CT_DataSIPProfileRegistry::IncomingResponse (CSIPClientTransaction& /*aTransaction*/, CSIPInviteDialogAssoc* /*aDialogAssoc*/)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::IncomingResponse(CSIPClientTransaction&, CSIPInviteDialogAssoc&)"));
    }

void CT_DataSIPProfileRegistry::IncomingResponse (CSIPClientTransaction& /*aTransaction*/, CSIPRegistrationBinding& /*aRegistration*/)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::IncomingResponse(CSIPClientTransaction&, CSIPRegistrationBinding&)"));
    }

void CT_DataSIPProfileRegistry::ErrorOccured (TInt /*aError*/, CSIPTransactionBase& /*aTransaction*/)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::ErrorOccured(TInt, CSIPTransactionBase&)"));
    }

void CT_DataSIPProfileRegistry::ErrorOccured (TInt /*aError*/, CSIPClientTransaction& /*aTransaction*/, CSIPRegistrationBinding& /*aRegistration*/)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::ErrorOccured(TInt, CSIPClientTransaction&, CSIPRegistrationBinding&)"));
    }

void CT_DataSIPProfileRegistry::ErrorOccured (TInt /*aError*/, CSIPTransactionBase& /*aTransaction*/, CSIPDialogAssocBase& /*aDialogAssoc*/)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::ErrorOccured(TInt, CSIPTransactionBase&, CSIPDialogAssocBase)"));
    }

void CT_DataSIPProfileRegistry::ErrorOccured (TInt /*aError*/, CSIPRefresh& /*aSIPRefresh*/)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::ErrorOccured(TInt, CSIPRefresh&)"));
    }

void CT_DataSIPProfileRegistry::ErrorOccured (TInt /*aError*/, CSIPRegistrationBinding& /*aRegistration*/)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::ErrorOccured(TInt, CSIPRegistrationBinding&)"));
    }

void CT_DataSIPProfileRegistry::ErrorOccured (TInt /*aError*/,	CSIPDialogAssocBase& /*aDialogAssoc*/)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::ErrorOccured(TInt, CSIPDialogAssocBase&)"));
    }

void CT_DataSIPProfileRegistry::InviteCompleted (CSIPClientTransaction& /*aTransaction*/)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::InviteCompleted(CSIPClientTransaction&)"));
    }

void CT_DataSIPProfileRegistry::InviteCanceled (CSIPServerTransaction& /*aTransaction*/)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::InviteCanceled(CSIPClientTransaction&)"));
    }

void CT_DataSIPProfileRegistry::ConnectionStateChanged (CSIPConnection::TState /*aState*/)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::ConnectionStateChanged(CSIPConnection::TState)"));
    }

