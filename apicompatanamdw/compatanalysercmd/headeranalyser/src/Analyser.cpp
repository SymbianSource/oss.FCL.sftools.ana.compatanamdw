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
#include <time.h>
#include <map>
#include <list>
#include <algorithm>
#include <assert.h>
#include <fstream>
#include <stdlib.h>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#ifdef __WIN__
#include <io.h>
#include <direct.h>
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "Analyser.h"
#include "CPPParser.h"
#include "CommandLine.h"
#include "CommandFile.h"
#include "BBCFileUtils.h"
#include "HAException.h"
#include "BBCAnalyser.h"
#include "AnalyserParams.h"
#include "MacroAnalyser.h"
#include "Utils.h"
#include "PlatformData.h"

const int KMaxDirLength=1024;

boost::mutex m;
boost::mutex::scoped_lock lock(m,false); //for synchronizing creation & destruction of threads in gHeaderThreads

boost::thread_group gComponentThreads;
boost::thread_group gHeaderThreads;

boost::thread* gpComponentThreads[MAX_THREAD_COUNT];
boost::thread* gpHeaderThreads[MAX_THREAD_COUNT2];

XERCES_CPP_NAMESPACE_USE
typedef pair<string,string> stringpair;
//the total number of files to be processed
static int _total_files = 0;
//the number of files that have been processed
static int _current_files = 0;

// make sure globbing is turned off when GCC is used
int _CRT_glob = 0;

// Fill the headers having API Info in global vector, so that report generator can access it.
vector<pair<string,stringpair> > HeaderInfoList; // vector<pair< headerfile name, pair<API name, API category>>>

// ----------------------------------------------------------------------------
// Analyser::Analyser
// Constructor
// ----------------------------------------------------------------------------
//
Analyser::Analyser(char** args, int argc) : iCPPParser(NULL)
{
    iCmdLine = new CommandLine(args, argc);
    iUseBaselinePlatformData = false;   
    iUseCurrentPlatformData = false;
    iUseForcedHeaders = true;
    iBasePlatformData = 0;
    iProductPlatformData = 0;
}

// ----------------------------------------------------------------------------
// Analyser::Analyser
// Constructor
// ----------------------------------------------------------------------------
//
Analyser::Analyser()
{
    
}

// ----------------------------------------------------------------------------
// Analyser::Analyser
// Destructor
// ----------------------------------------------------------------------------
//
Analyser::~Analyser()
{
    delete iCmdLine;
    iCmdLine = NULL;
    if (iCPPParser != NULL)
    {
        delete iCPPParser;
        iCPPParser = NULL;
    }
    if (iBasePlatformData)
    {
      delete iBasePlatformData;
      iBasePlatformData = 0;
    }
    if ( iProductPlatformData)
    {
      delete iProductPlatformData;
      iProductPlatformData = 0;
    }
}

// ----------------------------------------------------------------------------
// Analyser::validateHeaders
// validates header for include guards
// ----------------------------------------------------------------------------
//
void Analyser::validateHeaders(vector<pair<string, string> >& aFiles, vector<pair<string, string> >& aUnsuccessful)
{
	int count = 0;
	string input;
	string files[2];
	bool exists[2];
	string guard[2];
	vector<string> guards[2];

	vector< pair<string, string> >::iterator fileStart = aFiles.begin();
	vector< pair<string, string> >::iterator fileEnd = aFiles.end();
	//vector used to temporarily hold file pairs with include guards
	vector< pair<string, string> > temp;
	while(fileStart != fileEnd )
	{
		files[0] = fileStart->first;
		files[1] = fileStart->second;
		for(int i=0; i<2; i++)
		{

			//check for include guard in Base header
			exists[i] = guardExists(files[i], guard[i]);
		}
		//if either Base or Current header in the PAIR do not have include guards
		//add the file pair to RemovedFiles list.
		if( !exists[0] || !exists[1] )
			aUnsuccessful.push_back(*fileStart);
		else 
		{
			if ( find(guards[0].begin(),guards[0].end(),guard[0]) == guards[0].end() && find(guards[1].begin(),guards[1].end(),guard[1]) == guards[1].end())
			{
				guards[0].push_back(guard[0]);
				guards[1].push_back(guard[1]);
				temp.push_back(*fileStart);			
			}
			else
			{
				aUnsuccessful.push_back(*fileStart);
			}
		}
	
		++fileStart;
	}
	guards[0].clear();
	guards[1].clear();
	aFiles.clear();
	aFiles = temp;
}

// ----------------------------------------------------------------------------
// Analyser::guardExists
// guard Exists checs to see if the input file has include guards
// ----------------------------------------------------------------------------
//
bool Analyser::guardExists(const string& aFile, string& aGuard)
{
	bool exists = false;
	string guard("");
	string input("");
	string temp("");
	//macro used in the #ifndef line
	pair<string,string> macroOne;
	//macro #defined subsequently
	pair<string,string> macroTwo;
	int linenum = 0;
	//linenum containing the #ifndef statement
	int ifndefline = 0;

	ifstream fileRead(aFile.c_str(), ios::in);
	if( !fileRead.is_open())
		throw HAException("Header file does not exist");;
	while( !fileRead.eof() )
	{
		linenum++;
		temp = getLine(fileRead);
		input = trimWhiteSpace(temp);
		// Check if #ifndef are being used
		// Get the MACRO string if they are present
		if(input.substr(0,7) == "#ifndef") 
		{
			macroOne = MacroAnalyser::FindMacro(input);
			ifndefline = linenum;
		}
		// checks for the usage of #if (!defined ...) in include guard defns
		else if (input.substr(0,3) == "#if")
		{
			string tempstr("!defined");
			//strip all braces from the Macro string
			while(input.find("(") < input.length())
			{
				replaceChar(input,'(',' ');
				replaceChar(input,')',' ');
			}
			//get the actual MACRO string after required temp modifications
			string::size_type index = input.find(tempstr);
			if (index == string::npos)
			  continue;
			index = index + tempstr.length();
			tempstr = input.substr( index );
			input = trimWhiteSpace(tempstr);
			pair<string,string> temppair(input, "");
			macroOne = temppair;
			ifndefline = linenum;
		}
		// Check if #define is used 
		else if (input.substr(0, 7) == "#define")
		{
			macroTwo = MacroAnalyser::FindMacro(input);
			//if macro strings used in both #ifndef and #define are same
			//consider that include guard exists
			//also verify that #define follows #if
			if( macroTwo.first == macroOne.first && macroTwo.second == macroOne.second && ifndefline < linenum )
			{
				exists = true;
				aGuard = macroOne.first;
			}
			break;
		}
		// additional statement will be used for early termination of the loop
		// in cases with no "include" guards
		else if( input.substr(0, 8) == "#include") 
		{
			exists = false;
			break;
		}
	}
	fileRead.close();
	return exists;
}

// ----------------------------------------------------------------------------
// Analyser::readParameters
// readParameters should be called so that first is called baseline command
// and after that current command, otherwise it doesn't work
// ----------------------------------------------------------------------------
//
void Analyser::readParameters(basetype type, list<pair<string, string> >& files, string& forcedheaders)
{    
    string headerset;
    string dir;
    string file;
    string platform;
    string forcedheadersfile;
    string forcedheaders_file;
    string version;
    string versionstr;
    BBCFileUtils* fileUtils = NULL;
    static basetype first = type;

    if (first != EBase)
    {
        cout << "Error: Parameter read has been called in wrong order.";
        exit(3);
    }

    switch(type)
    {
    case EBase:
        dir = BASELINEDIR;
        file = BASELINE;
        platform = BASELINEPLAT;
        forcedheadersfile = BASEFORCEDHEADERSFILE;
        version = BASELINEVERSION;
        versionstr = "BASELINE";
        break;
    case ECurrent:
        dir = CURRENTDIR;
        file = CURRENT;
        platform = CURRENTPLAT;
        forcedheadersfile = CURRENTFORCEDHEADERSFILE;
        version = CURRENTVERSION;
        versionstr = "CURRENT";
        break;
    default:
        cout << "Error: Unknown type (not baseline, nor current).";
        exit(3);
    }
  
    // Query the baseline-related command line parameters
    // since validation has passed, none of these should really
    // cause an exception
    try
    {
        if( iParams.parameterExists(BASEPLATFORMDATA))
        {
            iUseBaselinePlatformData = true;
            string pfdir(BBCFileUtils::getFullPath(iParams.getParameter(BASEPLATFORMDATA)));
            if (!BBCFileUtils::isValidFilename(pfdir))
            {
                throw HAException("Baseline platform data file '" + pfdir + "' is not valid.");
            }
            iParams.storeParameter(BASEPLATFORMDATA, pfdir);
        }
        if( iParams.parameterExists(CURRENTPLATFORMDATA))
        {
            iUseCurrentPlatformData = true;         
            string pfdir(BBCFileUtils::getFullPath(iParams.getParameter(CURRENTPLATFORMDATA)));
            if (!BBCFileUtils::isValidFilename(pfdir))
            {
                throw HAException("Current platform data file '" + pfdir + "' is not valid.");
            }
            iParams.storeParameter(CURRENTPLATFORMDATA, pfdir);
        }
        if (iParams.parameterExists(TEMPDIR))
        {
            string tempdir(BBCFileUtils::getFullPath(iParams.getParameter(TEMPDIR)));
            iParams.storeParameter(TEMPDIR, tempdir);
            if (!BBCFileUtils::isValidDirectory(tempdir))
            {
                throw HAException("Temporary directory '" + tempdir + "' is not valid directory.");
            }
        }
        if (iParams.parameterExists(REPORTFILE))
        {
            string reportfile(BBCFileUtils::getFullPath(iParams.getParameter(REPORTFILE)));
            iParams.storeParameter(REPORTFILE, reportfile);
            if (rightmostDirSeparatorIndex(reportfile) == reportfile.length() - 1 || BBCFileUtils::isValidDirectory(reportfile))
            {
                throw HAException("No filename given for report file.");
            }
            string reportdir = reportfile.substr(0, rightmostDirSeparatorIndex(reportfile));
            
            if (reportdir.size() == ANALYSER_REPORT_DIR_SIZE)
            {
                reportdir += DIR_SEPARATOR;
            }
            if (!BBCFileUtils::isValidDirectory(reportdir))
            {
                throw HAException("Directory for report file is non-existent.");
            }
        }
        if (iParams.parameterExists(HEADERSET))
        {
            iHeaderSetInUse = true;
        }
		if (iParams.parameterExists(USETHREAD))
        {
            iUseThread = true;
        }
        if (iParams.parameterExists(dir))
        {
            // START -- Support for multiple header directories
            // Validate the ; separated header paths and store them
            list<pair<string, string> > dirs = BBCFileUtils::extractFilenames(iParams.getParameter(dir));
            list<pair<string, string> >::iterator dirbegin = dirs.begin();
            string tempval = "";
        
            for(; dirbegin != dirs.end(); dirbegin++)
            {
                if (dirbegin != dirs.begin())
                {
                    tempval += ";";
                }
                string header = BBCFileUtils::getFullPath(dirbegin->first);

               if (header.length() != ANALYSER_HEADER_MAX_LENGTH && header.at(header.length() - 1) == DIR_SEPARATOR)
                {
                    header.resize(header.length() - 1);
                }

                if (!BBCFileUtils::isValidDirectory(header))
                {
                    string::size_type pos = rightmostDirSeparatorIndex(header);
                    string tempvar;
                    if (pos != header.length() - 1)
                    {
                        tempvar = header.substr(pos + 1);
                        header.resize(pos);
                    }

                    if (header.size() == ANALYSER_HEADER_SIZE)
                    {
                        header += DIR_SEPARATOR;
                    }
    
                    if (!BBCFileUtils::isValidDirectory(header) || tempvar.find_first_of("*?") == string::npos)
                    {
                        string errormsg;
                        errormsg = "Non-existent ";
                        if (type == EBase)
                        {
                            errormsg += "base";
                        } else
                        {
                            errormsg += "current";
                        }
                        errormsg += " directory '" + header + DIR_SEPARATOR + tempvar + "'.\n";
                        throw HAException(errormsg);
                    }
                }
                if (header.at(header.length() - 1) == DIR_SEPARATOR)
                {
                    header.resize(header.length() - 1);
                }
                tempval += header;
            }
            iParams.storeParameter(dir, tempval);
            // END -- Support for multiple header directories
        }
        else
        {
            iParams.storeParameter(file, BBCFileUtils::getFullPath(iParams.getParameter(file)));
        }
        
        // Location of baseline's platform headers
        list<pair<string, string> > platformheaders = BBCFileUtils::extractFilenames(iParams.getParameter(platform));
        list<pair<string, string> >::iterator platformbegin = platformheaders.begin();
        string tempval = "";
        for(; platformbegin != platformheaders.end(); platformbegin++)
        {
            if (platformbegin != platformheaders.begin())
            {
                tempval += ";";
            }
            string header = BBCFileUtils::getFullPath(platformbegin->first);

            if (header.length() != ANALYSER_HEADER_MAX_LENGTH && header.at(header.length() - 1) == DIR_SEPARATOR)
            {
                header.resize(header.length() - 1);
            }
            
            tempval += header;
        }
        iParams.storeParameter(platform, tempval);

        // Location of forced headers file (containing full names of headers that 
        // will be included to preprocessing and processing phases, e.g. e32base.h)
        if (iParams.parameterExists(forcedheadersfile))
        {
            // START -- Support for multiple forced headers
            list<pair<string, string> > fheaders = BBCFileUtils::extractFilenames(iParams.getParameter(forcedheadersfile));
            list<pair<string, string> >::iterator fheadersbegin = fheaders.begin();
            string tempval = "";
            
            //for each forced header, get the full path before storing it
            for(; fheadersbegin != fheaders.end(); fheadersbegin++)
            {
                if (fheadersbegin != fheaders.begin())
                {
                    tempval += ";";
                }
                tempval += BBCFileUtils::getFullPath(fheadersbegin->first);
            }
            iParams.storeParameter(forcedheadersfile, tempval);
            forcedheaders = iParams.getParameter(forcedheadersfile);
            // END -- Support for multiple forced headers
        }
        
        if (!iParams.parameterExists(version))
        {
            iParams.storeParameter(version, versionstr);
        }
    } catch (HAException& e)
    {
        cout << "Error: "<<e.errorMessage()<<"\n";
        exit(2);
    }

    // Instantiate file utilities that generate the file lists based on 
    // commandline parameters. In this try/catch block, we're
    // handling the baseline files
    try
    {
        if (iParams.parameterExists(dir))
        {
            // baselinedir/currentdir commandline parameters given
            fileUtils = new BBCFileUtils(iParams.getParameter(dir));
            fileUtils->setTemp(iParams.getParameter(TEMPDIR));
            string wildcard;
            list<stringpair > sets;
            list<stringpair > discarddirs;
            list<stringpair > foundfiles;
            list<stringpair > completefilenames; // Filenames that are complete, i.e no wildcards used.
            vector<string> wildcardsinset;
            
            if (type == EBase)
            {                
                // We are reading the parameters of the baseline platform               
                
                if(iHeaderSetInUse)
                {
                    // the files to be analysed are defined using 'set' parameter.
                    sets = fileUtils->extractFilenames(iParams.getParameter(HEADERSET));   
                }
                else
                {
                    // 'set' parameter is absent. Use default file types in the files to be analysed.
                    sets = fileUtils->extractFilenames(WILDCARD_DEFAULT);
                }
                    
                sets = canonicalizeFilename(sets);
                                
                for(list<stringpair >::iterator s = sets.begin(); s != sets.end(); ++s )
                {
                    if( s->first.find_first_of("*?") != string::npos )
                    {
                        // Wildcard is used in filename.
                        std::string wc(s->first);
                        wildcardsinset.push_back(wc);
                        list<stringpair > tmpfiles(fileUtils->getFilesInDir(wc, ""));
                        files.insert(files.end(), tmpfiles.begin(), tmpfiles.end());
                    }                
                    else
                    {
                        completefilenames.push_back(*s);
                    }
                }
                
                files.sort(LessStringPair);// Sort files 
                files.unique(); // Remove duplicates

                // Remove trailing directory separator from the filenames, that were found using the wildcard,
                // to be able to build <code>foundfiles</code> list for later use.
                list<stringpair> foundwithwildcard(files);
                std::for_each(foundwithwildcard.begin(), foundwithwildcard.end(),RemoveTrailingDirSeparator<stringpair>());

                // Find files given with complete filename
                list<stringpair> tempcompletefiles(completefilenames);
                list<stringpair > tmplist(fileUtils->getFilesInDir(tempcompletefiles, "",foundfiles));

                // Add files found with wildcard to <code>foundfiles</code>
                foundfiles.sort(LessStringPair);                
                foundfiles.merge(foundwithwildcard, LessStringPair);
                foundfiles.unique(); // Remove duplicates

                // Merge all found files:
                tmplist.sort( LessStringPair );                
                files.merge(tmplist, LessStringPair);
                files.unique(); // Remove duplicates                
                if (iParams.parameterExists(DISCARDDIRS))
                {
                    discarddirs = BBCFileUtils::extractFilenames(iParams.getParameter(DISCARDDIRS));
                }
            } else if (type == ECurrent)
            {
                // We are reading the parameters of the current platform 
                // and the files to be analysed are defined using 'set' parameter.
                wildcard = WILDCARD_ALLFILES;
                files = fileUtils->getFilesInDir(wildcard, "");
                if (iParams.parameterExists(DISCARDDIRS))
                {
                    discarddirs = BBCFileUtils::extractFilenames(iParams.getParameter(DISCARDDIRS));
                }
            } else
            {
                // No 'set' parameter used
                wildcard = iParams.getParameter(BASELINE);
                files = fileUtils->getFilesInDir(wildcard, "");
                if (iParams.parameterExists(DISCARDDIRS))
                {
                    discarddirs = BBCFileUtils::extractFilenames(iParams.getParameter(DISCARDDIRS));
                }
            }
            if (iParams.parameterExists(RECURSIVE))
            {
                list<pair<string, string> > dirs = fileUtils->getDirsInDir("",discarddirs);
                while(!dirs.empty())
                {
                    string dir = dirs.front().first;
                    dirs.pop_front();
                    list<pair<string, string> > morefiles;
                    if (type == EBase)
                    {
                        // Read files which were given as complete names in the -set parameter:
                        morefiles = fileUtils->getFilesInDir(completefilenames, dir,foundfiles);

                        // Read files which were given as wildcards in the -set parameter:
                        for( vector<string>::iterator wc = wildcardsinset.begin(); wc != wildcardsinset.end(); ++wc)
                        {
                            list<pair<string, string> > tmpfiles = fileUtils->getFilesInDir(*wc, dir);
                            morefiles.insert(morefiles.end(), tmpfiles.begin(), tmpfiles.end());
                        }
                    } 
                    else
                    {
                        morefiles = fileUtils->getFilesInDir(wildcard, dir);
                    }
                    morefiles.sort(LessStringPair);
                    morefiles.unique();
                    list<pair<string, string> >::const_iterator file = morefiles.begin();
                    list<pair<string, string> >::const_iterator fileend = morefiles.end();
                    for(; file != fileend; file++)
                    {
                        files.push_back(*file);
                    }
                    list<pair<string, string> > moredirs = fileUtils->getDirsInDir(dir,discarddirs);
                    while(!moredirs.empty())
                    {
                        pair<string, string> direntry = moredirs.front();
                        moredirs.pop_front();
                        dirs.push_back(direntry);
                    }
                }
            }
            if (type == EBase)
            {
                list<pair<string, string> > notfound;
                diffs(files, sets, notfound);
                if (!notfound.empty())
                {
                    string errormessage = "Following files could not be found in baseline:\n";
                    list<pair<string, string> >::iterator file = notfound.begin();
                    list<pair<string, string> >::iterator fileend = notfound.end();
                    for(; file != fileend; file++)
                    {
                        errormessage += file->first;
                        errormessage += "\n";
                    }
					//this case has now been redefined as a input error that can be handled
					//the file is removed from the list to be analysed, and execution continues
                    //throw HAException(errormessage);
                }
            }
        }
        else
        {
            // baseline/current commandline parameters given
            string file_val = iParams.getParameter(file);
            string f = getFilenameWithoutDir(file_val);
            iParams.storeParameter(file, f);
            file_val.resize(file_val.length() - f.length() - 1);
            iParams.storeParameter(dir, file_val);
            fileUtils = new BBCFileUtils(iParams.getParameter(dir));
            fileUtils->setTemp(iParams.getParameter(TEMPDIR));
            pair<string, string> tempvar(f, toLowerCaseWin(f));
            files.push_back(tempvar);
        }
    } catch (HAException& e)
    {
        // something went wrong. Make a clean exit
        if (fileUtils != NULL)
        {
            delete fileUtils;
            fileUtils = NULL;
        }
        cout << "Error: " << e.errorMessage() << "\n";
        exit(2);
    }
    
    delete fileUtils;
    fileUtils = NULL;

}

