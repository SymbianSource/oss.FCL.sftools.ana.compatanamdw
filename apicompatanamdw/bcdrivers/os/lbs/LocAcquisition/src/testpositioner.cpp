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
* Description:  Test Class For RPositioner
*
*/


// System Includes


// User Includes
#include "testpositioner.h"


// Constant Declarations

    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ Default Constructor
// ---------------------------------------------------------------------------
//
CTestPositioner::CTestPositioner(CStifLogger* aLog)
    :CActive(0),iLog(aLog)
    {
    CActiveScheduler::Add(this);
    }

// ---------------------------------------------------------------------------
// C++ Destructor
// ---------------------------------------------------------------------------
//
CTestPositioner::~CTestPositioner()
    {
      if( IsActive() )
	      {
	      Cancel(); 	
	      }
    }

// ---------------------------------------------------------
// CTestPositioner::RunL 
//
// RunL to Handle Completed Request
// ---------------------------------------------------------
//
void CTestPositioner::RunL()
	{
	if(iStatus != KErrCancel)	
		{
		iLog->Log(_L("RunL %d"),iStatus.Int());		
		CActiveScheduler::Stop();				
		}
	}
	
// ---------------------------------------------------------
// CTestPositioner::DoCancel 
//
// To Handle Cancel Request
// ---------------------------------------------------------
//	
void CTestPositioner::DoCancel()
	{
	switch(iState)
		{
			case EGetLastKnownPosition: 
				iPositioner.CancelRequest(EPositionerGetLastKnownPosition);
			break;
			case EPositionInfo: 
				iPositioner.CancelRequest(EPositionerNotifyPositionUpdate);
			break;
		}
	
	iState = ENone;
	iLog->Log(_L("CancelL %d"),iStatus.Int());
	}

// ---------------------------------------------------------
// CTestPositionServer::DoCancel 
//
// To Cancel the Outstanding Request
// ---------------------------------------------------------
//		
TInt CTestPositioner::CancelRequest()
	{
	TInt err = KErrNone;
	switch(iState)
		{
			case EGetLastKnownPosition: 
				err = iPositioner.CancelRequest(EPositionerGetLastKnownPosition);
			break;
			case EPositionInfo: 
				err = iPositioner.CancelRequest(EPositionerNotifyPositionUpdate);
			break;
		}
	
	iState = ENone;
	iLog->Log(_L("CancelL %d"),err);		
	
	return err;
	}

// ---------------------------------------------------------
// CTestPositioner::DoCancel 
//
// To Handle Error in RunL
// ---------------------------------------------------------
//
TInt CTestPositioner::RunError(TInt aError)
	{
	iLog->Log(_L("Leave in RunL %d"),aError);
	return aError;
	}
	
// ---------------------------------------------------------
// CTestPositioner::Connect
//
// (other items are commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositioner::Connect()
	{
	TInt err = iPosServer.Connect();
	if(err != KErrNone)
		{
		TBuf<100> msg;
		msg.Copy(_L("Position server connect failed with error code :"));
		msg.AppendNum(err);	  
		iLog->Log(msg); 	  	
		}
	else
		{
		iLog->Log(_L("Position Server connect - passed")); 	
		}  
	return err;
	}	
  
// ---------------------------------------------------------
// CTestPositioner::Disconnect
//
// (other items are commented in a header).
// ---------------------------------------------------------
//
void CTestPositioner::Disconnect()
    {
    iPosServer.Close();
    iLog->Log(_L("Closing Position Server - passed")); 
    }
    
// ---------------------------------------------------------
// CTestPositioner::OpenPositionerResolver
//
// (other items are commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositioner::OpenPositionerResolver(RPositionServer& aPosServer, CStifItemParser& aItem )
	{
	TUid PsyUid;
	TUint PsyUidInInt;

	TInt err;
	iPosServer = aPosServer;
	
	//Get the PSYUid from the Stif framework
	if( aItem.GetNextInt(PsyUidInInt, EHex) != KErrNotFound )
		{
		PsyUid.iUid = PsyUidInInt;
		err = OpenPositionerById(iPosServer, PsyUid);
		}
	else  
		err = OpenPositioner(iPosServer);

	return err;
	}
    
// ---------------------------------------------------------
// CTestPositioner::OpenPositioner
//
// (other items are commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositioner::OpenPositioner(RPositionServer& aPosServer)
	{
	TInt err;
	iPosServer = aPosServer;

	err = iPositioner.Open(iPosServer);
	
	if(err != KErrNone)
		{
		TBuf<100> msg;
		msg.Copy(_L("OpenPositioner failed with error code :"));
		msg.AppendNum(err);	  
		iLog->Log(msg); 	  	
		}
	else
		{
		iLog->Log(_L("OpenPositioner - passed")); 	
		}  
 
	return err;
	}

// ---------------------------------------------------------
// CTestPositioner::OpenPositionerById
//
// (other items are commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositioner::OpenPositionerById(RPositionServer& aPosServer, const TUid aPsyUid)
  {
  iPosServer = aPosServer;
  TInt err = iPositioner.Open(iPosServer, aPsyUid);
  if(err != KErrNone)
	  {
	  TBuf<100> msg;
	  msg.Copy(_L("OpenPositionerByName failed with error code :"));
	  msg.AppendNum(err);	  
	  iLog->Log(msg); 	  	
	  }
	else
		{
		iLog->Log(_L("OpenPositionerByName passed")); 	
		}  

  return err;
  }
  
// ---------------------------------------------------------
// CTestPositioner::OpenPositionerByCriteria
//
// (other items are commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositioner::OpenPositionerByCriteria(RPositionServer& aPosServer)
  {
  TPositionCriteria criteria;
  
  iPosServer = aPosServer;
  TInt err = iPositioner.Open(iPosServer, criteria);
  if(err != KErrNone)
	  {
	  TBuf<100> msg;
	  msg.Copy(_L("OpenPositionerByCriteria failed with error code :"));
	  msg.AppendNum(err);	  
	  iLog->Log(msg); 	  	
	  }
	else
		{
		iLog->Log(_L("OpenPositionerByCriteria passed")); 	
		}  

  return err;
  }

// ---------------------------------------------------------
// CTestPositioner::ClosePositioner
//
// (other items are commented in a header).
// ---------------------------------------------------------
//
void CTestPositioner::ClosePositioner()
    {
    iPositioner.Close();
    iLog->Log(_L("ClosePositioner - passed"));     
    }  
    
// ---------------------------------------------------------
// CTestPositioner::SetRequestor
//
// (other items are commented in a header).
// ---------------------------------------------------------
//	
TInt CTestPositioner::SetRequestor( TInt aType,
			TInt aFormat,const TDesC &  aData )
    {   
	
	CRequestorBase::_TRequestorFormat reqFormat = CRequestorBase::EFormatUnknown;
	CRequestorBase::_TRequestorType reqType = CRequestorBase::ERequestorUnknown;

	switch(aType)
		{
			case 0:
			reqType = CRequestorBase::ERequestorUnknown;  
			break;
			case 1:
			reqType = CRequestorBase::ERequestorService;  
			break;
			case 2:
			reqType = CRequestorBase::ERequestorContact;  
			break;
		}
	    
	switch(aFormat)
		{
			case 0:
			reqFormat = CRequestorBase::EFormatUnknown;  
			break;
			case 1:
			reqFormat = CRequestorBase::EFormatApplication;
			break;
			case 2:
			reqFormat = CRequestorBase::EFormatTelephone;
			break;
			case 3:
			reqFormat = CRequestorBase::EFormatUrl;
			break;
			case 4:
			reqFormat = CRequestorBase::EFormatMail;
			break;			
			
		}

     TInt err = iPositioner.SetRequestor(reqType,reqFormat, aData);
	 TBuf<100> msg;                           
   	 if(err != KErrNone)
	    {	  
	    msg.Copy(_L("SetRequestor returned with error code :"));
	    msg.AppendNum(err);	  
	    iLog->Log(msg); 	  	
	    }
	 else
		{				
		msg.Copy(_L("SetRequestor - passed"));		
		iLog->Log(msg); 	
		}  	
                           
  	return err;
    }      

