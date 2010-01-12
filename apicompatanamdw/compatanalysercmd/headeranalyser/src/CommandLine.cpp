/*
* Copyright (c) 2008, 2009 Nokia Corporation and/or its subsidiary(-ies). 
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

#ifndef _MSC_VER
#define stricmp strcasecmp
#endif
#include <iostream>
#include <sstream>
#include <map>

#include "CommandLine.h"
#include "HAException.h"
#include "CmdGlobals.h"
#include "CommandFile.h"
#include "BBCFileUtils.h"
#include "Utils.h"
#include "ReportGeneratorConstants.h"


using namespace std;


// ----------------------------------------------------------------------------
// CommandLine::CommandLine
// Constructor
// ----------------------------------------------------------------------------
//
CommandLine::CommandLine() : iParametersValid(-1)
{
    initializeAcceptableParametersList();
}


// ----------------------------------------------------------------------------
// CommandLine::CommandLine
// Constructor
// ----------------------------------------------------------------------------
//
CommandLine::CommandLine(char** args, int argc) : iParametersValid(-1)
{
    // first check if the command line parameters contain any help command
    int i=1;
	while (i<argc)
	{
		if (stricmp("-?", args[i])==0 || stricmp("-h", args[i])==0 || stricmp("--help", args[i])==0)
		{
			showCommandLineOptionsAndExit();
		}
        i++;
    }
    
    initializeAcceptableParametersList();
    iArgList = args;
    iArgCount = argc;
}

// ----------------------------------------------------------------------------
// CommandLine::~CommandLine
// Destructor
// ----------------------------------------------------------------------------
//
CommandLine::~CommandLine()
{
    iAcceptableParameterMap.clear();
    parameterSpecifierSet.clear();
    requiredParametersSet.clear();
}

// ----------------------------------------------------------------------------
// CommandLine::getParameter
// Returns the parameter value for a given parameter
// ----------------------------------------------------------------------------
//
string CommandLine::getParameter(string aParm)
{
    map<string, string>::iterator mapitem = iParameterMap.find(aParm);
    bool isValidParm = mapitem == iParameterMap.end() ? false : true;
    if (!isValidParm)
    {
        string excstr = "No such parameter: ";
        excstr += aParm;
        throw HAException(excstr);
    }
    return mapitem->second;
}

const map <string, string>& CommandLine::getParameters()
{
    return iParameterMap;
}

// ----------------------------------------------------------------------------
// CommandLine::CommandLine
// ----------------------------------------------------------------------------
//
void CommandLine::insertParameter(string paramName, bool specifierRequired, bool optional) 
{
    mapentry parm(paramName, "");
    iAcceptableParameterMap.insert(parm);
    if (specifierRequired) 
    {
        parameterSpecifierSet.insert(paramName);
    }
    if (!optional)
    {
        requiredParametersSet.insert(paramName);
    }
}

// ----------------------------------------------------------------------------
// CommandLine::parameterExists
// Check parameter existence
// 
// ----------------------------------------------------------------------------
//
bool CommandLine::parameterExists(const string& aParmName)
{
    bool ret = false;
    map<string, string>::iterator mapitem = iParameterMap.find(aParmName);
    if (mapitem != iParameterMap.end())
    {
        ret = true;
    }
    return ret;
}

// ----------------------------------------------------------------------------
// CommandLine::initializeAcceptableParametersList
// Initialize acceptable parameter list
// 
// ----------------------------------------------------------------------------
//
void CommandLine::initializeAcceptableParametersList() 
{
    // note: baseline/current may be long strings (ie. many filenames separated by semicolons)
    insertParameter(BASELINE, true);
    insertParameter(CURRENT, true);
    insertParameter(BASELINEDIR, true);
    insertParameter(CURRENTDIR, true);
    insertParameter(REPORTFILE, true, false);
    insertParameter(BASELINEVERSION, true);
    insertParameter(CURRENTVERSION, true);
    insertParameter(COMMANDFILE, false);
    insertParameter(BASEPLATFORMDATA, true);
    insertParameter(CURRENTPLATFORMDATA, true);

    insertParameter(RECURSIVE, false);
    insertParameter(FILEREPLACE, true);
    insertParameter(HEADERSET, true);
    insertParameter(BASELINEPLAT, true, false);
    insertParameter(CURRENTPLAT, true, false);
    insertParameter(BUNDLESIZE, true);
    insertParameter(TRIMXML, true);
    insertParameter(TEMPDIR, true, false);
    insertParameter(BASEFORCEDHEADERSFILE, true);
    insertParameter(CURRENTFORCEDHEADERSFILE, true);
    insertParameter(DOCURL, true);
    insertParameter(DISCARDDIRS, true);
#if defined(_DEBUG) || defined(DEBUG)
    insertParameter(COMMANDLINETEST, false);
#endif
	insertParameter(USETHREAD, false);
}

// ----------------------------------------------------------------------------
// CommandLine::validateParameters
// Validate parameters
// 
// ----------------------------------------------------------------------------
//
string CommandLine::validateParameters()
{
    ostringstream ret;
    parse(iArgList, iArgCount);

    map<string, string>::iterator mapitem = iParameterMap.find(TEMPDIR);
    if (mapitem == iParameterMap.end() || mapitem->second.length() < 1)
    {
        const char* env2 = getenv("TEMP");
        if (env2 != NULL) 
        {
            string tempfiles(env2);
            if (mapitem != iParameterMap.end())
            {
                mapitem->second = tempfiles;
            } else
            {
                pair <string,string> parm(TEMPDIR, tempfiles);
                iParameterMap.insert(parm);
            }
        }
    }

    mapitem = iParameterMap.find(BASELINEPLAT);
    if (mapitem == iParameterMap.end() || mapitem->second.length() < 1)
    {
        string envvar = BASELINEPLAT;
        const char* env2 = getenv(toUpperCase(envvar).c_str());
        if (env2 != NULL) 
        {
            string tempfiles(env2);
            if (mapitem != iParameterMap.end())
            {
                mapitem->second = tempfiles;
            } else
            {
                pair <string,string> parm(TEMPDIR, tempfiles);
                iParameterMap.insert(parm);
            }
        }
    }

    mapitem = iParameterMap.find(CURRENTPLAT);
    if (mapitem == iParameterMap.end() || mapitem->second.length() < 1)
    {
        string envvar = CURRENTPLAT;
        const char* env2 = getenv(toUpperCase(envvar).c_str());
        if (env2 != NULL) 
        {
            string tempfiles(env2);
            if (mapitem != iParameterMap.end())
            {
                mapitem->second = tempfiles;
            } else
            {
                pair <string,string> parm(TEMPDIR, tempfiles);
                iParameterMap.insert(parm);
            }
        }
    }

    // START -- Support for multiple header directories --
    mapitem = iParameterMap.find(BASELINEDIR);
    if (mapitem == iParameterMap.end() || mapitem->second.length() < 1)
    {
        string envvar = BASELINEDIR;
        const char* env2 = getenv(toUpperCase(envvar).c_str());
        if (env2 != NULL) 
        {
            string tempfiles(env2);
            if (mapitem != iParameterMap.end())
            {
                mapitem->second = tempfiles;
            } else
            {
                pair <string,string> parm(TEMPDIR, tempfiles);
                iParameterMap.insert(parm);
            }
        }
    }

    mapitem = iParameterMap.find(CURRENTDIR);
    if (mapitem == iParameterMap.end() || mapitem->second.length() < 1)
    {
        string envvar = CURRENTDIR;
        const char* env2 = getenv(toUpperCase(envvar).c_str());
        if (env2 != NULL) 
        {
            string tempfiles(env2);
            if (mapitem != iParameterMap.end())
            {
                mapitem->second = tempfiles;
            } else
            {
                pair <string,string> parm(TEMPDIR, tempfiles);
                iParameterMap.insert(parm);
            }
        }
    }
    // END -- Support for multiple header directories --
    
    set<string>::iterator setitem = requiredParametersSet.begin();
    while (setitem != requiredParametersSet.end())
    {
        string s = *setitem;
        map<string, string>::iterator mapitem = iParameterMap.find(s);
        if (mapitem == iParameterMap.end())
        {
            if (ret.str().length() == 0)
            {
                ret << "Missing required parameters: ";
            }
            ret << s;
            ret << " ";
        } else 
        {
            // else branch not required anymore
            if (mapitem->second.length() == 0)
            {
                if (ret.str().length() == 0)
                {
                    ret << "Missing required parameters: ";
                }
                ret << s;
                ret << " ";
            }
        }
        setitem++;
    }

    if (ret.str().length() > 0)
    {
        ret << "\n";
    }

    if (!parameterExists(BASELINE) && !parameterExists(BASELINEDIR) && !parameterExists(CURRENT) && !parameterExists(CURRENTDIR))
    {
        ret << "One of the parameter listed next must be given: -"<< BASELINEDIR <<" -"<< BASELINE <<"\n";
        ret << "One of the parameter listed next must be given: -"<< CURRENTDIR <<" -"<< CURRENT <<"\n";
    }

    // check for parameter conflicts in baseline parameters
    if (parameterExists(BASELINE) && parameterExists(BASELINEDIR))
    {
        ret << "Parameter conflict: -"<< BASELINEDIR <<" and -"<< BASELINE <<" cannot co-exist\n";
    } else
    {
        if (parameterExists(BASELINE) && !parameterExists(CURRENT))
        {
            ret << "Parameter conflict: When -"<< BASELINE <<" is specified then also -"<< CURRENT <<" is required.\n";
        }
        if (parameterExists(BASELINEDIR) && !parameterExists(CURRENTDIR))
        {
            ret << "Parameter conflict: When -"<< BASELINEDIR <<" is specified then also -"<< CURRENTDIR <<" is required.\n";
        }
    }
    
    // Same for current headers
    if (parameterExists(CURRENT) && parameterExists(CURRENTDIR))
    {
        ret << "Parameter conflict: -"<< CURRENTDIR <<" and -"<< CURRENT <<" cannot co-exist\n";
    } else
    {
        if (parameterExists(CURRENT) && !parameterExists(BASELINE))
        {
            ret << "Parameter conflict: When -"<< CURRENT <<" is specified then also -"<< BASELINE <<" is required.\n";
        }
        if (parameterExists(CURRENTDIR) && !parameterExists(BASELINEDIR))
        {
            ret << "Parameter conflict: When -"<< CURRENTDIR <<" is specified then also -"<< BASELINEDIR <<" is required.\n";
        }
    }

    // Check for parameters which are specific only for baselinedir/currentdir
    if (parameterExists(BASELINE) || parameterExists(CURRENT))
    {
        if (parameterExists(FILEREPLACE))
        {
            ret << "Parameter conflict: -"<< FILEREPLACE <<" cannot be used in combination with file parameters (-"<< CURRENT <<"/-"<< BASELINE <<")\n";
        }
        if (parameterExists(RECURSIVE))
        {
            ret << "Parameter conflict: -"<< RECURSIVE <<" cannot be used in combination with file parameters (-"<< CURRENT <<"/-"<< BASELINE <<")\n";
        }
        if (parameterExists(HEADERSET))
        {
            ret << "Parameter conflict: -"<< HEADERSET <<" cannot be used in combination with file parameters (-"<< CURRENT <<"/-"<< BASELINE <<")\n";
        }
    }
    if (!parameterExists(RECURSIVE) && parameterExists(DISCARDDIRS))
    {
        ret << "Parameter conflict: -"<< DISCARDDIRS <<" requires -"<< RECURSIVE <<"\n";
    }
    // Check that all the parameters that require a specifier
    // indeed contain a specifier. If not, it's an error and must
    // be reported
    set<string>::iterator specIt = parameterSpecifierSet.begin();
    while (specIt != parameterSpecifierSet.end())
    {
        map<string,string>::iterator parmIt = iParameterMap.find(*specIt);
        if (parmIt != iParameterMap.end())
        {
            if (parmIt->second.length() < 1)
            {
                ret << "Missing required specifier for parameter -";
                ret << *specIt;
                ret << "\n";
            }
        }
        specIt++;
    }
    return ret.str();
}


// ----------------------------------------------------------------------------
// CommandLine::validParamValue
// Check if the parameter value is valid.
// ----------------------------------------------------------------------------
//
void CommandLine::validParamValue(string parm,string val)
{
    string ret;

    // Don't check parameter 'recursive' , 'usethread' or any other that
    // doesn't need a value.
    int dontCheckParm = parm.compare( RECURSIVE);
	int threadParm = parm.compare( USETHREAD);

    if ( dontCheckParm !=0 && threadParm != 0 )
    {
        if ( parm.compare( BASELINEVERSION )==0 || parm.compare( CURRENTVERSION )==0 || parm.compare( BUNDLESIZE )==0 || parm.compare( HEADERSET )==0 )
        {
            //check for atleast one char long 
            if( val.length()<=0 )
            {
                ret = "Invalid value for parameter: " + parm + '\n';
                throw HAException(ret);  
            }
        }  	
        else 
        {
            //check for atleast two char long 
            if ( val.length()<=1 )
            {
                ret = "Invalid value for parameter: " + parm + '\n';
                throw HAException(ret);
            }
        }
    }
}

// ----------------------------------------------------------------------------
// CommandLine::storeParameter
// Stores a parameter.
// ----------------------------------------------------------------------------
//
void CommandLine::storeParameter(string parm, string val, int parmType) 
{
    map<string, string>::iterator mapitem;
    bool isValidParm = false;
    string errormsg;
    mapitem = iAcceptableParameterMap.find(parm);
    isValidParm = mapitem == iAcceptableParameterMap.end() ? false : true;
    validParamValue(parm, val);
    if (isValidParm && parm.length() > 0)
    {
        // Valid parameters are those that the map structure has been initialised with;
        // any other parameter is invalid, and will yield an error.
        bool needsSpecifier = parameterSpecifierSet.find(parm) == parameterSpecifierSet.end() ? false : true;
        map<string, string>::iterator mapitem2;
        mapitem2 = iParameterMap.find(parm);
        pair<string,string> parmToInsert(parm, val);
        if (needsSpecifier) 
        {
            // Arguments that need specifier must have both the ARGUMENT_NAME and VALUE
            // (ie. both fields in the map must be of nonzero length)
            if (val.length() > 0) 
            {
                if (parmType == EParmCommandFile)
                {
                    // command file arguments can't replace (already existing) command-line
                    // arguments; command-file args will only be used when no similar
                    // argument was given in commandline.
                    if (mapitem2 != iParameterMap.end())
                    {
#if ( defined(_DEBUG) || defined(DEBUG) ) && !defined(NO_DBG)
                        cout << "Not overriding parameter from file: " << parm << "\n";
#endif
                    } else
                    {
#if ( defined(_DEBUG) || defined(DEBUG) ) && !defined(NO_DBG)
                        cout << "Got command-file parameter: "<<parm<<" value: "<<val<<"\n";
#endif
                        iParameterMap.insert(parmToInsert);
                    }
                } else if (parmType == EParmCommandLine)
                {
                    // command-line argument always overrides
#if ( defined(_DEBUG) || defined(DEBUG) ) && !defined(NO_DBG)
                    cout << "Got command-line parameter: "<<parm<<" value: "<<val<<"\n";
#endif
                    iParameterMap.insert(parmToInsert);
                } else if (parmType == EParmEnvironment)
                {
                }
            } else {
                errormsg = "Expected non-empty specifier for parameter \"-" + parm + "\"\n";
                throw(new HAException(errormsg));
            }
        } else
        {
#if ( defined(_DEBUG) || defined(DEBUG) ) && !defined(NO_DBG)
            cout << "Got switch: "<<parm<<"\n";
#endif
            iParameterMap.insert(parmToInsert);
        }
    } else {
        // Throw an exception containing the list of valid parameter names.
        string errormsg = "Invalid parameter: " + parm + "\n";
/*
        errormsg += "Valid parameters are:\n";

        map<string,string>::iterator iter;
        iter = iAcceptableParameterMap.begin();
        while (iter != iAcceptableParameterMap.end()) 
        {
            errormsg += "\t" + iter->first + "\n";
            iter++;
        }
*/
        HAException e(errormsg);
        throw(e);
    }

}

// ----------------------------------------------------------------------------
// CommandLine::parse
// ----------------------------------------------------------------------------
//
void CommandLine::parse(char** parms, size_t count, int parmsType)
{
	// "Key" string
    string currentstr;
	// "Value" string
	string currentparam;
    bool hasSpace = false;
    bool isString = false;
    int lastPos = -1;

    // Iterate through the parameters, char by char.
    // argument names have a preceding '-' (and whitespace),
    // argument values only have a preceding ' ' (whitespace).
    for (unsigned int i = 1; i < count; i++) 
    {
        int j = 0;
        char ch = parms[i][j];
        if (i > 1 && j == 0 && ch == '-') 
        {
            if (hasSpace == true && currentparam == FILEREPLACE)
            {
                if (currentstr.at(lastPos) != '\"')
                {
                    currentstr = currentstr.substr(0, lastPos) + "\"" + currentstr.substr(lastPos);
                }
                currentstr = currentstr + "\"";
            }
            storeParameter(currentparam, currentstr, parmsType);
            currentparam = "";
            currentstr = "";
            isString = false;
            hasSpace = false;
        } else if (i > 1 && j == 0 && isString == false)
        {
            isString = true;
            hasSpace = false;
            lastPos = 0;
        } else if (i > 1 && j == 0) 
        {
            if (hasSpace == true && currentparam == FILEREPLACE)
            {
                if (currentstr.at(lastPos) != '\"')
                {
                    currentstr = currentstr.substr(0, lastPos) + "\"" + currentstr.substr(lastPos);
                }
                currentstr = currentstr + "\"";
            }
            currentstr += ' ';
            hasSpace = false;
            lastPos = (int)currentstr.length();
        }
        while (ch != '\0') 
        {
            if (ch == '\\' || ch == '/')
            {
                ch = DIR_SEPARATOR;
            }
            if (!isString) 
            {
                if (j > 0)
                {
                    currentparam += ch;
                }
            } else 
            {
                if (ch == ' ') hasSpace = true;
                currentstr += ch;
            }
            j++;
            ch = parms[i][j];
        }
    }
    
    // Dump the last one as well
    if ( count > 1)
    {
        if (hasSpace == true && currentparam == FILEREPLACE)
        {
            currentstr = "\"" + currentstr + "\"";
        }
        storeParameter(currentparam, currentstr, parmsType);
    }

    // If the processed arguments didn't come from command file,
    // check out if one exists and parse it if necessary.
    if (parmsType != EParmCommandFile && parameterExists(COMMANDFILE))
    {
        string s = BBCFileUtils::getFullPath(getParameter(COMMANDFILE));
        storeParameter(COMMANDFILE, s);
        if (s.size() > 0)
        {

            CommandFile f = CommandFile(s);
            char** commands = f.getCommandBuffer();
            size_t length = f.commandBufferLength();
            parse(commands, length , EParmCommandFile);
        }
    }
    iParametersValid = true;

}

