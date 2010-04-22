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


// This contains CT_DataSIPCallIDHeader
#ifndef __T_DATASIPCALLIDHEADER_H__
#define __T_DATASIPCALLIDHEADER_H__

#include "t_csipheaderbase.h"
#include <sipcallidheader.h> 

class CT_DataSIPCallIDHeader : public CT_DataSIPHeaderBase
    {
public:
    static CT_DataSIPCallIDHeader* NewL();
    ~CT_DataSIPCallIDHeader();
    
    virtual TBool  DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual TAny*  GetObject();
    virtual void   SetObjectL(TAny* aAny);
    virtual void   DisownObjectL();

    virtual void   SetIsOwner(TBool aOwner);

protected:
    CT_DataSIPCallIDHeader();
    void ConstructL();
    virtual CSIPHeaderBase* GetSIPHeaderBase() const;
    
private:
    void DoCmdDestructor();
    void DoCmdDecodeL(const TTEFSectionName& aSection);
    void DoCmdInternalizeValueL(const TTEFSectionName& aSection);
    void DoCmdCompareL(const TTEFSectionName& aSection);
    
private:
    void  DestroyData();
    
private:
    CSIPCallIDHeader* iSIPCallIDHeader ;
    TBool iIsOwner;
    };
#endif /*__T_DATASIPCALLIDHEADER_H__*/
