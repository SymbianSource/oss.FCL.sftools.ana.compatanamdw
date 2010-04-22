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



#ifndef BRCTLBCTESTAPP_H
#define BRCTLBCTESTAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
// UID of the application
const TUid KUidBrCtlBCTest = { 0xA0000181 };

// CLASS DECLARATION

/**
* CBrCtlBCTestApp application class.
* Provides factory to create concrete document object.
* 
*/
class CBrCtlBCTestApp : public CAknApplication
    {
    
    public: // Functions from base classes
        /**
        * From CApaApplication, overridden to enable INI file support.
        * @return A pointer to the dictionary store
        */
    CDictionaryStore* OpenIniFileLC(RFs& aFs) const;
    private:

        /**
        * From CApaApplication, creates CBrCtlBCTestDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();
        
        /**
        * From CApaApplication, returns application's UID (KUidBrCtlBCTest).
        * @return The value of KUidBrCtlBCTest.
        */
        TUid AppDllUid() const;
    };

#endif // BRCTLBCTESTAPP_H

// End of File

