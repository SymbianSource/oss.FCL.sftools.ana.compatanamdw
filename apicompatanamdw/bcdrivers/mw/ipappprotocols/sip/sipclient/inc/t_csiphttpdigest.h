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


// This contains CT_DataSIPHttpDigest

#ifndef __T_DATASIPHTTPDIGEST_H__
#define __T_DATASIPHTTPDIGEST_H__

#include "DataWrapperBase.h"
#include <testexecutestepbase.h>
#include <siphttpdigest.h>
#include <siphttpdigestchallengeobserver.h>
#include <siphttpdigestchallengeobserver2.h>

class CT_DataSIPHttpDigest : public CDataWrapperBase, MSIPHttpDigestChallengeObserver, MSIPHttpDigestChallengeObserver2
	{
public:
    static CT_DataSIPHttpDigest* NewL();
    ~CT_DataSIPHttpDigest();
    
    virtual TBool   DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual TAny*   GetObject();
    virtual void    SetObjectL(TAny* aAny);
    virtual void    DisownObjectL();
    void            SetIsOwner(TBool aIsOwner);

public:
    // from MSIPHttpDigestChallengeObserver
    void ChallengeReceived(const TDesC8 &aRealm);
    
    // from MSIPHttpDigestChallengeObserver2
    void ChallengeReceived(const CSIPClientTransaction &aTransaction);
    void ChallengeReceived(const CSIPRefresh &aRefresh);
    
protected:
    CT_DataSIPHttpDigest();
    void ConstructL();    
    
private:
	void DoCmdNewL(const TTEFSectionName& aSection);
	void DoCmdNewLC(const TTEFSectionName& aSection);
    void DoCmdSetCredentialsL(const TTEFSectionName& aSection);
    void DoCmdRemoveCredentials(const TTEFSectionName& aSection);
    void DoCmdSetObserver(const TTEFSectionName& aSection);
    void DoCmdIgnoreChallengeL(const TTEFSectionName& aSection);    
	void DoCmdDestructor(const TTEFSectionName& aSection);
    void DestroyData();
    
    void DoCmdWaitForChallengeReceived(const TTEFSectionName& aSection);

private:
    CSIPHttpDigest* iSIPHttpDigest;
    TBool iIsOwner;
    TTEFSectionName iTEFSectionName;
	};

#endif /* __T_DATASIPHTTPDIGEST_H__ */

