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


#ifndef HEADERANALYSER_H_
#define HEADERANALYSER_H_

#ifdef __WIN__
#pragma warning(disable:4786)
#endif
#include <list>
#include <xercesc/dom/DOM.hpp>

#include "HANodeIterator.h"

using namespace std;

XERCES_CPP_NAMESPACE_USE

class HeaderAnalyser
{

public:    
    /**
    * Analys baseline and currentline trees
    * @param baseline DOMNode pointer baseline
    * @param current DOMNode pointer current
    * @param filesToAnalyse list pair of files to analyse
    * @return 0, if successful
    */
    virtual int analyseTrees(DOMNode* baseline, DOMNode* current, const list< pair<string,string> >& filesToAnalyse, const list<string>& aMacroFiles)=0;

    /**
    * Analyse baseline and currentline trees
    * @param baseline HANodeIterator to baseline
    * @param current HANodeIterator to current
    * @param filesToAnalyse list pair of files to analyse
    * @return 0, if successful
    */
    virtual int nodeAnalyseTrees(HANodeIterator baseline, HANodeIterator current,const list< pair<string,string> >& filesToAnalyse)=0;

    /**
    *Destructor
    */
    virtual ~HeaderAnalyser(){};
};
#endif
