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


#ifndef UNIONNODEANALYSIS_H_
#define UNIONNODEANALYSIS_H_

#ifdef __WIN__
#pragma warning(disable:4786)
#endif
#include <xercesc/dom/DOM.hpp>
#include "HANodeIterator.h"
#include "ClassNodeAnalysis.h"

using namespace std;

XERCES_CPP_NAMESPACE_USE

class UnionNodeAnalysis: public ClassNodeAnalysis
{
public:
    /**
    * Constructor
    * @return pointer NodeAnalysis object
    */
    static NodeAnalysis* Construct();
public:
    /**
    * Finds node to analyse it
    * @param baseline baseline node
    * @param current current node
    * @return 0, if there was no issues
    */
    int FindNodeAndAnalyse(HANodeIterator baseline,HANodeIterator current);

    /**
    * Constructor    
    */
	UnionNodeAnalysis();

    /**
    * Destructor
    */
    ~UnionNodeAnalysis(){}

protected:
    /**
    * Compare base sizes
    * @param baseline to which to compare
    * @param current what to compare
    * @param bfields 
    * @param cfields 
    * @param report if true finding are reported
    * @return 0 meaningless with union as it can not be derived
    */ 
	virtual int compareBaseSizes(HANodeIterator baseline, HANodeIterator current, 
								 const NodeIndex::dtable_t& bfields, const NodeIndex::dtable_t& cfields, 
								 bool report);

    /**
    * Compare virtual functions
    * @param baseline baseline HANodeIterator 
    * @param current current HANodeIterator
    * @param bvirtualMethods vector of baseline virtual methods
    * @param cvirtualMethods vector of current virtual methods
    * @param report if true finding are reported
    * @return true if match found
    */ 
	virtual int compareVirtualFunctions(HANodeIterator baseline,HANodeIterator current, 
                                                  const vector<DOMNode*>& bvirtualMethods, 
												  const vector<DOMNode*>& cvirtualMethods, 
                                                  bool report);
};

#endif
