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
* Description:  pthread_attr_getdetachstate call implementation.
*
*
*
*/

#include <pthread.h>
#include <errno.h>
#include "threadglobals.h"
#include "threadcreate.h"

EXPORT_C int pthread_attr_getdetachstate(const pthread_attr_t *attrib,
                                         int *detState)
{
    THR_PRINTF("[pthread] Begin pthread_attr_getdetachstate\n");

    _pthread_attr *thAttrPtr;
    
    if ((NULL == attrib) || (NULL == detState))
    {
        THR_PRINTF("[pthread] End of pthread_attr_getdetachstate\n");
        return EINVAL;
    }
    
    thAttrPtr = (_pthread_attr*) attrib;
    
    if ((thAttrPtr->detachState != PTHREAD_CREATE_JOINABLE) &&
        (thAttrPtr->detachState != PTHREAD_CREATE_DETACHED))
    {
        THR_PRINTF("[pthread] End of pthread_attr_getdetachstate\n");
        return EINVAL;        
    }
    
    
    *detState = thAttrPtr->detachState;
    
    THR_PRINTF("[pthread] End pthread_attr_getdetachstate\n");
    
    return 0;
}

// End of File
