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
#include "DataWrapperBase.h"
#include <utf.h>
#include <badesca.h>
#include <sipprofile.h> 
#include <sipprofiletypeinfo.h>
#include <sipmanagedprofile.h>
#include <sipcontenttypeheader.h>
#include <sipstrings.h>
#include <sipstrconsts.h>
#include <uri8.h>
#include <stdlib.h>

#include <commdb.h>             

#include <apdatahandler.h>
#include <apaccesspointitem.h>

RPointerArray<TAny> CT_SIPUtil::iMemArray;
TInt CT_SIPUtil::iAvaiableSpace = 0;
TInt CT_SIPUtil::iBiggestBlock = 0;
TUint32 CT_SIPUtil::iProfileId = 0;
HBufC8* CT_SIPUtil::iContent = NULL;

#define INFO_PRINTF1_UTIL(p1)                   aDataWrapper.Logger().LogExtra(((TText8*)__FILE__), __LINE__, ESevrInfo, (p1))
#define INFO_PRINTF2_UTIL(p1, p2)                aDataWrapper.Logger().LogExtra(((TText8*)__FILE__), __LINE__, ESevrInfo, (p1), (p2))
_LIT(KFormatEntryField, "%S_%S");
_LIT(KFormatFieldNumber, "%S%d");
_LIT(KSIPProfileEInternet,"EInternet");
_LIT(KSIPProfileEIms,"EIms");
_LIT(KSIPProfileEOther,"EOther");


void CT_SIPUtil::EatupMemory(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName)
    {
    // read left size in memory from INI
    TInt leftsize = 0;
    TBool ret = aDataWrapper.GetIntFromConfig(aSectName, aKeyName, leftsize);
    if (!ret || leftsize == 0)
        return;

    // eat memory until fail to avaiable memory is less than is left size  
    TInt nTotalSize = User::Heap().Size();
    TAny* mem = User::AllocZ(nTotalSize);

    if (mem)
        iMemArray.Append(mem);

    do
        {
        mem = User::AllocZ(leftsize);
        if (mem)
            {
            iMemArray.Append(mem);
            }
        }
    while (mem);

    // get avaiable memory, we can't log here, because no enough memory to write log
    // so we have to write log after free memory
    iAvaiableSpace = User::Available(iBiggestBlock);
    }

void CT_SIPUtil::FreeEatenMemory(CDataWrapperBase& aDataWrapper)
    {
    for (TInt i = 0; i < iMemArray.Count(); i++)
        {
        TAny* mem = iMemArray[i];
        User::Free(mem);
        }

    iMemArray.Reset();

    // write memory status after eat memory
    aDataWrapper.INFO_PRINTF3(_L("CT_GraphicsUtil::FreeEatenMemory, before free memory, avaiable=%d byte biggestblock=%d byte"),iAvaiableSpace,iBiggestBlock);
    }

void CT_SIPUtil::ConvertToUtf8(const TDesC& aSrc, TDes8& aDest)
    {
    HBufC8* tmp = HBufC8::NewL(aSrc.Length());
    TPtr8 tmpvalue(tmp->Des());
    CnvUtfConverter::ConvertFromUnicodeToUtf8(tmpvalue, aSrc);
    aDest.Copy(tmpvalue);
    delete tmp;
    tmp = NULL;
    }

void CT_SIPUtil::ConvertToUnicode(const TDesC8& aSrc, TDes& aDest)
    {
    HBufC* tmp = HBufC::NewL(aSrc.Length());
    TPtr tmpvalue(tmp->Des());
    CnvUtfConverter::ConvertToUnicodeFromUtf8(tmpvalue, aSrc);
    aDest.Copy(tmpvalue);
    delete tmp;
    tmp = NULL;
    }

TBool CT_SIPUtil::GetStringF(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName, RStringF& aData)
    {
    TPtrC ptr;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, ptr);
    if (ret)
        {
        if (ptr == _L("ACK"))
            {
            aData = SIPStrings::StringF(SipStrConsts::EAck);
            }
        else if(ptr == _L("MESSAGE"))
            {
            aData = SIPStrings::StringF(SipStrConsts::EMessage);
            }
        else if(ptr == _L("INVITE"))
            {
            aData = SIPStrings::StringF(SipStrConsts::EInvite);
            }
        else if (ptr == _L("EPhraseOk"))
            {
            aData = SIPStrings::StringF(SipStrConsts::EPhraseOk);
            }
        else if (ptr == _L("EPhraseRinging"))
            {
            aData = SIPStrings::StringF(SipStrConsts::EPhraseRinging);
            }  
        else if(ptr == _L("ERegister"))
            {
            aData = SIPStrings::StringF(SipStrConsts::ERegister);
            }
        else if(ptr == _L("EInvite"))
            {
            aData = SIPStrings::StringF(SipStrConsts::EInvite);
            }      
        else if(ptr == _L("ESubscribe"))
            {
            aData = SIPStrings::StringF(SipStrConsts::ESubscribe);
            }  
        else if(ptr == _L("From"))
            {
            aData = SIPStrings::StringF(SipStrConsts::EFromHeader);
            }
        else if(ptr == _L("To"))
            {
            aData = SIPStrings::StringF(SipStrConsts::EToHeader);
            }
        else if(ptr == _L("EExpires"))
            {
            aData = SIPStrings::StringF(SipStrConsts::EExpires);
            }
        else if(ptr == _L("ETag"))
            {
            aData = SIPStrings::StringF(SipStrConsts::ETag);
            }
        else if(ptr == _L("EEmpty"))
            {
            aData = SIPStrings::StringF(SipStrConsts::EEmpty);
            }
        else if(ptr == _L("EContentEncodingHeader"))
            {
            aData = SIPStrings::StringF(SipStrConsts::EContentEncodingHeader);
            }
        else if(ptr == _L("ESupportedHeader"))
            {
            aData = SIPStrings::StringF(SipStrConsts::ESupportedHeader);
            }
        else if(ptr == _L("EUnsupportedHeader"))
            {
            aData = SIPStrings::StringF(SipStrConsts::EUnsupportedHeader);
            }
        else
            {
            TInt intVal = 0;
            ret = aDataWrapper.GetIntFromConfig(aSectName, aKeyName, intVal);
            if (ret)
                {
                aData = SIPStrings::StringF((SipStrConsts::TStrings) intVal);
                }
            }
        }

    return ret;
    }

TBool CT_SIPUtil::GetSIPProfileTypeInfo(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName,
        TSIPProfileTypeInfo& aInfo)
    {
    TBuf<KMaxTestExecuteCommandLength> tempStore;
    _LIT(KFldProfileName, "name");
    _LIT(KFldProfileClass, "class");

    TPtrC profileName;
    TPtrC profileClass;
    tempStore.Format(KFormatEntryField, &aKeyName, &KFldProfileName);
    if (aDataWrapper.GetStringFromConfig(aSectName, tempStore, profileName))
        {
        ConvertToUtf8(profileName, aInfo.iSIPProfileName);
        tempStore.Format(KFormatEntryField, &aKeyName, &KFldProfileClass);
        if (aDataWrapper.GetStringFromConfig(aSectName, tempStore,
                profileClass))
            {
            if (profileClass == KSIPProfileEInternet())
                {
                aInfo.iSIPProfileClass = TSIPProfileTypeInfo::EInternet;
                }
            else if (profileClass == KSIPProfileEIms())
                {
                aInfo.iSIPProfileClass = TSIPProfileTypeInfo::EIms;
                }
            else if (profileClass == KSIPProfileEOther())
                {
                aInfo.iSIPProfileClass = TSIPProfileTypeInfo::EOther;
                }
            else
                {
                return EFalse;
                }
            return ETrue;
            }
        }
    return EFalse;
    }

TBool CT_SIPUtil::GetMDesC8ArrayL(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName, MDesC8Array *aArray)
    {
    TBuf<KMaxTestExecuteNameLength> tempStore;
    TInt index;
    TBool moreData = ETrue;
    TBuf8<KMaxTestExecuteCommandLength> val;

    for (index = 1; moreData; ++index)
        {
        TPtrC temp;
        tempStore.Format(KFormatFieldNumber, &aKeyName, index);
        if (!aDataWrapper.GetStringFromConfig(aSectName, tempStore, temp))
            {
            moreData = EFalse;
            }
        else
            {
            // TODO: should this copy operation be needed?
            TBuf<KMaxTestExecuteCommandLength> tempBuf;
            tempBuf.Copy(temp);
            CnvUtfConverter::ConvertFromUnicodeToUtf8(val, tempBuf);
            ((CDesC8Array*) aArray)->AppendL(val);
            }
        }
    return index > 2; // No data got from config.
    }

