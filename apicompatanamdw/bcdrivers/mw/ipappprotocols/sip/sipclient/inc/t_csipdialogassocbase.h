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
 * This contains CT_DataSIPDialogAssocBase
 */


#ifndef T_CSIPDIALOGASSOCBASE_H_
#define T_CSIPDIALOGASSOCBASE_H_

//  User includes
#include "DataWrapperBase.h"
#include <testexecutestepbase.h>

// Epoc includes
#include <sipdialogassocbase.h> 

class CT_DataSIPDialogAssocBase : public CDataWrapperBase
    {   
public:
    virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual void  SetIsOwner(TBool aOwner) = 0;
    CT_DataSIPDialogAssocBase();
    
protected:
    virtual CSIPDialogAssocBase* GetSIPDialogAssocBase() const = 0;  

private:
    void DoCmdDialog(const TTEFSectionName& aSection);
    void DoCmdSendNonTargetRefreshRequestL(const TTEFSectionName& aSection);  
    void DoCmdType(const TTEFSectionName& aSection);  
    void DoCmdIsNonTargetRefreshRequest(const TTEFSectionName& aSection);
    };

#endif /* T_CSIPDIALOGASSOCBASE_H_ */
