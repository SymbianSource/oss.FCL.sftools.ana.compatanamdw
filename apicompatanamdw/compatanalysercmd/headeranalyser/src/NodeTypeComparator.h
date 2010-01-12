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


#ifndef NODETYPECOMPARATOR_H
#define NODETYPECOMPARATOR_H

#include "HANodeIterator.h"

/**
 * Vector containing all the nodes of one C++ type.
 * Example: Type <code>const int&</code>
 * is represented with following NodeTypeElementList:
 * -----------------------------
 * | [2] FundamentalType -node | 
 * -----------------------------
 * | [1] CvQualifiedType -node |
 * -----------------------------
 * | [0] ReferenceType -node   |
 * -----------------------------
 */
typedef vector<DOMNode*> NodeTypeElementList;
#define CONSTFILTER_COMPARATOR 2
#define CONSTFILTER2_COMPARATOR 3
/**
 * NodeTypeComparator
 * Interface for function and function argument node type comparators. 
 * Classes implementing the <code>NodeTypeComparator</code> can be used to
 * compare function/method parameters, constness of a method and return 
 * value of the function/method.
 *
 * There can be several comparators, which have their own rules for 
 * validating the types. The <code>ComparatorFactory</code> -class 
 * instantiates the classes and it has an interface for getting all 
 * the available comparators.
 */
class NodeTypeComparator
{
public:
    /**
     * Compares single function parameter between the baseline and the current
     * platforms.
     * @param basenode Node of the baseline function argument
     * @param currnode Node of the current function argument
     * @return True if the arguments match, false otherwise.
     */
    virtual bool CompareParameter(  const HANodeIterator& basenode, 
                                    const HANodeIterator& currnode ) const = 0;
    /**
     * Compares the constness property of given function nodes.
     * @param basenode Node of the baseline function
     * @param currnode Node of the current function
     * @return True if the constness match, false otherwise.
     */
    virtual bool CompareConstness(  const HANodeIterator& basenode, 
                                    const HANodeIterator& currnode ) const = 0;
    /**
     * Compares the return values of the functions.
     * @param basenode Node of the baseline function
     * @param currnode Node of the current function
     * @return True if the return values match, false otherwise.
     */
    virtual bool CompareReturnValue(const HANodeIterator& basenode, 
                                    const HANodeIterator& currnode ) const = 0;

    /**
     * Compares the fully qualified names of the nodes.
     * @param basenode Baseline node, whose fully qualified name is compared.
     * @param currnode Current node, whose fully qualified name is compared.
     * @return True if the fully qualified names match, false otherwise
     */
    virtual bool CompareFqNames(const HANodeIterator& basenode, 
                                const HANodeIterator& currnode) const = 0;
};
/**
 * DefaultComparator
 * Default implemetation of the function comparator. Only exact matches are 
 * considered as matches.
 */
class DefaultComparator : public NodeTypeComparator
{
public:
    DefaultComparator();
    virtual ~DefaultComparator();

    /**
     * Reads the element nodes to <code>NodeTypeElementList</code> containers
     * and passes them for validation.
     * @param basenode Node for the baseline function or function argument
     * @param currnode Node for the current function or function argument
     * @return True if the parameter validation succeess, false otherwise
     */
    virtual bool CompareParameter(  const HANodeIterator& basenode, 
                                    const HANodeIterator& currnode ) const;   

    /**
     * Compares the fully qualified names of the nodes. Only exact match is 
     * allowed.
     * @param basenode Baseline node, whose fully qualified name is compared.
     * @param currnode Current node, whose fully qualified name is compared.
     * @return True if the fully qualified names match exactly.
     */
    virtual bool CompareFqNames(const HANodeIterator& basenode, 
                                const HANodeIterator& currnode) const;

    /**
     * Compares the <code>const</code> keyword between two nodes.
     * @param basenode Baseline node, whose constness is compared.
     * @param currnode Current node, whose constness is compared.
     * @return True if the <code>const</code> keywords match, false otherwise.
     */
    virtual bool CompareConstness(  const HANodeIterator& basenode, 
                                    const HANodeIterator& currnode) const;

    /**
     * Compares the return values of two functions. Allows only exact match.
     * @param basenode Node for the baseline function.
     * @param currnode Node for the current function.
     * @return True if the return values match, false otherwise.
     */
    virtual bool CompareReturnValue(const HANodeIterator& basenode, 
                                    const HANodeIterator& currnode ) const;

protected:
    /**
     * Gets the <code>HANodeIterator</code> pointing to the node, which is 
     * representing the type of the given node.
     * @param node Iterator pointing to the node, whose type node should 
     * be found.
     * @return Iterator pointing to the type node.
     */
    virtual HANodeIterator GetTypeNode(const HANodeIterator& node) const;

