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
# Description:  File image handling functions for CDS script
#

import sys, pprint
from array import array

_DBG = False
def dbg(str):
    if _DBG:
        print str

TT_UNKNOWN = '?'; TT_COMMENT = '#'; TT_STRING = '"'; TT_CODE = '.'
def translate_mark_for_print(mark):
    if mark == "\n":
        return "\\n"
    elif mark == "\r":
        return "\\r"
    elif mark == "\t":
        return "\\t"
    return mark
    
    
class CCLineImage(object):
    def __init__(self, data, mask, lineno=0, startPos=-1, endPos=-1):
        self.__data = data
        self.__mask = mask
        self.lineno = lineno
        self.startPos = startPos
        self.endPos = endPos
        self.datalen = len(data)

    def data(self):
        return self.__data[:]

    def code(self, useBlanks=True):
        return self._get_line((TT_CODE,), useBlanks)

    def comments(self, useBlanks=True):    
        return self._get_line((TT_COMMENT,), useBlanks)
    
    def strings(self, useBlanks=True):    
        return self._get_line((TT_STRING,), useBlanks)

    def code_and_strings(self, useBlanks=True):    
        return self._get_line((TT_STRING, TT_CODE), useBlanks)

    def text(self):    
        return self._get_line((TT_STRING, TT_CODE, TT_COMMENT), False)
        
    def mask(self):
        return self.__mask.tostring()

    def _get_line(self, typez, useBlanks):
        line = array('c')
        for i in xrange(self.datalen):
            if self.__data[i] == '\n':
                break
            elif self.__mask[i] in typez:
                line.append(self.__data[i])
            elif useBlanks:
                line.append(' ')
        return line.tostring()
        
            
