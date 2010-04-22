/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description:      ?Description
*
*/

// INCLUDE FILES
#include "BrCtlBCTestContainer.h"

#include <eiklabel.h>  // for example label control
#include <avkon.hrh>
#include <aknview.h>
#include <AknGlobalConfirmationQuery.h>
#include <BrCtlBCTest.rsg>
#include "brctlbctest.hrh"
#include <BrCtlInterface.h>
#include <CHARCONV.H>
#include "BrCtlBCTestObserver.h"
#include "BrCtlBCTestQueryDialog.h"

// Constants
_LIT( KTestFinished ,"Finished");
_LIT( KTestPassed , "Test case passed");
_LIT( KTestFailed , "Test case failed");


// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CBrCtlBCTestContainer::ConstructL(const TRect& aRect)
// EPOC two phased constructor
// ---------------------------------------------------------
//
void CBrCtlBCTestContainer::ConstructL(const TRect& aRect)
    {
    iBrCtlBCTestObserver = CBrCtlBCTestObserver::NewL();
    iBrCtlBCTestStateChangeObserver = CBrCtlBCTestStateChangeObserver::NewL( this );
    iDownloadMgr.ConnectL( TUid::Uid( KThisAppUid ), *this, EFalse );
    CreateWindowL();
    SetRect(aRect);
    ActivateL();
    iCommandBase = TBrCtlDefs::ECommandIdBase;
    iSavedPage = NULL;


    _LIT(KDir, "BrCtlBCTest");
    _LIT(KFile, "BrCtlBCTest.log");

    TInt err = 0;

    err = iFileLogger.Connect();

    if (err == KErrNone)
        {
        iFileLogger.CreateLog(KDir(), KFile(), EFileLoggingModeOverwrite);
        iCanLog = ETrue;

//        iFileLogger.WriteFormat(KConstructTest);
//        IncrementTestsPassed();
        }
    else
	    {
	    iCanLog = EFalse;
	    }
    }

// Destructor
CBrCtlBCTestContainer::~CBrCtlBCTestContainer()
    {
    if (iBrCtlInterface)
        {
        iBrCtlInterface->RemoveLoadEventObserver(iBrCtlBCTestObserver);
        iBrCtlInterface->RemoveStateChangeObserver(iBrCtlBCTestStateChangeObserver);
        delete iBrCtlInterface;
        }

    if (iSavedPage)
        {
        delete iSavedPage;
        }

    iFileLogger.CloseLog();
    iFileLogger.Close();

    iDownloadMgr.Close();
    delete iBrCtlBCTestStateChangeObserver;
    delete iBrCtlBCTestObserver;
    }

void CBrCtlBCTestContainer::SetAppUi(CBrCtlBCTestAppUi* aAppUi)
	{
    iAppUi = aAppUi;
	}

void CBrCtlBCTestContainer::HandleDMgrEventL( RHttpDownload& /*aDownload*/, THttpDownloadEvent /*aEvent*/ )
    {

    }

// ---------------------------------------------------------
// CBrCtlBCTestContainer::SizeChanged()
// Called by framework when the view size is changed
// ---------------------------------------------------------
//
void CBrCtlBCTestContainer::SizeChanged()
    {
    if (iBrCtlInterface)
        {
        iBrCtlInterface->SetRect(Rect());
        }

    }

// ---------------------------------------------------------
// CBrCtlBCTestContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CBrCtlBCTestContainer::CountComponentControls() const
    {
    if (iBrCtlInterface)
        return 1;
    return 0;
    }

// ---------------------------------------------------------
// CBrCtlBCTestContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CBrCtlBCTestContainer::ComponentControl(TInt aIndex) const
    {
    switch ( aIndex )
        {
        case 0:
            return iBrCtlInterface; // Could be NULL
        default:
            return NULL;
        }
    }

// ---------------------------------------------------------
// CBrCtlBCTestContainer::Draw(const TRect& aRect) const
// ---------------------------------------------------------
//
void CBrCtlBCTestContainer::Draw(const TRect& aRect) const
    {
    
    CWindowGc& gc = SystemGc();
    // example code...
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(KRgbGray);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    
    }

// ---------------------------------------------------------
// CBrCtlBCTestContainer::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CBrCtlBCTestContainer::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    }



// ----------------------------------------------------
// CBrCtlBCTestContainer::HandleKeyEventL(
//     const TKeyEvent& aKeyEvent,TEventCode /*aType*/)
// ?implementation_description
// ----------------------------------------------------
//
TKeyResponse CBrCtlBCTestContainer::HandleKeyEventL(
    const TKeyEvent& /*aKeyEvent*/,TEventCode /*aType*/)
    {
    return EKeyWasNotConsumed;
    }

// ----------------------------------------------------
// CBrCtlBCTestContainer::CancelLoad()
// ?implementation_description
// ----------------------------------------------------
//
void CBrCtlBCTestContainer::CancelLoad()
    {
    iCancelInitDataLoad = ETrue;
    }


