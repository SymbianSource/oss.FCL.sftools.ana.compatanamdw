/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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


 /*
* ==============================================================================
*  Name        : tselect.h
*  Part of     : testselect
*
*  Description : ?Description
*  Version:   0.5
*
  
*/
#ifndef __TESTSELECT_H__
#define __TESTSELECT_H__

#include <test/TestExecuteStepBase.h>
#include <e32svr.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h> 
#include <e32cons.h>

_LIT(KTestTimeout, "TestTimeout");		
_LIT(KTestReadFileDesc, "TestReadFileDesc");
_LIT(KTestWriteFileDesc, "TestWriteFileDesc");
_LIT(KTestReadWriteFileDesc, "TestReadWriteFileDesc");
_LIT(KTestPipeReadDesc, "TestPipeReadDesc");
_LIT(KTestPipeReadDesc1, "TestPipeReadDesc1");
_LIT(KTestPipeWriteDesc, "TestPipeWriteDesc");
_LIT(KTestSocketDesc, "TestSocketDesc");
_LIT(KTestSocketDesc2, "TestSocketDesc2");
_LIT(KTestMultipleDesc, "TestMultipleDesc");  

class CTestSelect : public CTestStep
	{
public:
	~CTestSelect(); 
	CTestSelect(const TDesC& aStepName);
	TVerdict doTestStepL();
	TVerdict doTestStepPreambleL();
	TVerdict doTestStepPostambleL();
private:
    TInt TestTimeout();
    TInt TestReadFileDesc();
    TInt TestWriteFileDesc();
    TInt TestReadWriteFileDesc();
    TInt TestPipeReadDesc();
    TInt TestPipeReadDesc1();
    TInt TestPipeWriteDesc();
    TInt TestSocketDesc();
    TInt TestSocketDesc2();
    TInt TestMultipleDesc();     
   	static void* ServerThread(TAny* ptr);
 protected:  // Data
        // ?one_line_short_description_of_data
        //?data_declaration;
        TInt iAcceptflag;
        TInt iSelectflag;
        TInt iWriteflag;
   
};
#endif 
