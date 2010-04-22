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

This contains CT_FileData
*/

//	User includes
#include "T_FileData.h"

/*@{*/
///	Parameters
_LIT(KFile,								"file");
_LIT(KUParamName,						"name");
_LIT(KRFsName,							"RFs");
_LIT(KFileMode,							"file_mode");
_LIT(KDataWrite,						"datawrite");

// FileMode
_LIT(KEFileShareExclusive,	 			"EFileShareExclusive");
_LIT(KEFileShareReadersOnly,	 		"EFileShareReadersOnly");
_LIT(KEFileShareAny,	 				"EFileShareAny");
_LIT(KEFileShareReadersOrWriters,	 	"EFileShareReadersOrWriters");
_LIT(KEFileStream,	 					"EFileStream");
_LIT(KEFileStreamText,					"EFileStreamText");
_LIT(KEFileRead,	 					"EFileRead");
_LIT(KEFileWrite,						"EFileWrite");
_LIT(KEFileReadAsyncAll,	 			"EFileReadAsyncAll");

///	Commands
_LIT(KCmdNew,							"new");
_LIT(KCmdClose,							"Close");
_LIT(KCmdDestructor,					"~");
_LIT(KCmdOpen,							"Open");
_LIT(KCmdCreate,						"Create");
_LIT(KCmdWrite,							"Write");

/*@}*/

CT_FileData* CT_FileData::NewL()
/**
 * Two phase constructor
 */
	{
	CT_FileData* ret = new (ELeave) CT_FileData();
	CleanupStack::PushL(ret);
	ret->ConstructL();
	CleanupStack::Pop(ret);
	return ret;
	}

CT_FileData::CT_FileData()
/**
 * Protected constructor. First phase construction
 */
:	iFile(NULL)
	{
	}

void CT_FileData::ConstructL()
/**
 * Protected constructor. Second phase construction
 */
	{
	}

CT_FileData::~CT_FileData()
/**
 * Destructor.
 */
	{
	DoCleanup();
	}

void CT_FileData::DoCleanup()
/**
 * Contains cleanup implementation
 */
	{
	//Deleting RFile.
	if(iFile != NULL)
		{
		INFO_PRINTF1(_L("Deleting current RFile"));
		delete iFile;
		iFile = NULL;
		}
	}

TAny* CT_FileData::GetObject()
/**
 * Return a pointer to the object that the data wraps
 *
 * @return pointer to the object that the data wraps
 */
	{
	return iFile;
	}

TBool CT_FileData::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
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

	if (aCommand == KCmdNew)
		{
		TRAPD(err,DoCmdNewL());
		if ( err!=KErrNone )
			{
			ERR_PRINTF2(_L("new error %d"), err);
			SetError(err);
			}
		}
	else if (aCommand == KCmdDestructor)
		{
		DoCmdDestructor();
		}
	else if (aCommand == KCmdOpen)
		{
		DoCmdOpenL(aSection);
		}
	else if (aCommand == KCmdWrite)
		{
		DoCmdWriteL(aSection);
		}
	else if (aCommand == KCmdClose)
		{
		DoCmdClose();
		}
	else if (aCommand == KCmdCreate)
		{
		DoCmdCreateL(aSection);
		}
	else
		{
		retVal = EFalse;
		}
	return retVal;
	}

void CT_FileData::DoCmdNewL()
/** Creates new RFile class instance */
	{
	//Deletes previous RFile class instance if it was already created.
	DoCleanup();

	INFO_PRINTF1(_L("Create new RFile class instance"));

	// do create
	iFile = new (ELeave) RFile();
	}

void CT_FileData::DoCmdDestructor()
/** Destroy RFile the object */
	{
	DoCleanup();
	}

void CT_FileData::DoCmdOpenL(const TDesC& aSection)
//Opens files
	{
	RFs*	rfsObject=NULL;
	TPtrC	rfsObjectName;
	TBool	dataOk=GET_MANDATORY_STRING_PARAMETER(KRFsName(), aSection, rfsObjectName);
	if ( dataOk )
		{
		rfsObject=(RFs*)GetDataObjectL(rfsObjectName);
		}

	TPtrC	filePath;
	if ( !GET_MANDATORY_STRING_PARAMETER(KFile(), aSection, filePath) )
		{
		dataOk=EFalse;
		}

	TFileMode	fileMode = EFileShareAny;
	if ( !GetFileMode(KFileMode, aSection, fileMode) )
		{
		ERR_PRINTF2(_L("Open() error reading parameter. %S"), &KFileMode());
		SetBlockResult(EFail);
		dataOk=EFalse;
		}

	if ( dataOk )
		{
		if (rfsObject)
			{
			TInt	err = iFile->Open(*rfsObject, filePath, fileMode);
			if ( err!=KErrNone )
				{
				ERR_PRINTF2(_L("Open() Error:%d"), err);
				SetError(err);
				}
			}
		else
			{
			ERR_PRINTF1(_L("RFs object is NULL"));
			SetBlockResult(EFail);
			}
		}
	}

