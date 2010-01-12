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


#ifndef __XMLSTRINGCONST_H__
#define __XMLSTRINGCONST_H__

#include "CmdGlobals.h"
#include "XMLUtils.h"

#include <xercesc/dom/DOM.hpp>

XERCES_CPP_NAMESPACE_USE

#ifdef __WIN__

extern const XMLCh* KXMLIdString;
extern const XMLCh* KXMLMangledString;
extern const XMLCh* KXMLMembersString;
extern const XMLCh* KXMLVirtualString;
extern const XMLCh* KXMLPublicString;
extern const XMLCh* KXMLPrivateString;
extern const XMLCh* KXMLProtectedString;
extern const XMLCh* KXMLAccessString;
extern const XMLCh* KXMLAttributeString;
extern const XMLCh* KXMLExportedString;
extern const XMLCh* KXMLExplicitString;
extern const XMLCh* KXMLInlineString;
extern const XMLCh* KXMLArtificialString;
extern const XMLCh* KXMLNameString;
extern const XMLCh* KXMLTypeString;
extern const XMLCh* KXMLHeaderfilenamesString;
extern const XMLCh* KXMLHeaderfileString;
extern const XMLCh* KXMLContextString;
extern const XMLCh* KXMLSizeString;
extern const XMLCh* KXMLAlignString;
extern const XMLCh* KXMLBasesString;
extern const XMLCh* KXMLConstString;
extern const XMLCh* KXMLInitString;
extern const XMLCh* KXMLReturnsString;
extern const XMLCh* KXMLMutableString;
extern const XMLCh* KXMLOffsetString;
extern const XMLCh* KXMLDefaultString;
extern const XMLCh* KXMLMaxString;
extern const XMLCh* KXMIncompleteString;
extern const XMLCh* KXMLMebmersString;
extern const XMLCh* KXMLPureVirtualString;
extern const XMLCh* KXMLStaticString;
extern const XMLCh* KXMLBaseTypeString;
extern const XMLCh* KXMLAbstractString;
extern const XMLCh* KXMLFileIdString;
extern const XMLCh* KXMLLineString;
extern const XMLCh* KXMLGlobalNamespaceString;

extern const XMLCh* KXMLArgumentString;
extern const XMLCh* KXMLEllipsisString;
extern const XMLCh* KXMLArrayTypeString;
extern const XMLCh* KXMLConverterString;
extern const XMLCh* KXMLEnumValueString;
extern const XMLCh* KXMLEnumerationString;
extern const XMLCh* KXMLBaseString;
extern const XMLCh* KXMLClassString;
extern const XMLCh* KXMLConstructorString;
extern const XMLCh* KXMLCvQualifiedTypeString;
extern const XMLCh* KXMLFileString;
extern const XMLCh* KXMLFundamentalTypeString;
extern const XMLCh* KXMLTypedefString;
extern const XMLCh* KXMLNamespaceString;
extern const XMLCh* KXMLVariableString;
extern const XMLCh* KXMLMethodString;
extern const XMLCh* KXMLFunctionString;
extern const XMLCh* KXMLDestructorString;
extern const XMLCh* KXMLFieldString;
extern const XMLCh* KXMLFunctionTypeString;
extern const XMLCh* KXMLMethodTypeString;
extern const XMLCh* KXMLNamespaceAliasString;
extern const XMLCh* KXMLOffsetTypeString;
extern const XMLCh* KXMLOperatorFunctionString;
extern const XMLCh* KXMLOperatorMethodString;
extern const XMLCh* KXMLPointerTypeString;
extern const XMLCh* KXMLReferenceTypeString;
extern const XMLCh* KXMLStructString;
extern const XMLCh* KXMLUnimplementedString;
extern const XMLCh* KXMLUnionString;
extern const char KAnonymousChar;

extern const XMLCh* KXMLIgnoreContext;
extern const XMLCh* KAnonymousName;

//Self generated nodes/attributes
extern const XMLCh* KXMLBBCPublicConstructorString;
extern const XMLCh* KXMLBBCProtectedConstructorString;
extern const XMLCh* KXMLBBCDestructorAccessString;

extern const XMLCh* KXMLBBCAccessPublicString;
extern const XMLCh* KXMLBBCAccessProtectedString;
extern const XMLCh* KXMLBBCAccessPrivateString;

extern const XMLCh* KXMLBBCPublicInlineString;
extern const XMLCh* KXMLBBCProtectedInlineString;
extern const XMLCh* KXMLBBCVirtualString;
extern const XMLCh* KXMLBBCVirtualInheritanceString;
extern const XMLCh* KXMLBBCFQNameString;
extern const XMLCh* KXMLBBCAnalysisStatus;

extern const XMLCh* KXMLBBCAnalysisStatusAnalysing;
extern const XMLCh* KXMLBBCAnalysisStatusClean;
extern const XMLCh* KXMLBBCAnalysisStatusIssues;

