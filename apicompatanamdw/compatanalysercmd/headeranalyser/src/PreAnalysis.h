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


#ifndef PREANALYSIS_H_
#define PREANALYSIS_H_

#ifdef __WIN__
#pragma warning(disable:4786)
#endif
#include <list>
#include <xercesc/dom/DOM.hpp>
#include "HANodeIterator.h"

using namespace std;

XERCES_CPP_NAMESPACE_USE

/**
* Pre analysis is used for checking some frequently used properties (virtuality, derivability,..)
* of the classes to be used in node analysis.
*/
class PreAnalysis
{
public:

    //The analysis function implementing the pre analysis
    virtual void preAnalyse(HANodeIterator parsetree,const list<string> & filesToAnalyse,bool baseline)=0;

    //Destructor
    virtual ~PreAnalysis(){}
};

#endif
