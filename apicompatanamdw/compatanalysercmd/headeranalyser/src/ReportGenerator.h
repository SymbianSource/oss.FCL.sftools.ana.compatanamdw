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


#ifndef __REPORT_GENERATOR_H__
#define __REPORT_GENERATOR_H__

#include "CmdGlobals.h"

#include <string>
#include <map>
#include <vector>

#include "ReportIssue.h"

using namespace std;

XERCES_CPP_NAMESPACE_USE

/**
* The ReportGenerator defines an issue reporting interface for the analysis 
* to use. It defines issue type IDs and issue severities and constructs 
* the XML document based on the reported issues. The ReportGenerator also 
* implements the saving of the resulting XML document to the file system.
*/
class ReportGenerator
{
public:
    /**
    * Destructor
    */ 
    ReportGenerator(string aOutputFile="");

    /**
    * Destructor
    */ 
    ~ReportGenerator();

public:
    /**
    * Set style sheet settings
    * @param aXSLFilename style sheet file
    * @param aIncludeInXML true if to be included in XML
    */ 
    void setXSL(string aXSLFilename, bool aIncludeInXML);

    /**
    * Set DTD (Document Type Definition ) usage
    * (method not used)
    * @param aDTDFilename DTD filename
    * @param aIncludeInDTD include DTD in XML
    */
    void setDTD(string aDTDFilename, bool aIncludeInDTD);

    /**
    * Start reporting, initalize XML-parser and create DOM document
    */
    void startReport();
    
    /**
    * Finish report, dump DOM to file
    */
    void finishReport();
    
    /**
    * Load strin tables
    * @param aFilename if to be included in XML
    */
    void loadStringTables(string aFilename);
    
    /**
    * Set command line parameters
    * @param aParms map of command line parameters
    */
    void setCmdLineParms(map<string, string> aParms);

    /**
    * Set base and currentline versions
    * @param aBaseline baseline version
    * @param aCurrent current version
    */
    void setVersions(string aBaseline, string aCurrent);

    /**
    * Adds issue to report
    * @param aIssue issue to report
    * @return the issue id, -1 if the adding was not successful
    */
    int addIssue(ReportIssue* aIssue);

    /**
    * Adds issue to the report. This node is marked as the cause for the issue
    * @param aFile header file
    * @param aFQName fully qualified name of the node
    * @param aIdentityId  identity= Class, ExportedFunction, Enumeration, etc.
    * @param aTypeId  what was happened ( something was removed, addded, changed..) 
    * @param aBCSeverityId how severe the issue was for binary compatibility
    * @param aSCSeverityId how severe the issue was for source compatibility
    * @param aIgnoreInformation reason to ignore
    * @param aLineNumber line number of the issue (0 always)
    * @param aCompareFileName compare file
	* @param aCompilationError compilation error reason
    * @return the issue id, -1 if the addition was not successful
    */
    int addIssue(const string& aFile, 
                const string& aFQName, const TIssueIdentity& aIdentityId, 
                const TIssueType& aTypeId, const TBCSeverity& aBCSeverityId, 
                const TSCSeverity& aSCSeverityId, const string& aIgnoreInformation,
                int aLineNumber, const string& aCompareFileName, const string& aCompilationError, bool alineNoNeeded = true);
private:
    /**
    * Preprocess issue list. Remove removed subclasses and merges similar issues
    * of the same function
    */
	void preprocessIssueList();

    /**
    * Preprocess issue list.
    */
	TIssueIdentity functionMapping(const vector<TIssueIdentity> & ids);

    /**
    * Merges similar issues of the same function
    */
	void mergeFunctionIssues();
    
    /**
    * Removes duplicates from the issue list, merges the different functions
    */
	void removeRemovedSubClasses();

    /**
    * Dump XSL data to file (not used)
    */
	void dumpXSLToFile();

    /**
    * Dump DTD data to file (not used)
    */
    void dumpDTDToFile();

    /**
    * Dump DOM data to file
    */
    void dumpDOMToFile();

    /**
    * Genarate version id nodes
    */
    void generateVersionIdNodes();

    /**
    * Initialise DOM
    */
    void initialiseDOM();

    /**
    * Uninitialize DOM
    */
    void uninitialiseDOM();

    /**
    * Generate issue list
    */
    void generateIssueList();

    /**
    * Generate issues for header
    */
    //void generateIssuesForHeader();

    /**
    * Get given commandline parameter value
    */
    string getCmdLineParm(string aParm);

    /**
    * Create documentation URL string
    */
    string createDocumentationUrlString(string element);

    /**
    * Create node with the given name
    * @return aName node name
    * @return pointer to DOMElement
    */
    DOMElement* createOpenNode(const char* aName);

