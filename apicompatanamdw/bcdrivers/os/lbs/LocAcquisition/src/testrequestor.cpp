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
* Description:  Helper class for CRequestorBase class
*
*/


// System Includes


// User Includes
#include "testrequestor.h"
#include <e32std.h>
#include <s32mem.h>

// Constant Declarations

    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ Default Constructor
// ---------------------------------------------------------------------------
//
TTestRequestor ::TTestRequestor (CStifLogger* aLog):iLog(aLog)
    {
        
    }

// ---------------------------------------------------------------------------
// C++ Destructor
// ---------------------------------------------------------------------------
//
TTestRequestor ::~TTestRequestor ()
    {
        
    }

// ---------------------------------------------------------------------------
// Test case for setting & getting requestor
// ---------------------------------------------------------------------------
TInt TTestRequestor ::SetGetRequestorL(CStifItemParser& aItem)
    {
        TInt reqApplicationType;
	    TInt reqApplicatonFormat;
	    TPtrC reqDataApplication1;
	    CRequestorBase::TRequestorFormat reqFormatArg1 = CRequestorBase::EFormatUnknown;
	    CRequestorBase::TRequestorType reqTypeArg1= CRequestorBase::ERequestorUnknown;
	    TPtrC reqDataApplication2;
	    CRequestorBase::TRequestorFormat reqFormatArg2;
	    CRequestorBase::TRequestorType reqTypeArg2 = CRequestorBase::ERequestorUnknown;
	    User::LeaveIfError(aItem.GetNextInt(reqApplicationType));
    	User::LeaveIfError(aItem.GetNextInt(reqApplicatonFormat));
    	User::LeaveIfError(aItem.GetNextString(reqDataApplication1));
    	//TPtrC reqDataApplication = GetDataL(aItem);	
    
    	switch(reqApplicationType)
    		{
    			case 0:
    			reqTypeArg1 = CRequestorBase::ERequestorUnknown;  
    			break;
    			case 1:
    			reqTypeArg1 = CRequestorBase::ERequestorService;  
    			break;
    			case 2:
    			reqTypeArg1 = CRequestorBase::ERequestorContact;  
    			break;
		}
			switch(reqApplicatonFormat)
		{
			case 0:
			reqFormatArg1 = CRequestorBase::EFormatUnknown;  
			break;
			case 1:
			reqFormatArg1 = CRequestorBase::EFormatApplication;
			break;
			case 2:
			reqFormatArg1 = CRequestorBase::EFormatTelephone;
			break;
			case 3:
			reqFormatArg1 = CRequestorBase::EFormatUrl;
			break;
			case 4:
			reqFormatArg1 = CRequestorBase::EFormatMail;
			break;			
			
		}
		
		CRequestor* requestor = CRequestor::New(reqTypeArg1,reqFormatArg1,reqDataApplication1);
		requestor->SetRequestorL(reqTypeArg1,reqFormatArg1,reqDataApplication1);
		
		requestor->GetRequestor(reqTypeArg2,reqFormatArg2,reqDataApplication2);
		if((reqTypeArg2==reqTypeArg1)&&(reqFormatArg2==reqFormatArg1)
		    &&(reqDataApplication2==reqDataApplication1))
		    {
		        return KErrNone;
		    }
		else
		    return KErrGeneral;
    	
    	
    }
    
    
