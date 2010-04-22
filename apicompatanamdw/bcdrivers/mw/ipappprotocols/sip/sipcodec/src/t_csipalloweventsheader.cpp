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

#include "t_csipalloweventsheader.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <s32file.h>
#include <e32cmn.h>


//  Epoc Includes

/*@{*/
_LIT(KCmdNewL,                              "NewL");
_LIT(KCmdNewLC,                             "NewLC");
_LIT(KCmdDisown,                            "Disown");
_LIT(KCmdDecodeL,                           "DecodeL");
_LIT(KCmdInternalizeValueL,                 "InternalizeValueL");
_LIT(KCmdEventPackage,                      "EventPackage");
_LIT(KCmdEventTemplates,                    "EventTemplates");
_LIT(KCmdSetEventPackageL,                  "SetEventPackageL");
_LIT(KCmdSetEventTemplatesL,                "SetEventTemplatesL");
_LIT(KCmdCompare,                           "==");
_LIT(KDestructor,                           "~");

_LIT(KFldSIPEventHeader,                    "EventHeader");
_LIT(KFldValue,                             "Value");
_LIT(KFldEventPackage,                      "EventPackage");
_LIT(KFldEventTemplates,                    "EventTemplates");
_LIT(KFldReadStream,                        "readstream");
_LIT(KFldExpected,                          "expected");
_LIT(KFldFileName,                          "filename");

_LIT(KLogError,                             "Error=%d");
_LIT(KLogMissingParameter,                  "Missing parameter '%S'");
_LIT(KLogNotExpectedValue,                  "Not expected value, actual=%d, expect=%d");


CT_DataSIPAllowEventsHeader* CT_DataSIPAllowEventsHeader::NewL()
    {
    CT_DataSIPAllowEventsHeader* ret=new (ELeave) CT_DataSIPAllowEventsHeader();
    CleanupStack::PushL(ret);
    ret->ConstructL();
    CleanupStack::Pop(ret);
    return ret;
    }

CT_DataSIPAllowEventsHeader::CT_DataSIPAllowEventsHeader():CT_DataSIPHeaderBase(), iIsOwner(ETrue)

    {
    }

void CT_DataSIPAllowEventsHeader::ConstructL()
    {
    }

CT_DataSIPAllowEventsHeader::~CT_DataSIPAllowEventsHeader()
    {
    DestroyData();
    }

/**
* Return a pointer to the object that the data wraps
*
* @return pointer to the object that the data wraps
*/
TAny* CT_DataSIPAllowEventsHeader::GetObject()
    {
    return iAllowEventsHeader;
    }

void CT_DataSIPAllowEventsHeader::SetObjectL(TAny* aAny)
    {
    iAllowEventsHeader=static_cast<CSIPAllowEventsHeader*> (aAny);
    }

void CT_DataSIPAllowEventsHeader::DisownObjectL()
    {
    iAllowEventsHeader=NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPAllowEventsHeader::DestroyData()
    {
    if (iIsOwner)
        {
        delete iAllowEventsHeader;
        iAllowEventsHeader = NULL;
        iIsOwner = EFalse;
        }
    }

CSIPHeaderBase* CT_DataSIPAllowEventsHeader::GetSIPHeaderBase() const
    {
    return iAllowEventsHeader;
    }

/**
Delegates the commands to a function

* @internalComponent
* @param aCommand Current command
* @param aSection Current ini file command section
* @param aAsyncErrorIndex index of command for SetAsyncError()
* @return TBool Returns whether the command was executed or not
*/
TBool CT_DataSIPAllowEventsHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
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
    else if( aCommand == KCmdDecodeL )
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
    else if( aCommand == KCmdDisown )
        {
        DisownObjectL();
        }
    else
        {
        retVal = CT_DataSIPHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
        }
    return retVal;  
    }

