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


#ifndef T_CSIPREFRESH_H_
#define T_CSIPREFRESH_H_

#include <testexecutestepbase.h>
#include "DataWrapperBase.h"

class CSIPRefresh;

class CT_DataSIPRefresh: public CDataWrapperBase
    {
public:
    static CT_DataSIPRefresh* NewL();
    ~CT_DataSIPRefresh();
    virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual TAny* GetObject();
    virtual void SetObjectL(TAny* aAny);
    virtual void DisownObjectL();
    
    void SetIsOwner(TBool aIsOwner);
    
protected:
    CT_DataSIPRefresh();
    void ConstructL();
    
private:
    // Wrapper functions.
    void DoCmdIntervalL(const TTEFSectionName& aSection);
    void DoCmdIsStandAlone(const TTEFSectionName& aSection);
    void DoCmdNewL(const TTEFSectionName& aSection);
    void DoCmdNewLC(const TTEFSectionName& aSection);
    void DoCmdSIPTransactionL(const TTEFSectionName& aSection);
    void DoCmdSetIntervalL(const TTEFSectionName& aSection);
    void DoCmdState(const TTEFSectionName& aSection);
    void DoCmdTerminateL(const TTEFSectionName& aSection);
    void DoCmdUpdateL(const TTEFSectionName& aSection);
    void DoCmdOperatorEqualL(const TTEFSectionName& aSection);
    void DoCmdDestructor(const TTEFSectionName& aSection); 
    
private:
    void DestroyData();
   
private:
    // Wrapped class.
    CSIPRefresh* iRefresh;
    TBool iIsOwner;
    };

#endif /* T_CSIPREFRESH_H_ */
