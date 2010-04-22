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


// This contains CT_DataSIPTokenHeaderBase
#ifndef T_CSIPTOKENHEADERBASE_H_
#define T_CSIPTOKENHEADERBASE_H_
#include <testexecutestepbase.h>
#include "t_csipheaderbase.h"
#include <siptokenheaderbase.h> 

class CT_DataSIPTokenHeaderBase : public CT_DataSIPHeaderBase
{
public:

    virtual TBool  DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual CSIPHeaderBase* GetSIPHeaderBase()const = 0;
    virtual CSIPTokenHeaderBase* GetSIPTokenHeaderBase()const = 0;

protected:
    CT_DataSIPTokenHeaderBase();    
    
private:
    void DoCmdSetValueL(const TTEFSectionName& aSection);
    void DoCmdValue(const TTEFSectionName& aSection);
};
#endif /*T_CSIPTOKENHEADERBASE_H_*/
