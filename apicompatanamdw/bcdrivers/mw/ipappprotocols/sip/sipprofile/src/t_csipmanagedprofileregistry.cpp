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


// This contains CT_DataSIPManagedProfileRegistry

#include "T_SIPUtil.h"
#include "t_csipmanagedprofileregistry.h"


/*@{*/
_LIT(KCmdCreate,							"CreateL");
_LIT(KCmdDestroyL,							"DestroyL");
_LIT(KCmdIsInUseL,							"IsInUseL");
_LIT(KCmdNewL,								"NewL");
_LIT(KCmdNewLC,								"NewLC");
_LIT(KCmdSaveL,								"SaveL");
_LIT(KCmdDestructor,						"~");

//Fields 
_LIT(KFldSIPProfileTypeInfo,				"SIPProfileTypeInfo");
_LIT(KFldSIPManagedProfile,					"SIPManagedProfile");
_LIT(KFldSIPProfile, 						"SIPProfile");
_LIT(KFldExpected, 							"expected");

//Error
_LIT(KLogErrMissingPara,					"Missing parameter '%S'");
_LIT(KLogError,								"Error=%d");


CT_DataSIPManagedProfileRegistry*	CT_DataSIPManagedProfileRegistry::NewL()
    {
	CT_DataSIPManagedProfileRegistry* self = new (ELeave)CT_DataSIPManagedProfileRegistry();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
    }

void CT_DataSIPManagedProfileRegistry::DestroyData() 
	{
	delete iSIPManagedProfileRegistry;
	iSIPManagedProfileRegistry=NULL;
	}

CT_DataSIPManagedProfileRegistry::~CT_DataSIPManagedProfileRegistry()
   {
   DestroyData();
   }


void CT_DataSIPManagedProfileRegistry::ConstructL()
	{
	}

CT_DataSIPManagedProfileRegistry::CT_DataSIPManagedProfileRegistry() 
: CT_DataSIPProfileRegistryBase(),	iSIPManagedProfileRegistry(0)
	{ 
	}

TAny*	CT_DataSIPManagedProfileRegistry::GetObject()
	{
	return iSIPManagedProfileRegistry;
	}

void CT_DataSIPManagedProfileRegistry::SetObjectL(TAny* aAny)
	{
	DestroyData();
	iSIPManagedProfileRegistry=static_cast<CSIPManagedProfileRegistry*> (aAny);
	}

void CT_DataSIPManagedProfileRegistry::DisownObjectL()
	{
	iSIPManagedProfileRegistry=NULL;
	}

CSIPProfileRegistryBase* CT_DataSIPManagedProfileRegistry::GetSIPProfileRegistryBase() const
	{
	return iSIPManagedProfileRegistry;
	}

TBool CT_DataSIPManagedProfileRegistry::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
	{
	/* Another work package will complete the implement of this */
	TBool	ret = ETrue;

	if ( aCommand == KCmdNewL )
		{
		DoCmdNewL();
		}
	else if ( aCommand == KCmdNewLC)
		{
		DoCmdNewLC();
		}
	else if ( aCommand == KCmdDestroyL )
		{
		DoCmdDestroyL(aSection);
		}
	else if ( aCommand == KCmdCreate )
		{
		DoCmdCreateL(aSection);
		}
	else if ( aCommand == KCmdIsInUseL )
		{
		DoCmdIsInUseL(aSection);
		}
	else if ( aCommand == KCmdSaveL )
		{
		DoCmdSaveL(aSection);
		}
	else if ( aCommand == KCmdDestructor )
		{
		DoCmdDestructor();
		}

	else
		{
		ret=CT_DataSIPProfileRegistryBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
		}

	return ret;
	}

void CT_DataSIPManagedProfileRegistry::DoCmdCreateL(const TTEFSectionName& aSection)
	{
	INFO_PRINTF1(_L("call CSIPManagedProfileRegistry::CreateL"));
	CSIPManagedProfile* sipManagedProfile = NULL;

	TPtrC sipManagedProfileName;
	TSIPProfileTypeInfo profileType ;

	if( !GetStringFromConfig(aSection, KFldSIPManagedProfile, sipManagedProfileName))
		 {
		 ERR_PRINTF2(KLogErrMissingPara, &KFldSIPManagedProfile());
		 SetBlockResult(EFail);
		 }  
	else
		{
		if( !CT_SIPUtil::GetSIPProfileTypeInfo(*this, aSection, KFldSIPProfileTypeInfo, profileType))
			{
			ERR_PRINTF2(KLogErrMissingPara, &KFldSIPProfileTypeInfo());
			SetBlockResult(EFail);
			}       
		else
			{       
			TRAPD(err, sipManagedProfile = iSIPManagedProfileRegistry->CreateL(profileType));
			if(err!=KErrNone)
				{
				ERR_PRINTF2(KLogError, err);
				SetError(err);
				}
			else 
				{ 
				SetDataObjectL(sipManagedProfileName , sipManagedProfile);
				}
			}
		}
	}

