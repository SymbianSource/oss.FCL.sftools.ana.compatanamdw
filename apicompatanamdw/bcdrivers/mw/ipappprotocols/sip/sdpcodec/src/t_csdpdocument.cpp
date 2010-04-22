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


#include "T_SIPUtil.h"
#include "t_csdpdocument.h"
#include "t_csdporiginfield.h"
#include "t_csdpconnectionfield.h"
#include "t_csdpmediafield.h"
#include <utf.h>
#include <s32mem.h> 

/*@{*/
_LIT(KCmdDestroy,               "~");
_LIT(KCmdNewL,                  "NewL");
_LIT(KCmdSetOrginField,         "SetOriginField");
_LIT(KCmdSetSessionNameL,       "SetSessionNameL");
_LIT(KCmdSetConnectionField,    "SetConnectionField");
_LIT(KCmdMediaFields_Append,    "MediaFields_Append");
_LIT(KCmdEncodeL,               "EncodeL");

//Fields 
_LIT(KFldSdpOriginField,        "origfield");
_LIT(KFldSdpConnectionField,    "connfield");
_LIT(KFldSdpMediaField,         "mediafield");
_LIT(KFldSessionName,           "sessname");

//Error
_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");

CT_DataSdpDocument*  CT_DataSdpDocument::NewL()
    {
    CT_DataSdpDocument* self = new (ELeave)CT_DataSdpDocument;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    
}

CT_DataSdpDocument::~CT_DataSdpDocument()
    {
    DestroyData();
    
    if(CT_SIPUtil::iContent)
        {
        delete CT_SIPUtil::iContent;
        }
    }

TBool CT_DataSdpDocument::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
    {
    TBool ret=ETrue;
    
    if ( aCommand==KCmdDestroy )
        {
        DoCmdDestructor(aSection);
        }
    else if ( aCommand==KCmdNewL )
        {
        DoCmdNewL(aSection);
        }
    else if ( aCommand==KCmdSetOrginField )
        {
        DoCmdSetOrginFieldL(aSection);
        }
    else if ( aCommand==KCmdSetSessionNameL )
        {
        DoCmdSetSessionNameL(aSection);
        }
    else if ( aCommand==KCmdSetConnectionField )
        {
        DoCmdSetConnectionFieldL(aSection);
        }
    else if ( aCommand==KCmdMediaFields_Append )
        {
        DoCmdMediaFields_AppendL(aSection);
        }
    else if ( aCommand==KCmdEncodeL )
        {
        DoCmdEncodeL(aSection);
        }
    else 
        {
        ret=EFalse;
        }

    return ret; 
    }

TAny* CT_DataSdpDocument::GetObject()
    {
    return iSdpDocument;
    }

void CT_DataSdpDocument::SetObjectL(TAny* aAny)
    {
    iSdpDocument = static_cast<CSdpDocument*>(aAny);
    }

void CT_DataSdpDocument::DisownObjectL()
    {
    iSdpDocument=NULL;
    }

void CT_DataSdpDocument::DestroyData()
    {
    delete iSdpDocument;
    iSdpDocument=NULL;       
    }

CT_DataSdpDocument::CT_DataSdpDocument() 
:   CDataWrapperBase(), iSdpDocument(NULL)
    {
    }

void CT_DataSdpDocument::ConstructL()
    {
    }

void CT_DataSdpDocument::DoCmdNewL(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSdpDocument::NewL()"));
    TRAPD(err, iSdpDocument = CSdpDocument::NewL());
    
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void CT_DataSdpDocument::DoCmdSetOrginFieldL(const TTEFSectionName& aSection)
    {
    CSdpOriginField* field = NULL;
    if( !CT_SIPUtil::GetSdpOriginFieldL(*this, aSection, KFldSdpOriginField, field) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSdpOriginField);
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSdpDocument::SetOriginField(CSdpOriginField*)"));
        iSdpDocument->SetOriginField(field);
        
        TPtrC wrapperName;
        (void)GetStringFromConfig(aSection, KFldSdpOriginField, wrapperName);
        CT_DataSdpOriginField* wrapper = static_cast<CT_DataSdpOriginField*>(GetDataWrapperL(wrapperName));
        wrapper->SetIsOwner(EFalse);
        }
    }

void CT_DataSdpDocument::DoCmdSetSessionNameL(const TTEFSectionName& aSection)
    {
    TPtrC temp;
    if (!GetStringFromConfig(aSection, KFldSessionName, temp))
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSessionName);
        SetBlockResult(EFail);
        }
    else
        {
        TBuf8<KMaxTestExecuteCommandLength> name;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(name, temp);
        INFO_PRINTF1(_L("call CSdpDocument::SetSessionNameL(const TDesC8&)"));
        TRAPD(err, iSdpDocument->SetSessionNameL(name));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    }

void CT_DataSdpDocument::DoCmdSetConnectionFieldL(const TTEFSectionName& aSection)
    {
    CSdpConnectionField* field = NULL;
    if( !CT_SIPUtil::GetSdpConnectionFieldL(*this, aSection, KFldSdpConnectionField, field) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSdpConnectionField);
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSdpDocument::SetConnectionField(CSdpConnectionField*)"));
        iSdpDocument->SetConnectionField(field);
        
        TPtrC wrapperName;
        (void)GetStringFromConfig(aSection, KFldSdpConnectionField, wrapperName);
        CT_DataSdpConnectionField* wrapper = static_cast<CT_DataSdpConnectionField*>(GetDataWrapperL(wrapperName));
        wrapper->SetIsOwner(EFalse);
        }
    }

void CT_DataSdpDocument::DoCmdMediaFields_AppendL(const TTEFSectionName& aSection)
    {
    CSdpMediaField* field = NULL;
    if( !CT_SIPUtil::GetSdpMediaFieldL(*this, aSection, KFldSdpMediaField, field) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSdpMediaField);
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSdpDocument::MediaFields() ::Append(CSdpMediaField*)"));
        iSdpDocument->MediaFields().Append(field);
        
        TPtrC wrapperName;
        (void)GetStringFromConfig(aSection, KFldSdpMediaField, wrapperName);
        CT_DataSdpMediaField* wrapper = static_cast<CT_DataSdpMediaField*>(GetDataWrapperL(wrapperName));
        wrapper->SetIsOwner(EFalse);
        }
    }

void CT_DataSdpDocument::DoCmdEncodeL(const TTEFSectionName& /*aSection*/)
    {
    const TInt maxbuflen = 1024;
    CBufFlat* buf = CBufFlat::NewL( maxbuflen );
    CleanupStack::PushL( buf );
    RBufWriteStream writeStream;
    writeStream.Open( *buf, 0 );

    INFO_PRINTF1(_L("call CSdpDocument::EncodeL(RWriteStream&)"));
    TRAPD(err, iSdpDocument->EncodeL(writeStream));
    
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    else
        {
        if(CT_SIPUtil::iContent)
            {
            delete CT_SIPUtil::iContent;
            CT_SIPUtil::iContent = NULL;
            }
        CT_SIPUtil::iContent = buf->Ptr(0).AllocL();
        }
    
    writeStream.Close();
    CleanupStack::PopAndDestroy(buf);
    }


void CT_DataSdpDocument::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSdpDocument::~CSdpDocument()"));
    DestroyData();
    }


