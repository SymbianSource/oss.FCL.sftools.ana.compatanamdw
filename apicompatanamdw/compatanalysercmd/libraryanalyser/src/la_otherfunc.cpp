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
* Description:  Other non-categorized LibraryAnalyser functionality 
*
*/


#include "la.hpp"

// ----------------------------------------------------------------------------------------------------------

void ParseCommandLineParameters(int argc, char* argv[])
{
    //for (int i=1; i<argc; i++)
    //    cerr << argv[i] << endl; 
    
	// loop through the command line parameters and check their usage
	int i=1;
	while (i<argc)
	{
		if (StringICmp("-?", argv[i])==0 ||
		    StringICmp("-h", argv[i])==0 ||
		    StringICmp("--help", argv[i])==0)
		{
			ShowCommandLineOptionsAndExit();
		}
		
		else if (StringICmp("GCC", argv[i])==0)
		{
			_cl_use_gcc = true;
			_toolchain_name = "GCC";
		}
		
		else if (StringICmp("GCCE", argv[i])==0)
		{
			_cl_use_gcce = true;
			_toolchain_name = "GCCE";
		}
		
		else if (StringICmp("RVCT", argv[i])==0)
		{
			_cl_use_rvct = true;
			_toolchain_name = "RVCT";
		}

		else if (StringICmp("--uselibs", argv[i])==0)
		{
			_cl_use_libs = true;
		}

		else if (StringICmp("--debug", argv[i])==0)
		{
			_cl_print_debug = true;
		}
				
		else if (StringICmp("-baselinelibdir", argv[i])==0)
		{
			if (i+1<argc) 
			{ 
				_cl_baselinelibdir = argv[i+1];
				//create a vector from the ';' seperated string
				_lib_dirs_baseline = splitString( _cl_baselinelibdir, ';');
				i++; 
			}
		} 		
		
		else if (StringICmp("-currentlibdir", argv[i])==0)
		{
			if (i+1<argc) 
			{ 
				_cl_currentlibdir = argv[i+1]; 
				//create a vector from the ';' seperated string
				_lib_dirs_current = splitString( _cl_currentlibdir, ';');
				i++; 
			}
		} 
		else if (StringICmp("-baselinedlldir", argv[i])==0)
		{
			if (i+1<argc) 
			{ 
				_cl_baselinedlldir = argv[i+1];
				i++; 
			}
		} 		
		
		else if (StringICmp("-currentdlldir", argv[i])==0)
		{
			if (i+1<argc) 
			{ 
				_cl_currentdlldir = argv[i+1]; 
				i++; 
			}
		} 

		else if (StringICmp("-baselineversion", argv[i])==0)
		{
			if (i+1<argc) { _cl_baselineversion = argv[i+1]; i++; }
		} 

		else if (StringICmp("-currentversion", argv[i])==0)
		{
			if (i+1<argc) { _cl_currentversion = argv[i+1]; i++; }
		} 

		else if (StringICmp("-reportfile", argv[i])==0)
		{
			if (i+1<argc) { _cl_reportfile = argv[i+1]; i++; }
		} 

		else if (StringICmp("-tools", argv[i])==0)
		{
			if (i+1<argc) { _cl_toolsdir = argv[i+1]; i++; }
		}
		
		else if (StringICmp("-temp", argv[i])==0)
		{
			if (i+1<argc) { _cl_tempdir = argv[i+1]; i++; }
		}		

		else if (StringICmp("-cfilt", argv[i])==0)
		{
			if (i+1<argc) { _cl_cfiltloc = argv[i+1]; i++; }
		}
		
		else if (StringICmp("-set", argv[i])==0)
		{
			if (i+1<argc) { _cl_set = argv[i+1]; i++; }
		}
		
		// check if the parameter is illegal
        else
        {
            string param = argv[i];
            
            if (!param.empty() && param.at(0) == '-')
            {
        		cerr << "ERROR: Illegal argument: " << param << endl;
        		cerr << "Type la -? for help" << endl;
                exit(EXIT_INVALID_ARGUMENT);            
            }   
        }

		i++;
	}    
}

// ----------------------------------------------------------------------------------------------------------

