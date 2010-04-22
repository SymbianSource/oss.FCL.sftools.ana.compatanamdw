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
* Description:  Helper class for TLocality class
*
*/


// System Includes


// User Includes
#include "testlocality.h"

// Constant Declarations

    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ Default Constructor
// ---------------------------------------------------------------------------
//
TTestLocality ::TTestLocality (CStifLogger* aLog):iLog(aLog)
    {
        
    }

// ---------------------------------------------------------------------------
// C++ Destructor
// ---------------------------------------------------------------------------
//
TTestLocality ::~TTestLocality ()
    {
        
    }

// -----------------------------------------------------------------------------
// This method calls the respective constructor based on the number of arguments
// -----------------------------------------------------------------------------
//	
TInt TTestLocality ::CreateLocality(CStifItemParser& aItem)
    {
        TInt lat = 0;
	    TInt lon = 0;
	    TInt alt = 0;
	    TInt haccuracy = 0;
	    TInt vaccuracy = 0;
	    
	    TInt error1 = aItem.GetNextInt(lat);
	    TInt error2 = aItem.GetNextInt(lon);
	    TInt error3 = aItem.GetNextInt(alt);
	    TInt error4 = aItem.GetNextInt(haccuracy);
	    TInt error5 = aItem.GetNextInt(vaccuracy);
	    if ( !error1 && !error2 && !error3 )
	        {
	            TCoordinate co_ord(lat,lon,alt);
	            if(!error4 && !error5)
	                {
	                    return Locality2(co_ord,haccuracy,vaccuracy);
	                }
	            else if(!error4)
	                {
	                    return Locality1(co_ord,haccuracy);
	                }
	            else
	        	return KErrArgument;
	        }
	     else
	        return DefaultConstructor();
	     
	    
    }

// ---------------------------------------------------------
//  Test case for Default Constructor of TLocality
// ---------------------------------------------------------
//	
TInt TTestLocality :: DefaultConstructor()
    {
	TLocality locality;
	
    return KErrNone;
    }
    
// ---------------------------------------------------------
//  Test case for Constructor of TLocality with horizontal accuracy
// ---------------------------------------------------------
TInt TTestLocality :: Locality1(TCoordinate& aCoordinate,TReal32 aHorizontalAccuracy)
    {
        TLocality locality(aCoordinate,aHorizontalAccuracy);
        if(locality.HorizontalAccuracy()!=aHorizontalAccuracy)
            {
                return KErrGeneral;
            }
        else
            return KErrNone;
    }
    
// -----------------------------------------------------------------------
//  Test case for Constructor of TLocality with horizontal accuracy & vertical accuracy
// -----------------------------------------------------------------------

TInt TTestLocality :: Locality2(TCoordinate& aCoordinate,TReal32 aHorizontalAccuracy,TReal32 aVerticalAccuracy)
    {
        TLocality locality(aCoordinate,aHorizontalAccuracy,aVerticalAccuracy);
        if(locality.HorizontalAccuracy()!=aHorizontalAccuracy && locality.VerticalAccuracy()!=aVerticalAccuracy)
            {
                return KErrGeneral;
            }
        else
            return KErrNone;
    }
  
// -----------------------------------------------------------------------
//  Test case for setting horizontal accuracy
// -----------------------------------------------------------------------  

 TInt TTestLocality :: SetGetHorAccuracy(CStifItemParser& aItem)
    {
        TLocality locality;
        TInt haccuracy = 0;
        TInt error = aItem.GetNextInt(haccuracy);
        if(!error)
            {
                locality.SetHorizontalAccuracy(haccuracy);
                if(locality.HorizontalAccuracy()==haccuracy)
                    {
                        return KErrNone;
                    }
            }
        return KErrGeneral;
    }
    
// -----------------------------------------------------------------------
//  Test case for setting vertical accuracy
// -----------------------------------------------------------------------  

 TInt TTestLocality :: SetGetVerAccuracy(CStifItemParser& aItem)
    {
        TLocality locality;
        TInt vaccuracy = 0;
        TInt error = aItem.GetNextInt(vaccuracy);
        if(!error)
            {
                locality.SetVerticalAccuracy(vaccuracy);
                if(locality.VerticalAccuracy()==vaccuracy)
                    {
                        return KErrNone;
                    }
            }
        return KErrGeneral;
    }
// -----------------------------------------------------------------------
//  Test case for setting horizontal & vertical accuracy
// -----------------------------------------------------------------------  

 TInt TTestLocality :: SetGetAccuracy(CStifItemParser& aItem)
    {
        TLocality locality;
        TInt haccuracy = 0;
        TInt vaccuracy = 0;
        TInt error1 = aItem.GetNextInt(haccuracy);
        TInt error2 = aItem.GetNextInt(vaccuracy);
        if(!error1 && !error2)
            {
                locality.SetAccuracy(haccuracy,vaccuracy);
                if(locality.HorizontalAccuracy()==haccuracy && locality.VerticalAccuracy()==vaccuracy)
                    {
                        return KErrNone;
                    }
            }
        return KErrGeneral;
    }
    
