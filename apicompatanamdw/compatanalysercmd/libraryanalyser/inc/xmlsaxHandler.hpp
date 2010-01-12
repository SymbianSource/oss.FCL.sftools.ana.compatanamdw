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
#include "xmlstringtostlstring.hpp"

#if !defined XMLSAXHANDLER
	#define  XMLSAXHANDLER

// Forward Reference
//class AttributeList;
class XMLNode;

// T - Domain Map
template<typename T>
class XMLSAXHandler : public HandlerBase
{
	typedef T*	root;
public:
	XMLSAXHandler();
	virtual ~XMLSAXHandler();

	T& getDomainMap() { return dataMap; }

	XMLNode& getRootElement() { return dataMap.root(); }
	
	// Handlers for the SAX DocumentHandler interface
	virtual void startElement(const XMLCh* const name, AttributeList& attributes);
	virtual void characters(const XMLCh* const chars, const unsigned int length);
	virtual void ignorableWhitespace(const XMLCh* const chars, const unsigned int length);
	virtual void endElement(const XMLCh* const name);
//	void ignoreElement(const XMLCh* const aName);

private:
	// Private data members
	T		dataMap;
//	T name ;
};

template<typename T>
XMLSAXHandler<T>::XMLSAXHandler()
{
}

template<typename T>
XMLSAXHandler<T>::~XMLSAXHandler()
{
}

//  SAXParser: Implementation of the SAX DocumentHandler interface
template<typename T>
void XMLSAXHandler<T>::startElement(const XMLCh* const name, AttributeList&  attributes)
{
	XMLStringToSTLString str(name);
	const XMLCh* value = NULL;

		int length = attributes.getLength();
		for(int i=0;i<length;i++)
		{
			value = attributes.getValue(i);
		}
		if (value)
		{
                        XMLStringToSTLString val(value);
			dataMap.create(str.data(),val.data());
		}
		else
			dataMap.create(str.data());

//	}
}

template<typename T>
void XMLSAXHandler<T>::endElement(const XMLCh* const name)
{
	XMLStringToSTLString str(name);
	dataMap.add(str.data());
}

template<typename T>
void XMLSAXHandler<T>::characters(const XMLCh* const chars, const unsigned length)
{
        XMLStringToSTLString str(chars);
	dataMap.updateAttribute(str.data());
}

template<typename T>
void XMLSAXHandler<T>::ignorableWhitespace( const XMLCh* const chars, const unsigned int length)
{
}
/*
template<typename T>
void XMLSAXHandler<T>::ignoreElement(const XMLCh* const aName)
{
	name = aName;
}*/

#endif // XMLSAXHANDLER
