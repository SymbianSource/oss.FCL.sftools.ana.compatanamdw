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
#include "t_csipprofileregistrybase.h"
#include <sipprofile.h> 

/*@{*/
_LIT(KCmdDefaultProfileL,					"DefaultProfileL");
_LIT(KCmdLastRegistrationError,				"LastRegistrationError");
_LIT(KCmdProfileL,							"ProfileL");
_LIT(KCmdProfilesL,							"ProfilesL");
_LIT(KCmdSupportedProfileTypesL,			"SupportedProfileTypesL");

//Fields 
_LIT(KFldSipProfile,						"profile");
_LIT(KFldAOR,								"aor");
_LIT(KFldSIPProfileTypeInfo,				"typeinfo");
_LIT(KFldSIPProfileID,						"id");
_LIT(KFldExpected, 							"expected");

// Logging
_LIT(KLogError,								"Error=%d");
_LIT(KLogMissingParameter,					"Missing parameter '%S'");
_LIT(KLogNotExpectedValue,					"Not expected value, actual=%d, expect=%d");

/**
* Constructor. First phase construction
*/
CT_DataSIPProfileRegistryBase::CT_DataSIPProfileRegistryBase()
:	CDataWrapperBase(), iCheckEvent(EFalse)
	{
	}

/**
* Process a command read from the ini file
*
* @param aDataWrapper	test step requiring command to be processed
* @param aCommand	the command to process
* @param aSection		the entry in the ini file requiring the command to be processed
*
* @return ETrue if the command is processed
*/
TBool CT_DataSIPProfileRegistryBase::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
	{
	TBool ret=ETrue;

	if ( aCommand==KCmdDefaultProfileL )
		{
		DoCmdDefaultProfileL(aSection);
		}
	else if ( aCommand==KCmdLastRegistrationError )
		{
		DoCmdLastRegistrationError(aSection);
		}
	else if ( aCommand==KCmdProfileL )
		{
		DoCmdProfileL(aSection);
		}
	else if ( aCommand==KCmdProfilesL )
		{
		DoCmdProfilesL(aSection);
		}
	else if ( aCommand==KCmdSupportedProfileTypesL )
		{
		DoCmdSupportedProfileTypesL(aSection);
		}
	else
		{
		ret=EFalse;
		}

	return ret;
	}

void CT_DataSIPProfileRegistryBase::DoCmdDefaultProfileL(const TDesC& aSection)
	{
    TPtrC datSipProfile;
    if( !GetStringFromConfig(aSection, KFldSipProfile, datSipProfile) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSipProfile);
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPProfileRegistryBase::DefaultProfileL()"));
        CSIPProfile* sp = NULL;
        TRAPD(err, sp = GetSIPProfileRegistryBase()->DefaultProfileL());
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            SetDataObjectL(datSipProfile, sp);
            }
        }
	}

void CT_DataSIPProfileRegistryBase::DoCmdLastRegistrationError(const TDesC& aSection)
	{
	CSIPProfile* sp = NULL;
	if( !CT_SIPUtil::GetSIPProfile(*this, aSection, KFldSipProfile, sp) )
		{
		ERR_PRINTF2(KLogMissingParameter, KFldSipProfile);
		SetBlockResult(EFail);
		}
	else 
		{
		INFO_PRINTF1(_L("call CSIPProfileRegistryBase::LastRegistrationError(const CSIPProfile&)"));
		TInt err = GetSIPProfileRegistryBase()->LastRegistrationError(*sp);
		if(KErrNone != err)
			{
			ERR_PRINTF2(KLogError, err);
			SetError(err);
			}
		}
	}

void CT_DataSIPProfileRegistryBase::DoCmdProfileL(const TDesC& aSection)
	{
    TPtrC datSipProfile;
    if( !GetStringFromConfig(aSection, KFldSipProfile, datSipProfile) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSipProfile);
        SetBlockResult(EFail);
        }
    else 
        {
        TUint32 profileID = 0;
        if( !GetTUint32FromConfig(aSection, KFldSIPProfileID, profileID) )
            {
            INFO_PRINTF2(_L("ProfileId = %d"), (TInt)CT_SIPUtil::iProfileId);
            }

        INFO_PRINTF1(_L("call CSIPProfileRegistryBase::ProfileL(TUint32)"));
        CSIPProfile* sp = NULL;
        TRAPD(err, sp = GetSIPProfileRegistryBase()->ProfileL(CT_SIPUtil::iProfileId));
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            SetDataObjectL(datSipProfile, sp);
            }
        }
	}

void CT_DataSIPProfileRegistryBase::DoCmdProfilesL(const TDesC& aSection)
	{
	TPtrC aor;
	TSIPProfileTypeInfo info;
	RPointerArray<CSIPProfile> profiles;
	TBool isfailed = EFalse;
	
	if( GetStringFromConfig(aSection, KFldAOR, aor) )
		{
		INFO_PRINTF1(_L("call CSIPProfileRegistryBase::ProfilesL(const TDesC8&, RPointerArray<CSIPProfile>&)"));
		TBuf8<128> aor8;
		CT_SIPUtil::ConvertToUtf8(aor, aor8);
		TRAPD(err, GetSIPProfileRegistryBase()->ProfilesL(aor8, profiles));
		
		if(KErrNone != err)
			{
			ERR_PRINTF2(KLogError, err);
			SetError(err);
			}
		else
			{
			const TInt count = profiles.Count();
			INFO_PRINTF2(_L("ProfilesCount = %d"), count);
			TInt expected;
			if(GetIntFromConfig(aSection, KFldExpected, expected))
				{
				if(count != expected)
					{
					ERR_PRINTF3(KLogNotExpectedValue, err, expected);
					isfailed = ETrue;
					}
				}
			
			for(TInt i=0; i<count; i++)
				{
				INFO_PRINTF2(_L("index: %d"), i);
				const TSIPProfileTypeInfo& type = profiles[i]->Type();
				LogTypeInfo(type);
				
				const TDesC8* ptr = NULL;
				profiles[i]->GetParameter(KSIPUserAor, ptr);
				if(*ptr != aor8)
					{
					ERR_PRINTF1(_L("AOR is not expected."));
					isfailed = ETrue;           
					}
				}
			}
		}       
	else if( CT_SIPUtil::GetSIPProfileTypeInfo(*this, aSection, KFldSIPProfileTypeInfo, info) )
		{
		INFO_PRINTF1(_L("call CSIPProfileRegistryBase::ProfilesL(const TSIPProfileTypeInfo&, RPointerArray<CSIPProfile>&)"));
		TRAPD(err,GetSIPProfileRegistryBase()->ProfilesL(info, profiles));
		
		if(KErrNone != err)
			{
			ERR_PRINTF2(KLogError, err);
			SetError(err);
			}
		else
			{
			const TInt count = profiles.Count();
			INFO_PRINTF2(_L("ProfilesCount = %d"), count);
			TInt expected;
			if(GetIntFromConfig(aSection, KFldExpected, expected))
				{
				if(count != expected)
					{
					ERR_PRINTF3(KLogNotExpectedValue, err, expected);
					isfailed = ETrue;
					}
				}
			
			 for(TInt i=0; i<profiles.Count(); i++)
				{
				INFO_PRINTF2(_L("index: %d"), i);
				const TSIPProfileTypeInfo& type = profiles[i]->Type();
				LogTypeInfo(type);
				
				if( type.iSIPProfileClass != info.iSIPProfileClass || type.iSIPProfileName != info.iSIPProfileName )
					{
					ERR_PRINTF1(_L("profile type information is not expected."));
					isfailed = ETrue;
					}
				}
			}
		}
	else
		{
		INFO_PRINTF1(_L("call CSIPProfileRegistryBase::ProfilesL(RPointerArray<CSIPProfile>&)"));
		TRAPD(err, GetSIPProfileRegistryBase()->ProfilesL(profiles));
		
		if(KErrNone != err)
			{
			ERR_PRINTF2(KLogError, err);
			SetError(err);
			}
		else
			{
			const TInt count = profiles.Count();
			INFO_PRINTF2(_L("ProfilesCount = %d"), count);
			TInt expected;
			if(GetIntFromConfig(aSection, KFldExpected, expected))
				{
				if(count != expected)
					{
					ERR_PRINTF3(KLogNotExpectedValue, err, expected);
					isfailed = ETrue;
					}
				}
			
			for(TInt i=0; i<profiles.Count(); i++)
				  {
				  INFO_PRINTF2(_L("index: %d"), i);
				  const TSIPProfileTypeInfo& type = profiles[i]->Type();
				  LogTypeInfo(type);
				  }
			}
		}

	profiles.ResetAndDestroy();
	profiles.Close();

	if(isfailed)
		{
		SetBlockResult(EFail);
		}
	}

void CT_DataSIPProfileRegistryBase::DoCmdSupportedProfileTypesL(const TDesC& aSection)
	{
	INFO_PRINTF1(_L("call CSIPProfileRegistryBase::SupportedProfileTypesL(RArray<TSIPProfileTypeInfo>&)"));
	TBool isfailed = EFalse;
	RArray<TSIPProfileTypeInfo> infos;
	TRAPD(err, GetSIPProfileRegistryBase()->SupportedProfileTypesL(infos));
	if(err!=KErrNone)
		{
		ERR_PRINTF2(KLogError, err);
		SetError(err);
		}
	else
		{
		const TInt count = infos.Count();
		INFO_PRINTF2(_L("SupportedProfileTypes count = %d"), count);
		TInt expected;
		if(GetIntFromConfig(aSection, KFldExpected, expected))
			{
			if(count != expected)
				{
				ERR_PRINTF3(KLogNotExpectedValue, err, expected);
				isfailed = ETrue;
				}
			}
		
		for(TInt i=0; i<count; i++)
			{
			INFO_PRINTF2(_L("index: %d"), i);
			LogTypeInfo(infos[i]);
			}
		
		infos.Close();
		
		if(isfailed)
			{
			SetBlockResult(EFail);
			}
		}
	}

void CT_DataSIPProfileRegistryBase::LogTypeInfo(const TSIPProfileTypeInfo& info)
	{
	TBuf<64> SIPProfileClass;
	CT_SIPUtil::GetSIPProfileClassStr(info.iSIPProfileClass, SIPProfileClass);
	INFO_PRINTF1(SIPProfileClass);

	TBuf<64> SIPProfileName;
	CT_SIPUtil::ConvertToUnicode(info.iSIPProfileName, SIPProfileName);
	INFO_PRINTF1(SIPProfileName);
	}

void CT_DataSIPProfileRegistryBase::ProfileRegistryEventOccurred(TUint32 aProfileId, TEvent aEvent)
	{
	INFO_PRINTF1(_L("call MSIPProfileRegistryObserver::ProfileRegistryEventOccurred(TUint32, TEvent)"));
	INFO_PRINTF3(_L("profile ID : %d, event : %d"), (TInt)aProfileId, (TInt)aEvent);    

    if(aEvent == EProfileCreated)
         {
         CT_SIPUtil::iProfileId = aProfileId;
         }
    
	if(iCheckEvent)
		{		
        if(aEvent != iExpected)
            {
            ERR_PRINTF3(_L("The returned event is not expected: %d, actual: %d"), (TInt)iExpected, (TInt)aEvent);
            SetBlockResult(EFail);    
            }
		iCheckEvent = EFalse;
		DecOutstanding();		
		}	
	}

void CT_DataSIPProfileRegistryBase::ProfileRegistryErrorOccurred(TUint32 aProfileId, TInt aError)
	{
	INFO_PRINTF1(_L("call MSIPProfileRegistryObserver::ProfileRegistryErrorOccurred(TUint32, TInt)"));
	INFO_PRINTF3(_L("profile ID : %d, error : %d"), (TInt)aProfileId, aError);

    if(iCheckEvent)
        {
        iCheckEvent = EFalse;
        DecOutstanding();
        }
	}

