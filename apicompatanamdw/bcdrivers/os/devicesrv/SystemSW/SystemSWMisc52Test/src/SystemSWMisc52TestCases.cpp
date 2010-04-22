/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description: This file contains hardcoded module implementation.
*
*/


// [INCLUDE FILES] - do not remove
#include <e32math.h>
#include <e32debug.h>
#include "SystemSWMisc52Test.h"
#include <HWRMLight.h>
#include <f32file.h>
// EXTERNAL DATA STRUCTURES
//extern  ?external_data;

// EXTERNAL FUNCTION PROTOTYPES  
//extern ?external_function( ?arg_type,?arg_type );

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def

// LOCAL CONSTANTS AND MACROS
//const ?type ?constant_var = ?constant;
//#define ?macro_name ?macro_def

// MODULE DATA STRUCTURES
//enum ?declaration
//typedef ?declaration

// LOCAL FUNCTION PROTOTYPES
//?type ?function_name( ?arg_type, ?arg_type );

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;

// ============================= LOCAL FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// ?function_name ?description.
// ?description
// Returns: ?value_1: ?description
//          ?value_n: ?description_line1
//                    ?description_line2
// -----------------------------------------------------------------------------
//
/*
?type ?function_name(
    ?arg_type arg,  // ?description
    ?arg_type arg)  // ?description
    {

    ?code  // ?comment

    // ?comment
    ?code
    }
*/

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::Case
// Returns a test case by number.
//
// This function contains an array of all available test cases 
// i.e pair of case name and test function. If case specified by parameter
// aCaseNumber is found from array, then that item is returned.
// 
// The reason for this rather complicated function is to specify all the
// test cases only in one place. It is not necessary to understand how
// function pointers to class member functions works when adding new test
// cases. See function body for instructions how to add new test case.
// -----------------------------------------------------------------------------
//
const TCaseInfo CSystemSWMisc52Test::Case ( 
    const TInt aCaseNumber ) const 
     {

    /**
    * To add new test cases, implement new test case function and add new 
    * line to KCases array specify the name of the case and the function 
    * doing the test case
    * In practice, do following
    * 1) Make copy of existing test case function and change its name
    *    and functionality. Note that the function must be added to 
    *    SystemSWMisc52Test.cpp file and to SystemSWMisc52Test.h 
    *    header file.
    *
    * 2) Add entry to following KCases array either by using:
    *
    * 2.1: FUNCENTRY or ENTRY macro
    * ENTRY macro takes two parameters: test case name and test case 
    * function name.
    *
    * FUNCENTRY macro takes only test case function name as a parameter and
    * uses that as a test case name and test case function name.
    *
    * Or
    *
    * 2.2: OOM_FUNCENTRY or OOM_ENTRY macro. Note that these macros are used
    * only with OOM (Out-Of-Memory) testing!
    *
    * OOM_ENTRY macro takes five parameters: test case name, test case 
    * function name, TBool which specifies is method supposed to be run using
    * OOM conditions, TInt value for first heap memory allocation failure and 
    * TInt value for last heap memory allocation failure.
    * 
    * OOM_FUNCENTRY macro takes test case function name as a parameter and uses
    * that as a test case name, TBool which specifies is method supposed to be
    * run using OOM conditions, TInt value for first heap memory allocation 
    * failure and TInt value for last heap memory allocation failure. 
    */ 

    static TCaseInfoInternal const KCases[] =
        {
        // [test cases entries] - do not remove
        
        ENTRY( "[Light] LightBlinkTestL", CSystemSWMisc52Test::LightBlinkTestL),
        ENTRY( "[Light] LightBlinkTest2L", CSystemSWMisc52Test::LightBlinkTest2L),
        ENTRY( "[Light] SetLightColorTestL", CSystemSWMisc52Test::SetLightColorTestL),
        ENTRY( "[Light] SetLightDefaultColorTestL", CSystemSWMisc52Test::SetLightDefaultColorTestL),
        ENTRY( "[Light] LightOnTestL", CSystemSWMisc52Test::LightOnTestL),
        ENTRY( "[Light] LightOnTest2L", CSystemSWMisc52Test::LightOnTest2L),
        //ENTRY( "[Sysutils] GetAttributeTestL         ",GetAttributeTestL          ),
        ENTRY( "[Sysutils] GetModelCodeTestL         ",CSystemSWMisc52Test::GetModelCodeTestL          ),
        ENTRY( "[Sysutils] GetModelNameTestL         ",CSystemSWMisc52Test::GetModelNameTestL          ),
        ENTRY( "[Sysutils] GetOSVersionTestL         ",CSystemSWMisc52Test::GetOSVersionTestL          ),
        ENTRY( "[Sysutils] GetOSVersionTestL         ",CSystemSWMisc52Test::GetOSVersionTestL          ),
        ENTRY( "[Sysutils] GetRevisionIDTestL        ",CSystemSWMisc52Test::GetRevisionIDTestL         ),
        ENTRY( "[Sysutils] GetUIPlatformNameTestL    ",CSystemSWMisc52Test::GetUIPlatformNameTestL     ),
        ENTRY( "[Sysutils] GetManufacturerNameTestL  ",CSystemSWMisc52Test::GetManufacturerNameTestL   ),
        ENTRY( "[Sysutils] GetDefaultDeviceNameTestL ",CSystemSWMisc52Test::GetDefaultDeviceNameTestL  ),
        ENTRY( "[Sysutils] GetUIPlatformVersionTestL ",CSystemSWMisc52Test::GetUIPlatformVersionTestL  ),
        ENTRY( "[Sysutils] GetUIPlatformVersionTest2L",CSystemSWMisc52Test::GetUIPlatformVersionTest2L ),
        ENTRY( "[FeatureDiscovery API] TFeatureSet",CSystemSWMisc52Test::TFeatureSetTestL ),
        ENTRY( "[FeatureDiscovery API] AppendTestL",CSystemSWMisc52Test::AppendTestL ),
        ENTRY( "[FeatureDiscovery API] IsFeatureSupported",CSystemSWMisc52Test::IsFeatureSupportedTestL ),
        ENTRY( "[FeatureDiscovery API] AreAllFeaturesSupported",CSystemSWMisc52Test::AreAllFeaturesSupportedTestL ),
        ENTRY( "[FeatureDiscovery API] IsFeatureSupported",CSystemSWMisc52Test::IsFeatureSupportedTestL ),
        ENTRY( "[FeatureDiscovery API] FeaturesSupported ",CSystemSWMisc52Test::FeaturesSupportedTestL  ),
        ENTRY( "[FeatureDiscovery API] FeaturesSupportedL",CSystemSWMisc52Test::FeaturesSupportedLTestL ),
        ENTRY( "[FeatureDiscovery API] IsSupported       ",CSystemSWMisc52Test::IsFeatureSupportedLTestL        ),                        
        ENTRY( "[Sysutils] MMCSpaceBelowCriticalLevelTestL",CSystemSWMisc52Test::MMCSpaceBelowCriticalLevelTestL ),
        ENTRY( "[Sysutils] GetPRInformationTestL",CSystemSWMisc52Test::GetPRInformationTestL ),
        
        
        // Example how to use OOM functionality
        //OOM_ENTRY( "Loop test with OOM", CSystemSWMisc52Test::LoopTest, ETrue, 2, 3),
        //OOM_FUNCENTRY( CSystemSWMisc52Test::PrintTest, ETrue, 1, 3 ),
        };

    // Verify that case number is valid
    if( (TUint) aCaseNumber >= sizeof( KCases ) / 
                               sizeof( TCaseInfoInternal ) )
        {
        // Invalid case, construct empty object
        TCaseInfo null( (const TText*) L"" );
        null.iMethod = NULL;
        null.iIsOOMTest = EFalse;
        null.iFirstMemoryAllocation = 0;
        null.iLastMemoryAllocation = 0;
        return null;
        } 

    // Construct TCaseInfo object and return it
    TCaseInfo tmp ( KCases[ aCaseNumber ].iCaseName );
    tmp.iMethod = KCases[ aCaseNumber ].iMethod;
    tmp.iIsOOMTest = KCases[ aCaseNumber ].iIsOOMTest;
    tmp.iFirstMemoryAllocation = KCases[ aCaseNumber ].iFirstMemoryAllocation;
    tmp.iLastMemoryAllocation = KCases[ aCaseNumber ].iLastMemoryAllocation;
    return tmp;

    }

// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::PrintTest
// Simple printing to UI test.
// -----------------------------------------------------------------------------
//
TInt CSystemSWMisc52Test::PrintTest( 
    TTestResult& aResult )
    {
     /* Simple print test */
    _LIT( KPrintTest, "PrintTest" );
    _LIT( KEnter, "Enter" );
    _LIT( KOnGoing, "On-going" );
    _LIT( KExit, "Exit" );

    TestModuleIf().Printf( 0, KPrintTest, KEnter );
           
    TestModuleIf().Printf( 1, KPrintTest, KOnGoing );
    
    TestModuleIf().Printf( 0, KPrintTest, KExit );

    // Test case passed

    // Sets test case result and description(Maximum size is KStifMaxResultDes)
    _LIT( KDescription, "PrintTest passed" );
    aResult.SetResult( KErrNone, KDescription );

    // Case was executed
    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::LightBlinkL
// 
// -----------------------------------------------------------------------------
//
TInt CSystemSWMisc52Test::LightBlinkTestL( TTestResult& aResult )
{
		
		CHWRMLight* light = CHWRMLight::NewL();
		THWRMLightColor color;
		color.iRed= 75;
		color.iGreen= 25;
		color.iBlue= 100;
		TInt retval = KErrNone;
		TRAP(retval,light->LightBlinkL(CHWRMLight::EPrimaryDisplayAndKeyboard, 4*1000, color));
		delete light;
		
		if (retval == KErrNotSupported)
				retval = KErrNone;
					
		return retval;
    
}
// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::LightBlinkL
// 
// -----------------------------------------------------------------------------
//
TInt CSystemSWMisc52Test::LightBlinkTest2L( TTestResult& aResult )
{
		
		CHWRMLight* light = CHWRMLight::NewL();
		THWRMLightColor color;
		color.iRed= 75;
		color.iGreen= 25;
		color.iBlue= 100;
		TInt retval = KErrNone;
		TRAP(retval,light->LightBlinkL(CHWRMLight::EPrimaryDisplayAndKeyboard, 4*1000, 500, 500, 20, color));
			delete light;
			
		if (retval == KErrNotSupported)
				retval = KErrNone;
				
		return retval;
    
}
// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::SetLightColorL
// 
// -----------------------------------------------------------------------------
//
TInt CSystemSWMisc52Test::SetLightColorTestL( TTestResult& aResult )
{
		
		CHWRMLight* light = CHWRMLight::NewL();
		THWRMLightColor color;
		color.iRed= 75;
		color.iGreen= 25;
		color.iBlue= 100;
		TInt retval = KErrNone;
		TRAP(retval,light->SetLightColorL(CHWRMLight::EPrimaryDisplay, color));
			delete light;
			
		if (retval == KErrNotSupported)
				retval = KErrNone;
				
		return retval;
    
}
// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::SetLightDefaultColorL
// 
// -----------------------------------------------------------------------------
//
TInt CSystemSWMisc52Test::SetLightDefaultColorTestL( TTestResult& aResult )
{
		
		CHWRMLight* light = CHWRMLight::NewL();
		
		TInt retval = KErrNone;
		TRAP(retval,light->SetLightDefaultColorL(CHWRMLight::EPrimaryDisplay));
			delete light;
			
		if (retval == KErrNotSupported)
				retval = KErrNone;
				
		return retval;
    
}
// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::LightOnL
// 
// -----------------------------------------------------------------------------
//
TInt CSystemSWMisc52Test::LightOnTestL( TTestResult& aResult )
{
		
		CHWRMLight* light = CHWRMLight::NewL();
		THWRMLightColor color;
		color.iRed= 75;
		color.iGreen= 25;
		color.iBlue= 100;
		TInt retval = KErrNone;
		TRAP(retval,light->LightOnL(CHWRMLight::EPrimaryDisplay, 4*1000, color));
			delete light;
		
		if (retval == KErrNotSupported)
				retval = KErrNone;
				
		return retval;
    
}
// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::LightOnL
// 
// -----------------------------------------------------------------------------
//
TInt CSystemSWMisc52Test::LightOnTest2L( TTestResult& aResult )
{
		
		CHWRMLight* light = CHWRMLight::NewL();
		THWRMLightColor color;
		color.iRed= 75;
		color.iGreen= 25;
		color.iBlue= 100;
		TInt retval = KErrNone;
		TRAP(retval,light->LightOnL(CHWRMLight::EPrimaryDisplayAndKeyboard, 4*1000, 20, ETrue, color));
			delete light;
			
		if (retval == KErrNotSupported)
				retval = KErrNone;
				
		return retval;
    
}


// Sysutil api testcases

// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::GetAttributeTestL
// 
// -----------------------------------------------------------------------------
//
TInt  CSystemSWMisc52Test::GetAttributeTestL( TTestResult& aResult )   
	{
		//CDeviceTypeInformation* attribs = SysUtil::GetDeviceTypeInfoL();
		//TPtrC16 actualValue;
	}     

// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::GetModelCode
// 
// -----------------------------------------------------------------------------
//
TInt  CSystemSWMisc52Test::GetModelCodeTestL( TTestResult& aResult ) 
{
		CDeviceTypeInformation* attribs = SysUtil::GetDeviceTypeInfoL();
		TPtrC16 modelCodeValue;
		TInt retVal = attribs->GetModelCode(modelCodeValue);
		_LIT(KResult,"Actual error = %d\n");
		iLog->Log(KResult, retVal);
		_LIT(KDescriptorResult,"descriptor value = %S \n");
		iLog->Log(KDescriptorResult, &modelCodeValue);
		//RDebug::Printf("Actual value = %S\n", &actualValue);

		delete attribs;
		if ( 1 == retVal )
			{
				return KErrNone;
			}
		else
			{
				return retVal;
			}
}          
// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::GetModelName
// 
// -----------------------------------------------------------------------------
//
TInt  CSystemSWMisc52Test::GetModelNameTestL( TTestResult& aResult )      
{
		CDeviceTypeInformation* attribs = SysUtil::GetDeviceTypeInfoL();
		TPtrC16 modelName;
		TInt retVal = attribs->GetModelName(modelName);
		_LIT(KResult,"Actual error = %d\n");
		iLog->Log(KResult, retVal);
		_LIT(KDescriptorResult,"descriptor value = %S \n");
		iLog->Log(KDescriptorResult, &modelName);
		RDebug::Printf("descriptor value = %S\n", &modelName);
		RDebug::Printf("Actual error = %d\n", retVal);
		delete attribs;
		//return retVal;
		if ( 1 == retVal )
			{
				return KErrNone;
			}
		else
			{
				return retVal;
			}	
}    
// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::GetOSVersion
// 
// -----------------------------------------------------------------------------
//
TInt  CSystemSWMisc52Test::GetOSVersionTestL( TTestResult& aResult )    
{
		CDeviceTypeInformation* attribs = SysUtil::GetDeviceTypeInfoL();
		TPtrC16 osVersion;
		TInt retVal = attribs->GetOSVersion(osVersion);
		_LIT(KResult,"Actual error = %d\n");
		iLog->Log(KResult, retVal);
		_LIT(KDescriptorResult,"descriptor value = %S \n");
		iLog->Log(KDescriptorResult, &osVersion);
		RDebug::Printf("Actual error = %d\n", retVal);
			RDebug::Printf("descriptor value = %S\n", &osVersion);
		delete attribs;
		if ( 1 == retVal )
			{
				return KErrNone;
			}
		else
			{
				return retVal;
			}	
}         
// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::GetOSVersion
// 
// -----------------------------------------------------------------------------
//
TInt  CSystemSWMisc52Test::GetOSVersionTest2L( TTestResult& aResult )   
	{
		CDeviceTypeInformation* attribs = SysUtil::GetDeviceTypeInfoL();
		TUint16 majorValue, minorValue;
		TInt retVal = attribs->GetOSVersion(majorValue, minorValue);
				_LIT(KResult,"Actual error = %d\n");
		iLog->Log(KResult, retVal);
		_LIT(KDescriptorResult,"major value = %d and minor value = %d \n");
		iLog->Log(KDescriptorResult, majorValue,minorValue);
		RDebug::Printf("Actual error = %d\n", retVal);
			RDebug::Printf("major value = %d and minor value = %d \n", majorValue,minorValue);
		delete attribs;
		if ( 1 == retVal )
			{
				return KErrNone;
			}
		else
			{
				return retVal;
			}		
		return retVal;
}       
// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::GetRevisionID
// 
// -----------------------------------------------------------------------------
//
TInt  CSystemSWMisc52Test::GetRevisionIDTestL( TTestResult& aResult )  
{
		CDeviceTypeInformation* attribs = SysUtil::GetDeviceTypeInfoL();
		TPtrC16 revisionID;
		TInt retVal = attribs->GetRevisionID(revisionID);
				_LIT(KResult,"Actual error = %d\n");
		iLog->Log(KResult, retVal);
		_LIT(KDescriptorResult,"descriptor value = %S \n");
		iLog->Log(KDescriptorResult, &revisionID);
		RDebug::Printf("Actual error = %d\n", retVal);
			RDebug::Printf("descriptor value = %S\n", &revisionID);
		delete attribs;
		if ( 1 == retVal )
			{
				return KErrNone;
			}
		else
			{
				return retVal;
			}	
}       
// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::GetUIPlatformName
// 
// -----------------------------------------------------------------------------
//
TInt  CSystemSWMisc52Test::GetUIPlatformNameTestL( TTestResult& aResult )
{
		CDeviceTypeInformation* attribs = SysUtil::GetDeviceTypeInfoL();
		TPtrC16 platformName;
		TInt retVal = attribs->GetUIPlatformName(platformName);
				_LIT(KResult,"Actual error = %d\n");
		iLog->Log(KResult, retVal);
		_LIT(KDescriptorResult,"descriptor value = %S \n");
		iLog->Log(KDescriptorResult, &platformName);
		RDebug::Printf("Actual error = %d\n", retVal);
			RDebug::Printf("descriptor value = %S\n", &platformName);
		delete attribs;
		if ( 1 == retVal )
			{
				return KErrNone;
			}
		else
			{
				return retVal;
			}	
}       
// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::GetManufacturerName
// 
// -----------------------------------------------------------------------------
//
TInt  CSystemSWMisc52Test::GetManufacturerNameTestL( TTestResult& aResult )  
{
		CDeviceTypeInformation* attribs = SysUtil::GetDeviceTypeInfoL();
		TPtrC16 manufactureName;
		TInt retVal = attribs->GetManufacturerName(manufactureName);
				_LIT(KResult,"Actual error = %d\n");
		iLog->Log(KResult, retVal);
		_LIT(KDescriptorResult,"descriptor value = %S \n");
		iLog->Log(KDescriptorResult, &manufactureName);
		RDebug::Printf("Actual error = %d\n", retVal);
			RDebug::Printf("descriptor value = %S\n", &manufactureName);
		delete attribs;
		if ( 1 == retVal )
			{
				return KErrNone;
			}
		else
			{
				return retVal;
			}	
} 
// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::GetDefaultDeviceName
// 
// -----------------------------------------------------------------------------
//
TInt  CSystemSWMisc52Test::GetDefaultDeviceNameTestL( TTestResult& aResult ) 
{
		CDeviceTypeInformation* attribs = SysUtil::GetDeviceTypeInfoL();
		TPtrC16 deviceName;
		TInt retVal = attribs->GetDefaultDeviceName(deviceName);
				_LIT(KResult,"Actual error = %d\n");
		iLog->Log(KResult, retVal);
		_LIT(KDescriptorResult,"descriptor value = %S \n");
		iLog->Log(KDescriptorResult, &deviceName);
					RDebug::Printf("descriptor value = %S\n", &deviceName);

		RDebug::Printf("Actual error = %d\n", retVal);
		delete attribs;
		if ( 1 == retVal )
			{
				return KErrNone;
			}
		else
			{
				return retVal;
			}	
} 
// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::GetUIPlatformVersion
// 
// -----------------------------------------------------------------------------
//
TInt  CSystemSWMisc52Test::GetUIPlatformVersionTestL( TTestResult& aResult ) 
{
		CDeviceTypeInformation* attribs = SysUtil::GetDeviceTypeInfoL();
		TPtrC16 uiPlatVer;
		TInt retVal = attribs->GetUIPlatformVersion(uiPlatVer);
				_LIT(KResult,"Actual error = %d\n");
		iLog->Log(KResult, retVal);
		_LIT(KDescriptorResult,"descriptor value = %S \n");
		iLog->Log(KDescriptorResult, &uiPlatVer);
		RDebug::Printf("Actual error = %d\n", retVal);
			RDebug::Printf("descriptor value = %S\n", &uiPlatVer);
		delete attribs;
		if ( 1 == retVal )
			{
				return KErrNone;
			}
		else
			{
				return retVal;
			}	
} 
// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::GetUIPlatformVersion
// 
// -----------------------------------------------------------------------------
//
TInt  CSystemSWMisc52Test::GetUIPlatformVersionTest2L( TTestResult& aResult )
{
		CDeviceTypeInformation* attribs = SysUtil::GetDeviceTypeInfoL();
		TUint16 majorValue, minorValue;
		TInt retVal = attribs->GetUIPlatformVersion(majorValue, minorValue);
				_LIT(KResult,"Actual error = %d\n");
		iLog->Log(KResult, retVal);
		_LIT(KDescriptorResult,"major value = %d and minor value = %d \n");
		iLog->Log(KDescriptorResult, majorValue,minorValue);
		RDebug::Printf("Actual error = %d\n", retVal);
RDebug::Printf("major value = %d and minor value = %d \n", majorValue,minorValue);
	
			delete attribs;
			return KErrNone;
		/*if ( 1 == retVal )
			{
				return KErrNone;
			}
		else
			{
				return retVal;
			}	*/
} 
//FeatureDiscovery API

// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::Append
// 
// -----------------------------------------------------------------------------
//
TInt  CSystemSWMisc52Test::AppendTestL( TTestResult& aResult )
	{
		TFeatureSet* obj = new(ELeave) TFeatureSet();
		TUid feature;
		TInt fture(1);
		feature = TUid::Uid(fture);
		TInt retVal = obj->Append(feature);
		RDebug::Printf("Return Valure = %d\n", retVal);
					_LIT(KResult,"Actual error = %d\n");
		iLog->Log(KResult, retVal);
			delete obj;
			return retVal;
	}


// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::TFeatureSet
// 
// -----------------------------------------------------------------------------
//
TInt  CSystemSWMisc52Test::TFeatureSetTestL( TTestResult& aResult )
	{
		TFeatureSet* obj;
		TInt res;
		TRAP(res, obj = new(ELeave) TFeatureSet());
		delete obj;
		return res;
	}


// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::IsFeatureSupported
// 
// -----------------------------------------------------------------------------
//	
TInt  CSystemSWMisc52Test::IsFeatureSupportedTestL( TTestResult& aResult )
	{		
		TFeatureSet* obj = new(ELeave) TFeatureSet();
		TUid feature;
		TInt fture(1);
		feature = TUid::Uid(fture);
		obj->Append(feature);
		TBool isFture = obj->IsFeatureSupported(feature);
		RDebug::Printf("Return Valure = %d\n", isFture);
			_LIT(KResult,"Actual error = %d\n");
		iLog->Log(KResult, isFture);
			delete obj;
			return (isFture);
	}
	
// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::AreAllFeaturesSupported
// 
// -----------------------------------------------------------------------------
//	
TInt  CSystemSWMisc52Test::AreAllFeaturesSupportedTestL( TTestResult& aResult )
	{		
		TFeatureSet* obj = new(ELeave) TFeatureSet();
		TUid feature;
		TInt fture(1);
		feature = TUid::Uid(fture);
		obj->Append(feature);
		TBool areSupported = obj->AreAllFeaturesSupported();
		RDebug::Printf("Return Valure = %d\n", areSupported);
				_LIT(KResult,"Actual error = %d\n");
		iLog->Log(KResult, areSupported);
			delete obj;
			return (areSupported);
	}	
	
// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::IsSupported
// 
// -----------------------------------------------------------------------------
//	
TInt  CSystemSWMisc52Test::IsSupportedTestL( TTestResult& aResult )
	{		
		CFeatureDiscovery* obj = CFeatureDiscovery::NewL();
		TInt fture(1);
		TBool ret = obj->IsSupported(fture);
		
		RDebug::Printf("Return Valure = %d\n", ret);
	_LIT(KResult,"Actual error = %d\n");
		iLog->Log(KResult, ret);			
			delete obj;
			return (ret);
	}	
// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::FeaturesSupportedL
// 
// -----------------------------------------------------------------------------
//	
TInt  CSystemSWMisc52Test::FeaturesSupportedLTestL( TTestResult& aResult )
	{		
		//CFeatureDiscovery* obj = CFeatureDiscovery::NewL();
			TFeatureSet* feature = new(ELeave) TFeatureSet();
			TUid id;
			id.iUid = 0x0001869C;// = new(ELeave) TFeatureSet();
			_LIT(KAppResult,"append Actual error = %d\n");
		TInt ret = feature->Append(id);
		iLog->Log(KAppResult, ret);		
		
		TRAP(ret,CFeatureDiscovery::FeaturesSupportedL(*feature));
	_LIT(KResult,"Actual error = %d\n");
		iLog->Log(KResult, ret);			
		RDebug::Printf("Return Valure = %d\n", ret);
			//delete obj;
			return (ret);
	}	

// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::FeaturesSupported
// 
// -----------------------------------------------------------------------------
//	
TInt  CSystemSWMisc52Test::FeaturesSupportedTestL( TTestResult& aResult )
	{		
		CFeatureDiscovery* obj = CFeatureDiscovery::NewL();
			TFeatureSet* feature = new(ELeave) TFeatureSet();
			TUid id;
			id.iUid = 0x0001869C;
			_LIT(KAppResult,"append Actual error = %d\n");
		TInt ret = feature->Append(id);
		iLog->Log(KAppResult, ret);			
		ret = obj->FeaturesSupported(*feature);
	_LIT(KResult,"Actual error = %d\n");
		iLog->Log(KResult, ret);			
		RDebug::Printf("Return Valure = %d\n", ret);
			delete obj;
			//sdelete feature;
			return (ret);
	}	


// -----------------------------------------------------------------------------
// CSystemSWMisc52Test::IsFeatureSupportedTestL
// 
// -----------------------------------------------------------------------------
//	
TInt  CSystemSWMisc52Test::IsFeatureSupportedLTestL( TTestResult& aResult )
	{		
		//CFeatureDiscovery* obj = CFeatureDiscovery::NewL();
			//TFeatureSet* obj = new(ELeave) TFeatureSet();
			TUid feature;
		TInt fture(1);
		feature = TUid::Uid(fture);
		
		TBool ret = CFeatureDiscovery::IsFeatureSupportedL(feature);
		
		RDebug::Printf("Return Valure = %d\n", ret);
	_LIT(KResult,"Actual error = %d\n");
		iLog->Log(KResult, ret);	
				if ( 1 == ret )
			{
				return KErrNone;
			}
		else
			{
				return ret;
			}			
			
	}	
TInt  CSystemSWMisc52Test::MMCSpaceBelowCriticalLevelTestL( TTestResult& aResult )		
{
		RFs fileSess;
		fileSess.Connect();
		TBool res = SysUtil::MMCSpaceBelowCriticalLevelL(&fileSess,0);
			fileSess.Close();
		if ( 1 == res )
			{
				return KErrNone;
			}
		else
			{
				return res;
			}	
		
}       
TInt  CSystemSWMisc52Test::GetPRInformationTestL( TTestResult& aResult )		
{
		TBuf<64> prInfo;
		_LIT16(KJunk,"xxxxx");
		prInfo.Insert(0,KJunk);
		TInt res = SysUtil::GetPRInformation(prInfo);
			_LIT(KResult,"Actual error = %d\n");
		iLog->Log(KResult, res);
		return res;
}       


//  End of File
