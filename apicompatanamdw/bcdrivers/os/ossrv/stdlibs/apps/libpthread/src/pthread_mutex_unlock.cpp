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
* Description:  POSIX implementation of mutexes on Symbian
*
*/


#include "mutextypes.h"

EXPORT_C int pthread_mutex_unlock (pthread_mutex_t * mutex)
{
    if( !VALID_MUTEX(mutex) )
    {
        return EINVAL;
    }

    _pthread_mutex_t* pMutex = mutex->iPtr;
    pthread_t self;
    int retval = 0;
    pMutex->iDataLock.Wait();
    if(mutex->iState == _EDestroyed)
    {
        return EINVAL;
    }
    switch(pMutex->iMutexType)
    {
        case  PTHREAD_MUTEX_NORMAL:
        {
            if(pMutex->iCount == 1)
            {
                pMutex->iCount = 0;
                pMutex->iSignalSemaphore.Signal();
            }
            break;
        }

        case  PTHREAD_MUTEX_RECURSIVE:
        {
            self = pthread_self();
            if(pMutex->iLockingThread == self)
            {
                pMutex->iCount--;       
                if(pMutex->iCount == 0)
                {
                    pMutex->iLockingThread = 0;
                    pMutex->iSignalSemaphore.Signal();
                }
            }
            else
            {
                retval = EPERM;
            }
            break;  
        }


        case  PTHREAD_MUTEX_ERRORCHECK:
        {
            self = pthread_self();
            if( (pMutex->iLockingThread != self) || (pMutex->iCount != 1) )
            {
                retval = EPERM;
                break;
            }
            pMutex->iCount = 0;
            pMutex->iLockingThread = 0;
            pMutex->iSignalSemaphore.Signal();
            break;
        }

        default:
            retval = ENOSYS;
            break;
    } //switch
    pMutex->iDataLock.Signal();
    return retval;

}


// End of File

