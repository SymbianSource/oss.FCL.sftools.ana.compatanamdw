/*
* Copyright (c) 2007-2008 Nokia Corporation and/or its subsidiary(-ies).
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

#if (!defined __T_FILE_DATA_H__)
#define __T_FILE_DATA_H__

//	User Includes
#include "DataWrapperBase.h"
#include "T_FsData.h"

//	EPOC includes
#include <f32file.h>
#include <datadictionary.h>

class CT_FileData: public CDataWrapperBase
	{
public:
	static CT_FileData*	NewL();
	~CT_FileData();

	virtual TBool	DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
	virtual TAny*	GetObject();

protected:
	CT_FileData();
	void ConstructL();

private:
	//	Commands
	void	DoCmdNewL();
	void	DoCmdDestructor();
	void	DoCmdCreateL(const TDesC& aSection);
	void	DoCmdOpenL(const TDesC& aSection);
	void	DoCmdWriteL(const TDesC& aSection);
	void	DoCmdClose();

	//	Helpers
	inline void	DoCleanup();
	TBool 		GetFileMode(const TDesC& aParameterName, const TDesC& aSection, TFileMode& aFileMode);

private:
	/** Instance for handling to resource file */
	RFile*		iFile;
	};

#endif /* __T_FILE_DATA_H__ */
