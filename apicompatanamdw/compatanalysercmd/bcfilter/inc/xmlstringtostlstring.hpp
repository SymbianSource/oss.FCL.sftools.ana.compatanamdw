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
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/sax/AttributeList.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <string>

#if !defined XMLSTRTOSTLSTR
		#define  XMLSTRTOSTLSTR

class XMLStringToSTLString
{
public:
	XMLStringToSTLString(const XMLCh* const toTranscode)
	{
		str = XMLString::transcode(toTranscode);
	}

	~XMLStringToSTLString() {}

	const std::string& data() const {
		return str;
	}

private:
	std::string	str;
};

inline std::ostream& operator<<(std::ostream& target, const XMLStringToSTLString& toDump)
{
    target << toDump.data();
    return target;
}
#endif // XMLSTRTOSTLSTR