// ----------------------------------------------------
// CBrCtlBCTestContainer::HandleCommandL(TInt aCommand)
// ?implementation_description
// ----------------------------------------------------
//
void CBrCtlBCTestContainer::HandleCommandL(TInt aCommand)
    {
    switch ( aCommand )
        {
        case EBrCtlBCTestCmdAllTests:
        	{
            iTestsPassed = 0;
            iTestsFailed = 0;
            iTotalTests = 66;
        	RunAllTestsL();
            _LIT(KTestResults, "All tests finished %d passed %d failed %d tests run out of %d total tests");

            iFileLogger.WriteFormat(KTestResults, iTestsPassed, iTestsFailed, iTestsPassed + iTestsFailed, iTotalTests);
        	break;
        	}

        case EBrCtlBCTestCmdBrCtlTests:
        	{
            iTestsPassed = 0;
            iTestsFailed = 0;
            iTotalTests = 36;
        	RunBrCtlTestsL();
        	break;
        	}

        case EBrCtlBCTestCmdPluginTests:
        	{
            iTestsPassed = 0;
            iTestsFailed = 0;
        	RunPluginTestsL();
        	break;
        	}

        case EBrCtlBCTestCmdDldMgrTests:
        	{
            iTestsPassed = 0;
            iTestsFailed = 0;
        	RunDldMgrTestsL();
        	break;
        	}

        default:
            if (aCommand >= iCommandBase &&
                aCommand < iCommandBase + TBrCtlDefs::ECommandIdWMLBase &&
                iBrCtlInterface)
                {
                iBrCtlInterface->HandleCommandL(aCommand);
                }

            if (aCommand >= iCommandBase + TBrCtlDefs::ECommandIdWMLBase &&
                aCommand < iCommandBase + TBrCtlDefs::ECommandIdRange &&
                iBrCtlInterface)
                {
                iBrCtlInterface->HandleCommandL(aCommand);
                }              
            break;      
        }
    }

TKeyResponse CBrCtlBCTestContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    if (iBrCtlInterface)
        return iBrCtlInterface->OfferKeyEventL(aKeyEvent, aType);
    return EKeyWasConsumed;
    }


void CBrCtlBCTestContainer::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane)
    {
    if (iBrCtlInterface && (aResourceId == R_BRCTLBCTEST_MENU))
        {
        iBrCtlInterface->AddOptionMenuItemsL(*aMenuPane, aResourceId);
        RPointerArray<TBrCtlWmlServiceOption>* options;
        options = iBrCtlInterface->WMLOptionMenuItemsL();
        TInt i;
        TInt count = options->Count();
        for (i = 0; i < count; i++)
            {
            TBrCtlWmlServiceOption* option = (*options)[i];
            if (option != NULL)
                {
                CEikMenuPaneItem::SData item;
                item.iText.Copy(option->Text());
                item.iCommandId = option->ElemID();
                item.iFlags = 0;
                item.iCascadeId = 0;
                aMenuPane->InsertMenuItemL(item, 0);
                }
            }
        }
    iMenuPane = aMenuPane;
    }

HBufC8* CBrCtlBCTestContainer::ReadFileLC(const TDesC& aFileName)
    {
    RFs rfs;
    RFile file;
    User::LeaveIfError(rfs.Connect());
    CleanupClosePushL(rfs);
    User::LeaveIfError(file.Open(rfs, aFileName, EFileRead));
    CleanupClosePushL(file);
    TInt size;
    User::LeaveIfError(file.Size(size));
    HBufC8* buf = HBufC8::NewLC(size);
    TPtr8 bufPtr(buf->Des());
    User::LeaveIfError(file.Read(bufPtr));
    CleanupStack::Pop(); // buf
    CleanupStack::PopAndDestroy(2); // file, rfs
    CleanupStack::PushL(buf);
    return buf;
    }


void CBrCtlBCTestContainer::RunAllTestsL()
    {
    _LIT( KAllTests, "Starting all Tests" );

    iFileLogger.WriteFormat( KAllTests );
    
    RunBrCtlTestsL();
    
//    RunPluginTestsL();
    
    RunDldMgrTestsL();
    
    TestsDoneDialog();
    }

void CBrCtlBCTestContainer::RunBrCtlTestsL()
    {
    _LIT( KBrCtlTests, "Starting BrCtl Tests" );

    iFileLogger.WriteFormat( KBrCtlTests );
    
    CreateBrowserControlLTest();
    HandleCommandLTest();
    HandleDownloadCommandLTest();
    ContentSizeTest();
    SetBrowserSettingLTest();
    BrowserSettingLTest();
    LoadDataLTest();
    InitLoadDataLTest();
    LoadUrlLTest();
    LoadFileLWithTDesCTest();
    LoadFileLWithFileHandleTest();
    WMLOptionsMenuItemsLTest();
    AddOptionMenuItemsLTest();
    ClearCacheTest();
    IsUrlInCacheTest();
    ClearItemInCacheTest();
    PageInfoLCTest();
    NavigationAvailableTest();
    CertInfoTest();
    AddLoadEventObserverLTest();
    RemoveLoadEventObserverTest();
    ImageCountLTest();
    FocusedElementTypeTest();
    AddStateChangeObserverLTest();
    RemoveStateChangeObserverTest();
    VersionInfoLCTest();
    SetSelfDownloadContentTypesLTest();
    SetParamLTest();
    LoadSavedPageLTest();
    MinimumSizeTest();
    OfferKeyEventLTest();
    SetFocusTest();
    FindKeywordTest();
    FindKeywordAgainTest();
    ZoomLevelsTest();
    TestTakeSnapShotL();

    }

void CBrCtlBCTestContainer::RunPluginTestsL()
    {
    _LIT( KPluginTests, "Starting Plugin Tests" );

    iFileLogger.WriteFormat( KPluginTests );
    
    _LIT(KUrl, "c:\\pluginapitest\\plugin.html");
    RFs rfs;
    RFile file;
    User::LeaveIfError(rfs.Connect());
    CleanupClosePushL(rfs);
    User::LeaveIfError(file.Open(rfs, KUrl(), EFileShareReadersOnly));
    CleanupClosePushL(file);
    iBrCtlInterface->LoadFileL(file);
    CleanupStack::PopAndDestroy(2); // file, rfs


    }