TBool CT_SIPUtil::GetSIP(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName, CSIP*& aData)
    {
    // get CSIPProfile data object from parameters
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        // Data object found
        aData = static_cast<CSIP*> (aDataWrapper.GetDataObjectL(name));
        }

    return ret;
    }

TBool CT_SIPUtil::GetSIPProfile(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName, CSIPProfile*& aData)
    {
    // get CSIPProfile data object from parameters
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        // Data object found
        aData = static_cast<CSIPProfile*> (aDataWrapper.GetDataObjectL(name));
        }

    return ret;
    }

TBool CT_SIPUtil::GetSIPProfileParameter(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName, TUint32& aResult)
    {
    TPtrC result;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, result);
    if (ret)
        {
        if (result == _L("KSIPProfileId"))
            {
            aResult = KSIPProfileId;
            }
        else if (result == _L("KSIPProviderName"))
            {
            aResult = KSIPProviderName;
            }
        else if (result == _L("KSIPAccessPointId"))
            {
            aResult = KSIPAccessPointId;
            }
        else if (result == _L("KSIPSigComp"))
            {
            aResult = KSIPSigComp;
            }
        else if (result == _L("KSIPSecurityNegotiation"))
            {
            aResult = KSIPSecurityNegotiation;
            }
        else if (result == _L("KSIPAutoRegistration"))
            {
            aResult = KSIPAutoRegistration;
            }
        else if (result == _L("KSIPUserAor"))
            {
            aResult = KSIPUserAor;
            }
        else if (result == _L("KSIPProfileRegistered"))
            {
            aResult = KSIPProfileRegistered;
            }
        else if (result == _L("KSIPRegisteredAors"))
            {
            aResult = KSIPRegisteredAors;
            }
        else if (result == _L("KSIPNegotiatedSecurityMechanism"))
            {
            aResult = KSIPNegotiatedSecurityMechanism;
            }
        else if (result == _L("KSIPDefaultProfile"))
            {
            aResult = KSIPDefaultProfile;
            }
        else if (result == _L("KSIPContactHeaderParams"))
            {
            aResult = KSIPContactHeaderParams;
            }
        else if (result == _L("KSIPRegisteredContact"))
            {
            aResult = KSIPRegisteredContact;
            }
        else if (result == _L("KSIPRegistrar"))
            {
            aResult = KSIPRegistrar;
            }
        else if (result == _L("KSIPOutboundProxy"))
            {
            aResult = KSIPOutboundProxy;
            }
        else if (result == _L("KSIPDigestUserName"))
            {
            aResult = KSIPDigestUserName;
            }
        else if (result == _L("KSIPDigestRealm"))
            {
            aResult = KSIPDigestRealm;
            }
        else if (result == _L("KSIPServerAddress"))
            {
            aResult = KSIPServerAddress;
            }
        else if (result == _L("KSIPDigestPassword"))
            {
            aResult = KSIPDigestPassword;
            }
        else if (result == _L("KSIPPrivateIdentity"))
            {
            aResult = KSIPPrivateIdentity;
            }
        else if (result == _L("KSIPHeaders"))
            {
            aResult = KSIPHeaders;
            }
        else
            {
            aResult = 0;
            ret = EFalse;
            }
        }

    return ret;
    }

TBool CT_SIPUtil::GetSIPProfileClass(const TDesC& aSIPProfileClassStr,
        TSIPProfileTypeInfo::TSIPProfileClass& aSIPProfileClass)
    {
    TBool found = ETrue;

    if (aSIPProfileClassStr == KSIPProfileEInternet())
        {
        aSIPProfileClass = TSIPProfileTypeInfo::EInternet;
        }
    else if (aSIPProfileClassStr == KSIPProfileEIms())
        {
        aSIPProfileClass = TSIPProfileTypeInfo::EIms;
        }
    else if (aSIPProfileClassStr == KSIPProfileEOther())
        {
        aSIPProfileClass = TSIPProfileTypeInfo::EOther;
        }
    else
        {
        found = EFalse;
        }

    return found;
    }

