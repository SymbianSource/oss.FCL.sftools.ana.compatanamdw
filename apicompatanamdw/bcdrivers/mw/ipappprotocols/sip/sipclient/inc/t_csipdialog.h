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


// This contains CT_DataSIPDialog
#ifndef T_CSIPDIALOG_H_
#define T_CSIPDIALOG_H_
#include <testexecutestepbase.h>
#include <sipdialog.h> 
#include "DataWrapperBase.h"

class CSIPDialog;
class CT_DataSIPDialog : public CDataWrapperBase
{
public:
    static CT_DataSIPDialog* NewL();
    ~CT_DataSIPDialog();
    
    virtual TAny*   GetObject();
    virtual void    SetObjectL(TAny* aAny);
    virtual void    DisownObjectL();    
	virtual TBool  DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);

	void           DestroyData();
	
	virtual void   SetIsOwner(TBool aOwner);

private:
    CT_DataSIPDialog();
    void ConstructL();
    
public:	
	void DoCmdCallIdL(const TTEFSectionName& aSection);
    void DoCmdConnection(const TTEFSectionName& aSection);
    void DoCmdFromHeader(const TTEFSectionName& aSection);
    void DoCmdIsAssociated(const TTEFSectionName& aSection);
    void DoCmdRegistrationContext(const TTEFSectionName& aSection);
    void DoCmdState(const TTEFSectionName& aSection);
    void DoCmdToHeader(const TTEFSectionName& aSection);
    void DoCmdOperatorEqualL(const TTEFSectionName& aSection);
    void DoCmdRemoteURI();
    void DoCmdSIPDialogAssociations(const TTEFSectionName& aSection);
    
private:
	CSIPDialog*		iSIPDialog ;
    TBool           iIsOwner;
};
#endif /*T_CSIPDialog_H_*/
