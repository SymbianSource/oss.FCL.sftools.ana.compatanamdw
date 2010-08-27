/*
* Copyright (c) 2005-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: 
*
*/


//  Include Files  

#include "ConfTimeZone.h"
#include <e32base.h>
#include <e32std.h>
#include <e32cons.h>			// Console
#include <f32file.h> 
#include <tz.h>
#include <BACLINE.H>            // CCommandLineArguments
#include <S32FILE.H>

//  Constants

_LIT(KTextConsoleTitle, "Console");
_LIT(KTextFailed, " failed, leave code = %d");
_LIT(KTextPressAnyKey, "\n\n[press any key]\n");
_LIT(KZoneSettingsFile, "c:\\data\\others\\zonesettings.dat");



//  Global Variables

LOCAL_D CConsoleBase* console; // write all messages to this
void SetTimeZoneL(TDesC& aTimeZone);
void GetTimeZoneL(TDes& aTimeZone);


//  Local Functions

LOCAL_C void MainL()
    {
    TFileName path( _L("c:\\logs\\TestFramework\\STDLIBS\\Stdlibs_Preconfig.txt"));
    RFile file;
    RFs fileSession;
    User::LeaveIfError(fileSession.Connect());
    CleanupClosePushL (fileSession);
    TInt err; 
    
    fileSession.MkDirAll(_L("c:\\logs\\TestFramework\\STDLIBS\\"));
    err = file.Replace(fileSession, path, EFileStreamText | EFileWrite);
    
    
    file.Write(_L8("PreConfig file of TimeZone application\n"));
    
    
    CCommandLineArguments *args = CCommandLineArguments::NewL();
     CleanupStack::PushL(args);
     if (args->Count()> 1)
         {
         TPtrC arg = args->Arg(1);
        if( arg.Compare(_L("1")) == 0)
             {
             RFileWriteStream outStream;
             TInt err = outStream.Replace(fileSession, KZoneSettingsFile, EFileWrite|EFileShareAny);
             CleanupClosePushL(outStream);
             if(err != KErrNone)
                 {
                 file.Write(_L8("preconfig result : failed\n"));
                 User::Leave(err);
                 }
             else
                     {
                 TBuf<64> getTimeZone;
                 TRAP(err, GetTimeZoneL(getTimeZone));
                 if(err != KErrNone)
                       {
                       
                       file.Write(_L8("preconfig result : failed\n"));
                       }
                   else
                       {
                       outStream.WriteL(getTimeZone);
                       
                       file.Write(_L8("preconfig result : passed\n"));

                       _LIT(KGMT0, "Africa/Casablanca");
                       TBuf<64> gmtTimeZone;
                       gmtTimeZone.Copy(KGMT0);

                       TRAP(err, SetTimeZoneL(gmtTimeZone));
                       if(err != KErrNone)
                            {
                            
                            file.Write(_L8("preconfig result : failed\n"));
                            }
                       else
                           {
                           file.Write(_L8("preconfig result : passed\n"));
                           }
                       }
                     }
                CleanupStack::PopAndDestroy();//outStream
             }
         else if( arg.Compare(_L("2")) == 0)
             {
                 RFileReadStream inStream;
                 TInt err = inStream.Open(fileSession, KZoneSettingsFile, EFileRead|EFileShareAny);
                 CleanupClosePushL(inStream);
                 if(err != KErrNone)
                         {
                         
                         file.Write(_L8("preconfig result : failed\n"));
                         User::Leave(err);
                         }
                     else
                         {
                         TBuf<64> timezone;
                         TInt streamSize = inStream.Source()->SizeL();
                         inStream.ReadL(timezone, streamSize/2);
                         
                         _LIT(KSettingTimeZone, "Setting TimeZone\n");
                         
                         
                         TRAPD(err, SetTimeZoneL(timezone));
                         if(err != KErrNone)
                              {
                              file.Write(_L8("preconfig result : failed\n"));
                              }
                         else
                             {
                             TBuf<64> setTimeZone;
                             setTimeZone.Copy(timezone);
                             
                              }
                         }
                 
                 CleanupStack::PopAndDestroy(); //inStream
                 }
         }
     else
         {
         console->Write(_L("No arg was Passed!\n"));
         }
     
     CleanupStack::PopAndDestroy(args);
     CleanupStack::PopAndDestroy();//fileSession
    }

LOCAL_C void DoStartL()
    {
    // Create active scheduler (to run active objects)
    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler();
    CleanupStack::PushL(scheduler);
    CActiveScheduler::Install(scheduler);

    MainL();

    // Delete active scheduler
    CleanupStack::PopAndDestroy(scheduler);
    }

//  Global Functions

GLDEF_C TInt E32Main()
    {
    // Create cleanup stack
    __UHEAP_MARK;
    CTrapCleanup* cleanup = CTrapCleanup::New();

    // Create output console
    TRAPD(createError, console = Console::NewL(KTextConsoleTitle, TSize(
            KConsFullScreen, KConsFullScreen)));
    if (createError)
        return createError;

    // Run application code inside TRAP harness, wait keypress when terminated
    TRAPD(mainError, DoStartL());
    if (mainError)
    
    
    
    


    delete console;
    delete cleanup;
    __UHEAP_MARKEND;
    return KErrNone;
    }


void SetTimeZoneL(TDesC& aTimeZone)
     {
 
     RTz tz;
     TInt err = tz.Connect();
     if(err != KErrNone)
         {
         User::Leave(err);
         }
     CleanupClosePushL(tz);
 
     TBuf8<256> timezone;
     timezone.Copy( aTimeZone ); // Conversion
     CTzId* tzId = CTzId::NewL( timezone );
     CleanupStack::PushL(tzId);
 
     tz.SetTimeZoneL( *tzId );
     CleanupStack::PopAndDestroy(tzId);
     CleanupStack::PopAndDestroy(&tz);
 
     if(err != KErrNone)
         {
         User::Leave(err);
         }
 
     }


void GetTimeZoneL(TDes& aTimeZone)
     {
 
     RTz tz;
     TInt err = tz.Connect();
     if(err != KErrNone)
         {
         User::Leave(err);
         }
     CleanupClosePushL(tz);
 
     CTzId* tzId = tz.GetTimeZoneIdL();
     CleanupStack::PushL(tzId);
     aTimeZone.Copy(tzId->TimeZoneNameID());
     tz.SetTimeZoneL( *tzId );
     
     CleanupStack::PopAndDestroy(tzId);
     CleanupStack::PopAndDestroy(&tz);
 
     if(aTimeZone.Length()== 0)
         {
         User::Leave(-2);
         }
 
     }
