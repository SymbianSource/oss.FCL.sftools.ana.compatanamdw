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


#include "t_csiprouteheaderbase.h"
#include "t_csipaddress.h"
#include "T_SIPUtil.h"
#include <siprouteheaderbase.h>

/*@{*/
_LIT(KCmdSetSIPAddressL,            "SetSIPAddressL");
_LIT(KCmdSIPAddress,                "SIPAddress");

//Fields 
_LIT(KFldSIPAddress,                "sipaddress");
_LIT(KFldModifiable,                "modifiable");

// Logging
_LIT(KLogError,                     "Error=%d");
_LIT(KLogMissingParameter,          "Missing parameter '%S'");


CT_DataSIPRouteHeaderBase::CT_DataSIPRouteHeaderBase()
: CT_DataSIPParameterHeaderBase()
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
TBool CT_DataSIPRouteHeaderBase::DoCommandL(const TTEFFunction& aCommand, 
        const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
    {
    TBool ret = ETrue;
    
    if ( aCommand==KCmdSetSIPAddressL )
        {
        DoCmdSetSIPAddressL(aSection);
        }
    else if (aCommand==KCmdSIPAddress)
        {
        DoCmdSIPAddressL(aSection);
        }  
    else
        {
        ret = CT_DataSIPParameterHeaderBase::DoCommandL(aCommand,aSection,aAsyncErrorIndex);
        }
    
    return ret;
    }

void CT_DataSIPRouteHeaderBase::DoCmdSetSIPAddressL(const TTEFSectionName& aSection)
    {
    CSIPAddress* address = NULL;
    if( !CT_SIPUtil::GetSIPAddressL(*this, aSection, KFldSIPAddress, address) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPAddress);
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("execute CSIPRouteHeaderBase::SetSIPAddressL(CSIPAddress*)"));
        CSIPRouteHeaderBase* routeheaderbase = static_cast<CSIPRouteHeaderBase*>(GetSIPHeaderBase());
        TRAPD(err, routeheaderbase->SetSIPAddressL(address));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            TPtrC wrapperName;
            (void)GetStringFromConfig(aSection, KFldSIPAddress, wrapperName);
            CT_DataSIPAddress* wrapper = static_cast<CT_DataSIPAddress*>(GetDataWrapperL(wrapperName));
            wrapper->SetIsOwner(EFalse);
            }
        }
    }

void CT_DataSIPRouteHeaderBase::DoCmdSIPAddressL(const TTEFSectionName& aSection)
    {
    TPtrC wrapperName;    
    if( !GetStringFromConfig(aSection, KFldSIPAddress, wrapperName) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPAddress);
        SetBlockResult(EFail);
        }
    else
        {
        TBool modifiable = EFalse;
        (void) GetBoolFromConfig(aSection, KFldModifiable, modifiable);
        
        CSIPRouteHeaderBase* routeheaderbase = static_cast<CSIPRouteHeaderBase*>(GetSIPHeaderBase());
        if(modifiable)
            {
            INFO_PRINTF1(_L("execute CSIPRouteHeaderBase::SIPAddress()"));
            CSIPAddress& address = routeheaderbase->SIPAddress();
            SetDataObjectL(wrapperName, (void*)&address);
            }
        else
            {
            INFO_PRINTF1(_L("execute const CSIPRouteHeaderBase::SIPAddress() const"));
            const CSIPAddress& address = ((const CSIPRouteHeaderBase*)routeheaderbase)->SIPAddress();
            SetDataObjectL(wrapperName, (void*)&address);
            }
        
        CT_DataSIPAddress* wrapper = static_cast<CT_DataSIPAddress*>(GetDataWrapperL(wrapperName));
        wrapper->SetIsOwner(EFalse);
        }
    }

