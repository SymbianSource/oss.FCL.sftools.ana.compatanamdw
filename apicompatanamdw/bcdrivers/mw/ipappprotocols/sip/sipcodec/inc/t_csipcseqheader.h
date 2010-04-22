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
 * This contains CT_DataSIPCSeqHeader
 */


#ifndef T_CSIPCSEQHEADER_H_
#define T_CSIPCSEQHEADER_H_

#include "t_csipheaderbase.h"
#include <sipcseqheader.h>

class CT_DataSIPCSeqHeader : public CT_DataSIPHeaderBase
    {
public: 
    static CT_DataSIPCSeqHeader* NewL();
    ~CT_DataSIPCSeqHeader();
    
    virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual TAny*   GetObject();
    virtual void    SetObjectL(TAny* aAny);
    virtual void    DisownObjectL();
    void            SetIsOwner(TBool aOwner);

protected:
    CT_DataSIPCSeqHeader();
    void ConstructL();
    virtual CSIPHeaderBase* GetSIPHeaderBase()const;
    void DoCmdNewL(const TTEFSectionName& aSection);
    void DoCmdNewLC(const TTEFSectionName& aSection);
    void DoCmdDecodeL(const TTEFSectionName& aSection);
    void DoCmdSeq(const TTEFSectionName& aSection);
    void DoCmdSetSeq(const TTEFSectionName& aSection);
    void DoCmdMethod(const TTEFSectionName& aSection);
    void DoCmdSetMethodL(const TTEFSectionName& aSection);
    void DoCmdInternalizeValueL(const TTEFSectionName& aSection);
    void DoCmdDestructor(const TTEFSectionName& aSection);
    void DestroyData();
    
private:
    CSIPCSeqHeader* iSIPCSeqHeader;
    TBool           iIsOwner;
    
    };
#endif /* T_CSIPCSEQHEADER_H_ */
