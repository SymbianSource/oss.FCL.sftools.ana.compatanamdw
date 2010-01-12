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
* Description:  
*
*/


#ifndef __COMMAND_LINE_H__
#define __COMMAND_LINE_H__
#include "CmdGlobals.h"
#ifdef __WIN__
#pragma warning(disable:4786)
#endif
#include <string>
#include <map>
#include <set>

using namespace std;
typedef pair<string, string> mapentry;

/**
* The class CommandLine handles the command line parsing and represents
* the options for the program in an easy way.
*/
class CommandLine {

// constructors & destructors
public:
    /**
    * Constructor
    */
    CommandLine();
    
    /**
    * Constructor
    * @param args commanline argument as pointer to string
    * @param argc argument count
    */
    CommandLine(char** args, int argc);

    /**
    * Destructor
    */
    ~CommandLine();

// public methods
public:
    /**
    * Returns the parameter value for a given parameter.
    *
    * @param parm parameter to get
    * @return parameter value
    * @exception throw an exception if illegal parameter is requested.
    */ 
    string getParameter(string parm);

    /**
    * Get parameters
    * @return map of parameters
    */ 
    const map <string, string>& getParameters();

    /**
    * Check if the asked parameter is given
    * @param parm parameter name
    * @return true if the asked parameter is given
    */ 
    bool parameterExists(const string& parm);

    /**
    * Validate parameters. Returns a string containing mismatching/insufficiently
    * specified parameters if there are any mismatches. Otherwise returns a string 
    * of zero length.
    * @return error string consisting of invalid parameters.
    */ 
    string  validateParameters();

    /**
    * Check if the given parameter value is valid
    * @param parm parameter to check
    * @param val parameter value to check
    */ 
    void validParamValue(string parm, string val);

// private methods
private:
    /**
    * Inserts a parameter into parameter validation lists.
    * This is *NOT* the same as storeParameter, which stores
    * the actual parameter value of a command line parm.
    *
    * Parameter to be inserted can require a specifier/no 
    * specifier, and can be optional/mandatory
    *
    * @param parmname name of the paramter to insert
    * @param specifierRequired if required, this true
    * @param optional true if parameter is optional
    */ 
    void insertParameter(string parmname, bool specifierRequired, bool optional = true);
    
    /**
    * Initialize  acceptable parameters list
    *
    * Define which parameters are valid and which additionally require a string 
    * after them (dir etc), and which are mandatory (ie. modal, ie. non-optional)
    * Also assign the initial values for epocroot directories.
    *
    * See documentation for exact meaning of each parameter.
    */ 
    void initializeAcceptableParametersList();

    /**
    * Stores a parameter. Actual functionality depends on parameter type
    * (was it a command-line parameter [overrides environmental variables and
    * command file variables], a command-file parameter [overrides environmental
    * variables] or an environmental variable)
    * In other words, it's not possible for a command-file parameter or
    * an environment variable to replace any parameter that has been
    * specified on command-line; respectively, command-line argument
    * will always override any other type of argument, no matter where it
    * was earlier defined.
    *
    * Throws an exception if no specifier is given to a parameter that
    * requires one (e.g. -baselinedir requires a specifier [directory],
    * whereas -recursive doesn't)
    *
    * @param parm parameter to store
    * @param val parameter value to store
    * @param parmtype commandline or commandfile
    * @exception an exeption is thrown if no specifier is given to a parameter 
    * that requires one (e.g. -baselinedir requires a specifier [directory],
    * whereas -recursive doesn't) 
    */ 
    void storeParameter(string parm, string val, int parmtype = EParmCommandLine);

    /**
    * Parses the command line parameters and stores them to public instance 
    * variables. 
    * @param params list of params
    * @param count count params
    * @param parmtype defaulttype=EParmCommandLine
    */ 
    void parse(char** params, size_t count, int parmtype = EParmCommandLine);

    /**
    * Show commandline options and exit programe
    * Not enough options are given, so options list is shown and 
    * the program is exited
    */ 
    void showCommandLineOptionsAndExit();
    
// Private instance variables
private:
    //! All the parameters that the program accepts
    map <string, string>    iAcceptableParameterMap;

    //! Map of parameters
    map <string, string>    iParameterMap;

    //! These command line parameters require option
    set <string>            parameterSpecifierSet;

    //! These command line parameters are required
    set <string>            requiredParametersSet;

    //! True if the parameters are valid
    int                     iParametersValid;
    
    //! Command line arguments
    char**                  iArgList;
    
    //! Count of command line arguments
    int                     iArgCount;
};

#endif
