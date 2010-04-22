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
* Description:  Header file for class vibrawrapper used in vibractrltest.
*
*/


#ifndef VIBRAWRAPPER_H
#define VIBRAWRAPPER_H

// INCLUDES
#include <vibractrl.h>
#include <centralrepository.h>
#include "TestScheduler.h"
#include <HWRMVibraSDKCRKeys.h>


// CONSTANTS
// None

// MACROS
// None

// DATA TYPES
// None

// FUNCTION PROTOTYPES
// None

// FORWARD DECLARATIONS
// None


// CLASS DECLARATION


/**
*  Test class vibractrl.
*  Checks the functionality of Vibractrl API.
*
*/

NONSHARABLE_CLASS(CVibrawrapper) 
        :public MVibraControlObserver
{
public: // Enumerations
       
private: // Enumerations
       
public: // Constructors and destructor
        
    /**
	* Constructor
	*/
	CVibrawrapper();

	/**
    * Two-phased constructor.
    */
    static CVibrawrapper* NewL(TBool NotifUsed);
        
    /**
    * Destructor.
    */
    virtual ~CVibrawrapper();

	/**
    * Method is called when vibra mode status is changed.
	* 
    * @param  CVibraControl::TVibraModeState aStatus: in: current status
    * @return none
    */
	void VibraModeStatus(CVibraControl::TVibraModeState aStatus);
	
	/**
    * Method is called when vibra request status is changed.
	* 
    * @param  CVibraControl::TVibraRequestStatus aStatus: in: current status
    * @return none
    */
	void VibraRequestStatus(CVibraControl::TVibraRequestStatus aStatus);

public: // New functions
       
public: // Functions from base classes        
       
protected: // New functions

protected: // Functions from base classes
        
private:

	/**
    * C++ default constructor.
    */
    void CWibrawrapper();

    /**
    * By default Symbian OS constructor is private.
    */
    void ConstructL(TBool NotifUsed);


public: // Data
	
	//vibra control
	CVibraControl* iVibra;

	//for waiting
	CTestScheduler* scheduler;
	
	//checking that the changes are notified
	TBool iStatusReceived;

	//status of vibra control request
	CVibraControl::TVibraRequestStatus iStatus;

	//gets updated when vibra mode gets changed in profile
	CVibraControl::TVibraModeState iVibraModeState;

	CActiveScheduler* myTestScheduler;
        
protected: // Data
        
private: // Data
        
public: // Friend classes
        
protected: // Friend classes
        
private: // Friend classes
      
};

#endif      // VIBRAWRAPPER_H
            
// End of File
