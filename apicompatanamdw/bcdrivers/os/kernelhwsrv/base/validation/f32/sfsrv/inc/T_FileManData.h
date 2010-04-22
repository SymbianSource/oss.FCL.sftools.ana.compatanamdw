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

#if (!defined __T_FILE_MAN_DATA_H__)
#define __T_FILE_MAN_DATA_H__

//	User Includes
#include "DataWrapperBase.h"
#include "T_FsData.h"

//	EPOC includes
#include <f32file.h>

class CT_FileManData: public CDataWrapperBase
	{
public:
	static CT_FileManData*	NewL();
	~CT_FileManData();

	virtual TBool	DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
	virtual TAny*	GetObject();

protected:
	CT_FileManData();
	void ConstructL();

private:
	//	Commands
	void	DoCmdNewL(const TDesC& aSection);
	void	DoCmdDestructor();
	void	DoCmdCopyL(const TDesC& aSection);

	//	Helpers
	void	DoCleanup();
	TBool	ReadFileManSwitch(const TDesC& aFormat, const TDesC& aEntry, TUint& aFileManSwitch);
	TBool	ConvertFileManSwitch(const TDesC& aSwitchString, CFileMan::TSwitch& aSwitchValue);

private:
	/** Instance for handling to resource file */
	CFileMan*	iFileMan;
	};

#endif /* __T_FILE_MAN_DATA_H__ */
