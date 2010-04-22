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
* Description:  Helper class for TPositionModuleStatus,TPositionModuleStatusEventBase
*                 TPositionModuleStatusEvent TPositionUpdateOptionsBase &
*                TPositionUpdateOptions classes
*
*/


// System Includes


// User Includes
#include "testpositionmodule.h"
#include <e32std.h>

// Constant Declarations

    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ Default Constructor
// ---------------------------------------------------------------------------
//
TTestPositionModule ::TTestPositionModule (CStifLogger* aLog):iLog(aLog)
    {
        
    }

// ---------------------------------------------------------------------------
// C++ Destructor
// ---------------------------------------------------------------------------
//
TTestPositionModule ::~TTestPositionModule ()
    {
        
    }

// ---------------------------------------------------------------------------
// Test case for default constructor of TPositionModuleStatusBase
// ---------------------------------------------------------------------------

TInt TTestPositionModule ::DefaultPositionModuleStatus()
    {
        TPositionModuleStatus pos;
        return KErrNone;
    }
// ---------------------------------------------------------------------------
// Test case for setting & getting Device Status
// ---------------------------------------------------------------------------
TInt TTestPositionModule ::SetGetDeviceStatus(CStifItemParser& aItem)
    {
        TInt deviceStatus = 0;
        TInt error = aItem.GetNextInt(deviceStatus);
        TPositionModuleStatus modStatus;
	    TPositionModuleStatus::TDeviceStatus dStatus = TPositionModuleStatus::EDeviceUnknown;
	    if(!error)
	        {
	            switch(deviceStatus)
	                {
	                case 0: dStatus = TPositionModuleStatus::EDeviceUnknown;
	                        break;
	                case 1: dStatus = TPositionModuleStatus::EDeviceDisabled;
	                        break;
	                case 2: dStatus =  TPositionModuleStatus::EDeviceInactive;
	                        break;
	                case 3: dStatus = TPositionModuleStatus::EDeviceInitialising;
	                        break;
	                case 4: dStatus = TPositionModuleStatus::EDeviceStandBy;
	                        break;
	                case 5: dStatus = TPositionModuleStatus::EDeviceReady;
	                        break;
	                case 6: dStatus = TPositionModuleStatus:: EDeviceActive;
	                        break;
	                default:break;
	                }
	                modStatus.SetDeviceStatus(dStatus);
	                TPositionModuleStatus::TDeviceStatus dStatus1 = modStatus.DeviceStatus();
	                if(dStatus1==dStatus)
	                    {
	                        return KErrNone;
	                    }
	                else
	                    return KErrGeneral;
	        
	        }
	        
	     else
	                    return KErrGeneral;
        
        
    }
 
// ---------------------------------------------------------------------------
// Test case for setting & getting TDataQualityStatus
// ---------------------------------------------------------------------------
TInt TTestPositionModule ::SetGetDataQualityStatus(CStifItemParser& aItem)
    {
        TInt dataQualityStatus = 0;
        TInt error = aItem.GetNextInt(dataQualityStatus);
        TPositionModuleStatus modStatus;
	    TPositionModuleStatus::TDataQualityStatus dQualityStatus = TPositionModuleStatus::EDataQualityUnknown;
	    if(!error)
	        {
	            switch(dataQualityStatus)
	                {
	                case 0: dQualityStatus = TPositionModuleStatus::EDataQualityUnknown;
	                        break;
	                case 1: dQualityStatus = TPositionModuleStatus::EDataQualityLoss;
	                        break;
	                case 2: dQualityStatus =  TPositionModuleStatus::EDataQualityPartial;
	                        break;
	                case 3: dQualityStatus = TPositionModuleStatus::EDataQualityNormal;
	                        break;
	               
	                default:break;
	                }
	                modStatus.SetDataQualityStatus(dQualityStatus);
	                TPositionModuleStatus::TDataQualityStatus dQualityStatus1 = modStatus.DataQualityStatus();
	                if(dQualityStatus1==dQualityStatus)
	                    {
	                        return KErrNone;
	                    }
	                else
	                    return KErrGeneral;
	        
	        }
	        
	     else
	                    return KErrGeneral;
        
        
    }
    
    
    
 // ---------------------------------------------------------------------------
// Test case for setting & getting Requested Events
// ---------------------------------------------------------------------------
TInt TTestPositionModule ::SetGetRequestedEvents(CStifItemParser& aItem)
    {
        TInt reqEvents = 0;
        TInt error = aItem.GetNextInt(reqEvents);
        TPositionModuleStatusEvent modStatusEvent;
	    TPositionModuleStatusEventBase::TModuleEvent modEvent = TPositionModuleStatusEventBase::EEventNone;
	    if(!error)
	        {
	            switch(reqEvents)
	                {
	                case 0: modEvent = TPositionModuleStatusEventBase::EEventNone;
	                        break;
	                case 1: modEvent = TPositionModuleStatusEventBase::EEventDeviceStatus;
	                        break;
	                case 2: modEvent =  TPositionModuleStatusEventBase::EEventDataQualityStatus;
	                        break;
	                case 3: modEvent = TPositionModuleStatusEventBase::EEventSystemModuleEvent;
	                        break;
	                case 4: modEvent = TPositionModuleStatusEventBase::EEventAll;
	                        break;
	               
	                default:break;
	                }
	                modStatusEvent.SetRequestedEvents(modEvent);
	               TPositionModuleStatusEventBase::TModuleEvent modEvent1 = modStatusEvent.RequestedEvents();
	                if(modEvent1==modEvent)
	                    {
	                        return KErrNone;
	                    }
	                else
	                    return KErrGeneral;
	        
	        }
	        
	     else
	                    return KErrGeneral;
        
        
    }
    
    
    
// ---------------------------------------------------------------------------
// Test case for setting & getting ModuleId 
// ---------------------------------------------------------------------------

TInt TTestPositionModule::SetGetModuleId()
    {
        TPositionModuleId KPositionNullModuleId = {KNullUidValue};
        TPositionModuleStatusEvent modStatusEvent;
        modStatusEvent.SetModuleId(KPositionNullModuleId);
        TPositionModuleId  KPositionNullModuleId1 = modStatusEvent.ModuleId();
        if(KPositionNullModuleId1==KPositionNullModuleId)
            {
                return KErrNone;
            }
        else
            return KErrGeneral;

    }


 // ---------------------------------------------------------------------------
// Test case for setting & getting Occurred Events
// ---------------------------------------------------------------------------
TInt TTestPositionModule ::SetGetOccurredEvents(CStifItemParser& aItem)
    {
        TInt occEvents = 0;
        TInt error = aItem.GetNextInt(occEvents);
        TPositionModuleStatusEvent modStatusEvent;
	    TPositionModuleStatusEventBase::TModuleEvent modEvent = TPositionModuleStatusEventBase::EEventNone;
	    if(!error)
	        {
	            switch(occEvents)
	                {
	                case 0: modEvent = TPositionModuleStatusEventBase::EEventNone;
	                        break;
	                case 1: modEvent = TPositionModuleStatusEventBase::EEventDeviceStatus;
	                        break;
	                case 2: modEvent =  TPositionModuleStatusEventBase::EEventDataQualityStatus;
	                        break;
	                case 3: modEvent = TPositionModuleStatusEventBase::EEventSystemModuleEvent;
	                        break;
	                case 4: modEvent = TPositionModuleStatusEventBase::EEventAll;
	                        break;
	               
	                default:break;
	                }
	                modStatusEvent.SetOccurredEvents(modEvent);
	               TPositionModuleStatusEventBase::TModuleEvent modEvent1 = modStatusEvent.OccurredEvents();
	                if(modEvent1==modEvent)
	                    {
	                        return KErrNone;
	                    }
	                else
	                    return KErrGeneral;
	        
	        }
	        
	     else
	                    return KErrGeneral;
        
        
    }
    

 // ---------------------------------------------------------------------------
// Test case for setting & getting System Module Events
// ---------------------------------------------------------------------------
TInt TTestPositionModule ::SetGetSystemModuleEvents(CStifItemParser& aItem)
    {
        TInt sysEvents = 0;
        TInt error = aItem.GetNextInt(sysEvents);
        TPositionModuleStatusEvent modStatusEvent;
	    TPositionModuleStatusEventBase::TSystemModuleEvent modEvent = TPositionModuleStatusEventBase::ESystemUnknown;
	    if(!error)
	        {
	            switch(sysEvents)
	                {
	                case 0: modEvent = TPositionModuleStatusEventBase::ESystemUnknown;
	                        break;
	                case 1: modEvent = TPositionModuleStatusEventBase::ESystemError;
	                        break;
	                case 2: modEvent =  TPositionModuleStatusEventBase::ESystemModuleInstalled;
	                        break;
	                case 3: modEvent = TPositionModuleStatusEventBase::ESystemModuleRemoved;
	                        break;
	                
	                default:break;
	                }
	                modStatusEvent.SetSystemModuleEvent(modEvent);
	               TPositionModuleStatusEventBase::TSystemModuleEvent modEvent1 = modStatusEvent.SystemModuleEvent();
	                if(modEvent1==modEvent)
	                    {
	                        return KErrNone;
	                    }
	                else
	                    return KErrGeneral;
	        
	        }
	        
	     else
	                    return KErrGeneral;
        
        
    }
    
    
    
// ---------------------------------------------------------------------------
// Test case for default constructor of TPositionModuleStatusEvent 
// ---------------------------------------------------------------------------
TInt  TTestPositionModule :: DefaultPositionModuleStatusEvent()
    {
        TPositionModuleStatusEvent posModStatus;
        return KErrNone;
    }
    
    
    
   
 // ---------------------------------------------------------------------------
// Test case for constructor with events as arguments
// ---------------------------------------------------------------------------
TInt TTestPositionModule ::PositionModuleStatusEvent1(CStifItemParser& aItem)
    {
        TInt reqEvents = 0;
        TInt error = aItem.GetNextInt(reqEvents);
        
	    TPositionModuleStatusEventBase::TModuleEvent modEvent = TPositionModuleStatusEventBase::EEventNone;
	    if(!error)
	        {
	            switch(reqEvents)
	                {
	                case 0: modEvent = TPositionModuleStatusEventBase::EEventNone;
	                        break;
	                case 1: modEvent = TPositionModuleStatusEventBase::EEventDeviceStatus;
	                        break;
	                case 2: modEvent =  TPositionModuleStatusEventBase::EEventDataQualityStatus;
	                        break;
	                case 3: modEvent = TPositionModuleStatusEventBase::EEventSystemModuleEvent;
	                        break;
	                case 4: modEvent = TPositionModuleStatusEventBase::EEventAll;
	                        break;
	               
	                default:break;
	                }
	                TPositionModuleStatusEvent modStatusEvent(modEvent);
	               TPositionModuleStatusEventBase::TModuleEvent modEvent1 = modStatusEvent.RequestedEvents();
	                if(modEvent1==modEvent)
	                    {
	                        return KErrNone;
	                    }
	                else
	                    return KErrGeneral;
	        
	        }
	        
	     else
	                    return KErrGeneral;
        
        
    }
    
    
 // ---------------------------------------------------------------------------
//Test case for setting & getting ModuleStatus
// ---------------------------------------------------------------------------
TInt TTestPositionModule ::SetGetModuleStatus(CStifItemParser& aItem)
    {
        TInt deviceStatus = 0;
        TInt error1 = aItem.GetNextInt(deviceStatus);
        TInt dataQualityStatus = 0;
        TInt error2 = aItem.GetNextInt(dataQualityStatus);
        TPositionModuleStatus modStatus1;
        TPositionModuleStatus modStatus2;

	    TPositionModuleStatus::TDeviceStatus dStatus = TPositionModuleStatus::EDeviceUnknown;
	    TPositionModuleStatus::TDataQualityStatus dQualityStatus = TPositionModuleStatus::EDataQualityUnknown;
	    TPositionModuleStatusEvent posModStatusEvent;
	                
	    if(!error1 && !error2)
	        {
	            switch(deviceStatus)
	                {
	                case 0: dStatus = TPositionModuleStatus::EDeviceUnknown;
	                        break;
	                case 1: dStatus = TPositionModuleStatus::EDeviceDisabled;
	                        break;
	                case 2: dStatus =  TPositionModuleStatus::EDeviceInactive;
	                        break;
	                case 3: dStatus = TPositionModuleStatus::EDeviceInitialising;
	                        break;
	                case 4: dStatus = TPositionModuleStatus::EDeviceStandBy;
	                        break;
	                case 5: dStatus = TPositionModuleStatus::EDeviceReady;
	                        break;
	                case 6: dStatus = TPositionModuleStatus:: EDeviceActive;
	                        break;
	                default:break;
	                }
	                modStatus1.SetDeviceStatus(dStatus);
	            switch(dataQualityStatus)
	                {
	                case 0: dQualityStatus = TPositionModuleStatus::EDataQualityUnknown;
	                        break;
	                case 1: dQualityStatus = TPositionModuleStatus::EDataQualityLoss;
	                        break;
	                case 2: dQualityStatus =  TPositionModuleStatus::EDataQualityPartial;
	                        break;
	                case 3: dQualityStatus = TPositionModuleStatus::EDataQualityNormal;
	                        break;
	               
	                default:break;
	                }
	                modStatus1.SetDataQualityStatus(dQualityStatus);
	                posModStatusEvent.SetModuleStatus(modStatus1);
	                posModStatusEvent.GetModuleStatus(modStatus2);
	                if(modStatus1.DeviceStatus()==modStatus2.DeviceStatus() &&
	                   modStatus1.DataQualityStatus()==modStatus2.DataQualityStatus())
	                    {
	                        return KErrNone;
	                    }
	                else
	                    return KErrGeneral;
	        }
	        else
	            return KErrGeneral;
	                
	             
    }
    
    
 // ---------------------------------------------------------------------------
//Test case for setting & getting UpdateInterval
// ---------------------------------------------------------------------------

TInt TTestPositionModule ::SetGetUpdateInterval(TTimeIntervalMicroSeconds aInterval)
    {
        TPositionUpdateOptions posUpdate;
        posUpdate.SetUpdateInterval(aInterval);
        TTimeIntervalMicroSeconds updateInterval = posUpdate.UpdateInterval();
        if(aInterval==updateInterval)
            {
                return KErrNone;
            }
         else
            return KErrGeneral;
        
    }
    
    
 // ---------------------------------------------------------------------------
//Test case for setting & getting UpdateTimeOut
// ---------------------------------------------------------------------------

TInt TTestPositionModule ::SetGetUpdateTimeOut(TTimeIntervalMicroSeconds aTimeOut)
    {
        TPositionUpdateOptions posUpdate;
        posUpdate.SetUpdateTimeOut(aTimeOut);
        TTimeIntervalMicroSeconds updateTimeOut = posUpdate.UpdateTimeOut();
        if(aTimeOut==updateTimeOut)
            {
                return KErrNone;
            }
         else
            return KErrGeneral;
        
    }
    
    
 // ---------------------------------------------------------------------------
//Test case for setting & getting MaxUpdateAge
// ---------------------------------------------------------------------------

TInt TTestPositionModule ::SetGetMaxUpdateAge(TTimeIntervalMicroSeconds aMaxAge)
    {
        TPositionUpdateOptions posUpdate;
        posUpdate.SetMaxUpdateAge(aMaxAge);
        TTimeIntervalMicroSeconds maxUpdateAge = posUpdate.MaxUpdateAge();
        if(aMaxAge==maxUpdateAge)
            {
                return KErrNone;
            }
         else
            return KErrGeneral;
        
    }
    
// ---------------------------------------------------------------------------
//Test case for default constructor of TpositionUpdateOptions
// ---------------------------------------------------------------------------
TInt TTestPositionModule ::DefaultPosUpdateOptions()
    {
        TPositionUpdateOptions posUpdate;
        return KErrNone;
    }
    
    
// ---------------------------------------------------------------------------
//Test case for constructor of TPositionUpdateOptions with arguments
// ---------------------------------------------------------------------------
TInt TTestPositionModule ::PosUpdateOptions1()
    {
        TTimeIntervalMicroSeconds interval(1000);
        TPositionUpdateOptions posUpdate(interval);
        if(posUpdate.UpdateInterval()==interval &&
           posUpdate.UpdateTimeOut()==0 &&
           posUpdate.MaxUpdateAge()==0 &&
           posUpdate.AcceptPartialUpdates()==EFalse)
            {
                return KErrNone;
            }
         else
            return KErrGeneral;
        
    }
        
// ---------------------------------------------------------------------------
//Test case for checking if partial updates are allowed
// ---------------------------------------------------------------------------
TInt TTestPositionModule ::SetGetPartialUpdates(CStifItemParser& aItem)
    {
        TInt acceptPartialUpdate = 0;
        TInt error = aItem.GetNextInt(acceptPartialUpdate);
        TPositionUpdateOptions posUpdate;
        if(!error)
            {
                posUpdate.SetAcceptPartialUpdates(acceptPartialUpdate);
                TBool check = posUpdate.AcceptPartialUpdates();
                if(check==acceptPartialUpdate)
                    {
                        return KErrNone;
                    }
                else
                    return KErrGeneral;
            }
         else
            return KErrGeneral;
    }