void CBrCtlBCTestContainer::RunDldMgrTestsL()
    {
    _LIT( KDldMgrTests, "Starting Download Manager Tests" );

    iFileLogger.WriteFormat( KDldMgrTests );
    
    CDownloadMgrUiLibRegistryDestructorTest();
    NewLTest();
    RegisterDownloadsListLTest();
    RegisterUserInteractionsLTest();
    HandleDownloadLTest();
    OkToExitLTest();
    PrepareToExitWithAppUiPointerTest();
    PrepareToExitWithAppUidTest();
    UserInteractGetBoolAttributeLTest();
    UserInteractGetIntAttributeLTest();
    UserInteractGetStringAttributeLTDesC8Test();
    UserInteractGetStringAttributeLTDesC16Test();
    UserInteractSetBoolAttributeLTest();
    UserInteractSetIntAttributeLTest();
    UserInteractSetStringAttributeLTDesC8Test();
    UserInteractSetStringAttributeLTDesC16Test();
    CancelDisplayingDownloadsListTest();
    CountTest();
    DisplayDownloadsListLTest();
    DownloadMenuTest();
    IsVisibleTest();
    DownloadListGetBoolAttributeLTest();
    DownloadListGetIntAttributeLTest();
    DownloadListGetStringAttributeLTDesC8Test();
    DownloadListGetStringAttributeLTDesC16Test();
    DownloadListSetBoolAttributeLTest();
    DownloadListSetIntAttributeLTest();
    DownloadListSetStringAttributeLTDesC8Test();
    DownloadListSetStringAttributeLTDesC16Test();
    AddMenuLTest();
    }

void CBrCtlBCTestContainer::CreateBrowserControlLTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::CreateBrowserControlL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    TPoint base(0, 0);
    TPoint extent(352, 295);
    TRect rect(base, extent);
    TRAPD(err, iBrCtlInterface = CreateBrowserControlL( this, rect, TBrCtlDefs::ECapabilityDisplayScrollBar | TBrCtlDefs::ECapabilityClientResolveEmbeddedURL | TBrCtlDefs::ECapabilityLoadHttpFw,
        iCommandBase, iBrCtlBCTestObserver, iBrCtlBCTestObserver,
        iBrCtlBCTestObserver, iBrCtlBCTestObserver, NULL, NULL, iBrCtlBCTestObserver) );

    iBrCtlInterface->MakeVisible( ETrue );

    iFileLogger.WriteFormat( KTestFinished );

    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    }

void CBrCtlBCTestContainer::HandleCommandLTest()
    {
    TBool testPassed = EFalse;
    
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::HandleCommandL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    if ( iBrCtlInterface )
	    {
	    TRAPD( err, iBrCtlInterface->HandleCommandL( TBrCtlDefs::ECommandShowImages ) );
	    
	    if ( err == KErrNone )
		    {
		    testPassed = ETrue;
		    }
	    }
    
    iFileLogger.WriteFormat( KTestFinished );

    if ( testPassed )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    }

void CBrCtlBCTestContainer::HandleDownloadCommandLTest()
    {
    TBool testPassed = EFalse;

    _LIT( KCurrentTest ,"Test the CBrCtlInterface::HandleDownloadCommandL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    if ( iBrCtlInterface )
	    {
	    TRAPD( err, iBrCtlInterface->HandleDownloadCommandL( 0, TBrCtlDefs::EDownloadCmdMarkAsProgressive ) );
	    
	    if ( err == KErrNone )
		    {
		    testPassed = ETrue;
		    }
	    }
    
    iFileLogger.WriteFormat( KTestFinished );

    if ( testPassed )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    }

void CBrCtlBCTestContainer::ContentSizeTest()
    {
    TBool testPassed = EFalse;

    _LIT( KCurrentTest ,"Test the CBrCtlInterface::ContentSize method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    TSize testSize;
    
    if ( iBrCtlInterface )
	    {
	    testSize = iBrCtlInterface->ContentSize();
	    
        if ( testSize.iWidth >= 0 && testSize.iHeight >= 0 )
	        {
	        testPassed = ETrue;
	        }
	    }
    
    iFileLogger.WriteFormat( KTestFinished );

    if ( testPassed )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    }

void CBrCtlBCTestContainer::SetBrowserSettingLTest()
    {
    TBool testPassed = EFalse;

    _LIT( KCurrentTest ,"Test the CBrCtlInterface::SetBrowserSettingL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    if ( iBrCtlInterface )
	    {
	    TRAPD( err, iBrCtlInterface->SetBrowserSettingL( TBrCtlDefs::ESettingsAutoLoadImages, 0 ) );
	    
	    if ( err == KErrNone )
		    {
		    testPassed = ETrue;
		    }
	    }

    iFileLogger.WriteFormat( KTestFinished );

    if ( testPassed )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    }

void CBrCtlBCTestContainer::BrowserSettingLTest()
    {
    TBool testPassed = EFalse;

    _LIT( KCurrentTest ,"Test the CBrCtlInterface::BrowserSettingL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    if ( iBrCtlInterface )
	    {
	    TUint setting;
	    
	    TRAPD( err, ( setting = iBrCtlInterface->BrowserSettingL( TBrCtlDefs::ESettingsAutoLoadImages ) ) );
	    
	    if ( err == KErrNone )
		    {
		    testPassed = ETrue;
		    }
	    }

    iFileLogger.WriteFormat( KTestFinished );

    if ( testPassed )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    }

void CBrCtlBCTestContainer::LoadDataLTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::LoadDataL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    _LIT(KUrl, "c:\\BrCtlTest\\loadtest.html");
    _LIT8(KDataType, "text/html");

    HBufC8* data = ReadFileLC(KUrl);
    TDataType dataType(KDataType());
    TUid uid;
    uid.iUid = KCharacterSetIdentifierIso88591;
    TRAPD( err, iBrCtlInterface->LoadDataL(KUrl, *data, dataType, uid) );

    iFileLogger.WriteFormat( KTestFinished );

    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    CleanupStack::PopAndDestroy(); // data
    }

void CBrCtlBCTestContainer::InitLoadDataLTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::InitLoadDataL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    _LIT(KUrl, "c:\\BrCtlTest\\loadtest.html");
    HBufC8* data = ReadFileLC(KUrl);
    _LIT8(KDataType, "text/html");
    TDataType dataType(KDataType());
    MBrCtlDataLoadConsumer* brCtlDataLoadConsumer = NULL;
    TUid uid;
    uid.iUid = KCharacterSetIdentifierIso88591;
    TRAPD( err, iBrCtlInterface->InitLoadDataL(KUrl, dataType, uid, data->Length(),
        this, &brCtlDataLoadConsumer) );

    if (brCtlDataLoadConsumer)
        {
        brCtlDataLoadConsumer->HandleNextDataChunk(*data);
        if (!iCancelInitDataLoad)
            {
            brCtlDataLoadConsumer->HandleLoadComplete();
            }
        }
        
    iCancelInitDataLoad = EFalse;

    iFileLogger.WriteFormat( KTestFinished );

    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    CleanupStack::PopAndDestroy(); // data
    }

void CBrCtlBCTestContainer::LoadUrlLTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::LoadUrlL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    _LIT(KUrl, "file://BrCtlTest/loadtest.html");

    TRAPD( err, iBrCtlInterface->LoadUrlL( KUrl ) );

    iFileLogger.WriteFormat( KTestFinished );

    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    }

void CBrCtlBCTestContainer::LoadFileLWithTDesCTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::LoadFileL method with TDesC argument" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    _LIT(KUrl, "c:\\BrCtlTest\\loadtest.html");
    TRAPD( err, iBrCtlInterface->LoadFileL(KUrl) );

    iFileLogger.WriteFormat( KTestFinished );

    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    }

