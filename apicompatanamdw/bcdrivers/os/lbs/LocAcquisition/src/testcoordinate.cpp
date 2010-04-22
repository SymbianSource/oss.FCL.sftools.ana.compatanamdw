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
* Description:  Helper class for TCoordinate class
*
*/


// System Includes


// User Includes
#include "testcoordinate.h"

// Constant Declarations

    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ Default Constructor
// ---------------------------------------------------------------------------
//
TTestCoordinate ::TTestCoordinate (CStifLogger* aLog):iLog(aLog)
    {
        
    }

// ---------------------------------------------------------------------------
// C++ Destructor
// ---------------------------------------------------------------------------
//
TTestCoordinate ::~TTestCoordinate ()
    {
        
    }

// -----------------------------------------------------------------------------
// This method calls the respective constructor based on the number of arguments
// -----------------------------------------------------------------------------
//	
TInt TTestCoordinate ::CreateCoordinate(CStifItemParser& aItem)
    {
        TInt lat = 0;
	    TInt lon = 0;
	    TInt alt = 0;
	    
	    TInt error1 = aItem.GetNextInt(lat);
	    TInt error2 = aItem.GetNextInt(lon);
	    TInt error3 = aItem.GetNextInt(alt);
	     
	    if ( !error1 && !error2 && !error3 )
	        {
	        return Constructor2(lat,lon,alt);
	        }
	    else if ( !error1 && !error2 )
            {
            return Constructor1(lat,lon);
            }
        return DefaultConstructor();
        
	    /*  
	    if(aItem.GetNextInt(lat)!=KErrNone && aItem.GetNextInt(lon)!=KErrNone && aItem.GetNextInt(alt)!=KErrNone )
	        {
	            return Constructor2(lat,lon,alt);
	        }
	    else
	    
	    if(aItem.GetNextInt(lat)!=KErrNone && aItem.GetNextInt(lon)!=KErrNone )
	        {
	            return Constructor1(lat,lon);
	        }
	    
	    
	    else return DefaultConstructor();     
	    */
	    
    }

// ---------------------------------------------------------
// Default Constructor of TCoordinate
// ---------------------------------------------------------
//	
TInt TTestCoordinate :: DefaultConstructor()
    {
	TCoordinate co_ord;
	
    return KErrNone;
    }
    
 // -------------------------------------------------------------------
//  Constructor of TCoordinate with latitude & longtitude as parameters
// --------------------------------------------------------------------
//	   

TInt TTestCoordinate :: Constructor1( TReal64 aLatitude,TReal64 aLongitude)
    {
    TCoordinate co_ord( aLatitude, aLongitude );
    if ( co_ord.Latitude() != aLatitude || co_ord.Longitude() != aLongitude )
        {
        return KErrGeneral;
        }	
    else    
        {
        return KErrNone; 
        }
       
    }
    
// ---------------------------------------------------------
//  Constructor of TCoordinate with latitude,longtitude & altitude
//   as parameters
// ---------------------------------------------------------
//	   
  TInt TTestCoordinate :: Constructor2( TReal64 aLatitude,TReal64 aLongitude,TReal64 aAltitude)
    {
    TCoordinate co_ord( aLatitude, aLongitude, aAltitude );
    if ( co_ord.Latitude() != aLatitude || 
         co_ord.Longitude() != aLongitude || 
         co_ord.Altitude()!= aAltitude)
        {
        return KErrGeneral;
        }	    	
    else
        {
        return KErrNone;        
        }
    }
// ---------------------------------------------------------
//  
//  Test Case for setting the coordinate values
// ---------------------------------------------------------
//	    
    
    TInt TTestCoordinate :: SetCoordinate(CStifItemParser& aItem)
        {
            TInt lat = 0;
	        TInt lon = 0;
	        TInt alt = 0;
	    
	        TInt error1 = aItem.GetNextInt(lat);
	        TInt error2 = aItem.GetNextInt(lon);
	        TInt error3 = aItem.GetNextInt(alt);
	     
	        if ( !error1 && !error2 && !error3 )
	        {
	        return SetLatLonAlt(lat,lon,alt);
	        }
	        else if ( !error1 && !error2 )
            {
            return SetLatLon(lat,lon);
            }
	        else
	        return KErrArgument;
           
        }
        
        
// ---------------------------------------------------------
//  
//  Test case for setting latitude & longitude
// ---------------------------------------------------------
	         
     TInt TTestCoordinate :: SetLatLon(TReal64 aLatitude,TReal64 aLongitude)
        {      
            TCoordinate co_ord;
            co_ord.SetCoordinate(aLatitude,aLongitude);
            if ( co_ord.Latitude() != aLatitude || co_ord.Longitude() != aLongitude )
            {
            return KErrGeneral;
            }	
            else    
            {
            return KErrNone; 
            }
            
        }
        
// ---------------------------------------------------------
//  
//  Test case for setting latitude longitude & altitude
// ---------------------------------------------------------

    TInt TTestCoordinate :: SetLatLonAlt(TReal64 aLatitude,TReal64 aLongitude,TReal64 aAltitude)
        {
            TCoordinate co_ord;
            co_ord.SetCoordinate(aLatitude,aLongitude,aAltitude);
            if ( co_ord.Latitude() != aLatitude || 
            co_ord.Longitude() != aLongitude || 
            co_ord.Altitude()!= aAltitude)
            {
            return KErrGeneral;
            }	    	
            else
            {
            return KErrNone;        
            }  
        }
        
// ---------------------------------------------------------
//  
//  Test case for asssigning a new datum to the object
// ---------------------------------------------------------
        
      TInt TTestCoordinate :: SetGetDatum()
        {
            TPositionDatumId KPositionDatum = {0x101FAA35};
            TCoordinate co_ord;
            co_ord.SetDatum(KPositionDatum);
            if(co_ord.Datum()==KPositionDatum)
                {
                    return KErrNone;
                }
            else
            
                return KErrGeneral;
                
                
        }
        
// ---------------------------------------------------------
//  
//  Test case for obtaining the distance between two coordinates
// ---------------------------------------------------------
 
      TInt TTestCoordinate :: GetDistance(CStifItemParser& aItem)
        {
      
            TInt lat1 = 0;
            TInt lon1 = 0;
            TInt lat2 = 0;
            TInt lon2 = 0;
            TPtrC ptr;
            TReal32 distance = 0;
            TInt err1 = aItem.GetNextInt(lat1);
            TInt err2 = aItem.GetNextInt(lon1);
            TInt err3 = aItem.GetNextInt(lat2);
            TInt err4 = aItem.GetNextInt(lon2);
           // TInt err5 = aItem.GetNextString(ptr);
            //TLex lex(ptr);
            //lex.Val(dist);
            
            if(!err1 && !err2 && !err3 && !err4 )
                {
                    TCoordinate co_ord1(lat1,lon1);
                    TCoordinate co_ord2(lat2,lon2);
                    //TReal32 dist1 = static_cast<TReal32>(dist);
                    TInt error = co_ord2.Distance(co_ord1,distance);
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
            
        
        
// ---------------------------------------------------------
//  
//  Test case for obtaining the bearing between two coordinates
// ---------------------------------------------------------

      TInt TTestCoordinate :: GetBearing(CStifItemParser& aItem)
        {
            TInt lat1 = 0;
            TInt lon1 = 0;
            TInt lat2 = 0;
            TInt lon2 = 0;
            TReal32 bearing2 = 0;
            TInt err1 = aItem.GetNextInt(lat1);
            TInt err2 = aItem.GetNextInt(lon1);
            TInt err3 = aItem.GetNextInt(lat2);
            TInt err4 = aItem.GetNextInt(lon2);
            //TInt err5 = aItem.GetNextInt(bearing1);
            
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
        			return KErrArgument;
                }
            else 
        		return KErrArgument;
  
        }
        
// ---------------------------------------------------------
//  
// Test case for moving the coordinate object
// ---------------------------------------------------------
    
      TInt TTestCoordinate :: MoveTo(CStifItemParser& aItem)
        {
             TInt lat1 = 0;
             TInt lon1 = 0;
             TInt bearing1 = 0;
             TPtrC ptr;
             TReal32 distance;
             //TInt dist = 0;
             TInt err1 = aItem.GetNextInt(lat1);
             TInt err2 = aItem.GetNextInt(lon1);
             TInt err3 = aItem.GetNextInt(bearing1);
             TInt err4 = aItem.GetNextString(ptr);
             TLex  lex(ptr);
             lex.Val(distance);
             
             
             if(!err1 && !err2 && !err3 && !err4)
                {
                    TCoordinate co_ord1(lat1,lon1);
                    TReal32 bearing2 = static_cast<TReal32>(bearing1);
                    //TReal32 lat = 11; 
                    //TReal32 lon = 20;
                   // TReal32 distance = static_cast<TReal32>(dist);
                    TInt error = co_ord1.Move(bearing2,distance);
                    if(!error)
                        {   
                            //TReal32 lat2 = co_ord1.Latitude();
                            //TReal32 lon2 = co_ord1.Longitude();
                            //if((lat2==lat)&&(lon2==lon))
                            //if((co_ord1.Latitude()==lat) && (co_ord1.Longitude()==lon ))
                                return KErrNone;
                            
                        }
                    else
        			return KErrArgument; 
                }
          
              else
              return KErrArgument;   
             
             
             
        }
