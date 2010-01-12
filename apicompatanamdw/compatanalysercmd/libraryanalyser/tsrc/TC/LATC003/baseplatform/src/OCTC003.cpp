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


#include "OCTC003.h"
#include <e32uid.h>

// construct/destruct

EXPORT_C COCTC003* COCTC003::NewLC(CConsoleBase& aConsole, const TDesC& aString)
	{
	COCTC003* self=new (ELeave) COCTC003(aConsole);
	CleanupStack::PushL(self);
	self->ConstructL(aString);
	return self;
	}

COCTC003::~COCTC003()
	{
	delete iString;
	}



EXPORT_C void COCTC003::Func1()
	{
	TInt a = 1;
	}
	
EXPORT_C void COCTC003::Func2()
	{
	TInt a = 2;
	}
	
EXPORT_C void COCTC003::Func3()
	{
	TInt a = 3;
	}

COCTC003::COCTC003(CConsoleBase& aConsole)
	: iConsole(aConsole)
	{
	}

void COCTC003::ConstructL(const TDesC& aString)
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
