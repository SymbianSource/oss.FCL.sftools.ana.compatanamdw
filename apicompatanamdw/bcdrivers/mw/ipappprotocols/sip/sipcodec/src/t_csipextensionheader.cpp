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


// This contains CT_DataSIPExtensionHeader

#include "t_csipextensionheader.h"
#include <utf.h>
#include <s32file.h>


/*@{*/
_LIT(KCmdInternalizeValueL,         "InternalizeValueL");
_LIT(KCmdNewL,                      "NewL");
_LIT(KCmdNewLC,                     "NewLC");
_LIT(KCmdSetValueL,                 "SetValueL");
_LIT(KCmdValue,                     "Value");
_LIT(KDestructor,                   "~");

// Fields 
_LIT(KFldName,                      "name");
_LIT(KFldValue,                     "value");
_LIT(KFldExpected,                  "expected");
_LIT(KFldFileName,                  "filename");
_LIT(KFldExtensionHeader,           "extensionheader");

// Error
_LIT(KLogError,                     "Error=%d");
_LIT(KMissingParameter,             "missing parameter '%S'");
//Info

CT_DataSIPExtensionHeader* CT_DataSIPExtensionHeader::NewL()
    {
    CT_DataSIPExtensionHeader* self = new (ELeave) CT_DataSIPExtensionHeader();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }
    
CT_DataSIPExtensionHeader::~CT_DataSIPExtensionHeader()
    {
    DestroyData();
    }

void CT_DataSIPExtensionHeader::DestroyData()
    {
    if (iIsOwner)
        {
        delete iSIPExtensionHeader;
        iSIPExtensionHeader = NULL;
        iIsOwner = EFalse;
        }
    }

CSIPHeaderBase* CT_DataSIPExtensionHeader::GetSIPHeaderBase() const
    {
    return iSIPExtensionHeader;
    }

TAny* CT_DataSIPExtensionHeader::GetObject()
    {
    return iSIPExtensionHeader;
    }

void CT_DataSIPExtensionHeader::SetObjectL(TAny* aAny)
    {
    DestroyData();
    iSIPExtensionHeader = static_cast<CSIPExtensionHeader*> (aAny);
    }

void CT_DataSIPExtensionHeader::DisownObjectL()
    {
    iSIPExtensionHeader = NULL;
    iIsOwner = EFalse;
    }

CT_DataSIPExtensionHeader::CT_DataSIPExtensionHeader() :CT_DataSIPHeaderBase(), iSIPExtensionHeader(NULL), iIsOwner(ETrue)
    {
    }

void CT_DataSIPExtensionHeader::ConstructL()
    {
    }

void CT_DataSIPExtensionHeader::DoCmdDestructor()
    {
    DestroyData();
    }

TBool CT_DataSIPExtensionHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
    {
    TBool ret = ETrue;
    if (aCommand == KDestructor)
        {
        DoCmdDestructor();
        }
    else if(aCommand == KCmdNewL)
        {
        DoCmdNewL(aSection);
        }
    else if(aCommand == KCmdNewLC)
        {
        DoCmdNewLC(aSection);
        }
    else if(aCommand == KCmdSetValueL)
        {
        DoCmdSetValueL(aSection);
        }
    else if(aCommand == KCmdValue)
        {
        DoCmdValue(aSection);
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

void CT_DataSIPExtensionHeader::DoCmdNewL(const TTEFSectionName& aSection)
    {
    TPtrC str1;
    TPtrC str2;
    
    if(!GetStringFromConfig(aSection, KFldName, str1))
        {
        ERR_PRINTF2(KMissingParameter, &KFldName());
        SetBlockResult(EFail);
        return;
        }
    if(!GetStringFromConfig(aSection, KFldValue, str2))
        {
        ERR_PRINTF2(KMissingParameter, &KFldValue());
        SetBlockResult(EFail);
        return;
        }
    
    TBuf8<KMaxTestExecuteCommandLength> headername;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(headername, str1);
    TBuf8<KMaxTestExecuteCommandLength> headervalue;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(headervalue, str2);    
    
    INFO_PRINTF1(_L("call CSIPExtensionHeader::NewL(const TDesC8 &, const TDesC8 &)"));
    TRAPD(err,iSIPExtensionHeader= CSIPExtensionHeader::NewL(headername,headervalue));
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

void CT_DataSIPExtensionHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    TPtrC str1;
    TPtrC str2;
    
    if(!GetStringFromConfig(aSection, KFldName, str1))
        {
        ERR_PRINTF2(KMissingParameter, &KFldName());
        SetBlockResult(EFail);
        return;
        }
    if(!GetStringFromConfig(aSection, KFldValue, str2))
        {
        ERR_PRINTF2(KMissingParameter, &KFldValue());
        SetBlockResult(EFail);
        return;
        }
    
    TBuf8<KMaxTestExecuteCommandLength> headername;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(headername, str1);
    TBuf8<KMaxTestExecuteCommandLength> headervalue;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(headervalue, str2);    
    
    INFO_PRINTF1(_L("call CSIPExtensionHeader::NewLC(const TDesC8 &, const TDesC8 &)"));
    TRAPD(err,iSIPExtensionHeader= CSIPExtensionHeader::NewLC(headername,headervalue); CleanupStack::Pop());
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

void CT_DataSIPExtensionHeader::DoCmdSetValueL(const TTEFSectionName& aSection)
    {
    TPtrC str;    

    if(!GetStringFromConfig(aSection, KFldValue, str))
        {
        ERR_PRINTF2(KMissingParameter, &KFldValue());
        SetBlockResult(EFail);
        return;
        }
    
    TBuf8<KMaxTestExecuteCommandLength> headervalue;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(headervalue, str);    
    INFO_PRINTF1(_L("call CSIPExtensionHeader::SetValueL(const TDesC8 &)"));
    TRAPD(err,iSIPExtensionHeader->SetValueL(headervalue));
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

void CT_DataSIPExtensionHeader::DoCmdValue(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPExtensionHeader::Value()"));
    const TDesC8& value = iSIPExtensionHeader->Value();
    TBuf<KMaxTestExecuteCommandLength> str;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(str, value);
    INFO_PRINTF2(_L("The actual value is: %S "), &str);
    TPtrC expected;
    if(GetStringFromConfig(aSection, KFldExpected, expected))
        {
        if(expected != str)
            {
            ERR_PRINTF2(_L("The expected value is: %S"), &expected);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPExtensionHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
    {
    // Get test data for command input parameter(s)
    CSIPExtensionHeader* sipExtensionHeader = NULL;
    TPtrC   datFileName;
    TPtrC   datSipExtensionHeader;
    if ( !GetStringFromConfig(aSection, KFldFileName, datFileName) )
        {
        ERR_PRINTF2(KMissingParameter, &KFldFileName);
        SetBlockResult(EFail);
        }
    else if(!GetStringFromConfig(aSection, KFldExtensionHeader, datSipExtensionHeader))
        {        
        ERR_PRINTF2(KMissingParameter, &KFldExtensionHeader());
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
        INFO_PRINTF1(_L("execute CSIPExtensionHeader::InternalizeValueL(RReadStream &)"));
        TRAPD(err, sipExtensionHeader = CSIPExtensionHeader::InternalizeValueL(readstrm));
        if ( err!=KErrNone )
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            SetDataObjectL(datSipExtensionHeader, sipExtensionHeader);
            }
        // Cleanup
        CleanupStack::PopAndDestroy(2,readstore);
        }   
    }

void CT_DataSIPExtensionHeader::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }
