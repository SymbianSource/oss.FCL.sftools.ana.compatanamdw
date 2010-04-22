/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test Class For HPositionGenericInfo
*
*/


#ifndef CTESTPOSITIONGENERICINFO_H
#define CTESTPOSITIONGENERICINFO_H

// System Includes
#include <StifLogger.h>
#include <StifParser.h>
#include <StifTestModule.h>
#include <e32base.h>
#include <e32std.h>
#include <bautils.h>
#include <f32file.h>

#include <lbs.h>
#include <LbsPositionInfo.h>
#include <LbsCommon.h>
#include <LbsRequestor.h>
#include <lbssatellite.h>
#include <lbsclasstypes.h>
#include <LbsFieldIds.h>


// Constants


// CLASS DECLARATION
/**
 *  Test Class For HPositionGenericInfo
 *
 *  This has HPositionGenericInfo object which invokes HPositionGenericInfo methods 
 *
 *  @lib testlbslocacquisition.lib
 *  @since S60 v3.2
 */

class CTestPositionGenericInfo :public CBase
    {
    public:
    	enum TValueType
    		{
    			EInt8 = 0,
				EInt16,
				EInt32,
				EInt64,
				EUint8,
				EUint16,
				EUint32,
				EReal32,
				EReal64,
				EDesC8,
				EDesC16,
				EPtrC8,
				EPtrC16,
				ETime,
				ETimeIntervalMicroSeconds
    		};
    public:  
    
    	// Constructors and destructor
        /**
        * C++ default constructor.
        */
        CTestPositionGenericInfo(CStifLogger* aLog);

        /**
        * Destructor. 
        */
        ~CTestPositionGenericInfo();

    public:         

        // New functions  
	    /**
	     * Method to Check the Successfull creation of
	     * HPositionGenericInfo Object
	     *
	     * @since S60 v3.2
	     * Returns KErrNone if successful. 
	     *
	     */        
		  TInt CheckNewL( CStifItemParser& aItem );
		  
	    /**
	     * Method to Check follwoing methods
	     * SetRequestedField
	     * SetRequestedFields
	     *
	     * @since S60 v3.2
	     *
	     */   		  
    	  TInt CheckRequestedFieldsL( );
    	  		  		  
	    /**
	     * Method to Check follwoing methods
	     * FirstRequestedFieldId
	     * NextRequestedFieldId
	     * IsFieldAvailable
	     *
	     * @since S60 v3.2
	     *
	     */ 
	      TInt CheckOrderOfRequestedFieldL( );
		  		  
	    /**
	     * Method to Check ClearPositionData
	     *
	     * @since S60 v3.2
	     *
	     */ 
	    TInt CheckClearPositionDataL();
	    		  		  
	    /**
	     * Method to Check ClearRequestedFields
	     *
	     * @since S60 v3.2
	     *
	     */ 
	    TInt CheckClearRequestedFieldsL();
	    
	    /**
	     * Method to Check ClearRequestedFields
	     *
	     * @since S60 v3.2
	     *
	     */ 
	    TInt CheckSetGetValueL( CStifItemParser& aItem );
	  
	private:  //Functions    
			  		  
	    /**
	     * Method to create HPositionGenericInfo with
	     * aBufferSize and aMaxFields
	     *
	     * @since S60 v3.2
	     *
	     */ 
		TInt CreateLC( TInt aBufferSize, TInt aMaxFields );
				  		  
	    /**
	     * Method to create HPositionGenericInfo with
	     * aBufferSize
	     *
	     * @since S60 v3.2
	     *
	     */ 
		TInt CreateLC( TInt aBufferSize );
				  		  
	    /**
	     * Method to call default HPositionGenericInfo
	     * constructor
	     *
	     * @since S60 v3.2
	     *
	     */ 
		TInt CreateLC( );
				  		  
	    /**
	     * Method to call default HPositionGenericInfo
	     * constructor
	     *
	     * @since S60 v3.2
	     *
	     */ 
		TInt CreateL( );
				  		  
	    /**
	     * Method to delete HPositionGenericInfo
	     *
	     * @since S60 v3.2
	     *
	     */ 
		TInt Delete( );
		
    private:  //data
	    /**
	     * HPositionGenericInfo Instance
	     */     		 
    	HPositionGenericInfo*         iPositionGenericInfo;
    	  
	    /**
	     * Pointer to Stif Logger - Does not Own
	     */           
        CStifLogger* 			iLog;
	        
     };     

#endif      // CTESTPOSITIONGENERICINFO_H

// End of File
