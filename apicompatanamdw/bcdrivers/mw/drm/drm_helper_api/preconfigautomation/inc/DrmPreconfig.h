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

#ifndef __DRMUTILITIES_H__
#define __DRMUTILITIES_H__


 void ProcessMessageL(const TDesC& aFile, const TDesC& aOutput);
 void ProcessRightsL(const TDesC& aFile);
 void EncryptFileL(const TDesC& aFile, TDesC& aOutput, TInt aMultiplier);
 LOCAL_C void UpdateDCFRepositoryL( const TDesC& aFileName);
 LOCAL_C void ReadFileL(HBufC8*& aContent, const TDesC& aName, RFs& aFs);

 //Functions to be called
 TUint EncryptL(TUint& aEncryptedCount, TUint& aRightsCount, TUint& aMessagesProcessed);
 TUint SetDrmClockL(RFile &aDRMLogFile);


#endif /* __DRMUTILITIES_H__ */