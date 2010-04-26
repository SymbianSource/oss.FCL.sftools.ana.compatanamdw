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


#ifndef __ANALYSER_H__
#define __ANALYSER_H__

#include "CmdGlobals.h"
#ifdef __WIN__
#pragma warning(disable:4786)
#endif

#include <string>
#include <vector>
#include <map>
#include <list>

#include <xercesc/dom/DOM.hpp>
#include "ReportGenerator.h"
#include "AnalyserParams.h"
#include "PlatformData.h"

class CommandLine;
class CPPParser;

using namespace std;
XERCES_CPP_NAMESPACE_USE

typedef pair<string,string> stringpair;
typedef vector<string> stringvector;
typedef map<string,string> stringmap;
typedef stringvector::const_iterator StringVecIterC;
typedef stringmap::const_iterator StringMapIterC;
typedef stringvector::iterator StringVecIter;
typedef stringmap::iterator StringMapIter;
typedef pair<Header*, Header*> HeaderPair;
typedef vector<HeaderPair> PlatformHeaders;

/**
 * LessStringPair
 * This function returns true if the stringpair lhs is less than the rhs.
 */
inline bool LessStringPair( const stringpair& lhs, const stringpair& rhs )
{
    if( lhs.first == rhs.first )
        return lhs.second < rhs.second;
    
    return lhs.first < rhs.first;
}

template<class TYPE> struct RemoveTrailingDirSeparator : public unary_function<TYPE, void>{} ;
/**
 * RemoveTrailingDirSeparator
 * Template function which removes the trailing dir separator from the filename.
 */
template<> struct RemoveTrailingDirSeparator<stringpair> : public unary_function<stringpair, void>
{
    void operator() (stringpair& x) 
    {        
        if( x.first.at(0) == DIR_SEPARATOR )
        {
            x.first.erase(0,1);
        }        
        if( x.second.at(0) == DIR_SEPARATOR )
        {
            x.second.erase(0,1);
        }
    }
};

struct StructMember
{
	string elementName;
	string elementType;
	string elementValue;
	int lineNo;
};

struct StructElement
{
	string structName;
	vector<StructMember>members; // pair<memType,memNeme>
	int lineNo;
};
struct EnumMember
{
	string enumMemName; // mem name
	string enumVal; // memvalue
	int lineNo;
};
struct EnumElement
{
	string enumName;
	vector<EnumMember> enums;
	int lineNo;
};

struct MacroElement
{
	string macroName; // pair<macro name , macro value>
	string macroVal;
	int lineNo;
};

struct ResourceContent
{
	string RHFileName;
	vector<StructElement> structList;
	vector<EnumElement> enumList;
	vector<MacroElement> macroList;
};


/**
* The parameters given to Headeranalyser are stored in in this class.
* Analyser class also coordinates the operation of other components and 
* handles the environment variables handling.
*/
class Analyser 
{
public:
    /**
    * Constructor
    * @param args Pointer to commanline arguments
    * @param argc Argument count
    */
    Analyser(char** args, int argc);
    
    /**
    * Constructor
    */
    Analyser();
    
    /**
    * Destructor
    */ 
    ~Analyser();

public:
    /**
    * Does the actual analyse of headers and creates a analysis report.
    * @return Error code, return code 0 means no error.
    */ 
    int analyse();

    /**
    * Check files in dir
    * @param baselineFile Baseline platform's file to be analysed
    * @param currentFile Current platform's file to be analysed
    * @param reportfile The name of the report file
    * @return Error code, return code 0 means no error.
    */ 
    //int analyse(string baselineFile, string currentFile, string reportfile);

    /**
    * Starts analysing the headers by passing the parsed trees to analyser
    * components.
    * @param baseline Pointer to the root of the tree parsed from the baseline
    * platform
    * @param current Pointer to the root of the tree parsed from the current
    * platform
    * @param files Headerfiles to be analysed
    * @param report Reference to a <code>ReportGenerator</code> object
    * @return Error code, return code 0 means no error.
    */ 
    int analyseTrees(DOMNode* baseline, DOMNode* current, const list< pair<string,string> >& files, ReportGenerator & report);

    /**
    * Analyse bundle of files.  Bundle size is between 1- 9999.
    * 
    * @param basefilenames  Bundle of filenames in baseline platform
    * @param curfilenames Bundle of filenames in current platform
    * @param report Reference to <code>ReportGenerator</code>
    * @param issues Number of issues found
    * @return Returns true, if the analysis was successful and no
    * exceptions were caught.
    */ 
    bool AnalyseBundle( const stringvector& basefilenames, 
                        const stringvector& curfilenames, 
                        ReportGenerator& report, 
                        int& issues, 
                        CPPParser* baseParser = 0,
                        CPPParser* currParser = 0,
                        stringvector* basecompileset = 0,
                        stringvector* currcompileset = 0);


private:

    // base type
    enum basetype { 
        EBase=0, 
        ECurrent 
    };

    /**
	* guard exists. checks for existence of "include" guards in the set of files
	* @param aFiles, set of files to be evaluated
	* @param aGuard, include guard returned for aFile
	* @return boolean value indicating existence of "include" guards
	*/
	bool guardExists(const string& aFile, string& aGuard);

	/**
	* Validate Headers. validates headers for automatic include guard inclusion
	* this scans both the pairs of headers passed as arguments
	* it creates a seperate headers pair list of those that do not have include guards.
	* @param aFiles, set of files to be evaluated
	* @param aUnsuccessful, set of files without include guards
	*/
	void validateHeaders(vector<pair<string, string> >& aFiles, vector<pair<string, string> >& aUnsuccessful);

	/**
    * Read parameters. readParameters should be called so that first is called 
    * baseline command  and after that current command, otherwise it
    * doesn't work.
    * @param type Platform type, either baseline or current.
    * @param files List of files
    * @param forcedheaders List of forced headers given in commandline arguments
    */ 
    void readParameters(basetype type, list<pair<string,string> >& files, string& forcedheaders);

    /**
    * Finds a replacement for a given baseline header if any. Tries to find an
    * entry for the given <code>aFile</code> and returns an <code>std::pair</code>
    * containing original (baseline) filename and the replacing filename.
    * @param aFile String pair containing filename to be checked.
    * @param aReplaceMap Map containing the files to be replaced with the replacing ones.
    * @param aCurrentFiles List of the current platforms headerfiles.
    * @return Pair containing the baseline header's name as a first string and the
    * replacing name as a second string.
    */ 
    pair<string, string> processFileReplaces(pair<string, string>& aFile, const stringmap& aReplaceMap, list<pair<string, string> >& aCurrentFiles);

    /**
    * Explodes the replace list (a string) into a map.
    *
    * String syntax is: 
    *     original filename>replacement file;original filename>replacement;...
    * 
    * Original filename must refer to the baseline file that has been
    * replaced with replacement file in the current version; original
    * filename must not contain a path, just the simple filename.
    * 
    * Replacement filename must contain the full path of the current
    * version file that replaces the baseline file (original filename).
    *
    * @param aReplaceList Value of a commandline argument containing the file replacements.
    * @param aReplaceMap Reference to the map in which the headerfile pairs are populated.
    */ 
    void createReplaceMap(const string& aReplaceList, stringmap& aReplaceMap);

    /**
    * Checks file differencies
    * @param aFiles Files to check
    * @param aMismatches Mismatches found
    */ 
    void fileDiffs(vector<pair<string, string> >& aFiles, list<string>& aMismatches);

    /**
    * Gets filename without path
    * @param aFilename Original filename (with or without the path).
    * @return Plain filename with the path stripped off.
    */ 
    string getFilenameWithoutDir(const string& aFilename);

    /**
    * Validates and processes given commandline parameters.
    * @return 0, if processing succeeds. 
    */ 
    int processParameters();

    /**
    * Tests if the file is available
    * @param map Map of files
    */ 
    //void testFileAvailability(stringmap map);

    /**
    * Merges baseline and current files into one vector.
    * @param aBasefiles    List of baseline files.
    * @param aCurrentfiles List of current files.
    * @param aReplaceList Value of a commandline argument containing the file replacements.
    * @param aMatches Vector in which the matching files are returned.
    */ 
    void MergeFiles(const list<pair<string, string> >& aBasefiles, list<pair<string, string> >& aCurrentfiles,
                    const string& aReplaceList, vector<pair<string, string> >& aMatches);

    /**
    * Check files in dir
    * @param allfiles list of files to check
    * @param sets 
    * @return list pair of files
    */ 
    void diffs( const list<pair<string, string> >& allfiles, 
                const list<pair<string, string> >& sets,
                list<pair<string, string> >& result);

    /**
    * Get the actual name of a file.
    * @param sets 
    * @return list pair of files
    */ 
    list<stringpair > canonicalizeFilename(list<pair<string,string> >& sets);

    /**
    * Check and fix bundlesize parameter value
    * Show warnig, if the value is over warning level.
    * @return bundlesize
    */ 
    int handleBundlesizeParam();

    /**
    * Get replace parameter
    * @return string of replace files
    */ 
    string getReplaceParam();

	 /**
    * To Initailze iBasePlatformData and iProductPlatformData 
    * and set all the headers' status  provided for analyse to 'HDR_STATUS_TO_BE_ANALYZED'.
    */
    void InitializePlatforms(PlatformHeaders& pfHeaders, vector<pair<string, string> >& headers, vector<pair<string, string> >& excludeheaders, vector<pair<string, string> >& resourcevector);

