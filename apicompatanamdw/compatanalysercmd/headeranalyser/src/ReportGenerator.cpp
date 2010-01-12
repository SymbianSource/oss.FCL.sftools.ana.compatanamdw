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


#include "CmdGlobals.h"
#ifdef __WIN__
#pragma warning(disable:4786)
#endif

#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <time.h>

#include "ReportGeneratorConstants.h"
#include "CmdGlobals.h"
#include "ReportIssue.h"
#include "XMLModuleErrorHandler.h"
#include "HAException.h"
#include "Utils.h"
#include "Issues.h"
#include "BBCFileUtils.h"
using namespace std;

extern vector<pair<string,pair<string,string> > > HeaderInfoList; // vector<pair< headerfile name, pair<API name, API category>>>

XERCES_CPP_NAMESPACE_USE


const char* KXMLStyleSheet = "xml-stylesheet";

// Style sheet filename
const char* KXMLXSL = "type=\"text/xsl\" href=\"BBCResults.xsl\"";
// Base64 coding characters
const char* KBase64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-";

#include "ReportGenerator.h"

// ----------------------------------------------------------------------------
// ReportGenerator::ReportGenerator
// ----------------------------------------------------------------------------
//
ReportGenerator::ReportGenerator(string aOutputFile) 
: 
iOutputFile(aOutputFile), 
iIssueId(0),
iDOMDocument(0),
iDOMRoot(0)
{
	// START -- Support for file checksum and comments
	unsigned long crc;
	iCrcTable = new unsigned long[256];
	for ( int i = 0; i <= 255 ; i++ )
	{
		crc = i;
		for ( int j = 8 ; j > 0; j-- )
		{
			if ( crc & 1 )
				crc = ( crc >> 1 ) ^ 0xEDB88320L;
			else
				crc >>= 1;
		}
		iCrcTable[i] = crc;
	}
	// END -- Support for file checksum and comments
}

// ----------------------------------------------------------------------------
// ReportGenerator::~ReportGenerator
// ----------------------------------------------------------------------------
//
ReportGenerator::~ReportGenerator()
{
	// START -- Support for file checksum and comments
	delete iCrcTable;
	iCrcTable = NULL;
	// END -- Support for file checksum and comments
	if( iDOMDocument )
	{
		iDOMDocument->release();
	}
	for( issueMap::iterator i = iIssueMap.begin(); i != iIssueMap.end(); ++i )
	{
		delete i->second;
		i->second = 0;
	}
}

// ----------------------------------------------------------------------------
// ReportGenerator::setXSL
// ----------------------------------------------------------------------------
//
void ReportGenerator::setXSL(string aXSLFilename, bool aIncludeInXML)
{
    iXSLFile = aXSLFilename;
    iEmbedXSL = aIncludeInXML;
}

// ----------------------------------------------------------------------------
// ReportGenerator::setDTD
// ----------------------------------------------------------------------------
//
void ReportGenerator::setDTD(string aDTDFilename, bool aIncludeInDTD)
{
    iDTDFile = aDTDFilename;
    iEmbedDTD = aIncludeInDTD;
}

// ----------------------------------------------------------------------------
// ReportGenerator::startReport
// ----------------------------------------------------------------------------
//
void ReportGenerator::startReport()
{
    initialiseDOM();
}

// ----------------------------------------------------------------------------
// ReportGenerator::finishReport
// ----------------------------------------------------------------------------
//
void ReportGenerator::finishReport()
{
    DOMElement* issuelist = createIssueListNode();
    iDOMRoot->appendChild(issuelist);
    dumpDOMToFile();
}

// ----------------------------------------------------------------------------
// ReportGenerator::loadStringTables
// ----------------------------------------------------------------------------
//
void ReportGenerator::loadStringTables(string aFilename)
{
}

// ----------------------------------------------------------------------------
// ReportGenerator::setCmdLineParms
// ----------------------------------------------------------------------------
//
void ReportGenerator::setCmdLineParms(map<string, string> aParms)
{
    map<string, string>::iterator begin = aParms.begin();
    map<string, string>::iterator end = aParms.end();
    while (begin != end)
    {
        iParams.insert(*begin);
        begin++;
    }
}

// ----------------------------------------------------------------------------
// ReportGenerator::getCmdLineParm
// ----------------------------------------------------------------------------
//
string ReportGenerator::getCmdLineParm(string aParm)
{
    map<string, string>::iterator begin = iParams.find(aParm);
    if (begin != iParams.end())
    {
        return (*begin).second;
    }
    else
    {
        return "Not specified";
    }
}


// ----------------------------------------------------------------------------
// ReportGenerator::setVersions
// ----------------------------------------------------------------------------
//
void ReportGenerator::setVersions(string aBaseline, string aCurrent)
{
    iBaselineVersion = aBaseline;
    iCurrentVersion = aCurrent;
}

// ----------------------------------------------------------------------------
// ReportGenerator::addIssue
// ----------------------------------------------------------------------------
//
int ReportGenerator::addIssue(ReportIssue* aIssue)
{
	aIssue->iId = iIssueId++;
	
    string key = "<";
    key += aIssue->HeaderFile();
    key += "><";
    key += aIssue->CompareFileName();
    key += ">";

    issueMapIterator it = iIssueMap.find(key);
    if (it != iIssueMap.end())
    {
		bool lineInfoNeed = true;
        // header entry is present in the report. append the issue to the header issue list
        issueVector* v = it->second;
		issueVector::iterator iv_it=v->begin();
		bool notAnalysed = false;
		 for (; iv_it != v->end(); ++iv_it)
		 {
			 ReportIssue* issue = iv_it->second;

			 TIssueIdentity id = issue->IdentityId();
			 TIssueType type = issue->TypeId();
			 if( id == EIssueIdentityFile && type == EIssueTypeEmpty)
			 {
				 notAnalysed = true;
				 lineInfoNeed = issue->LineInfoNeeded();
				 break;
			 }
		}
		if(lineInfoNeed == false)
		{
			aIssue->SetLineNumber(0);
		}
        if( v->insert(pair<const ReportIssue*, ReportIssue*>(aIssue,aIssue)).second == false )
        {
            return -1;
        }
    } else
    {
        // header entry is not present in the report. create an entry for the header with this issue
        issueVector* v = new issueVector();
        v->insert(pair<const ReportIssue*, ReportIssue*>(aIssue,aIssue));
        issueEntry entry(key,v);
        iIssueMap.insert(entry);
    }
    
	return iIssueId-1;
}

// ----------------------------------------------------------------------------
// ReportGenerator::addIssue
// ----------------------------------------------------------------------------
//
int ReportGenerator::addIssue(const string& aFile, 
                const string& aFQName, const TIssueIdentity& aIdentityId, 
                const TIssueType& aTypeId, const TBCSeverity& aBCSeverityId, 
                const TSCSeverity& aSCSeverityId, const string& aIgnoreInformation, 
                int aLineNumber, const string& aCompareFileName, const string& aCompilationError, bool alineNoNeeded )
{
	string fqName = aFQName;
	int loc = fqName.find(__FUN_MANGLED__);
	if(loc != -1)
	{
	fqName = fqName.substr(0,loc);
	}
    ReportIssue* issue = new ReportIssue(0, aFile, fqName, 
			aIdentityId, aTypeId, aBCSeverityId, aSCSeverityId, aIgnoreInformation, 
            aLineNumber, aCompareFileName, aCompilationError, alineNoNeeded );

    /*return*/
    int ret = addIssue(issue);
    if( ret == -1)
    {
        delete issue;
    }
    return ret;
}

// ----------------------------------------------------------------------------
// ReportGenerator::dumpXSLToFile
// ----------------------------------------------------------------------------
//
void ReportGenerator::dumpXSLToFile()
{
}

// ----------------------------------------------------------------------------
// ReportGenerator::dumpDTDToFile
// ----------------------------------------------------------------------------
//
void ReportGenerator::dumpDTDToFile()
{
}

// ----------------------------------------------------------------------------
// ReportGenerator::dumpDOMToFile
// ----------------------------------------------------------------------------
//
void ReportGenerator::dumpDOMToFile()
{
    XMLCh* features = _X("Core");
    DOMImplementation* imp =  DOMImplementationRegistry::getDOMImplementation(features);
    _XX(features);
    DOMWriter* writer = ((DOMImplementationLS*)imp)->createDOMWriter();
    
    writer->setFeature( XMLUni::fgDOMWRTFormatPrettyPrint,true);
    DOMErrorHandler* errorHandler = new XMLModuleErrorHandler();
    // Set error handler
    writer->setErrorHandler(errorHandler);
    XMLCh* tempfilename = XMLString::transcode(iOutputFile.c_str());
    XMLFormatTarget* ft = new LocalFileFormatTarget(tempfilename);
    writer->writeNode(ft, *iDOMDocument);
    XMLString::release(&tempfilename);
    delete ft;
    writer->release();
    delete errorHandler;
}

// ----------------------------------------------------------------------------
// ReportGenerator::generateVersionIdNodes
// ----------------------------------------------------------------------------
//
void ReportGenerator::generateVersionIdNodes()
{
}

// ----------------------------------------------------------------------------
// ReportGenerator::initialiseDOM
// ----------------------------------------------------------------------------
//
void ReportGenerator::initialiseDOM()
{    
    XMLCh * features = _X("Core");
    DOMImplementation* imp =  DOMImplementationRegistry::getDOMImplementation(features);
    _XX(features);
    if (imp != NULL)
    {
        try
        {
            XMLCh * repRoot = _X(NODE_REPORTROOT);
            DOMDocument* doc = imp->createDocument(NULL, repRoot, NULL);
		        _XX(repRoot);
		        if( iDOMDocument )
		        {
		            iDOMDocument->release();				
		            iDOMDocument = 0;
		        }
            iDOMDocument = doc;

            XMLCh * stylesheet = XMLString::transcode(KXMLStyleSheet);
            XMLCh * xsl = XMLString::transcode(KXMLXSL);
            
            // Style sheet is inserted to DOM document
            iDOMDocument->insertBefore( 
                iDOMDocument->createProcessingInstruction(
                  stylesheet,
                    xsl
                ),
                iDOMDocument->getDocumentElement()
            ); 
            XMLString::release(&stylesheet);
            XMLString::release(&xsl);
                
            iDOMRoot = iDOMDocument->getDocumentElement();
            // Header node created
            DOMElement* header = createHeaderNode();
            iDOMRoot->appendChild(header);
        } catch (const XMLException& /*e*/)
        {
            throw HAException("Error initialising the DOM Document");
        }
    }
}

// ----------------------------------------------------------------------------
// ReportGenerator::uninitialiseDOM
// ----------------------------------------------------------------------------
//
void ReportGenerator::uninitialiseDOM()
{
}

// ----------------------------------------------------------------------------
// ReportGenerator::createOpenNode
// ----------------------------------------------------------------------------
//
DOMElement* ReportGenerator::createOpenNode(const char* aNodeName)
{
    DOMElement* ret = NULL;
    XMLCh* ch = XMLString::transcode(aNodeName);
    ret = iDOMDocument->createElement(ch);
	XMLString::release(&ch);
    return ret;
}

// ----------------------------------------------------------------------------
// ReportGenerator::createHeaderNode
// ----------------------------------------------------------------------------
//
DOMElement* ReportGenerator::createHeaderNode()
{
    DOMElement* ret = NULL;
    ret = createOpenNode(NODE_HEADER);
    vector<DOMElement*> childvec;

    childvec.push_back(createSimpleTextNode(NODE_HEADER_BASELINEVERSION, iBaselineVersion.c_str()));
    childvec.push_back(createSimpleTextNode(NODE_HEADER_CURRENTVERSION, iCurrentVersion.c_str()));
    childvec.push_back(createTimestampNode());
    childvec.push_back(createSimpleTextNode(NODE_HEADER_HAVERSION, HEADER_ANALYSER_VERSION));
    childvec.push_back(createSimpleTextNode(NODE_HEADER_FORMATVERSION, HEADER_ANALYSER_REPORT_VERSION));
    childvec.push_back(createCmdLineNode());

    appendChildrenToNode(ret, childvec);
    return ret;
}

// ----------------------------------------------------------------------------
// ReportGenerator::removeRemovedSubClasses
// ----------------------------------------------------------------------------
//
void ReportGenerator::removeRemovedSubClasses()
{
    issueMapIterator it = iIssueMap.begin(); 
    for (; it != iIssueMap.end();++it)
    {
        issueVector* iv = it->second;
		issueVector::iterator iv_it=iv->begin();

        for (; iv_it != iv->end(); ++iv_it)
        {
            ReportIssue* issue = iv_it->second;

			TIssueIdentity id = issue->IdentityId();
			TIssueType type = issue->TypeId();
			
			//Do not process macros or other than issues type "removed"
			if ( EIssueTypeRemoval == type && EIssueIdentityMacro != id )
			{
				string fqname = issue->FQName();
				fqname += "::";
				
				issueVector::iterator iv_it2=iv_it;
				++iv_it2;
		
				for (; iv_it2 != iv->end(); ++iv_it2)
				{
					ReportIssue* issue2 = iv_it2->second;
					string fqname2 = issue2->FQName();
					
					//If the issue is inside removed class it can be removed from list
					if ( 0 == fqname2.compare(0, fqname.length(), fqname) )
					{
						issueVector::iterator iv_it3 = iv_it2;
						--iv_it2;
						iv->erase(iv_it3);
					} else //No more issues inside removed class so break
					{
						break;
					}
				}
			}
		}

	}
}

// ----------------------------------------------------------------------------
// ReportGenerator::functionMapping
// ----------------------------------------------------------------------------
//
TIssueIdentity ReportGenerator::functionMapping(const vector<TIssueIdentity> & ids)
{

	TIssueIdentity ret = EIssueIdentityExportedFunction;

	if (ids.size() == 1)
	{
		ret = ids[0];
	}
	else if (ids.size() == 3)
	{
		ret = EIssueIdentityExportedVirtualInlineFunction;
	}
	else
	{
		if (  (EIssueIdentityExportedFunction == ids[0] && EIssueIdentityVirtualFunction == ids[1]) ||
				(EIssueIdentityExportedFunction == ids[1] && EIssueIdentityVirtualFunction == ids[0]) )
		{
			ret = EIssueIdentityExportedVirtualFunction;
		} else	if (  (EIssueIdentityExportedFunction == ids[0] && EIssueIdentityInlineFunction == ids[1]) ||
				(EIssueIdentityExportedFunction == ids[1] && EIssueIdentityInlineFunction == ids[0]) )
		{
			ret = EIssueIdentityExportedInlineFunction;
		} else if (  (EIssueIdentityInlineFunction == ids[0] && EIssueIdentityVirtualFunction == ids[1]) ||
				(EIssueIdentityInlineFunction == ids[1] && EIssueIdentityVirtualFunction == ids[0]) )
		{
			ret = EIssueIdentityVirtualInlineFunction;
		}
	}
	return ret;
}

// ----------------------------------------------------------------------------
// ReportGenerator::mergeFunctionIssues
// ----------------------------------------------------------------------------
//
void ReportGenerator::mergeFunctionIssues()
{
    issueMapIterator it = iIssueMap.begin(); 
    for (; it != iIssueMap.end();++it)
    {
        issueVector* iv = it->second;
		issueVector::iterator iv_it=iv->begin();

        for (; iv_it != iv->end(); ++iv_it)
        {
            ReportIssue* issue = iv_it->second;

			TIssueIdentity id = issue->IdentityId();
			TIssueType type = issue->TypeId();
			
			//Process functions only
			if (    
				EIssueIdentityExportedFunction == id ||
				EIssueIdentityInlineFunction == id ||
				EIssueIdentityVirtualFunction == id 
			   )
			{
				vector<TIssueIdentity> identities;
				identities.reserve(3);
				string fqname = issue->FQName();
				identities.push_back(issue->IdentityId());
				issueVector::iterator iv_it2=iv_it;
				++iv_it2;
		
				TBCSeverity bcseverity = issue->BCSeverity();
				TSCSeverity scseverity = issue->SCSeverity();

				for (; iv_it2 != iv->end(); ++iv_it2)
				{
					ReportIssue* issue2 = iv_it2->second;
					string fqname2 = issue2->FQName();
					TIssueType type2 = issue2->TypeId();
					
					//If the issue has same type and it is for the same function
					if ( (fqname2 == fqname) && (type2 == type) )
					{
						if ( issue2->BCSeverity() < bcseverity )
						{
							bcseverity = issue2->BCSeverity();
						}
						if ( issue2->SCSeverity() < scseverity )
						{
							scseverity = issue2->SCSeverity();
						}
						identities.push_back(issue2->IdentityId());
						issueVector::iterator iv_it3 = iv_it2;
						--iv_it2;
						iv->erase(iv_it3);
					} 
				}
				if (identities.size() > 0)
				{
					issue->SetIdentityId( functionMapping(identities) );
					issue->SetBCSeverity(bcseverity);			
					issue->SetSCSeverity(scseverity);
				}
			}
		}

	}
}

// ----------------------------------------------------------------------------
// ReportGenerator::preprocessIssueList
// ----------------------------------------------------------------------------
//
void ReportGenerator::preprocessIssueList()
{
	removeRemovedSubClasses();
	mergeFunctionIssues();
}


// ----------------------------------------------------------------------------
// ReportGenerator::createIssueListNode
// ----------------------------------------------------------------------------
//
DOMElement* ReportGenerator::createIssueListNode()
{
    preprocessIssueList();

    DOMElement* ret = NULL;
	bool apiFound = false;
    ret = createOpenNode(NODE_ISSUELIST);
    issueMapIterator it = iIssueMap.begin();
    while (it != iIssueMap.end())
    {
		apiFound = false;
        issueVector* iv = it->second;
        issueVector::const_iterator iv_it = iv->begin();

        DOMElement* headerfilenode = createOpenNode(NODE_ISSUELIST_HEADERFILE);
        DOMElement* filenamenode = createSimpleTextNode(NODE_ISSUELIST_HEADERFILE_FILENAME, iv_it->second->HeaderFile().c_str());
        headerfilenode->appendChild(filenamenode);
                 
        // Append compared file here, Check from first Report issue, what was compare file name
        DOMElement* compareFileNameNode = createSimpleTextNode(
            NODE_ISSUELIST_HEADERFILE_COMPARE_FILENAME, iv_it->second->CompareFileName().c_str());

        headerfilenode->appendChild( compareFileNameNode );
        
        // START -- Support for file checksum and comments
        DOMElement* statusNode = createSimpleTextNode( NODE_ISSUELIST_HEADERFILE_STATUS, "" );
        headerfilenode->appendChild( statusNode );
        DOMElement* commentNode = createSimpleTextNode( NODE_ISSUELIST_HEADERFILE_COMMENT, "" );
        headerfilenode->appendChild( commentNode );

		// If Global header list is found with API info, then fill those in report file.
		for(unsigned int i = 0; i < HeaderInfoList.size(); i++ )
		{
			if(stricmp (HeaderInfoList.at(i).first.c_str(), iv_it->second->CompareFileName().c_str()) == 0)
			{
				DOMElement* apiNode = createAPIAttributeNode( NODE_ISSUELIST_HEADERFILE_ISSUE_APISTRING,
					                      HeaderInfoList.at(i).second.first.c_str(), HeaderInfoList.at(i).second.second.c_str() );
				headerfilenode->appendChild(apiNode);
				apiFound = true;
			}
			else if (stricmp( HeaderInfoList.at(i).first.c_str(), iv_it->second->HeaderFile().c_str()) == 0)
			{
				DOMElement* apiNode = createAPIAttributeNode( NODE_ISSUELIST_HEADERFILE_ISSUE_APISTRING,
					HeaderInfoList.at(i).second.first.c_str(), HeaderInfoList.at(i).second.second.c_str() );
				headerfilenode->appendChild(apiNode);
				apiFound = true;
			}
			if( apiFound == true )
				break;
		}
		// Global list is present, but the header has not been found from the list, then add api info for the header as "Unknown"
		if( apiFound == false && HeaderInfoList.size() > 0)
		{
			DOMElement* apiNode = createAPIAttributeNode( NODE_ISSUELIST_HEADERFILE_ISSUE_APISTRING,
				NODE_ISSUELIST_HEADERFILE_APIINFO_UNKNOWN, NODE_ISSUELIST_HEADERFILE_APIINFO_UNKNOWN );
			headerfilenode->appendChild(apiNode);
		}
		//else no API info will be available for any header.
        
        char checksum[14];
        if ( strlen( iv_it->second->CompareFileName().c_str() ) > 0) 
            getFileCRC( iv_it->second->CompareFileName().c_str(), checksum );
        else
            getFileCRC( iv_it->second->HeaderFile().c_str(), checksum );
			 	  
        // END   -- Support for file checksum and comments
	  
        //START  -- Support for shortname tag
        string fn;
        string directory;
        list<pair<string, string> > dirs;
        
        //select current filename to display if it is present, else select base filename
        if ( strlen( iv_it->second->CompareFileName().c_str() ) > 0) 
        {
            fn = iv_it->second->CompareFileName().c_str();	
            dirs = BBCFileUtils::extractFilenames(getCmdLineParm("currentdir"));
        }
        else
        {
            fn = iv_it->second->HeaderFile().c_str();
            dirs = BBCFileUtils::extractFilenames(getCmdLineParm("baselinedir"));
        }
		
        //select appropriate baseline/current dir from the list of baseline/current dirs
        list<pair<string, string> >::iterator dirbegin = dirs.begin();
        int p;
        for(; dirbegin != dirs.end(); dirbegin++)
        {
            p = toLowerCaseWin(fn).find(toLowerCaseWin(dirbegin->first),0);
            if(p!= string::npos)
            {
                directory = dirbegin->first;
                break;
            }
        }
                    
        // remove baseline/current dir part of the filename        
        string shortfilename;
        shortfilename.reserve(256);    
        shortfilename = removeBase(fn,directory);  
        
        // remove any leading directory separators from the filename 
        shortfilename=trimLeadingDirSeparator(shortfilename);
        shortfilename = toLowerCaseWin(shortfilename);  
        
        //create the shortname node
        DOMElement* shortNameNode = createSimpleTextNode( NODE_ISSUELIST_HEADERFILE_SHORTNAME,shortfilename.c_str() );	 
        //END  -- Support for shortname tag
    
		    vector<string> issueids;
        for (; iv_it != iv->end(); ++iv_it)
        {          
            ReportIssue* issue = iv_it->second;
            DOMElement* issuenode = createIssueNode(*issue);
            headerfilenode->appendChild(issuenode);
          
            // START -- Support for file checksum and comments
            string issueid;
            char* text;
            text = _X( issuenode->getElementsByTagName( _X( "typeid" ) )->item(0)->getTextContent() );
            issueid = text;
            _XX( text );
          
            text = _X( issuenode->getElementsByTagName( _X( "identityid" ) )->item(0)->getTextContent() );
            issueid += text;
            _XX( text );
          
            text = _X( issuenode->getElementsByTagName( _X( "cause" ) )->item(0)->getTextContent() );
            issueid += text;
            _XX( text );
          
            issueids.push_back( issueid );
            // END   -- Support for file checksum and comments
        }
        
        ret->appendChild(headerfilenode);
        it++;
        
        // START -- Support for file checksum and comments
        sort( issueids.begin(), issueids.end() );
        getIssuesCRC( issueids, &checksum[7] );
        DOMElement* checksumNode = createSimpleTextNode( NODE_ISSUELIST_HEADERFILE_CHECKSUM, checksum );
        headerfilenode->appendChild( checksumNode );
        // END   -- Support for file checksum and comments
        
        //START  -- Support for shortname tag
        // insert the shortname node 
        headerfilenode->appendChild( shortNameNode );
        //END  -- Support for shortname tag
    }
    return ret;
}

// ----------------------------------------------------------------------------
// ReportGenerator::createHeaderFileNode
// ----------------------------------------------------------------------------
//
DOMElement* ReportGenerator::createHeaderFileNode()
{
    DOMElement* ret = NULL;
    ret = createOpenNode(NODE_ISSUELIST_HEADERFILE);
    return ret;
}

// START -- Support for file checksum and comments

// ----------------------------------------------------------------------------
// ReportGenerator::getIssuesCRC
// ----------------------------------------------------------------------------
//
void ReportGenerator::getIssuesCRC( const vector<string>& aIssueIdsVector, char* aCrcResult )
{
	unsigned long crc = 0xFFFFFFFFL;
	vector<string>::const_iterator iter = aIssueIdsVector.begin();

	for ( iter = aIssueIdsVector.begin(); iter != aIssueIdsVector.end(); iter++ )
		for ( unsigned char* p = (unsigned char*) (*iter).c_str(); *p != '\0'; p++ )
			crc = iCrcTable[ ( crc & 0xff ) ^ *p ] ^ ( crc >> 8 );
	crc ^= 0xFFFFFFFFL;

	// The checksum is base64-encoded into 6 characters before it is returned.
	for ( int i = 0; i < 6; ++i )
		aCrcResult[i] = KBase64[ ( crc >> ( 30 - 6 * i ) ) & 0x3f ];
	aCrcResult[6] = '\0';

	return;
}
// END   -- Support for file checksum and comments

// START -- Support for file checksum and comments 

// ----------------------------------------------------------------------------
// ReportGenerator::getFileCRC
// ----------------------------------------------------------------------------
//
void ReportGenerator::getFileCRC( const char* aFilename, char* aCrcResult )
{
	unsigned long crc;
	unsigned long previousCrc;
	unsigned long length = 0;
	unsigned char* buffer = new unsigned char[512];
	unsigned char* p;
	int count;
	filebuf file;

	// Calculate CRC for file; all sequences of whitespace and/or comments
	// are replaced with _one_ space.
	// States:
	// 0 : "within star comment" : starts with "/*" and ends when
	//                             the next "*/" is encountered
	// 1 : "within line comment" : starts with "//" and ends when
	//                             the next "/n" or "\r" is encountered
	// 2 : "normal mode"         : "normal" text

	if ( file.open( aFilename, ios::in ) == NULL )
	{
		strcpy( aCrcResult, "*************");
		return;
	}

	crc = 0xFFFFFFFFL;
	previousCrc = 0xFFFFFFFFL;
	int state = 2;
	char previousChar = ' ';
	char slashPreviousChar = ' ';

	for ( ; ; )
	{
		count = (int) file.sgetn( (char*) buffer, 512 );
		if ( count == 0 )
		{
			break;
		}

		for ( p = buffer; count-- != 0; p++ )
		{
			if ( state == 0 )
			{
				if ( previousChar == '*' && *p == '/' )
				{
					state = 2;
					previousChar = slashPreviousChar;
					*p = ' ';
				}
			}
			else if ( state == 1 )
			{
				if ( *p == '\r' || *p == '\n' )
				{
					state = 2;
					previousChar = slashPreviousChar;
					*p = ' ';
				}
			}

			if ( state == 2 )
			{
				if ( *p == '/' && previousChar != '/' )
				{
					slashPreviousChar = previousChar;
				}

				if ( previousChar == '/' && *p == '*' )
				{
					state = 0;
					crc = previousCrc;  // previous char should not be included in CRC
					--length;
					*p = ' '; // do not allow /*/ to be interpreted as a comment
				}
				else if ( previousChar == '/' && *p == '/' )
				{
					state = 1;
					crc = previousCrc;  // previous char should not be included in CRC
					--length;
				}
				else {
					if ( *p == '\t' || *p == '\r' || *p == '\n' )
					{
						*p = ' ';
					}
					if ( *p != ' ' || previousChar != ' ' )
					{
						previousCrc = crc;
						crc = iCrcTable[ ( crc & 0xff ) ^ *p ] ^ ( crc >> 8 );
						++length;
					}
				}
			}
			previousChar = *p;
		}
	}
	crc ^= 0xFFFFFFFFL;
	file.close();
	delete buffer;

	// The 42-bit checksum is made up of
	//  * bits 32-41   : length of file MOD 1024 (10 bits)
	//  * bits 0-31    : the CRC-32 value
	// This checksum is base64-encoded into 7 characters (42 bits / 6 bits) before it is returned.
	int val;
	length &= 0x3ff;

	for ( int i = 0; i < 7; ++i )
	{
		if ( i == 0 )
			val = length >> 4;
		else if ( i == 1 )
			val = ( ( length << 2 ) | ( crc >> 30 ) ) & 0x3f;
		else
			val = ( crc >> ( 30 - 6 * ( i - 1 ) ) ) & 0x3f;
		aCrcResult[i] = KBase64[val];
	}
	aCrcResult[7] = '\0';

	return;
}
// END   -- Support for file checksum and comments

// ----------------------------------------------------------------------------
// ReportGenerator::createTimestampNode
// ----------------------------------------------------------------------------
//
DOMElement* ReportGenerator::createTimestampNode()
{
    DOMElement* ret = NULL;
    int second, minute, hour, day, month, year;

    time_t ttime;
    time(&ttime);
    struct tm* time = localtime(&ttime);
    second = time->tm_sec;
    minute = time->tm_min;
    hour = time->tm_hour;
    day = time->tm_mday;
    month = time->tm_mon + 1;
    year = time->tm_year + 1900;

    ret = createOpenNode(NODE_HEADER_TIMESTAMP);
    vector<DOMElement*> childvec;
    childvec.push_back(createSimpleTextNode(NODE_HEADER_TIMESTAMP_DAY, day));
    childvec.push_back(createSimpleTextNode(NODE_HEADER_TIMESTAMP_MONTH, month));
    childvec.push_back(createSimpleTextNode(NODE_HEADER_TIMESTAMP_YEAR, year));
    childvec.push_back(createSimpleTextNode(NODE_HEADER_TIMESTAMP_HOUR, hour));
    childvec.push_back(createSimpleTextNode(NODE_HEADER_TIMESTAMP_MINUTE, minute));
    childvec.push_back(createSimpleTextNode(NODE_HEADER_TIMESTAMP_SECOND, second));

    appendChildrenToNode(ret, childvec);
    return ret;
}

// ----------------------------------------------------------------------------
// ReportGenerator::appendChildrenToNode
// ----------------------------------------------------------------------------
//
void ReportGenerator::appendChildrenToNode(DOMElement* aParent, const vector<DOMElement*>& aChildren)
{
    size_t count = aChildren.size();
    for (unsigned int i = 0; i < count; i++)
    {
        aParent->appendChild(aChildren.at(i));
    }
}

// ----------------------------------------------------------------------------
// ReportGenerator::createSimpleTextNode
// ----------------------------------------------------------------------------
//
DOMElement* ReportGenerator::createSimpleTextNode(const char* aNodeName, const char* aNodeText)
{
    DOMElement* ret = NULL;

    XMLCh* ch = XMLString::transcode(aNodeName);
    XMLCh* ch2 = XMLString::transcode(aNodeText);
    ret = iDOMDocument->createElement(ch);
    DOMText* tn = iDOMDocument->createTextNode(ch2);
    ret->appendChild(tn);
    XMLString::release(&ch);
    XMLString::release(&ch2);
    return ret;
}

// ----------------------------------------------------------------------------
// ReportGenerator::createSimpleTextNode
// ----------------------------------------------------------------------------
//
DOMElement* ReportGenerator::createSimpleTextNode(const char* aNodeName, const XMLCh* aNodeText)
{
    DOMElement* ret = NULL;
    XMLCh* ch = XMLString::transcode(aNodeName);
    ret = iDOMDocument->createElement(ch);
    DOMText* tn = iDOMDocument->createTextNode(aNodeText);
    ret->appendChild(tn);
    XMLString::release(&ch);
    return ret;
}

// ----------------------------------------------------------------------------
// ReportGenerator::createSimpleTextNode
// ----------------------------------------------------------------------------
//
DOMElement* ReportGenerator::createSimpleTextNode(const char* aNodeName, const int aInteger)
{
    DOMElement* ret = NULL;
    XMLCh* ch = XMLString::transcode(aNodeName);
    string temp;
    itoa(aInteger, temp, 10);
    XMLCh* ch2 = XMLString::transcode(temp.c_str());
    ret = iDOMDocument->createElement(ch);
    DOMText* tn = iDOMDocument->createTextNode(ch2);
    ret->appendChild(tn);
    XMLString::release(&ch);
    XMLString::release(&ch2);
    return ret;
}
// ----------------------------------------------------------------------------
// ReportGenerator::createAttributeNode
// ----------------------------------------------------------------------------
//
DOMElement* ReportGenerator::createAPIAttributeNode(const char* aNodeName, const char* aNodeAPI,const char* aNodeCategory)
{
    DOMElement* ret = NULL;

    XMLCh* ch = XMLString::transcode(aNodeName);
	XMLCh* apivalue = XMLString::transcode(aNodeAPI);
    XMLCh* apiName = XMLString::transcode(NODE_ISSUELIST_HEADERFILE_ISSUE_APINAME);
	XMLCh* apicategoryvalue = XMLString::transcode(aNodeCategory);
	XMLCh* apicategoryname = XMLString::transcode(NODE_ISSUELIST_HEADERFILE_ISSUE_APICATEGORY);

    ret = iDOMDocument->createElement(ch);
	ret->setAttribute(apiName,apivalue);	
	ret->setAttribute(apicategoryname,apicategoryvalue);
	

    XMLString::release(&ch);
	XMLString::release(&apivalue);
	XMLString::release(&apiName);
	XMLString::release(&apicategoryvalue);
    XMLString::release(&apicategoryname);
    return ret;
}

// ----------------------------------------------------------------------------
// ReportGenerator::createCmdLineNode
// ----------------------------------------------------------------------------
//
DOMElement* ReportGenerator::createCmdLineNode()
{
    DOMElement* ret = NULL;
    ret = createOpenNode(NODE_HEADER_CMDLINE);
    map<string, string>::iterator begin = iParams.begin();
    while (begin != iParams.end())
    {
        DOMElement* ParamNode = createParmNode((*begin).first.c_str(),(*begin).second.c_str());
        ret->appendChild(ParamNode);
        begin++;
    }
    return ret;
}

// ----------------------------------------------------------------------------
// ReportGenerator::createParmNode
// ----------------------------------------------------------------------------
//
DOMElement* ReportGenerator::createParmNode(const char* aKey, const char* aValue)
{
    DOMElement* ret = NULL;
    
    // value <parm> **  </parm>
    ret = createOpenNode(NODE_HEADER_CMDLINE_PARM);
    
    // <pname>
    ret->appendChild(createSimpleTextNode(NODE_HEADER_CMDLINE_PARM_PNAME, aKey));
    // <pvalue>
    ret->appendChild(createSimpleTextNode(NODE_HEADER_CMDLINE_PARM_PVALUE, aValue));

    return ret;
}

