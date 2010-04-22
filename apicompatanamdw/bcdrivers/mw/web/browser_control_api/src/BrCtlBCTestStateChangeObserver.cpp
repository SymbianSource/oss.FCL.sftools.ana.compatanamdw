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
* Description:  Handle state changed events
*
*/


// INCLUDE FILES
#include "BrCtlBCTestContainer.h"
#include "BrCtlBCTestStateChangeObserver.h"

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CBrCtlBCTestStateChangeObserver::StateChanged
// ---------------------------------------------------------
//
void 
CBrCtlBCTestStateChangeObserver::StateChanged(TBrCtlDefs::TBrCtlState /* aState */, 
                                                 TInt /* aValue */)
    {
    // Here we are creating a string to be displayed on the screen, but you would
    // implement this method to have code that would be executed when the observer
    // receives state changed events.
    TBuf16<256> tgt; 
    TPoint point(0, 120);

//    _LIT(KHandleBrowserStateChange, "State Change event = %d, value = %d");
     
//    tgt.AppendFormat(KHandleBrowserStateChange, aState, aValue);

//    iContainer->SetPoint(point);
//    iContainer->SetText(tgt);

    iContainer->DrawNow();
    }

// ---------------------------------------------------------
// CBrCtlBCTestStateChangeObserver::ConstructL
// ---------------------------------------------------------
//
void 
CBrCtlBCTestStateChangeObserver::ConstructL(CBrCtlBCTestContainer* aContainer)
    {
    iContainer = aContainer;
    }

// ---------------------------------------------------------
// CBrCtlBCTestStateChangeObserver::~CBrCtlBCTestStateChangeObserver
// ---------------------------------------------------------
//
CBrCtlBCTestStateChangeObserver::~CBrCtlBCTestStateChangeObserver()
    {
    }


// ---------------------------------------------------------
// CBrCtlBCTestStateChangeObserver::NewL
// ---------------------------------------------------------
//
CBrCtlBCTestStateChangeObserver* 
CBrCtlBCTestStateChangeObserver::NewL(CBrCtlBCTestContainer* aContainer)
{
  CBrCtlBCTestStateChangeObserver* self = new(ELeave)CBrCtlBCTestStateChangeObserver;
  CleanupStack::PushL(self);
  self->ConstructL(aContainer);
  CleanupStack::Pop();
  return self;
}

// End of File  
  
