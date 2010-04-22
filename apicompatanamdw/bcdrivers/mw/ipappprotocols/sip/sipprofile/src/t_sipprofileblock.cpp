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


// This contains CT_SIPProfileBlock

#include "t_sipprofileblock.h"
#include "t_csip.h"
#include "t_csipconnection.h"
#include "t_csipmanagedprofile.h"
#include "t_csipmanagedprofileregistry.h"
#include "t_csipprofileregistry.h"

_LIT(KDataSIP,"CSIP");
_LIT(KDataSIPConnection,"CSIPConnection");
_LIT(KDataSIPManagedProfile,"CSIPManagedProfile");
_LIT(KDataSIPManagedProfileRegistry,"CSIPManagedProfileRegistry");
_LIT(KDataSIPProfile,"CSIPProfile");
_LIT(KDataSIPProfileRegistry,"CSIPProfileRegistry");

CDataWrapper* CT_SIPProfileBlock::CreateDataL( const TDesC& aData )
	{
	CDataWrapper* wrapper = NULL;
	if( KDataSIP() == aData )
		{
		wrapper = CT_DataSIP::NewL();
		}
	else if( KDataSIPConnection() == aData )
		{
		wrapper = CT_DataSIPConnection::NewL();
		}
	else if( KDataSIPManagedProfile() == aData )
		{
		wrapper = CT_DataSIPManagedProfile::NewL();
		}
	else if( KDataSIPManagedProfileRegistry() == aData )
		{
		wrapper = CT_DataSIPManagedProfileRegistry::NewL();
		}
	else if( KDataSIPProfile() == aData )
		{
		wrapper = CT_DataSIPProfile::NewL();
		}
	else if( KDataSIPProfileRegistry() == aData )
		{
		wrapper = CT_DataSIPProfileRegistry::NewL();
		}
	else 
		 ; 
	return wrapper;
	}




