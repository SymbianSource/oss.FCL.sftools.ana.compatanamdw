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
# Description:  Platform definitions container class
#

from lib import fileimage

class PlatformDefinitions(object):
    def __init__(self, filename):
        self.platformDefs = []
        self.defFile = filename

    def addPlatformDefinition(self, key, value):
        self.platformDefs.append((key.lower(),value.lower()))        

    def getPlatformDefinition(self, key):
        ret = []
        tempRet = []
        
        for mKey, mVal in self.platformDefs:
            if key.lower() == mKey:
                tempRet.append(mVal)
        keyElems = key.lower().strip().strip(') ').split('(')
        if len(keyElems) == 2:    
            for mKey, mVal in self.platformDefs:
                mKeyElems = mKey.strip().strip(') ').split('(')
                if len(mKeyElems) == 2 and keyElems[0].strip() == mKeyElems[0].strip(): 
                    tempVar = mKeyElems[1].strip()
                    #code to manage dual syntax for export in 5.0 builds
                    if mVal.find('##') == -1:
                        val = mVal.strip().replace(tempVar, keyElems[1].strip()) 
                    else:
                        val = mVal.strip().replace('##'+tempVar, keyElems[1].strip())
                    tempRet.append(val.replace('\\','/').strip().strip('/'))

        #now remove duplicates from the list
        for val in tempRet:
            if val not in ret:
                ret.append(val)
        return ret
       
                
    def getPlatformDefinitions(self):    
        return self.platformDefs

    def scanLine(self, pl):
        elems = pl.replace('\\', '/').split()            
        if len(elems) == 0 or elems[0] != '#define':
            return
        line = ''          
        i = 2
        while i < len(elems):
            line += ' ' + elems[i].lower()
            i += 1                        
        self.addPlatformDefinition(elems[1], line.strip());
    
    def scan(self):
        scanFile = open(self.defFile, 'r')
        rawContents = scanFile.read()
        parsedContents = None
        parsedContents = fileimage.CCFileImage()
        parsedContents.load_from_rawdata(rawContents)
        parsedContents.scan('      %d/%d bytes (%d percents)')

        fromPrevious = False        
        parsedLines = []
        line = ''

        # Parse lines so that lines separated with \ are concatenated:                
        for img in parsedContents.iter_lineimages():            
            if fromPrevious == False:
                line = ''
                
            elems = []
            # remove trailing and preceding spaces 
            testStr = img.code_and_strings().strip().lower()
            elems = testStr.split()

            for e in elems:
                if e == '\\':
                    fromPrevious = True                    
                    break
                else:         
                    line += ' ' + e.replace('\\', '/').strip().strip('/')

            if len(elems) > 0 and elems[-1] == '\\':
                continue
            else:
                parsedLines.append(line.strip())
                fromPrevious = False
                            
        for pl in parsedLines:
            self.scanLine(pl.lower())
            
        scanFile.close()
        