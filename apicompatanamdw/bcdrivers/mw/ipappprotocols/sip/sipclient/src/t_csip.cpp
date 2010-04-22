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


#include "t_csip.h"
#include "t_csipconnection.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <badesca.h> 

/*@{*/
_LIT(KCmdDestroy,                               "~");
_LIT(KCmdNewL,                                  "NewL");
_LIT(KCmdNewLC,                                 "NewLC");
_LIT(KCmdConnection,                            "Connection");
//_LIT(KCmdIsSecurityHandlingEnabled,             "IsSecurityHandlingEnabled");
_LIT(KCmdIsSigCompSupportedL,                   "IsSigCompSupportedL");
_LIT(KCmdNegotiatedSecurityMechanismL,          "NegotiatedSecurityMechanismL");
//_LIT(KCmdSetSecurityHandlingL,                  "SetSecurityHandlingL");
_LIT(KCmdSupportedSecurityMechanismsL,          "SupportedSecurityMechanismsL");


//Fields
_LIT(KFldUID,                                   "UID");
_LIT(KFldIAPID,                                 "iapID");
_LIT(KFldConnection,                            "connection");  
_LIT(KFldHop,                                   "Hop");
_LIT(KExpected,                                 "expected");

//Error
_LIT(KLogErrMissingPara,                        "Missing parameter '%S'");
_LIT(KLogError,                                 "Error=%d");


CT_DataSIP::CT_DataSIP()
:   CDataWrapperBase(), iSIP(NULL), iIsOwner(ETrue)
    {
    }

CT_DataSIP::~CT_DataSIP()
	{
	DestroyData();
	}

void CT_DataSIP::ConstructL()
	{
	}

CT_DataSIP* CT_DataSIP::NewL()
    {
	CT_DataSIP* self = new (ELeave)CT_DataSIP;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

TAny* CT_DataSIP::GetObject()
	{
	return iSIP;
	}

void CT_DataSIP::SetObjectL(TAny* aAny)
	{
	iSIP = static_cast<CSIP*>(aAny);
	}

void CT_DataSIP::DisownObjectL()
	{
	iSIP = NULL;
	iIsOwner = EFalse;
	}

TBool CT_DataSIP::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
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
	else if (aCommand == KCmdNewLC)
        {
        DoCmdNewLC(aSection);
        }
    else if (aCommand == KCmdConnection)
        {
        DoCmdConnection(aSection);
        }
    else if (aCommand == KCmdIsSigCompSupportedL)
        {
        DoCmdIsSigCompSupportedL(aSection);
        }
    else if (aCommand == KCmdNegotiatedSecurityMechanismL)
        {
        DoCmdNegotiatedSecurityMechanismL(aSection);
        }
    else if (aCommand == KCmdSupportedSecurityMechanismsL)
        {
        DoCmdSupportedSecurityMechanismsL(aSection);
        }
    else
        {
        ret = EFalse;
		}
	return ret;
    }

void CT_DataSIP::DoCmdNewL(const TTEFSectionName& aSection)
	{
	INFO_PRINTF1(_L("call CSIP::NewL(const TUid &aUid, MSIPObserver &aObserver)"));
	
	TInt uid;
	if(GetHexFromConfig(aSection, KFldUID, uid))
		{
		TRAPD(err, iSIP = CSIP::NewL(TUid::Uid(uid), *this));
		if(err == KErrNone)
		    {
		    iIsOwner = ETrue;
		    }
		else
		    {
		    ERR_PRINTF2(KLogError, err);
		    SetError(err);
		    }
		}
	else 
		{
		ERR_PRINTF2(KLogErrMissingPara, &KFldUID());
		SetBlockResult(EFail);
		}
	}

void CT_DataSIP::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIP::NewLC(const TUid &aUid, MSIPObserver &aObserver)"));
    
    TInt uid;
    if(GetHexFromConfig(aSection, KFldUID, uid))
        {
        TRAPD(err, iSIP = CSIP::NewLC(TUid::Uid(uid), *this); CleanupStack::Pop(iSIP));
        if(err == KErrNone)
            {
            iIsOwner = ETrue;
            }
        else
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    else 
        {
        ERR_PRINTF2(KLogErrMissingPara, &KFldUID());
        SetBlockResult(EFail);
        }   
    }

void CT_DataSIP::DoCmdConnection(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIP::Connection(TUint32 aIapId) const"));
    
    TPtrC strIapId;
    if(GetStringFromConfig(aSection, KFldIAPID, strIapId))
        {
        TUint32 iapid = CT_SIPUtil::GetIAPIDL(strIapId);
        if(iapid == 0)
            {
            iapid = CT_SIPUtil::AddAccessPointL(strIapId);
            INFO_PRINTF3(_L("Add a new IAP (name = %S and ID = [%d])"), &strIapId, iapid );
            }
        else
            {
            INFO_PRINTF3(_L("IAP (name = %S) found with IAP (ID = [%d])"), &strIapId, iapid );
            }
        
        if(iapid == 0)
            {
            ERR_PRINTF1(_L("Failed to add a IAP."));
            SetBlockResult(EFail);
            return;
            }

        TPtrC connection;
        if(GetStringFromConfig(aSection, KFldConnection, connection))
            {
            CSIPConnection* conn = iSIP->Connection(iapid);
            if(connection.Compare(_L("NULL")) == 0)  //expects the connection does not exist
                {
                if(conn)
                    {
                    ERR_PRINTF1(_L("The sip connection is not as expected NULL"));
                    SetBlockResult(EFail);
                    }
                }
            else
                {
                if(conn)
                    {
                    SetDataObjectL(connection, conn);
                    CT_DataSIPConnection* wrapper = static_cast<CT_DataSIPConnection*> (GetDataWrapperL(connection));
                    wrapper->SetIsOwner(EFalse);
                    }
                else
                    {
                    ERR_PRINTF1(_L("The sip connection does not exist"));
                    SetBlockResult(EFail);
                    }
                }
            }
        else
            {
            ERR_PRINTF2(KLogErrMissingPara, &KFldConnection());
            SetBlockResult(EFail);           
            }
        }
    else
        {
        ERR_PRINTF2(KLogErrMissingPara, &KFldIAPID());
        SetBlockResult(EFail);
        }
    }


