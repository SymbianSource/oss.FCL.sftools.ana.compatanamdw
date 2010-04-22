/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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


// INCLUDE FILES
#include <stdio.h>
#include <stdlib.h>

TInt main( int argc, char** argv)
{	
	int fd=atoi(argv[2]);
	
	printf("%s and %d\n", argv[1],argc);
	
	FILE* fp = fdopen(fd, "r");
	if (fp)
		{
		printf("pass\n");	
		}
	else
		printf("fail\n");	
	
	abort();
}


//  End of File

