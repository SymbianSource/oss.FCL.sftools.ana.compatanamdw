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
* Description:  Test Class For TPositionCourseInfo
*
*/


#ifndef CTESTPOSITIONCOURSEINFO_H
#define CTESTPOSITIONCOURSEINFO_H

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


// Constants


// CLASS DECLARATION
/**
 *  Test Class For TPositionCourseInfo
 *
 *  This has TPositionCourseInfo object which invokes TPositionCourseInfo methods 
 *
 *  @lib testlbslocacquisition.lib
 *  @since S60 v3.2
 */

class CTestPositionCourseInfo : public CBase
    {
    public:  
    
    	// Constructors and destructor
        /**
        * C++ default constructor.
        */
        CTestPositionCourseInfo(CStifLogger* aLog);

        /**
        * Destructor. 
        */
        ~CTestPositionCourseInfo();

    public:         

        // New functions  
	    /**
	     * Method to Check the Course Info
	     * @since S60 v3.2
	     * Returns KErrNone if successful. 
	     *
	     */        
		  TInt CheckCourse( );
		  		  	   
    private:  //data
	    /**
	     * TPositionCourseInfo Instance
	     */     		 
    	TPositionCourseInfo         iPositionCourseInfo;
    	  
	    /**
	     * Pointer to Stif Logger - Does not Own
	     */           
        CStifLogger* 			iLog;
	        
     };     

#endif      // CTESTPOSITIONCOURSEINFO_H

// End of File
