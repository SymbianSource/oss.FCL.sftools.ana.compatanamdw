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


#ifndef _HANODEITERATOR_H_
#define _HANODEITERATOR_H_

#include "CmdGlobals.h"
#ifdef __WIN__
#pragma warning(disable:4786)
#endif

#include <assert.h>
#include <map>
#include <list>
#include <xercesc/dom/DOM.hpp>

#include "ReportGenerator.h"
#include "Issues.h"
#include "NodeIndex.h"

using namespace std;

XERCES_CPP_NAMESPACE_USE


/**
* The BBCAnalyser utilizes the HANodeIterator for easy access to a GCCXML 
* generated XML document. The HANodeIterator provides methods for an 
* indexed access to the XML nodes with a node ID and a fully qualified 
* name. The issues are also reported through the HANodeIterator
*/
class HANodeIterator
{
public:
        
    /**
    * Constructor
    * @param aRootnode root DOM node
    * @param aNodemap referencce to NodeIndex
    * @param aReport reference to ReportGenerator
    * @param aFilesToAnalyse list of files to analyse
    * @param aBaselineNode true if currently handling baseline node
    */
    HANodeIterator(DOMNode * aRootnode, NodeIndex & aNodemap, ReportGenerator & aReport,
        const list< pair<string,string> >& aFilesToAnalyse, bool aBaselineNode );
    
    /**
    * Returns node
    * @return pointer to DOMNode
    */
    DOMNode* operator->() const;
    
    /**
    * Finds node from the XML tree by the attribute "id"
    * @param nodeId ID of the searchable node
    * @return true if the node is found
    */
    bool FindNodeById(const XMLCh * nodeId);

    /**
    * Finds node from the XML tree by the fully qualified name (C++) of it 
    * @param nodeName name the searchable node
    * @return true if the node is found
    */
    bool FindNodeByName(pair<const XMLCh *,const XMLCh *> nodeName);

    /**
    * Gets the fully qualified name of this node
    * @return fully qualified name of the node
    */
    pair<const XMLCh *,const XMLCh *> GetFullyQualifiedName();

    /**
    * Adds this node in the index    
    */
    void IndexNode();

    /**
    * Adds this file node to the file index
    * @param filetoanalyse file to be anylysed
    */
    void IndexFileNode(bool filetoanalyse);

    /**
    * Generates fully qualified name for this node and adds it to index
    * if parameter index is true
    * @param index when this is true the node is added to index 
    */
    void NameNode(bool index = false);

    /**
    * Gets the attribute of this node
    * @param attribute attribute to get
    * @return attribute value or NULL
    */    
    const XMLCh* GetAttribute(const char* attribute) const;

    /**
    * Gets the attribute of this node
    * @param attribute attribute to get
    * @return attribute value or NULL
    */    
    const XMLCh* GetAttribute(const XMLCh* attribute) const;
    
    /**
    * Checks if the attribute that can have values 0 or 1 has value 1 (true)
    * or 0 (false). If the attribute is missing return false.
    *
    * @param attribute attribute to search for
    * @return true if attribute is found
    */
    bool CheckForBooleanAttribute(const XMLCh* attribute) const;
    
    /**
    * Checks if the attribute that can have values 0 or 1 has value 1 (true)
    * or 0 (false). If the attribute is missing return false.
    *
    * @param attribute attribute to search for
    * @return true if attribute is found
    */
    bool CheckForBooleanAttribute(const char* attribute) const;

    /**
    * Set value to this node
    *
    * @param attribute attribute to set
    * @param value attribute value to set
    */
    void SetAttribute(const char* attribute, const char* value);

    /**
    * Set value to this node
    *
    * @param attribute attribute to set
    * @param value attribute value to set
    */
    void SetAttribute(const XMLCh* attribute, const XMLCh* value);

    /**
    * Set value to this node
    *
    * @param attribute attribute to set
    * @param value attribute value to set
    */
    void SetAttribute(const char* attribute, const XMLCh* value);

    /**
    * Set value to this node
    *
    * @param attribute attribute to set
    * @param value attribute value to set
    */
	void SetAttribute(const XMLCh* attribute, const char* value);

    /**
    * Get elements by tagname
    * @param tag tagname
    * @return pointer to DOMNodeList
    */ 
    DOMNodeList* GetElementsByTagName(const char* tag) const;

