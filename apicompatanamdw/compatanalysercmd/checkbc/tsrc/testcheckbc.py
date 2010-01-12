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

import os
import time
import sys
import inspect
import testcases
import shutil
import platform

if os.name == 'nt':
    path = os.path.dirname(sys.argv[0])
else:
    path = os.getcwd()

TC_DIR = path
TEMP_DIR = TC_DIR + os.sep + 'temp'
TOOLS_DIR = TC_DIR + os.sep + os.pardir + os.sep + os.pardir
EXEC_DIR = TC_DIR + os.sep + os.pardir + os.sep + "bin"

time_taken = 0
total_time_taken = 0
totalCount = 0
timeval = time.strftime("%a %b %d, %Y at %H:%M:%S", time.localtime())

if os.environ.get('RVCT22BIN') is None:
    print 'Environment Variable RVCT22BIN must be set before starting the test harness'
    sys.exit()
    
report_file = 0
passed = 0
failed = 0
ostr = ""

def UpdateTimeTaken(tm):
    global time_taken, total_time_taken
    time_taken = tm
    total_time_taken += tm


def write(key, res):
    global passed
    global failed
    global totalCount
    global ostr
    totalCount = totalCount + 1
    ostr = ostr+"  <testcase classname=\"BCFilter\" name=\""+key+"\" time=\""+str(round(time_taken,3))+"\">\n"
    if res[2] == 'PASSED':
        passed = passed + 1
    else:
        failed = failed + 1
        ostr = ostr+"    <failure message=\"Failed\" type=\"Failed\">Failed</failure>\n"
    ostr = ostr+"    <expresults>"+res[0]+"</expresults>\n"
    ostr = ostr+"    <actresults>"+res[1]+"</actresults>\n"
    ostr = ostr+"  </testcase>\n"

class registry:
    _register = {}
    items = 0
    cur_item = -1
    keys = []
    def __init__(self):
        pass

    def __iter__(self):
        return self
    
    def __getitem__(self, item):
        return self._register[item]

    def next(self):
        if self.cur_item >= (self.items-1):
            self.cur_item = -1
            raise StopIteration
        else:
            self.cur_item = self.cur_item + 1
            return tuple([ self.keys[self.cur_item],self._register[self.keys[self.cur_item]] ])
        
    def register(self, key, val):
        self._register[key] = val
        self.items = self.items + 1
        self.keys.append(key)
        
    def deregister(self, key):
        if self._register.has_key(key):
            self._register.pop(key)
            self.items = self.items - 1

    def next_entry(self):
        if self.cur_item < (self.items-1):
            self.cur_item = self.cur_item + 1
            return tuple([ self.keys[self.cur_item],self._register[self.keys[self.cur_item]] ])
        else:
            return tuple()
        
    def prev_entry(self):
        if self.cur_item != -1:
            self.cur_item = self.cur_item - 1
            return tuple([ self.keys[self.cur_item], self._register[self.keys[self.cur_item]] ])
        else:
            return tuple()

    def count():
        return self.items
    
def setUp(key):
    print '\n---------------------------------------------------------------'
    
def tearDown():
    print '\n---------------------------------------------------------------'

def testAll(db):
    global ostr
    result = 0
    os.chdir(TC_DIR)
    for key, value in db:
        print '\n---------------------------------------------------------------'
        stime = time.clock()
        res = value()
        etime = time.clock()
        print '\n---------------------------------------------------------------'
        UpdateTimeTaken(etime-stime)
        write(key, res)

def register_tc(db):
    index = 3
    if 'c' == sys.argv[2]:
        index = 4 
    if len(sys.argv) > index:
        cases = []
        file = open( sys.argv[index] )
        for line in file:
            cases.append(line.rstrip('\r\n').lower())
        file.close()
    for key,value in inspect.getmembers(testcases):
        if inspect.isfunction(value) and key.split('_')[0] == 'test':
            if len(sys.argv) > index:
                if key in cases:
                    db.register(key, value)
            else:
                db.register(key, value)

    
def open_results():
    if os.path.exists(REPORT) and os.name == 'nt':
        cmd = "start " + REPORT
        os.system(cmd)
    return

def write_header(file):
    global failed
    global totalCount
    global total_time_taken
    file.write('<?xml version="1.0" encoding="UTF-8" standalone="no" ?>\n')
    file.write('<?xml-stylesheet type="text/xsl" href="checkbctestresults.xsl"?>\n')
    file.write("<testsuite errors=\"0\" failures=\""+str(failed)+"\" hostname=\""+platform.node()+"\" name=\"BCFilter\" tests=\""+str(totalCount)+"\" time=\""+str(round(total_time_taken,3))+"\" timestamp=\""+str(timeval)+"\">\n")
    file.write("<properties>\n</properties>\n")
    
def write_footer(file, db):
    global ostr
    file.write(ostr)
    file.write("</testsuite>\n")
    file.close()

def copy_toolset():
    dir = os.getcwd()
    changed_TOOL_DIR = TOOLS_DIR;
    HA=""
    BCF=""
    LA=""
    
    file = open( sys.argv[1] )
    cases = file.readlines()
    file.close()
    for tc in cases:
        temp = tc.find('checkbc')
        if(temp!=-1):
            if(tc.split('=')[1].split(';')[0]== 'trunk'):
                changed_TOOL_DIR = changed_TOOL_DIR+ os.sep + os.pardir
            elif(tc.split('=')[1].split(';')[0]!= 'bin'):	
                changed_TOOL_DIR = changed_TOOL_DIR+ os.sep + os.pardir+ os.sep + os.pardir
                
    for tc in cases:
        temp = tc.find('ha')
        if(temp != -1):
            haDir = tc.split('=')[1].split(';')[0]
            if(haDir == 'trunk'):
                HA = changed_TOOL_DIR+os.sep+"headeranalyser"+os.sep+"trunk"+os.sep+"bin"
            elif(haDir != 'bin'):
                HA = changed_TOOL_DIR+os.sep+"headeranalyser"+os.sep+"tags"+os.sep+haDir+os.sep+"bin"
            else:
                HA = changed_TOOL_DIR+os.sep+"headeranalyser"+os.sep+"bin"
                
    for tc in cases:
        temp = tc.find('bcf')
        if(temp != -1):
            bcDir = tc.split('=')[1].split(';')[0]
            if(bcDir == 'trunk'):
                BCF = changed_TOOL_DIR+os.sep+"bcfilter"+os.sep+"trunk"+os.sep+"bin"
            elif(bcDir != 'bin'):
                BCF = changed_TOOL_DIR+os.sep+"bcfilter"+os.sep+"tags"+os.sep+bcDir+os.sep+"bin"
            else:
                BCF = changed_TOOL_DIR+os.sep+"bcfilter"+os.sep+"bin"
                
    for tc in cases:
        temp = tc.find('la')
        if(temp != -1):
            laDir = tc.split('=')[1].split(';')[0]
            if(laDir == 'trunk'):
                LA = changed_TOOL_DIR+os.sep+"libraryanalyser"+os.sep+"trunk"+os.sep+"bin"
            elif(laDir != 'bin'):
                LA = changed_TOOL_DIR+os.sep+"libraryanalyser"+os.sep+"tags"+os.sep+laDir+os.sep+"bin"
            else:
                LA = changed_TOOL_DIR+os.sep+"ordinalchecker"+os.sep+"bin"
                
    os.chdir( TC_DIR + os.sep + os.pardir )
    if not os.path.exists(EXEC_DIR):
        os.makedirs(EXEC_DIR)
    
    
    copy(HA+os.sep+"forced_9.4.h" ,"bin"+os.sep )
    copy(HA+os.sep+"forced_9.4v2.h" ,"bin"+os.sep )
    copy(HA+os.sep+"forced_mobileruntime.h" ,"bin"+os.sep )
    copy(HA+os.sep+"forced_kernel.h" ,"bin"+os.sep )
    
    if os.name == 'nt':
        copy(BCF+os.sep+"bcfilter.exe" ,"bin"+os.sep )
        copy(BCF+os.sep+"libxerces-c2_7_0.dll" ,"bin"+os.sep )

        copy(HA+os.sep+"ha.exe" ,"bin"+os.sep )
        copy(HA+os.sep+"ha_gccxml_cc1plus.exe" ,"bin"+os.sep )
        copy(HA+os.sep+"boost_thread-gcc-mt-1_33_1.dll" ,"bin"+os.sep )
        copy(HA+os.sep+"mingwm10.dll" ,"bin"+os.sep )
    
        copy(LA+os.sep+"la.exe" ,"bin"+os.sep )
        copy(LA+os.sep+"cfilt.exe" ,"bin"+os.sep )
    else:
        copy(BCF+os.sep+"bcfilter" ,"bin"+os.sep )
        copy(BCF+os.sep+"libxerces-c2_7_0.dll" ,"bin"+os.sep )

        copy(HA+os.sep+"ha" ,"bin"+os.sep )
        copy(HA+os.sep+"ha_gccxml_cc1plus" ,"bin"+os.sep )
        copy(HA+os.sep+"boost_thread-gcc-mt-1_33_1.dll" ,"bin"+os.sep )
        copy(HA+os.sep+"mingwm10.dll" ,"bin"+os.sep )

        copy(LA+os.sep+"la" ,"bin"+os.sep )
        copy(LA+os.sep+"cfilt" ,"bin"+os.sep )
    os.chdir(dir)

def copy(src, dst):
    try:
        shutil.copy(src, dst )
    except IOError, e:
        print e
        shutil.rmtree(EXEC_DIR)
        sys.exit(1)
        
if __name__ == '__main__':
    #Check for proper python version and then continue execution
    if not "2.4" <= platform.python_version() < "3.0":
        python_error()
    lst = []
    db = registry()
    if len(sys.argv) < 3:
        print "Usage: TestCheckBC.py <toolPathFile> [c] <outputfile> [<testcasefile>]"
        print "<toolPathFile> - Text file with info regarding which path to be taken for each component."
        print "                 These can be either bin / trunk / tag number"
        print "                 - bin, if it is for S60 Release"
        print "                 - trunk, if executable should be taken from trunk "
        print "                 - tag number, specify the tag no from which executable should be taken"
        print "[c] - Optional parameter to Copy binaries, if not already existing."
        print "<outputfile> - report filename eg: report.xml"
        print "[<testcasefile>] - Optional parameter. Text file with list of test cases mentioned, those to be executed."
        sys.exit(1)
    if not os.path.exists(TEMP_DIR):        
        os.makedirs(TEMP_DIR)
    if not os.path.exists(TEMP_DIR + os.sep + 'results'):
        os.makedirs(TEMP_DIR + os.sep + 'results')
    
    if 'c' == sys.argv[2]:
        copy_toolset()
        if(len(sys.argv)== 3):
            print '---------files copied--------'
            sys.exit(0)
        REPORT = TC_DIR + os.sep + 'reports' + os.sep + sys.argv[3]
    else:
        if not os.path.exists(EXEC_DIR):
            copy_toolset()
            print 'Toolset not found. New copy created'
        REPORT = TC_DIR + os.sep + 'reports' + os.sep + sys.argv[2]
    	
    register_tc(db)
    report_file = open(REPORT, 'w')
    testAll(db)
    write_header(report_file)
    write_footer(report_file, db)
    shutil.rmtree(TEMP_DIR) 
    open_results()