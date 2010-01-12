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
# Description:  Scanner for source files
#

import re
from processors.scanners.file_scanner import FileScanner
from lib import file_utils
_reInclude = re.compile(r'#\s*include\s*[\<"]\s*([\d\w\./_]+)\s*[\>"]')
class SourceScanner(FileScanner):
      
    def interested_extensions(self):
        return ['cpp', 'c']
        
    def needs_parsed_contents(self):
        return True

    def process_file(self, contents, fileObj, allObjs, pfDefs):
        fileName = fileObj.getShortname().replace('\\','/').strip('/').lower()                      
        for img in contents.iter_lineimages():                        
            match = _reInclude.search(img.code_and_strings())
            if match:
                headerName = match.group(1).lower().replace('\\', '/').replace('+','epoc32')
                if not file_utils.is_ignored_dir(file_utils.get_dir_name(headerName)):                    
                    fileObj.addInclude(file_utils.get_file_name(headerName))

_CLAZZ_ = SourceScanner