// ----------------------------------------------------------------------------
// Analyser::processParameters
// processParameters
// ----------------------------------------------------------------------------
//
int Analyser::processParameters()
{
    string err = "";

    // Validate command-line parameters.
    // If they are not sound and complete, break off with an error message.
    try
    {
        err = iCmdLine->validateParameters();
    } catch (HAException& e)
    {
        cout << "ERROR: Bad parameters, quitting. Type ha -? for help.\n";
        cout << e.errorMessage();
        cout << "\n";
        return (2);
    }

    if (err.size() > 0)
    {
        cout << "ERROR: Parameter validation fail. Type ha -? for help.\n";
        cout << err << "\n";
        return (2);
    }
    
    map<string, string> params = iCmdLine->getParameters();
    map<string, string>::iterator begin = params.begin();
    map<string, string>::iterator end = params.end();
    while (begin != end)
    {
        iParams.storeParameter((*begin).first,(*begin).second, true);
        ++begin;
    }

    // readParameters should be called so that first is called baseline command
    // and after that current command, otherwise it doesn't work

    // Read base dependent parameters
    readParameters(EBase, iFiles, iForcedBaselineHeaders);
    // ..and current ones
    readParameters(ECurrent, iFiles2, iForcedCurrentHeaders);

#if defined(_DEBUG) || defined(DEBUG)
    if(iParams.parameterExists(COMMANDLINETEST))
    {
        map<string, string> params = iParams.getGivenParameters();
        map<string, string>::iterator begin = params.begin();
        map<string, string>::iterator end = params.end();
        while (begin != end)
        {
            cout << "Param: '" << (*begin).first << "' Value: '" << (*begin).second << "'\n";
            begin++;
        }
        exit(100);
    }
#endif

    return 0;
}

// ----------------------------------------------------------------------------
// Analyser::analyseTrees
// processParameters
// ----------------------------------------------------------------------------
//
int Analyser::analyseTrees(DOMNode* baseline, DOMNode* current, const list< pair<string,string> >& files, ReportGenerator& report)
{
    int ret = 0;
    //print progress information for files which have compiled
    list< pair<string,string> >::const_iterator begin = files.begin();
    list< pair<string,string> >::const_iterator end = files.end();
    
    while (begin != end)
    {
        _current_files++;
		cout << "\nAnalysing files (" << _current_files << "/" << _total_files << "): " << (*begin).first <<" => "<< (*begin).second << endl;
        begin++;
    }

    BBCAnalyser analyser(report);
    ret =  analyser.analyseTrees(baseline, current, files, iMacroFiles);

    return ret;
}

// ----------------------------------------------------------------------------
// Analyser::handleBundlesizeParam
// Get bundlesize value
// ----------------------------------------------------------------------------
//
int Analyser::handleBundlesizeParam()
{
    int bundlesize=1; 

    if (iParams.parameterExists(BUNDLESIZE))
    {
        string tempstr = iParams.getParameter(BUNDLESIZE);
        if (tempstr.length() > 0)
        {
            bundlesize = atoi(tempstr.c_str());
            if (bundlesize < 1)
            {
                bundlesize = 1;
            } 
            else if (bundlesize > MAX_BUNDLESIZE)
            {
                bundlesize = MAX_BUNDLESIZE;                
            }
        }
    }

    if (bundlesize >= BUNDLESIZE_WARNING)
    {
    cout << "Note: Processing in large bundles, this may have a negative "
         << "performance impact and/or produce unwanted artifacts.\n";
    }
    return bundlesize;
}

// ----------------------------------------------------------------------------
// Analyser::getReplaceParam
// Get Replace parameter value
// ----------------------------------------------------------------------------
//
string Analyser::getReplaceParam()
{
    string replace;
    // File renames
    if (iParams.parameterExists(FILEREPLACE))
    {
        replace = iParams.getParameter(FILEREPLACE);
    } else
    {
        replace = "";
    }

    return replace;
}



