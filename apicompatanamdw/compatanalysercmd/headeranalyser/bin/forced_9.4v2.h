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

#include <variant/symbian_os.hrh>
#include <e32def.h>
#include <e32base.h>
#include <s32strm.h>
#include <f32file.h>

#undef IMPORT_C
#define IMPORT_C __THIS_IS_EXPORTED__
#undef EXPORT_C
#define EXPORT_C __THIS_IS_EXPORTED__

#ifndef _WCHAR_T_DECLARED
#define _WCHAR_T_DECLARED
#endif

typedef long n_long;
typedef short n_short;
typedef long n_time;

#ifndef __int64
#define __int64  long
#endif

// QT exported macros
#undef Q_DECL_EXPORT
#define Q_DECL_EXPORT __THIS_IS_EXPORTED__
#undef Q_DECL_IMPORT
#define Q_DECL_IMPORT __THIS_IS_EXPORTED__