void CT_FileData::DoCmdWriteL(const TDesC& aSection)
//Write data to file
	{
	TPtrC	data;
	if(GET_MANDATORY_STRING_PARAMETER(KDataWrite, aSection, data))
		{
		//convert 16 bit to 8
		HBufC8*	buffer8 = NULL;
		TRAPD (err, buffer8 = HBufC8::NewL( data.Length() ));
		if (err == KErrNone)
			{
			buffer8->Des().Copy(data);

			err = iFile->Write(buffer8->Des());
			if(err == KErrNone)
				{
				INFO_PRINTF1(_L("Write() data OK"));
				}
			else
				{
				ERR_PRINTF2(_L("Write() Error :% d"), err);
				SetError(err);
				}
			delete buffer8;
			buffer8 = NULL;
			}
		}
	else
		{
		ERR_PRINTF2(_L("Write() error reading parameter. %S"), &KDataWrite());
		}
	}

void CT_FileData::DoCmdClose()
	{
	INFO_PRINTF1(_L("Closing RFile"));
	iFile->Close();
	}

void CT_FileData::DoCmdCreateL(const TDesC& aSection)
	{
	RFs*	rfsObject=NULL;
	TPtrC	rfsObjectName;
	TBool	dataOk=GET_MANDATORY_STRING_PARAMETER(KRFsName, aSection, rfsObjectName);
	if ( dataOk )
		{
		rfsObject=(RFs*)GetDataObjectL(rfsObjectName);
		}

	//	Gets name of file from ini file.
	TPtrC	name;
	if ( !GET_MANDATORY_STRING_PARAMETER(KUParamName(), aSection, name) )
		{
		dataOk=EFalse;
		}

	TFileMode	fileMode = EFileShareAny;
	if ( !GetFileMode(KFileMode, aSection, fileMode) )
		{
		ERR_PRINTF2(_L("Create() error reading parameter. %S"), &KFileMode());
		SetBlockResult(EFail);
		dataOk=EFalse;
		}

	if ( dataOk )
		{
		//	Creates and opens a new file for writing.
		if (rfsObject)
			{
			TInt	err = iFile->Create(*rfsObject, name, fileMode);
			if ( err!=KErrNone )
				{
				ERR_PRINTF2(_L("Create(), error create() = %d"), err);
				SetError(err);
				}
			}
		else
			{
			ERR_PRINTF1(_L("RFs object is NULL"));
			SetBlockResult(EFail);
			}
		}
	}

TBool CT_FileData::GetFileMode(const TDesC& aParameterName, const TDesC& aSection, TFileMode& aFileMode)
	{
	TPtrC	modeStr;
	TBool	ret=GET_MANDATORY_STRING_PARAMETER(aParameterName, aSection, modeStr);
	if ( ret )
		{
		if (modeStr == KEFileShareExclusive)
			{
			aFileMode = EFileShareExclusive;
			}
		else if (modeStr == KEFileShareReadersOnly)
			{
			aFileMode = EFileShareReadersOnly;
			}
		else if (modeStr == KEFileShareAny)
			{
			aFileMode = EFileShareAny;
			}
		else if (modeStr == KEFileShareReadersOrWriters)
			{
			aFileMode = EFileShareReadersOrWriters;
			}
		else if (modeStr == KEFileStream)
			{
			aFileMode = EFileStream;
			}
		else if (modeStr == KEFileStreamText)
			{
			aFileMode = EFileStreamText;
			}
		else if (modeStr == KEFileRead)
			{
			aFileMode = EFileRead;
			}
		else if (modeStr == KEFileWrite)
			{
			aFileMode = EFileWrite;
			}
		else if (modeStr == KEFileReadAsyncAll)
			{
			aFileMode = EFileReadAsyncAll;
			}
		else
			{
			ret = EFalse;
			}
		}
	return ret;
	}
