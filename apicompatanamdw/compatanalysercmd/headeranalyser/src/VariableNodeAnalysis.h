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


#ifndef VARIABLENODEANALYSIS_H_
#define VARIABLENODEANALYSIS_H_

#ifdef __WIN__
#pragma warning(disable:4786)
#endif
#include <xercesc/dom/DOM.hpp>
#include "HANodeIterator.h"
#include "NodeAnalysis.h"


using namespace std;

XERCES_CPP_NAMESPACE_USE


/**
* The constants are analyzed for changes in initialization values. Any change in
* an initialization value is considered a binary break.
*/ 
class VariableNodeAnalysis: public NodeAnalysis
{
public:
    /**
    * Constructor
    * @return pointer NodeAnalysis object
    */
    static NodeAnalysis* Construct();
public:

    /**
    * Finds node and analyse it
    * @param baseline baseline node
    * @param current current node
    * @return 0, if there was no issues
    */
    int FindNodeAndAnalyse(HANodeIterator baseline,HANodeIterator current);

    /**
    * Analyse node for variables
    * @param baseline baseline node
    * @param current current node
    * @param report report or not (default= true)
    * @return 0, if there was no issues
    */
    int Analyse(HANodeIterator baseline,HANodeIterator current, bool report = true);

    /**
    * Destructor
    */
    ~VariableNodeAnalysis(){}
};

#endif
