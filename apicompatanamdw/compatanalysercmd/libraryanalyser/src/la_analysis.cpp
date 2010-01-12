/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description:  Functionality of analysis 
*
*/


#include "la.hpp"
#include "la_parser.hpp"
#include "xmlprocessor.hpp"
#include "xmldomainmap.hpp"
#include "xmlsaxparser.hpp"
#include "xmlnode.hpp"
#include "xmlsaxhandler.hpp"
#include "xmlsaxerrorhandler.hpp"



// ----------------------------------------------------------------------------------------------------------

typedef XMLSAXHandler<XMLDomainMap<XMLNode> > DOCHANDLER;
typedef XMLSAXErrorHandler ERRORHANDLER;
typedef XMLSAXParser<DOCHANDLER, ERRORHANDLER> PARSER;
typedef XMLProcessor<PARSER> XMLEngine;


int XmlTools::initialiseDOM()
{
    try
    {
        XMLPlatformUtils::Initialize();
    } catch (const XMLException& e )
    {
        char* message = _X( e.getMessage() );
        cout << "Error during initialization! :\n" << message << endl ;
        _XX(message);
		    return -1;
    }

    DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation( _X("Core") );
    iParser = ((DOMImplementationLS*)impl)->createDOMBuilder( DOMImplementationLS::MODE_SYNCHRONOUS, 0 );
    if ( iParser->canSetFeature( XMLUni::fgDOMValidation, true ) )
        iParser->setFeature( XMLUni::fgDOMValidation, true );
    if ( iParser->canSetFeature( XMLUni::fgDOMNamespaces, true ) )
        iParser->setFeature( XMLUni::fgDOMNamespaces, true );
    if ( iParser->canSetFeature( XMLUni::fgDOMDatatypeNormalization, true ) )
        iParser->setFeature( XMLUni::fgDOMDatatypeNormalization, true );
        
    return 0;
}

void XmlTools::uninitialiseDOM()
{
    iParser->release();
    XMLPlatformUtils::Terminate();
}

XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* XmlTools::readFile( const char* aFilename )
{
	XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* doc;
    DOMErrorHandler* myErrorHandler;

    fstream ifile;
    bool validate = false;
    
    string filedoctype;
    string doctype("<!DOCTYPE");
    
    //check if a document type definition is provided for the xml file
    ifile.open(aFilename);  
    ifile >> filedoctype ;
    ifile.close();
    
    if(doctype.compare(filedoctype) == 0)
        validate = true;
        
    //if document type definition present,create and set error handler to parser, to report any parse errors in issues document.
    if(validate)
    {
        myErrorHandler = new DOMPrintErrorHandler();
        XmlTools::iParser->setErrorHandler(myErrorHandler);	
    }
    
    try
    {
        doc = iParser->parseURI( aFilename );
    }
    catch ( const XMLException& e )
    {
        char* message = _X( e.getMessage() );
        cout << "Failed to read " << aFilename << ". \"" << message << "\"" << endl ;
        _XX( message );
        return NULL;
    }
    catch ( const DOMException& e )
    {
        char* message = _X( e.getMessage() );
        cout << "Failed to read " << aFilename << ". \"" << message << "\"" << endl ;
        _XX( message );
        return NULL;
    }
    catch (...) 
    {
        cout << "Failed to read " << aFilename << ". Unexpected error." << endl ;
    return NULL;
    }
    
    //delete the error handler, if set
    if(validate)
        delete myErrorHandler;
        
    return doc;
}

bool DOMPrintErrorHandler::handleError(const DOMError &domError)
{
    // Display whatever error message passed from the parser
    if (domError.getSeverity() == DOMError::DOM_SEVERITY_WARNING)
        XERCES_STD_QUALIFIER cerr << "\nWarning Message: ";
    else if (domError.getSeverity() == DOMError::DOM_SEVERITY_ERROR)
        XERCES_STD_QUALIFIER cerr << "\nError Message: ";
    else
        XERCES_STD_QUALIFIER cerr << "\nFatal Message: ";

    char *msg = XMLString::transcode(domError.getMessage());
    DOMLocator *errorLocator = domError.getLocation();
    XERCES_STD_QUALIFIER cerr<< errorLocator->getLineNumber() << ",";
    XERCES_STD_QUALIFIER cerr<< errorLocator->getColumnNumber() << ": ";
    XERCES_STD_QUALIFIER cerr<< msg <<XERCES_STD_QUALIFIER endl;
    XMLString::release(&msg);

    // Instructs the parser to continue parsing if possible.
    return true;
}

DOMElement* XmlTools::getTagNode( const DOMElement* aParentNode, const char* aTagName )
{
    DOMNodeList* list = aParentNode->getElementsByTagName( _X( aTagName ) );
    if ( list == NULL || list->getLength() == 0 )
        return NULL;
    else
        return (DOMElement*) list->item( 0 );
}

int XmlTools::getTagValue( const DOMElement* aParentNode, const char* aTagName, char* aTagValue, int minLen, int maxLen )
{
    DOMNodeList* list = aParentNode->getElementsByTagName( _X( aTagName ) );

    strcpy( aTagValue, "" );
    if ( list == NULL || list->getLength() == 0 )
        return -1;
    else
    {
        DOMNode* textNode = list->item( 0 )->getFirstChild();
        if ( textNode == NULL )
            return -1;
            
        char* text = _X( textNode->getNodeValue() );
        if ( text == NULL )
            return -1;
            
		int len =(int) strlen( text );
        if ( len < minLen || len > maxLen )
            return -1;
            
        strcpy( aTagValue, text );
        _XX( text );
        
        return 0;
    }
}


void ParseAndCompareDLLXmlFiles(const string& abaselineXmlFile,const string& acurrentXmlFile)
{
	XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* ibaseDoc = NULL;
	int currIndx = -1;
	int baseIndx = -1;
	char dll_name[1024];

	if ( XmlTools::initialiseDOM() == -1 )
        return ;

	// read report document
	ibaseDoc = XmlTools::readFile( abaselineXmlFile.c_str() );
	if ( ibaseDoc == NULL )
	{
		XmlTools::uninitialiseDOM();
		return ;
	}

	// Parse file
	cout << "Gathering dll information... " ;
	
	//With SAX parser , parse the base xml doc
	// Create an instance of our XMLFactory
	XMLEngine baseParser(abaselineXmlFile);
	// Turn off validation
	baseParser.doValidation(false);
	baseParser.parse();
	

	//With SAX parser , parse the current xml doc
	// Create an instance of our XMLFactory
	XMLEngine currParser(acurrentXmlFile);
	// Turn off validation
	currParser.doValidation(false);
	// Parse our XML file
	currParser.parse();

	cout << "Done" <<endl;

	// Get the tree root
	XMLNode baseRoot = baseParser.getRootElement();
	XMLNode curRoot = currParser.getRootElement();

	int totcurDlls = (int)curRoot.childCount(); 
	int totbaseDlls = (int)baseRoot.childCount();

	XMLNode dllNorode = curRoot.child("dll",currIndx);	
	XMLNode baseNode = baseRoot.child("dll",baseIndx);

	//If baseline dll is missing, report it as informative
	for(unsigned int outer = 0; outer < _lib_files_baseline.size(); outer++ )
	{
		dll_issue tempIssue;

		string finallibname(_lib_files_baseline.at(outer));
		finallibname=getFilename(finallibname);
		unsigned int inner;
		
		for(inner = baseIndx; inner < totbaseDlls; inner++ )
		{
			XMLNode base_dlllist = baseRoot.children_[inner];

			string base_dllname = base_dlllist.child("dllname").value();
			base_dllname = getFilename(base_dllname);
			if (StringICmpFileNamesWithoutExtension(finallibname,base_dllname) == 0)
				break;
		}
		if (inner == totbaseDlls)
		{
			intializeDllIssue(tempIssue);
			tempIssue.l_dllname = finallibname;
			tempIssue.i_list_typeid.push_back(DLL_BASELINE_MISSING);
			_dll_issuelist.push_back(tempIssue);			
		}
	}
	
    // get dll breaks by comparing baseline and current dll data file
	if (baseIndx >=0 && currIndx>=0)
	{
		for (unsigned long i = baseIndx; i < totbaseDlls; ++i )
		{
			dll_issue issue;
			XMLNode base_dlllist = baseRoot.children_[i];
			if ( base_dlllist.childCount() == 0 )
				continue;
			string base_dllname = base_dlllist.child("dllname").value();
			base_dllname = getFilename(base_dllname);
			
			int l;
			//char baseVal[5][255];
			char attribs[5][12] = { "uid1", "uid2", "uid3", "sid" ,"capability"};			
			
			if (base_dllname.size() > 0 )
			{
				intializeDllIssue(issue);				
				issue.l_dllname = base_dllname;
				string baseShortName = getFilename(base_dllname);
				int curIter;
				
				for( curIter = currIndx ; curIter < totcurDlls ; curIter++ )
				{
					XMLNode curr_dlllist = curRoot.children_[curIter];
					
					string cur_dllname = curr_dlllist.child("dllname").value();
					cur_dllname = getFilename(cur_dllname);
					vector<unsigned int> typeId_list;
									
					if(stricmp (baseShortName.c_str(),cur_dllname.c_str()) == 0)
					{						

						for ( l = 0; l < 5; ++ l )
						{
							string curVal = curr_dlllist.child(attribs[l]).value();
							string baseVal = base_dlllist.child(attribs[l]).value();
							unsigned int typeId = 0;

							if(l == 4) // capability check
							{
								unsigned long baseCap =parseHex(baseVal.c_str());
								unsigned long curCap = parseHex(curVal.c_str());
								unsigned long resultCap = baseCap & curCap;
								if( baseCap != resultCap)
									typeId_list.push_back(DLL_CAPABILITY_CHANGED);
							}							
							else if( curVal.compare(baseVal)!= 0)
							{								
								fillDllIssue(attribs[l], typeId);
								typeId_list.push_back(typeId);
							}
						}
						
						if(typeId_list.size()> 0 )
						{
							issue.i_list_typeid = typeId_list;
							_dll_issuelist.push_back(issue);
						}
						break;
					}
				}

				if (curIter == totcurDlls ) // missing dll in current xml file
				{
					issue.i_list_typeid.push_back( DLL_CURRENT_MISSING);
					_dll_issuelist.push_back(issue);	
				}
			}

		}
	}//end of dll list
	
	XmlTools::uninitialiseDOM();
}

