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


#ifndef T_CSIPADDRESSHEADERBASE_H_
#define T_CSIPADDRESSHEADERBASE_H_

#include "DataWrapperBase.h"
#include "t_csipparameterheaderbase.h"
#include <testexecutestepbase.h>
#include <sipaddressheaderbase.h> 


class CT_DataSIPAddress;

class CT_DataSIPAddressHeaderBase : public CT_DataSIPParameterHeaderBase
    {
public:
    virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    
protected:
    CT_DataSIPAddressHeaderBase();
    virtual CSIPHeaderBase* GetSIPHeaderBase() const = 0;
    
    void DoCmdSetSIPAddressL(const TTEFSectionName& aSection);
    void DoCmdSIPAddress(const TTEFSectionName& aSection);
    void DoCmdDestructor(const TTEFSectionName& aSection);
    void DestroyData();
    };


#endif /* T_CSIPADDRESSHEADERBASE_H_ */