void CT_DataSIPAllowEventsHeader::DoCmdNewL(const TTEFSectionName& aSection)
    {
    delete iAllowEventsHeader;
    iAllowEventsHeader = NULL;
    
    TPtrC str;
    if(!GetStringFromConfig(aSection, KFldEventPackage, str))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldEventPackage());
        SetBlockResult(EFail);
        return;
        }
    
    TBuf8<KMaxTestExecuteCommandLength> eventPackage;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(eventPackage, str);
    INFO_PRINTF1(_L("call CSIPAllowEventsHeader::NewL(const TDesC8 &)"));
    TRAPD(err, iAllowEventsHeader = CSIPAllowEventsHeader::NewL(eventPackage));
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void CT_DataSIPAllowEventsHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    delete iAllowEventsHeader;
    iAllowEventsHeader = NULL;
    
    TPtrC str;
    if(!GetStringFromConfig(aSection, KFldEventPackage, str))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldEventPackage());
        SetBlockResult(EFail);
        return;
        }
    
    TBuf8<KMaxTestExecuteCommandLength> eventPackage;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(eventPackage, str);
    INFO_PRINTF1(_L("call CSIPAllowEventsHeader::NewLC(const TDesC8 &)"));
    TRAPD(err, iAllowEventsHeader = CSIPAllowEventsHeader::NewLC(eventPackage); CleanupStack::Pop(iAllowEventsHeader));
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void CT_DataSIPAllowEventsHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
    {
    delete iAllowEventsHeader;
    iAllowEventsHeader = NULL;
    
    TPtrC str;
     if(!GetStringFromConfig(aSection, KFldValue, str))
         {
         ERR_PRINTF2(KLogMissingParameter, &KFldValue());
         SetBlockResult(EFail);
         return;
         }
     
     TBuf8<KMaxTestExecuteCommandLength> value;
     CnvUtfConverter::ConvertFromUnicodeToUtf8(value, str);
     INFO_PRINTF1(_L("call CSIPAllowEventsHeader::DecodeL(const TDesC8 &)")); 
     TRAPD(err, iAllowEventsHeader = (CSIPAllowEventsHeader::DecodeL(value)[0]));
     if(KErrNone != err)
         {
         ERR_PRINTF2(KLogError, err);
         SetError(err);
         } 
    }

void CT_DataSIPAllowEventsHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
    {
    delete iAllowEventsHeader;
    iAllowEventsHeader = NULL;
    
    TPtrC FileName;
    TPtrC datSipCallIDHeader;
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
        INFO_PRINTF1(_L("execute CSIPAllowEventsHeader::InternalizeValueL(RReadStream &)"));
        CSIPHeaderBase* base = NULL;
        TRAPD(err, base = CSIPAllowEventsHeader::InternalizeValueL(readstrm));
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            iAllowEventsHeader = dynamic_cast<CSIPAllowEventsHeader*>(base);
            }
        // Cleanup
        CleanupStack::PopAndDestroy(2, readstore);
        }  
    }
 
void CT_DataSIPAllowEventsHeader::DoCmdEventPackage(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPAllowEventsHeader::EventPackageL()"));
    const TDesC8& eventPackage = iAllowEventsHeader->EventPackage();
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

void CT_DataSIPAllowEventsHeader::DoCmdSetEventPackageL(const TTEFSectionName& aSection)
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
    INFO_PRINTF1(_L("call CSIPAllowEventsHeader::SetEventPackageL(const TDesC8 &)"));
    TRAPD(err, iAllowEventsHeader->SetEventPackageL(eventPackage));
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }       
    }

void CT_DataSIPAllowEventsHeader::DoCmdEventTemplates(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPAllowEventsHeader::EventTemplates()"));
    
    const CDesC8Array& eventTemplates = (const CDesC8Array&)iAllowEventsHeader->EventTemplates();
    
    
    CDesC8ArraySeg *expecedValues= new CDesC8ArraySeg(5);
    
    TBool checkExpectedValues = CT_SIPUtil::GetMDesC8ArrayL(*this, aSection, KFldExpected, (MDesC8Array *)expecedValues);
    
    
    if(checkExpectedValues)
        {
        for(TInt i=0; i < eventTemplates.Count(); i++)
            {
            INFO_PRINTF3(_L("The event template[%d]: %S"), i, eventTemplates[i]);
        
            if(i <expecedValues->Count())
                 {
                 if(eventTemplates[i].Compare((*expecedValues)[i]) != 0)
                     {
                     ERR_PRINTF3(_L("Expected event template[%d]: %S"), i, expecedValues+i);
                     SetBlockResult(EFail); 
                     }
                 }
            }
        }
   delete expecedValues;
    }

void CT_DataSIPAllowEventsHeader::DoCmdSetEventTemplatesL(const TTEFSectionName& aSection)
    {
    CDesC8ArraySeg *array= new CDesC8ArraySeg(5);
    if(CT_SIPUtil::GetMDesC8ArrayL(*this, aSection, KFldEventTemplates, (MDesC8Array *)array))
        {
        INFO_PRINTF1(_L("call CSIPAllowEventsHeader::SetEventTemplatesL(const MDesC8Array &)"));
        TRAPD(err, iAllowEventsHeader->SetEventTemplatesL(*array));
        
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
    }


void CT_DataSIPAllowEventsHeader::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }

