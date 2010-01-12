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
import shutil
import filecmp
import re
import time
import decimal
import platform

def UpdateTimeTaken(tm):
    global time_taken, total_time_taken
    time_taken = tm
    total_time_taken += tm

def CompareXml(file1,file2):
    f1 = open(file1)
    f2 = open(file2)
    line1=f1.readlines()
    line2=f2.readlines()
    f1.close()
    f2.close()
    i=0
    j=0
    temp = True
    
    #while the smaller file has some lines
    while j < len(line2) and i < len(line1): 
        #file1: if empty line, move to next line 	                      
        if line1[i].strip() == "":
            i = i + 1
            continue
        #file2: if empty line, move to next line 
        if line2[j].strip()  == "":
            j = j + 1
            continue
        #if non-empty lines in file1 and file2 are not equal return false
        if(line1[i].strip()!=line2[j].strip()):
            temp = False
            break
        i = i + 1
        j = j + 1
     
    # if lines left in file1, check if they are empty   
    while i < len(line1):  
        if line1[i].strip()  != "":
            temp = False
            break
        i = i + 1
        
    # if lines left in file2, check if they are empty     
    while j < len(line2):
        if line2[j].strip()  != "":
            temp = False
            break
        j = j + 1  
                 
    return temp


TC_DIR = os.getcwd() + os.sep + "TC" + os.sep
BC_BIN = os.pardir + os.sep + "bin" + os.sep
(CUR_PATH, tmp) = os.path.splitdrive(os.getcwd())
cases = []

bbcresults = os.pardir + os.sep + os.pardir + os.sep + "CheckBC" + os.sep + "reports" + os.sep + "BBCResults.xsl"

if len(sys.argv) == 1:
    print "Usage: " + sys.argv[0] + " <outputfile> [<testcasefile>]"
    sys.exit()
    
outputFile = os.getcwd() + os.sep + "results" + os.sep + sys.argv[1]

if len(sys.argv) == 2:
    cases = os.listdir(TC_DIR)
else:
    file = open( sys.argv[2] )
    for line in file:
        cases.append(line.rstrip('\n'))
    file.close()

if not os.path.exists( bbcresults ):
    print "Warning: Missing File: " + bbcresults + " Style sheet does not exist"
    

timeval = time.strftime("%a %b %d, %Y at %H:%M:%S", time.localtime())

ostr = ""

passedCount = 0 
totalCount = 0 
time_taken = 0
total_time_taken = 0

outfile=open(outputFile,"w")
outfile.write("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n")
outfile.write("<?xml-stylesheet type=\"text/xsl\" href=\"bcftestresults.xsl\"?>\n")

for tc in cases:
    tc = tc.upper()
    comment = TC_DIR + tc + os.sep + "comment.txt"
    if os.path.exists( comment ):
        file = open( comment )
        print "\n------------------------------------------"
        for line in file:
            print line.rstrip('\n')
        print "-------------------"
        file.close()
        
    config = TC_DIR + tc + os.sep + tc + "_conf.txt"
    if os.path.exists( config ):
        totalCount = totalCount + 1
        if os.path.exists( bbcresults ):
            tcbbcresults = TC_DIR + tc + os.sep + "data" + os.sep + "BBCResults.xsl"
            shutil.copyfile( bbcresults,tcbbcresults )
                
        file = open( config )
        report = (file.readline()).rstrip('\n\r ')
        if "BCFTC002" == tc:
            report = (CUR_PATH + report).rstrip('\n\r ')
        issue = (file.readline()).rstrip('\n\r ')
        output = (file.readline()).rstrip('\n\r ')
        file.close()
        
        (path, tmp) = os.path.split(issue)
        expOutFile = path + os.sep + tc + "_expected_results.xml"
        if output:
            inputFile = report
            actOutFile = output
            if os.path.exists( actOutFile ):
              os.remove(actOutFile)
        else:
            inputFile = path + os.sep + tc + "_actual_results.xml" 
            shutil.copyfile(report,inputFile)
            actOutFile = inputFile
            
        consolefile = path + os.sep + tc + "_actual_console.txt"
        if os.path.exists( consolefile ):
            os.remove(consolefile)
            
        cmd = BC_BIN + "bcfilter " + inputFile + " " + issue + " " + output + " >> " + consolefile
        print "....execution started...."
        stime = time.clock()
        os.system( cmd )
        etime = time.clock()
        UpdateTimeTaken(etime-stime)
        print "....execution completed...."
              	   
        passed = False
        if tc == "BCFTC008":
            p = re.compile('\d\d\d?% complete')
            file = open( consolefile )
            lines = file.readlines()
            file.close()
            for i in xrange(2,len(lines)):
                if p.match(lines[i].rstrip('\n')):
                    passed = True
                else:
                    passed = False
                    break   
            expOutFile = path + os.sep + tc + "_expected_console.txt"
            actOutFile = consolefile
             
        elif not os.path.exists(actOutFile):
            passed = False
        else:
            passed = CompareXml( expOutFile, actOutFile)
        
        ostr = ostr + "  <testcase classname=\"BCFilter\" name=\""+tc+"\" time=\""+str(round(time_taken,3))+"\">\n"
                   	
        if passed:
            passedCount = passedCount + 1 
            print "....Result : PASSED...."
        else:
            ostr = ostr+"    <failure message=\"Failed\" type=\"Failed\">Failed</failure>\n"
            print "....Result : FAILED...."
            
        ostr = ostr+"    <expresults>"+os.pardir+os.sep+expOutFile+"</expresults>\n"
        ostr = ostr+"    <actresults>"+os.pardir+os.sep+actOutFile+"</actresults>\n"
        ostr = ostr+"  </testcase>\n"
        
        if tc != "BCFTC008":
            os.remove(consolefile)	
        
failedcount = totalCount - passedCount
outfile.write("<testsuite errors=\"0\" failures=\""+str(failedcount)+"\" hostname=\""+platform.node()+"\" name=\"BCFilter\" tests=\""+str(totalCount)+"\" time=\""+str(round(total_time_taken,3))+"\" timestamp=\""+str(timeval)+"\">\n")
outfile.write("<properties>\n</properties>\n")
outfile.write(ostr)
outfile.write("</testsuite>\n")
outfile.close()
print "\n------------------------------------------"

if os.path.exists( outputFile ) and os.name == 'nt':
    cmd = "start " + outputFile
    os.system(cmd)        
       