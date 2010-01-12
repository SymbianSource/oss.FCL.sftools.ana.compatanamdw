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
* Description:  
*
*/


#include "XMLModuleErrorHandler.h"

// ----------------------------------------------------------------------------
// MLModuleErrorHandler::XMLModuleErrorHandler
// ----------------------------------------------------------------------------
//
XMLModuleErrorHandler::XMLModuleErrorHandler()
 : iSawErrors(false)
{
}

// ----------------------------------------------------------------------------
// MLModuleErrorHandler::~XMLModuleErrorHandler
// ----------------------------------------------------------------------------
//
XMLModuleErrorHandler::~XMLModuleErrorHandler() {
}

// ----------------------------------------------------------------------------
// MLModuleErrorHandler::handleError
// ----------------------------------------------------------------------------
//
bool XMLModuleErrorHandler::handleError(const DOMError& aError) {
    bool ret = true;
    return ret;
}

// ----------------------------------------------------------------------------
// MLModuleErrorHandler::sawErrors
// ----------------------------------------------------------------------------
//
bool XMLModuleErrorHandler::sawErrors() const {
    return iSawErrors;
}

// ----------------------------------------------------------------------------
// MLModuleErrorHandler::resetErrors
// ----------------------------------------------------------------------------
//
void XMLModuleErrorHandler::resetErrors() {
    iSawErrors = false;
}
