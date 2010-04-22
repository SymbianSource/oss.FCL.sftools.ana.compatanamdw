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
* Description:  POSIX implementation of pthread on Symbian
*
*/

#include "condvartypes.h"

EXPORT_C int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    return _internalCondWait(cond,mutex,NULL);
}



//End of File

