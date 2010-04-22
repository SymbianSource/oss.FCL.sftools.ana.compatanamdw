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


// This contains CT_DataSIPUnsignedIntHeaderBase
#ifndef T_CSIPUNSIGNEDINTHEADERBASE_H_
#define T_CSIPUNSIGNEDINTHEADERBASE_H_
#include <testexecutestepbase.h>
#include "t_csipheaderbase.h"
#include <sipunsignedintheaderbase.h> 

class CT_DataSIPUnsignedIntHeaderBase : public CT_DataSIPHeaderBase
{
public:

    virtual TBool  DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual CSIPHeaderBase* GetSIPHeaderBase()const = 0;
    virtual CSIPUnsignedIntHeaderBase* GetSIPUnsignedIntHeaderBase()const = 0;

protected:
    CT_DataSIPUnsignedIntHeaderBase();    
    
private:
    void DoCmdSetValue(const TTEFSectionName& aSection);
    void DoCmdValue(const TTEFSectionName& aSection);
};
#endif /*T_CSIPUNSIGNEDINTHEADERBASE_H_*/
