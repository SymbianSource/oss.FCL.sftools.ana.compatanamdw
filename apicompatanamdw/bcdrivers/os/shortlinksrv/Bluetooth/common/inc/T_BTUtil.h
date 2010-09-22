/*
* Copyright (c) 2006-2008 Nokia Corporation and/or its subsidiary(-ies).
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


#if (!defined __T_BT_UTIL_H__)
#define __T_BT_UTIL_H__

//	EPOC includes
#include <datawrapper.h>
#include <btsdp.h>
#include <es_sock.h>
#include <es_sock_partner.h>

class CT_BTUtil : public CBase
	{
public:
	static TBool				ReadSdpElementType(CDataWrapper& aDataWrapper, TSdpElementType& aType, const TDesC& aSection, const TDesC& aField);
	static MSdpElementBuilder*	ElementBuilderCastL(CDataWrapper& aDataWrapper, const TDesC& aObjectName, const TDesC& aTypeName);
	static CSdpAttrValueList*	AttrValueListCastL(CDataWrapper& aDataWrapper, const TDesC& aObjectName, const TDesC& aTypeName);
	static TUint				ConvertUUID32toInt(const TUUID& aUUID);

	// Uses a default value when not matched
	static void					GetLowPowerMode(CDataWrapper& aDataWrapper, const TDesC& aSection, TUint32& aModes);
	static TBool				GetShutdown(CDataWrapper& aDataWrapper, const TDesC& aSection, RSocket::TShutdown& aShutdown);
	static void					GetTBTPacketType(CDataWrapper& aDataWrapper, const TDesC& aSection, TInt& aType);
	static void					GetLinkStateNotifierBits(CDataWrapper& aDataWrapper, const TDesC& aSection, TUint32& aModes);

	// Informs when match not found
	static TBool				GetIntValue(TPtrC aConstantName, TInt& aValue);
	};

#endif /* __T_BT_UTIL_H__ */