void ShowCommandLineOptionsAndExit()
{
    cout << "LibraryAnalyser v" << LA_VERSION << " - " << LA_DATE << "\n"
            "Copyright (c) 2001-2009 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.\n"
            "\n"
#ifdef WIN32
            "Usage: la GCC|GCCE|RVCT [options]\n"
#else
            "Usage: la GCCE|RVCT [options]\n"
#endif
            "\n"
            "Where:\n"
#ifdef WIN32
            "  GCC                      Use Symbian GCC tool chain\n"
#endif
            "  GCCE                     Use CSL ARM tool chain\n"
            "  RVCT                     Use RVCT tool chain\n"
            "\n"
            "Required options:\n"
            "  -baselinelibdir DIR;DIR	    Read baseline libraries from DIRECTORY\n"
            "  -currentlibdir DIR;DIR	    Read libraries of current release from DIRECTORY\n"
            "  -baselineversion NAME    NAME of the baseline\n"
            "  -currentversion NAME     NAME of the current release\n"
            "  -reportfile FILE         Save report to FILE\n"
            "\n"
            "Required options when RVCT tool chain is used:\n"
            "  -cfilt FILE              Location FILE of cfilt/c++filt\n"
            "\n"
            "Optional options:\n"
            "  -baselinedlldir          Read baseline dlls from DIRECTORY or dll data from FILE\n"
            "      DIRECTORY|FILE\n"
			      "  -currentdlldir           Read dlls from DIRECTORY or dll data from FILE for current release\n"
            "      DIRECTORY|FILE\n"
            "  -tools DIRECTORY         DIRECTORY where the used toolset is installed\n"
            "  -temp DIRECTORY          DIRECTORY to store intermediate files\n"
            "  -set FILE                Textfile FILE which has a list of libraries to check\n"
            "  --uselibs                Always use LIBs instead of DSOs (not valid with GCC)\n"
            "\n";

	exit(EXIT_NORMAL);
}

// ----------------------------------------------------------------------------------------------------------

