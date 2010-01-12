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

import subprocess
import os
import re
import sys
import shutil
from xml.dom import minidom


if os.name == 'nt':
    path = os.path.dirname(sys.argv[0])
else:
    path = os.getcwd()

TC_DIR = path
CHECKBC = "python " + TC_DIR + os.sep + os.pardir + os.sep + "CheckBC.py"
DEFAULT_TEMP = TC_DIR + os.sep + os.pardir + os.sep + "temp"

#will create a seperate process for invoking checkbc with given parameters
def runTest(args):
    return subprocess.call(CHECKBC + args, shell=True)

def comment(list, updatepairs):
    ip = open( TC_DIR + os.sep + 'config_template', 'r')
    op = open( TC_DIR + os.sep + 'temp' + os.sep + 'config', 'w')
    for line in ip:
        if line[0] == '#':
            continue
        line = line.strip(' \t\n\r')
        pair = line.split('=')
        if updatepairs.has_key(pair[0]):
            line = pair[0] + '=' + updatepairs[pair[0]]
        if pair[0] not in list:
            op.write(line)
            op.write('\n')
    ip.close()
    op.close()

def failUnless(res, exp_res):
	if res == exp_res:
		return True
	else:
		return False	
		
def checklists(list1,list2):
    for val in list1:
        if not val in list2:
            return False
    return True

def checkreports(tag):
    expectedreport=TC_DIR + os.sep + 'testdata' + os.sep + 'expected_results' + os.sep + tag + '.xml'
    actualreport=TC_DIR + os.sep + 'temp' + os.sep + 'results' + os.sep + tag + '.xml'
    if not os.path.exists(actualreport):
    	return False
    
    expdoc=minidom.parse(expectedreport)
    actdoc=minidom.parse(actualreport)
    expparent=expdoc.documentElement
    actparent=actdoc.documentElement
    
    expparms=expparent.getElementsByTagName("parm")
    actparms=actparent.getElementsByTagName("parm")
    
    expparmslen=expparms.length
    actparmslen=actparms.length

    if expparmslen!=actparmslen:
    	return False
    
    for expparm in expparms:
    	exparg=expparm.getElementsByTagName("pname")[0].firstChild.nodeValue
    	expargval=""
    	if expparm.getElementsByTagName("pvalue")[0].firstChild:
    		expargval=expparm.getElementsByTagName("pvalue")[0].firstChild.nodeValue
    	
    	found=False
    	for actparm in actparms:
    		actarg=actparm.getElementsByTagName("pname")[0].firstChild.nodeValue
    		actargval=""
    		if actparm.getElementsByTagName("pvalue")[0].firstChild:
    			actargval=actparm.getElementsByTagName("pvalue")[0].firstChild.nodeValue
    		if exparg==actarg:
    			if exparg in "baselineversion currentversion bundlesize recursive replace excludedirs toolchain".split():
    				if expargval == actargval:
    					found=True
    				break
    					   	
    			if exparg in "baseplatformdata currentplatformdata".split():
    				expargval=expargval[ expargval.index(os.sep+'data') : len(expargval) ]
    				actargval=actargval[ actargval.index(os.sep+'data') : len(actargval) ]
    				if expargval == actargval:
    					found=True
    				break
    				
    			if exparg == 'cfilt':
    				if expargval.rfind(os.sep+'bin') != -1:
    					expargval=expargval[ expargval.index(os.sep+'bin') : len(expargval) ]
    					actargval=actargval[ actargval.index(os.sep+'bin') : len(actargval) ]
    				if expargval == actargval:
    					found=True
    				break
    						
    			if exparg in "forcebaseinclude forcecurrentinclude".split():			
    				list1=expargval.split(';')
    				list2=actargval.split(';')
    				if len(list1) == len(list2):
    				    for i in range(0,len(list1)): 
    				        list1[i]=list1[i][ list1[i].index(os.sep+'bin') : len(list1[i]) ]
    				        list2[i]=list2[i][ list2[i].index(os.sep+'bin') : len(list2[i]) ]        	
    				    found=checklists(list1,list2)
    				break
    				
    			if exparg in "baselinedir currentdir baselinelibdir currentlibdir baselinedlldir currentdlldir baseplatformheaders currentplatformheaders reportfile".split():
    				list1=expargval.split(';')
    				list2=actargval.split(';')
    				if len(list1) == len(list2):
    				    for i in range(0,len(list1)):
    				    	if list1[i].find(os.sep+'tsrc') != -1:
    				    		list1[i]=list1[i][ list1[i].index(os.sep+'tsrc') : len(list1[i]) ]
    				    		list2[i]=list2[i][ list2[i].index(os.sep+'tsrc') : len(list2[i]) ]
    				    	else:
    				    		list1[i]=list1[i][ list1[i].index(os.sep+'data') : len(list1[i]) ]
    				    		list2[i]=list2[i][ list2[i].index(os.sep+'data') : len(list2[i]) ]
    				    found=checklists(list1,list2)
    				break
					
    			if exparg in "baselinedlldir currentdlldir reportfile".split():
    				list1=expargval.split(';')
    				list2=actargval.split(';')
    				if len(list1) == len(list2):
    					  if actargval.find('.xml') != -1 and  expargval.find('.xml') != -1:
    					  	found = True
    					  	break

    					  for i in range(0,len(list1)):
    					    list1[i]=list1[i][ list1[i].index(os.sep+'tsrc') : len(list1[i]) ]
    					    list2[i]=list2[i][ list2[i].index(os.sep+'tsrc') : len(list2[i]) ]
    					  found=checklists(list1,list2)
    				    
    				break
    				
    			if exparg == 'set':
    				if expparent.getElementsByTagName("haversion").length > 0:
    					if expargval == actargval:
    						found=True
    					break	
    				if expparent.getElementsByTagName("laversion").length > 0:
    					if expargval.rfind(os.sep) != -1:
    						expargval=expargval[ expargval.rindex(os.sep) : len(expargval) ]
    						actargval=actargval[ actargval.rindex(os.sep) : len(actargval) ]
    					if expargval == actargval:
    						found=True
    					break
    						
    			if actarg == 'commandfile':
    				if expargval.rfind(os.sep) != -1:
    					expargval=expargval[ expargval.rindex(os.sep) : len(expargval) ]
    					actargval=actargval[ actargval.rindex(os.sep) : len(actargval) ]
    					if expargval == actargval:
    						found=True
    					break
    						
    			if exparg in "tools temp".split():
    				found=True
    				break
    	
    	if not found:
    		return False
  		
    return True
    			
