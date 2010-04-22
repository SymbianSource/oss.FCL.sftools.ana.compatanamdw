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


// This contains CT_DataSIPContentTypeHeader

#include "t_csipcontenttypeheader.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <s32file.h>

/*@{*/
_LIT(KCmdNewL,                  "NewL");
_LIT(KCmdNewLC,                 "NewLC");
_LIT(KCmdDecodeL,               "DecodeL");
_LIT(KCmdMediaType,             "MediaType");
_LIT(KCmdSetMediaTypeL,         "SetMediaTypeL");
_LIT(KCmdMediaSubtype,          "MediaSubtype");
_LIT(KCmdSetMediaSubtypeL,      "SetMediaSubtypeL");
_LIT(KCmdInternalizeValueL,     "InternalizeValueL");
_LIT(KCmdDestructor,            "~");

//_LIT(KFldHeaderBase,            "headerbase");
_LIT(KFldFileName,              "filename");
_LIT(KFldMediaSubtype,          "mediasubtype");
_LIT(KFldMediaType,             "mediatype");
_LIT(KFldHeaderValue,           "headervalue");

_LIT(KFldExpected,              "expected");

_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");
//_LIT(KLogNotExpectedValue,      "Not expected value, actual=%d, expect=%d");
_LIT(KLogNotExpectedValue1,     "Not expected value, actual=%S, expect=%S");
/*}@*/


CT_DataSIPContentTypeHeader*  CT_DataSIPContentTypeHeader::NewL()
    {
    CT_DataSIPContentTypeHeader* self = new (ELeave) CT_DataSIPContentTypeHeader();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;    
    }

CT_DataSIPContentTypeHeader::~CT_DataSIPContentTypeHeader()
    {
    DestroyData();
    }

CT_DataSIPContentTypeHeader::CT_DataSIPContentTypeHeader()
:   CT_DataSIPParameterHeaderBase(), iSIPContentTypeHeader(NULL), iIsOwner(ETrue)
	{
	}

void CT_DataSIPContentTypeHeader::ConstructL()
    {
    }

TAny* CT_DataSIPContentTypeHeader::GetObject()
    {
    return iSIPContentTypeHeader;
    }

void CT_DataSIPContentTypeHeader::SetObjectL(TAny* aAny)
    {
    iSIPContentTypeHeader = static_cast<CSIPContentTypeHeader*>(aAny);
    }

void CT_DataSIPContentTypeHeader::DisownObjectL()
    {
    iSIPContentTypeHeader = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPContentTypeHeader::DestroyData()
    {
    if (iIsOwner)
        {
        delete iSIPContentTypeHeader;
        iSIPContentTypeHeader = NULL;
        iIsOwner = EFalse;
        }
    }

CSIPHeaderBase* CT_DataSIPContentTypeHeader::GetSIPHeaderBase() const
    {
    return iSIPContentTypeHeader;
    }

/**
Delegates the commands to a function

* @internalComponent
* @param aCommand Current command
* @param aSection Current ini file command section
* @param aAsyncErrorIndex index of command for SetAsyncError()
* @return TBool Returns whether the command was executed or not
*/
TBool CT_DataSIPContentTypeHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
	{
	TBool	retVal = ETrue;

	if( aCommand == KCmdNewL)
	    {
	    DoCmdNewL(aSection);
	    }
	else if( aCommand == KCmdNewLC)
        {
        DoCmdNewLC(aSection);
        }
    else if( aCommand == KCmdDecodeL )
        {
        DoCmdDecodeL(aSection);
        }
    else if( aCommand == KCmdMediaType )
        {
        DoCmdMediaType(aSection);
        }
    else if( aCommand == KCmdSetMediaTypeL )
        {
        DoCmdSetMediaTypeL(aSection);
        }
    else if( aCommand == KCmdMediaSubtype )
        {
        DoCmdMediaSubtype(aSection);
        }
    else if( aCommand == KCmdSetMediaSubtypeL )
        {
        DoCmdSetMediaSubtypeL(aSection);
        }
    else if( aCommand == KCmdInternalizeValueL)
        {
        DoCmdInternalizeValueL(aSection);
        }
	else if( aCommand == KCmdDestructor )
        {
        DoCmdDestructor(aSection);
        }
	else
		{
		retVal = CT_DataSIPParameterHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);;
		}
	return retVal;  
	}

void CT_DataSIPContentTypeHeader::DoCmdNewL(const TTEFSectionName& aSection)
    {
    TBool dataOK = ETrue;    
    TPtrC temp;
    if( !GetStringFromConfig(aSection, KFldMediaType, temp) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldMediaType);        
        dataOK = EFalse;
        }    
    TPtrC temp1;
    if( !GetStringFromConfig(aSection, KFldMediaSubtype, temp1) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldMediaSubtype);
        dataOK = EFalse;
        }
    
    if(!dataOK)
        {
        SetBlockResult(EFail);
        }
    else
        {
        TBuf8<KMaxTestExecuteCommandLength> mediatype;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(mediatype, temp);
        TBuf8<KMaxTestExecuteCommandLength> mediasubtype;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(mediasubtype, temp1);                
        INFO_PRINTF1(_L("call CSIPContentTypeHeader::NewL(const TDesC8&, const TDesC8&)"));
        TRAPD(err, iSIPContentTypeHeader = CSIPContentTypeHeader::NewL(mediatype, mediasubtype));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            iIsOwner = ETrue;
            }
        }
    }

void CT_DataSIPContentTypeHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    TBool dataOK = ETrue;    
    TPtrC temp;
    if( !GetStringFromConfig(aSection, KFldMediaType, temp) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldMediaType);        
        dataOK = EFalse;
        }    
    TPtrC temp1;
    if( !GetStringFromConfig(aSection, KFldMediaSubtype, temp1) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldMediaSubtype);
        dataOK = EFalse;
        }
    
    if(!dataOK)
        {
        SetBlockResult(EFail);
        }
    else
        {
        TBuf8<KMaxTestExecuteCommandLength> mediatype;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(mediatype, temp);
        TBuf8<KMaxTestExecuteCommandLength> mediasubtype;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(mediasubtype, temp1);                
        INFO_PRINTF1(_L("call CSIPContentTypeHeader::NewLC(const TDesC8&, const TDesC8&)"));
        TRAPD(err, iSIPContentTypeHeader = CSIPContentTypeHeader::NewLC(mediatype, mediasubtype); CleanupStack::Pop());
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            iIsOwner = ETrue;
            }
        }
    }

void CT_DataSIPContentTypeHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
    {
    TPtrC temp;
    if( !GetStringFromConfig(aSection, KFldHeaderValue, temp) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldHeaderValue);
        SetBlockResult(EFail);
        }
    else
        {
        TBuf8<KMaxTestExecuteCommandLength> headervalue;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(headervalue, temp);
        INFO_PRINTF1(_L("call CSIPContentTypeHeader::DecodeL(const TDesC8&)"));
        TRAPD(err, iSIPContentTypeHeader = CSIPContentTypeHeader::DecodeL(headervalue));
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            iIsOwner = ETrue;
            }
        }
    }

void CT_DataSIPContentTypeHeader::DoCmdMediaType(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPContentTypeHeader::MediaType()"));
    const TPtrC8 ret = iSIPContentTypeHeader->MediaType();
    TBuf<KMaxTestExecuteCommandLength> temp1;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(temp1, ret);
    INFO_PRINTF2(_L("MediaType: %S"), &temp1);
    
    TPtrC temp;
    if( GetStringFromConfig(aSection, KFldExpected, temp) )
        {
        TBuf8<KMaxTestExecuteCommandLength> expected;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(expected, temp);
        if(ret != expected)
            {
            ERR_PRINTF3(KLogNotExpectedValue1, &temp1, &temp);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPContentTypeHeader::DoCmdSetMediaTypeL(const TTEFSectionName& aSection)
    {
    TPtrC temp;
    if( !GetStringFromConfig(aSection, KFldMediaType, temp) )
        {        
        ERR_PRINTF2(KLogMissingParameter, &KFldMediaType);
        SetBlockResult(EFail);
        }
    else
        {
        TBuf8<KMaxTestExecuteCommandLength> mediatype;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(mediatype, temp);
        INFO_PRINTF1(_L("call CSIPContentTypeHeader::SetMediaTypeL(const TDesC8&)"));
        TRAPD(err, iSIPContentTypeHeader->SetMediaTypeL(mediatype));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    }

void CT_DataSIPContentTypeHeader::DoCmdMediaSubtype(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPContentTypeHeader::MediaSubtype()"));
    const TPtrC8 ret = iSIPContentTypeHeader->MediaSubtype();
    TBuf<KMaxTestExecuteCommandLength> temp1;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(temp1, ret);
    INFO_PRINTF2(_L("MediaSubtype: %S"), &temp1);
    
    TPtrC temp;
    if( GetStringFromConfig(aSection, KFldExpected, temp) )
        {
        TBuf8<KMaxTestExecuteCommandLength> expected;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(expected, temp);
        if(ret != expected)
            {
            ERR_PRINTF3(KLogNotExpectedValue1, &temp1, &temp);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPContentTypeHeader::DoCmdSetMediaSubtypeL(const TTEFSectionName& aSection)
    {
    TPtrC temp;
    if( !GetStringFromConfig(aSection, KFldMediaSubtype, temp) )
        {        
        ERR_PRINTF2(KLogMissingParameter, &KFldMediaSubtype);
        SetBlockResult(EFail);
        }
    else
        {
        TBuf8<KMaxTestExecuteCommandLength> mediasubtype;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(mediasubtype, temp);
        INFO_PRINTF1(_L("call CSIPContentTypeHeader::SetMediaSubtypeL(const TDesC8&)"));
        TRAPD(err, iSIPContentTypeHeader->SetMediaSubtypeL(mediasubtype));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    }

void CT_DataSIPContentTypeHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
    {
    TPtrC filename;
    if( !GetStringFromConfig(aSection, KFldFileName, filename) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldFileName);
        SetBlockResult(EFail);
        }
    else
        {
        // ReadStore creation
        CDirectFileStore* store = CDirectFileStore::OpenLC(FileServer(), filename, EFileStream | EFileRead);
        TStreamId id = store->Root();
        RStoreReadStream readstream;
        readstream.OpenLC(*store, id);
        
        INFO_PRINTF1(_L("call CSIPContentTypeHeader::InternalizeL(RReadStream&)"));
        CSIPHeaderBase* headerbase = NULL;
        TRAPD(err, headerbase = CSIPContentTypeHeader::InternalizeValueL(readstream));
        delete iSIPContentTypeHeader;
        iSIPContentTypeHeader = dynamic_cast<CSIPContentTypeHeader*>(headerbase);
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        
        CleanupStack::PopAndDestroy(2);
        }
    }

void CT_DataSIPContentTypeHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPContentTypeHeader::~CSIPContentTypeHeader()"));
    DestroyData();
    }

void CT_DataSIPContentTypeHeader::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }
