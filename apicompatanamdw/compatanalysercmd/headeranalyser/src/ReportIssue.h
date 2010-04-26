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


#ifndef __REPORT_ISSUE_H__
#define __REPORT_ISSUE_H__

#include "CmdGlobals.h"
#ifdef __WIN__
#pragma warning(disable:4786)
#endif


#include <xercesc/dom/DOM.hpp>

XERCES_CPP_NAMESPACE_USE


#include <string>

using namespace std;

// Severity of the issue found for binary compatibility
enum TBCSeverity
{
    ESeverityNULL = 0,
    ESeverityBBCBreak,
    ESeverityPossibleBBCBreak,
    ESeverityInformative,
    ESeverityFCBreak,
    ESeverityPossibleFCBreak,
    ESeverityCount
};

// Severity of the issue found for source compatibility
enum TSCSeverity
{
    ESeveritySCNULL = 0,
    ESeveritySCBreak,
    ESeverityPossibleSCBreak,
    ESeveritySCInformative,
    ESeveritySCCount
};

// Identity of the issue found
enum TIssueIdentity
{
    EIssueIdentityClass,
    EIssueIdentityExportedFunction,
    EIssueIdentityInlineFunction,
    EIssueIdentityVirtualFunction,
    EIssueIdentityEnumeration,
    EIssueIdentityStruct,
    EIssueIdentityUnion,
    EIssueIdentityEnumerationValue,
    EIssueIdentityTypedef,
    EIssueIdentityVariable,
    EIssueIdentityField,
    EIssueIdentityFieldInaccessible,
    EIssueIdentityMacro,
    EIssueIdentityFile,
    EIssueIdentityVirtualTable,
    EIssueIdentitySubobject,
    EIssueIdentityVirtualTablePointer,
    EIssueIdentityExportedInlineFunction,
    EIssueIdentityExportedVirtualFunction,
    EIssueIdentityVirtualInlineFunction,
    EIssueIdentityExportedVirtualInlineFunction,
	EIssueIdentityStructMember,
    EIssueIdentityCount
	
};

// What kind of issue was happened in the code between two
// versions of the comparable header files
enum TIssueType
{
    EIssueTypeRemoval,
    EIssueTypeAddition,
    EIssueTypeChange,
    EIssueTypeSize,
    EIssueTypeAlign,
    EIssueTypeParam,
    EIssueTypeReturn,
	EIssueTypeAccess,
    EIssueTypeInheritance,
    EIssueTypeOffset,
    EIssueTypeOrderChange,
    EIssueTypeChangeInType,
    EIssueTypeChangeInInitialisation,
    EIssueTypeCompilationError,
    EIssueTypeNotAnalysed,
    EIssueTypeVirtualBases,
    EIssueTypeNewOverride,
    //EIssueTypeRemovedOverride,
    EIssueTypeEmpty,
    EIssueTypeBaseSize,
    EIssueTypeUnderConstruction,
	EIssueTypeParamConst,
    EIssueTypeParamConst2,
	EIssueTypeReturnConst,
    EIssueTypeReturnConst2,
	EIssueTypeDefaultParam,
	EIssueTypeOverload,
    EIssueTypeCount
};


/**
* The ReportIssues class is a data class that encapsulates 
* the data for an issue.
*/
class ReportIssue
{
	friend class ReportGenerator;
public:
    /*
    *Constructor
    * @param aIssueId the unique id of the issue in this report, running number
    * @param aFile the file where the issue is
    * @param aFQName the fully qualified name of the cause
    * @param aIssueIdentityId the issue identity id (class, enum, struct...)
    * @param aIssueTypeId the issue type (removed, added, changed...)
    * @param aBCSeverityId binary compatibility severity of the issue found
    * @param aSCSeverityId source compatibility severity of the issue found
    * @param aIgnoreInformation information needed for ignoring the issue
    * @param aLineNumber line where the issue is
	* @param aIssueLoc filename where the issue is
    * @param aCompareFileName
	* @param aCompilationError
    */
    ReportIssue(int aIssueId, const string& aFile, 
                const string& aFQName, const TIssueIdentity& aIssueIdentityId, 
                const TIssueType& aIssueTypeId, const TBCSeverity& aBCSeverityId, 
                const TSCSeverity& aSCSeverityId, const string& aIgnoreInformation,
                int aLineNumber, const string& aIssueLoc, const string& aCompareFileName, 
				const string& aCompilationError = "", bool alineNoNeeded = true);