TBool CT_SIPUtil::GetSIPProfileClassStr(
        const TSIPProfileTypeInfo::TSIPProfileClass& aSIPProfileClass,
        TDes& aSIPProfileClassStr)
    {
    TBool found = ETrue;

    if (aSIPProfileClass == TSIPProfileTypeInfo::EInternet)
        {
        aSIPProfileClassStr.Copy(_L("TSIPProfileTypeInfo::EInternet "));
        }
    else if (aSIPProfileClass == TSIPProfileTypeInfo::EIms)
        {
        aSIPProfileClassStr.Copy(_L("TSIPProfileTypeInfo::EIms "));
        }
    else if (aSIPProfileClass == TSIPProfileTypeInfo::EOther)
        {
        aSIPProfileClassStr.Copy(_L("TSIPProfileTypeInfo::EOther "));
        }
    else
        {
        found = EFalse;
        }

    return found;
    }

TBool CT_SIPUtil::GetEvent(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName,
        MSIPProfileRegistryObserver::TEvent& aData)
    {
    TPtrC ptr;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, ptr);
    if (ret)
        {
        if (ptr == _L("EProfileCreated"))
            {
            aData = MSIPProfileRegistryObserver::EProfileCreated;
            }
        else if (ptr == _L("EProfileUpdated"))
            {
            aData = MSIPProfileRegistryObserver::EProfileUpdated;
            }
        else if (ptr == _L("EProfileRegistered"))
            {
            aData = MSIPProfileRegistryObserver::EProfileRegistered;
            }
        else if (ptr == _L("EProfileDeregistered"))
            {
            aData = MSIPProfileRegistryObserver::EProfileDeregistered;
            }
        else if (ptr == _L("EProfileDestroyed"))
            {
            aData = MSIPProfileRegistryObserver::EProfileDestroyed;
            }
        else
            {
            TInt intVal = 0;
            ret = aDataWrapper.GetIntFromConfig(aSectName, aKeyName, intVal);
            if (ret)
                {
                aData = (MSIPProfileRegistryObserver::TEvent) intVal;
                }
            }
        }

    return ret;
    }

TUint32 CT_SIPUtil::GetIAPIDL(const TDesC& aAccessPoint)
    {
    TUint32 apId = 0;

    // search IAPs

    // Open view to IAP table, select all outgoing IAPs.    
    CCommsDatabase* commsDatabase = CCommsDatabase::NewL();
    CleanupStack::PushL(commsDatabase);
    CCommsDbTableView* searchView =
            commsDatabase->OpenIAPTableViewMatchingBearerSetLC(0xffffffff,
                    ECommDbConnectionDirectionOutgoing);

    TInt error = searchView->GotoFirstRecord();
    if (error == KErrNone)
        {
        // Buffer for reading IAP names from CommsDat. Buffer size is set to
        // maximum readable value from CommsDat.
        TBuf<KCommsDbSvrMaxColumnNameLength> apName;

        // Go through all IAPs.
        while (error == KErrNone)
            {
            apName.FillZ();
            // Read IAP ID and name from IAP table in CommsDat.
            TRAPD(err, searchView->ReadTextL( TPtrC( COMMDB_NAME ), apName ));

            if (err == KErrNone && apName.Match(aAccessPoint) == KErrNone)
                {
                    TRAP(err, searchView->ReadUintL( TPtrC( COMMDB_ID ), apId ));
                break;
                }
            error = searchView->GotoNextRecord();
            }
        }

    CleanupStack::PopAndDestroy(2); // searchView, commsDatabase


    return apId;
    }

TUint32 CT_SIPUtil::AddAccessPointL(const TDesC& aAccessPoint)
    {
    TUint32 apId = 0;
    CCommsDatabase* commsDatabase = CCommsDatabase::NewL();
    CleanupStack::PushL(commsDatabase);
    CApAccessPointItem *wlan = CApAccessPointItem::NewLC();
    wlan->SetNamesL(aAccessPoint);
    wlan->SetBearerTypeL(EApBearerTypeWLAN);
    wlan->WriteTextL(EApWlanNetworkName, aAccessPoint);
    CApDataHandler *handler = CApDataHandler::NewLC(*commsDatabase);
    apId = handler->CreateFromDataL(*wlan);
    CleanupStack::PopAndDestroy(3); // 
    return apId;
    }

TBool CT_SIPUtil::GetState(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName,
        CSIPTransactionBase::TState& aData)
    {
    TPtrC ptr;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, ptr);
    if (ret)
        {
        if (ptr == _L("ETrying"))
            {
            aData = CSIPTransactionBase::ETrying;
            }
        else if (ptr == _L("ECalling"))
            {
            aData = CSIPTransactionBase::ECalling;
            }
        else if (ptr == _L("EProceeding"))
            {
            aData = CSIPTransactionBase::EProceeding;
            }
        else if (ptr == _L("ECompleted"))
            {
            aData = CSIPTransactionBase::ECompleted;
            }
        else if (ptr == _L("EConfirmed"))
            {
            aData = CSIPTransactionBase::EConfirmed;
            }
        else if (ptr == _L("ETerminated"))
            {
            aData = CSIPTransactionBase::ETerminated;
            }
        else if (ptr == _L("EConstructing"))
            {
            aData = CSIPTransactionBase::EConstructing;
            }
        else
            {
            TInt intVal = 0;
            ret = aDataWrapper.GetIntFromConfig(aSectName, aKeyName, intVal);
            if (ret)
                {
                aData = (CSIPTransactionBase::TState) intVal;
                }
            }
        }

    return ret;
    }

TBool CT_SIPUtil::GetSIPResponseElements(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName,
        CSIPResponseElements *& aData)
    {
    // get CSIPResponseElements data object from parameters
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData
                = static_cast<CSIPResponseElements*> (aDataWrapper.GetDataObjectL(
                        name));
        }

    return ret;
    }

TBool CT_SIPUtil::GetSIPContentTypeHeaderFromConfigL(
        CDataWrapperBase& aDataWrapper, const TDesC& aSectName,
        const TDesC& aKeyName, CSIPContentTypeHeader*& aData)
    {
    // Create CSIPContentTypeHeader object from parameters
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData = static_cast<CSIPContentTypeHeader*> (aDataWrapper.GetDataObjectL(name));
        }

    return ret;
    }

TBool CT_SIPUtil::GetSIPTransactionL(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName,
        CSIPTransactionBase*& aData)
    {
    // get SIP Transaction data object from parameters
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData = static_cast<CSIPTransactionBase*> (aDataWrapper.GetDataObjectL(name));
        }

    return ret;
    }

TBool CT_SIPUtil::GetSIPClientTransactionL(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName,
        CSIPClientTransaction*& aData)
    {
    // get SIP Transaction data object from parameters
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData = static_cast<CSIPClientTransaction*> (aDataWrapper.GetDataObjectL(name));
        }

    return ret;
    }

TBool CT_SIPUtil::GetSIPServerTransactionL(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName,
        CSIPServerTransaction*& aData)
    {
    // get SIP Transaction data object from parameters
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData = static_cast<CSIPServerTransaction*> (aDataWrapper.GetDataObjectL(name));
        }

    return ret;
    }

TBool CT_SIPUtil::GetSIPHeadersL(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName, RPointerArray<
                CSIPHeaderBase>& aArray)
    {
    TBool moreData = ETrue;
    TBuf<KMaxTestExecuteNameLength> tempStore;
    TInt index;
    for (index = 1; moreData; ++index)
        {
        TPtrC name;
        tempStore.Format(KFormatFieldNumber, &aKeyName, index);
        if (!aDataWrapper.GetStringFromConfig(aSectName, tempStore, name))
            {
            moreData = EFalse;
            }
        else
            {
            aArray.AppendL(
                    static_cast<CSIPHeaderBase*> (aDataWrapper.GetDataObjectL(
                            name)));
            }
        }
    return index > 2;
    }
TBool CT_SIPUtil::GetSIPFromHeaderL(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName, CSIPFromHeader*& aData)
    {
    // get SIP FromHeader data object from parameters
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData = static_cast<CSIPFromHeader*> (aDataWrapper.GetDataObjectL(
                name));
        }

    return ret;
    }

TBool CT_SIPUtil::GetSIPToHeaderL(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName, CSIPToHeader*& aData)
    {
    // get SIP FromHeader data object from parameters
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData
                = static_cast<CSIPToHeader*> (aDataWrapper.GetDataObjectL(
                        name));
        }

    return ret;
    }

TBool CT_SIPUtil::GetSIPSeqHeaderL(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName, CSIPCSeqHeader*& aData)
    {
    // get CSIPCSeqHeader data object from parameters
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData = static_cast<CSIPCSeqHeader*> (aDataWrapper.GetDataObjectL(
                name));
        }

    return ret;
    }

