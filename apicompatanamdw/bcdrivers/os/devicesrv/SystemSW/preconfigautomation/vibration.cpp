/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
// vibration.cpp
//
// Created: 09/17/08
// Author:  
// Copyright (c) . All rights reserved.
//

#include "CommonFramework.h"
#include <centralrepository.h>
#include <HWRMVibraSDKCRKeys.h>
#include <f32file.h> 

#include <mproengengine.h>
#include <mproengprofile.h>
#include <ProEngFactory.h>
#include <MProEngToneSettings.h>
// do the example
LOCAL_C void doExampleL()
    {
    
	_LIT(KVibraOnText,"Turned vibration settings to ON!\n");

/*
//	TUid KCRUidVibraCtrl;
//	KCRUidVibraCtrl.iUid = (0x10200C8B);
//	TUint32 KVibra(0x00000001);
	TInt val(1);
	TInt getVal(-1);
	CRepository* repository = CRepository::NewL(KCRUidVibraCtrl);
	//check the vibration status
	TInt ret = repository->Get(KVibraCtrlProfileVibraEnabled,getVal);
//	ret = repository->Set(KVibraCtrlProfileVibraEnabled,val);
	// if vibration is OFF turn it to ON
	if( 0 == getVal)
	{
		console->Printf(_L("before SET method"));		
		TInt ret = repository->Set(KVibraCtrlProfileVibraEnabled,val);
		console->Printf(_L("after SET method"));		
	}
	
	ret = repository->Get(KVibraCtrlProfileVibraEnabled,getVal);
	if( 1 == getVal )
	{
		console->Printf(KVibraOnText);	
	}
	delete repository;
	
*/	
	
	TFileName path( _L("c:\\logs\\TestFramework\\SystemSW\\vibration_Preconfig.txt"));
	RFile file;
	RFs fileSession;
	TInt err = fileSession.Connect(); 
	
	fileSession.MkDirAll(_L("c:\\logs\\TestFramework\\SystemSW\\"));
	err = file.Replace(fileSession, path, EFileStreamText | EFileWrite);
	
	
	file.Write(_L8("PreConfig file of vibration ON application\n"));
	
	
	TBool vibraSettings(1);
	CActiveScheduler *vibraScheduler = new(ELeave) CActiveScheduler();
	CleanupStack::PushL(vibraScheduler );
	CActiveScheduler::Install(vibraScheduler );
	
	MProEngEngine* profileEngine = ProEngFactory::NewEngineL();
	CleanupReleasePushL( *profileEngine );

	MProEngProfile* profile = profileEngine->ActiveProfileL();
	CleanupReleasePushL( *profile );

	MProEngToneSettings& sett = profile->ToneSettings();

	TInt ret = sett.SetVibratingAlert( vibraSettings );

	TRAPD(res,profile->CommitChangeL());

	TBool retval = sett.VibratingAlert();
	if (KErrNone == ret && retval )
	    {
        file.Write(_L8("preconfig result : passed\n"));
	    }
	else
	    {
	    file.Write(_L8("preconfig result : failed\n"));
	    }
	CleanupStack::PopAndDestroy( profile );
	CleanupStack::PopAndDestroy( profileEngine );
	CleanupStack::PopAndDestroy(vibraScheduler );
	file.Close();
	fileSession.Close();

	}
