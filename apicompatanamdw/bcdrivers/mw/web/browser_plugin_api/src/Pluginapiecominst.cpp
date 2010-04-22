/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Example for developing a plug-in
*
*/



// INCLUDE FILES

#include <string.h>
#include <e32std.h>
#include <coecntrl.h>
#include <coeinput.h>
#include "pluginapiinst.h"
#include "pluginapiecommain.h"
#include <allbitmaps.mbg>

// CONSTANTS

const int KTotalNumTests = 28;
_LIT(KSourceUrl, "sourceurl");
_LIT(KEmptyString, "");


// ============================================================================
// CPluginAPIInst Class
// ============================================================================


// ----------------------------------------------------------------------------
// Two phase construction.
//
// @param aNpp - plug-in's opaque instance handle.
// @return     - plug-in object.
// ----------------------------------------------------------------------------
CPluginAPIInst* CPluginAPIInst :: NewL( NPP aNpp )
    {
    CPluginAPIInst* self = new ( ELeave ) CPluginAPIInst( aNpp );
    CleanupStack :: PushL( self );
    self->Construct();
    CleanupStack :: Pop();
    return self;
    }


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
CPluginAPIInst :: CPluginAPIInst( NPP aNpp ) : CCoeControl(), iNpp( aNpp )
    {
    iWriteReady     = 100;
    iSourceUrl      = NULL;
    iFirstTime      = ETrue;
    iFlipBitmap     = EFalse;
    iNumDownload    = 0;
    }


// ----------------------------------------------------------------------------
// second phase constructor
// ----------------------------------------------------------------------------
void CPluginAPIInst :: Construct( void )
    {
    _LIT(KDir, "PluginAPI");
    _LIT(KFile, "PluginAPI.log");
    _LIT(KConstructTest, "1. CPluginAPIInst :: Construct called, Test Passed");

    TInt err = 0;

    err = iFileLogger.Connect();

    if (err == KErrNone)
        {
        iFileLogger.CreateLog(KDir(), KFile(), EFileLoggingModeOverwrite);
        iCanLog = ETrue;
        iWriteReadyTestRun = EFalse;
        iWriteTestRun = EFalse;
        iSetWindowTestRun = EFalse;
        iFocusChangedTestRun = EFalse;
        iSizeChangedTestRun = EFalse;
        iStreamAsFileTestRun = EFalse;
        iNewStreamTestRun = EFalse;
        iDestroyStreamTestRun = EFalse;

        iFileLogger.WriteFormat(KConstructTest);
        IncrementTestsPassed();
        }
    else
	    {
	    iCanLog = EFalse;
	    }
    return;
    }


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
CPluginAPIInst :: ~CPluginAPIInst( void )
    {
    _LIT(KDestructorTest, "28. CPluginAPIInst :: ~CPluginAPIInst called, Test Passed");
    _LIT(KTestResults, "CPluginAPIInst test run finished %d passed %d failed %d tests run out of %d total tests");

    if ( iFileName )
        {
	    delete iFileName;
	    iFileName = NULL;
        }

    CPluginAPIEcomMain* npm = ( CPluginAPIEcomMain* ) Dll :: Tls();
    
    if (iCanLog)
        {
        iFileLogger.WriteFormat(KDestructorTest);
        IncrementTestsPassed();
        iFileLogger.WriteFormat(KTestResults, iTestsPassed, iTestsFailed, iTestsPassed + iTestsFailed, KTotalNumTests);
        }

    iFileLogger.CloseLog();
    iFileLogger.Close();
    
    delete iSourceUrl;
    }


