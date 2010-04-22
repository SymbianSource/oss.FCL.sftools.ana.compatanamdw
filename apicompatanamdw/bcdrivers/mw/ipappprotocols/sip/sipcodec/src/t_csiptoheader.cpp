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

#include "t_csiptoheader.h"
#include "t_csipaddress.h"
#include <utf.h>
#include <s32file.h>

//	Epoc Includes

/*@{*/
_LIT(KCmdNewL,								"NewL");
_LIT(KCmdNewLC,                             "NewLC");
_LIT(KCmdDisown,							"Disown");
_LIT(KCmdDecodeL,                      	    "DecodeL");
_LIT(KCmdInternalizeValueL,                 "InternalizeValueL");
_LIT(KDestructor,							"~");
_LIT(KFldSIPAddress,                        "sipaddress");
_LIT(KFldSIPFromToHeaderBase,               "sipfromtoheaderbase");
_LIT(KFldSIPToHeader,                       "siptoheader");
_LIT(KFldHeaderValue,                       "headervalue");
_LIT(KFldFileName,                          "filename");
_LIT(KLogError,								"Error=%d");
_LIT(KLogErrMissingPara, 					"Missing parameter '%S'");

CT_DataSIPToHeader* CT_DataSIPToHeader::NewL()
	{
	CT_DataSIPToHeader*	ret=new (ELeave) CT_DataSIPToHeader();
	CleanupStack::PushL(ret);
	ret->ConstructL();
	CleanupStack::Pop(ret);
	return ret;
	}

CT_DataSIPToHeader::CT_DataSIPToHeader():CT_DataSIPFromToHeaderBase(), iIsOwner(ETrue),iSIPToHeader(NULL)

	{
	}

void CT_DataSIPToHeader::ConstructL()
	{
	}

CT_DataSIPToHeader::~CT_DataSIPToHeader()
	{
	DestroyData();
	}

/**
* Return a pointer to the object that the data wraps
*
* @return pointer to the object that the data wraps
*/
TAny* CT_DataSIPToHeader::GetObject()
	{
	return iSIPToHeader;
	}

void CT_DataSIPToHeader::SetObjectL(TAny* aAny)
    {
    iSIPToHeader=static_cast<CSIPToHeader*> (aAny);
    }

void CT_DataSIPToHeader::DisownObjectL()
	{
	iSIPToHeader=NULL;
	iIsOwner = EFalse;
	}

void CT_DataSIPToHeader::DestroyData()
	{
	if (iIsOwner)
	    {
        delete iSIPToHeader;
        iSIPToHeader = NULL;
        iIsOwner = EFalse;
        }
	}

CSIPHeaderBase* CT_DataSIPToHeader::GetSIPHeaderBase() const
    {
    return iSIPToHeader;
    }

/**
Delegates the commands to a function

* @internalComponent
* @param aCommand Current command
* @param aSection Current ini file command section
* @param aAsyncErrorIndex index of command for SetAsyncError()
* @return TBool Returns whether the command was executed or not
*/
TBool CT_DataSIPToHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
	{
	TBool	retVal = ETrue;
	
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
	    retVal = CT_DataSIPFromToHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
	    }
	return retVal;  
	}

void CT_DataSIPToHeader::DoCmdNewL(const TTEFSectionName& aSection)
    { 
    INFO_PRINTF1(_L("call CSIPToHeader::NewL()"));
    TPtrC name;
    CSIPAddress* sipAddress = NULL;
    CSIPFromToHeaderBase* sipFromToHeaderBase = NULL;
    if( GetStringFromConfig(aSection, KFldSIPAddress, name) )
        {
        sipAddress = static_cast<CSIPAddress*> (GetDataObjectL(name));
        INFO_PRINTF1(_L("execute CSIPToHeader::NewL(CSIPAddress *)"));
        TRAPD(err, iSIPToHeader = CSIPToHeader::NewL(sipAddress));
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            CT_DataSIPAddress* wrapper = static_cast<CT_DataSIPAddress*> (GetDataWrapperL(name));
            wrapper->SetIsOwner(EFalse);
            }
        }
    else if( GetStringFromConfig(aSection, KFldSIPFromToHeaderBase, name) )
        {
        sipFromToHeaderBase = static_cast<CSIPFromToHeaderBase*> (GetDataObjectL(name));
        INFO_PRINTF1(_L("execute CSIPToHeader::NewL(const CSIPFromToHeaderBase &)"));
        TRAPD(err, iSIPToHeader = CSIPToHeader::NewL(*sipFromToHeaderBase));
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    else        
        {
        ERR_PRINTF1(_L("Missing parameter"));
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPToHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    { 
    INFO_PRINTF1(_L("call CSIPToHeader::NewLC()"));
    TPtrC name;
    CSIPAddress* sipAddress = NULL;
    CSIPFromToHeaderBase* sipFromToHeaderBase = NULL;
    if( GetStringFromConfig(aSection, KFldSIPAddress, name) )
        {
        sipAddress = static_cast<CSIPAddress*> (GetDataObjectL(name));
        INFO_PRINTF1(_L("execute CSIPToHeader::NewLC(CSIPAddress *)"));
        TRAPD(err, iSIPToHeader = CSIPToHeader::NewLC(sipAddress);CleanupStack::Pop(););
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            CT_DataSIPAddress* wrapper = static_cast<CT_DataSIPAddress*> (GetDataWrapperL(name));
            wrapper->SetIsOwner(EFalse);
            }
        }
    else if( GetStringFromConfig(aSection, KFldSIPFromToHeaderBase, name) )
        {
        sipFromToHeaderBase = static_cast<CSIPFromToHeaderBase*> (GetDataObjectL(name));
        INFO_PRINTF1(_L("execute CSIPToHeader::NewL(const CSIPFromToHeaderBase &)"));
        TRAPD(err, iSIPToHeader = CSIPToHeader::NewLC(*sipFromToHeaderBase);CleanupStack::Pop(););
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    else        
        {
        ERR_PRINTF1(_L("Missing parameter"));
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPToHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
	{
    CSIPToHeader* sipToHeader = NULL;
    TPtrC headerVal;
    TPtrC datSipToHeader;
    if (!GetStringFromConfig(aSection, KFldHeaderValue, headerVal))
        {
        ERR_PRINTF2(KLogErrMissingPara, &KFldHeaderValue());
        SetBlockResult(EFail);
        }
    else
        {
        if(!GetStringFromConfig(aSection, KFldSIPToHeader, datSipToHeader))
            {
            ERR_PRINTF2(KLogErrMissingPara, &KFldSIPToHeader());
            SetBlockResult(EFail);
            }
        else
            {
            TBuf8<KMaxTestExecuteCommandLength> headerVal8;
            CnvUtfConverter::ConvertFromUnicodeToUtf8(headerVal8, headerVal);
            INFO_PRINTF1(_L("execute CSIPToHeader::DecodeL()"));
            TRAPD(err,sipToHeader=CSIPToHeader::DecodeL(headerVal8));
            if (err != KErrNone)
                {
                ERR_PRINTF2(KLogError, err);
                SetError(err);
                }
            else
                {
                CT_DataSIPToHeader* wrapper = static_cast<CT_DataSIPToHeader*> (GetDataWrapperL(datSipToHeader));
                wrapper->SetIsOwner(ETrue);
                SetDataObjectL(datSipToHeader, sipToHeader);
                }
            }
        }	
	}

void CT_DataSIPToHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
    {
    TPtrC datFileName;
    if ( !GetStringFromConfig(aSection, KFldFileName, datFileName) )
        {
        ERR_PRINTF2(KLogErrMissingPara, &KFldFileName());
        SetBlockResult(EFail);
        return;
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
        INFO_PRINTF1(_L("execute CSIPToHeader::InternalizeValueL(RReadStream &)"));
        TRAPD(err, iSIPToHeader = (CSIPToHeader*)CSIPToHeader::InternalizeValueL(readstrm));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        // Cleanup
        CleanupStack::PopAndDestroy(2, readstore);
        }
    }
    
void CT_DataSIPToHeader::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }
