/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description:      ?Description
*
*/




// INCLUDE FILES
#include "BrCtlBCTestDocument.h"
#include "BrCtlBCTestAppUi.h"

// ================= MEMBER FUNCTIONS =======================

// constructor
CBrCtlBCTestDocument::CBrCtlBCTestDocument(CEikApplication& aApp)
: CAknDocument(aApp)    
    {
    }

// destructor
CBrCtlBCTestDocument::~CBrCtlBCTestDocument()
    {
    }

// EPOC default constructor can leave.
void CBrCtlBCTestDocument::ConstructL()
    {
    }

// Two-phased constructor.
CBrCtlBCTestDocument* CBrCtlBCTestDocument::NewL(
        CEikApplication& aApp)     // CBrCtlBCTestApp reference
    {
    CBrCtlBCTestDocument* self = new (ELeave) CBrCtlBCTestDocument( aApp );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;
    }
    
// ----------------------------------------------------
// CBrCtlBCTestDocument::CreateAppUiL()
// constructs CBrCtlBCTestAppUi
// ----------------------------------------------------
//
CEikAppUi* CBrCtlBCTestDocument::CreateAppUiL()
    {
    return new (ELeave) CBrCtlBCTestAppUi;
    }

// End of File  