// ----------------------------------------------------------------------------
// This function creates a new instance of the plug-in.
//
// @param aPluginType - the MIME type.
// @param aInstance   - the plug-in instance.
// @param aMode       - the mode
// @param aArgn       - attribute of the <object> tag; the names
// @param aArgv       - attribute of the <object> tag; the values
// @param aSaved      - this parameter is not supported.
// @return            - NPError status code.
// ----------------------------------------------------------------------------
NPError CPluginAPIInst :: PluginNew( 
                            NPMIMEType /*aPluginType*/, 
                            NPP aInstance, 
                            uint16 /*aMode*/, 
                            CDesC16Array* aArgn, 
                            CDesC16Array* aArgv, 
                            NPSavedData* /*aSaved*/ )
    {
    _LIT(KNewPluginTestPassed, "2. CPluginAPIInst :: NewPlugin Test Passed.");

    if ( aInstance->pdata != this )
        {
        return NPERR_INVALID_INSTANCE_ERROR;
        }

    // Log the plugin type and mode
    if (iCanLog)
        {
	      iFileLogger.WriteFormat(KNewPluginTestPassed);
	      IncrementTestsPassed();
        }

    // Traverse the attribute list to find the Url from which to retrieve data
    for ( TInt i = 0; i < aArgn->Count(); i++ )
        {
        TPtrC16 namePtr( (*aArgn)[i] );
        TPtrC16 valPtr( (*aArgv)[i] );

        if ( ( KSourceUrl().FindF( namePtr ) == 0 ) )
            {
            iSourceUrl = new TUint16[valPtr.Length() + 1];
            if ( iSourceUrl == NULL )
                {
                return NPERR_OUT_OF_MEMORY_ERROR;
                }
            TPtr16 ptr( iSourceUrl, 0, valPtr.Length() + 1 );
            ptr.Copy( valPtr );
            ptr.ZeroTerminate();
            break;
            }
        }
    return HandleGet();
    }


// ----------------------------------------------------------------------------
// This function deletes a plug-in instance.
// 
// @param aSave - this parameter is not supported.
// @return      - NPError status code.
// ----------------------------------------------------------------------------
NPError CPluginAPIInst :: PluginDestroy( NPSavedData** /*aSave*/ )
    {
    _LIT(KDestroyed, "27. CPluginAPIInst :: PluginDestroyed called. Test Passed");

    if (iCanLog)
        {
        iFileLogger.WriteFormat(KDestroyed);
        IncrementTestsPassed();
        }
    delete this;
    return NPERR_NO_ERROR;
    }


// ----------------------------------------------------------------------------
// This function sets the parent and the coordinates for the plug-in. 
// The first time PluginSetWindowL() is called, it is 
// important to construct the corresponding plug-in control. The other times 
// this call is made, it is expected that the function simply updates the 
// bounds of the control.
//
// @param aWindow - a plug-in window structure that contains window coordinates
//                  and platform specific window information.
// @return        - an error code, on success returns NPERR_NO_ERROR.
// ----------------------------------------------------------------------------
NPError CPluginAPIInst :: PluginSetWindowL( NPWindow* aWindow )
    {
    _LIT(KSetWindowTest, "20. CPluginAPIInst :: PluginSetWindowL called, Test Passed");

    MPluginAdapterPTR pPluginAdapter( NULL );
    pPluginAdapter = static_cast<MPluginAdapter*>( aWindow->window );
    CCoeControl* pParentControl = pPluginAdapter->GetParentControl();

	if ( !pParentControl )
		return NPERR_NO_ERROR;

    if ( iFirstTime )
        {
	    CreateWindowL( pParentControl );
        pPluginAdapter->SetPluginNotifier( this );
        pPluginAdapter->PluginConstructedL( this );
        }
  
    TPoint point( aWindow->x, aWindow->y );
    TSize size( aWindow->width, aWindow->height );
    SetExtent( point, size );
  
    if ( iFirstTime )
        {
        ActivateL();
        iFirstTime = EFalse;
        }

    if (iCanLog)
        {
        if (!iSetWindowTestRun)
	        {
	        iFileLogger.WriteFormat(KSetWindowTest);
	        IncrementTestsPassed();
	        iSetWindowTestRun = ETrue;
	        }
        }
        
    return NPERR_NO_ERROR;
    }


