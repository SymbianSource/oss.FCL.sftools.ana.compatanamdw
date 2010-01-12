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


#ifndef __MACRO_ANALYSER_H__
#define __MACRO_ANALYSER_H__
#include <map>
#include <string>
#include <list>
#include "TChange.h"
#include "CPPParser.h"
#include "AnalyserParams.h"

using namespace std;


/**
* The MacroAnalysis class analyses differences between the baseline and 
* the current version macro definitions and adds issues to 
* the ReportGenerator.
*/
class MacroAnalyser
{
public:
    /**
    * Constructor
    *
    * @param filebase base file to analyse
    * @param filecurrent current file to analyse
    * @param basebundle base header bundle used in analyse
    * @param currentbundle current header bundle used in analyse
    */ 
    MacroAnalyser(string filebase, string filecurrent, vector<string> basebundle, vector<string> currentbundle);


    /**
    * Destructor
    */
    ~MacroAnalyser(void);

    /**
    * Do the whole analysing
    */
    void Analyse(list<string>& aMacroFiles);

    /**
    * Get removed macros
    * @return map of removed macros
    */
    map<string, TChange<list<pair<string,string> > > >& getRemoved();

    /**
    * Get changed macros
    * @return map of changed macros
    */
    map<string, TChange<map<string, pair<pair<string, string>,string> > > >& getChanged();

    /**
    * Get base duplicates
    * @return map of duplicates in base headers 
    */
    map<string, vector<pair<string,string> > >& getBaseDuplicates();

    /**
    * Get current duplicates
    * @return map of duplicates in current headers 
    */
    map<string, vector<pair<string,string> > >& getCurrentDuplicates();

    /**
    * Find macros
    * @param aLine line to search
    * @return pair of macros found
    */
    static pair<string,string> FindMacro(string aLine);

private:
    /**
    * Parses macros
    * @param aFile the file to parse from
    * @param bundlefiles bundle of headers to parse
    * @param aRemoved pointer to removed items map
    * @param aAddToRemoved add findings to removed, if true (default=NULL)
    * @return map of duplicates in current headers (default=false)
    */
    map<string, list<pair<pair<string, string>,string> > >  parseMacros(ifstream& aFile, vector<string>& bundlefiles, map<string, TChange<list<pair<string,string> > > >* aRemoved = NULL, bool aAddToRemoved = false);

    /**
    * Find duplicates
    * @param basefilename baseline filename
    * @param currentfilename currentline filename
    * @param aBaseline baseline headers
    * @param aCurrent currentline headers
    * @param aRemovedList list of removed items
    * @param baselinedup baseline duplicates
    * @param currentdup current duplicates
    * @return true if duplicates are found
    */
    bool findDuplicates(const string& basefilename, const string& currentfilename, list<pair<pair<string, string>,string> >& aBaseline, 
		list<pair<pair<string, string>,string> >& aCurrent, TChange<list<pair<string,string> > >& aRemovedList, 
		map<string, vector<pair<string,string> > >& baselinedup, map<string, vector<pair<string,string> > >& currentdup);
private:

    //! Base header to check
    string iBaseFile;

    //! Current header to check
    string iCurrentFile;

    //! Changed macros list
    map<string, TChange<map<string, pair<pair<string, string>,string> > > > iChanged;

    //! Map of removed items
    map<string, TChange<list<pair<string,string> > > > iRemoved;

    //! Base duplicate items
    map<string, vector<pair<string,string> > > iBaseDuplicates;

    //! Current duplicate items
    map<string, vector<pair<string,string> > > iCurrentDuplicates;

    //! Bundle of base files
    vector<string> iBaseBundle;

    //! Bundle of current files
    vector<string> iCurrentBundle;
    
    //! List of not removed files
    list<string> iNotRemovedFiles;

    //! Parameter to analyser
    AnalyserParams iParams;

};
#endif
