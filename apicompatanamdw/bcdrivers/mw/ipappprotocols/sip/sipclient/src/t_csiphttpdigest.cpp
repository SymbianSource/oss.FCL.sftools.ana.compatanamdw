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


// This contains CT_DataSIPHttpDigest

#include "t_csiphttpdigest.h"
#include "t_csipaddress.h"
#include "t_csiprefresh.h"
#include "t_csipclienttransaction.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <s32file.h>

/*@{*/
_LIT(KCmdNewL,					"NewL");
_LIT(KCmdNewLC,                 "NewLC");
_LIT(KCmdSetCredentialsL,       "SetCredentialsL");
_LIT(KCmdRemoveCredentials,     "RemoveCredentials");
_LIT(KCmdSetObserver,           "SetObserver");
_LIT(KCmdIgnoreChallenge,       "IgnoreChallenge");
_LIT(KCmdDestructor,            "~");
_LIT(KCmdWaitForChallengeReceived,"WaitForChallengeReceived");

_LIT(KFldSIP,                   "sip");
_LIT(KFldSIPClientTransaction,  "sipclienttransaction");
_LIT(KFldSIPRefresh,            "siprefresh");
_LIT(KFldUseObserver2,          "useobserver2");
_LIT(KFldExpected,              "expected");
_LIT(KFldParamRealm,            "realm");
_LIT(KFldParamUsername,         "username");
_LIT(KFldParamPasswd,           "passwd");
_LIT(KFldParamProxy,            "outboundproxy");

//Log
_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");
/*}@*/


CT_DataSIPHttpDigest*  CT_DataSIPHttpDigest::NewL()
    {
    CT_DataSIPHttpDigest* self = new (ELeave) CT_DataSIPHttpDigest();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;    
    }

CT_DataSIPHttpDigest::~CT_DataSIPHttpDigest()
    {
    DestroyData();
    }

CT_DataSIPHttpDigest::CT_DataSIPHttpDigest()
:   /*CT_DataSIPDialogAssocBase(), */
CDataWrapperBase(), iSIPHttpDigest(NULL), iIsOwner(ETrue)
	{
	}

void CT_DataSIPHttpDigest::ConstructL()
    {
    }

TAny* CT_DataSIPHttpDigest::GetObject()
    {
    return iSIPHttpDigest;
    }

void CT_DataSIPHttpDigest::SetObjectL(TAny* aAny)
    {
    iSIPHttpDigest = static_cast<CSIPHttpDigest*>(aAny);
    }

void CT_DataSIPHttpDigest::DisownObjectL()
    {
    iSIPHttpDigest = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPHttpDigest::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

void CT_DataSIPHttpDigest::DestroyData()
    {
    if (iIsOwner)
        {
        delete iSIPHttpDigest;
        iSIPHttpDigest = NULL;
        iIsOwner = EFalse;
        }
    }

/**
Delegates the commands to a function

* @internalComponent
* @param aCommand Current command
* @param aSection Current ini file command section
* @param aAsyncErrorIndex index of command for SetAsyncError()
* @return TBool Returns whether the command was executed or not
*/
TBool CT_DataSIPHttpDigest::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
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
    else if( aCommand == KCmdSetCredentialsL )
        {
        DoCmdSetCredentialsL(aSection);
        }
    else if( aCommand == KCmdRemoveCredentials)
        {
        DoCmdRemoveCredentials(aSection);
        }
    else if( aCommand == KCmdSetObserver )
        {
        DoCmdSetObserver(aSection);
        }
    else if( aCommand == KCmdIgnoreChallenge)
        {
        DoCmdIgnoreChallengeL(aSection);
        }
    else if( aCommand == KCmdDestructor)
        {
        DoCmdDestructor(aSection);
        }
    else if( aCommand == KCmdWaitForChallengeReceived)
        {
        DoCmdWaitForChallengeReceived(aSection);
        }    
	else
		{
		retVal = EFalse;
		}
	return retVal;  
	}

