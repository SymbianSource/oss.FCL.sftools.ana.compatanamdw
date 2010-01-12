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
#include <string>

#if !defined XMLPARSERINTERFACE
	#define  XMLPARSERINTERFACE

class XMLParserInterface
{
public:
    virtual bool parse() = 0;
	virtual bool parse(const std::string&) = 0;
	
	virtual void doValidation(bool v = true) = 0;
	virtual void doSchema(bool s = true) = 0;
	virtual void fullSchemaChecking(bool s = true) = 0;
	virtual void namespaces(bool n = true) = 0;
};

#endif // XMLPARSERINTERFACE