void CBrCtlBCTestContainer::LoadFileLWithFileHandleTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::LoadFileL method with file handle argument" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    _LIT(KUrl, "c:\\BrCtlTest\\loadtest.html");
    RFs rfs;
    RFile file;
    User::LeaveIfError(rfs.Connect());
    CleanupClosePushL(rfs);
    User::LeaveIfError(file.Open(rfs, KUrl(), EFileShareReadersOnly));
    CleanupClosePushL(file);
    TRAPD( err, iBrCtlInterface->LoadFileL(file) );
    CleanupStack::PopAndDestroy(2); // file, rfs

    iFileLogger.WriteFormat( KTestFinished );

    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    }

void CBrCtlBCTestContainer::WMLOptionsMenuItemsLTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::WMLOptionsMenuItemsL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    RPointerArray<TBrCtlWmlServiceOption>* options;
    TRAPD( err, options = iBrCtlInterface->WMLOptionMenuItemsL() );

    iFileLogger.WriteFormat( KTestFinished );

    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    }

void CBrCtlBCTestContainer::AddOptionMenuItemsLTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::AddOptionMenuItemsL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    TRAPD( err, iBrCtlInterface->AddOptionMenuItemsL( *iMenuPane, 0, 0 ) );

    iFileLogger.WriteFormat( KTestFinished );

    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    }

void CBrCtlBCTestContainer::ClearCacheTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::ClearCache method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    TUint result = iBrCtlInterface->ClearCache();
    
    iFileLogger.WriteFormat( KTestFinished );

    if ( result >= 0 )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    }

void CBrCtlBCTestContainer::IsUrlInCacheTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::IsUrlInCache method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    _LIT(KUrl, "c:\\BrCtlTest\\loadtest.html");
    
    TBool result = iBrCtlInterface->IsUrlInCache( (TDesC16 &)KUrl() );
    
    iFileLogger.WriteFormat( KTestFinished );

    if ( result == EFalse )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    }

void CBrCtlBCTestContainer::ClearItemInCacheTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::ClearItemInCache method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    _LIT(KUrl, "c:\\BrCtlTest\\loadtest.html");
    
    TInt result = iBrCtlInterface->ClearItemInCache( (TDesC16 &)KUrl() );
    
    iFileLogger.WriteFormat( KTestFinished );

    if ( ( result == KErrNotFound ) || ( result == KErrNone ) )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    }

void CBrCtlBCTestContainer::PageInfoLCTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::PageInfoLC method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    _LIT(KUrl, "c:\\BrCtlTest\\loadtest.html");
    iBrCtlInterface->LoadFileL(KUrl);

    HBufC* url = iBrCtlInterface->PageInfoLC( TBrCtlDefs::EPageInfoUrl );

    iFileLogger.WriteFormat( KTestFinished );

	  iFileLogger.WriteFormat( KTestPassed );
    IncrementTestsPassed();
    
    CleanupStack::PopAndDestroy(); // url
    }

void CBrCtlBCTestContainer::NavigationAvailableTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::NavigationAvailable method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    TBool nav = iBrCtlInterface->NavigationAvailable( TBrCtlDefs::ENavigationBack );
    
    iFileLogger.WriteFormat( KTestFinished );

    if ( nav == 0 || nav == 1 )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    }

void CBrCtlBCTestContainer::CertInfoTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::CertInfo method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
  	const TCertInfo* certInfo = iBrCtlInterface->CertInfo();

    iFileLogger.WriteFormat( KTestFinished );

    if ( certInfo == NULL )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    }

