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
* Description:   Helper class for TPositionSelectionOrder,TPositionCriteriaBase
*                & TPositionCriteria class
*
*/


// System Includes


// User Includes
#include "testcriteria.h"
#include <e32std.h>

// Constant Declarations

    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ Default Constructor
// ---------------------------------------------------------------------------
//
TTestCriteria ::TTestCriteria (CStifLogger* aLog):iLog(aLog)
    {
        
    }

// ---------------------------------------------------------------------------
// C++ Destructor
// ---------------------------------------------------------------------------
//
TTestCriteria ::~TTestCriteria ()
    {
        
    }


// ---------------------------------------------------------
//  Test case for Default Constructor of TPositionSelectionOrder
// ---------------------------------------------------------
//	
TInt TTestCriteria :: DefaultPositionSelectionOrder()
    {
    	TPositionSelectionOrder posSelOrder;
    	
        return KErrNone;
    }

// ---------------------------------------------------------
// Test case for SetOrderTimeToFirstFix
// ---------------------------------------------------------
//	
TInt TTestCriteria :: DoSetOrderTimeToFirstFix(CStifItemParser& aItem)
    {
    	TPositionSelectionOrder posSelOrder;
    	TInt order1 = 0;
    	TInt err = aItem.GetNextInt(order1);
    	TPositionSelectionOrder::TOrder order2 = TPositionSelectionOrder::EOrderDontCare;
    	if(!err)
    	    {
    	        switch(order1)
    	            {
        	            case 0: order2 = TPositionSelectionOrder::EOrderDontCare; 
        	                    break;
        	            case 1: order2 = TPositionSelectionOrder::EOrderDefault;
        	                    break;
        	            case 2: order2 = TPositionSelectionOrder::EOrderVeryLow;
        	                    break;
        	            case 3: order2 = TPositionSelectionOrder::EOrderLow;
        	                    break;
        	            case 4: order2 = TPositionSelectionOrder::EOrderFairlyLow;
        	                    break;
        	            case 5: order2 = TPositionSelectionOrder::EOrderMedium;
        	                    break;
        	            case 6: order2 = TPositionSelectionOrder::EOrderFairlyHigh;
        	                    break;
        	            case 7: order2 = TPositionSelectionOrder::EOrderHigh;
        	                    break;
        	            case 8: order2 = TPositionSelectionOrder::EOrderVeryHigh;
        	                    break;
        	            default: break;
    	                    
    	            }
    	            TInt error = posSelOrder.SetOrderTimeToFirstFix(order2);
    	            return error;
    	    }
    	  else
    	    return KErrGeneral;
    	
        
    }
    
// ---------------------------------------------------------
// Test case for SetOrderTimeToNextFix
// ---------------------------------------------------------
//	
TInt TTestCriteria :: DoSetOrderTimeToNextFix(CStifItemParser& aItem)
    {
    	TPositionSelectionOrder posSelOrder;
    	TInt order1 = 0;
    	TInt err = aItem.GetNextInt(order1);
    	TPositionSelectionOrder::TOrder order2 = TPositionSelectionOrder::EOrderDontCare;
    	if(!err)
    	    {
    	        switch(order1)
    	            {
        	            case 0: order2 = TPositionSelectionOrder::EOrderDontCare; 
        	                    break;
        	            case 1: order2 = TPositionSelectionOrder::EOrderDefault;
        	                    break;
        	            case 2: order2 = TPositionSelectionOrder::EOrderVeryLow;
        	                    break;
        	            case 3: order2 = TPositionSelectionOrder::EOrderLow;
        	                    break;
        	            case 4: order2 = TPositionSelectionOrder::EOrderFairlyLow;
        	                    break;
        	            case 5: order2 = TPositionSelectionOrder::EOrderMedium;
        	                    break;
        	            case 6: order2 = TPositionSelectionOrder::EOrderFairlyHigh;
        	                    break;
        	            case 7: order2 = TPositionSelectionOrder::EOrderHigh;
        	                    break;
        	            case 8: order2 = TPositionSelectionOrder::EOrderVeryHigh;
        	                    break;
        	            default: break;
    	                    
    	            }
    	            TInt error = posSelOrder.SetOrderTimeToNextFix(order2);
    	            return error;
    	    }
    	  else
    	    return KErrGeneral;
    	
        
    }
    
// ---------------------------------------------------------
// Test case for SetOrderHorizontalAccuracy
// ---------------------------------------------------------
//	
TInt TTestCriteria :: DoSetOrderHorizontalAccuracy(CStifItemParser& aItem)
    {
    	TPositionSelectionOrder posSelOrder;
    	TInt order1 = 0;
    	TInt err = aItem.GetNextInt(order1);
    	TPositionSelectionOrder::TOrder order2 = TPositionSelectionOrder::EOrderDontCare;
    	if(!err)
    	    {
    	        switch(order1)
    	            {
        	            case 0: order2 = TPositionSelectionOrder::EOrderDontCare; 
        	                    break;
        	            case 1: order2 = TPositionSelectionOrder::EOrderDefault;
        	                    break;
        	            case 2: order2 = TPositionSelectionOrder::EOrderVeryLow;
        	                    break;
        	            case 3: order2 = TPositionSelectionOrder::EOrderLow;
        	                    break;
        	            case 4: order2 = TPositionSelectionOrder::EOrderFairlyLow;
        	                    break;
        	            case 5: order2 = TPositionSelectionOrder::EOrderMedium;
        	                    break;
        	            case 6: order2 = TPositionSelectionOrder::EOrderFairlyHigh;
        	                    break;
        	            case 7: order2 = TPositionSelectionOrder::EOrderHigh;
        	                    break;
        	            case 8: order2 = TPositionSelectionOrder::EOrderVeryHigh;
        	                    break;
        	            default: break;
    	                    
    	            }
    	            TInt error = posSelOrder.SetOrderHorizontalAccuracy(order2);
    	            return error;
    	    }
    	  else
    	    return KErrGeneral;
    	
        
    }
 
 
 // ---------------------------------------------------------
// Test case for SetOrderVerticalAccuracy
// ---------------------------------------------------------
//	
TInt TTestCriteria :: DoSetOrderVerticalAccuracy(CStifItemParser& aItem)
    {
    	TPositionSelectionOrder posSelOrder;
    	TInt order1 = 0;
    	TInt err = aItem.GetNextInt(order1);
    	TPositionSelectionOrder::TOrder order2 = TPositionSelectionOrder::EOrderDontCare;
    	if(!err)
    	    {
    	        switch(order1)
    	            {
        	            case 0: order2 = TPositionSelectionOrder::EOrderDontCare; 
        	                    break;
        	            case 1: order2 = TPositionSelectionOrder::EOrderDefault;
        	                    break;
        	            case 2: order2 = TPositionSelectionOrder::EOrderVeryLow;
        	                    break;
        	            case 3: order2 = TPositionSelectionOrder::EOrderLow;
        	                    break;
        	            case 4: order2 = TPositionSelectionOrder::EOrderFairlyLow;
        	                    break;
        	            case 5: order2 = TPositionSelectionOrder::EOrderMedium;
        	                    break;
        	            case 6: order2 = TPositionSelectionOrder::EOrderFairlyHigh;
        	                    break;
        	            case 7: order2 = TPositionSelectionOrder::EOrderHigh;
        	                    break;
        	            case 8: order2 = TPositionSelectionOrder::EOrderVeryHigh;
        	                    break;
        	            default: break;
    	                    
    	            }
    	            TInt error = posSelOrder.SetOrderVerticalAccuracy(order2);
    	            return error;
    	    }
    	  else
    	    return KErrGeneral;
    	
        
    }
    
 // ---------------------------------------------------------
// Test case for SetOrderCostIndicator
// ---------------------------------------------------------
//	
TInt TTestCriteria :: DoSetOrderCostIndicator(CStifItemParser& aItem)
    {
    	TPositionSelectionOrder posSelOrder;
    	TInt order1 = 0;
    	TInt err = aItem.GetNextInt(order1);
    	TPositionSelectionOrder::TOrder order2 = TPositionSelectionOrder::EOrderDontCare;
    	if(!err)
    	    {
    	        switch(order1)
    	            {
        	            case 0: order2 = TPositionSelectionOrder::EOrderDontCare; 
        	                    break;
        	            case 1: order2 = TPositionSelectionOrder::EOrderDefault;
        	                    break;
        	            case 2: order2 = TPositionSelectionOrder::EOrderVeryLow;
        	                    break;
        	            case 3: order2 = TPositionSelectionOrder::EOrderLow;
        	                    break;
        	            case 4: order2 = TPositionSelectionOrder::EOrderFairlyLow;
        	                    break;
        	            case 5: order2 = TPositionSelectionOrder::EOrderMedium;
        	                    break;
        	            case 6: order2 = TPositionSelectionOrder::EOrderFairlyHigh;
        	                    break;
        	            case 7: order2 = TPositionSelectionOrder::EOrderHigh;
        	                    break;
        	            case 8: order2 = TPositionSelectionOrder::EOrderVeryHigh;
        	                    break;
        	            default: break;
    	                    
    	            }
    	            TInt error = posSelOrder.SetOrderCostIndicator(order2);
    	            return error;
    	    }
    	  else
    	    return KErrGeneral;
    	
        
    }
  
  
 // ---------------------------------------------------------
// Test case for SetOrderPowerConsumption
// ---------------------------------------------------------
//	
TInt TTestCriteria :: DoSetOrderPowerConsumption(CStifItemParser& aItem)
    {
    	TPositionSelectionOrder posSelOrder;
    	TInt order1 = 0;
    	TInt err = aItem.GetNextInt(order1);
    	TPositionSelectionOrder::TOrder order2 = TPositionSelectionOrder::EOrderDontCare;
    	if(!err)
    	    {
    	        switch(order1)
    	            {
        	            case 0: order2 = TPositionSelectionOrder::EOrderDontCare; 
        	                    break;
        	            case 1: order2 = TPositionSelectionOrder::EOrderDefault;
        	                    break;
        	            case 2: order2 = TPositionSelectionOrder::EOrderVeryLow;
        	                    break;
        	            case 3: order2 = TPositionSelectionOrder::EOrderLow;
        	                    break;
        	            case 4: order2 = TPositionSelectionOrder::EOrderFairlyLow;
        	                    break;
        	            case 5: order2 = TPositionSelectionOrder::EOrderMedium;
        	                    break;
        	            case 6: order2 = TPositionSelectionOrder::EOrderFairlyHigh;
        	                    break;
        	            case 7: order2 = TPositionSelectionOrder::EOrderHigh;
        	                    break;
        	            case 8: order2 = TPositionSelectionOrder::EOrderVeryHigh;
        	                    break;
        	            default: break;
    	                    
    	            }
    	            TInt error = posSelOrder.SetOrderPowerConsumption(order2);
    	            return error;
    	    }
    	  else
    	    return KErrGeneral;
    	
        
    }
    
    
 // ---------------------------------------------------------
// Test case to check ResetSelectionOrder
// ---------------------------------------------------------

TInt TTestCriteria ::DoResetSelectionOrder()
    {
        TPositionSelectionOrder posSelOrder;
        posSelOrder.ResetSelectionOrder();
        return KErrNone;
    }

 // ---------------------------------------------------------
// Test case to check ClearSelectionOrder
// ---------------------------------------------------------

TInt TTestCriteria ::DoClearSelectionOrder()
    {
        TPositionSelectionOrder posSelOrder;
        posSelOrder.ClearSelectionOrder();
        return KErrNone;
    }
    
 // ---------------------------------------------------------
// Test case for NumSelectionItems
// ---------------------------------------------------------

TInt TTestCriteria ::GetNumSelectionItems()
    {
        TPositionSelectionOrder posSelOrder;
        TUint numSelItems = posSelOrder.NumSelectionItems();
        if(numSelItems)
            {
                return KErrNone;
            }
        else
            return KErrGeneral;
    }


 // ---------------------------------------------------------
// Test case for GetSelectionItem
// ---------------------------------------------------------

TInt TTestCriteria ::DoGetSelectionItem()
    {
        TPositionSelectionOrder posSelOrder;
        TPositionSelectionOrder::TOrder order;
        TPositionSelectionOrder::TField field;
        TUint index = 2;
        TInt error = posSelOrder.GetSelectionItem(index,field,order);
        return error;
        
        
    }


 // ---------------------------------------------------------
// Test case for setting & getting RequiredCapabilities
// ---------------------------------------------------------

TInt TTestCriteria ::SetGetRequiredCapabilities(CStifItemParser& aItem)
    {
         TInt capability1 = 0;
        
        TInt error = aItem.GetNextInt(capability1);
        TPositionCriteria posCriteria;
        
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
                  posCriteria.AddRequiredCapabilities(capability2);
                  TPositionModuleInfo::TCapabilities cap = posCriteria.RequiredCapabilities();
                  if(cap==capability2)
                    {
                        return KErrNone;
                    }
                  else 
                        return KErrGeneral;
                  
            }
         else
            return KErrGeneral;
            
            
    }
    
    
// ---------------------------------------------------------
// Test case for ClearRequiredCapabilities
// ---------------------------------------------------------

TInt TTestCriteria :: DoClearRequiredCapabilities()
    {
        TPositionCriteria posCriteria;
        TPositionModuleInfo::TCapabilities capability = TPositionModuleInfo::ECapabilityHorizontal;
        posCriteria.AddRequiredCapabilities(capability);
        TPositionModuleInfo::TCapabilities cap = posCriteria.RequiredCapabilities();
        posCriteria.ClearRequiredCapabilities();
        TPositionModuleInfo::TCapabilities cap1 = posCriteria.RequiredCapabilities();
        if(cap!=cap1)  
            {
                return KErrNone;
            }
        else
            return KErrGeneral;
        
    }

// ---------------------------------------------------------
// Test case for setting & getting RequiredQuality
// ---------------------------------------------------------

TInt TTestCriteria :: SetGetRequiredQuality()
    {
            TPositionCriteria posCriteria;
            TPositionQuality pos1;
            TPositionQuality pos2;
            TPositionQuality::TCostIndicator costInd = TPositionQuality::ECostUnknown;
            pos1.SetCostIndicator(costInd);
            posCriteria.SetRequiredQuality(pos1);
            posCriteria.GetRequiredQuality(pos2);
            if(pos1.CostIndicator()==pos2.CostIndicator())
                {
                    return KErrNone;
                }
            else
                return KErrGeneral;
            

        
    }


// ---------------------------------------------------------
// Test case for setting & getting SelectionOrder
// ---------------------------------------------------------

TInt TTestCriteria :: SetGetSelectionOrder()
    {
        TPositionSelectionOrder posSelOrder1;
        TPositionSelectionOrder posSelOrder2;
        TPositionSelectionOrder::TOrder order1 = TPositionSelectionOrder::EOrderLow ;
        TPositionSelectionOrder::TOrder order2;
        TPositionSelectionOrder::TField field;
        TUint index = 4;
        posSelOrder1.SetOrderCostIndicator(order1);
        TPositionCriteria posCriteria;
        posCriteria.SetSelectionOrder(posSelOrder1);
        posCriteria.GetSelectionOrder(posSelOrder2);
        posSelOrder2.GetSelectionItem(index,field,order2);
        if(order2==order1)
            {
                return KErrNone;
            }
        else
            return KErrGeneral;
        
        
        
        
        
    }
    
    
    
    
 // ---------------------------------------------------------
//Test case for ResetCriteria
// ---------------------------------------------------------
TInt TTestCriteria ::  DoResetCriteria()
    {
        TPositionCriteria posCriteria;
        posCriteria.ResetCriteria();
        return KErrNone;
    }

 // ---------------------------------------------------------
//Test case for ClearCriteria
// ---------------------------------------------------------
TInt TTestCriteria ::  DoClearCriteria()
    {
        TPositionCriteria posCriteria;
        posCriteria.ClearCriteria();
        return KErrNone;
    }
    
// ---------------------------------------------------------
//Test Case for default constructor of TPositionCriteria
// ---------------------------------------------------------
   TInt TTestCriteria :: DefaultPositionCriteria()
    {
        TPositionCriteria posCriteria;
        return KErrNone;
    }
    
// ---------------------------------------------------------
//Test Case for  constructor of TPositionCriteria with 
// required capabilities as parameter
// ---------------------------------------------------------
   TInt TTestCriteria :: PositionCriteriaCons(CStifItemParser& aItem)
    {
         TInt capability1 = 0;
        
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
                    
                   TPositionCriteria posCriteria(capability2);
                   TPositionModuleInfo::TCapabilities cap = posCriteria.RequiredCapabilities();
                  if(cap==capability2)
                    {
                        return KErrNone;
                    }
                  else 
                        return KErrGeneral;
            }
            else
                return KErrGeneral;
                    
    }