void WriteReportHeader()
{
    _reportf.open(_cl_reportfile.c_str(), ios::trunc);

    if (!_reportf.is_open())
        {
			cerr << "ERROR: Cannot open " << _cl_reportfile << " for writing!" << endl;
			cerr << "Please check that the directory exists and there are no write permission problems" << endl;
			exit(EXIT_CANNOT_WRITE_TO_REPORT_FILE);
        }

    WriteXMLLineOpeningTag(_reportf, 0, "?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?");
    WriteXMLLineOpeningTag(_reportf, 0, "?xml-stylesheet type=\"text/xsl\" href=\"BBCResults.xsl\"?");
    WriteXMLLineOpeningTag(_reportf, 0, "bbcresults");
    WriteXMLLineOpeningTag(_reportf, 1, "header");

    WriteXMLLineOpenClosed(_reportf, 2, "baselineversion", _cl_baselineversion);
    WriteXMLLineOpenClosed(_reportf, 2, "currentversion", _cl_currentversion);

    WriteXMLLineOpeningTag(_reportf, 2, "timestamp");
    WriteXMLLineOpenClosed(_reportf, 3, "day", Int2Str(_timenow->tm_mday));
    WriteXMLLineOpenClosed(_reportf, 3, "month", Int2Str(_timenow->tm_mon + 1));
    WriteXMLLineOpenClosed(_reportf, 3, "year", Int2Str(1900 + _timenow->tm_year));
    WriteXMLLineOpenClosed(_reportf, 3, "hour", Int2Str(_timenow->tm_hour));
    WriteXMLLineOpenClosed(_reportf, 3, "minute", Int2Str(_timenow->tm_min));
    WriteXMLLineOpenClosed(_reportf, 3, "second", Int2Str(_timenow->tm_sec));
    WriteXMLLineClosingTag(_reportf, 2, "timestamp");

    WriteXMLLineOpenClosed(_reportf, 2, "laversion", LA_VERSION);
    WriteXMLLineOpenClosed(_reportf, 2, "formatversion", LA_REPORT_FORMAT_VERSION);

    WriteXMLLineOpeningTag(_reportf, 2, "cmdlineparms");

    WriteXMLLineOpeningTag(_reportf, 3, "parm");
    WriteXMLLineOpenClosed(_reportf, 4, "pname", "toolchain");
    WriteXMLLineOpenClosed(_reportf, 4, "pvalue", _toolchain_name);
    WriteXMLLineClosingTag(_reportf, 3, "parm");

    WriteXMLLineOpeningTag(_reportf, 3, "parm");
    WriteXMLLineOpenClosed(_reportf, 4, "pname", "baselinelibdir");
    WriteXMLLineOpenClosed(_reportf, 4, "pvalue", _cl_baselinelibdir);
    WriteXMLLineClosingTag(_reportf, 3, "parm");

    WriteXMLLineOpeningTag(_reportf, 3, "parm");
    WriteXMLLineOpenClosed(_reportf, 4, "pname", "currentlibdir");
    WriteXMLLineOpenClosed(_reportf, 4, "pvalue", _cl_currentlibdir);
    WriteXMLLineClosingTag(_reportf, 3, "parm");
    
    WriteXMLLineOpeningTag(_reportf, 3, "parm");
    WriteXMLLineOpenClosed(_reportf, 4, "pname", "baselinedlldir");
    WriteXMLLineOpenClosed(_reportf, 4, "pvalue", _cl_baselinedlldir);
    WriteXMLLineClosingTag(_reportf, 3, "parm");

    WriteXMLLineOpeningTag(_reportf, 3, "parm");
    WriteXMLLineOpenClosed(_reportf, 4, "pname", "currentdlldir");
    WriteXMLLineOpenClosed(_reportf, 4, "pvalue", _cl_currentdlldir);
    WriteXMLLineClosingTag(_reportf, 3, "parm");
    
    if(_cl_baselinedlldir.empty() || _cl_currentdlldir.empty())
    {
      WriteXMLLineOpeningTag(_reportf, 3, "parm");
      WriteXMLLineOpenClosed(_reportf, 4, "pname", "warning");
      WriteXMLLineOpenClosed(_reportf, 4, "pvalue","Required parameters for checking dll properties not specified. Compatibility Breaks in dll are not checked." );
      WriteXMLLineClosingTag(_reportf, 3, "parm");
    }

    WriteXMLLineOpeningTag(_reportf, 3, "parm");
    WriteXMLLineOpenClosed(_reportf, 4, "pname", "baselineversion");
    WriteXMLLineOpenClosed(_reportf, 4, "pvalue", _cl_baselineversion);
    WriteXMLLineClosingTag(_reportf, 3, "parm");

    WriteXMLLineOpeningTag(_reportf, 3, "parm");
    WriteXMLLineOpenClosed(_reportf, 4, "pname", "currentversion");
    WriteXMLLineOpenClosed(_reportf, 4, "pvalue", _cl_currentversion);
    WriteXMLLineClosingTag(_reportf, 3, "parm");

    WriteXMLLineOpeningTag(_reportf, 3, "parm");
    WriteXMLLineOpenClosed(_reportf, 4, "pname", "reportfile");
    WriteXMLLineOpenClosed(_reportf, 4, "pvalue", _cl_reportfile);
    WriteXMLLineClosingTag(_reportf, 3, "parm");

    WriteXMLLineOpeningTag(_reportf, 3, "parm");
    WriteXMLLineOpenClosed(_reportf, 4, "pname", "tools");
    WriteXMLLineOpenClosed(_reportf, 4, "pvalue", _cl_toolsdir);
    WriteXMLLineClosingTag(_reportf, 3, "parm");

    WriteXMLLineOpeningTag(_reportf, 3, "parm");
    WriteXMLLineOpenClosed(_reportf, 4, "pname", "temp");
    WriteXMLLineOpenClosed(_reportf, 4, "pvalue", _cl_tempdir);
    WriteXMLLineClosingTag(_reportf, 3, "parm");
    
    WriteXMLLineOpeningTag(_reportf, 3, "parm");
    WriteXMLLineOpenClosed(_reportf, 4, "pname", "cfilt");
    WriteXMLLineOpenClosed(_reportf, 4, "pvalue", _cl_cfiltloc);
    WriteXMLLineClosingTag(_reportf, 3, "parm");

    WriteXMLLineOpeningTag(_reportf, 3, "parm");
    WriteXMLLineOpenClosed(_reportf, 4, "pname", "set");
    WriteXMLLineOpenClosed(_reportf, 4, "pvalue", _cl_set);
    WriteXMLLineClosingTag(_reportf, 3, "parm");

    WriteXMLLineClosingTag(_reportf, 2, "cmdlineparms");

    WriteXMLLineOpenClosed(_reportf, 2, "knownissuesversion", "");
    
    WriteXMLLineClosingTag(_reportf, 1, "header");
    WriteXMLLineOpeningTag(_reportf, 1, "issuelist");    
}

// ----------------------------------------------------------------------------------------------------------

void GenerateAndWriteIssueList()
{
	int total_files = _lib_files_baseline.size();
	int current_files = 0;
	cout <<"Total baseline files "<< _lib_files_baseline.size() << endl;
	cout <<"Total current files "<< _lib_files_current.size() << endl;
	
	vector<string>::const_iterator itr;
	for (unsigned int i=0; i<_lib_files_current.size(); i++)
	{
		bool exists = false;
		// check if the same lib exists in baselinedir
		for(itr = _lib_dirs_baseline.begin(); itr != _lib_dirs_baseline.end(); itr++)
		{
			if (FileExists(*itr + getFilename(_lib_files_current.at(i))))
			{
				exists = true;
				break;
			}
		}
		if(!exists)
		{
			total_files++;
		}
	}
	cout <<"Total files to be processed "<< total_files << endl;
	//vector<dll_issue> dll_issuelist;
    
	dll_issue reportdll;
	string dllname;

	if(_baselinedllfile.size() > 0 && _currentdllfile.size() > 0)
	{
		ParseAndCompareDLLXmlFiles(_baselinedllfile,_currentdllfile );
	}
	
	unsigned int dllIssueCount = _dll_issuelist.size();

    // first go through all libs in the baseline set
	for (unsigned int i=0; i<_lib_files_baseline.size(); i++)
	{
		unsigned int k;
		vector<string>::iterator itr = _lib_files_current.end();
		bool exists = false;

		//check if the same dll is present in exe_issue, if yes then add it to final report
		intializeDllIssue(reportdll);
		for(unsigned int indx = 0; indx < dllIssueCount; indx++)
		{
			dll_issue lIssue;
			lIssue = _dll_issuelist.at(indx);		
			if(StringICmpFileNamesWithoutExtension(getFilename(lIssue.l_dllname),getFilename(_lib_files_baseline.at(i))) == 0)
			{
				reportdll = lIssue;
				break;
			}
		}


        // check if the same lib exists in currentdir
        for(k = 0; k < _lib_dirs_current.size(); k++)
		    {
			      string file = _lib_dirs_current.at(k) + getFilename(_lib_files_baseline.at(i));
			      if (FileExists( file ))
			      {
			          for(itr=_lib_files_current.begin() ; itr != _lib_files_current.end() ; ++itr)
			          {
			              if(StringICmp(file,*itr)== 0)
			              {
			                  exists = true;
			                  break;
			              }
			          }
			          if(exists)
			              break;
			      }
			  }

        // check if the same lib exists in currentdir
        if (!exists)
        {
        	  cout.precision(0);
            cout << "\nAnalysing files (" << current_files+1 << "/" << total_files << "): " << _lib_files_baseline.at(i) << endl;  

			WriteXMLIssueOnlyInBaselineDir(_reportf, _lib_files_baseline.at(i),reportdll);
        }
        else
        {
            cout.precision(0);
            cout << "\nAnalysing files (" << current_files+1 << "/" << total_files << "): " << _lib_files_baseline.at(i) << " => " << *itr << endl;  
            // both files are available, now get the symbol table and do the comparision process
            vector<string> symbol_table_baseline;
            vector<string> symbol_table_current;

            // get the symbol tables of the libraries
            if (_cl_use_gcc)
            {
                GetSymbolTableWithNM(_gcc_nm_location, _lib_files_baseline.at(i), symbol_table_baseline);
                GetSymbolTableWithNM(_gcc_nm_location, *itr /*_lib_files_current.at(i)*/, symbol_table_current);
            }
            else if (_cl_use_gcce)
            {
                if (_cl_use_libs)
                {
                    GetSymbolTableWithNM(_gcce_nm_location, _lib_files_baseline.at(i), symbol_table_baseline);
                    GetSymbolTableWithNM(_gcce_nm_location, *itr /*_lib_files_current.at(i)*/, symbol_table_current);
                }
                else
                {
                    GetSymbolTableWithReadelf(_gcce_readelf_location, _gcce_cfilt_location, _lib_files_baseline.at(i), symbol_table_baseline);
                    GetSymbolTableWithReadelf(_gcce_readelf_location, _gcce_cfilt_location, *itr /*_lib_files_current.at(i)*/, symbol_table_current);
                }
            }
            else if (_cl_use_rvct)
            {
                if (_cl_use_libs)
                {
                    GetSymbolTableWithArmar(_rvct_armar_location, _rvct_cfilt_location, _lib_files_baseline.at(i), symbol_table_baseline);
                    GetSymbolTableWithArmar(_rvct_armar_location, _rvct_cfilt_location, *itr /*_lib_files_current.at(i)*/, symbol_table_current);
                }
                else
                {
                    GetSymbolTableWithFromelf(_rvct_fromelf_location, _rvct_cfilt_location, _lib_files_baseline.at(i), symbol_table_baseline);
                    GetSymbolTableWithFromelf(_rvct_fromelf_location, _rvct_cfilt_location, *itr /*_lib_files_current.at(i)*/, symbol_table_current);
                }
            }

            // create a vector to store all issues of this library
            vector<issue> issue_list;
			//Local variable to store severity of the issue
			TypeOfSeverity severity = NO_BREAK;
            // create and init vectors to store ordinal state
            vector<bool> matched_baseline;
            vector<bool> checked_baseline;
            vector<bool> matched_current;
            vector<bool> checked_current;
			vector<TypeOfSeverity> map_severity;
            
            for (unsigned int j=0; j<symbol_table_baseline.size(); j++)
                matched_baseline.push_back(false);

            for (unsigned int j=0; j<symbol_table_baseline.size(); j++)
                checked_baseline.push_back(false);

            for (unsigned int j=0; j<symbol_table_current.size(); j++)
                matched_current.push_back(false);

            for (unsigned int j=0; j<symbol_table_current.size(); j++)
                checked_current.push_back(false);
			//Initially set to NO_BREAK as the type of severity
            for (unsigned int j=0; j<symbol_table_baseline.size(); j++)
                map_severity.push_back(NO_BREAK);


            // first loop through all ordinals in baseline to find matches
            for (unsigned int j=0; j<symbol_table_baseline.size(); j++)
            {
                bool need_to_check_moving = false;

                if (j < symbol_table_current.size())
                {
                    // check if it's an exact match or otherwise binary compatible
                    if ( symbol_table_baseline.at(j) == symbol_table_current.at(j) ||
                        (severity = AreFunctionsCompatible(symbol_table_baseline.at(j), symbol_table_current.at(j)))
						 == NO_BREAK )
                    {
                        // match!
                        matched_baseline.at(j) = true;
                        matched_current.at(j) = true;

                        checked_baseline.at(j) = true;
                        checked_current.at(j) = true;
                    }                    
                    else
					{
						// possibly moved
						need_to_check_moving = true;
						//store the severity
						map_severity.at(j) = severity;
					}
                }
                else
                {
                    // it's out of range, so it can be a match, but check if it has moved
                    need_to_check_moving = true;
                }   
                
                // now do the actual checking if it has moved
                if (need_to_check_moving)
                {
                    for (unsigned int l=0; l<symbol_table_current.size(); l++)
                    {
                        if (symbol_table_baseline.at(j) == symbol_table_current.at(l))
                        {
							// match found, mark as moved
							map_severity.at(j) = CONFIRMED_BC_BREAK;
                            AppendToIssueListCaseMoved(issue_list, symbol_table_baseline.at(j), j+1, l+1,map_severity.at(j));
                            
                            matched_baseline.at(j) = true;
                            matched_current.at(l) = true;

                            checked_baseline.at(j) = true;
                            checked_current.at(l) = true;

                        } // if
                    } // for           
                } // if (need_to_check_moving)
            } // for (int j=0; j<symbol_table_baseline.size(); j++)
           

            // check for removed ordinals when no corresponding ordinals in current
            if (checked_baseline.size() > checked_current.size())
            {
                for (unsigned int j=checked_current.size(); j<checked_baseline.size(); j++)
                {
                    if (checked_baseline.at(j) == false)
                    {
                        // ignore any absent exports
                        string::size_type loc = symbol_table_baseline.at(j).find("_._.absent_export", 0);
                        
                        // mark as removed if not marked as absent
                        if( loc == string::npos )
						{
							// As removed results in both BC and SC break.
							map_severity.at(j) = CONFIRMED_BC_AND_SC_BREAK;
                            AppendToIssueListCaseRemoved(issue_list, symbol_table_baseline.at(j), j+1,map_severity.at(j));
						}

                        checked_baseline.at(j) = true;
                    }         
                }          
            }

            // check for added ordinals when no corresponding ordinals in current
            if (checked_baseline.size() < checked_current.size())
            {
                for (unsigned int j=checked_baseline.size(); j<checked_current.size(); j++)
                {
                    if (checked_current.at(j) == false)
                    {
                    // ignore any absent exports
                    string::size_type loc = symbol_table_current.at(j).find("_._.absent_export", 0);
                    
                    // mark as added if not marked as absent
                    if( loc == string::npos )
                        AppendToIssueListCaseAdded(issue_list, symbol_table_current.at(j), j+1,BC_INFORMATIVE);

                    checked_current.at(j) = true;
                    }         
                }          
            }

            // check for removed cases when current has a match at the same ordinal
            for (unsigned int j=0; j<checked_baseline.size(); j++)
            {
                if (checked_baseline.at(j) == false && matched_current.at(j) == true)
                {
                    // ignore any absent exports
                    string::size_type loc = symbol_table_baseline.at(j).find("_._.absent_export", 0);
                    
                    // mark as removed if not marked as absent
                    if( loc == string::npos )
					{
						// As removed results in both BC and SC break.
						map_severity.at(j) = CONFIRMED_BC_AND_SC_BREAK;
						AppendToIssueListCaseRemoved(issue_list, symbol_table_baseline.at(j), j+1,map_severity.at(j));
					}

                    checked_baseline.at(j) = true;
                }         
            }             

            // check for inserted cases
            for (unsigned int j=0; j<checked_current.size(); j++)
            {
                if (checked_current.at(j) == false && matched_baseline.at(j) == true)
                {
                    // ignore any absent exports
                    string::size_type loc = symbol_table_current.at(j).find("_._.absent_export", 0);
                    
                    // mark as inserted if not marked as absent
                    if( loc == string::npos )
                        AppendToIssueListCaseInserted(issue_list, symbol_table_current.at(j), j+1,CONFIRMED_BC_BREAK);

                    checked_current.at(j) = true;
                }         
            }  

            // check for modified cases
            for (unsigned int j=0; j<checked_baseline.size(); j++)
            {
                if (checked_baseline.at(j) == false && checked_current.at(j) == false && matched_current.at(j) == false)
                {
                    // ignore any absent exports
                    string::size_type loc = symbol_table_baseline.at(j).find("_._.absent_export", 0);
                    string::size_type loc2 = symbol_table_current.at(j).find("_._.absent_export", 0);

                    // mark as modfied if not marked as absent
                    if( loc == string::npos && loc2 == string::npos)
                        AppendToIssueListCaseModified(issue_list, symbol_table_baseline.at(j), symbol_table_current.at(j), j+1,map_severity.at(j));
                    // mark as added if absent export has been modified to something else
                    else if (loc != string::npos && loc2 == string::npos)
                        AppendToIssueListCaseAdded(issue_list, symbol_table_current.at(j), j+1,BC_INFORMATIVE);
                    // mark as removed if export has been modified as absent
                    else if (loc == string::npos && loc2 != string::npos)
                        AppendToIssueListCaseRemoved(issue_list, symbol_table_baseline.at(j), j+1,CONFIRMED_BC_AND_SC_BREAK);
                        
                    checked_baseline.at(j) = true;
                    checked_current.at(j) = true;
                }         
            }   

            // do some error checking :)
            for (unsigned int j=0; j<checked_baseline.size(); j++)
            {
                if (checked_baseline.at(j) == false)
                {
                    cout << "OC ALGORITHM ERROR: Baseline func " << symbol_table_baseline.at(j) << " not checked!" << endl;
                }         
            } 
            for (unsigned int j=0; j<checked_current.size(); j++)
            {
                if (checked_current.at(j) == false)
                {
                    cout << "OC ALGORITHM ERROR: Current rel func " << symbol_table_current.at(j) << " not checked!" << endl;
                }         
            }

            // sort the issue list
            sort(issue_list.begin(), issue_list.end(), IssueCompare);

            // finally write the issue_list to the xml file
			WriteIssueListToXML(_reportf, _lib_files_baseline.at(i), *itr /*_lib_files_current.at(i)*/,  issue_list, reportdll);
            
        } // else of (!FileExists(_cl_currentlibdir + _lib_files_baseline.at(i)))
        //erase analysed file from vector, so that files with duplicate names will be properly analysed.
        if( _lib_files_current.end() != itr )
            _lib_files_current.erase(itr);

        current_files++;
	} // for (unsigned int i=0; i<_lib_files_baseline.size(); i++)


    // finally go through all libs in the currentdir set
	for (unsigned int i=0; i<_lib_files_current.size(); i++)
	{
		bool exists = false;
		vector<string>::const_iterator itr = _lib_dirs_baseline.begin();
        // check if the same lib exists in baselinedir
		for(;itr != _lib_dirs_baseline.end(); itr++)
		{
			if (FileExists(*itr + getFilename( _lib_files_current.at(i)) ))
			{
				exists = true;
				break;
			}
		}
		if(!exists)
		{
             current_files++;
             cout.precision(0);
             cout << "\nAnalysing files (" << current_files << "/" << total_files << "): " << _lib_files_current.at(i) << endl;  

             // only in currentdir
             WriteXMLIssueOnlyInCurrentDir(_reportf, _lib_files_current.at(i));
        }
    }
	cout << "\n---------------------------------------------";
	cout << "\nFinished";
	cout << "\nTotal Files analysed : " << total_files;
	cout << "\n---------------------------------------------";
}

