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

TC_BASE_INC = TC_FOLDER+os.sep+"baseline_headers"+os.sep+"epoc32"+os.sep+"include"+os.sep
TC_CUR_INC = TC_FOLDER+os.sep+"current_headers"+os.sep+"epoc32"+os.sep+"include"+os.sep
TC_SCRIPT = TC_FOLDER+os.sep+"scripts"+os.sep
TC_RESULT = TC_FOLDER+os.sep+"results"+os.sep

TMP_BASE_INC = os.getcwd()+os.sep+"template"+os.sep+"baseline_headers"+os.sep+"epoc32"+os.sep+"include"+os.sep
TMP_CUR_INC = os.getcwd()+os.sep+"template"+os.sep+"current_headers"+os.sep+"epoc32"+os.sep+"include"+os.sep
TMP_SCRIPT = os.getcwd()+os.sep+"template"+os.sep+"scripts"+os.sep


if len(sys.argv) == 1:
    print "Usage: hatestbuild testcase_name"
    sys.exit()

if os.path.exists(TC_FOLDER):
    print "Test case directory " + TC_FOLDER + " already exists."
    sys.exit()

print "building test case directories...    "

os.makedirs(TC_BASE_INC)
os.makedirs(TC_CUR_INC)
os.makedirs(TC_RESULT)
os.makedirs(TC_SCRIPT)

print "copying test case files..."

shutil.copyfile(TMP_BASE_INC+'forced.h',TC_BASE_INC+'forced.h')
shutil.copyfile(TMP_BASE_INC+'template.h',TC_BASE_INC+TC_NUM+'.h')
shutil.copyfile(TMP_CUR_INC+'forced.h',TC_CUR_INC+'forced.h')
shutil.copyfile(TMP_CUR_INC+'template.h',TC_CUR_INC+TC_NUM+'.h')
shutil.copyfile(TMP_SCRIPT+'prepare.txt',TC_SCRIPT+'prepare.txt')
shutil.copyfile(TMP_SCRIPT+'template_conf.txt',TC_SCRIPT+TC_NUM+'_conf.txt')

print "Test case directory created: " + TC_FOLDER