void DoInitialChecksAndPreparations()
{
    // get the current date and time
    time_t timenow_t = time(NULL);
    _timenow = localtime(&timenow_t);  
    
    // check parameter correctness
#ifndef WIN32
        if (_cl_use_gcc)
        {
              cerr << "ERROR: GCC tool chain is not supported in Linux" << endl;  
              exit(EXIT_GCC_NOT_SUPPORTED);
        }
#endif

	if (!_cl_use_gcc && !_cl_use_gcce && !_cl_use_rvct)     
	{	
		cerr << "ERROR: No tool chain defined!" << endl;
		cerr << "Type la -? for help" << endl;
        exit(EXIT_WRONG_USAGE);
	} 

	if (_cl_use_rvct && _cl_cfiltloc.empty())     
	{	
		cerr << "ERROR: Specify -cfilt when RVCT is defined!" << endl;
		cerr << "Type la -? for help" << endl;
        exit(EXIT_WRONG_USAGE);
	}  

	if ( (_cl_use_gcc && (_cl_use_gcce || _cl_use_rvct)) || (_cl_use_gcce && (_cl_use_gcc || _cl_use_rvct)) ||
         (_cl_use_rvct && (_cl_use_gcc || _cl_use_gcce)) )   
	{	
		cerr << "ERROR: Specify only one tool chain!" << endl;
		cerr << "Type la -? for help" << endl;
        exit(EXIT_WRONG_USAGE);
	} 

	if (_cl_baselinelibdir.empty() || _cl_currentlibdir.empty() || _cl_baselineversion.empty() || _cl_currentversion.empty() || _cl_reportfile.empty())    
	{	
		cerr << "ERROR: Not all required parameters specified!" << endl;
		cerr << "Type la -? for help" << endl;
        exit(EXIT_WRONG_USAGE);
	}

    // make sure the directory names have trailing directory markers
	vector<string>::iterator i = _lib_dirs_baseline.begin();
	for( ; i != _lib_dirs_baseline.end(); i++)
		MakeSureTrailingDirectoryMarkerExists(*i);

	for( i = _lib_dirs_current.begin(); i != _lib_dirs_current.end(); i++)
	    MakeSureTrailingDirectoryMarkerExists(*i);

    MakeSureTrailingDirectoryMarkerExists(_cl_toolsdir);
    MakeSureTrailingDirectoryMarkerExists(_cl_tempdir);

	// check if baselinedir & currentdir exists
	vector<string>::const_iterator j = _lib_dirs_baseline.begin();
	for( ; j != _lib_dirs_baseline.end(); j++)
		if (!DirectoryExists(*j))
		{	
			cerr << "ERROR: " << *j << " not found!" << endl;
			cerr << "Check -baselinelibdir parameter" << endl;
			exit(EXIT_BASELINEDIR_NOT_FOUND);
		}
	for( j = _lib_dirs_current.begin(); j != _lib_dirs_current.end(); j++)
		if (!DirectoryExists(*j))
		{
			cerr << "ERROR: " << *j << " not found!" << endl;
			cerr << "Check -currentlibdir parameter" << endl;
			exit(EXIT_CURRENTDIR_NOT_FOUND);
		}
    
    //if both -baselinedlldir & -currentdlldir are given, check the validity of their value
    if (!_cl_baselinedlldir.empty() && !_cl_currentdlldir.empty())
    {
      if( !FileExists(_cl_baselinedlldir) )
      {
        //create a vector from the ';' seperated string
		    _dll_dirs_baseline = splitString( _cl_baselinedlldir, ';');
        for( i = _dll_dirs_baseline.begin(); i != _dll_dirs_baseline.end(); i++)
			  {
				  MakeSureTrailingDirectoryMarkerExists(*i);        
				  if ( !DirectoryExists(*i) )
				  {
					  cerr << "ERROR: " << *i << " not found!" << endl;
					  cerr << "Check -baselinedlldir parameter" << endl;
					  exit(EXIT_BASELINEDLLDIR_NOT_FOUND);
				  }
			  }
		  }
		  else
		  {
			  _baselinedllfile = _cl_baselinedlldir;
		  }
      if( !FileExists(_cl_currentdlldir) )
      {
        //create a vector from the ';' seperated string
		    _dll_dirs_current = splitString( _cl_currentdlldir, ';');
			  for( i = _dll_dirs_current.begin(); i != _dll_dirs_current.end(); i++)
			  {
				  MakeSureTrailingDirectoryMarkerExists(*i);  
				  if ( !DirectoryExists(*i) )
				  {
					  cerr << "ERROR: " << *i << " not found!" << endl;
					  cerr << "Check -currentdlldir parameter" << endl;
					  exit(EXIT_CURRENTDLLDIR_NOT_FOUND);
				  }
			  }
      }
		  else
		  {
			  _currentdllfile = _cl_currentdlldir;
		  }
    }

    // check if user given filter set exists
    if (!_cl_set.empty() && !FileExists(_cl_set))   
    {
		cerr << "ERROR: " << _cl_set << " not found!" << endl;
		cerr << "Check -set parameter" << endl;
        exit(EXIT_SET_FILE_NOT_FOUND);        
    }

    // if tools parameter is empty, try get it from path, otherwise check given parameter
    if (_cl_toolsdir.empty())
    {
        GetToolsPathFromEnvironmentVariable();
    }
    else
    {
        // check the given tools directory parameter is valid
        if (_cl_use_gcc)
        {
            _gcc_nm_location = _cl_toolsdir + GCC_NM_EXE;
    
        	if (!FileExists(_gcc_nm_location))
        	{
        		cerr << "ERROR: Unable to find " + _gcc_nm_location << ", check -tools parameter" << endl;
        		cerr << "Tip: GCC is typically installed to \\epoc32\\gcc\\bin directory" << endl;
        		exit(EXIT_TOOLCHAIN_NOT_FOUND);
        	}        
    
            // extra quotes needed to prevent white space problems while executing the tool
            InsertQuotesToFilePath(_gcc_nm_location);
        }
    
        else if (_cl_use_gcce)
        {
            _gcce_nm_location = _cl_toolsdir + GCCE_NM_EXE;
            _gcce_readelf_location = _cl_toolsdir + GCCE_READELF_EXE;
            _gcce_cfilt_location = _cl_toolsdir + GCCE_CFILT_EXE;
    
        	if (!FileExists(_gcce_nm_location))
        	{
        		cerr << "ERROR: Unable to find " + _gcce_nm_location << ", check -tools param" << endl;
        		cerr << "Tip: GCCE is typically installed to C:\\Program Files\\CSL Arm Toolchain\\bin" << endl;
        		exit(EXIT_TOOLCHAIN_NOT_FOUND);
        	} 
    
        	if (!FileExists(_gcce_readelf_location))
        	{
        		cerr << "ERROR: Unable to find " + _gcce_readelf_location << ", check -tools param" << endl;
        		cerr << "Tip: GCCE is typically installed to C:\\Program Files\\CSL Arm Toolchain\\bin" << endl;
        		exit(EXIT_TOOLCHAIN_NOT_FOUND);
        	} 
    
        	if (!FileExists(_gcce_cfilt_location))
        	{
        		cerr << "ERROR: Unable to find " + _gcce_cfilt_location << ", check -tools param" << endl;
        		cerr << "Tip: GCCE is typically installed to C:\\Program Files\\CSL Arm Toolchain\\bin" << endl;
        		exit(EXIT_TOOLCHAIN_NOT_FOUND);
        	} 
    
            // extra quotes needed to prevent white space problems while executing the tool
            InsertQuotesToFilePath(_gcce_nm_location);
            InsertQuotesToFilePath(_gcce_readelf_location);
            InsertQuotesToFilePath(_gcce_cfilt_location);
            
        }
    
        else if (_cl_use_rvct)
        {
            _rvct_armar_location = _cl_toolsdir + RVCT_ARMAR_EXE;
            _rvct_fromelf_location = _cl_toolsdir + RVCT_FROMELF_EXE;
    
        	if (!FileExists(_rvct_armar_location))
        	{
        		cerr << "ERROR: Unable to find " + _rvct_armar_location << ", check -tools param" << endl;
        		cerr << "Tip: Check your environment variables to see the directory where RVCT has been installed" << endl;
        		exit(EXIT_TOOLCHAIN_NOT_FOUND);
        	} 
    
        	if (!FileExists(_rvct_fromelf_location))
        	{
        		cerr << "ERROR: Unable to find " + _rvct_fromelf_location << ", check -tools param" << endl;
        		cerr << "Tip: Check your environment variables to see the directory where RVCT has been installed" << endl;
        		exit(EXIT_TOOLCHAIN_NOT_FOUND);
        	} 
                    
            // extra quotes needed to prevent white space problems while executing the tool
            InsertQuotesToFilePath(_rvct_armar_location);
            InsertQuotesToFilePath(_rvct_fromelf_location);
        }            
    } // else of if (!cl_toolsdir)
        
    // check path of RVCT's cfilt is correct
    if (_cl_use_rvct)
    {
        _rvct_cfilt_location = _cl_cfiltloc;
        
    	if (!FileExists(_rvct_cfilt_location))
    	{
    		cerr << "ERROR: Unable to find " + _rvct_cfilt_location << ", check -cfilt param" << endl;
    		cerr << "Tip: Working cfilt.exe can be found from the same directory where LibraryAnalyser has been installed" << endl;
    		exit(EXIT_CFILT_NOT_FOUND);
    	}    
        
        // extra quotes needed to prevent white space problems while executing the tool
        InsertQuotesToFilePath(_rvct_cfilt_location);
    }


    // get temporary directory from environment variable if not specified by the user
    if (_cl_tempdir.empty())
    {
        GetTempPathFromEnvironmentVariable();
    }
    // otherwise create path to user given parameter 
    else
    {
        MkDirAll(_cl_tempdir);
    }   
        
    // check that it is possible to create the temporary file under the temp directory
    _tempfile_location = _cl_tempdir + TEMP_FILENAME;
    ofstream tempf(_tempfile_location.c_str(), ios::trunc);
    if (!tempf.is_open())
    {
        tempf.close();
		cerr << "ERROR: Cannot open " << _tempfile_location << " for writing!" << endl;
		cerr << "Please check that are no write permission problems" << endl;
		exit(EXIT_CANNOT_WRITE_TO_TEMP_FILE);
    }
    else
        tempf.close(); 


    //if -baselinedlldir or -currentdlldir or both not given, throw warning
    if (_cl_baselinedlldir.empty() || _cl_currentdlldir.empty() )    
    {	
        cout << "WARNING: Required parameters for checking dll properties not specified. Breaks in dlls will not be checked!" << endl;
    }
    
    // check if analysing .dso or .lib files
    if (_cl_use_gcc || _cl_use_libs)  // for GCC use always .lib files
        _lib_extension = ".lib";
    else
        _lib_extension = ".dso";
}

