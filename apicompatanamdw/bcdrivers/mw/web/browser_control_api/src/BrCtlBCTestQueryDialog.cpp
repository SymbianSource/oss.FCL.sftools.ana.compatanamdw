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

#include <avkon.hrh>

#include "BrCtlBCTestQueryDialog.h"

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CBrCtlBCTestQueryDialog::CBrCtlBCTestQueryDialog( TDes& aDefInput, HBufC*& aRetBuf )
    : CAknTextQueryDialog( aDefInput )
    , iRetBuf( aRetBuf )
	{
	}

// ---------------------------------------------------------
// CBrCtlBCTestQueryDialog::PreLayoutDynInitL
// ---------------------------------------------------------
//
void  CBrCtlBCTestQueryDialog::PreLayoutDynInitL()
	{
    CAknTextQueryDialog::PreLayoutDynInitL();

    MakeLeftSoftkeyVisible( ETrue );
    } 

// ---------------------------------------------------------
// CBrCtlBCTestQueryDialog::OkToExitL
// ---------------------------------------------------------
//
TBool CBrCtlBCTestQueryDialog::OkToExitL( TInt aKeycode )
	{
	switch ( aKeycode )
		{
		case EAknSoftkeyOk:
			{
            CAknQueryControl* control = QueryControl();

            __ASSERT_DEBUG( control, User::Panic( KNullDesC, KErrGeneral ) );
            
            iRetBuf = HBufC::NewL( control->GetTextLength() + 1);
            TPtr temp( iRetBuf->Des() );
			control->GetText( temp );
            temp.ZeroTerminate();
			}
			// no break !!! same return value
		case EAknSoftkeyCancel:
			return ETrue;
		default:
			return EFalse;
		}
    }

// ---------------------------------------------------------
// CBrCtlBCTestQueryDialog::HandleQueryEditorStateEventL
//
// This code is base on AknQueryDialog.cpp
// ---------------------------------------------------------
//
TBool CBrCtlBCTestQueryDialog::HandleQueryEditorStateEventL(CAknQueryControl* /*aQueryControl*/, 
	TQueryControlEvent /*aEventType*/, TQueryValidationStatus /*aStatus*/)
    {
    return EFalse;
    }

//  End of File