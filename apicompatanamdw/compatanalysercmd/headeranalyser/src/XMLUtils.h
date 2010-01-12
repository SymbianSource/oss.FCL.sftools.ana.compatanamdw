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


#ifndef __XMLUTILS_H__
#define __XMLUTILS_H__

#include "CmdGlobals.h"
#ifdef __WIN__
#pragma warning(disable:4786)
#endif

#include <string>
#include <xercesc/dom/DOM.hpp>

#include "HANodeIterator.h"
#include "NodeIndex.h"
using namespace std;

XERCES_CPP_NAMESPACE_USE


#include <iostream>

//#if _DEBUG


#if 0
#define DEBUG_STUFF(s1) s1
#define DEBUG_PRINT(s1) {cout << s1 << flush;}
#define DEBUG_PRINT_XMLCh(s1) {printXMLCh(s1);}

#else

#define DEBUG_STUFF(s1)
#define DEBUG_PRINT(s1)
#define DEBUG_PRINT_XMLCh(s1)

#endif

void printXMLCh(const XMLCh* s1);



// The attribute types of node attributes. Is used to 
// choose between compare methods
enum TAttributeType
{
    ESimpleAttribute,
    EIdAttribute,
    EBooleanAttribute,
    EOptionalSimpleAttribute,
    EOptionalIdAttribute,
    ETypeAttribute,
    EOptionalTypeAttribute
};


// The struct that holds the attribute name and type
struct EntityAttributeElement
{
    const XMLCHAR* iAttributeName;
    TAttributeType iAttributeType;	
};

// The struct that holds the entity name and list of
// attributes that needs to be compared
struct EntityComparisonElement
{
    const XMLCHAR* iEntityName;	
    const EntityAttributeElement* iAttributeList;
    int iAttributeCount;
};

/**
* Convert XMLCh to std::string
* @param s1 XML string to convert
* @return converted string
*/
string toString(const XMLCh* s1);

/**
* Comparison between different strings
* @param s1 XML string to compare
* @param s2 XML string to compare
* @return true if the strings are equal
*/
bool Equals(const XMLCh* s1, const XMLCh* s2);

/**
* Comparison between different strings
* @param s1 C-string to compare
* @param s2 C-string to compare
* @return true if the strings are equal
*/
bool Equals(const char* s1, const char* s2);

/**
* Comparison between different strings
* @param s1 XML string to compare
* @param s2 C-string to compare
* @return true if the strings are equal
*/
bool Equals(const XMLCh* s1, const char* s2);

/**
* Comparison between different strings
* @param s1 C-string to compare
* @param s2 XML string to compare
* @return true if the strings are equal
*/
bool Equals(const char* s2, const XMLCh* s1);

/**
* Sets the attribute to the node
* @param node DOM node
* @param attribute to set
* @param value value to set
*/
void SetAttribute(DOMNode * node, const XMLCh* attribute, const XMLCh* value);

/**
* Sets the attribute to the node
* @param node DOM node
* @param attribute to set
* @param value value to set
*/
void SetAttribute(DOMNode * node, const char* attribute, const char* value);

/**
* Gets the attribute from the node
* @param node DOM node
* @param attribute to get
* @return attribute value
*/
const XMLCh* GetAttribute(DOMNode * node, const XMLCh* attribute);

/**
* Gets the attribute from the node
* @param node DOM node
* @param attribute to get
* @return attribute value
*/
const XMLCh* GetAttribute(DOMNode * node, const char * attribute);

/**
* Checks for boolean attribute (values 0 or 1). Return false if not specified
* @param node DOM node
* @param attribute to check
* @return false if not specified, true if attribute is boolean attribute
*/
bool CheckForBooleanAttribute(DOMNode * node, const XMLCh* attribute);

/**
* Checks for boolean attribute (values 0 or 1). Return false if not specified
* @param node DOM node
* @param attribute to check
* @return false if not specified, true if attribute is boolean attribute
*/
bool CheckForBooleanAttribute(DOMNode * node, const char* attribute);

/**
* Gets the typename of the node
* @param node DOM node
* @return type name
*/
string GetTypeName(HANodeIterator node);

/**
* Determines if the node can be considered function
* @param node DOM node
* @return true if node is function
*/
bool IsFunction(HANodeIterator node);

/**
* Generates function signature. Notice that function signature does not
* include return value or default values
* @param node DOM node
* @return signature
*/
string GenerateFunctionSignature(HANodeIterator node);

/**
* Generates fully qualified name
* @param node DOM node
* @return fully qualified name
*/
string GenerateFullyQualifiedName(HANodeIterator node);