// ----------------------------------------------------------------------------
// ReportGenerator::createDocumentationUrlString
// ----------------------------------------------------------------------------
//
string ReportGenerator::createDocumentationUrlString(string element)
{
    string ret;
    if (getCmdLineParm(DOCURL) != "Not speciefied") 
    {
        ret = getCmdLineParm(DOCURL) + element;
    }
    else
    {
        ret = "";
    }
    return ret;
}

// ----------------------------------------------------------------------------
// ReportGenerator::createIssueNode
// ----------------------------------------------------------------------------
//
DOMElement* ReportGenerator::createIssueNode(ReportIssue& aIssue)
{
    // IssueNode field element to report file
    DOMElement* ret = NULL;

    // create file name here
    ret = createOpenNode(NODE_ISSUELIST_HEADERFILE_ISSUE);

    vector<DOMElement*> childvec;
    
    // issue identifier field
    childvec.push_back(createSimpleTextNode(NODE_ISSUELIST_HEADERFILE_ISSUE_ISSUEID, aIssue.Id()));

    // issue type identifier field
    childvec.push_back(createSimpleTextNode(NODE_ISSUELIST_HEADERFILE_ISSUE_TYPEID, aIssue.TypeId()));

    // issue identify ( entity ) identifier field
    childvec.push_back(createSimpleTextNode(NODE_ISSUELIST_HEADERFILE_ISSUE_IDENTITYID, aIssue.IdentityId()));

    // identity description
    childvec.push_back(createSimpleTextNode( NODE_ISSUELIST_HEADERFILE_ISSUE_IDENTITYDESCRIPTION, aIssue.IdentityDescription()));

    // issue description field 
    childvec.push_back(createSimpleTextNode(NODE_ISSUELIST_HEADERFILE_ISSUE_TYPESTRING, aIssue.TypeDescription()));
    
    // issue cause description a.k.a FQName
    childvec.push_back(createSimpleTextNode(NODE_ISSUELIST_HEADERFILE_ISSUE_CAUSE, aIssue.FQName().c_str()));
    
    // issue documentation finder field
	childvec.push_back(createSimpleTextNode(NODE_ISSUELIST_HEADERFILE_ISSUE_DOCUMENTATION, createDocumentationUrlString(aIssue.FQName()).c_str()));
   
    // issue ignore finder field
    childvec.push_back(createSimpleTextNode(NODE_ISSUELIST_HEADERFILE_ISSUE_IGNOREINFORMATION, aIssue.IgnoreInformationDescription().c_str()));
    
    // issue linenumber field
    childvec.push_back(createSimpleTextNode(NODE_ISSUELIST_HEADERFILE_ISSUE_LINENUMBER, aIssue.LineNumber()));
    
    // issue extrainformation field
    //childvec.push_back(createSimpleTextNode(NODE_ISSUELIST_HEADERFILE_ISSUE_EXTRAINFORMATION, aIssue.ExtraInformationDescription().c_str()));
    
    // binary compatibility severity sub field for issue
    DOMElement* bcseverity = createOpenNode(NODE_ISSUELIST_HEADERFILE_ISSUE_SEVERITY);
    bcseverity->appendChild(createSimpleTextNode(NODE_ISSUELIST_HEADERFILE_ISSUE_SEVERITY_TYPEID, aIssue.BCSeverity()));
    bcseverity->appendChild(createSimpleTextNode(NODE_ISSUELIST_HEADERFILE_ISSUE_SEVERITY_TYPESTRING, aIssue.BCSeverityDescription()));

    // source compatibility severity sub field for issue
	DOMElement* scseverity = createOpenNode(NODE_ISSUELIST_HEADERFILE_ISSUE_SCSEVERITY);
    scseverity->appendChild(createSimpleTextNode(NODE_ISSUELIST_HEADERFILE_ISSUE_SEVERITY_TYPEID, aIssue.SCSeverity()));
    scseverity->appendChild(createSimpleTextNode(NODE_ISSUELIST_HEADERFILE_ISSUE_SEVERITY_TYPESTRING, aIssue.SCSeverityDescription()));
	
	// if iisue type is compilation error,  description of compilation error
	if(aIssue.TypeId() == EIssueTypeCompilationError)
		childvec.push_back(createSimpleTextNode(NODE_ISSUELIST_HEADERFILE_ISSUE_COMPILATION_ERROR, aIssue.CompilationError().c_str()));


    appendChildrenToNode(ret, childvec);
    ret->appendChild(bcseverity);
	ret->appendChild(scseverity);
    return ret;
}

// ----------------------------------------------------------------------------
// ReportGenerator::createSeverityNode
// ----------------------------------------------------------------------------
//
//DOMElement* ReportGenerator::createSeverityNode(const int aId)
DOMElement* ReportGenerator::createSeverityNode()
{
    DOMElement* ret = NULL;
    ret = createOpenNode(NODE_ISSUELIST_HEADERFILE_ISSUE_SEVERITY);
    return ret;
}

