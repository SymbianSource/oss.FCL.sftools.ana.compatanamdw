/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description:  Test case for requirement HABC007
*
*/


#ifndef HATC007_1_H
#define HATC007_1_H

/**
 * struct hatc007_class_templ. This tests that if moving the type of the typedef 
 * to another header and gccxml parses the type as incomplete, no errors are reported.
 */

// Moved here from HATC007.h
template <typename T>
class hatc007_class_templ
{
public:
    hatc007_class_templ(T const& aC);

private:
    T* mArrPtr;
};

#endif