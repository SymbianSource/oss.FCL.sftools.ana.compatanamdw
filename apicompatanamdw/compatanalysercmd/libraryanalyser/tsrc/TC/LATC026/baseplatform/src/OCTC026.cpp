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


#include "OCTC026.h"
#include <e32uid.h>

EXPORT_C COCTC026* COCTC026::TestFunction()
	{
	return 0;
	}

COCTC026::~COCTC026()
	{
	delete iString;
	}

COCTC026::COCTC026(CConsoleBase& aConsole)
	: iConsole(aConsole)
	{
	}

void COCTC026::ConstructL(const TDesC& aString)
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
