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
# Description:  Scanner for .mmp files
#

import re, pprint, lib
import os,config
from processors.scanners.file_scanner import FileScanner
from lib import file_utils

class MmpScanner(FileScanner):  

    def interested_extensions(self):
        return ['mmp', 'mmh','mmpi']
        
    def needs_parsed_contents(self):
        return True

    def processIncludePath(self, line, fileObj, pfDefs):
        tmpIncPaths = []        
        tmpIncPaths = line.split()
        for ip in tmpIncPaths:
            ipTrimmed = ip.strip('/').strip().replace('+', 'epoc32').lower()            
            # --- Include paths ---
            # Don't include development time include paths (i.e paths beginning with '.' or '..'),
            # because they are not available when analyzing final platforms.
            if not ip == 'systeminclude' and not ipTrimmed.startswith('.'):
                macroDef = pfDefs.getPlatformDefinition(ipTrimmed)                
                if len(macroDef) > 0:
                    for macroIp in macroDef:                
                        if len(macroIp) > 0:
                            self.processIncludePath(macroIp, fileObj, pfDefs)
                elif not file_utils.is_ignored_dir(file_utils.get_dir_name(ipTrimmed)):
                    fileObj.addIncludePath(ipTrimmed)
        
    
    def process_file(self, contents, fileObj, allObjs, pfDefs):  
    	  tempMmh = []      
    	  fileName = fileObj.getShortname().replace('\\','/').strip('/')        
        # Loop all the lines in mmp-file:
    	  line = ''
    	  fromPrevious = False
    	  for img in contents.iter_lineimages():
            # Join lines separated with '\':
            testStr = img.code_and_strings().strip().lower()
            if testStr.endswith('\\'):
                if fromPrevious == False:
                    line = ''
                line += testStr.strip('\\').replace('\\', '/') + ' '
                temp = fromPrevious
                fromPrevious = True                
                continue
            elif fromPrevious == True:
                line += testStr.replace('\\', '/')
                temp = fromPrevious
                fromPrevious = False                
            else:
                line = testStr.replace('\\', '/')                
                        
            # Check if this is a macro defined in platform_paths.hrh:
            macroTest = pfDefs.getPlatformDefinition(line)
            
            if len(macroTest) > 0:                
                line = macroTest[0] #definition was found from platform defs              
            if (line.startswith('sourcepath') ):
                # Add source paths to project object, if the directory is valid:
                tmpSrcPaths = []
                tmpSrcPaths = line.split()
                for sp in tmpSrcPaths:                    
                    if not sp == 'sourcepath':
                        pDir = file_utils.complete_path(fileName, sp.lower())
                        if not file_utils.is_ignored_dir(file_utils.get_dir_name(pDir)):
                            fileObj.addSourcePath(pDir.strip('/'))
                continue
            elif (line.startswith('source') ):
                # Add source files to project object:
                tmpSrcFiles = []        
                tmpSrcFiles = line.split()
                for sf in tmpSrcFiles:                    
                    if not sf.lower() == 'source':
                        if sf.count('..') > 0:
                            # Relative path.
                            # Get dir-name:
                            srcDir = file_utils.get_dir_name(sf).lower()
                            # Get filename:
                            srcFile = file_utils.get_file_name(sf).lower()
                            # If the source file is given with relative path, solve the path and add it to
                            # source paths. Only the filename is then added to source files.
                            if not srcDir in fileObj.getSourcePaths():
                                if not file_utils.is_ignored_dir(file_utils.get_dir_name(srcDir)):
                                    fileObj.addSourcePath(srcDir)                                                
                            if not srcFile in fileObj.getSources():
                                if not file_utils.is_ignored_dir(file_utils.get_dir_name(srcFile)):
                                    fileObj.addSource(srcFile)
                        elif not file_utils.is_ignored_dir(file_utils.get_dir_name(sf)):
                            fileObj.addSource(sf.lower())
                continue
            elif (line.startswith('systeminclude') ):
                self.processIncludePath(line, fileObj, pfDefs)                
                continue
            
            elif line.startswith('#include'):
            	incFile = line.replace('#include', '').lower().strip().strip(' <>"')
            	if(incFile.find('.mmh') != -1):
            		tempMmh.append(incFile)
            		
            	else:
            		fileObj.addInclude(file_utils.complete_path(fileName, incFile))
            	continue
            	
    	  #add epoc32/include by default as include path
    	  temp = "epoc32/include"
    	  self.processIncludePath(temp, fileObj, pfDefs)

    	  includepaths = fileObj.getIncludePaths()
    	  for outer in tempMmh:
    	  	path_list = []
    	  	file_utils.read_mmh_file(outer,includepaths,path_list)
    	  	for i in path_list:
    	  		self.processIncludePath(i, fileObj, pfDefs)
    	  	
    	  	if( len( path_list ) <= 0 ):
    	  		fileObj.addInclude(file_utils.complete_path(fileName, outer))		
           	  
_CLAZZ_ = MmpScanner
 