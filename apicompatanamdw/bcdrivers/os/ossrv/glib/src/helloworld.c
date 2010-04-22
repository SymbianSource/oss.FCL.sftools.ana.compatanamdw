/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies). 
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


// This is a test application used by g_spawn APIs. This application
// is spawned by them.

#include <stdio.h>

int main(int argc,char *argv[])
{
	int i;
	FILE *fp;

	fp = fopen("c:\\Helloworld.txt", "w");

	if(!fp)
	{
		printf("File creation failed\n");
		return 0;
	}
	
	fprintf(fp,"argc = %d\n", argc );
		
	for(i=0;i<argc;i++)
	{
		fprintf(fp,"argv[%d] = %s\n",i,argv[i]);
	}
	
	fclose(fp);
	return 0;
}
