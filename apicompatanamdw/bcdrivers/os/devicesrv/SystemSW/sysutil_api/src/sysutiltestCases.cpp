/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/

/* Changed by Vaibhav - 13Aug07 for Removing CodeScanner Warnings - High/medium */


// INCLUDE FILES
#include <e32math.h>
#include "sysutiltest.h"

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
// Csysutiltest::Case
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
const TCaseInfo Csysutiltest::Case ( 
    const TInt aCaseNumber ) const 
     {

    /**
    * To add new test cases, implement new test case function and add new 
    * line to KCases array specify the name of the case and the function 
    * doing the test case
    * In practice, do following
    * 1) Make copy of existing test case function and change its name
    *    and functionality. Note that the function must be added to 
    *    sysutiltest.cpp file and to sysutiltest.h 
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
        // To add new test cases, add new items to this array
        ENTRY( "[Sysutil] GetSWVersion", GetSWVersion ),
        ENTRY( "[Sysutil] GetLangSWVersion", GetLangSWVersion ),
        ENTRY( "[Sysutil] GetLangSWVersion", GetLangSWVersion ),
        ENTRY( "[Sysutil] GetLangVersion", GetLangVersion ),
        ENTRY( "[Sysutil] FFSSpaceBelowCriticalLevelL", FFSSpaceBelowCriticalLevelL ),
        ENTRY( "[Sysutil] MMCSpaceBelowCriticalLevelL", MMCSpaceBelowCriticalLevelL ),
        ENTRY( "[Sysutil] DiskSpaceBelowCriticalLevelL", DiskSpaceBelowCriticalLevelL ),
        
        //ENTRY( "Loop test", LoopTest ),
        // Example how to use OOM functionality
        //OOM_ENTRY( "Loop test with OOM", LoopTest, ETrue, 2, 3),
        //OOM_FUNCENTRY( PrintTest, ETrue, 1, 3 ),
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
// ?classname::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
?type ?classname::?member_function(
   ?arg_type arg,
   ?arg_type arg )
   {

   ?code

   }
*/

// ---------------------------------------------------------
// Csysutiltest::GetSWVersion
// Returns: KErrNone
// ---------------------------------------------------------
TInt Csysutiltest::GetSWVersion(TTestResult& aResult)
{
	TInt err=KErrNone;
	
	TestModuleIf().Printf( 0, _L("RunTestCase"), 
	    _L("SysUtil::GetSWVersion"));

	aResult.iResult = KErrNone;
	
	_LIT16(dummy,"xxxxx");

	TBuf16<KSysUtilVersionTextLength> aVersion;
	
	aVersion.Insert(0,dummy);

	/* TInt fileErr = CheckIsFileExist( _L("Z:\\system\\versions\\sw.txt")); Tek Path changed */
	TInt fileErr = CheckIsFileExist( _L("Z:\\resource\\versions\\sw.txt"));
	
	err = SysUtil::GetSWVersion( aVersion );

	if ( !(fileErr != KErrNone && err == fileErr) )
	{
		if ( aVersion == dummy ) 
		{
			aResult.iResultDes.Copy( _L("Get SW version failed") );
			aResult.iResult = err;				
		}
	}

	return KErrNone;
}

// ---------------------------------------------------------
// Csysutiltest::GetLangSWVersion
// Returns: KErrNone
// ---------------------------------------------------------
TInt Csysutiltest::GetLangSWVersion(TTestResult& aResult)
{
	TInt err=KErrNone;

	_LIT16(KDummy,"xxxxx");

	TestModuleIf().Printf( 0, _L("RunTestCase"), 
	    _L("SysUtil::GetLangSWVersion"));

	aResult.iResult = KErrNone;

	TBuf16<KSysUtilVersionTextLength> aVersion;
	
	aVersion.Insert(0,KDummy);

	/* TInt fileErr = CheckIsFileExist( _L("Z:\\system\\versions\\langsw.txt")); TeK Path changed */
    TInt fileErr = CheckIsFileExist( _L("Z:\\resource\\versions\\langsw.txt"));
    
	err = SysUtil::GetLangSWVersion( aVersion );


	if ( !(fileErr != KErrNone && err == fileErr) )
	{
		if ( aVersion == KDummy ) 
		{
			aResult.iResultDes.Copy( _L("Get lang SW version failed") );
			aResult.iResult = err;				
		}
	} else
	{
		aResult.iResultDes.Copy( _L("Langsw.txt is missing, should be included to base packets") );		
	}

	return KErrNone;
}

// ---------------------------------------------------------
// Csysutiltest::GetLangVersion
// Returns: KErrNone
// ---------------------------------------------------------
TInt Csysutiltest::GetLangVersion(TTestResult& aResult)
{
	TInt err=KErrNone;

	_LIT16(dummy,"xxxxx");

	TestModuleIf().Printf( 0, _L("RunTestCase"), 
	    _L("SysUtil::GetLangVersion"));

	aResult.iResult = KErrNone;

	TBuf16<25> aVersion;
	
	aVersion.Insert(0,dummy);

	/* TInt fileErr = CheckIsFileExist( _L("Z:\\system\\versions\\lang.txt")); TeK Path changed */
	TInt fileErr = CheckIsFileExist( _L("Z:\\resource\\versions\\lang.txt"));
	
	/* This test is not valid if file does not exist
	 * Reason for missing file is that "english engineering" package
	 * does not include that. (TeK 19.8.2005)
	 */
	if(fileErr == KErrNone)
	{
		err = SysUtil::GetLangVersion( aVersion );

		if ( err != KErrNone )
		{
			 aResult.iResultDes.Copy( _L("Get lang version value failed") );
			 aResult.iResult = err;				
		} 
		
	}
	else
	{
		aResult.iResultDes.Copy( _L("Lang.txt is missing. GetLangVersion skipped") );		
	}

	return KErrNone;
}

// ---------------------------------------------------------
// Csysutiltest::FFSSpaceBelowCriticalLevelL
// Returns: KErrNone
// ---------------------------------------------------------
TInt Csysutiltest::FFSSpaceBelowCriticalLevelL(TTestResult& aResult)
{
	TBool bStatus = EFalse;

	TestModuleIf().Printf( 0, _L("RunTestCase"), 
	    _L("SysUtil::FFSSpaceBelowCriticalLevelL"));

	aResult.iResult = KErrNone;
	bStatus = SysUtil::FFSSpaceBelowCriticalLevelL( NULL, 0 );

	if ( bStatus )
		{
		aResult.iResultDes.Copy( _L("FFSpaceBelowCriticalLevel = TRUE") );
		}
	else
		{
		aResult.iResultDes.Copy( _L("FFSpaceBelowCriticalLevel = FALSE") );		
		}
	
	return KErrNone;
}

// ---------------------------------------------------------
// Csysutiltest::MMCSpaceBelowCriticalLevelL
// Returns: KErrNone
// ---------------------------------------------------------
TInt Csysutiltest::MMCSpaceBelowCriticalLevelL(TTestResult& aResult)
{

	TInt err=KErrNone;
	TBool bStatus = EFalse;

	TestModuleIf().Printf( 0, _L("RunTestCase"), 
	    _L("SysUtil::MMCSpaceBelowCriticalLevelL"));

	aResult.iResult = KErrNone;

	TRAP(err, bStatus = SysUtil::MMCSpaceBelowCriticalLevelL( NULL, 0 ) );

	if ( err == KErrNotSupported )
		{
		aResult.iResultDes.Copy( _L("System has no MMC drive support") );		
		aResult.iResult = err;
		}
	else if ( err == KErrNotReady )
		{
		aResult.iResultDes.Copy( _L("MMC drive contains no media") );
		aResult.iResult = err;
		}
	else 
		{
		if ( bStatus )
			{
			aResult.iResultDes.Copy( _L("MMCSpaceBelowCriticalLevel = TRUE") );
			}
		else
			{
			aResult.iResultDes.Copy( _L("MMCSpaceBelowCriticalLevel = FALSE") );
			}
		}

	return KErrNone;
}

// ---------------------------------------------------------
// Csysutiltest::DiskSpaceBelowCriticalLevelL
// Returns: KErrNone
// ---------------------------------------------------------
TInt Csysutiltest::DiskSpaceBelowCriticalLevelL(TTestResult& aResult)
{
	TInt err=KErrNone;
	TBool bStatus = EFalse;

	TestModuleIf().Printf( 0, _L("RunTestCase"), 
	    _L("SysUtil::DiskSpaceBelowCriticalLevelL"));

	aResult.iResult = KErrNone;

	TRAP(err, bStatus = SysUtil::DiskSpaceBelowCriticalLevelL( NULL, 0, EDriveZ ) );

	if ( err == KErrNotSupported )
		{
		aResult.iResultDes.Copy( _L("System does not have this drive") );		
		aResult.iResult = err;
		}
	else if ( err == KErrNotReady )
		{
		aResult.iResultDes.Copy( _L("Drive contains no media") );
		aResult.iResult = err;
		}
	else 
		{
		if ( bStatus )
			{
			aResult.iResultDes.Copy( _L("DiskSpaceBelowCriticalLevel = TRUE") );
			}
		else
			{
			aResult.iResultDes.Copy( _L("DiskSpaceBelowCriticalLevel = FALSE") );
			}
		}

	return KErrNone;
}

TInt Csysutiltest::CheckIsFileExist( const TDesC& aFilename )
{
    RFs fs;
    TInt err;
    err = fs.Connect();
    if (err != KErrNone)
        return err;

    RFile file;
    err = file.Open(fs, aFilename, EFileRead | EFileStreamText | EFileShareAny);

    file.Close();
    fs.Close();

	return err;
}
// ========================== OTHER EXPORTED FUNCTIONS =========================

// -----------------------------------------------------------------------------
// ?function_name implements...
// ?implementation_description.
// Returns: ?value_1: ?description
//          ?value_n: ?description
//                    ?description
// -----------------------------------------------------------------------------
//
/*
?type  ?function_name(
    ?arg_type arg,  // ?description
    ?arg_type arg )  // ?description
    {

    ?code

    }
*/
//  End of File
