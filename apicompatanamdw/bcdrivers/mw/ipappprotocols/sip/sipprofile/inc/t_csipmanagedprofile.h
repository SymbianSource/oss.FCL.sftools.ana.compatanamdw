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


// This contains CT_DataSIPManagedProfile
#ifndef T_CSIPMANAGEDPROFILE_H_
#define T_CSIPMANAGEDPROFILE_H_
#include <testexecutestepbase.h>
#include "t_csipprofile.h"
class CSIPManagedProfile;
class CT_DataSIPManagedProfile : public CT_DataSIPProfile
{
public:
	static CT_DataSIPManagedProfile* NewL();
	~CT_DataSIPManagedProfile();
	virtual TBool  DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
	virtual TAny*  GetObject();
	virtual void   SetObjectL(TAny* aAny);
	virtual void   DisownObjectL();
	virtual CSIPProfile* GetSIPProfileObject(); 
	
protected:
	CT_DataSIPManagedProfile();
	void ConstructL();
	
private:
	void DoCmdSetType(const TTEFSectionName& aSection);
	void DoCmdCloneL(const TTEFSectionName& aSection);
    void DoCmdSetParameterL(const TTEFSectionName& aSection);    
    void DoCmdDestructor();
    
private:
    void  DestroyData();

    TInt AddAccessPointL(const TDesC& aAccessPoint);
    
private:
    // Helper
    struct TStringToIntegerMap
        {
        TPtrC   iName;
        TUint32 iVal;
        };
    
private:
	CSIPManagedProfile*					iSIPManagedProfile ;
	TUint32                             iapID;
};
#endif /*T_CSIPMANAGEDPROFILE_H_*/
