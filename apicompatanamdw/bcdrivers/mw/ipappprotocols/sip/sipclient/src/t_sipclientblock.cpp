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


// This contains CT_SIPClientBlock

#include "t_sipclientblock.h"
#include "t_csip.h"
#include "t_csipconnection.h"
#include "t_csipmanagedprofile.h"
#include "t_csipmanagedprofileregistry.h"
#include "t_csipprofileregistry.h"
#include "t_csipmessageelements.h"
#include "t_csiptransactionbase.h"
#include "t_csipclienttransaction.h"
#include "t_csipservertransaction.h"
#include "t_csiprequestelements.h"
#include "t_csipresponseelements.h"
#include "t_csipaddress.h"
#include "t_csiprefresh.h"
#include "t_csipcontenttypeheader.h"
#include "t_csipfromheader.h"
#include "t_csiptoheader.h"
#include "t_csipreferdialogassoc.h"
#include "t_csiprefertoheader.h"
#include "t_csipinvitedialogassoc.h"
#include "t_csipsubscribedialogassoc.h"
#include "t_csiphttpdigest.h"
#include "t_csipregistrationbinding.h"
#include "t_csiprouteheader.h"
#include "t_csipcontactheader.h"
#include "t_csipcallidheader.h"
#include "t_csipdialog.h"
#include "t_csipeventheader.h"
#include "t_csipexpiresheader.h"
#include "t_csdpdocument.h"
#include "t_csdporiginfield.h"
#include "t_csdpconnectionfield.h"
#include "t_csdpmediafield.h"
#include "t_sdpcodecstringpool.h"
#include "t_csipcseqheader.h"

_LIT(KDataSIP, "CSIP");
_LIT(KDataSIPConnection, "CSIPConnection");
_LIT(KDataSIPManagedProfile,"CSIPManagedProfile");
_LIT(KDataSIPManagedProfileRegistry, "CSIPManagedProfileRegistry");
_LIT(KDataSIPProfile, "CSIPProfile");
_LIT(KDataSIPProfileRegistry, "CSIPProfileRegistry");
_LIT(KDataSIPMessageElements, "CSIPMessageElements");
_LIT(KDataSIPClientTransaction, "CSIPClientTransaction");
_LIT(KDataSIPServerTransaction, "CSIPServerTransaction");
_LIT(KDataSIPRequestElements, "CSIPRequestElements");
_LIT(KDataSIPResponseElements, "CSIPResponseElements");
_LIT(KDataSIPAddress, "CSIPAddress");
_LIT(KDataSIPRefresh, "CSIPRefresh");
_LIT(KDataSIPContentTypeHeader, "CSIPContentTypeHeader");
_LIT(KDataSIPFromHeader, "CSIPFromHeader");
_LIT(KDataSIPToHeader, "CSIPToHeader");
_LIT(KDataSIPCSeqHeader, "CSIPCSeqHeader");
_LIT(KDataSIPReferDialogAssoc, "CSIPReferDialogAssoc");
_LIT(KDataSIPReferToHeader, "CSIPReferToHeader");
_LIT(KDataSIPInviteDialogAssoc, "CSIPInviteDialogAssoc");
_LIT(KDataSIPHttpDigest, "CSIPHttpDigest");
_LIT(KDataSIPRegistrationBinding, "CSIPRegistrationBinding");
_LIT(KDataSIPRouteHeader, "CSIPRouteHeader");
_LIT(KDataSIPContactHeader, "CSIPContactHeader");
_LIT(KDataSIPCallIDHeader, "CSIPCallIDHeader");
_LIT(KDataSIPDialog, "CSIPDialog");
_LIT(KDataSIPSubscribeDialogAssoc, "CSIPSubscribeDialogAssoc");
_LIT(KDataSIPEventHeader,"CSIPEventHeader");
_LIT(KDataSIPExpiresHeader,"CSIPExpiresHeader");
_LIT(KDataSdpDocument, "CSdpDocument");
_LIT(KDataSdpOriginField, "CSdpOriginField");
_LIT(KDataSdpConnectionField, "CSdpConnectionField");
_LIT(KDataSdpMediaField, "CSdpMediaField");
_LIT(KDataSdpCodecStringPool, "SdpCodecStringPool");

CDataWrapper* CT_SIPClientBlock::CreateDataL( const TDesC& aData )
	{
	CDataWrapper* wrapper = NULL;
	if( KDataSIP() == aData )
		{
		wrapper = CT_DataSIP::NewL();
		}
	else if( KDataSIPConnection() == aData )
		{
		wrapper = CT_DataSIPConnection::NewL();
		}
	else if( KDataSIPManagedProfile() == aData )
		{
		wrapper = CT_DataSIPManagedProfile::NewL();
		}
	else if( KDataSIPManagedProfileRegistry() == aData )
		{
		wrapper = CT_DataSIPManagedProfileRegistry::NewL();
		}
	else if( KDataSIPProfile() == aData )
		{
		wrapper = CT_DataSIPProfile::NewL();
		}
	else if( KDataSIPProfileRegistry() == aData )
		{
		wrapper = CT_DataSIPProfileRegistry::NewL();
		}
	else if (KDataSIPMessageElements() == aData)
	    {
	    wrapper = CT_DataSIPMessageElements::NewL();
	    }
    else if (KDataSIPClientTransaction() == aData)
        {
        wrapper = CT_DataSIPClientTransaction::NewL();
        }
    else if (KDataSIPServerTransaction() == aData)
        {
        wrapper = CT_DataSIPServerTransaction::NewL();
        }
    else if (KDataSIPRequestElements() == aData)
        {
        wrapper = CT_DataSIPRequestElements::NewL();
        }
    else if (KDataSIPResponseElements() == aData)
        {
        wrapper = CT_DataSIPResponseElements::NewL();
        }
    else if (KDataSIPAddress() == aData)
        {
        wrapper = CT_DataSIPAddress::NewL();
        }
    else if (KDataSIPContentTypeHeader() == aData)
        {
        wrapper = CT_DataSIPContentTypeHeader::NewL();
        }
    else if (KDataSIPRefresh() == aData)
        {
        wrapper = CT_DataSIPRefresh::NewL();
        }
    else if (KDataSIPFromHeader() == aData)
		{
        wrapper = CT_DataSIPFromHeader::NewL();
		}
    else if (KDataSIPReferDialogAssoc() == aData)
        {
        wrapper = CT_DataSIPReferDialogAssoc::NewL();
        }
    else if (KDataSIPReferToHeader() == aData)
        {
        wrapper = CT_DataSIPReferToHeader::NewL();
        }
    else if (KDataSIPInviteDialogAssoc() == aData)
        {
        wrapper = CT_DataSIPInviteDialogAssoc::NewL();
        }
    else if (KDataSIPHttpDigest() == aData)
        {
        wrapper = CT_DataSIPHttpDigest::NewL();
        }
    else if (KDataSIPRegistrationBinding() == aData)
        {
        wrapper = CT_DataSIPRegistrationBinding::NewL();
        }
    else if (KDataSIPToHeader() == aData)
		{
        wrapper = CT_DataSIPToHeader::NewL();
		}
    else if (KDataSIPRouteHeader() == aData)
        {
        wrapper = CT_DataSIPRouteHeader::NewL();
        }
    else if (KDataSIPContactHeader() == aData)
        {
        wrapper = CT_DataSIPContactHeader::NewL();
        }
    else if (KDataSIPCallIDHeader() == aData)
        {
        wrapper = CT_DataSIPCallIDHeader::NewL();
        }
    else if (KDataSIPDialog() == aData)
        {
        wrapper = CT_DataSIPDialog::NewL();
        }
    else if (KDataSIPSubscribeDialogAssoc() == aData)
        {
        wrapper = CT_DataSIPSubscribeDialogAssoc::NewL();
        }
    else if(KDataSIPEventHeader() == aData)
        {
        wrapper = CT_DataSIPEventHeader::NewL();
        }
    else if(KDataSIPExpiresHeader() == aData)
        {
        wrapper = CT_DataSIPExpiresHeader::NewL();
        }
    else if (KDataSdpDocument() == aData)
        {
        wrapper = CT_DataSdpDocument::NewL();
        }
    else if (KDataSdpOriginField() == aData)
        {
        wrapper = CT_DataSdpOriginField::NewL();
        }
    else if (KDataSdpConnectionField() == aData)
        {
        wrapper = CT_DataSdpConnectionField::NewL();
        }
    else if (KDataSdpMediaField() == aData)
        {
        wrapper = CT_DataSdpMediaField::NewL();
        }
    else if(KDataSdpCodecStringPool() == aData)
        {
        wrapper = CT_DataSdpCodecStringPool::NewL();
        }
    else if(KDataSIPCSeqHeader() == aData)
        {
        wrapper = CT_DataSIPCSeqHeader::NewL();
        }
	return wrapper;
	}

