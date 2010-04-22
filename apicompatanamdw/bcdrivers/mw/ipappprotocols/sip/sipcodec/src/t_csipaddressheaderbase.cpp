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
#include "t_csipaddressheaderbase.h"
#include "t_csipaddress.h"
#include <sipaddress.h>
#include <utf.h>

/*@{*/
_LIT(KCmdSetSIPAddressL,                    "SetSIPAddressL");
_LIT(KCmdSIPAddress,                        "SIPAddress");

//Fields 
_LIT(KFldSIPAddress,                        "SIPAddress");
_LIT(KFldConstFlag,                         "ConstFlag");
_LIT(KFldExpectedDisplayName,               "ExpectedDisplayName");
// Logging
_LIT(KLogError,                             "Error=%d");
_LIT(KLogMissingParameter,                  "Missing parameter '%S'");
//_LIT(KLogPreconditionNotReady,              "Precondition '%S' is not ready");
//_LIT(KLogNotExpectedIntValue,               "Not expected value, actual=%d, expect=%d");
_LIT(KLogNotExpectedStringValue,            "Not expected value, actual=%S, expect=%S");

/**
* Constructor. First phase construction
*/
CT_DataSIPAddressHeaderBase::CT_DataSIPAddressHeaderBase()
:   CT_DataSIPParameterHeaderBase()
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
TBool CT_DataSIPAddressHeaderBase::DoCommandL(const TTEFFunction& aCommand, 
        const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
    {
    TBool ret = ETrue;
    
    if ( aCommand==KCmdSetSIPAddressL )
        {
        DoCmdSetSIPAddressL(aSection);
        }
    else if ( aCommand==KCmdSIPAddress )
        {
        DoCmdSIPAddress(aSection);
        }
    else
        {
        ret=CT_DataSIPParameterHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
        }
    
    return ret;
    }

void CT_DataSIPAddressHeaderBase::DoCmdSetSIPAddressL(const TTEFSectionName& aSection)
    {
    TPtrC name;
    CSIPAddress* sipAddress;
    
    if( GetStringFromConfig(aSection, KFldSIPAddress, name) )
        {
        sipAddress = static_cast<CSIPAddress*> (GetDataObjectL(name));
        INFO_PRINTF1(_L("call CSIPAddressHeaderBase::DoCmdSetSIPAddressL(CSIPAddress*)"));
        TRAPD(err, ((CSIPAddressHeaderBase*)GetSIPHeaderBase())->SetSIPAddressL(sipAddress));
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        CT_DataSIPAddress* wrapper = static_cast<CT_DataSIPAddress*>(GetDataWrapperL(name));
        wrapper->SetIsOwner(EFalse);
        }
    else        
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPAddress);
        SetBlockResult(EFail);
        }
    }


void CT_DataSIPAddressHeaderBase::DoCmdSIPAddress(const TTEFSectionName& aSection)
    {
    TBool datConstFlag;
    if (!GetBoolFromConfig(aSection, KFldConstFlag, datConstFlag))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldConstFlag);
        SetBlockResult(EFail);
        return;
        }
    
    HBufC8* text = NULL;
    TInt err;
    if (datConstFlag)
        {
        INFO_PRINTF1(_L("call const CSIPAddress& CSIPAddressHeaderBase::SIPAddress() const"));
        const CSIPAddress& sipAddress = ((const CSIPAddressHeaderBase*)GetSIPHeaderBase())->SIPAddress();
        TRAP(err, text = sipAddress.ToTextLC(EFalse); CleanupStack::Pop());
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPAddress& CSIPAddressHeaderBase::SIPAddress()"));
        CSIPAddress& sipAddress = ((CSIPAddressHeaderBase*)GetSIPHeaderBase())->SIPAddress();
        TRAP(err, text = sipAddress.ToTextLC(EFalse); CleanupStack::Pop());
        }
    
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }

    TPtrC expectedText;
    if (GetStringFromConfig(aSection, KFldExpectedDisplayName, expectedText))
        {
        TBuf8<KMaxTestExecuteCommandLength> expected;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(expected, expectedText);        
        if (text->Des() != expected)
            {
            TBuf<KMaxTestExecuteCommandLength> temp;
            CnvUtfConverter::ConvertToUnicodeFromUtf8(temp, text->Des());
            ERR_PRINTF3(KLogNotExpectedStringValue, &temp, &expectedText);
            SetBlockResult(EFail);
            } 
        else
            INFO_PRINTF1(_L("CSIPAddressHeaderBase::SIPAddress invoke successfully"));
        }
    }
