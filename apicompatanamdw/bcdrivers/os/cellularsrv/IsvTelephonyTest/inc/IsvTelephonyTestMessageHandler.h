/*
* Copyright (c) 2002-2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  
*
*/



#ifndef ISVTELEPHONYTESTMESSAGEHANDLER_H
#define ISVTELEPHONYTESTMESSAGEHANDLER_H

//  INCLUDES
#include <e32base.h>

// CONSTANTS
// Message max length, currently limited by Stif logger and Ui 
const TInt KMessageHandlerMaxMessageSize = 254;

// CLASS DECLARATION

/**
*  Interface for log/UI message printing.   
*
*  @lib 
*  @since 
*/
class MIsvTelephonyTestMessageHandler 
    {
	public: 
	    /**
		* Enumeration for log/UI output selection
		*/ 
		enum TMessageOption 
			{
			EMessagesOff = 0, 
			EMessagesLog, 
			EMessagesUi, 
			EMessagesLogAndUi 
			};
	
    public:
        /**
        * Pure virtual functions 
        */
        /** 
        * Outputs messages to Stif UI or log
        * @param aMessage Contains the message
        */        
		virtual void PrintMessage( const TDesC& aMessage ) = 0;

        /** 
        * Outputs messages to Stif UI or log
        * @param aMessage Contains the message
        */        
		virtual void PrintMessage( TRefByValue<const TDesC> aMessage,... ) = 0; 
    
    };

#endif      // ISVTELEPHONYTESTMESSAGEHANDLER_H
            
// End of File
