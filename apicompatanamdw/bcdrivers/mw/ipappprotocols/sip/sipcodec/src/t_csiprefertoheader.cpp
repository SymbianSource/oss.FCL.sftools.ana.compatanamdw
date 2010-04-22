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


// This contains CT_DataSIPReferToHeader

#include "t_csiprefertoheader.h"
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

_LIT(KFldSIPReferToHeader,      "siprefertoheader");
_LIT(KFldSIPAddress ,           "sipaddress");
_LIT(KFldHeaderValue,           "headervalue");
_LIT(KFldFileName,              "filename");

_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");
//_LIT(KLogNotExpectedValue,      "Not expected value, actual=%d, expect=%d");
/*}@*/


CT_DataSIPReferToHeader*  CT_DataSIPReferToHeader::NewL()
    {
    CT_DataSIPReferToHeader* self = new (ELeave) CT_DataSIPReferToHeader();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;    
    }

CT_DataSIPReferToHeader::~CT_DataSIPReferToHeader()
    {
    DestroyData();
    }

CT_DataSIPReferToHeader::CT_DataSIPReferToHeader()
:   CT_DataSIPAddressHeaderBase(), iSIPReferToHeader(NULL), iIsOwner(ETrue)
	{
	}

void CT_DataSIPReferToHeader::ConstructL()
    {
    }

TAny* CT_DataSIPReferToHeader::GetObject()
    {
    return iSIPReferToHeader;
    }

void CT_DataSIPReferToHeader::SetObjectL(TAny* aAny)
    {
    iSIPReferToHeader = static_cast<CSIPReferToHeader*>(aAny);
    }

void CT_DataSIPReferToHeader::DisownObjectL()
    {
    iSIPReferToHeader = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPReferToHeader::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

void CT_DataSIPReferToHeader::DestroyData()
    {
    if (iIsOwner)
        {
        delete iSIPReferToHeader;
        iSIPReferToHeader = NULL;
        iIsOwner = EFalse;
        }
    }


CSIPHeaderBase* CT_DataSIPReferToHeader::GetSIPHeaderBase() const
    {
    return iSIPReferToHeader;
    }

/**
Delegates the commands to a function

* @internalComponent
* @param aCommand Current command
* @param aSection Current ini file command section
* @param aAsyncErrorIndex index of command for SetAsyncError()
* @return TBool Returns whether the command was executed or not
*/
TBool CT_DataSIPReferToHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
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

void CT_DataSIPReferToHeader::DoCmdNewL(const TTEFSectionName& aSection)
    {
    CSIPAddress* addr = NULL;
    if( !CT_SIPUtil::GetSIPAddressL(*this, aSection, KFldSIPAddress, addr) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSIPAddress);
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPReferToHeader::NewL(CSIPAddress*)"));
        TRAPD(err, iSIPReferToHeader = CSIPReferToHeader::NewL(addr));
        
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

void CT_DataSIPReferToHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    CSIPAddress* addr = NULL;
    if( !CT_SIPUtil::GetSIPAddressL(*this, aSection, KFldSIPAddress, addr) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSIPAddress);
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPReferToHeader::NewLC(CSIPAddress*)"));
        TRAPD(err, iSIPReferToHeader = CSIPReferToHeader::NewLC(addr); CleanupStack::Pop());
        
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

void CT_DataSIPReferToHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPReferToHeader::DecodeL(const TDesC8&)"));
    
    TPtrC temp;
    if( !GetStringFromConfig(aSection, KFldHeaderValue, temp) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldHeaderValue);
        SetBlockResult(EFail);
        }
    else
        {
        TPtrC wrapperName;
        if( !GetStringFromConfig(aSection, KFldSIPReferToHeader, wrapperName) )
            {
            ERR_PRINTF2(KLogMissingParameter, KFldSIPReferToHeader);
            SetBlockResult(EFail);
            }
        else
            {
            TBuf8<KMaxTestExecuteCommandLength> headervalue;
            CnvUtfConverter::ConvertFromUnicodeToUtf8(headervalue, temp);
            INFO_PRINTF1(_L("call CSIPReferToHeader::DecodeL(const TDesC8&)"));
            CSIPReferToHeader* ret = NULL;
            TRAPD(err, ret = CSIPReferToHeader::DecodeL(headervalue));
            
            if(KErrNone != err)
                {
                ERR_PRINTF2(KLogError, err);
                SetError(err);
                }
            else
                {
                CT_DataSIPReferToHeader* wrapper = static_cast<CT_DataSIPReferToHeader*>(GetDataWrapperL(wrapperName));
                wrapper->SetIsOwner(ETrue);
                SetDataObjectL(wrapperName, ret);
                }
            }
        }
    }

void CT_DataSIPReferToHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
    {
    TPtrC filename;
    if( !GetStringFromConfig(aSection, KFldFileName, filename) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldFileName);
        SetBlockResult(EFail);
        }
    else
        {
        // ReadStore creation
        CDirectFileStore* store = CDirectFileStore::OpenLC(FileServer(), filename, EFileStream | EFileRead);
        TStreamId id = store->Root();
        RStoreReadStream readstream;
        readstream.OpenLC(*store, id);
        
        INFO_PRINTF1(_L("call CSIPReferToHeader::InternalizeL(RReadStream&)"));
        CSIPHeaderBase* headerbase;
        TRAPD(err, headerbase = CSIPReferToHeader::InternalizeValueL(readstream));
        iSIPReferToHeader = dynamic_cast<CSIPReferToHeader*>(headerbase);
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        
        CleanupStack::PopAndDestroy(2);
        }
    }

void CT_DataSIPReferToHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPReferToHeader::~CSIPReferToHeader()"));
    DestroyData();
    }

