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



#include "OCTC001.h"
#include <e32uid.h>

EXPORT_C COCTC001* COCTC001::TestFunction() const
	{
return 0;
	}

COCTC001::~COCTC001()
	{
	delete iString;
	}

COCTC001::COCTC001(CConsoleBase& aConsole)
	: iConsole(aConsole)
	{
	}

void COCTC001::ConstructL(const TDesC& aString)
	{
	iString=aString.AllocL();
    }


#ifdef EKA2 
GLDEF_C TInt E32Dll() 
#else 
GLDEF_C TInt E32Dll(TDllReason /*aReason*/) 
#endif 


// DLL entry point
	{
	return(KErrNone);
	}