void CBrCtlBCTestContainer::AddLoadEventObserverLTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::AddLoadEventObserverL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    TRAPD( err, iBrCtlInterface->AddLoadEventObserverL(iBrCtlBCTestObserver) );

    iFileLogger.WriteFormat( KTestFinished );

    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    iBrCtlInterface->RemoveLoadEventObserver(iBrCtlBCTestObserver);
    }

void CBrCtlBCTestContainer::RemoveLoadEventObserverTest()
    {
    _LIT( KCurrentTest ,"Test the RemoveLoadEventObserver method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    iBrCtlInterface->AddLoadEventObserverL(iBrCtlBCTestObserver);

    iBrCtlInterface->RemoveLoadEventObserver(iBrCtlBCTestObserver);

    iFileLogger.WriteFormat( KTestFinished );

    iFileLogger.WriteFormat( KTestPassed );
    IncrementTestsPassed();
    }

void CBrCtlBCTestContainer::ImageCountLTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::ImageCountL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    TInt imgcount;
    
    TRAPD( err, imgcount = iBrCtlInterface->ImageCountL() );
    
    iFileLogger.WriteFormat( KTestFinished );

    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    }

void CBrCtlBCTestContainer::FocusedElementTypeTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::FocusedElementType method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    _LIT(KUrl, "c:\\BrCtlTest\\loadtest.html");
    iBrCtlInterface->LoadFileL(KUrl);

    iBrCtlInterface->SetFocus( ETrue, EDrawNow );
    
    TBrCtlDefs::TBrCtlElementType elementtype;
    
    TRAPD( err, elementtype = iBrCtlInterface->FocusedElementType() );

    _LIT(KTestResults, "element type is %d ");

    iFileLogger.WriteFormat( KTestResults, elementtype );

    iFileLogger.WriteFormat( KTestFinished );

    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    }

void CBrCtlBCTestContainer::AddStateChangeObserverLTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::AddStateChangeObserverL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    TRAPD( err, iBrCtlInterface->AddStateChangeObserverL(iBrCtlBCTestStateChangeObserver) );

    iFileLogger.WriteFormat( KTestFinished );

    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    iBrCtlInterface->RemoveStateChangeObserver(iBrCtlBCTestStateChangeObserver);
    }

void CBrCtlBCTestContainer::RemoveStateChangeObserverTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::RemoveStateChangeObserver method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    iBrCtlInterface->AddStateChangeObserverL(iBrCtlBCTestStateChangeObserver);

    iBrCtlInterface->RemoveStateChangeObserver(iBrCtlBCTestStateChangeObserver);

    iFileLogger.WriteFormat( KTestFinished );

    iFileLogger.WriteFormat( KTestPassed );
    IncrementTestsPassed();
    }

void CBrCtlBCTestContainer::VersionInfoLCTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::VersionInfoLC method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    HBufC* verinfo = iBrCtlInterface->VersionInfoLC( TBrCtlDefs::EVersionInfoName );
    
    iFileLogger.WriteFormat( verinfo->Des() );
    
    iFileLogger.WriteFormat( KTestFinished );

    if ( verinfo->Length() > 0 )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
	    
	CleanupStack::PopAndDestroy(); // verinfo
    }

void CBrCtlBCTestContainer::SetSelfDownloadContentTypesLTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::SetSelfDownloadContentTypesL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    _LIT( KContentType ,"text/html");
    TRAPD(err, iBrCtlInterface->SetSelfDownloadContentTypesL( (TDesC16&)KContentType() ) );
    
    iFileLogger.WriteFormat( KTestFinished );

    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    }

void CBrCtlBCTestContainer::SetParamLTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::SetParamL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    _LIT( KContentType, "text/html");

    TRAPD( err, iBrCtlInterface->SetParamL( TBrCtlDefs::EParamsSelfDownoadableTypes, KContentType ) )

    iFileLogger.WriteFormat( KTestFinished );

    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    }

void CBrCtlBCTestContainer::LoadSavedPageLTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::LoadSavedPageL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    _LIT( KUid, "savedpage://4");
    _LIT(KUrl, "c:\\BrCtlTest\\loadtest.saved");

    HBufC8* databuf = ReadFileLC(KUrl);
    HBufC16* bigbuf = HBufC::NewL(databuf->Des().Length());

    bigbuf->Des().Copy(databuf->Des());
    
    TRAPD( err, iBrCtlInterface->LoadSavedPageL( KUid, *bigbuf ) );
    
    iFileLogger.WriteFormat( KTestFinished );

    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    
    delete bigbuf;
 	CleanupStack::PopAndDestroy(); // databuf
   }

void CBrCtlBCTestContainer::MinimumSizeTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::MinimumSize method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    TSize testSize = iBrCtlInterface->MinimumSize();
    
    iFileLogger.WriteFormat( KTestFinished );

    if ( testSize.iWidth > 0 && testSize.iHeight > 0 )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    }

void CBrCtlBCTestContainer::OfferKeyEventLTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::OfferKeyEventL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    TKeyEvent key;
    
    key.iCode = 0;
    key.iScanCode = 0;
    key.iModifiers = 0;
    key.iRepeats = 0;
    
    TRAPD( err, iBrCtlInterface->OfferKeyEventL( key, EEventNull ) );
    
    iFileLogger.WriteFormat( KTestFinished );

    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    }

void CBrCtlBCTestContainer::SetFocusTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::SetFocus method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    iBrCtlInterface->SetFocus( ETrue, EDrawNow );
    
    iFileLogger.WriteFormat( KTestFinished );

    iFileLogger.WriteFormat( KTestPassed );
    IncrementTestsPassed();
    }

void CBrCtlBCTestContainer::FindKeywordTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::FindKeyword method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    _LIT(KUrl, "c:\\BrCtlTest\\loadtest.html");
    iBrCtlInterface->LoadFileL(KUrl);

    _LIT( KKeyword ,"" );
    TInt result = iBrCtlInterface->FindKeyword( KKeyword );
    
    iFileLogger.WriteFormat( KTestFinished );

    if ( result == 0 )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    }

void CBrCtlBCTestContainer::FindKeywordAgainTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::FindKeywordAgain method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    TBrCtlDefs::TBrCtlFindResponse result = iBrCtlInterface->FindKeywordAgain( ETrue );
    
    iFileLogger.WriteFormat( KTestFinished );

    if ( result == TBrCtlDefs::EFindNoMatches )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    }

void CBrCtlBCTestContainer::ZoomLevelsTest()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::ZoomLevels method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    RArray<TUint>* zoom = iBrCtlInterface->ZoomLevels();
    
    iFileLogger.WriteFormat( KTestFinished );

    if ( zoom == NULL )
		    {
				iFileLogger.WriteFormat( KTestPassed );
				IncrementTestsPassed();
		    }
    else
        {
		    if ( zoom->Count() > 0 )
				    {
				    iFileLogger.WriteFormat( KTestPassed );
			      IncrementTestsPassed();
				    }
		    else
				    {
				    iFileLogger.WriteFormat( KTestFailed );
			      IncrementTestsFailed();
				    }
        }
    }

void CBrCtlBCTestContainer::CDownloadMgrUiLibRegistryDestructorTest()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiLibRegistry destructor method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    delete registry;

    iFileLogger.WriteFormat( KTestFinished );
    
	iFileLogger.WriteFormat( KTestPassed );
    IncrementTestsPassed();
	}

void CBrCtlBCTestContainer::NewLTest()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiLibRegistry::NewL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry;
    
    TRAPD( err, registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr ) );
    
    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    delete registry;
	}

void CBrCtlBCTestContainer::RegisterDownloadsListLTest()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiLibRegistry::RegisterDownloadsListL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiDownloadsList* downloadList;
    
    TRAPD(err, downloadList = &registry->RegisterDownloadsListL() );
    
    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    delete registry;
	}

void CBrCtlBCTestContainer::RegisterUserInteractionsLTest()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiLibRegistry::RegisterUserInteractionsL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiUserInteractions* userInteractions;
    
    TRAPD(err, userInteractions = &registry->RegisterUserInteractionsL() );
    
    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    delete registry;
	}

void CBrCtlBCTestContainer::HandleDownloadLTest()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiUserInteractions::HandleDownloadL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiUserInteractions* userInteractions = &registry->RegisterUserInteractionsL();
    
    _LIT8( KCodUrl, "testsuite.nokia-boston.com" );
    HBufC8* buf = HBufC8::NewLC( KCodUrl().Length() );
    buf->Des().Copy( KCodUrl() );            
    _LIT8( KCodMimeType, "text/x-co-desc" );


    TInt retVal;
    RHttpDownload* download;
    download = &iDownloadMgr.CreateCodDownloadL( KCodUrl(),
        	                                     buf->Des(),
        	                                     KCodMimeType(),
        	                                     NULL,
        	                                     retVal );


    TRAPD( err, userInteractions->HandleDownloadL( *download ) );
    
    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    iDownloadMgr.DeleteAll();
    delete registry;
	}

void CBrCtlBCTestContainer::OkToExitLTest()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiUserInteractions::OkToExitL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiUserInteractions* userInteractions = &registry->RegisterUserInteractionsL();
    
    TRAPD( err, userInteractions->OkToExitL() );
    
    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    iDownloadMgr.DeleteAll();
    delete registry;
	}

void CBrCtlBCTestContainer::PrepareToExitWithAppUiPointerTest()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiUserInteractions::PrepareToExit method with AppUi argument" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiUserInteractions* userInteractions = &registry->RegisterUserInteractionsL();
    
    const TInt KTestAppMainViewId = 1;
    const TInt KTestAppCustMsgOpenDownloadsListId = 1;
    TVwsViewId viewId( TUid::Uid( KThisAppUid ), 
                       TUid::Uid(KTestAppMainViewId) ); 
    TUid customMessageId( TUid::Uid(KTestAppCustMsgOpenDownloadsListId) ); 
    TBufC8<1> viewActivationMsg( KNullDesC8 );
    TInt result = userInteractions->PrepareToExit( *iAppUi, 
                                                   ETerminatedBySystem, 
                                                   viewId, 
                                                   customMessageId, 
                                                   viewActivationMsg );

    iFileLogger.WriteFormat( KTestFinished );
    
    if ( result == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    delete registry;
	}

void CBrCtlBCTestContainer::PrepareToExitWithAppUidTest()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiUserInteractions::PrepareToExit method with AppUid argument" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiUserInteractions* userInteractions = &registry->RegisterUserInteractionsL();
    
    TInt result = userInteractions->PrepareToExit( 0, 
                                                   0, 
                                                   0 );

    iFileLogger.WriteFormat( KTestFinished );
    
    if ( result == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    delete registry;
	}

void CBrCtlBCTestContainer::UserInteractGetBoolAttributeLTest()
    {
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiUserInteractions::GetBoolAttributeL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiUserInteractions* userInteractions = &registry->RegisterUserInteractionsL();
    
    TBool value;
    
    TRAPD( err, userInteractions->GetBoolAttributeL( 0, value ) );

    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    delete registry;
    }

void CBrCtlBCTestContainer::UserInteractGetIntAttributeLTest()
{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiUserInteractions::GetIntAttributeL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiUserInteractions* userInteractions = &registry->RegisterUserInteractionsL();
    
    TInt32 value;
    
    TRAPD( err, userInteractions->GetIntAttributeL( 0, value ) );

    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNotSupported )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    delete registry;
}