void CT_DataSIPHttpDigest::DoCmdNewL(const TTEFSectionName& aSection)
    {
    CSIP* sip = NULL;
    if( !CT_SIPUtil::GetSIP(*this, aSection, KFldSIP, sip) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSIP);
        SetBlockResult(EFail);
        }
    else
        {        
        TBool useob2 = EFalse;
        if( !GetBoolFromConfig(aSection, KFldUseObserver2, useob2) )
            {
            ERR_PRINTF2(KLogMissingParameter, KFldUseObserver2);
            SetBlockResult(EFail);
            }
        else
            {
            TInt err = 0;
            if(!useob2)
                {
                INFO_PRINTF1(_L("call CSIPHttpDigest::NewL(CSIP&, MSIPHttpDigestChallengeObserver&)"));
                TRAP(err, iSIPHttpDigest = CSIPHttpDigest::NewL(*sip, *(MSIPHttpDigestChallengeObserver*)this));
                }
            else
                {
                INFO_PRINTF1(_L("call CSIPHttpDigest::NewL(CSIP&, MSIPHttpDigestChallengeObserver&)"));
                TRAP(err, iSIPHttpDigest = CSIPHttpDigest::NewL(*sip, *(MSIPHttpDigestChallengeObserver2*)this));
                }
            
            if(KErrNone != err)
                {
                ERR_PRINTF2(KLogError, err);
                SetError(err);
                }
            }
        }
    }

void CT_DataSIPHttpDigest::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    CSIP* sip = NULL;
    if( !CT_SIPUtil::GetSIP(*this, aSection, KFldSIP, sip) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSIP);
        SetBlockResult(EFail);
        }
    else
    {        
    TBool useob2 = EFalse;
    if( !GetBoolFromConfig(aSection, KFldUseObserver2, useob2) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldUseObserver2);
        SetBlockResult(EFail);
        }
    else
        {
        TInt err = 0;
        if(!useob2)
            {
            INFO_PRINTF1(_L("call CSIPHttpDigest::NewLC(CSIP&, MSIPHttpDigestChallengeObserver&)"));
            TRAP(err, iSIPHttpDigest = CSIPHttpDigest::NewLC(*sip, *(MSIPHttpDigestChallengeObserver*)this); CleanupStack::Pop());
            }
        else
            {
            INFO_PRINTF1(_L("call CSIPHttpDigest::NewLC(CSIP&, MSIPHttpDigestChallengeObserver&)"));
            TRAP(err, iSIPHttpDigest = CSIPHttpDigest::NewLC(*sip, *(MSIPHttpDigestChallengeObserver2*)this); CleanupStack::Pop());
            }
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    }
    }

