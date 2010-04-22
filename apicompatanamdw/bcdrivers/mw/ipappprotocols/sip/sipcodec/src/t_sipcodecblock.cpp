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


// This contains CT_SIPCodecBlock

#include "t_sipcodecblock.h"
#include "t_csip.h"
#include "t_sipstrings.h"
#include "t_csipfromheader.h"
#include "t_csiptoheader.h"
#include "t_csipcallidheader.h"
#include "t_csipaddress.h"
#include "t_csipcseqheader.h"
#include "t_csipalloweventsheader.h"
#include "t_csiprackheader.h"
#include "t_csipextensionheader.h"
#include "t_csiprackheader.h"
#include "t_csipreplytoheader.h"
#include "t_csiptimestampheader.h"
#include "t_csiprefertoheader.h"
#include "t_csippassociateduriheader.h"
#include "t_csipacceptcontactheader.h"
#include "t_csipacceptheader.h"
#include "t_csipcontentdispositionheader.h"
#include "t_csipacceptlanguageheader.h"
#include "t_csipacceptencodingheader.h"
#include "t_csipcontenttypeheader.h"
#include "t_csipcontactheader.h"
#include "t_csipretryafterheader.h"
#include "t_csipeventheader.h"
#include "t_csipsubscriptionstateheader.h"
#include "t_csiprouteheader.h"
#include "t_csipcontentencodingheader.h"
#include "t_csipallowheader.h"
#include "t_csipproxyrequireheader.h"
#include "t_csipsupportedheader.h"
#include "t_csiprequireheader.h"
#include "t_csipsecurityclientheader.h"
#include "t_csiprseqheader.h"
#include "t_csipunsupportedheader.h"
#include "t_csipexpiresheader.h"

_LIT(KDataSIP, "CSIP");
_LIT(KDataSIPStrings, "SIPStrings");
_LIT(KDataSIPFromHeader, "CSIPFromHeader");
_LIT(KDataSIPToHeader, "CSIPToHeader");
_LIT(KDataSIPCallIDHeader, "CSIPCallIDHeader");
_LIT(KDataSIPAddress, "CSIPAddress");
_LIT(KDataSIPCSeqHeader, "CSIPCSeqHeader");
_LIT(KDataSIPAllowEventsHeader, "CSIPAllowEventsHeader");
_LIT(KDataSIPRAckHeader, "CSIPRAckHeader");
_LIT(KDataSIPExtensionHeader, "CSIPExtensionHeader");
_LIT(KDataSIPReplyToHeader, "CSIPReplyToHeader");
_LIT(KDataSIPTimestampHeader, "CSIPTimestampHeader");
_LIT(KDataSIPReferToHeader, "CSIPReferToHeader");
_LIT(KDataSIPPAssociatedURIHeader, "CSIPPAssociatedURIHeader");
_LIT(KDataSIPAcceptContactHeader, "CSIPAcceptContactHeader");
_LIT(KDataSIPAcceptHeader, "CSIPAcceptHeader");
_LIT(KDataSIPContentDispositionHeader, "CSIPContentDispositionHeader");
_LIT(KDataSIPAcceptLanguageHeader, "CSIPAcceptLanguageHeader");
_LIT(KDataSIPAcceptEncodingHeader, "CSIPAcceptEncodingHeader");
_LIT(KDataSIPContentTypeHeader, "CSIPContentTypeHeader");
_LIT(KDataSIPContactHeader, "CSIPContactHeader");
_LIT(KDataSIPRetryAfterHeader, "CSIPRetryAfterHeader");
_LIT(KDataSIPEventHeader,"CSIPEventHeader");
_LIT(KDataSIPSubscriptionStateHeader,"CSIPSubscriptionStateHeader");
_LIT(KDataSIPRouteHeader,"CSIPRouteHeader");
_LIT(KDataSIPContentEncodingHeader,"CSIPContentEncodingHeader");
_LIT(KDataSIPAllowHeader,"CSIPAllowHeader");
_LIT(KDataSIPProxyRequireHeader,"CSIPProxyRequireHeader");
_LIT(KDataSIPSupportedHeader,"CSIPSupportedHeader");
_LIT(KDataSIPRequireHeader,"CSIPRequireHeader");
_LIT(KDataSIPSecurityClientHeader,"CSIPSecurityClientHeader");
_LIT(KDataSIPRSeqHeader,"CSIPRSeqHeader");
_LIT(KDataSIPUnsupportedHeader,"CSIPUnsupportedHeader");
_LIT(KDataSIPExpiresHeader,"CSIPExpiresHeader");