extern const XMLCh* KXMLBBCVirtualFunctionIndex;

extern const XMLCh* KXML1String;
extern const XMLCh* KXML0String;


const int KEntityComparisonTableCount=33;
extern const EntityComparisonElement KEntityComparisonTable[KEntityComparisonTableCount];

extern const XMLCh* KXMLEmptyString;
extern const XMLCh* KXMLAnonymousNamespacePrefix;
extern const XMLCh* KXMLInternalNamePrefix;
extern const XMLCh* KXMLPlatformVersion;

#else

// other than Windows platform defines
extern const char* KXMLIdString;
extern const char* KXMLMangledString;
extern const char* KXMLMembersString;
extern const char* KXMLVirtualString;
extern const char* KXMLPublicString;
extern const char* KXMLPrivateString;
extern const char* KXMLProtectedString;
extern const char* KXMLAccessString;
extern const char* KXMLAttributeString;
extern const char* KXMLExportedString;
extern const char* KXMLExplicitString;
extern const char* KXMLInlineString;
extern const char* KXMLArtificialString;
extern const char* KXMLNameString;
extern const char* KXMLTypeString;
extern const char* KXMLHeaderfilenamesString;
extern const char* KXMLHeaderfileString;
extern const char* KXMLContextString;
extern const char* KXMLSizeString;
extern const char* KXMLAlignString;
extern const char* KXMLBasesString;
extern const char* KXMLConstString;
extern const char* KXMLInitString;
extern const char* KXMLReturnsString;
extern const char* KXMLMutableString;
extern const char* KXMLOffsetString;
extern const char* KXMLDefaultString;
extern const char* KXMLMaxString;
extern const char* KXMIncompleteString;
extern const char* KXMLMebmersString;
extern const char* KXMLPureVirtualString;
extern const char* KXMLStaticString;
extern const char* KXMLBaseTypeString;
extern const char* KXMLAbstractString;
extern const char* KXMLFileIdString;
extern const char* KXMLLineString;
extern const char* KXMLGlobalNamespaceString;

extern const char* KXMLArgumentString;
extern const char* KXMLEllipsisString;
extern const char* KXMLArrayTypeString;
extern const char* KXMLConverterString;
extern const char* KXMLEnumValueString;
extern const char* KXMLEnumerationString;
extern const char* KXMLBaseString;
extern const char* KXMLClassString;
extern const char* KXMLConstructorString;
extern const char* KXMLCvQualifiedTypeString;
extern const char* KXMLFileString;
extern const char* KXMLFundamentalTypeString;
extern const char* KXMLTypedefString;
extern const char* KXMLNamespaceString;
extern const char* KXMLVariableString;
extern const char* KXMLMethodString;
extern const char* KXMLFunctionString;
extern const char* KXMLDestructorString;
extern const char* KXMLFieldString;
extern const char* KXMLFunctionTypeString;
extern const char* KXMLMethodTypeString;
extern const char* KXMLNamespaceAliasString;
extern const char* KXMLOffsetTypeString;
extern const char* KXMLOperatorFunctionString;
extern const char* KXMLOperatorMethodString;
extern const char* KXMLPointerTypeString;
extern const char* KXMLReferenceTypeString;
extern const char* KXMLStructString;
extern const char* KXMLUnimplementedString;
extern const char* KXMLUnionString;
extern const char KAnonymousChar;

extern const char* KXMLIgnoreContext;
extern const char* KAnonymousName;

//Self generated nodes/attributes
extern const char* KXMLBBCPublicConstructorString;
extern const char* KXMLBBCProtectedConstructorString;
extern const char* KXMLBBCDestructorAccessString;
extern const char* KXMLBBCAccessPublicString;
extern const char* KXMLBBCAccessProtectedString;
extern const char* KXMLBBCAccessPrivateString;

extern const char* KXMLBBCPublicInlineString;
extern const char* KXMLBBCProtectedInlineString;
extern const char* KXMLBBCVirtualString;
extern const char* KXMLBBCVirtualInheritanceString;
extern const char* KXMLBBCFQNameString;
extern const char* KXMLBBCAnalysisStatus;

extern const char* KXMLBBCAnalysisStatusAnalysing;
extern const char* KXMLBBCAnalysisStatusClean;
extern const char* KXMLBBCAnalysisStatusIssues;

extern const char* KXMLBBCVirtualFunctionIndex;


extern const char* KXML1String;
extern const char* KXML0String;


const int KEntityComparisonTableCount=33;
extern const EntityComparisonElement KEntityComparisonTable[KEntityComparisonTableCount];

extern const char* KXMLEmptyString;
extern const char* KXMLAnonymousNamespacePrefix;
extern const char* KXMLInternalNamePrefix;
extern const char* KXMLPlatformVersion;


#endif
#endif
