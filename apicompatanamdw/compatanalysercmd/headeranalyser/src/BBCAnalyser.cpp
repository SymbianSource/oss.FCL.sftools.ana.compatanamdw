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
#include <time.h>
#include <xercesc/dom/DOM.hpp>

#include "BBCAnalyser.h"
#include "BBCPreAnalysis.h"
#include "Issues.h"
#include "ReportGenerator.h"
#include "ReportIssue.h"
#include "XMLUtils.h"
#include "XMLStringConst.h"
#include "VariableNodeAnalysis.h"
#include "EnumNodeAnalysis.h"
#include "FunctionNodeAnalysis.h"
#include "TypedefNodeAnalysis.h"
#include "OperatorFunctionNodeAnalysis.h"
#include "UnionNodeAnalysis.h"
#include "ClassNodeAnalysis.h"
#include "StructNodeAnalysis.h"
#include "NodeTypeComparator.h"
#include "Utils.h"

using namespace std;

XERCES_CPP_NAMESPACE_USE



struct ConstructorElement
{
    const XMLCHAR* iEntityName;	
    NodeAnalysis::Constructor iConstructor;
};

// Table of different node analysis constructor functions
const ConstructorElement KConstructorTable[KEntityComparisonTableCount]=
    {
    {KXMLBaseString,UnderConstructionNodeAnalysis::Construct},
    {KXMLFundamentalTypeString,UnderConstructionNodeAnalysis::Construct},
    {KXMLTypedefString,TypedefNodeAnalysis::Construct},//
    {KXMLNamespaceString,UnderConstructionNodeAnalysis::Construct},
    {KXMLCvQualifiedTypeString,UnderConstructionNodeAnalysis::Construct},
    {KXMLVariableString,VariableNodeAnalysis::Construct},//
    {KXMLFundamentalTypeString,UnderConstructionNodeAnalysis::Construct},
    {KXMLTypedefString,UnderConstructionNodeAnalysis::Construct},
    {KXMLNamespaceString,UnderConstructionNodeAnalysis::Construct},
    {KXMLFunctionString,FunctionNodeAnalysis::Construct},//
    {KXMLEnumerationString,EnumNodeAnalysis::Construct},//
    {KXMLFieldString,UnderConstructionNodeAnalysis::Construct},
    {KXMLArgumentString,UnderConstructionNodeAnalysis::Construct},
    {KXMLEllipsisString,UnderConstructionNodeAnalysis::Construct},
    {KXMLArrayTypeString,UnderConstructionNodeAnalysis::Construct},
    {KXMLClassString,ClassNodeAnalysis::Construct},//
    {KXMLConstructorString,UnderConstructionNodeAnalysis::Construct},
    {KXMLConverterString,UnderConstructionNodeAnalysis::Construct},
    {KXMLDestructorString,UnderConstructionNodeAnalysis::Construct},
    {KXMLEnumValueString,UnderConstructionNodeAnalysis::Construct},
    {KXMLFileString,UnderConstructionNodeAnalysis::Construct},
    {KXMLFunctionTypeString,UnderConstructionNodeAnalysis::Construct},
    {KXMLMethodString,UnderConstructionNodeAnalysis::Construct},
    {KXMLMethodTypeString,UnderConstructionNodeAnalysis::Construct},
    {KXMLNamespaceAliasString,UnderConstructionNodeAnalysis::Construct},
    {KXMLOffsetTypeString,UnderConstructionNodeAnalysis::Construct},
    {KXMLOperatorFunctionString,OperatorFunctionNodeAnalysis::Construct},
    {KXMLOperatorMethodString,UnderConstructionNodeAnalysis::Construct},
    {KXMLPointerTypeString,UnderConstructionNodeAnalysis::Construct},
    {KXMLReferenceTypeString,UnderConstructionNodeAnalysis::Construct},
    {KXMLStructString,StructNodeAnalysis::Construct},
    {KXMLUnimplementedString,UnderConstructionNodeAnalysis::Construct},
    {KXMLUnionString,UnionNodeAnalysis::Construct}
    };

// ----------------------------------------------------------------------------
// NodeAnalysis::FindNodeAnalysisConstructor
// ----------------------------------------------------------------------------
//
NodeAnalysis::Constructor FindNodeAnalysisConstructor(const XMLCh* nodeName)
{
    int i = 0;

    for (i = 0;i < KEntityComparisonTableCount; ++i)
    {
        if ( Equals(KConstructorTable[i].iEntityName,nodeName) )
        {
            return KConstructorTable[i].iConstructor;
        }
    }
    return NULL;
}

// ----------------------------------------------------------------------------
// BBCPreAnalysis::preAnalyseClassForVirtuality
// 
// Analyse for virtuality
// ----------------------------------------------------------------------------
//
bool BBCPreAnalysis::preAnalyseClassForVirtuality(HANodeIterator classNode)
{
	bool isvirtual = false;
	bool hasvirtualbases = false;

    //Check to see if we have already inspected this class
    if ( classNode.GetAttribute(KXMLBBCVirtualString) )
    {
        return classNode.CheckForBooleanAttribute(KXMLBBCVirtualString);
    }

    if ( classNode->hasChildNodes() )
    {
        //Check for virtual bases first as it is quicker
        DOMNodeList * childs = classNode->getChildNodes();
        
        XMLSize_t childcount = childs->getLength();
        
        for (unsigned int i = 0; i < childcount; ++i)
        {
            DOMNode* child = childs->item(i);
            
            //Skip any other than Base node
            if ( !Equals(child->getNodeName(),KXMLBaseString) ) 
            {
                continue;
            }
            
            HANodeIterator childclass(classNode);
            childclass.current = child;

            if ( childclass.CheckForBooleanAttribute(KXMLVirtualString) )
            {
                classNode.SetAttribute(KXMLBBCVirtualInheritanceString,KXML1String);
                hasvirtualbases = true;
            }
				
            const XMLCh * classid = childclass.GetAttribute(KXMLTypeString);
    
            assert(classid != NULL);

            bool ret = childclass.FindNodeById(classid);

            assert(ret == true);

            if ( preAnalyseClassForVirtuality( childclass ) )
            {
                //The class is virtual, mark it to the xml document and return
                classNode.SetAttribute(KXMLBBCVirtualString, KXML1String);
                isvirtual = true;
            }
            
            if ( childclass.CheckForBooleanAttribute(KXMLBBCVirtualInheritanceString) )
            {
                classNode.SetAttribute(KXMLBBCVirtualInheritanceString,KXML1String);
                hasvirtualbases = true;
            }
        }
        
    }

    //We have already detected that this is virtual class
    if ( isvirtual )
    {
        ClassGenerateVirtualTable(classNode);
        return true;
    }

    //Go through the methods of the class and check them for virtuality
    const XMLCh* attributeValue = classNode.GetAttribute(KXMLMembersString);
    
    if (attributeValue)
    {
        BaseRefVectorOf< XMLCh > * memberids_ptr = XMLString::tokenizeString(attributeValue);
        auto_ptr<BaseRefVectorOf< XMLCh > > memberids(memberids_ptr);

        for (unsigned int i = 0; i < memberids->size(); ++i)
        {
            const XMLCh * memberid = memberids->elementAt(i);
            
            HANodeIterator member(classNode);
            bool memberfound = member.FindNodeById(memberid);

            if ( memberfound )
            {
                if ( member.CheckForBooleanAttribute(KXMLVirtualString) ||
                    member.CheckForBooleanAttribute(KXMLPureVirtualString))
                {
                    //Generate primary virtual table for the class
                    ClassGenerateVirtualTable(classNode);
                    //The class is virtual, mark it to the xml document and return
                    classNode.SetAttribute(KXMLBBCVirtualString, KXML1String);
                    return true;
                }
            }
            else
            {
                //The tree is broken
                assert(false);
            }
        }
        //memberids->cleanup();
        //delete memberids;
    }
    
    classNode.SetAttribute(KXMLBBCVirtualString, KXML0String);
    return false;
}

// ----------------------------------------------------------------------------
// BBCAnalyser::preAnalyseClassForDerivability
//
// Check for derivability. The class is derivable iff:
// 1. Has a public or protected explicitely declared exported constructor
// 2. Has a public or protected inline constructor
// In GCCXML:
// 
// Check methods of type "Constructor" 
//
// Constructor type / attribute:| artificial | explicit | inline | exported
//--------------------------------------------------------------------------
// implicite inline constructor |     x     |     x     |   x    |          
// inline constructor           |           |    (x)    |   x    |          
// exported constructor         |           |    (x)    |        |    x     
// ----------------------------------------------------------------------------
//
void BBCPreAnalysis::preAnalyseClassForDerivability(HANodeIterator classNode)
{
    //Go through the methods of the class and check them for constructor
    const XMLCh* attributeValue = classNode.GetAttribute(KXMLMembersString);

    //Default to public desctructor as it is same as no desctructor at all
    classNode.SetAttribute(KXMLBBCDestructorAccessString,KXMLBBCAccessPublicString);
	
    if (attributeValue)
    {
        BaseRefVectorOf< XMLCh > * memberids_ptr = XMLString::tokenizeString (attributeValue);
        auto_ptr<BaseRefVectorOf< XMLCh > > memberids(memberids_ptr);

        for (unsigned int i = 0; i < memberids->size(); ++i)
        {
            const XMLCh * memberid = memberids->elementAt(i);
            
            HANodeIterator member(classNode);
            
            if ( member.FindNodeById(memberid) )
            {
                //The member is constructor
                if ( Equals(member->getNodeName(),KXMLConstructorString) )
                {
                    //Check if the constructor is protected or public
                    const XMLCh* accessAttribute = member.GetAttribute(KXMLAccessString);
                    
                    if ( Equals(accessAttribute,KXMLProtectedString) || Equals(accessAttribute,KXMLPublicString) )
                    {
                        //If the constructor is artificial (compiler generated) we need to check for the explicit attribute 
                        // to recognize the proper constructor and not the helper constructor generated by the compiler
                        bool artificial = member.CheckForBooleanAttribute(KXMLArtificialString);
                        
                        bool explicit_val = member.CheckForBooleanAttribute(KXMLExplicitString);
                        
                        bool inline_val = member.CheckForBooleanAttribute(KXMLInlineString);
                    
                        const XMLCh* attributeAttribute = member.GetAttribute(KXMLAttributeString);                            
                        //Check for export or inline
                        if ( ( inline_val && explicit_val && artificial ) || //the constructor is compiler generated inline function
                             ( inline_val && !artificial ) ||  //the constructor is explicitely declared inline function
                             (attributeAttribute && Equals(attributeAttribute,KXMLExportedString))  //the constructor is explicitely declared exported function
                            )
                            {
                                if ( Equals(accessAttribute,KXMLProtectedString) )
                                {
                                    //Is derivable class. Mark the node as one.
                                    classNode.SetAttribute(KXMLBBCProtectedConstructorString,KXML1String);
                                }
                                
                                if ( Equals(accessAttribute,KXMLPublicString) )
                                {
                                    classNode.SetAttribute(KXMLBBCPublicConstructorString,KXML1String);
                                    //Class is instantiable,too!!!
                                }
                            }
                    }
                } else if ( Equals(member->getNodeName(),KXMLDestructorString) )
                {
                    //Check if the destructor is private, protected or public and accessibility
                    // if the desctructor is not accessible it is marked as private 
                    const XMLCh* accessAttribute = member.GetAttribute(KXMLAccessString);
                    
                    bool inline_val = member.CheckForBooleanAttribute(KXMLInlineString);
                    bool virtual_val = member.CheckForBooleanAttribute(KXMLVirtualString) ||
                                        member.CheckForBooleanAttribute(KXMLPureVirtualString);
                    bool exported_val = false; 
                    const XMLCh* attributeAttribute = member.GetAttribute(KXMLAttributeString);                            
                             
                    if (attributeAttribute && Equals(attributeAttribute,KXMLExportedString) )
                    {
                        exported_val = true;
                    }

                    if ( !Equals(accessAttribute,KXMLPrivateString) && (inline_val || virtual_val || exported_val) )
                    {

                        if ( Equals(accessAttribute,KXMLPublicString) )
                        {
                            classNode.SetAttribute(KXMLBBCDestructorAccessString,KXMLBBCAccessPublicString);

                        } else if ( Equals(accessAttribute,KXMLProtectedString) )
                        {
                            classNode.SetAttribute(KXMLBBCDestructorAccessString,KXMLBBCAccessProtectedString);
                        } 
                    }
                    else
                    {
                        classNode.SetAttribute(KXMLBBCDestructorAccessString,KXMLBBCAccessPrivateString);
                    }
                }

            }
            else
            {
                //The tree is broken
                assert(false);
            }
        }
        //delete memberids;
    }
}


// ----------------------------------------------------------------------------
// BBCAnalyser::preAnalyseClassForInlineFunctions
// 
// ----------------------------------------------------------------------------
//
void BBCPreAnalysis::preAnalyseClassForInlineFunctions(HANodeIterator classNode)
{
    //Go through the methods of the class and check them for virtuality
    const XMLCh* attributeValue = classNode.GetAttribute(KXMLMembersString);

    if (attributeValue)
    {
        BaseRefVectorOf< XMLCh > * memberids_ptr = XMLString::tokenizeString (attributeValue);
        auto_ptr<BaseRefVectorOf< XMLCh > > memberids(memberids_ptr);
        bool hasPublicInline = false;
        bool hasProtectedInline = false;
        
        for (unsigned int i = 0; i < memberids->size(); ++i)
        {
            const XMLCh * memberid = memberids->elementAt(i);
            
            HANodeIterator member(classNode);
            
            if ( member.FindNodeById(memberid) )
            {
                //Check every inline function but do not take artificial (compiler generated) functions into account
                if ( member.CheckForBooleanAttribute(KXMLInlineString) && !member.CheckForBooleanAttribute(KXMLArtificialString) )
                {

                    //Check if the constructor is protected or public
                    const XMLCh* attributeValue = member.GetAttribute(KXMLAccessString);
                    
                    if ( Equals(attributeValue,KXMLProtectedString) )
                    {
                        //The class has protected inline function
                        hasProtectedInline = true;
                        classNode.SetAttribute(KXMLBBCProtectedInlineString,KXML1String);
                    }
                    
                    if ( Equals(attributeValue,KXMLPublicString) )
                    {
                        //The class has public inline function
                        hasPublicInline = true;
                        classNode.SetAttribute(KXMLBBCPublicInlineString,KXML1String);
                    }
                    
                    //It is enough if we have public inline, the class is fully exposed
                    if ( hasPublicInline )
                    {
                        return;
                    }
                }
            }
            else
            {
                //The tree is broken
                assert(false);
            }
        }
        //memberids->cleanup();
        //delete memberids;
    }
    
}


