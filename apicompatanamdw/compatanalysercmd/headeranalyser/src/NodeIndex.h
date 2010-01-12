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


#ifndef __NODE_INDEX_H_
#define __NODE_INDEX_H_

#include "CmdGlobals.h"
#ifdef __WIN__
#pragma warning(disable:4786)
#endif
#include <assert.h>
#include <map>
#include <list>
#include <xercesc/dom/DOM.hpp>

using namespace std;

XERCES_CPP_NAMESPACE_USE

//The access specifiers in class
enum TAccess
{
    EAccessGlobal,
    EAccessPublic,
    EAccessProtected,
    EAccessPrivate,
    EAccessHidden
};

// The compare function for the fully qualified name that takes
// into account the identity of the node
struct compareFQName
{
bool operator()(
    const pair<const XMLCh *,const XMLCh *>&  p1,
    const pair<const XMLCh *,const XMLCh *>&  p2) const;
};

// General compare function for XMLCh
struct ltstr
{
  bool operator()(const XMLCh * s1,const XMLCh * s2) const;
};

// Struct for data members
struct DataMember
{
	string iName;
	DOMNode* iNode;
	int iOffset;
	TAccess iAccess;
	int iLineNo;

	DataMember(string name,DOMNode* node, int offset, TAccess access, int lineNo):
	iName(name),
	iNode(node),
	iOffset(offset),
	iAccess(access),
	iLineNo(lineNo)
	{
	}

	DataMember(const DataMember& other)
	{
		this->operator=(other);
	}

	const DataMember & operator=(const DataMember& other)
	{
		iName = other.iName;
		iNode = other.iNode;
		iOffset = other.iOffset;
		iAccess = other.iAccess;
		iLineNo = other.iLineNo;
		return *this;
	}
};


/**
* The NodeIndex class indexes the nodes of the XML node tree by 
* the fully qualified name and node ID.
*/
class NodeIndex
{
public:
    typedef map< pair<const XMLCh *,const XMLCh *> , DOMNode*, compareFQName > fqnamemap;
    typedef map< const XMLCh *,pair<const XMLCh*,bool>, ltstr > fileidmap;
	typedef vector<pair<string,DOMNode*> > vtable_t;
	typedef map< string, vtable_t > vtableindex_t;
	typedef vector<DataMember> dtable_t;
	typedef map< string, dtable_t > dtableindex_t;
public:

    /**
    * Clears the node map
    */
    void clear();

    /**
    * Add the node with its id to the map
    */
    void AddNodeIdToMap(DOMNode * node);

    /**
    * Add the node with fully qualified name to the map
    * @param node current DOMNode pointer
    * @param fqname fully qualified name
    */
    void AddNodeFQNameToMap(DOMNode * node, const pair<const XMLCh*,const XMLCh*>& fqname);

    /**
    * Add the file node to file map
    * @param id the node id
    * @param file filepair to add
    */
    void AddFileNodeToMap(const XMLCh* id,pair<const XMLCh*,bool> file);

    /**
    * Finds the node with id.
    * @param root DOMNode pointer
    * @param id of the node
    * @return NULL if not found
    */
    DOMNode * FindNodeById(DOMNode * root, const XMLCh* id);

    /**
    * Finds the node with fully qualified name.
    * @param root DOMNode pointer
    * @param FQName fullu qualified name of the node
    * @return pointer to DOMnode or NULL if not found
    */
    DOMNode * FindNodeByFQName(DOMNode * root, pair<const XMLCh*,const XMLCh* > FQName);

    /**
    * Returns the file pair <filename,tobeanalysed> by file id
    * @param fileid id to search
    * @return found filepair
    */
    const pair<const XMLCh*,bool>& FindFileByFileId(const XMLCh* fileid);

    /**
    * Dumps the tables (for debugging)
    */
    void DumpTables();

    /**
    * Adds a virtual function to the table vtable
    * @param vtable virtual table name
    * @param functionsig function signature
    * @param node pointer to DOMNode
    */
	void AddVirtualFunction(const string& vtable,const string& functionsig, DOMNode* node);

    /**
    * Gets the virtual table vtable
    * @param vtable virtual table name
    * @return virtual table pointer
    */
	const vtable_t* GetVirtualTable(const string& vtable);

    /**
    * Add empty virtual table
    * @param vtable virtual table name
    * @return virtual table pointer
    */
	const vtable_t*	AddEmptyVirtualTable(const string& vtable);
	
    /**
    * Adds a data member to the table vtable
    * @param parentNode Node iterator pointing to the parent node.
    * @param parentName Name of the parent node.
    * @param memberName name of the data table
    * @param memberNode
    * @param index offset value of member
    * @param access how restricted the access of member is
    */
	void AddDataMember(const HANodeIterator& parentNode, const string& parentName, const string& memberName, DOMNode* memberNode, int index, TAccess access,int lineNo);

    /**
    * Gets the data member table
    * @param node Node iterator pointing to the node whose members should be returned.
    * @param nodeName Name of the node.
    * @return table pointer
    */
	const dtable_t* GetDataMemberTable(const HANodeIterator& node, const string& nodeName);

    /**
    * Add empty data member table
    * @param node Reference to the node of the object, whose members will 
    * get the new (empty) table entry
    * @param nodeName Name of the node.
    * @return data table pointer
    */
	const dtable_t* AddEmptyDataMemberTable(const HANodeIterator& node, const string& nodeName);
	
//Private methods
private:
    
    /**
    * Search from the tree
    * @param root DOM root node
    * @param id to search
    * @return id table pointer
    */
    DOMNode * FindNodeByIdFromTree(DOMNode * root, const XMLCh* id);

    /**
    * Inserts data member entry to the given table.
    * @param parentName Name of the data member's parent.
    * @param member Data member to be inserted to the data table.
    * @param dataTable Reference to the data table.
    */
    void InsertDataMember(const string& parentName, const DataMember& member, dtableindex_t& dataTable);
    
//Private member variables
private:
        
    //! Maps node id string to node pointer
    map< const XMLCh *,DOMNode*,ltstr > iIdToNodeMap;

    //! Maps filename to list of nodes declared in that file
    fileidmap iIdToFileMap;

    //! File node map
    fqnamemap iFQNameToNodeMap;

    //! VTable map
    vtableindex_t iVTableIndex;

    //! DTable map
    dtableindex_t iDTableIndex;

    //! Data table for anonymous classes
    dtableindex_t iAnonymousTable;
};

#endif