// ----------------------------------------------------------------------------------------------------------

void GetToolsPathFromEnvironmentVariable()
{
   #ifdef WIN32
    // get path environment variable
    const char* env_path = getenv("PATH");
    
    if (env_path != NULL)
    {
        string env_path_str = env_path;
        
        string::size_type previous_delimpos = 0;
        bool match_found(false);
        string test_path;

        for (unsigned int i=0; i<env_path_str.length(); i++)
        {
            // directories in %PATH% are separated with ';'-char
            string::size_type delimpos = env_path_str.find(";", i);
            
            if (delimpos != string::npos)
            {
                // get path
                test_path = env_path_str.substr(previous_delimpos, delimpos-previous_delimpos);
                
                //cerr << "Test_path: " << test_path << endl;
                
                MakeSureTrailingDirectoryMarkerExists(test_path);
                
                // remember found position
                previous_delimpos = delimpos + 1;
                i = delimpos;

                // do check if path is correct
                if (_cl_use_gcc)
                {
                    _gcc_nm_location = test_path + GCC_NM_EXE;
           
                	if (FileExists(_gcc_nm_location))
                	{
                		match_found = true;

                        // extra quotes needed to prevent white space problems while executing the tool
                        InsertQuotesToFilePath(_gcc_nm_location);
                	}        
                }
            
                else if (_cl_use_gcce)
                {
                    _gcce_nm_location = test_path + GCCE_NM_EXE;
                    _gcce_readelf_location = test_path + GCCE_READELF_EXE;
                    _gcce_cfilt_location = test_path + GCCE_CFILT_EXE;
            
                	if (FileExists(_gcce_nm_location) && FileExists(_gcce_readelf_location) && FileExists(_gcce_cfilt_location))
                	{
                		match_found = true;

                        // extra quotes needed to prevent white space problems while executing the tool
                        InsertQuotesToFilePath(_gcce_nm_location);
                        InsertQuotesToFilePath(_gcce_readelf_location);
                        InsertQuotesToFilePath(_gcce_cfilt_location);
                	} 
                }
            
                else if (_cl_use_rvct)
                {
                    _rvct_armar_location = test_path + RVCT_ARMAR_EXE;
                    _rvct_fromelf_location = test_path + RVCT_FROMELF_EXE;
            
                	if (FileExists(_rvct_armar_location) && FileExists(_rvct_fromelf_location))
                	{
                		match_found = true;

                        // extra quotes needed to prevent white space problems while executing the tool
                        InsertQuotesToFilePath(_rvct_armar_location);
                        InsertQuotesToFilePath(_rvct_fromelf_location);
                	} 
                }   

            }          

            // first matching directory found, no need to loop anymore
            if (match_found)
            {
                _cl_toolsdir = test_path;
                cerr << "Tool chain found from %PATH% at " << test_path << endl;
                break;
            }                           
            
            if (i>5000)
                break;  // something went wrong..
        }

        if (!match_found)
        {
            cerr << "ERROR: Cannot find specified compiler toolset from PATH environment" << endl;
            cerr << "Fix PATH environment variable or specify -tools parameter" << endl;
        	exit(EXIT_TOOLCHAIN_NOT_FOUND_FROM_PATH);                      
        }

    }
    else
    {
        cerr << "ERROR: PATH environment variable not available, please specify -tools parameter" << endl;
    	exit(EXIT_PATH_VARIABLE_NOT_FOUND);                
    }
  
   #else

    cerr << "ERROR: Optional -tools parameter is only supported in Windows environment " << endl;
	exit(EXIT_ONLY_SUPPORTED_IN_WIN32);                

   #endif

}

// ----------------------------------------------------------------------------------------------------------

void GetTempPathFromEnvironmentVariable()
{
   #ifdef WIN32
    // get path environment variable
    const char* env_path = getenv("TEMP");
    
    if (env_path != NULL)
    {
        string env_path_str = env_path;
        MakeSureTrailingDirectoryMarkerExists(env_path_str);
        
        // check if the directory exists
        if (DirectoryExists(env_path_str))
        {
            _cl_tempdir = env_path_str; 
        }
        else
        {
            cerr << "ERROR: Directory specified in TEMP environment variable does not exist" << endl;
            cerr << "Fix TEMP environment variable or specify -temp parameter" << endl;
        	exit(EXIT_TEMP_DIRECTORY_DOES_NOT_EXIST);               
        }
    }
    else
    {
        cerr << "ERROR: TEMP environment variable not available, please specify -temp parameter" << endl;
    	exit(EXIT_TEMP_VARIABLE_NOT_FOUND);                
    }
  
   #else

    cerr << "ERROR: Optional -temp parameter is only supported in Windows environment " << endl;
	exit(EXIT_ONLY_SUPPORTED_IN_WIN32);                

   #endif

}

// ----------------------------------------------------------------------------------------------------------

void GetListsOfImportLibraries()
{
    string lib_filter = "*" + _lib_extension;
    
    GetFileNamesFromDirectory(_lib_dirs_baseline, lib_filter, _lib_files_baseline);
    GetFileNamesFromDirectory(_lib_dirs_current, lib_filter, _lib_files_current);
}

