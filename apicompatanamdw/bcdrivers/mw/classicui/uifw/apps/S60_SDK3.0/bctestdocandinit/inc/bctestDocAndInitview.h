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
* Description:  Test BC for DocAndInit control API.
*
*/


#ifndef BCTEST_DOCANDINIT_VIEW_H
#define BCTEST_DOCANDINIT_VIEW_H

#include <aknview.h>

const TUid KBCTestDocAndInitViewId = { 1 };

class CBCTestDocAndInitContainer;
class CBCTestUtil;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestDocAndInitView : public CAknView
    {
public: // Constructors and destructor

    /**
     * Symbian static 2nd constructor
     */
    static CBCTestDocAndInitView* NewL();
    
    /**
     * dtor
     */
    virtual ~CBCTestDocAndInitView();

public: // from CAknView
    
    /**
     * Return view Id.
     */
    TUid Id() const;
    
    /**
    * From CAknView, HandleCommandL.
    * @param aCommand Command to be handled.
    */
    void HandleCommandL( TInt aCommand );
    
protected: // from CAknView
    
    /**
     * When view is activated, do something
     */
    void DoActivateL( const TVwsViewId&, TUid, const TDesC8& );
    
    /**
     * When view is deactivated, do something
     */
    void DoDeactivate();

private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestDocAndInitView();

    /**
     * symbian 2nd ctor
     */
    void ConstructL();

private: // data

    /**
     * pointor to the BC Test framework utility.
     * own
     */
    CBCTestUtil*  iTestUtil;

    /**
     * pointor to the container.
     * own
     */
    CBCTestDocAndInitContainer*  iContainer;

    };

#endif // BCTEST_DOCANDINIT_VIEW_H

// End of File
