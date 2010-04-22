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


// This contains CT_DataSIPManagedProfile
#include "t_csipmanagedprofile.h"
#include <sipmanagedprofile.h> 
#include "T_SIPUtil.h"
#include <utf.h>

/*@{*/
_LIT(KDestructor,                   "~");
_LIT(KCmdSetParameter,              "SetParameter");
_LIT(KCmdSetType,                   "SetType");
_LIT(KCmdCloneL,                    "CloneL");

// Fields 
_LIT(KFldParamKey,                  "paramkey");
_LIT(KFldParamValue,                "paramvalue");
_LIT(KFldSIPManagedProfile,         "sipmanagedprofile");
_LIT(KFldServerType,                "servertype");
_LIT(KFldSIPProfileTypeInfo,        "profiletypeinfo");

// Constants
_LIT(KParamKeyTUint32,              "keytoTUint32value");
_LIT(KParamKeyString,               "KeytoStringvalue");
_LIT(KParamKeyBool,                 "keytoTBoolvalue");
_LIT(KParamKeyMDesC8Array,          "keytoMDesC8Arrayvalue");

// Error
_LIT(KLogError,                     "Error=%d");
_LIT(KMissingParameter,             "missing parameter '%S'");
//Info

CT_DataSIPManagedProfile* CT_DataSIPManagedProfile::NewL()
    {
    CT_DataSIPManagedProfile* self = new (ELeave) CT_DataSIPManagedProfile();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }
	
CT_DataSIPManagedProfile::~CT_DataSIPManagedProfile()
    {
    DestroyData();
    }

void CT_DataSIPManagedProfile::DestroyData()
    {
    delete iSIPManagedProfile;
    iSIPManagedProfile = NULL;
    }

TAny* CT_DataSIPManagedProfile::GetObject()
    {
    return iSIPManagedProfile;
    }

void CT_DataSIPManagedProfile::SetObjectL(TAny* aAny)
    {
    DestroyData();
    iSIPManagedProfile = static_cast<CSIPManagedProfile*> (aAny);
    }

void CT_DataSIPManagedProfile::DisownObjectL()
    {
    iSIPManagedProfile = NULL;
    }

CT_DataSIPManagedProfile::CT_DataSIPManagedProfile() :
    CT_DataSIPProfile(), iSIPManagedProfile(NULL), iapID(0)
    {
    }

void CT_DataSIPManagedProfile::ConstructL()
    {
    }

TBool CT_DataSIPManagedProfile::DoCommandL(const TTEFFunction& aCommand,
        const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
    {
    TBool ret = ETrue;
    if (aCommand == KDestructor)
        {
        DoCmdDestructor();
        }
    else if (aCommand == KCmdSetParameter)
        {
        DoCmdSetParameterL(aSection);
        }
    else if (aCommand == KCmdSetType)
        {
        DoCmdSetType(aSection);
        }
    else if (aCommand == KCmdCloneL)
        {
        DoCmdCloneL(aSection);
        }
    else
        {
        ret = CT_DataSIPProfile::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
        }
    return ret;
    }

void CT_DataSIPManagedProfile::DoCmdCloneL(const TTEFSectionName& aSection)
    {
    CSIPManagedProfile* sipManagedProfile = NULL;
    TPtrC datSipProfile;
    if (!GetStringFromConfig(aSection, KFldSIPManagedProfile, datSipProfile))
        {
        ERR_PRINTF2(KMissingParameter, &KFldSIPManagedProfile());
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("execute CSIPManagedProfile::CloneL()"));
        TRAPD(err,sipManagedProfile=iSIPManagedProfile->CloneL());
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            SetDataObjectL(datSipProfile, sipManagedProfile);
            }
        }
    }

