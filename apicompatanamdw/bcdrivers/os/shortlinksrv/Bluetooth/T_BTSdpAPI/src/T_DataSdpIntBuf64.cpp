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

#include "T_DataSdpIntBuf64.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CT_DataSdpIntBuf64* CT_DataSdpIntBuf64::NewL()
	{
	CT_DataSdpIntBuf64*	ret=new (ELeave) CT_DataSdpIntBuf64();
	CleanupStack::PushL(ret);
	ret->ConstructL();
	CleanupStack::Pop(ret);
	return ret;
	}

CT_DataSdpIntBuf64::CT_DataSdpIntBuf64()
:	iSdpIntBuf64(NULL)
	{
	}

void CT_DataSdpIntBuf64::ConstructL()
	{
	}

CT_DataSdpIntBuf64::~CT_DataSdpIntBuf64()
	{
	DestroyData();
	}


void CT_DataSdpIntBuf64::DestroyData()
	{
	delete iSdpIntBuf64;
	iSdpIntBuf64=NULL;
	}
	
void CT_DataSdpIntBuf64::SetObjectL(TAny* aAny)
	{
	DestroyData();
	iSdpIntBuf64 = static_cast<TSdpIntBuf<TUint64>*> (aAny);
	}

void CT_DataSdpIntBuf64::DisownObjectL()
	{
	iSdpIntBuf64 = NULL;
	}
	
inline TCleanupOperation CT_DataSdpIntBuf64::CleanupOperation()
	{
	return CleanupOperation;
	}

void CT_DataSdpIntBuf64::CleanupOperation(TAny* aAny)
	{
	TSdpIntBuf<TUint64>* arg=static_cast<TSdpIntBuf<TUint64>*>(aAny);
	delete arg;
	}

/**
 * Process a command read from the ini file
 *
 * @param aCommand			The command to process
 * @param aSection			The section in the ini containing data for the command
 * @param aAsyncErrorIndex	Command index for async calls to return errors to
 *
 * @return					ETrue if the command is processed
 *
 * @leave					System wide error
 */
TBool CT_DataSdpIntBuf64::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
	{
	return EFalse;
	}
