/*
* Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* This contains CT_DataSIPStrings
*/


#include "t_sipstrings.h"
#include <sipstrings.h>
#include <utf.h>

/*@{*/
_LIT(KCmdClose,     "Close");
_LIT(KCmdOpenL,     "OpenL");
_LIT(KCmdPool,      "Pool");
_LIT(KCmdStringF,   "StringF");
_LIT(KCmdTable,     "Table");

//Fields
_LIT(KFldIndex,     "index");

//Error
_LIT(KLogError,             "Error=%d");
_LIT(KLogMissingParameter,  "Missing parameter '%S'");

CT_DataSIPStrings::CT_DataSIPStrings()
:   CDataWrapperBase()
    {
    }

CT_DataSIPStrings::~CT_DataSIPStrings()
    {    
    }

void CT_DataSIPStrings::ConstructL()
    {
    }

CT_DataSIPStrings* CT_DataSIPStrings::NewL()
    {
    CT_DataSIPStrings* self = new (ELeave)CT_DataSIPStrings();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

TAny* CT_DataSIPStrings::GetObject()
    {
    return NULL;
    }

TBool CT_DataSIPStrings::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
	{
	TBool ret = ETrue;

	if ( aCommand==KCmdOpenL )
		{
		DoCmdOpenL(aSection);
		}
    else if ( aCommand==KCmdClose )
        {
        DoCmdClose(aSection);
        }
    else if ( aCommand==KCmdPool )
        {
        DoCmdPool(aSection);
        }
    else if ( aCommand==KCmdStringF )
        {
        DoCmdStringF(aSection);
        }
    else if ( aCommand==KCmdTable )
        {
        DoCmdTable(aSection);
        }
	else
		{
		ret = EFalse;
		}
	return ret;
    }

void CT_DataSIPStrings::DoCmdClose(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call SIPStrings::Close()"));
    SIPStrings::Close();
    }

void CT_DataSIPStrings::DoCmdOpenL(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call SIPStrings::OpenL()"));
    TRAPD(err, SIPStrings::OpenL());
    
    if (KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void CT_DataSIPStrings::DoCmdPool(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call SIPStrings::Pool()"));
    RStringPool ret = SIPStrings::Pool();
    }

void CT_DataSIPStrings::DoCmdStringF(const TTEFSectionName& aSection)
    {
    TInt index = 0;
    if( !GetIntFromConfig(aSection, KFldIndex, index) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldIndex);
        SetBlockResult(EFail);
        }
    else
        {        
        INFO_PRINTF1(_L("call SIPStrings::StringF(TInt)"));
        
        RStringF ret = SIPStrings::StringF(index);
        TBuf<32> temp;
        CnvUtfConverter::ConvertToUnicodeFromUtf8(temp, ret.DesC());
        INFO_PRINTF1(temp);
        }
    }

void CT_DataSIPStrings::DoCmdTable(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call SIPStrings::Table()"));
    const TStringTable& ret = SIPStrings::Table();
    }

