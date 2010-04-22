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


// This contains CT_DataSIPCallIDHeader

#include "t_csipcallidheader.h"
#include <utf.h>
#include <s32file.h>

/*@{*/
_LIT(KCmdDestructor,        "~");
_LIT(KCmdDecodeL,           "DecodeL");
_LIT(KCmdInternalizeValueL, "InternalizeValueL");
_LIT(KCmdCompare,           "==");

// Fields 
_LIT(KFldSIPCallIDHeader,   "sipCallIDHeader");
_LIT(KFldHeaderValue,       "headerValue");
_LIT(KFldFileName,          "filename");
_LIT(KFldExpected,          "expected");

// Error
_LIT(KLogError,             "Error=%d");
_LIT(KMissingParameter,     "missing parameter '%S'");
 

CT_DataSIPCallIDHeader*  CT_DataSIPCallIDHeader::NewL()
    {
    CT_DataSIPCallIDHeader* self = new (ELeave) CT_DataSIPCallIDHeader();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;    
    }

CT_DataSIPCallIDHeader::~CT_DataSIPCallIDHeader()
    {
    DestroyData();
    }

CT_DataSIPCallIDHeader::CT_DataSIPCallIDHeader()
:   CT_DataSIPHeaderBase(), iSIPCallIDHeader(NULL), iIsOwner(ETrue)
    {
    }

void CT_DataSIPCallIDHeader::ConstructL()
    {
    }

void CT_DataSIPCallIDHeader::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }

void CT_DataSIPCallIDHeader::DestroyData()
    {
    if(iIsOwner && iSIPCallIDHeader)
        {
        delete iSIPCallIDHeader;
        iSIPCallIDHeader = NULL;
        }
    }

TAny* CT_DataSIPCallIDHeader::GetObject()
    {
    return iSIPCallIDHeader;
    }

void CT_DataSIPCallIDHeader::SetObjectL(TAny* aAny)
    {
    DestroyData();
    iSIPCallIDHeader = static_cast<CSIPCallIDHeader*> (aAny);
    }

void CT_DataSIPCallIDHeader::DisownObjectL()
    {
    iSIPCallIDHeader = NULL;
    iIsOwner = EFalse;
    }

CSIPHeaderBase* CT_DataSIPCallIDHeader::GetSIPHeaderBase() const
    {
    return iSIPCallIDHeader;
    }

TBool CT_DataSIPCallIDHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
    {
    TBool ret = ETrue;
    if (aCommand == KCmdDestructor)
        {
        DoCmdDestructor();
        }
    else if(aCommand == KCmdDecodeL)
        {
        DoCmdDecodeL(aSection);
        }
    else if(aCommand == KCmdCompare)
        {
        DoCmdCompareL(aSection);
        }
    else if(aCommand == KCmdInternalizeValueL)
        {
        DoCmdInternalizeValueL(aSection);
        }  
    else
        {
        ret = CT_DataSIPHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
        }
    return ret;
    }

void CT_DataSIPCallIDHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
    {
    TPtrC headerVal;
    TPtrC datSipCallIDHeader;
    if (!GetStringFromConfig(aSection, KFldHeaderValue, headerVal))
        {
        ERR_PRINTF2(KMissingParameter, &KFldHeaderValue());
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("execute CSIPCallIDHeader::DecodeL(const TDesC8 &)"));
        TBuf8<KMaxTestExecuteCommandLength> headerVal8;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(headerVal8, headerVal);
        TRAPD(err, iSIPCallIDHeader = CSIPCallIDHeader::DecodeL(headerVal8));
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    }

void CT_DataSIPCallIDHeader::DoCmdCompareL(const TTEFSectionName& aSection)
    {
    CSIPCallIDHeader * sipCallIDHeader = NULL;
    TPtrC name;
    if (!GetStringFromConfig(aSection, KFldSIPCallIDHeader, name))
        {
        ERR_PRINTF2(KMissingParameter, &KFldSIPCallIDHeader());
        SetBlockResult(EFail);
        }
    else
        {
        sipCallIDHeader = static_cast<CSIPCallIDHeader*> (GetDataObjectL(name));
        INFO_PRINTF1(_L("execute CSIPCallIDHeader::operator==(const CSIPCallIDHeader &aCallIDHeader)"));
        TBool actual = (*iSIPCallIDHeader) == (*sipCallIDHeader);
        INFO_PRINTF2(_L("operator==() = %d"), actual);        
        TBool expected = EFalse;
        if (GetBoolFromConfig(aSection, KFldExpected, expected))
            {
            if (!expected != !actual)
                {
                ERR_PRINTF3(_L("actual value is not as expected, expected: %d, actual: %d"), expected, actual);
                SetBlockResult(EFail);
                }
            }
        }
    }

void CT_DataSIPCallIDHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
    {
    TPtrC datFileName;
    TPtrC datSipCallIDHeader;
    if ( !GetStringFromConfig(aSection, KFldFileName, datFileName) )
        {
        ERR_PRINTF2(KMissingParameter, &KFldFileName());
        SetBlockResult(EFail);
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
        INFO_PRINTF1(_L("execute CSIPCallIDHeader::InternalizeValueL(RReadStream &)"));
        CSIPHeaderBase* base = NULL;
        TRAPD(err, base = CSIPCallIDHeader::InternalizeValueL(readstrm));
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            iSIPCallIDHeader = dynamic_cast<CSIPCallIDHeader*>(base);
            }
        // Cleanup
        CleanupStack::PopAndDestroy(2, readstore);
        }
    }

void CT_DataSIPCallIDHeader::DoCmdDestructor()
    {
    INFO_PRINTF1(_L("execute CSIPCallIDHeader::~CSIPCallIDHeader()"));
    DestroyData();
    }