// ----------------------------------------------------------------------------
// This function has an empty implementation here, but the actual purpose of 
// the function is to set values for the plugin variables. 
//
// @param aVariable - the variable whose value is to be set.
// @param aValue    - pointer to the 32-bit parameter that contains the value.
// @return          - NPError status code.
// ----------------------------------------------------------------------------
NPError CPluginAPIInst :: PluginSetValue( 
                            NPNVariable /*aVariable*/, 
                            void* /*aValue*/ )
    {
    return NPERR_NO_ERROR;
    }


// ----------------------------------------------------------------------------
// This function notifies a plug-in instance of a new data stream.
// 
// @param aMimeType - the MIME type of the stream.
// @param aStream   - the new stream object.
// @param aSeekable - flag that indicates whether or not stream is searchable.
// @param aStype    - the type of the stream. The plug-in sets the stream type.
//                    Currently supported stream types are:	
//                        NP_NORMAL
//                        NP_ASFILE
 //                       NP_ASFILEONLY
// @return          - NPError status code.
// ----------------------------------------------------------------------------
NPError CPluginAPIInst :: PluginNewStream( 
                            NPMIMEType /*aMimeType*/, 
                            NPStream* aStream, 
                            NPBool /*aSeekable*/, 
                            uint16* aStype )
    {
    _LIT(KNewStreamTest, "21. CPluginAPIInst :: PluginNewStream called, Test Passed");

    *aStype         = NP_ASFILE;
    iStream         = aStream;
    iStream->pdata  = this;

    if (iCanLog)
        if (!iNewStreamTestRun)
        {
	        {
	        iFileLogger.WriteFormat(KNewStreamTest);
	        IncrementTestsPassed();
	        iNewStreamTestRun = ETrue;
	        }
        }

    return NPERR_NO_ERROR;
    }


// ----------------------------------------------------------------------------
// This function destroys the stream that was previously created to stream data
// to the plug-in.
//
// @param aStream - the stream to be destroyed.
// @param aReason - the reason for destroying the stream. Possible values are:
//                      NPRES_DONE - normal completion and all data was sent to
//                      the instance. 
//                      NPRES_USER_BREAK - the user canceled the stream
//                      NPRES_NETWORK_ERR - stream failed because of problems 
//                      with the network, disk I/O error, lack of memory, or 
//                      some other problem.        
// @return        - NPError status code.
// ----------------------------------------------------------------------------
NPError CPluginAPIInst :: PluginDestroyStream( 
                                NPStream* /*aStream*/, 
                                NPReason /*aReason*/ )
    {
    _LIT(KDestroyStreamTest, "25. CPluginAPIInst :: PluginDestroyStream called, Test Passed");

    if (iCanLog)
        {
        if (!iDestroyStreamTestRun)
	        {
	        iFileLogger.WriteFormat(KDestroyStreamTest);
	        IncrementTestsPassed();
	        iDestroyStreamTestRun = ETrue;
	        }
        }
        
    return NPERR_NO_ERROR;
    }


// ----------------------------------------------------------------------------
// This function passes a file name to the plug-in in which the stream data 
// is stored. 
//
// @param aStream   - the stream
// @param aFileName - the file name
// ----------------------------------------------------------------------------
void CPluginAPIInst :: PluginStreamAsFile( 
                            NPStream* aStream, 
                            const TDesC16& aFileName )
    {
    _LIT(KStreamAsFileTest, "24. CPluginAPIInst :: PluginStreamAsFile called, Test Passed");

    if (iCanLog)
        {
        if (!iStreamAsFileTestRun)
	        {
            iFileLogger.WriteFormat(KStreamAsFileTest);
            IncrementTestsPassed();
            iStreamAsFileTestRun = ETrue;
	        }
        }
        
    if ( ( aStream->pdata != this ) || ( aStream != iStream ) 
                                    || ( iNumDownload > 0 ) )
        {
        return;
        }    
    iFileName = aFileName.Alloc();
    iNumDownload ++;
    }


