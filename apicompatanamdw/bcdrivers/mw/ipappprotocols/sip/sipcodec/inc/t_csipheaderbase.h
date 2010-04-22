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


// This contains CT_DataSIPHeaderBase
#ifndef T_CSIPHEADERBASE_H_
#define T_CSIPHEADERBASE_H_
#include <testexecutestepbase.h>
#include "DataWrapperBase.h"
#include <sipheaderbase.h> 

class CT_DataSIPHeaderBase : public CDataWrapperBase
{
public:

    virtual TBool  DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual CSIPHeaderBase* GetSIPHeaderBase()const = 0;
    virtual void            SetIsOwner(TBool aOwner) = 0;

protected:
    CT_DataSIPHeaderBase();    
    
private:
    virtual void DoCmdCloneL(const TTEFSectionName& aSection);
    virtual void DoCmdName(const TTEFSectionName& aSection);
    virtual void DoCmdToTextValueL(const TTEFSectionName& aSection);
    void DoCmdToTextL(const TTEFSectionName& aSection);
    void DoCmdToTextLC(const TTEFSectionName& aSection);
    void DoCmdToTextValueLC(const TTEFSectionName& aSection);
    void DoCmdExternalizeL(const TTEFSectionName& aSection);
    void DoCmdExternalizeSupported(const TTEFSectionName& aSection);
    void DoCmdPushLC(const TTEFSectionName& aSection);
};
#endif /*T_CSIPHeaderBase_H_*/