// ----------------------------------------------------------------------------------------------------------

void GetFileNamesFromDirectory(const vector<string>& directories, const string& filter, vector<string>& resultset)
{  
    // get list of files from the directory by executing OS specific dir/ls command
    string dir_command = DIR_COMMAND;
    vector<string> tempVector;
    vector<string> localVector;
    unsigned int i = 0;
    unsigned int j = 0;
    string cmd;

    // Get filter extension to compare with libname extension
	string::size_type dot_loc = filter.find_last_of(".");
	string filterExtensn;
	if (dot_loc != string::npos)
		filterExtensn = filter.substr(dot_loc,string::npos);

	for(; i < directories.size(); i++)
	{
		cmd = dir_command + " \"" + directories.at(i) + "\"" + filter + " " + CERR_TO_NULL;
		ExecuteCommand(cmd, localVector);
		string fileExtn;
		//append the list of files, along with directory names, to a common vector
		for(j = 0;j < localVector.size(); j++)
		{
			// get lib name extensiion and compare with filter extension.
			dot_loc = localVector.at(j).find_last_of(".");			
			if (dot_loc != string::npos)
				fileExtn = localVector.at(j).substr(dot_loc,string::npos);
			// if extensions are not matching , ignore the libname
			if(stricmp(fileExtn.c_str(),filterExtensn.c_str()) == 0 )
			{
				#ifdef WIN32
				tempVector.push_back( directories.at(i) + localVector.at(j) );
				#else
				tempVector.push_back( localVector.at(j) );
				#endif
			}
		}
	}

	// loop through all returned files
	for (unsigned int i=0; i<tempVector.size(); i++)
	{
		// remove any leading and trailing white spaces
		string file_entry = tempVector.at(i);
		TrimAll(file_entry);

		if (!file_entry.empty())
		{
			resultset.push_back(file_entry);
		}

	}
}

// ----------------------------------------------------------------------------------------------------------

