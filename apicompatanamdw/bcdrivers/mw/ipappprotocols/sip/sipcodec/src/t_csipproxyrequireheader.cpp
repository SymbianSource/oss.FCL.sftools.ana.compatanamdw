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
 *
*/


// This contains CT_DataSIPProxyRequireHeader

#include "t_csipproxyrequireheader.h"
#include "t_csipaddress.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <s32file.h>

/*@{*/
//Commands
_LIT(KCmdNewL,					"NewL");
_LIT(KCmdNewLC,                 "NewLC");
_LIT(KCmdDecodeL,               "DecodeL");
_LIT(KCmdInternalizeValueL,     "InternalizeValueL");
_LIT(KCmdDestructor,            "~");
//Fields
_LIT(KFldFileName,              "filename");
_LIT(KFldValue,                   "Value");
_LIT(KFldRStringFMethod,          "stringfmethod");
//Logs
_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");

/*}@*/


CT_DataSIPProxyRequireHeader*  CT_DataSIPProxyRequireHeader::NewL()
    {
    CT_DataSIPProxyRequireHeader* self = new (ELeave) CT_DataSIPProxyRequireHeader();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;    
    }

CT_DataSIPProxyRequireHeader::~CT_DataSIPProxyRequireHeader()
    {
    DestroyData();
    }

CT_DataSIPProxyRequireHeader::CT_DataSIPProxyRequireHeader()
:   CT_DataSIPTokenHeaderBase(), iSIPProxyRequireHeader(NULL), iIsOwner(ETrue)
	{
	}

void CT_DataSIPProxyRequireHeader::ConstructL()
    {
    }

TAny* CT_DataSIPProxyRequireHeader::GetObject()
    {
    return iSIPProxyRequireHeader;
    }

void CT_DataSIPProxyRequireHeader::SetObjectL(TAny* aAny)
    {
    iSIPProxyRequireHeader = static_cast<CSIPProxyRequireHeader*>(aAny);
    }

void CT_DataSIPProxyRequireHeader::DisownObjectL()
    {
    iSIPProxyRequireHeader = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPProxyRequireHeader::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

void CT_DataSIPProxyRequireHeader::DestroyData()
    {
    if (iIsOwner)
        {
        delete iSIPProxyRequireHeader;
        iSIPProxyRequireHeader = NULL;
        iIsOwner = EFalse;
        }
    }

CSIPTokenHeaderBase* CT_DataSIPProxyRequireHeader::GetSIPTokenHeaderBase() const
    {
    return iSIPProxyRequireHeader;
    }

CSIPHeaderBase* CT_DataSIPProxyRequireHeader::GetSIPHeaderBase() const
    {
    return iSIPProxyRequireHeader;
    }


/**
Delegates the commands to a function

* @internalComponent
* @param aCommand Current command
* @param aSection Current ini file command section
* @param aAsyncErrorIndex index of command for SetAsyncError()
* @return TBool Returns whether the command was executed or not
*/
TBool CT_DataSIPProxyRequireHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
	{
	TBool	retVal = ETrue;

    if( aCommand == KCmdNewL )
        {
        DoCmdNewL(aSection);
        }
    else if( aCommand == KCmdNewLC )
        {
        DoCmdNewLC(aSection);
        }
    else if( aCommand == KCmdDecodeL )
        {
        DoCmdDecodeL(aSection);
        }
    else if( aCommand == KCmdInternalizeValueL)
        {
        DoCmdInternalizeValueL(aSection);
        }
    else if( aCommand == KCmdDestructor)
        {
        DoCmdDestructor(aSection);
        }
	else
		{
		retVal = CT_DataSIPTokenHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);;
		}
	return retVal;  
	}

void CT_DataSIPProxyRequireHeader::DoCmdNewL(const TTEFSectionName& aSection)
    {
    RStringF strfmethod;
    if (!CT_SIPUtil::GetStringF(*this, aSection, KFldRStringFMethod, strfmethod))
           {
           ERR_PRINTF2(KLogMissingParameter, &KFldRStringFMethod());
           SetBlockResult(EFail);
           return;
           }
    else
        {
        INFO_PRINTF1(_L("call CSIPProxyRequireHeader::NewL(RStringF)"));
        TRAPD(err, iSIPProxyRequireHeader = CSIPProxyRequireHeader::NewL(strfmethod));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    

    }

void CT_DataSIPProxyRequireHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    RStringF strfmethod;
    if (!CT_SIPUtil::GetStringF(*this, aSection, KFldRStringFMethod, strfmethod))
           {
           ERR_PRINTF2(KLogMissingParameter, &KFldRStringFMethod());
           SetBlockResult(EFail);
           return;
           }
    else
        {
        INFO_PRINTF1(_L("call CSIPProxyRequireHeader::NewLC(RStringF)"));
        TRAPD(err, iSIPProxyRequireHeader = CSIPProxyRequireHeader::NewLC(strfmethod); CleanupStack::Pop(iSIPProxyRequireHeader));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    }

void CT_DataSIPProxyRequireHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
    {
    delete iSIPProxyRequireHeader;
    iSIPProxyRequireHeader = NULL;
    
    TPtrC str;
     if(!GetStringFromConfig(aSection, KFldValue, str))
         {
         ERR_PRINTF2(KLogMissingParameter, &KFldValue());
         SetBlockResult(EFail);
         return;
         }
     
     TBuf8<KMaxTestExecuteCommandLength> value;
     CnvUtfConverter::ConvertFromUnicodeToUtf8(value, str);
     INFO_PRINTF1(_L("call CSIPProxyRequireHeader::DecodeL(const TDesC8 &)")); 
     TRAPD(err, iSIPProxyRequireHeader = (CSIPProxyRequireHeader::DecodeL(value)[0]));
     if(KErrNone != err)
         {
         ERR_PRINTF2(KLogError, err);
         SetError(err);
         } 
    }

void CT_DataSIPProxyRequireHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
    {
    delete iSIPProxyRequireHeader;
    iSIPProxyRequireHeader = NULL;
    
    TPtrC FileName;
    if ( !GetStringFromConfig(aSection, KFldFileName, FileName) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldFileName);
        SetBlockResult(EFail);
        }
    else
        {
        CDirectFileStore*   readstore = CDirectFileStore::OpenL(FileServer(), FileName, EFileStream | EFileRead);
        CleanupStack::PushL(readstore);
        TStreamId           headerid = readstore->Root();
        RStoreReadStream    readstrm;

        readstrm.OpenL(*readstore, headerid);
        CleanupClosePushL(readstrm);
        // Execute command and log parameters
        INFO_PRINTF1(_L("execute CSIPProxyRequireHeader::InternalizeValueL(RReadStream &)"));
        CSIPHeaderBase* base = NULL;
        TRAPD(err, base = CSIPProxyRequireHeader::InternalizeValueL(readstrm));
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            iSIPProxyRequireHeader = dynamic_cast<CSIPProxyRequireHeader*>(base);
            }
        // Cleanup
        CleanupStack::PopAndDestroy(2, readstore);
        }  
    }

void CT_DataSIPProxyRequireHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPProxyRequireHeader::~CSIPProxyRequireHeader()"));
    DestroyData();
    }