    /**
     * Reads elements of the type node to the given elements.
     * @param node Iterator pointing to the type node.
     * @param elements Node type elements are inserted in this container.
     */
    virtual void ReadElements(  const HANodeIterator& node, 
                                NodeTypeElementList& elements ) const;

    /**
     * Compares two element lists.
     * @param basenode Iterator pointing to the baseline node 
     * (e.g. function argument)
     * @param currnode Iterator pointing to the current node.
     * @param baseelements <code>NodeTypeElementList</code> containing the elements 
     * of the baseline node.
     * @param currelements <code>NodeTypeElementList</code> containing the elements
     * of the current node.
     * @return True if the elements match, false otherwise.
     */
    virtual bool ValidateTypeElements(const HANodeIterator& basenode, 
                                const HANodeIterator& currnode,
                                const NodeTypeElementList& baseelements, 
                                const NodeTypeElementList& currelements) const;

    /**
     * Validates one element of a <code>NodeTypeElementList</code>.
     * @param basenode Iterator pointing to the baseline type element's node.
     * @param currnode Iterator pointing to the current type element's node.
     * @return True if the elements match.
     */
    virtual bool ValidateElement(  const HANodeIterator& basenode, 
                                    const HANodeIterator& currnode) const;
};

/**
 * ConstFilter.
 * <code>NodeTypeComparator</code> which has more loose constness match
 * criterias than the <code>DefaultComparator</code>. It is allowed to 
 * change non-const function, function parameter or function return type
 * to const, if the function is not virtual and the type is not "complex",
 * e.g. pointer to pointer or reference to pointer.
 *
 * NOTE! This filter should be used only for non-virtual functions.
 */
class ConstFilter : public DefaultComparator
{
public:
    ConstFilter();
    
    /**
     * Allows changing the non-const function to const.
     */
    virtual bool CompareConstness(  const HANodeIterator& basenode, 
                                    const HANodeIterator& currnode) const;

    virtual bool CompareReturnValue(const HANodeIterator& basenode, 
                                    const HANodeIterator& currnode ) const;
protected:

    /**
     * Allows changing non-const "simple" type to const.
     */
    virtual bool ValidateTypeElements(const HANodeIterator& basenode, 
                                const HANodeIterator& currnode,
                                const NodeTypeElementList& baseelements, 
                                const NodeTypeElementList& currelements) const;

};


/**
 * ConstFilter2.
 * <code>NodeTypeComparator</code> which has more loose constness match
 * criterias than the <code>DefaultComparator</code>. It is allowed to 
 * change non-const function, function parameter or function return type
 * to const and vice-versa, if the function is not virtual and the type is not "complex",
 * e.g. pointer to pointer or reference to pointer.
 *
 * NOTE! This filter should be used only for non-virtual functions.
 */
class ConstFilter2 : public DefaultComparator
{
public:
    ConstFilter2();
    
    /**
     * Allows changing the non-const function to const and vice-versa.
     */
    virtual bool CompareConstness(  const HANodeIterator& basenode, 
                                    const HANodeIterator& currnode) const;

    virtual bool CompareReturnValue(const HANodeIterator& basenode, 
                                    const HANodeIterator& currnode ) const;
protected:

    /**
     * Allows changing non-const "simple" type to const and vice-versa.
     */
    virtual bool ValidateTypeElements(const HANodeIterator& basenode, 
                                const HANodeIterator& currnode,
                                const NodeTypeElementList& baseelements, 
                                const NodeTypeElementList& currelements) const;

};


/**
 * Container class for <code>NodeTypeComparator</code> instances.
 */
typedef vector<NodeTypeComparator*> ComparatorVector;

/**
 * ComparatorFactory
 * This singleton class instantiates and stores the comparator objects.
 */
class ComparatorFactory
{
public:
    /**
     * Returns the singleton instance of this class.
     * @return Reference to the instances of this class.
     */
    static ComparatorFactory& Instance();

    /**
     * Returns the container for the <code>NodeTypeComparator</code> objects.
     * @return Reference to the <code>ComparatorVector</code>.
     */
    ComparatorVector& GetComparators();

    /**
     * Destructor
     */
    ~ComparatorFactory();

private:

    /**
     * Private default constructor, as this is a singleton class.
     */
    ComparatorFactory();

    /**
     * Singleton instance of this class.
     */
    static std::auto_ptr<ComparatorFactory> iInstance;

    /**
     * Vector containing the <code>NodeTypeComparator</code> objects.
     */
    ComparatorVector iComparators;
};

#endif
