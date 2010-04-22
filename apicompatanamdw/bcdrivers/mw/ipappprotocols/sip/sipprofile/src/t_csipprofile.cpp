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


// This contains CT_DataSIPProfile

#include "t_csipprofile.h"
#include "T_SIPUtil.h"
#include <utf.h> 

/*@{*/
_LIT(KCmdDisown,							"Disown");
_LIT(KCmdGetParameter,						"GetParameter");
_LIT(KCmdType,								"Type");
_LIT(KDestructor,							"~");
_LIT(KFldSIPProfileTypeInfo,				"profiletypeinfo");
_LIT(KSipProfileClass,						"SipProfileClass=%d");
_LIT(KSERVERTYPE,							"servertype");
_LIT(KUINTPARAMKEY,							"uintparamkey");
_LIT(KBOOLPARAMKEY,							"boolparamkey");
_LIT(KMDESPARAMKEY,							"mdesparamkey");
_LIT(KTDESPARAMKEY,							"tdesparamkey");
_LIT(KFldExpected, 							"expected");
_LIT(KLogError,								"Error=%d");
_LIT(KLogErrMissingPara, 					"Missing parameter '%S'");
/*}@*/

CT_DataSIPProfile* CT_DataSIPProfile::NewL()
	{
	CT_DataSIPProfile*	ret=new (ELeave) CT_DataSIPProfile();
	CleanupStack::PushL(ret);
	ret->ConstructL();
	CleanupStack::Pop(ret);
	return ret;
	}

CT_DataSIPProfile::CT_DataSIPProfile() 
: CDataWrapperBase(),iSIPProfile(NULL)
	{
	}

void CT_DataSIPProfile::ConstructL()
	{
	}

CT_DataSIPProfile::~CT_DataSIPProfile()
	{
	DestroyData();
	}

/**
* Return a pointer to the object that the data wraps
*
* @return pointer to the object that the data wraps
*/
TAny* CT_DataSIPProfile::GetObject()
	{
	return iSIPProfile;
	}

void CT_DataSIPProfile::SetObjectL(TAny* aAny)
	{
	iSIPProfile=static_cast<CSIPProfile*> (aAny);
	}

void CT_DataSIPProfile::DisownObject()
	{
	iSIPProfile=NULL;
	}

void CT_DataSIPProfile::DestroyData()
	{
	delete iSIPProfile;
	iSIPProfile=NULL;
	}

CSIPProfile* CT_DataSIPProfile::GetSIPProfileObject()
	{
	return iSIPProfile;
	}

/**
Delegates the commands to a function

* @internalComponent
* @param aCommand Current command
* @param aSection Current ini file command section
* @param aAsyncErrorIndex index of command for SetAsyncError()
* @return TBool Returns whether the command was executed or not
*/
TBool CT_DataSIPProfile::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
	{
	TBool	retVal = ETrue;
	
	if( aCommand == KDestructor )
		{
		DestroyData();
		}
	else if( aCommand == KCmdType )
		{
		DoCmdType(aSection);
		}
	else if( aCommand == KCmdGetParameter )
		{
		DoCmdGetParameter(aSection);
		}
	else if( aCommand == KCmdDisown )
		{
		DisownObject();
		}
	else
		{
		retVal=EFalse;
		}
	return retVal;  
	}


void CT_DataSIPProfile::DoCmdType(const TTEFSectionName& aSection)
	{
	INFO_PRINTF1(_L("execute CSIPProfile::Type"));
	const TSIPProfileTypeInfo& info=GetSIPProfileObject()->Type();
	HBufC* tmp = HBufC::NewL(info.iSIPProfileName.Length());
	TPtr profilename(tmp->Des());
	CnvUtfConverter::ConvertToUnicodeFromUtf8(profilename,info.iSIPProfileName);
	INFO_PRINTF1(profilename);
	INFO_PRINTF2(KSipProfileClass,info.iSIPProfileClass);
	
	TSIPProfileTypeInfo expectedinfo;
	if (!CT_SIPUtil::GetSIPProfileTypeInfo(*this, aSection, KFldSIPProfileTypeInfo, expectedinfo))
		{
		INFO_PRINTF1(_L("CSIPProfile::Type invoke successfully"));
		}
	else
		{        
		if (expectedinfo.iSIPProfileName.Compare(info.iSIPProfileName))
			{
			INFO_PRINTF1(_L("expected SipProfileName does not match the actuall"));
			SetBlockResult(EFail);
			}
		else if(expectedinfo.iSIPProfileClass!=info.iSIPProfileClass)
			{
			INFO_PRINTF1(_L("expected SipProfileClass does not match the actuall"));
			SetBlockResult(EFail);
			}    
		else
			INFO_PRINTF1(_L("CSIPProfile::Type invoke successfully"));
		}

	delete tmp;
	tmp = NULL;
	}
    