    /**
    * Get elements by tagname
    * @param tag tagname
    * @return pointer to DOMNodeList
    */ 
    DOMNodeList* GetElementsByTagName(const XMLCh* tag) const;

    /**
    * Adds issue to the report. This node is marked as the cause for the issue
    * @param aIdentityId  identity= Class, ExportedFunction, Enumeration, etc.
    * @param aTypeId  what was happened ( something was removed, addded, changed..) 
    * @param bcseverity how severe the issue was for binary compatibility
    * @param scseverity how severe the issue was for source compatibility
    * @param ignoreinfo reason to ignore
    * @param fileid ID of the file
    * @param name filename
    */
    void addIssue(TIssueIdentity aIdentityId, TIssueType aTypeId, TBCSeverity bcseverity, TSCSeverity scseverity, string ignoreinfo, const XMLCh* fileid, const string name, int lineNumber) const;

    /**
    * Check if this node is in the file that is currently analysed
    * @return true if this node is in the file that is currently analysed
    */
    bool toBeAnalysed();

    /**
    * Generates ignore information
    * @param aIdentityId see above
    * @param aTypeId see above
    * @return ignore info as string
    */    
    string generateIgnoreInformation(const TIssueIdentity& aIdentityId, const TIssueType& aTypeId) const;

    /**
    * Generates ignore information
    * @param other reference to other HANodeIterator object
    * @return true if the same node type found
    */ 
    bool IsSameNodeType(const HANodeIterator& other);

public:  
    //! Does not own
    DOMNode *root;
    
    //! Does not own
    DOMNode *current;

    //! Does not own
    NodeIndex &iNodeIndex;
    
    //! Reference to ReporGenerator object (Issue report)
    ReportGenerator &iReport;

    //! Does not own, files that is analysed
    const list< pair<string,string> >& iFilesToAnalyse;

	//! Is this baseline node?
    bool iBaselineNode;

private:
};

// ---------------------------------------------------------------------------------------------
// A quick fix to disable compiler warnings about CheckAccessibility

/**
* Checks if the member memberNode is visible
* @param memberNode the node which accessibilty is determined
* @return true if accessible
*/ 
bool CheckAccessibility(HANodeIterator memberNode);

/**
* Checks if the member memberNode is visible and if the visibility is
* through inline function
* @param memberNode the node which accessibilty is determined
* @param exposedByInline true if node is exposed by inline
* @return true if accessible
*/
bool CheckAccessibility(HANodeIterator memberNode, bool & exposedByInline);


/**
* Checks to see if a member with access "access" is visible from class classNode
* through inline function
* @param classNode the node which accessibilty is determined
* @param exposedByInline true if node is exposed by inline
* @param access which kind of access this node has
* @return true if accessible
*/
bool CheckAccessibility(HANodeIterator classNode, bool & exposedByInline, TAccess access);

// ---------------------------------------------------------------------------------------------


template<TIssueIdentity Identity,TIssueType IssueType> 
void AddIssue(const HANodeIterator* self, const HANodeIterator& ignorenode, int lineNumber, const XMLCh* fileid, const DataMember & data)
{
    bool exposedByInline=false;
    CheckAccessibility(*self,exposedByInline,data.iAccess);

	TBCSeverity sev = BCseverityAccessible<Identity,IssueType>(!exposedByInline);
	TSCSeverity scsev = SCseverityAccessible<Identity,IssueType>(!exposedByInline);
	string ign = ignoreInfo<Identity,IssueType>(*self,ignorenode);
	self->addIssue(Identity,IssueType,sev,scsev,ign,fileid, data.iName,lineNumber);
}

template<TIssueIdentity Identity,TIssueType IssueType> 
void AddIssue(const HANodeIterator* self, const HANodeIterator& ignorenode, int lineNumber, const XMLCh* fileid=NULL, const string namepostfix="")
{
    bool exposedByInline=false;
    CheckAccessibility(*self,exposedByInline);

	TBCSeverity sev = BCseverityAccessible<Identity,IssueType>(!exposedByInline);
	TSCSeverity scsev = SCseverityAccessible<Identity,IssueType>(!exposedByInline);
	string ign = ignoreInfo<Identity,IssueType>(*self,ignorenode);
	self->addIssue(Identity,IssueType,sev,scsev,ign,fileid, namepostfix,lineNumber);
}

#endif
