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
#include <iostream>
#include <string>

#if !defined XMLPROCESSOR
	#define  XMLPROCESSOR

class XMLNode;

// T = ParserType    : XMLSAXParser, XMLDOMParser etc.
template<typename T>
class XMLProcessor
{
public:
	XMLProcessor() {
        }
	XMLProcessor(const std::string& x) { 
		xmlFile = x; 
	}
	virtual ~XMLProcessor() {}

	T& getParseEngine() { return parseEngine; }

	XMLNode& getRootElement() { return parseEngine.getRootElement(); }
	
	std::string& name() { return xmlFile; }
	
	bool parse() { return parseEngine.parse(xmlFile); }

	bool parse(const std::string& f) { return parseEngine.parse(f); }
	
	void doValidation(bool v) { parseEngine.doValidation(v); }
	void doSchema(bool s) { parseEngine.doSchema(s); }
	void fullSchemaChecking(bool s) { parseEngine.fullSchemaChecking(s); }
	void namespaces(bool n) { parseEngine.namespaces(n); }

private:
	T	parseEngine;
	std::string	xmlFile;
};

#endif // XMLPROCESSOR
