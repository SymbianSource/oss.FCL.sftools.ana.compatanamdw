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


class COCTC005 : public CBase
  	{
public:

IMPORT_C COCTC005();
IMPORT_C ~COCTC005();
IMPORT_C void Func1(TUint a);
IMPORT_C void Func2(TInt a);
IMPORT_C TInt Func3( char* c1, char** c2 );
IMPORT_C TInt Func4( char const * c1, char const * const* c2 );
IMPORT_C TInt Func5( TInt (*) (char* c1), char* c2 );

private:

TInt iI;
TUint iUI;
	};