void CBrCtlBCTestContainer::UserInteractGetStringAttributeLTDesC8Test()
{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiUserInteractions::GetStringAttributeL method with TDesC8 argument" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiUserInteractions* userInteractions = &registry->RegisterUserInteractionsL();
    
    HBufC8* stringAttr = HBufC8::NewLC( KMaxUrlLength );
    TPtr8 stringAttrPtr = stringAttr->Des();
    
    TRAPD( err, userInteractions->GetStringAttributeL( 0, stringAttrPtr ) );

    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNotSupported )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

 	CleanupStack::PopAndDestroy(); // stringAttr
    delete registry;
}

void CBrCtlBCTestContainer::UserInteractGetStringAttributeLTDesC16Test()
{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiUserInteractions::GetStringAttributeL method with TDesC16 argument" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiUserInteractions* userInteractions = &registry->RegisterUserInteractionsL();
    
    HBufC16* stringAttr = HBufC16::NewLC( KMaxUrlLength );
    TPtr16 stringAttrPtr = stringAttr->Des();
    
    TRAPD( err, userInteractions->GetStringAttributeL( 0, stringAttrPtr ) );

    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNotSupported )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

 	CleanupStack::PopAndDestroy(); // stringAttr
    delete registry;
}

void CBrCtlBCTestContainer::UserInteractSetBoolAttributeLTest()
{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiUserInteractions::SetBoolAttributeL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiUserInteractions* userInteractions = &registry->RegisterUserInteractionsL();
    
    TRAPD( err, userInteractions->SetBoolAttributeL( 0, EFalse ) );

    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    delete registry;
}

void CBrCtlBCTestContainer::UserInteractSetIntAttributeLTest()
{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiUserInteractions::SetIntAttributeL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiUserInteractions* userInteractions = &registry->RegisterUserInteractionsL();
    
    TRAPD( err, userInteractions->SetIntAttributeL( 0, 0 ) );

    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNotSupported )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    delete registry;
}

void CBrCtlBCTestContainer::UserInteractSetStringAttributeLTDesC8Test()
{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiUserInteractions::SetStringAttributeL method with TDesC8 argument" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiUserInteractions* userInteractions = &registry->RegisterUserInteractionsL();
    
    _LIT8( KEmptyString, "" );
    TRAPD( err, userInteractions->SetStringAttributeL( 0, KEmptyString ) );

    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNotSupported )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    delete registry;
}

void CBrCtlBCTestContainer::UserInteractSetStringAttributeLTDesC16Test()
{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiUserInteractions::SetStringAttributeL method with TDesC16 argument" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiUserInteractions* userInteractions = &registry->RegisterUserInteractionsL();
    
    _LIT16( KEmptyString, "" );
    TRAPD( err, userInteractions->SetStringAttributeL( 0, KEmptyString ) );

    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNotSupported )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    delete registry;
}

void CBrCtlBCTestContainer::CancelDisplayingDownloadsListTest()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiDownloadList::CancelDisplayingDownloadsList method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiDownloadsList* downloadList = &registry->RegisterDownloadsListL();
    
    downloadList->DisplayDownloadsListL();
    
    downloadList->CancelDisplayingDownloadsList();
    
    iFileLogger.WriteFormat( KTestFinished );
    
    iFileLogger.WriteFormat( KTestPassed );
    IncrementTestsPassed();

    delete registry;
	}

void CBrCtlBCTestContainer::CountTest()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiDownloadList::Count method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiDownloadsList* downloadList = &registry->RegisterDownloadsListL();
    
    TInt result = downloadList->Count();
        
    iFileLogger.WriteFormat( KTestFinished );
    
    if ( result == 0 )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    delete registry;
	}

void CBrCtlBCTestContainer::DisplayDownloadsListLTest()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiDownloadList::DisplayDownloadsListL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiDownloadsList* downloadList = &registry->RegisterDownloadsListL();
    
    TRAPD( err, downloadList->DisplayDownloadsListL() );
    
    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    downloadList->CancelDisplayingDownloadsList();
    delete registry;
	}

void CBrCtlBCTestContainer::DownloadMenuTest()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiDownloadList::DownloadMenu method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiDownloadsList* downloadList = &registry->RegisterDownloadsListL();
    
    CDownloadMgrUiDownloadMenu* downloadMenu = NULL;
    downloadMenu = &downloadList->DownloadMenu();
    
    iFileLogger.WriteFormat( KTestFinished );
    
    if ( downloadMenu )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    downloadList->CancelDisplayingDownloadsList();
    delete registry;
	}

void CBrCtlBCTestContainer::IsVisibleTest()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiDownloadList::IsVisible method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiDownloadsList* downloadList = &registry->RegisterDownloadsListL();
    
    TBool isVisible = downloadList->IsVisible();
    
    iFileLogger.WriteFormat( KTestFinished );
    
    if ( isVisible == EFalse )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    downloadList->CancelDisplayingDownloadsList();
    delete registry;
	}

void CBrCtlBCTestContainer::DownloadListGetBoolAttributeLTest()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiDownloadsList::GetBoolAttributeL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiDownloadsList* downloadList = &registry->RegisterDownloadsListL();
    
    TBool value;
    
    TRAPD( err, downloadList->GetBoolAttributeL( 0, value ) );

    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNotSupported )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    delete registry;
	}

void CBrCtlBCTestContainer::DownloadListGetIntAttributeLTest()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiDownloadsList::GetIntAttributeL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiDownloadsList* downloadList = &registry->RegisterDownloadsListL();
    
    TInt32 value;
    
    TRAPD( err, downloadList->GetIntAttributeL( 0, value ) );

    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNotSupported )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    delete registry;
	}