TBool CT_SIPUtil::GetSIPAddressL(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName, CSIPAddress*& aData)
    {
    // get CSIPAddress data object from parameters
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData = static_cast<CSIPAddress*> (aDataWrapper.GetDataObjectL(name));
        }

    return ret;
    }

TBool CT_SIPUtil::GetUri8L(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName, CUri8*& aData)
    {
    TPtrC uriStr;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, uriStr);
    if (ret)
        {
        TBuf8<KMaxTestExecuteNameLength> uriStr8;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(uriStr8, uriStr);
        TUriParser8 parser;
        TInt err = parser.Parse(uriStr8);
        if (err != KErrNone)
            {
            ret = EFalse;
            }
        else
            {
            aData = CUri8::NewL(parser);
            }
        }

    return ret;
    }

TBool CT_SIPUtil::GetSIPFromToHeaderBaseL(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName,
        CSIPFromToHeaderBase*& aData)
    {
    // get SIP FromToHeaderBase data object from parameters
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData
                = static_cast<CSIPFromToHeaderBase*> (aDataWrapper.GetDataObjectL(
                        name));
        }

    return ret;
    }

TBool CT_SIPUtil::GetStringFFromConfigL(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName,
        const RStringPool& aPool, RStringF& aData)
    {
    // It's user's responsibility to close RStringF and RStringPool objects.
    TPtrC val;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, val);

    if (ret)
        {
        TBuf8<KMaxTestExecuteCommandLength> val8;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(val8, val);
        aData = aPool.OpenFStringL(val8);
        }
    return ret;
    }

TBool CT_SIPUtil::ConvertStringToEnumState(TPtrC& aStrState,
        CSIPConnection::TState& aState)
    {
    TBool ret = ETrue;
    if (aStrState == _L("EActive"))
        {
        aState = CSIPConnection::EActive;
        }
    else if (aStrState == _L("EInactive"))
        {
        aState = CSIPConnection::EInactive;
        }
    else if (aStrState == _L("EInit"))
        {
        aState = CSIPConnection::EInit;
        }
    else if (aStrState == _L("ESuspended"))
        {
        aState = CSIPConnection::ESuspended;
        }
    else if (aStrState == _L("EUnavailable"))
        {
        aState = CSIPConnection::EUnavailable;
        }
    else
        {
        ret = EFalse;
        }

    return ret;
    }

TBool CT_SIPUtil::GetSIPRefreshState(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName,
        CSIPRefresh::TState& aData)
    {
    TPtrC state;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, state);
    if (ret)
        {
        if (state == _L("EInactive"))
            {
            aData = CSIPRefresh::EInactive;
            }
        else if (state == _L("EActive"))
            {
            aData = CSIPRefresh::EActive;
            }
        else if (state == _L("ETerminated"))
            {
            aData = CSIPRefresh::ETerminated;
            }
        else if (state == _L("EConstructing"))
            {
            aData = CSIPRefresh::EConstructing;
            }
        }
    return ret;
    }

TBool CT_SIPUtil::GetSIPMessageElements(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName,
        CSIPMessageElements*& aData)
    {
    // get SIP MessageElements data object from parameters
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData
                = static_cast<CSIPMessageElements*> (aDataWrapper.GetDataObjectL(
                        name));
        }

    return ret;
    }

TBool CT_SIPUtil::GetSIPRefreshL(CDataWrapperBase& aDataWrapper,
        const TDesC& aSectName, const TDesC& aKeyName, CSIPRefresh*& aData)
    {
    // get SIP Refresh data object from parameters
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData = static_cast<CSIPRefresh*> (aDataWrapper.GetDataObjectL(name));
        }

    return ret;
    }

TBool CT_SIPUtil::GetSIPReferToHeaderL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPReferToHeader*& aData)
    {
    // get SIP Refresh data object from parameters
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData = static_cast<CSIPReferToHeader*> (aDataWrapper.GetDataObjectL(name));
        }

    return ret;
    }

TBool CT_SIPUtil::GetSIPDialogL(CDataWrapperBase & aDataWrapper,
        const TDesC & aSectName, const TDesC & aKeyName, CSIPDialog *& aData)
    {
    // get SIP Dialog data object from parameters
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData = static_cast<CSIPDialog*> (aDataWrapper.GetDataObjectL(name));
        }

    return ret;
    }

TBool CT_SIPUtil::GetSIPConnectionL(CDataWrapperBase & aDataWrapper,
        const TDesC & aSectName, const TDesC & aKeyName,
        CSIPConnection *& aData)
    {
    // get SIP Connection data object from parameters
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData = static_cast<CSIPConnection*> (aDataWrapper.GetDataObjectL(
                name));
        }

    return ret;
    }

TBool CT_SIPUtil::GetSIPContactHeaderL(CDataWrapperBase & aDataWrapper,
        const TDesC & aSectName, const TDesC & aKeyName,
        CSIPContactHeader *& aData)
    {
    // get SIP ContactHeader data object from parameters
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData = static_cast<CSIPContactHeader*> (aDataWrapper.GetDataObjectL(name));
        }

    return ret;
    }

TBool CT_SIPUtil::GetSIPRegistrationContextL(CDataWrapperBase & aDataWrapper,
        const TDesC & aSectName, const TDesC & aKeyName,
        MSIPRegistrationContext *& aData)
    {
    // get SIP RegistrationContext data object from parameters
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData = static_cast<MSIPRegistrationContext*> (aDataWrapper.GetDataObjectL(name));
        }

    return ret;
    }

TBool   CT_SIPUtil::GetSIPEventHeaderL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, 
        const TDesC& aKeyName, CSIPEventHeader*& aData)
    {
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData = static_cast<CSIPEventHeader*> (aDataWrapper.GetDataObjectL(name));
        }

    return ret;    
    }
	
TBool CT_SIPUtil::GetSIPDialogState(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPDialog::TState& aData)
    {
    TPtrC result;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, result);
    if(ret)
        {
        if(result==_L("EInit"))
            {
            aData=CSIPDialog::EInit;
            }
        else if(result==_L("EEarly"))
            {
            aData=CSIPDialog::EEarly;
            }
        else if(result==_L("EConfirmed"))
            {
            aData=CSIPDialog::EConfirmed;
            }
        else if(result==_L("ETerminated"))
            {
            aData=CSIPDialog::ETerminated;
            }
        else
            {
            ret = EFalse;
            }
        }
    return ret;
    }	

TBool CT_SIPUtil::GetSIPHeaderBaseL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPHeaderBase*& aData)
    {
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData = static_cast<CSIPHeaderBase*> (aDataWrapper.GetDataObjectL(name));
        }

    return ret;  
    }

TBool CT_SIPUtil::GetSIPRouteHeaderL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPRouteHeader*& aData)
    {
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData = static_cast<CSIPRouteHeader*> (aDataWrapper.GetDataObjectL(name));
        }

    return ret;  
    }

TBool CT_SIPUtil::GetSdpOriginFieldL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSdpOriginField*& aData)
    {
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData = static_cast<CSdpOriginField*> (aDataWrapper.GetDataObjectL(name));
        }

    return ret; 
    }

TBool CT_SIPUtil::GetSdpConnectionFieldL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSdpConnectionField*& aData)
    {
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData = static_cast<CSdpConnectionField*> (aDataWrapper.GetDataObjectL(name));
        }

    return ret;     
    }

TBool CT_SIPUtil::GetSdpMediaFieldL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSdpMediaField*& aData)
    {
    TPtrC name;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, name);
    if (ret)
        {
        aData = static_cast<CSdpMediaField*> (aDataWrapper.GetDataObjectL(name));
        }

    return ret; 
    }

TBool CT_SIPUtil::GetTRealFromConfig(CDataWrapperBase & aDataWrapper, const TDesC & aSectName, const TDesC & aKeyName, TReal& aData)
    {
    TPtrC str;
    TBool ret = aDataWrapper.GetStringFromConfig(aSectName, aKeyName, str);
    
    if (ret)
        {
        // Only atof(TDesC8::Ptr()) works.
        TBuf8<KMaxTestExecuteCommandLength> buf;
        CnvUtfConverter::ConvertFromUnicodeToUtf8(buf, str);
        aData = atof((char*) (buf.Ptr()));
        }
    return ret;
    }

TBool CT_SIPUtil::CompareTReal(TReal aData1, TReal aData2)
    {
    TReal absDelta = 0.001;
    if(aData1 > aData2)
        return (aData1 - aData2) < absDelta;
    else
        return (aData2 - aData1) < absDelta;
    }