#print checkreports('headers_test_17')		
#print child  		
    

#Test without passing any parameters, procees should return 1 on exit
def test_00():
    print "Executing test: test_00"
    str = 'FAILED'
    args = ""
    res = repr(runTest(args))
    if failUnless(res, '3'):
        str = 'PASSED'
    return tuple(['3', res, str])

#Test passing help parameters, procees should return 1 on exit    
def test_01():
    print "Executing test: test_01"
    str = 'FAILED'
    args = " -h"
    res = repr(runTest(args))
    if failUnless(res, '8'):
        str = 'PASSED'
    return tuple(['8', res, str])        

#Test tool version parameter, process should return 1 on exit
def test_02():
    print "Executing test: test_02"
    str = 'FAILED'
    v = re.compile('[1-9]+[.][0-9]+[.][0-9]+[ ][-][ ]([12]?[0-9]+|30|31)(nd|st|th|rd)[ ](January|February|March|April|May|June|July|August|September|October|November|December)[ ](2008|2009|2010)')
    res = ''
    args = " -v > test_02.txt"
    runTest(args)
    f = open('test_02.txt')
    for line in f:
        res = line
        if re.match( v, line):
            str = 'PASSED'
        print line    
    f.close()
    os.remove('test_02.txt')
    return tuple(['format : xx.yy.zz - dd month yyyy', res, str])

#Test data version parameter, process should return 1 on exit
def test_03():
    print "Executing test: test_03"
    str = 'FAILED'
    res = ''
    args = " -dv > test_03.txt"
    runTest(args)
    f = open('test_03.txt')
    for line in f:
        try:
            res = int(line)
        except ValueError:            
            pass
        else:
            if ( 0 < res <= 9 ):
                str = 'PASSED'            
    f.close()
    os.remove('test_03.txt')
    return tuple(['integer value 0-9', repr(res), str])

#Test wrong parameters, process should return 3 on exit        
def test_04():
    print "Executing test: test_04"
    str = 'FAILED'
    args = " report.xml temp/config -j -d file -b"
    res = repr(runTest(args))
    if failUnless(res, '3'):
        str = 'PASSED'
    return tuple(['3', res, str])

#Test passing both header&libary analysis input
def test_05():
    print "Executing test: test_05"
    str = 'FAILED'
    cmt = ['BASELINE_HEADERS', 'CURRENT_HEADERS', 'EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER' ]
    comment(cmt, {})
    args = " temp/config -ha -la -f test_05"
    res = repr(runTest(args))
    if failUnless(res, '0'):
    	if checkreports('headers_test_05') and checkreports('libraries_test_05'):
    	    str = 'PASSED'
    return tuple(['0', res, str])

#Test execution for all headers only        
def test_06():
    print "Executing test: test_06"
    str = 'FAILED'
    cmt = ['REPLACE_HEADERS' ]
    comment(cmt, {'EXCLUDE_DIR_HEADERS':''})
    args = " temp/config -ha test_06"
    res = repr(runTest(args))
    if failUnless(res, '0'):
        if checkreports('headers_test_06'):
            str = 'PASSED'
    return tuple(['0', res, str])

#Test executiion for all libraries only      
def test_07():
    print "Executing test: test_07"
    str = 'FAILED'
    cmt = ['EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER' ]
    comment(cmt, {})
    args = " temp/config -la test_07"
    res = repr(runTest(args))
    if failUnless(res, '0'):
        if checkreports('libraries_test_07'):
            str = 'PASSED'
    return tuple(['0', res, str])

#Test execution for all headers & filter        
def test_08():
    print "Executing test: test_08"
    str = 'FAILED'
    cmt = ['EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER', 'REPORT_FILE_LIBRARIES', 'FILTER_FILE_LIBRARIES' ]
    comment(cmt, {})
    args = " temp/config -ha -f test_08"
    res = repr(runTest(args))
    if failUnless(res, '0'):
        if checkreports('headers_test_08'):
            str = 'PASSED'
    return tuple(['0', res, str])

#Test execution for all libraries & filter        
def test_09():
    print "Executing test: test_09"
    str = 'FAILED'
    cmt = ['EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS', 'REPORT_FILE_HEADERS', 'FILTER_FILE_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER' ]
    comment(cmt, {})
    args = " temp/config -la -f test_09"
    res = repr(runTest(args))
    if failUnless(res, '0'):    
        if checkreports('libraries_test_09'):
            str = 'PASSED'
    return tuple(['0', res, str])

#Test execution for only filtering        
def test_10():
    print "Executing test: test_10"
    str = 'FAILED'
    shutil.copy(os.getcwd()+'/testdata/SAReport_test_10.xml',os.getcwd()+'/testdata/SAReport_test_10.xml.bak')
    cmt = ['EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS', 'REPORT_FILE_HEADERS', 'FILTER_FILE_HEADERS', 'REPORT_FILE_LIBRARIES', 'FILTER_FILE_LIBRARIES' ]
    comment(cmt, {})
    args = " temp/config -f test_10"
    res = repr(runTest(args))
    shutil.move(os.getcwd()+'/testdata/SAReport_test_10.xml.bak',os.getcwd()+'/testdata/SAReport_test_10.xml')
    if failUnless(res, '0'):
        str = 'PASSED'
    return tuple(['0', res, str])

#Test execution for multiple header analysis followed by filtering        
def test_11():
    print "Executing test: test_11"
    str = 'FAILED'
    cmt = ['EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER', 'REPORT_FILE_LIBRARIES', 'FILTER_FILE_LIBRARIES' ]
    comment(cmt, {})
    args = " temp/config -hm tsrc/testdata/headers.txt -f test_11"
    res = repr(runTest(args))
    if failUnless(res, '0'):
    	if checkreports('headers_test_11'):
    	    str = 'PASSED'
    return tuple(['0', res, str])

#Test execution for multiple library analysis followed by filtering        
def test_12():
    print "Executing test: test_12"
    str = 'FAILED'
    cmt = ['EXCLUDE_DIR_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER', 'REPORT_FILE_HEADERS', 'FILTER_FILE_HEADERS' ]
    comment(cmt, {})
    args = " temp/config -lm tsrc/testdata/libraries.txt -f test_12"
    res = repr(runTest(args))
    if failUnless(res, '0'):
        if checkreports('libraries_test_12'):
            str = 'PASSED'
    return tuple(['0', res, str])

#Test execution combining both multiple header and library analysis
def test_13():
    print "Executing test: test_13"
    str = 'FAILED'
    cmt = ['EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER' ]
    comment(cmt, {})
    args = " temp/config -lm tsrc/testdata/libraries.txt -hm tsrc/testdata/headers.txt -f test_13"
    res = repr(runTest(args))
    if failUnless(res, '0'):
        if checkreports('libraries_test_13') and checkreports('headers_test_13'):
            str = 'PASSED'
    return tuple(['0', res, str])
    
#Test execution for single header and single library analysis followed by filtering        
def test_14():
    print "Executing test: test_14"
    str = 'FAILED'
    cmt = ['EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER' ]
    comment(cmt, {})
    args = " temp/config -hs e32notif.h -ls agentdialog.dso -f test_14"
    res = repr(runTest(args))
    if failUnless(res, '0'):
    	if checkreports('headers_test_14') and checkreports('libraries_test_14'):
    	    str = 'PASSED'
    return tuple(['0', res, str])

#Test execution for single header analysis followed by filtering        
def test_15():
    print "Executing test: test_15"
    str = 'FAILED'
    cmt = ['EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER', 'REPORT_FILE_LIBRARIES', 'FILTER_FILE_LIBRARIES' ]
    comment(cmt, {})
    args = " temp/config -hs bitbase.h -f test_15"
    res = repr(runTest(args))
    if failUnless(res, '0'):
        if checkreports('headers_test_15'):
            str = 'PASSED'
    return tuple(['0', res, str])

#Test execution for single library analysis followed by filtering        
def test_16():
    print "Executing test: test_16"
    str = 'FAILED'
    cmt = ['REPORT_FILE_HEADERS', 'FILTER_FILE_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER', 'EXCLUDE_DIR_HEADERS' ]
    comment(cmt, {})
    args = " temp/config -ls cafutils.dso -f test_16"
    res = repr(runTest(args))
    if failUnless(res, '0'):
        if checkreports('libraries_test_16'):
            str = 'PASSED'
    return tuple(['0', res, str])

#Test replace headers parameters
def test_17():
    print "Executing test: test_17"
    str = 'FAILED'
    cmt = ['EXCLUDE_DIR_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER', 'REPORT_FILE_LIBRARIES', 'FILTER_FILE_LIBRARIES' ]
    comment(cmt, {'REPLACE_HEADERS':'myheaderbase.h:myheadera.h'})
    args = " temp/config -hs myheaderbase.h -f test_17"
    res = repr(runTest(args))
    if failUnless(res, '0'):
        if checkreports('headers_test_17'):
            str = 'PASSED'
    return tuple(['0', res, str])

#Test Exclude directories
def test_18():
    print "Executing test: test_18"
    str = 'FAILED'
    cmt = ['REPLACE_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER', 'REPORT_FILE_LIBRARIES', 'FILTER_FILE_LIBRARIES' ]
    comment(cmt, {})
    args = " temp/config -hs caf/agent.h -f test_18"
    res = repr(runTest(args))
    if failUnless(res, '0'):
        if checkreports('headers_test_18'):
            str = 'PASSED'
    return tuple(['0', res, str])

#Test default Toolchain 
def test_19():
    print "Executing test: test_19"
    str = 'FAILED'
    cmt = ['TOOLCHAIN', 'EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER', 'FILTER_FILE_HEADERS', 'REPORT_FILE_HEADERS' ]
    comment(cmt, {})
    args = " temp/config -ls bitgdi.dso -f test_19"
    res = repr(runTest(args))
    if failUnless(res, '0'):
        if checkreports('libraries_test_19'):
            str = 'PASSED'
    return tuple(['0', res, str])

#Test armv5 toolchain
def test_20():
    print "Executing test: test_20"
    str = 'FAILED'
    cmt = ['EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS', 'REPORT_FILE_HEADERS', 'FILTER_FILE_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER' ]
    comment(cmt, {'TOOLCHAIN':'rvct', 'TOOLCHAIN_PATH':os.environ.get('RVCT22BIN')})
    args = " temp/config -ls audioequalizerutility.dso -f test_20"
    res = repr(runTest(args))
    if failUnless(res, '0'):
        if checkreports('libraries_test_20'):
            str = 'PASSED'
    return tuple(['0', res, str])

