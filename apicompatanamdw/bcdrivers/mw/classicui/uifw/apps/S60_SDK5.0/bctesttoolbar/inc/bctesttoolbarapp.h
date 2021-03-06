/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Declares main application class.
*
*/


#ifndef C_BCTESTTOOLBARAPP_H
#define C_BCTESTTOOLBARAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestToolBar = { 0x200089C3 }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestToolBarApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestToolBarApp : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCTestToolBarDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCTestToolBar ).
        * @return The value of KUidBCTestToolBar.
        */
        TUid AppDllUid() const;

    };

#endif // C_BCTESTTOOLBARAPP_H

// End of File
