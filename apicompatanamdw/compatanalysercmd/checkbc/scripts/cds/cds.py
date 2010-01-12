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
# Description:  Execution entry point of CDS script
#

import config, lib

lib.empty_warns()
lib.empty_log()

processorModules = []
for processorName in config.ACTIVE_PROCESSORS:
    processorModules.append(lib.dynamic_import(processorName))
    
if __name__ == '__main__':
    timer = lib.ExecTimer()
    timer.start_timing()
    lib.log_progress('CDS --- Processing started')
        
    for module in processorModules:
        module._RUNFN_()

    lib.log_progress('\n\nTotal processing time = ' + timer.get_processing_time())
    lib.log_progress('CDS --- Processing ended successfully')
    
