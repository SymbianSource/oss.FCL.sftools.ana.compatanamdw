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
* Description:  Example for developing a plugin
*
*/


#ifndef PLUGINAPIECOMMAIN_H
#define PLUGINAPIECOMMAIN_H

// INCLUDES

#include <e32std.h>
#include <npupp.h>
#include "pluginapi.h"
#include "CEcomBrowserPluginInterface.h"

// DATA TYPES

typedef MPluginAdapter *MPluginAdapterPTR;
typedef CCoeControl *CCoeControlPTR;

// CLASS DECLARATION

/**
*  CPluginAPIEcomMain class.
*/
class CPluginAPIEcomMain : public CEcomBrowserPluginInterface
    {
    public:
    	/**
        * Two-phased constructor.
        */
        static CPluginAPIEcomMain* NewL (TAny* aInitParam);

		/**
        * Destructor.
        */
        ~CPluginAPIEcomMain();

		/**
        * Accessor method for retrieving iNPNfunctions
        */
        NPNetscapeFuncs* Funcs ( void ) { return iNPNfunctions; }

    private:
    
    	/**
    	* Private constuctor
    	*/
        CPluginAPIEcomMain ( NPNetscapeFuncs* aNPNfunctions );
		
		/**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL (NPPluginFuncs* aPluginFuncs );

        NPNetscapeFuncs* iNPNfunctions;
    };


#endif // PLUGINAPIECOMMAIN_H

// End of File