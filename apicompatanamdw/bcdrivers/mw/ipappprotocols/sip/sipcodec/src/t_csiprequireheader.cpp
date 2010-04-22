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


// This contains CT_DataSIPRequireHeader

#include "t_csiprequireheader.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <s32file.h>

//  Epoc Includes

/*@{*/
_LIT(KCmdNewL,                              "NewL");
_LIT(KCmdNewLC,                             "NewLC");
_LIT(KCmdDecodeL,                           "DecodeL");
_LIT(KCmdInternalizeValueL,                 "InternalizeValueL");
_LIT(KCmdDestructor,                        "~");


_LIT(KFldValue,                             "value");
_LIT(KFldFileName,                          "filename");
_LIT(KFldRequireHeader,                     "requireheader");

_LIT(KFormatFieldNumber,                    "%S%d");

_LIT(KLogError,                             "Error=%d");
_LIT(KLogMissingParameter,                  "Missing parameter '%S'");
/*@}*/

CT_DataSIPRequireHeader* CT_DataSIPRequireHeader::NewL()
    {
    CT_DataSIPRequireHeader* ret=new (ELeave) CT_DataSIPRequireHeader();
    CleanupStack::PushL(ret);
    ret->ConstructL();
    CleanupStack::Pop(ret);
    return ret;
    }

CT_DataSIPRequireHeader::CT_DataSIPRequireHeader():CT_DataSIPTokenHeaderBase(), iIsOwner(EFalse)
    {
    }

void CT_DataSIPRequireHeader::ConstructL()
    {
    }

CT_DataSIPRequireHeader::~CT_DataSIPRequireHeader()
    {
    DestroyData();
    }

/**
* Return a pointer to the object that the data wraps
*
* @return pointer to the object that the data wraps
*/
TAny* CT_DataSIPRequireHeader::GetObject()
    {
    return iSIPRequireHeader;
    }

void CT_DataSIPRequireHeader::SetObjectL(TAny* aAny)
    {
    iSIPRequireHeader=static_cast<CSIPRequireHeader*> (aAny);
    }

void CT_DataSIPRequireHeader::DisownObjectL()
    {
    iSIPRequireHeader=NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPRequireHeader::DestroyData()
    {
    if (iIsOwner)
        {
        delete iSIPRequireHeader;
        iSIPRequireHeader = NULL;
        iIsOwner = EFalse;
        }
    }

CSIPHeaderBase* CT_DataSIPRequireHeader::GetSIPHeaderBase() const
    {
    return iSIPRequireHeader;
    }

CSIPTokenHeaderBase* CT_DataSIPRequireHeader::GetSIPTokenHeaderBase() const
    {
    return iSIPRequireHeader;
    }

/**
Delegates the commands to a function

* @internalComponent
* @param aCommand Current command
* @param aSection Current ini file command section
* @param aAsyncErrorIndex index of command for SetAsyncError()
* @return TBool Returns whether the command was executed or not
*/
TBool CT_DataSIPRequireHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
    {
    TBool   retVal = ETrue;
    
    if( aCommand == KCmdDestructor )
        {
        DoCmdDestructor(aSection);
        }
    else if (aCommand == KCmdDecodeL)
        {
        DoCmdDecodeL(aSection);
        }
    else if (aCommand == KCmdInternalizeValueL)
        {
        DoCmdInternalizeValueL(aSection);
        }
    else if (aCommand == KCmdNewL)
        {
        DoCmdNewL(aSection);
        }
    else if (aCommand == KCmdNewLC)
        {
        DoCmdNewLC(aSection);
        }
     else
        {
        retVal = CT_DataSIPTokenHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
        }
    return retVal;  
    }

void  CT_DataSIPRequireHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
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
    INFO_PRINTF1(_L("call CSIPRequireHeader::DecodeL(const TDesC8&)"));
    RPointerArray<CSIPRequireHeader> ret;
    TRAPD(err, ret = CSIPRequireHeader::DecodeL(value));

    if (KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        return;
        }

    TInt cnt = ret.Count();
    INFO_PRINTF2(_L("%d CSIPRequireHeader objects got from DecodeL()"), cnt);
    TBool moreData = ETrue;
    TBuf<KMaxTestExecuteNameLength> tempStore;
    TInt index = 1;
    while (moreData && index <= cnt)
        {
        TPtrC name;
        tempStore.Format(KFormatFieldNumber, &KFldRequireHeader, index);
        if (GetStringFromConfig(aSection, tempStore, name))
            {
            SetDataObjectL(name, ret[index - 1]);
            CT_DataSIPRequireHeader* wrapper = (CT_DataSIPRequireHeader*) GetDataWrapperL(name);
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

void  CT_DataSIPRequireHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
    {
    TPtrC datFileName;
    if( !GetStringFromConfig(aSection, KFldFileName, datFileName) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldFileName);
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
        
        INFO_PRINTF1(_L("call CSIPRequireHeader::InternalizeValueL(RReadStream&)"));
        TRAPD(err, iSIPRequireHeader = (CSIPRequireHeader*)CSIPRequireHeader::InternalizeValueL(readstrm));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        iIsOwner = err == KErrNone;
        CleanupStack::PopAndDestroy(2);
        }
    }

void  CT_DataSIPRequireHeader::DoCmdNewL(const TTEFSectionName& aSection)
    {
    RStringF value;
    if (!CT_SIPUtil::GetStringF(*this, aSection, KFldValue, value))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldValue);
        SetBlockResult(EFail);
        return;
        }

    INFO_PRINTF1(_L("call CSIPRequireHeader::NewL(RStringF)"));
    TRAPD(err, iSIPRequireHeader = CSIPRequireHeader::NewL(value));

    if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    iIsOwner = err == KErrNone;
    }

void  CT_DataSIPRequireHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    RStringF value;
    if (!CT_SIPUtil::GetStringF(*this, aSection, KFldValue, value))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldValue);
        SetBlockResult(EFail);
        return;
        }

    INFO_PRINTF1(_L("call CSIPRequireHeader::NewLC(RStringF)"));
    TRAPD(err, iSIPRequireHeader = CSIPRequireHeader::NewLC(value); CleanupStack::Pop(iSIPRequireHeader));

    if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    iIsOwner = err == KErrNone;
    }

void CT_DataSIPRequireHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPRequireHeader::~CSIPRequireHeader()"));
    DestroyData();
    }

void CT_DataSIPRequireHeader::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }
