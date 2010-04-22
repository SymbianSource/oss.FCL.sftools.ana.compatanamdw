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


// This contains CT_DataSIPRouteHeader

#include "t_csiprouteheader.h"
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

//_LIT(KFldSIPRouteHeader,        "siprouteheader");
_LIT(KFldSIPAddress ,           "sipaddress");
_LIT(KFldFileName,              "filename");
//_LIT(KFldExpected,              "expected");
_LIT(KFldValue,                   "Value");
_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");
//_LIT(KLogNotExpectedValue,      "Not expected value, actual=%d, expect=%d");
/*}@*/


CT_DataSIPRouteHeader*  CT_DataSIPRouteHeader::NewL()
    {
    CT_DataSIPRouteHeader* self = new (ELeave) CT_DataSIPRouteHeader();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;    
    }

CT_DataSIPRouteHeader::~CT_DataSIPRouteHeader()
    {
    DestroyData();
    }

CT_DataSIPRouteHeader::CT_DataSIPRouteHeader()
:   CT_DataSIPRouteHeaderBase(), iSIPRouteHeader(NULL), iIsOwner(ETrue)
	{
	}

void CT_DataSIPRouteHeader::ConstructL()
    {
    }

TAny* CT_DataSIPRouteHeader::GetObject()
    {
    return iSIPRouteHeader;
    }

void CT_DataSIPRouteHeader::SetObjectL(TAny* aAny)
    {
    iSIPRouteHeader = static_cast<CSIPRouteHeader*>(aAny);
    }

void CT_DataSIPRouteHeader::DisownObjectL()
    {
    iSIPRouteHeader = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPRouteHeader::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

void CT_DataSIPRouteHeader::DestroyData()
    {
    if (iIsOwner)
        {
        delete iSIPRouteHeader;
        iSIPRouteHeader = NULL;
        iIsOwner = EFalse;
        }
    }


CSIPHeaderBase* CT_DataSIPRouteHeader::GetSIPHeaderBase() const
    {
    return iSIPRouteHeader;
    }

/**
Delegates the commands to a function

* @internalComponent
* @param aCommand Current command
* @param aSection Current ini file command section
* @param aAsyncErrorIndex index of command for SetAsyncError()
* @return TBool Returns whether the command was executed or not
*/
TBool CT_DataSIPRouteHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
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
		retVal = CT_DataSIPRouteHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);;
		}
	return retVal;  
	}

void CT_DataSIPRouteHeader::DoCmdNewL(const TTEFSectionName& aSection)
    {
    CSIPAddress* addr = NULL;
    if( !CT_SIPUtil::GetSIPAddressL(*this, aSection, KFldSIPAddress, addr) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSIPAddress);
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPRouteHeader::NewL(CSIPAddress*)"));
        TRAPD(err, iSIPRouteHeader = CSIPRouteHeader::NewL(addr));
        
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

void CT_DataSIPRouteHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    CSIPAddress* addr = NULL;
    if( !CT_SIPUtil::GetSIPAddressL(*this, aSection, KFldSIPAddress, addr) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSIPAddress);
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPRouteHeader::NewLC(CSIPAddress*)"));
        TRAPD(err, iSIPRouteHeader = CSIPRouteHeader::NewLC(addr); CleanupStack::Pop());
        
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

void CT_DataSIPRouteHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
    {
    delete iSIPRouteHeader;
    iSIPRouteHeader = NULL;
    
    TPtrC str;
     if(!GetStringFromConfig(aSection, KFldValue, str))
         {
         ERR_PRINTF2(KLogMissingParameter, &KFldValue());
         SetBlockResult(EFail);
         return;
         }
     
     TBuf8<KMaxTestExecuteCommandLength> value;
     CnvUtfConverter::ConvertFromUnicodeToUtf8(value, str);
     INFO_PRINTF1(_L("call CSIPRouteHeader::DecodeL(const TDesC8 &)")); 
     TRAPD(err, iSIPRouteHeader = (CSIPRouteHeader::DecodeL(value)[0]));
     if(KErrNone != err)
         {
         ERR_PRINTF2(KLogError, err);
         SetError(err);
         } 
    }

void CT_DataSIPRouteHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
    {
    delete iSIPRouteHeader;
    iSIPRouteHeader = NULL;
    
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
        INFO_PRINTF1(_L("execute CSIPRouteHeader::InternalizeValueL(RReadStream &)"));
        CSIPHeaderBase* base = NULL;
        TRAPD(err, base = CSIPRouteHeader::InternalizeValueL(readstrm));
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            iSIPRouteHeader = dynamic_cast<CSIPRouteHeader*>(base);
            }
        // Cleanup
        CleanupStack::PopAndDestroy(2, readstore);
        }  
    }

void CT_DataSIPRouteHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPRouteHeader::~CSIPRouteHeader()"));
    DestroyData();
    }
