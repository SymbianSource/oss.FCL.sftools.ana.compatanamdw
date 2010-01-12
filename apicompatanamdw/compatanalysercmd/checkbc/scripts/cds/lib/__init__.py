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
# Description:  Initialization file for LIB package
#

import datetime, config, os, file_utils

class ExecTimer(object):
    def __init__(self):
        self.startTime = None
        
    def start_timing(self):
        self.startTime = datetime.datetime.now()    
        
    def get_time_delta(self):
        delta = datetime.datetime.now() - self.startTime
        secs = delta.seconds
        mins = secs / 60
        secs = secs % 60
        hours = mins / 60
        mins = mins % 60
        return hours, mins, secs
        
    def get_processing_time(self):
        hours, mins, secs = self.get_time_delta()
        return '%02d:%02d:%02d' % (hours, mins, secs)
        
        
def profile_fn(fn, logfile, *args, **kwargs):
    import hotshot
    prof = hotshot.Profile(logfile)
    prof.runcall(fn, *args, **kwargs)
    prof.close()

def print_profile_results(logfile, statLen=50, sortwords=('time', 'calls')):
    import hotshot.stats
    stats = hotshot.stats.load(logfile)
    stats.strip_dirs()
    stats.sort_stats(*sortwords)
    stats.print_stats(statLen)

def warn(msg):
    f = None
    try:
        f = open(config.WARN_FILENAME, 'a')
    except IOError:
        os.mkdir(file_utils.get_dir_name(config.WARN_FILENAME))
        f = open(config.WARN_FILENAME, 'a')
    f.write(msg + '\n')
    f.close()
    
def empty_warns():
    f = None
    try:
        f = open(config.WARN_FILENAME, 'w')
    except IOError:
        os.mkdir(file_utils.get_dir_name(config.WARN_FILENAME))
        f = open(config.WARN_FILENAME, 'w')
       
    f.write('')
    f.close()

def log_progress(msg):
    print msg
    f = None
    try:
        f = open(config.LOG_FILENAME, 'a')
    except IOError:
        os.mkdir(file_utils.get_dir_name(config.LOG_FILENAME))
        f = open(config.LOG_FILENAME, 'a')
    f.write(msg + '\n')
    f.close()
    
def empty_log():
    try:
        f = open(config.LOG_FILENAME, 'w')
    except IOError:
        os.mkdir(file_utils.get_dir_name(config.LOG_FILENAME))
        f = open(config.LOG_FILENAME, 'w')
    f.write('')
    f.close()

def dynamic_import(name):
    mod = __import__(name)
    components = name.split('.')
    for comp in components[1:]:
        mod = getattr(mod, comp)
    return mod