void CT_DataSIPHttpDigest::DoCmdSetCredentialsL(const TTEFSectionName& aSection)
    {
    TPtrC datrealm, datusrname, datpasswd, datproxy;
    
    if (!GetStringFromConfig(aSection, KFldParamRealm, datrealm))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldParamRealm());
        SetBlockResult(EFail);
        return;
        }
    if(!GetStringFromConfig(aSection, KFldParamUsername, datusrname))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldParamUsername());
        SetBlockResult(EFail);
        return;
        }
    if(!GetStringFromConfig(aSection, KFldParamPasswd, datpasswd))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldParamPasswd());
        SetBlockResult(EFail);
        return;
        }
    TBuf8<KMaxTestExecuteCommandLength> valrealm;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(valrealm, datrealm);
    TBuf8<KMaxTestExecuteCommandLength> valusrname;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(valusrname, datusrname);   
    TBuf8<KMaxTestExecuteCommandLength> valpasswd;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(valpasswd, datpasswd);
    if(!GetStringFromConfig(aSection, KFldParamProxy, datproxy))
        {
        INFO_PRINTF1(_L("execute CSIPHttpDigest::SetCredentialsL(const TDesC8 &, const TDesC8 &, const TDesC8 &"));
        TRAPD(err, iSIPHttpDigest->SetCredentialsL(valrealm, valusrname, valpasswd));
        if(err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    else
        {
        CSIPClientTransaction* trans = NULL;
        CSIPRefresh* refresh = NULL;
        TBuf8<KMaxTestExecuteCommandLength> valproxy;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(valproxy, datproxy);
        if (CT_SIPUtil::GetSIPClientTransactionL(*this, aSection, KFldSIPClientTransaction, trans))
            {
            INFO_PRINTF1(_L("execute CSIPHttpDigest::SetCredentialsL(const CSIPClientTransaction &, const TDesC8 &, const TDesC8 &, const TDesC8 &, const TDesC8 &)"));
            TRAPD(err, iSIPHttpDigest->SetCredentialsL(*trans, valproxy, valrealm, valusrname, valpasswd));
            if(err != KErrNone)
                {
                ERR_PRINTF2(KLogError, err);
                SetError(err);
                }
            }
        else if (CT_SIPUtil::GetSIPRefreshL(*this, aSection, KFldSIPRefresh, refresh))
            {
            INFO_PRINTF1(_L("execute CSIPHttpDigest::SetCredentialsL(const CSIPRefresh &, const TDesC8 &, const TDesC8 &, const TDesC8 &, const TDesC8 &)"));
            TRAPD(err, iSIPHttpDigest->SetCredentialsL(*refresh, valproxy, valrealm, valusrname, valpasswd));
            if(err != KErrNone)
                {
                ERR_PRINTF2(KLogError, err);
                SetError(err);
                }
            }
        else
            {
            INFO_PRINTF1(_L("execute CSIPHttpDigest::SetCredentialsL(const TDesC8 &, const TDesC8 &, const TDesC8 &, const TDesC8 &)"));
            TRAPD(err, iSIPHttpDigest->SetCredentialsL(valproxy, valrealm, valusrname, valpasswd));
            if(err != KErrNone)
                {
                ERR_PRINTF2(KLogError, err);
                SetError(err);
                }
            }
        }
    }

void CT_DataSIPHttpDigest::DoCmdRemoveCredentials(const TTEFSectionName& aSection)
    {
    TPtrC datrealm;
    TInt ret;
    TInt expected;
    if (GetStringFromConfig(aSection, KFldParamRealm, datrealm))
        {
        TBuf8<KMaxTestExecuteCommandLength> valrealm;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(valrealm, datrealm);
        INFO_PRINTF1(_L("execute CSIPHttpDigest::RemoveCredentials(const TDesC8 &)"));
        ret = iSIPHttpDigest->RemoveCredentials(valrealm);
        if(ret != KErrNone)
            {
            ERR_PRINTF2(KLogError, ret);
            SetError(ret);
            }
        else
            {
            INFO_PRINTF2(_L("Remove successfully: %d"), ret);
            }
        }
    else
        {
        INFO_PRINTF1(_L("execute CSIPHttpDigest::RemoveCredentials()"));
        ret = iSIPHttpDigest->RemoveCredentials();
        if(ret != KErrNone)
            {
            ERR_PRINTF2(KLogError, ret);
            SetError(ret);
            }
        else
            {
            INFO_PRINTF2(_L("Remove successfully: %d"), ret);
            }   
        }
    
    if(GetIntFromConfig(aSection, KFldExpected, expected))
        {
        if (ret != expected)
            {
            ERR_PRINTF3(_L("actual value is not as expected, expected: %d, actual: %d"), expected, ret);
            SetBlockResult(EFail);
            }
        else
            {
            INFO_PRINTF3(_L("actual value is as expected, expected: %d, actual: %d"), expected, ret);
            }
        }
    }

void CT_DataSIPHttpDigest::DoCmdSetObserver(const TTEFSectionName& aSection)
    {
    
    TBool useob2 = EFalse;
    if( !GetBoolFromConfig(aSection, KFldUseObserver2, useob2) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldUseObserver2());
        SetBlockResult(EFail);
        }
    else
        {
        if(!useob2)
            {
            INFO_PRINTF1(_L("call CSIPHttpDigest::SetObserver(MSIPHttpDigestChallengeObserver&)"));
            iSIPHttpDigest->SetObserver(*(MSIPHttpDigestChallengeObserver*)this);
            }
        else
            {
            INFO_PRINTF1(_L("call CSIPHttpDigest::SetObserver(MSIPHttpDigestChallengeObserver2&)"));
            iSIPHttpDigest->SetObserver(*(MSIPHttpDigestChallengeObserver2*)this);
            }
        }
    }

