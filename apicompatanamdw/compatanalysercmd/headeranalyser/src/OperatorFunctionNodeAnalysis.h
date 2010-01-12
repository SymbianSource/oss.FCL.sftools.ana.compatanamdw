/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies). 
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


#ifndef OPERATORFUNCTIONNODEANALYSIS_H_
#define OPERATORFUNCTIONNODEANALYSIS_H_

#include "FunctionNodeAnalysis.h"

using namespace std;

XERCES_CPP_NAMESPACE_USE


/**
*
*/
class OperatorFunctionNodeAnalysis: public FunctionNodeAnalysis
{
public:

    /**
    * Constructor
    * @return pointer NodeAnalysis object
    */
    static NodeAnalysis* Construct();
public:

    /**
    * Destructor
    */
    ~OperatorFunctionNodeAnalysis(){}
};

#endif
