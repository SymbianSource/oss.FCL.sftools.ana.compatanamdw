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
# Description:  File object classes
#

import config, lib
import webAPIDB
from lib import file_utils

FILE_STATUS_UNDEF = 0
FILE_STATUS_SCANNED = 1 # File is scanned to FileObject
FILE_STATUS_DUMPED = 2 # File is dumped to XML file.

COMPONENT_LEVEL_TOP = 0 # ADO-level component.
COMPONENT_LEVEL_SUB = 1 # Component included by ADO-level component

class FileObject(object):

    errorFile = ''    
    def __init__(self, fullname, shortname, status=FILE_STATUS_UNDEF, level=COMPONENT_LEVEL_TOP):
        self.myFullname = fullname.replace('\\', '/').strip('/')
        self.myShortname = shortname.replace('\\', '/').strip('/')
        self.myStatus = status
        self.myLevel = level
        self.myIncludes = []
    
    def setStatus(self, status):
        self.myStatus = status

    def getStatus(self):
        return self.myStatus

    def getFullname(self):
        return self.myFullname

    def getShortname(self):
        return self.myShortname

    def getLevel(self):
        return self.myLevel

    def setLevel(self, level):
        self.myLevel = level

    def getIncludes(self):
        return self.myIncludes

    def addInclude(self, inc):
        self.myIncludes.append(inc)
    
    def get_xml_element(self, allComponents, allProjects, allSources):
        ret = ''       
        for i in self.getIncludes():
            fileext = file_utils.get_fileext(i.lower())
            if fileext == 'h' or fileext == 'hrh' or fileext == 'hpp' or fileext == 'pan':
                ret += '        <inc>' + i + '</inc>\n'                
        return ret

    def appendIncludes(self, incList, allObjs):
        for key in self.myIncludes:
            if not key in incList:
                incList.append(key.lower())
            obj = allObjs.get(key.lower())
            if obj:
                obj.appendIncludes(incList, allObjs)
            else:
                lib.log_progress('Cannot find file: ' + key.lower() + ', which was included from ' + self.getShortname())

class Component(FileObject):

    def __init__(self, fullname, shortname, status=FILE_STATUS_UNDEF, level=COMPONENT_LEVEL_TOP):
        super(Component, self).__init__(fullname, shortname, status, level)  
        self.myExports=[]
        self.myProjects=[]

    def getExports(self):
        return self.myExports
    
    def addExport(self, exp):
        self.myExports.append(exp)

    def getProjects(self):
        return self.myProjects

    def addProject(self, proj):
        self.myProjects.append(proj)        
        
    def get_xml_element(self, allComponents, allProjects, allSources):
        exportCounter = 0
        ret = ''
        if self.myStatus == FILE_STATUS_DUMPED:
            return ret #already dumped

        # If the level is SUB-component, then this will be dumped 
        # by the including bld.inf fileobject.
        if self.myLevel == COMPONENT_LEVEL_SUB:
            return ret 

        # Here we are dealing with 'TOP' level bld.inf (i.e not included by other bld.inf files)        
        include_elems = ''
        ret += '  <component id=\"%(fn)s\">\n' % {'fn':self.myShortname}
                
        # Listed MMP-files:
        allMmpFiles = {}
        # Exported headers:
        allHeaderFiles = {}
        
        myApi = webAPIDB.webAPIDB()

        # Get all the included .inf files recursively in the same dict object:        
        for f in self.myIncludes:
            fileext = file_utils.get_fileext(f.lower())
            if fileext == 'inf':                
                subComp = allComponents.get(f.lower())
                if subComp:                    
                    subComp.appendIncludes(self.myIncludes, allComponents)
                    subComp.setStatus(FILE_STATUS_DUMPED)
                else:
                    lib.log_progress('Cannot find the file: ' + f.lower() + ', which was included from ' + self.getShortname())                 

        # Exported headers from this .inf file:
        detailinfo=[]
        for e in self.myExports:
            if e.find('epoc32/include')!= -1:                      
                exportCounter += 1
                ret += '    <hdr id=\"%(h)s\">\n' % {'h':e.strip('/')}
                if config.API_INFO_NEEDED == 'yes':
            	    detailinfo = myApi.findAPIFromHeader(file_utils.get_file_name(e))
            	    ret += '      <api name=\"%(h)s\" '% {'h':detailinfo[0]}
            	    ret += ' category=\"%(h)s\"/>\n' % {'h':detailinfo[1].strip('\r').strip('\n').strip(' ')}
                ret += '    </hdr>\n'

        # Exported headers from included .inf files:
        for inf in self.myIncludes:
            fileext = file_utils.get_fileext(inf.lower())
            if fileext == 'inf' or fileext == 'inc':
                o = allComponents.get(inf.lower())
                if not o:
                    continue
                for se in o.getExports():
                    if se.find('epoc32/include')!= -1:                      
                        exportCounter += 1                    
                        ret += '    <hdr id=\"%(h)s\">\n' % {'h':se.strip('/')}
                        if config.API_INFO_NEEDED == 'yes':
                    	    detailinfo = myApi.findAPIFromHeader(file_utils.get_file_name(se))
                    	    ret += '      <api name=\"%(h)s\" '% {'h':detailinfo[0]}
                    	    ret += ' category=\"%(h)s\"/>\n' % {'h':detailinfo[1].strip('\r').strip('\n').strip(' ')}
                        ret += '    </hdr>\n'

        # File is not exporting anything, so we don't write any component element for it:
        if exportCounter == 0:
            self.myStatus = FILE_STATUS_DUMPED
            return '\n'
        
        # Projects (mmp-files) listed in this .inf file:            
        for p in self.myProjects:
            fileext = file_utils.get_fileext(p.lower())
            if fileext == 'mmp':
                subComp = allProjects.get(p.lower())
                if subComp:
                    ret += subComp.get_xml_element(allComponents, allProjects, allSources)
                    subComp.setStatus(FILE_STATUS_DUMPED)
                else:
                    lib.log_progress('Cannot find the file: ' + p.lower() + ' listed in PRJ_MMPFILES of ' + self.getShortname())

        # Projects (mmp-files) listed in included .inf files:
        for inf in self.myIncludes:
            fileext = file_utils.get_fileext(inf.lower())
            if fileext == 'inf':
                o = allComponents.get(inf.lower())
                if not o:                
                    continue
                for sp in o.getProjects():
                    fileext = file_utils.get_fileext(sp.lower())                
                    if fileext == 'mmp':
                        subComp = allProjects.get(sp.lower())
                        if subComp:
                            ret += subComp.get_xml_element(allComponents, allProjects, allSources)
                            subComp.setStatus(FILE_STATUS_DUMPED)
                        else:
                            lib.log_progress('Cannot find the file: ' + sp.lower() + ' listed in PRJ_MMPFILES of ' + self.getShortname())        
        
        ret += '  </component>\n'

        self.myStatus = FILE_STATUS_DUMPED                
        return ret

class Project(FileObject):

    def __init__(self, fullname, shortname, status=FILE_STATUS_UNDEF, level=COMPONENT_LEVEL_TOP):
        super(Project,self).__init__(fullname, shortname, status, level)    
        self.myIncPaths=[]
        self.mySrcPaths=[]
        self.mySrcFiles=[]

    def getIncludePaths(self):
        return self.myIncPaths

    def addIncludePath(self, inc):
    	  pathpresent = False
    	  for ip in self.myIncPaths:
    	  	if(ip == inc):
    	  		pathpresent = True
    	  		break
    	  if pathpresent == False:
    	  	self.myIncPaths.append(inc)

    def getSourcePaths(self):
        return self.mySrcPaths

    def addSourcePath(self, sp):
        self.mySrcPaths.append(sp)

    def getSources(self):
        return self.mySrcFiles

    def addSource(self, sf):
        self.mySrcFiles.append(sf)       


    def get_xml_element(self, allComponents, allProjects, allSources):
        ret = ''
        if self.myStatus == FILE_STATUS_DUMPED:
            return ret
        if self.myLevel == COMPONENT_LEVEL_TOP:
            ret += '    <prj id=\"%(fn)s\">\n' % {'fn':self.myShortname}

        # Get all the included files recursively in the same dict object:        
        for f in self.myIncludes:
            fileext = file_utils.get_fileext(f.lower())
            if fileext == 'mmp' or fileext == 'mmh' or fileext == 'mmpi':
                subComp = allProjects.get(f.lower())
                if subComp:
                    subComp.appendIncludes(self.myIncludes, allProjects)
                    subComp.setStatus(FILE_STATUS_DUMPED)
                else:
                    lib.log_progress('Cannot find the file: ' + f.lower() + ', which was included from ' + self.getShortname())
                    

        for f in self.myIncludes:
            fileext = file_utils.get_fileext(f.lower())
            if fileext == 'mmp' or fileext == 'mmh' or fileext == 'mmpi':
                subProject = allProjects.get(f.lower())
                if subProject:
                    ret += subProject.get_xml_element(allComponents, allProjects, allSources)
                    for sp in subProject.getSourcePaths():
                        if not sp in self.mySrcPaths:
                            self.mySrcPaths.append(sp)

                    for sf in subProject.getSources():
                        if not sf in self.mySrcFiles:
                            self.mySrcFiles.append(sf)                            

                    for ip in subProject.getIncludePaths():
                        if not ip in self.myIncPaths:
                            self.myIncPaths.append(ip)                    
        
        for i in self.myIncPaths:
            ret += '      <incpath>'
            ret += i
            ret += '</incpath>\n'

        if self.myLevel == COMPONENT_LEVEL_TOP:
            for sf in self.mySrcFiles:
                for sp in self.mySrcPaths:
                    fullpath = sp + '/' + sf
                    source = allSources.get(fullpath.lower())
                    if source:
                        ret += '      <src id=\"' + fullpath + '\">\n'
                        ret += source.get_xml_element(allComponents, allProjects, allSources)
                        ret += '      </src>\n'
                        break                    

        if self.myLevel == COMPONENT_LEVEL_TOP:
            ret += '    </prj>\n'

        self.myStatus = FILE_STATUS_DUMPED                        
        return ret            

class Source(FileObject):
    def __init__(self, fullname, shortname, status=FILE_STATUS_UNDEF, level=COMPONENT_LEVEL_TOP):
        super(Source,self).__init__(fullname, shortname, status, level)
        return
    def get_xml_element(self, allComponents, allProjects, allSources):
        ret = ''       
        for i in self.myIncludes:
            fileext = file_utils.get_fileext(i.lower())
            if fileext == 'h' or fileext == 'hrh' or fileext == 'hpp' or fileext == 'pan':
                ret += '        <inc>' + i + '</inc>\n'                
        return ret
