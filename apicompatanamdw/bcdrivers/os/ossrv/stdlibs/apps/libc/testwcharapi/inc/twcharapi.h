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



#ifndef TWCHARAPI_H
#define TWCHARAPI_H

#include <test/TestExecuteStepBase.h>
#include <e32svr.h>

//#include <u32std.h>
//#include <unicode.h>
#include <collate.h>

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <_ansi.h>
#include <sys/stat.h> //S_ISWUSR
#include <sys/syslimits.h> //PATH_MAX
#include <unistd.h>
#include <wchar.h>
#include <locale.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <utime.h>
#include <sys/ioctl.h>
#include  <sys/wait.h>
#include <sys/uio.h>

_LIT(Ktwasctime, "twasctime");
_LIT(Ktwctime, "twctime");
_LIT(Ktwcslcat, "twcslcat");
_LIT(Ktwcslcpy, "twcslcpy");
_LIT(Ktwsetlocale, "twsetlocale");
_LIT(Ktwperror, "twperror");
_LIT(Ktwcserror, "twcserror");
_LIT(Ktwfindfirst, "twfindfirst");
_LIT(Ktwfindclose, "twfindclose");
_LIT(Ktwtelldir, "twtelldir");
_LIT(Ktwseekdir, "twseekdir");
_LIT(Ktwsetlocale1, "twsetlocale1");
_LIT(Ktwfindfirst1, "twfindfirst1");
_LIT(Ktwfindnext1, "twfindnext1");
_LIT(Kwcreat2, "wcreat2");
_LIT(Kwpopen3_1, "wpopen3_1");

class CTestWCharApi : public CTestStep
	{
public:
	~CTestWCharApi(); 
	CTestWCharApi(const TDesC& aStepName);
	TVerdict doTestStepL();
	TVerdict doTestStepPreambleL();
	TVerdict doTestStepPostambleL();
	void LocateSupportedDLLs();	
	
protected:
    TInt twseekdir();
	TInt twtelldir();
	TInt twasctime();
	TInt twctime();
	TInt twcslcat();
	TInt twcslcpy();
	TInt twsetlocale();
	TInt twperror();
	TInt twcserror();
	TInt twfindfirst();
	TInt twfindclose();	
	TInt twsetlocale1();
	TInt twfindfirst1();
	TInt twfindnext1();	
	TInt wcreat2();
	TInt wpopen3_1();
private:    // Data
    #define SUPPORTED_LOCALES 104
    struct localeStrings
		{
		char localeName[50];
		TInt flag;		
		};

	struct localeStrings locales[SUPPORTED_LOCALES];	
	};
#endif 
