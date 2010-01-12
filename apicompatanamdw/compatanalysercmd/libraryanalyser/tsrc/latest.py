#
# Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
# This component and the accompanying materials are made available
# under the terms of "Eclipse Public License v1.0"
# which accompanies this distribution, and is available
# at the URL "http://www.eclipse.org/legal/epl-v10.html".
#
# Initial Contributors:
# Nokia Corporation - initial contribution.
#
# Contributors:
#
# Description:
#

import sys
import os
import re
import time
import platform
from xml.dom import minidom
LATEST_RVCT_BIN = os.environ.get('RVCT22BIN')
if LATEST_RVCT_BIN is None:
    print "Environment variable RVCT22BIN must be set before starting the test harness"
    sys.exit()

TC_DIR = os.getcwd() + os.sep + "TC" + os.sep
SCRIPTS_DIR = os.getcwd() + os.sep + "scripts" + os.sep
RESULTS_DIR = os.getcwd() + os.sep + "results" + os.sep
usage = "-h /h -? /?".split()
debug = 0

def UpdateTimeTaken(tm):
    global time_taken, total_time_taken
    time_taken = tm
    total_time_taken += tm

def Usage():
    print "Usage               : "+ sys.argv[0] + " <outputfile> | -build [<testcasefile>]"
    print "Execute test case(s): " + sys.argv[0] + " <outputfile> [<testcasefile>]"
    print "Build test case     : " + sys.argv[0] + " -build <testcase name>"
    sys.exit()

def LABuild():
    if len(sys.argv) != 3:
        Usage()
    cmd = "python " + SCRIPTS_DIR + "latestbuild.py " + sys.argv[2].upper()
    os.system(cmd)
    sys.exit()

def OpenResults():
    result = RESULTS_DIR + sys.argv[1]
    if os.path.exists(result):
        cmd = "start " + result
        os.system(cmd)
    return
    
def RunAll():
    global time_taken;
    cases = os.listdir(TC_DIR)
    p = re.compile('^LATC')
    for tc in cases:
        tc = tc.strip().upper()
        if p.match(tc):
            print "\n" + tc
            cmd = "python " + SCRIPTS_DIR + "latestrun.py " + tc
            stime = time.clock()
            os.system(cmd)
            etime = time.clock()
            UpdateTimeTaken(etime-stime)
            CompareResult(tc)
    WriteXml()
    if os.name != "posix" :
        OpenResults()
    return
    
def RunTC():
    global time_taken;
    file = open( sys.argv[2] )
    cases = file.readlines()
    file.close()
    for tc in cases:
        tc = tc.strip().upper()
        if tc:
            print "\n" + tc
            cmd = "python " + SCRIPTS_DIR + "latestrun.py " + tc
            stime = time.clock()
            os.system(cmd)
            etime = time.clock()
            UpdateTimeTaken(etime-stime)
            CompareResult(tc)
    WriteXml()
    if os.name != "posix" :
        OpenResults()
    return


def CheckIssues(issue1, issueArr):
    issuefound = 0

    if debug == 1:
        print >>debfile, "-------------------------------\n"
        print >>debfile, "Type Id: "+ issue1.getElementsByTagName('typeid')[0].firstChild.data +" --> "
    
    for issue2 in issueArr:
        if  issue1.getElementsByTagName('typeid')[0].firstChild.data == issue2.getElementsByTagName('typeid')[0].firstChild.data and \
            (issue1.getElementsByTagName('funcpos').length == 0 or issue1.getElementsByTagName('funcpos')[0].firstChild.data == issue2.getElementsByTagName('funcpos')[0].firstChild.data ) and \
            (issue1.getElementsByTagName('newfuncpos').length == 0 or issue1.getElementsByTagName('newfuncpos')[0].firstChild.data == issue2.getElementsByTagName('newfuncpos')[0].firstChild.data ) and \
            (issue1.getElementsByTagName('funcname').length == 0 or issue1.getElementsByTagName('funcname')[0].firstChild.data == issue2.getElementsByTagName('funcname')[0].firstChild.data ) and \
            (issue1.getElementsByTagName('newfuncname').length == 0 or issue1.getElementsByTagName('newfuncname')[0].firstChild.data == issue2.getElementsByTagName('newfuncname')[0].firstChild.data ) and \
            (issue1.getElementsByTagName('bc_severity') == 0 or issue1.getElementsByTagName('bc_severity')[0].firstChild.data == issue2.getElementsByTagName('bc_severity')[0].firstChild.data ) and \
            (issue1.getElementsByTagName('sc_severity') == 0 or issue1.getElementsByTagName('sc_severity')[0].firstChild.data == issue2.getElementsByTagName('sc_severity')[0].firstChild.data ):
               if debug == 1:
                   print >>debfile, "Found.\n"
               issuefound = 1
               break				

    if issuefound == 0:        
        if debug == 1:
            print >>debfile, "NOT FOUND.\n"

    return issuefound 

