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

#include "OCTC004.h"
#include <e32uid.h>
#pragma message("Please ensure that you read the ReadMe file.")


EXPORT_C COCTC004::COCTC004()
    {
    }

EXPORT_C COCTC004::~COCTC004() 
	{
	}

EXPORT_C void COCTC004::Func2()
	{
    iA = 2;
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
