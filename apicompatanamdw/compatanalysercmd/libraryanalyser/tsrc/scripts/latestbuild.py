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

TC_BASE_INC = TC_FOLDER+os.sep+"baseplatform"+os.sep+"epoc32"+os.sep+"inc"+os.sep
TC_BASE_LIB = TC_FOLDER+os.sep+"baseplatform"+os.sep+"epoc32"+os.sep+"lib"+os.sep
TC_BASE_GROUP = TC_FOLDER+os.sep+"baseplatform"+os.sep+"epoc32"+os.sep+"group"+os.sep
TC_BASE_SRC = TC_FOLDER+os.sep+"baseplatform"+os.sep+"epoc32"+os.sep+"src"+os.sep
TC_CUR_INC = TC_FOLDER+os.sep+"currentplatform"+os.sep+"epoc32"+os.sep+"inc"+os.sep
TC_CUR_LIB = TC_FOLDER+os.sep+"currentplatform"+os.sep+"epoc32"+os.sep+"lib"+os.sep
TC_CUR_GROUP = TC_FOLDER+os.sep+"currentplatform"+os.sep+"epoc32"+os.sep+"group"+os.sep
TC_CUR_SRC = TC_FOLDER+os.sep+"currentplatform"+os.sep+"epoc32"+os.sep+"src"+os.sep

TC_SCRIPT = TC_FOLDER+os.sep+"scripts"+os.sep
TC_RESULT = TC_FOLDER+os.sep+"results"+os.sep

TMP_SCRIPT = os.getcwd()+os.sep+"template"+os.sep+"scripts"+os.sep


if len(sys.argv) == 1:
    print "Usage: latestbuild testcase_name"
    sys.exit()

if os.path.exists(TC_FOLDER):
    print "Test case directory " + TC_FOLDER + " already exists."
    sys.exit()

print "building test case directories...    "

os.makedirs(TC_BASE_INC)
os.makedirs(TC_BASE_LIB)
os.makedirs(TC_BASE_GROUP)
os.makedirs(TC_BASE_SRC)
os.makedirs(TC_CUR_INC)
os.makedirs(TC_CUR_LIB)
os.makedirs(TC_CUR_GROUP)
os.makedirs(TC_CUR_SRC)
os.makedirs(TC_SCRIPT)
os.makedirs(TC_RESULT)

print "copying test case files..."

shutil.copyfile(TMP_SCRIPT+'prepare.txt',TC_SCRIPT+'prepare.txt')
shutil.copyfile(TMP_SCRIPT+'config.txt',TC_SCRIPT+'config.txt')

print "Test case directory created: " + TC_FOLDER