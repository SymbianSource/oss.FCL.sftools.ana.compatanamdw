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


// This contains CT_SIPClientBlock

#ifndef __T_SIPCLIENT_BLOCK_H__
#define __T_SIPCLIENT_BLOCK_H__

//	User Includes
#include <testblockcontroller.h>


class CT_SIPClientBlock : public CTestBlockController
	{
public:
	CT_SIPClientBlock() : CTestBlockController() {}
	~CT_SIPClientBlock() {}

	CDataWrapper* CreateDataL( const TDesC& aData );
	};

#endif /* __T_SIPCLIENT_BLOCK_H__ */