void CT_DataSIP::DoCmdIsSigCompSupportedL(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIP::IsSigCompSupportedL()"));
    
    TBool actual = iSIP->IsSigCompSupportedL();
    INFO_PRINTF2(_L("The actual value is %d"), actual);
    
    TBool expectedEnabled;
    if(GetBoolFromConfig(aSection, KExpected, expectedEnabled))
        {
        if(expectedEnabled != actual)
            {
            ERR_PRINTF2(_L("expected value is %d"), expectedEnabled);
            SetBlockResult(EFail);
            }
        else
            {
            INFO_PRINTF1(_L("returns value as expected"));
            }
        }    
    }

void CT_DataSIP::DoCmdNegotiatedSecurityMechanismL(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIP::NegotiatedSecurityMechanismL(const TDesC8& aHop)"));
    
    TPtrC str;
    if(GetStringFromConfig(aSection, KFldHop, str))
        {
        TBuf8<KMaxTestExecuteCommandLength> hop;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(hop, str);
        HBufC8* ret = NULL;
        TRAPD(err, ret = iSIP->NegotiatedSecurityMechanismL(hop));
        if(err == KErrNone)
            {
            if(ret)
                {
                INFO_PRINTF2(_L("actual value is %S"), ret->Des());
                TPtrC expectedStr;
                if(GetStringFromConfig(aSection, KExpected, expectedStr))
                    {
                    TBuf8<KMaxTestExecuteCommandLength> expected;
                    CnvUtfConverter::ConvertFromUnicodeToUtf8(expected, expectedStr);
                    if(ret->Compare(expected) != 0)
                        {
                        ERR_PRINTF2(_L("Expected value is %S"), &expected);
                        SetBlockResult(EFail);
                        }
                    }
                }
            else
                {
                INFO_PRINTF1(_L("The returned value is NULL"));
                }
            }
        else
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    else
        {
        ERR_PRINTF2(KLogErrMissingPara, &KFldHop());
        SetBlockResult(EFail);       
        }
    }


void CT_DataSIP::DoCmdSupportedSecurityMechanismsL(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIP::SupportedSecurityMechanismsL()"));
    
    CDesC8Array* mechanicsms = NULL;
    TRAPD(err, mechanicsms = iSIP->SupportedSecurityMechanismsL());
    if(err == KErrNone)
        {
        CleanupStack::PushL(mechanicsms);
        
        CDesC8ArrayFlat* expecedValues = new(ELeave) CDesC8ArrayFlat(1);
        CleanupStack::PushL(expecedValues);
        TBool checkExpectedValues = CT_SIPUtil::GetMDesC8ArrayL(*this, aSection, KExpected, (MDesC8Array*)expecedValues);
        for(TInt i=0; i < mechanicsms->Count(); i++)
            {
            TBuf<KMaxTestExecuteCommandLength> mechanicsm;
            CnvUtfConverter::ConvertToUnicodeFromUtf8(mechanicsm, (*mechanicsms)[i]);
            INFO_PRINTF2(_L("Supported security mechanism: %S"), &mechanicsm);
            
            if(checkExpectedValues && i <expecedValues->Count())
                {
                if((*mechanicsms)[i].Compare((*expecedValues)[i]) != 0)
                    {
                    TBuf<KMaxTestExecuteCommandLength> expected;
                    CnvUtfConverter::ConvertToUnicodeFromUtf8(expected, (*expecedValues)[i]);
                    ERR_PRINTF2(_L("Expected security mechanisms: %S"), &expected);
                    SetBlockResult(EFail); 
                    }
                }
            }
        CleanupStack::PopAndDestroy(2);
        }
    else
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);        
        }
    }


void CT_DataSIP::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
	{
	INFO_PRINTF1(_L("call CSIP::~CSIP()"));
	DestroyData();
	}

void CT_DataSIP::IncomingRequest(TUint32, CSIPServerTransaction *)
	{
	INFO_PRINTF1(_L("IncomingRequest"));
	/// ToDo
	
	}

void CT_DataSIP::TimedOut(CSIPServerTransaction &)
	{
    INFO_PRINTF1(_L("TimedOut"));
    /// ToDo
    }

void CT_DataSIP::DestroyData()
	{
	if(iIsOwner && iSIP)
	    {
	    delete iSIP;
	    iSIP = NULL;
	    iIsOwner = EFalse;
	    }	
	}

void CT_DataSIP::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

