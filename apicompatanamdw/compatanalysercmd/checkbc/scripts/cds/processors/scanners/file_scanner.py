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
# Description:  Base class for file scanner implementations.
#

import pprint, cPickle, lib

class ScannerDbException(Exception):
    pass

class FileScanner(object):
    def __init__(self):
        return
        
    def interested_extensions(self):
        return []
        
    def needs_parsed_contents(self):
        return False

    def process_file(self, contents, fileObj, fileObjects, pfDefs):
        return
        
    def name(self):
        return self.__class__.__name__
        
    def add_to_listdict(self, dict_, key, value, uniq=False):
        try:
            if (not uniq) or (value not in dict_[key]):
                dict_[key].append(value)
        except KeyError:
            dict_[key] = []
            if (not uniq) or (value not in dict_[key]):
                dict_[key].append(value)

    
    def print_progress(self, curLine, total):
        return    
    def __str__(self):
        return ''
        
    def warn(self, msg):
        lib.warn(msg)