void CT_DataSIPManagedProfile::DoCmdSetParameterL(
        const TTEFSectionName& aSection)
    {
    TInt err = KErrNone;
    TUint32 key;
    TBool dataOK = EFalse;

    // Parameter of TUint32 type.
    if (CT_SIPUtil::GetSIPProfileParameter(*this, aSection, KParamKeyTUint32, key))
        {
        if(key == KSIPAccessPointId)
            {
            TPtrC strVal;
            if(GetStringFromConfig(aSection, KFldParamValue,strVal))
                {
                TUint32 apId = CT_SIPUtil::GetIAPIDL(strVal);
                if(apId == 0)
                    {
                    apId = CT_SIPUtil::AddAccessPointL(strVal);
                    INFO_PRINTF3(_L("Add a new IAP (name = %S and ID = [%d])"), &strVal, apId );
                    }
                else
                    {
                    INFO_PRINTF3(_L("IAP (name = %S) found with IAP (ID = [%d])"), &strVal, apId );
                    }
                
                if(apId == 0)
                    {
                    ERR_PRINTF1(_L("Failed to add a IAP."));
                    SetBlockResult(EFail);
                    return;
                    }
                else
                    {
                    INFO_PRINTF1(_L("execute CSIPManagedProfile::SetParameter(TUint32,TUint32)"));
                    err = iSIPManagedProfile->SetParameter(KSIPAccessPointId, apId);
                    }
                dataOK = ETrue;
                }
            }
        else
            {
            TUint32 intVal;
            if (GetTUint32FromConfig(aSection, KFldParamValue, intVal))
                {
                dataOK = ETrue;
                INFO_PRINTF1(_L("execute CSIPManagedProfile::SetParameter(TUint32,TUint32)"));
                err = iSIPManagedProfile->SetParameter(key, intVal);
                }
            }
        }
    // Parameter of TDesC type
    else if (CT_SIPUtil::GetSIPProfileParameter(*this, aSection, KParamKeyString, key))
        {
        TPtrC strVal;
        TUint32 serverType;
        if (GetStringFromConfig(aSection, KFldParamValue, strVal))
            {
            dataOK = ETrue;
            // For a particular server type
            TBuf8<KMaxTestExecuteCommandLength> val;
            CnvUtfConverter::ConvertFromUnicodeToUtf8(val, strVal);
            if (CT_SIPUtil::GetSIPProfileParameter(*this, aSection, KFldServerType, serverType))
                {
                INFO_PRINTF1(_L("execute CSIPManagedProfile::SetParameter(TUint32,TUint32,const TDesC8 &)"));
                err = iSIPManagedProfile->SetParameter(serverType, key, val);
                }
            else
                {
                INFO_PRINTF1(_L("execute CSIPManagedProfile::SetParameter(TUint32,const TDesC8 &)"));
                err = iSIPManagedProfile->SetParameter(key, val);
                }
            }
        }
    // Parameter of TBool type.
    else if (CT_SIPUtil::GetSIPProfileParameter(*this, aSection, KParamKeyBool, key))
        {
        TBool boolVal;
        if (GetBoolFromConfig(aSection, KFldParamValue, boolVal))
            {
            dataOK = ETrue;
            INFO_PRINTF1(_L("execute CSIPManagedProfile::SetParameter(TUint32,TBool)"));
            err = iSIPManagedProfile->SetParameter(key, boolVal);
            }
        }
    // Parameter of MDesC8Array type.
    else if (CT_SIPUtil::GetSIPProfileParameter(*this, aSection, KParamKeyMDesC8Array, key))
        {
        CDesC8ArrayFlat* arrayVal = new (ELeave) CDesC8ArrayFlat(1);
        CleanupStack::PushL(arrayVal);

        dataOK = ETrue;
        INFO_PRINTF1(_L("execute CSIPManagedProfile::SetParameter(TUint32,const MDesC8Array&)"));
        CT_SIPUtil::GetMDesC8ArrayL(*this, aSection, KFldParamValue, (MDesC8Array*)arrayVal);
        err = iSIPManagedProfile->SetParameter(key, *arrayVal);
        CleanupStack::PopAndDestroy(arrayVal);
        }
    // Error handling
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldParamKey());
        SetBlockResult(EFail);
        return;
        }
    
    if (!dataOK)
        {
        ERR_PRINTF2(KMissingParameter, &KFldParamValue());
        SetBlockResult(EFail);
        }
    else if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void CT_DataSIPManagedProfile::DoCmdSetType(const TTEFSectionName& aSection)
    {
    TSIPProfileTypeInfo info;
    if (!CT_SIPUtil::GetSIPProfileTypeInfo(*this, aSection, KFldSIPProfileTypeInfo, info))
        {
        ERR_PRINTF2(KMissingParameter, &KFldSIPProfileTypeInfo());
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("execute CSIPManagedProfile::SetType(const TSIPProfileTypeInfo&)"));
        iSIPManagedProfile->SetType(info);
        }
    }

void CT_DataSIPManagedProfile::DoCmdDestructor()
    {
    INFO_PRINTF1(_L("call CSIPManagedProfile::~CSIPManagedProfile()"));
    DestroyData();
    }

CSIPProfile* CT_DataSIPManagedProfile::GetSIPProfileObject()
    {
    return iSIPManagedProfile;
    }


