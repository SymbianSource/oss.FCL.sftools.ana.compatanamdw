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

#include <xercesc/dom/DOM.hpp>

#include "Issues.h"
#include "ReportGenerator.h"
#include "ReportIssue.h"
#include "NodeIndex.h"
#include "HANodeIterator.h"
#include "XMLStringConst.h"
#include "ClassNodeAnalysis.h"
#include "Utils.h"
using namespace std;

XERCES_CPP_NAMESPACE_USE


// ----------------------------------------------------------------------------
// HANodeIterator::HANodeIterator
// Constructor
// ----------------------------------------------------------------------------
//
HANodeIterator::HANodeIterator(DOMNode * aRootnode, NodeIndex & aNodemap, ReportGenerator & aReport,
                               const list< pair<string,string> >& aFilesToAnalyse, bool aBaselineNode ):
            root(aRootnode),
            current(aRootnode),
            iNodeIndex(aNodemap),
            iReport(aReport),
            iFilesToAnalyse(aFilesToAnalyse),
            iBaselineNode(aBaselineNode)
    {
    }

// ----------------------------------------------------------------------------
// HANodeIterator::toBeAnalysed
// 
// ----------------------------------------------------------------------------
//
bool HANodeIterator::toBeAnalysed()
    {
    const XMLCh* fileid = this->GetAttribute(KXMLFileIdString);
    const pair<const XMLCh*,bool>& file = iNodeIndex.FindFileByFileId(fileid);
    return file.second;
    }

XMLCh* GClassString=NULL;


// ----------------------------------------------------------------------------
// HANodeIterator::GetFullyQualifiedName
// ----------------------------------------------------------------------------
//
pair<const XMLCh *,const XMLCh *> HANodeIterator::GetFullyQualifiedName()
    {
    const XMLCh * fqname=NULL;
    const XMLCh * nodename=NULL;

    fqname = this->GetAttribute(KXMLBBCFQNameString);
    nodename = current->getNodeName();
    pair<const XMLCh *,const XMLCh *> ret;
    ret.first = fqname;
    ret.second = nodename;

    if (Equals(ret.second,KXMLStructString))
    {
/*
#ifdef __WIN__
        ret.second = KXMLClassString;
#else
        if (!GClassString)
        {
            GClassString = XMLString::transcode(KXMLClassString);
        }

        ret.second = GClassString;
#endif*/
     GET_FULLY_QUALIFIED_NAME;
    }
    return ret;
    }

// ----------------------------------------------------------------------------
// HANodeIterator::operator->
// ----------------------------------------------------------------------------
//
DOMNode* HANodeIterator::operator->() const
    {
        return (this->current); 
    }

// ----------------------------------------------------------------------------
// HANodeIterator::IndexFileNode
// ----------------------------------------------------------------------------
//
void HANodeIterator::IndexFileNode(bool analysedfile)
    {
    //id="f0" name="../src/Headeranal.cpp"/
    const XMLCh * id = this->GetAttribute(KXMLIdString);
    const XMLCh * name = this->GetAttribute(KXMLNameString);
    pair<const XMLCh*,bool> file;
    file.first = name;
    file.second = analysedfile;
    iNodeIndex.AddFileNodeToMap(id,file);
    }

// ----------------------------------------------------------------------------
// HANodeIterator::IndexNode
// ----------------------------------------------------------------------------
//    
void HANodeIterator::IndexNode()
    {
        iNodeIndex.AddNodeIdToMap(current);
    }

