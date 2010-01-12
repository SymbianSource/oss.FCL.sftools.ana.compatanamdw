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


#include "CmdGlobals.h"
#ifdef __WIN__
#pragma warning(disable:4786)
#endif

#include <assert.h>
#include <map>
#include <list>
#include <string>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include "XMLUtils.h"
#include "XMLStringConst.h"
#include "NodeIndex.h"
#include "XMLModuleErrorHandler.h"
#include "BBCFileUtils.h"
#include "HAException.h"
#include "Utils.h"

using namespace std;

XERCES_CPP_NAMESPACE_USE

//Attributes of the elements, copied from the unofficial DTD for GCCXML


//<!ELEMENT Base EMPTY>
//<!ATTLIST Base access (public | private | protected) "public">
//<!ATTLIST Base type IDREF #REQUIRED>
//<!ATTLIST Base virtual (0 | 1) "0">
//Base
//<Base type="_191" access="public" virtual="0"/>
const int KBaseAttributeCount = 3;
const EntityAttributeElement KBaseAttributes[KBaseAttributeCount]={
                                                {KXMLTypeString,EIdAttribute},
                                                {KXMLAccessString,ESimpleAttribute},
                                                {KXMLVirtualString,EBooleanAttribute}
                                                };

//<!ELEMENT Variable EMPTY>
//<!ATTLIST Variable access (public | private | protected) "public">
//<!ATTLIST Variable artificial CDATA #IMPLIED>
//<!ATTLIST Variable attributes CDATA #IMPLIED>
//<!ATTLIST Variable context IDREF #REQUIRED>
//<!ATTLIST Variable extern (0 | 1) "0">
//<!ATTLIST Variable file CDATA #REQUIRED>
//<!ATTLIST Variable id ID #REQUIRED>
//<!ATTLIST Variable init CDATA #IMPLIED>
//<!ATTLIST Variable line CDATA #REQUIRED>
//<!ATTLIST Variable location CDATA #REQUIRED>
//<!ATTLIST Variable mangled CDATA #IMPLIED>
//<!ATTLIST Variable name CDATA #REQUIRED>
//<!ATTLIST Variable type CDATA #REQUIRED>
//<Variable id="_26" name="KMediaPasswordNotifyUid" type="_575c" init="268454912" context="_1" location="f2:4254" file="f2" line="4254"/>
const int KVariableAttributeCount = 4;
const EntityAttributeElement KVariableAttributes[KVariableAttributeCount]={
                                                {KXMLNameString,ESimpleAttribute},
                                                {KXMLTypeString,EIdAttribute},
                                                {KXMLInitString,EOptionalSimpleAttribute},
                                                //{KXMLContextString,EIdAttribute},
                                                {KXMLAccessString,EOptionalSimpleAttribute}
                                                };

//<!ELEMENT FundamentalType EMPTY>
//<!ATTLIST FundamentalType align CDATA #IMPLIED>
//<!ATTLIST FundamentalType attributes CDATA #IMPLIED>
//<!ATTLIST FundamentalType id ID #REQUIRED>
//<!ATTLIST FundamentalType name CDATA #REQUIRED>
//<!ATTLIST FundamentalType size CDATA #IMPLIED>
//<FundamentalType id="_573" name="unsigned int" size="32" align="32"/>
const int KFundamentalTypeAttributeCount = 3;
const EntityAttributeElement KFundamentalTypeAttributes[KFundamentalTypeAttributeCount]={
                                                {KXMLNameString,ESimpleAttribute},
                                                {KXMLSizeString,ESimpleAttribute},
                                                {KXMLAlignString,ESimpleAttribute}
                                                };

//<!ELEMENT Typedef EMPTY>
//<!ATTLIST Typedef attributes CDATA #IMPLIED>
//<!ATTLIST Typedef context IDREF #REQUIRED>
//<!ATTLIST Typedef file CDATA #REQUIRED>
//<!ATTLIST Typedef id ID #REQUIRED>
//<!ATTLIST Typedef line CDATA #REQUIRED>
//<!ATTLIST Typedef location CDATA #REQUIRED>
//<!ATTLIST Typedef name CDATA #REQUIRED>
//<!ATTLIST Typedef type CDATA #REQUIRED>
//<Typedef id="_574" name="TUint" type="_573" context="_1" location="f10:600" file="f10" line="600"/>
const int KTypedefAttributeCount = 2;
const EntityAttributeElement KTypedefAttributes[KTypedefAttributeCount]={
                                                {KXMLNameString,ESimpleAttribute},
                                                {KXMLTypeString,EIdAttribute}//,
                                                //{KXMLContextString,EIdAttribute}
                                                };

//<!ELEMENT Namespace EMPTY>
//<!ATTLIST Namespace attributes CDATA #IMPLIED>
//<!ATTLIST Namespace context IDREF #IMPLIED>
//<!ATTLIST Namespace id ID #REQUIRED>
//<!ATTLIST Namespace mangled CDATA #IMPLIED>
//<!ATTLIST Namespace members CDATA #IMPLIED>
//<!ATTLIST Namespace name CDATA #REQUIRED>
//<Namespace id="_2" name="std" context="_1" members="" mangled="_Z3std"/>
const int KNamespaceAttributeCount = 2;
const EntityAttributeElement KNamespaceAttributes[KNamespaceAttributeCount]={
                                                {KXMLNameString,ESimpleAttribute},
                                                {KXMLContextString,EOptionalIdAttribute}//,
                                                //{KXMLMembersString,EIdAttribute}
                                                };

//<!ELEMENT CvQualifiedType EMPTY>
//<!ATTLIST CvQualifiedType align CDATA #IMPLIED>
//<!ATTLIST CvQualifiedType attributes CDATA #IMPLIED>
//<!ATTLIST CvQualifiedType const CDATA #IMPLIED>
//<!ATTLIST CvQualifiedType id ID #REQUIRED>
//<!ATTLIST CvQualifiedType restrict CDATA #IMPLIED>
//<!ATTLIST CvQualifiedType size CDATA #IMPLIED>
//<!ATTLIST CvQualifiedType type IDREF #REQUIRED>
//<!ATTLIST CvQualifiedType volatile CDATA #IMPLIED>
//<CvQualifiedType id="_4c" type="_4" const="1"/>
const int KCvQualifiedTypeAttributeCount = 2;
const EntityAttributeElement KCvQualifiedTypeAttributes[KCvQualifiedTypeAttributeCount]={
                                                {KXMLTypeString,EIdAttribute},
                                                {KXMLConstString,EBooleanAttribute}
                                                };

//<!ELEMENT Function (Argument | Ellipsis)*>
//<!ATTLIST Function attributes CDATA #IMPLIED>
//<!ATTLIST Function context IDREF #REQUIRED>
//<!ATTLIST Function endline CDATA #IMPLIED>
//<!ATTLIST Function extern (0 | 1) "0">
//<!ATTLIST Function file CDATA #REQUIRED>
//<!ATTLIST Function id ID #REQUIRED>
//<!ATTLIST Function line CDATA #REQUIRED>
//<!ATTLIST Function location CDATA #REQUIRED>
//<!ATTLIST Function mangled CDATA #IMPLIED>
//<!ATTLIST Function name CDATA #REQUIRED>
//<!ATTLIST Function returns CDATA #REQUIRED>
//<!ATTLIST Function throw CDATA #IMPLIED>
//<Function id="_8" name="PanicTFixedArray" returns="_585" context="_1" mangled="_Z16PanicTFixedArrayv" location="f1:4492" file="f1" line="4492" extern="1"/>
const int KFunctionAttributeCount = 4;
const EntityAttributeElement KFunctionAttributes[KFunctionAttributeCount]={
                                                {KXMLNameString,ESimpleAttribute},
                                                {KXMLReturnsString,EIdAttribute},
                                                {KXMLContextString,EIdAttribute},
                                                {KXMLConstString,EBooleanAttribute}
                                                };

//<!ELEMENT Enumeration (EnumValue)+>
//<!ATTLIST Enumeration access (public | private | protected) "public">
//<!ATTLIST Enumeration align CDATA #IMPLIED>
//<!ATTLIST Enumeration artificial CDATA #IMPLIED>
//<!ATTLIST Enumeration attributes CDATA #IMPLIED>
//<!ATTLIST Enumeration context CDATA #REQUIRED>
//<!ATTLIST Enumeration file CDATA #REQUIRED>
//<!ATTLIST Enumeration id ID #REQUIRED>
//<!ATTLIST Enumeration line CDATA #REQUIRED>
//<!ATTLIST Enumeration location CDATA #REQUIRED>
//<!ATTLIST Enumeration name CDATA #REQUIRED>
//<!ATTLIST Enumeration size CDATA #IMPLIED>
//<Enumeration id="_25" name="TMediaPswdNotifyExitMode" context="_1" location="f2:4259" file="f2" line="4259" artificial="1" size="32" align="32">
const int KEnumerationAttributeCount = 4;
const EntityAttributeElement KEnumerationAttributes[KEnumerationAttributeCount]={
                                                {KXMLAccessString,EOptionalSimpleAttribute},
                                                {KXMLAlignString,ESimpleAttribute},
                                                //{KXMLContextString,EIdAttribute},
                                                {KXMLNameString,ESimpleAttribute},
                                                {KXMLSizeString,ESimpleAttribute}
                                                };

//<!ELEMENT Field EMPTY>
//<!ATTLIST Field access (public | private | protected) "public">
//<!ATTLIST Field attributes CDATA #IMPLIED>
//<!ATTLIST Field bits CDATA #IMPLIED>
//<!ATTLIST Field context IDREF #REQUIRED>
//<!ATTLIST Field file CDATA #REQUIRED>
//<!ATTLIST Field id ID #REQUIRED>
//<!ATTLIST Field line CDATA #REQUIRED>
//<!ATTLIST Field location CDATA #REQUIRED>
//<!ATTLIST Field mangled CDATA #IMPLIED>
//<!ATTLIST Field mutable (0 | 1) "0">
//<!ATTLIST Field name CDATA #REQUIRED>
//<!ATTLIST Field offset CDATA #IMPLIED>
//<!ATTLIST Field type CDATA #REQUIRED>
//<Field id="_2157" name="iFlags" type="_575" offset="256" context="_178" access="private" mangled="_ZN9RMessage26iFlagsE" mutable="1" location="f3:3155" file="f3" line="3155"/>
const int KFieldAttributeCount = 5;
const EntityAttributeElement KFieldAttributes[KFieldAttributeCount]={
                                                {KXMLAccessString,EOptionalSimpleAttribute},
                                                {KXMLMutableString,EBooleanAttribute},
                                                {KXMLNameString,ESimpleAttribute},
                                                {KXMLOffsetString,ESimpleAttribute},
                                                {KXMLTypeString,ETypeAttribute}
                                                };

