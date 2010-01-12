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
#ifndef XMLDATAMAP
#define XMLDATAMAP

// STL related includes
#include <stack>
#include <list>
//#include <unistd.h>
using namespace std;

template<typename T>
class XMLDomainMap
{
     //   typedef T              DomainObject; //satarupa
	typedef std::stack<T>	DomainObjectStack;
	typedef std::list<T>         DomainObjectList;

public:
	XMLDomainMap() {
	}
	
	XMLDomainMap(const XMLDomainMap<T>& rhs) {
		if(&rhs == this)
			return;

		this->operator=(rhs);
		return;
	}
	
	virtual ~XMLDomainMap() {
	}

	XMLDomainMap<T>& operator=(const XMLDomainMap<T>& rhs) {
		if(&rhs == this)
			return *this;

		objectStack = rhs.objectStack;
		objectList = rhs.objectList;
		return *this;
	}

	// public interface
	void create(const std::string& name) {
		T obj(name);
		objectStack.push(obj);
	}

	void create(const std::string& name,const std::string& value) {
		T obj(name,value);
		objectStack.push(obj);
	}


	// called from the endElement method of SAX Handler
	void add(const std::string& name) {
		T child = objectStack.top();
		child.name(name);
		objectStack.pop();
	
		if(objectStack.size())
		{
			T parent = objectStack.top();
			objectStack.pop();
			parent.addChild(child);
			objectStack.push(parent);
		}
		else
		{
			objectList.push_back(child);
		}
	}

	// called from the characters method of SAX Handler
	void updateAttribute(const std::string& v)
	{
		T obj = objectStack.top();		
		
		if((obj!= "headerfile") &&(obj != "library") && (obj != "version"))
		{
			objectStack.pop();
			if((v.c_str()[0] == '&')||(v.c_str()[0] == '>')||(v.c_str()[0] == '<'))
			{
				string ws = obj.value();
				ws.append(v.data());
				obj.value(ws);

			}
			else
			    obj.value(v);

			objectStack.push(obj);
		}
	}

	size_t size() 
        { 
                return objectList.size(); 
        }

        T& root() 	
        { 
		//DomainObjectList::iterator start = objectList.begin();
               // return *start; 
                 return *(objectList.begin());
               
	}	

private:
	DomainObjectStack	objectStack;
	DomainObjectList	objectList;
};

#endif // XMLDATAMAP
