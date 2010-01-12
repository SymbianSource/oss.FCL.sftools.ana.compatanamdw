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


#ifndef NODEANALYSIS_H_
#define NODEANALYSIS_H_

#ifdef __WIN__
#pragma warning(disable:4786)
#endif
#include <list>
#include <xercesc/dom/DOM.hpp>
#include "HANodeIterator.h"

using namespace std;

XERCES_CPP_NAMESPACE_USE

class NodeAnalysis
{
public:
     /**
    * Finds node analyser
    * @param baseline baseline node
    * @return pointer NodeAnalysys object
    */
    static NodeAnalysis* FindNodeAnalyser(HANodeIterator baseline);

    typedef NodeAnalysis* (*Constructor)();

    /**
    * Finds node
    * @param nodetofind node to find
    * @param findfrom where to find node from
    * @return 0, if there was no issues
    */
    static DOMNode* findNode(HANodeIterator nodetofind, HANodeIterator findfrom);
public:

    /**
    * Finds node to analyse it
    * @param baseline baseline node
    * @param current current node
    * @return 0, if there was no issues
    */
    virtual int FindNodeAndAnalyse(HANodeIterator baseline,HANodeIterator current)=0;

    /**
    * Analyse
    * @param baseline baseline node
    * @param current current node
    * @param report report or not (default= true)
    * @return 0, if there was no issues
    */
    virtual int Analyse(HANodeIterator baseline,HANodeIterator current, bool report = true)=0;

    /**
    * Destructor
    */
    virtual ~NodeAnalysis(){}
};

#endif