void CT_DataSIPProfile::DoCmdGetParameter(const TTEFSectionName& aSection)
	{
	TUint32 servertype;
	TUint32 key;
	TUint32 uintvalue;
	TBool  boolvalue;
	TBuf8<128> buf;
	TDesC8 const *  pDes = &buf;
	
	if(CT_SIPUtil::GetSIPProfileParameter(*this,aSection,KSERVERTYPE,servertype))
		{
		if(CT_SIPUtil::GetSIPProfileParameter(*this,aSection,KTDESPARAMKEY,key))
			{
			INFO_PRINTF1(_L("execute CSIPProfile::GetParameter(TUint32,TUint32,const TDesC8 &)"));
			TInt err=GetSIPProfileObject()->GetParameter(servertype,key,pDes);
			if(err!=KErrNone)
				{
				ERR_PRINTF2(KLogError, err);
				SetError(err);
				}
			else
				{
				TBuf<60> actualDes;
				TPtrC expectDes;
				if (GetStringFromConfig(aSection, KFldExpected, expectDes))
					{
					CnvUtfConverter::ConvertToUnicodeFromUtf8(actualDes,*pDes);
					if(expectDes.Compare(actualDes)!=0)
						{
						ERR_PRINTF3(_L("The returned value is not as expected, expected: %S, actual: %S"), &expectDes, &actualDes);
						SetBlockResult(EFail);
						}
					}
				else  
					INFO_PRINTF1(_L("Get parameter successfully"));
				}
			}
		else
			{
			ERR_PRINTF2(KLogErrMissingPara, &KUINTPARAMKEY());
			SetBlockResult(EFail);
			}
		}
	else{
		if(CT_SIPUtil::GetSIPProfileParameter(*this,aSection,KUINTPARAMKEY,key))
			{
			INFO_PRINTF1(_L("execute CSIPProfile::GetParameter(TUint32,TUint32)"));
			TInt err=GetSIPProfileObject()->GetParameter(key,uintvalue);	
			if(err!=KErrNone)
				{
				ERR_PRINTF2(KLogError, err);
				SetError(err);
				}
			else
				{
				TUint expect;
				if(key == KSIPAccessPointId)
				    {
				    TPtrC str;
				    if(GetStringFromConfig(aSection, KFldExpected, str) && uintvalue != (expect = CT_SIPUtil::GetIAPIDL(str)))
				        {
                        ERR_PRINTF3(_L("The returned value is not as expected, expected: %d, actual: %d"), expect, uintvalue);
                        SetBlockResult(EFail);
				        }
				    }
				else if (GetTUintFromConfig(aSection, KFldExpected, expect))
					{
					if(expect!=uintvalue)
						{
						ERR_PRINTF3(_L("The returned value is not as expected, expected: %d, actual: %d"), expect, uintvalue);
						SetBlockResult(EFail);
						}
					}
				else
					INFO_PRINTF1(_L("Get parameter successfully"));
				}
			}
		
		else if(CT_SIPUtil::GetSIPProfileParameter(*this,aSection,KBOOLPARAMKEY,key))
			{
			INFO_PRINTF1(_L("execute CSIPProfile::GetParameter(TUint32,TBool)"));
			TInt err=GetSIPProfileObject()->GetParameter(key,boolvalue);
			if(err!=KErrNone)
				{
				ERR_PRINTF2(KLogError, err);
				SetError(err);
				}
			else
				{
				TBool expect;
				if (GetBoolFromConfig(aSection, KFldExpected, expect))
					{
					 if(!expect!=!boolvalue)
						 {
						 ERR_PRINTF3(_L("The returned value is not as expected, expected: %d, actual: %d"), expect, boolvalue);
						 SetBlockResult(EFail);
						 }
					 }
				else
					INFO_PRINTF1(_L("Get parameter successfully"));
				}
			}
		else if(CT_SIPUtil::GetSIPProfileParameter(*this,aSection,KTDESPARAMKEY,key))
			{
			INFO_PRINTF1(_L("execute CSIPProfile::GetParameter(TUint32,const TDesC8 &)"));
			TInt err=GetSIPProfileObject()->GetParameter(key,pDes);
			if(err!=KErrNone)
				{
				ERR_PRINTF2(KLogError, err);
				SetError(err);
				}
			else
				{
				TBuf<60> actualDes;
				TPtrC expectDes;
				if (GetStringFromConfig(aSection, KFldExpected, expectDes))
					{
					CnvUtfConverter::ConvertToUnicodeFromUtf8(actualDes,*pDes);
					if(expectDes.Compare(actualDes)!=0)
						{
						ERR_PRINTF3(_L("The returned value is not as expected, expected: %S, actual: %S"), &expectDes, &actualDes);
						SetBlockResult(EFail);
						}
					}
				else                    
					INFO_PRINTF1(_L("Get parameter successfully"));
				}
			}
		else if(CT_SIPUtil::GetSIPProfileParameter(*this,aSection,KMDESPARAMKEY,key))
			{
			INFO_PRINTF1(_L("execute CSIPProfile::GetParameter(TUint32,const MDesC8Array&)"));
			MDesC8Array const * pArray = NULL;
			TInt err=GetSIPProfileObject()->GetParameter(key,pArray);
			if(err!=KErrNone)
				{
				ERR_PRINTF2(KLogError, err);
				SetError(err);
				}
			else
				{
				CDesC8ArrayFlat* expectedArray = new (ELeave) CDesC8ArrayFlat(5);
				CleanupStack::PushL(expectedArray);
				if (CT_SIPUtil::GetMDesC8ArrayL(*this, aSection, KFldExpected, (MDesC8Array*)expectedArray))
					{
					TInt index;
					for(index=0; index<((CDesC8ArrayFlat*)pArray)->Count();index++)
						{
						if((*((CDesC8ArrayFlat*)pArray))[index].Compare((*expectedArray)[index]))
							{
							ERR_PRINTF2(_L("The actual array[%d] item is not as expected"), index);
							SetBlockResult(EFail);
							}
						}
					}
				else
					{
					INFO_PRINTF1(_L("Get parameter successfully"));
					}
				CleanupStack::PopAndDestroy(expectedArray);
				}
			}
		else
			{
			ERR_PRINTF1(_L("missing parameter"));
			SetBlockResult(EFail);
			}

		}
	}

