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



#ifndef BRCTLBCTESTQUERYDIALOG_H
#define BRCTLBCTESTQUERYDIALOG_H


//  INCLUDES

#include <eikdialg.h>
#include <aknmultilinequerycontrol.h>
#include <aknquerydialog.h>

// CLASS DECLARATION

/**
*  Class definition
*/
class CBrCtlBCTestQueryDialog : public CAknTextQueryDialog
    {
    public:  // Constructors and destructor
    
        /**
        * C++ default constructor.
	    * @param aMsg User name (it may contains default value).
	    * @param aResp Password.
        */
	    CBrCtlBCTestQueryDialog( TDes& aDefInput, HBufC*& aRetBuf );

        /**
        * Destructor.
        */
        virtual ~CBrCtlBCTestQueryDialog(){};

    private:	// from CEikDialog

	    /**
	    * Fills the edwins with default values.
	    */
        void  PreLayoutDynInitL();

	    /**
	    * Set the password if the user pressed Ok.
	    * @param aKeyCode The ID of the pushed button.
	    * @return May the dialog exit?
	    */
        TBool OkToExitL( TInt aKeycode );

        // MAknQueryControlObserver
        TBool HandleQueryEditorStateEventL(CAknQueryControl* aQueryControl, TQueryControlEvent aEventType, TQueryValidationStatus aStatus);

    private:	// Data

        HBufC*& iRetBuf;
    };

#endif // BRCTLBCTESTQUERYDIALOG_H

// End of File