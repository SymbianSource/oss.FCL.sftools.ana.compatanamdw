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
# Description:  Source code scanner functions.
#

import os, sys, datetime
import config, lib, platformdefs, fileobject
from lib import file_utils, ExecTimer, profile_fn, print_profile_results, fileimage, dynamic_import

scannerModules = []
pfDefs = platformdefs.PlatformDefinitions('')
for scannerName in config.ACTIVE_SCANNERS:
    scannerModules.append(dynamic_import(scannerName))  
    
def create_scanners():    
    scanners = []
    for module in scannerModules:
        scanners.append(module._CLAZZ_())
    return scanners

def initialize_scanners(scanners):
    allExtensions = []
    parsedExtensions = []
    for scanner in scanners:
        for e in scanner.interested_extensions():
            el = e.lower()            
            if el not in allExtensions:
                allExtensions.append(el)
            if scanner.needs_parsed_contents():
                if el not in parsedExtensions:
                    parsedExtensions.append(el)
    return allExtensions, parsedExtensions    

def scan_files(scanners, files, parsedExtensions, pfDefs):

    progressPrintThreshold = 100
    fileCounter = 0
    totalCount = len(files)
    previousPercents = 0
    for fileKey in files.keys():
        fileObj = files.get(fileKey)
        if not fileObj:
            continue
        fullname = fileObj.getFullname()
        shortname = fileObj.getShortname()
        # Read file contents:
        rawContents = open(fullname, 'r').read()
        parsedContents = None

        # Check if we are interested in the file-extension:
        fileext = file_utils.get_fileext(shortname.lower())        
        if fileext in parsedExtensions:
            #lib.log_progress('   parsing contents of ' + shortname)
            if fileCounter > 0 and (fileCounter % progressPrintThreshold == 0):
                percents = (fileCounter*100 / totalCount)
                if not percents == previousPercents:
                    lib.log_progress('%d percents of %s-files parsed (%d/%d)' % (percents, fileext, fileCounter, totalCount) )
                previousPercents = percents
            # Parse file contents form raw format:
            parsedContents = fileimage.CCFileImage()
            parsedContents.load_from_rawdata(rawContents)
            #parsedContents.scan('      %d/%d bytes (%d percents)')
            parsedContents.scan(None)
            fileCounter += 1
        for scanner in scanners:
            if not fileext in scanner.interested_extensions():                
                continue
            #lib.log_progress('   scanning using %s' % scanner.name())
            #Process file with correct scanner:
            scanner.process_file(parsedContents, fileObj, files, pfDefs)
        fileObj.setStatus(fileobject.FILE_STATUS_SCANNED)
    
def save_results(allComponents, allProjects, allSources):
    #lib.log_progress('Saving scanner contents...')
    i = 1
    resultFile = None
    try:
        resultFile = open(config.REPORT_FULLNAME, 'w')
    except IOError:
        # Create directory if it didn't exist:
        os.mkdir(file_utils.get_dir_name(config.REPORT_FULLNAME))
        resultFile = open(config.REPORT_FULLNAME, 'w')
        
    today = datetime.date.today()        
    resultFile.write('<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>\n')
    resultFile.write('<!-- Version history BEGIN -->\n')
    resultFile.write('<!-- ')
    resultFile.write(today.strftime("%d.%m.%Y"))
    resultFile.write(' Automatically created. Version: 1.0 -->\n')
    resultFile.write('<!-- Version history END -->\n')
    resultFile.write('<platform versionid=\"%(v)s\" build=\"%(b)s\">\n' % {'v':config.PLATFORM_VERSION, 'b':config.BUILD})
    resultFile.write('<component id="excluded header list">\n')
    resultFile.write('</component>\n')
    for compKey in allComponents.keys():
        comp = allComponents.get(compKey)
        if not comp:
            continue
        if comp.getLevel() == fileobject.COMPONENT_LEVEL_TOP:
            if not comp.getStatus() == fileobject.FILE_STATUS_DUMPED:
                resultFile.write(comp.get_xml_element(allComponents, allProjects, allSources))

    resultFile.write('</platform>')
    resultFile.close()

def finalizeObjects(fileObjs):
    # This funtion sets Component level to COMPONENT_LEVEL_SUB if
    # the component is included by ADO-level component. This is
    # to ensure that we are not writing the same file twice to XML.
    for k in fileObjs.keys():
        o = fileObjs.get(k)
        if not o:
            continue # should not happen, but just in case...
        for i in o.getIncludes():            
            iObj = fileObjs.get(i.lower())
            if iObj:                
                iObj.setLevel(fileobject.COMPONENT_LEVEL_SUB)            

def run():
    timer = ExecTimer()
    timer.start_timing()
    try:
        fileobject.FileObject.errorFile = open(config.ERROR_LOG_FILENAME, 'w')
    except IOError:
        os.mkdir(file_utils.get_dir_name(config.ERROR_LOG_FILENAME))
        fileobject.FileObject.errorFile = open(config.ERROR_LOG_FILENAME, 'w')
    
    lib.log_progress('Loading scanners')
    scanners = create_scanners()
    allExtensions, parsedExtensions = initialize_scanners(scanners)
                
    lib.log_progress('Gathering files from the filesystem')
    allComponents = {}
    allProjects = {}
    allSources = {}
    for p, r in config.SCANNER_PATHS:
        path = p.lower()
        removedPrefix = r.lower()

        # BLD.INF files:        
        components = file_utils.get_filelist([path], 'inf;inc')
        if components:
            for f in components:
                # Filename is the key
                key = f.replace(removedPrefix, '').replace('\\', '/').strip().strip('/').lower()
                # Create Component object matching the key:
                allComponents[key]=fileobject.Component(f.lower(), key, fileobject.FILE_STATUS_UNDEF)              

        # MMP-files: 
        projects = file_utils.get_filelist([path], 'mmp;mmh;mmpi')
        if projects:
            for f in projects:                
                key = f.replace(removedPrefix, '').replace('\\', '/').strip().strip('/').lower()
                # Create Project object matching the key:
                allProjects[key]=fileobject.Project(f.lower(), key, fileobject.FILE_STATUS_UNDEF)                 

        # Source code files:           
        sources = file_utils.get_filelist([path], 'cpp;c')
        if sources:
            for f in sources:
                key = f.replace(removedPrefix, '').replace('\\', '/').strip().strip('/').lower()
                # Create Source object matching the key:
                allSources[key]=fileobject.Source(f.lower(), key, fileobject.FILE_STATUS_UNDEF) 

    # Find platform_paths.hrh file if available:
    pfDefs = platformdefs.PlatformDefinitions('')
    if not (config.PLATFORM_PATHS_HRH_LOCATION == '' or config.PLATFORM_PATHS_HRH_FILE == '' ):
        found = False
        headers = file_utils.get_filelist([config.PLATFORM_PATHS_HRH_LOCATION], file_utils.get_fileext(config.PLATFORM_PATHS_HRH_FILE))        
        if headers:
            for h in headers:
                # Read path definitions to PlatformDefinitions object.
                if file_utils.get_file_name(h.lower()) == config.PLATFORM_PATHS_HRH_FILE:
                     pfDefs = platformdefs.PlatformDefinitions(h)
                     pfDefs.scan()
                     found = True
                     break
        if found == False:
            lib.log_progress('Error: Platform path definitions file ' + config.PLATFORM_PATHS_HRH_FILE +' cannot be found from: ' + config.PLATFORM_PATHS_HRH_LOCATION)
            return

    # Scan files:    
    lib.log_progress('Scanning files')
    scan_files(scanners, allComponents, parsedExtensions, pfDefs)    
    scan_files(scanners, allProjects, parsedExtensions, pfDefs)
    scan_files(scanners, allSources, parsedExtensions, pfDefs)

    # Finalize objects: Component status is updated:
    lib.log_progress('Finalizing file objects')
    finalizeObjects(allComponents)    
    finalizeObjects(allProjects)    
    finalizeObjects(allSources)

    # Write fileobjects to XML-file:
    lib.log_progress('Writing the result file: ' + config.REPORT_FULLNAME)
    save_results(allComponents, allProjects, allSources)
   
    lib.log_progress('Finished scanning')
    lib.log_progress('Scanning time = ' + timer.get_processing_time())    
    fileobject.FileObject.errorFile.close()
_RUNFN_ = run


if __name__ == '__main__':
    lib.empty_warns()
    lib.empty_log()    
    run()
    