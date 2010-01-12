/*
* Copyright (c) 1995-2001 Nokia Corporation and/or its subsidiary(-ies). 
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
	@file
	@internalTechnology
*/

#ifndef __E32NOTIF_H__
#define __E32NOTIF_H__
#include <e32std.h>

#define __NOTIFIER_NAME _L("!Notifier")
enum TNotifierMessage 
	{
	ENotifierNotify,
	ENotifierInfoPrint,
	EStartNotifier,
	ECancelNotifier,
	EUpdateNotifier,
	EStartNotifierAndGetResponse,
	EStartNotifierFromSpecifiedDll,
	EStartNotifierFromSpecifiedDllAndGetResponse,
	ENotifierNotifyCancel,
	EUpdateNotifierAndGetResponse,
	};

#endif
