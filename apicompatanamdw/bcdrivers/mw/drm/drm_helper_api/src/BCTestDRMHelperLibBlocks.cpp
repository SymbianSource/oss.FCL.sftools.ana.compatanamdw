/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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



// [INCLUDE FILES] - do not remove
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include "BCTestDRMHelperLib.h"
#include <DRMHelper.h> 
#include <COEMAIN.H>

_LIT(KAppName, "BCAppDRMHelperLib");

_LIT( KVideoInterval, "c:\\data\\others\\video_interval1h.dcf" );
_LIT( KValidFile, "c:\\data\\others\\sd_S60FBT_005.dcf" );
_LIT( KImageInterval, "c:\\data\\others\\sd_water003.dcf" );
_LIT( KImageStartEnd, "c:\\data\\others\\sd_S60FBT_015.dcf" );
_LIT( KSilentFile, "c:\\data\\others\\129-allthatshewants.odf" );
const TInt KROsInDB = 3;
const TInt KDRMHelperTestLibraryContentUriMaxLen = 256;

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
// CBCTestDRMHelperLib::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CBCTestDRMHelperLib::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CBCTestDRMHelperLib::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CBCTestDRMHelperLib::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "LaunchRightsManagerUI", CBCTestDRMHelperLib::LaunchRightsManagerUIL ),
        ENTRY( "LaunchRightsManagerUIContentUri", CBCTestDRMHelperLib::LaunchRightsManagerUIContentUriL ),
        ENTRY( "LaunchRightsManagerUIFileHandle", CBCTestDRMHelperLib::LaunchRightsManagerUIFileHandleL ),
        ENTRY( "HandleErrorExpiredFile", CBCTestDRMHelperLib::HandleErrorExpiredFileL),
        ENTRY( "HandleErrorNoRightsUri", CBCTestDRMHelperLib::HandleErrorNoRightsUriL),
        ENTRY( "HandleErrorNoRightsFileHandle", CBCTestDRMHelperLib::HandleErrorNoRightsFileHandleL),
        ENTRY( "CheckRightsAmountFile", CBCTestDRMHelperLib::CheckRightsAmountFileL),
        ENTRY( "CheckRightsAmountFileHandle", CBCTestDRMHelperLib::CheckRightsAmountFileHandleL),
        ENTRY( "CheckRightsAmountUri", CBCTestDRMHelperLib::CheckRightsAmountUriL),
        ENTRY( "CheckRightsPercentFile", CBCTestDRMHelperLib::CheckRightsPercentFileL),
        ENTRY( "CheckRightsPercentFileHandle", CBCTestDRMHelperLib::CheckRightsPercentFileHandleL),
        ENTRY( "GetRightsDetailsFile", CBCTestDRMHelperLib::GetRightsDetailsFileL),
        ENTRY( "GetRightsDetailsFileHandle", CBCTestDRMHelperLib::GetRightsDetailsFileHandleL),
        ENTRY( "SetAutomatedFile", CBCTestDRMHelperLib::SetAutomatedFileL),
        ENTRY( "SetAutomatedUri", CBCTestDRMHelperLib::SetAutomatedUriL),
        ENTRY( "SetAutomatedFileHandle", CBCTestDRMHelperLib::SetAutomatedFileHandleL),
        ENTRY( "ShowAutomatedNoteFile", CBCTestDRMHelperLib::ShowAutomatedNoteFileL),
        ENTRY( "ShowAutomatedNoteUri", CBCTestDRMHelperLib::ShowAutomatedNoteUriL),
        ENTRY( "ShowAutomatedNoteFileHandle", CBCTestDRMHelperLib::ShowAutomatedNoteFileHandleL),
        ENTRY( "SetAutomatedPassiveFile", CBCTestDRMHelperLib::SetAutomatedPassiveFileL),
        ENTRY( "SetAutomatedPassiveUri", CBCTestDRMHelperLib::SetAutomatedPassiveUriL),
        ENTRY( "SetAutomatedPassiveFileHandle", CBCTestDRMHelperLib::SetAutomatedPassiveFileHandleL),
        ENTRY( "SetAutomatedSilentFile", CBCTestDRMHelperLib::SetAutomatedSilentFileL),
        ENTRY( "SetAutomatedSilentUri", CBCTestDRMHelperLib::SetAutomatedSilentUriL),
        ENTRY( "SetAutomatedSilentFileHandle", CBCTestDRMHelperLib::SetAutomatedSilentFileHandleL),
        ENTRY( "RemoveAutomatedFile", CBCTestDRMHelperLib::RemoveAutomatedFileL),
        ENTRY( "RemoveAutomatedUri", CBCTestDRMHelperLib::RemoveAutomatedUriL),
        ENTRY( "RemoveAutomatedFileHandle", CBCTestDRMHelperLib::RemoveAutomatedFileHandleL),
        ENTRY( "RemoveAutomatedPassiveFile", CBCTestDRMHelperLib::RemoveAutomatedPassiveFileL),
        ENTRY( "RemoveAutomatedPassiveUri", CBCTestDRMHelperLib::RemoveAutomatedPassiveUriL),
        ENTRY( "RemoveAutomatedPassiveFileHandle", CBCTestDRMHelperLib::RemoveAutomatedPassiveFileHandleL),
        ENTRY( "CanSetAutomatedFile", CBCTestDRMHelperLib::CanSetAutomatedFileL),
        ENTRY( "CanSetAutomatedUri", CBCTestDRMHelperLib::CanSetAutomatedUriL),
        ENTRY( "CanSetAutomatedFileHandle", CBCTestDRMHelperLib::CanSetAutomatedFileHandleL),
        ENTRY( "IndicateIdle", CBCTestDRMHelperLib::IndicateIdleL),
        ENTRY( "SetCountLimit", CBCTestDRMHelperLib::SetCountLimit1L),
        ENTRY( "SetTimeLimit", CBCTestDRMHelperLib::SetTimeLimit1L),
        ENTRY( "SetPercentageLimit", CBCTestDRMHelperLib::SetPercentageLimit1L),
        ENTRY( "GetContentUriList", CBCTestDRMHelperLib::GetContentUriListL),
        ENTRY( "DataTypesCount", CBCTestDRMHelperLib::DataTypesCountL),
        ENTRY( "SupportedDataType", CBCTestDRMHelperLib::SupportedDataTypeL),
        ENTRY( "RegisterDataType", CBCTestDRMHelperLib::RegisterDataTypeL),
        ENTRY( "UnregisterDataType", CBCTestDRMHelperLib::UnregisterDataTypeL),
        ENTRY( "SupportedDrmMethods", CBCTestDRMHelperLib::SupportedDrmMethodsL),
        ENTRY( "ConsumeUri", CBCTestDRMHelperLib::ConsumeUriL),
        ENTRY( "ConsumeFile", CBCTestDRMHelperLib::ConsumeFileL),
        ENTRY( "ConsumeFileHandle", CBCTestDRMHelperLib::ConsumeFileHandleL),
        ENTRY( "ActivateContentFile", CBCTestDRMHelperLib::ActivateContentFileL),
        ENTRY( "ActivateContentData", CBCTestDRMHelperLib::ActivateContentDataL),
        ENTRY( "HasPreviewFile", CBCTestDRMHelperLib::HasPreviewFileL),
        ENTRY( "HasPreviewData", CBCTestDRMHelperLib::HasPreviewDataL),
        ENTRY( "GetPreviewRightsFile", CBCTestDRMHelperLib::GetPreviewRightsFileL),
        ENTRY( "GetPreviewRightsData", CBCTestDRMHelperLib::GetPreviewRightsDataL),
        ENTRY( "EmbeddedPreviewCompletedFile", CBCTestDRMHelperLib::EmbeddedPreviewCompletedFileL),
        ENTRY( "EmbeddedPreviewCompletedData", CBCTestDRMHelperLib::EmbeddedPreviewCompletedDataL),
        ENTRY( "HasInfoUrlFile", CBCTestDRMHelperLib::HasInfoUrlFileL),
        ENTRY( "HasInfoUrlData", CBCTestDRMHelperLib::HasInfoUrlDataL),
        ENTRY( "OpenInfoUrlFile", CBCTestDRMHelperLib::OpenInfoUrlFileL),
        ENTRY( "OpenInfoUrlData", CBCTestDRMHelperLib::OpenInfoUrlDataL),        
        ENTRY( "SetPreviewMediaType", CBCTestDRMHelperLib::SetPreviewMediaTypeL),
        ENTRY( "HandleErrorOrPreviewFile", CBCTestDRMHelperLib::HandleErrorOrPreviewFileL),
        ENTRY( "HandleErrorOrPreviewFileHandle", CBCTestDRMHelperLib::HandleErrorOrPreviewFileHandleL),
        ENTRY( "HandleErrorOrPreviewSilentFile", CBCTestDRMHelperLib::HandleErrorOrPreviewSilentFileL),
        ENTRY( "HandleErrorOrPreviewSilentFileHandle", CBCTestDRMHelperLib::HandleErrorOrPreviewSilentFileHandleL),

        // [test cases entries] - Do not remove

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CBCTestDRMHelperLib::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CBCTestDRMHelperLib::ExampleL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KBCTestDRMHelperLib, "BCTestDRMHelperLib" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, KBCTestDRMHelperLib, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KBCTestDRMHelperLib, 
                                KParam, i, &string );
        i++;
        }

    return KErrNone;

    }