void CBrCtlBCTestContainer::DownloadListGetStringAttributeLTDesC8Test()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiDownloadsList::GetStringAttributeL method with TDesC8 argument" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiDownloadsList* downloadList = &registry->RegisterDownloadsListL();
    
    HBufC8* stringAttr = HBufC8::NewLC( KMaxUrlLength );
    TPtr8 stringAttrPtr = stringAttr->Des();
    
    TRAPD( err, downloadList->GetStringAttributeL( 0, stringAttrPtr ) );

    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNotSupported )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

 	CleanupStack::PopAndDestroy(); // stringAttr
    delete registry;
	}

void CBrCtlBCTestContainer::DownloadListGetStringAttributeLTDesC16Test()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiDownloadsList::GetStringAttributeL method with TDesC16 argument" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiDownloadsList* downloadList = &registry->RegisterDownloadsListL();
    
    HBufC16* stringAttr = HBufC16::NewLC( KMaxUrlLength );
    TPtr16 stringAttrPtr = stringAttr->Des();
    
    TRAPD( err, downloadList->GetStringAttributeL( 0, stringAttrPtr ) );

    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNotSupported )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

 	CleanupStack::PopAndDestroy(); // stringAttr
    delete registry;
	}

void CBrCtlBCTestContainer::DownloadListSetBoolAttributeLTest()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiDownloadsList::SetBoolAttributeL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiDownloadsList* downloadList = &registry->RegisterDownloadsListL();
    
    TRAPD( err, downloadList->SetBoolAttributeL( 0, EFalse ) );

    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNotSupported )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    delete registry;
	}

void CBrCtlBCTestContainer::DownloadListSetIntAttributeLTest()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiDownloadsList::SetIntAttributeL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiDownloadsList* downloadList = &registry->RegisterDownloadsListL();
    
    TRAPD( err, downloadList->SetIntAttributeL( 0, 0 ) );

    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNotSupported )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    delete registry;
	}

void CBrCtlBCTestContainer::DownloadListSetStringAttributeLTDesC8Test()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiDownloadsList::SetStringAttributeL method with TDesC8 argument" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiDownloadsList* downloadList = &registry->RegisterDownloadsListL();
    
    _LIT8( KEmptyString, "" );
    TRAPD( err, downloadList->SetStringAttributeL( 0, KEmptyString ) );

    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNotSupported )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    delete registry;
	}

void CBrCtlBCTestContainer::DownloadListSetStringAttributeLTDesC16Test()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiDownloadsList::SetStringAttributeL method with TDesC16 argument" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiDownloadsList* downloadList = &registry->RegisterDownloadsListL();
    
    _LIT16( KEmptyString, "" );
    TRAPD( err, downloadList->SetStringAttributeL( 0, KEmptyString ) );

    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNotSupported )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    delete registry;
	}

void CBrCtlBCTestContainer::AddMenuLTest()
	{
    _LIT( KCurrentTest ,"Test the CDownloadMgrUiDownloadMenu::AddMenuL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CDownloadMgrUiLibRegistry* registry = CDownloadMgrUiLibRegistry::NewL( iDownloadMgr );
    
    CDownloadMgrUiDownloadsList* downloadList = &registry->RegisterDownloadsListL();
    
    CEikMenuPane* fakePane = new(ELeave) CEikMenuPane( iAppUi );

    CEikMenuPaneItem::SData item;
    fakePane->InsertMenuItemL(item, 0);
    item.iCommandId = 1;
    fakePane->InsertMenuItemL(item, 0);
    fakePane->InsertMenuItemL(item, 0);
    fakePane->InsertMenuItemL(item, 0);
    fakePane->InsertMenuItemL(item, 0);

    TRAPD( err, downloadList->DownloadMenu().AddMenuL( 22, *fakePane, 1 ) );    

    iFileLogger.WriteFormat( KTestFinished );
    
    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }

    downloadList->CancelDisplayingDownloadsList();
    delete fakePane;
    delete registry;
	}

void CBrCtlBCTestContainer::TestsDoneDialog()
	{
	CAknGlobalConfirmationQuery* pQ = CAknGlobalConfirmationQuery::NewL();
	CleanupStack::PushL(pQ);

	_LIT(KQuestion, "Tests complete.");

	TRequestStatus theStat = KRequestPending;
	pQ->ShowConfirmationQueryL(theStat, KQuestion, R_AVKON_SOFTKEYS_OK_EMPTY);
	User::WaitForRequest(theStat);
	   
	CleanupStack::PopAndDestroy(pQ);
	TBool answer = (theStat.Int() == EAknSoftkeyYes);
	}

void CBrCtlBCTestContainer::IncrementTestsPassed ()
    {
    iTestsPassed++;
    }

void CBrCtlBCTestContainer::IncrementTestsFailed ()
    {
    iTestsFailed++;
    }

void CBrCtlBCTestContainer::TestTakeSnapShotL()
    {
    _LIT( KCurrentTest ,"Test the CBrCtlInterface::TakeSnapShotL method" );
    iFileLogger.WriteFormat( KCurrentTest );
    
    CFbsBitmap* bitmap( new CFbsBitmap() );
         
    TRAPD( err, iBrCtlInterface->TakeSnapshotL(*bitmap) );
		delete bitmap;
		
    iFileLogger.WriteFormat( KTestFinished );

    if ( err == KErrNone )
	    {
	    iFileLogger.WriteFormat( KTestPassed );
        IncrementTestsPassed();
	    }
    else
	    {
	    iFileLogger.WriteFormat( KTestFailed );
        IncrementTestsFailed();
	    }
    }

// End of File  
