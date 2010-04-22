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


#include "t_csipfromtoheaderbase.h"
#include "t_csipaddress.h"
#include "sipaddress.h" 
#include "T_SIPUtil.h"

/*@{*/
_LIT(KCmdSIPAddress,                         "SIPAddress");
_LIT(KCmdSetSIPAddressL,                     "SetSIPAddressL");
_LIT(KCmdCompare,                            "==");
//Fields 
_LIT(KFldBeConst,                            "beconst");
_LIT(KFldSIPAddress,                         "sipaddress");
_LIT(KFldExpected,                           "expected");
_LIT(KFldSIPFromToHeaderBase,                "sipfromtoheaderbase");

// Logging
_LIT(KLogError,                             "Error=%d");
_LIT(KLogMissingParameter,                  "Missing parameter '%S'");
_LIT(KLogNotExpectedValue,                  "Not expected value, actual=%d, expect=%d");

CT_DataSIPFromToHeaderBase::CT_DataSIPFromToHeaderBase() :
CT_DataSIPParameterHeaderBase()
    {
    }

/**
* Process a command read from the ini file
*
* @param aDataWrapper   test step requiring command to be processed
* @param aCommand   the command to process
* @param aSection       the entry in the ini file requiring the command to be processed
*
* @return ETrue if the command is processed
*/
TBool CT_DataSIPFromToHeaderBase::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
    {
    TBool ret=ETrue;

    if ( aCommand==KCmdSIPAddress )
        {
        DoCmdSIPAddress(aSection);
        }
    else if ( aCommand==KCmdSetSIPAddressL )
        {
        DoCmdSetSIPAddressL(aSection);
        }
    else if ( aCommand==KCmdCompare )
        {
        DoCmdCompare(aSection);
        }
    else
        {
        ret = CT_DataSIPParameterHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);;
        }

    return ret;
    }

void CT_DataSIPFromToHeaderBase::DoCmdSIPAddress(const TTEFSectionName& aSection)
    {
    TBool beconst=EFalse;
    TPtrC addrName;
    if (!GetStringFromConfig(aSection, KFldSIPAddress, addrName))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPAddress());
        SetBlockResult(EFail);
        return;
        }
    GetBoolFromConfig(aSection, KFldBeConst, beconst);
    if(beconst)
        {
        const CSIPAddress *aSIPAddress = NULL;
        INFO_PRINTF1(_L("call CSIPFromToHeader::SIPAddress() const CSIPAddress &SIPAddress() const"));
        aSIPAddress=&(((const CSIPFromToHeaderBase*)GetSIPHeaderBase())->SIPAddress());
        SetDataObjectL(addrName, (CSIPAddress*)aSIPAddress);
        }
    else
        {
        CSIPAddress *aSIPAddress = NULL;
        INFO_PRINTF1(_L("call CSIPFromToHeader::SIPAddress() "));
        aSIPAddress=&(((CSIPFromToHeaderBase*)GetSIPHeaderBase())->SIPAddress());
        SetDataObjectL(addrName, aSIPAddress);
        }  
    CT_DataSIPAddress* wrapper = static_cast<CT_DataSIPAddress*>(GetDataWrapperL(addrName));
    wrapper->SetIsOwner(EFalse);
    }

void CT_DataSIPFromToHeaderBase::DoCmdSetSIPAddressL(const TTEFSectionName& aSection)
    {
    CSIPAddress *aSIPAddress = NULL;
    TPtrC addrName;
    if (!GetStringFromConfig(aSection, KFldSIPAddress, addrName))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPAddress());
        SetBlockResult(EFail);
        return;
        }
    aSIPAddress = static_cast<CSIPAddress*> (GetDataObjectL(addrName));
    INFO_PRINTF1(_L("call CSIPFromToHeader::SetSIPAddressL(aSIPAddress)"));
    TRAPD(err,((CSIPFromToHeaderBase*)GetSIPHeaderBase())->SetSIPAddressL(aSIPAddress));
    if ( err!=KErrNone )
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    else
        {
        CT_DataSIPAddress* wrapper = static_cast<CT_DataSIPAddress*>(GetDataWrapperL(addrName));
        wrapper->SetIsOwner(EFalse);
        }
    }

// For operator ==()
void CT_DataSIPFromToHeaderBase::DoCmdCompare(const TTEFSectionName& aSection)
    {
    CSIPFromToHeaderBase* sipfromtoheaderbase;
    if(!CT_SIPUtil::GetSIPFromToHeaderBaseL(*this, aSection, KFldSIPFromToHeaderBase, sipfromtoheaderbase) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPFromToHeaderBase());
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPFromToHeaderBase::==(const CSIPFromToHeaderBase&)")); 
        TBool ret = (*(CSIPFromToHeaderBase*)GetSIPHeaderBase() == *sipfromtoheaderbase);
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
