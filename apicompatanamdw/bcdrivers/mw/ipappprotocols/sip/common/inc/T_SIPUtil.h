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


#ifndef T_SIPUTIL_H_
#define T_SIPUTIL_H_

#include "DataWrapperBase.h"
#include <sipprofileregistryobserver.h>
#include <siptransactionbase.h>
#include <sipconnection.h>
#include <siprefresh.h>
#include <sipeventheader.h> 
#include <sipdialog.h>

class MDesC8Array;
class RStringF;
class CSIP;
class CSIPProfile;
class CSIPResponseElements;
class CSIPContentTypeHeader;
class CSIPHeaderBase;
class CSIPTransactionBase;
class CSIPClientTransaction;
class CSIPServerTransaction;
class CSIPFromHeader;
class CSIPToHeader;
class CSIPCSeqHeader;
class CSIPAddress;
class CUri8;
class CSIPFromToHeaderBase;
class CSIPDialog;
class CSIPReferToHeader;
class CSIPConnection;
class CSIPContactHeader;
class CSIPRouteHeader;
class MSIPRegistrationContext;
class CSdpOriginField;
class CSdpConnectionField;
class CSdpMediaField;

class CT_SIPUtil
    {
public:
	static void    EatupMemory(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName);
	static void    FreeEatenMemory(CDataWrapperBase& aDataWrapper);
	static void    ConvertToUtf8(const TDesC& aSrc,TDes8& aDest);	
	static void    ConvertToUnicode(const TDesC8& aSrc,TDes& aDest);
	static TBool   GetSIPProfileTypeInfo(CDataWrapperBase& aDataWrapper, const TDesC& aSectName,const TDesC& aKeyName, TSIPProfileTypeInfo& aInfo);
	static TBool   GetMDesC8ArrayL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName,const TDesC& aKeyName, MDesC8Array *aArray);
	static TBool   GetStringF(CDataWrapperBase& aDataWrapper, const TDesC& aSectName,const TDesC& aKeyName, RStringF& aData);
	static TBool   GetSIP(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIP*& aData);
	static TBool   GetSIPProfile(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPProfile*& aData);
	static TBool   GetSIPProfileParameter(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, TUint32& aResult);
	static TBool   GetSIPProfileClass(const TDesC& aSIPProfileClassStr, TSIPProfileTypeInfo::TSIPProfileClass& aSIPProfileClass );
	static TBool   GetSIPProfileClassStr(const TSIPProfileTypeInfo::TSIPProfileClass& aSIPProfileClass,TDes& aSIPProfileClassStr);
	static TBool   GetEvent(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, MSIPProfileRegistryObserver::TEvent& aData);
	static TUint32 GetIAPIDL(const TDesC& aAccessPoint);
	static TUint32 AddAccessPointL(const TDesC& aAccessPoint);
	static TBool   GetState(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPTransactionBase::TState& aData);	
	static TBool   GetSIPResponseElements (CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPResponseElements *& aData);
	static TBool   GetSIPContentTypeHeaderFromConfigL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPContentTypeHeader*& aData);
	static TBool   GetSIPHeadersL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, RPointerArray<CSIPHeaderBase>& aArray);
	static TBool   GetSIPTransactionL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPTransactionBase*& aData);
	static TBool   GetSIPClientTransactionL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPClientTransaction*& aData);
	static TBool   GetSIPServerTransactionL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPServerTransaction*& aData);
	static TBool   GetSIPFromHeaderL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPFromHeader*& aData);
	static TBool   GetSIPToHeaderL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPToHeader*& aData);
	static TBool   GetSIPSeqHeaderL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPCSeqHeader*& aData);
	static TBool   GetSIPAddressL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPAddress*& aData);
	static TBool   GetUri8L(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CUri8*& aData);	
	static TBool   GetStringFFromConfigL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, const RStringPool& aPool, RStringF& aData);
	static TBool   GetSIPFromToHeaderBaseL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPFromToHeaderBase*& aData);
	static TBool   ConvertStringToEnumState(TPtrC& aStrState, CSIPConnection::TState& aState);
    static TBool   GetSIPRefreshState(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPRefresh::TState& aData);
    static TBool   GetSIPMessageElements(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPMessageElements*& aData);
    static TBool   GetSIPRefreshL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPRefresh*& aData);
    static TBool   GetSIPDialogL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPDialog*& aData);
    static TBool   GetSIPReferToHeaderL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPReferToHeader*& aData);
    static TBool   GetSIPConnectionL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPConnection*& aData);
    static TBool   GetSIPContactHeaderL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPContactHeader*& aData);
    static TBool   GetSIPRegistrationContextL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, MSIPRegistrationContext*& aData);
    static TBool   GetSIPEventHeaderL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPEventHeader*& aData);
	static TBool   GetSIPDialogState(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPDialog::TState& aData);
    static TBool   GetSIPHeaderBaseL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPHeaderBase*& aData);
    static TBool   GetSIPRouteHeaderL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSIPRouteHeader*& aData);
    static TBool   GetSdpOriginFieldL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSdpOriginField*& aData);
    static TBool   GetSdpConnectionFieldL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSdpConnectionField*& aData);
    static TBool   GetSdpMediaFieldL(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, CSdpMediaField*& aData);
    static TBool   GetTRealFromConfig(CDataWrapperBase& aDataWrapper, const TDesC& aSectName, const TDesC& aKeyName, TReal& aData);
    static TBool   CompareTReal(TReal aData1, TReal aData2);
  
public:
    static TUint32 iProfileId;
    static HBufC8* iContent;
    
private:
	static TInt iAvaiableSpace;
	static TInt iBiggestBlock;
	static RPointerArray < TAny > iMemArray;
    };

#endif /*T_SIPUTIL_H_*/
