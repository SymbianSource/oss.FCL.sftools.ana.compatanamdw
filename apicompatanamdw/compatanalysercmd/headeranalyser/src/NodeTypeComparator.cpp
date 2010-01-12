/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies). 
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
#include "XMLUtils.h"
#include "XMLStringConst.h"
#include "NodeTypeComparator.h"

// Set the static instance member to NULL
std::auto_ptr<ComparatorFactory> ComparatorFactory::iInstance = 
    std::auto_ptr<ComparatorFactory>(0);

/**
 * DefaultComparator default constructor
 */
DefaultComparator::DefaultComparator()
{}

/**
 * DefaultComparator destructor
 */
DefaultComparator::~DefaultComparator() 
{}

/**
 * DefaultComparator::CompareParameter
 * Default implementation for function parameter comparison.
 */
bool DefaultComparator::CompareParameter(const HANodeIterator& basenode, 
                                         const HANodeIterator& currnode) const
{
    NodeTypeElementList baseelements;
    NodeTypeElementList currelements;

    // Read nodes of both parameters to elements:
    ReadElements(basenode, baseelements);
    ReadElements(currnode, currelements);

    return ValidateTypeElements(basenode, currnode, baseelements, currelements);
}
/**
 * DefaultComparator::CompareReturnValue
 * Default implementation for function return value comparison.
 */
bool DefaultComparator::CompareReturnValue( 
                                const HANodeIterator& basenode, 
                                const HANodeIterator& currnode) const
{
    // Get ids for the return type nodes:
    const XMLCh* basereturnid = basenode.GetAttribute(KXMLReturnsString);
    const XMLCh* currreturnid = currnode.GetAttribute(KXMLReturnsString);

    if( basereturnid == 0 || currreturnid == 0 )
    {
        // Functions should always have return value ID, but check it anyway.
        return CompareAttributes(   basenode,
                                    currnode,
                                    KXMLReturnsString,
                                    EOptionalTypeAttribute);
    }

    // Find the return type nodes...
    HANodeIterator basemethod(basenode);
    HANodeIterator currmethod(currnode);
    bool ret1 = basemethod.FindNodeById(basereturnid);
    bool ret2 = currmethod.FindNodeById(currreturnid);
    assert( ret1 && ret2 );

    //... and compare them
    return this->CompareParameter(basemethod, currmethod);
}

/**
 * DefaultComparator::ReadElements
 * Reads all nodes of a parameter to elements.
 * Parameter is splitted in elements as following examples show:
 * Example 1: const int& is splitted in elements const + int + &
 * XML structure is:
 *  - ReferenceType with attribute type="_a"
 *  - CVQualifiedType with attributes id="_a" and const="1" and type="_b"
 *  - FundamentalType with attributes id="_b" and name="int"
 *
 * Example 2: int ** is splitted in elements: int + * + *
 * XML structure is:
 *  - PointerType with attributes type="_c"
 *  - PointerType with attributes id="_c" and type="_d"
 *  - FundamentalType with attributes id="_d" and name="int"
 */
void DefaultComparator::ReadElements(const HANodeIterator& node, 
                                    NodeTypeElementList& elements ) const
{    
    elements.push_back(node.current);    
    if( node.GetAttribute(KXMLTypeString) )
    {
        // This parameter has more elements, so read next element:
        ReadElements(GetTypeNode(node), elements);
    }
}

// Just for debugging purposes...
void PrintElementList(const NodeTypeElementList& elements )
{
    NodeTypeElementList::const_iterator i = elements.begin();
    for( ; i != elements.end(); ++i )
    {
        cout << toString((*i)->getNodeName()) << endl;
    }
}

/**
 * DefaultComparator::ValidateTypeElements
 * Compares the nodes of the parameter in baseline and current elements
 */
bool DefaultComparator::ValidateTypeElements(   const HANodeIterator& basenode, 
                                                const HANodeIterator& currnode,
                                                const NodeTypeElementList& baseelements, 
                                                const NodeTypeElementList& currelements) const
{
    if( baseelements.size() != currelements.size())
    {
        return false;
    }

    // Loop through elements and check them one by one:
    for( size_t i = 0; i < baseelements.size(); ++i )
    {
        HANodeIterator baseIt(basenode);
        baseIt.current = baseelements[i];
        HANodeIterator currIt(currnode);
        currIt.current = currelements[i];
        if( !ValidateElement(baseIt, currIt))
        {
            return false;
        }
    }
    return true;
}

/**
 * DefaultComparator::ValidateElement
 * Compares one node of the parameter.
 */
bool DefaultComparator::ValidateElement(const HANodeIterator& basenode, 
                                        const HANodeIterator& currnode) const
{
    const XMLCh * basenodename = basenode->getNodeName();
    const XMLCh * currnodename = currnode->getNodeName();
    if( !Equals(basenodename, currnodename))
    {      
        // Node types did not match, however if this is really the case, 
        // mismatch is caught when comparing the actual declaration.
        // Here we just check that the names of the types match.
        const XMLCh* bname = basenode.GetAttribute(KXMLNameString);
        const XMLCh* cname = currnode.GetAttribute(KXMLNameString);
        if( !Equals(bname, cname) )
        {
            return false;
        }
    }

    if ( Equals(basenodename, KXMLFunctionTypeString) )
    {
        // Parameter is a function pointer, so compare their signatures:
        return GetTypeName(basenode) == GetTypeName(currnode);
    }

    if( Equals(basenodename, KXMLFundamentalTypeString) ||
        Equals(basenodename, KXMLTypedefString))
    {
        // Fundamental type or typedefed type, check fully qualified names.
        return CompareFqNames(basenode, currnode );
    }

    if(  Equals( basenodename, KXMLCvQualifiedTypeString ) )
    {
        // CvQualifiedType: Check that the constness match.
        return basenode.CheckForBooleanAttribute(KXMLConstString) ==
               currnode.CheckForBooleanAttribute(KXMLConstString);
    }

    if(  Equals( basenodename, KXMLArrayTypeString ) )
    {
        // Check array maximum size:
        return basenode.CheckForBooleanAttribute(KXMLMaxString) ==
               currnode.CheckForBooleanAttribute(KXMLMaxString);
    }

    if(  Equals( basenodename, KXMLPointerTypeString ) ||
         Equals( basenodename, KXMLReferenceTypeString ) )
    {
        // Just check that type names match 
        // (i.e. both are pointers or references)
        return Equals(basenodename, currnodename);
    }
    else
    {
        // None of the above, so let's try to get the type attributes.
        // If type attributes exist, they are checked in the next run.
        const XMLCh* btype = basenode.GetAttribute(KXMLTypeString);
        const XMLCh* ctype = currnode.GetAttribute(KXMLTypeString);

        if ( btype && ctype )
        {
            return true; // Type should be next in the list
        }
    }

    // No luck, just compare the fully qualified names (exact match).
    return CompareFqNames(basenode, currnode );
}

/**
 * DefaultComparator::GetTypeNode
 * Gets the node for the type of pointer, reference etc. node.
 */
HANodeIterator DefaultComparator::GetTypeNode(const HANodeIterator& node) const
{
    const XMLCh* type = node.GetAttribute(KXMLTypeString);    
    assert(type);

    HANodeIterator typenode(node);
    
    bool typefound = typenode.FindNodeById(type);    
    assert(typefound);

    return typenode;
}
/**
 * DefaultComparator::CompareFqNames
 * Checks whether the fully qualified names match.
 */
bool DefaultComparator::CompareFqNames(const HANodeIterator& basenode, 
                                       const HANodeIterator& currnode) const
{
    const XMLCh* basefqname = basenode.GetAttribute(KXMLBBCFQNameString);
    const XMLCh* currfqname = currnode.GetAttribute(KXMLBBCFQNameString);

    string bfq;
    string cfq;

    if( !basefqname )
        bfq = GenerateFullyQualifiedName(basenode);
    else
        bfq = toString(basefqname);

    if( !currfqname )
        cfq = GenerateFullyQualifiedName(currnode);
    else
        cfq = toString(currfqname);

    return bfq == cfq;
}
/**
 * DefaultComparator::CompareConstness
 * Checks whether the constness of the nodes match.
 */
bool DefaultComparator::CompareConstness(
                                    const HANodeIterator& basenode, 
                                    const HANodeIterator& currnode ) const
{    

    return basenode.CheckForBooleanAttribute(KXMLConstString) == 
           currnode.CheckForBooleanAttribute(KXMLConstString);
}
/**
 * ConstFilter
 * Constness filter. This class does not have as strict constness rules 
 * as the base class has. Implemented rules in this class:
 * 1. You can change non-const function parameter to const.
 * 2. You can change non-const method to const.
 * 3. You can change const return value to non-const.
 */
ConstFilter::ConstFilter()
{}

bool ConstFilter::CompareReturnValue(   const HANodeIterator& basenode, 
                                        const HANodeIterator& currnode ) const
{
    // Let's just switch the nodes and compare the nodes.
    // The parameter comparison for this class is implemented so, that
    // current platform's function parameter can be changed from non-const
    // to const. But since the rules for the function return value is
    // just the opposite, let's cheat the compare method by switching
    // the nodes:
    return DefaultComparator::CompareReturnValue(currnode, basenode);
}

/*
 * This comparator allows 'const' qualifier to be added to the type.
 */
bool ConstFilter::ValidateTypeElements( const HANodeIterator& basenode, 
                                        const HANodeIterator& currnode,
                                        const NodeTypeElementList& baseelements, 
                                        const NodeTypeElementList& currelements) const
{
    if( baseelements.size() > currelements.size())
        return false; 

    HANodeIterator baseIt(basenode);
    HANodeIterator currIt(currnode);

    NodeTypeElementList::const_iterator baseelementsIter = baseelements.begin();
    NodeTypeElementList::const_iterator currelementsIter = currelements.begin();

    while(  baseelementsIter != baseelements.end() && 
            currelementsIter != currelements.end() )
    {        
        baseIt.current = *baseelementsIter;        
        currIt.current = *currelementsIter;

        const XMLCh * basenodename = baseIt->getNodeName();
        const XMLCh * currnodename = currIt->getNodeName();

        bool currconst = currIt.CheckForBooleanAttribute(KXMLConstString);

        if( !Equals(basenodename, currnodename ) && 
            Equals( currnodename, KXMLCvQualifiedTypeString) &&
            currconst )
        {
            // const qualifier added to current platform's parameter, 
            // let's skip that and check next elements
            ++currelementsIter;
            continue;
        }
        else 
        {            
            if( !ValidateElement(baseIt, currIt) )
            {
                return false;
            }
        }

        ++baseelementsIter;
        ++currelementsIter;
    }

    if( currelementsIter != currelements.end() )
    {
        return false;
    }
    return true;
}

/**
 * It is acceptable to change a non-const function argument to const.
 * Changing the non-const function to const is also allowed.
 */
bool ConstFilter::CompareConstness(const HANodeIterator& basenode, 
                                   const HANodeIterator& currnode) const
{    
    if( DefaultComparator::CompareConstness(basenode, currnode) )
    {
        return true;
    }

    const XMLCh * basenodename = basenode->getNodeName();
    const XMLCh * currnodename = currnode->getNodeName();

    assert( basenodename && currnodename );

    bool baseconst = basenode.CheckForBooleanAttribute(KXMLConstString);
    bool currconst = currnode.CheckForBooleanAttribute(KXMLConstString);

    if( baseconst == currconst )
    {
        return true; // Exact match
    }
    if( currconst == true )
    {
        if(IsFunction(basenode) && Equals(basenodename, currnodename))
        {
            // It is allowed to change non-const function 
            return true;
        }
    }
    return false;
}




/**
 * ConstFilter2
 * Constness filter. This class does not have as strict constness rules 
 * as the base class has. Implemented rules in this class:
 * 1. You can change non-const function parameter to const and vice-versa.
 * 2. You can change non-const method to const and vice-versa.
 * 3. You can change const return value to non-const and vice-versa.
 */
ConstFilter2::ConstFilter2()
{}

bool ConstFilter2::CompareReturnValue(   const HANodeIterator& basenode, 
                                        const HANodeIterator& currnode ) const
{
    // Let's just switch the nodes and compare the nodes.
    // The parameter comparison for this class is implemented so, that
    // current platform's function parameter can be changed from non-const
    // to const. But since the rules for the function return value is
    // just the opposite, let's cheat the compare method by switching
    // the nodes:
    return DefaultComparator::CompareReturnValue(currnode, basenode);
}

/*
 * This comparator allows 'const' qualifier to be added or removed to the type.
 */
bool ConstFilter2::ValidateTypeElements( const HANodeIterator& basenode, 
                                        const HANodeIterator& currnode,
                                        const NodeTypeElementList& baseelements, 
                                        const NodeTypeElementList& currelements) const
{

    HANodeIterator baseIt(basenode);
    HANodeIterator currIt(currnode);

    NodeTypeElementList::const_iterator baseelementsIter = baseelements.begin();
    NodeTypeElementList::const_iterator currelementsIter = currelements.begin();

    while(  baseelementsIter != baseelements.end() && 
            currelementsIter != currelements.end() )
    {        
        baseIt.current = *baseelementsIter;        
        currIt.current = *currelementsIter;

        const XMLCh * basenodename = baseIt->getNodeName();
        const XMLCh * currnodename = currIt->getNodeName();

        bool currconst = currIt.CheckForBooleanAttribute(KXMLConstString);
        bool baseconst = baseIt.CheckForBooleanAttribute(KXMLConstString);

        if( !Equals(basenodename, currnodename) && 
             Equals( currnodename, KXMLCvQualifiedTypeString) && currconst) 
        { 
                // const qualifier added to current platform's parameter, 
                // let's skip that and check next elements
                ++currelementsIter;
                continue;
        }       
        else if( !Equals(basenodename, currnodename) && 
                 Equals( basenodename, KXMLCvQualifiedTypeString) && baseconst )
        {
                // const qualifier removed from the current platform's parameter, 
                // let's skip that and check next elements
                ++baseelementsIter;
                continue;
        }
        else 
        {            
            if( !ValidateElement(baseIt, currIt) )
            {
                return false;
            }
        }

        ++baseelementsIter;
        ++currelementsIter;
    }

    if( currelementsIter != currelements.end() )
    {
        return false;
    }
    return true;
}

/**
 * It is acceptable to change a non-const function argument to const and vice-versa.
 * Changing the non-const function to const and vice-versa is also allowed.
 */
bool ConstFilter2::CompareConstness(const HANodeIterator& basenode, 
                                   const HANodeIterator& currnode) const
{    
    if( DefaultComparator::CompareConstness(basenode, currnode) )
    {
        return true;
    }

    const XMLCh * basenodename = basenode->getNodeName();
    const XMLCh * currnodename = currnode->getNodeName();

    assert( basenodename && currnodename );

    bool baseconst = basenode.CheckForBooleanAttribute(KXMLConstString);
    bool currconst = currnode.CheckForBooleanAttribute(KXMLConstString);

    if( baseconst == currconst )
    {
        return true; // Exact match
    }
    if( currconst == true )
    {
        if(IsFunction(basenode) && Equals(basenodename, currnodename))
        {
            // It is allowed to change non-const function 
            return true;
        }
    }
    else if ( baseconst == true )
    {
        if(IsFunction(currnode) && Equals(basenodename, currnodename))
        {
            // It is allowed to change const function 
            return true;
        }
    }
    return false;
}





/**
 * Comparator factory holding the implemented comparators.
 * Singleton class.
 */
ComparatorFactory& ComparatorFactory::Instance()
{
    if( iInstance.get() == 0 )
        iInstance.reset(new ComparatorFactory());
    return *iInstance;
}

/**
 * Destructor
 */
ComparatorFactory::~ComparatorFactory() 
{
    ComparatorVector::iterator i = iComparators.begin();
    for( ; i != iComparators.end(); ++i )
    {
        delete *i;
    }
};
 
/**
 * ComparatorFactory::ComparatorFactory() 
 * Instantiates comparator objects. When adding new comparator, it should
 * be instantiated here.
 */
ComparatorFactory::ComparatorFactory() 
{    
    iComparators.push_back(new DefaultComparator());
    iComparators.push_back(new ConstFilter());
    iComparators.push_back(new ConstFilter2());
}

/**
 * ComparatorFactory::GetComparators()
 * Returns all instantiated comparator objects.
 */
ComparatorVector& ComparatorFactory::GetComparators()
{
    return iComparators;
}