	/**
	* To analyse all the provided headers with system include paths and additional dependent headers.
	*/
    void AnalyzePlatforms(PlatformHeaders& pfHeaders, PlatformHeaders& unsuccessfulHeaders, ReportGenerator& report, int& issues, bool createThread);

	/**
	* To analyse header with default parameters.
	*/
    void AnalyseHeaders(const vector<pair<string, string> >& headerList, int bundlesize, ReportGenerator& report, int& issues, int& compErrors);
    
    /**
    * Wrapper function to analyse all files in a component in separate thread
    * 
    * @param report Reference to <code>ReportGenerator</code>
    * @param issues Number of issues found
    * @param baseParser CPPParser object
    * @param currParser CPPParser object
    * @param pfHeaders Reference to PlatformHeaders
    * @param unsuccessfulHdrs Reference to unsuccessful PlatformHeaders
    */
    void Analyser::Wrapper( ReportGenerator& report,
                            int& issues,
                            CPPParser baseParser,
                            CPPParser currParser,
                            PlatformHeaders& pfHeaders,
                            PlatformHeaders& unsuccessfulHdrs
                           );
                           
		/**
    * Wrapper function to analyse group of files in a component individually in different thread
    *
    * @param filenames Vector of filenames to be analysed individually
    * @param pfHeaders Reference to PlatformHeaders
    * @param unsuccessfulHdrs Reference to unsuccessful PlatformHeaders 
    * @param report Reference to <code>ReportGenerator</code>
    * @param issues Number of issues found
    */
    void Analyser::Wrapper2(stringvector filenames, PlatformHeaders& pfHeaders, PlatformHeaders& unsuccessfulHeaders, ReportGenerator& report, int& issues);

	/**
	* To analysis of .rh file, using text parser.
	* resourcevector - list of baseline and current .rh pair
	* icludes- any included file other than .rh will be returned
	* report - Report pointer to fill issues in report
	*/
	void ParseAndCompareResourceFiles(vector<pair< string, string> >& resourcevector, ReportGenerator& report);
	
	/**
	* Get list of enums, structs and macros in ResourceContent, present in one .rh file,  using text parser.
	* includes -  returns list of .rh files included in current analyzed .rh file
	*/	
	void getElementListFromRHFile(std::ifstream& RHFile,ResourceContent& resource, vector<string>& includes );

	/**
	* Comapre baseline and current resources filled in ResourceContent data stucture.
	* report - Report pointer to fill issues in report
	*/		
	void compareResources(ResourceContent& baseResource, ResourceContent& curResource, ReportGenerator& report);

private:

    //! Pointer to Commandline object
    CommandLine*                 iCmdLine;

    //! Pointer to CPPParser object
    CPPParser*                   iCPPParser;

    //! count of analysed files
    int                          iAnalysedFileCount;

    //! true if the header set is given with SET parameter
    bool                         iHeaderSetInUse;

    //! count of files
    list<pair<string, string> > iFiles;

    //! count of files
    list<pair<string, string> > iFiles2;

    //! String containing forced baseline file names
    string                      iForcedBaselineHeaders;

    //! String containing forced current file names
    string                      iForcedCurrentHeaders;

    //! Parameter to analyser
    AnalyserParams              iParams;

    //! Reference to  ReportGenerator
    ReportGenerator             iReport;

    //! List of not removed files
    list<string>                iNotRemovedFiles;
    
    //! Files with macros
    list<string>				iMacroFiles;

    //! Name of the macrofile
    string						iCompErrTxt;
	
	//! Resource File Already Anaylyzed

	vector<pair<string, string> >   iRHFile_Analyzed;

	
    //! Pointer Variable to store base platform data
    PlatformData* iBasePlatformData;

    //! Pointer Variable to store product platform data
    PlatformData* iProductPlatformData;

    //! Flag to check base platformdata's existence
    bool iUseBaselinePlatformData;    

    //! Flag to check product platformdata's existence
    bool iUseCurrentPlatformData;

    //! Flag set to be true,if 2nd time analyze with single header required
    bool iOnlySystemIncludeRequired;

    //! Headers to be analyzed in baseline platform
    stringvector iBaseFilenames; 
    
    //! Headers to be analyzed in product platform
    stringvector iCurrFilenames; 
    
    //! Files without include guards need to be compiled individually
    PlatformHeaders iInvalidFiles; 
    
    //! Additional headers needed to compile baseline
    stringvector iBaseIncludes;  
    
    //! Additional headers needed to compile product
    stringvector iCurrIncludes;  

	//! False by default. If mentioned then use thread. Set the bool to true.
	bool iUseThread;

};

#endif