//<!ELEMENT Argument EMPTY>
//<!ATTLIST Argument attributes CDATA #IMPLIED>
//<!ATTLIST Argument default CDATA #IMPLIED>
//<!ATTLIST Argument name CDATA #IMPLIED>
//<!-- type can not be an IDREF as it might be "_4c" etc. which will be 
//an invalid id -->
//<!ATTLIST Argument type CDATA #REQUIRED>
//<Argument name="_ctor_arg" type="_128" location="f0:91" file="f0" line="91"/>
const int KArgumentAttributeCount = 3;
const EntityAttributeElement KArgumentAttributes[KArgumentAttributeCount]={
                                                {KXMLNameString,ESimpleAttribute},
                                                {KXMLTypeString,EIdAttribute},
                                                {KXMLDefaultString,EOptionalSimpleAttribute}
                                                };
//<!ELEMENT Ellipsis EMPTY>
const int KEllipsisAttributeCount = 0;
//const EntityAttributeElement KEllipsisAttributes[KEllipsisAttributeCount]={};


//<!ELEMENT ArrayType EMPTY>
//<!ATTLIST ArrayType align CDATA #IMPLIED>
//<!ATTLIST ArrayType attributes CDATA #IMPLIED>
//<!ATTLIST ArrayType id ID #REQUIRED>
//<!ATTLIST ArrayType max CDATA #REQUIRED>
//<!ATTLIST ArrayType min CDATA #FIXED "0">
//<!ATTLIST ArrayType size CDATA #IMPLIED>
//<!ATTLIST ArrayType type IDREF #REQUIRED>
const int KArrayTypeAttributeCount = 2;
const EntityAttributeElement KArrayTypeAttributes[KArrayTypeAttributeCount]={
                                                {KXMLTypeString,EIdAttribute},
                                                {KXMLMaxString,ESimpleAttribute}
                                                };
//<!ELEMENT Class (Base)*>
//<!ATTLIST Class abstract (0 | 1) "0">
//<!ATTLIST Class access (public | private | protected) "public">
//<!ATTLIST Class align CDATA #IMPLIED>
//<!ATTLIST Class artificial CDATA #IMPLIED>
//<!ATTLIST Class attributes CDATA #IMPLIED>
//<!ATTLIST Class bases CDATA #IMPLIED>
//<!ATTLIST Class context IDREF #REQUIRED>
//<!ATTLIST Class file CDATA #REQUIRED>
//<!ATTLIST Class id ID #REQUIRED>
//<!ATTLIST Class incomplete (0 | 1) "0">
//<!ATTLIST Class line CDATA #REQUIRED>
//<!ATTLIST Class location CDATA #REQUIRED>
//<!ATTLIST Class mangled CDATA #REQUIRED>
//<!ATTLIST Class members CDATA #IMPLIED>
//<!ATTLIST Class name CDATA #REQUIRED>
//<!ATTLIST Class size CDATA #IMPLIED>
const int KClassAttributeCount = 6;
const EntityAttributeElement KClassAttributes[KClassAttributeCount]={
                                                {KXMLAccessString,EOptionalSimpleAttribute},
                                                {KXMLAlignString,ESimpleAttribute},
                                                {KXMIncompleteString,EBooleanAttribute},				
                                                {KXMLNameString,ESimpleAttribute},
                                                {KXMLSizeString,ESimpleAttribute},
                                                {KXMLMebmersString,EIdAttribute}
                                                };
//<!ELEMENT Constructor (Argument | Ellipsis)*>
//<!ATTLIST Constructor access (public | private | protected) "public">
//<!ATTLIST Constructor artificial CDATA #IMPLIED>
//<!ATTLIST Constructor attributes CDATA #IMPLIED>
//<!ATTLIST Constructor context CDATA #REQUIRED>
//<!ATTLIST Constructor endline CDATA #IMPLIED>
//<!ATTLIST Constructor extern (0 | 1) "0">
//<!ATTLIST Constructor file CDATA #REQUIRED>
//<!ATTLIST Constructor id ID #REQUIRED>
//<!ATTLIST Constructor line CDATA #REQUIRED>
//<!ATTLIST Constructor location CDATA #REQUIRED>
//<!ATTLIST Constructor mangled CDATA #REQUIRED>
//<!ATTLIST Constructor name CDATA #REQUIRED>
//<!ATTLIST Constructor throw CDATA #IMPLIED>
const int KConstructorAttributeCount = 2;
const EntityAttributeElement KConstructorAttributes[KConstructorAttributeCount]={
                                                {KXMLAccessString,EOptionalSimpleAttribute},
                                                {KXMLNameString,ESimpleAttribute}
                                                };
//<!ELEMENT Converter EMPTY>
//<!ATTLIST Converter access (public | private | protected) "public">
//<!ATTLIST Converter attributes CDATA #IMPLIED>
//<!ATTLIST Converter const (0 | 1) "0">
//<!ATTLIST Converter context IDREF #REQUIRED>
//<!ATTLIST Converter endline CDATA #IMPLIED>
//<!ATTLIST Converter extern (0 | 1) "0">
//<!ATTLIST Converter file CDATA #REQUIRED>
//<!ATTLIST Converter id ID #REQUIRED>
//<!ATTLIST Converter line CDATA #REQUIRED>
//<!ATTLIST Converter location CDATA #REQUIRED>
//<!ATTLIST Converter mangled CDATA #REQUIRED>
//<!ATTLIST Converter name CDATA #REQUIRED>
//<!ATTLIST Converter returns IDREF #REQUIRED>
//<!ATTLIST Converter throw CDATA #IMPLIED>
//<!ATTLIST Converter virtual (0 | 1) "0">
const int KConverterAttributeCount = 0; 
//const EntityAttributeElement KConverterAttributes[KConverterAttributeCount]={};

//<!ELEMENT Destructor (Argument)*>
//<!ATTLIST Destructor access (public | private | protected) "public">
//<!ATTLIST Destructor artificial CDATA #IMPLIED>
//<!ATTLIST Destructor attributes CDATA #IMPLIED>
//<!ATTLIST Destructor context IDREF #REQUIRED>
//<!ATTLIST Destructor endline CDATA #IMPLIED>
//<!ATTLIST Destructor extern (0 | 1) "0">
//<!ATTLIST Destructor file CDATA #REQUIRED>
//<!ATTLIST Destructor id ID #REQUIRED>
//<!ATTLIST Destructor line CDATA #REQUIRED>
//<!ATTLIST Destructor location CDATA #REQUIRED>
//<!ATTLIST Destructor mangled CDATA #REQUIRED>
//<!ATTLIST Destructor name CDATA #REQUIRED>
//<!ATTLIST Destructor throw CDATA #IMPLIED>
//<!ATTLIST Destructor virtual (0 | 1) "0">
const int KDestructorAttributeCount = 3;
const EntityAttributeElement KDestructorAttributes[KDestructorAttributeCount]={
                                                {KXMLAccessString,EOptionalSimpleAttribute},
                                                {KXMLNameString,ESimpleAttribute},
                                                {KXMLVirtualString,EBooleanAttribute}
                                                };
//<!ELEMENT EnumValue EMPTY>
//<!ATTLIST EnumValue init CDATA #REQUIRED>
//<!ATTLIST EnumValue name CDATA #REQUIRED>
const int KEnumValueAttributeCount = 2;
const EntityAttributeElement KEnumValueAttributes[KEnumValueAttributeCount]={
                                                {KXMLInitString,ESimpleAttribute},
                                                {KXMLNameString,ESimpleAttribute} 
                                                };
//<!ELEMENT File EMPTY>
const int KFileAttributeCount = 0;
//const EntityAttributeElement KFileAttributes[KFileAttributeCount]={};

//<!ELEMENT FunctionType (Argument | Ellipsis)*>
//<!ATTLIST FunctionType attributes CDATA #IMPLIED>
//<!ATTLIST FunctionType id ID #REQUIRED>
//<!ATTLIST FunctionType returns IDREF #REQUIRED>
const int KFunctionTypeAttributeCount =	1;
const EntityAttributeElement KFunctionTypeAttributes[KFunctionTypeAttributeCount]={
                                                {KXMLReturnsString,EIdAttribute}
                                                };
//<!ELEMENT Method (Argument | Ellipsis)*>
//<!ATTLIST Method access (public | private | protected) "public">
//<!ATTLIST Method attributes CDATA #IMPLIED>
//<!ATTLIST Method const (0 | 1) "0">
//<!ATTLIST Method context IDREF #REQUIRED>
//<!ATTLIST Method endline CDATA #IMPLIED>
//<!ATTLIST Method extern (0 | 1) "0">
//<!ATTLIST Method file CDATA #REQUIRED>
//<!ATTLIST Method id ID #REQUIRED>
//<!ATTLIST Method line CDATA #REQUIRED>
//<!ATTLIST Method location CDATA #REQUIRED>
//<!ATTLIST Method mangled CDATA #REQUIRED>
//<!ATTLIST Method name CDATA #REQUIRED>
//<!ATTLIST Method pure_virtual (0 | 1) "0">
//<!ATTLIST Method returns CDATA #REQUIRED>
//<!ATTLIST Method static (0 | 1) "0">
//<!ATTLIST Method throw CDATA #IMPLIED>
//<!ATTLIST Method virtual (0 | 1) "0">
const int KMethodAttributeCount = 7;
const EntityAttributeElement KMethodAttributes[KMethodAttributeCount]={
                                                {KXMLAccessString,EOptionalSimpleAttribute},
                                                {KXMLConstString,EBooleanAttribute},
                                                {KXMLNameString,ESimpleAttribute},
                                                {KXMLPureVirtualString,EBooleanAttribute},
                                                {KXMLReturnsString,EIdAttribute},
                                                {KXMLStaticString,EBooleanAttribute},
                                                {KXMLVirtualString,EBooleanAttribute}
                                                };

//<!ELEMENT MethodType (Argument | Ellipsis)*>
//<!ATTLIST MethodType attributes CDATA #IMPLIED>
//<!ATTLIST MethodType basetype IDREF #REQUIRED>
//<!ATTLIST MethodType id ID #REQUIRED>
//<!ATTLIST MethodType returns CDATA #REQUIRED>
const int KMethodTypeAttributeCount = 2;
const EntityAttributeElement KMethodTypeAttributes[KMethodTypeAttributeCount]={
                                                {KXMLBaseTypeString,EIdAttribute},
                                                {KXMLReturnsString,EIdAttribute},
                                                };