// ----------------------------------------------------------------------------
// This function writes a chunk of data to the plug-in.
//
// @param aStream - the stream
// @param aOffset - the offset in the stream.
// @param aLength - the size of the new data.
// @param aBuffer - the data.
// @return        - the number of bytes consumed by the plug-in instance.
// ----------------------------------------------------------------------------
int32 CPluginAPIInst :: PluginWrite( 
                        NPStream* aStream, 
                        int32 /*aOffset*/, 
                        int32 aLength, 
                        void* /*aBuffer*/ )
    {
    _LIT(KWriteTest, "23. CPluginAPIInst :: PluginWrite called, Test Passed");

    if (iCanLog)
        {
            if (!iWriteTestRun)
            {
            iFileLogger.WriteFormat(KWriteTest);
            IncrementTestsPassed();
            iWriteTestRun = ETrue;
            }
        }
        
    if ( aStream->pdata != this || aStream != iStream )
        {
        return 0;
        }

    return aLength;
    }


// ----------------------------------------------------------------------------
// The browser calls the NPP_Write function with the amount of data returned 
// from the NPP_WriteReady function.
//
// @param aStream - the stream
// @return        - maximum data size that the plug-in can handle.
// ----------------------------------------------------------------------------
int32 CPluginAPIInst :: PluginWriteReady( NPStream* /*aStream*/ )
    {
    _LIT(KWriteReadyTest, "22. CPluginAPIInst :: PluginWriteReady called, Test Passed");

    if (iCanLog)
        {
            if (!iWriteReadyTestRun)
            {
            iFileLogger.WriteFormat(KWriteReadyTest);
            IncrementTestsPassed();
            iWriteReadyTestRun = ETrue;
            }
        }
        
    return iWriteReady;
    }


// ----------------------------------------------------------------------------
// The browser calls the NPP_URLNotify function to notify the plug-in of the 
// completion of a URL request made by the NPN_GetURLNotify function or the 
// NPN_PostURLNotify function.
//
// @param aUrl        - url of the NPN_GetURLNotify function or of the 
//                      NPN_PostURLNotify function request.
// @param aReason     - reason code for completion of the request.
// @param aNotifyData - contains the private plug-in data passed to the 
//                      corresponding call to the NPN_GetURLNotify function.
// ----------------------------------------------------------------------------
void CPluginAPIInst :: PluginURLNotify( 
                        const TDesC16& /*aUrl*/, 
                        NPReason       /*aReason*/, 
                        void*          /*aNotifyData*/ )
    {
    return;
    }


// ----------------------------------------------------------------------------
// This function draws the control. When iFlipBitmap is true it renders one 
// bitmap, and when iFlipBitmap is false it renders another one.
//
// @param aRect - The region of the control to be redrawn. Co-ordinates are 
//                relative to the control's origin (top left corner).
// ----------------------------------------------------------------------------
void CPluginAPIInst :: Draw( const TRect& aRect ) const
    {   
    TInt ret( KErrNone );
    CFbsBitmap* bitmap = NULL;
  
    bitmap = new CFbsBitmap();
    if ( !bitmap )
        {
        return;
        }

    if ( iFileName )
		{
		if( iFlipBitmap )
			{
			ret = bitmap->Load( iFileName->Des(), EMbmAllbitmapsRedflower, ETrue );
			}
		else 
			{
			ret = bitmap->Load( iFileName->Des(), EMbmAllbitmapsBlueflower, ETrue );
			}
		}
    if ( ret != KErrNone || !iFileName )
        {
        delete ( bitmap );
        bitmap = NULL;
        return;
        }

    SystemGc().Clear();
    SystemGc().DrawBitmap( aRect, bitmap );
    delete ( bitmap );
    bitmap = NULL;
    }
// ----------------------------------------------------------------------------
// This function implements the NotifyL() function of the MPluginNotifier 
// interface. It notifies the plug-in of an event. 
//
// @param aCallType - the event type that is passed to the plug-in. 
//                    Possible values are :
//                    EEditCut, 
//                    EEditCopy, 
//                    EEditPaste, 
//                    EEditDelete, 
//                    EApplicationFocusChanged, 
//                    ESystemNotification
// @param aParam    - the parameter associated with the event.
// @return          - not used.
// ----------------------------------------------------------------------------
TInt CPluginAPIInst :: NotifyL( TNotificationType aCallType, TAny* /*aParam*/ )
    {
    _LIT(KNotifyTest, "26. CPluginAPIInst :: NotifyL called, Test Passed");

    if (iCanLog)
        {
        if (!iNotifyTestRun)
            {
            iFileLogger.WriteFormat(KNotifyTest);
            IncrementTestsPassed();
            iNotifyTestRun = ETrue;
            }
        }
        
    switch ( aCallType )
        {
        case EApplicationFocusChanged:
            {
			if ( iFlipBitmap )
                {
		        iFlipBitmap = EFalse;
                }
	        else 
                {
		        iFlipBitmap = ETrue;
                }
            DrawNow();
            break;
            }
        default:
            break;
        }
    return 0;
    }


// ----------------------------------------------------------------------------
// Returns the supported input capabilities which correspond to the behaviour 
// of the OfferKeyEventL() function of the control; 
//
// @return - TCoeInputCapabilities::EAllText which supports all types of text.
// ----------------------------------------------------------------------------

TCoeInputCapabilities CPluginAPIInst :: InputCapabilities ( void )
    {
    _LIT(KInputCapabilitiesTest, "13. CPluginAPIInst :: InputCapabilities called, Test Passed");

    if (iCanLog)
        {
        iFileLogger.WriteFormat(KInputCapabilitiesTest);
        IncrementTestsPassed();
        }
  
    return TCoeInputCapabilities( TCoeInputCapabilities::EAllText );
    }


// ----------------------------------------------------------------------------
// This function handles key events. when 'Enter' key or 'OK' key is pressed, 
// the bitmap rendered is flipped from redflower to blueflower and viceversa.
//
// @param aKeyEvent - the key event.
// @param aType     - type of key event:EEventKey, EEventKeyUp or EEventKeyDown
// @return          - the function returns EKeyWasNotConsumed if it does not do 
//                    anything in response to a key event. If it is able to 
//                    process the event it returns EKeyWasConsumed.
// ----------------------------------------------------------------------------
TKeyResponse CPluginAPIInst :: OfferKeyEventL( 
                                const TKeyEvent& aKeyEvent, 
                                TEventCode aType )
    {
	if ( aType == EEventKeyUp )
	    {
		switch ( aKeyEvent.iScanCode )
		    {
		    case EStdKeyEnter:
		    case EStdKeyDevice3:
                {
				if ( iFlipBitmap )
                    {
		            iFlipBitmap = EFalse;
                    }
	            else 
                    {
		            iFlipBitmap = ETrue;
                    }
			    DrawNow();
			    return EKeyWasConsumed;
                }
		    default:
			    return EKeyWasNotConsumed;
		    }
	    }
	return EKeyWasNotConsumed;
    }


// ----------------------------------------------------------------------------
// This function inherited from MCoeControlObserver handles an event from an 
// observed control.
//
// @param aControl   - pointer to the control from which the event originated.
// @param aEventType - the event type.
// ----------------------------------------------------------------------------
void CPluginAPIInst :: HandleControlEventL( 
                            CCoeControl* aControl,
                            TCoeEvent aEventType )
    {
    if ( aControl != (( MPluginAdapter* ) ( iNpp->ndata ))->GetParentControl() )
        {
        return;
        }

    switch ( aEventType )
        {
        case EEventRequestFocus:
	    default:
	        break;
        }
    }


// ----------------------------------------------------------------------------
// This function handles pointer events. On clicking the left mouse button, 
// the bitmap rendered is flipped from redflower to blueflower and viceversa.
//
// @param aPointerEvent - The pointer event.
// ----------------------------------------------------------------------------
void CPluginAPIInst :: HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    switch ( aPointerEvent.iType )
        {
        case TPointerEvent::EButton1Down:
            {
			if ( iFlipBitmap )
                {
		        iFlipBitmap = EFalse;
                }
	        else 
                {
		        iFlipBitmap = ETrue;
                }
	        DrawNow();
	        break;
            }       
        default:
	        break;
        }
    }


// ----------------------------------------------------------------------------
// This function is called whenever a control gains or loses focus - as a 
// result of a call to SetFocus(). 
//
// @param aDrawNow  - Contains the value that was passed to it by SetFocus().
// ----------------------------------------------------------------------------
void CPluginAPIInst :: FocusChanged( TDrawNow /*aDrawNow*/ )
    {
    DrawNow();
    }


// ----------------------------------------------------------------------------
// This function which responds to size changes to set the size and position of 
// the contents of the control does nothing and has an empty implementation.
// ----------------------------------------------------------------------------
void CPluginAPIInst :: SizeChanged( void )
    {
    _LIT(KSizeChangedTest, "19. CPluginAPIInst :: SizeChanged called, Test Passed");

    if (iCanLog)
        {
        if (!iSizeChangedTestRun)
	        {
            iFileLogger.WriteFormat(KSizeChangedTest);
            IncrementTestsPassed();
            iSizeChangedTestRun = ETrue;
	        }
        }
        
    return;
    }


