/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/



#ifndef BCAPPLMKEDITORENGINE_H
#define BCAPPLMKEDITORENGINE_H

#include <coemop.h>
#include <e32base.h>
class CLmkAddEditEngine : public CBase, public MObjectProvider
{
		public:
		
		protected:
			TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
    	MObjectProvider* MopNext();
};

#endif      // BCAPPLMKEDITORENGINE_H

// End of File
