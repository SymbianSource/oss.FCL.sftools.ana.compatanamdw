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



#include "t_csippassociateduriheader.h"
#include "t_csipaddress.h"
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
_LIT(KCmdCompare,                           "==");
_LIT(KDestructor,                           "~");

_LIT(KFldSIPAddress,                    "SIPAddress");
_LIT(KFldValue,                             "Value");
_LIT(KFldEventPackage,                      "EventPackage");
_LIT(KFldEventTemplates,                    "EventTemplates");
_LIT(KFldReadStream,                        "readstream");
_LIT(KFldExpected,                          "expected");
_LIT(KFldFileName,                          "filename");

_LIT(KLogError,                             "Error=%d");
_LIT(KLogMissingParameter,                  "Missing parameter '%S'");
_LIT(KLogNotExpectedValue,                  "Not expected value, actual=%d, expect=%d");


CT_DataSIPPAssociatedURIHeader* CT_DataSIPPAssociatedURIHeader::NewL()
    {
    CT_DataSIPPAssociatedURIHeader* ret=new (ELeave) CT_DataSIPPAssociatedURIHeader();
    CleanupStack::PushL(ret);
    ret->ConstructL();
    CleanupStack::Pop(ret);
    return ret;
    }

CT_DataSIPPAssociatedURIHeader::CT_DataSIPPAssociatedURIHeader():CT_DataSIPAddressHeaderBase(), iIsOwner(ETrue)

    {
    }

void CT_DataSIPPAssociatedURIHeader::ConstructL()
    {
    }

CT_DataSIPPAssociatedURIHeader::~CT_DataSIPPAssociatedURIHeader()
    {
    DestroyData();
    }

/**
* Return a pointer to the object that the data wraps
*
* @return pointer to the object that the data wraps
*/
TAny* CT_DataSIPPAssociatedURIHeader::GetObject()
    {
    return iURIHeader;
    }

void CT_DataSIPPAssociatedURIHeader::SetObjectL(TAny* aAny)
    {
    iURIHeader=static_cast<CSIPPAssociatedURIHeader*> (aAny);
    }

void CT_DataSIPPAssociatedURIHeader::DisownObjectL()
    {
    iURIHeader=NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPPAssociatedURIHeader::DestroyData()
    {
    if (iIsOwner)
        {
        delete iURIHeader;
        iURIHeader = NULL;
        iIsOwner = EFalse;
        }
    }

CSIPHeaderBase* CT_DataSIPPAssociatedURIHeader::GetSIPHeaderBase() const
    {
    return iURIHeader;
    }

/**
Delegates the commands to a function

* @internalComponent
* @param aCommand Current command
* @param aSection Current ini file command section
* @param aAsyncErrorIndex index of command for SetAsyncError()
* @return TBool Returns whether the command was executed or not
*/
TBool CT_DataSIPPAssociatedURIHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
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
    else if( aCommand == KCmdDisown )
        {
        DisownObjectL();
        }
    else
        {
        retVal = CT_DataSIPAddressHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
        }
    return retVal;  
    }

void CT_DataSIPPAssociatedURIHeader::DoCmdNewL(const TTEFSectionName& aSection)
    {
    delete iURIHeader;
    iURIHeader = NULL;
    
    TPtrC   name;
    CSIPAddress *sipAddress;
    if (GetStringFromConfig(aSection, KFldSIPAddress, name))
        {
        sipAddress = static_cast<CSIPAddress*>(GetDataObjectL(name));
        INFO_PRINTF1(_L("call CSIPPAssociatedURIHeader::NewL(CSIPAddress *aSIPAddress)"));
        TRAPD(err, iURIHeader = CSIPPAssociatedURIHeader::NewL(sipAddress));
        if(KErrNone != err)
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
    else
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPAddress());
        SetBlockResult(EFail);
        return;
        }
    }


void CT_DataSIPPAssociatedURIHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    delete iURIHeader;
    iURIHeader = NULL;
    
    TPtrC   name;
    CSIPAddress *sipAddress;
    if (GetStringFromConfig(aSection, KFldSIPAddress, name))
        {
        sipAddress = static_cast<CSIPAddress*>(GetDataObjectL(name));
        INFO_PRINTF1(_L("call CSIPPAssociatedURIHeader::NewL(CSIPAddress *aSIPAddress)"));
        TRAPD(err, iURIHeader = CSIPPAssociatedURIHeader::NewLC(sipAddress); CleanupStack::Pop(iURIHeader));
        if(KErrNone != err)
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
    else
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPAddress());
        SetBlockResult(EFail);
        return;
        }
    }


void CT_DataSIPPAssociatedURIHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
    {
    delete iURIHeader;
    iURIHeader = NULL;
    
    TPtrC str;
     if(!GetStringFromConfig(aSection, KFldValue, str))
         {
         ERR_PRINTF2(KLogMissingParameter, &KFldValue());
         SetBlockResult(EFail);
         return;
         }
     
     TBuf8<KMaxTestExecuteCommandLength> value;
     CnvUtfConverter::ConvertFromUnicodeToUtf8(value, str);
     INFO_PRINTF1(_L("call CSIPPAssociatedURIHeader::DecodeL(const TDesC8 &)")); 
     TRAPD(err, iURIHeader = (CSIPPAssociatedURIHeader::DecodeL(value)[0]));
     if(KErrNone != err)
         {
         ERR_PRINTF2(KLogError, err);
         SetError(err);
         } 
    }

void CT_DataSIPPAssociatedURIHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
    {
    delete iURIHeader;
    iURIHeader = NULL;
    
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
        INFO_PRINTF1(_L("execute CSIPPAssociatedURIHeader::InternalizeValueL(RReadStream &)"));
        CSIPHeaderBase* base = NULL;
        TRAPD(err, base = CSIPPAssociatedURIHeader::InternalizeValueL(readstrm));
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            iURIHeader = dynamic_cast<CSIPPAssociatedURIHeader*>(base);
            }
        // Cleanup
        CleanupStack::PopAndDestroy(2, readstore);
        }  
    }
 


void CT_DataSIPPAssociatedURIHeader::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }

