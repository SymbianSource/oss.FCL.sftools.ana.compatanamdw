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


#ifndef __T_CSIPProfileRegistryBase__
#define __T_CSIPProfileRegistryBase__

#include "DataWrapperBase.h"
#include <testexecutestepbase.h>
#include <sipprofileregistrybase.h>
#include <sipprofileregistryobserver.h>

class CT_DataSIPProfileRegistryBase : public CDataWrapperBase, public MSIPProfileRegistryObserver
	{
public:
	virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);

public: // from MSIPProfileRegistryObserver
	virtual void ProfileRegistryEventOccurred(TUint32 aProfileId, TEvent aEvent);
	virtual void ProfileRegistryErrorOccurred(TUint32 aProfileId, TInt aError);
    
protected:
	CT_DataSIPProfileRegistryBase();
	
	virtual CSIPProfileRegistryBase* GetSIPProfileRegistryBase() const = 0;

	void    DoCmdDefaultProfileL(const TDesC& aSection);
	void    DoCmdLastRegistrationError(const TDesC& aSection);
	void    DoCmdProfileL(const TDesC& aSection);
	void    DoCmdProfilesL(const TDesC& aSection);
	void    DoCmdSupportedProfileTypesL(const TDesC& aSection);

private:
    void    LogTypeInfo(const TSIPProfileTypeInfo& info);

protected:
    TEvent iExpected;
    TBool iCheckEvent;
	};

#endif /* __T_CSIPProfileRegistryBase__ */
