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

def HABuild():
    if len(sys.argv) != 3:
        Usage()
    cmd = "python " + SCRIPTS_DIR + "hatestbuild.py " + sys.argv[2].upper()
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
    p = re.compile('^HATC')
    for tc in cases:
        tc = tc.strip().upper()
        if p.match(tc):
            print "\n" + tc
            cmd = "python " + SCRIPTS_DIR + "hatestrun.py " + tc
            stime = time.clock()
            os.system(cmd)
            etime = time.clock()
            UpdateTimeTaken(etime-stime)
            CompareResult(tc)
    WriteXml()
    if os.name != "posix":
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
            cmd = "python " + SCRIPTS_DIR + "hatestrun.py " + tc
            stime = time.clock()
            os.system(cmd)
            etime = time.clock()
            UpdateTimeTaken(etime-stime)
            CompareResult(tc)
    WriteXml()
    if os.name != "posix":
        OpenResults()
    return


def CheckIssues(issue1, issueArr):
    issuefound = 0

    if debug == 1:
        print >>debfile, "-------------------------------\n"
        if issue1.getElementsByTagName('cause')[0].firstChild != None:
            print >>debfile, "ISSUE: "+ issue1.getElementsByTagName('cause')[0].firstChild.data +" --> "
        else:
            print >>debfile, "ISSUE:  --> "
        
    for issue2 in issueArr:
        if  issue1.getElementsByTagName('typestring')[0].firstChild.data == issue2.getElementsByTagName('typestring')[0].firstChild.data and \
            (( issue1.getElementsByTagName('cause')[0].firstChild == None and issue2.getElementsByTagName('cause')[0].firstChild == None ) or \
            (issue1.getElementsByTagName('cause')[0].firstChild != None and \
            issue1.getElementsByTagName('cause')[0].firstChild.data == issue2.getElementsByTagName('cause')[0].firstChild.data )) and \
            issue1.getElementsByTagName('identitydescription')[0].firstChild.data == issue2.getElementsByTagName('identitydescription')[0].firstChild.data and \
            issue1.getElementsByTagName('severity')[0].getElementsByTagName('typestring')[0].firstChild.data == issue2.getElementsByTagName('severity')[0].getElementsByTagName('typestring')[0].firstChild.data and \
            issue1.getElementsByTagName('severity')[0].getElementsByTagName('typeid')[0].firstChild.data == issue2.getElementsByTagName('severity')[0].getElementsByTagName('typeid')[0].firstChild.data and \
            issue1.getElementsByTagName('scseverity')[0].getElementsByTagName('typestring')[0].firstChild.data == issue2.getElementsByTagName('scseverity')[0].getElementsByTagName('typestring')[0].firstChild.data and \
            issue1.getElementsByTagName('scseverity')[0].getElementsByTagName('typeid')[0].firstChild.data == issue2.getElementsByTagName('scseverity')[0].getElementsByTagName('typeid')[0].firstChild.data and \
            issue1.getElementsByTagName('linenumber')[0].firstChild.data == issue2.getElementsByTagName('linenumber')[0].firstChild.data :
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
    ohdr = ohdr + "<?xml-stylesheet type=\"text/xsl\" href=\"hatestresults.xsl\"?>\n"
    ohdr = ohdr+"<testsuite errors=\"0\" failures=\""+str(failedcount)+"\" hostname=\""+platform.node()+"\" name=\"HeaderAnalyser\" tests=\""+str(totalCount)+"\" time=\""+str(round(total_time_taken,3))+"\" timestamp=\""+str(timeval)+"\">\n"
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
    expfilename = "TC"+os.sep+tc+os.sep+"results"+os.sep+tc+"_expected_results.xml"
    if debug == 1:
        print >>debfile, "Reading expected results from file: "+expfilename+"\n"
        
    expected = minidom.parse(expfilename)
                            
    # Read actual results (xml report):
    actfilename = "TC"+os.sep+tc+os.sep+"results"+os.sep+tc+"_results.xml"
    if not os.path.exists(actfilename):
        print "os.path.exists(actfilename)"
        failed = 1
        print >>errfile, "--------------------------------------------\n"
        print >>errfile, "TESTCASE: "+tc+"\n\n"
        print >>errfile, "Difference: Actual results file missing:\n"
        print >>errfile, "Filename: "+actfilename+"\n"
        print >>errfile, "--------------------------------------------\n"
        ostr = ostr+"  <testcase classname=\"HeaderAnalyser\" name=\""+tc+"\" time=\""+str(round(time_taken,3))+"\"\">\n"
        ostr = ostr+"    <failure message=\"Failed\" type=\"Failed\">Failed</failure>\n"
        ostr = ostr+"    <expresults>"+os.pardir+os.sep+expfilename+"</expresults>\n"
        ostr = ostr+"    <actresults>"+os.pardir+os.sep+actfilename+"</actresults>\n"
        ostr = ostr+"  </testcase>\n"
        totalCount += 1
        return

    if debug == 1 :
        print >>debfile, "Reading actual results from file: "+actfilename+"\n"

    actual = minidom.parse(actfilename)               
    ostr = ostr + "  <testcase classname=\"HeaderAnalyser\" name=\""+tc+"\" time=\""+str(round(time_taken,3))+"\">\n"
       

    totalCount += 1
    
    failed = 0 
    headerfound = 0 

    for expHeader in expected.getElementsByTagName('headerfile'):   
        headerfound = 0 
        expHeaderFilename = expHeader.getElementsByTagName('filename')[0].firstChild.data
        expHeaderCompareFilename = expHeader.getElementsByTagName('comparefilename')[0].firstChild.data
            
        # Strip off the paths from the filenames:
        
        tmpIndex = expHeaderFilename.lower().rindex('\\') # index where the header name begins
        expFile = expHeaderFilename[ tmpIndex+1 : len(expHeaderFilename) ].lower()
       
       
        tmpIndex = expHeaderCompareFilename.lower().rindex('\\') # index of last backslash.
        expCompareFile = expHeaderCompareFilename[ tmpIndex+1 : len(expHeaderCompareFilename) ].lower()

        if debug == 1:
            print >>debfile, "********************************\n"
            print >>debfile, "EXP FILE: "+expFile+" -->\n"

        for actHeader in actual.getElementsByTagName('headerfile'):
            actHeaderFilename = actHeader.getElementsByTagName('filename')[0].firstChild.data
            actHeaderCompareFilename = actHeader.getElementsByTagName('comparefilename')[0].firstChild.data
            
            # Strip off the paths from the filenames:
            
            tmpIndex = actHeaderFilename.lower().rindex(os.sep)  # index of last backslash.
            actFile = actHeaderFilename[ tmpIndex+1 : len(actHeaderFilename) ].lower()
            
            tmpIndex = actHeaderCompareFilename.lower().rindex(os.sep)  # index of last backslash.
            actCompareFile = actHeaderCompareFilename[ tmpIndex+1 : len(actHeaderCompareFilename) ].lower()

            if expFile == actFile and expCompareFile == actCompareFile:   
                if debug == 1:
                    print >>debfile, "Found.\n"
                    
                for iss1 in expHeader.getElementsByTagName('issue'):
                    if CheckIssues(iss1, actHeader.getElementsByTagName('issue')) == 0:
                        failed = 1
                        print >>errfile, "--------------------------------------------\n"
                        print >>errfile, "TESTCASE: "+tc+"\n\n"
                        print >>errfile, "Difference: Issue missing from actual results:\n"
                        print >>errfile, "Filename: "+expFile+"\n"
                        if iss1.getElementsByTagName('cause')[0].firstChild != None:
                            print >>errfile, "Issue: "+iss1.getElementsByTagName('cause')[0].firstChild.data+"\n"
                        else:
                            print >>errfile, "Issue: \n"
                        print >>errfile, "Description: "+iss1.getElementsByTagName('identitydescription')[0].firstChild.data +" "+ iss1.getElementsByTagName('typestring')[0].firstChild.data+" \n"                     
                        print >>errfile, "--------------------------------------------\n"

                headerfound = 1
                break
            

        if headerfound == 0:
            if debug == 1:
                print >>debfile, "NOT FOUND.\n"
            failed = 1
            print >>errfile, "--------------------------------------------\n"
            print >>errfile, "TESTCASE: "+tc+"\n\n"
            print >>errfile, "Difference: Header results missing from actual results:\n"
            print >>errfile, "Filename: "+expFile+"\n"
            if iss1.getElementsByTagName('cause')[0].firstChild != None:
                print >>errfile, "Issue: "+iss1.getElementsByTagName('cause')[0].firstChild.data+"\n"
            else:
                print >>errfile, "Issue: \n"
            print >>errfile, "Description: "+iss1.getElementsByTagName('identitydescription')[0].firstChild.data +" "+ iss1.getElementsByTagName('typestring')[0].firstChild.data+" \n"                     
            print >>errfile, "--------------------------------------------\n"

    
    for actHeader in actual.getElementsByTagName('headerfile'):
        actHeaderFilename = actHeader.getElementsByTagName('filename')[0].firstChild.data
        actHeaderCompareFilename = actHeader.getElementsByTagName('comparefilename')[0].firstChild.data
        
        # Strip off the paths from the filenames:
        
        tmpIndex = actHeaderFilename.lower().rindex(os.sep)  # index of last backslash.
        actFile = actHeaderFilename[ tmpIndex+1 : len(actHeaderFilename) ].lower()
        
        tmpIndex = actHeaderCompareFilename.lower().rindex(os.sep)  # index of last backslash.
        actCompareFile = actHeaderCompareFilename[ tmpIndex+1 : len(actHeaderCompareFilename) ].lower()
        
        if debug == 1:
            print >>debfile, "********************************\n"
            print >>debfile, "ACT FILE: "+actFile+" -->\n"

        headerfound = 0 
        for expHeader in expected.getElementsByTagName('headerfile'):
           expHeaderFilename = expHeader.getElementsByTagName('filename')[0].firstChild.data
           expHeaderCompareFilename = expHeader.getElementsByTagName('comparefilename')[0].firstChild.data
            
           # Strip off the paths from the filenames:
           tmpIndex = expHeaderFilename.lower().rindex('\\') # index where the header name begins
           expFile = expHeaderFilename[ tmpIndex+1 : len(expHeaderFilename) ].lower()
       
           tmpIndex = expHeaderCompareFilename.lower().rindex('\\') # index of last backslash.
           expCompareFile = expHeaderCompareFilename[ tmpIndex+1 : len(expHeaderCompareFilename) ].lower()
            
           if actFile == expFile and actCompareFile == expCompareFile:   
               if debug == 1:
                   print >>debfile, "Found.\n"
                   
               for iss2 in actHeader.getElementsByTagName('issue'):
                   if CheckIssues(iss2, expHeader.getElementsByTagName('issue')) == 0:
                       failed = 1
                       print >>errfile, "--------------------------------------------\n"
                       print >>errfile, "TESTCASE: "+tc+"\n\n"
                       print >>errfile, "Difference: Issue missing from expected results:\n"
                       print >>errfile, "Filename: "+actFile+"\n"
                       if iss1.getElementsByTagName('cause')[0].firstChild != None:
                           print >>errfile, "Issue: "+iss1.getElementsByTagName('cause')[0].firstChild.data+"\n"
                       else:
                           print >>errfile, "Issue: \n"
                       print >>errfile, "Description: "+iss1.getElementsByTagName('identitydescription')[0].firstChild.data +" "+ iss1.getElementsByTagName('typestring')[0].firstChild.data+" \n"
                       print >>errfile, "--------------------------------------------\n"
                       
               headerfound = 1
               break
            
        if headerfound == 0:
            if debug == 1:
                print >>debfile, "NOT FOUND.\n"
            
            failed = 1
            print >>errfile, "--------------------------------------------\n"
            print >>errfile, "TESTCASE: "+tc+"\n\n"
            print >>errfile, "Difference: Header results missing from expected results:\n"
            print >>errfile, "Filename: "+actFile+"\n"
            if iss1.getElementsByTagName('cause')[0].firstChild != None:
                print >>errfile, "Issue: "+iss1.getElementsByTagName('cause')[0].firstChild.data+"\n"
            else:
                print >>errfile, "Issue: \n"
            print >>errfile, "Description: "+iss1.getElementsByTagName('identitydescription')[0].firstChild.data +" "+ iss1.getElementsByTagName('typestring')[0].firstChild.data+" \n"
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
    HABuild()
    
ostr = ""
if debug == 1:
    debfile = open("log/hatestdebug.txt","w") # Debug information is printed to this file.

passedCount = 0 
totalCount = 0 
time_taken = 0
total_time_taken = 0

outfile = open("results/"+ sys.argv[1],"w") # Test execution results are printed here.
errfile = open("log/hatestdiff.txt","w")  # Differences of not passed test cases are printed here.

if len(sys.argv) == 2:
    RunAll()
else:
    RunTC()

