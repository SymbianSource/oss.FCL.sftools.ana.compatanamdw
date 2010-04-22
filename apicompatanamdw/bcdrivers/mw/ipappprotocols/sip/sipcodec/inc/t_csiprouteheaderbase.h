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


#ifndef __T_DATASIPROUTEHEADERBASE_H_
#define __T_DATASIPROUTEHEADERBASE_H_

#include "t_csipparameterheaderbase.h" 

class CT_DataSIPRouteHeaderBase : public CT_DataSIPParameterHeaderBase
    {
public:    
    virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    
protected:
    CT_DataSIPRouteHeaderBase();
    
    virtual CSIPHeaderBase* GetSIPHeaderBase() const = 0;

    void DoCmdSetSIPAddressL(const TTEFSectionName& aSection);
    void DoCmdSIPAddressL(const TTEFSectionName& aSection);
    };

#endif /* __T_DATASIPROUTEHEADERBASE_H_ */
