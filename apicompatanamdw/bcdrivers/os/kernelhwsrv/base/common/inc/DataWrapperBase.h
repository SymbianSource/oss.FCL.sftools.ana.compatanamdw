/*
* Copyright (c) 2007-2008 Nokia Corporation and/or its subsidiary(-ies).
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


#if (!defined __DATA_WRAPPER_BASE__)
#define __DATA_WRAPPER_BASE__

//	EPOC includes
#include <datawrapper.h>

class CDataWrapperBase : public CDataWrapper
	{
public:
	virtual ~CDataWrapperBase();

	TBool	GetBoolFromConfig(const TDesC& aSectName,const TDesC& aKeyName,TBool& aResult);
	TBool	GetIntFromConfig(const TDesC& aSectName, const TDesC& aKeyName, TInt& aResult);
	TBool	GetStringFromConfig(const TDesC& aSectName, const TDesC& aKeyName, TPtrC& aResult);
	TBool	GetHexFromConfig(const TDesC& aSectName, const TDesC& aKeyName, TInt& aResult);
	virtual void	InitialiseL();

protected:
	CDataWrapperBase();

	TBool	GetCommandStringParameter(const TDesC& aParameterName, const TDesC& aSection, TPtrC& aResult, TText8 *aFileName, TInt aLine, TBool aMandatory);
	TBool	GetCommandIntParameter(const TDesC& aParameterName, const TDesC& aSection, TInt& aResult, TText8 *aFileName, TInt aLine, TBool aMandatory);
	TBool	GetCommandBoolParameter(const TDesC& aParameterName, const TDesC& aSection, TBool& aResult, TText8 *aFileName, TInt aLine, TBool aMandatory);

private:
	TBool	GetCommandStringParameterL(const TDesC& aSectName, const TDesC& aKeyName, TPtrC& aResult);

private:
	// Included ini files
	RPointerArray<CIniData>	iInclude;
	RPointerArray<HBufC>	iBuffer;
	};

#endif /* __DATA_WRAPPER_BASE__ */