// ----------------------------------------------------------------------------
// This function calls the NPN_GetURL function to ask the browser to deliver 
// the data to the plug-in instance in a new stream.
//
// @return - if the url is NULL returns NPERR_GENERIC_ERROR, otherwise returns
//           NPError status code from calling the NPN_GetURL function.
// ----------------------------------------------------------------------------
NPError CPluginAPIInst :: HandleGet( void )
    {
    CPluginAPIEcomMain* npm = ( CPluginAPIEcomMain* ) Dll :: Tls();
    TPtrC url;
    NPError testError;

    _LIT(KHandleGetTest, "3. CPluginAPIInst :: HandleGet called, Test Passed");
    _LIT(KNPNGetURLTestPassed, "18. NPNGetURLTest, Test Passed");
    _LIT(KNPNGetURLTestFailed, "18. NPNGetURLTest, Test Failed");
    _LIT(KNPNForceRedrawTestPassed, "4. Call to NPNForceRedraw didn't crash, so test passed");
    _LIT(KNPNInvalidateRectTestPassed, "5. Call to NPNInvalidateRect didn't crash, so test passed");
    _LIT(KNPNInvalidateRegionTestPassed, "6. Call to NPNInvalidateRegion didn't crash, so test passed");
    _LIT(KNPNSetValueTestPassed, "7. NPNSetValueTest, Test Passed");
    _LIT(KNPNSetValueTestFailed, "7. NPNSetValueTest, Test Failed");
    _LIT(KNPNNewStreamTestPassed, "8. NPNNewStreamTest, Test Passed");
    _LIT(KNPNNewStreamTestFailed, "8. NPNNewStreamTest, Test Failed");
    _LIT(KNPNDestroyStreamTestPassed, "9. NPNDestroyStreamTest, Test Passed");
    _LIT(KNPNDestroyStreamTestFailed, "9. NPNDestroyStreamTest, Test Failed");
    _LIT(KNPNRequestReadTestPassed, "10. NPNRequestReadTest, Test Passed");
    _LIT(KNPNRequestReadTestFailed, "10. NPNRequestReadTest, Test Failed");
    _LIT(KNPNWriteTestPassed, "11. NPNWriteTest, Test Passed");
    _LIT(KNPNWriteTestFailed, "11. NPNWriteTest, Test Failed");
    _LIT(KNPNGetURLNotifyTestPassed, "12. NPNGetURLNotifyTest, Test Passed");
    _LIT(KNPNGetURLNotifyTestFailed, "12. NPNGetURLNotifyTest, Test Failed");
    _LIT(KNPNPostURLTestPassed, "13. NPNPostURLTest, Test Passed");
    _LIT(KNPNPostURLTestFailed, "13. NPNPostURLTest, Test Failed");
    _LIT(KNPNPostURLNotifyTestPassed, "14. NPNPostURLNotifyTest, Test Passed");
    _LIT(KNPNPostURLNotifyTestFailed, "14. NPNPostURLNotifyTest, Test Failed");
    _LIT(KNPNMemAllocTestPassed, "15. NPNMemAllocTest, Test Passed");
    _LIT(KNPNMemAllocTestFailed, "15. NPNMemAllocTest, Test Failed");
    _LIT(KNPNMemFlushTestPassed, "16. NPNMemFlushTest, Test Passed");
    _LIT(KNPNMemFlushTestFailed, "16. NPNMemFlushTest, Test Failed");
    _LIT(KNPNMemFreeTestPassed, "17. NPNMemFreeTest, Test Passed");
    _LIT(KNPNMemFreeTestFailed, "17. NPNMemFreeTest, Test Failed");

    if (iCanLog)
        {
        iFileLogger.WriteFormat(KHandleGetTest);
        IncrementTestsPassed();
        }

    npm->Funcs()->forceredraw( iNpp );
    if (iCanLog)
        {
        iFileLogger.WriteFormat(KNPNForceRedrawTestPassed);
        IncrementTestsPassed();
        }

    npm->Funcs()->invalidaterect( iNpp, NULL );
    if (iCanLog)
        {
        iFileLogger.WriteFormat(KNPNInvalidateRectTestPassed);
        IncrementTestsPassed();
        }
    
    npm->Funcs()->invalidateregion( iNpp, NULL );
    if (iCanLog)
        {
        iFileLogger.WriteFormat(KNPNInvalidateRegionTestPassed);
        IncrementTestsPassed();
        }
    
    testError = npm->Funcs()->setvalue( iNpp, NPPVpluginWindowSize, NULL );
    if (iCanLog)
        {
        if (testError == NPERR_NO_ERROR || testError == NPERR_GENERIC_ERROR)
            {
            iFileLogger.WriteFormat(KNPNSetValueTestPassed);
            IncrementTestsPassed();
            }
        else
            {
            iFileLogger.WriteFormat(KNPNSetValueTestFailed);
            IncrementTestsFailed();
            }
        }

    testError = npm->Funcs()->newstream( iNpp, (const TDesC8&)KEmptyString, &KEmptyString, NULL );
    if (iCanLog)
        {
        if (testError == NPERR_GENERIC_ERROR)
            {
            iFileLogger.WriteFormat(KNPNNewStreamTestPassed);
            IncrementTestsPassed();
            }
        else
            {
            iFileLogger.WriteFormat(KNPNNewStreamTestFailed);
            IncrementTestsFailed();
            }
        }
    
    testError = npm->Funcs()->destroystream( iNpp, NULL, NPRES_DONE );
    if (iCanLog)
        {
        if (testError == NPERR_GENERIC_ERROR)
            {
            iFileLogger.WriteFormat(KNPNDestroyStreamTestPassed);
            IncrementTestsPassed();
            }
        else
            {
            iFileLogger.WriteFormat(KNPNDestroyStreamTestFailed);
            IncrementTestsFailed();
            }
        }
    
    testError = npm->Funcs()->requestread( NULL, NULL );
    if (iCanLog)
        {
        if (testError == NPERR_GENERIC_ERROR)
            {
            iFileLogger.WriteFormat(KNPNRequestReadTestPassed);
            IncrementTestsPassed();
            }
        else
            {
            iFileLogger.WriteFormat(KNPNRequestReadTestFailed);
            IncrementTestsFailed();
            }
        }
    
    testError = npm->Funcs()->write( iNpp, NULL, 0, NULL );
    if (iCanLog)
        {
        if (testError == NPERR_GENERIC_ERROR)
            {
            iFileLogger.WriteFormat(KNPNWriteTestPassed);
            IncrementTestsPassed();
            }
        else
            {
            iFileLogger.WriteFormat(KNPNWriteTestFailed);
            IncrementTestsFailed();
            }
        }
  
    testError = npm->Funcs()->geturlnotify( iNpp, (const TDesC16&)KSourceUrl, NULL, NULL );
    if (iCanLog)
        {
        if (testError == NPERR_NO_ERROR || testError == NPERR_GENERIC_ERROR)
            {
            iFileLogger.WriteFormat(KNPNGetURLNotifyTestPassed);
            IncrementTestsPassed();
            }
        else
            {
            iFileLogger.WriteFormat(KNPNGetURLNotifyTestFailed);
            IncrementTestsFailed();
            }
        }

    testError = npm->Funcs()->posturl( iNpp, (const TDesC16&)KSourceUrl, NULL, (const TDesC16&)KSourceUrl, EFalse );
    if (iCanLog)
        {
        if (testError == NPERR_NO_ERROR || testError == NPERR_GENERIC_ERROR)
            {
            iFileLogger.WriteFormat(KNPNPostURLTestPassed);
            IncrementTestsPassed();
            }
        else
            {
            iFileLogger.WriteFormat(KNPNPostURLTestFailed);
            IncrementTestsFailed();
            }
        }

    testError = npm->Funcs()->posturlnotify( iNpp, (const TDesC16&)KSourceUrl, NULL, (const TDesC16&)KSourceUrl, EFalse, NULL );
    if (iCanLog)
        {
        if (testError == NPERR_NO_ERROR || testError == NPERR_GENERIC_ERROR)
            {
            iFileLogger.WriteFormat(KNPNPostURLNotifyTestPassed);
            IncrementTestsPassed();
            }
        else
            {
            iFileLogger.WriteFormat(KNPNPostURLNotifyTestFailed);
            IncrementTestsFailed();
            }
        }

    void *memObject = npm->Funcs()->memalloc( 1024 );
    if (iCanLog)
        {
        if (memObject != NULL)
            {
            iFileLogger.WriteFormat(KNPNMemAllocTestPassed);
            IncrementTestsPassed();
            }
        else
            {
            iFileLogger.WriteFormat(KNPNMemAllocTestFailed);
            IncrementTestsFailed();
            }
        }
  
    testError = npm->Funcs()->memflush( 1024 );
    if (iCanLog)
        {
        if (testError == NPERR_GENERIC_ERROR)
            {
            iFileLogger.WriteFormat(KNPNMemFlushTestPassed);
            IncrementTestsPassed();
            }
        else
            {
            iFileLogger.WriteFormat(KNPNMemFlushTestFailed);
            IncrementTestsFailed();
            }
        }
 
    TRAPD( err, npm->Funcs()->memfree( memObject ) );
    if (iCanLog)
        {
        if (err == KErrNone)
            {
            iFileLogger.WriteFormat(KNPNMemFreeTestPassed);
            IncrementTestsPassed();
            }
        else
            {
            iFileLogger.WriteFormat(KNPNMemFreeTestFailed);
            IncrementTestsFailed();
            }
        }

    if ( iSourceUrl ) // iSourceUrl is non-null
        {
        url.Set( iSourceUrl );
        testError = npm->Funcs()->geturl( iNpp, url, NULL );
        
        if (iCanLog)
            {
            if (testError == NPERR_NO_ERROR || testError == NPERR_GENERIC_ERROR)
                {
                iFileLogger.WriteFormat(KNPNGetURLTestPassed);
                IncrementTestsPassed();
                }
            else
                {
                iFileLogger.WriteFormat(KNPNGetURLTestFailed);
                IncrementTestsFailed();
                }
            }
            
        return testError;
        }
    else
        {
        return NPERR_GENERIC_ERROR;
        }
    }


void CPluginAPIInst :: IncrementTestsPassed ( void )
    {
    iTestsPassed++;
    }

void CPluginAPIInst :: IncrementTestsFailed ( void )
    {
    iTestsFailed++;
    }
