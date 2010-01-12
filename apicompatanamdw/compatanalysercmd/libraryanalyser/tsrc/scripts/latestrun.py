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

LATEST_GCCE_BIN = os.pardir+os.sep+"tsrc"+os.sep+"bin"
LATEST_GCC_BIN = os.pardir+os.sep+"tsrc"+os.sep+"bin"
LATEST_RVCT_BIN = os.environ.get('RVCT22BIN')

TC_NUM = sys.argv[1]
TC_FOLDER = os.getcwd()+os.sep+"TC"+os.sep+TC_NUM
SCRIPT_DIR = TC_FOLDER+os.sep+"scripts"+os.sep
BBCRESULTS = os.pardir+os.sep+os.pardir+os.sep+"checkbc"+os.sep+"results"+os.sep+"BBCResults.xsl"

if len(sys.argv) == 1:
    print "Usage: latestrun testcase_name"
    sys.exit()
    
if not os.path.exists(TC_FOLDER):
    print "Test case directory cannot be found: " + TC_FOLDER
    sys.exit()
    
if not os.path.exists(SCRIPT_DIR+"prepare.txt"):
    print "Test case directory cannot be found: " + SCRIPT_DIR + "prepare.txt"
    sys.exit()
    
file = open( SCRIPT_DIR+"prepare.txt" )
BASENAME = ((file.readline()).replace("\\",os.sep).replace("/",os.sep)).rstrip('\n\r ')
BASEDIR = ((file.readline()).replace("\\",os.sep).replace("/",os.sep)).rstrip('\n\r ')
CURRNAME = ((file.readline()).replace("\\",os.sep).replace("/",os.sep)).rstrip('\n\r ')
CURRDIR = ((file.readline()).replace("\\",os.sep).replace("/",os.sep)).rstrip('\n\r ')
RESDIR = ((file.readline()).replace("\\",os.sep).replace("/",os.sep)).rstrip('\n\r ')
TOOLCHAIN = ((file.readline()).replace("\\",os.sep).replace("/",os.sep)).rstrip('\n\r ')
USELIBS = ((file.readline()).replace("\\",os.sep).replace("/",os.sep)).rstrip('\n\r ')
BASEDLLDIR = ((file.readline()).replace("\\",os.sep).replace("/",os.sep)).rstrip('\n\r ')
CURRDLLDIR = ((file.readline()).replace("\\",os.sep).replace("/",os.sep)).rstrip('\n\r ')
file.close()

print "Checking test case directories..."
basedirlist = BASEDIR.split(';')
BASEDIRS = ""
for d in basedirlist:
	if d != "":
		if not os.path.exists(TC_FOLDER+os.sep+d):
			print "Cannot find base platform directory: " + TC_FOLDER+os.sep+d
			sys.exit()
		if BASEDIRS != "":
			BASEDIRS = BASEDIRS + ";"
		BASEDIRS = BASEDIRS+TC_FOLDER+os.sep+d

curdirlist = CURRDIR.split(';')
CURRDIRS = ""
for d in curdirlist:
	if d != "":
		if not os.path.exists(TC_FOLDER+os.sep+d):
			print "Cannot find current platform directory: " + TC_FOLDER+os.sep+d
			sys.exit()
		if CURRDIRS != "":
			CURRDIRS = CURRDIRS + ";"
		CURRDIRS = CURRDIRS+TC_FOLDER+os.sep+d

basedlldirlist = BASEDLLDIR.split(';')
BASEDLLDIRS = ""
for d in basedlldirlist:
	if d != "":
		if not os.path.exists(TC_FOLDER+os.sep+d):
			BASEDLLDIRS = ""
		else:
			if BASEDLLDIRS != "":
				BASEDLLDIRS = BASEDLLDIRS + ";"
			BASEDLLDIRS = BASEDLLDIRS+TC_FOLDER+os.sep+d

curdlldirlist = CURRDLLDIR.split(';')
CURRDLLDIRS = ""
for d in curdlldirlist:
	if d != "":
		if not os.path.exists(TC_FOLDER+os.sep+d):
			CURRDLLDIRS = ""
		else:
			if CURRDLLDIRS != "":
				CURRDLLDIRS = CURRDLLDIRS + ";"
			CURRDLLDIRS = CURRDLLDIRS+TC_FOLDER+os.sep+d

if not os.path.exists(TC_FOLDER+os.sep+RESDIR):
    print "Cannot find result directory: " + TC_FOLDER+os.sep+RESDIR
    sys.exit()    
TC_BBCRESULTS =  TC_FOLDER+os.sep+RESDIR+os.sep +"BBCResults.xsl"

if not os.path.exists( BBCRESULTS):
    print "Cannot find BBCResults.xsl"
else:
    shutil.copyfile(BBCRESULTS,TC_BBCRESULTS)

if TOOLCHAIN == "GCCE":
    LATEST_TOOLDIR = LATEST_GCCE_BIN
elif TOOLCHAIN == "GCC":
    if os.name == "posix":
        print "Test case not supported on Linux"
        sys.exit()
    LATEST_TOOLDIR = LATEST_GCC_BIN 
elif TOOLCHAIN == "RVCT":
    LATEST_TOOLDIR = LATEST_RVCT_BIN
else:
	  TOOLCHAIN = "GCCE"
	  LATEST_TOOLDIR ="" 

print "---- Starting Library Analyser ----"
os.chdir(os.pardir+os.sep+"bin")

if os.name == "posix":
    LATEST_CFILT_BIN = os.getcwd()+os.sep+"cfilt"
else:
    LATEST_CFILT_BIN = os.getcwd()+os.sep+"cfilt.exe"
    
lib_command = ""
if BASEDIRS != "":
	lib_command = " -baselinelibdir " + BASEDIRS
if CURRDIRS != "":
	lib_command = lib_command + " -currentlibdir " + CURRDIRS
	
dll_command = ""
if BASEDLLDIRS != "":
	dll_command=" -baselinedlldir " + BASEDLLDIRS;
if CURRDLLDIRS != "":
	dll_command = dll_command + " -currentdlldir " + CURRDLLDIRS
    
RESULTS_DIR = TC_FOLDER + os.sep + RESDIR + os.sep
if os.path.exists(RESULTS_DIR+"results.xml"):
    os.remove(RESULTS_DIR+"results.xml")

if LATEST_TOOLDIR == "":
	cmd=os.getcwd()+os.sep+"la "+TOOLCHAIN+lib_command+dll_command+" -baselineversion \""+BASENAME+"\" -currentversion \""+CURRNAME+"\" -reportfile \""+TC_FOLDER+os.sep+"results"+os.sep+"results.xml\" -temp \""+os.getcwd()+os.sep+"temp\" -set \""+TC_FOLDER+os.sep+"scripts"+os.sep+"config.txt\"" 
else:
	cmd=os.getcwd()+os.sep+"la "+TOOLCHAIN+lib_command+dll_command+" -baselineversion \""+BASENAME+"\" -currentversion \""+CURRNAME+"\" -reportfile \""+TC_FOLDER+os.sep+"results"+os.sep+"results.xml\" -tools \""+LATEST_TOOLDIR+"\" -temp \""+os.getcwd()+os.sep+"temp\" -set \""+TC_FOLDER+os.sep+"scripts"+os.sep+"config.txt\""

print cmd
if USELIBS == "TRUE":
    cmd = cmd + " --uselibs"
if TOOLCHAIN == "RVCT":
    cmd = cmd + " -cfilt " + LATEST_CFILT_BIN

os.system(cmd)
os.chdir(os.pardir+os.sep+"tsrc")
sys.exit()

   