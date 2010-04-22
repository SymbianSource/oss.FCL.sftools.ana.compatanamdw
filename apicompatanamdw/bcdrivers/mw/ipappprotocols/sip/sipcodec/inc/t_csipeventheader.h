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


#ifndef T_CSIPEVENTHEADER_H_
#define T_CSIPEVENTHEADER_H_
#include "t_csipparameterheaderbase.h"

#include <sipeventheader.h> 
class CT_DataSIPEventHeader : public CT_DataSIPParameterHeaderBase
    {
public:
    virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    ~CT_DataSIPEventHeader();
    static CT_DataSIPEventHeader* NewL();
    virtual TAny*   GetObject();
    virtual void    SetObjectL(TAny* aAny);
    virtual void    DisownObjectL();
    virtual CSIPHeaderBase* GetSIPHeaderBase() const;
    virtual void   SetIsOwner(TBool aOwner);
    
protected:
    CT_DataSIPEventHeader();
    void ConstructL();
    void DoCmdNewL(const TTEFSectionName& aSection);
    void DoCmdNewLC(const TTEFSectionName& aSection);
    void DoCmdEventPackage(const TTEFSectionName& aSection);
    void DoCmdEventTemplates(const TTEFSectionName& aSection);
    void DoCmdSetEventPackageL(const TTEFSectionName& aSection);
    void DoCmdSetEventTemplatesL(const TTEFSectionName& aSection);
    void DoCmdCompare(const TTEFSectionName& aSection);
    void DoCmdDecodeL(const TTEFSectionName& aSection);
    void DoCmdInternalizeValueL(const TTEFSectionName& aSection);
    void DoCmdDestructor(const TTEFSectionName& aSection);
    void DestroyData();
    
private:
    CSIPEventHeader* iSIPEventHeader;
    TBool         iIsOwner;
    };

#endif /* T_CSIPEVENTHEADER_H_ */