def WriteXml():
    global totalCount, passedCount, timeval, outfile, errfile, debug, debfile, time_taken, total_time_taken
    timeval = time.strftime("%a %b %d, %Y at %H:%M:%S", time.localtime())
    
    if totalCount > 0:
        passedPercent = "%.2f" % (passedCount/totalCount)*100
    else:
        passedPercent = "0"

    failedcount = totalCount - passedCount
    ohdr = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
    ohdr = ohdr + "<?xml-stylesheet type=\"text/xsl\" href=\"latestresults.xsl\"?>\n"
    ohdr = ohdr+"<testsuite errors=\"0\" failures=\""+str(failedcount)+"\" hostname=\""+platform.node()+"\" name=\"LibraryAnalyser\" tests=\""+str(totalCount)+"\" time=\""+str(round(total_time_taken,3))+"\" timestamp=\""+str(timeval)+"\">\n"
    ohdr = ohdr+"<properties>\n</properties>\n"
    ohdr = ohdr+ostr+"</testsuite>\n"
    print >>outfile, ohdr
    outfile.close()
    
    if passedCount == totalCount:
        print >>errfile, "No differencies.\n"
    
    errfile.close()
    if debug == 1:
        debfile.close()

def CompareResult(tc):              
    global ostr, totalCount, passedCount, debug, debfile, errfile
    if debug == 1:
        print >>debfile, "\n-----------------------\n"
        print >>debfile, "Testcase "+tc+"\n"
        print >>debfile, "-----------------------\n"
    
    # Read expected results (xml report):
    expfilename = "TC"+os.sep+tc+os.sep+"results"+os.sep+"expected_results.xml"
    if debug == 1:
        print >>debfile, "Reading expected results from file: "+expfilename+"\n"
        
    expected = minidom.parse(expfilename)
                            
    # Read actual results (xml report):
    actfilename = "TC"+os.sep+tc+os.sep+"results"+os.sep+"results.xml"
    if not os.path.exists(actfilename):
        failed = 1
        print >>errfile, "--------------------------------------------\n"
        print >>errfile, "TESTCASE: "+tc+"\n\n"
        print >>errfile, "Difference: Actual results file missing:\n"
        print >>errfile, "Filename: "+actfilename+"\n"
        print >>errfile, "--------------------------------------------\n"
        ostr = ostr+"  <testcase classname=\"LibraryAnalyser\" name=\""+tc+"\" time=\""+str(round(time_taken,3))+"\"\">\n"
        ostr = ostr+"    <failure message=\"Failed\" type=\"Failed\">Failed</failure>\n"
        ostr = ostr+"    <expresults>"+os.pardir+os.sep+expfilename+"</expresults>\n"
        ostr = ostr+"    <actresults>"+os.pardir+os.sep+actfilename+"</actresults>\n"
        ostr = ostr+"  </testcase>\n"
        totalCount += 1
        return

    if debug == 1 :
        print >>debfile, "Reading actual results from file: "+actfilename+"\n"

    actual = minidom.parse(actfilename)               
    ostr = ostr + "  <testcase classname=\"LibraryAnalyser\" name=\""+tc+"\" time=\""+str(round(time_taken,3))+"\">\n"
       

    totalCount += 1
    
    failed = 0 
    libfound = 0 

    for expLibrary in expected.getElementsByTagName('library'):   
        libfound = 0 
        if expLibrary.getElementsByTagName('name')[0].firstChild != None:
            expLibraryFilename = expLibrary.getElementsByTagName('name')[0].firstChild.data
        else:
            expLibraryFilename = " "
            
        if expLibrary.getElementsByTagName('comparefilename')[0].firstChild != None:
            expLibraryCompareFilename = expLibrary.getElementsByTagName('comparefilename')[0].firstChild.data
        else:
            expLibraryCompareFilename = " "
            
        # Strip off the paths from the filenames:
        
        if expLibraryFilename != " ":
          tmpIndex = expLibraryFilename.lower().rindex('\\') # index where the Library name begins
          expFile = expLibraryFilename[ tmpIndex+1 : len(expLibraryFilename) ].lower()
        else:
          expFile = " "
       
       
        if expLibraryCompareFilename != " ":
            tmpIndex = expLibraryCompareFilename.lower().rindex('\\') # index of last backslash.
            expCompareFile = expLibraryCompareFilename[ tmpIndex+1 : len(expLibraryCompareFilename) ].lower()
        else:
            expCompareFile = " "

        if debug == 1:
            print >>debfile, "********************************\n"
            print >>debfile, "EXP FILE: "+expFile+" -->\n"

        for actLibrary in actual.getElementsByTagName('library'):
            if actLibrary.getElementsByTagName('name')[0].firstChild != None:
                actLibraryFilename = actLibrary.getElementsByTagName('name')[0].firstChild.data
            else:
                actLibraryFilename = " "
                
            if actLibrary.getElementsByTagName('comparefilename')[0].firstChild != None:
                actLibraryCompareFilename = actLibrary.getElementsByTagName('comparefilename')[0].firstChild.data
            else:
                actLibraryCompareFilename = " "
            
            # Strip off the paths from the filenames:
            
            if actLibraryFilename != " ":
                tmpIndex = actLibraryFilename.lower().rindex(os.sep)  # index of last backslash.
                actFile = actLibraryFilename[ tmpIndex+1 : len(actLibraryFilename) ].lower()
            else:
                actFile = " "
            
            if actLibraryCompareFilename != " ":
                tmpIndex = actLibraryCompareFilename.lower().rindex(os.sep)  # index of last backslash.
                actCompareFile = actLibraryCompareFilename[ tmpIndex+1 : len(actLibraryCompareFilename) ].lower()
            else:
                actCompareFile = " "

            if expFile == actFile:   
                if debug == 1:
                    print >>debfile, "Found.\n"
                    
                for iss1 in expLibrary.getElementsByTagName('issue'):
                    if CheckIssues(iss1, actLibrary.getElementsByTagName('issue')) == 0:
                        failed = 1
                        print >>errfile, "--------------------------------------------\n"
                        print >>errfile, "TESTCASE: "+tc+"\n\n"
                        print >>errfile, "Difference: Issue missing from actual results:\n"
                        print >>errfile, "Filename: "+expFile+"\n"
                        if iss2.getElementsByTagName('typeid').length > 0:
                            print >>errfile, "Typeid: "+iss1.getElementsByTagName('typeid')[0].firstChild.data+"\n"
                        if iss1.getElementsByTagName('funcpos').length > 0:
                            print >>errfile, "Function position: "+iss1.getElementsByTagName('funcpos')[0].firstChild.data+"\n"
                        if iss1.getElementsByTagName('newfuncpos').length > 0:
                            print >>errfile, "New function position: "+iss1.getElementsByTagName('newfuncpos')[0].firstChild.data+"\n"
                        if iss1.getElementsByTagName('funcname').length > 0:
                            print >>errfile, "Function name: "+iss1.getElementsByTagName('funcname')[0].firstChild.data+"\n"
                        if iss1.getElementsByTagName('newfuncname').length > 0:
                            print >>errfile, "New function name: "+iss1.getElementsByTagName('newfuncname')[0].firstChild.data+"\n"
                        if iss1.getElementsByTagName('bc_severity').length > 0:
                            print >>errfile, "BC Severity: "+iss1.getElementsByTagName('bc_severity')[0].firstChild.data+"\n"
                        if iss1.getElementsByTagName('sc_severity').length > 0:
                            print >>errfile, "SC Severity: "+iss1.getElementsByTagName('sc_severity')[0].firstChild.data+"\n"
                        print >>errfile, "--------------------------------------------\n"

                libfound = 1
                break
            

        if libfound == 0:
            if debug == 1:
                print >>debfile, "NOT FOUND.\n"
            failed = 1
            print >>errfile, "--------------------------------------------\n"
            print >>errfile, "TESTCASE: "+tc+"\n\n"
            print >>errfile, "Difference: Library results missing from actual results:\n"
            print >>errfile, "Filename: "+expFile+"\n"
            if expLibrary.getElementsByTagName('typeid').length > 0:
                print >>errfile, "Typeid: "+expLibrary.getElementsByTagName('typeid')[0].firstChild.data+"\n"
            if expLibrary.getElementsByTagName('funcpos').length > 0:
                print >>errfile, "Function position: "+expLibrary.getElementsByTagName('funcpos')[0].firstChild.data+"\n"
            if expLibrary.getElementsByTagName('newfuncpos').length > 0:
                print >>errfile, "New function position: "+expLibrary.getElementsByTagName('newfuncpos')[0].firstChild.data+"\n"
            if expLibrary.getElementsByTagName('funcname').length > 0:
                print >>errfile, "Function name: "+expLibrary.getElementsByTagName('funcname')[0].firstChild.data+"\n"
            if expLibrary.getElementsByTagName('newfuncname').length > 0:
                print >>errfile, "New function name: "+expLibrary.getElementsByTagName('newfuncname')[0].firstChild.data+"\n"
            if expLibrary.getElementsByTagName('bc_severity').length > 0:
                print >>errfile, "BC Severity: "+expLibrary.getElementsByTagName('bc_severity')[0].firstChild.data+"\n"
            if expLibrary.getElementsByTagName('sc_severity').length > 0:
                print >>errfile, "SC Severity: "+expLibrary.getElementsByTagName('sc_severity')[0].firstChild.data+"\n"
            print >>errfile, "--------------------------------------------\n"
    
    for actLibrary in actual.getElementsByTagName('library'):
        if actLibrary.getElementsByTagName('name')[0].firstChild != None:
            actLibraryFilename = actLibrary.getElementsByTagName('name')[0].firstChild.data
        else:
            actLibraryFilename = " "
        
        if actLibrary.getElementsByTagName('comparefilename')[0].firstChild != None:
            actLibraryCompareFilename = actLibrary.getElementsByTagName('comparefilename')[0].firstChild.data
        else:
            actLibraryCompareFilename = " "
        
        # Strip off the paths from the filenames:
        
        if actLibraryFilename != " ":
        	  tmpIndex = actLibraryFilename.lower().rindex(os.sep)  # index of last backslash.
        	  actFile = actLibraryFilename[ tmpIndex+1 : len(actLibraryFilename) ].lower()
        else:
            actFile = " "
        
        if actLibraryCompareFilename != " ":
        	 tmpIndex = actLibraryCompareFilename.lower().rindex(os.sep)  # index of last backslash.
        	 actCompareFile = actLibraryCompareFilename[ tmpIndex+1 : len(actLibraryCompareFilename) ].lower()
        else:
           actCompareFile = " "
        
        if debug == 1:
            print >>debfile, "********************************\n"
            print >>debfile, "ACT FILE: "+actFile+" -->\n"

        libfound = 0 
        for expLibrary in expected.getElementsByTagName('library'):
           if expLibrary.getElementsByTagName('name')[0].firstChild != None:
              expLibraryFilename = expLibrary.getElementsByTagName('name')[0].firstChild.data
           else:
              expLibraryFilename = " "
           
           if expLibrary.getElementsByTagName('comparefilename')[0].firstChild != None:
               expLibraryCompareFilename = expLibrary.getElementsByTagName('comparefilename')[0].firstChild.data
           else:
               expLibraryCompareFilename = " "
            
           # Strip off the paths from the filenames:
           if expLibraryFilename != " ":
               tmpIndex = expLibraryFilename.lower().rindex('\\') # index where the header name begins
               expFile = expLibraryFilename[ tmpIndex+1 : len(expLibraryFilename) ].lower()
           else:
               expFile = " "
       
           if expLibraryCompareFilename != " ":
               tmpIndex = expLibraryCompareFilename.lower().rindex('\\') # index of last backslash.
               expCompareFile = expLibraryCompareFilename[ tmpIndex+1 : len(expLibraryCompareFilename) ].lower()
           else:
               expCompareFile = " "
            
           if actFile == expFile and actCompareFile == expCompareFile:   
               if debug == 1:
                              print >>debfile, "Found.\n"
                   
               for iss2 in actLibrary.getElementsByTagName('issue'):
                   if CheckIssues(iss2, expLibrary.getElementsByTagName('issue')) == 0:
                       failed = 1
                       print >>errfile, "--------------------------------------------\n"
                       print >>errfile, "TESTCASE: "+tc+"\n\n"
                       print >>errfile, "Difference: Issue missing from expected results:\n"
                       print >>errfile, "Filename: "+expFile+"\n"
                       if iss2.getElementsByTagName('typeid').length > 0:
                           print >>errfile, "Typeid: "+iss2.getElementsByTagName('typeid')[0].firstChild.data+"\n"
                       if iss2.getElementsByTagName('funcpos').length > 0:
                           print >>errfile, "Function position: "+iss2.getElementsByTagName('funcpos')[0].firstChild.data+"\n"
                       if iss2.getElementsByTagName('newfuncpos').length > 0:
                           print >>errfile, "New function position: "+iss2.getElementsByTagName('newfuncpos')[0].firstChild.data+"\n"
                       if iss2.getElementsByTagName('funcname').length > 0:
                           print >>errfile, "Function name: "+iss2.getElementsByTagName('funcname')[0].firstChild.data+"\n"
                       if iss2.getElementsByTagName('newfuncname').length > 0:
                           print >>errfile, "New function name: "+iss2.getElementsByTagName('newfuncname')[0].firstChild.data+"\n"
                       if iss2.getElementsByTagName('bc_severity').length > 0:
                           print >>errfile, "BC Severity: "+iss2.getElementsByTagName('bc_severity')[0].firstChild.data+"\n"
                       if iss2.getElementsByTagName('sc_severity').length > 0:
                           print >>errfile, "SC Severity: "+iss2.getElementsByTagName('sc_severity')[0].firstChild.data+"\n"
                       print >>errfile, "--------------------------------------------\n"
                       
               libfound = 1
               break
            
        if libfound == 0:
            if debug == 1:
                print >>debfile, "NOT FOUND.\n"
            
            failed = 1
            print >>errfile, "--------------------------------------------\n"
            print >>errfile, "TESTCASE: "+tc+"\n\n"
            print >>errfile, "Difference: Library results missing from expected results:\n"
            print >>errfile, "Filename: "+expFile+"\n"
            if actLibrary.getElementsByTagName('typeid').length > 0:
                print >>errfile, "Typeid: "+actLibrary.getElementsByTagName('typeid')[0].firstChild.data+"\n"
            if actLibrary.getElementsByTagName('funcpos').length > 0:
                print >>errfile, "Function position: "+actLibrary.getElementsByTagName('funcpos')[0].firstChild.data+"\n"
            if actLibrary.getElementsByTagName('newfuncpos').length > 0:
                print >>errfile, "New function position: "+actLibrary.getElementsByTagName('newfuncpos')[0].firstChild.data+"\n"
            if actLibrary.getElementsByTagName('funcname').length > 0:
                print >>errfile, "Function name: "+actLibrary.getElementsByTagName('funcname')[0].firstChild.data+"\n"
            if actLibrary.getElementsByTagName('newfuncname').length > 0:
                print >>errfile, "New function name: "+actLibrary.getElementsByTagName('newfuncname')[0].firstChild.data+"\n"
            if actLibrary.getElementsByTagName('bc_severity').length > 0:
                print >>errfile, "BC Severity: "+actLibrary.getElementsByTagName('bc_severity')[0].firstChild.data+"\n"
            if actLibrary.getElementsByTagName('sc_severity').length > 0:
                print >>errfile, "SC Severity: "+actLibrary.getElementsByTagName('sc_severity')[0].firstChild.data+"\n"
            print >>errfile, "--------------------------------------------\n"
        
    if failed == 0:
        passedCount += 1
        ostr = ostr+"    <expresults>"+os.pardir+os.sep+expfilename+"</expresults>\n"
        ostr = ostr+"    <actresults>"+os.pardir+os.sep+actfilename+"</actresults>\n"
        ostr = ostr+"  </testcase>\n"
    else:
        ostr = ostr+"    <failure message=\"Failed\" type=\"Failed\">Failed</failure>\n"
        ostr = ostr+"    <expresults>"+os.pardir+os.sep+expfilename+"</expresults>\n"
        ostr = ostr+"    <actresults>"+os.pardir+os.sep+actfilename+"</actresults>\n"
        ostr = ostr+"  </testcase>\n"


if len(sys.argv) == 1:
    Usage()
if sys.argv[1] in usage:
    Usage()

if sys.argv[1] == "-build":
    LABuild()
    
ostr = ""
if debug == 1:
    debfile = open("log/latestdebug.txt","w") # Debug information is printed to this file.

passedCount = 0 
totalCount = 0 
time_taken = 0
total_time_taken = 0

outfile = open("results/"+ sys.argv[1],"w") # Test execution results are printed here.
errfile = open("log/latestdiff.txt","w")  # Differences of not passed test cases are printed here.
if len(sys.argv) == 2:
    RunAll()
else:
    RunTC()
    
    