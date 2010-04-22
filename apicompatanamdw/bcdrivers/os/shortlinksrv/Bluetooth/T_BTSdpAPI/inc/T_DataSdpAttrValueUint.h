/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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


#if (!defined __T_DATA_SDP_ATTR_VALUE_UINT_H__)
#define __T_DATA_SDP_ATTR_VALUE_UINT_H__

//	User Includes
#include "T_DataSdpAttrValue.h"

/**
 * Test Active Notification class
 *
 */
class CT_DataSdpAttrValueUint :	public CT_DataSdpAttrValue
	{
public:
	/**
	* Two phase constructor
	*/
	static CT_DataSdpAttrValueUint*	NewL();

	/**
	* Public destructor
	*/
	~CT_DataSdpAttrValueUint();

	/**
	* Process a command read from the ini file
	*
	* @param aCommand			The command to process
	* @param aSection			The section in the ini containing data for the command
	* @param aAsyncErrorIndex	Command index for async calls to return errors to
	*
	* @return					ETrue if the command is processed
	*
	* @leave					System wide error
	*/
	virtual TBool	DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);

	/**
	* Return a pointer to the object that the data wraps
	*
	* @return	pointer to the object that the data wraps
	*/
	virtual TAny*	GetObject()	{ return iAttrValUint; }

	/**
	* Set the object that the data wraps
	*
	* @param	aObject object that the wrapper is testing
	*
	*/
	virtual void	SetObjectL(TAny* aAny);

	/**
	* The object will no longer be owned by this
	*
	* @leave	KErrNotSupported if the the function is not supported
	*/
	virtual void	DisownObjectL();

	inline virtual TCleanupOperation CleanupOperation();

protected:
	/**
	* Protected constructor. First phase construction
	*/
	CT_DataSdpAttrValueUint();

	/**
	* Second phase construction
	*/
	void	ConstructL();

	virtual CSdpAttrValue*	GetSdpAttrValue() const;

private:
	static void CleanupOperation(TAny* aAny);

	/**
	* Helper methods
	*/
	void			DestroyData();
	inline 	void	DoCmdNewUintL(const TDesC& aSection);
	inline	void	DoCmdDestructor();

private:
	CSdpAttrValueUint*	iAttrValUint;
	};

#endif /* __T_DATA_SDP_ATTR_VALUE_UINT_H__ */
