/*
* Copyright (c) 2005-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  thr_main call is implemented. This is a non POSIX API.
*
*
*/

#include <pthread.h>
#include "threadglobals.h"
#include "threadcreate.h"
#include "pthreadmisc.h"

extern "C" 
{
    

int thr_main()
{
    _pthread_node_t *selfNodePtr;
    
    THR_PRINTF("[pthread] Begin thr_main\n");
    
    //Get the TLS value (self node pointer)
    selfNodePtr = (_pthread_node_t*) _pthread_getTls();

    THR_PRINTF("[pthread] End thr_main\n");
    
    return (selfNodePtr->mainFlag);
}

}
// End of File
