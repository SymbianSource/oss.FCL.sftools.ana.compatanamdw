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



#include "OCTC005.h"
#include <e32uid.h>
#pragma message("Please ensure that you read the ReadMe file.")

EXPORT_C COCTC005::COCTC005()
	{
	}

EXPORT_C COCTC005::~COCTC005()
	{	
	}

EXPORT_C void COCTC005::Func1(TUint a)
	{
    iUI = a+1;
	}
	
	
// Change parameter to TUint
EXPORT_C void COCTC005::Func2(TInt a)
	{
    iI = a+1;
	}
	
// Change parameters to const
EXPORT_C TInt COCTC005::Func3( char* c1, char** c2 )
    {
    if( c1 == 0 )
        return 0;
    
    if( *c2 == 0 )
        return 1;
    
    return 2;
    }
    
// Change parameters to non-const
EXPORT_C TInt COCTC005::Func4( char const * c1, char const * const * const c2 )
    {
    if( c1 == 0 )
        return 0;
    
    if( *c2 == 0 )
        return 1;
    
    return 2;
    }
 
// Change c1 from 'char*' to 'char const*'   
EXPORT_C TInt COCTC005::Func5( TInt (*pF) (char* c1), char* c2 )
    {
    return pF(c2);
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