// ----------------------------------------------------------------------------
// CommandLine::showCommandLineOptionsAndExit
// Show options and exit
// ----------------------------------------------------------------------------
//
void CommandLine::showCommandLineOptionsAndExit()
{    
    cout << "HeaderAnalyser v" << HEADER_ANALYSER_VERSION << " - " << HEADER_ANALYSER_DATE << endl;
    cout << "Copyright (c) 2001-2009 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.\n"
            "\n"
            "Usage: ha [parameters]\n"
            "\n"
            "Parameters:\n"
            "  -baseline FILE             Baseline FILE used when comparing two files\n"
            "  -current FILE              Current release FILE used when comparing two files\n"
            "  -baselinedir               Baseline directory WILDCARDS used when comparing two files\n"
            "      WILDCARDS;WILDCARDS\n"
            "  -currentdir                Current release DIR used when comparing two files\n"
            "      DIR;DIR\n"
            "  -baselineversion NAME      NAME of the baseline\n"
            "  -currentversion NAME       NAME of the current release\n"
            "  -reportfile FILE           Save report to FILE\n"
            "  -commandfile FILE          Read command line parameters from FILE\n"
            "  -baseplatformheaders       Read baseline platform headers from DIR\n"
            "      DIR;DIR\n"
            "  -currentplatformheaders    Read current release platform headers from DIR\n"
            "      DIR;DIR\n"
            "  -forcebaseinclude          Force to include this FILE always for baseline\n"
            "      FILE;FILE\n"
            "  -forcecurrentinclude       Force to include this FILE always for current release\n"
            "      FILE;FILE\n"
            "  -recursive                 Include sub directories when scanning files\n"
            "  -excludedirs DIR;DIR       When recursive is in use, exclude DIR\n"
            "  -set FILE;FILE             Include only this FILE to the analysis. Wildcards can be used also.\n"
            "  -replace FILE NEWFILE      Notify FILE has been renamed as NEWFILE in current\n"
            "  -bundlesize COUNT          Specifies COUNT files are processed in one go\n"
            "  -temp DIRECTORY            DIRECTORY to store intermediate files\n"
            "  -docurl URL                Includes documentation URL for each issue\n"
			"  -baseplatformdata FILE     Read baseline platform data from FILE.\n"
			"                             The data is used when compiling the baseline headers\n"
			"  -currentplatformdata FILE  Read current platform data from FILE.\n"
			"                             The data is used when compiling the current headers\n"
			"  -usethread                 Enables multiple threading logic.Useful for Public vs Rnd\n"
			"                             Sdk analysis or small no of headers (<3000).\n"
            "\n";
    
    exit(0);    
}
