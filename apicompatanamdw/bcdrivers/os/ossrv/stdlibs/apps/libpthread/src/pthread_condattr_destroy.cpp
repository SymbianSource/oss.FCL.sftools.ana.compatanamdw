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

/*
This function destroys the condtion variable attribute object.
*/
EXPORT_C int pthread_condattr_destroy(pthread_condattr_t * /*attr*/)
{
    return 0;
}

//End of File

