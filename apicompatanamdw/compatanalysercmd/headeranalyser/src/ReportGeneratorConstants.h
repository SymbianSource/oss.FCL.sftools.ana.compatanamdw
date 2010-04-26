/*
* Copyright (c) 2008, 2009 Nokia Corporation and/or its subsidiary(-ies). 
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


#ifndef __REPORT_GENERATOR_CONSTANTS_H__
#define __REPORT_GENERATOR_CONSTANTS_H__

// Node names for Report XML

#define HEADER_ANALYSER_VERSION "1.6.4"
#define HEADER_ANALYSER_DATE "15th February 2010"
#define HEADER_ANALYSER_REPORT_VERSION "1.2"

#define NODE_REPORTROOT "bbcresults"
#define NODE_HEADER "header"
#define NODE_HEADER_BASELINEVERSION "baselineversion"
#define NODE_HEADER_CURRENTVERSION "currentversion"
#define NODE_HEADER_CURRENTDIR "currentdir"
#define NODE_HEADER_TIMESTAMP "timestamp"
#define NODE_HEADER_TIMESTAMP_DAY "day"
#define NODE_HEADER_TIMESTAMP_MONTH "month"
#define NODE_HEADER_TIMESTAMP_YEAR "year"
#define NODE_HEADER_TIMESTAMP_HOUR "hour"
#define NODE_HEADER_TIMESTAMP_MINUTE "minute"
#define NODE_HEADER_TIMESTAMP_SECOND "second"
#define NODE_HEADER_HAVERSION "haversion"
#define NODE_HEADER_FORMATVERSION "formatversion"
#define NODE_HEADER_CMDLINE "cmdlineparms"
#define NODE_HEADER_CMDLINE_PARM "parm"
#define NODE_HEADER_CMDLINE_PARM "parm"

#define NODE_HEADER_CMDLINE_PARM_PNAME "pname"
#define NODE_HEADER_CMDLINE_PARM_PVALUE "pvalue"

#define NODE_ISSUELIST "issuelist"
#define NODE_ISSUELIST_HEADERFILE "headerfile"
#define NODE_ISSUELIST_HEADERFILE_FILENAME "filename"
#define NODE_ISSUELIST_HEADERFILE_ISSUE "issue"
#define NODE_ISSUELIST_HEADERFILE_COMPARE_FILENAME "comparefilename"
// START -- Support for file checksum and comments
#define NODE_ISSUELIST_HEADERFILE_CHECKSUM "checksum"
#define NODE_ISSUELIST_HEADERFILE_STATUS "status"
#define NODE_ISSUELIST_HEADERFILE_COMMENT "comment"
#define NODE_ISSUELIST_HEADERFILE_SHORTNAME "shortname"
// END   -- Support for file checksum and comments
#define NODE_ISSUELIST_HEADERFILE_ISSUE_ISSUEID "issueid"
#define NODE_ISSUELIST_HEADERFILE_ISSUE_IDENTITYID "identityid"
#define NODE_ISSUELIST_HEADERFILE_ISSUE_IDENTITYDESCRIPTION "identitydescription"
#define NODE_ISSUELIST_HEADERFILE_ISSUE_IGNOREINFORMATION "ignoreinformation"
#define NODE_ISSUELIST_HEADERFILE_ISSUE_LINENUMBER "linenumber"
#define NODE_ISSUELIST_HEADERFILE_ISSUE_ISSUELOC "issuelocation"
#define NODE_ISSUELIST_HEADERFILE_ISSUE_EXTRAINFORMATION "extrainformation"
#define NODE_ISSUELIST_HEADERFILE_ISSUE_TYPEID "typeid"
#define NODE_ISSUELIST_HEADERFILE_ISSUE_TYPESTRING "typestring"
#define NODE_ISSUELIST_HEADERFILE_ISSUE_CAUSE "cause"
#define NODE_ISSUELIST_HEADERFILE_ISSUE_DOCUMENTATION "documentation"
#define NODE_ISSUELIST_HEADERFILE_ISSUE_SEVERITY "severity"
#define NODE_ISSUELIST_HEADERFILE_ISSUE_SCSEVERITY "scseverity"
#define NODE_ISSUELIST_HEADERFILE_ISSUE_SEVERITY_TYPEID "typeid"
#define NODE_ISSUELIST_HEADERFILE_ISSUE_SEVERITY_TYPESTRING "typestring"
#define NODE_ISSUELIST_HEADERFILE_ISSUE_COMPILATION_ERROR "compilationerror"
#define NODE_ISSUELIST_HEADERFILE_ISSUE_APISTRING "api"
#define NODE_ISSUELIST_HEADERFILE_ISSUE_APINAME "name"
#define NODE_ISSUELIST_HEADERFILE_ISSUE_APICATEGORY "category"
#define NODE_ISSUELIST_HEADERFILE_APIINFO_UNKNOWN "Unknown"


#endif