void CT_DataSIPHttpDigest::DoCmdIgnoreChallengeL(const TTEFSectionName& aSection)
    {
    TPtrC temp;
    if( !GetStringFromConfig(aSection, KFldParamRealm, temp) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldParamRealm());
        SetBlockResult(EFail);
        }
    else
        {
        TInt err=0;
        TBuf8<KMaxTestExecuteCommandLength> realm;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(realm, temp);
        
        CSIPClientTransaction* trans = NULL;
        CSIPRefresh* refresh = NULL;
        if( CT_SIPUtil::GetSIPClientTransactionL(*this, aSection, KFldSIPClientTransaction, trans) )
            {
            INFO_PRINTF1(_L("call CSIPHttpDigest::IgnoreChallenge(const CSIPClientTransaction&, const TDesC8&)"));
            err=iSIPHttpDigest->IgnoreChallenge(*trans, realm);
            }
        else if( CT_SIPUtil::GetSIPRefreshL(*this, aSection, KFldSIPRefresh, refresh) )
            {
            INFO_PRINTF1(_L("call CSIPHttpDigest::IgnoreChallenge(const CSIPRefresh&, const TDesC8&)"));
            err=iSIPHttpDigest->IgnoreChallenge(*refresh, realm);
            }
        else
            {
            INFO_PRINTF1(_L("call CSIPHttpDigest::IgnoreChallenge(const TDesC8&)"));
            err=iSIPHttpDigest->IgnoreChallenge(realm);
            }
        if(err!=KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    }

void CT_DataSIPHttpDigest::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPHttpDigest::~CSIPHttpDigest()"));
    DestroyData();
    }

// from MSIPHttpDigestChallengeObserver
void CT_DataSIPHttpDigest::ChallengeReceived(const TDesC8 &aRealm)
    {
    INFO_PRINTF1(_L("call MSIPHttpDigestChallengeObserver::ChallengeReceived(const TDesC8&)"));
    TBuf<50> receivedRealm;
    CT_SIPUtil::ConvertToUnicode(aRealm,receivedRealm);
    INFO_PRINTF2(_L("realm : %S"), &receivedRealm);
    TPtrC expectedRealm;
    if( GetStringFromConfig(iTEFSectionName, KFldExpected, expectedRealm) )
        {
        if(expectedRealm.Compare(receivedRealm)==0)
            {
            INFO_PRINTF3(_L("The received realm : %S matched the expected %S"),&receivedRealm,&expectedRealm);
            }
        else
            {
            ERR_PRINTF3(_L("The received realm name: %S is not matched the expected %S"),&receivedRealm,&expectedRealm);
            SetBlockResult(EFail);
            }
        }
    
    DecOutstanding();
    }

// from MSIPHttpDigestChallengeObserver2
void CT_DataSIPHttpDigest::ChallengeReceived(const CSIPClientTransaction &aTransaction)
    {
    INFO_PRINTF1(_L("call MSIPHttpDigestChallengeObserver2::ChallengeReceived(const CSIPClientTransaction&)"));
    
    TPtrC wrapperName;
    if( !GetStringFromConfig(iTEFSectionName, KFldSIPClientTransaction, wrapperName) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPClientTransaction());
        SetBlockResult(EFail);
        }
    else
        {
        CT_DataSIPClientTransaction* wrapper = static_cast<CT_DataSIPClientTransaction*>(GetDataWrapperL(wrapperName));
        wrapper->SetIsOwner(EFalse);
        SetDataObjectL(wrapperName, (void*)&aTransaction);
        }
        
    DecOutstanding();
    }

void CT_DataSIPHttpDigest::ChallengeReceived(const CSIPRefresh &aRefresh)
    {
    INFO_PRINTF1(_L("call MSIPHttpDigestChallengeObserver2::ChallengeReceived(const CSIPRefresh&)"));
    
    TPtrC wrapperName;
    if( !GetStringFromConfig(iTEFSectionName, KFldSIPRefresh, wrapperName) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSIPRefresh);
        SetBlockResult(EFail);
        }
    else
        {
        CT_DataSIPRefresh* wrapper = static_cast<CT_DataSIPRefresh*>(GetDataWrapperL(wrapperName));
        wrapper->SetIsOwner(EFalse);
        SetDataObjectL(wrapperName, (void*)&aRefresh);
        }
        
    DecOutstanding();
    }

void CT_DataSIPHttpDigest::DoCmdWaitForChallengeReceived(const TTEFSectionName& aSection)
    {
    iTEFSectionName = aSection;
    IncOutstanding();
    }
