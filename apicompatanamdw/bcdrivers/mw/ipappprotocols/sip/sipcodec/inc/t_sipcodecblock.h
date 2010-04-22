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


// This contains CT_SIPCodecBlock

#ifndef __T_SIPCODEC_BLOCK_H__
#define __T_SIPCODEC_BLOCK_H__

//	User Includes
#include <testblockcontroller.h>


class CT_SIPCodecBlock : public CTestBlockController
	{
public:
	CT_SIPCodecBlock() : CTestBlockController() {}
	~CT_SIPCodecBlock() {}

	CDataWrapper* CreateDataL( const TDesC& aData );
	};

#endif /* __T_SIPCODEC_BLOCK_H__ */
