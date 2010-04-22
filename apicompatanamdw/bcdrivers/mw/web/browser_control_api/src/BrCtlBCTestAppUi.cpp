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
#include "BrCtlBCTestAppUi.h"
#include "BrCtlBCTestContainer.h" 
#include <BrCtlBCTest.rsg>
#include "brctlbctest.hrh"

#include <avkon.hrh>


// ================= MEMBER FUNCTIONS =======================
//
// ----------------------------------------------------------
// CBrCtlBCTestAppUi::ConstructL()
// ?implementation_description
// ----------------------------------------------------------
//
void CBrCtlBCTestAppUi::ConstructL()
    {
    BaseConstructL();
    iAppContainer = new (ELeave) CBrCtlBCTestContainer;
    iAppContainer->SetMopParent(this);
    iAppContainer->ConstructL( ClientRect() );
    AddToStackL( iAppContainer );
    iAppContainer->SetAppUi(this);
    }

// ----------------------------------------------------
// CBrCtlBCTestAppUi::~CBrCtlBCTestAppUi()
// Destructor
// Frees reserved resources
// ----------------------------------------------------
//
CBrCtlBCTestAppUi::~CBrCtlBCTestAppUi()
    {
    if (iAppContainer)
        {
        RemoveFromStack( iAppContainer );
        delete iAppContainer;
        }

   }

// ------------------------------------------------------------------------------
// CBrCtlBCTestAppUi::::DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane)
//  This function is called by the EIKON framework just before it displays
//  a menu pane. Its default implementation is empty, and by overriding it,
//  the application can set the state of menu items dynamically according
//  to the state of application data.
// ------------------------------------------------------------------------------
//
void CBrCtlBCTestAppUi::DynInitMenuPaneL(
    TInt aResourceId,CEikMenuPane* aMenuPane)
    {
    iAppContainer->DynInitMenuPaneL(aResourceId, aMenuPane);
    }

// ----------------------------------------------------
// CBrCtlBCTestAppUi::HandleKeyEventL(
//     const TKeyEvent& aKeyEvent,TEventCode /*aType*/)
// ?implementation_description
// ----------------------------------------------------
//
TKeyResponse CBrCtlBCTestAppUi::HandleKeyEventL(
    const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    return iAppContainer->HandleKeyEventL(aKeyEvent, aType);;
    }

// ----------------------------------------------------
// CBrCtlBCTestAppUi::HandleCommandL(TInt aCommand)
// ?implementation_description
// ----------------------------------------------------
//
void CBrCtlBCTestAppUi::HandleCommandL(TInt aCommand)
    {
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
        case EEikCmdExit:
            {
            Exit();
            break;
            }

        default:
            iAppContainer->HandleCommandL(aCommand);
            break;      
        }
    }

// End of File  
