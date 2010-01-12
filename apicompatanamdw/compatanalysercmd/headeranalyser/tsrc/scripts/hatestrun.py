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

TC_NUM = sys.argv[1]
TC_FOLDER = os.getcwd()+os.sep+"TC"+os.sep+TC_NUM
SCRIPT_DIR = TC_FOLDER+os.sep+"scripts"+os.sep
RESULTS_DIR = TC_FOLDER+os.sep+"results"+os.sep
BBCRESULTS = os.pardir+os.sep+os.pardir+os.sep+"checkbc"+os.sep+"results"+os.sep+"BBCResults.xsl"

if len(sys.argv) == 1:
    print "Usage: hatestrun testcase_name"
    sys.exit()
    
if not os.path.exists(TC_FOLDER):
    print "Test case directory cannot be found: " + TC_FOLDER
    sys.exit()

if not os.path.exists(SCRIPT_DIR+"prepare.txt"):
    print "Cannot find file: " + SCRIPT_DIR + "prepare.txt"
    sys.exit()

file = open( SCRIPT_DIR+"prepare.txt" )
BASEDIR = ((file.readline()).replace("\\",os.sep).replace("/",os.sep)).rstrip('\n\r ')
CURRDIR = ((file.readline()).replace("\\",os.sep).replace("/",os.sep)).rstrip('\n\r ')
RESDIR = ((file.readline()).replace("\\",os.sep).replace("/",os.sep)).rstrip('\n\r ')
file.close()

print "Checking test case directories..."
if not os.path.exists(TC_FOLDER+os.sep+BASEDIR):
    print "Cannot find base platform directory: " + TC_FOLDER+os.sep+BASEDIR
    sys.exit()

if not os.path.exists(TC_FOLDER+os.sep+CURRDIR):
    print "Cannot find current platform directory: " + TC_FOLDER+os.sep+CURRDIR
    sys.exit()

if not os.path.exists(TC_FOLDER+os.sep+RESDIR):
    print "Cannot find result directory: " + TC_FOLDER+os.sep+RESDIR
    sys.exit()
    
TC_BBCRESULTS =  TC_FOLDER+os.sep+RESDIR+os.sep +"BBCResults.xsl"

if not os.path.exists( BBCRESULTS):
    print "Cannot find BBCResults.xsl"
else:
    shutil.copyfile(BBCRESULTS,TC_BBCRESULTS)

if os.path.exists(RESULTS_DIR+TC_NUM+"_results.xml"):
    os.remove(RESULTS_DIR+TC_NUM+"_results.xml")

print "---- Starting HeaderAnalyser ----"
os.chdir(os.pardir+os.sep+"bin")
cmd = os.getcwd() + os.sep + "ha -commandfile " + SCRIPT_DIR + TC_NUM + "_conf.txt"
os.system(cmd)
os.chdir(os.pardir+os.sep+"tsrc")
sys.exit()

   