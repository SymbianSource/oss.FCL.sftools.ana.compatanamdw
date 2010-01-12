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
* Description:  Misc utility functions 
*
*/


#include "la.hpp"

// ----------------------------------------------------------------------------------------------------------

void MakeSureTrailingDirectoryMarkerExists(string& path)
{
	if (!path.empty() && path.at(path.length()-1) != DIR_SEPARATOR2)
        {
		path.insert(path.length(), DIR_SEPARATOR);
        }
}

// ----------------------------------------------------------------------------------------------------------

bool FileExists(const string& path)
{
    if (!path.empty())
    {
        struct stat stat_p;
        if (stat(path.c_str(), &stat_p) == 0)
            return !S_ISDIR(stat_p.st_mode);  // return true if not a directory
        else
            return false;  // cannot find entry
    }
    else
        return false;
}

// ----------------------------------------------------------------------------------------------------------

bool DirectoryExists(const string& path)
{
    if (!path.empty())
    {
        string temp_path = path;
        
        // remove trailing directory marker if exists
        if (path.at(path.length()-1) == DIR_SEPARATOR2)
            temp_path = path.substr(0, path.length()-1);
            
        struct stat stat_p;
        if (stat(temp_path.c_str(), &stat_p) == 0)
            return S_ISDIR(stat_p.st_mode);  // return true if a directory
        else
            return false;  // cannot find entry
    }
    else
        return false;
}

// ----------------------------------------------------------------------------------------------------------

bool RemoveFile(const string& path)
{
    return _unlink(path.c_str()) == 0;
}

// ----------------------------------------------------------------------------------------------------------

string LowerCase(const string& s)
{
	char* buf = new char[s.length()];
	s.copy(buf, s.length());
	
	for(unsigned int i = 0; i < s.length(); i++)
		buf[i] = tolower(buf[i]);
	
	string r(buf, s.length());
	delete buf;
	return r;
}

// ----------------------------------------------------------------------------------------------------------

void MkDirAll(const string& path)
{
    if (!path.empty() && !DirectoryExists(path))
    {
        string target_path = path;
        
        // make sure that the directory has a trailing directory marker
        MakeSureTrailingDirectoryMarkerExists(target_path);
        
        // loop through each character in the string and try to find directory delimeters
        for (unsigned int i=0; i<target_path.length(); i++)
        {
            string::size_type pos = target_path.find(DIR_SEPARATOR, i);

            if (pos != string::npos)
            {
                // construct the base directory name
                string base_directory = target_path.substr(0, pos+1);
                //cerr << "MkDirAll: base_directory: " << base_directory << endl;
                
                if (!DirectoryExists(base_directory))
                {
                    //cerr << "MkDirAll: trying to create: " << base_directory << endl;
                    _mkdir(base_directory.c_str());    
                }
                
                i=pos;
            }    
        }
    }
}

// ----------------------------------------------------------------------------------------------------------

bool ExecuteCommand(const string& command, vector<string>& resultset)
{
    // note, cannot use compiler parameters "-std=c++98" because of popen/pclose
    // also cannot compile this code is MSVC because usage of popen/pclose

    FILE* fp;
    char buffer[1024];
    string tempstr;

    resultset.clear();

    if ((fp = _popen(command.c_str(), "r")) == NULL)
    {    
        return false;
    }

    while (fgets(buffer, sizeof(buffer), fp))
    {
        tempstr = buffer;
        resultset.push_back(tempstr.substr(0, tempstr.size()-1));  
    }   

    _pclose(fp);

    return true;
}

// ----------------------------------------------------------------------------------------------------------

string& TrimRight(string& s)
{
	int pos(s.size());
	for (; pos && (s[pos-1]==' ' || s[pos-1]=='\t' || s[pos-1]=='\r'); --pos);
	s.erase(pos, s.size()-pos);
	return s;
}

// ----------------------------------------------------------------------------------------------------------

string& TrimLeft(string& s)
{
	int pos(0);
	for (; s[pos]==' ' || s[pos]=='\t' || s[pos]=='\r'; ++pos);
	s.erase(0, pos);
	return s;
}

// ----------------------------------------------------------------------------------------------------------

string& TrimAll(string& s)
{
	return TrimLeft(TrimRight(s));
}

// ----------------------------------------------------------------------------------------------------------

int StringICmp(const string& s1, const string& s2)
{
    string ss1 = LowerCase(s1);
    string ss2 = LowerCase(s2);
    
    return ss1.compare(ss2);
}

// ----------------------------------------------------------------------------------------------------------

