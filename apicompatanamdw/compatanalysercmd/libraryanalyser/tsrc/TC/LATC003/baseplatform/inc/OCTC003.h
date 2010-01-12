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

#include <e32cons.h>


class COCTC003 : public CBase
  	{
public:
		
	IMPORT_C static COCTC003* NewLC(CConsoleBase& aConsole, const TDesC& aString);
		
	~COCTC003();
		
	IMPORT_C void Func1();
	IMPORT_C void Func2();
	IMPORT_C void Func3();
private:
		
	COCTC003(CConsoleBase& aConsole);
		
	void ConstructL(const TDesC& aString);
private:
	CConsoleBase& iConsole;
	HBufC*        iString;
	};