PlatformHeaders::iterator FindHeaderPair(const string& ID, PlatformHeaders& pfHeaders)
{
    for( PlatformHeaders::iterator i = pfHeaders.begin(); i != pfHeaders.end(); ++i )
    {
        if( i->first->ID() == ID )
        {
            return i;
        }
    }
    return pfHeaders.end();
}
// ----------------------------------------------------------------------------
// Analyzes one component at a time.
// 
// 
// ----------------------------------------------------------------------------
//
void Analyser::AnalyzePlatforms(PlatformHeaders& pfHeaders, PlatformHeaders& unsuccessfulHdrs, ReportGenerator& report, int& issues, bool createThread)
{
	string epocRoot("epoc32");
	epocRoot += DIR_SEPARATOR + string("include"); 
	// START -- Support for multiple header directories       
	list<pair<string, bool> > baseEpocRoot = BBCFileUtils::MergeDirs(iParams.getParameter(BASELINEDIR), epocRoot);
	list<pair<string, bool> > currEpocRoot = BBCFileUtils::MergeDirs(iParams.getParameter(CURRENTDIR), epocRoot);
	// END -- Support for multiple header directories
	for( PlatformHeaders::iterator pfHdr = pfHeaders.begin(); pfHdr != pfHeaders.end(); ++pfHdr )
	{        
		if( pfHdr->first->Status() == Header::HDR_STATUS_TO_BE_ANALYZED /*|| pfHdr->first->Status() == Header::HDR_STATUS_INVALID*/)
		{
			stringvector baseIncPaths;  // This contains include paths needed to compile baseline headers
			stringvector currIncPaths;  // This contains include paths needed to compile product headers

			baseIncPaths.clear();
			currIncPaths.clear();
			
			iBaseFilenames.clear();
			iCurrFilenames.clear();
			iBaseIncludes.clear();
			iCurrIncludes.clear();
			iInvalidFiles.clear();

			// All headers in the (baseline platform) component:
			FileList& baseCmpHeaders = pfHdr->first->GetComponent()->Headers();             
			iBaseFilenames.reserve(baseCmpHeaders.size());
			iCurrFilenames.reserve(baseCmpHeaders.size());

			// Make sure that the epoc32/include directory is always in include paths:
			// START -- Support for multiple header directories
			list<pair<string, bool> >::iterator iter1 = baseEpocRoot.begin();
			for(; iter1 != baseEpocRoot.end(); iter1++)
			{
				if( iter1->second )
				{
					baseIncPaths.push_back(iter1->first);
				}  
			}
			list<pair<string, bool> >::iterator iter2 = currEpocRoot.begin();
			for(; iter2 != currEpocRoot.end(); iter2++)
			{         
				if( iter2->second )
				{
					currIncPaths.push_back(iter2->first);
				}
			}
			// END -- Support for multiple header directories
			
			string forcedHeader;
			char* base = new char[KMaxDirLength+1];
			getcwd(base, KMaxDirLength);

			vector< stringpair > tmpfiles;	
			vector< stringpair > invalid;
			// Loop all the headers that are in the same component:
			for( FileList::iterator bH = baseCmpHeaders.begin(); bH != baseCmpHeaders.end(); ++bH )
			{
				Header* baseHdr = dynamic_cast<Header*>(*bH);
							
				PlatformHeaders::iterator pairIter = FindHeaderPair(baseHdr->ID(), pfHeaders);
				if(pairIter != pfHeaders.end() && pairIter->second != 0)
				{
					// If analysing in bundle, get the headers to be anaysed to validate for include guard before addition to bundle.
					if( (pfHeaders.size() > 1) && baseHdr && (baseHdr->Status() == Header::HDR_STATUS_TO_BE_ANALYZED) )
					{
						stringpair tmp(baseHdr->ID(), pairIter->second->ID());
						tmpfiles.push_back(tmp);
					}
				}
			}
			
			if(tmpfiles.size())
			{
				// If analysing in bundle, validate for include guard before addition to bundle.
				validateHeaders(tmpfiles, invalid);
				// Exclude "iInvalidFiles" from bundle analysis. Analyse them only singly. 
				if( invalid.size() )
				{
					for( int i=0 ; i < invalid.size() ; i++ )
					{
					
						PlatformHeaders::iterator pairIter = FindHeaderPair(invalid[i].first, pfHeaders);
						//No need to check if the invalid file exists in pfHeaders, as it already done above. 
						HeaderPair temp(pairIter->first, pairIter->second);
						if(find(iInvalidFiles.begin(), iInvalidFiles.end(), temp) == iInvalidFiles.end())
							iInvalidFiles.push_back(temp);
						pairIter->first->SetStatus(Header::HDR_STATUS_INVALID);	
					}
				}
			}

			for( FileList::iterator bH = baseCmpHeaders.begin(); bH != baseCmpHeaders.end(); ++bH )
			{
				Header* baseHdr = dynamic_cast<Header*>(*bH);
							
				PlatformHeaders::iterator pairIter = FindHeaderPair(baseHdr->ID(), pfHeaders);
				if(pairIter != pfHeaders.end() && pairIter->second != 0)
				{
					
					// If the status is "to be analyzed" , get this header to the bundle too
					if( baseHdr && 
						(baseHdr->Status() == Header::HDR_STATUS_TO_BE_ANALYZED ))
					{                       
						// Find all additional includes that are needed in compilation of this header:   
						const vector<string>& bIncs = iBasePlatformData->IncludesForHeader(baseHdr);                    
						forcedHeader.clear();
						forcedHeader = baseHdr->CachedForcedInclude();
						// Find all include paths that are needed in compilation of this header:
						const vector<string>& bPaths = iBasePlatformData->IncludePathsForHeader(baseHdr);                    

						// Add include paths for baseline platform headers:   
						// START -- Support for multiple header directories                                     
						for( vector<string>::const_iterator i = bPaths.begin(); i != bPaths.end(); ++i )
						{
							list<pair<string, bool> > fullIncPath = BBCFileUtils::MergeDirs(iParams.getParameter(BASELINEDIR), *i);
							list<pair<string, bool> >::iterator fulliterbegin = fullIncPath.begin();
							for(; fulliterbegin != fullIncPath.end(); fulliterbegin++)
							{
								if( find(baseIncPaths.begin(), baseIncPaths.end(), fulliterbegin->first) == baseIncPaths.end() )
								{
									baseIncPaths.push_back(fulliterbegin->first);
								}
							}
						}                    

						// Add additional include directives to header list:
						for( vector<string>::const_iterator i = bIncs.begin(); i != bIncs.end(); ++i )
						{                          
							// Make sure the header exists, because we don't want to generate new compilation errors...
							bool exists = false;
							// Test that header exists by merging the header name with include paths:
							for( stringvector::iterator ip = baseIncPaths.begin(); ip != baseIncPaths.end(); ++ip )
							{
								list<pair<string, bool> > fullIncPath = BBCFileUtils::MergeDirs( *ip, *i );
								list<pair<string, bool> >::iterator fulliterbegin = fullIncPath.begin();
								for(; fulliterbegin != fullIncPath.end(); fulliterbegin++)
								{                           
									if( find(iBaseIncludes.begin(), iBaseIncludes.end(), fulliterbegin->first) == iBaseIncludes.end() )
									{
										if( BBCFileUtils::FileExists(fulliterbegin->first) )
										{                                    
											iBaseIncludes.push_back(fulliterbegin->first);
											exists = true;
											break; 
										}                                
									}
								}
							}
							if( exists == false )
							{
								// Try to find the included header from the same directory than the header itself is:
								list<pair<string, bool> > fullIncPath = 
									BBCFileUtils::MergeDirs(iParams.getParameter(BASELINEDIR), baseHdr->Path() + DIR_SEPARATOR + *i);                            

								list<pair<string, bool> >::iterator fulliterbegin = fullIncPath.begin();
								for(; fulliterbegin != fullIncPath.end(); fulliterbegin++)
								{
									if( BBCFileUtils::FileExists(fulliterbegin->first) )
									{                         
										iBaseIncludes.push_back(fulliterbegin->first);
									} 
								}                           
							}
						}
						// END -- Support for multiple header directories

						// Add this header to the list of headers that are needed for compilation:                    
						if( find(iBaseIncludes.begin(), iBaseIncludes.end(), baseHdr->ID()) == iBaseIncludes.end())
						{
							iBaseIncludes.push_back(baseHdr->ID());
						}

						// Add headers to the list of headers that are to be analyzed:										
						iBaseFilenames.push_back(baseHdr->ID());
						iCurrFilenames.push_back(pairIter->second->ID());
						baseHdr->SetStatus(Header::HDR_STATUS_READY);
       
						forcedHeader = DIR_SEPARATOR + forcedHeader;
						forcedHeader = base + forcedHeader;
						if( BBCFileUtils::isValidFilename(forcedHeader) )
							if( find(iBaseIncludes.begin(), iBaseIncludes.end(), forcedHeader) == iBaseIncludes.end())
								iBaseIncludes.insert(iBaseIncludes.begin(),forcedHeader);
              
              
						// Then we need to find corresponding headers from the product (current) platform:                                        
					
						Header* currHeader = pairIter->second; //Current header

						// Find additional includes and include paths for the current platform's header:
						const vector<string>& cIncs = iProductPlatformData->IncludesForHeader(currHeader, baseHdr);                        
						forcedHeader.clear();
						forcedHeader =currHeader->CachedForcedInclude(); 
						const vector<string>& cPaths =iProductPlatformData->IncludePathsForHeader(currHeader);                        

						// Add include paths to the list, if it does not exist there yet:
						for( vector<string>::const_iterator i = cPaths.begin(); i != cPaths.end(); ++i )
						{
							// SART -- Support for multiple header directories
							list<pair<string, bool> > fullIncPath = BBCFileUtils::MergeDirs(iParams.getParameter(CURRENTDIR), *i);
							list<pair<string, bool> >::iterator fulliterbegin = fullIncPath.begin();
							for(; fulliterbegin != fullIncPath.end(); fulliterbegin++)
							{
								if( find(currIncPaths.begin(), currIncPaths.end(), fulliterbegin->first) == currIncPaths.end() )
								{
									currIncPaths.push_back(fulliterbegin->first);
								}
							}
							// END -- Support for multiple header directories
						}

						// Add additional include directives to header list:
						for( vector<string>::const_iterator i = cIncs.begin(); i != cIncs.end(); ++i )
						{
							bool exists = false;
							// Make sure the header exists, because we don't want to generate new compilation errors...
							for( stringvector::iterator ip = currIncPaths.begin(); ip != currIncPaths.end(); ++ip )
							{
								// START -- Support for multiple header directories
								list<pair<string, bool> > fullIncPath = BBCFileUtils::MergeDirs( *ip, *i );
								list<pair<string, bool> >::iterator fulliterbegin = fullIncPath.begin();
								for(; fulliterbegin != fullIncPath.end(); fulliterbegin++)
								{
									if( find(iCurrIncludes.begin(), iCurrIncludes.end(), fulliterbegin->first) == iCurrIncludes.end() )
									{                                        
										if( BBCFileUtils::FileExists(fulliterbegin->first) )
										{
											iCurrIncludes.push_back(fulliterbegin->first);
											exists = true;
											break;
										}                                    
									}
								}
								// END -- Support for multiple header directories
							}
							if( exists == false )
							{
								// Try to find the included header from the same directory than the header itself is:
								// START -- Support for multiple header directories
								list<pair<string, bool> > fullIncPath = 
									BBCFileUtils::MergeDirs(iParams.getParameter(CURRENTDIR), currHeader->Path() + DIR_SEPARATOR + *i);                            
								list<pair<string, bool> >::iterator fulliterbegin = fullIncPath.begin();
								for(; fulliterbegin != fullIncPath.end(); fulliterbegin++)
								{
									if( BBCFileUtils::FileExists(fulliterbegin->first) )
									{                                
										iCurrIncludes.push_back(fulliterbegin->first);
									}
								}
								// END -- Support for multiple header directories
							}
						}
							// Add this header to the list:                        
						if( find(iCurrIncludes.begin(), iCurrIncludes.end(), currHeader->ID()) == iCurrIncludes.end())
						{
							iCurrIncludes.push_back(currHeader->ID());                            
						}
					
						forcedHeader = DIR_SEPARATOR + forcedHeader;
						forcedHeader = base + forcedHeader;
						if( BBCFileUtils::isValidFilename(forcedHeader) )
							if( find(iCurrIncludes.begin(), iCurrIncludes.end(), forcedHeader) == iCurrIncludes.end())
								iCurrIncludes.insert(iCurrIncludes.begin(),forcedHeader);
									
					}
				}
			}
			// Build include paths for parser objects:
			string bIP;
			for( stringvector::iterator i = baseIncPaths.begin(); i != baseIncPaths.end(); ++i )
			{
				if( i != baseIncPaths.begin() )
					bIP += ";";

				bIP += *i;
			}

			string cIP;
			for( stringvector::iterator i = currIncPaths.begin(); i != currIncPaths.end(); ++i )
			{
				if( i != currIncPaths.begin() )
					cIP += ";";

				cIP += *i;
			}

			// Construct parsers:
			auto_ptr<CPPParser> parser(new CPPParser(bIP));
			auto_ptr<CPPParser> parser2(new CPPParser(cIP));

			// Set temp directories for parsers
			parser->setTemp(iParams.getParameter(TEMPDIR));
			parser2->setTemp(iParams.getParameter(TEMPDIR));

			// Set forced headers 
			if(iUseForcedHeaders)
			{
				parser->setForcedHeaders(iForcedBaselineHeaders);
				parser2->setForcedHeaders(iForcedCurrentHeaders);
			}

			if (createThread)
			{		
				//if the number of threads in this group has reached pre-defined max count, destroy all the threads in this group before creating one.
				//boost::thread_group object does not destroy a thread when it goes to completion. if the threads are not destroyed lot of memory will be eaten up unneccessarily
				if(gHeaderThreads.size() >= MAX_THREAD_COUNT)
				{
				
					gHeaderThreads.join_all();
					int size = gHeaderThreads.size();
					for(int i=0;i<size;i++)
					{
						gHeaderThreads.remove_thread(gpComponentThreads[i]);
						gpComponentThreads[i]->~thread();	
					}
				}
						
				//create a copy of the Analyser object for the new thread
				Analyser* obj = new Analyser();
				*obj = *this;
				int size = gHeaderThreads.size();
				gpComponentThreads[size]=gHeaderThreads.create_thread(boost::bind(&Analyser::Wrapper,obj, boost::ref(report), boost::ref(issues), *(parser.get()), *(parser2.get()), boost::ref(pfHeaders), boost::ref(unsuccessfulHdrs)));				
			}
			else //do not create different thread for the second time when AnalyzePlatforms is called recurssively
			{
				Wrapper(report, issues, *(parser.get()), *(parser2.get()), pfHeaders, unsuccessfulHdrs);	
			}		
		}
	}
	
}

// ----------------------------------------------------------------------------
// Analyser::InitializePlatforms
// 
// 
// ----------------------------------------------------------------------------
//
void Analyser::InitializePlatforms(PlatformHeaders& pfHeaders, vector<pair<string, string> >& headers, 
								   vector<pair<string, string> >& excludeheaders, vector<pair<string, string> >& resourcevector)
{
	if( iBasePlatformData )
		delete iBasePlatformData;
	if( iProductPlatformData )
		delete iProductPlatformData;

	iBasePlatformData = new PlatformData(iParams.getParameter(BASELINEVERSION),
		iParams.getParameter(BASELINEDIR));
	iProductPlatformData = new PlatformData(iParams.getParameter(CURRENTVERSION),
		iParams.getParameter(CURRENTDIR));

	if( iUseBaselinePlatformData )
		iBasePlatformData->Initialize(iParams.getParameter(BASEPLATFORMDATA));
	if( iUseCurrentPlatformData )
		iProductPlatformData->Initialize(iParams.getParameter(CURRENTPLATFORMDATA));

	vector<pair<string, string> > updatedHdrs;
	updatedHdrs.reserve(headers.size());    

	// Mark the platform header objects with status 'HDR_STATUS_TO_BE_ANALYZED':
	vector<pair<string, string> >::const_iterator hdr = headers.begin();

	for( ;hdr != headers.end(); ++hdr )
	{
		pair<string,stringpair> headerInfo;
		bool is_Resource = false;
		int loc = -1;
		pair<string,string> resource;
		Header* baseHdrObj = 0;
		Header* currHdrObj = 0;        
		string hdrTest(hdr->first);
		toLower(hdrTest);

		// Check whether the header is a resource file. If, so add it to resource vector instead of pfheaders.
		if( (loc = int(hdrTest.find_last_of("."))) != string::npos &&
			hdrTest.substr(loc,string::npos) == RH_EXTENSION )
		{
			is_Resource = true;
			resource.first = hdrTest;
		}
		CFileMap::const_iterator bI = iBasePlatformData->HeadersById().find(hdrTest);
		if( bI != iBasePlatformData->HeadersById().end() )
		{
			baseHdrObj = dynamic_cast<Header*>((*bI).second);
		}

		hdrTest = hdr->second;
		toLower(hdrTest);
		if(is_Resource == true)
		{
			resource.second = hdrTest;
			resourcevector.push_back(resource);
		}

		CFileMap::const_iterator cI = iProductPlatformData->HeadersById().find(hdrTest);
		if( cI != iProductPlatformData->HeadersById().end() )
		{
			currHdrObj = dynamic_cast<Header*>((*cI).second);
		}

		if(baseHdrObj && baseHdrObj->Status()== Header::HDR_STATUS_IGNORE )
		{
			excludeheaders.push_back(*hdr);
		}
		else if( baseHdrObj && currHdrObj )
		{
			if( is_Resource == false)
			{
				pfHeaders.push_back(HeaderPair(baseHdrObj, currHdrObj));
				baseHdrObj->SetStatus(Header::HDR_STATUS_TO_BE_ANALYZED);
				currHdrObj->SetStatus(Header::HDR_STATUS_TO_BE_ANALYZED);
			}

			// get API info from current header
			if(currHdrObj->APIinfo().first.size() > 0)
			{
				headerInfo.first = currHdrObj->ID();
				headerInfo.second.first = currHdrObj->APIinfo().first; // API NAME
				headerInfo.second.second = currHdrObj->APIinfo().second; // API REL. CATEGORY
			}

		}
		else
		{
			// get API info from base header
			if(baseHdrObj && baseHdrObj->APIinfo().first.size() > 0)
			{
				headerInfo.first = baseHdrObj->ID();
				headerInfo.second.first = baseHdrObj->APIinfo().first; // API NAME
				headerInfo.second.second = baseHdrObj->APIinfo().second; // API REL. CATEGORY

			}
			// get API info from current header
			else if(currHdrObj && currHdrObj->APIinfo().first.size() > 0)
			{
				headerInfo.first = currHdrObj->ID();
				headerInfo.second.first = currHdrObj->APIinfo().first; // API NAME
				headerInfo.second.second = currHdrObj->APIinfo().second; // API REL. CATEGORY
			}
			// No info found from platform data, so use common include paths and 
			// other common compile-time parameters for this header:
			if( is_Resource == false)
			updatedHdrs.push_back(*hdr);
		}
		// Fill the headers having API Info in global vector, so that report generator can access it.
		if(headerInfo.first.size() > 0)
		{
			HeaderInfoList.push_back(headerInfo);
		}
	}
	headers = updatedHdrs;
}