//<!ELEMENT NamespaceAlias EMPTY>
//<!ATTLIST NamespaceAlias context IDREF #IMPLIED>
//<!ATTLIST NamespaceAlias id ID #REQUIRED>
//<!ATTLIST NamespaceAlias mangled CDATA #IMPLIED>
//<!ATTLIST NamespaceAlias name CDATA #REQUIRED>
//<!ATTLIST NamespaceAlias namespace CDATA #REQUIRED>
const int KNamespaceAliasAttributeCount = 0;
//const EntityAttributeElement KNamespaceAliasAttributes[KNamespaceAliasAttributeCount]={};

//<!ELEMENT OffsetType EMPTY>
//<!ATTLIST OffsetType align CDATA #IMPLIED>
//<!ATTLIST OffsetType attributes CDATA #IMPLIED>
//<!ATTLIST OffsetType id ID #REQUIRED>
//<!ATTLIST OffsetType basetype IDREF #REQUIRED>
//<!ATTLIST OffsetType size CDATA #IMPLIED>
//<!ATTLIST OffsetType type CDATA #REQUIRED>
const int KOffsetTypeAttributeCount = 0;
//const EntityAttributeElement KOffsetTypeAttributes[KOffsetTypeAttributeCount]={};

//<!ELEMENT OperatorFunction (Argument | Ellipsis)*>
//<!ATTLIST OperatorFunction attributes CDATA #IMPLIED>
//<!ATTLIST OperatorFunction context IDREF #REQUIRED>
//<!ATTLIST OperatorFunction endline CDATA #IMPLIED>
//<!ATTLIST OperatorFunction extern (0 | 1) "0">
//<!ATTLIST OperatorFunction file CDATA #REQUIRED>
//<!ATTLIST OperatorFunction id ID #REQUIRED>
//<!ATTLIST OperatorFunction line CDATA #REQUIRED>
//<!ATTLIST OperatorFunction location CDATA #REQUIRED>
//<!ATTLIST OperatorFunction mangled CDATA #REQUIRED>
//<!ATTLIST OperatorFunction name CDATA #REQUIRED>
//<!ATTLIST OperatorFunction returns IDREF #REQUIRED>
//<!ATTLIST OperatorFunction throw CDATA #IMPLIED>
const int KOperatorFunctionAttributeCount = 2;
const EntityAttributeElement KOperatorFunctionAttributes[KOperatorFunctionAttributeCount]={
                                                {KXMLNameString,ESimpleAttribute},
                                                {KXMLReturnsString,EIdAttribute}
                                                };

//<!ELEMENT OperatorMethod (Argument | Ellipsis)*>
//<!ATTLIST OperatorMethod access (public | private | protected) "public">
//<!ATTLIST OperatorMethod attributes CDATA #IMPLIED>
//<!ATTLIST OperatorMethod const (0 | 1) "0">
//<!ATTLIST OperatorMethod context IDREF #REQUIRED>
//<!ATTLIST OperatorMethod endline CDATA #IMPLIED>
//<!ATTLIST OperatorMethod extern (0 | 1) "0">
//<!ATTLIST OperatorMethod file CDATA #REQUIRED>
//<!ATTLIST OperatorMethod id ID #REQUIRED>
//<!ATTLIST OperatorMethod line CDATA #REQUIRED>
//<!ATTLIST OperatorMethod location CDATA #REQUIRED>
//<!ATTLIST OperatorMethod mangled CDATA #REQUIRED>
//<!ATTLIST OperatorMethod name CDATA #REQUIRED>
//<!ATTLIST OperatorMethod pure_virtual (0 | 1) "0">
//<!ATTLIST OperatorMethod returns IDREF #REQUIRED>
//<!ATTLIST OperatorMethod static (0 | 1) "0">
//<!ATTLIST OperatorMethod throw CDATA #IMPLIED>
//<!ATTLIST OperatorMethod virtual (0 | 1) "0">
const int KOperatorMethodAttributeCount = 6;
const EntityAttributeElement KOperatorMethodAttributes[KOperatorMethodAttributeCount]={
                                                {KXMLAccessString,EOptionalSimpleAttribute},
                                                {KXMLConstString,EBooleanAttribute},
                                                {KXMLNameString,ESimpleAttribute},
                                                {KXMLPureVirtualString,EBooleanAttribute},
                                                {KXMLVirtualString,EBooleanAttribute},
                                                {KXMLReturnsString,EIdAttribute}
                                                };
//<!ELEMENT PointerType EMPTY>
//<!ATTLIST PointerType align CDATA #IMPLIED>
//<!ATTLIST PointerType attributes CDATA #IMPLIED>
//<!ATTLIST PointerType id ID #REQUIRED>
//<!ATTLIST PointerType size CDATA #IMPLIED>
//<!ATTLIST PointerType type CDATA #REQUIRED>
const int KPointerTypeAttributeCount = 1;
const EntityAttributeElement KPointerTypeAttributes[KPointerTypeAttributeCount]={
                                                {KXMLTypeString,EIdAttribute}
                                                };
//<!ELEMENT ReferenceType EMPTY>
//<!ATTLIST ReferenceType align CDATA #IMPLIED>
//<!ATTLIST ReferenceType attributes CDATA #IMPLIED>
//<!ATTLIST ReferenceType id ID #REQUIRED>
//<!ATTLIST ReferenceType size CDATA #IMPLIED>
//<!ATTLIST ReferenceType type CDATA #REQUIRED>
const int KReferenceTypeAttributeCount = 1;
const EntityAttributeElement KReferenceTypeAttributes[KReferenceTypeAttributeCount]={
                                                {KXMLTypeString,EIdAttribute}
                                                };

//<!ELEMENT Struct (Base)*>
//<!ATTLIST Struct abstract (0 | 1) "0">
//<!ATTLIST Struct access (public | private | protected) "public">
//<!ATTLIST Struct align CDATA #IMPLIED>
//<!ATTLIST Struct artificial (0 | 1) "0">
//<!ATTLIST Struct attributes CDATA #IMPLIED>
//<!ATTLIST Struct bases CDATA #IMPLIED>
//<!ATTLIST Struct context IDREF #REQUIRED>
//<!ATTLIST Struct file CDATA #REQUIRED>
//<!ATTLIST Struct id ID #REQUIRED>
//<!ATTLIST Struct incomplete (0 | 1) "0">
//<!ATTLIST Struct line CDATA #REQUIRED>
//<!ATTLIST Struct location CDATA #REQUIRED>
//<!ATTLIST Struct mangled CDATA #REQUIRED>
//<!ATTLIST Struct members CDATA #IMPLIED>
//<!ATTLIST Struct name CDATA #IMPLIED>
//<!ATTLIST Struct size CDATA #IMPLIED>
const int KStructAttributeCount = 6;
const EntityAttributeElement KStructAttributes[KStructAttributeCount]={
                                                {KXMLAccessString,ESimpleAttribute},
                                                {KXMLAbstractString,EBooleanAttribute},
                                                {KXMLBasesString,EIdAttribute},
                                                {KXMLNameString,ESimpleAttribute},
                                                {KXMLSizeString,ESimpleAttribute},
                                                {KXMLMembersString,EIdAttribute}
                                                };

//<!ELEMENT Unimplemented EMPTY>
//<!ATTLIST Unimplemented function CDATA #IMPLIED>
//<!ATTLIST Unimplemented id ID #REQUIRED>
//<!ATTLIST Unimplemented node CDATA #REQUIRED>
//<!ATTLIST Unimplemented tree_code (187 | 190 | 193) #REQUIRED>
//<!ATTLIST Unimplemented tree_code_name (template_type_parm | 
//	typename_type | using_decl) #REQUIRED>
const int KUnimplementedAttributeCount = 0;
//const EntityAttributeElement KUnimplementedAttributes[KUnimplementedAttributeCount]={};

//<!ELEMENT Union (Base)*>
//<!ATTLIST Union abstract (0 | 1) "0">
//<!ATTLIST Union access (public | private | protected) "public">
//<!ATTLIST Union align CDATA #IMPLIED>
//<!ATTLIST Union artificial (0 | 1) "0">
//<!ATTLIST Union attributes CDATA #IMPLIED>
//<!ATTLIST Union bases CDATA #IMPLIED>
//<!ATTLIST Union context IDREF #REQUIRED>
//<!ATTLIST Union file CDATA #REQUIRED>
//<!ATTLIST Union id ID #REQUIRED>
//<!ATTLIST Union incomplete (0 | 1) "0">
//<!ATTLIST Union line CDATA #REQUIRED>
//<!ATTLIST Union location CDATA #REQUIRED>
//<!ATTLIST Union mangled CDATA #REQUIRED>
//<!ATTLIST Union members CDATA #IMPLIED>
//<!ATTLIST Union name CDATA #IMPLIED>
//<!ATTLIST Union size CDATA #IMPLIED>
const int KUnionAttributeCount = 5;
const EntityAttributeElement KUnionAttributes[KUnionAttributeCount]={
                                                {KXMLAccessString,ESimpleAttribute},
                                                {KXMLAlignString,ESimpleAttribute},
                                                {KXMLBasesString,EOptionalIdAttribute},
                                                {KXMLMembersString,EIdAttribute},
                                                {KXMLSizeString,ESimpleAttribute}
                                                };

const EntityComparisonElement KEntityComparisonTable[KEntityComparisonTableCount]=
    {
    {KXMLBaseString,KBaseAttributes,KBaseAttributeCount},
    {KXMLFundamentalTypeString,KFundamentalTypeAttributes,KFundamentalTypeAttributeCount},
    {KXMLTypedefString,KTypedefAttributes,KTypedefAttributeCount},
    {KXMLNamespaceString,KNamespaceAttributes,KNamespaceAttributeCount},
    {KXMLCvQualifiedTypeString,KCvQualifiedTypeAttributes,KCvQualifiedTypeAttributeCount},
    {KXMLVariableString,KVariableAttributes,KVariableAttributeCount},
    {KXMLFundamentalTypeString,KFundamentalTypeAttributes,KFundamentalTypeAttributeCount},
    {KXMLTypedefString,KTypedefAttributes,KTypedefAttributeCount},
    {KXMLNamespaceString,KNamespaceAttributes,KNamespaceAttributeCount},
    {KXMLFunctionString,KFunctionAttributes,KFunctionAttributeCount},
    {KXMLEnumerationString,KEnumerationAttributes,KEnumerationAttributeCount},
    {KXMLFieldString,KFieldAttributes,KFieldAttributeCount},
    {KXMLArgumentString,KArgumentAttributes,KArgumentAttributeCount},
    {KXMLEllipsisString,NULL,KEllipsisAttributeCount},
    {KXMLArrayTypeString,KArrayTypeAttributes,KArrayTypeAttributeCount},
    {KXMLClassString,KClassAttributes,KClassAttributeCount},
    {KXMLConstructorString,KConstructorAttributes,KConstructorAttributeCount},
    {KXMLConverterString,NULL,KConverterAttributeCount},
    {KXMLDestructorString,KDestructorAttributes,KDestructorAttributeCount},
    {KXMLEnumValueString,KEnumValueAttributes,KEnumValueAttributeCount},
    {KXMLFileString,NULL,KFileAttributeCount},
    {KXMLFunctionTypeString,KFunctionTypeAttributes,KFunctionTypeAttributeCount},
    {KXMLMethodString,KMethodAttributes,KMethodAttributeCount},
    {KXMLMethodTypeString,KMethodTypeAttributes,KMethodTypeAttributeCount},
    {KXMLNamespaceAliasString,NULL,KNamespaceAliasAttributeCount},
    {KXMLOffsetTypeString,NULL,KOffsetTypeAttributeCount},
    {KXMLOperatorFunctionString,KOperatorFunctionAttributes,KOperatorFunctionAttributeCount},
    {KXMLOperatorMethodString,KOperatorMethodAttributes,KOperatorMethodAttributeCount},
    {KXMLPointerTypeString,KPointerTypeAttributes,KPointerTypeAttributeCount},
    {KXMLReferenceTypeString,KReferenceTypeAttributes,KReferenceTypeAttributeCount},
    {KXMLStructString,KStructAttributes,KStructAttributeCount},
    {KXMLUnimplementedString,NULL,KUnimplementedAttributeCount},
    {KXMLUnionString,KUnionAttributes,KUnionAttributeCount}
    };



// ----------------------------------------------------------------------------
// IsProperNode
// ----------------------------------------------------------------------------
//
bool IsProperNode(HANodeIterator node)
{
    bool ret = (DOMNode::ELEMENT_NODE == node->getNodeType());

    if (ret)
    {
        const XMLCh * nodecontext = node.GetAttribute(KXMLContextString);
        if (nodecontext)
        {
            ret = !Equals(nodecontext,KXMLIgnoreContext);
        }
    }

    if (ret)
    {
        if ( node.CheckForBooleanAttribute(KXMLArtificialString) )
        {
        const XMLCh * nodetype = node->getNodeName();

        ret = Equals(nodetype,KXMLUnionString) || 
                 Equals(nodetype,KXMLStructString) ||
                 Equals(nodetype,KXMLEnumerationString) ||
                 Equals(nodetype,KXMLClassString);
        }
    }

    return ret;

}

// ----------------------------------------------------------------------------
// IsNamedNode
// ----------------------------------------------------------------------------
//
bool IsNamedNode(HANodeIterator node)
    {
    bool ret = (DOMNode::ELEMENT_NODE == node->getNodeType());

    if (ret)
    {

        const XMLCh* name = node.GetAttribute(KXMLNameString);

        if (!name)
        {
            return false;
        }

        const XMLCh * nodetype = node->getNodeName();
        assert(nodetype != NULL);

        if ( !(Equals(nodetype,KXMLClassString ) ||
            Equals(nodetype,KXMLEnumerationString ) ||
            Equals(nodetype,KXMLFunctionString ) ||
            Equals(nodetype,KXMLNamespaceString ) ||
            Equals(nodetype,KXMLOperatorFunctionString ) ||
            Equals(nodetype,KXMLStructString  ) ||
            Equals(nodetype,KXMLTypedefString  ) ||
            Equals(nodetype,KXMLUnionString  ) ||
            Equals(nodetype,KXMLVariableString )) )
        {
            ret = false;
        }
    
    }

    return ret;
}

// ----------------------------------------------------------------------------
// IsFunction
// ----------------------------------------------------------------------------
//
void printXMLCh(const XMLCh* s1)
{
    char * tmp = XMLString::transcode(s1);

    cout << tmp;

    XMLString::release(&tmp);
}

// ----------------------------------------------------------------------------
// toString
// ----------------------------------------------------------------------------
//
string toString(const XMLCh* s1)
{
    char* ts1 = XMLString::transcode(s1);
	string value;
	if(ts1 != NULL)
	{
    value = ts1;
    XMLString::release(&ts1);
	}
    return value;
}

// ----------------------------------------------------------------------------
// Equals
// ----------------------------------------------------------------------------
//
bool Equals(const XMLCh* s1, const XMLCh* s2)
{
    return XMLString::equals(s1,s2);
}


// ----------------------------------------------------------------------------
// Equals
// ----------------------------------------------------------------------------
//
bool Equals(const char* s1, const char* s2)
{
    return XMLString::equals(s1,s2);    
}

// ----------------------------------------------------------------------------
// Equals
// ----------------------------------------------------------------------------
//
bool Equals(const XMLCh* s1, const char* s2)
{
    XMLCh* ts2 = XMLString::transcode(s2);
    bool ret = XMLString::equals(s1,ts2);
    XMLString::release(&ts2);
    return ret;
}

// ----------------------------------------------------------------------------
// StartsWith
// ----------------------------------------------------------------------------
//
bool StartsWith(const XMLCh* s1, const char* s2)
{
    XMLCh* ts2 = XMLString::transcode(s2);
    bool ret = XMLString::startsWith(s1,ts2);
    XMLString::release(&ts2);
    return ret;
}

// ----------------------------------------------------------------------------
// StartsWith
// ----------------------------------------------------------------------------
//
bool StartsWith(const XMLCh* s1, const XMLCh* s2)
{
    bool ret = XMLString::startsWith(s1,s2);
    return ret;
}

// ----------------------------------------------------------------------------
// Equals
// ----------------------------------------------------------------------------
//
bool Equals(const char* s2, const XMLCh* s1)
{
    return Equals(s1,s2);
}


// ----------------------------------------------------------------------------
// SetAttribute
// ----------------------------------------------------------------------------
//
void SetAttribute(DOMNode * node, const XMLCh* attribute, const XMLCh* value)
{
    short nodetype = node->getNodeType();
    assert(nodetype == DOMNode::ELEMENT_NODE);

    DOMElement * element = static_cast<DOMElement*>(node);

    element->setAttribute(attribute,value);
}

// ----------------------------------------------------------------------------
// SetAttribute
// ----------------------------------------------------------------------------
//
void SetAttribute(DOMNode * node, const char* attribute, const char* value)
{
    XMLCh* tattribute = XMLString::transcode(attribute);
    XMLCh* tvalue = XMLString::transcode(value);
    SetAttribute(node,tattribute,tvalue);
    XMLString::release(&tattribute);
    XMLString::release(&tvalue);
}

// ----------------------------------------------------------------------------
// GetAttribute
// ----------------------------------------------------------------------------
//
const XMLCh* GetAttribute(DOMNode * node, const XMLCh* attribute)
{
    DOMNamedNodeMap * attributes = node->getAttributes();
    
    if ( !attributes )
    {
        return NULL;
    }
    
    DOMNode * attributeId = attributes->getNamedItem(attribute);
    
    if ( attributeId )
    {
        return attributeId->getNodeValue();
    }

    return NULL;
}

// ----------------------------------------------------------------------------
// GetAttribute
// ----------------------------------------------------------------------------
//
const XMLCh* GetAttribute(DOMNode * node, const char * attribute)
{
    XMLCh * idident = XMLString::transcode(attribute);
    const XMLCh * attributeValue = GetAttribute(node,idident);
    XMLString::release(&idident);

    return attributeValue;
    
}

// ----------------------------------------------------------------------------
// CheckForBooleanAttribute
// ----------------------------------------------------------------------------
//
bool CheckForBooleanAttribute(DOMNode * node, const XMLCh* attribute)
{
    const XMLCh* attributeValue = GetAttribute(node, attribute);
    
    if ( attributeValue )
    {
        return Equals(attributeValue,"1");
    }
    return false;
}

// ----------------------------------------------------------------------------
// CheckForBooleanAttribute
// ----------------------------------------------------------------------------
//
bool CheckForBooleanAttribute(DOMNode * node, const char* attribute)
{
    const XMLCh* attributeValue = GetAttribute(node, attribute);
    
    if ( attributeValue )
    {
        return Equals(attributeValue,"1");
    }
    return false;
}

// ----------------------------------------------------------------------------
// GetSize
// ----------------------------------------------------------------------------
//
const XMLCh* GetSize(HANodeIterator node)
{
	const XMLCh* size = node.GetAttribute(KXMLSizeString);
	
	if ( !size )
	{
		const XMLCh* type = node.GetAttribute(KXMLTypeString);

        assert(type);

        HANodeIterator typenode(node);

        bool typefound = typenode.FindNodeById(type);

        assert(typefound);

        return GetSize(typenode);		
	}

    return size;
}

// ----------------------------------------------------------------------------
// GetTypeName
// ----------------------------------------------------------------------------
//
string GetTypeName(HANodeIterator node)
{
    const XMLCh* fqname = node.GetAttribute(KXMLBBCFQNameString);
    
    if (fqname)
    {
        return toString(fqname);
    }

    string ret;

    const XMLCh * nodename = node->getNodeName();

    if ( Equals(nodename,KXMLEllipsisString) )
    {
    ret += " ";
    ret += "...";
    ret += ",";
    }
    else if ( Equals(nodename, KXMLFunctionTypeString) )
    {
        //ret += "(*)";
        const XMLCh* retType = node.GetAttribute(KXMLReturnsString);    
        if( retType )
        {
            HANodeIterator typenode(node);
            bool typefound = typenode.FindNodeById(retType);
            assert(typefound);
            ret += GetTypeName(typenode) + " ";	
        }
    
        ret += "(*) ";
        ret += GenerateFunctionSignature(node);
    }
    else if ( Equals(nodename, KXMLFundamentalTypeString) )
    {
        ret += GenerateFullyQualifiedName(node);
    }
    else if ( Equals(nodename, KXMLTypedefString) )
    {
        ret += GenerateFullyQualifiedName(node);
    }
    else if ( Equals(nodename,KXMLCvQualifiedTypeString) )
    {

        const XMLCh* type = node.GetAttribute(KXMLTypeString);

        assert(type);

        HANodeIterator typenode(node);

        bool typefound = typenode.FindNodeById(type);

        assert(typefound);

         if ( node.CheckForBooleanAttribute(KXMLConstString) )
        {
        ret += " const ";
        }
        ret += GetTypeName(typenode);		
    }
    else if ( Equals(nodename,KXMLArrayTypeString) )
    {
        const XMLCh* type = node.GetAttribute(KXMLTypeString);

        assert(type);

        HANodeIterator typenode(node);

        bool typefound = typenode.FindNodeById(type);

        assert(typefound);
        ret += GetTypeName(typenode);		
        ret += "[]";
    }
    else if ( Equals(nodename,KXMLPointerTypeString) )
    {
        const XMLCh* type = node.GetAttribute(KXMLTypeString);

        assert(type);

        HANodeIterator typenode(node);

        bool typefound = typenode.FindNodeById(type);

        assert(typefound);
        ret += GetTypeName(typenode);
        if(!Equals(typenode->getNodeName(), KXMLFunctionTypeString) )
        {
            ret += "*";
        }
    }
    else if ( Equals(nodename,KXMLReferenceTypeString) )
    {
        const XMLCh* type = node.GetAttribute(KXMLTypeString);

        assert(type);

        HANodeIterator typenode(node);

        bool typefound = typenode.FindNodeById(type);

        assert(typefound);
        ret += GetTypeName(typenode);		
        ret += "&";
    }	
    else
    {
        const XMLCh* type = node.GetAttribute(KXMLTypeString);

        //assert(type);
        if ( type )
        {
            HANodeIterator typenode(node);

            bool typefound = typenode.FindNodeById(type);

            assert(typefound);
            ret += GetTypeName(typenode);
        }else
        {
        ret += GenerateFullyQualifiedName(node);
        }
    }

    XMLCh* fqnamep = XMLString::transcode(ret.c_str());
    node.SetAttribute(KXMLBBCFQNameString, fqnamep);
    XMLString::release(&fqnamep);
    
    return ret;	
}

const XMLCh* FindAttributeValueForType(const HANodeIterator& node, const char* attribute)
{
    XMLCh* ch_attribute = XMLString::transcode(attribute);
	const XMLCh* ret = FindAttributeValueForType(node,ch_attribute);
	XMLString::release(&ch_attribute);
	return ret;

}

// ----------------------------------------------------------------------------
// FindAttributeValueForType
// ----------------------------------------------------------------------------
// 
const XMLCh* FindAttributeValueForType(const HANodeIterator& node, const XMLCh* attribute)
{
    const XMLCh* size = node.GetAttribute(attribute);
    
    if (size)
    {
        return size;
    }

	const XMLCh* type = node.GetAttribute(KXMLTypeString);

    if ( !type )
	{
		return NULL;
	}

	HANodeIterator typenode(node);

    bool typefound = typenode.FindNodeById(type);

    assert(typefound);

	return FindAttributeValueForType(typenode,attribute);
}

// ----------------------------------------------------------------------------
// IsFunction
// ----------------------------------------------------------------------------
//
bool IsFunction(HANodeIterator node) 
    {
        //Add the return value and parameters to the name (due to overloading)
        const XMLCh* name = node.current->getNodeName();

        if (!name)
        {
            return false;
        }

        if ( Equals(name,KXMLConstructorString) ||
            Equals(name,KXMLMethodString) ||
            Equals(name,KXMLFunctionString) ||
            Equals(name,KXMLOperatorFunctionString) ||
            Equals(name,KXMLOperatorMethodString) ||
            Equals(name,KXMLDestructorString) ||
            Equals(name,KXMLFunctionTypeString)
            )
        {
            return true;
        }

        return false;
    }

void GetElementNodes(   HANodeIterator node, 
                        DOMNodeList* domNodes, 
                        std::vector<DOMNode*>& elemNodes)
{
    XMLSize_t domNodeCount = domNodes->getLength();         
    for(unsigned int i = 0; i < domNodeCount; ++i)
    {
        DOMNode* domNode = domNodes->item(i);
        HANodeIterator nodeit(node);
        nodeit.current = domNode;
        
        short nodetype = nodeit->getNodeType();
        if (nodetype == DOMNode::ELEMENT_NODE)
        {
            elemNodes.push_back(domNodes->item(i));
        }
    }
}

// ----------------------------------------------------------------------------
// GenerateFunctionSignature
// Builds function signature which contains function name and all the parameters. 
// ----------------------------------------------------------------------------
//
string GenerateFunctionSignature(HANodeIterator node)
{
    short nodetype = node->getNodeType();
    assert(nodetype == DOMNode::ELEMENT_NODE);
    assert(IsFunction(node));

    string ret;

	const XMLCh * name = node->getNodeName();

    if ( Equals(name, KXMLDestructorString) )
    {
        ret += "~";
    }
    else if ( Equals(name,KXMLOperatorMethodString) || Equals(name,KXMLOperatorFunctionString) )
	{
        ret += "operator";
	}

    const XMLCh* nameatt = node.GetAttribute(KXMLNameString);
    
	if (nameatt)
	{
		ret += toString(nameatt);
	}

    ret +="(";

    DOMElement * nodeelement = static_cast<DOMElement*>(node.current);
    DOMNodeList* childs = nodeelement->getChildNodes();
    XMLSize_t childcount = childs->getLength();

    unsigned int i = 0;
    for (i = 0; i < childcount; ++i)
    {
        DOMNode* child = childs->item(i);
        HANodeIterator childit(node);
        childit.current = child;
        
        short nodetype = childit->getNodeType();
        if (nodetype == DOMNode::ELEMENT_NODE)
        {
            ret += " " + GetTypeName(childit) + ",";
        }

    }
     
    if (ret[ret.length()-1] == ',')
    {
        ret.resize(ret.length()-1);
    }
    ret += " )";

    if ( node.CheckForBooleanAttribute(KXMLConstString) )
    {
        ret += " const";
    }	

    return ret;
}

// ----------------------------------------------------------------------------
// GenerateFullyQualifiedName
// ----------------------------------------------------------------------------
//
string GenerateFullyQualifiedName(HANodeIterator node)
{
    const XMLCh* fqname = node.GetAttribute(KXMLBBCFQNameString);
    
    if (fqname)
    {
        return toString(fqname);
    }

    string name;

    const XMLCh* nameatt = 0;
	const XMLCh* mangledatt = 0;

    if( IsAnonymousType(node) )
    {
        // Node is of "anonymous" type so it has not name. 
        // Let's use the gccxml generated id instead.
        nameatt = node.GetAttribute(KXMLIdString);
    }
    else
    {
        nameatt = node.GetAttribute(KXMLNameString);
    }

    if ( nameatt )
    {
        if ( Equals(KXMLNamespaceString,node->getNodeName()) )
        {
            if ( StartsWith(nameatt,KXMLAnonymousNamespacePrefix) )
            {
                name += "<unnamed>";
            }
            else if ( Equals(KXMLGlobalNamespaceString,nameatt) )
            { 
                //Skip the global namespace

            }else
            {
                name += toString(nameatt);
            }

        }
        else if ( IsFunction(node) )
		{
			//Add the return value and parameters to the name (due to overloading)
			// Consider mangled attribute here.
			mangledatt = node.GetAttribute(KXMLMangledString);
			string mangled = toString(mangledatt);
			name += GenerateFunctionSignature(node) + __FUN_MANGLED__ + toString(mangledatt);

        }
        else
        {
            name += toString(nameatt);
        }
    }

    const XMLCh* contextatt = node.GetAttribute(KXMLContextString);

    if ( contextatt )
    {
        HANodeIterator basenode(node);
        basenode.FindNodeById(contextatt);
        string basename = GenerateFullyQualifiedName(basenode);
        name = basename + "::" + name;
    }


    if ( nameatt || contextatt)
    {
        XMLCh* fqnamep = XMLString::transcode(name.c_str());
        node.SetAttribute(KXMLBBCFQNameString, fqnamep);
        XMLString::release(&fqnamep);
    }

    return name;
}

// ----------------------------------------------------------------------------
// FindComparison
// ----------------------------------------------------------------------------
//
const EntityComparisonElement* FindComparison(const XMLCh* nodeName)
{
    int i = 0;
    for (i = 0;i < KEntityComparisonTableCount; ++i)
    {
        if ( Equals(KEntityComparisonTable[i].iEntityName,nodeName) )
        {
            return &KEntityComparisonTable[i];
        }
    }
    return NULL;

}

// ----------------------------------------------------------------------------
// CompareIdLists
// ----------------------------------------------------------------------------
//
bool CompareIdLists(HANodeIterator baseline, HANodeIterator current,const XMLCh* idAttributeName)
{
    HANodeIterator newbaseline = baseline;
    const XMLCh* baselineids = baseline.GetAttribute(idAttributeName);
    
    HANodeIterator newcurrent = current;
    const XMLCh* currentids = current.GetAttribute(idAttributeName);

    BaseRefVectorOf< XMLCh > * baselineidtokens_ptr = XMLString::tokenizeString (baselineids);
    BaseRefVectorOf< XMLCh > * currentidtokens_ptr = XMLString::tokenizeString (currentids);

	auto_ptr<BaseRefVectorOf< XMLCh > > baselineidtokens(baselineidtokens_ptr);
	auto_ptr<BaseRefVectorOf< XMLCh > > currentidtokens(currentidtokens_ptr);
    
    for (unsigned int i = 0; i < baselineidtokens->size(); ++i)
    {
        const XMLCh * baselineid = baselineidtokens->elementAt(i);
        const XMLCh * currentid = currentidtokens->elementAt(i);
        newbaseline.FindNodeById(baselineid);
        newcurrent.FindNodeById(currentid);

        if ( !CompareNodes(newbaseline,newcurrent) )
        {
            
            return false;
        }
    }


    return true;
}

// ----------------------------------------------------------------------------
// CompareNodes
// ----------------------------------------------------------------------------
//
bool CompareNodes(HANodeIterator baseline, HANodeIterator current )
{
    assert(Equals(baseline->getNodeName(),current->getNodeName()));

    const EntityComparisonElement* compElem = FindComparison(baseline->getNodeName());

    assert(compElem);

    int i = 0;
    for (i = 0;i < compElem->iAttributeCount; ++i)
    {
        const EntityAttributeElement* attributes = &compElem->iAttributeList[i];

        if ( !CompareAttributes(baseline, current, attributes->iAttributeName, attributes->iAttributeType) )
        {
            return false;
        }
    }
    return true;
}

// ----------------------------------------------------------------------------
// CompareFileNames
// ----------------------------------------------------------------------------
//
bool CompareFileNames(string first,string second)
{
    if (first.length() != second.length() )
    {
        return false;
    }

    unsigned int i = 0;
    for (i = 0; i < first.length(); ++i)
    {
        if (first.at(i) == '\\' || first.at(i) == '/' )
        {
            if (second.at(i) != '\\' && second.at(i) != '/' )
            {
                return false;
            }
        } else
        {
            if ( tolower(first.at(i)) != tolower(second.at(i)) )
            {
                return false;
            }
        }

    }
    return true;
}

// ----------------------------------------------------------------------------
// CompareAttributes
// ----------------------------------------------------------------------------
//
bool CompareAttributes(HANodeIterator baseline, HANodeIterator current, const char* attributeName, TAttributeType attributeType)
{
    XMLCh* attributeName2 = XMLString::transcode(attributeName);
    bool ret = CompareAttributes(baseline,current,attributeName2,attributeType);
    XMLString::release(&attributeName2);
    return ret;

}

// ----------------------------------------------------------------------------
// CompareAttributes
// ----------------------------------------------------------------------------
//
bool CompareAttributes(HANodeIterator baseline, HANodeIterator current, const XMLCh* attributeName, TAttributeType attributeType)
{
    switch (attributeType)
    {
        case EOptionalTypeAttribute:
            {
            if ( NULL == baseline.GetAttribute(attributeName) ||
                NULL == current.GetAttribute(attributeName) )
                {
                    if ( baseline.GetAttribute(attributeName) ||
                         current.GetAttribute(attributeName) )
                    {
                        return false;
                    }
                    else
                    {
                        return true;
                    }
                    break;
                }
            }
        case ETypeAttribute:
            {
            const XMLCh * baselineid = baseline.GetAttribute(attributeName);
            const XMLCh * currentid = current.GetAttribute(attributeName);
            assert(baselineid);
            assert(baselineid);
            HANodeIterator newbaseline(baseline);
            HANodeIterator newcurrent(current);
            bool ret1=newbaseline.FindNodeById(baselineid);
            bool ret2=newcurrent.FindNodeById(currentid);
            assert(ret1 && ret2);
            string baselinetype = GetTypeName(newbaseline);
            string currenttype = GetTypeName(newcurrent);

            // Test if either of the types is incomplete.
            // If either one is incomplete, the size and alignment
            // does not match. We don't check the size and alignment
            // for incomplete types, since the actual types are 
            // checked with their headers.
            bool bincomplete = newbaseline.CheckForBooleanAttribute(KXMIncompleteString);
            bool cincomplete = newcurrent.CheckForBooleanAttribute(KXMIncompleteString);
	
            if( !bincomplete && !cincomplete )
                {
			    const XMLCh * baselinesize = FindAttributeValueForType(newbaseline,KXMLSizeString);
			    const XMLCh * currentsize = FindAttributeValueForType(newcurrent,KXMLSizeString);

			    const XMLCh * baselinealign = FindAttributeValueForType(newbaseline,KXMLAlignString);
			    const XMLCh * currentalign = FindAttributeValueForType(newcurrent,KXMLAlignString);

			    if ( !baselinesize )
			        {
				    baselinesize = baselinealign;
			        }
				
			    if ( !currentsize )
			        {
				    currentsize = currentalign;
			        }

			    return baselinetype == currenttype && Equals(baselinesize,currentsize) && Equals(baselinealign, currentalign);
                }
            else
                {
                // either or both of the types were incomplete, so compare just the type names.
                return baselinetype == currenttype;
                }
            }
        
        case EOptionalSimpleAttribute:
            {
            if ( NULL == baseline.GetAttribute(attributeName) ||
                NULL == current.GetAttribute(attributeName) )
                {
                    if ( baseline.GetAttribute(attributeName) ||
                         current.GetAttribute(attributeName) )
                    {
                        return false;
                    }
                    else
                    {
                        return true;
                    }
                    break;
                }
            }
        case ESimpleAttribute:
        case EBooleanAttribute:
        {
            if (!Equals(
                        baseline.GetAttribute(attributeName),
                        current.GetAttribute(attributeName)
                        )
                )
            {
                return false;
            }
            break;
        }

        case EOptionalIdAttribute:
        {
            if ( NULL == baseline.GetAttribute(attributeName) || 
                NULL == current.GetAttribute(attributeName))
            {
                if ( baseline.GetAttribute(attributeName) || 
                    current.GetAttribute(attributeName) )
                {
                    return false;
                }
                else
                {
                    return true;
                }
                break;
            }
        }
        case EIdAttribute:
        {
            if (!CompareIdLists(baseline, current, attributeName))
            {
                return false;
            }
            break;
        }

        default:
        {
            //Attribute type unknown
        assert(false);
        }
    }
    return true;
}

// ----------------------------------------------------------------------------
// CalcDerivedAccessModifier
// ----------------------------------------------------------------------------
//
#if 0
TAccess CalcDerivedAccessModifier(TAccess member, TAccess inheritance)
{
	TAccess ret=EAccessGlobal;
	switch (inheritance)
	{
	case EAccessGlobal: 
	case EAccessPublic:
		switch(member)
		{
		case EAccessGlobal:
			ret = member;
			break;
		case EAccessPublic:
			ret = member;
			break;
		case EAccessProtected:
			ret = member;
			break;
		case EAccessPrivate:
			ret = EAccessHidden;
			break;
        case EAccessHidden:
            ret = member;
            break;
		default:
			assert(false);
			break;
		}
		break;
	case EAccessProtected:
		switch(member)
		{
		case EAccessGlobal:
			ret = member;
			break;
		case EAccessPublic:
			ret = EAccessProtected;
			break;
		case EAccessProtected:
			ret = EAccessProtected;
			break;
		case EAccessPrivate:
			ret = EAccessHidden;
			break;
        case EAccessHidden:
            ret = member;
            break;
		default:
			assert(false);
			break;
		}
		break;
	case EAccessPrivate:
		switch(member)
		{
		case EAccessGlobal:
			ret = member;
			break;
		case EAccessPublic:
			ret = EAccessHidden;
			break;
		case EAccessProtected:
			ret = EAccessHidden;
			break;
		case EAccessPrivate:
			ret = EAccessHidden;
			break;
        case EAccessHidden:
            ret = EAccessHidden;
            break;
		default:
			assert(false);
			break;
		}
		break;
	default:
		assert(false);
		break;
	}
	return ret;
}
#endif

// ----------------------------------------------------------------------------
// CalcAccessModifier
// ----------------------------------------------------------------------------
//
TAccess CalcAccessModifier(HANodeIterator node)
{
    const XMLCh * ac = node.GetAttribute(KXMLAccessString);

    TAccess ret = EAccessGlobal;

    if ( !ac )
    {
        ret = EAccessGlobal;
    } 
    else if ( Equals(ac,KXMLPublicString) )
    {
        ret = EAccessPublic;
    } 
    else if ( Equals(ac,KXMLProtectedString) )
    {
        ret = EAccessProtected;
    } 
    else if ( Equals(ac,KXMLPrivateString) )
    {
        ret = EAccessPrivate;
    }
    else
    {
        assert(false);
    }

    return ret;

}

// ----------------------------------------------------------------------------
// CheckAccessModifier
// ----------------------------------------------------------------------------
//
bool CheckAccessModifier(HANodeIterator baseline,HANodeIterator current)
{
    TAccess baselineaccess = CalcAccessModifier(baseline);
    TAccess currentaccess = CalcAccessModifier(current);
	return CheckAccessModifier(baselineaccess,currentaccess);
}

// ----------------------------------------------------------------------------
// CheckAccessModifier
// ----------------------------------------------------------------------------
//
bool CheckAccessModifier(TAccess baselineaccess,TAccess currentaccess)
{
    return (currentaccess <= baselineaccess);
}

// ----------------------------------------------------------------------------
// CompareNames
// ----------------------------------------------------------------------------
//
bool CompareNames(HANodeIterator baseline, HANodeIterator current)
{
    const XMLCh * basename = baseline.GetAttribute(KXMLNameString);
    const XMLCh * currentname = current.GetAttribute(KXMLNameString);

    if ( basename == NULL || currentname == NULL )
    {
        return false;
    }

    return Equals(basename,currentname);
}

// ----------------------------------------------------------------------------
// ClassIsDerivable
// ----------------------------------------------------------------------------
//
bool ClassIsDerivable(HANodeIterator node)
{
    return ( 
            (
             node.CheckForBooleanAttribute(KXMLBBCPublicConstructorString) ||
             node.CheckForBooleanAttribute(KXMLBBCProtectedConstructorString)
            )&&
            (
             Equals(node.GetAttribute(KXMLBBCDestructorAccessString),KXMLBBCAccessPublicString) ||
             Equals(node.GetAttribute(KXMLBBCDestructorAccessString),KXMLBBCAccessProtectedString)
            )
           );

}

// ----------------------------------------------------------------------------
// ClassIsInstantiable
// ----------------------------------------------------------------------------
//
bool ClassIsInstantiable(HANodeIterator node)
{
    return 	node.CheckForBooleanAttribute(KXMLBBCPublicConstructorString) &&
    Equals(node.GetAttribute(KXMLBBCDestructorAccessString),KXMLBBCAccessPublicString);
}


// ----------------------------------------------------------------------------
// FindParentContext
// ----------------------------------------------------------------------------
//
bool FindParentContext(HANodeIterator memberNode, HANodeIterator& parentNode)
{
    if ( Equals(memberNode->getNodeName(),KXMLEnumValueString) )
    {
        parentNode.current = memberNode->getParentNode();
		return true;
    }

    const XMLCh* contextid = memberNode.GetAttribute(KXMLContextString);

    if (contextid)
    {		
        bool ret = parentNode.FindNodeById(contextid);
        return ret;
    }
    
    return false;
}

// ----------------------------------------------------------------------------
// CheckAccessibility
// ----------------------------------------------------------------------------
//
bool CheckAccessibility(HANodeIterator memberNode)
{
    bool dummy=false;
    return CheckAccessibility(memberNode, dummy);
}

// ----------------------------------------------------------------------------
// CheckAccessibility
// ----------------------------------------------------------------------------
//
bool CheckAccessibility(HANodeIterator memberNode, bool & exposedByInline)
{
    TAccess access = CalcAccessModifier(memberNode);
    
    HANodeIterator parentNode(memberNode);
    if ( !FindParentContext(memberNode, parentNode) )
    {
        // Not a member of a class, so this is accessible
        return true;
    }
        
	return CheckAccessibility(parentNode, exposedByInline, access);
}

// ----------------------------------------------------------------------------
// CheckAccessibility
// ----------------------------------------------------------------------------
//
bool CheckAccessibility(HANodeIterator parentNode, bool & exposedByInline, TAccess access)
{
    if ( !CheckAccessibility(parentNode,exposedByInline) )
    {
        return false;
    }

    if ( EAccessPublic >= access )
    {
        return true;
    }

	if ( EAccessHidden == access )
    {
        return false;
    }

	if ( ClassIsDerivable(parentNode) )
    {
        if ( EAccessProtected == access )
        {
            // Protected methods are accessible by derived classes
            return true; 
        }

        if ( 
                EAccessPrivate == access &&
                parentNode.CheckForBooleanAttribute(KXMLBBCProtectedInlineString)
            )
        {
            // Although this method is private, it might be possible that it
            // is accessed by protected inline function. Because this is derivable
            // class this private method might be exposed by the protected inline
            // function.
            exposedByInline = true;
            return true;
        }
    }

	if ( parentNode.CheckForBooleanAttribute(KXMLBBCPublicInlineString) )
    {
        // Class has public inline function(s) and it is possible that they
        // are exposing some private stuff.
        exposedByInline = true;
        return true;
    }

    return false;
}

// ----------------------------------------------------------------------------
// IsAnonymous
// ----------------------------------------------------------------------------
//
bool IsAnonymous(HANodeIterator node)
{
    const XMLCh* nodename = node.GetAttribute(KXMLNameString);

    //If the name starts with the character KAnonymousName 
    // this is anonymous
    if (nodename)
    {
        return StartsWith(nodename,KAnonymousName);
    }else
    {
        return true;
    }
}

// ----------------------------------------------------------------------------
// IsAnonymousType
// ----------------------------------------------------------------------------
//
bool IsAnonymousType(HANodeIterator node)
{
    const XMLCh* nodetypeid = node.GetAttribute(KXMLTypeString);

    if (nodetypeid)
    {
        //The node has type attribute so check the parent type for 
        // anonymity
        HANodeIterator typenode(node);
        bool ret = typenode.FindNodeById(nodetypeid);
        assert(ret);
        
        return IsAnonymousType(typenode);
    }
    
    const XMLCh* nodename = node.GetAttribute(KXMLNameString);
    const XMLCh* nodetypename = node->getNodeName();

    if ( nodename )
    {
        if ( Equals(KXMLEnumerationString, nodetypename) && IsAnonymous(node) )
        {
            //This is anonymous enumeration
            return true;
        }
        //The node does have name so this is not anonymous
        return false;	
    }

    
    if ( !Equals(KXMLUnionString, nodetypename) &&
        !Equals(KXMLStructString, nodetypename) &&
        !Equals(KXMLEnumerationString, nodetypename) )
    {
        return false;
    }

    //If there is no type and no name attributes the type is anonymous
    return true;
}

// ----------------------------------------------------------------------------
// FindAnonymousType
// ----------------------------------------------------------------------------
//
bool FindAnonymousType(HANodeIterator node, HANodeIterator& anonymousnode)
{
    const XMLCh* nodetypeid = node.GetAttribute(KXMLTypeString);

    if (nodetypeid)
    {
        //The node has type attribute so check the parent type for 
        // anonymity
        HANodeIterator typenode(node);
        bool ret = typenode.FindNodeById(nodetypeid);
        assert(ret);
        
        return FindAnonymousType(typenode,anonymousnode);
    }
    
    const XMLCh* nodename = node.GetAttribute(KXMLNameString);
    const XMLCh* nodetypename = node->getNodeName();

    if ( nodename && !(Equals(KXMLEnumerationString, nodetypename) && IsAnonymous(node)) )
    {
        //The node does have name so this is not anonymous
        return false;
    }

    //If there is no type and no name attributes the type is anonymous
    anonymousnode.current = node.current;
    return true;
}

// ----------------------------------------------------------------------------
// ClassPrimaryBase
// ----------------------------------------------------------------------------
//
bool ClassPrimaryBase(const HANodeIterator& classnode,HANodeIterator& primarybase )
{
    //Iterate through the base classes
    DOMNodeList* childs = classnode.GetElementsByTagName(KXMLBaseString);
   
	if (childs)
	{
		XMLSize_t childcount = childs->getLength();

		for (unsigned int i = 0; i < childcount; ++i)
		{
			HANodeIterator classit(classnode);
			classit.current = childs->item(i);

			//If the subclass' offset is zero, it is the primary base
			if ( Equals( KXML0String, classit.GetAttribute(KXMLOffsetString)) )
			{
				bool found = primarybase.FindNodeById(classit.GetAttribute(KXMLTypeString));
				assert(found);
				
				if ( primarybase.CheckForBooleanAttribute(KXMLBBCVirtualString) )
				{
					return true;
				} else
				{
					return false;
				}
			}
		}
	}
	return false;
}

// ----------------------------------------------------------------------------
// ClassOrderMembers
// ----------------------------------------------------------------------------
//
void ClassOrderMembers(HANodeIterator node,
                                    vector<DOMNode*>& virtualMethods,
                                    vector<DOMNode*>& inlineMethods,
                                    vector<DOMNode*>& exportedMethods,
                                    vector<DOMNode*>& methods,
                                    vector<DOMNode*>& fields,
                                    vector<DOMNode*>& others)
{
    const XMLCh* attributeValue = node.GetAttribute(KXMLMembersString);
    if (attributeValue)
    {
        BaseRefVectorOf< XMLCh > * memberids_ptr = XMLString::tokenizeString(attributeValue);
		auto_ptr<BaseRefVectorOf< XMLCh > > memberids(memberids_ptr);

        for (unsigned int i = 0; i < memberids->size(); ++i)
        {
            const XMLCh * memberid = memberids->elementAt(i);
            
            HANodeIterator member(node);

            if ( member.FindNodeById(memberid) )
            {	

                if ( !IsProperNode(member) )
                {
                    continue;
                }
                //Put it in the right vector
                const XMLCh* membernodename = member->getNodeName();
                assert(membernodename != NULL);
                if ( IsFunction(member) )
                {
                    //Check for export
                    const XMLCh* attributeValue = member.GetAttribute(KXMLAttributeString);                            
					bool normalMethod = true;

                    //Check for virtuality 
                    if ( member.CheckForBooleanAttribute(KXMLVirtualString) ||
                         member.CheckForBooleanAttribute(KXMLPureVirtualString) )
                    {
                        //printMember(member);
                        //DEBUG_PRINT(" is virtual member\n");
                        //Method is virtual
                        virtualMethods.push_back(member.current);
						normalMethod = false;
                    }
                    //Check for export
                    if ( attributeValue && Equals(attributeValue,KXMLExportedString)
                            )
                    {
                        //printMember(member);
                        //DEBUG_PRINT(" is exported or inline method\n");
                        //Method is exported
                        exportedMethods.push_back(member.current);
						normalMethod = false;
                    }
                    //Check for inline
                    if ( member.CheckForBooleanAttribute(KXMLInlineString)
                            )
                    {
                        //printMember(member);
                        //DEBUG_PRINT(" is exported or inline method\n");
                        //Method is exported
                        inlineMethods.push_back(member.current);
						normalMethod = false;
                    }

                    //Normal method
                    if ( normalMethod )
					{
                        //printMember(member);
                        //DEBUG_PRINT(" is normal method\n");
                        methods.push_back(member.current);
                    }
                    
                } else if ( Equals(membernodename,KXMLFieldString) )
                {
                    //printMember(member);
                    //DEBUG_PRINT(" is field\n");
                    fields.push_back(member.current);

                } else
                {
                    //printMember(member);
                    //DEBUG_PRINT(" is other member\n");
                    others.push_back(member.current);
                }

                
            }
            else
            {
                //The tree is broken
                assert(false);
            }
        }

    }    
}

// ----------------------------------------------------------------------------
// ClassOrderMembers
// ----------------------------------------------------------------------------
//
void ClassOrderMembers(HANodeIterator node,
                                    vector<DOMNode*>& virtualMethods,
                                    vector<DOMNode*>& inlineMethods,
                                    vector<DOMNode*>& exportedMethods,
                                    vector<DOMNode*>& exportedVirtualMethods,
                                    vector<DOMNode*>& methods,
                                    vector<DOMNode*>& fields,
                                    vector<DOMNode*>& others)
{
    const XMLCh* attributeValue = node.GetAttribute(KXMLMembersString);
    
    if (attributeValue)
    {
        BaseRefVectorOf< XMLCh > * memberids_ptr = XMLString::tokenizeString(attributeValue);
		auto_ptr<BaseRefVectorOf< XMLCh > > memberids(memberids_ptr);

        for (unsigned int i = 0; i < memberids->size(); ++i)
        {
            const XMLCh * memberid = memberids->elementAt(i);
            
            HANodeIterator member(node);

            if ( member.FindNodeById(memberid) )
            {	

                if ( !IsProperNode(member) )
                {
                    continue;
                }
                //Put it in the right vector
                const XMLCh* membernodename = member->getNodeName();
                assert(membernodename != NULL);
                if ( IsFunction(member) )
                {
                    //Check for export
                    const XMLCh* attributeValue = member.GetAttribute(KXMLAttributeString);                            
					bool normalMethod = true;
                    bool virtualMethod = false;
                    bool exportedMethod = false;

                    //Check for virtuality 
                    if ( member.CheckForBooleanAttribute(KXMLVirtualString) ||
                         member.CheckForBooleanAttribute(KXMLPureVirtualString) )
                    {
                        //printMember(member);
                        //DEBUG_PRINT(" is virtual member\n");
                        //Method is virtual
                        virtualMethods.push_back(member.current);
						normalMethod = false;
                        virtualMethod = true;
                    }
                    //Check for export
                    if ( attributeValue && Equals(attributeValue,KXMLExportedString) )
                    {
                        //printMember(member);
                        //DEBUG_PRINT(" is exported or inline method\n");
                        //Method is exported
                        exportedMethods.push_back(member.current);
						normalMethod = false;
                        exportedMethod = true;
                    }
                    /*if (virtualMethod && exportedMethod)
                    {
                        virtualMethods.pop_back();
                        exportedMethods.pop_back();
                        exportedVirtualMethods.push_back(member.current);
                    }*/
                    //Check for inline
                    if ( member.CheckForBooleanAttribute(KXMLInlineString) )
                    {
                        //printMember(member);
                        //DEBUG_PRINT(" is exported or inline method\n");
                        //Method is exported
                        inlineMethods.push_back(member.current);
						normalMethod = false;
                    }

                    //Normal method
                    if ( normalMethod )
					{
                        //printMember(member);
                        //DEBUG_PRINT(" is normal method\n");
                        methods.push_back(member.current);
                    }
                    
                } else if ( Equals(membernodename,KXMLFieldString) )
                {
                    //printMember(member);
                    //DEBUG_PRINT(" is field\n");
                    fields.push_back(member.current);

                } else
                {
                    //printMember(member);
                    //DEBUG_PRINT(" is other member\n");
                    others.push_back(member.current);
                }

                
            }
            else
            {
                //The tree is broken
                assert(false);
            }
        }
        
    }    
}

// ----------------------------------------------------------------------------
// ClassGenerateVirtualTable
// ----------------------------------------------------------------------------
//
const NodeIndex::vtable_t& ClassGenerateVirtualTable(HANodeIterator& classnode)
{	
	string vtablename = GenerateFullyQualifiedName(classnode);
	
	//Notice that this does not clear vtable, if one already exists
	const NodeIndex::vtable_t* vtable = classnode.iNodeIndex.AddEmptyVirtualTable(vtablename);

	if ( 0 != vtable->size() )
	{
		//The vtable already exists
		return *vtable;
	}
	else
	{
		vector<DOMNode*> virtualMethods;
		vector<DOMNode*> inlineMethods;
		vector<DOMNode*> exportedMethods;
		vector<DOMNode*> methods;
		vector<DOMNode*> fields;
		vector<DOMNode*> others;

		ClassOrderMembers(classnode, virtualMethods, inlineMethods, exportedMethods,
						methods, fields, others);

		HANodeIterator primarybase(classnode);
		//Lets check if we have primary base
		if ( ClassPrimaryBase( classnode,primarybase ) )
		{
			//First copy the virtual table of primary base
			const NodeIndex::vtable_t& primvtable = ClassGenerateVirtualTable(primarybase);
			if (primvtable.size())
			{
				NodeIndex::vtable_t::const_iterator it = primvtable.begin();
				for (; it != primvtable.end(); ++it)
				{
					classnode.iNodeIndex.AddVirtualFunction(vtablename,it->first,it->second);
				}

				//Then add the new virtual functions and overwritings of the other bases.
				unsigned int i = 0;
				for ( i = 0; i < virtualMethods.size(); ++i)
				{
					HANodeIterator functionnode(classnode);
					functionnode.current = virtualMethods[i];

					//We assume that the primary base includes virtual destructor so we can skip it
					// here (it overwrites the place from primary base)
					const XMLCh* nodetype = functionnode->getNodeName();
		            if ( Equals(nodetype,KXMLDestructorString) )
					{
						continue;
					}

					string funcsig = GenerateFunctionSignature(functionnode);

					//Check the primary base for overwriting
					NodeIndex::vtable_t::const_iterator it = primvtable.begin();
					for (; it != primvtable.end(); ++it)
					{
						if ( funcsig == it->first )
						{
							//This function overwrites one from the primary base and is not added
							//to the end of the vtable
							break;
						}
					}
					if ( it == primvtable.end() )
					{
						//Function was not found from the primary base vtable and is added
						//to the end of the table
						classnode.iNodeIndex.AddVirtualFunction(vtablename,funcsig,functionnode.current);
					}
				}
			}
		}else
		{
			//We do not have primary base and we can construct the virtual table from clean start
			unsigned int i = 0;
			for ( i = 0; i < virtualMethods.size(); ++i)
			{
				HANodeIterator functionnode(classnode);
				functionnode.current = virtualMethods[i];
				string funcsig = GenerateFunctionSignature(functionnode);
				classnode.iNodeIndex.AddVirtualFunction(vtablename,funcsig,functionnode.current);
			}
		}
		return *vtable;
	}

}

// ----------------------------------------------------------------------------
// ClassBaseSize
// ----------------------------------------------------------------------------
//
int ClassBaseSize(const HANodeIterator& classnode, const NodeIndex::dtable_t& fields)
{
	//This is empty class
	if ( 0 == fields.size() )
	{
		return 8;
	}

	DataMember lastmember = fields[fields.size()-1];

	//The last member is virtual table pointer
	if ( NULL == lastmember.iNode )
	{
		return lastmember.iOffset + 32;
	}

	HANodeIterator lastfield(classnode);
	lastfield.current = lastmember.iNode;

	const XMLCh* type = lastfield.GetAttribute(KXMLTypeString);
    assert(type);
    HANodeIterator typenode(classnode);
    bool typefound = typenode.FindNodeById(type);
    assert(typefound);
	const XMLCh * nodetype = typenode->getNodeName();
	assert(nodetype);

	int fieldsize_int = 0;
	//If the last member is class, get the base size for it
    if ( Equals(nodetype,KXMLStructString) || Equals(nodetype,KXMLClassString) )
	{
		const NodeIndex::dtable_t& fields = ClassGenerateDataMemberTable(typenode);
		fieldsize_int = ClassBaseSize(typenode,fields);
	}else
	{
		const XMLCh* fieldsize = GetSize(lastfield);
		assert( fieldsize );
		string fieldsize_str = toString(fieldsize);
		fieldsize_int = atoi(fieldsize_str.c_str());
	}

	/*const XMLCh* offset = lastfield.GetAttribute(KXMLOffsetString);

	assert( offset );

	string offset_str = toString(offset);

	int offset_int = atoi(offset_str.c_str());*/

	return fieldsize_int+lastmember.iOffset;//offset_int;
}

// ----------------------------------------------------------------------------
// ClassGenerateDataMemberTable
// ----------------------------------------------------------------------------
//
const NodeIndex::dtable_t& ClassGenerateDataMemberTable(const HANodeIterator& classnode)
{	
    string dtablename = GenerateFullyQualifiedName(classnode);
	//Notice that this does not clear dtable, if one already exists
	const NodeIndex::dtable_t* dtable = classnode.iNodeIndex.AddEmptyDataMemberTable(classnode, dtablename);

	if ( 0 != dtable->size() )
	{
		//The vtable already exists
		return *dtable;
	}
	else
	{

		//Lets check if we are dynamic class so that we need to add
		// the virtual table pointer
		if ( classnode.CheckForBooleanAttribute(KXMLBBCVirtualString) )
		{
			string name = "::vtableptr";
			int lineNo = 0;
			string line_str = toString(classnode.GetAttribute(KXMLLineString));
			if(line_str.size() > 0)
				lineNo = atoi(line_str.c_str());
			classnode.iNodeIndex.AddDataMember(classnode,dtablename,name,NULL,0,EAccessGlobal,lineNo);
		}

		//Add the fields from bases
		DOMNodeList* childs = classnode.GetElementsByTagName(KXMLBaseString);	   
		if (childs)
		{
			XMLSize_t childcount = childs->getLength();

			for (unsigned int i = 0; i < childcount; ++i)
			{
				HANodeIterator classit(classnode);
				classit.current = childs->item(i);

				HANodeIterator baseclass(classnode);
				bool found = baseclass.FindNodeById(classit.GetAttribute(KXMLTypeString));
				assert(found);

				if ( baseclass.CheckForBooleanAttribute(KXMLBBCVirtualString) )
				{
					string offset_str = toString(classit.GetAttribute(KXMLOffsetString));
					int offset = atoi(offset_str.c_str());
					//Change offset from bytes to bits
					offset = offset*8;
                    int lineNo = 0;
					string line_str = toString(classit.GetAttribute(KXMLLineString));
					lineNo = atoi(line_str.c_str());

					string name = "[";
					name += GenerateFullyQualifiedName(baseclass);
					name += "::vtableptr";
					name += "]";
					classnode.iNodeIndex.AddDataMember(classnode,dtablename,name,NULL,offset,EAccessGlobal,lineNo);
				}
			}
		}
		
		//Add the current members
		vector<DOMNode*> virtualMethods;
		vector<DOMNode*> inlineMethods;
		vector<DOMNode*> exportedMethods;
		vector<DOMNode*> methods;
		vector<DOMNode*> fields;
		vector<DOMNode*> others;

		ClassOrderMembers(classnode, virtualMethods, inlineMethods, exportedMethods,
						methods, fields, others);

		unsigned int i = 0;
		for ( i = 0; i < fields.size(); ++i)
		{
			HANodeIterator fieldnode(classnode);
			fieldnode.current = fields[i];
			string offset_str = toString(fieldnode.GetAttribute(KXMLOffsetString));
			int offset = atoi(offset_str.c_str());

			const XMLCh* ch_name = fieldnode.GetAttribute(KXMLNameString);
			string name = "::"; //GenerateFullyQualifiedName(fieldnode);
			if (ch_name)
			{
				name += toString(ch_name);
			}

			int lineNo = 0;
			string line_str = toString(fieldnode.GetAttribute(KXMLLineString));
			lineNo = atoi(line_str.c_str());

			TAccess access = CalcAccessModifier(fieldnode);
			classnode.iNodeIndex.AddDataMember(classnode,dtablename,name,fieldnode.current,offset,access,lineNo);
		}
		return *dtable;
		
	}

}

int ParseXMLFile(   const string& xmlFilename, 
                    XERCES_CPP_NAMESPACE_QUALIFIER DOMBuilder*& domParser,
                    XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument*& domDocument,
                    XERCES_CPP_NAMESPACE_QUALIFIER DOMNode*& domRootNode )
{    
    int ret = 0;

    if( BBCFileUtils::FileExists(xmlFilename) == false )
        throw HAException(string("File: ") + xmlFilename + string(" cannot be found!\n"));
    
    static const XMLCh gLS[] = { chLatin_L, chLatin_S, chNull };
    DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(gLS);
    domParser = ((DOMImplementationLS*)impl)->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);
    XMLModuleErrorHandler errorHandler;
    domParser->setErrorHandler(&errorHandler);
    XMLCh * nowhitespace = XMLString::transcode("whitespace-in-element-content");
    domParser->setFeature(nowhitespace,false);
    XMLString::release(&nowhitespace);

    try {
            domDocument = domParser->parseURI(xmlFilename.c_str());        
        } catch (XMLException& exception) {

            if (domParser != NULL) {
                domParser->release();           
                domParser = 0;
            }
            if (domDocument != NULL) {
                domDocument = NULL;
            }
            domRootNode = NULL;
            ret = -1;
            cout << "XML ERROR: " << exception.getMessage();
            return ret;
        }
        if (domDocument != NULL)
        {
            domRootNode = (DOMNode*)domDocument->getDocumentElement();
            if( domRootNode == 0 )
                throw HAException(string("\nXML ERROR: Root element missing from ") + xmlFilename + "\n");
        }
        else
        {
            throw HAException(string("File: ") + xmlFilename + string(" could not be parsed! Please, check the filename.\n"));
        }
        return ret;
}

string& toLower(string& name)
{
#ifdef __WIN__    
    string::iterator it(name.begin());

    for(; it != name.end(); ++it)
    {
        *it = tolower((unsigned char)*it);
    }
#endif
    return name;
}