// ----------------------------------------------------------------------------------------------------------
    
void WriteReportFooter()
{
    // generate the footer of XML file
    WriteXMLLineClosingTag(_reportf, 1, "issuelist");
    WriteXMLLineClosingTag(_reportf, 0, "bbcresults");

    // close writing to the report file
    _reportf.close();    
}

// ----------------------------------------------------------------------------------------------------------

void AppendToIssueListCaseMoved(vector<issue>& issueList, const string& funcname, int funcpos, int newfuncpos,TypeOfSeverity severity)
{
	issue i;
	string bc_severity = "";
	string sc_severity = "";
	getSeverityString(severity,bc_severity,sc_severity);

	i.i_typeid = ISSUE_MOVED;
	i.i_funcname = funcname;
	i.i_newfuncname = "";
	i.i_funcpos = funcpos;
	i.i_newfuncpos = newfuncpos;
	i.i_BC_severity = bc_severity;
	i.i_SC_severity = sc_severity;
	
    issueList.push_back(i); 
}

// ----------------------------------------------------------------------------------------------------------

void AppendToIssueListCaseRemoved(vector<issue>& issue_list, const string& funcname, int funcpos,TypeOfSeverity severity)
{
	issue i;
	string bc_severity = "";
	string sc_severity = "";
	getSeverityString(severity,bc_severity,sc_severity);

	i.i_typeid = ISSUE_REMOVED;
	i.i_funcname = funcname;
	i.i_newfuncname = "";
	i.i_funcpos = funcpos;
	i.i_newfuncpos = 0;
	i.i_BC_severity = bc_severity;
	i.i_SC_severity = sc_severity;
	
	issue_list.push_back(i); 
}

