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


// This contains CT_DataSIPReplyToHeader

#include "t_csipreplytoheader.h"
#include "t_csipaddress.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <s32file.h>

/*@{*/
_LIT(KCmdNewL,					"NewL");
_LIT(KCmdNewLC,                 "NewLC");
_LIT(KCmdDecodeL,               "DecodeL");
_LIT(KCmdInternalizeValueL,     "InternalizeValueL");
_LIT(KCmdDestructor,            "~");

_LIT(KFldSIPReplyToHeader,      "sipreplytoheader");
_LIT(KFldSIPAddress ,           "sipaddress");
_LIT(KFldHeaderValue,           "headervalue");
_LIT(KFldFileName,              "filename");

_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");
/*}@*/


CT_DataSIPReplyToHeader*  CT_DataSIPReplyToHeader::NewL()
    {
    CT_DataSIPReplyToHeader* self = new (ELeave) CT_DataSIPReplyToHeader();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;    
    }

CT_DataSIPReplyToHeader::~CT_DataSIPReplyToHeader()
    {
    DestroyData();
    }

CT_DataSIPReplyToHeader::CT_DataSIPReplyToHeader()
:   CT_DataSIPAddressHeaderBase(), iSIPReplyToHeader(NULL), iIsOwner(ETrue)
	{
	}

void CT_DataSIPReplyToHeader::ConstructL()
    {
    }

TAny* CT_DataSIPReplyToHeader::GetObject()
    {
    return iSIPReplyToHeader;
    }

void CT_DataSIPReplyToHeader::SetObjectL(TAny* aAny)
    {
    iSIPReplyToHeader = static_cast<CSIPReplyToHeader*>(aAny);
    }

void CT_DataSIPReplyToHeader::DisownObjectL()
    {
    iSIPReplyToHeader = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPReplyToHeader::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

void CT_DataSIPReplyToHeader::DestroyData()
    {
    if (iIsOwner)
        {
        delete iSIPReplyToHeader;
        iSIPReplyToHeader = NULL;
        iIsOwner = EFalse;
        }
    }


CSIPHeaderBase* CT_DataSIPReplyToHeader::GetSIPHeaderBase() const
    {
    return iSIPReplyToHeader;
    }

/**
Delegates the commands to a function

* @internalComponent
* @param aCommand Current command
* @param aSection Current ini file command section
* @param aAsyncErrorIndex index of command for SetAsyncError()
* @return TBool Returns whether the command was executed or not
*/
TBool CT_DataSIPReplyToHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
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
		retVal = CT_DataSIPAddressHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);;
		}
	return retVal;  
	}

void CT_DataSIPReplyToHeader::DoCmdNewL(const TTEFSectionName& aSection)
    {
    CSIPAddress* addr = NULL;
    if( !CT_SIPUtil::GetSIPAddressL(*this, aSection, KFldSIPAddress, addr) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPAddress());
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPReplyToHeader::NewL(CSIPAddress*)"));
        TRAPD(err, iSIPReplyToHeader = CSIPReplyToHeader::NewL(addr));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            TPtrC wrappername;
            (void) GetStringFromConfig(aSection, KFldSIPAddress, wrappername);
            CT_DataSIPAddress* wrapper = static_cast<CT_DataSIPAddress*>(GetDataWrapperL(wrappername));
            wrapper->SetIsOwner(EFalse);
            }
        }
    }

void CT_DataSIPReplyToHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    CSIPAddress* addr = NULL;
    if( !CT_SIPUtil::GetSIPAddressL(*this, aSection, KFldSIPAddress, addr) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPAddress());
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPReplyToHeader::NewLC(CSIPAddress*)"));
        TRAPD(err, iSIPReplyToHeader = CSIPReplyToHeader::NewLC(addr); CleanupStack::Pop());
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            TPtrC wrappername;
            (void) GetStringFromConfig(aSection, KFldSIPAddress, wrappername);
            CT_DataSIPAddress* wrapper = static_cast<CT_DataSIPAddress*>(GetDataWrapperL(wrappername));
            wrapper->SetIsOwner(EFalse);
            }
        }
    }

void CT_DataSIPReplyToHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPReplyToHeader::DecodeL(const TDesC8&)"));
    
    TPtrC temp;
    if( !GetStringFromConfig(aSection, KFldHeaderValue, temp) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldHeaderValue());
        SetBlockResult(EFail);
        }
    else
        {
        TPtrC wrapperName;
        if( !GetStringFromConfig(aSection, KFldSIPReplyToHeader, wrapperName) )
            {
            ERR_PRINTF2(KLogMissingParameter, &KFldSIPReplyToHeader());
            SetBlockResult(EFail);
            }
        else
            {
            TBuf8<KMaxTestExecuteCommandLength> headervalue;
            CnvUtfConverter::ConvertFromUnicodeToUtf8(headervalue, temp);
            INFO_PRINTF1(_L("call CSIPReplyToHeader::DecodeL(const TDesC8&)"));
            CSIPReplyToHeader* ret = NULL;
            TRAPD(err, ret = CSIPReplyToHeader::DecodeL(headervalue));
            
            if(KErrNone != err)
                {
                ERR_PRINTF2(KLogError, err);
                SetError(err);
                }
            else
                {
                CT_DataSIPReplyToHeader* wrapper = static_cast<CT_DataSIPReplyToHeader*>(GetDataWrapperL(wrapperName));
                wrapper->SetIsOwner(ETrue);
                SetDataObjectL(wrapperName, ret);
                }
            }
        }
    }

void CT_DataSIPReplyToHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
    {
    TPtrC filename;
    if( !GetStringFromConfig(aSection, KFldFileName, filename) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldFileName());
        SetBlockResult(EFail);
        }
    else
        {
        CDirectFileStore* store = CDirectFileStore::OpenLC(FileServer(), filename, EFileStream | EFileRead);
        TStreamId id = store->Root();
        RStoreReadStream readstream;
        readstream.OpenLC(*store, id);
        
        INFO_PRINTF1(_L("call CSIPReplyToHeader::InternalizeL(RReadStream&)"));
        CSIPHeaderBase* headerbase = NULL;
        TRAPD(err, headerbase = CSIPReplyToHeader::InternalizeValueL(readstream));
        iSIPReplyToHeader = dynamic_cast<CSIPReplyToHeader*>(headerbase);
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        
        CleanupStack::PopAndDestroy(2);
        }
    }

void CT_DataSIPReplyToHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPReplyToHeader::~CSIPReplyToHeader()"));
    DestroyData();
    }

