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


#ifndef T_CSIPREQUIREHEADER_H_
#define T_CSIPREQUIREHEADER_H_
#include "t_csiptokenheaderbase.h"

#include <siprequireheader.h> 
class CT_DataSIPRequireHeader : public CT_DataSIPTokenHeaderBase
    {
public:
    virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    ~CT_DataSIPRequireHeader();
    static CT_DataSIPRequireHeader* NewL();
    virtual TAny*   GetObject();
    virtual void    SetObjectL(TAny* aAny);
    virtual void    DisownObjectL();
    virtual CSIPHeaderBase* GetSIPHeaderBase() const;
    virtual CSIPTokenHeaderBase* GetSIPTokenHeaderBase()const;
    virtual void   SetIsOwner(TBool aOwner);
    
protected:
    CT_DataSIPRequireHeader();
    void ConstructL();
    void DoCmdDecodeL(const TTEFSectionName& aSection);
    void DoCmdInternalizeValueL(const TTEFSectionName& aSection);
    void DoCmdNewL(const TTEFSectionName& aSection);
    void DoCmdNewLC(const TTEFSectionName& aSection);
    void DoCmdDestructor(const TTEFSectionName& aSection);
    void DestroyData();
    
private:
    CSIPRequireHeader* iSIPRequireHeader;
    TBool         iIsOwner;
    };

#endif /* T_CSIPREQUIREHEADER_H_ */