// ---------------------------------------------------------
// CTestPositioner::SetRequestorStackL
//
// (other items are commented in a header).
// ---------------------------------------------------------
//	
TInt CTestPositioner::SetRequestorStackL( CStifItemParser& aItem )
	{
	TPtrC data;
	RRequestorStack stack = RRequestorStack();	
	if( aItem.GetNextString(data) != KErrNotFound )
		{
	    CRequestor* serviceId1 = 
			CRequestor::NewL(CRequestor::ERequestorService, CRequestor::EFormatApplication, 
	                    data);

	    CleanupStack::PushL(serviceId1);

	    stack.Append(serviceId1);
	    
	    CleanupStack::Pop(serviceId1);
		
		}

    TInt err = iPositioner.SetRequestor(stack);

	TBuf<100> msg;                           
   	if(err != KErrNone)
	   	{	  
	   	msg.Copy(_L("SetRequestorStack returned with error code :"));
	   	msg.AppendNum(err);	  
	   	iLog->Log(msg); 	  	
	   	}
	else
		{				
		msg.Copy(_L("SetRequestorStack - passed"));		
		iLog->Log(msg); 	
		}  	
                           
  	return err;
    }   

// ---------------------------------------------------------
// CTestPositioner::SetUpdateOp
//
// (other items are commented in a header).
// ---------------------------------------------------------
//	
TInt CTestPositioner::SetUpdateOp(TInt aInterval,TInt aTimeOut,TInt aAge)
	{
	TPositionUpdateOptions updateOption(aInterval,aTimeOut,aAge);
	TInt err = iPositioner.SetUpdateOptions(updateOption);
	TBuf<100> msg;   
   	if(err != KErrNone)
	    {	  
	    msg.Copy(_L("SetUpdateOptions returned with error code :"));
	    msg.AppendNum(err);	  
	    iLog->Log(msg); 	  	
	    }
	 else
		{				
		msg.Copy(_L("SetUpdateOptions - passed"));		
		iLog->Log(msg); 	
		}  	

	return err;	
	} 

// ---------------------------------------------------------
// CTestPositioner::GetUpdateOp
//
// (other items are commented in a header).
// ---------------------------------------------------------
//	
TInt CTestPositioner::GetUpdateOp(TInt aInterval,TInt aTimeOut,TInt aAge)
	{
	TPositionUpdateOptions updateOption;
	TInt err = iPositioner.GetUpdateOptions(updateOption);
	
	TBuf<100> msg;   
   	if(err == KErrNone && updateOption.UpdateInterval() == aInterval &&
   			updateOption.UpdateTimeOut() == aTimeOut &&
   			updateOption.MaxUpdateAge() == aAge )
	    {	
		msg.Copy(_L("GetUpdateOptions passed"));		
		iLog->Log(msg); 	      	  	
	    }
	 else
		{				
	    msg.Copy(_L("GetUpdateOptions returned with error code :"));
	    msg.AppendNum(err);	  
	    iLog->Log(msg); 
		}  	
	
	return err;
		
	}

// ---------------------------------------------------------
// CTestPositioner::GetLastKnownPostionResolverL
//
// (other items are commented in a header).
// ---------------------------------------------------------
//		
TInt CTestPositioner::GetLastKnownPostionResolverL( CStifItemParser& aItem )
	{
	TInt choice;
	TInt err = KErrNone;
	TPositionInfo Posinfo;
	HPositionGenericInfo* Posinfo1;
	
	User::LeaveIfError(aItem.GetNextInt(choice));
	iState = EGetLastKnownPosition;
	
	switch(choice)
		{
			case 0:
			err = GetLastKnownPostionL(&Posinfo);
			break;
			case 1:
			Posinfo1 = HPositionGenericInfo::NewLC(); // default sizes
			err = GetLastKnownPostionL(Posinfo1);
			CleanupStack::PopAndDestroy(Posinfo1);
			break;
			case 2:
			Posinfo1 = HPositionGenericInfo::NewLC(); // default sizes
			TPositionFieldId fieldList1[3];
			fieldList1[0] = EPositionFieldDistrict;
			fieldList1[1] = EPositionFieldNMEASentences;
			fieldList1[2] = EPositionFieldNone;	
			
			Posinfo1->SetRequestedFields(fieldList1);
			err = GetLastKnownPostionL(Posinfo1);
			CleanupStack::PopAndDestroy(Posinfo1);
			break;			
		}
	return err;
	}

// ---------------------------------------------------------
// CTestPositioner::GetLastKnownPostion
//
// (other items are commented in a header).
// ---------------------------------------------------------
//		
TInt CTestPositioner::GetLastKnownPostionL(TPositionInfoBase *aPosInfo)
	{
	iPositioner.GetLastKnownPosition(*aPosInfo,iStatus);
	SetActive();
	iLog->Log(_L("Started RunSession with status %d"),iStatus.Int());
	
	CActiveScheduler::Start();
	
	TBuf<100> msg;   
   	if(iStatus.Int() != KErrNone)
	    {	  
	    msg.Copy(_L("GetLastKnownPosition returned with error code :"));
	    msg.AppendNum(iStatus.Int());	  
	    iLog->Log(msg); 	  	
	    }
	 else
		{				
		msg.Copy(_L("GetLastKnownPosition passed"));		
		iLog->Log(msg); 	
		}  	
	return iStatus.Int();
	}

// ---------------------------------------------------------
// CTestPositioner::GetLastKnownPostionCancelResolverL
//
// (other items are commented in a header).
// ---------------------------------------------------------
//		
TInt CTestPositioner::GetLastKnownPostionCancelResolverL( CStifItemParser& aItem )
	{
	TInt choice;
	TInt err = KErrNone;
	TPositionInfo Posinfo;
	HPositionGenericInfo* Posinfo1;
	
	User::LeaveIfError(aItem.GetNextInt(choice));
	iState = EGetLastKnownPosition;
	
	switch(choice)
		{
			case 0:
			err = GetLastKnownPostionCancel(&Posinfo);
			break;
			case 1:
			Posinfo1 = HPositionGenericInfo::NewLC(); // default sizes
			err = GetLastKnownPostionCancel(Posinfo1);
			CleanupStack::PopAndDestroy(Posinfo1);
			break;
			case 2:
			Posinfo1 = HPositionGenericInfo::NewLC(); // default sizes
			TPositionFieldId fieldList1[3];
			fieldList1[0] = EPositionFieldDistrict;
			fieldList1[1] = EPositionFieldNMEASentences;
			fieldList1[2] = EPositionFieldNone;	
			
			Posinfo1->SetRequestedFields(fieldList1);
			err = GetLastKnownPostionCancel(Posinfo1);
			CleanupStack::PopAndDestroy(Posinfo1);
			break;			
		}
	return err;
	}

// ---------------------------------------------------------
// CTestPositioner::GetLastKnownPostionCancel
//
// (other items are commented in a header).
// ---------------------------------------------------------
//		
TInt CTestPositioner::GetLastKnownPostionCancel(TPositionInfoBase *aPosInfo)
	{
	iPositioner.GetLastKnownPosition(*aPosInfo,iStatus);
	SetActive();
	iLog->Log(_L("Started RunSession with status %d"),iStatus.Int());
	
	iState = EGetLastKnownPosition;
	Cancel();

	iState = ENone;	
	TBuf<100> msg;   
   	if(iStatus.Int() != KErrNone)
	    {	  
	    msg.Copy(_L("GetLastKnownPostionCancel returned with error code :"));
	    msg.AppendNum(iStatus.Int());	  
	    iLog->Log(msg); 	  	
	    }
	 else
		{				
		msg.Copy(_L("GetLastKnownPostionCancel passed"));		
		iLog->Log(msg); 	
		}  	
	return iStatus.Int();
	}

// ---------------------------------------------------------
// CTestPositioner::GetPositionInfoResolverL
//
// (other items are commented in a header).
// ---------------------------------------------------------
//		
TInt CTestPositioner::GetPositionInfoResolverL( CStifItemParser& aItem )
	{
	TInt choice;
	TInt err = KErrNone;
	TPositionInfo Posinfo;
	HPositionGenericInfo* Posinfo1;
	
	User::LeaveIfError(aItem.GetNextInt(choice));
	iState = EPositionInfo;
	
	switch(choice)
		{
			case 0:
				err = GetPositionInfoL(&Posinfo);
			break;
			case 1:
				Posinfo1 = HPositionGenericInfo::NewLC(); // default sizes
				err = GetPositionInfoL(Posinfo1);
				CleanupStack::PopAndDestroy(Posinfo1);
			break;
			case 2:
				Posinfo1 = HPositionGenericInfo::NewLC(); // default sizes
				TPositionFieldId fieldList1[3];
				fieldList1[0] = EPositionFieldDistrict;
				fieldList1[1] = EPositionFieldNMEASentences;
				fieldList1[2] = EPositionFieldNone;	
				
				Posinfo1->SetRequestedFields(fieldList1);
				err = GetPositionInfoL(Posinfo1);
				CleanupStack::PopAndDestroy(Posinfo1);
			break;	
			case 3:
				TPositionInfo Posinfo1;
				GetPositionInfoPanicDuplicate(&Posinfo1);
			break;		
		}
	return err;
	}
	
// ---------------------------------------------------------
// CTestPositioner::GetPositionInfoL
//
// (other items are commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositioner::GetPositionInfoL( TPositionInfoBase *aPosInfo )
	{
	iPositioner.NotifyPositionUpdate(*aPosInfo,iStatus);
	SetActive();
	iLog->Log(_L("Started RunSession with status %d"),iStatus.Int());
	
	CActiveScheduler::Start();
	
	TBuf<100> msg;   
   	if(iStatus.Int() != KErrNone)
	    {	  
	    msg.Copy(_L("NotifyPositionUpdate returned with error code :"));
	    msg.AppendNum(iStatus.Int());	  
	    iLog->Log(msg); 	  	
	    }
	 else
		{				
		msg.Copy(_L("NotifyPositionUpdate passed"));		
		iLog->Log(msg); 	
		}  	
	return iStatus.Int();

	}
	
// ---------------------------------------------------------
// CTestPositioner::GetPositionInfoPanicDuplicate
//
// (other items are commented in a header).
// ---------------------------------------------------------
//
void CTestPositioner::GetPositionInfoPanicDuplicate( TPositionInfoBase *aPosInfo )
	{
    // Asynchronous module status
    iPositioner.NotifyPositionUpdate(*aPosInfo,iStatus);
    SetActive();
    TRequestStatus status;
	iPositioner.NotifyPositionUpdate(*aPosInfo,status);
	User::WaitForRequest(status);

	}	
	
// ---------------------------------------------------------
// CTestPositioner::GetPositionInfoCancelResolverL
//
// (other items are commented in a header).
// ---------------------------------------------------------
//		
TInt CTestPositioner::GetPositionInfoCancelResolverL( CStifItemParser& aItem )
	{
	TInt choice;
	TInt err = KErrNone;
	TPositionInfo Posinfo;
	HPositionGenericInfo* Posinfo1;
	
	User::LeaveIfError(aItem.GetNextInt(choice));
	iState = EPositionInfo;
	
	switch(choice)
		{
			case 0:
			err = GetPositionInfoCancelL(&Posinfo);
			break;
			case 1:
			Posinfo1 = HPositionGenericInfo::NewLC(); // default sizes
			err = GetPositionInfoCancelL(Posinfo1);
			CleanupStack::PopAndDestroy(Posinfo1);
			break;
			case 2:
			Posinfo1 = HPositionGenericInfo::NewLC(); // default sizes
			TPositionFieldId fieldList1[3];
			fieldList1[0] = EPositionFieldDistrict;
			fieldList1[1] = EPositionFieldNMEASentences;
			fieldList1[2] = EPositionFieldNone;	
			
			Posinfo1->SetRequestedFields(fieldList1);
			err = GetPositionInfoCancelL(Posinfo1);
			CleanupStack::PopAndDestroy(Posinfo1);
			break;			
		}
	return err;
	}
	
// ---------------------------------------------------------
// CTestPositioner::GetPositionInfoCancelL
//
// (other items are commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositioner::GetPositionInfoCancelL( TPositionInfoBase *aPosInfo )
	{
	iPositioner.NotifyPositionUpdate(*aPosInfo,iStatus);
	SetActive();
	iLog->Log(_L("Started RunSession with status %d"),iStatus.Int());
	
	iState = EPositionInfo;
	Cancel();
	
	iState = ENone;
	TBuf<100> msg;   
   	if(iStatus.Int() != KErrNone)
	    {	  
	    msg.Copy(_L("GetPositionInfoCancelL returned with error code :"));
	    msg.AppendNum(iStatus.Int());	  
	    iLog->Log(msg); 	  	
	    }
	 else
		{				
		msg.Copy(_L("GetPositionInfoCancelL passed"));		
		iLog->Log(msg); 	
		}  	
	return iStatus.Int();

	}


// ---------------------------------------------------------
// CTestPositioner::ClosePosServerPanic
//
// (other items are commented in a header).
// ---------------------------------------------------------
//	
void CTestPositioner::ClosePosServerPanic(TPositionInfoBase *aPosInfo)
    {
   	iPositioner.NotifyPositionUpdate(*aPosInfo,iStatus);
	SetActive();
	
	iPositioner.Close();
    iLog->Log(_L("ClosePosServerPanic - passed"));	
	}	 

// ---------------------------------------------------------
// CTestPositioner::SetRequestStateL
//
// (other items were commented in a header).
// ---------------------------------------------------------
//	
void CTestPositioner::SetRequestStateL( CStifItemParser& aItem )
	{
	TInt state;
	User::LeaveIfError(aItem.GetNextInt(state));
	if(state == 0)
		iState = EGetLastKnownPosition;
	else
		iState = EPositionInfo;
	}	

// ---------------------------------------------------------
// CTestPositioner::TestExtendedInterface
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositioner::TestExtendedInterface()
	{
	ExtendedInterface(0,NULL,NULL);
	return KErrNone;
	}

// ---------------------------------------------------------
// CTestPositioner::DeleteLastKnownPostionCacheL
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositioner::DeleteLastKnownPostionCacheL()
    {
    _LIT(KCacheName,"LastKnownPos.dat");
	_LIT(KCachePath,"C:\\private\\101f97b2\\");	
    RFs FsSession;
	TParse name;
	TInt err = KErrNone;
	User::LeaveIfError(FsSession.Connect());
	FsSession.Parse(KCacheName,KCachePath,name);
	if(BaflUtils::FileExists(FsSession, name.FullName()))
    	{
    	HBufC* filename = HBufC::NewL(KCachePath().Length()+KCacheName().Length());
		filename->Des().Append(KCachePath);
		filename->Des().Append(KCacheName);
		CleanupStack::PushL(filename);
		
    	err = FsSession.Delete(*filename);
    	
    	CleanupStack::PopAndDestroy(filename);
    	}
    FsSession.Close();
    return err;
    }
  