// -----------------------------------------------------------------------
//   Test case for obtaining the distance between 2 coordinates
// ----------------------------------------------------------------------- 

  TInt TTestLocality :: GetDistance(CStifItemParser& aItem)
    {
            TInt lat1 = 0;
            TInt lon1 = 0;
            TInt lat2 = 0;
            TInt lon2 = 0;
            TPtrC ptr;
            //TReal32 dist;
            TReal32 distance = 0;
            TInt err1 = aItem.GetNextInt(lat1);
            TInt err2 = aItem.GetNextInt(lon1);
            TInt err3 = aItem.GetNextInt(lat2);
            TInt err4 = aItem.GetNextInt(lon2);
            TInt haccuracy = 0;
            //TInt err5 = aItem.GetNextString(ptr);
            //TLex lex(ptr);
            //lex.Val(dist);
            
            if(!err1 && !err2 && !err3 && !err4 )
                {
                    TCoordinate co_ord1(lat1,lon1);
                    TCoordinate co_ord2(lat2,lon2);
                    TLocality locality(co_ord2,haccuracy);
                    
                    TInt error = locality.Distance(co_ord1,distance);
                    if(!error)
                        {
                            return KErrNone;
                        }
                    else
                    return KErrArgument;
                           
                }
            else
                return KErrArgument;
                
    }
    
// -----------------------------------------------------------------------
//   Test case for obtaining the distance between 2 localities
// ----------------------------------------------------------------------- 
   TInt TTestLocality :: GetDistance1(CStifItemParser& aItem)
    {
            TInt lat1 = 0;
            TInt lon1 = 0;
            TInt lat2 = 0;
            TInt lon2 = 0;
            TInt haccuracy1 = 0;
            TInt haccuracy2 = 0;   
            TInt err1 = aItem.GetNextInt(lat1);
            TInt err2 = aItem.GetNextInt(lon1);
            TInt err3 = aItem.GetNextInt(lat2);
            TInt err4 = aItem.GetNextInt(lon2);
            TInt err5 = aItem.GetNextInt(haccuracy1);
            TInt err6 = aItem.GetNextInt(haccuracy2);
            TReal32 distance;
            TReal32 delta;
           
            if(!err1 && !err2 && !err3 && !err4 )
                {
                    
                    TCoordinate co_ord1(lat1,lon1);
                    TCoordinate co_ord2(lat2,lon2);
                    if(!err5 && !err6)
                        {
                             TLocality locality1(co_ord1,haccuracy1);
                             TLocality locality2(co_ord2,haccuracy2);
                             TInt error = locality1.Distance(locality2,distance,delta);
                             if(!error)
                                {
                                    return KErrNone;
                                }
				              else
				                return KErrGeneral;

                        }
	              else
	                return KErrArgument;
                }
              else
                return KErrArgument;
              
    }
    

    
// -----------------------------------------------------------------------
//   Test case for obtaining the bearing between 2 coordinates
// ----------------------------------------------------------------------- 

 TInt TTestLocality :: GetBearing(CStifItemParser& aItem)
    {
            TInt lat1 = 0;
            TInt lon1 = 0;
            TInt lat2 = 0;
            TInt lon2 = 0;
            //TInt bearing1 = 0;
            TReal32 bearing2 = 0;
            TInt err1 = aItem.GetNextInt(lat1);
            TInt err2 = aItem.GetNextInt(lon1);
            TInt err3 = aItem.GetNextInt(lat2);
            TInt err4 = aItem.GetNextInt(lon2);
             if(!err1 && !err2 && !err3 && !err4 )
                {
                    TCoordinate co_ord1(lat1,lon1);
                    TCoordinate co_ord2(lat2,lon2);
                      //TReal32 bearing = static_cast<TReal32>(bearing1);
                    TInt error = co_ord1.BearingTo(co_ord2,bearing2);
                    if(!error)
                        {
                            return KErrNone;
                            
                        }
   	                else
	                return KErrGeneral;   
                }
             else 
                return KErrArgument;
            
           
    }
    
    
    
// -----------------------------------------------------------------------
//   Test case for obtaining the bearing between 2 localities
// ----------------------------------------------------------------------- 

 TInt TTestLocality :: GetBearing1(CStifItemParser& aItem)
    {
         TInt lat1 = 0;
            TInt lon1 = 0;
            TInt lat2 = 0;
            TInt lon2 = 0;
            TInt haccuracy1 = 0;
            TInt haccuracy2 = 0;   
            TInt err1 = aItem.GetNextInt(lat1);
            TInt err2 = aItem.GetNextInt(lon1);
            TInt err3 = aItem.GetNextInt(lat2);
            TInt err4 = aItem.GetNextInt(lon2);
            TInt err5 = aItem.GetNextInt(haccuracy1);
            TInt err6 = aItem.GetNextInt(haccuracy2);
            TReal32 bearing;
            TReal32 delta;
           
            if(!err1 && !err2 && !err3 && !err4 )
                {
                    
                    TCoordinate co_ord1(lat1,lon1);
                    TCoordinate co_ord2(lat2,lon2);
                    if(!err5 && !err6)
                        {
                             TLocality locality1(co_ord1,haccuracy1);
                             TLocality locality2(co_ord2,haccuracy2);
                             TInt error = locality1.BearingTo(locality2,bearing,delta);
                             if(!error)
                                {
                                    return KErrNone;
                                }
				             else
				                return KErrGeneral;
                        }
                    else
	                	return KErrArgument;
                }
              else
              	return KErrArgument;
    }
