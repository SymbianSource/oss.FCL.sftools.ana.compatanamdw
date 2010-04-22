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


#ifndef T_CSIPSECURITYHEADERBASE_H_
#define T_CSIPSECURITYHEADERBASE_H_
#include "t_csipparameterheaderbase.h"

#include <sipsecurityheaderbase.h> 
class CT_DataSIPSecurityHeaderBase : public CT_DataSIPParameterHeaderBase
    {
public:
    virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual CSIPHeaderBase* GetSIPHeaderBase() const = 0;
    
protected:
    CT_DataSIPSecurityHeaderBase();
    void DoCmdMechanismName(const TTEFSectionName& aSection);
    void DoCmdPreferenceParam(const TTEFSectionName& aSection);
    void DoCmdSetMechanismNameL(const TTEFSectionName& aSection);
    void DoCmdSetPreferenceParamL(const TTEFSectionName& aSection);
    void DoCmdDestructor(const TTEFSectionName& aSection);
    };

#endif /* T_CSIPSECURITYHEADERBASE_H_ */
