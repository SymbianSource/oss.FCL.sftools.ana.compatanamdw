/*
* Copyright (c) 1997-2006 Nokia Corporation and/or its subsidiary(-ies). 
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
@publishedPartner
@released
*/
#define __EIKON_SERVER _L("Eikon server")

/**
@internalComponent
*/
enum TEikServPanic
	{
	EEikServPanicNotifyBadDescriptor,
	EEikServPanicAlarmAlertServiceNotSupported,
	EEikServPanicNoTaskListDialog,
	EEikServPanicTaskNull,
	EEsPanicAlarmAlert,
	EEikServPanicAlarmAlertServerAlreadyConnected,
	EEikServEnvPanicNullAppUi,
	EEikServPanicNoSuchLabelInAlarm,
	EEikServPanicDriveIndexOutOfRange,
	EEikServPanicNotiferArrayNotNull,
	EEikServPanicChannelIndexOutOfRange,
	EEikServPanicNullObservedList,
	EEikServPanicQueueIndexOutOfRange,
	//EEikServPanicNotifyAlertQueueEmpty,
	EEikSrvClientPanicInconsistentMessageParameters,
	};

/**
@internalComponent
*/
void Panic(TEikServPanic aPanic);

