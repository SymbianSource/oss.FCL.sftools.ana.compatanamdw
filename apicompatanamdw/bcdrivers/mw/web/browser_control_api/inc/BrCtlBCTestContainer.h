/*
* Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies). 
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



#ifndef BRCTLBCTESTCONTAINER_H
#define BRCTLBCTESTCONTAINER_H

// INCLUDES
#include <coecntrl.h>
#include <DownloadMgrClient.h>
#include <CDownloadMgrUiLibRegistry.h>
#include <CDownloadMgrUiUserInteractions.h>
#include <CDownloadMgrUiDownloadsList.h>
#include <CDownloadMgrUiDownloadMenu.h>
#include <fbs.h>
#include "BrCtlInterface.h"
#include "BrCtlBCTestAppUi.h"
#include "BrCtlBCTestObserver.h"
#include "BrCtlBCTestStateChangeObserver.h"
   
// CONSTATNS
const TInt KThisAppUid = 0xA0000181;

// FORWARD DECLARATIONS
//class CBrCtlInterface;

// CLASS DECLARATION

/**
*  CBrCtlBCTestContainer  container control class.
*  
*/
class CBrCtlBCTestContainer : public CCoeControl,
                                     MCoeControlObserver,
                                     MBrCtlDataLoadSupplier,
                                     MHttpDownloadMgrObserver
    {
    public: // Constructors and destructor
        
        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL(const TRect& aRect);

        /**
        * Destructor.
        */
        ~CBrCtlBCTestContainer();

    public: // New functions
    
        void SetAppUi(CBrCtlBCTestAppUi* aAppUi);
        
        void HandleCommandL(TInt aCommand);

        void DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane);

        TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

    public: // Functions from base classes

    private:    // from MHttpDownloadMgrObserver

        void HandleDMgrEventL( RHttpDownload& aDownload, THttpDownloadEvent aEvent );

    private: // Functions from base classes

       /**
        * From CoeControl,SizeChanged.
        */
        void SizeChanged();

       /**
        * From CoeControl,CountComponentControls.
        */
        TInt CountComponentControls() const;

       /**
        * From CCoeControl,ComponentControl.
        */
        CCoeControl* ComponentControl(TInt aIndex) const;

       /**
        * From CCoeControl,Draw.
        */
        void Draw(const TRect& aRect) const;

        /**
        * Handle key events.
        */
        TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

       /**
        * From MBrCtlDataLoadSupplier, Cancel an on-going load
        */
        void CancelLoad();

	    /**
        * Read the file.
        */
        HBufC8* ReadFileLC(const TDesC& aFileName);

        void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
        void RunAllTestsL();
        void RunBrCtlTestsL();
        void RunPluginTestsL();
        void RunDldMgrTestsL();
        
    private: // Functions to test CBrCtlInterface
    
        void CreateBrowserControlLTest();
        void HandleCommandLTest();
        void HandleDownloadCommandLTest();
        void ContentSizeTest();
        void SetBrowserSettingLTest();
        void BrowserSettingLTest();
        void LoadDataLTest();
        void InitLoadDataLTest();
        void LoadUrlLTest();
        void LoadFileLWithTDesCTest();
        void LoadFileLWithFileHandleTest();
        void WMLOptionsMenuItemsLTest();
        void AddOptionMenuItemsLTest();
        void ClearCacheTest();
        void IsUrlInCacheTest();
        void ClearItemInCacheTest();
        void PageInfoLCTest();
        void NavigationAvailableTest();
        void CertInfoTest();
        void AddLoadEventObserverLTest();
        void RemoveLoadEventObserverTest();
        void ImageCountLTest();
        void FocusedElementTypeTest();
        void AddStateChangeObserverLTest();
        void RemoveStateChangeObserverTest();
        void VersionInfoLCTest();
        void SetSelfDownloadContentTypesLTest();
        void SetParamLTest();
        void LoadSavedPageLTest();
        void MinimumSizeTest();
        void OfferKeyEventLTest();
        void SetFocusTest();
        void FindKeywordTest();
        void FindKeywordAgainTest();
        void ZoomLevelsTest();
        void TestTakeSnapShotL();

    private: // Functions to test CDownloadMgrUiLibRegistry
    
        void CDownloadMgrUiLibRegistryDestructorTest();
        void NewLTest();
        void RegisterDownloadsListLTest();
        void RegisterUserInteractionsLTest();
    
    private: // Functions to test CDownloadMgrUiUserInteractions
    
        void HandleDownloadLTest();
        void OkToExitLTest();
        void PrepareToExitWithAppUiPointerTest();
        void PrepareToExitWithAppUidTest();
        void UserInteractGetBoolAttributeLTest();
        void UserInteractGetIntAttributeLTest();
        void UserInteractGetStringAttributeLTDesC8Test();
        void UserInteractGetStringAttributeLTDesC16Test();
        void UserInteractSetBoolAttributeLTest();
        void UserInteractSetIntAttributeLTest();
        void UserInteractSetStringAttributeLTDesC8Test();
        void UserInteractSetStringAttributeLTDesC16Test();
    
    private: // Functions to test CDownloadMgrUiDownloadsList
    
        void CancelDisplayingDownloadsListTest();
        void CountTest();
        void DisplayDownloadsListLTest();
        void DownloadMenuTest();
        void IsVisibleTest();
        void DownloadListGetBoolAttributeLTest();
        void DownloadListGetIntAttributeLTest();
        void DownloadListGetStringAttributeLTDesC8Test();
        void DownloadListGetStringAttributeLTDesC16Test();
        void DownloadListSetBoolAttributeLTest();
        void DownloadListSetIntAttributeLTest();
        void DownloadListSetStringAttributeLTDesC8Test();
        void DownloadListSetStringAttributeLTDesC16Test();

    private: // Function to test CDownloadMgrUiDownloadMenu
    
        void AddMenuLTest();
        
    private: // utility functions
    
        void IncrementTestsPassed();
        void IncrementTestsFailed();
        void TestsDoneDialog();
        
    private: //data
        
        CBrCtlInterface* iBrCtlInterface;
        TUint iBrCtlCapabilities;
        TInt iCommandBase;
        CBrCtlBCTestObserver* iBrCtlBCTestObserver;
        CBrCtlBCTestStateChangeObserver* iBrCtlBCTestStateChangeObserver;
        RHttpDownloadMgr iDownloadMgr;
        TBool iCancelInitDataLoad;
        RFileLogger iFileLogger;
        TBool iCanLog;
        CBrCtlBCTestAppUi* iAppUi;
        CEikMenuPane* iMenuPane;
        TUint iTestsPassed;
        TUint iTestsFailed;
        TUint iTotalTests;

        HBufC* iSavedPage;
    };

#endif // BRCTLBCTESTCONTAINER_H

// End of File
