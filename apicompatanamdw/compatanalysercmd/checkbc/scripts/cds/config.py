#
# Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
# Description:  Configuration file for CDS script
#

# --- PLATFORM VERSION ---

# This is used as in platform's xml-description as a version-id.
# By default, the version string is used also in report and error log filenames.
# Allowed values are: '5.0', '5.1' and '5.2'
PLATFORM_VERSION = '5.0'
BUILD = 'wk26_2008'

# --- REPORT FILENAME ---
REPORT_FILENAME = 's60_platform_data_temp'

# --- PLATFORM_PATHS.HRH FILE NAME AND LOCATION ---

# Platform_paths.hrh file is searched from the following directory with the given filename.
PLATFORM_PATHS_HRH_LOCATION = r'C:\Build_C\S60_5_0_200826\epoc32\include\domain\osextensions'
PLATFORM_PATHS_HRH_FILE = r'platform_paths.hrh'

# --- SUB-DIRECTORIES THAT ARE NOT SCANNED ---

# All source code directories with following names are ignored and left out from the scan
IGNORED_FOLDERS = (
    'tsrc',
    'internal',
    'integtest',
    'test',
    'unittest',
    'inttest'
    )

# --- TOOL OUTPUT DIRECTORY ---

# --- Report, logs etc. are saved here: ---
TOOL_DIR = 'C:\\TEMP'

REPORT_FULLNAME = TOOL_DIR + '\\' + REPORT_FILENAME + '.xml'

# --- ERROR LOG FILENAME ---
ERROR_LOG_FILENAME = TOOL_DIR + '\\log\\s60_platform_' + PLATFORM_VERSION + '.log'

# --- PROCESSOR CONFIGURATION ---
ACTIVE_PROCESSORS = (
    'processors.scanner',
)

# --- SCANNER CONFIGURATION ---
ACTIVE_SCANNERS = (    
    'processors.scanners.bld_inf_scanner',
    'processors.scanners.mmp_scanner',
    'processors.scanners.src_scanner',    
)

# --- SOURCE CODE PATHS ---
# Tuples of (path, removed prefix)
SCANNER_PATHS = (
(r'C:\Build_C\S60_5_0_200826\src', r'C:\Build_C\S60_5_0_200826'),
(r'C:\Build_C\S60_5_0_200826\S60', r'C:\Build_C\S60_5_0_200826'),
)

# --- OUTPUT FILE LOCATIONS ---
WARN_FILENAME = TOOL_DIR + '\\results\\warns.txt'
LOG_FILENAME = TOOL_DIR + '\\results\\scanner.log'

# --- OPTIONAL API INFO FIELD ( options 'yes' or 'no') ---
API_INFO_NEEDED = 'yes'

# --- OPTIONAL IF API INFO NEEDED, MENTION THE SDK INDEX,
# --- ex: for 5.0 release_index 155,
# ---     for 5.1 sdk, release_index 154
# ---     for 5.2 release_index 150
#If not mentioned, then any release will be taken.
#Else while generating the platform data script , we can get the updated release index from kevlar for each sdk.

API_REL_INDX ='155'