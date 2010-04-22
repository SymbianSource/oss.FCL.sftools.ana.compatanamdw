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
* Description:  Helper class for TPositionClassTypeBase, TPositionQualityBase 
*                & TPositionQuality classes
*
*/


// System Includes
#include <e32std.h>
#include <StifTestModule.h>
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include "testlbslocacquisition.h"

#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include <e32des16.h>




// User Includes
#include "testpositionquality.h"

// Constant Declarations

    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ Default Constructor
// ---------------------------------------------------------------------------
//
TTestPositionQuality ::TTestPositionQuality (CStifLogger* aLog):iLog(aLog)
    {
        
    }

// ---------------------------------------------------------------------------
// C++ Destructor
// ---------------------------------------------------------------------------
//
TTestPositionQuality ::~TTestPositionQuality ()
    {
        
    }
    
    
// ---------------------------------------------------------------------------
// Test case for PositionClassType
// ---------------------------------------------------------------------------
TInt TTestPositionQuality :: GetPositionClassType()
    {
         TPositionQuality pos;
         TUint32 classType = pos.PositionClassType();
         return KErrNone;
    }
    
// ---------------------------------------------------------------------------
// Test case for PositionClassSize
// ---------------------------------------------------------------------------
TInt TTestPositionQuality :: GetPositionClassSize()
    {
         TPositionQuality pos;
         TUint classSize = pos.PositionClassSize();
         return KErrNone;
    }
    
// ---------------------------------------------------------------------------
// Test case for Compare
// ---------------------------------------------------------------------------
TInt TTestPositionQuality :: DoCompare()

    {
    
             TPositionQuality posQuality;
             TPositionQualityItem::TResult aComparison;
             TInt aHighIndex;
             aHighIndex = posQuality.HighWaterMark();
	         TInt compResult = posQuality.Compare(posQuality,aHighIndex+1,aComparison);
	         if(!compResult)
	            {
	                return KErrNone;
	            }
	         else
	            return compResult;
            
            
    }
    
    
// ---------------------------------------------------------------------------
// Test case for IsDefined
// ---------------------------------------------------------------------------
TInt TTestPositionQuality :: GetIsDefined()   
    {
        TPositionQuality posQuality;
        TInt elementId = 2;
        TBool defined = posQuality.IsDefined(elementId);
        return KErrNone;
    }
    
    
    
    
// ---------------------------------------------------------------------------
// Test case for getting the HighWaterMark
// ---------------------------------------------------------------------------
TInt TTestPositionQuality ::GetHighWaterMark()
    {
        TPositionQuality pos;
        TInt highWaterMark = pos.HighWaterMark();
        if(highWaterMark)
            {
                return KErrNone;
            }
        else
            return KErrGeneral;
        
    }
// ---------------------------------------------------------------------------
// Test case for default constructor of TPositionQuality class
// ---------------------------------------------------------------------------
TInt TTestPositionQuality ::DefaultPositionQuality()
    {
        TPositionQuality pos;
        return KErrNone;
    }
    
// ---------------------------------------------------------------------------
// Test case for setting & gettting the time to first fix
// ---------------------------------------------------------------------------
TInt TTestPositionQuality ::SetGetTimeToFirstFix(TTimeIntervalMicroSeconds time)
    {
       
        TPositionQuality posquality;
        posquality.SetTimeToFirstFix(time);
        TTimeIntervalMicroSeconds time3 = posquality.TimeToFirstFix();
           if(time3==time) 
            {
                                               
                 return KErrNone;
                                     
            }
                        
     else
            return KErrGeneral;
    }                  
            
                 
// ---------------------------------------------------------------------------
// Test case for setting & gettting the time to next fix
// ---------------------------------------------------------------------------
TInt TTestPositionQuality ::SetGetTimeToNextFix(TTimeIntervalMicroSeconds time)
    {
       
        TPositionQuality posquality;
        posquality.SetTimeToNextFix(time);
        TTimeIntervalMicroSeconds time3 = posquality.TimeToNextFix();
           if(time3==time) 
            {
                                               
                 return KErrNone;
                                     
            }
                        
     else
            return KErrGeneral;
    }                
            
         
                 
// ---------------------------------------------------------------------------
// Test case for setting & gettting the horizontal accuracy
// ---------------------------------------------------------------------------
TInt TTestPositionQuality ::SetGetHorizontalAccuracy(TReal32 haccuracy)
    {
       
        TPositionQuality posquality;
        posquality.SetHorizontalAccuracy(haccuracy);
        TReal32 haccuracy1 = posquality.HorizontalAccuracy();
           if(haccuracy1==haccuracy) 
            {
                                               
                 return KErrNone;
                                     
            }
                        
     else
            return KErrGeneral;
    }                
            
            
                  
// ---------------------------------------------------------------------------
// Test case for setting & gettting the vertical accuracy
// ---------------------------------------------------------------------------
TInt TTestPositionQuality ::SetGetVerticalAccuracy(TReal32 vaccuracy)
    {
       
        TPositionQuality posquality;
        posquality.SetVerticalAccuracy(vaccuracy);
        TReal32 vaccuracy1 = posquality.VerticalAccuracy();
           if(vaccuracy1==vaccuracy) 
            {
                                               
                 return KErrNone;
                                     
            }
                        
     else
            return KErrGeneral;
    }        
    
    
// ---------------------------------------------------------------------------
// Test case for setting & gettting the cost indicator
// ---------------------------------------------------------------------------
TInt TTestPositionQuality :: SetGetCostIndicator(CStifItemParser& aItem)
    {
        TInt cost = 0;
        TPositionQuality pos;
        
        TInt err = aItem.GetNextInt(cost);
        if(!err)
            {
                TPositionQuality::TCostIndicator costInd = TPositionQuality::ECostUnknown;
                switch(cost)
                    {
                        case 0: costInd = TPositionQuality::ECostUnknown;
                                break;
                        case 1: costInd = TPositionQuality::ECostZero;
                                break;
                        case 2: costInd = TPositionQuality::ECostPossible;
                                break;
                        case 3: costInd = TPositionQuality::ECostCharge;
                                break;
                        default: break;
                                             
                    }
                  pos.SetCostIndicator(costInd);
                  
                  TPositionQuality::TCostIndicator costIndicator = pos.CostIndicator();
                  if(costIndicator==costInd)
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
// Test case for setting & gettting the power consumption
// ---------------------------------------------------------------------------
  TInt TTestPositionQuality :: SetGetPowerConsumption(CStifItemParser& aItem)
    {
        TInt powercons = 0;
        TPositionQuality pos;
        
        TInt err = aItem.GetNextInt(powercons);
        if(!err)
            {
                 TPositionQuality::TPowerConsumption powerconsum1 = TPositionQuality::EPowerUnknown;
                 switch(powercons)
                    {
                    case 0: powerconsum1 = TPositionQuality::EPowerUnknown;
                            break;
                    case 1: powerconsum1 = TPositionQuality::EPowerZero;
                            break;
                    case 2: powerconsum1 = TPositionQuality::EPowerLow;
                            break;
                    case 3: powerconsum1 = TPositionQuality::EPowerMedium;
                            break;
                    case 4: powerconsum1 = TPositionQuality::EPowerHigh;
                            break;
                    default: break;
                    
                    }
                 pos.SetPowerConsumption(powerconsum1);
                 
                 TPositionQuality::TPowerConsumption powerconsum2 = pos.PowerConsumption();
                 if(powerconsum2==powerconsum1)
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
// Test case for constructor of TPositionModuleInfo
// ---------------------------------------------------------------------------

TInt TTestPositionQuality ::PositionModuleInfoConst()
    {
        TPositionModuleInfo pos;
        return KErrNone;
    }
    
// ---------------------------------------------------------------------------
// Test case for setting & getting ModuleId
// ---------------------------------------------------------------------------

TInt TTestPositionQuality ::SetGetModuleId()
    {
        TPositionModuleId KPositionNullModuleId = {KNullUidValue};
        TPositionModuleInfo posmodinfo;
        posmodinfo.SetModuleId(KPositionNullModuleId);
        TPositionModuleId  KPositionNullModuleId1 = posmodinfo.ModuleId();
        if(KPositionNullModuleId1==KPositionNullModuleId)
            {
                return KErrNone;
            }
        else
            return KErrGeneral;

    }
 
    
// ---------------------------------------------------------------------------
// Test case for setting & getting ModuleName 
// ---------------------------------------------------------------------------

TInt TTestPositionQuality::SetGetModuleName(CStifItemParser& aItem)
    {
        TPtrC ptr1;
        TBuf<200> buf;
        TInt error = aItem.GetNextString(ptr1);
        TPositionModuleInfo posmodinfo;
        posmodinfo.SetModuleName(ptr1);
        posmodinfo.GetModuleName(buf);
        if(buf==ptr1)
            {
                return KErrNone;
            }
        else
            return KErrGeneral;
        
        
    }  
    
    
 // ---------------------------------------------------------------------------
// Test case for checking if module is available
// ---------------------------------------------------------------------------
 TInt TTestPositionQuality::SetGetIsAvailable(CStifItemParser& aItem)
    {
        TInt available = 0;
        TInt error = aItem.GetNextInt(available);
        TPositionModuleInfo posmodinfo;
        if(!error)
            {
                posmodinfo.SetIsAvailable(available);
                TBool check = posmodinfo.IsAvailable();
                if(check==available)
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
// Test case for setting & getting TechnologyType
// ---------------------------------------------------------------------------
TInt TTestPositionQuality :: SetGetTechnologyType(CStifItemParser& aItem)
    {
        TInt techType1 = 0;
        TPositionModuleInfo pos;
        TInt error = aItem.GetNextInt(techType1);
        
        if(!error)
            {
                TPositionModuleInfo::TTechnologyType techType2 = TPositionModuleInfo::ETechnologyUnknown;
                switch(techType1)
                    {
                        case 0: techType2 = TPositionModuleInfo::ETechnologyUnknown;
                                break;
                        case 1: techType2 = TPositionModuleInfo::ETechnologyTerminal;	
                                break;
                        case 2: techType2 = TPositionModuleInfo::ETechnologyNetwork;
                                break;
                        case 3: techType2 = TPositionModuleInfo::ETechnologyAssisted;
                                break;
                        default:break;
                        
                    }
                 pos.SetTechnologyType(techType2);
                 TPositionModuleInfo::TTechnologyType techType3 = pos.TechnologyType();
                 if(techType3==techType2)
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
// Test case for setting & getting DeviceLocation
// ---------------------------------------------------------------------------
TInt TTestPositionQuality :: SetGetDeviceLocation(CStifItemParser& aItem)
    {
        TInt devLoc1 = 0;
        TPositionModuleInfo pos;
        TInt error = aItem.GetNextInt(devLoc1);
        
        if(!error)
            {
                TPositionModuleInfo::TDeviceLocation devLoc2 = TPositionModuleInfo::EDeviceUnknown;
                switch(devLoc1)
                    {
                        case 0: devLoc2 = TPositionModuleInfo::EDeviceUnknown;
                                break;
                        case 1: devLoc2 = TPositionModuleInfo::EDeviceInternal;	
                                break;
                        case 2: devLoc2 = TPositionModuleInfo::EDeviceExternal;
                                break;
                        
                        default:break;
                        
                    }
                 pos.SetDeviceLocation(devLoc2);
                 TPositionModuleInfo::TDeviceLocation devLoc3 = pos.DeviceLocation();
                 if(devLoc3==devLoc2)
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
// Test case for setting & getting Capabilities
// ---------------------------------------------------------------------------
TInt TTestPositionQuality :: SetGetCapabilities(CStifItemParser& aItem)
    {
        TInt capability1 = 0;
        TPositionModuleInfo pos;
        TInt error = aItem.GetNextInt(capability1);
        
        if(!error)
            {
                TPositionModuleInfo::TCapabilities capability2 = TPositionModuleInfo::ECapabilityNone;
                switch(capability1)
                    {
                        case 0: capability2 = TPositionModuleInfo::ECapabilityNone;
                                break;
                        case 1: capability2 = TPositionModuleInfo::ECapabilityHorizontal;	
                                break;
                        case 2: capability2 = TPositionModuleInfo::ECapabilityVertical;
                                break;
                        case 3: capability2 = TPositionModuleInfo::ECapabilitySpeed;
                                break;
                        case 4: capability2 = TPositionModuleInfo::ECapabilityDirection;
                                break;
                        case 5: capability2 = TPositionModuleInfo::ECapabilitySatellite;
                                break;
                        case 6: capability2 = TPositionModuleInfo::ECapabilityCompass ;
                                break;
                        case 7: capability2 = TPositionModuleInfo::ECapabilityNmea ;
                                break;
                        case 8: capability2 = TPositionModuleInfo::ECapabilityAddress ;
                                break;
                        case 9: capability2 = TPositionModuleInfo::ECapabilityBuilding;
                                break;
                        case 10:capability2 = TPositionModuleInfo::ECapabilityMedia ;
                                break;
                        default:break;
                        
                    }
                 pos.SetCapabilities(capability2);
                 TPositionModuleInfo::TCapabilities capability3 = pos.Capabilities();
                 if(capability3==capability2)
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
// Test case for setting & getting Classes Supported
// ---------------------------------------------------------------------------
 TInt TTestPositionQuality ::SetGetClassesSupported(TPositionClassFamily posClassType,TUint32 posInfoClasstype)
    {
        TPositionModuleInfo posModuleInfo;
        //TPositionClassFamily posClassType1;
        posModuleInfo.SetClassesSupported(posClassType,posInfoClasstype);
        TUint32 getClassType = posModuleInfo.ClassesSupported(posClassType);
        if(getClassType == 0)
		{
		_LIT(KErrMsg3,"TPositionModuleInfo::ClassesSupported() returned with :");
		TBuf8<80> errMsg3;
		errMsg3.Copy(KErrMsg3);
		errMsg3.AppendNum(getClassType);
		iLog->Log(errMsg3);	
		return getClassType;		
		}
	return KErrNone;
    }
    
 // ---------------------------------------------------------------------------
// Test case for setting & getting Version
// ---------------------------------------------------------------------------
    
    
    TInt TTestPositionQuality :: SetGetVersion(CStifItemParser& aItem)
        {
            TInt major = 0;
            TInt minor = 0;
            TInt build = 0;
            TInt err1 = aItem.GetNextInt(major);
            TInt err2 = aItem.GetNextInt(minor);
            TInt err3 = aItem.GetNextInt(build);
            TPositionModuleInfo posModuleInfo;
            
            if(!err1 && !err2 && !err3)
                {
                    TVersion version(major,minor,build);
                    posModuleInfo.SetVersion(version);
                    TVersion ver = posModuleInfo.Version();
                    if((ver.iMajor==major)&&(ver.iMinor==minor)&&(ver.iBuild==build))
                        {
                            return KErrNone;
                        }
                    else
                		return KErrGeneral;
                }
             else
                return KErrGeneral;
        }
