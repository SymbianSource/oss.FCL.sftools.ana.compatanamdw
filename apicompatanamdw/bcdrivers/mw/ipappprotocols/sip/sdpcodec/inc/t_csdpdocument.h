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


#ifndef __T_DATASDPDOCUEMNT_H_
#define __T_DATASDPDOCUEMNT_H_

#include "t_csipprofileregistrybase.h"
#include <testexecutestepbase.h>
#include <sdpdocument.h>

class CT_DataSdpDocument : public CDataWrapperBase
    {
public:
    static CT_DataSdpDocument* NewL();
    ~CT_DataSdpDocument();
    
    virtual TBool   DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual TAny*   GetObject();
    virtual void    SetObjectL(TAny* aAny);
    virtual void    DisownObjectL();
    
protected:
    CT_DataSdpDocument();
    void ConstructL();
    
private:
    void DoCmdNewL(const TTEFSectionName& aSection);
    void DoCmdSetOrginFieldL(const TTEFSectionName& aSection);
    void DoCmdSetSessionNameL(const TTEFSectionName& aSection);
    void DoCmdSetConnectionFieldL(const TTEFSectionName& aSection);
    void DoCmdMediaFields_AppendL(const TTEFSectionName& aSection);
    void DoCmdEncodeL(const TTEFSectionName& aSection);    
    void DoCmdDestructor(const TTEFSectionName& aSection);
    void DestroyData();
    
private:
    CSdpDocument* iSdpDocument;
    };

#endif /*__T_DATASDPDOCUEMNT_H_*/
