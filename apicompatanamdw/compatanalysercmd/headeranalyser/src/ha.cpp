/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies). 
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  
*
*/


#include "CmdGlobals.h"
#ifdef __WIN__
#pragma warning(disable:4786)
#endif
#include <xercesc/util/PlatformUtils.hpp>
#include <iostream>
#include "CommandLine.h"
#include "HAException.h"
#include "Analyser.h"

using namespace std;

int main(int argc, char *argv[]) 
{
    try 
    {
        // Perform per-process Xerces XML parser initialization
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) 
    {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Error during initialization! :\n"
             << message << "\n";
        XMLString::release(&message);
        return -1;
    }

    int ret=0;
    try 
    {	
        auto_ptr<Analyser> anal(new Analyser(argv, argc));
        ret = anal->analyse();        
    } catch (HAException e)
    {
        cout << e.errorMessage();
		XMLPlatformUtils::Terminate();
        return -1;
    } catch (...)
    {
        cout << "Program terminated unexpectedly." << endl;
		XMLPlatformUtils::Terminate();
        return -1;
    }

    // Perform per-process Xerces XML parser termination
    XMLPlatformUtils::Terminate();

    return ret;
}