// ---------------------------------------------------------------------------
// Test case for  getting requestor data
// ---------------------------------------------------------------------------
TInt TTestRequestor ::GetRequestorDataL(CStifItemParser& aItem)
    {
        TInt reqApplicationType;
	    TInt reqApplicatonFormat;
	    TPtrC reqDataApplication1;
	    CRequestorBase::TRequestorFormat reqFormatArg1 = CRequestorBase::EFormatUnknown;
	    CRequestorBase::TRequestorType reqTypeArg1 = CRequestorBase::ERequestorUnknown;
	    User::LeaveIfError(aItem.GetNextInt(reqApplicationType));
    	User::LeaveIfError(aItem.GetNextInt(reqApplicatonFormat));
    	User::LeaveIfError(aItem.GetNextString(reqDataApplication1));
    	switch(reqApplicationType)
    	{
    			case 0:
    			reqTypeArg1 = CRequestorBase::ERequestorUnknown;  
    			break;
    			case 1:
    			reqTypeArg1 = CRequestorBase::ERequestorService;  
    			break;
    			case 2:
    			reqTypeArg1 = CRequestorBase::ERequestorContact;  
    			break;
		}
			
		switch(reqApplicatonFormat)
		    {
			case 0:
			reqFormatArg1 = CRequestorBase::EFormatUnknown;  
			break;
			case 1:
			reqFormatArg1 = CRequestorBase::EFormatApplication;
			break;
			case 2:
			reqFormatArg1 = CRequestorBase::EFormatTelephone;
			break;
			case 3:
			reqFormatArg1 = CRequestorBase::EFormatUrl;
			break;
			case 4:
			reqFormatArg1 = CRequestorBase::EFormatMail;
			break;			
			
		    }
		
		CRequestor* requestor = CRequestor::New(reqTypeArg1,reqFormatArg1,reqDataApplication1);
		requestor->SetRequestorL(reqTypeArg1,reqFormatArg1,reqDataApplication1);
		TPtrC reqDataApplication2 = requestor->RequestorData();
		if(reqDataApplication2==reqDataApplication1)
		    {
		        return KErrNone;
		    }
		else
		    return KErrGeneral;
		
		
    }
    
    
    
// ---------------------------------------------------------------------------
// Test case for  getting requestor type
// ---------------------------------------------------------------------------
TInt TTestRequestor ::GetRequestorTypeL(CStifItemParser& aItem)
    {
        TInt reqApplicationType;
	    TInt reqApplicatonFormat;
	    TPtrC reqDataApplication1;
	    CRequestorBase::TRequestorFormat reqFormatArg1 = CRequestorBase::EFormatUnknown;
	    CRequestorBase::TRequestorType reqTypeArg1 = CRequestorBase::ERequestorUnknown;
	    User::LeaveIfError(aItem.GetNextInt(reqApplicationType));
    	User::LeaveIfError(aItem.GetNextInt(reqApplicatonFormat));
    	User::LeaveIfError(aItem.GetNextString(reqDataApplication1));
    	switch(reqApplicationType)
    	{
    			case 0:
    			reqTypeArg1 = CRequestorBase::ERequestorUnknown;  
    			break;
    			case 1:
    			reqTypeArg1 = CRequestorBase::ERequestorService;  
    			break;
    			case 2:
    			reqTypeArg1 = CRequestorBase::ERequestorContact;  
    			break;
		}
			
		switch(reqApplicatonFormat)
		    {
			case 0:
			reqFormatArg1 = CRequestorBase::EFormatUnknown;  
			break;
			case 1:
			reqFormatArg1 = CRequestorBase::EFormatApplication;
			break;
			case 2:
			reqFormatArg1 = CRequestorBase::EFormatTelephone;
			break;
			case 3:
			reqFormatArg1 = CRequestorBase::EFormatUrl;
			break;
			case 4:
			reqFormatArg1 = CRequestorBase::EFormatMail;
			break;			
			
		    }
		
		CRequestor* requestor = CRequestor::New(reqTypeArg1,reqFormatArg1,reqDataApplication1);
		requestor->SetRequestorL(reqTypeArg1,reqFormatArg1,reqDataApplication1);
		TInt reqAppType = requestor->RequestorType();
		if(reqTypeArg1==reqAppType)
		    {
		        return KErrNone;
		    }
		else
		    return KErrGeneral;
		
		
    }
  
  
  
// ---------------------------------------------------------------------------
// Test case for  getting requestor format
// ---------------------------------------------------------------------------
TInt TTestRequestor ::GetRequestorFormatL(CStifItemParser& aItem)
    {
        TInt reqApplicationType;
	    TInt reqApplicatonFormat;
	    TPtrC reqDataApplication1;
	    CRequestorBase::TRequestorFormat reqFormatArg1 = CRequestorBase::EFormatUnknown;
	    CRequestorBase::TRequestorType reqTypeArg1 = CRequestorBase::ERequestorUnknown;
	    User::LeaveIfError(aItem.GetNextInt(reqApplicationType));
    	User::LeaveIfError(aItem.GetNextInt(reqApplicatonFormat));
    	User::LeaveIfError(aItem.GetNextString(reqDataApplication1));
    	switch(reqApplicationType)
    	{
    			case 0:
    			reqTypeArg1 = CRequestorBase::ERequestorUnknown;  
    			break;
    			case 1:
    			reqTypeArg1 = CRequestorBase::ERequestorService;  
    			break;
    			case 2:
    			reqTypeArg1 = CRequestorBase::ERequestorContact;  
    			break;
		}
			
		switch(reqApplicatonFormat)
		    {
			case 0:
			reqFormatArg1 = CRequestorBase::EFormatUnknown;  
			break;
			case 1:
			reqFormatArg1 = CRequestorBase::EFormatApplication;
			break;
			case 2:
			reqFormatArg1 = CRequestorBase::EFormatTelephone;
			break;
			case 3:
			reqFormatArg1 = CRequestorBase::EFormatUrl;
			break;
			case 4:
			reqFormatArg1 = CRequestorBase::EFormatMail;
			break;			
			
		    }
		
		CRequestor* requestor = CRequestor::New(reqTypeArg1,reqFormatArg1,reqDataApplication1);
		requestor->SetRequestorL(reqTypeArg1,reqFormatArg1,reqDataApplication1);
		TInt reqAppFormat = requestor->RequestorFormat();
		if(reqFormatArg1==reqAppFormat)
		    {
		        return KErrNone;
		    }
		else
		    return KErrGeneral;
		
		
    }
    
    
    
// ---------------------------------------------------------------------------
// Test case for  CRequestor::New
// ---------------------------------------------------------------------------
TInt TTestRequestor ::TestRequestorNew(CStifItemParser& aItem)
    {
        TInt reqApplicationType;
	    TInt reqApplicatonFormat;
	    TPtrC reqDataApplication1;
	    CRequestorBase::TRequestorFormat reqFormatArg1 = CRequestorBase::EFormatUnknown;
	    CRequestorBase::TRequestorType reqTypeArg1= CRequestorBase::ERequestorUnknown;
	    TPtrC reqDataApplication2;
	    CRequestorBase::TRequestorFormat reqFormatArg2;
	    CRequestorBase::TRequestorType reqTypeArg2 = CRequestorBase::ERequestorUnknown;
	    User::LeaveIfError(aItem.GetNextInt(reqApplicationType));
    	User::LeaveIfError(aItem.GetNextInt(reqApplicatonFormat));
    	User::LeaveIfError(aItem.GetNextString(reqDataApplication1));
    	//TPtrC reqDataApplication = GetDataL(aItem);	
    
    	switch(reqApplicationType)
    		{
    			case 0:
    			reqTypeArg1 = CRequestorBase::ERequestorUnknown;  
    			break;
    			case 1:
    			reqTypeArg1 = CRequestorBase::ERequestorService;  
    			break;
    			case 2:
    			reqTypeArg1 = CRequestorBase::ERequestorContact;  
    			break;
		}
			switch(reqApplicatonFormat)
		{
			case 0:
			reqFormatArg1 = CRequestorBase::EFormatUnknown;  
			break;
			case 1:
			reqFormatArg1 = CRequestorBase::EFormatApplication;
			break;
			case 2:
			reqFormatArg1 = CRequestorBase::EFormatTelephone;
			break;
			case 3:
			reqFormatArg1 = CRequestorBase::EFormatUrl;
			break;
			case 4:
			reqFormatArg1 = CRequestorBase::EFormatMail;
			break;			
			
		}
		
		CRequestor* requestor = CRequestor::New(reqTypeArg1,reqFormatArg1,reqDataApplication1);
		
		requestor->GetRequestor(reqTypeArg2,reqFormatArg2,reqDataApplication2);
		if((reqTypeArg2==reqTypeArg1)&&(reqFormatArg2==reqFormatArg1)
		    &&(reqDataApplication2==reqDataApplication1))
		    {   
		        delete requestor;
		        return KErrNone;
		    }
		else
		    
		    return KErrGeneral;
    	
    	
    }
    
    
 // ---------------------------------------------------------------------------
// Test case for  CRequestor::NewL
// ---------------------------------------------------------------------------
TInt TTestRequestor ::TestRequestorNewL(CStifItemParser& aItem)
    {
        TInt reqApplicationType;
	    TInt reqApplicatonFormat;
	    TPtrC reqDataApplication1;
	    CRequestorBase::TRequestorFormat reqFormatArg1 = CRequestorBase::EFormatUnknown;
	    CRequestorBase::TRequestorType reqTypeArg1= CRequestorBase::ERequestorUnknown;
	    TPtrC reqDataApplication2;
	    CRequestorBase::TRequestorFormat reqFormatArg2;
	    CRequestorBase::TRequestorType reqTypeArg2 = CRequestorBase::ERequestorUnknown;
	    User::LeaveIfError(aItem.GetNextInt(reqApplicationType));
    	User::LeaveIfError(aItem.GetNextInt(reqApplicatonFormat));
    	User::LeaveIfError(aItem.GetNextString(reqDataApplication1));
    	//TPtrC reqDataApplication = GetDataL(aItem);	
    
    	switch(reqApplicationType)
    		{
    			case 0:
    			reqTypeArg1 = CRequestorBase::ERequestorUnknown;  
    			break;
    			case 1:
    			reqTypeArg1 = CRequestorBase::ERequestorService;  
    			break;
    			case 2:
    			reqTypeArg1 = CRequestorBase::ERequestorContact;  
    			break;
		}
			switch(reqApplicatonFormat)
		{
			case 0:
			reqFormatArg1 = CRequestorBase::EFormatUnknown;  
			break;
			case 1:
			reqFormatArg1 = CRequestorBase::EFormatApplication;
			break;
			case 2:
			reqFormatArg1 = CRequestorBase::EFormatTelephone;
			break;
			case 3:
			reqFormatArg1 = CRequestorBase::EFormatUrl;
			break;
			case 4:
			reqFormatArg1 = CRequestorBase::EFormatMail;
			break;			
			
		}
		
		CRequestor* requestor = CRequestor::NewL(reqTypeArg1,reqFormatArg1,reqDataApplication1);
		
		requestor->GetRequestor(reqTypeArg2,reqFormatArg2,reqDataApplication2);
		if((reqTypeArg2==reqTypeArg1)&&(reqFormatArg2==reqFormatArg1)
		    &&(reqDataApplication2==reqDataApplication1))
		    {   
		        delete requestor;
		        return KErrNone;
		    }
		else
		    
		    return KErrGeneral;
    	
    	
    }
    
    
     
 // ---------------------------------------------------------------------------
// Test case for  CRequestor::NewLC
// ---------------------------------------------------------------------------
TInt TTestRequestor ::TestRequestorNewLC(CStifItemParser& aItem)
    {
        TInt reqApplicationType;
	    TInt reqApplicatonFormat;
	    TPtrC reqDataApplication1;
	    CRequestorBase::TRequestorFormat reqFormatArg1 = CRequestorBase::EFormatUnknown;
	    CRequestorBase::TRequestorType reqTypeArg1= CRequestorBase::ERequestorUnknown;
	    TPtrC reqDataApplication2;
	    CRequestorBase::TRequestorFormat reqFormatArg2;
	    CRequestorBase::TRequestorType reqTypeArg2 = CRequestorBase::ERequestorUnknown;
	    User::LeaveIfError(aItem.GetNextInt(reqApplicationType));
    	User::LeaveIfError(aItem.GetNextInt(reqApplicatonFormat));
    	User::LeaveIfError(aItem.GetNextString(reqDataApplication1));
    	//TPtrC reqDataApplication = GetDataL(aItem);	
    
    	switch(reqApplicationType)
    		{
    			case 0:
    			reqTypeArg1 = CRequestorBase::ERequestorUnknown;  
    			break;
    			case 1:
    			reqTypeArg1 = CRequestorBase::ERequestorService;  
    			break;
    			case 2:
    			reqTypeArg1 = CRequestorBase::ERequestorContact;  
    			break;
		}
			switch(reqApplicatonFormat)
		{
			case 0:
			reqFormatArg1 = CRequestorBase::EFormatUnknown;  
			break;
			case 1:
			reqFormatArg1 = CRequestorBase::EFormatApplication;
			break;
			case 2:
			reqFormatArg1 = CRequestorBase::EFormatTelephone;
			break;
			case 3:
			reqFormatArg1 = CRequestorBase::EFormatUrl;
			break;
			case 4:
			reqFormatArg1 = CRequestorBase::EFormatMail;
			break;			
			
		}
		
		CRequestor* requestor = CRequestor::NewLC(reqTypeArg1,reqFormatArg1,reqDataApplication1);
		
		requestor->GetRequestor(reqTypeArg2,reqFormatArg2,reqDataApplication2);
		if((reqTypeArg2==reqTypeArg1)&&(reqFormatArg2==reqFormatArg1)
		    &&(reqDataApplication2==reqDataApplication1))
		    {   
		        CleanupStack::PopAndDestroy(requestor);
		        return KErrNone;
		    }
		else
		    
		    return KErrGeneral;
    	
    	
    }   
    
 
// ---------------------------------------------------------------------------
// Test case for  CRequestor::NewL with RReadStream instance 
// ---------------------------------------------------------------------------

TInt TTestRequestor ::TestRequestorNewL1(CStifItemParser& aItem)
    {
           TInt reqApplicationType;
    	    TInt reqApplicatonFormat;
    	    TPtrC reqDataApplication1;
    	    CRequestorBase::TRequestorFormat reqFormatArg1 = CRequestorBase::EFormatUnknown;
    	    CRequestorBase::TRequestorType reqTypeArg1= CRequestorBase::ERequestorUnknown;
    	    TPtrC reqDataApplication2;
    	    CRequestorBase::TRequestorFormat reqFormatArg2;
    	    CRequestorBase::TRequestorType reqTypeArg2 = CRequestorBase::ERequestorUnknown;
    	    User::LeaveIfError(aItem.GetNextInt(reqApplicationType));
        	User::LeaveIfError(aItem.GetNextInt(reqApplicatonFormat));
        	User::LeaveIfError(aItem.GetNextString(reqDataApplication1));
        	//TPtrC reqDataApplication = GetDataL(aItem);	
        
        	switch(reqApplicationType)
        		{
        			case 0:
        			reqTypeArg1 = CRequestorBase::ERequestorUnknown;  
        			break;
        			case 1:
        			reqTypeArg1 = CRequestorBase::ERequestorService;  
        			break;
        			case 2:
        			reqTypeArg1 = CRequestorBase::ERequestorContact;  
        			break;
    		}
    			switch(reqApplicatonFormat)
    		{
    			case 0:
    			reqFormatArg1 = CRequestorBase::EFormatUnknown;  
    			break;
    			case 1:
    			reqFormatArg1 = CRequestorBase::EFormatApplication;
    			break;
    			case 2:
    			reqFormatArg1 = CRequestorBase::EFormatTelephone;
    			break;
    			case 3:
    			reqFormatArg1 = CRequestorBase::EFormatUrl;
    			break;
    			case 4:
    			reqFormatArg1 = CRequestorBase::EFormatMail;
    			break;			
    			
    		}
    		
    	const TInt KPosBufFlatExpandSize = 100;	
    	CBufFlat* bufFlat = CBufFlat::NewL(KPosBufFlatExpandSize);
        CleanupStack::PushL(bufFlat); 
        RBufWriteStream  wStream(*bufFlat);
        
        CleanupClosePushL(wStream); 
        	CRequestor* requestor1 = CRequestor::NewL(reqTypeArg1,reqFormatArg1,reqDataApplication1);
        requestor1->ExternalizeL(wStream);
        RBufReadStream rstream(*bufFlat);
        CleanupClosePushL(rstream); 
        	CRequestor* requestor = CRequestor::NewL(rstream);
        		requestor->GetRequestor(reqTypeArg2,reqFormatArg2,reqDataApplication2);
        		delete requestor;
        		delete requestor1;
        		CleanupStack::PopAndDestroy(bufFlat);
    		if((reqTypeArg2==reqTypeArg1)&&(reqFormatArg2==reqFormatArg1)
    		    &&(reqDataApplication2==reqDataApplication1))
    		    {   
    		        
    		        //CleanupStack::PopAndDestroy(requestor);
    		        return KErrNone;
    		    }
    		else
    		    
    		    return KErrGeneral;
    }

// ---------------------------------------------------------------------------
// Test case for  CRequestor::ExtendedInterface 
// ---------------------------------------------------------------------------
TInt TTestRequestor::TestExtendedInterface()
	{
	CTestRequestorBase* req = new(ELeave)CTestRequestorBase();
	TInt err = req->TestExtendedInterface();
	delete req;
	return err;
	}
	
// ---------------------------------------------------------------------------
// Test case for  CTestRequestorBase::ExtendedInterface 
// ---------------------------------------------------------------------------
TInt CTestRequestorBase::TestExtendedInterface()
	{
	ExtendedInterface(0,NULL,NULL);
	return KErrNone;
	}
