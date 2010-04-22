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




#ifndef BRCTLBCTESTDOCUMENT_H
#define BRCTLBCTESTDOCUMENT_H

// INCLUDES
#include <akndoc.h>
   
// CONSTANTS

// FORWARD DECLARATIONS
class  CEikAppUi;

// CLASS DECLARATION

/**
*  CBrCtlBCTestDocument application class.
*/
class CBrCtlBCTestDocument : public CAknDocument
    {
    public: // Constructors and destructor
        /**
        * Two-phased constructor.
        */
        static CBrCtlBCTestDocument* NewL(CEikApplication& aApp);

        /**
        * Destructor.
        */
        virtual ~CBrCtlBCTestDocument();

    public: // New functions

    protected:  // New functions

    protected:  // Functions from base classes

    private:

        /**
        * EPOC default constructor.
        */
        CBrCtlBCTestDocument(CEikApplication& aApp);
        void ConstructL();

    private:

        /**
        * From CEikDocument, create CBrCtlBCTestAppUi "App UI" object.
        */
        CEikAppUi* CreateAppUiL();
    };

#endif // BRCTLBCTESTDOCUMENT_H

// End of File

