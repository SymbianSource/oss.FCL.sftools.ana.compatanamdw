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


#include "CmdGlobals.h"
#ifdef __WIN__
#pragma warning(disable:4786)
#endif

#include <assert.h>
#include <map>
#include <list>
#include <string>
//#include <sstream>

#include <xercesc/dom/DOM.hpp>

#include "BBCAnalyser.h"
#include "Issues.h"
#include "ReportGenerator.h"
#include "ReportIssue.h"
#include "NodeIndex.h"
#include "XMLStringConst.h"



using namespace std;

XERCES_CPP_NAMESPACE_USE

// ----------------------------------------------------------------------------
// NodeIndex::AddNodeFQNameToMap
// 
// ----------------------------------------------------------------------------
//
const pair<const XMLCh*,bool>& NodeIndex::FindFileByFileId(const XMLCh* fileid)
    {
    return iIdToFileMap[fileid];
    }

// ----------------------------------------------------------------------------
// NodeIndex::AddFileNodeToMap
// 
// ----------------------------------------------------------------------------
//
void NodeIndex::AddFileNodeToMap(const XMLCh* id,pair<const XMLCh*,bool> file)
    {
        this->iIdToFileMap[id] = file;
    }

// ----------------------------------------------------------------------------
// NodeIndex::AddNodeFQNameToMap
// 
// ----------------------------------------------------------------------------
//
void NodeIndex::AddNodeFQNameToMap(DOMNode * node, const pair<const XMLCh*,const XMLCh*>& fqname)
    {	
        this->iFQNameToNodeMap[fqname] = node;
    }


// ----------------------------------------------------------------------------
// NodeIndex::clear
// 
// ----------------------------------------------------------------------------
// 
void NodeIndex::clear()
    {
        iIdToNodeMap.clear();
        iFQNameToNodeMap.clear();
    }
   
// ----------------------------------------------------------------------------
// NodeIndex::AddNodeIdToMap
// Add the node with its id to the map
// 
// ----------------------------------------------------------------------------
//  
void NodeIndex::AddNodeIdToMap(DOMNode * node)
    {
        const XMLCh * attributeId = ::GetAttribute(node,KXMLIdString);
        
        if ( attributeId )
        {
            iIdToNodeMap[attributeId] = node;
        }
        
    }

 
// ----------------------------------------------------------------------------
// NodeIndex::FindNodeById
// Finds the node with id
// 
// ----------------------------------------------------------------------------
//   
DOMNode * NodeIndex::FindNodeById(DOMNode * root, const XMLCh* id)
    {
        map<const XMLCh*, DOMNode*, ltstr>::iterator cur = iIdToNodeMap.find(id);

        if ( cur == iIdToNodeMap.end() )
        {
            //The node was not found so start traveling the tree
            DOMNode * node = FindNodeByIdFromTree(root,id);
            //We have found the node
            if ( node )
            {
                AddNodeIdToMap(node);
            }
            return node;
        } else
        {
            return cur->second;
        }
    }
    
 
// ----------------------------------------------------------------------------
// NodeIndex::FindNodeByFQName
// Finds the node with fully qualified name
// 
// ----------------------------------------------------------------------------
// 
DOMNode * NodeIndex::FindNodeByFQName(DOMNode * root, pair<const XMLCh*,const XMLCh* > FQName)
    {
        fqnamemap::iterator cur = iFQNameToNodeMap.find(FQName);

        if ( cur == iFQNameToNodeMap.end() )
        {
            //The node was not found so return NULL
            return NULL;
        } else
        {
            return cur->second;
        }
    }
 
// ----------------------------------------------------------------------------
// NodeIndex::FindNodeByIdFromTree
// Search from the tree
// 
// ----------------------------------------------------------------------------
//
DOMNode * NodeIndex::FindNodeByIdFromTree(DOMNode * root, const XMLCh* id)
    {
        DOMNodeList * childs = root->getChildNodes();
        
        XMLSize_t childcount = childs->getLength();
        
        for (unsigned int i = 0; i < childcount; ++i)
        {
            DOMNode* child = childs->item(i);
            
            const XMLCh* attributeValue = GetAttribute(child,KXMLIdString);

            if ( attributeValue )
            {
                if ( XMLString::equals(id, attributeValue) )
                {
                    //The node was found
                    return child;
                }
            }
            
        }
        // Not found
        return NULL;
    }
 
// ----------------------------------------------------------------------------
// NodeIndex::DumpTables
// 
// ----------------------------------------------------------------------------
// 
void NodeIndex::DumpTables()
{
/*
	map< const XMLCh *,DOMNode*,ltstr >::iterator it = iIdToNodeMap.begin();
    DEBUG_PRINT("NodeIndex: ")
    DEBUG_PRINT(this)
    DEBUG_PRINT("\n")
    for (; it != iIdToNodeMap.end(); ++it)
    {
        DEBUG_PRINT_XMLCh((*it).first)
        DEBUG_PRINT(" ")
        DEBUG_PRINT((*it).second)
        DEBUG_PRINT("\n")
   }
    fqnamemap::iterator it2 = iFQNameToNodeMap.begin();
#ifndef NO_DBG
    LOG(" ")
    DEBUG_PRINT("NodeIndex: ")
    DEBUG_PRINT(this)
    DEBUG_PRINT("\n")
#endif
    for (; it2 != iFQNameToNodeMap.end(); ++it2)
    {
        DEBUG_PRINT_XMLCh((*it).first.first)
        DEBUG_PRINT(" ")
        DEBUG_PRINT_XMLCh((*it).first.second)
        DEBUG_PRINT("\n")
    }
*/
}

 
// ----------------------------------------------------------------------------
// NodeIndex::AddVirtualFunction
// Adds a virtual function to the table vtable
// 
// ----------------------------------------------------------------------------
// 
void NodeIndex::AddVirtualFunction(const string& vtablename, const string& functionsig, DOMNode * node)
{
	vtableindex_t::iterator it = iVTableIndex.find(vtablename);

	if ( it != iVTableIndex.end() )
	{
		it->second.push_back(pair<string, DOMNode*>(functionsig,node));
	}
	else
	{
		vtable_t tmp_vtable;
		tmp_vtable.push_back(pair<string, DOMNode*>(functionsig,node));		
		iVTableIndex.insert(pair<string,vtable_t >(vtablename,tmp_vtable));
	}
}
 
