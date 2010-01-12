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


#ifndef __ISSUES_H_
#define __ISSUES_H_
#include "CmdGlobals.h"

#include <xercesc/dom/DOM.hpp>

XERCES_CPP_NAMESPACE_USE

#include "ReportIssue.h"
class HANodeIterator;

template <TIssueIdentity Identity,TIssueType IssueType>
string ignoreInfo(const HANodeIterator& baseline,const HANodeIterator& current);	

/**
* In the following the severities and ignore information of issues are defined 
* through template mechanism. This allows linking time checking that we have 
* not forgot to define meaningful information for new issues. In order to modify
* severity information or ignore information first determine the TIssueIdentity
* and TIssueType /of the issue and then find the correct function 
* (BCseverityAccessible<TIssueIdentity,TIssueType> and 
* ignoreInfo<TIssueIdentity,TIssueType>) and modify the function definition to 
* match with the severity and ignore information.
*
* @param accessible that defines if the element is directly accessible
*                   or only through some inline method
* @return severity level of the issue
*/
template <TIssueIdentity Identity,TIssueType IssueType>
TBCSeverity BCseverityAccessible(bool accessible);

/**
* In the following the severities and ignore information of issues are defined 
* through template mechanism. This allows linking time checking that we have 
* not forgot to define meaningful information for new issues. In order to modify
* severity information or ignore information first determine the TIssueIdentity
* and TIssueType /of the issue and then find the correct function 
* (SCseverityAccessible<TIssueIdentity,TIssueType> and 
* ignoreInfo<TIssueIdentity,TIssueType>) and modify the function definition to 
* match with the severity and ignore information.
*
* @param accessible that defines if the element is directly accessible
*                   or only through some inline method
* @return scseverity level of the issue
*/

template <TIssueIdentity Identity,TIssueType IssueType>
TSCSeverity SCseverityAccessible(bool accessible);

/**
* Return binary compatibility severity description
*/
extern const char* KSeverityDesc[ESeverityCount];

/**
* Return source compatibility severity description
*/
extern const char* KSeveritySCDesc[ESeveritySCCount];

/**
* Return identity description
*/
extern const char* KIssueIdentityDesc[EIssueIdentityCount];

/**
* Return type description. Issue is removal, addition, change,
* access, inheritance,etc.
*/
extern const char* KIssueTypeDesc[EIssueTypeCount];

#endif
