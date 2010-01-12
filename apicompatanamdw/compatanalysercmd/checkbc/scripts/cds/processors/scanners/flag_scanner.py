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
# Description:  Flag scanner for source, header and project files
#

import re
from processors.scanners.file_scanner import FileScanner

_reDefine = re.compile(r'(?:#define|MACRO)\s+([\w\d_]+)\s*(.*)')
_reUndef = re.compile(r'#undef[ \t]+([\w\d_]+)')
_reMisformattedStart = re.compile(r'#\s+(if|undef|def)')
MULTILINE = '__MULTI_LINE$__'

def DBG(txt):
    #print txt
    pass


class FlagScanner(FileScanner):
    def __init__(self, progressStr='', progressTreshold=-1):
        super(FlagScanner, self).__init__(progressStr, progressTreshold)

        # list of (filename, lineno, define, value)
        self.defines = []
        # list of (filename, startLineNo, endLineNo, flagname, operator, value)        
        self.checks = []
        
        self.publicData.extend([self.defines, self.checks])
        
    def interested_extensions(self):
        return ['cpp', 'mmp', 'iby', 'oby', 'inf', 'rss', 'c', 'h', 'hpp', 'hrh', 'rh', 'inl', 'rsg']
        
    def needs_parsed_contents(self):
        return True

    def _move_define_params(self, name, value):
        if len(value) and (value[0] == '('):
            # assign parameters to name portion
            pstack = 1
            name += value[0]; 
            value = value[1:]
            while pstack > 0 and value:
                if value[0] == '(':
                    pstack += 1
                elif value[0] == ')':
                    pstack -= 1
                name += value[0]; 
                value = value[1:]
            name = name.replace(' ', '').replace('\t', '')
            value = value.strip()
        return name, value

    def _get_define_decl(self, text):
        if ((text.find("#define") == -1) and (text.find("#undef") == -1)):
            return (None, None)
        text = text.replace(MULTILINE, '\n')
        m = _reDefine.search(text)
        if m:
            name, value = self._move_define_params(m.group(1), m.group(2))
            DBG('Defines found: %s --- %s' % (name, value))
            return (name, value)
        m = _reUndef.search(text)
        if m:
            name = m.group(1)
            DBG('undef found for ' + name)
            return (name, None)
        DBG('No defines found after all')
        return (None, None)

    
    def _get_checked_defines(self, text):
        'returns list of flagnames. plain [] in case there is no checks in text'
        
        # at first remove "misformatted" preprocessor usage (e.g. #    if -> #if)
        text = re.sub(_reMisformattedStart, r'#\1', text)
        if len(text) < 3 or text[0:3].find('#if') == -1:
            return []
         
        parts, tmpParts = [text.replace(MULTILINE, '\n')], []
        for s in ('#ifdef', '#ifndef', '#if', 'defined', '(', ')', '&', '|', '[', ']', '!', '=', '<', '>'):
            #DBG('PARTS --- ' + str(parts))
            for part in parts:
                tmpParts.extend(part.split(s))
            parts, tmpParts = tmpParts, []
            
        tmpParts, parts = parts, []
        for part in tmpParts:
            part = part.strip()
            if part and part not in parts:
                parts.append(part)
        DBG('checked defines = ' + str(parts))
        return parts

    
    def process_file(self, contents, fullFileName, shortFileName):
        # store (filename, usages, usedLineNo) values based on #if... #endif declarations here
        #   during scanning
        checkStack = []
        
        lineCount = contents.get_linecount()
        lineNo = 0
        multilineLineNo = -1
        multilineLineTxt = ''
        for img in contents.iter_lineimages():
            self.print_progress(lineNo, lineCount)
            lineNo += 1
            txt = img.code_and_strings().strip()
            DBG('line: ' + txt)
            if txt and txt[-1] == '\\':
                if multilineLineNo < 0:
                    multilineLineNo = lineNo
                multilineLineTxt = multilineLineTxt + txt[:-1] + MULTILINE
                continue
            elif multilineLineNo > 0:
                DBG('closing multiline')
                txt = multilineLineTxt + txt
                multilineLineTxt = ''
                
            if len(txt) >= 6 and txt[0:6].find('#endif') != -1:
                DBG('found endif, closing latest define checks')
                try:
                    usageInfo = checkStack.pop()
                    usages = usageInfo[1]
                    for usage in usages:
                        self.checks.append([usageInfo[0], usage, usageInfo[2], lineNo])
                except IndexError:
                    self.warn('Encountered unmatching #endif in %s:%d' % (shortFileName, lineNo))
                continue                    

            name, value = self._get_define_decl(txt)
            if name:
                usedLineNo = lineNo
                if multilineLineNo > 0:
                    usedLineNo = multilineLineNo
                    multilineLineNo = -1
                self.defines.append((shortFileName, lineNo, name, value))
            else:
                usages = self._get_checked_defines(txt)
                if usages:
                    usedLineNo = lineNo
                    if multilineLineNo > 0:
                        usedLineNo = multilineLineNo
                        multilineLineNo = -1
                    checkStack.append([shortFileName, usages, usedLineNo])
            
    def store_to_db(self, snapshotId, file2id, cursor):
        SQL = 'INSERT INTO defines (snapshotId, fileId, lineNo, defname, defvalue) VALUES (%s, %s, %s, %s, %s)'
        for define in self.defines:
            cursor.execute(SQL, (snapshotId, file2id[define[0]], define[1], define[2], define[3]))
        SQL = 'INSERT INTO define_checks (snapshotId, fileId, definition, startLineNo, endLineNo)' + \
              'VALUES (%s, %s, %s, %s, %s)'
        for check in self.checks:
            cursor.execute(SQL, (snapshotId, file2id[check[0]], check[1], check[2], check[3]))

_CLAZZ_ = FlagScanner