// ----------------------------------------------------------------------------
// NodeIndex::GetVirtualTable
// Gets the virtual table vtable
// 
// ----------------------------------------------------------------------------
//
const NodeIndex::vtable_t* NodeIndex::GetVirtualTable(const string& vtablename)
{
	vtableindex_t::iterator it = iVTableIndex.find(vtablename);

	if ( it != iVTableIndex.end() )
	{
		return &(it->second);
	}
	return NULL;
}
 
// ----------------------------------------------------------------------------
// NodeIndex::AddEmptyVirtualTable
// Inserts empty vtable if one does not already exists. Returns a pointer
// to the vtable.
// 
// ----------------------------------------------------------------------------
// 
const NodeIndex::vtable_t* NodeIndex::AddEmptyVirtualTable(const string& vtable)
{
	vtable_t tmp_vtable;
	pair<vtableindex_t::iterator,bool> ret = iVTableIndex.insert(pair<string,vtable_t >(vtable,tmp_vtable));

	return &(ret.first->second);
}
// ----------------------------------------------------------------------------
// NodeIndex::InsertDataMember
// Adds a data member to the given table
// 
// ----------------------------------------------------------------------------
//
 void NodeIndex::InsertDataMember(const string& parentName, const DataMember& member, dtableindex_t& dataMap)
{
    dtableindex_t::iterator it = dataMap.find(parentName);
    if( it != dataMap.end() )
    {
        it->second.push_back(member);
    }
    else
    {
        it = dataMap.insert(make_pair(parentName, dtable_t())).first;
        it->second.push_back(member);
    }
}
// ----------------------------------------------------------------------------
// NodeIndex::AddDataMember
// Adds a data member to the member data table.
// 
// ----------------------------------------------------------------------------
// 
void NodeIndex::AddDataMember(const HANodeIterator& parentNode, const string& parentName, const string& memberName, DOMNode* memberNode, int index, TAccess access,int lineNo)
{
	if( IsAnonymousType(parentNode) )
	{
        InsertDataMember(parentName, DataMember(memberName, memberNode, index, access,lineNo), iAnonymousTable);
    }
    else
    {
        InsertDataMember(parentName, DataMember(memberName, memberNode, index, access,lineNo), iDTableIndex);
    }
}
 
// ----------------------------------------------------------------------------
// NodeIndex::GetDataMemberTable
// Gets the data member table
// 
// ----------------------------------------------------------------------------
// 
const NodeIndex::dtable_t* NodeIndex::GetDataMemberTable(const HANodeIterator& node, const string& nodeName)
{	
	dtableindex_t::iterator it;
	if( IsAnonymousType(node) )
	{
		it = iAnonymousTable.find(nodeName);
		if( it != iAnonymousTable.end() )
		{
			return &(it->second);
		}
	}
	else
	{
		it = iDTableIndex.find(nodeName);
		if( it != iDTableIndex.end() )
		{
		return &(it->second);
		}
    }
    return NULL;
}
 
// ----------------------------------------------------------------------------
// NodeIndex::AddEmptyDataMemberTable
// Add empty data table
// 
// ----------------------------------------------------------------------------
// 
const NodeIndex::dtable_t* NodeIndex::AddEmptyDataMemberTable(const HANodeIterator& node, const string& nodeName)
{
	if( IsAnonymousType(node) )
	{
		return &(iAnonymousTable.insert(make_pair(nodeName, dtable_t()))).first->second;
	}
	
    return &(iDTableIndex.insert(make_pair(nodeName, dtable_t()))).first->second;
}

// ----------------------------------------------------------------------------
// ltstr::operator
// Finds the node with id id. Returns NULL if not found
// 
// ----------------------------------------------------------------------------
// 
bool ltstr::operator()(const XMLCh * s1,const XMLCh * s2) const
  {
    return XMLString::compareString(s1, s2) < 0;
  }

 
// ----------------------------------------------------------------------------
// compareFQName::operator
// Finds the node with id id. Returns NULL if not found
// 
// ----------------------------------------------------------------------------
//
bool compareFQName::operator()(
    const pair<const XMLCh *,const XMLCh *>&  p1,
    const pair<const XMLCh *,const XMLCh *>&  p2) const
  {
    if ( 0 == XMLString::compareString(p1.first,p2.first) )
    {
        return XMLString::compareString(p1.second,p2.second) < 0;
    }
    else
    {
        return XMLString::compareString(p1.first,p2.first) < 0;
    }
  }