// ----------------------------------------------------------------------------
// Analyser::analyse
// Do the actual analyse of headers
// Create analysis report
// ----------------------------------------------------------------------------
//
int Analyser::analyse()
{
	// Local variable instantiation
	int ret = 0;
	iHeaderSetInUse = false;
	iUseForcedHeaders = true;
	iUseThread = false;
	string epocroot;
	int bundlesize = 1;
	unsigned int amount, amount2;
	iOnlySystemIncludeRequired = false;
	unsigned int excludedHeaderSize;

	if (processParameters() == 2) return 2;

	// Get the bundle size (as string) and convert it to an integer
	bundlesize = handleBundlesizeParam();

	// Get replace parameter for file renaming
	string replace = getReplaceParam();

	// Update the amount of found files
	amount = (unsigned int)iFiles.size();
	// Update the amount of found files
	amount2 = (unsigned int)iFiles2.size();

	// Vector that holds the merge results and if it can't find baseline
	// file from current file it will put empty string as current file
	vector<pair<string,string> > mergeVector;
	mergeVector.reserve(amount);

	// List holds files which were found in current but not in baseline.
	// Full path
	list<string> addedFiles;

	// List holds files which were in baseline file list but
	// weren't in current file list, ie they were removed.
	// Contains full path with filename
	list<string> removedFiles;
	try
	{
		// Merges baseline and current files into one vector
		MergeFiles(iFiles, iFiles2, replace, mergeVector);

		// Finds removed files
		fileDiffs(mergeVector, removedFiles);
	}
	catch (HAException e)
	{
		cout << "Error in processing file lists:\n" << e.errorMessage() << "\n";
		exit(4);
	}

	// Mergemap now contains pairs of following type:
	// baseline complex filename (w/ absolute path) -> current version complex filename (w/ absolute path)
	_total_files = (unsigned int)mergeVector.size();

	cout << "\nTotal baseline files: " << amount << "\nTotal current files: " << amount2 << "\nFile pairs found: "
		<< _total_files << "\n";

	cout << "\nComparing " << _total_files << " matching files between\n " << iParams.getParameter(BASELINEDIR)
		<< " (Version " << iParams.getParameter(BASELINEVERSION) << ")\nand\n " << iParams.getParameter(CURRENTDIR)
		<< " (Version " << iParams.getParameter(CURRENTVERSION) << ")\n\n\n\n";

	
	ReportGenerator report(iParams.getParameter(REPORTFILE));
	report.setCmdLineParms(iParams.getGivenParameters());
	report.setVersions(iParams.getParameter(BASELINEVERSION),iParams.getParameter(CURRENTVERSION));
	report.setXSL("BBCResults.xsl",false);
	

	report.startReport();
	// start the timer
	time_t starttime;
	time_t endtime;
	starttime = time(NULL);
	
	PlatformHeaders pfHeaders;
	pfHeaders.reserve(mergeVector.size());

	// Vector that holds the the headers those should be excluded from analysis.
	// These header files are mentioned in platform headers
	vector<pair<string,string> > excludeHeaders;
	excludeHeaders.reserve(mergeVector.size());


	// Headers that are found from platform data are inserted in pfHeaders.
	// Others are left to mergeVector.
	vector<pair<string, string> > resourceVector;
	resourceVector.reserve(mergeVector.size());

	if(mergeVector.size() > 0 )
		InitializePlatforms(pfHeaders, mergeVector,excludeHeaders,resourceVector);
	excludedHeaderSize = int(excludeHeaders.size());	

	endtime = time(NULL);
	time_t pfInitTime = endtime - starttime;
	time_t originalStartTime = starttime;
	starttime = time(NULL);

	//Now analyse Resource Header RH files using text parser
	if(resourceVector.size()>0)
		ParseAndCompareResourceFiles(resourceVector, report);

	// Process each removed filename from removedMap
	list<string>::iterator removedbegin = removedFiles.begin();
	list<string>::iterator removedend = removedFiles.end();
	for(; removedbegin != removedend; removedbegin++)
	{
		string filename = *removedbegin;
		report.addIssue(filename, "", EIssueIdentityFile, EIssueTypeRemoval, ESeverityBBCBreak, ESeveritySCBreak, "", 0, "","");
	}

	int issues = 0;
	PlatformHeaders unsuccessfulHeaders;
	vector<pair<string, string> > unsuccessfulHeaderNames;
	vector<pair<string, string> > platformUnsuccessfulHeaderNames;
	int compErrors = 0;

	//validate if the headers have include guards,
	//move ones without guards for individual compilation
	validateHeaders(mergeVector, unsuccessfulHeaderNames);

	boost::thread_group mainThreads;
	int mergeVectorCompErrs = 0;
	int unsuccessfulCompErrs = 0;
	int platformUnsuccessfulCompErrs = 0;

	// Analyse headers that were not found from platform data:	
	if( mergeVector.size() > 0 )
	{
		//create copy of Analyser object for the new thread
			Analyser* obj1=new Analyser();
			*obj1=*this;
			//analyse mergeVector in different thread
			mainThreads.create_thread(boost::bind(&Analyser::AnalyseHeaders,obj1,boost::ref(mergeVector),bundlesize,boost::ref(report),boost::ref(issues),boost::ref(mergeVectorCompErrs)));
	}
	
	// Compile unsuccessful headers one by one, because it is unlikely that they
	// will be compiled successfully here either:
	if( unsuccessfulHeaderNames.size() > 0 )
	{
		//create copy of Analyser object for the new thread
			Analyser* obj2 = new Analyser();
			*obj2=*this;
			//analyse unsuccessfulHeaderNames in different thread
			mainThreads.create_thread(boost::bind(&Analyser::AnalyseHeaders,obj2,boost::ref(unsuccessfulHeaderNames),1,boost::ref(report),boost::ref(issues),boost::ref(unsuccessfulCompErrs)));
	}
	
	if(pfHeaders.size() > 0)
	{
		AnalyzePlatforms(pfHeaders, unsuccessfulHeaders, report, issues, iUseThread);    
		if (iUseThread)
		{
			gHeaderThreads.join_all(); // wait for all threads in gHeaderThreads to complete
			gComponentThreads.join_all(); // wait for all threads in gComponentThreads to complete

			//destroy the thredas in gHeaderThreads
			int size = gHeaderThreads.size();
			for (int i=0;i<size;i++)
			{
				gHeaderThreads.remove_thread(gpComponentThreads[i]);
				gpComponentThreads[i]->~thread();
			}

			//destroy the thredas in gComponentThreads
			size=gComponentThreads.size();
			for (int i=0;i<size;i++)
			{
				gComponentThreads.remove_thread(gpHeaderThreads[i]);
				gpHeaderThreads[i]->~thread();
			}
		}
		
		for( PlatformHeaders::iterator i = unsuccessfulHeaders.begin(); i != unsuccessfulHeaders.end(); ++i )
		{  
			// Build list of headers that could not be compiled with platform data:
			platformUnsuccessfulHeaderNames.push_back(pair<string, string>(i->first->ID(), i->second->ID()));
		}
		
		if(platformUnsuccessfulHeaderNames.size() >0)
			AnalyseHeaders(platformUnsuccessfulHeaderNames, 1, report, issues, platformUnsuccessfulCompErrs); 
	}
	
	mainThreads.join_all(); // wait for all threads in mainThreads to complete
	compErrors += mergeVectorCompErrs + unsuccessfulCompErrs + platformUnsuccessfulCompErrs;
	report.finishReport();

	// List number of files which had compilation errors and could not be compiled	
	if ( _current_files + excludedHeaderSize < _total_files )
		cout << "\n" << ( _total_files - (_current_files + excludedHeaderSize) ) <<"  files out of " << _total_files << " had some issues and could not be analysed.\n" << endl;

	// Wrap up the run and print statistics
	unsigned int count = _total_files * 2;

	endtime = time(NULL);
	time_t runningtime = endtime - starttime;
	double timedelta = 0.0;
	if (count > 0)
	{
		timedelta = (double)runningtime/(double)count;
	}
	cout << "\n";
	cout << "---------------------------------------------" << endl;
	cout << "Finished!" << endl;
	cout << "Files processed: " << count << endl;
	cout << "Total time: " << endtime - originalStartTime << " seconds." << endl;
	cout << "Platform data initialization time: " << pfInitTime << " seconds.\n";
	cout << "Compilation and analysis time: " << (long)runningtime << " seconds (Average: "<<timedelta<<" seconds per file).\n";
	cout << "Compilation errors: " << compErrors << endl;
	if(excludedHeaderSize > 0 )
	cout << "No of excluded headers: " << excludedHeaderSize << endl;
	cout << "---------------------------------------------" << endl;

	if (iNotRemovedFiles.size() != 0)
	{
		cout << iNotRemovedFiles.size() << "\n";
		list<string> tempvar;
		list<string>::iterator removefile = iNotRemovedFiles.begin();
		list<string>::iterator fileend = iNotRemovedFiles.end();
		for(; removefile != fileend; removefile++)
		{
			CPPParser::RemoveFile(*removefile, tempvar);
		}
		if (tempvar.size() != 0)
		{
			iNotRemovedFiles = tempvar;
		} else
		{
			iNotRemovedFiles.clear();
		}
	}

	if (ret == 0 && issues != 0)
	{
		ret = 1;
	}
	return ret;
}

void Analyser::AnalyseHeaders(const vector<pair<string, string> >& headerList, int bundlesize, ReportGenerator& report, int& issues, int& compErrors)
{    
	unsigned int processedcount = 1;    
	stringvector basefilenames;
	stringvector curfilenames;
	vector<pair<string, string> > unsuccessfulHeaders;
	
	vector<pair<string, string> >::const_iterator fnmapiter = headerList.begin();
	while (fnmapiter != headerList.end())
	{
		// Push the pair's members to their respective vectors
		// for bundle handling
		basefilenames.push_back(fnmapiter->first);
		curfilenames.push_back(fnmapiter->second);

		// If a bundle is full or the item is the last one to process,
		// we parse the current file lists to xml files
		if ((processedcount > 0 && (processedcount % bundlesize == 0)) || 
			processedcount == headerList.size())
		{
			if (!AnalyseBundle(basefilenames,curfilenames,report, issues))
			{
				//If there where parsing errors in a bundle, we try to compile each header
				// one by one
				stringvector::iterator basebegin = basefilenames.begin();
				stringvector::iterator baseend = basefilenames.end();
				stringvector::iterator currentbegin = curfilenames.begin();

				if( basefilenames.size() == 1 ||
					bundlesize == 1 )

				{
					if( basebegin != baseend )
					{
						if(!iUseForcedHeaders)
						{
							//Add compilation error to the report
							string compilationError = iCompErrTxt;
							report.addIssue((*basebegin), "", EIssueIdentityFile, EIssueTypeCompilationError, ESeverityBBCBreak, ESeveritySCBreak, "", 0,
								(*currentbegin),compilationError);
							issues++;						
						}
						else
							unsuccessfulHeaders.push_back(pair<string,string>(*basebegin,*currentbegin));
							
						compErrors++;
					}
				}
				else
				{
					while(basebegin != baseend )
					{
						stringvector basefilename;
						stringvector curfilename;
						basefilename.push_back(*basebegin);
						curfilename.push_back(*currentbegin);
						if (!AnalyseBundle(basefilename,curfilename,report, issues))
						{
							if(!iUseForcedHeaders)
							{
								//Add compilation error to the report						
								string compilationError = iCompErrTxt;
								report.addIssue((*basebegin), "", EIssueIdentityFile, EIssueTypeCompilationError, ESeverityBBCBreak, ESeveritySCBreak, "", 0,
									(*currentbegin),compilationError);
								issues++;								
							}
							else
								unsuccessfulHeaders.push_back(pair<string,string>(*basebegin,*currentbegin));
							
							compErrors++;
						}
						basebegin++;
						currentbegin++;
					}
				}
			}
			basefilenames.clear();
			curfilenames.clear();
		}

		fnmapiter++;
		processedcount++;
	}
	
	if( compErrors > 0 && iUseForcedHeaders )
	{
		iUseForcedHeaders = false;
		issues = 0;
		compErrors = 0;   
		AnalyseHeaders(unsuccessfulHeaders, 1, report, issues, compErrors);
		iUseForcedHeaders = true;
	}
	
	if (iNotRemovedFiles.size() != 0)
	{            
		list<string> tempvar;
		list<string>::iterator removefile = iNotRemovedFiles.begin();
		list<string>::iterator fileend = iNotRemovedFiles.end();
		for(; removefile != fileend; removefile++)
		{
			CPPParser::RemoveFile(*removefile, tempvar);
		}
		if (tempvar.size() != 0)
		{
			iNotRemovedFiles = tempvar;
		} 
		else
		{
			iNotRemovedFiles.clear();
		}
	} 
	
}

// ----------------------------------------------------------------------------
// Analyser::AnalyseBundle
// ----------------------------------------------------------------------------
//
//bool Analyser::AnalyseBundle(const stringvector& basefilenames, const stringvector& curfilenames, ReportGenerator& report, int& issues)
bool Analyser::AnalyseBundle(const stringvector& basefilenames, 
                             const stringvector& curfilenames, 
                             ReportGenerator& report, 
                             int& issues,
                             CPPParser* baseParser,
                             CPPParser* currParser,
                             stringvector* basecompileset,
                             stringvector* currcompileset)
{
	auto_ptr<CPPParser> baseAutoPtr;
	auto_ptr<CPPParser> currAutoPtr;
	CPPParser* parser  = 0;
	CPPParser* parser2 = 0;

	if( baseParser )
	{
		// This function does not own the pointer, so no auto_ptr used here.
		parser = baseParser;
	}
	else
	{
		parser = new CPPParser(iParams.getParameter(BASELINEPLAT));
		// Set temp directory for parser
		parser->setTemp(iParams.getParameter(TEMPDIR));
		// Set forced headers
		if(iUseForcedHeaders)
		parser->setForcedHeaders(iForcedBaselineHeaders);
		// Wrap allocated memory to an auto_ptr to get it deallocated properly.
		baseAutoPtr.reset(parser);                                  
	}
	if( currParser )
	{
		// This function does not own the pointer, so no auto_ptr used here.
		parser2 = currParser;        
	}
	else
	{
		parser2 = new CPPParser(iParams.getParameter(CURRENTPLAT));
		// Set temp directory for parser
		parser2->setTemp(iParams.getParameter(TEMPDIR));
		// Set forced headers
		if(iUseForcedHeaders)
		parser2->setForcedHeaders(iForcedCurrentHeaders);
		// Wrap allocated memory to an auto_ptr to get it deallocated properly.
		currAutoPtr.reset(parser2);
	}

	try 
	{
		// Parse the filename vectors into XML and eventually into a DOM format
		DOMNode* root = 0;
		DOMNode* root2 = 0;
		if(basecompileset && basecompileset->size() != 0 )
		{
			root = parser->parse(*basecompileset, "base", iParams.getParameter(BASELINEDIR), iNotRemovedFiles);
		}
		else
		{
			root = parser->parse(basefilenames, "base", iParams.getParameter(BASELINEDIR), iNotRemovedFiles);
		}
		if(currcompileset && currcompileset->size() != 0 )
		{
			root2 = parser2->parse(*currcompileset, "current", iParams.getParameter(CURRENTDIR), iNotRemovedFiles);
		}
		else
		{
			root2 = parser2->parse(curfilenames, "current", iParams.getParameter(CURRENTDIR), iNotRemovedFiles);
		}

		MacroAnalyser macros(parser->getMacroFilename(), parser2->getMacroFilename(), basefilenames, curfilenames);

		macros.Analyse(iMacroFiles);

#if !defined(_DEBUG) && !defined(DEBUG)
		parser->RemoveFile(parser->getMacroFilename(), iNotRemovedFiles);
		parser2->RemoveFile(parser2->getMacroFilename(), iNotRemovedFiles);
		parser->RemoveFile(parser->getCompErrFile(), iNotRemovedFiles);
		parser2->RemoveFile(parser2->getCompErrFile(), iNotRemovedFiles);
#endif
		// Merged macros
		//
		list<pair<string,string> > mergedfiles;
		stringvector::const_iterator basebegin = basefilenames.begin();
		stringvector::const_iterator baseend = basefilenames.end();
		stringvector::const_iterator currentbegin = curfilenames.begin();
		while(basebegin != baseend)
		{
			mergedfiles.push_back(pair<string,string>(*basebegin,*currentbegin));
			basebegin++;
			currentbegin++;
		}
		if(mergedfiles.size() > 0)
		{
			issues += analyseTrees(root, root2,mergedfiles,report);
		}

		// Duplicated macros
		//
		// Base duplicates
		map<string, vector<pair<string,string> > >& duplicatedMacros = macros.getBaseDuplicates();
		map<string, vector<pair<string,string> > >::iterator duplicatedbegin = duplicatedMacros.begin();
		map<string, vector<pair<string,string> > >::iterator duplicatedend = duplicatedMacros.end();
		for(; duplicatedbegin != duplicatedend; duplicatedbegin++)
		{
			string filename = duplicatedbegin->first;
			// Process each duplicated macro from duplicatedMacros
			vector<pair<string,string> >::iterator duplicatedbegin2 = duplicatedbegin->second.begin();
			vector<pair<string,string> >::iterator duplicatedend2 = duplicatedbegin->second.end();
			for(; duplicatedbegin2 != duplicatedend2; duplicatedbegin2++)
			{
				string macroname = duplicatedbegin2->first;
				int lineNo = atoi(duplicatedbegin2->second.c_str());
				report.addIssue(filename, macroname, EIssueIdentityMacro, EIssueTypeNotAnalysed, ESeverityInformative, ESeveritySCInformative, "", lineNo, "", "");
				issues++;
			}
		}

		// Current
		map<string, vector<pair<string,string> > >& currDuplicatedMacros = macros.getCurrentDuplicates();
		duplicatedbegin = currDuplicatedMacros.begin();
		duplicatedend = currDuplicatedMacros.end();
		for(; duplicatedbegin != duplicatedend; duplicatedbegin++)
		{
			string filename = duplicatedbegin->first;
			// Process each duplicated macro from duplicatedMacros
			vector<pair<string,string> >::iterator duplicatedbegin2 = duplicatedbegin->second.begin();
			vector<pair<string,string> >::iterator duplicatedend2 = duplicatedbegin->second.end();
			for(; duplicatedbegin2 != duplicatedend2; duplicatedbegin2++)
			{
				string macroname = duplicatedbegin2->first;
				int lineNo = atoi(duplicatedbegin2->second.c_str());
				report.addIssue("", macroname, EIssueIdentityMacro, EIssueTypeNotAnalysed, ESeverityInformative, ESeveritySCInformative, "", lineNo, filename, "");
				issues++;
			}
		}

		// Removed macros
		//
		map<string, TChange<list<pair<string,string> > > >& removedMacros = macros.getRemoved();
		map<string, TChange<list<pair<string,string> > > >::iterator removedbegin = removedMacros.begin();
		map<string, TChange<list<pair<string,string> > > >::iterator removedend = removedMacros.end();
		for(; removedbegin != removedend; removedbegin++)
		{
			string basefilename = removedbegin->second.GetBase();
			string currentfilename = removedbegin->second.GetCurrent();
			// Process each removed macro from removedMacros
			list<pair<string,string> >::iterator removedbegin2 = removedbegin->second.GetValue().begin();
			list<pair<string,string> >::iterator removedend2 = removedbegin->second.GetValue().end();
			for(; removedbegin2 != removedend2; removedbegin2++)
			{
				string macroname = removedbegin2->first;
				//int lineNo = atoi(removedbegin2->second.c_str());
				// No need to pass the line no in removed case.
				report.addIssue(basefilename, macroname, EIssueIdentityMacro, EIssueTypeRemoval, ESeverityPossibleBBCBreak, ESeveritySCBreak, "", 0, currentfilename, "");
				issues++;
			}
		}

		// Changed macros
		//
		map<string, TChange<map<string, pair<pair<string,string>,string> > > >& changedMacros = macros.getChanged();
		map<string, TChange<map<string, pair<pair<string,string>,string> > > >::iterator changedbegin = changedMacros.begin();
		map<string, TChange<map<string, pair<pair<string,string>,string> > > >::iterator changedend = changedMacros.end();
		for(; changedbegin != changedend; changedbegin++)
		{
			string basefilename = changedbegin->second.GetBase();
			string currentfilename = changedbegin->second.GetCurrent();
			// Process each changed macro from changedMacros
			map<string, pair<pair<string,string>,string> >::iterator changedbegin2 = changedbegin->second.GetValue().begin();
			map<string, pair<pair<string,string>,string> >::iterator changedend2 = changedbegin->second.GetValue().end();
			for(; changedbegin2 != changedend2; changedbegin2++)
			{
				string macroname = changedbegin2->first;
				string newcode = changedbegin2->second.first.second;
				int lineNo = atoi(changedbegin2->second.second.c_str());
				report.addIssue(basefilename, macroname, EIssueIdentityMacro, EIssueTypeChange, ESeverityPossibleBBCBreak, ESeveritySCNULL, newcode, lineNo, currentfilename, "");
				issues++;
			}
		}

		
		//clear the last set of files with macros
		iMacroFiles.clear();
	} catch (HAException e)
	{
#if !defined(_DEBUG) && !defined(DEBUG)
		parser->RemoveFile(parser->getMacroFilename(), iNotRemovedFiles);
		parser2->RemoveFile(parser2->getMacroFilename(), iNotRemovedFiles);
#endif

		//header has failed compilation with gccxml. get the compilation error text.
		if (parser2->getCompErrFile()!="")
		{
			iCompErrTxt = BBCFileUtils::getCompilationError(parser2->getCompErrFile());
			if (iCompErrTxt == "")
				iCompErrTxt = BBCFileUtils::getCompilationError(parser->getCompErrFile());
		}
		else 
		{
			if(parser->getCompErrFile()!="")
				iCompErrTxt = BBCFileUtils::getCompilationError(parser->getCompErrFile());
		}
#if !defined(_DEBUG) && !defined(DEBUG)
		parser->RemoveFile(parser->getCompErrFile(), iNotRemovedFiles);
		parser2->RemoveFile(parser2->getCompErrFile(), iNotRemovedFiles);
#endif

		
		//delete parser;
		//delete parser2;
		return false;
	}
	//delete parser;
	//delete parser2;
	return true;
}


// ----------------------------------------------------------------------------
// Analyser::processFileReplaces
// Process the file replaces
// ----------------------------------------------------------------------------
//
pair<string, string> Analyser::processFileReplaces(pair<string, string>& aFile, const stringmap& aReplaceMap, list<pair<string, string> >& aCurrentFiles)
{
    string searched(aFile.second);
    pair<string, string>  replacement(aFile);
    // If there are items on replace map, then apply the
    // replaces when necessary
    if (aReplaceMap.size() > 0)
    {
        StringMapIterC fileMapIter = aReplaceMap.find(searched);
        if (fileMapIter != aReplaceMap.end())
        {
            string file = fileMapIter->second;
            list<pair<string, string> >::const_iterator filereplace = FindFromList(toLowerCaseWin(file), aCurrentFiles, ERightValue, compareFiles);
            if (filereplace != aCurrentFiles.end())
            {
                replacement = *filereplace;
            }
        }
    }

    return replacement;
}


// ----------------------------------------------------------------------------
// Analyser::createReplaceMap
//
// ----------------------------------------------------------------------------
//
void Analyser::createReplaceMap(const string& aReplaceList, stringmap& aReplaceMap)
{
    string originalfilename("");
    string replacementfilename("");
    string* name = &originalfilename;
    bool original = true;
    bool isstr = false;
    for (size_t i = 0; i < aReplaceList.length(); i++)
    {
        char ch = aReplaceList.at(i);
        if (ch == ' ' && isstr == false)
        {
            if (original == true)
            {
                original = false;
                name = &replacementfilename;
            }
            else
            {
                // Pair separator found. 
                // Store the pair (original, replacement)
                stringpair mappair(toLowerCaseWin(originalfilename), toLowerCaseWin(replacementfilename));
                aReplaceMap.insert(mappair);
                replacementfilename.resize(0);
                originalfilename.resize(0);

                original = true;
                name = &originalfilename;
            }
        } else if (ch == '"')
        {
            if (isstr == true)
            {
                isstr = false;
            } else
            {
                isstr = true;
            }
        } else
        {
            *name += ch;
        }
    }
    if (original == true)
    {
        throw HAException("Syntax error: There has been given file name to replace but not file name for replace.");
    }
    if (originalfilename.length() > 0 && replacementfilename.length() > 0)
    {
        // Store the last pair in replacement list
        stringpair mappair(toLowerCaseWin(originalfilename), toLowerCaseWin(replacementfilename));
        aReplaceMap.insert(mappair);
    }
}

// ----------------------------------------------------------------------------
// Analyser::fileDiffs
// ----------------------------------------------------------------------------
//
void Analyser::fileDiffs(vector<pair<string, string> >& aFiles, list<string>& aMismatches)
{
    vector<pair<string, string> > ret;
    ret.reserve(aFiles.size());
    vector<pair<string, string> >::iterator file = aFiles.begin();
    vector<pair<string, string> >::iterator fileend = aFiles.end();
    
    for(;file != fileend; file++)
    {
        // START -- Support for multiple header directories
        list<pair<string, string> > basedirs = BBCFileUtils::extractFilenames(iParams.getParameter(BASELINEDIR));
        list<pair<string, string> >::iterator basedirbegin = basedirs.begin();
        string basedir;
        string basefile;
        for(; basedirbegin != basedirs.end(); basedirbegin++)
        {
            // Find the base dir from the list of base dirs
            basedir = basedirbegin->first;
            basefile = basedir + DIR_SEPARATOR + file->first;
            if (BBCFileUtils::FileExists(basefile))
                break;
        }  
    
        list<pair<string, string> > curdirs = BBCFileUtils::extractFilenames(iParams.getParameter(CURRENTDIR));
        list<pair<string, string> >::iterator curdirbegin = curdirs.begin();
        string curdir;
        string curfile;
        for(; curdirbegin != curdirs.end(); curdirbegin++)
        {
            // Find the current dir from the list of current dirs
            curdir = curdirbegin->first;
            curfile = curdir + DIR_SEPARATOR + file->second;
            if (BBCFileUtils::FileExists(curfile))
                break;
        } 
        // END -- Support for multiple header directories
         
        if (file->second == "")
        {
            // We hadn't find matching file from current list so we add it to removed list
            aMismatches.push_back(basefile);
        } else
        {
            pair<string, string> tempvar(basefile, curfile);
            ret.push_back(tempvar);
        }
    }
    aFiles = ret;
}

// ----------------------------------------------------------------------------
// Analyser::getFilenameWithoutDir
// Return the file part of the filename, eg. retuns the rightmost part of
// the given string, up to a "\" // or "/" separator.
// ----------------------------------------------------------------------------
//
string Analyser::getFilenameWithoutDir(const string& aFilename)
{
    string ret = aFilename;
    string::size_type idx = rightmostDirSeparatorIndex(aFilename);
    if (idx != string::npos)
    {
        ret = aFilename.substr(idx+1, aFilename.length() - idx);
    }
    return ret;
}

// ----------------------------------------------------------------------------
// Analyser::testFileAvailability
// ----------------------------------------------------------------------------
//
#if 0
void Analyser::testFileAvailability(stringmap map)
{
    stringmap::iterator begin = map.begin();
    stringmap::iterator end = map.end();

    for(; begin!= end; begin++)
    {
        string file = (*begin).first;

        int isValid = ACCESS(file.c_str(), 0);
        if (isValid == -1)
        {
            throw HAException("File: \"" + file + "\" not found");
        }
        
        file = (*begin).second;

        isValid = ACCESS(file.c_str(), 0);
        if (isValid == -1)
        {
            throw HAException("File: \"" + file + "\" not found");
        }
    }
}

#endif

// ----------------------------------------------------------------------------
// Analyser::MergeFiles
// ----------------------------------------------------------------------------
//
void Analyser::MergeFiles(const list<pair<string, string> >& aBasefiles, list<pair<string, string> >& aCurrentfiles,
                          const string& aReplaceList, vector<pair<string, string> >& aMatches)
{
    size_t asdf = aBasefiles.size();
    list<pair<string, string> >::const_iterator baseiter = aBasefiles.begin();
    list<pair<string, string> >::const_iterator baseend = aBasefiles.end();
    list<pair<string, string> > removedcurrentfiles;
    list<pair<string, string> > mismatches;
    if (!iParams.givenParameter(BASELINE))
    {
        stringmap replaceMap;
        if (aReplaceList.length() > 0)
        {            
            createReplaceMap(aReplaceList, replaceMap);         
            stringmap::iterator begin = replaceMap.begin();
            stringmap::iterator end = replaceMap.end();
        }                
        for(; baseiter != baseend; baseiter++)
        {            
            pair<string, string> file = *baseiter;
            file = processFileReplaces(file, replaceMap, aCurrentfiles);
            pair<string,string> tempvar;
			//compareWholeString will be set to true, 
			//only if the file name with whole path of current file need to compare with base file.
			//else by default will always be set to false.
            list<pair<string, string> >::iterator current = FindFromList(file.second, aCurrentfiles, ERightValue, compareFiles, false,true);
            if (current != aCurrentfiles.end())
            {
                tempvar.first = baseiter->first.substr(1);
                tempvar.second = current->first.substr(1);
                aMatches.push_back(tempvar);
                removedcurrentfiles.push_back(*current);
                aCurrentfiles.erase(current);
            } else
            {
                current = FindFromList(file.second, removedcurrentfiles, ERightValue, compareFiles, false);
                if (current != removedcurrentfiles.end())
                {
                    tempvar.first = baseiter->first.substr(1);
                    tempvar.second = current->first.substr(1);
                    aMatches.push_back(tempvar);
                } else
                {
                    mismatches.push_back(file);
                }
            }
        }        
        baseiter = mismatches.begin();
        baseend = mismatches.end();        
        for(; baseiter != baseend; baseiter++)
        {
            string filename = BBCFileUtils::StripPath(baseiter->second);
            pair<string, string> file(filename, filename); // We don't need to put filename to lowercase as it's already in lowercase
            file = processFileReplaces(file, replaceMap, aCurrentfiles);
            string empty("");
            pair<string,string> tempvar;
            tempvar.first = baseiter->first.substr(1);
            list<pair<string, string> >::iterator current = FindFromList(file.second, aCurrentfiles, ERightValue, compareFiles);
            if (current != aCurrentfiles.end())
            {
                tempvar.second = current->first.substr(1);
            } else
            {
                tempvar.second = empty;
            }
            aMatches.push_back(tempvar);
        }        
    } else
    {
        // START -- Support for multiple header directories
        list<pair<string, string> > basedirs = BBCFileUtils::extractFilenames(iParams.getParameter(BASELINEDIR));
        list<pair<string, string> >::iterator basedirbegin = basedirs.begin();
        bool  basefilefound = false;
        string basefile;
        for(; basedirbegin != basedirs.end(); basedirbegin++)
        {
            string basedir = basedirbegin->first;       
            basefile = basedir + DIR_SEPARATOR + aBasefiles.front().first;

            if (ACCESS(basefile.c_str(), 0) != -1)
            {
                basefilefound = true;
                break;
            }
      }
        list<pair<string, string> > curdirs = BBCFileUtils::extractFilenames(iParams.getParameter(CURRENTDIR));
        list<pair<string, string> >::iterator curdirbegin = curdirs.begin();
        bool  curfilefound = false;
        string curfile;
        
        for(; curdirbegin != curdirs.end(); curdirbegin++)
        {
            string curdir = curdirbegin->first;       
            curfile = curdir + DIR_SEPARATOR + aBasefiles.front().first;
            if (ACCESS(curfile.c_str(), 0) != -1)
            {
                curfilefound = true;
                break;
            }
        }
        if (!basefilefound )
        {
            throw HAException("File \"" + basefile + "\" not found");
        }
        if (!curfilefound)
        {
            throw HAException("File \"" + curfile + "\" not found");
        }
        pair<string,string> tempvar(aBasefiles.front().first, aCurrentfiles.front().first);
        aMatches.push_back(tempvar);
        // END -- Support for multiple header directories
    }
}

// ----------------------------------------------------------------------------
// AnalyserParams::diffs
//  	
// ----------------------------------------------------------------------------
//
void Analyser::diffs(   const list<pair<string, string> >& allfiles, 
                        const list<pair<string, string> >& sets, 
                        list<pair<string, string> >& result)
{
    result = sets;
    list<stringpair >::iterator setiter = result.begin();
    while(setiter != result.end())
    {
        if( setiter->first.find_first_of("*?") != string::npos )
            setiter = result.erase(setiter);
        else
            ++setiter;
    }
    
    list<pair<string, string> >::const_iterator file = allfiles.begin();
    list<pair<string, string> >::const_iterator fileend = allfiles.end();
    for(; file != fileend; file++)
    {    
        list<pair<string, string> >::iterator set = 
            FindFromList(file->second, result, ERightValue);
        if (set == result.end())
        {
            set = FindFromList(file->second, result, ERightValue, compareFiles);
        }
        
        if (set != result.end())
        {
            result.erase(set);
        }
    }
    
}

// ----------------------------------------------------------------------------
// AnalyserParams::canonicalizeFilename
// Get the actual name of a file. 
// ----------------------------------------------------------------------------
//
list<pair<string, string> > Analyser::canonicalizeFilename(list<pair<string, string> >& sets)
{
    list<pair<string, string> > ret;
    list<pair<string, string> >::iterator begin = sets.begin();
    list<pair<string, string> >::iterator end = sets.end();
    for(; begin != end; begin++)
    {
        if (begin->first.at(0) != DIR_SEPARATOR && begin->first.find(DIR_SEPARATOR) != string::npos)
        {
            string left = "";
            left += DIR_SEPARATOR;
            left += begin->first;
            string right = "";
            right += DIR_SEPARATOR;
            right += begin->second;
            ret.push_back(pair<string, string>(left, right));
        } else
        {
            ret.push_back(*begin);
        }
    }

    return ret;
}


// ----------------------------------------------------------------------------
// Analyser::Wrapper
// Wrapper function to analyse all files in a component in separate thread.
// 
// ----------------------------------------------------------------------------
//
void Analyser::Wrapper( ReportGenerator& report, 
                        int& issues, 
                        CPPParser baseParser, 
                        CPPParser currParser, 
                        PlatformHeaders& pfHeaders, 
                        PlatformHeaders& unsuccessfulHdrs
                       )
{
	stringvector tiBaseFilenames; // This contains also additional headers needed to compile baseline
	stringvector tiCurrFilenames; // This contains also additional headers needed to compile product  
	PlatformHeaders tiInvalidFiles;	// holds a list of files without include guards need to be compiled individually
	stringvector tiBaseIncludes; // This contains also additional headers needed to compile baseline
	stringvector tiCurrIncludes; // This contains also additional headers needed to compile product  

	stringvector baseSysIncludes; // This contains headers needed to compile baseline for 3rd time analyzation of a single header.
	stringvector curSysIncludes;  //  This contains headers needed to compile product for 3rd time analyzation of a single header.

	tiBaseFilenames.assign(iBaseFilenames.begin(),iBaseFilenames.end());
	tiCurrFilenames.assign(iCurrFilenames.begin(),iCurrFilenames.end());
	tiInvalidFiles.assign(iInvalidFiles.begin(),iInvalidFiles.end());
	tiBaseIncludes.assign(iBaseIncludes.begin(),iBaseIncludes.end());
	tiCurrIncludes.assign(iCurrIncludes.begin(),iCurrIncludes.end());
	
	if (iOnlySystemIncludeRequired == true)
	{
		//tiBaseIncludes and tiCurrIncludes are required for 3rd time analyzation.
		//This time parse each unsuccessful header with both system includes and paths.
		baseSysIncludes.assign(tiBaseIncludes.begin(),tiBaseIncludes.end());
		curSysIncludes.assign(tiCurrIncludes.begin(),tiCurrIncludes.end());

		// Clear these includes as for 2nd time parsing of each unsuccessful headres, 
		//as only system include paths arerequuired.
		tiBaseIncludes.clear();
		tiCurrIncludes.clear();
	}
	
	
	if( (tiBaseIncludes.size()>0 && tiCurrIncludes.size()>0)|| (tiBaseFilenames.size()>0 && tiCurrFilenames.size()>0) )
	{
		if( AnalyseBundle(tiBaseFilenames, tiCurrFilenames, report, issues, &baseParser, &currParser, &tiBaseIncludes, &tiCurrIncludes))
		{
			tiBaseFilenames.clear();
			tiCurrFilenames.clear();
		}
	}

	if (iNotRemovedFiles.size() != 0)
	{            
		list<string> tempvar;
		list<string>::iterator removefile = iNotRemovedFiles.begin();
		list<string>::iterator fileend = iNotRemovedFiles.end();
		for(; removefile != fileend; removefile++)
		{
			CPPParser::RemoveFile(*removefile, tempvar);
		}
		if (tempvar.size() != 0)
		{
			iNotRemovedFiles = tempvar;
		} 
		else
		{
			iNotRemovedFiles.clear();
		}
	}  
	
	if(tiInvalidFiles.size() > 0)
	{
		// also add to this list, the set of headers
		// without include guards
		PlatformHeaders::iterator add = tiInvalidFiles.begin();
		for(; add != tiInvalidFiles.end(); ++add )
		{
			tiBaseFilenames.push_back( add->first->ID() );
			tiCurrFilenames.push_back( add->second->ID() );
		}
	}		
	
	// if thread flag is set and there are gretaer number of files, create threads for analysing every PLATFORM_BUNDLESIZE number of files
	if( iUseThread && tiBaseFilenames.size() >= PLATFORM_BUNDLESIZE  )
	{
		stringvector tmp;
		int pcount = 0;
		stringvector::iterator i = tiBaseFilenames.begin();                
		for(; i != tiBaseFilenames.end(); ++i )
		{				
			pcount++;
			PlatformHeaders::iterator h = FindHeaderPair(*i, pfHeaders);
			if( h != pfHeaders.end() )
			{			
				tmp.push_back(*i);
			}			
			if ((pcount % PLATFORM_BUNDLESIZE == 0 || pcount == tiBaseFilenames.size()) && tmp.size()>0)		
			{
				while (lock.locked())
				{
					#ifdef __WIN__
					Sleep(4000);
					#else
					usleep(4000*1000);
					#endif
				}
				lock.lock();
				
				if(gComponentThreads.size() >= MAX_THREAD_COUNT2)
				{
					gComponentThreads.join_all();
					int size = gComponentThreads.size();
					for (int i=0;i<size;i++)
					{	
						gComponentThreads.remove_thread(gpHeaderThreads[i]);
						gpHeaderThreads[i]->~thread();	
					}				
				}
						
				//2nd time analyzation of each header in a different thread
				Analyser* obj = new Analyser();
				*obj = *this;
				int size = gComponentThreads.size();
				gpHeaderThreads[size]=gComponentThreads.create_thread(boost::bind(&Analyser::Wrapper2,obj,tmp, 
						boost::ref(pfHeaders), boost::ref(unsuccessfulHdrs), boost::ref(report), boost::ref(issues)));
				lock.unlock();	
				tmp.clear();
							
			}
		}
	}
	else // do not create different thread. analyse in the same thread.
	{						
		stringvector::iterator i = tiBaseFilenames.begin();                
		for(; i != tiBaseFilenames.end(); ++i )
		{                    
			PlatformHeaders::iterator h = FindHeaderPair(*i, pfHeaders);
			if( h != pfHeaders.end() )
			{
				if(( pfHeaders.size() > 1 ) )
				{
					PlatformHeaders tempHeaders;
					tempHeaders.push_back(*h);
					h->first->SetStatus(Header::HDR_STATUS_TO_BE_ANALYZED);
					iOnlySystemIncludeRequired = true;
					//2nd time analyzation of each header in same thread
					AnalyzePlatforms( tempHeaders, unsuccessfulHdrs, report, issues, false );
					iOnlySystemIncludeRequired = false;
				}
				else
				{
					//The 3rd time parsing is required to check again each unsuccessful headers 
					//with system includes and paths from platform data
					if(!AnalyseBundle(tiBaseFilenames, tiCurrFilenames, report, issues, &baseParser, &currParser, &baseSysIncludes, &curSysIncludes))
					{
						if( FindHeaderPair(h->first->ID(), unsuccessfulHdrs ) == unsuccessfulHdrs.end() )
						{
							unsuccessfulHdrs.push_back(*h); 
						}
					} 
					if (iNotRemovedFiles.size() != 0)
					{            
						list<string> tempvar;
						list<string>::iterator removefile = iNotRemovedFiles.begin();
						list<string>::iterator fileend = iNotRemovedFiles.end();
						for(; removefile != fileend; removefile++)
						{
							CPPParser::RemoveFile(*removefile, tempvar);
						}
						if (tempvar.size() != 0)
						{
							iNotRemovedFiles = tempvar;
						} 
						else
						{
							iNotRemovedFiles.clear();
						}
					}	
				}                        
			}
		}	
	}	
}  