// ----------------------------------------------------------------------------
// HANodeIterator::NameNode
// Name node
// ----------------------------------------------------------------------------
//
void HANodeIterator::NameNode(bool index)
    {
    
        const XMLCh* fqname = this->GetAttribute(KXMLBBCFQNameString);
        if ( !fqname )
        {
            string generatedname;

            const XMLCh* name = this->GetAttribute(KXMLNameString);

            if ( Equals(name,"") )
                return;

            if ( Equals(current->getNodeName(),KXMLEnumValueString) )
            {
                //We are naming the members of anonymous enumeration
                // Generate the name for the parents context

                HANodeIterator tempnode(*this);
                tempnode.current = current->getParentNode();

                const XMLCh * parentContext = tempnode.GetAttribute(KXMLContextString);
                bool found = tempnode.FindNodeById(parentContext);
                assert(found);

                generatedname = GenerateFullyQualifiedName(tempnode);
                generatedname += "::";
                generatedname += toString(name);
            }else
            {
                generatedname = GenerateFullyQualifiedName(*this);
            }

            //DEBUG_PRINT("Fullyqualified name: ");
            //DEBUG_PRINT(generatedname);
            //DEBUG_PRINT("\n");

            XMLCh* fqnamep = XMLString::transcode(generatedname.c_str());
            this->SetAttribute(KXMLBBCFQNameString, fqnamep);
            XMLString::release(&fqnamep);
        }
        if (index)
        {
            fqname = this->GetAttribute(KXMLBBCFQNameString);
            pair<const XMLCh*,const XMLCh*>  fqname = this->GetFullyQualifiedName();
            iNodeIndex.AddNodeFQNameToMap(current,fqname);
        }
    }

// ----------------------------------------------------------------------------
// HANodeIterator::FindNodeById
// Constructor
// 
// ----------------------------------------------------------------------------
//
bool HANodeIterator::FindNodeById(const XMLCh * nodeId)
    {
    DOMNode * node = iNodeIndex.FindNodeById(root, nodeId);

    if (node)
        {
            current = node;
            return true;
        }

    return false;
    }

// ----------------------------------------------------------------------------
// HANodeIterator::IsSameNodeType
// Constructor
// 
// ----------------------------------------------------------------------------
//
bool HANodeIterator::IsSameNodeType(const HANodeIterator& other)
{
    if ( Equals(current->getNodeName(),other->getNodeName()) )
    {
        return true;
    }

    if ( (Equals( KXMLClassString,other->getNodeName()) && Equals( KXMLStructString,current->getNodeName()))
             ||
         (Equals( KXMLClassString,current->getNodeName()) && Equals( KXMLStructString,other->getNodeName()))
        )
    {
        return true;
    }

    return false;
}

// ----------------------------------------------------------------------------
// HANodeIterator::FindNodeByName
// Find node by name
// 
// ----------------------------------------------------------------------------
//
bool HANodeIterator::FindNodeByName(pair<const XMLCh *,const XMLCh *> nodeName)
    {
    DOMNode * node = iNodeIndex.FindNodeByFQName(root, nodeName);

    if (node)
        {
            current = node;
            return true;
        }

    return false;
    }

// ----------------------------------------------------------------------------
// HANodeIterator::GetAttribute
// 
// ----------------------------------------------------------------------------
//
const XMLCh* HANodeIterator::GetAttribute(const char* attribute) const
    {
    return ::GetAttribute(this->current,attribute);
    }

// ----------------------------------------------------------------------------
// HANodeIterator::GetAttribute
// 
// ----------------------------------------------------------------------------
//
const XMLCh* HANodeIterator::GetAttribute(const XMLCh* attribute) const
    {
    return ::GetAttribute(this->current,attribute);
    }
// ----------------------------------------------------------------------------
// HANodeIterator::HANodeIterator
// 
// ----------------------------------------------------------------------------
//
bool HANodeIterator::CheckForBooleanAttribute(const XMLCh* attribute) const
    {
    return ::CheckForBooleanAttribute(current, attribute);
    }

// ----------------------------------------------------------------------------
// HANodeIterator::CheckForBooleanAttribute
// 
// ----------------------------------------------------------------------------
//
bool HANodeIterator::CheckForBooleanAttribute(const char* attribute) const
    {
    return ::CheckForBooleanAttribute(current, attribute);
    }

// ----------------------------------------------------------------------------
// HANodeIterator::SetAttribute
// Constructor
// 
// ----------------------------------------------------------------------------
//
void HANodeIterator::SetAttribute(const char* attribute, const char* value)
    {
        ::SetAttribute(current, attribute, value);
    }

// ----------------------------------------------------------------------------
// HANodeIterator::SetAttribute
// Set attribute value
// 
// ----------------------------------------------------------------------------
//
void HANodeIterator::SetAttribute(const char* attribute, const XMLCh* value)
    {
    XMLCh* chattribute = XMLString::transcode(attribute);
    ::SetAttribute(current, chattribute, value);
    XMLString::release(&chattribute);
    }

// ----------------------------------------------------------------------------
// HANodeIterator::SetAttribute
// Set attribute value
// 
// ----------------------------------------------------------------------------
//
void HANodeIterator::SetAttribute(const XMLCh* attribute, const char* value)
    {
    XMLCh* chvalue = XMLString::transcode(value);
    ::SetAttribute(current, attribute, chvalue);
    XMLString::release(&chvalue);
    }

// ----------------------------------------------------------------------------
// HANodeIterator::SetAttribute
// Set attribute value
// 
// ----------------------------------------------------------------------------
//
void HANodeIterator::SetAttribute(const XMLCh* attribute, const XMLCh* value)
    {
    ::SetAttribute(current, attribute, value);
    }


// ----------------------------------------------------------------------------
// HANodeIterator::GetElementsByTagName
// 
// ----------------------------------------------------------------------------
//
DOMNodeList* HANodeIterator::GetElementsByTagName(const char* tag) const
    {
    XMLCh * enumvaltag = XMLString::transcode(tag);
    DOMNodeList* childs = GetElementsByTagName(enumvaltag);
    XMLString::release(&enumvaltag);

    return childs;
    }

// ----------------------------------------------------------------------------
// HANodeIterator::GetElementsByTagName
// 
// ----------------------------------------------------------------------------
//
DOMNodeList* HANodeIterator::GetElementsByTagName(const XMLCh* tag) const
    {
    return (static_cast<DOMElement*>(this->current))->getElementsByTagName(tag);
    }

// ----------------------------------------------------------------------------
// HANodeIterator::addIssue
// Add issue found in analysis
// ----------------------------------------------------------------------------
//
void HANodeIterator::addIssue(TIssueIdentity aIdentityId, TIssueType aTypeId, TBCSeverity bcseverity, TSCSeverity scseverity, string ignoreinfo, const XMLCh* fileid, const string name,int lineNumber) const
    {
    bool lFlag = false;
    if ( !fileid )
    {
        fileid = this->GetAttribute(KXMLFileIdString);
    }

    string fqname(GenerateFullyQualifiedName(*this));
    fqname += name;
    const pair<const XMLCh*,bool>& file = iNodeIndex.FindFileByFileId(fileid);

    string compareFileName("");

    list< pair<string,string> >::const_iterator it = iFilesToAnalyse.begin();

    /*int linenumber = 0;
    const XMLCh* strlinenumber = this->GetAttribute(KXMLLineString);

    if ( strlinenumber )
    {
        linenumber = atoi(toString(strlinenumber).c_str());
    }
   */
    string filename(toString(file.first));

    string::size_type dirSepInd = filename.find_first_of("\\/");
    if( dirSepInd != string::npos && filename.at(dirSepInd) != DIR_SEPARATOR )
    {
        // We need to convert to proper dir-separator
        replaceChar(filename, filename.at(dirSepInd), DIR_SEPARATOR);
    }

    for (; it != iFilesToAnalyse.end(); ++it)
    {
        if (iBaselineNode)
        {
            if ( CompareFileNames(((*it).first),filename ) )
            {
                filename = ((*it).first);
                compareFileName = ((*it).second);
                lFlag = true;
                break;
            }
        }
        else
        {
            if ( CompareFileNames(((*it).second),filename ) )
            {
                compareFileName = ((*it).first);
                filename = ((*it).second);
                lFlag = true;
                break;
            }
        }
    }
    if(lFlag == true )
    {
        if ( iBaselineNode )
        {
            this->iReport.addIssue(filename, 
                fqname, aIdentityId, aTypeId, bcseverity, scseverity, ignoreinfo, lineNumber,
                compareFileName, "");
        }
        else
        {
            this->iReport.addIssue(compareFileName, 
                fqname, aIdentityId, aTypeId, bcseverity, scseverity, ignoreinfo, lineNumber,
                filename, "");
        }
    }
    }
