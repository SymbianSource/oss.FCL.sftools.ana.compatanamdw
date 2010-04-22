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


#ifndef __T_CSIPPARAMETERHEADERBASE_H_
#define __T_CSIPPARAMETERHEADERBASE_H_

#include "t_csipheaderbase.h"
#include <testexecutestepbase.h>
#include <sipparameterheaderbase.h> 

class CT_DataSIPParameterHeaderBase : public  CT_DataSIPHeaderBase
    {
public:
    
    virtual TBool   DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    
protected:
    CT_DataSIPParameterHeaderBase();
    
    virtual CSIPHeaderBase* GetSIPHeaderBase() const = 0;
    
    void DoCmdHasParam(const TTEFSectionName& aSection);
    void DoCmdParamValue(const TTEFSectionName& aSection);
    void DoCmdSetParamL(const TTEFSectionName& aSection);
    void DoCmdDeleteParam(const TTEFSectionName& aSection);
    void DoCmdParamCount(const TTEFSectionName& aSection);
    void DoCmdParam(const TTEFSectionName& aSection);
    
    };

#endif /* __T_CSIPPARAMETERHEADERBASE_H_ */