// ----------------------------------------------------------------------------------------------------------

void AppendToIssueListCaseInserted(vector<issue>& issue_list, const string& newfuncname, int newfuncpos,TypeOfSeverity severity)
{
	issue i;
	string bc_severity = "";
	string sc_severity = "";
	getSeverityString(severity,bc_severity,sc_severity);

	i.i_typeid = ISSUE_INSERTED;
	i.i_funcname = "";
	i.i_newfuncname = newfuncname;
	i.i_funcpos = 0;
	i.i_newfuncpos = newfuncpos;
	i.i_BC_severity = bc_severity;
	i.i_SC_severity = sc_severity;
	
	issue_list.push_back(i); 
}

// ----------------------------------------------------------------------------------------------------------

void AppendToIssueListCaseModified(vector<issue>& issue_list, const string& funcname, const string& newfuncname, int funcpos,TypeOfSeverity severity)
{
	issue i;
	string bc_severity = "";
	string sc_severity = "";
	getSeverityString(severity,bc_severity,sc_severity);

	i.i_typeid = ISSUE_MODIFIED;
	i.i_funcname = funcname;
	i.i_newfuncname = newfuncname;
	i.i_funcpos = funcpos;
	i.i_newfuncpos = 0;
	i.i_BC_severity = bc_severity;
	i.i_SC_severity = sc_severity;
	
	issue_list.push_back(i); 
}

