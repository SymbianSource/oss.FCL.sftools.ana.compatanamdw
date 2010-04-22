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

EXPORT_C int pthread_mutex_trylock (pthread_mutex_t * mutex)
{
    if( !VALID_MUTEX(mutex) )
    {
        return EINVAL;
    }
    _pthread_mutex_t* pMutex = mutex->iPtr;

    pMutex->iDataLock.Wait();
    if(mutex->iState == _EDestroyed)
    {
        return EINVAL;
    }

    //return immediately if mutex is locked, unless the mutex is a recursive 
    // mutex and we are locking again.  
    if(pMutex->iCount)
    {
        if(pMutex->iMutexType != PTHREAD_MUTEX_RECURSIVE || 
           pMutex->iLockingThread != pthread_self())
        {
            pMutex->iDataLock.Signal();
            return EBUSY;  
        }
    }

    int retval = 0;
    switch(pMutex->iMutexType)
    {
        case  PTHREAD_MUTEX_NORMAL:
        {
            pMutex->iCount = 1; 
            pMutex->iSignalSemaphore.Wait();
            break;
        }

        case  PTHREAD_MUTEX_RECURSIVE:
        {
            if(pMutex->iCount)
            {
                pMutex->iCount++;       
            }
            else
            {
                pMutex->iCount = 1;
                pMutex->iLockingThread = pthread_self();
                pMutex->iSignalSemaphore.Wait();
            }
            break;
        }

        case  PTHREAD_MUTEX_ERRORCHECK:
        {
            pMutex->iCount = 1;
            pMutex->iLockingThread  = pthread_self();
            pMutex->iSignalSemaphore.Wait();
            break;
        }
            
        default:
            retval = ENOSYS;
            break;

    }
    pMutex->iDataLock.Signal();
    return retval;
 }


// End of File