    /**
    * Create node to hold report header data
    * @return pointer to DOMElement
    */
    DOMElement* createHeaderNode();

    /**
    * Create node to hold list of issues found
    * @return pointer to DOMElement
    */
    DOMElement* createIssueListNode();

    /**
    * Create issue node
    * @return pointer to DOMElement
    */
    DOMElement* createIssueNode(ReportIssue* aIssue);

    /**
    * Create headerfile node
    * @return the pointer to DOM node
    */
    DOMElement* createHeaderFileNode();

    /**
    * Create time stamp node
    * @return pointer to DOMElement
    */
    DOMElement* createTimestampNode();

    /**
    * Create text node
    * @param aNodeName name of the node
    * @param aNodeText text of the node
    * @return pointer to DOMElement
    */
    DOMElement* createSimpleTextNode(const char* aNodeName, const char* aNodeText);

    /**
    * Create text node
    * @param aNodeName name of the node
    * @param aInteger converted to string
    * @return pointer to DOMElement
    */
    DOMElement* createSimpleTextNode(const char* aNodeName, const int aInteger);
    
    /**
    * Create text node
    * @param aNodeName name of the node
    * @param aNodeText text of the node
    * @return pointer to DOMElement
    */
    DOMElement* createSimpleTextNode(const char* aNodeName, const XMLCh* aNodeText);

	/**
    * Create attribute node
    * @param aNodeName name of the node
    * @param aNodeAPI attribute value (API name) of the node
    * @param aNodeCategory attribute value (API category) of the node
    * @return pointer to DOMElement
    */
	DOMElement* createAPIAttributeNode(const char* aNodeName, const char* aNodeAPI,const char* aNodeCategory);

    /**
    * Create commandline node node. The node consists of commandline parameters.
    * @return pointer to DOMElement
    */
    DOMElement* createCmdLineNode();
        
    /**
    * Create parameter node
    * @param aKey parameter key
    * @param aValue parameter key value
    * @return pointer to DOMElement
    */
    DOMElement* createParmNode(const char* aKey, const char* aValue);
    
    /**
    * Create issue node
    * @return pointer to DOMElement
    */
    DOMElement* createIssueNode(ReportIssue& aIssue);
    
    /**
    * Create severity node
    * @return pointer to DOMElement
    */
    //DOMElement* createSeverityNode(const int aId);
    DOMElement* createSeverityNode();
    
    /**
    * Append children to node
    * @param aParent parent node
    * @param aChildren children to append
    */
    void appendChildrenToNode(DOMElement* aParent, const vector<DOMElement*>& aChildren);

    // START -- Support for file checksum and comments

    /**
    * Calculate file CRC.
    * @param aFilename file to calculate
    * @param aCrcResult CRC value calculated
    */    
    void getFileCRC( const char* aFilename, char* aCrcResult );

    /**
    * Get issue CRC
    * @param aIssueIdsVector vector of issue ids
    * @param aCrcResult calculated CRC
    */
	void getIssuesCRC( const vector<string>& aIssueIdsVector, char* aCrcResult );
    // END   -- Support for file checksum and comments

private:
    //! output file
    string          iOutputFile;

    //! output file
    string          iXSLFile;

    //! output file
    string          iDTDFile;
    
    //! Baseline version name
    string          iBaselineVersion;
    
    //! //! Baseline version name
    string          iCurrentVersion;
    
    //! Embed style sheet or not
    bool            iEmbedXSL;
        
    //! Embed style Document Type Definition or not
    bool            iEmbedDTD;

    //! The whole XML document
    XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument*    iDOMDocument;
        
    //! Root node
    XERCES_CPP_NAMESPACE_QUALIFIER DOMElement*     iDOMRoot;
    
    //! Commandline parameters to Header analyser
    map<string,string> iParams;

    // START -- Support for file checksum and comments
    //! Table of CRC values
    unsigned long*	iCrcTable;
    // END   -- Support for file checksum and comments
        
    // Struct to compare issue pointers 
    struct compareReportIssuePointers
	{
	bool operator()(const ReportIssue * s1,const ReportIssue * s2) const
		{
		return (*s1) < (*s2);
		};
	};

    //! 
	typedef map<const ReportIssue*,ReportIssue*,compareReportIssuePointers> issueVector;

    //! Entry to add to issue map
    typedef pair<string, issueVector*>  issueEntry;

    //! Map holding issues
    typedef map<string, issueVector*>   issueMap;

    //! Iterator for traversing issue map
    typedef issueMap::iterator          issueMapIterator;

    //! Map holding issues
    issueMap                            iIssueMap;

     //! ID of the issue
    int iIssueId;
};
#endif