//member functions

// ---------------------------------------------------------
// CBCTestDRMHelperLib::ContentUriLC
//
// (other items were commented in a header).
// ---------------------------------------------------------
// 
HBufC* CBCTestDRMHelperLib::ContentUriLC( const TDesC& aFileName )
    {
    HBufC* contentUri = HBufC::NewLC( KDRMHelperTestLibraryContentUriMaxLen );
    TVirtualPathPtr virtualPath( aFileName, KDefaultContentObject );

    ContentAccess::CData* data = ContentAccess::CData::NewLC( 
        virtualPath, EPeek, EContentShareReadWrite );
    TPtr ptr = contentUri->Des();
    User::LeaveIfError( data->GetStringAttribute( EContentID, ptr ) );
    CleanupStack::PopAndDestroy( data );
    return contentUri;
    }
 
// ---------------------------------------------------------
// CBCTestDRMHelperLib::ConvertTo8BitLC
//
// (other items were commented in a header).
// ---------------------------------------------------------
// 
HBufC8* CBCTestDRMHelperLib::ConvertTo8BitLC( HBufC* aBuffer )
    {
    HBufC8* buffer8 = HBufC8::NewLC( aBuffer->Length() );
    buffer8->Des().Copy( *aBuffer );
    return buffer8;
    }

// ---------------------------------------------------------
// CBCTestDRMHelperLib::OpenFileL
//
// (other items were commented in a header).
// ---------------------------------------------------------
// 
void CBCTestDRMHelperLib::OpenFileL( const TDesC& aFileName, RFile& aFile )
    {
    TInt r = KErrNone;
    
    r = aFile.Open(iFs, aFileName, EFileRead | EFileShareReadersOrWriters);    
    
    if (r == KErrInUse)
        {
        r = aFile.Open(iFs, aFileName, EFileRead | EFileShareAny);
        if (r == KErrInUse)
            {
            r = aFile.Open(iFs, aFileName, EFileRead | EFileShareReadersOnly);
            }
        }
    User::LeaveIfError( r );    
    }
    
 
// ---------------------------------------------------------
// CBCTestDRMHelperLib::CreateContentObjectLC
//
// (other items were commented in a header).
// ---------------------------------------------------------
// 
ContentAccess::CData* CBCTestDRMHelperLib::CreateContentObjectLC( const TDesC& aFileName )
    {
    TVirtualPathPtr virtualPath( aFileName );
    
    ContentAccess::CData* content = NULL;
    TRAPD( r, content = ContentAccess::CData::NewL( virtualPath, EPeek, EContentShareReadWrite ) );
    if ( r == KErrInUse )
        {
        content = ContentAccess::CData::NewL( virtualPath, EPeek, EContentShareReadOnly );
        }
    else 
        {
        User::LeaveIfError( r );    
        }
    CleanupStack::PushL( content );
    return content;
    }        
    
