/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
#ifndef __LA_PARSER_HPP__
#define __LA_PARSER_HPP__


#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>

#define _X(s) XMLString::transcode(s)
#define _XX(s) XMLString::release(&s)


using namespace std;
XERCES_CPP_NAMESPACE_USE

namespace XmlTools
{
  // initialization
  int initialiseDOM();
  void uninitialiseDOM();  
  // I/O
  XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* readFile( const char* aFilename );
  XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* getTagNode(const XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* aParentNode, const char* aTagName );
  int getTagValue(const XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* aParentNode, const char* aTagName, char* aTagValue, int minLen, int maxLen );
  DOMBuilder* iParser = NULL;
 }

class DOMPrintErrorHandler : public DOMErrorHandler
{
public:

  DOMPrintErrorHandler(){};
  ~DOMPrintErrorHandler(){};

  //The error handler interface
  bool handleError(const DOMError& domError);
  void resetErrors(){};

private :
  // Unimplemented constructors and operators
  DOMPrintErrorHandler(const DOMErrorHandler&);
  void operator=(const DOMErrorHandler&);

};
#endif
