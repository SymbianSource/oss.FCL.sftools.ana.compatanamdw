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



/*
 * t_csipalloweventsheader.h
 */

#ifndef T_CSIPALLOWEVENTSHEADER_H_
#define T_CSIPALLOWEVENTSHEADER_H_

#include <testexecutestepbase.h>
#include <sipalloweventsheader.h> 
#include "t_csipheaderbase.h"

class CT_DataSIPAllowEventsHeader : public CT_DataSIPHeaderBase
{
public:
    static CT_DataSIPAllowEventsHeader* NewL();
    ~CT_DataSIPAllowEventsHeader();
    virtual TBool  DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual TAny*  GetObject();
    virtual void   SetObjectL(TAny* aAny);
    virtual void   DisownObjectL();
    virtual CSIPHeaderBase* GetSIPHeaderBase() const;
    virtual void   SetIsOwner(TBool aOwner);
    
protected:
    CT_DataSIPAllowEventsHeader();
    void ConstructL();
    
private:
    void DoCmdDestructor();
    void DoCmdDecodeL(const TTEFSectionName& aSection);
    void DoCmdNewL(const TTEFSectionName& aSection);
    void DoCmdNewLC(const TTEFSectionName& aSection);
    void DoCmdEventPackage(const TTEFSectionName& aSection);
    void DoCmdSetEventPackageL(const TTEFSectionName& aSection);
    void DoCmdEventTemplates(const TTEFSectionName& aSection);
    void DoCmdSetEventTemplatesL(const TTEFSectionName& aSection);
    void DoCmdInternalizeValueL(const TTEFSectionName& aSection);
    
private:
    void  DestroyData();
    
private:
    CSIPAllowEventsHeader*           iAllowEventsHeader ;
    TBool                            iIsOwner;
};


#endif /* T_CSIPALLOWEVENTSHEADER_H_ */
