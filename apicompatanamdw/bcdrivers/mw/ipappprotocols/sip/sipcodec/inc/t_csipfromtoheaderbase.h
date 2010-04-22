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

#ifndef T_CSIPFROMTOHEADERBASE_H_
#define T_CSIPFROMTOHEADERBASE_H_

//  User includes
#include "t_csipparameterheaderbase.h"

// Epoc includes
#include <sipfromtoheaderbase.h>

class CT_DataSIPFromToHeaderBase : public CT_DataSIPParameterHeaderBase
    {
public:
    /**
    * Process a command read from the ini file
    *
    * \param aTestStep  test step requiring command to be processed
    * \param aCommand   the command to process
    * \param aSection   the entry in the ini file requiring the command to be processed
    *
    * \return ETrue if the command is processed
    */
    virtual TBool   DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    
protected:
    CT_DataSIPFromToHeaderBase();
    virtual CSIPHeaderBase * GetSIPHeaderBase()const = 0; 
    void    DoCmdSIPAddress(const TTEFSectionName& aSection);
    void    DoCmdSetSIPAddressL(const TTEFSectionName& aSection);
    void    DoCmdCompare(const TTEFSectionName& aSection); // operator ==()
   };


#endif /* T_CSIPFROMTOHEADERBASE_H_ */