CDataWrapper* CT_SIPCodecBlock::CreateDataL( const TDesC& aData )
    {
    CDataWrapper* wrapper = NULL;
  
    if( KDataSIPStrings() == aData )
        {
        wrapper = CT_DataSIPStrings::NewL();
        }
    else if( KDataSIPFromHeader() == aData )
        {
        wrapper = CT_DataSIPFromHeader::NewL();
        }
    else if( KDataSIPToHeader() == aData )
        {
        wrapper = CT_DataSIPToHeader::NewL();
        }
    else if( KDataSIPCallIDHeader() == aData )
        {
        wrapper = CT_DataSIPCallIDHeader::NewL();
        }
    else if( KDataSIP() == aData )
        {
        wrapper = CT_DataSIP::NewL();
        }
    else if( KDataSIPAddress() == aData )
        {
        wrapper = CT_DataSIPAddress::NewL();
        }
    else if( KDataSIPCSeqHeader() == aData )
        {
        wrapper = CT_DataSIPCSeqHeader::NewL();
        }
    else if(KDataSIPAllowEventsHeader() == aData)
        {
        wrapper = CT_DataSIPAllowEventsHeader::NewL();
        } 
    else if (KDataSIPRAckHeader() == aData)
        {
        wrapper = CT_DataSIPRAckHeader::NewL();
        }
    else if (KDataSIPExtensionHeader() == aData)
        {
        wrapper = CT_DataSIPExtensionHeader::NewL();
        }
    else if (KDataSIPReplyToHeader() == aData)
        {
        wrapper = CT_DataSIPReplyToHeader::NewL();
        }
    else if (KDataSIPTimestampHeader() == aData)
        {
        wrapper = CT_DataSIPTimestampHeader::NewL();
        }
    else if (KDataSIPReferToHeader() == aData)
        {
        wrapper = CT_DataSIPReferToHeader::NewL();
        }
    else if(KDataSIPPAssociatedURIHeader() == aData)
        {
        wrapper = CT_DataSIPPAssociatedURIHeader::NewL();
        }   
    else if (KDataSIPAcceptContactHeader() == aData)
        {
        wrapper = CT_DataSIPAcceptContactHeader::NewL();
        }
    else if (KDataSIPAcceptHeader() == aData)
        {
        wrapper = CT_DataSIPAcceptHeader::NewL();
        }
    else if (KDataSIPContentDispositionHeader() == aData)
        {
        wrapper = CT_DataSIPContentDispositionHeader::NewL();
        }
    else if (KDataSIPAcceptLanguageHeader()== aData)
        {
        wrapper = CT_DataSIPAcceptLanguageHeader::NewL();
        }   
    else if (KDataSIPAcceptEncodingHeader() == aData)
        {
        wrapper = CT_DataSIPAcceptEncodingHeader::NewL();
        }   
    else if (KDataSIPContentTypeHeader() == aData)
        {
        wrapper = CT_DataSIPContentTypeHeader::NewL();
        }
    else if (KDataSIPContactHeader() == aData)
        {
        wrapper = CT_DataSIPContactHeader::NewL();
        }	
    else if (KDataSIPRetryAfterHeader() == aData)
        {
        wrapper = CT_DataSIPRetryAfterHeader::NewL();
        }
    else if (KDataSIPEventHeader() == aData)
        {
            wrapper = CT_DataSIPEventHeader::NewL();
        }
    else if (KDataSIPSubscriptionStateHeader() == aData)
        {
            wrapper = CT_DataSIPSubscriptionStateHeader::NewL();
        }
    else if (KDataSIPRouteHeader() == aData)
        {
        wrapper = CT_DataSIPRouteHeader::NewL();
        }
    else if (KDataSIPAllowHeader() == aData)
		{
        wrapper = CT_DataSIPAllowHeader::NewL();
		}
    else if (KDataSIPProxyRequireHeader() == aData) 
        {
        wrapper = CT_DataSIPProxyRequireHeader::NewL();
        }
    else if (KDataSIPContentEncodingHeader() == aData)
        {
        wrapper = CT_DataContentEncodingHeader::NewL();
        }
    else if (KDataSIPSupportedHeader() == aData)
        {
        wrapper = CT_DataSupportedHeader::NewL();
        }
    else if (KDataSIPRequireHeader() == aData)
		{
        wrapper = CT_DataSIPRequireHeader::NewL();
		}
	else if (KDataSIPSecurityClientHeader() == aData)
        {
        wrapper = CT_DataSIPSecurityClientHeader::NewL();
        }	
    else if (KDataSIPRSeqHeader() == aData)
        {
        wrapper = CT_DataSIPRSeqHeader::NewL();
        }
    else if (KDataSIPUnsupportedHeader() == aData)
        {
        wrapper = CT_DataUnsupportedHeader::NewL();
        }       
	else if (KDataSIPExpiresHeader() == aData)
        {
        wrapper = CT_DataSIPExpiresHeader::NewL();
        }  	 
    return wrapper;
    }