#Test without toochain path
def test_21():
    print "Executing test: test_21"
    str = 'FAILED'
    cmt = ['EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS', 'REPORT_FILE_HEADERS', 'FILTER_FILE_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER' ]
    if os.name == 'nt':	
        comment(cmt, {'TOOLCHAIN_PATH':''})
    else:
        print "Testcase currently not valid for Linux\n"
    args = " temp/config -ls c32.dso -f test_21"
    res = repr(runTest(args))
    if failUnless(res, '0'):
        if checkreports('libraries_test_21'):
            str = 'PASSED'
    return tuple(['0', res, str])

#Test without platform data
def test_22():
    print "Executing test: test_22"
    str = 'FAILED'
    cmt = ['EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS', 'REPORT_FILE_LIBRARIES', 'FILTER_FILE_LIBRARIES', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER' ]
    comment(cmt, {'USE_PLATFORM_DATA':'false'})
    args = " temp/config -hs s32strm.h -f test_22"
    res = repr(runTest(args))
    if failUnless(res, '0'):
        if checkreports('headers_test_22'):
            str = 'PASSED'
    return tuple(['0', res, str])
    
#Test carbide plugin options
def test_23():
    print "Executing test: test_23"
    str = 'FAILED'
    res = 'PID value in integer'
    terms = []
    cmt = ['EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER' ]
    comment(cmt, {})
    args = " temp/config -c -hs e32notif.h -ls caleninterimutils.dso -f test_23 > test_23.txt"
    runTest(args)
    f = open('test_23.txt')
    for line in f:
        print line
        if line.find('PID:') != -1:
            terms = line.split(':')
            try:
                val = int(terms[1])
            except ValueError:
                res = 'not integer'
                str = 'FAILED'
                break
            else:
                if (0 < val <= 100000):
                    str = 'PASSED'
    f.close()
    os.remove('test_23.txt')
    return tuple(['integer 1-100000', res, str])

#Test execution without passing config file
def test_24():
    print "Executing test: test_24"
    str = 'FAILED'
    args = " -ha -la -f test_24"
    res = repr(runTest(args))
    if failUnless(res, '3'):
        str = 'PASSED'
    return tuple(['3', res, str])

#Test execution without passing report-id
def test_25():
    print "Executing test: test_25"
    str = 'FAILED'
    cmt = ['REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER', 'EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS' ]
    comment(cmt, {})
    args = " temp/config -hs e32notif.h -ls aknnotify.dso -f test_25"
    res = repr(runTest(args))
    if failUnless(res, '0'):
        if checkreports('headers_test_25') and checkreports('libraries_test_25'):
            str = 'PASSED'
    return tuple(['0', res, str])

#Test execution for recursive headers     
def test_26():
    print "Executing test: test_26"
    str = 'FAILED'
    cmt = ['RECURSIVE_HEADERS', 'EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER', 'REPORT_FILE_LIBRARIES', 'FILTER_FILE_LIBRARIES' ]
    comment(cmt, {})
    args = " temp/config -hs e32notif.h test_26"
    res=repr(runTest(args))
    if failUnless(res, '0'):
        if checkreports('headers_test_26'):
            str = 'PASSED'
    return tuple(['0', res, str])
    
#Test execution for only filtering without issue file specified in config        
def test_27():
    print "Executing test: test_27"
    str = 'FAILED'
    shutil.copy(os.getcwd()+'/testdata/SAReport_test_10.xml',os.getcwd()+'/testdata/SAReport_test_10.xml.bak')
    cmt = ['ISSUES_FILE', 'EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS', 'REPORT_FILE_HEADERS', 'FILTER_FILE_HEADERS', 'REPORT_FILE_LIBRARIES', 'FILTER_FILE_LIBRARIES' ]
    comment(cmt, {})
    args = " temp/config -f test_10"
    res = repr(runTest(args))
    shutil.move(os.getcwd()+'/testdata/SAReport_test_10.xml.bak',os.getcwd()+'/testdata/SAReport_test_10.xml')
    if failUnless(res, '0'):
        str = 'PASSED'
    return tuple(['0', res, str])
    
#Test execution without passing the temp parameter
def test_28():
    print "Executing test: test_28"
    str = 'FAILED'
    cmt = ['TEMP', 'EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER' ]
    comment(cmt, {})
    args = " temp/config -hs e32notif.h -ls agentdialog.dso test_28"
    res = repr(runTest(args))
    if failUnless(res, '0'):
        if checkreports('headers_test_28') and checkreports('libraries_test_28'):
            str = 'PASSED'
    shutil.rmtree(DEFAULT_TEMP)
    return tuple(['0', res, str])

#Test execution to check baseline_sdk_dir and current_sdk_dir mandatory.
def test_29():
    print "Executing test: test_29"
    str = 'FAILED'
    cmt = ['TEMP','BASELINE_SDK_DIR', 'CURRENT_SDK_DIR']
    comment(cmt, {})
    args = " temp/config -hs e32notif.h -ls agentdialog.dso test_29"
    res = repr(runTest(args))
    if failUnless(res, '6'):
      str = 'PASSED'
    shutil.rmtree(DEFAULT_TEMP)
    return tuple(['0', res, str])

#Test execution for relative path in baseline headers     
def test_30():
    print "Executing test: test_30"
    str = 'FAILED'
    cmt = ['REPLACE_HEADERS' ]
    comment(cmt, {'BASELINE_HEADERS':'ecom'})
    args = " temp/config -ha test_30"
    res = repr(runTest(args))
    if failUnless(res, '0'):
      if checkreports('headers_test_30'):
        str = 'PASSED'
    return tuple(['0', res, str])

#Test execution to check for dependency between import library and dll    
def test_31():
    print "Executing test: test_31"
    str = 'FAILED'
    cmt = ['EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS', 'REPORT_FILE_HEADERS', 'FILTER_FILE_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER','BASELINE_IMPORTDLLS' ]
    comment(cmt, {})
    args = " temp/config -la -f test_31"
    res = repr(runTest(args))
    if failUnless(res, '6'):
    	str = 'PASSED'
    return tuple(['0', res, str])
    
#Test execution only with default sdk, not import library and dll    
def test_32():
    print "Executing test: test_32"
    str = 'FAILED'
    cmt = ['EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS', 'REPORT_FILE_HEADERS', 'FILTER_FILE_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER','BASELINE_IMPORTLIBRARIES',
            'CURRENT_IMPORTLIBRARIES','BASELINE_IMPORTDLLS','CURRENT_IMPORTDLLS']
    comment(cmt, {})
    args = " temp/config -la test_32"
    res = repr(runTest(args))
    if failUnless(res, '0'):    
        if checkreports('libraries_test_32'):
            str = 'PASSED'
    return tuple(['0', res, str])

#Test execution with import library and dll    
def test_33():
    print "Executing test: test_33"
    str = 'FAILED'
    cmt = ['EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS', 'REPORT_FILE_HEADERS', 'FILTER_FILE_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER']
    comment(cmt, {})
    args = " temp/config -la test_33"
    res = repr(runTest(args))
    if failUnless(res, '0'):    
        if checkreports('libraries_test_33'):
            str = 'PASSED'
    return tuple(['0', res, str])
    
#Test execution with multiple build target    
def test_34():
    print "Executing test: test_34"
    str = 'FAILED'
    cmt = ['EXCLUDE_DIR_HEADERS', 'REPLACE_HEADERS', 'REPORT_FILE_HEADERS', 'FILTER_FILE_HEADERS', 'REPORT_FILE_FILTER', 'OUTPUT_FILE_FILTER','BASELINE_IMPORTLIBRARIES',
            'CURRENT_IMPORTLIBRARIES','BASELINE_IMPORTDLLS','CURRENT_IMPORTDLLS']
    comment(cmt, {'BASELINE_BUILDTARGET':'ARMv5;ARMv6', 'CURRENT_BUILDTARGET':'ARMv5;ARMv6'})
    args = " temp/config -la test_34"
    res = repr(runTest(args))
    if failUnless(res, '0'):    
        if checkreports('libraries_test_34'):
            str = 'PASSED'
    return tuple(['0', res, str])