class CCTextBlockImage(object):
    delimitPairs = (('(', ')'), ('{', '}'), ('[', ']'), ('<', '>'))
    delimitChars = [e for s, e in delimitPairs] + [s for s, e in delimitPairs]
    endDelimiters = [e for s, e in delimitPairs]
    startDelimiters = [s for s, e in delimitPairs]
    
    def __init__(self):
        self.data = array('c')
        self.datamask = array('c')
        
        self.chPrev = None
        self.ch = None
        self.chNext = None
        self.pos = 0
        self.continueScan = True
        self.dataLen = 0
        self.lineFeeds = []
        self.lineFeedLen = 0

    def load(self, textblock):
        import sys
        del self.data
        self.data = array('c', textblock)
        self.datamask = array('c', TT_UNKNOWN * len(self.data))
        self.dataLen = len(textblock)
                
    def _dbg_chars(self):
        if _DBG:
            dbg("pos=%d, len=%d, prev=%s, cur=%s, next=%s" % (self.pos, self.dataLen, 
                                                            translate_mark_for_print(self.chPrev),
                                                            translate_mark_for_print(self.ch), 
                                                            translate_mark_for_print(self.chNext)))

    # moves current data pointer and marks passed chars as charType
    def _seek(self, amount, prevType=None, curType=None, nextType=None):

        if not self.dataLen > 0:
            return
        if prevType:
            self.datamask[self.pos-1] = prevType
        if curType:
            self.datamask[self.pos] = curType
        if nextType:
            self.datamask[self.pos+1] = nextType
            
        oldPos = self.pos
        self.pos += amount
        assert (oldPos <= self.pos) and (amount <= 2)

        if self.pos <= 0:
            self.pos = 0; self.chPrev = None; self.ch = self.data[0]
            if self.dataLen > 1:
                self.chNext = self.data[1]
            
            self._dbg_chars()
        elif self.pos == self.dataLen - 1:
            self.chNext = None; self.ch = self.data[-1]; self.chPrev = self.data[-2]
            self._dbg_chars()
        elif self.pos > self.dataLen - 1:
            self.pos = self.dataLen - 1
            dbg("FINISHING SCAN")
            self.continueScan = False
        else:
            self.ch = self.data[self.pos]; self.chNext = self.data[self.pos+1]; self.chPrev = self.data[self.pos-1]
            self._dbg_chars()



    def scan(self, bytePrintFmtStr='', bytePrintTreshold=20000):
        if self.dataLen == 0:
            return

        SINGLELINE = 1; MULTILINE = 2; STRING = 3; CODE = 4
        self.pos = 0; self.continueScan = True

        state = CODE
        self._seek(0)
        while self.continueScan:
            if (self.pos > 1) and (self.pos % bytePrintTreshold == 0) and bytePrintFmtStr:
                print bytePrintFmtStr % (self.pos, self.dataLen, ((self.pos * 100) / self.dataLen))
            if state == CODE:
                if (self.ch == '/') and (self.chNext == '/'):
                    dbg("FOUND // -> ENTER SINGLELINE STATE")
                    self._seek(2, curType=TT_COMMENT, nextType=TT_COMMENT)
                    state = SINGLELINE
                elif (self.ch == '/') and (self.chNext == '*'):
                    dbg("FOUND /* -> ENTER MULTILINE STATE")
                    self._seek(2, curType=TT_COMMENT, nextType=TT_COMMENT)
                    state = MULTILINE
                elif (self.ch == '"'):
                    dbg('FOUND " --> ENTER STRING STATE')
                    self._seek(1, curType=TT_STRING)
                    state = STRING
                else:
                    if (self.ch == '\n'):
                        self.lineFeeds.append(self.pos)
                    self._seek(1, curType=TT_CODE)
            elif state == STRING:
                if (self.ch == '\n'):
                    if (self.chPrev != '\\'):
                        dbg("FOUND line-end on string --> ENTER CODE STATE")
                        state = CODE
                    self.lineFeeds.append(self.pos)
                    self._seek(1, curType=TT_STRING)
                elif (self.ch == '"'):
                    dbg('FOUND " on string --> ENTER CODE STATE')
                    self._seek(1, curType=TT_STRING)                                   
                    state = CODE
                else:
                    self._seek(1, curType=TT_STRING)
            elif state == MULTILINE:
                if (self.ch == '*') and (self.chNext == '/'):
                    dbg("FOUND multiline end --> ENTER CODE STATE")
                    self._seek(2, curType=TT_COMMENT, nextType=TT_COMMENT)
                    state = CODE
                else:
                    if (self.ch == '\n'):
                        self.lineFeeds.append(self.pos)
                    self._seek(1, curType=TT_COMMENT)
            elif state == SINGLELINE:
                if (self.ch == '\n'):
                    dbg("FOUND line-end on singleline comment --> ENTER CODE STATE")
                    self.lineFeeds.append(self.pos)                    
                    self._seek(1, curType=TT_COMMENT)
                    state = CODE
                else:
                    self._seek(1, curType=TT_COMMENT)
                    
        self.lineFeedLen = len(self.lineFeeds)


    def __str__(self):
        rawdata = array('c')
        for mark in self.data:
            rawdata.append(translate_mark_for_print(mark))
        return rawdata.tostring()

    def iter_lineimages(self, startPos=-1, forward=True, lineCount=-1):
        curline = array('c')
        curmask = array('c')
        pos = 0
        linesLeft = 9999999
        datalen = len(self.data)
        
        if startPos != -1:
            pos = startPos
            assert (pos >= 0) and (pos < datalen)
        if lineCount != -1:
            assert lineCount > 0
            linesLeft = self.get_lineno(pos)
            if forward:
                linesLeft = self.get_linecount() - self.get_lineno(pos)
            if lineCount < linesLeft:
                linesLeft = lineCount
            #print "%d - %d" % (self.get_linecount(), self.get_lineno(pos))
            assert linesLeft >= 0
            
        lineStartPos = 0
        lineNo = 1
        while (pos >= 0) and (pos < datalen) and (linesLeft > 0):
            mark = self.data[pos]
            maskmark = self.datamask[pos]
            if mark == '\n':
                yield CCLineImage(curline, curmask, lineNo, lineStartPos, pos)
                linesLeft -= 1
                curline = array('c')
                curmask = array('c')
                lineStartPos = pos + 1
                lineNo += 1
            else:
                curline.append(mark)
                curmask.append(maskmark)
            if forward:
                pos += 1
            else:
                pos -= 1
        if len(curline) > 0:
            yield CCLineImage(curline, curmask, lineNo, lineStartPos, pos)

    def get_line_startpos(self, pos):
        if pos > (self.dataLen - 1):
            return -1
        if self.lineFeedLen == 0:
            return 0
        for i in xrange(lineFeedLen):
            if self.lineFeeds[i] > pos:
                if i > 0:
                    return self.lineFeeds[i-1] + 1
                return 0
        return pos - self.lineFeeds[-1]

    def get_linecount(self):
        return len(self.lineFeeds) + 1
    
    def get_lineno(self, pos):
        if pos > (self.dataLen - 1):
            return -1
        lineFeedLen = len(self.lineFeeds)
        if lineFeedLen == 0:
            return 1
        for i in xrange(lineFeedLen):
            if self.lineFeeds[i] > pos:
                #print "if %d > %d" % (self.lineFeeds[i], pos)
                return i
        return lineFeedLen
            
    def get_colno(self, pos):
        if pos > (len(self.data) - 1):
            return -1
        if len(self.lineFeeds) == 0:
            return pos
        for i in xrange(len(self.lineFeeds)):
            if self.lineFeeds[i] < pos:
                return pos - self.lineFeeds[i]

    def get_lineimages(self, startPos=-1, endPos=-1):
        lineImgs = []
        curline = array('c')
        curmask = array('c')
        lastInd = len(self.data) - 1
        if startPos < 0: startPos = 0
        if startPos > lastInd: startPos = lastInd
        if endPos < 0: endPos = 0
        if endPos > lastInd: endPos = lastInd
        pos = startPos
        while pos <= endPos:
            if self.data[pos] == '\n':
                lineImgs.append(CCLineImage(curline, curmask, self.get_lineno(pos), self.get_line_startpos(pos), pos))
                curline = array('c')
                curmask = array('c')
            else:
                curline.append(self.data[pos])
                curmask.append(self.datamask[pos])
            pos += 1
        if len(curline) > 0:
            lineImgs.append(CCLineImage(curline, curmask, self.get_lineno(pos), self.get_line_startpos(pos), pos))

        return lineImgs                        

    def find_matching_delimiter(self, pos):
        if (len(self.data) < pos) or (pos < 0):
            return -1
        
        data = self.data
        startChar = data[pos]
        if startChar not in self.delimitChars:
            return -1
        
        forward = True
        if startChar in self.endDelimiters:
            forward = False

        endChar = ''
        for s, e in self.delimitPairs:
            if startChar == s:
                endChar = e
            elif startChar == e:
                endChar = s

        curStackPos = 0
        datalen = len(data)
        while pos < datalen:
            if data[pos] == startChar:
                curStackPos += 1
            elif data[pos] == endChar:
                curStackPos -= 1
            if curStackPos <= 0:
                return pos
            if forward:
                pos += 1
            else:
                pos -= 1
        return -1

    def get_surrounding_lineimages(self, linesFw, linesBw, pos):
        if (len(self.data) < pos) or (pos < 0) or (linesFw < 0) or (linesBw < 0):
            return []
        lineImgs = []
        if linesBw and (pos > 0):
            pos -= 1
            while linesBw > 0:
                if self.data[pos] == '\n':
                    linesBw -= 1; linesFw += 1
                if pos < 0:
                    break
                pos -= 1

        for lineImg in self.iter_lineimages(pos, forward=True, lineCount=linesFw):
            lineImgs.append(lineImg)
        return lineImgs

class CCFileImage(CCTextBlockImage):
    def __init__(self):
        super(CCFileImage, self).__init__()

    def load(self, filename):
        rawdata = open(filename, 'r').read()
        self.load_from_rawdata(rawdata)
        
    def load_from_rawdata(self, rawdata):
        super(CCFileImage, self).load(rawdata)
        
if __name__=="__main__":
    f = CCFileImage()
    f.load(sys.argv[1])
    f.scan()
    for img in f.iter_lineimages():
        print img.mask()
        print img.text()
        #print img.code()
        #print img.comments()
        #print img.code_and_strings()
        #print img.strings()
        print ''