// ----------------------------------------------------------------------------------------------------------

void AppendToIssueListCaseAdded(vector<issue>& issue_list, const string& newfuncname, int newfuncpos,TypeOfSeverity severity)
{
	issue i;
	string bc_severity = "";
	string sc_severity = "";
	getSeverityString(severity,bc_severity,sc_severity);

	i.i_typeid = ISSUE_ADDED;
	i.i_funcname = "";
	i.i_newfuncname = newfuncname;
	i.i_funcpos = 0;
	i.i_newfuncpos = newfuncpos;
	i.i_BC_severity = bc_severity;
	i.i_SC_severity = sc_severity;

	issue_list.push_back(i); 
}

// ----------------------------------------------------------------------------------------------------------

bool IssueCompare(const issue& left, const issue& right)
{
    if (left.i_funcpos > 0 && right.i_funcpos > 0)
    {
        if (left.i_funcpos == right.i_funcpos && left.i_newfuncpos > 0 && right.i_newfuncpos > 0)
            return left.i_newfuncpos < right.i_newfuncpos;
        else
            return left.i_funcpos < right.i_funcpos; 
    }
    
    else if (left.i_funcpos == 0 && right.i_funcpos > 0)
    {
        if (left.i_newfuncpos == right.i_funcpos)
            return left.i_funcpos < right.i_newfuncpos;
        else
            return left.i_newfuncpos < right.i_funcpos;
    }
    
    else if (left.i_funcpos > 0 && right.i_funcpos == 0)
    {
        if (left.i_funcpos == right.i_newfuncpos)
            return left.i_newfuncpos < right.i_funcpos;
        else
            return left.i_funcpos < right.i_newfuncpos;
    }
       
    else // if (left.i_funcpos == 0 && right.i_funcpos == 0)
    {
        return left.i_newfuncpos < right.i_newfuncpos;
    }
}

// ----------------------------------------------------------------------------------------------------------

void WriteXMLLineOpenClosed(ofstream& f, unsigned int tabstops, const string& element, const string& data)
{
    string tabs(tabstops, REPORT_TAB_CHAR);
    string xmldata(data);
    
    // replace & -> &auml;
    string::size_type i=0;
    while ((i=xmldata.find("&", i)) != string::npos)
    {
        xmldata.replace(i, 1, "&amp;");
        i++;
    }

    // replace < -> &lt;
    i=0;
    while ((i=xmldata.find("<", i)) != string::npos)
        xmldata.replace(i, 1, "&lt;");    

    // replace > -> &gt;
    i=0;
    while ((i=xmldata.find(">", i)) != string::npos)
        xmldata.replace(i, 1, "&gt;");    


    f << tabs << "<" << element << ">" << xmldata << "</" << element << ">" << endl;
}

// ----------------------------------------------------------------------------------------------------------

void WriteXMLLineOpeningTag(ofstream& f, unsigned int tabstops, const string& element)
{
    string tabs(tabstops, REPORT_TAB_CHAR);

    f << tabs << "<" << element << ">" << endl;
}

// ----------------------------------------------------------------------------------------------------------

void WriteXMLLineClosingTag(ofstream& f, unsigned int tabstops, const string& element)
{
    string tabs(tabstops, REPORT_TAB_CHAR);

    f << tabs << "</" << element << ">" << endl;
}

// ----------------------------------------------------------------------------------------------------------

void writeXMLIssueLibraryHeader(ofstream& f, const string& libname, const string& curlibname)
{
    
    WriteXMLLineOpeningTag(f, 2, "library");
    WriteXMLLineOpenClosed(f, 3, "name", libname);
    WriteXMLLineOpenClosed(f, 3, "comparefilename", curlibname);
    
    string finallibname(curlibname);
    if (finallibname.empty())
       finallibname=libname;
    finallibname=getFilename(finallibname);
    // remove any extensions from libname
    string::size_type dot_loc = finallibname.find_last_of(".");
    if (dot_loc != string::npos)
        finallibname = finallibname.substr(0, dot_loc);    
    WriteXMLLineOpenClosed(f, 3, "shortname", finallibname);
    WriteXMLLineOpenClosed(f, 3, "baseplatform", getPlatform(libname));
    WriteXMLLineOpenClosed(f, 3, "currentplatform", getPlatform(curlibname));
}

// ----------------------------------------------------------------------------------------------------------

void writeXMLIssueLibraryFooter(ofstream& f)
{
    WriteXMLLineClosingTag(f, 2, "library");
}

// ----------------------------------------------------------------------------------------------------------