// ----------------------------------------------------------------------------
// BBCAnalyser::preAnalyseClass
// 
// ----------------------------------------------------------------------------
//
void BBCPreAnalysis::preAnalyseClass(HANodeIterator classNode)
{
    preAnalyseClassForVirtuality(classNode);
    preAnalyseClassForDerivability(classNode);
    preAnalyseClassForInlineFunctions(classNode);
}


// ----------------------------------------------------------------------------
// printNode
// DEBUG method
// 
// ----------------------------------------------------------------------------
//
void printNode(HANodeIterator node)
{
    DEBUG_STUFF(const XMLCh * name = node->getNodeName();)
    const XMLCh * value = node->getNodeValue();
 
    DEBUG_PRINT_XMLCh(name)

    if ( value )
    {
        DEBUG_PRINT(":")
        DEBUG_PRINT_XMLCh(value)
    }

    DOMNamedNodeMap * atts = node->getAttributes();
    if (atts)
    {
        DEBUG_PRINT(" attributes: ")
        XMLSize_t size = atts->getLength();
        for (unsigned int i = 0; i < size; ++i )
        {
            DOMNode * att = atts->item(i);
            HANodeIterator cit(node);
            cit.current = att;
            printNode(cit);
        }
    }
    DEBUG_PRINT("\n")
}


// ----------------------------------------------------------------------------
// BBCAnalyser::preAnalyseGenerateMaps
// 
// ----------------------------------------------------------------------------
//
void BBCPreAnalysis::preAnalyseGenerateMaps(HANodeIterator rootnode, bool baseline)
{
    //First generate the file maps	
    short nodetype = rootnode->getNodeType();
    assert(nodetype == DOMNode::ELEMENT_NODE);

#ifndef NO_DBG
    DEBUG_PRINT("****************preAnalyse: Generating index*********************\n")
    DEBUG_STUFF(time_t starttime = time(NULL);)
#endif

    DOMDocument * doc =  rootnode->getOwnerDocument();
    DOMNodeIterator * domit = doc->createNodeIterator (rootnode.current,DOMNodeFilter::SHOW_ELEMENT, NULL, true);
    DOMNode * it = NULL;
    while ( NULL != (it = domit->nextNode()) )
    {
        HANodeIterator childit(rootnode);
        childit.current = it;

#ifdef _DEBUG
        //printNode(childit);
        // Keep commented, too much stuff to print
#endif
        if (DOMNode::ELEMENT_NODE == childit->getNodeType())
        {
            childit.IndexNode();
        }
    }
#ifndef NO_DBG
    DEBUG_PRINT("****************preAnalyse: Generating index END*********************\n")
    DEBUG_STUFF(time_t endtime = time(NULL);)
    DEBUG_STUFF(time_t runningtime = endtime - starttime;)
    DEBUG_PRINT("ELAPSED TIME: ")
    DEBUG_PRINT((long)runningtime)
    DEBUG_PRINT("\n")

    DEBUG_PRINT("****************preAnalyse: Generating name map*********************\n")
    DEBUG_STUFF(time_t starttime2 = time(NULL);)
#endif

    doc =  rootnode->getOwnerDocument();
    domit = doc->createNodeIterator (rootnode.current,DOMNodeFilter::SHOW_ELEMENT, NULL, true);
    it = NULL;
    while ( NULL != (it = domit->nextNode()) )
    {
        HANodeIterator childit(rootnode);
        childit.current = it;		

        // Add node to name map if following conditions are true:
        // 1. Node is proper i.e. it is in proper context and it is not artificial (compiler generated).
        // 2. Node is named (class, enum, function.. etc.)
        // 3. It is declared in the analysed header OR it is not a baseline node. 
        //    Without this rule, classes that are moved to another, not to be analysed header,
        //    would not be properly analysed.
        if (IsProperNode(childit) && IsNamedNode(childit) && (childit.toBeAnalysed() || !baseline))
        {        
            const XMLCh* nodetype = childit->getNodeName();
            
            if ( Equals(nodetype,KXMLEnumerationString) )
            {
                //Check to see if the enumeration is anonymous	
                if ( IsAnonymous(childit) )
                {
                    DOMNodeList* enumchilds = childit.GetElementsByTagName(KXMLEnumValueString);
                    XMLSize_t enumchildcount = enumchilds->getLength();
                    unsigned int i = 0;
                    for (i = 0; i < enumchildcount; ++i)
                    {
                        HANodeIterator enumchildit(childit);
                        enumchildit.current = enumchilds->item(i);
                        
                        enumchildit.NameNode(!baseline);
                        
                    }

                    continue;//Skip the enum naming 
                }
            }

            childit.NameNode(!baseline);
        }
    }

#ifndef NO_DBG
    DEBUG_PRINT("****************preAnalyse: Generating name map END*********************\n")
    DEBUG_STUFF(time_t endtime2 = time(NULL);)
    DEBUG_STUFF(time_t runningtime2 = endtime2 - starttime2;)
    DEBUG_PRINT("ELAPSED TIME: ")
    DEBUG_PRINT((long)runningtime2)
    DEBUG_PRINT("\n")
#endif
}


// ----------------------------------------------------------------------------
// BBCAnalyser::checkForEmptyFiles 
// ----------------------------------------------------------------------------
//
vector<bool> BBCAnalyser::checkForEmptyFiles(HANodeIterator rootnode, const list<string>& filesToAnalyse, const list<string>& aMacroFiles)
{
    DOMNodeList* childs = rootnode.GetElementsByTagName(KXMLFileString);
    XMLSize_t childcount = childs->getLength();

    vector<bool> filefound(filesToAnalyse.size(),false);

    for (unsigned int i = 0; i < childcount; ++i)
    {
        DOMNode* child = childs->item(i);
        HANodeIterator childit(rootnode);
        childit.current = child;        
        const XMLCh* filename = childit.GetAttribute(KXMLNameString);
        list<string>::const_iterator it = filesToAnalyse.begin();
        int j = 0;
        for (;it != filesToAnalyse.end(); ++it)
        {
            if ( CompareFileNames((*it),toString(filename)) )
            {
                filefound[j] = true;
                break;
            }
            ++j;
        }
    }
	
	//validate that file is not empty
	//in case file only contained macros
	if(!aMacroFiles.empty())
	{
		list<string>::const_iterator start = filesToAnalyse.begin();
		for(unsigned int i=0; i < filesToAnalyse.size(); i++, start++)
		{
			if(!filefound[i])
			{
				list<string>::const_iterator mFiles = aMacroFiles.begin();
				for(;mFiles != aMacroFiles.end();mFiles++)
					if( toLowerCaseWin(*start) == *mFiles )
					{
						filefound[i] = true;
						break;
					}
			}
		}
	}
	return filefound;
}


// ----------------------------------------------------------------------------
// BBCAnalyser::preAnalyse
// 
// ----------------------------------------------------------------------------
//
void BBCPreAnalysis::preAnalyse(HANodeIterator rootnode,const list<string> & filesToAnalyse, bool baseline)
{
    short nodetype = rootnode->getNodeType();    
    assert(nodetype == DOMNode::ELEMENT_NODE);

    //First generate the file maps	
#ifndef NO_DBG
    DEBUG_PRINT("****************preAnalyse: Generating file maps*********************\n")
    DEBUG_STUFF(time_t starttime = time(NULL);)
#endif

    DOMNodeList* childs = rootnode.GetElementsByTagName(KXMLFileString);
    XMLSize_t childcount = childs->getLength();
#ifndef NO_DBG
    DEBUG_PRINT("preAnalyseGenerateMaps: Files to analyse: ")
    DEBUG_PRINT(childcount)
    DEBUG_PRINT("\n")
#endif

    unsigned int i = 0;
    for (i = 0; i < childcount; ++i)
    {
        DOMNode* child = childs->item(i);
        HANodeIterator childit(rootnode);
        childit.current = child;
        bool filetoanalyse = false;
        const XMLCh* filename = childit.GetAttribute(KXMLNameString);
        list<string>::const_iterator it = filesToAnalyse.begin();
        int i = 0;
        for (;it != filesToAnalyse.end(); ++it)
        {
            if ( CompareFileNames((*it),toString(filename)) )
            {
                filetoanalyse = true;
                break;
            }
            ++i;
        }
        childit.IndexFileNode(filetoanalyse);
    }
#ifndef NO_DBG
    DEBUG_PRINT("****************preAnalyse: Generating file maps END*********************\n")
    DEBUG_STUFF(time_t endtime = time(NULL);)
    DEBUG_STUFF(time_t runningtime = endtime - starttime;)
    DEBUG_PRINT("ELAPSED TIME: ")
    DEBUG_PRINT((long)runningtime)
    DEBUG_PRINT("\n")
#endif

    preAnalyseGenerateMaps(rootnode,baseline);

    //rootnode.iNodeIndex.DumpTables();

#ifndef NO_DBG
    DEBUG_PRINT("****************preAnalyse: Preanalysing classes*********************\n")
    DEBUG_STUFF(time_t starttime2 = time(NULL);)
    DEBUG_PRINT("preAnalyse: Nodes to analyse: ")
    DEBUG_PRINT(childcount)
    DEBUG_PRINT("\n")
#endif

    DOMDocument * doc =  rootnode->getOwnerDocument();
    DOMNodeIterator * domit = doc->createNodeIterator (rootnode.current,DOMNodeFilter::SHOW_ELEMENT, NULL, true);
    DOMNode * it = NULL;
    while ( NULL != (it = domit->nextNode()) )
    {
        HANodeIterator childit(rootnode);
        childit.current = it;
#ifdef _DEBUG
        // printNode(childit);
        // Keep commented, too much stuff to print
#endif      
        const XMLCh * nodename = childit->getNodeName();
        if ( DOMNode::ELEMENT_NODE == childit->getNodeType() && childit.toBeAnalysed() && 
             ( Equals(nodename,KXMLClassString) || Equals(nodename,KXMLStructString)
			 || Equals(nodename,KXMLUnionString))
           )
        {
            preAnalyseClass(childit);
        }
    }
    
#ifndef NO_DBG
    DEBUG_PRINT("****************preAnalyse: Preanalysing classes END*********************\n")
    DEBUG_STUFF(time_t endtime2 = time(NULL);)
    DEBUG_STUFF(time_t runningtime2 = endtime2 - starttime2;)
    DEBUG_PRINT("ELAPSED TIME: ")
    DEBUG_PRINT((long)runningtime2)
    DEBUG_PRINT("\n")
#endif
}

// ----------------------------------------------------------------------------
// BBCAnalyser::nodeAnalyseTrees
// ----------------------------------------------------------------------------
//
int BBCAnalyser::nodeAnalyseTrees(HANodeIterator baseline, HANodeIterator current,const list< pair<string,string> >& filesToAnalyse)
{
    //Find out the files to be processed
    short nodetype = baseline->getNodeType();    
    assert(nodetype == DOMNode::ELEMENT_NODE);
    nodetype = current->getNodeType();    
    assert(nodetype == DOMNode::ELEMENT_NODE);

    int ret = 0;

    DOMDocument * doc =  baseline->getOwnerDocument();
    DOMNodeIterator * domit = doc->createNodeIterator (baseline.current,DOMNodeFilter::SHOW_ELEMENT, NULL, true);
    DOMNode * it = NULL;

    while ( NULL != (it = domit->nextNode()) )
    {
        HANodeIterator childit(baseline);
        childit.current = it;

         if (IsNamedNode(childit) && IsProperNode(childit) && childit.toBeAnalysed())
        {
            if ( !CheckAccessibility(childit) )
            {
                //The node is not visible, so no need to analyse
                continue;
            }
            HANodeIterator currentit(current);
			
            const XMLCh* name = childit.GetAttribute(KXMLNameString);
            if ( StartsWith(name,KXMLInternalNamePrefix) )
            {
                //Skip compiler generated pseudo elements
                continue;
            }
            
            const XMLCh* id = childit.GetAttribute(KXMLIdString);
            DEBUG_PRINT("Analysing:")
            if ( name )
            {
                DEBUG_PRINT_XMLCh(name)
            }
            if ( id )
            {
                DEBUG_PRINT(":")
                DEBUG_PRINT_XMLCh(id)
            }
            DEBUG_PRINT("\n")


            NodeAnalysis::Constructor constructorfunction = FindNodeAnalysisConstructor(childit->getNodeName());
            NodeAnalysis * analyser = constructorfunction();
        
            ret += analyser->FindNodeAndAnalyse(childit,currentit);
            delete analyser;			
        }
    }

    return ret;
}

// ----------------------------------------------------------------------------
// BBCAnalyser::analyseTrees
// ----------------------------------------------------------------------------
//
int BBCAnalyser::analyseTrees(DOMNode* baseline, DOMNode* current,const list< pair<string,string> >& filesToAnalyse, const list<string>& aMacroFiles)
{
#ifndef NO_DBG
    DEBUG_PRINT("****************Analyse: ANALYSE starts*********************\n")
    DEBUG_STUFF(time_t starttime = time(NULL);)
#endif

    iBaselineIndex.clear();
    iCurrentIndex.clear();
    
    HANodeIterator baselineit(baseline,iBaselineIndex,iReport, filesToAnalyse, true );
    HANodeIterator currentit(current,iCurrentIndex,iReport, filesToAnalyse, false);
    
    list<string> basefiles, currentfiles;
    list< pair<string,string> >::const_iterator it = filesToAnalyse.begin();
    
    for (; it != filesToAnalyse.end(); ++it)
    {
        basefiles.push_back((*it).first);
        currentfiles.push_back((*it).second);
    }

    preAnalysis.preAnalyse(baselineit,basefiles,true);
    preAnalysis.preAnalyse(currentit,currentfiles,false);

    vector<bool> bfilefound;
    bfilefound = checkForEmptyFiles(baselineit,basefiles,aMacroFiles);
    
    vector<bool> cfilefound;
    cfilefound = checkForEmptyFiles(currentit,currentfiles,aMacroFiles);

    list<pair<string,string> >::const_iterator fileit = filesToAnalyse.begin();
    size_t i = 0;

    for (i=0;i < bfilefound.size(); ++i,++fileit)
    {
        if ( !cfilefound[i] && !bfilefound[i] )
        {
            // Serious problem, the analysed file is not in the GCCXML output
            iReport.addIssue(fileit->first,"", EIssueIdentityFile, EIssueTypeEmpty, 
            BCseverityAccessible<EIssueIdentityFile,EIssueTypeEmpty>(true), SCseverityAccessible<EIssueIdentityFile,EIssueTypeEmpty>(true), "", 0, "",fileit->second, "");
        }
        else if ( !bfilefound[i] )
        {
            // Serious problem, the analysed file is not in the GCCXML output
            iReport.addIssue(fileit->first,"", EIssueIdentityFile, EIssueTypeEmpty, 
            BCseverityAccessible<EIssueIdentityFile,EIssueTypeEmpty>(true), SCseverityAccessible<EIssueIdentityFile,EIssueTypeEmpty>(true), "", 0, "",fileit->second, "");
        }
        else if ( !cfilefound[i])
        {
            // Serious problem, the analysed file is not in the GCCXML output
            iReport.addIssue(fileit->first,"", EIssueIdentityFile, EIssueTypeEmpty, 
				    BCseverityAccessible<EIssueIdentityFile,EIssueTypeEmpty>(true), SCseverityAccessible<EIssueIdentityFile,EIssueTypeEmpty>(true), "", 0, "",fileit->second, "");
        }
    }

    //baselineit.iNodeIndex.DumpTables();
    //currentit.iNodeIndex.DumpTables();

#ifndef NO_DBG
    DEBUG_PRINT("****************nodeAnalyse: Analysing*********************\n")
    DEBUG_STUFF(time_t starttime2 = time(NULL);)
#endif

    int ret = nodeAnalyseTrees(baselineit, currentit, filesToAnalyse);
#ifndef NO_DBG
    DEBUG_STUFF(time_t endtime2 = time(NULL);)
    DEBUG_STUFF(time_t runningtime2 = endtime2- starttime2;)
    DEBUG_PRINT("****************nodeAnalyse: Analysing END*********************\n")
    DEBUG_PRINT("ELAPSED TIME: ")
    DEBUG_PRINT((long)runningtime2)
    DEBUG_PRINT("\n")

    DEBUG_PRINT("****************Analyse: ANALYSE END*********************\n")
    DEBUG_STUFF(time_t endtime = time(NULL);)
    DEBUG_STUFF(time_t runningtime = endtime - starttime;)
    DEBUG_PRINT("ELAPSED TIME: ")
    DEBUG_PRINT((long)runningtime)
    DEBUG_PRINT("\n")
#endif

    return ret;
}


// ----------------------------------------------------------------------------
// BBCAnalyser::BBCAnalyser
// ----------------------------------------------------------------------------
//
BBCAnalyser::BBCAnalyser(ReportGenerator & report):
iReport(report)
{
}


// ----------------------------------------------------------------------------
// NodeAnalysis::findNode
// 
// ----------------------------------------------------------------------------
//
DOMNode* NodeAnalysis::findNode(HANodeIterator nodetofind, HANodeIterator findfrom )
{
    DOMNode * ret = NULL;

    pair<const XMLCh*,const XMLCh*> fqname = nodetofind.GetFullyQualifiedName();
#ifndef NO_DBG
    DEBUG_PRINT("Finding node from current three with fqname: ")
    DEBUG_PRINT_XMLCh(fqname.first)
    DEBUG_PRINT(" ... ")
#endif

    if ( findfrom.FindNodeByName(fqname) )
    {
        ret = findfrom.current;
    }
    return ret;
}

///////////////////////////////UnderConstructionNodeAnalysis////////////////////////////

// ----------------------------------------------------------------------------
// UnderConstructionNodeAnalysis::Construct
// 
// ----------------------------------------------------------------------------
//
NodeAnalysis* UnderConstructionNodeAnalysis::Construct()
{
    return new UnderConstructionNodeAnalysis();
}


// ----------------------------------------------------------------------------
// UnderConstructionNodeAnalysis::Analyse
// 
// ----------------------------------------------------------------------------
//
int UnderConstructionNodeAnalysis::Analyse(HANodeIterator baseline,HANodeIterator current, bool report)
{
    assert(
        Equals(baseline->getNodeName(), current->getNodeName())
        );

    if (report)
    {
        AddIssue<EIssueIdentityFile, EIssueTypeUnderConstruction>(&baseline, baseline,0,"");
    }
    return 1;
}


// ----------------------------------------------------------------------------
// UnderConstructionNodeAnalysis::FindNodeAndAnalyse
// 
// ----------------------------------------------------------------------------
//
int UnderConstructionNodeAnalysis::FindNodeAndAnalyse(HANodeIterator baseline,HANodeIterator current)
{
    AddIssue<EIssueIdentityFile,EIssueTypeUnderConstruction>(&baseline,baseline,0,"");
    return 1;
}
////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////VariableNodeAnalysis/////////////////////////////////////


// ----------------------------------------------------------------------------
// VariableNodeAnalysis::Construct
// ----------------------------------------------------------------------------
//
NodeAnalysis* VariableNodeAnalysis::Construct()
{
    return new VariableNodeAnalysis();
}

// ----------------------------------------------------------------------------
// VariableNodeAnalysis::FindNodeAndAnalyse 
// ----------------------------------------------------------------------------
//
int VariableNodeAnalysis::FindNodeAndAnalyse(HANodeIterator baseline,HANodeIterator current)
{
    DOMNode* node = NodeAnalysis::findNode(baseline,current);
    if ( !node )
    {
        AddIssue<EIssueIdentityVariable, EIssueTypeRemoval>(&baseline, baseline,0,"");
        return 1;
    }
    current.current = node;

    return this->Analyse(baseline,current);
}


