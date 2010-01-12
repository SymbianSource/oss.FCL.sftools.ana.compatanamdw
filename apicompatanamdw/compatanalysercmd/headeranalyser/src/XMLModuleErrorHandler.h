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


#ifndef XML_MODULE_ERROR_HANDLER
#define XML_MODULE_ERROR_HANDLER

#include "CmdGlobals.h"
#ifdef __WIN__
#pragma warning(disable:4786)
#endif
#include <xercesc/dom/DOMErrorHandler.hpp>

XERCES_CPP_NAMESPACE_USE

/**
* DOM error handler
*/
class XMLModuleErrorHandler : public DOMErrorHandler
{
public:
    XMLModuleErrorHandler();
    ~XMLModuleErrorHandler();

public:
    /**
    * True if there was errors
    * @return true if there was errors parameter value to check
    */ 
    bool sawErrors() const;
    bool handleError(const DOMError& domError);
    void resetErrors();

private :
    XMLModuleErrorHandler(const XMLModuleErrorHandler&);
    void operator=(const XMLModuleErrorHandler&);

private:
    bool    iSawErrors;
};


#endif