void FilterListsOfImportLibraries()
{
    // if list filtering is enabled (-set param), use only those library files defined in the list
    if (!_cl_set.empty())
    {
		// open the file for reading
        ifstream set_f(_cl_set.c_str());

		if (set_f.is_open())
		{
            if (_cl_print_debug)
            {
                cerr << "Filtering import libraries based on " << _cl_set << endl;    
            }

			vector<string> lib_files_filter;
			string item_str;
			int i=0;
			
			// read all names from the lib
			while(!set_f.eof() && i<50000)
			{
				getline(set_f, item_str);
				item_str = TrimAll(item_str);

				if (!item_str.empty())
                {
                	// strip any directory path, both Windows and Unix style 
                    string::size_type sep_pos = item_str.find_last_of("\\");
                    if (sep_pos != string::npos)
                        item_str = item_str.substr(sep_pos+1, item_str.length()-sep_pos-1); 
                    sep_pos = item_str.find_last_of("/");
                    if (sep_pos != string::npos)
                        item_str = item_str.substr(sep_pos+1, item_str.length()-sep_pos-1);
                        
                    //cerr << "Set filter: " << item_str << endl;     
                        
                    // append the file name to the vector
					lib_files_filter.push_back(item_str);
                }
				
				i++;
			}
			set_f.close();


			// remove from _lib_files_baseline those strings which aren't in lib_files_filter
			for (unsigned int j=0; j<_lib_files_baseline.size(); )
			{
				bool found = false;

				for (unsigned int k=0; k<lib_files_filter.size(); k++)
				{
                   if (StringICmpFileNamesWithoutExtension(getFilename(_lib_files_baseline.at(j)), lib_files_filter.at(k)) == 0)
					{
						// element found, no need to loop anymore
						found = true;
						break;
					}
				}			

				if (!found)  // if not found, remove element j from the vector _lib_files_baseline
					_lib_files_baseline.erase(_lib_files_baseline.begin()+j, _lib_files_baseline.begin()+j+1);
                else
                    j++;
			}

			// remove from _lib_files_current those strings which aren't in lib_files_filter
			for (unsigned int j=0; j<_lib_files_current.size(); )
			{
				bool found = false;

				for (unsigned int k=0; k<lib_files_filter.size(); k++)
				{
					          if (StringICmpFileNamesWithoutExtension(getFilename(_lib_files_current.at(j)), lib_files_filter.at(k)) == 0)
					{
						// element found, no need to loop anymore
						found = true;
						break;
					}
				}			

				if (!found)  // if not found, remove element j from the vector _lib_files_current
					_lib_files_current.erase(_lib_files_current.begin()+j, _lib_files_current.begin()+j+1);
                else
                    j++;
			}
		}
		else
		{
    		cerr << "ERROR: Cannot open " << _cl_set << " for reading!" << endl;
    		cerr << "Check -set parameter" << endl;
            exit(EXIT_CANNOT_OPEN_SET_FILE);
		}

    }
    else
    {
      bool match = false;
      boost::regex re("\\S*\\{\\S{8}\\}\\.[a-zA-Z]{3}");
      
      // filter out any unwanted files from _lib_files_baseline ex:libcrypto{000a0000}.dso
      for (unsigned int j=0; j<_lib_files_baseline.size(); )
      {
        match= boost::regex_match(_lib_files_baseline.at(j), re);
       
        if (match)
          _lib_files_baseline.erase(_lib_files_baseline.begin()+j, _lib_files_baseline.begin()+j+1);
        else
          j++;
      }
      
      // filter out any unwanted files from _lib_files_current ex:libcrypto{00000009}.lib
      for (unsigned int j=0; j<_lib_files_current.size(); )
      {
        match= boost::regex_match(_lib_files_current.at(j), re); 
        
        if (match)
          _lib_files_current.erase(_lib_files_current.begin()+j, _lib_files_current.begin()+j+1);
        else
          j++;
      }
      
    }
}

// ----------------------------------------------------------------------------------------------------------

void DoPreAnalysisChecks()
{
    // report an error if nothing to analyse
    if (_lib_files_baseline.size() == 0 && _lib_files_current.size() == 0)
    {
    	cerr << "WARNING: Nothing to analyse!" << endl;
    }     
}

// ----------------------------------------------------------------------------------------------------------

void DoFinalTasks()
{
    // delete the temporary file
    if (!_tempfile_location.empty())
        RemoveFile(_tempfile_location);
    /*if (!_baselinedllfile.empty())
        RemoveFile(_baselinedllfile);
    if (!_currentdllfile.empty())
        RemoveFile(_currentdllfile);*/
}

