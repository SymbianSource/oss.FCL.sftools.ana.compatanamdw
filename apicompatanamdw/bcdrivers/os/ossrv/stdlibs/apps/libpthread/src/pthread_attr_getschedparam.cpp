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
* Description:  pthread_attr_getschedparam call implementation.
*
*
*
*/

#include <pthread.h>
#include <errno.h>
#include "threadglobals.h"
#include "threadcreate.h"

EXPORT_C int pthread_attr_getschedparam(const pthread_attr_t *attrib,
                                        struct sched_param *param)
{
    THR_PRINTF("[pthread] Begin pthread_attr_getschedparam\n");

    _pthread_attr *thAttrPtr;
    
    if ((NULL == attrib) || (NULL == param))
    {
        THR_PRINTF("[pthread] End of pthread_attr_getschedparam\n");
        return EINVAL;
    }
    
    thAttrPtr = (_pthread_attr*) attrib;
    
    if ((thAttrPtr->sp.sched_priority < MIN_RR_PRIORITY) ||
        (thAttrPtr->sp.sched_priority > MAX_RR_PRIORITY))
    {
        THR_PRINTF("[pthread] End of pthread_attr_getschedparam\n");
        return EINVAL;        
    }    
    
    memcpy (param, &thAttrPtr->sp, sizeof (struct sched_param));
    
    THR_PRINTF("[pthread] End pthread_attr_getschedparam\n");
    
    return 0;
}


// End of File