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


#include <xercesc/dom/DOM.hpp>
#include "XMLStringConst.h"

#include "CmdGlobals.h"

#ifdef __WIN__
// Windows platform defines
const XMLCh* KXMLIdString = (const XMLCh*)L"id";
const XMLCh* KXMLMangledString = (const XMLCh*)L"mangled";
const XMLCh* KXMLMembersString = (const XMLCh*)L"members";
const XMLCh* KXMLVirtualString = (const XMLCh*)L"virtual";
const XMLCh* KXMLPublicString = (const XMLCh*)L"public";
const XMLCh* KXMLPrivateString = (const XMLCh*)L"private";
const XMLCh* KXMLProtectedString = (const XMLCh*)L"protected";
const XMLCh* KXMLAccessString = (const XMLCh*)L"access";
const XMLCh* KXMLAttributeString = (const XMLCh*)L"attributes";
const XMLCh* KXMLExportedString = (const XMLCh*)L"gccxml(exported)";
const XMLCh* KXMLExplicitString = (const XMLCh*)L"explicit";
const XMLCh* KXMLInlineString = (const XMLCh*)L"inline";
const XMLCh* KXMLArtificialString = (const XMLCh*)L"artificial";
const XMLCh* KXMLNameString = (const XMLCh*)L"name";
const XMLCh* KXMLTypeString = (const XMLCh*)L"type";
const XMLCh* KXMLHeaderfilenamesString = (const XMLCh*)L"headerfilenames";
const XMLCh* KXMLHeaderfileString = (const XMLCh*)L"headerfile";
const XMLCh* KXMLContextString = (const XMLCh*)L"context";
const XMLCh* KXMLSizeString = (const XMLCh*)L"size";
const XMLCh* KXMLAlignString = (const XMLCh*)L"align";
const XMLCh* KXMLBasesString = (const XMLCh*)L"bases";
const XMLCh* KXMLConstString = (const XMLCh*)L"const";
const XMLCh* KXMLInitString = (const XMLCh*)L"init";
const XMLCh* KXMLReturnsString = (const XMLCh*)L"returns";
const XMLCh* KXMLMutableString = (const XMLCh*)L"mutable";
const XMLCh* KXMLOffsetString = (const XMLCh*)L"offset";
const XMLCh* KXMLDefaultString = (const XMLCh*)L"default";
const XMLCh* KXMLMaxString = (const XMLCh*)L"max";
const XMLCh* KXMIncompleteString = (const XMLCh*)L"incomplete";
const XMLCh* KXMLMebmersString = (const XMLCh*)L"members";
const XMLCh* KXMLPureVirtualString = (const XMLCh*)L"pure_virtual";
const XMLCh* KXMLStaticString = (const XMLCh*)L"static";
const XMLCh* KXMLBaseTypeString = (const XMLCh*)L"base";
const XMLCh* KXMLAbstractString = (const XMLCh*)L"abstract";
const XMLCh* KXMLFileIdString = (const XMLCh*)L"file";
const XMLCh* KXMLLineString = (const XMLCh*)L"line";
const XMLCh* KXMLGlobalNamespaceString = (const XMLCh*)L"::";

