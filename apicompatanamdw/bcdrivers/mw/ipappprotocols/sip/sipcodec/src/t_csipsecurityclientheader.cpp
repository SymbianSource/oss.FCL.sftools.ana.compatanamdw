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


// This contains CT_DataSIPSecurityClientHeader

#include "t_csipsecurityclientheader.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <s32file.h>

/*@{*/
_LIT(KCmdNewL,                  "NewL");
_LIT(KCmdNewLC,                 "NewLC");
_LIT(KCmdDecodeL,               "DecodeL");
_LIT(KCmdInternalizeValueL,     "InternalizeValueL");
_LIT(KCmdDestructor,            "~");

_LIT(KFldMechanism,             "mechanism");
_LIT(KFldValue,                 "Value");
_LIT(KFldSecurityClientHeader,  "securityclientheader");
_LIT(KFldFileName,              "filename");

_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");
_LIT(KFormatFieldNumber,        "%S%d");
/*}@*/


CT_DataSIPSecurityClientHeader*  CT_DataSIPSecurityClientHeader::NewL()
    {
    CT_DataSIPSecurityClientHeader* self = new (ELeave) CT_DataSIPSecurityClientHeader();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;    
    }

CT_DataSIPSecurityClientHeader::~CT_DataSIPSecurityClientHeader()
    {
    DestroyData();
    }

CT_DataSIPSecurityClientHeader::CT_DataSIPSecurityClientHeader()
:   CT_DataSIPSecurityHeaderBase(), iSIPSecurityClientHeader(NULL), iIsOwner(ETrue)
    {
    }

void CT_DataSIPSecurityClientHeader::ConstructL()
    {
    }

TAny* CT_DataSIPSecurityClientHeader::GetObject()
    {
    return iSIPSecurityClientHeader;
    }

void CT_DataSIPSecurityClientHeader::SetObjectL(TAny* aAny)
    {
    iSIPSecurityClientHeader = static_cast<CSIPSecurityClientHeader*>(aAny);
    }

void CT_DataSIPSecurityClientHeader::DisownObjectL()
    {
    iSIPSecurityClientHeader = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPSecurityClientHeader::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

void CT_DataSIPSecurityClientHeader::DestroyData()
    {
    if (iIsOwner)
        {
        delete iSIPSecurityClientHeader;
        iSIPSecurityClientHeader = NULL;
        iIsOwner = EFalse;
        }
    }


CSIPHeaderBase* CT_DataSIPSecurityClientHeader::GetSIPHeaderBase() const
    {
    return iSIPSecurityClientHeader;
    }

/**
Delegates the commands to a function

* @internalComponent
* @param aCommand Current command
* @param aSection Current ini file command section
* @param aAsyncErrorIndex index of command for SetAsyncError()
* @return TBool Returns whether the command was executed or not
*/
TBool CT_DataSIPSecurityClientHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
    {
    TBool   retVal = ETrue;

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
        retVal = CT_DataSIPSecurityHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);;
        }
    return retVal;  
    }

void CT_DataSIPSecurityClientHeader::DoCmdNewL(const TTEFSectionName& aSection)
    {
    TPtrC str;
    if(!GetStringFromConfig(aSection, KFldMechanism, str))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldMechanism());
        SetBlockResult(EFail);
        return;
        }
    
    TBuf8<KMaxTestExecuteCommandLength> mechanism;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(mechanism, str);
    
    INFO_PRINTF1(_L("call CSIPSecurityClientHeader::NewL(const TDesC8 &)"));
    
    TRAPD(err, iSIPSecurityClientHeader = CSIPSecurityClientHeader::NewL(mechanism));
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }   
    }

void CT_DataSIPSecurityClientHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    TPtrC str;
    if(!GetStringFromConfig(aSection, KFldMechanism, str))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldMechanism());
        SetBlockResult(EFail);
        return;
        }
    
    TBuf8<KMaxTestExecuteCommandLength> mechanism;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(mechanism, str);
    
    INFO_PRINTF1(_L("call CSIPSecurityClientHeader::NewLC(const TDesC8 &)"));
    
    TRAPD(err, iSIPSecurityClientHeader = CSIPSecurityClientHeader::NewLC(mechanism); CleanupStack::Pop());
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }   
    }

void CT_DataSIPSecurityClientHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
    {
     TPtrC temp;
     if( !GetStringFromConfig(aSection, KFldValue, temp) )
         {
         ERR_PRINTF2(KLogMissingParameter, &KFldValue);
         SetBlockResult(EFail);
         }
     else
         {
         TBuf8<KMaxTestExecuteCommandLength> value;
         CnvUtfConverter::ConvertFromUnicodeToUtf8(value, temp);
         INFO_PRINTF1(_L("call CSIPSecurityClientHeader::DecodeL(const TDesC8&)"));
         RPointerArray<CSIPSecurityClientHeader> ret;
         TRAPD(err, ret = CSIPSecurityClientHeader::DecodeL(value));

         if (KErrNone != err)
             {
             ERR_PRINTF2(KLogError, err);
             SetError(err);
             return;
             }
         
         TInt cnt = ret.Count();
         INFO_PRINTF2(_L("%d CSIPSecurityClientHeader objects got from DecodeL()"), cnt);
         TBool moreData = ETrue;
         TBuf<KMaxTestExecuteNameLength> tempStore;
         TInt index = 1;
         while (moreData && index <= cnt)
             {
             TPtrC name;
             tempStore.Format(KFormatFieldNumber, &KFldSecurityClientHeader, index);
             if (GetStringFromConfig(aSection, tempStore, name))
                 {
                 SetDataObjectL(name, ret[index - 1]);
                 CT_DataSIPSecurityClientHeader* wrapper = (CT_DataSIPSecurityClientHeader*)GetDataWrapperL(name);
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
    }

void CT_DataSIPSecurityClientHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
    {
    delete iSIPSecurityClientHeader;
    iSIPSecurityClientHeader = NULL;
    
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
        INFO_PRINTF1(_L("execute CSIPSecurityClientHeader::InternalizeValueL(RReadStream &)"));
        CSIPHeaderBase* base = NULL;
        TRAPD(err, base = CSIPSecurityClientHeader::InternalizeValueL(readstrm));
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            iSIPSecurityClientHeader = dynamic_cast<CSIPSecurityClientHeader*>(base);
            }
        // Cleanup
        CleanupStack::PopAndDestroy(2, readstore);
        }  
    }

void CT_DataSIPSecurityClientHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPSecurityClientHeader::~CSIPSecurityClientHeader()"));
    DestroyData();
    }