// ---------------------------------------------------------
// CBCTestDRMHelperLib::CheckPermissionL
//
// (other items were commented in a header).
// ---------------------------------------------------------
// 
void CBCTestDRMHelperLib::CheckPermissionL( CDRMHelperRightsConstraints* aConstraint )
    {
    TInt err( KErrNone );
    TUint32 counter(0);
    TUint32 originalCounter(0);
    TTime time;
    TTimeIntervalSeconds interval;
    TTimeIntervalSeconds timer;

    if ( aConstraint->FullRights() )
        {
		iLog->Log( _L( "Full rights!"));
        }

    if ( aConstraint->IsPreview() )
        {
		iLog->Log( _L( "Preview rights!!"));
        }

    TRAP( err, aConstraint->GetCountersL( counter, originalCounter ) );
    if ( err != KErrNotFound )
        {
		iLog->Log( _L( "GetCountersL leaved with: %d "),err);
        }
    err = KErrNone;

    TRAP( err, aConstraint->GetStartTimeL( time ) );
    if ( err != KErrNotFound )
        {
		iLog->Log( _L( "GetStartTimeL leaved with: %d "),err);
        }
    err = KErrNone;

    TRAP( err, aConstraint->GetEndTimeL( time ) );
    if ( err != KErrNotFound )
        {
		iLog->Log( _L( "GetEndTimeL leaved with: %d "),err);
        }
    err = KErrNone;

    TRAP( err, aConstraint->GetIntervalL( interval ) );
    if ( err )
        {
		iLog->Log( _L( "GetIntervalL leaved with: %d "),err);
        }
    err = KErrNone;

    TRAP( err, aConstraint->GetIntervalStartL( time ) );
    if ( err != KErrNotFound )
        {
		iLog->Log( _L( "GetIntervalStartL leaved with: %d "),err);
        }
    err = KErrNone;

    TRAP( err, aConstraint->GetTimedCountL( counter, originalCounter, timer ) );
    if ( err != KErrNotFound )
        {
		iLog->Log( _L( "GetTimedCountL leaved with: %d "),err);
        }
    err = KErrNone;

    TRAP( err, aConstraint->GetAccumulatedTimeL( interval ) );
    if ( err != KErrNotFound )
        {
		iLog->Log( _L( "GetAccumulatedTimeL leaved with: %d "),err);
        }
    err = KErrNone;
    }



//test cases
TInt CBCTestDRMHelperLib::LaunchRightsManagerUIL()
{
	SetupL();
	TRAPD(res,iHelper->LaunchDetailsViewEmbeddedL( KVideoInterval ));
	Teardown();
	return res;
}

TInt CBCTestDRMHelperLib::LaunchRightsManagerUIContentUriL()
{
	SetupL();
    contentUri = ContentUriLC( KVideoInterval );
    contentUri8 = ConvertTo8BitLC( contentUri );
    iHelper->LaunchDetailsViewEmbeddedL( contentUri8 );     
    CleanupStack::PopAndDestroy( 2, contentUri );       
    Teardown();
    return retval;    
}
TInt CBCTestDRMHelperLib::LaunchRightsManagerUIFileHandleL()
{
	SetupL();
    OpenFileL( KVideoInterval, file );
    CleanupClosePushL( file );
    iHelper->LaunchDetailsViewEmbeddedL( file );
    CleanupStack::PopAndDestroy(); // close file	
    Teardown();
    return retval;    
}
TInt CBCTestDRMHelperLib::HandleErrorExpiredFileL()
{
	SetupL();
	TInt retval = iHelper->HandleErrorL( KErrCANoPermission, KValidFile );
	if ( retval )
	{
	 iLog->Log( _L( "HandleErrorL returned: &d" ), retval );
	 User::Leave(retval);
	}
    Teardown();
    return retval;    
}
TInt CBCTestDRMHelperLib::HandleErrorNoRightsUriL()
{
	SetupL();
	contentUri = ContentUriLC( KValidFile );
	contentUri8 = ConvertTo8BitLC( contentUri );
	TInt retval = iHelper->HandleErrorL( KErrCANoRights, *contentUri8 );     
	CleanupStack::PopAndDestroy( 2, contentUri );       
	if ( retval )
	{
	 iLog->Log( _L( "HandleErrorL returned: %d" ), retval );
	 User::Leave(retval);
	}
    Teardown();
    return retval;    
}
TInt CBCTestDRMHelperLib::HandleErrorNoRightsFileHandleL()
{
	SetupL();
	OpenFileL( KValidFile, file );
	CleanupClosePushL( file );
	TInt retval = iHelper->HandleErrorL( KErrCANoRights, file );     
	CleanupStack::PopAndDestroy(); // close file       
	if ( retval )
	    {
	      iLog->Log( _L( "HandleErrorL returned: %d" ), retval );
	      User::Leave(retval);
	    }            	
    Teardown();
    return retval;    

}
TInt CBCTestDRMHelperLib::CheckRightsAmountFileL		()
{
	SetupL();
    TInt retval = iHelper->CheckRightsAmountL( KVideoInterval, 0, 0 );
	if ( retval )
	    {
	    iLog->Log( _L( "CheckRightsAmountL returned: %d" ), retval );
	    User::Leave( retval );
	    }    
    Teardown();
    return retval;    
    
}
TInt CBCTestDRMHelperLib::CheckRightsAmountFileHandleL()
{
	SetupL();
    OpenFileL( KVideoInterval, file );
    CleanupClosePushL( file );
    TInt retval = iHelper->CheckRightsAmountL( file, 0, 0 );
    CleanupStack::PopAndDestroy(); // close file       
    if ( retval )
        {
          iLog->Log( _L( "CheckRightsAmountL returned: %d" ), retval );
          User::Leave(retval);
        }	
    Teardown();
    return retval;    
        
}
TInt CBCTestDRMHelperLib::CheckRightsAmountUriL()
{
	SetupL();
	contentUri = ContentUriLC( KVideoInterval );
	contentUri8 = ConvertTo8BitLC( contentUri );
	TInt retval = iHelper->CheckRightsAmountL( *contentUri8, 0, 0 );
	CleanupStack::PopAndDestroy( 2, contentUri );       
	if ( retval )
		{
		  iLog->Log( _L( "CheckRightsAmountL returned: %d" ), retval );
		  User::Leave(retval);
		}
    Teardown();
    return retval;    

}
TInt CBCTestDRMHelperLib::CheckRightsPercentFileL()
{
	SetupL();
    TInt retval = iHelper->CheckRightsPercentL( KVideoInterval, 100 );
    if ( retval )
        {
          iLog->Log( _L( "CheckRightsPercentL returned: %d" ), retval );
          User::Leave(retval);
        }
    Teardown();
    return retval;    
        
}
TInt CBCTestDRMHelperLib::CheckRightsPercentFileHandleL()
{
	SetupL();
    OpenFileL( KVideoInterval, file );
    CleanupClosePushL( file );
    TInt retval = iHelper->CheckRightsPercentL( file, 100 );
    CleanupStack::PopAndDestroy(); // close file       
    if ( retval )
        {
          iLog->Log( _L( "CheckRightsPercentL returned: %d" ), retval );
          User::Leave(retval);
        }
    Teardown();
    return retval;    

}
TInt CBCTestDRMHelperLib::GetRightsDetailsFileL()
{
	SetupL();
iHelper->GetRightsDetailsL( KImageInterval, 0, expired, sendingAllowed,
    play, display, execute, print );
if ( expired )
    {
	  iLog->Log( _L8( "GetRightsDetailsFileL : Expired!" ) );
      User::Leave(KErrGeneral);
    }
if ( !sendingAllowed )
    {
      iLog->Log( _L8( "GetRightsDetailsFileL : Sending not allowed!" ) );
      User::Leave(KErrGeneral);
    }
if ( play )
    {
      iLog->Log( _L8( "GetRightsDetailsFileL : play permission found!" ) );
      User::Leave(KErrGeneral);
    }
if ( execute )
    {
      iLog->Log( _L8( "GetRightsDetailsFileL : execute permission found!" ) );
      User::Leave(KErrGeneral);
    }
if ( display )
    {
    CheckPermissionL( display );
    delete display;
    }
else
    {
      iLog->Log( _L8( "GetRightsDetailsFileL : display permission not found!" ) );
      User::Leave(KErrGeneral);
    }                
if ( print )
    {
    CheckPermissionL( print );
    delete print;
    }
else
    {
      iLog->Log( _L8( "GetRightsDetailsFileL : print permission not found!" ) );
      User::Leave(KErrGeneral);
    }
    Teardown();
    return KErrNone;    
    
}
TInt CBCTestDRMHelperLib::GetRightsDetailsFileHandleL()
{
	SetupL();
    OpenFileL( KImageInterval, file );
    CleanupClosePushL( file );
    iHelper->GetRightsDetailsL( file, 0, expired, sendingAllowed,
        play, display, execute, print );
    CleanupStack::PopAndDestroy(); // close file

    if ( expired )
        {
          iLog->Log( _L8( "GetRightsDetailsFileHandleL : Expired!" ) );
          User::Leave(KErrGeneral);
        }
    if ( !sendingAllowed )
        {
          iLog->Log( _L8( "GetRightsDetailsFileHandleL : Sending not allowed!" ) );
          User::Leave(KErrGeneral);
        }
    if ( play )
        {
          iLog->Log( _L8( "GetRightsDetailsFileHandleL : play permission found!" ) );
          User::Leave(KErrGeneral);
        }
    if ( execute )
        {
          iLog->Log( _L8( "GetRightsDetailsFileHandleL : execute permission found!" ) );
          User::Leave(KErrGeneral);
        }
    if ( display )
        {
        CheckPermissionL( display );
        delete display;
        }
    else
        {
          iLog->Log( _L8( "GetRightsDetailsFileHandleL : display permission not found!" ) );
          User::Leave(KErrGeneral);
        }                
    if ( print )
        {
        CheckPermissionL( print );
        delete print;
        }
    else
        {
          iLog->Log( _L8( "GetRightsDetailsFileHandleL : print permission not found!" ) );
          User::Leave(KErrGeneral);
        }
    Teardown();
    return KErrNone;    
	
}
TInt CBCTestDRMHelperLib::SetAutomatedFileL()
{
	SetupL();
    TInt retval = iHelper->SetAutomated( KImageStartEnd );
    if ( retval )
        {
          iLog->Log( _L( "SetAutomated returned: %d" ), retval );
          User::Leave(retval);
        }	
    Teardown();
    return retval;    
       
}
TInt CBCTestDRMHelperLib::SetAutomatedUriL()
{
	SetupL();
    contentUri = ContentUriLC( KImageStartEnd );
    contentUri8 = ConvertTo8BitLC( contentUri );
    TInt retval = iHelper->SetAutomated( *contentUri8 );
    if ( retval )
        {
          iLog->Log( _L( "SetAutomated returned: %d" ), retval );
          User::Leave(retval);
        }
    CleanupStack::PopAndDestroy( 2, contentUri );
    Teardown();
    return retval;    
    
}
TInt CBCTestDRMHelperLib::SetAutomatedFileHandleL()
{
	SetupL();
    OpenFileL( KImageStartEnd, file );
    TInt retval = iHelper->SetAutomated( file );
    if ( retval )
        {
          iLog->Log( _L( "SetAutomated returned: %d" ), retval );
          User::Leave(retval);
        }
    file.Close();
    Teardown();
    return retval;    
    
}
TInt CBCTestDRMHelperLib::ShowAutomatedNoteFileL()
{
	SetupL();
    TInt retval = iHelper->ShowAutomatedNote( KImageStartEnd );
    if ( retval != KErrCancel )
        {
          iLog->Log( _L( "ShowAutomatedNote returned: %d" ), retval );
          User::Leave(retval);
        }
    Teardown();
    return KErrNone;    

}
TInt CBCTestDRMHelperLib::ShowAutomatedNoteUriL()
{
	SetupL();
    contentUri = ContentUriLC( KImageStartEnd );
    contentUri8 = ConvertTo8BitLC( contentUri );
    TInt retval = iHelper->ShowAutomatedNote( *contentUri8 );
    if ( retval != KErrCancel )
        {
          iLog->Log( _L( "ShowAutomatedNote returned: %d" ), retval );
          User::Leave(retval);
        }
    CleanupStack::PopAndDestroy( 2, contentUri );
    Teardown();
    return KErrNone;    
    
}
TInt CBCTestDRMHelperLib::ShowAutomatedNoteFileHandleL()
{
	SetupL();
    OpenFileL( KImageStartEnd, file );
    TInt retval = iHelper->ShowAutomatedNote( file );
    if ( retval != KErrCancel )
        {
          iLog->Log( _L( "ShowAutomatedNote returned: %d" ), retval );
          User::Leave(retval);
        }
    file.Close();
    Teardown();
    return KErrNone;    
	
}
TInt CBCTestDRMHelperLib::SetAutomatedPassiveFileL()
{
   SetupL();
   TInt retval = iHelper->SetAutomatedPassive( KImageStartEnd );
   if ( retval )
        {
          iLog->Log( _L( "SetAutomatedPassive returned: %d" ), retval );
          User::Leave(retval);
        }
    Teardown();
    return retval;    

}
TInt CBCTestDRMHelperLib::SetAutomatedPassiveUriL()
{
	SetupL();    
    contentUri = ContentUriLC( KImageStartEnd );
    contentUri8 = ConvertTo8BitLC( contentUri );
    TInt retval = iHelper->SetAutomatedPassive( *contentUri8 );
    if ( retval )
        {
          iLog->Log( _L( "SetAutomatedPassive returned: %d" ), retval );
          User::Leave(retval);
        }
    CleanupStack::PopAndDestroy( 2, contentUri );
    Teardown();
    return retval;    
	
}
TInt CBCTestDRMHelperLib::SetAutomatedPassiveFileHandleL()
{
	SetupL();    
    OpenFileL( KImageStartEnd, file );
    TInt retval = iHelper->SetAutomatedPassive( file );
    if ( retval )
        { 
          iLog->Log( _L( "SetAutomatedPassive returned: %d" ), retval );
          User::Leave(retval);
        }
    file.Close();
    Teardown();
    return retval;    

}
TInt CBCTestDRMHelperLib::SetAutomatedSilentFileL()
{
	SetupL(); 
    TInt retval = iHelper->SetAutomatedSilent( KImageStartEnd, ETrue );
    if ( retval )
        {  
          iLog->Log( _L( "SetAutomatedSilent returned: %d" ), retval );
          User::Leave(retval);
        }
    Teardown();
    return retval;    

}
TInt CBCTestDRMHelperLib::SetAutomatedSilentUriL()
{
	SetupL();    
    contentUri = ContentUriLC( KImageStartEnd );
    contentUri8 = ConvertTo8BitLC( contentUri );
    TInt retval = iHelper->SetAutomatedSilent( *contentUri8, ETrue );
    if ( retval )
        {
          iLog->Log( _L( "SetAutomatedSilent returned: %d" ), retval );
          User::Leave(retval);
        }
    CleanupStack::PopAndDestroy( 2, contentUri );
    Teardown();
    return retval;    

}
TInt CBCTestDRMHelperLib::SetAutomatedSilentFileHandleL()
{
	SetupL();    
    OpenFileL( KImageStartEnd, file );
    TInt retval = iHelper->SetAutomatedSilent( file, ETrue );
    if ( retval )
        {
          iLog->Log( _L( "SetAutomatedSilent returned: %d" ), retval );
          User::Leave(retval);
        }
    file.Close();
    Teardown();
    return retval;    

}
TInt CBCTestDRMHelperLib::RemoveAutomatedFileL()
{
	SetupL();       
    TInt retval = iHelper->RemoveAutomated( KImageStartEnd );
    if ( retval )
        {
          iLog->Log( _L( "RemoveAutomated returned: %d" ), retval );
          User::Leave(retval);
        }
    Teardown();
    return retval;    

}
TInt CBCTestDRMHelperLib::RemoveAutomatedUriL()
{
	SetupL();    
    contentUri = ContentUriLC( KImageStartEnd );
    contentUri8 = ConvertTo8BitLC( contentUri );
    TInt retval = iHelper->RemoveAutomated( *contentUri8 );
    if ( retval )
        {
          iLog->Log( _L( "RemoveAutomated returned: %d" ), retval );
          User::Leave(retval);
        }
    CleanupStack::PopAndDestroy( 2, contentUri );
    Teardown();
    return retval;                

}
TInt CBCTestDRMHelperLib::RemoveAutomatedFileHandleL()
{
	SetupL();  
    OpenFileL( KImageStartEnd, file );
    TInt retval = iHelper->RemoveAutomated( file );
    if ( retval )
        { 
          iLog->Log( _L( "RemoveAutomated returned: %d" ), retval );
          User::Leave(retval);
        }
    file.Close();
    Teardown();
    return retval;    

}
TInt CBCTestDRMHelperLib::RemoveAutomatedPassiveFileL()
{
	SetupL();
	TInt retval = iHelper->RemoveAutomatedPassive( KImageStartEnd );
    if ( retval )
        {
          iLog->Log( _L( "RemoveAutomatedpassive returned: %d" ), retval );
          User::Leave(retval);
        }
    Teardown();
    return retval;    

}
TInt CBCTestDRMHelperLib::RemoveAutomatedPassiveUriL()
{
	SetupL();
    contentUri = ContentUriLC( KImageStartEnd );
    contentUri8 = ConvertTo8BitLC( contentUri );
    TInt retval = iHelper->RemoveAutomatedPassive( *contentUri8 );
    if ( retval )
        {
          iLog->Log( _L( "RemoveAutomatedpassive returned: %d" ), retval );
          User::Leave(retval);
        }
    CleanupStack::PopAndDestroy( 2, contentUri );   
    Teardown();
    return retval;    
             
}
TInt CBCTestDRMHelperLib::RemoveAutomatedPassiveFileHandleL()
{
	SetupL();
    OpenFileL( KImageStartEnd, file );
    TInt retval = iHelper->RemoveAutomatedPassive( file );
    if ( retval )
        {
          iLog->Log( _L( "RemoveAutomatedpassive returned: %d" ), retval );
          User::Leave(retval);
        }
    file.Close();
    Teardown();
    return retval;    
            
}
TInt CBCTestDRMHelperLib::CanSetAutomatedFileL()
{
	SetupL();
    TInt retval = iHelper->CanSetAutomated( KImageStartEnd, automatedUseAllowed );
    if ( retval )
        {
          iLog->Log( _L( "CanSetAutomated returned: %d" ), retval );
          User::Leave(retval);
        }
    if ( !automatedUseAllowed )
        {
          iLog->Log( _L( "CanSetAutomated returned: !automatedUseAllowed %d" ), retval );
          User::Leave(retval);
        }
    Teardown();
    return retval;    

}
TInt CBCTestDRMHelperLib::CanSetAutomatedUriL()
{
	SetupL();
    contentUri = ContentUriLC( KImageStartEnd );
    contentUri8 = ConvertTo8BitLC( contentUri );
    TInt retval = iHelper->CanSetAutomated( *contentUri8, automatedUseAllowed );
    if ( retval )
        {
          iLog->Log( _L( "CanSetAutomated returned: %d" ), retval );
          User::Leave(retval);
        }
    if ( !automatedUseAllowed )
        {
          iLog->Log( _L8( "CanSetAutomatedUriL : Automated use not allowed!" ) );
          User::Leave(retval);
        }
    CleanupStack::PopAndDestroy( 2, contentUri );   
    Teardown();
    return retval;                 
}
TInt CBCTestDRMHelperLib::CanSetAutomatedFileHandleL()
{
	SetupL();
    OpenFileL( KImageStartEnd, file );
    TInt retval = iHelper->CanSetAutomated( file, automatedUseAllowed );
    if ( retval )
        {
          iLog->Log( _L( "CanSetAutomated returned: " ), retval );
          User::Leave(retval);
        }
    if ( !automatedUseAllowed )
        {
        iLog->Log(_L("CanSetAutomated : automated use allowed failed"));
        User::Leave( retval );
        }
    file.Close();
    Teardown();
    return retval;    
}
TInt CBCTestDRMHelperLib::IndicateIdleL()
{
	SetupL();
    TRAPD(retval,iHelper->IndicateIdle());
    Teardown();
    return retval;    
}
TInt CBCTestDRMHelperLib::SetCountLimit1L ()
{
	SetupL();
    TRAPD(retval,iHelper->SetCountLimitL( 3 ));
    Teardown();
    return retval;    
}
TInt CBCTestDRMHelperLib::SetTimeLimit1L()
{
	SetupL();
    TRAPD(retval,iHelper->SetTimeLimitL( 7 ));
    Teardown();
    return retval;    
}
TInt CBCTestDRMHelperLib::SetPercentageLimit1L()
{
	SetupL();
    TRAPD(retval,iHelper->SetPercentageLimitL( 10 ));
    Teardown();
    return retval;        
}
TInt CBCTestDRMHelperLib::GetContentUriListL()
{
	SetupL();
    TInt retval = iHelper->GetContentURIList( uriList );
    if ( retval )
        {
          iLog->Log( _L( "GetContentURIList returned: %d" ), retval );
          User::Leave(retval);
        }
    if ( uriList )
        {
        if ( uriList->Count() != KROsInDB )
            {
             iLog->Log( _L( "GetContentURIList returned number of ROs in DB: %d" ), uriList->Count() );
             User::Leave(KErrGeneral);
            }    
        uriList->ResetAndDestroy();
        delete uriList;
        }
    Teardown();
    return retval;    
}
TInt CBCTestDRMHelperLib::DataTypesCountL()
{
	SetupL();
   TInt retval = iHelper->DataTypesCount( supportedDataTypes );
    if ( retval )
        {
          iLog->Log( _L8( "DataTypesCount returned: " ), retval );
          User::Leave(KErrGeneral);
        }
    else if ( !supportedDataTypes )
        {
          iLog->Log( _L8( "DataTypesCount: No data types found" ) );
          User::Leave(KErrGeneral);
        }
    Teardown();
    return retval;    	
}
TInt CBCTestDRMHelperLib::SupportedDataTypeL()
{
	SetupL();
   TInt retval = iHelper->DataTypesCount( supportedDataTypes );
    if ( !retval && supportedDataTypes )
        {
        retval = iHelper->SupportedDataType( supportedDataTypes - 1,
            dataType );
        if ( retval )
            {
            iLog->Log( _L( "SupportedDataType returned: %d" ), retval );
            User::Leave(retval);
            }
        }
    else
        {
          iLog->Log( _L( "SupportedDataType: getting amount of datatypes failed" ) );
          User::Leave(KErrGeneral);
        }
    Teardown();
    return retval;            
}
TInt CBCTestDRMHelperLib::RegisterDataTypeL()
{
	SetupL();
    TInt retval = iHelper->RegisterDataType( dataType );
    if ( retval == KErrNone )
        {
        iLog->Log( _L( "RegisterDataType returned: %d" ), retval );
        User::Leave( retval );
        }
    Teardown();
    return KErrNone;            
}
TInt CBCTestDRMHelperLib::UnregisterDataTypeL()
{
	SetupL();
    TInt retval = iHelper->UnRegisterDataType( 0 );
    if ( retval == KErrNone )
        {
        iLog->Log( _L( "UnRegisterDataType returned: %d" ), 
                    retval );
        User::Leave( retval );
        }
    Teardown();
    return KErrNone;                    
}
TInt CBCTestDRMHelperLib::SupportedDrmMethodsL()
{
	SetupL();
	CDRMHelper::TDRMHelperOMALevel omaLevel;
	omaLevel = CDRMHelper::EOMA_None ;
    TInt retval = iHelper->SupportedDRMMethods2( drmMethod, omaLevel );
    if ( retval )
        {
          iLog->Log( _L( "SupportedDRMMethods returned: %d" ), 
                    retval );
          User::Leave(retval);
        }
    Teardown();
    return retval;            
}
TInt CBCTestDRMHelperLib::ConsumeUriL()
{
	SetupL();
    contentUri = ContentUriLC( KImageStartEnd );
    contentUri8 = ConvertTo8BitLC( contentUri );
    TInt retval = iHelper->Consume2( *contentUri8, ContentAccess::EView, 
        CDRMHelper::EStart );
    if ( retval )
        {
          iLog->Log( _L( "Consume2 start returned: %d" ), 
                    retval );
          User::Leave(retval);
        }
    else
        {
        retval = iHelper->Consume2( *contentUri8, ContentAccess::EView, 
            CDRMHelper::EFinish );
        if ( retval )
            {
              iLog->Log( _L( "Consume2 finish returned: %d" ), 
                        retval );
	          User::Leave(retval);
            }
        }
    CleanupStack::PopAndDestroy( 2, contentUri ); 
    Teardown();
    return retval;        
}
TInt CBCTestDRMHelperLib::ConsumeFileL()
{
	SetupL();
    TInt retval = iHelper->ConsumeFile2( KImageStartEnd, ContentAccess::EView, 
        CDRMHelper::EStart );
    if ( retval )
        {
          iLog->Log( _L( "ConsumeFile2 start returned: %d" ), 
                    retval );
          User::Leave(retval);
        }
    else
        {
        retval = iHelper->ConsumeFile2( KImageStartEnd, 
            ContentAccess::EView, CDRMHelper::EFinish );
        if ( retval )
            {
              iLog->Log( _L( "ConsumeFile2 finish returned: %d" ), 
                        retval );
	          User::Leave(retval);
            }
        }
    Teardown();
    return retval;            
}
TInt CBCTestDRMHelperLib::ConsumeFileHandleL()
{
	SetupL();
    OpenFileL( KImageStartEnd, file );
    TInt retval = iHelper->ConsumeFile2( file, ContentAccess::EView, 
        CDRMHelper::EStart );
    if ( retval )
        {
          iLog->Log( _L( "ConsumeFile2 start returned: %d" ), 
                    retval );
          User::Leave(retval);
        }
    else
        {
        retval = iHelper->ConsumeFile2( KImageStartEnd, 
            ContentAccess::EView, CDRMHelper::EFinish );
        if ( retval )
            {
              iLog->Log( _L( "ConsumeFile2 finish returned: %d" ), 
                        retval );
	          User::Leave(retval);
            }
        }
    file.Close();
    Teardown();
    return retval;        
}
TInt CBCTestDRMHelperLib::ActivateContentFileL()
{
	SetupL();
   fileName = KValidFile;
   TInt retval;
   TRAP( retval, iHelper->ActivateContentL( fileName ) );
   if ( retval != KErrCancel )
        {
          iLog->Log( _L( "ActivateContentL returned: %d" ), 
                    retval );
          User::Leave(retval);
        }                
   Teardown();
   return KErrNone;            
}
TInt CBCTestDRMHelperLib::ActivateContentDataL()
{
	SetupL();
	ContentAccess::CData* content;
	content = NULL;
    content = CreateContentObjectLC( KValidFile );
    TInt retval;
    TRAP( retval, iHelper->ActivateContentL( *content ) );
    if ( retval != KErrCancel )
        {
          iLog->Log( _L( "ActivateContentL returned: %d" ), 
                    retval );
          User::Leave(retval);
        }                
    CleanupStack::PopAndDestroy( content );
    Teardown();
    return KErrNone;        
}
TInt CBCTestDRMHelperLib::HasPreviewFileL()
{
	SetupL();
	CDRMHelper::TDRMHelperPreviewType previewType;
    fileName = KImageStartEnd;
    previewType = iHelper->HasPreviewL( fileName, previewUrl );
    if ( previewType != CDRMHelper::ENoPreview )
        {
        iLog->Log( _L8( "HasPreviewL: preview found" ) );
          delete previewUrl;
          User::Leave(KErrGeneral);
        }                
    Teardown();
    return KErrNone;    	
}
TInt CBCTestDRMHelperLib::HasPreviewDataL()
{
	SetupL();
	CDRMHelper::TDRMHelperPreviewType previewType;
	ContentAccess::CData* content;
	content = NULL;
    content = CreateContentObjectLC( KImageStartEnd );
    previewType = iHelper->HasPreviewL( *content, previewUrl );
    if ( previewType != CDRMHelper::ENoPreview )
        {
        iLog->Log( _L8( "HasPreviewL: preview found" ) );
        delete previewUrl;
        User::Leave(KErrGeneral);
        }                
    CleanupStack::PopAndDestroy( content );
    Teardown();
    return retval;        
}
TInt CBCTestDRMHelperLib::GetPreviewRightsFileL()
{
	SetupL();
    fileName = KImageStartEnd;
    TRAP( retval, iHelper->GetPreviewRightsL( fileName ) );
    if ( retval != KErrArgument )
        {
          iLog->Log( _L( "GetPreviewRightsL returned: %d" ), 
                    retval );
          User::Leave(retval);
        }                
    Teardown();
    return KErrNone;                
}
TInt CBCTestDRMHelperLib::GetPreviewRightsDataL()
{
	SetupL();
	ContentAccess::CData* content;
	content = NULL;
    content = CreateContentObjectLC( KImageStartEnd );
    TRAP( retval, iHelper->GetPreviewRightsL( *content ) );
    if ( retval != KErrArgument )
        {
          iLog->Log( _L( "GetPreviewRightsL returned: %d" ), 
                    retval );
          User::Leave(retval);
        }                
    CleanupStack::PopAndDestroy( content );
    Teardown();
    return KErrNone;        
}
TInt CBCTestDRMHelperLib::EmbeddedPreviewCompletedFileL()
{
	SetupL();
    fileName = KImageStartEnd;
    TRAP( retval, buyRights = iHelper->EmbeddedPreviewCompletedL( fileName ) );
    if ( retval && retval != KErrArgument )
        {
          iLog->Log( _L( "EmbeddedPreviewCompletedFileL returned: %d" ), 
                    retval );
          User::Leave(retval);
        }
    if ( buyRights )            
        {
          iLog->Log( _L8( "EmbeddedPreviewCompletedL: wrong value" ) );
          User::Leave(KErrGeneral);
        }
    Teardown();
    return retval;            
}
TInt CBCTestDRMHelperLib::EmbeddedPreviewCompletedDataL()
{
	SetupL();
	ContentAccess::CData* content;
	content = NULL;
    content = CreateContentObjectLC( KImageStartEnd );
    TRAP( retval, buyRights = iHelper->EmbeddedPreviewCompletedL( *content ) );
    if ( retval && retval != KErrArgument )
        {
          iLog->Log( _L( "EmbeddedPreviewCompletedDataL returned: %d" ), 
                    retval );
          User::Leave(retval);
        }
    if ( buyRights )            
        {
          iLog->Log( _L8( "EmbeddedPreviewCompletedDataL: wrong value" ) );
          User::Leave(KErrGeneral);
        }
    CleanupStack::PopAndDestroy( content );
    Teardown();
    return retval;     
}
TInt CBCTestDRMHelperLib::HasInfoUrlFileL()
{
	SetupL();
    fileName = KImageStartEnd;            
    infoUrlExists = iHelper->HasInfoUrlL( fileName, infoUrl );
    if ( infoUrlExists )
        {
          iLog->Log( _L8( "EmbeddedPreviewCompletedL: wrong value" ) );
          delete infoUrl;
          User::Leave(KErrGeneral);
        }      
    Teardown();
    return KErrNone;                               
}
TInt CBCTestDRMHelperLib::HasInfoUrlDataL()
{
	SetupL();
	ContentAccess::CData* content;
	content = NULL;
    content = CreateContentObjectLC( KImageStartEnd );
    infoUrlExists = iHelper->HasInfoUrlL( *content, infoUrl );
    if ( infoUrlExists )
        {
          iLog->Log( _L8( "EmbeddedPreviewCompletedL: wrong value" ) );
          delete infoUrl;
          User::Leave(KErrGeneral);
        }                            
    CleanupStack::PopAndDestroy( content );
    Teardown();
    return KErrNone;    
}
TInt CBCTestDRMHelperLib::OpenInfoUrlFileL()
{
	SetupL();
    fileName = KImageStartEnd;
    TRAP( retval, iHelper->OpenInfoUrlL( fileName ) );
    if ( retval != KErrArgument )
        {
          iLog->Log( _L( "OpenInfoUrlL returned: %d" ), 
                    retval );
          User::Leave(retval);
        } 
    Teardown();
    return KErrNone;                       
}
TInt CBCTestDRMHelperLib::OpenInfoUrlDataL()
{
	SetupL();
	ContentAccess::CData* content;
	content = NULL;
    content = CreateContentObjectLC( KImageStartEnd );
    TRAP( retval, iHelper->OpenInfoUrlL( *content ) );
    if ( retval != KErrArgument )
        {
          iLog->Log( _L( "OpenInfoUrlL returned: %d" ), 
                    retval );
          User::Leave(retval);
        }                
    CleanupStack::PopAndDestroy( content );
    Teardown();
    return KErrNone;
}

TInt CBCTestDRMHelperLib::SetPreviewMediaTypeL()
{
	SetupL();
    retval = iHelper->SetPreviewMediaType( EPreviewTypeAudio );
    if ( retval )
        {
        iLog->Log( _L( "SetPreviewMediaType returned %d"),retval);
        User::Leave( retval );
        }                
    Teardown();
    return KErrNone;	
}
TInt CBCTestDRMHelperLib::HandleErrorOrPreviewFileL()
{
	SetupL();
    retval = iHelper->HandleErrorOrPreviewL( KErrCANoPermission, 
        KValidFile, previewUrl );
    if ( previewUrl )
        {
        iLog->Log( _L( "HandleErrorOrPreviewL: preview URI returned: %d"), retval);
        delete previewUrl;
        previewUrl = NULL;
        User::Leave( retval );
        }   
    else if ( retval != KErrCANoPermission &&
         retval != KErrCANoRights &&
         retval != KErrCancel )
        {
        iLog->Log( _L( "HandleErrorOrPreviewL returned: %d"),retval);
        User::Leave( retval );
        }
    Teardown();
    return KErrNone;	
}
TInt CBCTestDRMHelperLib::HandleErrorOrPreviewFileHandleL()
{
	SetupL();
    OpenFileL( KValidFile, file );
    retval = iHelper->HandleErrorOrPreviewL( KErrCANoRights, file, 
        previewUrl );
    if ( previewUrl )
        {
        iLog->Log( _L( "HandleErrorOrPreviewL: preview URI returned: %d"), retval);
        delete previewUrl;
        previewUrl = NULL;
        User::Leave( retval );
        }   
    else if ( retval != KErrCANoPermission &&
         retval != KErrCANoRights &&
         retval != KErrCancel )
        {
        iLog->Log( _L( "HandleErrorOrPreviewL returned: %d"),retval );
        User::Leave( retval );
        }
    file.Close();
    Teardown();
    return KErrNone;	
}
TInt CBCTestDRMHelperLib::HandleErrorOrPreviewSilentFileL()
{
	SetupL();
            retval = iHelper->HandleErrorOrPreviewL( KErrCANoPermission, 
                KSilentFile, previewUrl );
            if ( previewUrl )
                {
		        iLog->Log( _L( "HandleErrorOrPreviewL: preview URI returned: %d"), retval);
				delete previewUrl;
                previewUrl = NULL;
                User::Leave( retval );
                }   
            else if ( retval != KErrCANoPermission &&
                 retval != KErrCANoRights &&
                 retval != KErrCancel )
                {
		        iLog->Log( _L( "HandleErrorOrPreviewL returned: %d"),retval);
                User::Leave( retval );
                }
    Teardown();
    return KErrNone;	
}
TInt CBCTestDRMHelperLib::HandleErrorOrPreviewSilentFileHandleL()
{
	SetupL();
    OpenFileL( KSilentFile, file );
    retval = iHelper->HandleErrorOrPreviewL( KErrCANoRights, file, 
        previewUrl );
    if ( previewUrl )
        {
        iLog->Log( _L( "HandleErrorOrPreviewL: preview URI returned"));
        delete previewUrl;
        previewUrl = NULL;
        User::Leave( KErrGeneral );
        }   
    else if ( retval != KErrCANoPermission &&
         retval != KErrCANoRights &&
         retval != KErrCancel )
        {
        iLog->Log( _L( "HandleErrorOrPreviewL returned: %d"),retval);
        User::Leave( retval );
        }
    file.Close();
    Teardown();
    return KErrNone;	
}

void CBCTestDRMHelperLib::SetupL()
{

    contentUri = NULL;
    contentUri8 = NULL;
    expired =  EFalse ;
    sendingAllowed = EFalse;
    play = NULL;
    display = NULL;
    print = NULL;
    execute = NULL;
    automatedUseAllowed = EFalse ;
    uriList = NULL;
    supportedDataTypes = 0 ;
    drmMethod = 0 ;
//    omaLevel = CDRMHelper::EOMA_None ;
    //content = NULL;
    previewUrl = NULL;
    buyRights = EFalse ;
    infoUrlExists = EFalse ;
    infoUrl = NULL;
    // Create CDRMHelper object
    User::LeaveIfError( iFs.Connect() );
    iHelper = CDRMHelper::NewL( *CCoeEnv::Static(), iFs );

//	BringToForeground();
}

void CBCTestDRMHelperLib::Teardown()
{
//	SendToBackground();
	
	delete iHelper;
	iHelper = NULL;
	iFs.Close();
}