const XMLCh* KXMLArgumentString = (const XMLCh*)L"Argument";
const XMLCh* KXMLEllipsisString = (const XMLCh*)L"Ellipsis";
const XMLCh* KXMLArrayTypeString = (const XMLCh*)L"ArrayType";
const XMLCh* KXMLConverterString = (const XMLCh*)L"Converter";
const XMLCh* KXMLEnumValueString = (const XMLCh*)L"EnumValue";
const XMLCh* KXMLEnumerationString = (const XMLCh*)L"Enumeration";
const XMLCh* KXMLBaseString = (const XMLCh*)L"Base";
const XMLCh* KXMLClassString = (const XMLCh*)L"Class";
const XMLCh* KXMLConstructorString = (const XMLCh*)L"Constructor";
const XMLCh* KXMLCvQualifiedTypeString = (const XMLCh*)L"CvQualifiedType";
const XMLCh* KXMLFileString = (const XMLCh*)L"File";
const XMLCh* KXMLFundamentalTypeString = (const XMLCh*)L"FundamentalType";
const XMLCh* KXMLTypedefString = (const XMLCh*)L"Typedef";
const XMLCh* KXMLNamespaceString = (const XMLCh*)L"Namespace";
const XMLCh* KXMLVariableString = (const XMLCh*)L"Variable";
const XMLCh* KXMLMethodString = (const XMLCh*)L"Method";
const XMLCh* KXMLFunctionString = (const XMLCh*)L"Function";
const XMLCh* KXMLDestructorString = (const XMLCh*)L"Destructor";
const XMLCh* KXMLFieldString = (const XMLCh*)L"Field";
const XMLCh* KXMLFunctionTypeString = (const XMLCh*)L"FunctionType";
const XMLCh* KXMLMethodTypeString = (const XMLCh*)L"MethodType";
const XMLCh* KXMLNamespaceAliasString = (const XMLCh*)L"NamespaceAlias";
const XMLCh* KXMLOffsetTypeString = (const XMLCh*)L"OffsetType";
const XMLCh* KXMLOperatorFunctionString = (const XMLCh*)L"OperatorFunction";
const XMLCh* KXMLOperatorMethodString = (const XMLCh*)L"OperatorMethod";
const XMLCh* KXMLPointerTypeString = (const XMLCh*)L"PointerType";
const XMLCh* KXMLReferenceTypeString = (const XMLCh*)L"ReferenceType";
const XMLCh* KXMLStructString = (const XMLCh*)L"Struct";
const XMLCh* KXMLUnimplementedString = (const XMLCh*)L"Unimplemented";
const XMLCh* KXMLUnionString = (const XMLCh*)L"Union";

const XMLCh* KXML1String = (const XMLCh*)L"1";
const XMLCh* KXML0String = (const XMLCh*)L"0";

const XMLCh* KXMLIgnoreContext = (const XMLCh*)L"_0";

//Self generated nodes/attributes
const XMLCh* KXMLBBCPublicConstructorString = (const XMLCh*)L"publicconstructor";
const XMLCh* KXMLBBCProtectedConstructorString = (const XMLCh*)L"protectedconstructor";
const XMLCh* KXMLBBCDestructorAccessString = (const XMLCh*)L"destructoraccess";
const XMLCh* KXMLBBCAccessPublicString = (const XMLCh*)L"0";
const XMLCh* KXMLBBCAccessProtectedString = (const XMLCh*)L"1";
const XMLCh* KXMLBBCAccessPrivateString = (const XMLCh*)L"2";

const XMLCh* KXMLBBCPublicInlineString = (const XMLCh*)L"bbcpublicinline";
const XMLCh* KXMLBBCProtectedInlineString = (const XMLCh*)L"bbcprotectedinline";
const XMLCh* KXMLBBCVirtualString = (const XMLCh*)L"bbcvirtual";
const XMLCh* KXMLBBCVirtualInheritanceString = (const XMLCh*)L"bbcvirtualinheritance";
const XMLCh* KXMLBBCFQNameString = (const XMLCh*)L"bbcfqname";
const XMLCh* KXMLBBCAnalysisStatus = (const XMLCh*)L"bbcanalysisstatus";

const XMLCh* KXMLBBCAnalysisStatusAnalysing = (const XMLCh*)L"1";
const XMLCh* KXMLBBCAnalysisStatusClean = (const XMLCh*)L"2";
const XMLCh* KXMLBBCAnalysisStatusIssues = (const XMLCh*)L"3";

const XMLCh* KXMLBBCVirtualFunctionIndex = (const XMLCh*)L"bbcvtableindex";


const XMLCh* KAnonymousName = (const XMLCh*)L"$";

const XMLCh* KXMLEmptyString = (const XMLCh*)L"";

const XMLCh* KXMLAnonymousNamespacePrefix = (const XMLCh*)L"_GLOBAL__N_";
const XMLCh* KXMLInternalNamePrefix = (const XMLCh*)L"__";
const XMLCh* KXMLPlatformVersion = (const XMLCh*)L"versionid";

#else

// other than Windows platform defines
const char* KXMLIdString = "id";
const char* KXMLMangledString = "mangled";
const char* KXMLMembersString = "members";
const char* KXMLVirtualString = "virtual";
const char* KXMLPublicString = "public";
const char* KXMLPrivateString = "private";
const char* KXMLProtectedString = "protected";
const char* KXMLAccessString = "access";
const char* KXMLAttributeString = "attributes";
const char* KXMLExportedString = "gccxml(exported)";
const char* KXMLExplicitString = "explicit";
const char* KXMLInlineString = "inline";
const char* KXMLArtificialString = "artificial";
const char* KXMLNameString = "name";
const char* KXMLTypeString = "type";
const char* KXMLHeaderfilenamesString = "headerfilenames";
const char* KXMLHeaderfileString = "headerfile";
const char* KXMLContextString = "context";
const char* KXMLSizeString = "size";
const char* KXMLAlignString = "align";
const char* KXMLBasesString = "bases";
const char* KXMLConstString = "const";
const char* KXMLInitString = "init";
const char* KXMLReturnsString = "returns";
const char* KXMLMutableString = "mutable";
const char* KXMLOffsetString = "offset";
const char* KXMLDefaultString = "default";
const char* KXMLMaxString = "max";
const char* KXMIncompleteString = "incomplete";
const char* KXMLMebmersString = "members";
const char* KXMLPureVirtualString = "pure_virtual";
const char* KXMLStaticString = "static";
const char* KXMLBaseTypeString = "base";
const char* KXMLAbstractString = "abstract";
const char* KXMLFileIdString = "file";
const char* KXMLLineString = "line";
const char* KXMLGlobalNamespaceString = "::";

const char* KXMLArgumentString = "Argument";
const char* KXMLEllipsisString = "Ellipsis";
const char* KXMLArrayTypeString = "ArrayType";
const char* KXMLConverterString = "Converter";
const char* KXMLEnumValueString = "EnumValue";
const char* KXMLEnumerationString = "Enumeration";
const char* KXMLBaseString = "Base";
const char* KXMLClassString = "Class";
const char* KXMLConstructorString = "Constructor";
const char* KXMLCvQualifiedTypeString = "CvQualifiedType";
const char* KXMLFileString = "File";
const char* KXMLFundamentalTypeString = "FundamentalType";
const char* KXMLTypedefString = "Typedef";
const char* KXMLNamespaceString = "Namespace";
const char* KXMLVariableString = "Variable";
const char* KXMLMethodString = "Method";
const char* KXMLFunctionString = "Function";
const char* KXMLDestructorString = "Destructor";
const char* KXMLFieldString = "Field";
const char* KXMLFunctionTypeString = "FunctionType";
const char* KXMLMethodTypeString = "MethodType";
const char* KXMLNamespaceAliasString = "NamespaceAlias";
const char* KXMLOffsetTypeString = "OffsetType";
const char* KXMLOperatorFunctionString = "OperatorFunction";
const char* KXMLOperatorMethodString = "OperatorMethod";
const char* KXMLPointerTypeString = "PointerType";
const char* KXMLReferenceTypeString = "ReferenceType";
const char* KXMLStructString = "Struct";
const char* KXMLUnimplementedString = "Unimplemented";
const char* KXMLUnionString = "Union";

const char* KXML1String = "1";
const char* KXML0String = "0";

const char* KXMLIgnoreContext = "_0";

//Self generated nodes/attributes
const char* KXMLBBCPublicConstructorString = "publicconstructor";
const char* KXMLBBCProtectedConstructorString = "protectedconstructor";
const char* KXMLBBCDestructorAccessString = "destructoraccess";
const char* KXMLBBCAccessPublicString = "0";
const char* KXMLBBCAccessProtectedString = "1";
const char* KXMLBBCAccessPrivateString = "2";


const char* KXMLBBCPublicInlineString = "bbcpublicinline";
const char* KXMLBBCProtectedInlineString = "bbcprotectedinline";
const char* KXMLBBCVirtualString = "bbcvirtual";
const char* KXMLBBCVirtualInheritanceString = "bbcvirtualinheritance";
const char* KXMLBBCFQNameString = "bbcfqname";
const char* KXMLBBCAnalysisStatus = "bbcanalysisstatus";

const char* KXMLBBCAnalysisStatusAnalysing = "1";
const char* KXMLBBCAnalysisStatusClean = "2";
const char* KXMLBBCAnalysisStatusIssues = "3";

const char* KXMLBBCVirtualFunctionIndex = "bbcvtableindex";

const char* KAnonymousName = ".";

const char* KXMLEmptyString = "";

const char* KXMLAnonymousNamespacePrefix = "_GLOBAL__N_";
const char* KXMLInternalNamePrefix = "__";
const char* KXMLPlatformVersion = "versionid";

#endif