// ----------------------------------------------------------------------------
// Analyser::Wrapper2
// Wrapper function to analyse group of files in a component individually in different thread.
// 
// ----------------------------------------------------------------------------
//
void Analyser::Wrapper2(stringvector filenames, PlatformHeaders& pfHeaders, PlatformHeaders& unsuccessfulHdrs, ReportGenerator& report, int& issues)
{
	PlatformHeaders tempHeaders;
	stringvector::iterator i = filenames.begin();                
	for(; i != filenames.end(); ++i )
	{	
		PlatformHeaders::iterator h = FindHeaderPair(*i, pfHeaders);
		if( h != pfHeaders.end() )
		{	
			tempHeaders.push_back(*h);
			h->first->SetStatus(Header::HDR_STATUS_TO_BE_ANALYZED);
			iOnlySystemIncludeRequired = true;	
			AnalyzePlatforms( tempHeaders, unsuccessfulHdrs, report, issues, false );
			iOnlySystemIncludeRequired = false;
		}
	}	

	if (iNotRemovedFiles.size() != 0)
					{            
						list<string> tempvar;
						list<string>::iterator removefile = iNotRemovedFiles.begin();
						list<string>::iterator fileend = iNotRemovedFiles.end();
						for(; removefile != fileend; removefile++)
						{
							CPPParser::RemoveFile(*removefile, tempvar);
						}
						if (tempvar.size() != 0)
						{
							iNotRemovedFiles = tempvar;
						} 
						else
						{
							iNotRemovedFiles.clear();
						}
					}
}



void Analyser::ParseAndCompareResourceFiles(vector<pair< string, string> >& resourcevector, ReportGenerator& report)
{
	ResourceContent baseResource;
	ResourceContent curResource;

	list<pair<string, string> > iBaseSystemheaders = BBCFileUtils::extractFilenames(iParams.getParameter(BASELINEPLAT));
	list<pair<string, string> > iCurSystemheaders = BBCFileUtils::extractFilenames(iParams.getParameter(CURRENTPLAT));

	for(int outer = 0; outer< (int)resourcevector.size(); outer++)
	{
		list<pair<string, string> > baseSystemheaders;
		list<pair<string, string> > curSystemheaders;

		baseSystemheaders = iBaseSystemheaders;
		curSystemheaders = iCurSystemheaders;
		pair <string, string> files = resourcevector.at(outer);
		vector <string> bIncludes;
		vector <string> cIncludes;


		baseResource.RHFileName = "";
		curResource.RHFileName = "";

		baseResource.RHFileName = BBCFileUtils::TrimAll(files.first);
		curResource.RHFileName = BBCFileUtils::TrimAll(files.second);

		pair <string, string> fileAnalyzed;
		fileAnalyzed.first = baseResource.RHFileName;
		fileAnalyzed.second = curResource.RHFileName;
		bool pairFound = false;
		// check if the file is already analyzed or not.
		for(int i = 0; i < (int)iRHFile_Analyzed.size(); i++ )
		{
			pair<string,string> filePair = iRHFile_Analyzed.at(i);
			if(fileAnalyzed.first == filePair.first )
			{
				pairFound = true;
				break;
			}
		}
		// File is not analyzed yet, so analyze it.
		if(pairFound == false )
		{
			iRHFile_Analyzed.push_back(fileAnalyzed);

			ifstream file(files.first.c_str());
			if(!file.is_open())
			{
				cerr << "ERROR: Cannot open " << files.first << " for reading!" << endl;
				exit(17);
			}

			// baseline resource file parsing
			getElementListFromRHFile(file,baseResource,bIncludes );
			file.close();

			// handle #include .RH headers, get proper path from system includes
			int basePos = (int)baseResource.RHFileName.find_last_of(DIR_SEPARATOR);
			string basePath = baseResource.RHFileName.substr(0,basePos);
			vector<pair<string,string> > includes;
			bool isPresent = false;
			pair<string,string> bPath;
			list<pair<string,string> >::iterator bHdr = baseSystemheaders.begin();
			for(;bHdr!= baseSystemheaders.end(); bHdr++)
			{
				bPath = *bHdr;
				if(bPath.first == basePath)
				{
					isPresent = true;
					break;
				}			
			}
			if(isPresent == false)
			{
				pair<string,string> bPair;
				bPair.first =basePath;
				bPair.second =basePath;
				baseSystemheaders.push_back(bPair);
			}

			bHdr= baseSystemheaders.begin();
			for(int i = 0; i < (int)bIncludes.size(); i++) 
			{
				for(;bHdr != baseSystemheaders.end(); bHdr++)
				{
					pair<string,string> baseHeader = *bHdr;
					pair<string,string>basePair;
					if(BBCFileUtils::FileExists(baseHeader.first + DIR_SEPARATOR + bIncludes.at(i)) )
					{
						basePair.first = baseHeader.first + DIR_SEPARATOR + bIncludes.at(i);
						includes.push_back(basePair);
						break;
					}
				}
			}

			ifstream file2(files.second.c_str());
			if(!file2.is_open())
			{
				cerr << "ERROR: Cannot open " << files.second << " for reading!" << endl;
				exit(17);
			}
			// current resource file parsing
			getElementListFromRHFile(file2,curResource, cIncludes );
			file2.close();
			
			_current_files++;
			cout << "\nAnalysing files (" << _current_files << "/" << _total_files << "): " << files.first <<" => "<< files.second << endl;

			// get current resource file's path and add to system include paths 
			// to get proper path for #include rh headers in current file
			int cPos = (int)curResource.RHFileName.find_last_of(DIR_SEPARATOR);
			string curPath = curResource.RHFileName.substr(0,cPos);
			isPresent = false;
			list<pair<string,string> >::iterator chdr= curSystemheaders.begin();
			pair<string,string> cPath;
			for(;chdr != curSystemheaders.end(); chdr++)
			{
				cPath = *chdr;
				if(cPath.first == curPath)
				{
					isPresent = true;
					break;
				}			
			}
			if(isPresent == false)
			{
				pair<string,string> cPair;
				cPair.first = curPath;
				cPair.second = curPath;
				curSystemheaders.push_back(cPair);
			}

			
			for(int out = 0; out < (int)includes.size(); out++)
			{
				int bLoc = (int)includes.at(out).first.find_last_of(DIR_SEPARATOR);
				string bString = includes.at(out).first.substr(bLoc+1,string::npos);
				bool includedHeaderPresent = false;

				for(int j = 0; j < (int)cIncludes.size(); j++) 
				{
					bool fileMatched = false;
					chdr= curSystemheaders.begin();
					for(;chdr != curSystemheaders.end(); chdr++)
					{
						pair<string,string> curHeader = *chdr;
						string curFile = curHeader.first + DIR_SEPARATOR + cIncludes.at(j);
						int loc = (int)curFile.find_last_of(DIR_SEPARATOR);
						string curTemp = curFile.substr(loc+1 ,string::npos);
						if(bString == curTemp)
						{
							includedHeaderPresent = true;
							if(BBCFileUtils::FileExists(curFile) ) 
							{
								fileMatched = true; // current file found in curr dir
								includes.at(out).second = curFile;
								break;
							}							
						}
					}

					if ( fileMatched = false )
					{
						// file does not exists in curdir
						report.addIssue(baseResource.RHFileName, includes.at(out).first, EIssueIdentityFile, 
							EIssueTypeRemoval,ESeverityBBCBreak,ESeveritySCNULL, "", 0, curResource.RHFileName,"");
						break;
					}
				}
				if(includedHeaderPresent == false)
				{
					// add issue, as field is removed in current file.
					report.addIssue(baseResource.RHFileName, bString, EIssueIdentityField, 
						EIssueTypeRemoval,ESeverityNULL,ESeveritySCBreak, "", 0, curResource.RHFileName,"");
				}
			}

			for(int l = 0; l < (int)includes.size(); l++ )
			{
				pair<string,string> pair = includes.at(l);
				if(pair.first.size() > 0 && pair.second.size()>0)
				{				
					resourcevector.push_back(pair);
				}
			}

			compareResources( baseResource, curResource, report);
		}


		baseResource.structList.clear();
		baseResource.enumList.clear();
		baseResource.macroList.clear();

		curResource.structList.clear();
		curResource.enumList.clear();
		curResource.macroList.clear();


	}// end of one resource
	cout<<"\n\n"<<endl;
}


void Analyser::getElementListFromRHFile(std::ifstream& RHFile,ResourceContent& resource, vector< string >& includes )
{
	string line;
	EnumElement lEnum;
	string tempData;
	string elementVal;

	StructElement lStruct;
	string structName;

	bool structInuse = false;
	bool enumInuse = false;
	bool macroInuse = false;
	bool keyFound = false;
	bool elementfound = false;
	bool valueFound = false;

	bool comment = false;	
	bool ignoreLine = false;

	bool newLinecharFound = false; // for macros, newline character can be present

	long currentEnumVal = -1;

	char keywords [23][15] = {"short","long", "word", "len", "byte", "struct", "ltext","enum", "ltext8", "ltext16", "ltext32", "llink", "srlink","double",
		"buf<1>","buf<2>","buf<4>","buf<8>","buf<16>","buf<32>","buf<64>","buf<128>","buf<256>"};

	MacroElement macro;
	int lineNo = 0;

	while(getline(RHFile,line))
	{
		lineNo++;
		pair<string,int> enummember;
		StructMember elementMember;
		line = toLowerCase(trimWhiteSpace(line));

		// Ignore all comment lines. e.g /*xxxxxxxxxx*/ Struct ABCD , start reading characterwise from struct
		if(enumInuse == false && macroInuse == false && structInuse == false )
		{
			if(line.find("/*") != -1 )
			{
				if( line.find("*/") == -1)
				{
				comment = true;
				continue;
				}
				else
				{
					int com = (int)line.find_last_of("*");
					line= line.substr(com +2, string::npos);
				}
			}
			if(line.find("*/") != -1 )
			{
				comment = false;
				if(ignoreLine == true)
					ignoreLine = false;
				continue;
			}
			if(comment == true)
			{
				continue;
			}
			if(line.find("//") != -1 ) 
			{
				int com = (int)line.find_first_of("//");
				bool wordFound = false;
				line = line.substr(0,com);
				for (int i = 0; i< (int)line.size(); i++ )
				{
					// check  '//' commentline starts after some key value e.g struct ABCD // xyz
					if ( (int)line.at(i ) != 32 && (int)line.at(i) != 9 ) // 32 and 9 are for space and invalid character
					{
						wordFound = true;
						break;
					}
				}
				if(wordFound == false)
				continue;
			}

		}
 
		// Find any other header file is included in current file
		// Then add it to file and check whether this is already analyzed or not.
		// If not, then analyze it.
		if(line.find ("#") != -1 && line.find("include") != -1 )
		{
				int start = (int)line.find_first_of ("<");
			
			int end;
			if(start == -1)
			{
				start =(int) line.find_first_of("\"");
				end = (int)line.find_last_of("\"");
			}
			else
			{
				end = (int)line.find(">");
			}

			if (start > 0 && end > 0 )
			{
				line = line.substr(start + 1,(end - start) - 1);
				line = BBCFileUtils::TrimAll(line);
				int loc = (int)line.find(RH_EXTENSION);
				// Include only .rh files
				if(loc != -1)
					includes.push_back(line);
			}
		}

		// Now check lines for key structure (struct, enum, #inlude and start reading characterwise unless the key structure end.
		if (keyFound == false )
		{
			tempData.clear();
			int enumloc = (int)line.find(KEY_ENUM);
			// to get enum key word properly. After "enum" keyword, there might be no name present.
			// For this case, following checks are needed.
			if( enumloc!= -1)
			{
				enumInuse = true;
				string prestring = line.substr(0,enumloc);
				for(int i = 0; i< (int)prestring.size(); i++ )
				{
					if( (int)prestring.at(i)!= 32 && (int)prestring.at(i) != 9 )
					{
						enumInuse =false;
						break;
					}
				}
				if(enumInuse == true)
				{
					string postline = line.substr(enumloc+strlen(KEY_ENUM) ,string::npos);
					if( postline.size() > 0 && (int)postline.at(0)!= 32 && (int)postline.at(0) != 9 )
					{
							enumInuse =false;
							break;
					}
					else
					{
						line = postline;
						macroInuse = false;
						structInuse = false;
						lEnum.enumName = "";
						lEnum.enums.clear();
					}
				}
			}
			if(line.find(KEY_MACRO) != -1)
			{
				macroInuse = true;
				enumInuse = false;
				structInuse = false;
				macro.macroName = "";
				macro.macroVal = "";
				line = line.substr(strlen(KEY_MACRO),string::npos);
			}

			if(line.find(KEY_STRUCT) != -1)
			{
				structInuse = true;
				enumInuse = false;
				macroInuse = false;
				lStruct.structName = "";
				lStruct.members.clear();
				line = line.substr(strlen(KEY_STRUCT),string::npos);
			}	
		}

		// If any of the key found, then following lines will be checked character wise.
		if ( enumInuse == true || macroInuse == true || structInuse == true )
		{
			keyFound = true;

			EnumMember enummember;

			string elementName;
			string elementType;
			string structElementVal;

			bool lineend = false;
			int length = int(line.size());

			for (int j = 0; j < length ; j++)
			{
				int temp = line.at(j);
				//int templie = line.at(j);
				switch (temp)
				{
				case 32:  // For ' '
				case 9: //for Invalid space
					{
						if (structInuse == true && tempData.size() > 0)
						{
							if ( elementfound == true )
							{	
								for (int k = 0 ; k < 23 ; k++ )
								{
									// got the type, will check with all possible data types.Else it will be member name.
									int loc = int(line.find_first_of(keywords[k]));
									string key(keywords[k]);
									if (tempData == key )
									{											
										elementType.append(keywords[k]);
										tempData.clear();
										break;
									}										
								}
							}
						}
						if (macroInuse == true && macro.macroName.size() <=0 && tempData.size() > 0) // can be macro name
						{
							macro.macroName = tempData;
							macro.lineNo = lineNo;
							tempData.clear();
						}
					}
					break;
				case 59://For ';'
					{						
						if ( structInuse == true && elementfound == true && tempData.size() > 0)
						{
							elementName.append(tempData);
							elementMember.elementName = elementName;
							elementMember.elementType = elementType;
							elementMember.lineNo = lineNo;
							if (valueFound == true)
							{
								elementMember.elementValue= structElementVal; 
								valueFound = false;
							}
							lStruct.members.push_back (elementMember);
							tempData.clear();
						}

						if(macroInuse ==false)
							break;	

					}
					
				case 44://For ','
					{	
						if(macroInuse ==false)
						{
							if ( enumInuse == true && elementfound == true && tempData.size() > 0)
							{
								if (valueFound == true)
								{
									enummember.enumVal = elementVal.c_str();
									char *p;
									// convert enumVal to long , so that can be incremented if required.
									currentEnumVal = strtol(enummember.enumVal.c_str(),&p,0);
									valueFound = false;
								}
								else
								{
									currentEnumVal += 1;
									string p;
									// convert long to string
									enummember.enumVal = ltoa(currentEnumVal,p,0);
								}
								enummember.enumMemName.append(tempData);
								enummember.lineNo = lineNo;

								lEnum.enums.push_back(enummember);

								tempData.clear();
								elementVal.clear();
							}
							break;
						}
					}
					
				case 61: //For '='
					{
						if(macroInuse == false)
						{
							valueFound = true;
							break;
						}
					}
					//break;

				case 123:  //For '{'
					{
						if(macroInuse ==false)
						{
							if(tempData.size() > 0 )
							{
								if(structInuse == true)
								{
									lStruct.structName.assign(tempData);
									lStruct.lineNo = lineNo;
								}
								else
								{
									lEnum.enumName.assign(tempData);
									lEnum.lineNo = lineNo;
								}
							}
							tempData.clear();
							elementfound = true;

							break;
						}
					}
				case 125: //For '}'
					{
						if(macroInuse ==false)
						{
							if(structInuse == true)
							{
								structInuse = false;	
								if(tempData.size() > 0) // if some inline macro is present
								{
									elementMember.elementName = tempData ;
									elementMember.elementType = "";
									elementMember.lineNo = lineNo;
									lStruct.members.push_back(elementMember);
								}
								resource.structList.push_back(lStruct);
							}
							else if ( enumInuse == true )
							{
								if (elementfound == true && tempData.size() > 0)
								{
									if (valueFound == true)
									{
										enummember.enumVal = elementVal.c_str(); 
										char *p;
										// convert enumVal to long , so that can be incremented if required.
										currentEnumVal = strtol(enummember.enumVal.c_str(),&p,0);
										valueFound = false;
									}
									else
									{
										currentEnumVal += 1;
										string p;
										// convert long to string
										enummember.enumVal = ltoa(currentEnumVal,p,0);
									}

									enummember.lineNo = lineNo;

									enummember.enumMemName.append(tempData);

									lEnum.enums.push_back(enummember);							
								}
								currentEnumVal = -1;
								elementVal.clear();
								enumInuse = false;
								resource.enumList.push_back(lEnum);
							}
							keyFound = false;
							elementfound = false;
							tempData.clear();

							break;
						}
					}
				default:
					{
						// followings are to ignore any comment line in between.
						if( j+1 <length)
						{
							if (line.at(j) == '/' )
							{
								if(line.at(j+1) == '*')
									ignoreLine = true;

								else if ( line.at(j+1) == '/')
								{
									lineend = true;
									break;
								}
							}
							if(ignoreLine == true)
							{
								if (j+1 <length && line.at(j) == '*' && line.at(j+1) == '/')
								{
									ignoreLine = false;
									j = j+2;
									continue;

								}
							}
						} // comment line checks ended

						if(ignoreLine == false && j<length)
						{
							// newline character's int value is 92, for macros, newline char can be present mainly.
							if ((int) line.at(j)== 92 && macroInuse == true && tempData.size() > 0) // can be macro name
							{
								newLinecharFound = true; // new line character found
								if ( macro.macroName.size() <=0)
								{
									macro.macroName = tempData;	
									macro.lineNo = lineNo;
								}
								else
								{
									macro.macroVal.append(tempData);
								}
								tempData.clear();
								
							}
							// Check macro definition ended after newlines
							if( (int) line.at(j)!= 92 && j+1 >= length && macroInuse == true &&  newLinecharFound == true )
							{
								newLinecharFound =false;
								//macroInuse = false;
								//macro.macroVal.append(tempData);
								//tempData.clear();
								break;
							}
							if (enumInuse == true || macroInuse == true || structInuse == true)
							{
								if(valueFound == true)
								{
									if ( structInuse == true )
										structElementVal.push_back(line.at(j));
									else
										elementVal.push_back(line.at(j));									
								}
								else
								{
									if( (int)line.at(j) != 92)// ignore newline character
									tempData.push_back(line.at(j));
								}
							}
						}

						
					}
					break;
				}
				if (lineend == true)
					break;
			}// line end

			// Macro structure ended, fill the values.
			if( macroInuse == true && newLinecharFound == false && tempData.size() > 0 )
			{
				if(tempData.size()> 0 )
				{
					macro.macroVal.append(tempData);
					tempData.clear();
				}
				keyFound = false;
				macroInuse = false ;
				resource.macroList.push_back(macro);
			}
		}

	}// End of all lines in resource file

}