int StringICmpFileNamesWithoutExtension(const string& s1, const string& s2)
{
    // remove extension and then compare
    string ss1;
    string ss2;
    
    string::size_type dot_pos1 = s1.find_last_of('.');
    if (dot_pos1 == string::npos)
        ss1 = s1;
    else
        ss1 = s1.substr(0, dot_pos1);    

    string::size_type dot_pos2 = s2.find_last_of('.');
    if (dot_pos2 == string::npos)
        ss2 = s2;
    else
        ss2 = s2.substr(0, dot_pos2);
        
    //cerr << endl << ss1 << endl << ss2 << endl;
    
    return StringICmp(ss1, ss2);
}

// ----------------------------------------------------------------------------------------------------------

string Int2Str(int value)
{
    ostringstream os;
    if (os << value)
        return os.str();
    else    
        return ""; 
}

// ----------------------------------------------------------------------------------------------------------

int Str2Int(const string& s)
{
    int res(0);

    // return 0 for empty string
    if (s.empty())
    {
    }
    
    // hex conversion if the string begings with 0x...
    else if (s.length() >= 3 && s.at(0) == '0' && s.at(1) == 'x')
    {
        //sscanf(s.c_str(), "%x", &res);
        istringstream is(s);
        is >> hex >> res;
        if(!is || !is.eof())
            res = 0;
    }
    
    // normal integer
    else  
    {
        //sscanf(s.c_str(), "%d", &res);
        istringstream is(s);
        is >> res;
        if(!is || !is.eof())
            res = 0;
    }    

    return res;
}

// ----------------------------------------------------------------------------------------------------------

void InsertQuotesToFilePath(string& s)
{
    // example C:\Program Files\do something.exe -> C:\"Program Files"\"do something.exe"
    
    bool firstBacklashFound = false;
    bool anyQuoteInserted = false;

    if (!s.empty())
    {
        int s_length = s.length();

        for (int i=0; i<s_length; i++)
        {
            string::size_type pos = s.find(DIR_SEPARATOR, i);
            
            if (pos != string::npos)
            {
                if (!firstBacklashFound)
                {
                    // replace \ -> \"
                    s.insert(pos+1, "\"");
                    
                    anyQuoteInserted = true;
                    firstBacklashFound = true;
                    s_length++;
                    i = pos+1;
                }
                else
                {
                    // replace \ -> "\"
                    s.insert(pos, "\"");
                    s.insert(pos+2, "\"");

                    anyQuoteInserted = true;                        
                    s_length += 2;
                    i = pos+2;
                }
            }          
           
            if (i>255)
                return;  // something went wrong..
        }

        // append extra quote to the end if needed        
        if (anyQuoteInserted)
            s.insert(s.length(), "\"");
    }
}

// ----------------------------------------------------------------------------------------------------------
vector<string> splitString(const string& str, char separator)
{
    vector<string> ret;
    string::size_type pos = str.find(separator);
    unsigned int lastpos = 0;
    while(pos != string::npos)
    {
        ret.push_back(str.substr(lastpos, pos - lastpos));
        lastpos = (unsigned int)pos + 1;
        pos = str.find(separator, lastpos);
    }
    if (!str.empty())
    {
        ret.push_back(str.substr(lastpos, pos));
    }
    return ret;
}
// ----------------------------------------------------------------------------------------------------------
const string getFilename( const string& path)
{
    string::size_type pos = path.find_last_of(DIR_SEPARATOR);
    unsigned int newpos = pos+1;
	if(pos != string::npos)
    {
        return path.substr( newpos, path.size()-newpos);
    }
    return path;
}
// ----------------------------------------------------------------------------------------------------------
const string getPlatform( const string& path)
{
    string platform(path);
    string pattern;
    string::size_type pos1;
    string::size_type pos2;
    pattern.append("epoc32").append(DIR_SEPARATOR).append("release").append(DIR_SEPARATOR);
    
    if ((pos1 = platform.find(pattern)) != string::npos)
    {
      pos2=platform.find(DIR_SEPARATOR,pos1+pattern.length());
      if(pos2!=string::npos)
        platform = platform.substr(pos1+pattern.length(),pos2-(pos1+pattern.length()));
      else
        platform="";
    }
    else
      platform = ""; 
      
    return platform;
}
// ----------------------------------------------------------------------------------------------------------
void getSeverityString(TypeOfSeverity severity, string& bc_severity, string& sc_severity)
{
	switch (severity)
	{
	case CONFIRMED_BC_BREAK:
		{
		bc_severity = "BBC Break";
		sc_severity = "None";
		}
		break;
	case POSSIBLE_BC_BREAK:
		bc_severity = "Possible BBC Break";
		sc_severity = "None";
		break;
	case CONFIRMED_SC_BREAK:
		bc_severity = "None";
		sc_severity = "SC Break";
		break;
	case POSSIBLE_SC_BREAK:
		bc_severity = "None";
		sc_severity = "Possible SC Break";
		break;
	case CONFIRMED_BC_AND_SC_BREAK:
		{
		bc_severity = "BBC Break";
		sc_severity = "SC Break";
		}
		break;
	case POSSIBLE_BC_SC_BREAK:
		{
		bc_severity = "Possible BBC Break";
		sc_severity = "Possible SC Break";
		}
		break;
	case CONFIRMED_BC_POSSIBLE_SC_BREAK:
		{
		bc_severity = "BBC Break";
		sc_severity = "Possible SC Break";
		}
		break;
	case POSSIBLE_BC_CONFIRMED_SC_BREAK:
		{
		bc_severity = "Possible BBC Break";
		sc_severity = "SC Break";
		}
		break;
	case BC_INFORMATIVE:
		{
		bc_severity = "Informative";
		sc_severity = "None";
		}
		break;
    case SC_INFORMATIVE:
		{
		bc_severity = "None";
		sc_severity = "Informative";
		}
		break;
	case BC_SC_INFORMATIVE:
		{
		bc_severity = "Informative";
		sc_severity = "Informative";
		}
		break;
    default:
		{
		bc_severity = "No Break";
		sc_severity = "No Break";
		}
		break;
	}
}

// ----------------------------------------------------------------------------------------------------------
string CharToHex(char* buf)
{
  string ret;
  static char finalhash[4];	
  char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  int k=0;

  for(int j = 3; j >=0; j--)
  {
    finalhash[k*2] = hex[((buf[j] >> 4) & 0xF)];
    finalhash[(k*2) + 1] = hex[((buf[j]) & 0xF)];
    k++;
  }

  ret=finalhash;
  return ret;
}

// ----------------------------------------------------------------------------------------------------------
string HexValueAt(fstream& f, const int offset)
{
	string ret;
	char* buf;
  buf = (char*)malloc(DLL_ENTRY_SIZE);
	f.seekg(offset);	
  memset (buf , 0 , DLL_ENTRY_SIZE);
  f.read(buf, DLL_ENTRY_SIZE);
  ret=CharToHex(buf);
  
  // free buf memory
  if(buf != NULL)
  {
	  free((void*)buf);
	  buf = NULL;
  }
  return ret;
}
// ----------------------------------------------------------------------------------------------------------
void intializeDllIssue(dll_issue& aIssue)
{
	aIssue.l_dllname = "";
	aIssue.i_list_typeid.clear();
}
// ----------------------------------------------------------------------------------------------------------
void fillDllIssue ( char* dllMember ,  unsigned int& typeId)
{
	if (strcmp (dllMember,"uid1") == 0 )
		typeId = DLL_TARGET_TYPE_CHANGED;
	if (strcmp (dllMember,"uid2") == 0 )
		typeId =  DLL_UID2_CHANGED;
	if (strcmp (dllMember,"uid3") == 0 )
		typeId = DLL_UID3_CHANGED;
	if (strcmp (dllMember,"sid") == 0 )
		typeId = DLL_SID_CHANGED;
	if (strcmp (dllMember,"capability") == 0 )
		typeId = DLL_CAPABILITY_CHANGED;
}
// ----------------------------------------------------------------------------------------------------------
int parseHex(const char* hex)
{
	int res;
	int val;
	const char* ptr;
	
	res = 0;
	ptr = hex;
	
	while((*ptr)=='0') ptr++;
	
	while(*ptr)
	{
		if(!((*ptr<'0')||(*ptr>'9')))
		{
			val = *ptr - '0';
		}
		else if(!((*ptr<'a')||(*ptr>'f')))
		{
			val = *ptr - 'a' + 10;
		}
		else if(!((*ptr<'A')||(*ptr>'F')))
		{
			val = *ptr - 'A' + 10;
		}
		else
		{
			return -1;
		}
		
		res = res*16+val;
		
		ptr++;
	}
	
	return res;
}
string GetDllBreakTypeInfoString (int typeId)
{
	string typeinfo = "";
	switch(typeId)
	{
	case DLL_TARGET_TYPE_CHANGED:
		typeinfo = "Target type/UID1 has been changed";
		break;
	case DLL_UID2_CHANGED:
		typeinfo = "UID2 has been changed";
		break;
	case DLL_UID3_CHANGED:
		typeinfo = "UID3 has been changed";
		break;
	case DLL_SID_CHANGED:
		typeinfo = "Secure ID has been changed";
		break;
	case DLL_CAPABILITY_CHANGED:
		typeinfo = "Capability has been changed";
		break;
	case DLL_CURRENT_MISSING:
		typeinfo = "DLL is missing in current SDK";
		break;
	case DLL_BASELINE_MISSING:
		typeinfo = "Baseline DLL is not available for analysis";
		break;
	default:
		break;
	}
	return typeinfo;
}