// ----------------------------------------------------------------------------------------------------------
  
void CreateDllDataFile(string dllDataFile, vector<string>& dllPath, string type)
{  
  string filter = "*.dll";
  vector<string> dlls_done; 
  vector<string> resultset;
  

  ofstream outputfile( dllDataFile.c_str());
  if(!outputfile.is_open())
  {
    cerr << "ERROR: Cannot open " << dllDataFile << " for writing!" << endl;
    exit(EXIT_CANNOT_OPEN_FILE);
  }
  
  WriteXMLLineOpeningTag(outputfile,0,"dll_list");
	
  GetFileNamesFromDirectory(dllPath,filter,resultset);
  vector<string>::iterator dll = resultset.begin();
  for( ; dll != resultset.end(); dll++)
  {
     	string dllname =  getFilename(*dll);
      //consider the dll only if the corresponding library is to be analysed
      vector<string>::const_iterator i = _lib_files_baseline.begin();
      for(; i != _lib_files_baseline.end(); ++i)   
      {
        if(StringICmpFileNamesWithoutExtension(getFilename(*i),dllname)==0)
					break;
			}

      if (i == _lib_files_baseline.end())
        continue;
                
      //consider the dll file only once
      if(count(dlls_done.begin(),dlls_done.end(),dllname)==1)
      {
        cout<<"Warning: More than one files matches for the given filename '"<<dllname;
        cout<<"' in the "<<type<<" sdk, only the first file is used."<<endl;
        dlls_done.push_back(dllname);
        continue;
      }
      
      if(count(dlls_done.begin(),dlls_done.end(),dllname)>1) 
        continue;
      
      dlls_done.push_back(dllname);

      
      WriteXMLLineOpeningTag(outputfile,0,"dll");    
      WriteXMLLineOpenClosed(outputfile,1,"dllname",dllname);
			
      fstream dllFile((*dll).c_str(),ios::binary | ios::in);
	
      if(!dllFile.is_open())
      {
        cerr << "ERROR: Cannot open " << *dll << " for reading!" << endl;
        exit(EXIT_CANNOT_OPEN_FILE);
      }

      string value;
      
      value=HexValueAt(dllFile, UID1_OFFSET); // 0x00 offset of UID1
      WriteXMLLineOpenClosed(outputfile,1,"uid1",value);
			
      value=HexValueAt(dllFile, UID2_OFFSET); // 0x04 offset of UID2
      WriteXMLLineOpenClosed(outputfile,1,"uid2",value);

      value=HexValueAt(dllFile, UID3_OFFSET); // 0x08 offset of UID3
      WriteXMLLineOpenClosed(outputfile,1,"uid3",value);

      value=HexValueAt(dllFile, SID_OFFSET); // 0x80 offset of Secure ID
      WriteXMLLineOpenClosed(outputfile,1,"sid",value);

      value=HexValueAt(dllFile, CAPABILITY_OFFSET); // 0x88 offset of Capabilities
      WriteXMLLineOpenClosed(outputfile,1,"capability",value);

      WriteXMLLineClosingTag(outputfile,0,"dll");
			
      dllFile.close();
  }
  
  WriteXMLLineClosingTag(outputfile,0,"dll_list");
  outputfile.close();
  
}

// ----------------------------------------------------------------------------------------------------------
void GetDllDataFiles()
{
    if (!_cl_baselinedlldir.empty() && !_cl_currentdlldir.empty() )    
    {	
        //if -baselinedlldir value is path, construct the dll data xml file 
        if( _baselinedllfile.empty() )
        {
            _baselinedllfile = _cl_tempdir + "baselinedlldata.xml";
            CreateDllDataFile(_baselinedllfile,_dll_dirs_baseline, "baseline");
        }
        //if -currentdlldir value is path, construct the dll data xml file 
        if( _currentdllfile.empty() )
        {
            _currentdllfile = _cl_tempdir + "currentdlldata.xml";
            CreateDllDataFile(_currentdllfile,_dll_dirs_current, "current");
        }
    }
}