/**
* Returns the comparison element for the element with name nodeName
* @param nodeName name of the node
* @return comparison element
*/
const EntityComparisonElement* FindComparison(const XMLCh* nodeName);

/**
* Comparers id lists
* @param baseline baseline node
* @param current current node
* @param idAttributeName 
* @return true if compared lists are equal
*/
bool CompareIdLists(HANodeIterator baseline, HANodeIterator current,const XMLCh* idAttributeName);

/**
* Compares nodes
* @param baseline baseline node
* @param current current node
* @return true if nodes are equal
*/
bool CompareNodes(HANodeIterator baseline, HANodeIterator current);

/**
* Compares names
* @param baseline baseline node
* @param current current node
* @return true if names are equal
*/
bool CompareNames(HANodeIterator baseline, HANodeIterator current);

/**
* Is the node proper (to be analysed)
* @param node node to check
* @return true if the node is proper to analyse
*/
bool IsProperNode(HANodeIterator node);

/**
* Is the node named (in node index)
* @param node node to check
* @return true if the node is named
*/
bool IsNamedNode(HANodeIterator node);

/**
* Compares two file names
* @param first first file to compare
* @param second second file to compare
* @return true if strings match
*/
bool CompareFileNames(string first,string second);


/**
* Compares to attributes
* @param baseline first file to compare
* @param current second file to compare
* @param attributeName name of the attribute
* @param attributeType node attribute type
* @return true if strings match
*/
bool CompareAttributes(HANodeIterator baseline, HANodeIterator current, const XMLCh* attributeName, TAttributeType attributeType);

/**
* Compares to attributes
* @param baseline first file to compare
* @param current second file to compare
* @param attributeName name of the attribute
* @param attributeType node attribute type
* @return true if strings match
*/
bool CompareAttributes(HANodeIterator baseline, HANodeIterator current, const char* attributeName, TAttributeType attributeType);

/**
* Return access level of the node
* @param node node to analyse
* @return access level of node
*/
TAccess CalcAccessModifier(HANodeIterator node);

/**
* Return derived access level of the node
* @param member to check
* @param inheritance level of member
* @return derived access
*/
//TAccess CalcDerivedAccessModifier(TAccess member, TAccess inheritance);

/**
* Check if the access modifier is strightened
* @param baseline baseline node to check
* @param current current node to check
* @return true if strightened
*/
bool CheckAccessModifier(HANodeIterator baseline,HANodeIterator current);

/**
* Check if the access modifier is strightened
* @param baseline baseline access to check
* @param current current access to check
* @return true if strightened
*/
bool CheckAccessModifier(TAccess baseline,TAccess current);

/**
* Check if the node is anonymous
* Return derived access level of the node
* @param node node to check
* @return true if anaonymous
*/
bool IsAnonymous(HANodeIterator node);

/**
* Check if the type is anonymous
* @param node node to check
* @return true if type anonymous
*/
bool IsAnonymousType(HANodeIterator node);

/**
* Is the node type anonymous, returns the anonymous type
* @param node node to check
* @param anonymousnode reference to type returned
* @return true if anonymous node found
*/

bool FindAnonymousType(HANodeIterator node, HANodeIterator& anonymousnode);

/**
* Check if the class is derivable
* @param node node to check
* @return true if the class is derivable
*/
bool ClassIsDerivable(HANodeIterator node);

/**
* Check if the class is instantiable
* @param node node to check
* @return true if the class is instantiable
*/
bool ClassIsInstantiable(HANodeIterator node);

/**
* If returns true the primarybase includes primary base. If the subclass' offset 
* is zero, it is the primary base.
* @param classnode node to check
* @param primarybase returned primary base
* @return true if the class includes primary base
*/
bool ClassPrimaryBase(const HANodeIterator& classnode,HANodeIterator& primarybase );

/**
* Checks if the member memberNode is visible
* @param memberNode node to check
* @return true if the class is visible
*/
bool CheckAccessibility(HANodeIterator memberNode);

/**
* Checks if the member memberNode is visible and if the visibility is 
* through inline function
* @param memberNode node to check
* @param exposedByInline true if exposed by inline function
* @return true if the class is visible
*/
bool CheckAccessibility(HANodeIterator memberNode, bool & exposedByInline);

/**
* Checks to see if a member with access "access" is visible from
* class classNode
* through inline function
* @param classNode node to check
* @param exposedByInline true if exposed by inline function
* @param access access level of the node
* @return true if the class is visible
*/
bool CheckAccessibility(HANodeIterator classNode, bool & exposedByInline, TAccess access);

/**
* Finds the parent node
* through inline function
* @param memberNode node to check
* @param parentNode parent node context found
* @return true if the parent node found
*/
bool FindParentContext(HANodeIterator memberNode, HANodeIterator& parentNode);

/**
* Gets the type size
* through inline function
* @param node node from which to calculate size
* @return pointer to node size
*/
const XMLCh* GetSize(HANodeIterator node);


/**
* Orders the members of a class in different vectors
* @param node node to search
* @param virtualMethods         vector of virtual methods
* @param inlineMethods          vector of inline methods
* @param exportedMethods        vector of exported methods
* @param exportedVirtualMethods vector of exportedVirtualMethods
* @param methods                vector of methods
* @param fields                 vector of fields pointers
* @param others                 vector of others pointers
*/
void ClassOrderMembers(HANodeIterator node,
                                    vector<DOMNode*>& virtualMethods,
                                    vector<DOMNode*>& inlineMethods,
                                    vector<DOMNode*>& exportedMethods,
                                    vector<DOMNode*>& exportedVirtualMethods,
                                    vector<DOMNode*>& methods,
                                    vector<DOMNode*>& fields,
                                    vector<DOMNode*>& others);

/**
* Orders the members of a class in different vectors
* @param node node to search
* @param virtualMethods         vector of virtual methods
* @param inlineMethods          vector of inline methods
* @param exportedMethods        vector of exported methods
* @param methods                vector of methods
* @param fields                 vector of fields pointers
* @param others                 vector of others pointers
*/
void ClassOrderMembers(HANodeIterator node,
                                    vector<DOMNode*>& virtualMethods,
                                    vector<DOMNode*>& inlineMethods,
                                    vector<DOMNode*>& exportedMethods,
                                    vector<DOMNode*>& methods,
                                    vector<DOMNode*>& fields,
                                    vector<DOMNode*>& others);

/**
* Generates virtual table
* @param classnode classnode to generate virtual table
* @return reference to vtable_t
*/
const NodeIndex::vtable_t& ClassGenerateVirtualTable(HANodeIterator& classnode);

/**
* Generates data member table
* @param classnode node to generate data member table
* @return refrence to dtable_t
*/
const NodeIndex::dtable_t& ClassGenerateDataMemberTable(const HANodeIterator& classnode);

/**
* Checks if the s1 starts with s2
* @param s1 node to search
* @param s2 search string 
* @return true if s1 starts with s2
*/
bool StartsWith(const XMLCh* s1, const char* s2);

/**
* Checks if the s1 starts with s2
* @param s1 node to search
* @param s2 search string 
* @return true if s1 starts with s2
*/
bool StartsWith(const XMLCh* s1, const XMLCh* s2);

/**
* Finds the value of attribute from the node type
* @param node node to search
* @param attribute attribute to search
* @return value of the attribute if found
*/
const XMLCh* FindAttributeValueForType(const HANodeIterator& node, const char* attribute);

/**
* Finds the value of attribute from the node type
* @param node node to search
* @param attribute attribute to search
* @return value of the attribute if found
*/
const XMLCh* FindAttributeValueForType(const HANodeIterator& node, const XMLCh* attribute);

/**
* Returns the base size of the class
* @param classnode node to search
* @param fields fields to calculate
* @return value of class base size
*/
//int ClassBaseSize(const HANodeIterator& classnode, const vector<DOMNode*>& fields);

/**
* Returns the base size of the class
* @param classnode node to search
* @param fields fields to calculate
* @return value of class base size
*/
int ClassBaseSize(const HANodeIterator& classnode, const NodeIndex::dtable_t& fields);

/**
 * Returns all nodes representing XML-elements.
 */
void GetElementNodes(HANodeIterator node, DOMNodeList* domNodes, std::vector<DOMNode*>& elemNodes);

/**
 * Reads and parses XML document into DOM.
 * @param xmlFilename Filename of the XML-document
 * @param domParser Pointer to the DOM parser is returned here.
 * @param domDocument Pointer to the DOM document is returned here.
 * @param domRootNode Pointer to the DOM root node is returned here.
 */
int ParseXMLFile(   const string& xmlFilename, 
                    XERCES_CPP_NAMESPACE_QUALIFIER DOMBuilder*& domParser,
                    XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument*& domDocument,
                    XERCES_CPP_NAMESPACE_QUALIFIER DOMNode*& domRootNode );

/**
 * Converts the given string in lower case.
 * @param name Reference to the name string, which is to be converted.
 */
string& toLower(string& name);

#endif
