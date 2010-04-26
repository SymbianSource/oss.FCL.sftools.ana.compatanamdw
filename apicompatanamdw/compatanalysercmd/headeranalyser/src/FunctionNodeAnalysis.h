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


#ifndef FUNCTIONNODEANALYSIS_H_
#define FUNCTIONNODEANALYSIS_H_

#ifdef __WIN__
#pragma warning(disable:4786)
#endif
#include <xercesc/dom/DOM.hpp>
#include "HANodeIterator.h"
#include "NodeAnalysis.h"

using namespace std;

XERCES_CPP_NAMESPACE_USE

template <TIssueType IssueType>
void AddIssueFunction(const HANodeIterator* self,TIssueIdentity funcType, const HANodeIterator& ignorenode, int lineNo, 
					  const string& issueloc, const XMLCh* fileid=NULL)
{
	switch (funcType)
	{
	case EIssueIdentityExportedFunction:
		AddIssue<EIssueIdentityExportedFunction,IssueType>(self,ignorenode,lineNo,issueloc,fileid);
		break;
	case EIssueIdentityInlineFunction:
		AddIssue<EIssueIdentityInlineFunction,IssueType>(self,ignorenode,lineNo,issueloc,fileid);
		break;
	default:
		assert(false);
		break;

	};

}

/**
* Changes in function signatures are analyzed. Any change in the signature of an
* accessible function is  considered to be a binary break. 
*/
class FunctionNodeAnalysis: public NodeAnalysis
{
public:
    /**
    * Constructor
    * @return pointer NodeAnalysis object
    */
    static NodeAnalysis* Construct();
public:

    FunctionNodeAnalysis();

    /**
    * Finds node to analyse it
    * @param baseline baseline node
    * @param current current node
    * @return 0, if there was no issues
    */
    int FindNodeAndAnalyse(HANodeIterator baseline,HANodeIterator current);

    /**
    * Analyse
    * @param baseline baseline node
    * @param current current node
    * @param report report or not (default= true)
    * @return 0, if there was no issues
    */
    int Analyse(HANodeIterator baseline,HANodeIterator current, bool report = true);

    /**
    * Destructor
    */
    ~FunctionNodeAnalysis(){}
    
private:
    //! Type of function found 
	TIssueIdentity iFuncType;
};

#endif
