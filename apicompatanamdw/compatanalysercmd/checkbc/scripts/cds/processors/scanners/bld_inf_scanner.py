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
# Description:  Scanner for .inf files
#

import re, pprint, lib
from processors.scanners.file_scanner import FileScanner
from lib import file_utils, fileimage
from processors.platformdefs import PlatformDefinitions

#reExport = re.compile(r'([\./\\\w]*\.\w*)\s*([/\\\w]*\.?\w*)')

class BldInfScanner(FileScanner):

    def interested_extensions(self):
        return ['inf', 'inc']
        
    def needs_parsed_contents(self):
        return True

    # This function handles the lines in PRJ_EXPORTS section:
    def processExport(self, line, fileObj, pfDefs, myPfDefs):
        source = ''
        target = ''
        line=line.replace('\t',' ')
        elems = line.lower().split(' ', 1)
        if len(elems) > 0:
            source = elems[0].strip().strip(' |')
        if len(elems) > 1:
           target = elems[1].strip().strip(' |')
        
        if target.startswith('.'):
           return # Local export

        # Read included files        
        if line.startswith('#include'):
            fileName = fileObj.getFullname().replace('\\','/').strip('/')
            incFile = line.replace('#include', '').lower().strip().strip(' <>"')
            fullIncFile = file_utils.complete_path(fileName.lower(), incFile)
            try:
                fObj = open(fullIncFile, 'r')
                rawContents = fObj.read()
                parsedContents = fileimage.CCFileImage()
                parsedContents.load_from_rawdata(rawContents)
                parsedContents.scan(None)
                formIncLines = self.getFormattedLines(parsedContents)
                # scan lines from included files recursively:
                for incLine in formIncLines:
                    self.processExport(incLine, fileObj, pfDefs, myPfDefs)
                fObj.close()
            except IOError:
                return

        # Check if the source is macro, which is defined in platform_paths.hrh
        macroDefSource = pfDefs.getPlatformDefinition(source)
        if len(macroDefSource) == 0:
            # Check if the source is macro, which is defined in this file:
            macroDefSource = myPfDefs.getPlatformDefinition(source)
        if len(macroDefSource) > 0:
            source = macroDefSource[0]
            
        ext = source.split('.')[-1]
        if ext == 'h' or ext == 'hrh' or ext == 'lag' or ext == 'hpp' or ext == 'pan' or ext == 'rh':
            if target == '':
                # empty target
                target = 'epoc32/include/'
                target += source.split('/')[-1]
            else:
                macroDefTargets = pfDefs.getPlatformDefinition(target)
                if len(macroDefTargets) == 0:
                    macroDefTargets = myPfDefs.getPlatformDefinition(target)
                if len(macroDefTargets) > 0:
                    for t in macroDefTargets:
                        fileObj.addExport(t.lower())                                
                    return
                else:
                    # replace '+' with 'epoc32'
                    target = target.replace('+', 'epoc32')                        

            if target.find('epoc32/') == -1:
                # Only the sub-directory give, add epoc32/include:
                target = 'epoc32/include/' + target
            if file_utils.get_file_name(target) == '':
                if not target.endswith('/'):
                    target += '/'
                target += file_utils.get_file_name(source)

            # If the directory is valid, add target to exports of the object:                    
            if not file_utils.is_ignored_dir(file_utils.get_dir_name(target)):
                fileObj.addExport(target)

    # This function joins lines separated with '\'
    def getFormattedLines(self, contents):    
        formattedLines = []
        fromPrevious = False
        line = ''
        for img in contents.iter_lineimages():            
            testStr = img.code_and_strings().strip()
            if testStr.endswith('\\'):
                if fromPrevious == False:
                    line = ''
                line += testStr.strip('\\').replace('\\', '/') + ' '
                fromPrevious = True
                continue
            elif fromPrevious == True:
                line += testStr.replace('\\', '/')
                fromPrevious = False
            else:
                line = testStr.replace('\\', '/')

            formattedLines.append(line)

        return formattedLines            

    def process_file(self, contents, fileObj, allObjs, pfDefs):        
        fileName = fileObj.getShortname().replace('\\','/').strip('/')
        inExportSection = False
        inMmpFilesSection = False        
        OTHER_SECTIONS = ('PRJ_PLATFORMS', 'PRJ_TESTEXPORTS', 'PRJ_TESTMMPFILES', 'PRJ_EXTENSIONS')                
        # Loop all the lines in bld.inf:
        formattedLines = self.getFormattedLines(contents)
        myPlatformDefs = PlatformDefinitions('')
        
        for line in formattedLines:
            # Read macros from this file:
            myPlatformDefs.scanLine(line.lower())            
            inIncludeLine = False
            
            if (line.startswith('PRJ_EXPORTS')):
                inExportSection = True
                inMmpFilesSection = False
                continue
            elif (line.startswith('PRJ_MMPFILES')):
                inMmpFilesSection = True
                inExportSection = False
                continue
            elif (line.startswith('PRJ_')):
                for s in OTHER_SECTIONS:
                    if line.find(s) != -1:
                        inExportSection = False
                        inMmpFilesSection = False
                        continue
                if line.startswith('#include'):
                    incFile = line.replace('#include', '').lower().strip().strip(' <>"')
                    fullIncFile = file_utils.complete_path(fileObj.getFullname().lower(), incFile)
                    try:
                        fObj = open(fullIncFile, 'r')
                        rawContents = fObj.read()
                        parsedContents = fileimage.CCFileImage()
                        parsedContents.load_from_rawdata(rawContents)
                        parsedContents.scan(None)
                        formIncLines = self.getFormattedLines(parsedContents)
                        for incLine in formIncLines:                        
                            self.processExport(incLine, fileObj, pfDefs, myPlatformDefs)
                        fObj.close()
                        continue
                    except IOError:
                        continue
            elif line.startswith('#include'):                
                incFile = line.replace('#include', '').lower().strip().strip(' <>"')
                fileObj.addInclude(file_utils.complete_path(fileName.lower(), incFile))
                continue
            
            if inExportSection:
                self.processExport(line, fileObj, pfDefs, myPlatformDefs)                                
                        
            elif inMmpFilesSection:                
                ext = line.split('.')[-1].lower()
                if ext == line and not line == '' and not line.startswith('#'):
                    # MMP file is given without .mmp extension. Add one to it:
                    ext = 'mmp'
                    line += '.mmp'
                if (ext == 'mmp' ):
                    if not file_utils.is_ignored_dir(file_utils.get_dir_name(line)):
                        fileObj.addProject(file_utils.complete_path(fileName, line.lower()))
                
                    

_CLAZZ_ = BldInfScanner
