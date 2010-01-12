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
* Description:  Utility functions for getting data via 3rd party tools
*
*/


#include "la.hpp"

// ----------------------------------------------------------------------------------------------------------
// TIP: Use The Regex Coach (http://weitz.de/regex-coach/) to check that the regular expressions are working correctly
// Note that in C/C++ code \ has been replaced with \\ and " with \".
// ----------------------------------------------------------------------------------------------------------

void GetSymbolTableWithNM(const string& nm_location, const string& lib_name, vector<string>& symbol_table)
{
    symbol_table.clear();
    vector<string> tempVector;
    vector<ordinal> ordinals;
    
    // execute nm
    string cmd = nm_location + " --demangle \"" + lib_name + "\"";
    ExecuteCommand(cmd, tempVector);

   
    // parse the results of the command
    for (unsigned int j=0; j<tempVector.size(); j++)
    {
        // first check if we have found the beginning of a block
 
        boost::cmatch matches1;
        boost::cmatch matches2;
        boost::cmatch matches3;
    
        bool match1 = false;
        bool match2 = false;
        bool match3 = false;
    
        // Symbian OS 6.1 LIB file, example: ds00001.o:
        boost::regex re1("^ds(\\d+)\\.o\\:");
        match1 = boost::regex_match(tempVector.at(j).c_str(), matches1, re1);
    
        if (!match1)
        {
            // Symbian OS 7.x-8.x LIB file, example: C:/DOCUME~1/mattlait/LOCALS~1/Temp/1/d1000s_00001.o:
            boost::regex re2("^\\S*s_(\\d+)\\.o\\:");
            match2 = boost::regex_match(tempVector.at(j).c_str(), matches2, re2);
            
            if (!match2)
            {
                // Symbian OS 9.x LIB file, example: AGENTDIALOG{000a0000}-14.o:
                boost::regex re3("^\\S*\\{000a0000\\}-(\\d+)\\.o\\:");
                match3 = boost::regex_match(tempVector.at(j).c_str(), matches3, re3);
            }
        }
    
        if (match1 || match2 || match3)
        {
            // now get the ordinal number
            string ordNum;
            
            if (match1)
                {
                string ms(matches1[1].first, matches1[1].second);
                ordNum = ms;
                }
            else if (match2)
                {
                string ms(matches2[1].first, matches2[1].second);
                ordNum = ms;
                }
            else if (match3)
                {
                string ms(matches3[1].first, matches3[1].second);
                ordNum = ms;
                }
    
            // now start looking for the line with the export name
            // eg: 00000000 T CUserActivityManager::RunL(void)
            while (j<tempVector.size()-1)
            {
                j++;
    
                boost::regex re4("^\\d+\\sT\\s(.*)$");
                boost::cmatch matches4;
    
                if (boost::regex_match(tempVector.at(j).c_str(), matches4, re4))
                {
                    // now we have a full entry
                    string ms(matches4[1].first, matches4[1].second);

                    // append to the ordinal list
                    ordinals.push_back(ordinal(Str2Int(ordNum), ms));
   
                    break;
                }
            }
        } // (match1 || match2)
    } // for (int j=0; j<tempVector.size(); j++)
    
    // convert the ordinal list into a symbol table
    ConvertOrdinalListIntoSymbolTable(ordinals, symbol_table, lib_name); 


    //for (int k=0; k<symbol_table.size(); k++)
    //{
    //    cerr << symbol_table.at(k) << endl;
    //}

    //if (symbol_table.size() == 0)
    //{
    //    cerr << "Warning: No ordinals in " << lib_directory << lib_name << endl;
    //}
  

}

// ----------------------------------------------------------------------------------------------------------

void GetSymbolTableWithReadelf(const string& readelf_location, const string& cfilt_location, const string& lib_name, vector<string>& symbol_table)
{
    symbol_table.clear();
    vector<string> tempVector;
    vector<ordinal> ordinals;
    
    // execute readelf
    // note: 2>NUL is used here to redirect standard error output to NULL since readelf seems to output lots of unwanted warning messages
    string cmd = readelf_location + " -s -W \"" + lib_name + "\" " + CERR_TO_NULL;
    ExecuteCommand(cmd, tempVector);

   
    // parse the results of the command
    for (unsigned int j=0; j<tempVector.size(); j++)
    {
        boost::cmatch matches1;
    
        // example:
        //     1: 00000000     4 NOTYPE  GLOBAL DEFAULT    1 _ZN13CSpdiaControl10DrawShadowER9CWindowGcRK5TSize@@SpdCtrl{000a0000}[10005986].dll
        boost::regex re1("^\\s*(\\d+)\\:.+GLOBAL.+\\d+\\s+(.*)\\@\\@.*");
        
        if (boost::regex_match(tempVector.at(j).c_str(), matches1, re1))
        {
            // match found
            string ms1(matches1[1].first, matches1[1].second);
            string ms2(matches1[2].first, matches1[2].second);

            // append to the ordinal list
            ordinals.push_back(ordinal(Str2Int(ms1), ms2));
        }

    } // for (int j=0; j<tempVector.size(); j++)
    
    // convert the ordinal list into a symbol table
    ConvertOrdinalListIntoSymbolTable(ordinals, symbol_table, lib_name); 

    // finally demangle all function names since it's not done in this case automatically
    DemangleOrdinalsInSymbolTable(cfilt_location, symbol_table);

    //for (int k=0; k<symbol_table.size(); k++)
    //{
    //    cerr << symbol_table.at(k) << endl;
    //}

    //if (symbol_table.size() == 0)
    //{
    //    cerr << "Warning: No ordinals in " << lib_directory << lib_name << endl;
    //}

}

