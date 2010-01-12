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
# Description:  File utility functions for CDS script
#

import os, sys, config

def complete_path(basePath, relativePath):

    if relativePath.strip('/').startswith('+'):
        return relativePath.strip('/').replace('+', 'epoc32')

    if relativePath.lower().startswith('/epoc32') or relativePath.lower().startswith('epoc32'):
        return relativePath.strip('/')
   
    lastBaseElem = True        
    upCntr = 0
    firstPathElems = []
    secondPathElems = []
    completePath = ''
    relSplitted = relativePath.split('/')
    baseSplitted = basePath.split('/')
    
    for r in reversed(relSplitted):
        if r == '..':                
            upCntr += 1
        elif not r == '.':
            secondPathElems.append(r)
    
    for b in reversed(baseSplitted):        
        if lastBaseElem == False:            
            if upCntr == 0 and not b == '.':
                firstPathElems.append(b)            
            elif upCntr > 0:
                upCntr -= 1
                
        lastBaseElem = False

    for f in reversed(firstPathElems):        
        completePath += f
        completePath += '/'

    for s in reversed(secondPathElems):
        completePath += s
        completePath += '/'

    return  completePath.strip('/')

def get_fileext(filename):
    return filename.split('.')[-1].lower()

def get_file_name(pathname):
    return os.path.basename(pathname)

def abspath(pathname):
    return os.path.abspath(pathname)
    
def get_dir_name(pathname):
    return os.path.dirname(pathname)
    
def get_files_from_dir(directory, extension=None, recursive=True):
    """Gets all the files with given extension from the given directory. If no extension
    is given, gets all files. Searches also all subdirs from given directories, if recursive=True.
    extensions string has format 'cpp;h;hrh'
    """
    
    if directory.split('/')[-1].split('\\')[-1].lower() in config.IGNORED_FOLDERS:
        return
    exts = extension.split(';')
    directory = os.path.abspath(directory)
    # Go through each object in directory
    for itemname in os.listdir(directory):
        fullpath = os.path.join(directory, itemname)

        # handle directories
        if os.path.isdir(fullpath) and not os.path.islink(fullpath) and recursive:
            for x in get_files_from_dir(fullpath, extension):  # recurse into subdir
                yield x   # this passes the result from recursive call to caller of this func

        # handle files
        else:
            if extension:
                for ext in exts:
                    if get_fileext(itemname) == ext:
                        yield fullpath
                        break
            else:
                yield fullpath
                
                
def _get_valid_pathname(name, check_fn, additionalCheckPath=""):
    retval = None
    if check_fn(name):
        retval = os.path.abspath(name)
    elif check_fn(os.getcwd() + name):
        retval = os.path.abspath(os.getcwd() + name)
    elif check_fn(os.path.dirname(sys.argv[0]) + "\\" + name):
        retval = os.path.abspath(os.path.dirname(sys.argv[0]) + "\\" + name)
    elif additionalCheckPath != "":
        name = os.path.dirname(os.path.abspath(additionalCheckPath)) + '\\' + name
        if check_fn(name):
            retval = name
    return retval
    
def get_valid_dirname(name, additionalCheckPath=""):
    """If given name is valid directory, returns the name as absolute path. Validness is done
    by checking absolute path, relative path to work directory, relative path to script file
    and from additional check path.
    If name is not valid, returns None
    """
    return _get_valid_pathname(name, os.path.isdir, additionalCheckPath)

def get_valid_filename(name, additionalCheckPath=""):
    """If given name is valid file, returns the name as absolute path. Validness is done
    by checking absolute path, relative path to work directory, relative path to script file
    and from additional check path.
    If name is not valid, returns None
    """
    return _get_valid_pathname(name, os.path.isfile, additionalCheckPath)

def is_correct_filetype(extension, filename):
    exts = extension.split(";")
    for ext in exts:
        if get_fileext(filename) == ext:
            return True
    return False
    

_CONSOLE_LINE_LEN = 140
def _print_to_curline(msg):
    if len(msg) > _CONSOLE_LINE_LEN:
        msg = "%s..." % msg[:_CONSOLE_LINE_LEN-3]
    else:
        msg = "%s%s" % (msg, (_CONSOLE_LINE_LEN - len(msg))*" ")
    print '\r%s' % msg ,  


def get_filelist(filesAndDirs, extension="", recursive=True, acceptsFiles=True, acceptsDirs=True, printOutput=True):
    """Returns tuple of files found from given file and directory list (filesAndDirs)
    having file extensions defined in extension (example = "cpp;c;hpp;h").
    If no extension string is given, searches for all files
    Searches also all subdirs from given directories, if recursive=True.
    Search is done for both, relative and absolute paths.
    If there was error in search, returns None
    """
    # check and collect files and dirs (also relative ones)
    files = []
    dirs = []
    
    for item in filesAndDirs:
        name = get_valid_filename(item)
        if name:
            if acceptsFiles:
                files.append(name.lower())
            else:
                if printOutput:
                    print "No files allowed as parameter but filename given (%s)!\n" % item
                return None
        else:
            name = get_valid_dirname(item)
            if name:
                if acceptsDirs:
                    dirs.append(name.lower())
                else:
                    if printOutput:
                        print "No directories allowed as parameter but directory name given (%s)!\n" % item
                    return None
            else:
                if printOutput:
                    print "Invalid file/directory name given!: %s\n" % item
                return None

    # find all relevant files from given directories
    print "Searching for files..."
    for dir_ in dirs:        
        for file_ in get_files_from_dir(dir_, extension, recursive):
            if printOutput:
                _print_to_curline('File %s' % file_)
            if file_ not in files:
                files.append(file_.lower())
    if printOutput:
        _print_to_curline("")
        print ""
    return files

def is_ignored_dir(directory):
    if directory.split('/')[-1].lower() in config.IGNORED_FOLDERS:
        return True

    return False

    
def read_mmh_file(mmhfile,includepaths,path_list):
	actualfile = ""
	
	for p,r in config.SCANNER_PATHS:
		sdkpath = r.lower()
	for inner in includepaths:
		inner = inner.replace('/', os.sep)
		mmhfile1 = mmhfile.replace('/', os.sep)
		mmhfile1 = mmhfile1.strip().strip('../')
		
		lpath = inner + os.sep +mmhfile1
		actualfile = sdkpath + os.sep + lpath
				
		if os.path.exists( actualfile):
			tempfile1 = open(actualfile)
			cases = tempfile1.readlines()
			tempfile1.close()
			for ip in cases:
				if ip.startswith('systeminclude'):
					path_list.append(ip)
				elif ip.startswith('#include'):
					incFile = ip.replace('#include', '').lower().strip().strip(' <>"')
					if incFile.find('.mmh') != -1:
						read_mmh_file(incFile,includepaths,path_list)

					
		