// ----------------------------------------------------------------------------
// VariableNodeAnalysis::Analyse
// ----------------------------------------------------------------------------
//
int VariableNodeAnalysis::Analyse(HANodeIterator baseline,HANodeIterator current, bool report)
{
    assert( Equals(KXMLVariableString, baseline->getNodeName()) &&
        Equals(KXMLVariableString, current->getNodeName()) &&
        Equals(baseline->getNodeName(), current->getNodeName())
        );

    int ret = 0;

	int lineNo = 0;
	string issueLoc;
	const XMLCh* lineNumber = current.GetAttribute(KXMLLineString);
	lineNo = atoi(toString(lineNumber).c_str());
	const XMLCh* fnameNode= current.GetAttribute(KXMLFileIdString);
	if( fnameNode!= NULL)
	{
		HANodeIterator fileNode(current);
		bool ret1 = fileNode.FindNodeById(fnameNode);
		issueLoc = toString(fileNode.GetAttribute(KXMLNameString));
	}

    if ( IsAnonymousType(baseline) )
    {
        //We need to to comparison between the baseline type and current type anonymously
    
        HANodeIterator baselinetypeit(baseline);
        HANodeIterator currenttypeit(current);

        const XMLCh* baselinetypeid = baseline.GetAttribute(KXMLTypeString);
        const XMLCh* currenttypeid = current.GetAttribute(KXMLTypeString);

        assert( baselinetypeid && currenttypeid);

        bool ret1 = baselinetypeit.FindNodeById(baselinetypeid);
        bool ret2 = currenttypeit.FindNodeById(currenttypeid);

        assert(ret1 && ret2);

        HANodeIterator baselinetypeanonit(baselinetypeit);
        HANodeIterator currenttypeanonit(currenttypeit);
        ret1 = FindAnonymousType(baselinetypeit,baselinetypeanonit);
        ret2 = FindAnonymousType(currenttypeit,currenttypeanonit);
        
        assert(ret1);

        if ( !ret2 || !baselinetypeanonit.IsSameNodeType(currenttypeanonit) )
        {
            if (report)
            {
                AddIssue<EIssueIdentityVariable, EIssueTypeChangeInType>(&baseline, current,lineNo,issueLoc);
            }
            ++ret;
        }
        else
        {

            NodeAnalysis::Constructor constructorfunction = FindNodeAnalysisConstructor(baselinetypeanonit->getNodeName());
            NodeAnalysis * analyser = constructorfunction();
            int ret = analyser->Analyse(baselinetypeanonit,currenttypeanonit,false);
            if ( ret > 0 )
            {
                if (report)
                {
                    AddIssue<EIssueIdentityVariable, EIssueTypeChangeInType>(&baseline, current,lineNo,issueLoc);
                }
                ++ret;
            }
            delete analyser;
        }
    }
    else
    {
        //{KXMLTypeString,EIdAttribute}
        if ( !CompareAttributes(baseline,current,KXMLTypeString,ETypeAttribute) )
        {
            if (report)
            {
                AddIssue<EIssueIdentityVariable, EIssueTypeChangeInType>(&baseline, current,lineNo,issueLoc);
            }
            ++ret;
        }
    }

    //{KXMLInitString,EOptionalSimpleAttribute}
    if ( !CompareAttributes(baseline,current,KXMLInitString,EOptionalSimpleAttribute) )
    {
        if (report)
        {
            AddIssue<EIssueIdentityVariable, EIssueTypeChangeInInitialisation>(&baseline, current,lineNo,issueLoc);
        }
        ++ret;
    }

	if (!CheckAccessModifier(baseline,current))
    {
        if (report)
        {
            //AddIssue<iIdentity,EIssueTypeAccess>(&baseline, current);
			AddIssue<EIssueIdentityVariable,EIssueTypeAccess>(&baseline, current,lineNo,issueLoc);
        }
        ret += 1;
    }
    
    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////EnumNodeAnalysis/////////////////////////////////////////

// ----------------------------------------------------------------------------
// EnumNodeAnalysis::Construct
// 
// ----------------------------------------------------------------------------
//
NodeAnalysis* EnumNodeAnalysis::Construct()
{
    return new EnumNodeAnalysis;
}

// ----------------------------------------------------------------------------
// EnumNodeAnalysis::FindNodeAndAnalyse
// 
// ----------------------------------------------------------------------------
//
int EnumNodeAnalysis::FindNodeAndAnalyse(HANodeIterator baseline,HANodeIterator current)
{
    int ret = 0;
    if ( IsAnonymous(baseline) )
    {
        DOMNodeList* enumchilds = baseline.GetElementsByTagName(KXMLEnumValueString);
        XMLSize_t enumchildcount = enumchilds->getLength();
        unsigned int i = 0;
        for (i = 0; i < enumchildcount; ++i)
        {
			int lineNo = 0;
			string issueLoc;
            HANodeIterator enumchildit(baseline);
            enumchildit.current = enumchilds->item(i);
            
            DOMNode* node = NodeAnalysis::findNode(enumchildit,current);
            if ( !node )
            {
                AddIssue<EIssueIdentityEnumerationValue,EIssueTypeRemoval>(&enumchildit, enumchildit, 0, "", baseline.GetAttribute(KXMLFileIdString));
                ++ret;
                continue;
            }
            current.current = node;
			DOMNode* parentnode = node->getParentNode();
			const XMLCh* lineNumber = GetAttribute(parentnode,KXMLLineString);
			lineNo = atoi(toString(lineNumber).c_str());
			const XMLCh* fnameNode= current.GetAttribute(KXMLFileIdString);
			if( fnameNode!= NULL)
			{
				HANodeIterator fileNode(current);
				bool ret1 = fileNode.FindNodeById(fnameNode);
				issueLoc = toString(fileNode.GetAttribute(KXMLNameString));
			}

            if ( !CheckEnumValue(enumchildit,current) )
            {
                AddIssue<EIssueIdentityEnumerationValue,EIssueTypeChangeInInitialisation>(&enumchildit, current, lineNo, issueLoc,baseline.GetAttribute(KXMLFileIdString));
                ++ret;
            }
			HANodeIterator currentparent(current);
			if ( FindParentContext(current, currentparent))
			{
				if ( !CheckAccessModifier(baseline,currentparent) )
				{
					AddIssue<EIssueIdentityEnumerationValue,EIssueTypeAccess>(&enumchildit, current, lineNo, issueLoc, baseline.GetAttribute(KXMLFileIdString));
					++ret;
				}
			}
        }
    }
    else
    {

         DOMNode* node = NodeAnalysis::findNode(baseline,current);
        if ( !node )
        {
            AddIssue<EIssueIdentityEnumeration,EIssueTypeRemoval>(&baseline, baseline,0,"");
            return 1;
        }
        current.current = node;

        ret += this->Analyse(baseline,current);
    }
    return ret;
}


// ----------------------------------------------------------------------------
// EnumNodeAnalysis::CheckEnumValue
// 
// ----------------------------------------------------------------------------
//
bool EnumNodeAnalysis::CheckEnumValue(HANodeIterator baseline,HANodeIterator current)
{

    return CompareNodes(baseline,current);
}

// ----------------------------------------------------------------------------
// EnumNodeAnalysis::Analyse
// 
// ----------------------------------------------------------------------------
//
int EnumNodeAnalysis::Analyse(HANodeIterator baseline,HANodeIterator current, bool report)
{
    assert( Equals(KXMLEnumerationString, baseline->getNodeName()) &&
            Equals(KXMLEnumerationString, current->getNodeName()) &&
            Equals(baseline->getNodeName(), current->getNodeName())
            );


    int ret = 0;
	int lineNo = 0;
	string issueLoc;
	const XMLCh* lineNumber = current.GetAttribute(KXMLLineString);
	lineNo = atoi(toString(lineNumber).c_str());
	const XMLCh* fnameNode = current.GetAttribute(KXMLFileIdString);
	if( fnameNode!= NULL)
	{
		HANodeIterator fileNode(current);
		bool ret1 = fileNode.FindNodeById(fnameNode);
		issueLoc = toString(fileNode.GetAttribute(KXMLNameString));
	}

    //{KXMLAlignString,ESimpleAttribute}
    if ( !CompareAttributes(baseline,current,KXMLAlignString,ESimpleAttribute) )
    {
        if (report)
        {
            AddIssue<EIssueIdentityEnumeration,EIssueTypeAlign>(&baseline, current,lineNo,issueLoc);
        }
        ++ret;
    }

    //{KXMLSizeString,ESimpleAttribute}
    if ( !CompareAttributes(baseline,current,KXMLSizeString,ESimpleAttribute) )
    {
        if (report)
        {
            AddIssue<EIssueIdentityEnumeration,EIssueTypeSize>(&baseline, current,lineNo,issueLoc);
        }
        ++ret;
    }

	if (!CheckAccessModifier(baseline,current))
    {
        if (report)
        {
            //AddIssue<iIdentity,EIssueTypeAccess>(&baseline, current);
			AddIssue<EIssueIdentityEnumeration, EIssueTypeAccess>(&baseline, current,lineNo,issueLoc);
        }
        ++ret;
    }

    //Check the enum values
    DOMNodeList* baselinechilds = baseline.GetElementsByTagName(KXMLEnumValueString);
    DOMNodeList* currentchilds = current.GetElementsByTagName(KXMLEnumValueString);
   
    XMLSize_t baselinechildcount = baselinechilds->getLength();
    XMLSize_t currentchildcount = currentchilds->getLength();

    unsigned int i = 0;
    for (i = 0; i < baselinechildcount; ++i)
    {
        HANodeIterator baselineit(baseline);
        baselineit.current = baselinechilds->item(i);
        unsigned int ii = 0;
        for (ii = 0; ii < currentchildcount; ++ii)
        {
            HANodeIterator currentit(current);
            currentit.current = currentchilds->item(ii);

            if ( CompareAttributes(baselineit,currentit,KXMLNameString,ESimpleAttribute)  )
            {
                if ( !CompareAttributes(baselineit,currentit,KXMLInitString,ESimpleAttribute) )
                {
                    if (report)
                    {
                        AddIssue<EIssueIdentityEnumeration,EIssueTypeChange>(&baseline, current,lineNo,issueLoc);
                    }
                    ++ret;
                    return ret;
                }
                break;
            }

        }

        if ( currentchildcount == ii )
        {

            if (report)
            {
				AddIssue<EIssueIdentityEnumerationValue,EIssueTypeRemoval>(&baseline, current,lineNo,issueLoc);
            }
            ++ret;
            return ret;
        }
    }

    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////FunctionNodeAnalysis/////////////////////////////////////


// ----------------------------------------------------------------------------
// FunctionNodeAnalysis::FunctionNodeAnalysis
// 
// ----------------------------------------------------------------------------
//
FunctionNodeAnalysis::FunctionNodeAnalysis():
iFuncType(EIssueIdentityExportedFunction)
{
}

// ----------------------------------------------------------------------------
// FunctionNodeAnalysis::Construct
// 
// ----------------------------------------------------------------------------
//
NodeAnalysis* FunctionNodeAnalysis::Construct()
{
    return new FunctionNodeAnalysis;
}

// ----------------------------------------------------------------------------
// FunctionNodeAnalysis::FindNodeAndAnalyse
// 
// ----------------------------------------------------------------------------
//
int FunctionNodeAnalysis::FindNodeAndAnalyse(HANodeIterator baseline,HANodeIterator current)
{
    if ( baseline.CheckForBooleanAttribute(KXMLInlineString) )
    {
        iFuncType = EIssueIdentityInlineFunction;
    }

    //Check first if the function is exported
    const XMLCh* attributeValue = baseline.GetAttribute(KXMLAttributeString);                            

    if ( (iFuncType == EIssueIdentityInlineFunction) || (attributeValue && Equals(attributeValue,KXMLExportedString)) )
    {
        DOMNode* node = NodeAnalysis::findNode(baseline,current);
        if ( !node )
        {
			//AddIssue<iFuncType,EIssueTypeRemoval>(&baseline, baseline);
            AddIssueFunction<EIssueTypeRemoval>(&baseline,iFuncType,baseline,0,"");
            return 1;
        }
        current.current = node;

        return this->Analyse(baseline,current);
    }
    
    return 0;
}

// ----------------------------------------------------------------------------
// FunctionNodeAnalysis::Analyse
// 
// ----------------------------------------------------------------------------
//
int FunctionNodeAnalysis::Analyse(HANodeIterator baseline,HANodeIterator current, bool report)
{
    assert( 
    Equals(baseline->getNodeName(), current->getNodeName())
    );

    int ret = 0;
//<!ELEMENT FunctionType (Argument | Ellipsis)*>
//<!ATTLIST FunctionType attributes CDATA #IMPLIED>
//<!ATTLIST FunctionType id ID #REQUIRED>
//<!ATTLIST FunctionType returns IDREF #REQUIRED>

	int lineNo = 0;
	string issueLoc;
	const XMLCh* lineNumber = current.GetAttribute(KXMLLineString);
	lineNo = atoi(toString(lineNumber).c_str());
	const XMLCh* fnameNode = current.GetAttribute(KXMLFileIdString);
	if( fnameNode!= NULL)
	{
		HANodeIterator fileNode(current);
		bool ret1 = fileNode.FindNodeById(fnameNode);
		issueLoc = toString(fileNode.GetAttribute(KXMLNameString));
	}

    const XMLCh* attributeValue = current.GetAttribute(KXMLAttributeString);                            
    if (
        (
            (iFuncType == EIssueIdentityInlineFunction) && !current.CheckForBooleanAttribute(KXMLInlineString) 
        ) ||
        ( 
            (iFuncType == EIssueIdentityExportedFunction) && (!attributeValue || !Equals(attributeValue,KXMLExportedString) )
            &&
            (!current.CheckForBooleanAttribute(KXMLVirtualString))
        )
       )
    {
        if (report)
        {
			AddIssueFunction<EIssueTypeRemoval>(&baseline,iFuncType,baseline,0,"");

        }
        ++ret;
        return ret;
    }
    
    string basefuncsig = GenerateFunctionSignature(baseline);
    string currentfuncsig = GenerateFunctionSignature(current);

    if ( basefuncsig != currentfuncsig )
    {
        ++ret;
        if (report)
        {
			AddIssueFunction<EIssueTypeParam>(&baseline,iFuncType,current,lineNo,issueLoc);
        }
    }
    else
    {
        //Check also the default parameter values
        DOMElement * baselineelement = static_cast<DOMElement*>(baseline.current);
        DOMNodeList* baselinechilds = baselineelement->getChildNodes();
        DOMElement * currentelement = static_cast<DOMElement*>(current.current);
        DOMNodeList* currentchilds = currentelement->getChildNodes();
        
        XMLSize_t childcount = baselinechilds->getLength();

        unsigned int i = 0;
        for (i = 0; i < childcount; ++i)
        {
            DOMNode* baselinechild = baselinechilds->item(i);
            HANodeIterator baselinechildit(baseline);
            baselinechildit.current = baselinechild;

            DOMNode* currentchild = currentchilds->item(i);
            HANodeIterator currentchildit(current);
            currentchildit.current = currentchild;

            short nodetype = baselinechildit->getNodeType();
            if (nodetype == DOMNode::ELEMENT_NODE)
            {
				const XMLCh * baselinesize = FindAttributeValueForType(baselinechildit,KXMLSizeString);
				const XMLCh * currentsize = FindAttributeValueForType(currentchildit,KXMLSizeString);

				const XMLCh * baselinealign = FindAttributeValueForType(baselinechildit,KXMLAlignString);
				const XMLCh * currentalign = FindAttributeValueForType(currentchildit,KXMLAlignString);

				if ( !baselinesize )
				{
					baselinesize = baselinealign;
				}
					
				if ( !currentsize )
				{
					currentsize = currentalign;
				}

				if ( !Equals(baselinesize,currentsize) || !Equals(baselinealign, currentalign) )
				{
					++ret;
					if (report)
					{
						//AddIssue<iFuncType,EIssueTypeParam>(&baseline, current);
						AddIssueFunction<EIssueTypeParam>(&baseline,iFuncType,current,lineNo,issueLoc);
					}
					break;
				}
				// if default value is changed then it should be reported as informative
				if(!CompareAttributes(baselinechildit,currentchildit,KXMLDefaultString,EOptionalSimpleAttribute))
				{
					++ret;
					if (report)
					{
						AddIssueFunction<EIssueTypeDefaultParam>(&baseline,iFuncType,current,lineNo,issueLoc);
					}
					break;
				}
            }

        }

    }

    if ( !CompareAttributes(baseline,current,KXMLReturnsString,EOptionalTypeAttribute) )
    {
        ++ret;
        if (report)
        {
			AddIssueFunction<EIssueTypeReturn>(&baseline,iFuncType,current,lineNo,issueLoc);
        }
    }

    return ret;
}


////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////TypedefNodeAnalysis/////////////////////////////////////


// ----------------------------------------------------------------------------
// TypedefNodeAnalysis::Construct
// ----------------------------------------------------------------------------
//
NodeAnalysis* TypedefNodeAnalysis::Construct()
{
    return new TypedefNodeAnalysis;
}

// ----------------------------------------------------------------------------
// TypedefNodeAnalysis::FindNodeAndAnalyse
// ----------------------------------------------------------------------------
//
int TypedefNodeAnalysis::FindNodeAndAnalyse(HANodeIterator baseline,HANodeIterator current)
{
     DOMNode* node = NodeAnalysis::findNode(baseline,current);
    if ( !node )
    {
        AddIssue<EIssueIdentityTypedef,EIssueTypeRemoval>(&baseline, baseline,0,"");
        return 1;
    }
    current.current = node;

    return this->Analyse(baseline,current);
}

// ----------------------------------------------------------------------------
// TypedefNodeAnalysis::Analyse
// ----------------------------------------------------------------------------
//
int TypedefNodeAnalysis::Analyse(HANodeIterator baseline,HANodeIterator current, bool report)
{
    assert( Equals(KXMLTypedefString, baseline->getNodeName()) &&
    Equals(KXMLTypedefString, current->getNodeName()) &&
    Equals(baseline->getNodeName(), current->getNodeName())
    );

  //<Typedef id="_9" name="TOmaInt" type="_8" context="_1" location="f0:108" file="f0" line="108"/>

	int lineNo = 0;
	string issueLoc;
	const XMLCh* lineNumber = current.GetAttribute(KXMLLineString);
	lineNo = atoi(toString(lineNumber).c_str());
	const XMLCh* fnameNode = current.GetAttribute(KXMLFileIdString);
	if( fnameNode != NULL)
	{
		HANodeIterator fileNode(current);
		bool retval= fileNode.FindNodeById(fnameNode);
		issueLoc = toString(fileNode.GetAttribute(KXMLNameString));
	}

    int ret = 0;

    if ( !CompareAttributes(baseline,current,KXMLNameString,ESimpleAttribute) )
    {
        if (report)
        {
            AddIssue<EIssueIdentityTypedef,EIssueTypeChange>(&baseline, current,lineNo,issueLoc);
        }
        ++ret;
    }

    if ( !CompareAttributes(baseline,current,KXMLTypeString,ETypeAttribute) )
    {
        if (report)
        {
            AddIssue<EIssueIdentityTypedef,EIssueTypeChange>(&baseline, current,lineNo,issueLoc);
        }
        ++ret;
    }

    HANodeIterator baselinetypeit(baseline);
    HANodeIterator currenttypeit(current);

    const XMLCh* baselinetypeid = baseline.GetAttribute(KXMLTypeString);
    const XMLCh* currenttypeid = current.GetAttribute(KXMLTypeString);

    assert( baselinetypeid && currenttypeid);

    bool ret1 = baselinetypeit.FindNodeById(baselinetypeid);
    bool ret2 = currenttypeit.FindNodeById(currenttypeid);

    assert(ret1 && ret2);

	if ( IsFunction(baselinetypeit) )
	{
		if ( !CompareAttributes(baselinetypeit,currenttypeit,KXMLReturnsString,EOptionalTypeAttribute) )
		{
			if (report)
			{
				AddIssue<EIssueIdentityTypedef,EIssueTypeChange>(&baseline, current,lineNo,issueLoc);
			}
			++ret;
		}
	}

	if (!CheckAccessModifier(baseline,current))
    {
        if (report)
        {
            //AddIssue<iIdentity,EIssueTypeAccess>(&baseline, current);
            AddIssue<EIssueIdentityTypedef,EIssueTypeAccess>(&baseline, current,lineNo,issueLoc);
        }
        ret += 1;
    }

    return ret;
}


////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////OperatorFunctionNodeAnalysis/////////////////////////////

// ----------------------------------------------------------------------------
// OperatorFunctionNodeAnalysis::Construct
// ----------------------------------------------------------------------------
//
NodeAnalysis* OperatorFunctionNodeAnalysis::Construct()
{
    return new OperatorFunctionNodeAnalysis;
}

////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////UnionNodeAnalysis////////////////////////////////////////

// ----------------------------------------------------------------------------
// UnionNodeAnalysis::Construct
// ----------------------------------------------------------------------------
//
NodeAnalysis* UnionNodeAnalysis::Construct()
{
    return new UnionNodeAnalysis;
}

// ----------------------------------------------------------------------------
// UnionNodeAnalysis::UnionNodeAnalysis
// 
// ----------------------------------------------------------------------------
//
UnionNodeAnalysis::UnionNodeAnalysis()
{
	iIdentity = EIssueIdentityUnion;
}

// ----------------------------------------------------------------------------
// UnionNodeAnalysis::compareBaseSizes
// ----------------------------------------------------------------------------
//
int UnionNodeAnalysis::compareBaseSizes(HANodeIterator baseline, HANodeIterator current, const NodeIndex::dtable_t& bfields, const NodeIndex::dtable_t& cfields, bool report)
{
	//Not meaningful in union as it can not be derived
	return 0;
}

// ----------------------------------------------------------------------------
// UnionNodeAnalysis::FindNodeAndAnalyse
// ----------------------------------------------------------------------------
//
int UnionNodeAnalysis::FindNodeAndAnalyse(HANodeIterator baseline,HANodeIterator current)
{
    //First check to see if this is an anonymous Union
    const XMLCh* name = baseline.GetAttribute(KXMLNameString);
    if ( !name )
    {
        //This is anonymous union and does not need to be analysed
        return 0;
    }
    
    if ( Equals(name,KXMLEmptyString) )
    {
        return 0;
    }

    DOMNode* node = NodeAnalysis::findNode(baseline,current);

    if ( !node )
    {
        AddIssue<EIssueIdentityUnion,EIssueTypeRemoval>(&baseline, baseline,0,"");
        return 1;
    }
    current.current = node;

    return this->Analyse(baseline,current);
}

// ----------------------------------------------------------------------------
// UnionNodeAnalysis::compareVirtualFunctions
// The union can not have virtual functions
// ----------------------------------------------------------------------------
//
int UnionNodeAnalysis::compareVirtualFunctions(HANodeIterator baseline,HANodeIterator current, 
                                                  const vector<DOMNode*>& bvirtualMethods, 
												  const vector<DOMNode*>& cvirtualMethods, 
                                                  bool report)
{
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////ClassNodeAnalysis////////////////////////////////////////

// ----------------------------------------------------------------------------
// printMember
// Debug stuff
// ----------------------------------------------------------------------------
//
void printMember(HANodeIterator member)
{
    DEBUG_PRINT_XMLCh(member->getNodeName());
    DEBUG_PRINT(":");
    const XMLCh * memname = member.GetAttribute(KXMLNameString);
    if (memname)
    {
        DEBUG_PRINT_XMLCh(memname);
    }
}

// ----------------------------------------------------------------------------
// ClassNodeAnalysis::compareMethodsSignature
// Compare baseline and current methods and return false if they do not match.
// Uses additional comparator object if available.
// ----------------------------------------------------------------------------
//
bool ClassNodeAnalysis::compareMethodsSignature(HANodeIterator basemethod,HANodeIterator currentmethod, const NodeTypeComparator& comparator)
{
    short basenodetype = basemethod->getNodeType();
    short currnodetype = currentmethod->getNodeType();
    assert(basenodetype == DOMNode::ELEMENT_NODE && currnodetype == DOMNode::ELEMENT_NODE);
    assert(IsFunction(basemethod) && IsFunction(currentmethod));

#ifdef _DEBUG
    string basefuncsig = GenerateFunctionSignature(basemethod);
    string currentfuncsig = GenerateFunctionSignature(currentmethod);
    cout << "   basefuncsig=" << basefuncsig << endl;
    cout << "currentfuncsig=" << currentfuncsig << endl;
#endif

    if( !Equals(basemethod->getNodeName(), currentmethod->getNodeName() ))
    {
        return false;
    }

    const XMLCh* basenameatt = basemethod.GetAttribute(KXMLNameString);
    const XMLCh* currnameatt = currentmethod.GetAttribute(KXMLNameString);

    if( !Equals(basenameatt, currnameatt ))
    {
        return false;
    }

    DOMElement * basenodeelement = static_cast<DOMElement*>(basemethod.current);
    DOMElement * currnodeelement = static_cast<DOMElement*>(currentmethod.current);    
    std::vector<DOMNode*> baseElementNodes;
    std::vector<DOMNode*> currElementNodes;
    GetElementNodes(basemethod, basenodeelement->getChildNodes(), baseElementNodes);
    GetElementNodes(currentmethod, currnodeelement->getChildNodes(), currElementNodes);    

    if( baseElementNodes.size() != currElementNodes.size() )
    {
        return false;
    }

    for(size_t i = 0; i < baseElementNodes.size(); ++i)
    {
        DOMNode* basechild = baseElementNodes[i];
        DOMNode* currchild = currElementNodes[i];
        HANodeIterator basechildit(basemethod);
        HANodeIterator currchildit(currentmethod);
        basechildit.current = basechild;
        currchildit.current = currchild;
        
        short basetype = basechildit->getNodeType();
        short currtype = currchildit->getNodeType();
        if( !comparator.CompareParameter(basechildit, currchildit) )
        {
            return false;
        }        
    }
    
    if( !comparator.CompareConstness(basemethod, currentmethod) )
    {
        return false;
    }

    return true;
}
// ----------------------------------------------------------------------------
// ClassNodeAnalysis::compareMethodsReturn
// ----------------------------------------------------------------------------
//
bool ClassNodeAnalysis::compareMethodsReturn(HANodeIterator basemethod,HANodeIterator currentmethod, NodeTypeComparator& cmp) 
{
    return cmp.CompareReturnValue(basemethod, currentmethod);
}

// ----------------------------------------------------------------------------
// ClassNodeAnalysis::compareField
// ----------------------------------------------------------------------------
//
int ClassNodeAnalysis::compareField(HANodeIterator baseline, HANodeIterator current, const DataMember& basemember,const DataMember& currentmember, bool report)
{
	//<!ATTLIST Field mutable (0 | 1) "0">
	//<!ATTLIST Field name CDATA #REQUIRED>
	//<!ATTLIST Field offset CDATA #IMPLIED>
	//<!ATTLIST Field type CDATA #REQUIRED>
	int ret = 0;

	HANodeIterator basefield(baseline);
	basefield.current = basemember.iNode;
	HANodeIterator currentfield(current);
	currentfield.current = currentmember.iNode;
	
	int baseoffset = basemember.iOffset;
    int currentoffset = currentmember.iOffset;

	TIssueIdentity identity = EIssueIdentityField;
	bool accessthroughinline = false;

	string issueLoc;
	const XMLCh* fnameNode = current.GetAttribute(KXMLFileIdString);
	if( fnameNode!= NULL)
	{
		HANodeIterator fileNode(current);
		bool ret1 = fileNode.FindNodeById(fnameNode);
		issueLoc = toString(fileNode.GetAttribute(KXMLNameString));
	}

	if ( !CheckAccessibility(baseline,accessthroughinline,basemember.iAccess) )
	{
		identity = EIssueIdentityFieldInaccessible;
	} else
	{

		if ( baseoffset != currentoffset )
		{
			ret++;
			if ( report )
			{
				AddIssueField<EIssueTypeOffset>(&baseline,identity, currentfield,currentmember.iLineNo,
					issueLoc,NULL,basemember);
			}
			else
			{
				return ret;
			}

		}
	}

	if ( IsAnonymousType(basefield) )
    {
        //We need to do comparison between the baseline type and current type anonymously
    
        HANodeIterator baselinetypeit(basefield);
        HANodeIterator currenttypeit(currentfield);

        const XMLCh* baselinetypeid = basefield.GetAttribute(KXMLTypeString);
        const XMLCh* currenttypeid = currentfield.GetAttribute(KXMLTypeString);

        assert( baselinetypeid && currenttypeid);

        bool ret1 = baselinetypeit.FindNodeById(baselinetypeid);
        bool ret2 = currenttypeit.FindNodeById(currenttypeid);

        assert(ret1 && ret2);

        HANodeIterator baselinetypeanonit(baselinetypeit);
        HANodeIterator currenttypeanonit(currenttypeit);
        ret1 = FindAnonymousType(baselinetypeit,baselinetypeanonit);
        ret2 = FindAnonymousType(currenttypeit,currenttypeanonit);
        
        assert(ret1);

		if ( !ret2 || !baselinetypeanonit.IsSameNodeType(currenttypeanonit) )
		{
			if (report)
			{
				AddIssueField<EIssueTypeChangeInType>(&baseline,identity, currentfield,currentmember.iLineNo,
					issueLoc, NULL,basemember);
			}
			ret++;
		}
		else
		{
			bool report2 = false;

            if ( Equals(KXMLUnionString, baselinetypeit->getNodeName()) && Equals(KXMLEmptyString, basefield.GetAttribute(KXMLNameString)) )
            {
                report2 = report;
            }

			NodeAnalysis::Constructor constructorfunction = FindNodeAnalysisConstructor(baselinetypeanonit->getNodeName());
			NodeAnalysis * analyser = constructorfunction();
			int retval2 = analyser->Analyse(baselinetypeanonit,currenttypeanonit,report2);
			if ( retval2 > 0 && !report2)
			{
				if (report)
				{
					AddIssueField<EIssueTypeChangeInType>(&baseline,identity, currentfield,currentmember.iLineNo,
						issueLoc,NULL,basemember);
				}
				++ret;
            }
            delete analyser;
        }
    }
    else
    {
        //{KXMLTypeString,EIdAttribute}
        if ( !CompareAttributes(basefield,currentfield,KXMLTypeString,ETypeAttribute) )
        {
			ret++;
			if ( report )
			{
				AddIssueField<EIssueTypeChangeInType>(&baseline,identity, currentfield,currentmember.iLineNo,
					issueLoc,NULL,basemember);
			}
			else
			{
				return ret;
			}
		}else //Check if the size has changed although the the type has remained same
		{
			const XMLCh* basefieldsize = GetSize(basefield);
			const XMLCh* currentfieldsize = GetSize(currentfield);

			if ( !Equals(basefieldsize,currentfieldsize) )
			{
				ret++;
				if ( report )
				{
					AddIssueField<EIssueTypeSize>(&baseline,identity, currentfield,currentmember.iLineNo,
						issueLoc,NULL,basemember);
				}
				else
				{
					return ret;
				}
			}

		}
    }
    return ret;
}

// ----------------------------------------------------------------------------
// dumpNodeVectordumpNodeVector
// ----------------------------------------------------------------------------
//
void dumpNodeVector(HANodeIterator node,const vector<DOMNode*> & nodes)
{
    DEBUG_PRINT("Dumping node vector:\n")
    vector<DOMNode*>::const_iterator it = nodes.begin();
    for (;it != nodes.end(); ++it)
    {
        node.current = (*it);

        DEBUG_PRINT_XMLCh(node->getNodeName())
        const XMLCh * name = node.GetAttribute(KXMLNameString);
        if (name)
        {
        DEBUG_PRINT(":")
        DEBUG_PRINT_XMLCh(name)
        }
        const XMLCh * id = node.GetAttribute(KXMLIdString);
        if (id)
        {
        DEBUG_PRINT(" with id ")
        DEBUG_PRINT_XMLCh(id)
        }
        DEBUG_PRINT("\n")
    }
}

// ----------------------------------------------------------------------------
// ClassNodeAnalysis::compareNonvirtualFunctions
// ----------------------------------------------------------------------------
//
int ClassNodeAnalysis::compareNonvirtualFunctions( HANodeIterator baseline,
                                                    HANodeIterator current, 
                                                    const vector<DOMNode*>& bexportedMethods,
                                                    const vector<DOMNode*>& cexportedMethods,
                                                    TIssueIdentity identity,
                                                    bool report )
{
    int ret = 0;
	int parentLineNo = 0;

    // Get default comparator:
    const ComparatorVector& cmps = ComparatorFactory::Instance().GetComparators();       
    ComparatorVector::const_iterator comparator = cmps.begin();
	const XMLCh* parenLinenumber = current.GetAttribute( KXMLLineString);
	parentLineNo = atoi(toString(parenLinenumber).c_str());

	string parentIssueLoc;
	const XMLCh* fnameNode = current.GetAttribute(KXMLFileIdString);
	if(fnameNode != NULL)
	{
		HANodeIterator fileNode(current);
		bool ret1 = fileNode.FindNodeById(fnameNode);
		parentIssueLoc = toString(fileNode.GetAttribute(KXMLNameString));
	}

    // Build method maps for baseline and current platform's classes:
    MethodMatchMap baseMap;    
    vector<DOMNode*>::const_iterator i = bexportedMethods.begin();
    for( ; i != bexportedMethods.end(); ++i )
    {
        baseMap.insert( make_pair(*i, MethodMatchFlags(false, false)));
    }

    vector<DOMNode*>::const_iterator j = cexportedMethods.begin();
    MethodMatchMap currMap;    
    for( ; j != cexportedMethods.end(); ++j )
    {
        currMap.insert( make_pair(*j, MethodMatchFlags(false, false)));
    }

    if( comparator != cmps.end() )
    {
        int comparatorRound = 1;
        // Call compare function and give the default comparator as a parameter
        ret = this->compareNonvirtualFunctions(baseline, current, bexportedMethods, cexportedMethods, identity, report, comparator, baseMap, currMap, comparatorRound);        
    }

    if( report )
    {
        MethodMatchMap::iterator baseFunc = baseMap.begin();
        for(; baseFunc != baseMap.end(); ++baseFunc )
        {
			int lineNo = 0;
			string baseMethodName = toString(GetAttribute(baseFunc->first,KXMLNameString));
			MethodMatchMap::iterator curFunc = currMap.begin();
			for(; curFunc != currMap.end(); ++curFunc )
			{
				string curMethodName = toString(GetAttribute(curFunc->first,KXMLNameString));
				if (baseMethodName == curMethodName)
				{
					const XMLCh* linenumber = GetAttribute(curFunc->first, KXMLLineString);
					lineNo = atoi(toString(linenumber).c_str());
					break;

				}
			}
            if( baseFunc->second.signatureMatch == false )
            {
                // Function signatures do not match
                HANodeIterator removedMethod(baseline);
                removedMethod.current = baseFunc->first;
                AddIssueFunction<EIssueTypeRemoval>(&removedMethod, identity, removedMethod,parentLineNo,parentIssueLoc);            
                ++ret;
            }
            else if( baseFunc->second.returnValueMatch == false )
			{
				// Function return values do not match
				HANodeIterator removedMethod(baseline);
				removedMethod.current = baseFunc->first;
				AddIssueFunction<EIssueTypeReturn>(&removedMethod,identity, removedMethod,lineNo,parentIssueLoc);                
				++ret;
			}
        }
    }
    return ret;
}
// ----------------------------------------------------------------------------
// ClassNodeAnalysis::compareNonvirtualFunctions
// ----------------------------------------------------------------------------
//
int ClassNodeAnalysis::compareNonvirtualFunctions(
        HANodeIterator baseline,
        HANodeIterator current, 
        const vector<DOMNode*>& bexportedMethods,
        const vector<DOMNode*>& cexportedMethods,
        TIssueIdentity identity,                                          
        bool report,
        ComparatorVector::const_iterator comparator,
        MethodMatchMap& baseMap,
        MethodMatchMap& currMap,
		int comparatorRound)
{
    int ret = 0;

	int lineNo1 = 0;
	//const XMLCh* lineNumber = current.GetAttribute(KXMLLineString);
	//lineNo = atoi(toString(lineNumber).c_str());

	//Exported methods    
	vector<DOMNode*>::const_iterator bIter = bexportedMethods.begin();        
	for( ; bIter != bexportedMethods.end(); ++bIter )
	{
		int baseCount = 0;
		int currCount = 0;
		MethodMatchMap::iterator baseMapIter = baseMap.find(*bIter);
		assert(baseMapIter != baseMap.end());
		if( baseMapIter->second.signatureMatch )
		{
			continue; // This method has already been found and analyzed.
		}
		HANodeIterator basemethod(baseline);        
		basemethod.current = *bIter;
            
		vector<DOMNode*>::const_iterator cIter = cexportedMethods.begin(); 
		const XMLCh* baseMathodID = basemethod->getNodeName();
        const XMLCh* basenameatt;
		const XMLCh* basereturnatt;
		const XMLCh* basemangledatt;
		if(Equals(baseMathodID,KXMLMethodString))
		{
			basenameatt = basemethod.GetAttribute(KXMLNameString);
			HANodeIterator baseReturMathod(basemethod);
			bool ret = baseReturMathod.FindNodeById(basemethod.GetAttribute(KXMLReturnsString));
			basereturnatt = baseReturMathod.GetAttribute(KXMLNameString);
			basemangledatt = basemethod.GetAttribute(KXMLMangledString);
		}
		for( ; cIter != cexportedMethods.end(); ++cIter)            
		{                
			HANodeIterator currentmethod(current);
			currentmethod.current = *cIter;
			const XMLCh* lineNumber1 = GetAttribute(currentmethod.current,KXMLLineString);
			lineNo1 = atoi(toString(lineNumber1).c_str());
			
			string issueLoc;
			const XMLCh* fnameNode = currentmethod.GetAttribute(KXMLFileIdString);
			if( fnameNode!= NULL)
			{
				HANodeIterator fileNode(currentmethod);
				bool retval = fileNode.FindNodeById(fnameNode);
				issueLoc = toString(fileNode.GetAttribute(KXMLNameString));
			}

			MethodMatchMap::iterator currMapIter = currMap.find(*cIter);
            
			const XMLCh* curMathodID = currentmethod->getNodeName();
			if(Equals(curMathodID,KXMLMethodString))
			{
				HANodeIterator curReturMathod(currentmethod);
				bool ret1 = curReturMathod.FindNodeById(currentmethod.GetAttribute(KXMLReturnsString));
				const XMLCh* curReturnatt = curReturMathod.GetAttribute(KXMLNameString); 

				// check for overloaded function, first time matching the name, return type and signature
				if(	Equals(baseMathodID,KXMLMethodString)&&
					Equals(basenameatt, currentmethod.GetAttribute(KXMLNameString)) && 
					Equals(basereturnatt, curReturnatt) && 
					Equals(basemangledatt, currentmethod.GetAttribute(KXMLMangledString)) )
				{
					baseCount++;// match found
				}

				
			}			

			if( currMapIter != currMap.end() && 
				currMapIter->second.signatureMatch == false &&
				compareMethodsSignature(basemethod, currentmethod, **comparator) )
			{                    
				if( comparatorRound==CONSTFILTER_COMPARATOR )
				{                        
					// if one of the parameter has changed from non-const to const
					ret++;
					if(report)
					{
						//add the issue as it is a source compatibility break
						AddIssueFunction<EIssueTypeParamConst>(&basemethod,identity,currentmethod,lineNo1,issueLoc);
					}

					//make signature and return value true so that the issue is not reported again
					if( baseMapIter != baseMap.end() )
						baseMapIter->second.signatureMatch = true;
					currMapIter->second.signatureMatch = true;

					baseMapIter->second.returnValueMatch = true;
					currMapIter->second.returnValueMatch = true;
					break;
				}

				else if( comparatorRound==CONSTFILTER2_COMPARATOR )
				{                        
					// if one of the parameter has changed from const to non-const
					ret++;
					if(report)
					{
						//add the issue as it is a source compatibility break
						AddIssueFunction<EIssueTypeParamConst2>(&basemethod,identity,currentmethod,lineNo1,issueLoc);
					}

					//make signature and return value true so that the issue is not reported again
					if( baseMapIter != baseMap.end() )
						baseMapIter->second.signatureMatch = true;
					currMapIter->second.signatureMatch = true;

					baseMapIter->second.returnValueMatch = true;
					currMapIter->second.returnValueMatch = true;
					break;
				}

				if( baseMapIter != baseMap.end() )
					baseMapIter->second.signatureMatch = true;
				currMapIter->second.signatureMatch = true;
				//Check also the default parameter values
				DOMElement * baselineelement = static_cast<DOMElement*>(basemethod.current);
				DOMNodeList* baselinechilds = baselineelement->getChildNodes();
				DOMElement * currentelement = static_cast<DOMElement*>(currentmethod.current);
				DOMNodeList* currentchilds = currentelement->getChildNodes();

				XMLSize_t childcount = baselinechilds->getLength();

				unsigned int i = 0;
				for (i = 0; i < childcount; ++i)
				{
					DOMNode* baselinechild = baselinechilds->item(i);
					HANodeIterator baselinechildit(baseline);
					baselinechildit.current = baselinechild;

					DOMNode* currentchild = currentchilds->item(i);
					HANodeIterator currentchildit(current);
					currentchildit.current = currentchild;

					short nodetype = baselinechildit->getNodeType();
					if (nodetype == DOMNode::ELEMENT_NODE)
					{
						const XMLCh * baselinesize = FindAttributeValueForType(baselinechildit,KXMLSizeString);
						const XMLCh * currentsize = FindAttributeValueForType(currentchildit,KXMLSizeString);

						const XMLCh * baselinealign = FindAttributeValueForType(baselinechildit,KXMLAlignString);
						const XMLCh * currentalign = FindAttributeValueForType(currentchildit,KXMLAlignString);

						if ( !baselinesize )
						{
							baselinesize = baselinealign;
						}

						if ( !currentsize )
						{
							currentsize = currentalign;
						}

						if ( !Equals(baselinesize,currentsize) || !Equals(baselinealign, currentalign) )
						{
							++ret;
							if (report)
							{
								AddIssueFunction<EIssueTypeParam>(&basemethod,identity,currentmethod,lineNo1,issueLoc);
							}
							break;
						}
						// if default value is changed then it should be reported as informative
						if(!CompareAttributes(baselinechildit,currentchildit,KXMLDefaultString,EOptionalSimpleAttribute))
						{
							++ret;
							if (report)
							{
								AddIssueFunction<EIssueTypeDefaultParam>(&basemethod,identity,currentmethod,lineNo1,issueLoc);
							}
							break;
						}
					}
				}

				// Check function return values
				const ComparatorVector& cmps = ComparatorFactory::Instance().GetComparators();       
				ComparatorVector::const_iterator retComparator = cmps.begin();
				int retComparatorRound = 1;
				for ( ; retComparator != cmps.end(); retComparator++ )
				{
					if ( compareMethodsReturn(basemethod,currentmethod, **retComparator) )
					{ 
						if( retComparatorRound==CONSTFILTER_COMPARATOR )
						{                       
							// if the return value has changed from const to non-const
							ret++;
							if(report)
							{
								//add the issue as it is a source compatibility break
								AddIssueFunction<EIssueTypeReturnConst>(&basemethod,identity,currentmethod,lineNo1,issueLoc);
							}
						}
						else if( retComparatorRound==CONSTFILTER2_COMPARATOR )
						{                       
							// if the return calue has changed from non-const to const
							ret++;
							if(report)
							{
								//add the issue as it is a source compatibility break
								AddIssueFunction<EIssueTypeReturnConst2>(&basemethod,identity,currentmethod,lineNo1,issueLoc);
							}
						}         

						baseMapIter->second.returnValueMatch = true;
						currMapIter->second.returnValueMatch = true;
						break;
					}
					retComparatorRound++;
				}


				if ( !CheckAccessModifier(basemethod,currentmethod) )
				{
					if (report)
					{
						AddIssueFunction<EIssueTypeAccess>(&basemethod,identity, currentmethod,lineNo1,issueLoc);
					}
					++ret;
				}
				break;
			}
		} // end of cuurent mathod loop
		// check for overloaded function in current having same name and return type with diff signature
		if (baseCount) 
		{
			currCount++;
			cIter = cexportedMethods.begin(); 
			int lineNo;
			string fileName;
			for( ; cIter != cexportedMethods.end(); ++cIter)            
			{                
				HANodeIterator currentmethod(current);
				currentmethod.current = *cIter;

				const XMLCh* curMathodID = currentmethod->getNodeName();
				if(Equals(curMathodID,KXMLMethodString))
				{
					HANodeIterator curReturMathod(currentmethod);
					bool ret1 = curReturMathod.FindNodeById(currentmethod.GetAttribute(KXMLReturnsString));
					const XMLCh* curReturnatt = curReturMathod.GetAttribute(KXMLNameString); 

					const XMLCh* lineNumber1 = GetAttribute(currentmethod.current,KXMLLineString);
			        lineNo = atoi(toString(lineNumber1).c_str());
					const XMLCh* fnameNode = currentmethod.GetAttribute(KXMLFileIdString);
					if(fnameNode != NULL)
					{
						HANodeIterator filenode1(currentmethod); 
						ret1 = filenode1.FindNodeById(fnameNode);
						fileName = toString(filenode1.GetAttribute(KXMLNameString));
					}

					if(Equals(basenameatt, currentmethod.GetAttribute(KXMLNameString)) && 
						Equals(basereturnatt, curReturnatt ) &&
						!Equals(basemangledatt, currentmethod.GetAttribute(KXMLMangledString)) )
					{					
						currCount++;// overloaded function found in current
						break;
					}
				}				
			}

			//Now check if the function is overloaded in base also or not .
			if(currCount > 1)
			{
				vector<DOMNode*>::const_iterator baseInnerIter = bexportedMethods.begin();        
				for( ; baseInnerIter != bexportedMethods.end(); ++baseInnerIter )
				{
					HANodeIterator bmethod(baseline);
					bmethod.current = *baseInnerIter;

					const XMLCh* bMathodID = bmethod->getNodeName();
					if(Equals(bMathodID,KXMLMethodString))
					{
						HANodeIterator returMathod(bmethod);
						bool ret1 = returMathod.FindNodeById(bmethod.GetAttribute(KXMLReturnsString));
						const XMLCh* returnatt = returMathod.GetAttribute(KXMLNameString); 

						if(Equals(basenameatt, bmethod.GetAttribute(KXMLNameString)) && 
							Equals(basereturnatt, returnatt) &&
							!Equals(basemangledatt, bmethod.GetAttribute(KXMLMangledString)) )
						{					
							baseCount++;// overloaded function found in base
							break;
						}
					}
				}

				// Report the overloaded function only if it first time overloaded
				if(baseCount == 1)
				{
					ret++;
					if(report)
					{
						//add the issue as it is a binary compatibility break
						AddIssue<EIssueIdentityExportedFunction,EIssueTypeOverload>(&basemethod, basemethod,lineNo,fileName);
					}
				}
			}
		}
	}//end of base exported mathod loop
        
    // Recursive call with next comparator (if any) and updated method maps.
    const ComparatorVector& cmps = ComparatorFactory::Instance().GetComparators();
    if( ++comparator != cmps.end() )
    {
        comparatorRound++;
        ret += ClassNodeAnalysis::compareNonvirtualFunctions(
            baseline,
            current, 
            bexportedMethods,        
            cexportedMethods,                                           
            identity,                                          
            report,
            comparator,
            baseMap,
            currMap,
            comparatorRound);
    }
    
    return ret;
}

// ----------------------------------------------------------------------------
// ClassNodeAnalysis::compareOthers
// ----------------------------------------------------------------------------
//
int ClassNodeAnalysis::compareOthers(HANodeIterator baseline,HANodeIterator current, 
                                     const vector<DOMNode*>& bothers, const vector<DOMNode*>& cothers, 
                                     bool report)
{
	int retval = 0;
	return retval;
}

// ----------------------------------------------------------------------------
// printlist
// ----------------------------------------------------------------------------
//
void printlist(const NodeIndex::dtable_t& lista)
{
	NodeIndex::dtable_t::const_iterator it = lista.begin();
	for (; it != lista.end(); ++it)
	{
		cout << it->iName << " at " << it->iOffset << "with node:" << it->iNode <<  endl;
	}
}

// ----------------------------------------------------------------------------
// ClassNodeAnalysis::compareFields
// ----------------------------------------------------------------------------
//
int ClassNodeAnalysis::compareFields(HANodeIterator baseline,HANodeIterator current,
                                     const vector<DOMNode*>& bfields_class,
									 const vector<DOMNode*>& cfields_class,
                                     bool report)
{
	int ret = 0;

	const NodeIndex::dtable_t& bfields = ClassGenerateDataMemberTable(baseline);
	const NodeIndex::dtable_t& cfields = ClassGenerateDataMemberTable(current);

	int lineNo = 0;
	const XMLCh* lineNumber = current.GetAttribute(KXMLLineString);
	lineNo = atoi(toString(lineNumber).c_str());

	string issueLoc;
	const XMLCh* fnameNode = current.GetAttribute(KXMLFileIdString);
	if(fnameNode != NULL)
	{
		HANodeIterator fileNode(current);
		bool retval = fileNode.FindNodeById(fnameNode);
		issueLoc = toString(fileNode.GetAttribute(KXMLNameString));
	}

	// If you don't like to see the issue about base size when the size has changed
	// uncomment the test below

	//if (!iReportAddedMembers)
	//{
		// Check only if size has not changed
		ret += compareBaseSizes(baseline, current, bfields, cfields, report);
	//}

	// Fields
    // Order and type of accessible members matters
    //////////////////////////////////////////////////////////////
    vector<bool> fieldFound(cfields.size(),false);
    vector<bool> fieldRemoved(bfields.size(),false);
    vector<bool> fieldChanged(bfields.size(),false);
    vector<int> fieldChangedCurrent(bfields.size(),-1);
    vector<bool> fieldAccessible(bfields.size(),false);

	unsigned int i = 0;
    for (i=0; i < bfields.size(); ++i)
    {
		if ( !bfields[i].iNode )
		{
			unsigned int ii = 0;
			for (ii=0; ii < cfields.size(); ++ii)
			{
				if ( !fieldFound[ii] && (bfields[i].iName == cfields[ii].iName) )
				{
	                fieldFound[ii] = true;

					if ( bfields[i].iOffset != cfields[ii].iOffset )
					{
						if (report)
						{
							AddIssue<EIssueIdentityVirtualTablePointer,EIssueTypeOffset>(&baseline,current,
								lineNo,issueLoc,NULL,bfields[i]);							
						}
						++ret;
					}
					break;
				}
			}

			if ( cfields.size() == ii )
			{
				fieldRemoved[i] = true;
			}

			continue;
		}

        HANodeIterator basefield(baseline);
        basefield.current = bfields[i].iNode;
		bool dummy;
 		fieldAccessible[i] = CheckAccessibility(baseline, dummy, bfields[i].iAccess);

        unsigned int ii = 0;
        for (ii=0; ii < cfields.size(); ++ii)
        {
            HANodeIterator currentfield(current);
            currentfield.current = cfields[ii].iNode;
            
            if ( !fieldFound[ii] && (bfields[i].iName == cfields[ii].iName) )//CompareNames(basefield,currentfield) )
            {
                fieldFound[ii] = true;

                if ( fieldAccessible[i] && !CheckAccessModifier(bfields[i].iAccess,cfields[ii].iAccess) )
                {
                    if (report)
                    {
                        AddIssue<EIssueIdentityField,EIssueTypeAccess>(&baseline, currentfield,cfields[ii].iLineNo,
							issueLoc,NULL,bfields[i]);
                    }
                    ++ret;
                }

				if ( 0 != compareField(baseline,current,bfields[i],cfields[ii],false) )
                {
					fieldChanged[i] = true;
					fieldChangedCurrent[i] = ii;
					if (fieldAccessible[i])
					{
						iReportAddedMembers = true;
					}
                }
                break;
            }
        }

        if ( cfields.size() == ii )
        {
			fieldRemoved[i] = true;
            if ( fieldAccessible[i] )
            {
				iReportAddedMembers = true;
            }
        }
    }

    for (i = 0; i < fieldRemoved.size(); ++i)
    {
        if (fieldRemoved[i])
        {
			if ( !bfields[i].iNode )
			{
				if (report)
				{
					AddIssue<EIssueIdentityVirtualTablePointer,EIssueTypeRemoval>(&baseline,current,lineNo,
						issueLoc,NULL,bfields[i]);							
				}
				continue;
			}

            HANodeIterator basefield(baseline);
            basefield.current = bfields[i].iNode;

			if (iReportAddedMembers || fieldAccessible[i])
			{
				if (report)
				{
					if (fieldAccessible[i])
					{
						AddIssue<EIssueIdentityField,EIssueTypeRemoval>(&baseline, basefield,lineNo,
							issueLoc,NULL,bfields[i]);
					}
					else
					{
						AddIssue<EIssueIdentityFieldInaccessible,EIssueTypeRemoval>(&baseline, basefield,lineNo,
							issueLoc,NULL,bfields[i]);
					}
				}
				++ret;
			}
        }

        if (fieldChanged[i])
        {
            HANodeIterator basefield(baseline);
            HANodeIterator currentfield(current);
            basefield.current = bfields[i].iNode;
			int ii = fieldChangedCurrent[i];

			if ( -1 == ii )
			{
				continue;
			}

			if (iReportAddedMembers || fieldAccessible[i])
			{
				if (report)
				{
					compareField(baseline, current, bfields[i], cfields[ii], report);
				}
				++ret;
			}
        }

    }

    for (i = 0; i < fieldFound.size(); ++i)
    {
        if (!fieldFound[i])
        {
 			if ( !cfields[i].iNode )
			{
				if (report)
				{
					AddIssue<EIssueIdentityVirtualTablePointer,EIssueTypeAddition>(&baseline,current,lineNo,
						issueLoc,NULL,cfields[i]);							
				}
				continue;
			}

			HANodeIterator currentfield(current);
            currentfield.current = cfields[i].iNode;
            if (report && iReportAddedMembers)
            {
                AddIssue<EIssueIdentityField,EIssueTypeAddition>(&current, currentfield,cfields[i].iLineNo,
					issueLoc,NULL,cfields[i]);
            }
            ++ret;
        }
    }
	return ret;
}

// ----------------------------------------------------------------------------
// printlist
// Output list members
// 
// ----------------------------------------------------------------------------
//
void printlist(const NodeIndex::vtable_t& lista)
{
	NodeIndex::vtable_t::const_iterator it = lista.begin();
	for (; it != lista.end(); ++it)
	{
		cout << it->first << endl;
	}

}

// ----------------------------------------------------------------------------
// ClassNodeAnalysis::indexVirtualMethods
// ----------------------------------------------------------------------------
//
void ClassNodeAnalysis::indexVirtualMethods(HANodeIterator node, 
											const vector<DOMNode*>& virtualMethods, 
											const NodeIndex::vtable_t& vtable,
											vector<pair<DOMNode*,int> >& virtualMethodsWithIndex)
{
	vector<DOMNode*>::const_iterator it = virtualMethods.begin();

	for (; it != virtualMethods.end(); ++it)
	{	
		NodeIndex::vtable_t::const_iterator vtableit = vtable.begin();
		for (int i = 0; vtableit != vtable.end(); ++vtableit, ++i)
		{
			HANodeIterator funcnode(node);
			funcnode.current = *it;

			char index_str[256];

			sprintf(index_str, "%d",i);
			
			funcnode.SetAttribute(KXMLBBCVirtualFunctionIndex, index_str );

			string funcsig = GenerateFunctionSignature(funcnode);
			if (funcsig == vtableit->first)
			{
				virtualMethodsWithIndex.push_back(pair<DOMNode*,int>(*it,i));
			}
		}
	}
}

// ----------------------------------------------------------------------------
// ClassNodeAnalysis::compareVirtualTables
// ----------------------------------------------------------------------------
//
int ClassNodeAnalysis::compareVirtualTables(HANodeIterator baseline,HANodeIterator current,
											const NodeIndex::vtable_t& basevtable, 
											const NodeIndex::vtable_t& currentvtable,
                                            bool report)
{
	if ( basevtable.size() != currentvtable.size() )
	{
		return 1;
	}

	NodeIndex::vtable_t::const_iterator baseit = basevtable.begin();
	NodeIndex::vtable_t::const_iterator currentit = currentvtable.begin();

	unsigned int i = 0;
    for (i=0; baseit != basevtable.end(); ++baseit,++i,++currentit)
    {

        if ( baseit->first != currentit->first )
		{
			return 1;
		}
    }
	return 0;
}

// ----------------------------------------------------------------------------
// ClassNodeAnalysis::compareVirtualFunctions
// ----------------------------------------------------------------------------
//
int ClassNodeAnalysis::compareVirtualFunctions(HANodeIterator baseline,HANodeIterator current, 
                                                  const vector<DOMNode*>& bvirtualMethods, 
												  const vector<DOMNode*>& cvirtualMethods, 
                                                  bool report)
{
	int ret = 0;
	//Analyse virtual methods, not a single change is tolerated

    // First we build virtual tables for baseline and current classes.
	const NodeIndex::vtable_t& basevtable = ClassGenerateVirtualTable(baseline);
	const NodeIndex::vtable_t& currentvtable = ClassGenerateVirtualTable(current);

	int parentLineNo = 0;
	int lineNo = 0;
	string parentIssueLoc;
	const XMLCh* parentlineNumber = current.GetAttribute(KXMLLineString);
	parentLineNo = atoi(toString(parentlineNumber).c_str());
	const XMLCh* fnameNode = current.GetAttribute(KXMLFileIdString);
	if(fnameNode != NULL)
	{
		HANodeIterator fileNode(current);
		bool retval = fileNode.FindNodeById(fnameNode);
		parentIssueLoc = toString(fileNode.GetAttribute(KXMLNameString));
	}
	if ( 0 != compareVirtualTables(baseline,current,basevtable,currentvtable,report) )
	{
        // Virtual table has been changed.
		AddIssue<EIssueIdentityVirtualTable,EIssueTypeChange>(&baseline, current, parentLineNo,
			parentIssueLoc, NULL, "[Primary-vtable]");	
	}

	vector<pair<DOMNode*,int> > bvirtualMethodsWithIndex;
	vector<pair<DOMNode*,int> > cvirtualMethodsWithIndex;

    // Add virtual methods to vectors with their indexes (i.e. order inside a class).
	indexVirtualMethods(baseline,bvirtualMethods,basevtable,bvirtualMethodsWithIndex);
	indexVirtualMethods(current,cvirtualMethods,currentvtable,cvirtualMethodsWithIndex);

    unsigned int i = 0;
    vector<bool> virtualMethodFound(cvirtualMethodsWithIndex.size(),false);

    // Use only default comparator here, since virtual functions should have strict match.
    const ComparatorVector& cmps = ComparatorFactory::Instance().GetComparators();
    ComparatorVector::const_iterator defaultcomparator = cmps.begin();
    assert( defaultcomparator != cmps.end() );

    for (i=0; i < bvirtualMethodsWithIndex.size(); ++i)
    {
        HANodeIterator basemethod(baseline);
        basemethod.current = bvirtualMethodsWithIndex[i].first;

        unsigned int ii = 0;
        for (ii=0; ii < cvirtualMethodsWithIndex.size(); ++ii)
        {
            HANodeIterator currentmethod(current);
            currentmethod.current = cvirtualMethodsWithIndex[ii].first;
            
			lineNo = 0;
			string issueLoc;
			const XMLCh* lineNumber = currentmethod.GetAttribute(KXMLLineString);
			lineNo = atoi(toString(lineNumber).c_str());
			const XMLCh* fnameNode = currentmethod.GetAttribute(KXMLFileIdString);
			if( fnameNode!= NULL)
			{
				HANodeIterator fileNode1(currentmethod);
				bool retval = fileNode1.FindNodeById(fnameNode);
				issueLoc = toString(fileNode1.GetAttribute(KXMLNameString));
			}
            if ( compareMethodsSignature(basemethod,currentmethod, **defaultcomparator) )
            {
                virtualMethodFound[ii] = true;
                if (bvirtualMethodsWithIndex[i].second != cvirtualMethodsWithIndex[ii].second)
                {
                    // Here the indexes don't match --> The order of virtual methods has been
                    // changed. This means that the layout of the virtual table has been changed
                    // and the binary compatibility is broken.
                    if (report)
                    {
						AddIssue<EIssueIdentityVirtualFunction,EIssueTypeOrderChange>(&basemethod, currentmethod,
							lineNo,issueLoc);
					}
                    ++ret;
                }

				//Check also the default parameter values
				DOMElement * baselineelement = static_cast<DOMElement*>(basemethod.current);
				DOMNodeList* baselinechilds = baselineelement->getChildNodes();
				DOMElement * currentelement = static_cast<DOMElement*>(currentmethod.current);
				DOMNodeList* currentchilds = currentelement->getChildNodes();
			    
				XMLSize_t childcount = baselinechilds->getLength();

				unsigned int i = 0;
				for (i = 0; i < childcount; ++i)
				{
					DOMNode* baselinechild = baselinechilds->item(i);
					HANodeIterator baselinechildit(baseline);
					baselinechildit.current = baselinechild;

					DOMNode* currentchild = currentchilds->item(i);
					HANodeIterator currentchildit(current);
					currentchildit.current = currentchild;

					short nodetype = baselinechildit->getNodeType();
					if (nodetype == DOMNode::ELEMENT_NODE)
					{
						const XMLCh * baselinesize = FindAttributeValueForType(baselinechildit,KXMLSizeString);
						const XMLCh * currentsize = FindAttributeValueForType(currentchildit,KXMLSizeString);

						const XMLCh * baselinealign = FindAttributeValueForType(baselinechildit,KXMLAlignString);
						const XMLCh * currentalign = FindAttributeValueForType(currentchildit,KXMLAlignString);

						if ( !baselinesize )
						{
							baselinesize = baselinealign;
						}
							
						if ( !currentsize )
						{
							currentsize = currentalign;
						}

						if ( !Equals(baselinesize,currentsize) || !Equals(baselinealign, currentalign) )
						{
							++ret;
							if (report)
							{
								AddIssue<EIssueIdentityVirtualFunction,EIssueTypeParam>(&basemethod,currentmethod,
									lineNo,issueLoc);
							}
							break;
						}
						// if default value is changed then it should be reported as informative
						if(!CompareAttributes(baselinechildit,currentchildit,KXMLDefaultString,EOptionalSimpleAttribute))
						{
							++ret;
							if (report)
							{
								AddIssue<EIssueIdentityVirtualFunction,EIssueTypeDefaultParam>(&basemethod,currentmethod, 
									lineNo,issueLoc);
							}
							break;
						}
					}
				}					
                // check the return types of the methods
				if ( !compareMethodsReturn(basemethod,currentmethod,**defaultcomparator) )
                {
                    if (report)
                    {
						AddIssue<EIssueIdentityVirtualFunction,EIssueTypeReturn>(&basemethod, currentmethod,lineNo,issueLoc);
                    }
                    ++ret;
                }

                if ( !CheckAccessModifier(basemethod,currentmethod) )
                {
                    if (report)
                    {
						AddIssue<EIssueIdentityVirtualFunction,EIssueTypeAccess>(&basemethod, currentmethod,lineNo,issueLoc);
                    }
                    ++ret;
                }
                break;
            }
        }

        if ( cvirtualMethodsWithIndex.size() == ii )
        {
            //Method not found

/*
			// This code detects if the removed virtual function was actually an removed override.
            unsigned int baseindex = bvirtualMethodsWithIndex[i].second;
            HANodeIterator basemethod(baseline);
            basemethod.current = bvirtualMethodsWithIndex[i].first;
			
			if ( (baseindex < currentvtable.size()) && (currentvtable[baseindex].first == GenerateFunctionSignature(basemethod)) )
			{
				//This is a new override and we should report this if the class is derivable
				if (ClassIsDerivable(baseline))
				{
					if (report)
					{
						AddIssue<EIssueIdentityVirtualFunction,EIssueTypeRemovedOverride>(&basemethod, basemethod);
					}
					++ret;
				}
			}
			else*/
			{				
				if (report)
				{
					AddIssue<EIssueIdentityVirtualFunction,EIssueTypeRemoval>(&basemethod, basemethod,
						parentLineNo,parentIssueLoc);
				}
				++ret;
			}
        }
    }

    for (i = 0; i < virtualMethodFound.size(); ++i)
    {
        if (!virtualMethodFound[i])
        {
            HANodeIterator currentmethod(current);
            currentmethod.current = cvirtualMethodsWithIndex[i].first;

			lineNo = 0;
			string issueLoc;
			const XMLCh* lineNumber = currentmethod.GetAttribute(KXMLLineString);
			lineNo = atoi(toString(lineNumber).c_str());
			const XMLCh* fnameNode = currentmethod.GetAttribute(KXMLFileIdString);
			if( fnameNode!= NULL)
			{
				HANodeIterator fileNode1(currentmethod);
				bool retval = fileNode1.FindNodeById(fnameNode);
				issueLoc = toString(fileNode1.GetAttribute(KXMLNameString));
			}
			//Check the base vtable for entry for this function
            unsigned int baseindex = cvirtualMethodsWithIndex[i].second;
			
			if ( (baseindex < basevtable.size()) && (basevtable[baseindex].first == GenerateFunctionSignature(currentmethod)) )
			{				
				// New rule is added for Q_OBJECT macro defining virtual functions.
				// Do - add the Q_OBJECT macro to a class if the class already inherits from QObject ,
				// should not report as overridden.
				if( basevtable[baseindex].first == __Q_OBJECT_METAOBJECT__
					|| basevtable[baseindex].first == __Q_OBJECT_METACALL__
					|| basevtable[baseindex].first == __Q_OBJECT_METACAST__ )
				{
				}
				else if(ClassIsDerivable(baseline))
				{//This is a new overwrite and we should report this if the class is derivable
					if (report)
					{
						AddIssue<EIssueIdentityVirtualFunction,EIssueTypeNewOverride>(&currentmethod, currentmethod,
							lineNo,issueLoc);
					}
					++ret;
				}
			}
			else
			{	
				//This method really modifies the primary vtable
				// If you also want to find out if this function overrides entry in vtable of non-primary base 
				// then generate virtual table for them and search for the function signature from them
				if (report)
				{
					AddIssue<EIssueIdentityVirtualFunction,EIssueTypeAddition>(&currentmethod, currentmethod,
						lineNo,issueLoc);
				}
				++ret;
			}
        }
    }
	return ret;
}

// ----------------------------------------------------------------------------
// ClassNodeAnalysis::compareBaseSizes
// ----------------------------------------------------------------------------
//
int ClassNodeAnalysis::compareBaseSizes(HANodeIterator baseline, HANodeIterator current, const NodeIndex::dtable_t& bfields, const NodeIndex::dtable_t& cfields, bool report)
{
	int ret = 0;

	if ( ClassIsDerivable(baseline) )
	{
		int bbasesize = ClassBaseSize(baseline,bfields);
		int cbasesize = ClassBaseSize(current,cfields);

		if ( (bbasesize) != (cbasesize) )
		{
			int lineNo = 0;
			const XMLCh* lineNumber = current.GetAttribute(KXMLLineString);
			lineNo = atoi(toString(lineNumber).c_str());
			string issueLoc;
			const XMLCh* fnameNode = current.GetAttribute(KXMLFileIdString);
			if(fnameNode != NULL)
			{
				HANodeIterator fileNode(current);
				bool retval = fileNode.FindNodeById(fnameNode);
				issueLoc = toString(fileNode.GetAttribute(KXMLNameString));
			}
			++ret;
			if (report)
			{		
				AddIssueClass<EIssueTypeBaseSize>(&baseline,iIdentity, current,lineNo,issueLoc);
			}
		}
	}
	return ret;
}

// ----------------------------------------------------------------------------
// ClassNodeAnalysis::compareClassMembers
// ----------------------------------------------------------------------------
//
int ClassNodeAnalysis::compareClassMembers(HANodeIterator baseline,HANodeIterator current, bool report)
{
	int ret = 0;
    //Base material
    vector<DOMNode*> bvirtualMethods;
    vector<DOMNode*> binlineMethods;
    vector<DOMNode*> bexportedMethods;
    vector<DOMNode*> bexportedvirtualMethods;
    vector<DOMNode*> bmethods;
    vector<DOMNode*> bfields;
    vector<DOMNode*> bothers;

    //Current material
    vector<DOMNode*> cvirtualMethods;
    vector<DOMNode*> cinlineMethods;
    vector<DOMNode*> cexportedMethods;
    vector<DOMNode*> cexportedvirtualMethods;
    vector<DOMNode*> cmethods;
    vector<DOMNode*> cfields;
    vector<DOMNode*> cothers;

    //Reserve some space for efficiency
    bvirtualMethods.reserve(10);
    bexportedMethods.reserve(10);
    bmethods.reserve(10);
    bfields.reserve(10);
    bothers.reserve(10);

    cvirtualMethods.reserve(10);
    cexportedMethods.reserve(10);
    cmethods.reserve(10);
    cfields.reserve(10);
    cothers.reserve(10);

    //Order members
    ClassOrderMembers(baseline,bvirtualMethods,binlineMethods,bexportedMethods,bexportedvirtualMethods,bmethods,bfields,bothers);
    ClassOrderMembers(current,cvirtualMethods,cinlineMethods,cexportedMethods,cexportedvirtualMethods,cmethods,cfields,cothers);

	//Virtual functions
	ret += compareVirtualFunctions(baseline, current, bvirtualMethods, cvirtualMethods, report);

	//if ( baseline.CheckForBooleanAttribute(KXMLBBCVirtualString) )
	//{
		//ret += compareExportedVirtualFunctions(baseline, current, bexportedvirtualMethods, cexportedvirtualMethods, report);
	//}else if ( current.CheckForBooleanAttribute(KXMLBBCVirtualString) )
	//{
		//The class has changed from non-dynamic class to dynamic class
		//Do we need to report something?
	//}
    
    //Exported methods
	ret += compareNonvirtualFunctions(baseline,current,bexportedMethods,cexportedMethods,EIssueIdentityExportedFunction,report);

    //Inlined methods
    ret += compareNonvirtualFunctions(baseline, current, binlineMethods, cinlineMethods,EIssueIdentityInlineFunction, report);

	//Fields
	ret += compareFields(baseline,current,bfields, cfields, report);

	//Others
	ret += compareOthers(baseline, current, bothers, cothers, report);

    return ret;
}

// ----------------------------------------------------------------------------
// ClassNodeAnalysis::compareBases
// ----------------------------------------------------------------------------
//
int ClassNodeAnalysis::compareBases(HANodeIterator baseline,HANodeIterator current,bool report)
{
    //Check base classes
    int ret = 0;

    DOMNodeList* baselinechilds = baseline.GetElementsByTagName(KXMLBaseString);
    DOMNodeList* currentchilds = current.GetElementsByTagName(KXMLBaseString);
   
    XMLSize_t baselinechildcount = baselinechilds->getLength();
    XMLSize_t currentchildcount = currentchilds->getLength();

	int lineNo = 0;
	string issueLoc;
	const XMLCh* lineNumber = current.GetAttribute(KXMLLineString);
	lineNo = atoi(toString(lineNumber).c_str());
	const XMLCh* fnameNode = current.GetAttribute(KXMLFileIdString);
	if(fnameNode!= NULL)
	{
		HANodeIterator fileNode(current);
		bool retval = fileNode.FindNodeById(fnameNode);
		issueLoc = toString(fileNode.GetAttribute(KXMLNameString));
	}
    if ( baselinechildcount == currentchildcount )
    {
		unsigned int i = 0;
        for (i = 0; i < baselinechildcount; ++i)
        {
            HANodeIterator baselineit(baseline);
            HANodeIterator currentit(current);
            baselineit.current = baselinechilds->item(i);
            
            HANodeIterator basenameit(baseline);
            basenameit.FindNodeById(baselineit.GetAttribute(KXMLTypeString));
            string basename( GenerateFullyQualifiedName(basenameit) );

			unsigned int ii = 0;
			for (ii = 0; ii < currentchildcount; ++ii)
			{
				currentit.current = currentchilds->item(ii);

				HANodeIterator currentnameit(current);
				currentnameit.FindNodeById(currentit.GetAttribute(KXMLTypeString));
				string currentname( GenerateFullyQualifiedName(currentnameit) );
				if ( basename == currentname )
				{
					if ( basenameit.CheckForBooleanAttribute(KXMLBBCVirtualString) )
					{
					
						const NodeIndex::vtable_t& basevtable = ClassGenerateVirtualTable(basenameit);
						const NodeIndex::vtable_t& currentvtable = ClassGenerateVirtualTable(currentnameit);

						if ( 0 != compareVirtualTables(basenameit,currentnameit,basevtable,currentvtable,report) )
						{
							string vtablename = "[";
							vtablename += basename;
							vtablename += "-vtable]";
							AddIssue<EIssueIdentityVirtualTable,EIssueTypeChange>(&baseline, current, 
								lineNo, issueLoc,NULL, vtablename);
						}
					
					}
					if ( 
						!Equals( baselineit.GetAttribute(KXMLVirtualString), currentit.GetAttribute(KXMLVirtualString)) )
					{
						//Virtuality differs
						if (report)
						{
							AddIssueClass<EIssueTypeInheritance>(&baseline,iIdentity, current,lineNo,issueLoc);
						}
						++ret;
					}
            
					if ( !Equals( baselineit.GetAttribute(KXMLOffsetString), currentit.GetAttribute(KXMLOffsetString)) )
					{
						if (report)
						{
							string subobjectname = "[" + basename;
							subobjectname += "]";
							AddIssue<EIssueIdentitySubobject,EIssueTypeOffset>(&baseline,current,lineNo, 
								issueLoc,NULL,subobjectname);
						}
						++ret;
					}
					break;
				}
			}
			if ( currentchildcount == ii )
			{
				if (report)
				{
					//AddIssueClass<EIssueTypeInheritance>(&baseline,iIdentity, current);
                    //base class removed from inheritance
					string subobjectname = "[" + basename;
					subobjectname += "]";
					AddIssue<EIssueIdentitySubobject,EIssueTypeRemoval>(&baseline,current,lineNo,issueLoc,NULL,subobjectname);
				}
				++ret;
			}
        }    
    } else
    {
        //Different amount of bases
        if (report)
        {
			AddIssueClass<EIssueTypeInheritance>(&baseline,iIdentity, current,lineNo,issueLoc);
        }
        ++ret;

        //check if a base class is removed from inheritance
		unsigned int i = 0;
        for (i = 0; i < baselinechildcount; ++i)
        {
            HANodeIterator baselineit(baseline);
            HANodeIterator currentit(current);
            baselineit.current = baselinechilds->item(i);
            
            HANodeIterator basenameit(baseline);
            basenameit.FindNodeById(baselineit.GetAttribute(KXMLTypeString));
            string basename( GenerateFullyQualifiedName(basenameit) );

			unsigned int ii = 0;
			for (ii = 0; ii < currentchildcount; ++ii)
			{
				currentit.current = currentchilds->item(ii);
				
				HANodeIterator currentnameit(current);
				currentnameit.FindNodeById(currentit.GetAttribute(KXMLTypeString));
				
				string currentname( GenerateFullyQualifiedName(currentnameit) );
				if ( basename == currentname )
				{
					break;
				}
			}
			if ( currentchildcount == ii )
			{
				if (report)
				{
					string subobjectname = "[" + basename;
					subobjectname += "]";
					AddIssue<EIssueIdentitySubobject,EIssueTypeRemoval>(&baseline,current,lineNo,issueLoc,NULL,subobjectname);
				}
				++ret;
			}
        }    
    }

    return ret;

}

// ----------------------------------------------------------------------------
// ClassNodeAnalysis::ClassNodeAnalysis
// ----------------------------------------------------------------------------
//
ClassNodeAnalysis::ClassNodeAnalysis()
    : iReportAddedMembers(false),
      iIdentity(EIssueIdentityClass)
{
}


// ----------------------------------------------------------------------------
// ClassNodeAnalysis::Construct
// ----------------------------------------------------------------------------
//
NodeAnalysis* ClassNodeAnalysis::Construct()
{
    return new ClassNodeAnalysis;
}

// ----------------------------------------------------------------------------
// ClassNodeAnalysis::FindNodeAndAnalyse
// ----------------------------------------------------------------------------
//
int ClassNodeAnalysis::FindNodeAndAnalyse(HANodeIterator baseline,HANodeIterator current)
{
    if ( baseline.CheckForBooleanAttribute(KXMIncompleteString) )
    {
        return 0;
    }

     DOMNode* node = NodeAnalysis::findNode(baseline,current);
    if ( !node )
    {
        //AddIssue<>(&baseline,EIssue_class_removal);
        AddIssue<EIssueIdentityClass,EIssueTypeRemoval>(&baseline, baseline,0,"");
        return 1;
    }
    current.current = node;

    return this->Analyse(baseline,current);
}

// ----------------------------------------------------------------------------
// ClassNodeAnalysis::Analyse
// ----------------------------------------------------------------------------
//
int ClassNodeAnalysis::Analyse(HANodeIterator baseline,HANodeIterator current, bool report)
{
    //ASSERTS
    int ret=0;
    short nodetype = baseline->getNodeType();    
    assert(nodetype == DOMNode::ELEMENT_NODE);
    nodetype = current->getNodeType();    
    assert(nodetype == DOMNode::ELEMENT_NODE);
	int lineNo = 0;
	const XMLCh* lineNumber = current.GetAttribute(KXMLLineString);
	lineNo = atoi(toString(lineNumber).c_str());
    string issueLoc;
	const XMLCh* fnameNode = current.GetAttribute(KXMLFileIdString);
	if( fnameNode!= NULL)
	{
		HANodeIterator fileNode(current);
		bool retval = fileNode.FindNodeById(fnameNode);
		issueLoc =toString(fileNode.GetAttribute(KXMLNameString)); 
	}

    const XMLCh* baseanalysisstatus = baseline.GetAttribute(KXMLBBCAnalysisStatus);

    if (baseanalysisstatus)
    {
        if ( Equals(baseanalysisstatus,KXMLBBCAnalysisStatusAnalysing) )
        {
            //We are analysing recursively, should not happen
            assert(false);
        }
        else if ( Equals(baseanalysisstatus,KXMLBBCAnalysisStatusClean) )
        {
            return 0;
        }

		if (!report)
		{
			return 1;
		}
    }

    
    baseline.SetAttribute(KXMLBBCAnalysisStatus,KXMLBBCAnalysisStatusAnalysing);

    bool bincomplete = baseline.CheckForBooleanAttribute(KXMIncompleteString);
    bool cincomplete = current.CheckForBooleanAttribute(KXMIncompleteString);

    // Check if either baseline or current node is of incomplete type.
    // Type is incomplete if the type is just forward declared or the
    // analysed header file can be compiled without resolving the details
    // of the type. This kind of situation occurs for example when only
    // a reference or pointer to the class is used in the analyzed header, 
    // and the class is declared in other header file.
    //
    // If the type is incomplete, we cannot compare the nodes.
    if ( bincomplete || cincomplete )
    {
        if ( bincomplete && cincomplete )
        {	
            ret = 0;
        }
        else if (bincomplete)
        {
            ret = 0;
        }
        else
        {            
			AddIssueClass<EIssueTypeNotAnalysed>(&baseline,iIdentity, baseline,0,issueLoc);
            ret = 1;
        }
    }
    else
    {
        // Check that the access level of the current node has not been changed
        // to more restricted.
        if (!CheckAccessModifier(baseline,current))
        {
            if (report)
            {         
				AddIssueClass<EIssueTypeAccess>(&baseline,iIdentity, current,lineNo,issueLoc);
            }
            ret += 1;
        }


		// Check if the class has virtual bases
		if ( baseline.CheckForBooleanAttribute(KXMLBBCVirtualInheritanceString) )
		{
			AddIssueClass<EIssueTypeVirtualBases>(&baseline,iIdentity, current,lineNo,issueLoc);
			++ret;
		}

		if ( current.CheckForBooleanAttribute(KXMLBBCVirtualInheritanceString) )
		{
			AddIssueClass<EIssueTypeVirtualBases>(&current,iIdentity, current,lineNo,issueLoc);
			++ret;
		}

        // Check if the class is istantiable or derivable
        if ( ClassIsInstantiable(baseline) || (ClassIsDerivable(baseline) && EIssueIdentityUnion != iIdentity) )
        {

            if ( !CompareAttributes(baseline,current,KXMLAlignString,ESimpleAttribute) )
            {
                if (report)
                {                    
					AddIssueClass<EIssueTypeAlign>(&baseline,iIdentity, current,lineNo,issueLoc);
                    iReportAddedMembers = true;
                }
                ret += 1;
            }

            if ( !CompareAttributes(baseline,current,KXMLSizeString,ESimpleAttribute) )
            {
                if (report)
                {                 
					AddIssueClass<EIssueTypeSize>(&baseline,iIdentity, current,lineNo,issueLoc);
                    iReportAddedMembers = true;
                }
                ret += 1;
            }
        }
       	//ret += compareBaseSizes(baseline,current,report);
        ret += compareClassMembers(baseline,current,report);
        ret += compareBases(baseline,current,report);
    }

    if ( ret == 0 )
    {
        baseline.SetAttribute(KXMLBBCAnalysisStatus,KXMLBBCAnalysisStatusClean);
    } else
    {
        baseline.SetAttribute(KXMLBBCAnalysisStatus,KXMLBBCAnalysisStatusIssues);
    }

    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////StructNodeAnalysis///////////////////////////////////////

// ----------------------------------------------------------------------------
// StructNodeAnalysis::Construct
// ----------------------------------------------------------------------------
//
NodeAnalysis* StructNodeAnalysis::Construct()
{
    return new StructNodeAnalysis;
}

// ----------------------------------------------------------------------------
// StructNodeAnalysis::StructNodeAnalysis
// ----------------------------------------------------------------------------
//
StructNodeAnalysis::StructNodeAnalysis()
{
	iIdentity = EIssueIdentityStruct;
}
////////////////////////////////////////////////////////////////////////////////////////