void CT_DataSIPManagedProfileRegistry::DoCmdDestroyL(const TTEFSectionName& aSection)
	{
	INFO_PRINTF1(_L("call CSIPManagedProfileRegistry::DestroyL"));
	CSIPProfile* sp(NULL);

	if(!CT_SIPUtil::GetSIPProfile(*this,aSection,KFldSIPProfile,sp))
		{
		ERR_PRINTF2(KLogErrMissingPara, &KFldSIPProfile());
		SetBlockResult(EFail);
		}
	else
		{
        if( !CT_SIPUtil::GetEvent(*this, aSection, KFldExpected, iExpected))
            {
            ERR_PRINTF2(KLogErrMissingPara, KFldExpected);
            SetBlockResult(EFail);
            }
        else
            {            
            TRAPD(err, iSIPManagedProfileRegistry->DestroyL(*sp));          
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

void  CT_DataSIPManagedProfileRegistry::DoCmdIsInUseL(const TTEFSectionName& aSection)
	{
	INFO_PRINTF1(_L("call CSIPManagedProfileRegistry::IsInUseL"));
	CSIPProfile* sp(NULL);
	TBool actualVal = EFalse ; 
	TBool expectedVal;

	if(!CT_SIPUtil::GetSIPProfile(*this,aSection,KFldSIPProfile,sp))
		{
		ERR_PRINTF2(KLogErrMissingPara, &KFldSIPProfile());
		SetBlockResult(EFail);
		}
	else
	   {
		TRAPD(err, actualVal = iSIPManagedProfileRegistry->IsInUseL(*sp));
		if  ( err!=KErrNone)
		  {
		  ERR_PRINTF2(KLogError, err);
		  SetError(err);
		  }
		else
		  {
		  if (GetBoolFromConfig(aSection, KFldExpected, expectedVal))
			   {
			   if (actualVal!=expectedVal)
				   {
				   ERR_PRINTF3(_L("The returned value is not as expected, expected: %d, actual: %d"), expectedVal, actualVal);
				   SetBlockResult(EFail);
				   }
			   }
		  }
	   }
	}

void  CT_DataSIPManagedProfileRegistry::DoCmdSaveL(const TTEFSectionName& aSection) 
	{
	INFO_PRINTF1(_L("call CSIPManagedProfileRegistry::SaveL"));
	CSIPProfile* sp(NULL);	

	if(!CT_SIPUtil::GetSIPProfile(*this,aSection,KFldSIPProfile,sp))
		{
		ERR_PRINTF2(KLogErrMissingPara, &KFldSIPProfile());
		SetBlockResult(EFail);
		}
	else
	    {
	    if( !CT_SIPUtil::GetEvent(*this, aSection, KFldExpected, iExpected))
            {
            ERR_PRINTF2(KLogErrMissingPara, KFldExpected);
            SetBlockResult(EFail);
            }
        else
            {            
            TRAPD(err, iSIPManagedProfileRegistry->SaveL(*sp));         
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

void CT_DataSIPManagedProfileRegistry::DoCmdDestructor()
	{
	INFO_PRINTF1(_L("call CSIPManagedProfileRegistry::~CSIPManagedProfileRegistry()"));
	DestroyData();
	}

void CT_DataSIPManagedProfileRegistry::DoCmdNewL()
	{
	TRAPD(err,iSIPManagedProfileRegistry=CSIPManagedProfileRegistry::NewL(*this));
	if ( err!=KErrNone)
		{
		ERR_PRINTF2(KLogError, err);
		SetError(err);
		}
	}
	
void CT_DataSIPManagedProfileRegistry::DoCmdNewLC() 
	{
	CSIPManagedProfileRegistry* temp = NULL;
	TRAPD(err,temp=CSIPManagedProfileRegistry::NewLC(*this);CleanupStack::Pop(temp));
	if  ( err!=KErrNone)
		{
		ERR_PRINTF2(KLogError, err);
		SetError(err);
		}   
	else{
		iSIPManagedProfileRegistry=temp;
		}
	}