void WriteXMLIssueOnlyInBaselineDir(ofstream& f, const string& libname, dll_issue& dllIssue)
{
	writeXMLIssueLibraryHeader(f, libname, "");
	WriteXMLLineOpeningTag(f, 3, "issue");
	WriteXMLLineOpenClosed(f, 4, "typeid", Int2Str(ISSUE_ONLY_IN_BASELINEDIR));
	WriteXMLLineOpenClosed(f, 4, "bc_severity", "BBC Break");
	WriteXMLLineOpenClosed(f, 4, "sc_severity", "SC Break");
	WriteXMLLineClosingTag(f, 3, "issue");
	for(unsigned int i =0; i< dllIssue.i_list_typeid.size(); i++ )
	{
		string typeinfo = "";
		WriteXMLLineOpeningTag(f, 3, "issue");
		WriteXMLLineOpenClosed(f, 4, "typeid", Int2Str(dllIssue.i_list_typeid.at(i)));
		typeinfo = GetDllBreakTypeInfoString(dllIssue.i_list_typeid.at(i));
		if(typeinfo.size() > 0)
			WriteXMLLineOpenClosed(f, 4, "typeinfo", typeinfo);

		if (dllIssue.i_list_typeid.at(i) == DLL_BASELINE_MISSING )
			WriteXMLLineOpenClosed(f, 4, "bc_severity", "Informative");            
		else
			WriteXMLLineOpenClosed(f, 4, "bc_severity", "BBC Break"); 

		WriteXMLLineOpenClosed(f, 4, "sc_severity", "None");            

		WriteXMLLineClosingTag(f, 3, "issue");
	}
	writeXMLIssueLibraryFooter(f);
}            

// ----------------------------------------------------------------------------------------------------------

void WriteXMLIssueOnlyInCurrentDir(ofstream& f, const string& libname)
{
    writeXMLIssueLibraryHeader(f, "", libname);
    WriteXMLLineOpeningTag(f, 3, "issue");
    WriteXMLLineOpenClosed(f, 4, "typeid", Int2Str(ISSUE_ONLY_IN_CURRENTDIR));
    WriteXMLLineOpenClosed(f, 4, "bc_severity", "Informative");
    WriteXMLLineOpenClosed(f, 4, "sc_severity", "Informative");
    WriteXMLLineClosingTag(f, 3, "issue");
    writeXMLIssueLibraryFooter(f);
}            

// ----------------------------------------------------------------------------------------------------------

void WriteIssueListToXML(ofstream& f, const string& libname, const string& curlibname,vector<issue>& issue_list, dll_issue& dllIssue)
{
	if (issue_list.size() > 0 || dllIssue.i_list_typeid.size() > 0)
    {
        string finallibname(curlibname);
        // write header
        WriteXMLLineOpeningTag(f, 2, "library");
        WriteXMLLineOpenClosed(f, 3, "name", libname);
        WriteXMLLineOpenClosed(f, 3, "comparefilename", curlibname);
        finallibname=getFilename(finallibname);
        // remove any extensions from libname
        string::size_type dot_loc = finallibname.find_last_of(".");
        if (dot_loc != string::npos)
            finallibname = finallibname.substr(0, dot_loc);    
        WriteXMLLineOpenClosed(f, 3, "shortname", finallibname);
        WriteXMLLineOpenClosed(f, 3, "baseplatform", getPlatform(libname));
        WriteXMLLineOpenClosed(f, 3, "currentplatform", getPlatform(curlibname));

        // write all single issues        
        for (unsigned int i=0; i<issue_list.size(); i++)
        {
            WriteXMLLineOpeningTag(f, 3, "issue");
            
            WriteXMLLineOpenClosed(f, 4, "typeid", Int2Str(issue_list.at(i).i_typeid));

            if (issue_list.at(i).i_funcname.length() > 0)          
                WriteXMLLineOpenClosed(f, 4, "funcname", issue_list.at(i).i_funcname);
            
            if (issue_list.at(i).i_newfuncname.length() > 0)          
                WriteXMLLineOpenClosed(f, 4, "newfuncname", issue_list.at(i).i_newfuncname);
            
            if (issue_list.at(i).i_funcpos > 0)          
                WriteXMLLineOpenClosed(f, 4, "funcpos", Int2Str(issue_list.at(i).i_funcpos));
    
            if (issue_list.at(i).i_newfuncpos > 0)          
                WriteXMLLineOpenClosed(f, 4, "newfuncpos", Int2Str(issue_list.at(i).i_newfuncpos));
                
            if (issue_list.at(i).i_BC_severity.length() > 0)
                WriteXMLLineOpenClosed(f, 4, "bc_severity", issue_list.at(i).i_BC_severity);

            if (issue_list.at(i).i_SC_severity.length() > 0)          
                WriteXMLLineOpenClosed(f, 4, "sc_severity", issue_list.at(i).i_SC_severity);            
            
            WriteXMLLineClosingTag(f, 3, "issue");
        }

		
				for (unsigned int i=0; i<dllIssue.i_list_typeid.size(); i++)
				{
					string typeinfo = "";
					WriteXMLLineOpeningTag(f, 3, "issue");
					WriteXMLLineOpenClosed(f, 4, "typeid", Int2Str(dllIssue.i_list_typeid.at(i)));
					typeinfo = GetDllBreakTypeInfoString(dllIssue.i_list_typeid.at(i));
					if(typeinfo.size() > 0)
						WriteXMLLineOpenClosed(f, 4, "typeinfo", typeinfo);

					if (dllIssue.i_list_typeid.at(i) == DLL_BASELINE_MISSING )
						WriteXMLLineOpenClosed(f, 4, "bc_severity", "Informative");            
					else
						WriteXMLLineOpenClosed(f, 4, "bc_severity", "BBC Break"); 

					WriteXMLLineOpenClosed(f, 4, "sc_severity", "None");            
					WriteXMLLineClosingTag(f, 3, "issue");
				}        

				// finally write footer        
				WriteXMLLineClosingTag(f, 2, "library");        
    }
}

// ----------------------------------------------------------------------------------------------------------

