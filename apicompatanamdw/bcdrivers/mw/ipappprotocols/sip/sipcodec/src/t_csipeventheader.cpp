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


// This contains CT_DataSIPToHeader

#include "t_csipeventheader.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <s32file.h>

//  Epoc Includes

/*@{*/
_LIT(KCmdNewL,                              "NewL");
_LIT(KCmdNewLC,                             "NewLC");
_LIT(KCmdDisown,                            "Disown");
_LIT(KCmdDecoderL,                          "DecodeL");
_LIT(KCmdInternalizeValueL,                 "InternalizeValueL");
_LIT(KCmdEventPackage,                      "EventPackage");
_LIT(KCmdEventTemplates,                    "EventTemplates");
_LIT(KCmdSetEventPackageL,                  "SetEventPackageL");
_LIT(KCmdSetEventTemplatesL,                "SetEventTemplatesL");
_LIT(KCmdCompare,                           "==");
_LIT(KDestructor,                           "~");

_LIT(KFldSIPEventHeader,                    "eventheader");
_LIT(KFldValue,                             "value");
_LIT(KFldEventPackage,                      "eventpackage");
_LIT(KFldEventTemplates,                    "eventtemplates");
_LIT(KFldExpected,                          "expected");
_LIT(KFldFileName,                          "filename");       

_LIT(KLogError,                             "Error=%d");
_LIT(KLogMissingParameter,                  "Missing parameter '%S'");
_LIT(KLogNotExpectedValue,                  "Not expected value, actual=%d, expect=%d");


CT_DataSIPEventHeader* CT_DataSIPEventHeader::NewL()
    {
    CT_DataSIPEventHeader* ret=new (ELeave) CT_DataSIPEventHeader();
    CleanupStack::PushL(ret);
    ret->ConstructL();
    CleanupStack::Pop(ret);
    return ret;
    }

CT_DataSIPEventHeader::CT_DataSIPEventHeader():CT_DataSIPParameterHeaderBase(), 
iSIPEventHeader(NULL), iIsOwner(ETrue)

    {
    }

void CT_DataSIPEventHeader::ConstructL()
    {
    }

CT_DataSIPEventHeader::~CT_DataSIPEventHeader()
    {
    DestroyData();
    }

/**
* Return a pointer to the object that the data wraps
*
* @return pointer to the object that the data wraps
*/
TAny* CT_DataSIPEventHeader::GetObject()
    {
    return iSIPEventHeader;
    }

void CT_DataSIPEventHeader::SetObjectL(TAny* aAny)
    {
    iSIPEventHeader=static_cast<CSIPEventHeader*> (aAny);
    }

void CT_DataSIPEventHeader::DisownObjectL()
    {
    iSIPEventHeader=NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPEventHeader::DestroyData()
    {
    if (iIsOwner)
        {
        delete iSIPEventHeader;
        iSIPEventHeader = NULL;
        iIsOwner = EFalse;
        }
    }

CSIPHeaderBase* CT_DataSIPEventHeader::GetSIPHeaderBase() const
    {
    return iSIPEventHeader;
    }

/**
Delegates the commands to a function

* @internalComponent
* @param aCommand Current command
* @param aSection Current ini file command section
* @param aAsyncErrorIndex index of command for SetAsyncError()
* @return TBool Returns whether the command was executed or not
*/
TBool CT_DataSIPEventHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
    {
    TBool   retVal = ETrue;
    
    if( aCommand == KDestructor )
        {
        DestroyData();
        }
    else if( aCommand == KCmdNewL )
        {
        DoCmdNewL(aSection);
        }
    else if( aCommand == KCmdNewLC )
        {
        DoCmdNewLC(aSection);
        }
    else if( aCommand == KCmdDecoderL )
        {
        DoCmdDecodeL(aSection);
        }
    else if( aCommand == KCmdInternalizeValueL )
        {
        DoCmdInternalizeValueL(aSection);
        }
    else if( aCommand == KCmdEventPackage)
        {
        DoCmdEventPackage(aSection);
        }
    else if( aCommand == KCmdEventTemplates)
        {
        DoCmdEventTemplates(aSection);
        }
    else if( aCommand == KCmdSetEventPackageL)
        {
        DoCmdSetEventPackageL(aSection);
        }
    else if( aCommand == KCmdSetEventTemplatesL)
        {
        DoCmdSetEventTemplatesL(aSection);
        }
    else if( aCommand == KCmdCompare)
        {
        DoCmdCompare(aSection);
        }
    else if( aCommand == KCmdDisown )
        {
        DisownObjectL();
        }
    else
        {
        retVal = CT_DataSIPParameterHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
        }
    return retVal;  
    }

void CT_DataSIPEventHeader::DoCmdNewL(const TTEFSectionName& aSection)
    {
    delete iSIPEventHeader;
    iSIPEventHeader = NULL;
    
    TPtrC str;
    if(!GetStringFromConfig(aSection, KFldEventPackage, str))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldEventPackage());
        SetBlockResult(EFail);
        return;
        }
    
    TBuf8<KMaxTestExecuteCommandLength> eventPackage;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(eventPackage, str);
    INFO_PRINTF1(_L("call CSIPEventHeader::NewL(const TDesC8 &)"));
    TRAPD(err, iSIPEventHeader = CSIPEventHeader::NewL(eventPackage));
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void CT_DataSIPEventHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    delete iSIPEventHeader;
    iSIPEventHeader = NULL;
    
    TPtrC str;
    if(!GetStringFromConfig(aSection, KFldEventPackage, str))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldEventPackage());
        SetBlockResult(EFail);
        return;
        }
    
    TBuf8<KMaxTestExecuteCommandLength> eventPackage;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(eventPackage, str);
    INFO_PRINTF1(_L("call CSIPEventHeader::NewLC(const TDesC8 &)"));
    TRAPD(err, iSIPEventHeader = CSIPEventHeader::NewLC(eventPackage); CleanupStack::Pop(iSIPEventHeader));
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void CT_DataSIPEventHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
    {
    delete iSIPEventHeader;
    iSIPEventHeader = NULL;
    
    TPtrC str;
     if(!GetStringFromConfig(aSection, KFldValue, str))
         {
         ERR_PRINTF2(KLogMissingParameter, &KFldValue());
         SetBlockResult(EFail);
         return;
         }
     
     TBuf8<KMaxTestExecuteCommandLength> value;
     CnvUtfConverter::ConvertFromUnicodeToUtf8(value, str);
     INFO_PRINTF1(_L("call CSIPEventHeader::DecodeL(const TDesC8 &)"));
     TRAPD(err, iSIPEventHeader = CSIPEventHeader::DecodeL(value));
     if(KErrNone != err)
         {
         ERR_PRINTF2(KLogError, err);
         SetError(err);
         } 
    }

void CT_DataSIPEventHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
    {
    delete iSIPEventHeader;
    iSIPEventHeader = NULL;
 
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
        
        INFO_PRINTF1(_L("call CSIPEventHeader::InternalizeValueL(RReadStream &)"));
        TRAPD(err, iSIPEventHeader = (CSIPEventHeader*)CSIPEventHeader::InternalizeValueL(readstrm));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        
        CleanupStack::PopAndDestroy(2);
        }
    }
 
void CT_DataSIPEventHeader::DoCmdEventPackage(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPEventHeader::EventPackageL()"));
    const TDesC8& eventPackage = iSIPEventHeader->EventPackage();
    TBuf<KMaxTestExecuteCommandLength> str;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(str, eventPackage);
    INFO_PRINTF2(_L("The actual event package is: %S "), &str);
    TPtrC expected;
    if(GetStringFromConfig(aSection, KFldExpected, expected))
        {
        if(expected != str)
            {
            ERR_PRINTF2(_L("The expected event package is: %S"), &expected);
            SetBlockResult(EFail);
            }
        }
    
    }

void CT_DataSIPEventHeader::DoCmdSetEventPackageL(const TTEFSectionName& aSection)
    {
    TPtrC str;
    if(!GetStringFromConfig(aSection, KFldEventPackage, str))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldEventPackage());
        SetBlockResult(EFail);
        return;
        }
    
    TBuf8<KMaxTestExecuteCommandLength> eventPackage;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(eventPackage, str);
    INFO_PRINTF1(_L("call CSIPEventHeader::SetEventPackageL(const TDesC8 &)"));
    TRAPD(err, iSIPEventHeader->SetEventPackageL(eventPackage));
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }       
    }

void CT_DataSIPEventHeader::DoCmdEventTemplates(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPEventHeader::SetEventPackageL(const TDesC8 &)"));
    
    const CDesC8Array& eventTemplates = (const CDesC8Array&)iSIPEventHeader->EventTemplates();

    CDesC8ArraySeg* expecedValues = new (ELeave) CDesC8ArraySeg(1);
    TBool checkExpectedValues = CT_SIPUtil::GetMDesC8ArrayL(*this, aSection, KFldExpected, (MDesC8Array*)expecedValues);

    for(TInt i=0; i < eventTemplates.Count(); i++)
        {
        TBuf<KMaxTestExecuteCommandLength> templates;
        CnvUtfConverter::ConvertToUnicodeFromUtf8(templates, eventTemplates[i]);
        INFO_PRINTF3(_L("The event template[%d]: %S"), i, &templates);
        
        if(checkExpectedValues && i <expecedValues->Count())
            {
            if(eventTemplates[i].Compare((*expecedValues)[i]) != 0)
                {
                CnvUtfConverter::ConvertToUnicodeFromUtf8(templates, (*expecedValues)[i]);
                ERR_PRINTF3(_L("Expected event template[%d]: %S"), i, &templates);
                SetBlockResult(EFail); 
                }
            }
        }
   
    }

void CT_DataSIPEventHeader::DoCmdSetEventTemplatesL(const TTEFSectionName& aSection)
    {
    CDesC8ArraySeg* array = new (ELeave) CDesC8ArraySeg(1);
    CleanupStack::PushL(array);
    if(CT_SIPUtil::GetMDesC8ArrayL(*this, aSection, KFldEventTemplates, (MDesC8Array*)array))
        {
        INFO_PRINTF1(_L("call CSIPEventHeader::SetEventTemplatesL(const MDesC8Array &)"));
        TRAPD(err, iSIPEventHeader->SetEventTemplatesL(*array));
        
        if(err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    else
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldEventTemplates());
        SetBlockResult(EFail);
        }
    CleanupStack::PopAndDestroy(1);
    }

void CT_DataSIPEventHeader::DoCmdCompare(const TTEFSectionName& aSection)
    {
    CSIPEventHeader* eventHeader = NULL;
    if( !CT_SIPUtil::GetSIPEventHeaderL(*this, aSection, KFldSIPEventHeader, eventHeader) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPEventHeader());
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPEventHeader::==(const CSIPEventHeader&)")); 
        TBool ret = (*iSIPEventHeader == *eventHeader);
        
        TBool expected;
        if( GetBoolFromConfig(aSection, KFldExpected, expected) )
            {
            if(!ret != !expected)
                {
                ERR_PRINTF3(KLogNotExpectedValue, (TInt)ret, (TInt)expected);
                SetBlockResult(EFail);
                }
            }
        }
    }

void CT_DataSIPEventHeader::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }
