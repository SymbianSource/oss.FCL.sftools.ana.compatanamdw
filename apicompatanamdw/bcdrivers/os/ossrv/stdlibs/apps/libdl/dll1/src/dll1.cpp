/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
#include <e32uid.h>
#include <dlfcn.h>

#ifndef EKA2 
GLDEF_C TInt E32Dll(TDllReason /*aReason*/) 

// DLL entry point
	{
	return(KErrNone);
	}
#endif 

extern "C" EXPORT_C int strcmp(const char *string1, const char *string2)
{
	while (*string1 == *string2++)
		if (*string1++ == 0)
			return (0);
	return (*(const unsigned char *)string1 - *(const unsigned char *)(string2 - 1));
}

extern "C" EXPORT_C float abs(float i)
{
	return (i < 0) ? -i : i;
}


