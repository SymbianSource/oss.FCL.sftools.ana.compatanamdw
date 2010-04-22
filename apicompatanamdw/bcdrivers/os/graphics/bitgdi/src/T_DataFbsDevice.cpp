/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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

This contains CT_DataFbsDevice
*/

#include "T_DataFbsDevice.h"

/*@{*/
//Parameters
/*@}*/

/**
* Constructor. First phase construction
*/
CT_DataFbsDevice::CT_DataFbsDevice()
:	CT_DataBitmapDevice()
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
TBool CT_DataFbsDevice::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
	{
	/* Another work package will implement this */
	return CT_DataBitmapDevice::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
	}
