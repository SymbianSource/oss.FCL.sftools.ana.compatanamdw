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


#include "ReportIssue.h"
#include "Issues.h"




// ----------------------------------------------------------------------------
// ReportIssue::ReportIssue
// 
// ----------------------------------------------------------------------------
//
ReportIssue::ReportIssue()
{

}

// ----------------------------------------------------------------------------
// ReportIssue::ReportIssue
// 
// ----------------------------------------------------------------------------
//
ReportIssue::ReportIssue(int aIssueId, const string& aFile, 
                const string& aFQName, const TIssueIdentity& aIdentityId, 
                const TIssueType& aTypeId, const TBCSeverity& aBCSeverityId, 
                const TSCSeverity& aSCSeverityId, const string& aIgnoreInformation,
                int aLineNumber, const string& aIssueLoc, const string& aCompareFileName, 
				const string& aCompilationError, bool alineNoNeeded):
    iHeaderFile(aFile),
    iFQName(aFQName),
    iId(aIssueId),
    iBCSeverity(aBCSeverityId),
    iSCSeverity(aSCSeverityId),
    iIgnoreInformation(aIgnoreInformation),
    iIdentityId(aIdentityId),
    iTypeId(aTypeId),
    iLineNumber( aLineNumber ),
	iIssueLoc(aIssueLoc),
    iCompareFileName( aCompareFileName ),
	iCompilationError(aCompilationError)
    {
    }

// ----------------------------------------------------------------------------
// ReportIssue::~ReportIssue
// 
// ----------------------------------------------------------------------------
// 
ReportIssue::~ReportIssue()
{
}
 
// ----------------------------------------------------------------------------
// ReportIssue::SetId
// 
// ----------------------------------------------------------------------------
//   
void ReportIssue::SetId(const int aId)
{
    iId = aId;
}

// ----------------------------------------------------------------------------
// ReportIssue::SetBCSeverity
// ----------------------------------------------------------------------------
//
void ReportIssue::SetBCSeverity(const TBCSeverity& aBCSeverity)
{
    iBCSeverity = aBCSeverity;
}

// ----------------------------------------------------------------------------
// ReportIssue::SetSCSeverity
// ----------------------------------------------------------------------------
//
void ReportIssue::SetSCSeverity(const TSCSeverity& aSCSeverity)
{
    iSCSeverity = aSCSeverity;
}

// ----------------------------------------------------------------------------
// ReportIssue::SetFQName
// ----------------------------------------------------------------------------
//
void ReportIssue::SetFQName(const string& aFQName)
{
    iFQName = aFQName;
}

// ----------------------------------------------------------------------------
// ReportIssue::SetFQName
// ----------------------------------------------------------------------------
//
void ReportIssue::SetHeaderFile(const string& aFile)
{
    iHeaderFile = aFile;
}


// ----------------------------------------------------------------------------
// ReportIssue::SetIdentityId
// ----------------------------------------------------------------------------
//
void ReportIssue::SetIdentityId(const TIssueIdentity& aIdentityId)
{
    iIdentityId = aIdentityId;
}

// ----------------------------------------------------------------------------
// ReportIssue::SetTypeId
// 
// ----------------------------------------------------------------------------
//  
void ReportIssue::SetTypeId(const TIssueType& aTypeId)
{
    iTypeId = aTypeId;
}

// ----------------------------------------------------------------------------
// ReportIssue::Id
// ----------------------------------------------------------------------------
//
int ReportIssue::Id() const
{
    return iId;
}

// ----------------------------------------------------------------------------
// ReportIssue::BCSeverity
// ----------------------------------------------------------------------------
//
const TBCSeverity& ReportIssue::BCSeverity() const
{
    return iBCSeverity;
}

// ----------------------------------------------------------------------------
// ReportIssue::SCSeverity
// ----------------------------------------------------------------------------
//
const TSCSeverity& ReportIssue::SCSeverity() const
{
    return iSCSeverity;
}

// ----------------------------------------------------------------------------
// ReportIssue::FQName
// ----------------------------------------------------------------------------
//
const string&  ReportIssue::FQName() const
{
    return iFQName;
}

// ----------------------------------------------------------------------------
// ReportIssue::HeaderFile
// 
// ----------------------------------------------------------------------------
//
const string&  ReportIssue::HeaderFile() const
{
    return iHeaderFile;
}

// ----------------------------------------------------------------------------
// ReportIssue::FQName
// 
// ----------------------------------------------------------------------------
//
const TIssueIdentity& ReportIssue::IdentityId() const 
{
    return iIdentityId;
}

// ----------------------------------------------------------------------------
// ReportIssue::TypeId
// ----------------------------------------------------------------------------
//
const TIssueType& ReportIssue::TypeId() const
{
    return iTypeId;
}

// ----------------------------------------------------------------------------
// ReportIssue::BCSeverityDescription
// ----------------------------------------------------------------------------
//
const char* ReportIssue::BCSeverityDescription() const
{
    return KSeverityDesc[iBCSeverity];
}

// ----------------------------------------------------------------------------
// ReportIssue::SCSeverityDescription
// ----------------------------------------------------------------------------
//
const char* ReportIssue::SCSeverityDescription() const
{
    return KSeveritySCDesc[iSCSeverity];
}

// ----------------------------------------------------------------------------
// ReportIssue::IdentityDescription
// ----------------------------------------------------------------------------
//
const char* ReportIssue::IdentityDescription() const
{
    return KIssueIdentityDesc[iIdentityId];
}

// ----------------------------------------------------------------------------
// ReportIssue::TypeDescription
// ----------------------------------------------------------------------------
//
const char* ReportIssue::TypeDescription() const
{
    return KIssueTypeDesc[iTypeId];
}

// ----------------------------------------------------------------------------
// ReportIssue::IgnoreInformationDescription
// ----------------------------------------------------------------------------
//
const string& ReportIssue::IgnoreInformationDescription() const
{
    return iIgnoreInformation;
}

// ----------------------------------------------------------------------------
// ReportIssue::LineNumber
// ----------------------------------------------------------------------------
//
int ReportIssue::LineNumber() const
{
    return iLineNumber;
}
void ReportIssue::SetLineNumber(int lineNumber)
{
	iLineNumber = lineNumber;
}

// ----------------------------------------------------------------------------
// ReportIssue::LineNumber
// ----------------------------------------------------------------------------
//
const string& ReportIssue::IssueLocation() const
{
    return iIssueLoc;
}

// ----------------------------------------------------------------------------
// ReportIssue::CompareFileName
// ----------------------------------------------------------------------------
//
const string& ReportIssue::CompareFileName() const
{
    return iCompareFileName;
}

// ----------------------------------------------------------------------------
// ReportIssue::Cause of compilation error
// ----------------------------------------------------------------------------
//
const string& ReportIssue::CompilationError() const
{
    return iCompilationError;
}

// ----------------------------------------------------------------------------
// ReportIssue::ReportIssue
// ----------------------------------------------------------------------------
//
ReportIssue::ReportIssue(const ReportIssue & other)
{
	(*this)=other;
}

// ----------------------------------------------------------------------------
// ReportIssue::FQName
// ----------------------------------------------------------------------------
//	
const ReportIssue& ReportIssue::operator=(const ReportIssue& other)
{
	iHeaderFile=other.iHeaderFile;
    iFQName=other.iFQName;
    iId=other.iId;
    iBCSeverity=other.iBCSeverity;
    iSCSeverity=other.iSCSeverity;
    iIgnoreInformation=other.iIgnoreInformation;
    iIdentityId=other.iIdentityId;
    iTypeId=other.iTypeId;	
    iLineNumber=other.iLineNumber;
	iIssueLoc=other.iIssueLoc;
    iCompareFileName=other.iCompareFileName;
	iCompilationError=other.iCompilationError;
	return (*this);
}

bool ReportIssue::operator<(const ReportIssue& other) const
{
	if (iFQName == other.iFQName)
	{
		if ( iIdentityId == other.iIdentityId )
		{
			return iTypeId < other.iTypeId;
		}
		else
		{
			return iIdentityId < other.iIdentityId;
		}
	}else
	{
		return iFQName < other.iFQName;
	}
}

bool ReportIssue::operator==(const ReportIssue& other) const
{
	return ((*this) < other == false) && 
           (other < (*this) == false);
}
