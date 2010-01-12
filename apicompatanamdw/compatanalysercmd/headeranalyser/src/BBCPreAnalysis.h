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


#ifndef BBCPREANALYSIS_H_
#define BBCPREANALYSIS_H_

#ifdef __WIN__
#pragma warning(disable:4786)
#endif
#include <map>
#include <list>
#include <xercesc/dom/DOM.hpp>
#include "HANodeIterator.h"
#include "PreAnalysis.h"

using namespace std;

XERCES_CPP_NAMESPACE_USE

class BBCPreAnalysis: public PreAnalysis
{
public:
    /**
    * Strip filename and extension
    * @param parsetree absolute 
    * @param filesToAnalyse list of files to analyse
    * @param baseline true if baseline is being analysed
    */
    void preAnalyse(HANodeIterator parsetree,const list<string> & filesToAnalyse, bool baseline);    

    /**
    * Pre analyse for virtuality. To detect the virtuality of the class we need to 
    * check the methods and also the virtuality of the base classes.
    * @param classNode clas node to check 
    * @return true, if virtual
    */
    bool preAnalyseClassForVirtuality(HANodeIterator classNode);

    /**
    * Preanalyse class for derivability
    *
    * Check for derivability. The class is derivable iff:
    * 1. Has a public or protected explicitely declared exported constructor
    * 2. Has a public or protected inline constructor
    * In GCCXML:
    * 
    * Check methods of type "Constructor" 
    *
    * Constructor type / attribute:| artificial | explicit | inline | exported
    * --------------------------------------------------------------------------
    * implicite inline constructor |     x     |     x     |   x    |          
    * inline constructor           |           |    (x)    |   x    |          
    * exported constructor         |           |    (x)    |        |    x     
    * ----------------------------------------------------------------------------
    * @param classNode iterator class node to check
    */
    void preAnalyseClassForDerivability(HANodeIterator classNode);

    /**
    * Preanalyse class for inline functions
    * @param classNode iterator class node to check
    */
    void preAnalyseClassForInlineFunctions(HANodeIterator classNode);

    /**
    * Pre analyse class 
    * @param classNode iterator class node
    */
    void preAnalyseClass(HANodeIterator classNode);

    /**
    * Pre analyse and generate maps
    * @param rootnode  
    * @param baseline true, if baseline is analysed
    */
    void preAnalyseGenerateMaps(HANodeIterator rootnode, bool baseline);

    /**
    * Destructor
    */
    ~BBCPreAnalysis(){}

private:
    /**
    * Pre analyse class 
    * @param classNode class node to analyse
    */
	void preAnalyseClass(DOMNode* classNode);
};

#endif
