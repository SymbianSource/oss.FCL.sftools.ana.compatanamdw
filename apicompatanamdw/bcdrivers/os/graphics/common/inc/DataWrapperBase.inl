/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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


inline RFs& CDataWrapperBase::FileServer()
	{ 
	return iFs;
	}

inline TInt CDataWrapperBase::GetHandle() const
	{
	return iHandle;
	}

inline void CDataWrapperBase::SetHandle(TInt aHandle)
	{
	iHandle=aHandle;
	}
	
inline TInt CDataWrapperBase::GetIdentifier() const
	{
	return iIdentifier;
	}

inline void CDataWrapperBase::SetIdentifier(TInt aIdentifier)
	{
	iIdentifier=aIdentifier;
	}
