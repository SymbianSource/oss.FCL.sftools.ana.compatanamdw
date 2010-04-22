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


// This contains CT_DataSIPProfile

#ifndef __T_SIPPROFILE__
#define __T_SIPPROFILE__

//	User includes
#include "DataWrapperBase.h"
#include <testexecutestepbase.h>

// Epoc includes
#include <sipprofile.h> 

class CT_DataSIPProfile : public CDataWrapperBase
	{
public:
	/**
	* Two phase constructor
	*/
	static CT_DataSIPProfile*	NewL();

	/**
	* Public destructor
	*/
	~CT_DataSIPProfile();

	/**
	* Process a command read from the ini file
	*
	* \param aTestStep	test step requiring command to be processed
	* \param aCommand	the command to process
	* \param aSection	the entry in the ini file requiring the command to be processed
	*
	* \return ETrue if the command is processed
	*/
	virtual TBool	DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);

	/**
	* Return a pointer to the object that the data wraps
	*
	* \return pointer to the object that the data wraps
	*/
	virtual TAny*	GetObject();
	virtual void    SetObjectL(TAny* aAny);
	virtual void	DisownObject();
	virtual CSIPProfile* GetSIPProfileObject(); 
	
protected:
	/**
	* Protected constructor. First phase construction
	*/
	CT_DataSIPProfile();
	void	ConstructL();
    void 	DestroyData();
    
private:
	void	DoCmdDestructor();    
	void    DoCmdType(const TTEFSectionName& aSection);
	void    DoCmdGetParameter(const TTEFSectionName& aSection);  
    
private:
	CSIPProfile* iSIPProfile;	
	};

#endif /* __T_SIPPROFILE__ */

