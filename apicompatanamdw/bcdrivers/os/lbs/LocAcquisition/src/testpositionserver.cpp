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
* Description:  Test Class For RPositionServer
*
*/


// System Includes


// User Includes
#include "testpositionserver.h"


// Constant Declarations

    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ Default Constructor
// ---------------------------------------------------------------------------
//
CTestPositionServer::CTestPositionServer(CStifLogger* aLog)
    :CActive(0),iLog(aLog)
    {
    CActiveScheduler::Add(this);
    }

// ---------------------------------------------------------------------------
// C++ Destructor
// ---------------------------------------------------------------------------
//
CTestPositionServer::~CTestPositionServer()
    {
      if( IsActive() )
	      {
	      Cancel(); 	
	      }
    }

// ---------------------------------------------------------
// CTestPositionServer::RunL 
//
// RunL to Handle Completed Request
// ---------------------------------------------------------
//	
void CTestPositionServer::RunL()
	{
	if(iStatus != KErrCancel)	
		{
		iLog->Log(_L("RunL %d"),iStatus.Int());		
		CActiveScheduler::Stop();				
		}
	}
	
// ---------------------------------------------------------
// CTestPositionServer::DoCancel 
//
// To Handle Cancel Request
// ---------------------------------------------------------
//	
void CTestPositionServer::DoCancel()
	{
	TInt err = iPosServer.CancelRequest(EPositionServerNotifyModuleStatusEvent);
	iLog->Log(_L("CancelL %d"),err);

	}

// ---------------------------------------------------------
// CTestPositionServer::CancelRequest 
//
// To Cancel the Outstanding Request
// ---------------------------------------------------------
//	
TInt CTestPositionServer::CancelRequest()
	{
	TInt err = iPosServer.CancelRequest(EPositionServerNotifyModuleStatusEvent);
	iLog->Log(_L("CancelL %d"),err);
	return err;
	}

// ---------------------------------------------------------
// CTestPositionServer::RunError 
//
// To Handle Error in RunL
// ---------------------------------------------------------
//
TInt CTestPositionServer::RunError(TInt aError)
	{
	iLog->Log(_L("Leave in RunL %d"),aError);
	return aError;
	}
	
// ---------------------------------------------------------
// CTestPositionServer::PositionServer
//
// (other items are commented in a header).
// ---------------------------------------------------------
//
RPositionServer& CTestPositionServer::PositionServer()
	{
	return iPosServer;
	}	
	
// ---------------------------------------------------------
// CTestPositionServer::Connect
//
// (other items are commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositionServer::Connect()
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
// CTestPositionServer::Disconnect
//
// (other items are commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositionServer::Disconnect()
    {
    iPosServer.Close();
    iLog->Log(_L("Closing Position Server - passed")); 
    return KErrNone;
    } 
  
// ---------------------------------------------------------
// CTestPositionServer::Disconnect
//
// (other items are commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositionServer::VersionCheck()
	{
	TVersion ver = iPosServer.Version();
	if(ver.iMajor == 1 && ver.iMinor == 0 && ver.iBuild == 0 )
		{
		iLog->Log(_L("Version numbers are Verified to be correct!"));	  	
		return KErrNone;
		}
	else
		{
		iLog->Log(_L("Wrong Version"));  
		return KErrGeneral;	
		}  
	}

// ---------------------------------------------------------
// CTestPositionServer::GetDefaultModule
//
// (other items are commented in a header).
// ---------------------------------------------------------
//	
TInt CTestPositionServer::GetDefaultModule()
	{
	TPositionModuleId moduleId;
	TInt err = iPosServer.GetDefaultModuleId(moduleId);
	TBuf<100> msg;
	
    if(err != KErrNone)
	    {	  
	    msg.Copy(_L("GetDefaultModule failed with error code :"));
	    msg.AppendNum(err);	  
	    iLog->Log(msg); 	  	
	    }
	else
		{
		msg.Copy(_L("GetDefaultModule passed Id of Module is:"));
		msg.AppendNumUC(moduleId.iUid, EHex);
		iLog->Log(msg); 	
		}  
	
	return err;

    }
	
// ---------------------------------------------------------
// CTestPositionServer::GetModuleNum
//
// (other items are commented in a header).
// ---------------------------------------------------------
//		
TInt CTestPositionServer::GetModuleNum()
	{
	TInt err;
	TUint number;

	err = iPosServer.GetNumModules(number);
	TBuf<100> msg;
	
    if(err != KErrNone)
	    {	  
	    msg.Copy(_L("GetModuleNumPanic failed with error code :"));
	    msg.AppendNum(err);	  
	    iLog->Log(msg); 	  	
	    }
	else
		{
		msg.Copy(_L("GetModuleNumPanic passed Number of Module is:"));
		msg.AppendNum(number);
		iLog->Log(msg); 	
		}  
	
	return err;
	}
    
// ---------------------------------------------------------
// CTestPositionServer::GetModuleInfoIndex
//
// (other items are commented in a header).
// ---------------------------------------------------------
//	
TInt CTestPositionServer::GetModuleInfoIndex(TInt aIndex)
	{
	TPositionModuleInfo infoModule;
	TInt err;
	err = iPosServer.GetModuleInfoByIndex(aIndex,infoModule);
	TBuf<100> msg;
	
    if(err != KErrNone)
	    {	  
	    msg.Copy(_L("GetModuleInfoByIndex failed with error code :"));
	    msg.AppendNum(err);	  
	    iLog->Log(msg); 	  	
	    }
	else
		{
		TBuf<100> moduleName;
		infoModule.GetModuleName(moduleName);
		msg.Copy(_L("GetModuleInfoByIndex passed Module Name is:"));
		msg.Append(moduleName);
		iLog->Log(msg); 	
		}  
	
	return err;
		
	}
	
// ---------------------------------------------------------
// CTestPositionServer::GetModuleInfoId
//
// (other items are commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositionServer::GetModuleInfoId(TPositionModuleId aUid)
	{
	TPositionModuleInfo infoModule;
	TInt err;

	err = iPosServer.GetModuleInfoById(aUid,infoModule);
	TBuf<100> msg;		
    if(err != KErrNone)
	    {	  
	    msg.Copy(_L("GetModuleInfoById failed with error code :"));
	    msg.AppendNum(err);	  
	    iLog->Log(msg); 	  	
	    }
	else
		{
		TBuf<100> moduleName;
		infoModule.GetModuleName(moduleName);
		msg.Copy(_L("GetModuleInfoById passed Module Name is:"));
		msg.Append(moduleName);
		iLog->Log(msg); 	
		}  	

	return err;
	
	}
	
// ---------------------------------------------------------
// CTestPositionServer::GetModuleStatus
//
// (other items are commented in a header).
// ---------------------------------------------------------
//	
TInt CTestPositionServer::GetModuleStatus(TPositionModuleId aUid)
	{
	TPositionModuleStatus moduleStatus;
	TInt err;
	TBuf<100> msg;	
	err = iPosServer.GetModuleStatus(moduleStatus,aUid);
   if(err != KErrNone)
	    {	  
	    msg.Copy(_L("GetModuleStatus failed with error code :"));
	    msg.AppendNum(err);	  
	    iLog->Log(msg); 	  	
	    }
	else
		{
		TBuf<20> intStatus;
		intStatus.Num(moduleStatus.DeviceStatus());
		msg.Copy(_L("GetModuleStatus passed Device Status is :"));
		msg.Append(intStatus);
		iLog->Log(msg); 	
		}  	
	return err;	
	
	}

// ---------------------------------------------------------
// CTestPositionServer::GetModuleChangeNotification
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositionServer::GetModuleChangeNotification(TInt aEvent, TPositionModuleId aUid)
	{
	TPositionModuleStatus moduleStatus;
	TPositionModuleStatusEventBase::_TModuleEvent event = TPositionModuleStatusEvent::EEventNone;

	//Setting of Event type according to aEvent parameter
    switch(aEvent) 
	    {
	    	case 0:
	    	event = TPositionModuleStatusEvent::EEventNone; 
	    	break;
			case 4:
	    	event = TPositionModuleStatusEvent::EEventAll; 
	    	break;	    	
	    }
    iModuleEvent.SetRequestedEvents(event);

    // Asynchronous module status
    iPosServer.NotifyModuleStatusEvent(iModuleEvent, iStatus, aUid);

    if(0 != aEvent)
    	{
		SetActive();
		TInt err = iPositioner.Open(iPosServer, aUid);
		CActiveScheduler::Start();

		iPositioner.Close();
    	}
	TBuf<100> msg;
	msg.Copy(_L("In GetModuleChangeNotificationErr1: NotifyModuleStatusEvent returned with :"));
	msg.AppendNum(iStatus.Int());
	iLog->Log(msg);
	return iStatus.Int();
}	

// ---------------------------------------------------------
// CTestPositionServer::GetModuleChangeNotificationCancel
//
// (other items were commented in a header).
// ---------------------------------------------------------
//	
TInt CTestPositionServer::GetModuleChangeNotificationCancel(TInt aEvent, TPositionModuleId aUid)
	{
	TPositionModuleStatus moduleStatus;
	TPositionModuleStatusEventBase::_TModuleEvent event = TPositionModuleStatusEvent::EEventNone;

	//Setting of Event type according to aEvent parameter
    switch(aEvent) 
	    {
	    	case 0:
	    	event = TPositionModuleStatusEvent::EEventNone; 
	    	break;
			case 4:
	    	event = TPositionModuleStatusEvent::EEventAll; 
	    	break;	    	
	    }
    iModuleEvent.SetRequestedEvents(event);

    // Asynchronous module status
    iPosServer.NotifyModuleStatusEvent(iModuleEvent, iStatus, aUid);
	SetActive();
	iLog->Log(_L("Started RunSession with status %d"),iStatus.Int());
	
  	Cancel();
  	
    TBuf<100> msg;
    msg.Copy(_L("In GetModuleChangeNotificationErr2: NotifyModuleStatusEvent returned with :"));
    msg.AppendNum(iStatus.Int());
    iLog->Log(msg);
	return iStatus.Int();
	}

// ---------------------------------------------------------
// CTestPositionServer::DisconnectPanicOutstanding
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CTestPositionServer::DisconnectPanicOutstanding(TInt aEvent, TPositionModuleId aUid)
{
	TPositionModuleStatus moduleStatus;
	TPositionModuleStatusEventBase::_TModuleEvent event = TPositionModuleStatusEvent::EEventNone;

	//Setting of Event type according to aEvent parameter
    switch(aEvent) 
	    {
	    	case 0:
	    	event = TPositionModuleStatusEvent::EEventNone; 
	    	break;
			case 4:
	    	event = TPositionModuleStatusEvent::EEventAll; 
	    	break;	    	
	    }
    iModuleEvent.SetRequestedEvents(event);

    // Asynchronous module status
    iPosServer.NotifyModuleStatusEvent(iModuleEvent, iStatus, aUid);
    SetActive();
        
    TBuf<100> msg;
    msg.Copy(_L("In DisconnectPanicOutstanding returned with :"));
    msg.AppendNum(iStatus.Int());
    iLog->Log(msg);
    iPosServer.Close();
}

// ---------------------------------------------------------
// CTestPositionServer::GetModuleChangeNotificationPanicDuplicate
//
// (other items were commented in a header).
// ---------------------------------------------------------
//	
void CTestPositionServer::GetModuleChangeNotificationPanicDuplicate(TInt aEvent, TPositionModuleId aUid)
	{
	TPositionModuleStatus moduleStatus;
	TPositionModuleStatusEventBase::_TModuleEvent event = TPositionModuleStatusEvent::EEventNone;

	//Setting of Event type according to aEvent parameter
    switch(aEvent) 
	    {
	    	case 0:
	    	event = TPositionModuleStatusEvent::EEventNone; 
	    	break;
			case 4:
	    	event = TPositionModuleStatusEvent::EEventAll; 
	    	break;	    	
	    }
    iModuleEvent.SetRequestedEvents(event);

    // Asynchronous module status
    iPosServer.NotifyModuleStatusEvent(iModuleEvent, iStatus, aUid);
    SetActive();
    TRequestStatus status;
	iPosServer.NotifyModuleStatusEvent(iModuleEvent, status, aUid);
	User::WaitForRequest(status);
    
}

