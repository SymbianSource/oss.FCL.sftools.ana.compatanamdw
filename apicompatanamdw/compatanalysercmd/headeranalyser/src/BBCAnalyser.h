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


#ifndef BBCANALYSER_H_
#define BBCANALYSER_H_

#ifdef __WIN__
#pragma warning(disable:4786)
#endif
#include <assert.h>
#include <map>
#include <list>
#include "CmdGlobals.h"
#include "ReportGenerator.h"
#include "XMLUtils.h"
#include "NodeIndex.h"
#include "HANodeIterator.h"

#include "HeaderAnalyser.h"
#include "PreAnalysis.h"
#include "NodeAnalysis.h"
#include "BBCPreAnalysis.h"

#include <xercesc/dom/DOM.hpp>

using namespace std;

XERCES_CPP_NAMESPACE_USE


/**
* The BBCAnalyser implements the HeaderAnalyser interface and includes the analysis 
* functionality.
*
* The BBCAnalyser includes two kinds of analysis. Firstly, some frequently used 
* properties of declarations are calculated and saved in XML document for usage
* in further analysis. These are implemented in classes implementing the 
* PreAnalysis interface.
*
* Secondly, the declarations are analyzed by classes that implement the
* NodeAnalysis interface. The idea is to have the top level NodeAnalysis to analyze
* all global declarations and delegate the complex declarations to other 
* NodeAnalysis classes for further analysis. This enables the problem partitioning
* in solvable units and keeps the analysis algorithms maintainable.
*/
class BBCAnalyser: public HeaderAnalyser
{
public:
    /**
    * Constructor
    * @param report reference to <code>ReportGenerator</code>    
    */ 
    BBCAnalyser(ReportGenerator & report);

    /**
    * Traverses recursively the parsed xml tree and analyses it.
    * @param baseline Pointer to the root of the baseline platform's xml output.
    * @param current Pointer to the root of the current platform's xml output.
    * @param filesToAnalyse List containing the filepairs to be analysed.
    * @return Error code, return code 0 means no error.
    */ 
    int analyseTrees(DOMNode* baseline, DOMNode* current, const list< pair<string,string> >& filesToAnalyse, const list<string>& aMacroFiles);

    /**
    * This method does the actual analysis recursively for the nodes of the parser's xml output. 
    * This method is called by <code>analyseTrees</code>.
    * @param baseline Iterator object pointing to the baseline platform's node.
    * @param current Iterator object pointing to the current platform's node.
    * @param filesToAnalyse List of the files to be analysed (ordered as pairs).
    * @return Error code, return code 0 means no error.
    */ 
    int nodeAnalyseTrees(HANodeIterator baseline, HANodeIterator current, const list< pair<string,string> >& filesToAnalyse);

    /**
    * Destructor
    */
    ~BBCAnalyser(){}

private:
    /**
    * Check if there is empty files
    * @param Iterator pointing to the root node of the parsers xml output
    * @param filesToAnalyse List of files to analyse
    * @return Vector containing the boolean values, that indicate is the file in the
    * position empty or not. For example, if <code>vector<bool>[0]==true</code>, then
    * the first file in <code>filesToAnalyse</code> is empty.
    */
	vector<bool> checkForEmptyFiles(HANodeIterator rootnode, const list<string>& filesToAnalyse, const list<string>& aMacroFiles);

private:
    //! Preanalyse object
	BBCPreAnalysis preAnalysis;
    
    //! Baseline node index
    NodeIndex iBaselineIndex;

    //! Current node index
    NodeIndex iCurrentIndex;

    //! Reference to ReporGenerator object
    ReportGenerator& iReport;
};


class UnderConstructionNodeAnalysis: public NodeAnalysis
{
public:
    /**
    * Constructor
    * @return pointer NodeAnalysis object
    */
    static NodeAnalysis* Construct();
public:

    /**
    * Find node and analyse it 
    * @param baseline to analyse
    * @param current to analyse
    * @return 0 if there was no issues
    */
    int FindNodeAndAnalyse(HANodeIterator baseline,HANodeIterator current);

    /**
    * Analyse nodes
    * @param baseline to analyse
    * @param current to analyse
    * @param report true if analysed results are reported (default=true)
    * @return 0 if no issues found
    */
    int Analyse(HANodeIterator baseline,HANodeIterator current, bool report = true);

    /**
    * Destructor
    */
    ~UnderConstructionNodeAnalysis(){};
};

#endif
