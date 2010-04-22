/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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

/**
@test
@internalComponent

This contains CT_FileManData
*/

//	User includes
#include "T_FileManData.h"

/*@{*/
///	Parameters
_LIT(KRFsName,							"RFs");
_LIT(KRFileName,						"RFile");
_LIT(KSource,							"source");
_LIT(KDestination,						"destination");
_LIT(KSwitch,							"switch%d");

/// CFileMan::TSwitch
_LIT(KSwitchOverWrite,					"EOverWrite");
_LIT(KSwitchRecurse,					"ERecurse");

///	Commands
_LIT(KCmdNewL,							"NewL");
_LIT(KCmdDestructor,					"~");
_LIT(KCmdCopy,							"Copy");
/*@}*/

CT_FileManData* CT_FileManData::NewL()
/**
 * Two phase constructor
 */
	{
	CT_FileManData* ret = new (ELeave) CT_FileManData();
	CleanupStack::PushL(ret);
	ret->ConstructL();
	CleanupStack::Pop(ret);
	return ret;
	}

CT_FileManData::CT_FileManData()
/**
 * Protected constructor. First phase construction
 */
:	iFileMan(NULL)
	{
	}

void CT_FileManData::ConstructL()
/**
 * Protected constructor. Second phase construction
 */
	{
	}

CT_FileManData::~CT_FileManData()
/**
 * Destructor.
 */
	{
	DoCleanup();
	}

void CT_FileManData::DoCleanup()
/**
 * Contains cleanup implementation
 */
	{
	//Deleting RFile.
	if(iFileMan != NULL)
		{
		INFO_PRINTF1(_L("Deleting current CFileMan"));
		delete iFileMan;
		iFileMan = NULL;
		}
	}

TAny* CT_FileManData::GetObject()
/**
 * Return a pointer to the object that the data wraps
 *
 * @return pointer to the object that the data wraps
 */
	{
	return iFileMan;
	}

TBool CT_FileManData::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
/**
 * Process a command read from the ini file
 *
 * @param aCommand	the command to process
 * @param aSection		the entry in the ini file requiring the command to be processed
 *
 * @return ETrue if the command is processed
 */
	{
	TBool retVal = ETrue;

	if (aCommand == KCmdNewL)
		{
		DoCmdNewL(aSection);
		}
	else if (aCommand == KCmdDestructor)
		{
		DoCmdDestructor();
		}
	else if (aCommand == KCmdCopy)
		{
		DoCmdCopyL(aSection);
		}
	else
		{
		retVal = EFalse;
		}
	return retVal;
	}

void CT_FileManData::DoCmdNewL(const TDesC& aSection)
/** Creates new RFile class instance */
	{
	//Deletes previous RFile class instance if it was already created.
	DoCleanup();

	RFs*	rfs=NULL;
	TPtrC	rfsName;
	TBool	dataOk=GET_MANDATORY_STRING_PARAMETER(KRFsName(), aSection, rfsName);
	if ( dataOk )
		{
		rfs=(RFs*)GetDataObjectL(rfsName);

		if (rfs)
			{
			// do create
			TRAPD(err, iFileMan = CFileMan::NewL(*rfs));
			if ( err!=KErrNone )
				{
				ERR_PRINTF2(_L("CFileMan::NewL %d"), err);
				SetError( err );
				}
			}
		else
			{
			ERR_PRINTF1(_L("RFs object is NULL"));
			SetBlockResult(EFail);
			}
		}
	}

void CT_FileManData::DoCmdDestructor()
/** Destroy RFile the object */
	{
	DoCleanup();
	}

void CT_FileManData::DoCmdCopyL(const TDesC& aSection)
/** Creates new RFile class instance */
	{
	TBool	dataOk=ETrue;

	RFile*	file=NULL;
	TPtrC	fileNameSource;
	TBool	hasFile=GET_OPTIONAL_STRING_PARAMETER(KRFileName, aSection, fileNameSource);
	if ( hasFile )
		{
		file=(RFile*)GetDataObjectL(fileNameSource);
		}
	else
		{
		if ( !GET_MANDATORY_STRING_PARAMETER(KSource, aSection, fileNameSource) )
			{
			dataOk=EFalse;
			}
		}

	TPtrC	fileNameDestination;
	if ( !GET_MANDATORY_STRING_PARAMETER(KDestination, aSection, fileNameDestination) )
		{
		dataOk=EFalse;
		}

	TUint	copySwitch=CFileMan::EOverWrite;
	if ( !ReadFileManSwitch(KSwitch(), aSection, copySwitch) )
		{
		dataOk=EFalse;
		}
	if ( dataOk )
		{
		TInt	err=KErrNone;
		if ( hasFile )
			{
			if (file)
				{
				err=iFileMan->Copy(*file, fileNameDestination);
				}
			else
				{
				ERR_PRINTF1(_L("RFile object is NULL"));
				SetBlockResult(EFail);
				}
			}
		else
			{
			err=iFileMan->Copy(fileNameSource, fileNameDestination);
			}
		if ( err!=KErrNone )
			{
			ERR_PRINTF2(_L("CFileMan::Copy %d"), err);
			SetError( err );
			}
		}
	}

TBool CT_FileManData::ReadFileManSwitch(const TDesC& aFormat, const TDesC& aSection, TUint& aFileManSwitch)
	{
	TBuf<KMaxTestExecuteCommandLength>	tempStore;
	TInt								index=0;
	TBool								moreData=ETrue;
	TPtrC								switchString;
	TInt								switchInt;
	TUint								fileManSwitch=0;
	TBool								ret=ETrue;
	while ( moreData )
		{
		tempStore.Format(aFormat, ++index);
		if ( GET_OPTIONAL_STRING_PARAMETER(tempStore, aSection,  switchString) )
			{
			CFileMan::TSwitch	switchValue;
			if ( ConvertFileManSwitch(switchString, switchValue) )
				{
				fileManSwitch |= switchValue;
				}
			else
				{
				if ( GET_OPTIONAL_INT_PARAMETER(tempStore, aSection, switchInt) )
					{
					fileManSwitch |= switchInt;
					}
				else
					{
					ret=EFalse;
					ERR_PRINTF2(_L("Illegal group %S"), &switchString);
					SetBlockResult(EFail);
					}
				}
			}
		else
			{
			moreData=EFalse;
			}
		}

	//	(index!=1) => some data was read in
	if ( (ret) && (index!=1) )
		{
		aFileManSwitch=fileManSwitch;
		}

	return ret;
	}

TBool CT_FileManData::ConvertFileManSwitch(const TDesC& aSwitchString, CFileMan::TSwitch& aSwitchValue)
	{
	TBool	ret=ETrue;

	if ( aSwitchString == KSwitchOverWrite )
		{
		aSwitchValue=CFileMan::EOverWrite;
		}
	else if ( aSwitchString == KSwitchRecurse )
		{
		aSwitchValue=CFileMan::ERecurse;
		}
	else
		{
		ret=EFalse;
		}

	return ret;
	}