void Analyser::compareResources(ResourceContent &baseResource, ResourceContent &curResource, ReportGenerator& report)
{
	int base_struct_no = (int)baseResource.structList.size();
	int cur_struct_no = (int)curResource.structList.size();

	int base_enum_no = (int)baseResource.enumList.size();
	int cur_enum_no = (int)curResource.enumList.size();

	int base_macro_no = (int)baseResource.macroList.size();
	int cur_macro_no = (int)curResource.macroList.size();

	StructElement baseStruct;
	StructElement curStruct;

	EnumElement baseEnum;
	EnumElement curEnum;

	MacroElement baseMacro;
	MacroElement curMacro;

	for(int i = 0; i < base_struct_no; i++ )
	{
		baseStruct =  baseResource.structList.at(i);
		bool structFound = false;
		for(int j = 0; j < cur_struct_no; j++ )
		{
			curStruct = curResource.structList.at(j);
			if(baseStruct.structName == curStruct.structName )
			{
				int baseMemNo = (int)baseStruct.members.size();
				int curMemNo = (int)curStruct.members.size();

				structFound = true;

				for( int bInner = 0; bInner < baseMemNo; bInner++ )
				{
					bool memFound = false;
					for ( int cInner = 0; cInner < curMemNo; cInner++ )
					{
						if ( baseStruct.members.at(bInner).elementName == curStruct.members.at(cInner).elementName )
						{
							memFound = true;
							if(baseStruct.members.at(bInner).elementType == curStruct.members.at(cInner).elementType)
							{
								if(baseStruct.members.at(bInner).elementValue.size() > 0
									&& (baseStruct.members.at(bInner).elementValue != curStruct.members.at(cInner).elementValue) )
								{
									//add issue	member value mismatch		
									string bVal = baseStruct.structName + "::" + baseStruct.members.at(bInner).elementName;
									string cVal = curStruct.members.at(cInner).elementValue;
									int lineNo = curStruct.members.at(cInner).lineNo;
									report.addIssue(baseResource.RHFileName, bVal, EIssueIdentityStructMember, EIssueTypeChangeInInitialisation, 
										ESeverityNULL, ESeveritySCBreak, cVal, lineNo,curResource.RHFileName,"");
								} 
							}
							else
							{
								// add issue tyechange
								string bType = baseStruct.structName + "::" + baseStruct.members.at(bInner).elementName;
								string cType = curStruct.members.at(cInner).elementType;
								int lineNo = curStruct.members.at(cInner).lineNo;
								report.addIssue(baseResource.RHFileName, bType, EIssueIdentityStructMember, EIssueTypeChangeInType, 
									ESeverityNULL, ESeveritySCBreak, cType, lineNo,curResource.RHFileName,"");
							}

							break;

						}// memeber name matched
					}// loop thru all curr struct member

					if( memFound == false)
					{
						// Add Issue Member not found  // baseStruct.members.at(bInner)
						string bMember = baseStruct.structName + "::" + baseStruct.members.at(bInner).elementName;
						int lineNo = curStruct.lineNo;
						report.addIssue(baseResource.RHFileName, bMember, EIssueIdentityStructMember, EIssueTypeRemoval, 
							ESeverityNULL,ESeveritySCBreak, "", lineNo,curResource.RHFileName,"");
					}
				}// loop base struct member

			}// struct name match
		}// loop curr structs

		if( structFound == false )
		{ 
			//Add issue struct not found
			report.addIssue(baseResource.RHFileName, baseStruct.structName, EIssueIdentityStruct, EIssueTypeRemoval, 
				ESeverityNULL, ESeveritySCBreak, "", 0,curResource.RHFileName,"");
		}
	}//loop base structs

	// --------------Enum Comparison ------------
	vector<EnumMember>baseEnumNameEmptyMemberList;
	vector<EnumMember>curEnumNameEmptyMemberList;
	vector<EnumElement> bEnumList;
	vector<EnumElement> cEnumList;

    for( int b = 0; b < base_enum_no; b++)
	{
		baseEnum = baseResource.enumList.at(b);
		
		if(baseEnum.enumName.size()<=0)
		{
			for(int k = 0; k < (int)baseEnum.enums.size(); k++)
			{
				baseEnumNameEmptyMemberList.push_back(baseEnum.enums.at(k));
			}
		}
		else
		{
			bEnumList.push_back(baseEnum);
		}
	}

	for( int c = 0; c < cur_enum_no; c++)
	{
		curEnum = curResource.enumList.at(c);
		
		if(curEnum.enumName.size()<=0)
		{
			for(int k = 0; k < (int)curEnum.enums.size(); k++)
			{
				curEnumNameEmptyMemberList.push_back(curEnum.enums.at(k));
			}
		}
		else
		{
			cEnumList.push_back(curEnum);
		}
	}

	// Compare and report issue for enum list with name
	for( int l = 0; l < (int) bEnumList.size(); l++)
	{
		baseEnum = bEnumList.at(l);
		bool enumFound = false;

		for( int m = 0; m < (int)cEnumList.size(); m++ )
		{
			curEnum = cEnumList.at(m);
			if ( baseEnum.enumName == curEnum.enumName )
			{
				int bMemNo = (int)baseEnum.enums.size();
				int cMemNo = (int)curEnum.enums.size();

				enumFound = true;

				for ( int outer = 0; outer < bMemNo; outer++ )
				{
					bool enumMemFound = false;
					for( int inner = 0; inner < cMemNo; inner++ )
					{
						if(baseEnum.enums.at(outer).enumMemName == curEnum.enums.at(inner).enumMemName )
						{ 
							enumMemFound = true;
							// member name found
							if(baseEnum.enums.at(outer).enumVal.size() > 0 )
							{
								if (baseEnum.enums.at(outer).enumVal != curEnum.enums.at(inner).enumVal )
								{
									//add issue Member value changed
									string baseEnumVal = baseEnum.enumName +"::" + baseEnum.enums.at(outer).enumMemName;
									string curEnumVal = curEnum.enums.at(inner).enumVal;
									int lineNo = curEnum.enums.at(inner).lineNo;

									report.addIssue(baseResource.RHFileName, baseEnumVal, EIssueIdentityEnumerationValue, EIssueTypeChangeInInitialisation, 
										ESeverityNULL, ESeveritySCBreak, curEnumVal, lineNo,curResource.RHFileName,"");
								}
							}
							break;
						}
					} // loop cur mems

					if ( enumMemFound == false)
					{ 
						// Add Enum Member Missing
						string bMemName = baseEnum.enumName +"::" + baseEnum.enums.at(outer).enumMemName;
						int lineNo = curEnum.lineNo;
						report.addIssue(baseResource.RHFileName, bMemName, EIssueIdentityEnumerationValue, EIssueTypeRemoval, 
							ESeverityNULL, ESeveritySCBreak, "", lineNo,curResource.RHFileName,"");

					}
				}// loop base mems

				break;
			}// enum name matched
		}// loop cur enums

		if (enumFound == false )
		{
			// Enum List missing
			string bEnum = baseEnum.enumName;
			string cEnum = curEnum.enumName;
			report.addIssue(baseResource.RHFileName, bEnum, EIssueIdentityEnumerationValue, EIssueTypeRemoval, 
				ESeverityNULL, ESeveritySCBreak, cEnum, 0,curResource.RHFileName,"");
		}
	}//base enums

	// Now check for enum list with no enum name, in this case check member name and value
	if(baseEnumNameEmptyMemberList.size() > 0)
	{
		EnumMember bEnumMem;
		for(unsigned long i = 0; i < (unsigned long)baseEnumNameEmptyMemberList.size(); i++)
		{
			bEnumMem = baseEnumNameEmptyMemberList.at(i);
			EnumMember cEnumMem;
			bool enumMemFound = false;
			for(unsigned long j = 0; j <(unsigned long) curEnumNameEmptyMemberList.size(); j++ )
			{
				cEnumMem = curEnumNameEmptyMemberList.at(j);
				if(bEnumMem.enumMemName == cEnumMem.enumMemName)
				{
					enumMemFound = true;
					if(bEnumMem.enumVal != cEnumMem.enumVal )
					{
						//add issue enum value changed 
						string baseEnumVal = "::" + bEnumMem.enumMemName;
						string curEnumVal = cEnumMem.enumMemName;
						int lineNo = cEnumMem.lineNo;

						report.addIssue(baseResource.RHFileName, baseEnumVal, EIssueIdentityEnumerationValue, EIssueTypeChangeInInitialisation, 
							ESeverityNULL, ESeveritySCBreak, curEnumVal, lineNo,curResource.RHFileName,"");
					}
					break;
				}
			}
			if(enumMemFound == false)
			{
				// add issue enum mem mising
				string bMemName = "::" + bEnumMem.enumMemName;
				report.addIssue(baseResource.RHFileName, bMemName, EIssueIdentityEnumerationValue, EIssueTypeRemoval, 
					ESeverityNULL, ESeveritySCBreak, "", 0,curResource.RHFileName,"");
			}
		}
	}


	// --------------------- Macro Comparision --------------

	for (int p = 0; p < base_macro_no; p++ )
	{
		bool macroFound = false;
		baseMacro = baseResource.macroList.at(p);
		for (int q = 0; q < cur_macro_no; q++ )
		{
			curMacro = curResource.macroList.at(q);
			if(baseMacro.macroName == curMacro.macroName )
			{ // check Macro value
				macroFound = true;
				if(baseMacro.macroVal != curMacro.macroVal )
				{
					//add issue macro value mismatch
					report.addIssue(baseResource.RHFileName, baseMacro.macroName, EIssueIdentityMacro, EIssueTypeChange, 
						ESeverityNULL, ESeveritySCBreak, curMacro.macroVal, curMacro.lineNo,curResource.RHFileName,"");
				}
				break; // macro name matched
			}

		}

		if (macroFound == false )
		{
			// add issue macro not found
			report.addIssue(baseResource.RHFileName, baseMacro.macroName, EIssueIdentityMacro, EIssueTypeRemoval, 
				ESeverityNULL, ESeveritySCBreak, "", 0,curResource.RHFileName,"");
		}
	}



}

