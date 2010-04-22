/*
* Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description:      Handle state changed events
*
*/



#ifndef BRCTLBCTESTSTATECHANGEOBSERVER_H
#define BRCTLBCTESTSTATECHANGEOBSERVER_H

// INCLUDES
#include <BrCtlInterface.h>

// FORWARD DECLARATIONS
class CBrCtlBCTestContainer;

// CLASS DECLARATION

/** 
* CBrCtlBCTestStateChangeObserver class.
* This class inherits from the MBrCtlStateChangeObserver interface which is used to 
* receive state-changed events.
*/
class CBrCtlBCTestStateChangeObserver : public CBase, public MBrCtlStateChangeObserver
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CBrCtlBCTestStateChangeObserver* NewL(CBrCtlBCTestContainer* aContainer);

        /**
        * Destructor.
        */
        ~CBrCtlBCTestStateChangeObserver();

        /**
        * A state change events notification
        * @since 2.8
        * @param aState The state, currently the only state is EStateImageMapView  
        * @param aValue This value will be true if we going to image map view and
        *               it will be false if we are returning from image map view
        * @return void
        */
        void StateChanged(TBrCtlDefs::TBrCtlState aState, TInt aValue);

    private:
	    /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL(CBrCtlBCTestContainer* aContainer);

    private:   // data
        // Pointer to the container class associated with this observer
        CBrCtlBCTestContainer* iContainer;
    };

#endif      // BRCTLBCTESTSTATECHANGEOBSERVER_H
            
// End of File

