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


 

// This case tests that changing function to const does not cause BC break issue.

#include <e32cons.h>


class COCTC026 : public CBase
  	{
public:
	
	// non-const to const
	IMPORT_C COCTC026* TestFunction() const;	
	~COCTC026();	
private:
	
	COCTC026(CConsoleBase& aConsole);
	
	void ConstructL(const TDesC& aString);
private:
	CConsoleBase& iConsole;
	HBufC*        iString;
	};