    /**
    * Constructor
    */ 
    ReportIssue();

    /**
    * Destructor
    */ 
    ~ReportIssue();

    /**
    * Constructor
    * @param other issue to report
    */ 
	ReportIssue(const ReportIssue & other);

	const ReportIssue& operator=(const ReportIssue& other);

	bool operator<(const ReportIssue& other) const;
	bool operator==(const ReportIssue& other) const;
public:
    /**
    * Set issue id
    * @param aId id number to set
    */ 
    void SetId(const int aId);

    /**
    * Set binary compatibility severity level of the issue
    * @param aId reference to severity (TBCSeverity&)
    */
    void SetBCSeverity(const TBCSeverity& aId);
    
    /**
    * Set source compatibility  severity level of the issue
    * @param aId reference to severity (TSCSeverity&)
    */
    void SetSCSeverity(const TSCSeverity& aId);

    /**
    * Set fully qualified name
    * @param aCause full
    */
    void SetFQName(const string& aCause);

    /**
    * Set headerfile
    * @param aFile name of the header file
    */
    void SetHeaderFile(const string& aFile);

    /**
    * Get identity
    * @param aIdentityId TIssueIdentity reference to the issue identity id (class, enum, struct...)
    */
    void SetIdentityId(const TIssueIdentity& aIdentityId);

    /**
    * Set type id
    * @param aTypeId the issue type (removed, added, changed...)
    */
    void SetTypeId(const TIssueType& aTypeId);

    /**
    * Get issue ID
    */ 
    int Id() const;

    /**
    * Get binary compatibility severity level
    * @return reference to severity level
    */ 
    const TBCSeverity& BCSeverity() const;
    
    /**
    * Get source compatibility severity level
    * @return reference to severity level
    */
    const TSCSeverity& SCSeverity() const;
    
    /**
    * Get fully qualified name of the issue
    * @return reference to fully qualified name
    */ 
    const string& FQName() const;
    
    /**
    * Get header filename
    * @return name of the file
    */ 
    const string& HeaderFile() const;
    
    /**
    * Get identity ID
    * @return reference to issue identity
    */ 
    const TIssueIdentity& IdentityId() const;
    
    /**
    * Get issue type id
    * @return reference to issue type
    */ 
    const TIssueType& TypeId() const;
    
    /**
    * Get sbinary compatibility severity description string
    * @return description string
    */ 
    const char* BCSeverityDescription() const;
    
    /**
    * Get source compatibility severity description string
    * @return description string
    */
    const char* SCSeverityDescription() const;
    
    /**
    * Get identity description
    * @return description string
    */ 
    const char* IdentityDescription() const;
    
    /**
    * Get type description
    * @return description string
    */ 
    const char* TypeDescription() const;
    
    /**
    * Get ignore information description (information needed for ignoring 
    * the issue)
    * @return information description string
    */ 
    const string& IgnoreInformationDescription() const;
        
    /**
    * Get line number
    * @return line number
    */ 
    int LineNumber() const;

	void SetLineNumber(const int lineNumber);

	/**
    * Get issue location file name
    * @return file name string
    */

	const string& IssueLocation() const;
    
    /**
    * Get compare filename
    * @return filename string
    */ 
    const string& CompareFileName() const;

	/** 
    * Return reson behind the compilation error
    */ 
    const string& CompilationError() const;
    

private:
    //! Headerfile where the issue is found from
    string         iHeaderFile;

    //! Fully qualified name of the cause
    string         iFQName;

    //! ID number of the issua
    int            iId;

    //! How severe is the issue found for binary comaptibility
    TBCSeverity      iBCSeverity;
    
    //! How severe is the issue found for source comaptibility
    TSCSeverity      iSCSeverity;

    //! Information needed for ignoring the issue
    string         iIgnoreInformation;

    //! What was happened in the code
    TIssueIdentity iIdentityId;

    //!  type id of the issue
    TIssueType     iTypeId;	

    //! Line number
    int            iLineNumber;

	//! Compare filename
    string         iIssueLoc;

    //! Compare filename
    string         iCompareFileName;

	//! Cause of compilation error
    string         iCompilationError;


};

#endif
