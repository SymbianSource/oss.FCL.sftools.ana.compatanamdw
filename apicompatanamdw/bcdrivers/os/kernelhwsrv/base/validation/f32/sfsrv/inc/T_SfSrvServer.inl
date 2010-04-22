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

This contains CT_SfSrvServer inline functions
*/

CT_SfSrvServer::CT_SfSrvBlock::CT_SfSrvBlock()
:	CTestBlockController()
	{
	}

CT_SfSrvServer::CT_SfSrvBlock::~CT_SfSrvBlock()
	{
	}

CDataWrapper* CT_SfSrvServer::CT_SfSrvBlock::CreateDataL(const TDesC& aData)
	{
	CDataWrapper*	wrapper = NULL;
	if( KRFs() == aData )
		{
		wrapper = CT_FsData::NewL();
		}
	else if( KRFile() == aData )
		{
		wrapper = CT_FileData::NewL();
		}
	else if( KRFormat() == aData )
		{
		wrapper = CT_FormatData::NewL();
		}
    else if( KCFileMan() == aData )
		{
		wrapper = CT_FileManData::NewL();
		}    
	return wrapper;
	}

CT_SfSrvServer::CT_SfSrvServer()
	{
	}

CT_SfSrvServer::~CT_SfSrvServer()
	{
	}

CTestBlockController* CT_SfSrvServer::CreateTestBlock()
	{
	return new CT_SfSrvBlock();
	}
