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


// This contains CT_DataSIPFromHeader
#include "t_csipfromheader.h"
#include "t_csipaddress.h"
#include <utf.h>
#include <s32file.h>



/*@{*/
_LIT(KDestructor,                   "~");
_LIT(KCmdDecodeL,                   "DecodeL");
_LIT(KCmdNewL,                      "NewL");
_LIT(KCmdNewLC,                     "NewLC");
_LIT(KCmdInternalizeValueL,         "InternalizeValueL");

// Fields 
_LIT(KFldSIPFromHeader,             "sipFromHeader");
_LIT(KFldHeaderValue,               "headerValue");
_LIT(KParamSIPAddress,              "sipAddress");
_LIT(KParamSIPFromToHeaderBase,     "sipFromToHeaderBase");
_LIT(KFldFileName,                  "filename");
//_LIT(KFldExpectedHeaderName,        "expectedheadername");

// Error
_LIT(KLogError,                     "Error=%d");
_LIT(KMissingParameter,             "missing parameter '%S'");
//Info

CT_DataSIPFromHeader* CT_DataSIPFromHeader::NewL()
    {
    CT_DataSIPFromHeader* self = new (ELeave) CT_DataSIPFromHeader();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }
	
CT_DataSIPFromHeader::~CT_DataSIPFromHeader()
    {
    DestroyData();
    }

void CT_DataSIPFromHeader::DestroyData()
    {
    if (iIsOwner)
        {
        delete iSIPFromHeader;
        iSIPFromHeader = NULL;
        iIsOwner = EFalse;
        }
    }

TAny* CT_DataSIPFromHeader::GetObject()
    {
    return iSIPFromHeader;
    }

void CT_DataSIPFromHeader::SetObjectL(TAny* aAny)
    {
    DestroyData();
    iSIPFromHeader = static_cast<CSIPFromHeader*> (aAny);
    }

void CT_DataSIPFromHeader::DisownObjectL()
    {
    iSIPFromHeader = NULL;
    iIsOwner = EFalse;
    }

CT_DataSIPFromHeader::CT_DataSIPFromHeader() :
CT_DataSIPFromToHeaderBase(), iSIPFromHeader(NULL), iIsOwner(ETrue)
    {
    }

void CT_DataSIPFromHeader::ConstructL()
    {
    }

void CT_DataSIPFromHeader::DoCmdDestructor()
    {
    DestroyData();
    }

CSIPHeaderBase* CT_DataSIPFromHeader::GetSIPHeaderBase() const
    {
    return iSIPFromHeader;
    }

TBool CT_DataSIPFromHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
    {
    TBool ret = ETrue;
    if (aCommand == KDestructor)
        {
        DoCmdDestructor();
        }
    else if(aCommand == KCmdDecodeL)
        {
        DoCmdDecodeL(aSection);
        }
    else if(aCommand == KCmdNewL)
        {
        DoCmdNewL(aSection);
        }
    else if(aCommand == KCmdNewLC)
        {
        DoCmdNewLC(aSection);
        }
    else if(aCommand == KCmdInternalizeValueL)
        {
        DoCmdInternalizeValueL(aSection);
        }  
    else
        {
        ret = CT_DataSIPFromToHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
        }
    return ret;
    }

void CT_DataSIPFromHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
    {
    CSIPFromHeader* sipFromHeader = NULL;
    TPtrC headerVal;
    TPtrC datSipFromHeader;
    if (!GetStringFromConfig(aSection, KFldHeaderValue, headerVal))
        {
        ERR_PRINTF2(KMissingParameter, &KFldHeaderValue());
        SetBlockResult(EFail);
        }
    else
        {
        if(!GetStringFromConfig(aSection, KFldSIPFromHeader, datSipFromHeader))
            {
            ERR_PRINTF2(KMissingParameter, &KFldSIPFromHeader());
            SetBlockResult(EFail);
            }
        else
            {
            TBuf8<KMaxTestExecuteCommandLength> headerVal8;
            CnvUtfConverter::ConvertFromUnicodeToUtf8(headerVal8, headerVal);
            INFO_PRINTF1(_L("execute CSIPFromHeader::DecodeL()"));
            TRAPD(err,sipFromHeader=CSIPFromHeader::DecodeL(headerVal8));
            if (err != KErrNone)
                {
                ERR_PRINTF2(KLogError, err);
                SetError(err);
                }
            else
                {
                CT_DataSIPFromHeader* wrapper = static_cast<CT_DataSIPFromHeader*> (GetDataWrapperL(datSipFromHeader));
                wrapper->SetIsOwner(ETrue);
                SetDataObjectL(datSipFromHeader, sipFromHeader);
                }
            }
        }
    }

void CT_DataSIPFromHeader::DoCmdNewL(const TTEFSectionName& aSection)
    {
    CSIPAddress*  sipAddress;
    CSIPFromToHeaderBase    *sipFromToHeaderBase;
    TPtrC   name;

    // Parameter of CSIPAddress type.
    if (GetStringFromConfig(aSection, KParamSIPAddress, name))
        {
        sipAddress = static_cast<CSIPAddress*>(GetDataObjectL(name));
        INFO_PRINTF1(_L("execute CSIPFromHeader::NewL(CSIPAddress *aSIPAddress)"));
        TRAPD(err,iSIPFromHeader=CSIPFromHeader::NewL(sipAddress));
        if ( err!=KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            iIsOwner = ETrue;
            CT_DataSIPAddress* wrapper = static_cast<CT_DataSIPAddress*>(GetDataWrapperL(name));
            wrapper->SetIsOwner(EFalse);
            }
        }
    // Parameter of CSIPFromToHeaderBase type.
    else if(GetStringFromConfig(aSection, KParamSIPFromToHeaderBase, name))
        {
        sipFromToHeaderBase = static_cast<CSIPFromToHeaderBase*>(GetDataObjectL(name));
        INFO_PRINTF1(_L("execute CSIPFromHeader::NewL(const CSIPFromToHeaderBase &)"));
        TRAPD(err,iSIPFromHeader=CSIPFromHeader::NewL(*sipFromToHeaderBase));
        if ( err!=KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            iIsOwner = ETrue;
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KParamSIPAddress());
        ERR_PRINTF2(KMissingParameter, &KParamSIPFromToHeaderBase());
        SetBlockResult(EFail);
        return;
        } 
    }

void CT_DataSIPFromHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    CSIPAddress*  sipAddress;
    CSIPFromToHeaderBase    *sipFromToHeaderBase;
    TPtrC   name;

    // Parameter of CSIPAddress type.
    if (GetStringFromConfig(aSection, KParamSIPAddress, name))
        {
        sipAddress = static_cast<CSIPAddress*>(GetDataObjectL(name));
        INFO_PRINTF1(_L("execute CSIPFromHeader::NewL(CSIPAddress *aSIPAddress)"));
        TRAPD(err,iSIPFromHeader=CSIPFromHeader::NewLC(sipAddress); CleanupStack::Pop());
        if ( err!=KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            iIsOwner = ETrue;
            CT_DataSIPAddress* wrapper = static_cast<CT_DataSIPAddress*>(GetDataWrapperL(name));
            wrapper->SetIsOwner(EFalse);
            }
        }
    // Parameter of CSIPFromToHeaderBase type.
    else if(GetStringFromConfig(aSection, KParamSIPFromToHeaderBase, name))
        {
        sipFromToHeaderBase = static_cast<CSIPFromToHeaderBase*>(GetDataObjectL(name));
        INFO_PRINTF1(_L("execute CSIPFromHeader::NewL(const CSIPFromToHeaderBase &)"));
        TRAPD(err,iSIPFromHeader=CSIPFromHeader::NewLC(*sipFromToHeaderBase); CleanupStack::Pop());
        if ( err!=KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            iIsOwner = ETrue;
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KParamSIPAddress());
        ERR_PRINTF2(KMissingParameter, &KParamSIPFromToHeaderBase());
        SetBlockResult(EFail);
        return;
        } 
    }

void CT_DataSIPFromHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
    {
    TPtrC datFileName;
    if ( !GetStringFromConfig(aSection, KFldFileName, datFileName) )
        {
        ERR_PRINTF2(KMissingParameter, &KFldFileName());
        SetBlockResult(EFail);
        return;
        }
    else
        {
        CDirectFileStore*   readstore = CDirectFileStore::OpenL(FileServer(), datFileName, EFileStream | EFileRead);
        CleanupStack::PushL(readstore);
        TStreamId           headerid = readstore->Root();
        RStoreReadStream    readstrm;
        
        readstrm.OpenL(*readstore, headerid);
        CleanupClosePushL(readstrm);
        // Execute command and log parameters
        INFO_PRINTF1(_L("execute CSIPFromHeader::InternalizeValueL(RReadStream &)"));
        TRAPD(err, iSIPFromHeader = (CSIPFromHeader*)CSIPFromHeader::InternalizeValueL(readstrm));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        // Cleanup
        CleanupStack::PopAndDestroy(2, readstore);
        }
    }

void CT_DataSIPFromHeader::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }
