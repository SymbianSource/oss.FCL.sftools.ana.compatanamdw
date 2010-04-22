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
 * This contains CT_DataSIPStrings
 */


#ifndef __T_DATASIPSTRINGS_H__
#define __T_DATASIPSTRINGS_H__

#include "DataWrapperBase.h"

class CT_DataSIPStrings : public CDataWrapperBase 
    {
public:
	virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    ~CT_DataSIPStrings();
    static CT_DataSIPStrings* NewL();
    virtual TAny*   GetObject();
    
protected:
    void ConstructL();
	CT_DataSIPStrings();
	void DoCmdOpenL(const TTEFSectionName& aSection);
	void DoCmdClose(const TTEFSectionName& aSection);
	void DoCmdPool(const TTEFSectionName& aSection);
	void DoCmdStringF(const TTEFSectionName& aSection);
	void DoCmdTable(const TTEFSectionName& aSection);
    };

#endif /*__T_DATASIPSTRINGS_H__*/