// ----------------------------------------------------------------------------------------------------------

void GetSymbolTableWithArmar(const string& armar_location, const string& cfilt_location, const string& lib_name, vector<string>& symbol_table)
{
    symbol_table.clear();
    vector<string> tempVector;
    vector<ordinal> ordinals;
    
    // execute armar
    string cmd = armar_location + " --zs \"" + lib_name + "\"";
    ExecuteCommand(cmd, tempVector);

   
    // parse the results of the command
    for (unsigned int j=0; j<tempVector.size(); j++)
    {
        // find the entries, example:
        // _ZN13TAgnWeeklyRptC1Ev from AGNMODEL{000a0000}-187.o at offset 158366
        boost::regex re1("(\\S*)\\s+from\\s.*-(\\d+)\\.o.*");
        boost::cmatch matches1;
        
        if (boost::regex_match(tempVector.at(j).c_str(), matches1, re1))
        {
            // match found
            string ms1(matches1[2].first, matches1[2].second);
            string ms2(matches1[1].first, matches1[1].second);

            // append to the ordinal list
            ordinals.push_back(ordinal(Str2Int(ms1), ms2));            
        }

    } // for (int j=0; j<tempVector.size(); j++)
    
    // convert the ordinal list into a symbol table
    ConvertOrdinalListIntoSymbolTable(ordinals, symbol_table, lib_name); 

    // finally demangle all function names since it's not done in this case automatically
    DemangleOrdinalsInSymbolTable(cfilt_location, symbol_table);


    //for (int k=0; k<symbol_table.size(); k++)
    //{
    //    cerr << symbol_table.at(k) << endl;
    //}

    //if (symbol_table.size() == 0)
    //{
    //    cerr << "Warning: No ordinals in " << lib_directory << lib_name << endl;
    //}

}

// ----------------------------------------------------------------------------------------------------------

void GetSymbolTableWithFromelf(const string& fromelf_location, const string& cfilt_location, const string& lib_name, vector<string>& symbol_table)
{
    symbol_table.clear();
    vector<string> tempVector;
    vector<ordinal> ordinals;
    
    // execute fromelf
    string cmd = fromelf_location + " -s \"" + lib_name + "\"";
    ExecuteCommand(cmd, tempVector);
   
    // parse the results of the command
    for (unsigned int j=0; j<tempVector.size(); j++)
    {
        // first find the start of the symbol table
        // ** Section #5 '.version' (SHT_GNU_versym)
        boost::regex re1("^.*(SHT_GNU_versym).*");
        boost::cmatch matches1;
        
        if (boost::regex_match(tempVector.at(j).c_str(), matches1, re1))
        {
            //int previous_ordinal = 0;

            while (j<tempVector.size()-1)
            {
                j++;

                //cout << tempVector.at(j) << endl;

                // now find the entries, examples:
                //         7   _ZNK17CPbkContactEngine9FsSessionEv           2 PbkEng{000a0000}[101f4cce].dll
                //         8   _ZN17CPbkContactEngine19CreateEmptyContactLEv
                //                                                           2 PbkEng{000a0000}[101f4cce].dll
                // notice that line can be spread to two lines so make sure we don't accidentally get a wrong line

                // first parse out any unwanted lines
                boost::regex re2("^\\s*\\d+\\s+\\S+\\.\\w+$");
                boost::cmatch matches2;
                if (boost::regex_match(tempVector.at(j).c_str(), matches2, re2))
                {
                    //cout << "skipping" << endl;    
                    continue;                
                }

                // now it should be the wanted line
                boost::regex re3("^\\s*(\\d+)\\s*(\\S*).*");
                boost::cmatch matches3;

                if (boost::regex_match(tempVector.at(j).c_str(), matches3, re3))
                {    
                    // cout << tempVector.at(j) << endl;

                    // match found
                    string ms1(matches3[1].first, matches3[1].second);
                    string ms2(matches3[2].first, matches3[2].second);
        
                    // append to the ordinal list
                    ordinals.push_back(ordinal(Str2Int(ms1), ms2));

                    //cout << "match " << ms1 << " " << ms2 << endl;    
                    
                    // with fromelf, all entries are in order
                    // check that we don't miss any ordinals
                    //if (previous_ordinal + 1 != Str2Int(ms1))
                    //{
                    //    cerr << endl << "Aborting because of Fromelf ordinal order check error in " << lib_directory << lib_name << " in line:" << endl << tempVector.at(j) << endl;
                    //    exit(11);    
                    //}
                    //previous_ordinal = Str2Int(ms1);
                }

            } //while (j<tempVector.size())

      
        } //if (boost::regex_match(tempVector.at(j).c_str(), matches1, re1))

    } // for (int j=0; j<tempVector.size(); j++)

    // convert the ordinal list into a symbol table
    ConvertOrdinalListIntoSymbolTable(ordinals, symbol_table, lib_name); 

    // finally demangle all function names since it's not done in this case automatically
    DemangleOrdinalsInSymbolTable(cfilt_location, symbol_table);

    //for (int k=0; k<symbol_table.size(); k++)
    //{
    //    cerr << symbol_table.at(k) << endl;
    //}

    //if (symbol_table.size() == 0)
    //{
    //    cerr << "Warning: No ordinals in " << lib_directory << lib_name << endl;
    //}

}

// ----------------------------------------------------------------------------------------------------------

void ConvertOrdinalListIntoSymbolTable(const vector<ordinal>& ordinals, vector<string>& symbol_table, const string& lib_path)
{
    // remove any invalid ordinals from the list    
    vector<ordinal> ordinalVectorCopy;
    ordinalVectorCopy.reserve(ordinals.size());

    for (unsigned int i=0; i<ordinals.size(); i++)
    {
        if (ordinals.at(i).funcpos <= 0 && ordinals.at(i).funcpos > 32000)
        {
            cerr << "Error: Invalid ordinal " << ordinals.at(i).funcname << " @ " << Int2Str(ordinals.at(i).funcpos) << endl;
        }
        else
        {
            ordinalVectorCopy.push_back(ordinals.at(i));
        }
    }

    // sort the ordinal list
    sort(ordinalVectorCopy.begin(), ordinalVectorCopy.end(), OrdinalCompare);

    // now check that there are no missing ordinals in the list
    unsigned int previous_ordnumber = 0;
    unsigned int current_ordnumber = 1;
    for (unsigned int i=0; i<ordinalVectorCopy.size(); i++)
    {      
        // get the current ordinal number
        current_ordnumber = ordinalVectorCopy.at(i).funcpos;
        //cout << "CurOrdNum: " << Int2Str(current_ordnumber) << endl;
        
        // the current ordinal number obviously should be one bigger than the previous one
        if ( current_ordnumber != previous_ordnumber+1 )
        {
            // append a dummy ordinal to the list
            ordinalVectorCopy.insert(ordinalVectorCopy.begin()+i, ordinal(i+1, "UnknownOrdinal-"+Int2Str(i+1)));
            current_ordnumber = i+1;
            //cout << "Appended a dummy ordinal at pos " << Int2Str(i+1) << endl;
        }

        // remember the previous ordinal number
        previous_ordnumber = current_ordnumber;
        
        // if the ordinal list is corrupted, it may lead to an infinite loop
        if (i>25000)
        {
            cerr << endl << "Something went horribly wrong when trying to parse " << lib_path << ". Aborting." << endl;           
            exit(10);
        }
    }    
   
    // finally copy data from the ordinal list to the symbol table
    if (symbol_table.size() < ordinalVectorCopy.size())
    {
        symbol_table.reserve(ordinalVectorCopy.size());
    }
    for (unsigned int i=0; i<ordinalVectorCopy.size(); i++)
    {      
        symbol_table.push_back( ordinalVectorCopy.at(i).funcname );
    }
}

// ----------------------------------------------------------------------------------------------------------

void DemangleOrdinalsInSymbolTable(const string& cfilt_location, vector<string>& symbol_table)
{
    ofstream f(_tempfile_location.c_str(), ios::trunc);
    if (f.is_open())
    {
        // create a temp file which contain all the function names
        for (unsigned int k=0; k<symbol_table.size(); k++)
        {   
            f << symbol_table.at(k) << endl;
        }
        f.close();

        // execute cfilt
        vector<string> cfilt_result_set;
        string tempfile_loc = _tempfile_location;
        InsertQuotesToFilePath(tempfile_loc);
        string cmd = cfilt_location + " < " + tempfile_loc;
        ExecuteCommand(cmd, cfilt_result_set);

        // check that all functions exist and then replace the symbol table with demangled functions        
        if (cfilt_result_set.size() == symbol_table.size())
        {
            symbol_table = cfilt_result_set;
        }
    }
    else
    {
        f.close();
    }    
}

// ----------------------------------------------------------------------------------------------------------

bool OrdinalCompare(const ordinal& left, const ordinal& right)
{
    return left.funcpos < right.funcpos;
}

// ----------------------------------------------------------------------------------------------------------

   
