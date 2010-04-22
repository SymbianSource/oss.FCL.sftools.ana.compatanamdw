/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test netscape plugins implementation
*
*/



// INCLUDE FILES
#include <e32std.h>
#include <e32base.h>
#include "pluginapiecommain.h"
#include "pluginapiinst.h"

// EXTERNAL DATA STRUCTURES

// EXTERNAL FUNCTION PROTOTYPES

// CONSTANTS

// MACROS

// LOCAL CONSTANTS AND MACROS

// MODULE DATA STRUCTURES

// LOCAL FUNCTION PROTOTYPES

// FORWARD DECLARATIONS

// ============================= LOCAL FUNCTIONS ===============================

CPluginAPIEcomMain* CPluginAPIEcomMain::NewL( TAny* aInitParam )
{
    TFuncs* funcs = REINTERPRET_CAST( TFuncs*, aInitParam );
    CPluginAPIEcomMain* self = new ( ELeave ) CPluginAPIEcomMain( funcs->iNetscapeFuncs );
    CleanupStack::PushL( self );
    self->ConstructL( funcs->iPluginFuncs );
    CleanupStack::Pop();

	Dll :: SetTls ( ( void* ) self );

    return self;
}

void CPluginAPIEcomMain::ConstructL( NPPluginFuncs* aPluginFuncs )
{
    InitializeFuncs( aPluginFuncs );
}

CPluginAPIEcomMain::CPluginAPIEcomMain(NPNetscapeFuncs* aNpf):
                 CEcomBrowserPluginInterface(),iNPNfunctions(aNpf)
{

}

CPluginAPIEcomMain::~CPluginAPIEcomMain()
{
}
// ========================== OTHER EXPORTED FUNCTIONS =========================
