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

// This contains CT_DataSIPAllowHeader
#include "t_csipallowheader.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <s32file.h>

/*@{*/
_LIT(KCmdNewL,                  "NewL");
_LIT(KCmdNewLC,                 "NewLC");
_LIT(KCmdDecodeL,               "DecodeL");
_LIT(KCmdInternalizeValueL,     "InternalizeValueL");
_LIT(KCmdDestructor,            "~");

_LIT(KFldFileName,              "filename");
_LIT(KFldValue,                 "value");
_LIT(KFldAllowHeader,           "allowheader");

_LIT(KFormatFieldNumber,        "%S%d");

_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");
/*}@*/

CT_DataSIPAllowHeader* CT_DataSIPAllowHeader::NewL()
    {
    CT_DataSIPAllowHeader* self = new (ELeave) CT_DataSIPAllowHeader();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

CT_DataSIPAllowHeader::~CT_DataSIPAllowHeader()
    {
    DestroyData();
    }

CT_DataSIPAllowHeader::CT_DataSIPAllowHeader() :
    CT_DataSIPTokenHeaderBase(), iSIPAllowHeader(NULL), iIsOwner(EFalse)
    {
    }

void CT_DataSIPAllowHeader::ConstructL()
    {
    }

TAny* CT_DataSIPAllowHeader::GetObject()
    {
    return iSIPAllowHeader;
    }

void CT_DataSIPAllowHeader::SetObjectL(TAny* aAny)
    {
    iSIPAllowHeader = static_cast<CSIPAllowHeader*> (aAny);
    }

void CT_DataSIPAllowHeader::DisownObjectL()
    {
    iSIPAllowHeader = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPAllowHeader::DestroyData()
    {
    if (iIsOwner)
        {
        delete iSIPAllowHeader;
        iSIPAllowHeader = NULL;
        iIsOwner = EFalse;
        }
    }

CSIPHeaderBase* CT_DataSIPAllowHeader::GetSIPHeaderBase() const
    {
    return iSIPAllowHeader;
    }

CSIPTokenHeaderBase* CT_DataSIPAllowHeader::GetSIPTokenHeaderBase() const
    {
    return iSIPAllowHeader;
    }

/**
 Delegates the commands to a function

 * @internalComponent
 * @param aCommand Current command
 * @param aSection Current ini file command section
 * @param aAsyncErrorIndex index of command for SetAsyncError()
 * @return TBool Returns whether the command was executed or not
 */
TBool CT_DataSIPAllowHeader::DoCommandL(const TTEFFunction& aCommand,
        const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
    {
    TBool retVal = ETrue;

    if (aCommand == KCmdNewL)
        {
        DoCmdNewL(aSection);
        }
    else if (aCommand == KCmdNewLC)
        {
        DoCmdNewLC(aSection);
        }
    else if (aCommand == KCmdDecodeL)
        {
        DoCmdDecodeL(aSection);
        }
    else if (aCommand == KCmdInternalizeValueL)
        {
        DoCmdInternalizeValueL(aSection);
        }
    else if (aCommand == KCmdDestructor)
        {
        DoCmdDestructor(aSection);
        }
    else
        {
        retVal = CT_DataSIPTokenHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);;
        }
    return retVal;
    }

void CT_DataSIPAllowHeader::DoCmdNewL(const TTEFSectionName& aSection)
    {
    RStringF value;
    if (!CT_SIPUtil::GetStringF(*this, aSection, KFldValue, value))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldValue);
        SetBlockResult(EFail);
        return;
        }

    INFO_PRINTF1(_L("call CSIPAllowHeader::NewL(RStringF)"));
    TRAPD(err, iSIPAllowHeader = CSIPAllowHeader::NewL(value));

    if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    iIsOwner = err == KErrNone;
    }

void CT_DataSIPAllowHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    RStringF value;
    if (!CT_SIPUtil::GetStringF(*this, aSection, KFldValue, value))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldValue);
        SetBlockResult(EFail);
        return;
        }

    INFO_PRINTF1(_L("call CSIPAllowHeader::NewLC(RStringF)"));
    TRAPD(err, iSIPAllowHeader = CSIPAllowHeader::NewLC(value); CleanupStack::Pop(iSIPAllowHeader));

    if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    iIsOwner = err == KErrNone;
    }

void CT_DataSIPAllowHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
    {
    TPtrC temp;
    if( !GetStringFromConfig(aSection, KFldValue, temp) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldValue);
        SetBlockResult(EFail);
        return;
        }
    TBuf8<KMaxTestExecuteCommandLength> value;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(value, temp);
    INFO_PRINTF1(_L("call CSIPAllowHeader::DecodeL(const TDesC8&)"));
    RPointerArray<CSIPAllowHeader> ret;
    TRAPD(err, ret = CSIPAllowHeader::DecodeL(value));

    if (KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        return;
        }

    TInt cnt = ret.Count();
    INFO_PRINTF2(_L("%d CSIPAllowHeader objects got from DecodeL()"), cnt);
    TBool moreData = ETrue;
    TBuf<KMaxTestExecuteNameLength> tempStore;
    TInt index = 1;
    while (moreData && index <= cnt)
        {
        TPtrC name;
        tempStore.Format(KFormatFieldNumber, &KFldAllowHeader, index);
        if (GetStringFromConfig(aSection, tempStore, name))
            {
            SetDataObjectL(name, ret[index - 1]);
            CT_DataSIPAllowHeader* wrapper = (CT_DataSIPAllowHeader*) GetDataWrapperL(name);
            wrapper->SetIsOwner(ETrue);
            ++index;
            }
        else
            {
            moreData = EFalse;
            }
        }
    // Destroy unstored ones.
    for (--index; index < cnt; ++index)
        {
        delete ret[index];
        }
    ret.Close();
    }

void CT_DataSIPAllowHeader::DoCmdInternalizeValueL(
        const TTEFSectionName& aSection)
    {
    TPtrC filename;
    if (!GetStringFromConfig(aSection, KFldFileName, filename))
        {
        ERR_PRINTF2(KLogMissingParameter, KFldFileName);
        SetBlockResult(EFail);
        }
    else
        {
        // ReadStore creation
        CDirectFileStore* store = CDirectFileStore::OpenLC(FileServer(),
                filename, EFileStream | EFileRead);
        TStreamId id = store->Root();
        RStoreReadStream readstream;
        readstream.OpenLC(*store, id);

        INFO_PRINTF1(_L("call CSIPAllowHeader::InternalizeL(RReadStream&)"));
        CSIPHeaderBase* headerbase = NULL;
        TRAPD(err, headerbase = CSIPAllowHeader::InternalizeValueL(readstream));
        delete iSIPAllowHeader;
        iSIPAllowHeader = dynamic_cast<CSIPAllowHeader*> (headerbase);

        if (KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }

        CleanupStack::PopAndDestroy(2);
        }
    }

void CT_DataSIPAllowHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPAllowHeader::~CSIPAllowHeader()"));
    DestroyData();
    }

void CT_DataSIPAllowHeader::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }
