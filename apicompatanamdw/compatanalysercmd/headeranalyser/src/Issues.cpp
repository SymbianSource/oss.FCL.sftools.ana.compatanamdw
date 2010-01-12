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

#include <sstream>
#include "Issues.h"
#include "XMLStringConst.h"

const char* KIgnoreInfoNone = "None";

// Textual descriptions for the severity levels
// Can be seen in the result xml
const char* KSeverityNULL = "None";
const char* KSeverityBBCBreak = "BBC Break";
const char* KSeverityPossibleBBCBreak = "Possible BBC Break";
const char* KSeverityFCBreak = "FC Break";
const char* KSeverityPossibleFCBreak = "Possible FC Break";
const char* KSeverityInformative = "Informative";

// Table of severity descriptions levels for binary compatibility
const char* KSeverityDesc[ESeverityCount] = 
{
    KSeverityNULL,
    KSeverityBBCBreak,
    KSeverityPossibleBBCBreak,
    KSeverityInformative,
	KSeverityFCBreak,
    KSeverityPossibleFCBreak
};

// Textual descriptions for the severity levels
// Can be seen in the result xml
const char* KSeveritySCNULL = "None";
const char* KSeveritySCBreak = "SC Break";
const char* KSeverityPossibleSCBreak = "Possible SC Break";
const char* KSeveritySCInformative = "Informative";

// Table of severity descriptions levels for source compatibility
const char* KSeveritySCDesc[ESeveritySCCount] = 
{
    KSeveritySCNULL,
    KSeveritySCBreak,
    KSeverityPossibleSCBreak,
    KSeveritySCInformative
};


// Textual descriptions for the identities
// Can be seen in the result xml
const char* KIdentityClass = "Class";
const char* KIdentityEnumeration = "Enumeration";
const char* KIdentityExportedFunction = "Exported function";
const char* KIdentityVirtualFunction = "Virtual function";
const char* KIdentityStruct = "Struct";
const char* KIdentityUnion = "Union";
const char* KIdentityEnumerationValue = "Enumeration value";
const char* KIdentityTypedef = "Typedef";
const char* KIdentityVariable = "Constant";
const char* KIdentityField = "Field";
const char* KIdentityFieldInaccessible = "Field";
const char* KIdentityFile = "File";
const char* KIdentityMacro = "Macro";
const char* KIdentityInlineFunction = "Inline function";
const char* KIdentityVirtualTable= "Virtual table";
const char*	KIdentitySubobject = "Subobject";
const char* KIdentityVirtualTablePointer = "Virtual table pointer";
const char* KIdentityExportedInlineFunction = "Exported inline function";
const char* KIdentityExportedVirtualFunction = "Exported virtual function";
const char* KIdentityVirtualInlineFunction = "Virtual inline function";
const char* KIdentityExportedVirtualInlineFunction = "Exported virtual inline function";
const char* KIdentityStructMember = "Strcut member";


// Table of the issue description
const char* KIssueIdentityDesc[EIssueIdentityCount] = 
{
    KIdentityClass,
    KIdentityExportedFunction,
    KIdentityInlineFunction,
    KIdentityVirtualFunction,
    KIdentityEnumeration,
    KIdentityStruct,
    KIdentityUnion,
    KIdentityEnumerationValue,
    KIdentityTypedef,
    KIdentityVariable,
    KIdentityField,
    KIdentityFieldInaccessible,
    KIdentityMacro,
    KIdentityFile,
    KIdentityVirtualTable,
    KIdentitySubobject,
    KIdentityVirtualTablePointer,
    KIdentityExportedInlineFunction,
    KIdentityExportedVirtualFunction,
    KIdentityVirtualInlineFunction,
    KIdentityExportedVirtualInlineFunction,
	KIdentityStructMember
};

// Textual descriptions for the issue types
// Can be seen in the result xml
const char* KIssueTypeRemoval = "has been removed";
const char* KIssueTypeAddition = "has been added";
const char* KIssueTypeChange = "has been changed";
const char* KIssueTypeSize = "has changed size";
const char* KIssueTypeBaseSize = "has changed base size";
const char* KIssueTypeAlign = "has changed alignment";
const char* KIssueTypeParam = "has changed one of its parameters";
const char* KIssueTypeParamConst = "has changed one of its parameters or funtion type";
const char* KIssueTypeParamConst2 = "has changed one of its parameters or funtion type";
const char* KIssueTypeReturn = "has changed its return value";
const char* KIssueTypeReturnConst = "has changed its return value";
const char* KIssueTypeReturnConst2 = "has changed its return value";
const char* KIssueTypeAccess = "has more restricted access level";
const char* KIssueTypeInheritance = "has changes in inheritance";
const char* KIssueTypeOffset = "has changed its offset";
const char* KIssueTypeOrderChange = "order has changed";
const char* KIssueTypeCompilationError = "has compilation errors";
const char* KIssueTypeNotAnalysed = "could not be analysed";
const char* KIssueTypeUnderConstruction = "analysis under construction";
const char* KIssueTypeVirtualBases = "has virtual bases";
const char* KIssueTypeChangeInType = "has changed its type";
const char* KIssueTypeChangeInInitialisation = "has changed its initialisation value";
const char* KIssueTypeNewOverride = "overridden in derivable class";
//const char* KIssueTypeRemovedOverride = "removed override in derivable class";
const char* KIssueTypeEmpty = "contains nothing to be analysed";

// Table of the issue type descriptions
const char* KIssueTypeDesc[EIssueTypeCount] = 
{
    KIssueTypeRemoval,
    KIssueTypeAddition,
    KIssueTypeChange,
    KIssueTypeSize,
    KIssueTypeAlign,
    KIssueTypeParam,
	KIssueTypeReturn,
	KIssueTypeAccess,
    KIssueTypeInheritance,
    KIssueTypeOffset,
    KIssueTypeOrderChange,
    KIssueTypeChangeInType,
    KIssueTypeChangeInInitialisation,
    KIssueTypeCompilationError,
    KIssueTypeNotAnalysed,
    KIssueTypeVirtualBases,
    KIssueTypeNewOverride,
//	KIssueTypeRemovedOverride,
    KIssueTypeEmpty,
    KIssueTypeBaseSize,
    KIssueTypeUnderConstruction,
    KIssueTypeParamConst,
    KIssueTypeParamConst2,
	KIssueTypeReturnConst,
    KIssueTypeReturnConst2    
};

template <typename T>
string GetIgnoreInfoFromAttribute(const HANodeIterator& node, const T* attribute)
{
	string ignoreinfo="";
	
	const XMLCh* idx = node.GetAttribute(attribute);
	if (idx)
	{
		ignoreinfo = toString(idx);
	}
	return ignoreinfo;
}

/**
* In the following the severities and ignore information of issues are defined through template mechanism.
* This allows linking time checking that we have not forgot to define meaningful information for new issues.
* In order to modify severity information or ignore information first determine the TIssueIdentity and TIssueType
* of the issue and then find the correct function (BCseverityAccessible<TIssueIdentity,TIssueType>, 
* SCseverityAccessible<TIssueIdentity,TIssueType> and ignoreInfo<TIssueIdentity,TIssueType>) and modify the function
* definition to match with the severity and ignore information.

* The BCseverityAccessible function includes parameter [accessible] that defines if the element is directly accessible
* or only through some inline method.
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////
template <> TBCSeverity BCseverityAccessible<EIssueIdentityClass,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityBBCBreak;
}


template <> string ignoreInfo<EIssueIdentityClass,EIssueTypeRemoval>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}


//Size,                     
//ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityClass,EIssueTypeSize>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityBBCBreak;
}

template <> string ignoreInfo<EIssueIdentityClass,EIssueTypeSize>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return  GetIgnoreInfoFromAttribute(current,KXMLSizeString);
}

//Align,                    
//ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityClass,EIssueTypeAlign>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityBBCBreak;
}

template <> string ignoreInfo<EIssueIdentityClass,EIssueTypeAlign>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;
    const XMLCh* align = current.GetAttribute(KXMLAlignString);
	if (align)
	{
		ignoreinfo = toString(align);
	}
	return ignoreinfo;
}

//Access,                   
//ESeverityInformative,     

template <> TBCSeverity BCseverityAccessible<EIssueIdentityClass,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}

template <> string ignoreInfo<EIssueIdentityClass,EIssueTypeAccess>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;
	const XMLCh* access = current.GetAttribute(KXMLAccessString);
	if (access)
	{
		ignoreinfo = toString(access);
	}
	return ignoreinfo;
}

//Inheritance,              
//ESeverityPossibleBBCBreak,

template <> TBCSeverity BCseverityAccessible<EIssueIdentityClass,EIssueTypeInheritance>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityPossibleBBCBreak;
}

template <> string ignoreInfo<EIssueIdentityClass,EIssueTypeInheritance>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;
    DOMNodeList* childs = current.GetElementsByTagName(KXMLBaseString);

    XMLSize_t childcount = childs->getLength();

    for (unsigned int i = 0; i < childcount; ++i)
    {
        HANodeIterator baselineit(current);
        baselineit.current = childs->item(i);
        
        ignoreinfo += GetIgnoreInfoFromAttribute(baselineit,KXMLAccessString);
        ignoreinfo += " ";

        if (baselineit.CheckForBooleanAttribute(KXMLVirtualString) )
        {
            ignoreinfo += "virtual ";
        }							

        ignoreinfo += GetTypeName(baselineit);
        ignoreinfo += ";";
    }

	return ignoreinfo;
}

//KIssueNotAnalysed        
//ESeverityInformative,    	

template <> TBCSeverity BCseverityAccessible<EIssueIdentityClass,EIssueTypeNotAnalysed>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}

template <> string ignoreInfo<EIssueIdentityClass,EIssueTypeNotAnalysed>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}


//EIssueTypeVirtualBases
//Informative

template <> TBCSeverity BCseverityAccessible<EIssueIdentityClass,EIssueTypeVirtualBases>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}

template <> string ignoreInfo<EIssueIdentityClass,EIssueTypeVirtualBases>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}

//EIssueTypeBaseSize
//ESeverityBBCBreak
template <> TBCSeverity BCseverityAccessible<EIssueIdentityClass,EIssueTypeBaseSize>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityBBCBreak;
}

template <> string ignoreInfo<EIssueIdentityClass,EIssueTypeBaseSize>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	const NodeIndex::dtable_t& datafields = ClassGenerateDataMemberTable(current);
	int basesize = ClassBaseSize(current,datafields);

	ostringstream stream; 
	stream << basesize << flush;  
	ignoreinfo = stream.str();

	return ignoreinfo;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityEnumeration,
//   Removal,                  
//    {ESeverityPossibleFCBreak,
template <> TBCSeverity BCseverityAccessible<EIssueIdentityEnumeration,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleFCBreak;
	}
	return ESeverityPossibleFCBreak;
}

template <> string ignoreInfo<EIssueIdentityEnumeration,EIssueTypeRemoval>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}


//Change,                   
//SeverityFCBreak, 
template <> TBCSeverity BCseverityAccessible<EIssueIdentityEnumeration,EIssueTypeChange>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleFCBreak;
	}
	return ESeverityPossibleFCBreak;
}

template <> string ignoreInfo<EIssueIdentityEnumeration,EIssueTypeChange>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

    DOMNodeList* baselinechilds = current.GetElementsByTagName(KXMLEnumValueString);
    XMLSize_t baselinechildcount = baselinechilds->getLength();
    unsigned int i = 0;
    for (i = 0; i < baselinechildcount; ++i)
    {
        HANodeIterator baselineit(current);
        baselineit.current = baselinechilds->item(i);
        ignoreinfo += GetIgnoreInfoFromAttribute(baselineit,KXMLNameString);
        ignoreinfo += "=";
        ignoreinfo += GetIgnoreInfoFromAttribute(baselineit,KXMLInitString);
        ignoreinfo += ";";
    }

	return ignoreinfo;
}

//Size,                     
//ESeverityFCBreak,      
template <> TBCSeverity BCseverityAccessible<EIssueIdentityEnumeration,EIssueTypeSize>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleFCBreak;
	}
	return ESeverityFCBreak;
}
template <> string ignoreInfo<EIssueIdentityEnumeration,EIssueTypeSize>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;
	
	const XMLCh* size = current.GetAttribute(KXMLSizeString);
	if (size)
	{
		ignoreinfo = toString(size);
	}
	return ignoreinfo;
}

//Align,                    
//ESeverityFCBreak,         
template <> TBCSeverity BCseverityAccessible<EIssueIdentityEnumeration,EIssueTypeAlign>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleFCBreak;
	}
	return ESeverityFCBreak;
}
template <> string ignoreInfo<EIssueIdentityEnumeration,EIssueTypeAlign>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;
	
	const XMLCh* align = current.GetAttribute(KXMLAlignString);
	if (align)
	{
		ignoreinfo = toString(align);
	}
	return ignoreinfo;
}

//Access,                   
//ESeverityInformative,   
template <> TBCSeverity BCseverityAccessible<EIssueIdentityEnumeration,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityEnumeration,EIssueTypeAccess>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;
	const XMLCh* access = current.GetAttribute(KXMLAccessString);
	if (access)
	{
		ignoreinfo = toString(access);
	}
	return ignoreinfo;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityExportedFunction,
//   Removal,                  
//   ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityExportedFunction,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityExportedFunction,EIssueTypeRemoval>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}
	
//	Param,                    
//	ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityExportedFunction,EIssueTypeParam>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityExportedFunction,EIssueTypeParam>(const HANodeIterator& baseline,const HANodeIterator& current)
{
    string ignoreinfo=KIgnoreInfoNone;
    DOMElement * element = static_cast<DOMElement*>(current.current);
    DOMNodeList* childs = element->getChildNodes();
    
    XMLSize_t childcount = childs->getLength();

    unsigned int i = 0;
    for (i = 0; i < childcount; ++i)
    {
        DOMNode* child = childs->item(i);
        HANodeIterator childit(current);
        childit.current = child;

        short nodetype = childit->getNodeType();
        if (nodetype == DOMNode::ELEMENT_NODE)
        {
            const XMLCh * defaultval = childit.GetAttribute(KXMLDefaultString);
            if ( defaultval )
            {
                ignoreinfo += toString(defaultval);
            }
            else
            {
            }
            ignoreinfo += ";";
        }

    }
	return ignoreinfo;
}

//	Param non-const to const,                    
//	ESeverityNULL,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityExportedFunction,EIssueTypeParamConst>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityNULL;
	}
	return ESeverityNULL;
}
template <> string ignoreInfo<EIssueIdentityExportedFunction,EIssueTypeParamConst>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;
    //ignoreinfo = GenerateFunctionSignature(*this);
    DOMElement * element = static_cast<DOMElement*>(current.current);
    DOMNodeList* childs = element->getChildNodes();
    
    XMLSize_t childcount = childs->getLength();

    unsigned int i = 0;
    for (i = 0; i < childcount; ++i)
    {
        DOMNode* child = childs->item(i);
        HANodeIterator childit(current);
        childit.current = child;

        short nodetype = childit->getNodeType();
        if (nodetype == DOMNode::ELEMENT_NODE)
        {
            const XMLCh * defaultval = childit.GetAttribute(KXMLDefaultString);
            if ( defaultval )
            {
                ignoreinfo += toString(defaultval);
            }
            else
            {
            }
            ignoreinfo += ";";
        }

    }
	return ignoreinfo;
}

//	Param const to non-const,                    
//	ESeverityFCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityExportedFunction,EIssueTypeParamConst2>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleFCBreak;
	}
	return ESeverityFCBreak;
}
template <> string ignoreInfo<EIssueIdentityExportedFunction,EIssueTypeParamConst2>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;
    //ignoreinfo = GenerateFunctionSignature(*this);
    DOMElement * element = static_cast<DOMElement*>(current.current);
    DOMNodeList* childs = element->getChildNodes();
    
    XMLSize_t childcount = childs->getLength();

    unsigned int i = 0;
    for (i = 0; i < childcount; ++i)
    {
        DOMNode* child = childs->item(i);
        HANodeIterator childit(current);
        childit.current = child;

        short nodetype = childit->getNodeType();
        if (nodetype == DOMNode::ELEMENT_NODE)
        {
            const XMLCh * defaultval = childit.GetAttribute(KXMLDefaultString);
            if ( defaultval )
            {
                ignoreinfo += toString(defaultval);
            }
            else
            {
            }
            ignoreinfo += ";";
        }

    }
	return ignoreinfo;
}

//	Return,                   
//	ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityExportedFunction,EIssueTypeReturn>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityExportedFunction,EIssueTypeReturn>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	const XMLCh * baselineid = current.GetAttribute(KXMLReturnsString);
	if (baselineid)
	{
		HANodeIterator newbaseline(current);
		bool ret1=newbaseline.FindNodeById(baselineid);
		if (ret1)
		{
			ignoreinfo += GetTypeName(newbaseline);
		}
	}

	return ignoreinfo;
}

//	Return const to non-const,                   
//	ESeverityNULL,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityExportedFunction,EIssueTypeReturnConst>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityNULL;
	}
	return ESeverityNULL;
}
template <> string ignoreInfo<EIssueIdentityExportedFunction,EIssueTypeReturnConst>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	const XMLCh * baselineid = current.GetAttribute(KXMLReturnsString);
	if (baselineid)
	{
		HANodeIterator newbaseline(current);
		bool ret1=newbaseline.FindNodeById(baselineid);
		if (ret1)
		{
			ignoreinfo += GetTypeName(newbaseline);
		}
	}

	return ignoreinfo;
}

//	Return non-const to const,                   
//	ESeverityFCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityExportedFunction,EIssueTypeReturnConst2>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleFCBreak;
	}
	return ESeverityFCBreak;
}
template <> string ignoreInfo<EIssueIdentityExportedFunction,EIssueTypeReturnConst2>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	const XMLCh * baselineid = current.GetAttribute(KXMLReturnsString);
	if (baselineid)
	{
		HANodeIterator newbaseline(current);
		bool ret1=newbaseline.FindNodeById(baselineid);
		if (ret1)
		{
			ignoreinfo += GetTypeName(newbaseline);
		}
	}

	return ignoreinfo;
}

//	Access,                               	
//	ESeverityInformative,                 
template <> TBCSeverity BCseverityAccessible<EIssueIdentityExportedFunction,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityExportedFunction,EIssueTypeAccess>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;
	const XMLCh* access = current.GetAttribute(KXMLAccessString);
	if (access)
	{
		ignoreinfo = toString(access);
	}
	return ignoreinfo;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityInlineFunction,
//   Removal,                  
//    {ESeverityInformative,   
template <> TBCSeverity BCseverityAccessible<EIssueIdentityInlineFunction,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityInlineFunction,EIssueTypeRemoval>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityExportedFunction,EIssueTypeRemoval>(baseline,current);
}

//	Param,                    
//	ESeverityInformative,     
template <> TBCSeverity BCseverityAccessible<EIssueIdentityInlineFunction,EIssueTypeParam>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityInlineFunction,EIssueTypeParam>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityExportedFunction,EIssueTypeParam>(baseline,current);
}

//	Param non-const to const,                    
//	ESeverityNULL,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityInlineFunction,EIssueTypeParamConst>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityNULL;
	}
	return ESeverityNULL;
}
template <> string ignoreInfo<EIssueIdentityInlineFunction,EIssueTypeParamConst>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityExportedFunction,EIssueTypeParamConst>(baseline,current);
}

//	Param const to non-const,                    
//	ESeverityFCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityInlineFunction,EIssueTypeParamConst2>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityInlineFunction,EIssueTypeParamConst2>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityExportedFunction,EIssueTypeParamConst2>(baseline,current);
}

//	Return,                   
//	ESeverityInformative,     
template <> TBCSeverity BCseverityAccessible<EIssueIdentityInlineFunction,EIssueTypeReturn>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityInlineFunction,EIssueTypeReturn>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityExportedFunction,EIssueTypeReturn>(baseline,current);
}

//	Return const to non-const,                   
//	ESeverityNULL,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityInlineFunction,EIssueTypeReturnConst>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityNULL;
	}
	return ESeverityNULL;
}
template <> string ignoreInfo<EIssueIdentityInlineFunction,EIssueTypeReturnConst>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityExportedFunction,EIssueTypeReturnConst>(baseline,current);
}

//	Return non-const to const,                   
//	ESeverityFCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityInlineFunction,EIssueTypeReturnConst2>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleFCBreak;
	}
	return ESeverityFCBreak;
}
template <> string ignoreInfo<EIssueIdentityInlineFunction,EIssueTypeReturnConst2>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityExportedFunction,EIssueTypeReturnConst2>(baseline,current);
}

//	Access,                   
//	ESeverityInformative,     
template <> TBCSeverity BCseverityAccessible<EIssueIdentityInlineFunction,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityInlineFunction,EIssueTypeAccess>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityExportedFunction,EIssueTypeAccess>(baseline,current);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityExportedVirtualFunction,
//   Removal,                  
//    {ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityExportedVirtualFunction,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityBBCBreak;
	}
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityExportedVirtualFunction,EIssueTypeRemoval>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityVirtualFunction,
//   Removal,                  
//    {ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityVirtualFunction,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityBBCBreak;
	}
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityVirtualFunction,EIssueTypeRemoval>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}

//	Addition,                 
//	ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityVirtualFunction,EIssueTypeAddition>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityBBCBreak;
	}
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityVirtualFunction,EIssueTypeAddition>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}

//	Param,                    
//	ESeverityBBCBreak,  

template <> TBCSeverity BCseverityAccessible<EIssueIdentityVirtualFunction,EIssueTypeParam>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityBBCBreak;
	}
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityVirtualFunction,EIssueTypeParam>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityExportedFunction,EIssueTypeParam>(baseline,current);
}

//	Return,                   
//	ESeverityBBCBreak,     
template <> TBCSeverity BCseverityAccessible<EIssueIdentityVirtualFunction,EIssueTypeReturn>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityBBCBreak;
	}
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityVirtualFunction,EIssueTypeReturn>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;
	return ignoreInfo<EIssueIdentityExportedFunction,EIssueTypeReturn>(baseline,current);
}

//	Access,                   
//	ESeverityInformative,     
template <> TBCSeverity BCseverityAccessible<EIssueIdentityVirtualFunction,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityVirtualFunction,EIssueTypeAccess>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;
	const XMLCh* access = current.GetAttribute(KXMLAccessString);
	if (access)
	{
		ignoreinfo = toString(access);
	}
	return ignoreinfo;}

//	OrderChange,              	
//	ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityVirtualFunction,EIssueTypeOrderChange>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityBBCBreak;
	}
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityVirtualFunction,EIssueTypeOrderChange>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;
	
	const XMLCh* idx = current.GetAttribute(KXMLBBCVirtualFunctionIndex);
	if (idx)
	{
		ignoreinfo = toString(idx);
	}
	return ignoreinfo;
}


//	KIssueTypeNewOverride,
//	ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityVirtualFunction,EIssueTypeNewOverride>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityBBCBreak;
	}
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityVirtualFunction,EIssueTypeNewOverride>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;
	return ignoreinfo;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityStruct,
//   Removal,                  
//    {ESeverityBBCBreak,	       
template <> TBCSeverity BCseverityAccessible<EIssueIdentityStruct,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityStruct,EIssueTypeRemoval>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityClass,EIssueTypeRemoval>(baseline,current);
}

//	BaseSize,                     
//	ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityStruct,EIssueTypeBaseSize>(bool accessible)
{
	return BCseverityAccessible<EIssueIdentityClass,EIssueTypeBaseSize>(accessible);
}

template <> string ignoreInfo<EIssueIdentityStruct,EIssueTypeBaseSize>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityClass,EIssueTypeBaseSize>(baseline,current);
}

// EIssueTypeNotAnalysed
// ESeverityInformative
template <> TBCSeverity BCseverityAccessible<EIssueIdentityStruct,EIssueTypeNotAnalysed>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityStruct,EIssueTypeNotAnalysed>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityClass,EIssueTypeNotAnalysed>(baseline,current);
}


//	Size,                     
//	ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityStruct,EIssueTypeSize>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityBBCBreak;
}

template <> string ignoreInfo<EIssueIdentityStruct,EIssueTypeSize>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityClass,EIssueTypeSize>(baseline,current);
}
//	Align,                    
//	ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityStruct,EIssueTypeAlign>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityBBCBreak;
}

template <> string ignoreInfo<EIssueIdentityStruct,EIssueTypeAlign>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityClass,EIssueTypeAlign>(baseline,current);
}
//	Access,                   
//	ESeverityInformative,     
template <> TBCSeverity BCseverityAccessible<EIssueIdentityStruct,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}

template <> string ignoreInfo<EIssueIdentityStruct,EIssueTypeAccess>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityClass,EIssueTypeAccess>(baseline,current);
}
//	Inheritance,              
//	ESeverityPossibleBBCBreak,
template <> TBCSeverity BCseverityAccessible<EIssueIdentityStruct,EIssueTypeInheritance>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityPossibleBBCBreak;
}

template <> string ignoreInfo<EIssueIdentityStruct,EIssueTypeInheritance>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityClass,EIssueTypeInheritance>(baseline,current);
}

//EIssueTypeVirtualBases
//Informative

template <> TBCSeverity BCseverityAccessible<EIssueIdentityStruct,EIssueTypeVirtualBases>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}

template <> string ignoreInfo<EIssueIdentityStruct,EIssueTypeVirtualBases>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityUnion,
//   Removal,                  
//    {ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityUnion,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityBBCBreak;
}

template <> string ignoreInfo<EIssueIdentityUnion,EIssueTypeRemoval>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}

template <> TBCSeverity BCseverityAccessible<EIssueIdentityUnion,EIssueTypeInheritance>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityPossibleBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityUnion,EIssueTypeInheritance>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}


//	Size,                     
//	ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityUnion,EIssueTypeSize>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityBBCBreak;
}

template <> string ignoreInfo<EIssueIdentityUnion,EIssueTypeSize>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return GetIgnoreInfoFromAttribute(current,KXMLSizeString);
}

//	BaseSize,                     
//	ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityUnion,EIssueTypeBaseSize>(bool accessible)
{
	return BCseverityAccessible<EIssueIdentityClass,EIssueTypeBaseSize>(accessible);
}

template <> string ignoreInfo<EIssueIdentityUnion,EIssueTypeBaseSize>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityClass,EIssueTypeBaseSize>(baseline,current);
}


//	Align,                    
//	ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityUnion,EIssueTypeAlign>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityUnion,EIssueTypeAlign>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return GetIgnoreInfoFromAttribute(current,KXMLAlignString);
/*	string ignoreinfo=KIgnoreInfoNone;
    ignoreinfo = toString(current.GetAttribute(KXMLAlignString));
	return ignoreinfo;
	*/
}

//	Access,                   
//	ESeverityInformative,     
template <> TBCSeverity BCseverityAccessible<EIssueIdentityUnion,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityUnion,EIssueTypeAccess>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;
	const XMLCh* access = current.GetAttribute(KXMLAccessString);
	if (access)
	{
		ignoreinfo = toString(access);
	}
	return ignoreinfo;
}

//	KIssueNotAnalysed         
//	ESeverityInformative,     
template <> TBCSeverity BCseverityAccessible<EIssueIdentityUnion,EIssueTypeNotAnalysed>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityUnion,EIssueTypeNotAnalysed>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}


//EIssueTypeVirtualBases
//Informative

template <> TBCSeverity BCseverityAccessible<EIssueIdentityUnion,EIssueTypeVirtualBases>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}

template <> string ignoreInfo<EIssueIdentityUnion,EIssueTypeVirtualBases>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityEnumerationValue,
//   Removal,                  
//   {ESeverityFCBreak,		   
template <> TBCSeverity BCseverityAccessible<EIssueIdentityEnumerationValue,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleFCBreak;
	}
	return ESeverityPossibleFCBreak;
}
template <> string ignoreInfo<EIssueIdentityEnumerationValue,EIssueTypeRemoval>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}


//	ChangeInInitialisation,   ,	
//	ESeverityFCBreak,        ,
template <> TBCSeverity BCseverityAccessible<EIssueIdentityEnumerationValue,EIssueTypeChangeInInitialisation>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleFCBreak;
	}
	return ESeverityPossibleFCBreak;
}
template <> string ignoreInfo<EIssueIdentityEnumerationValue,EIssueTypeChangeInInitialisation>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return GetIgnoreInfoFromAttribute(current,KXMLInitString);
}

//Access,                   
//ESeverityInformative,   
template <> TBCSeverity BCseverityAccessible<EIssueIdentityEnumerationValue,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityEnumerationValue,EIssueTypeAccess>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;
	const XMLCh* access = current.GetAttribute(KXMLAccessString);
	if (access)
	{
		ignoreinfo = toString(access);
	}
	return ignoreinfo;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityTypedef,
//   Removal,                  
//    {ESeverityPossibleBBCBreak,
template <> TBCSeverity BCseverityAccessible<EIssueIdentityTypedef,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityPossibleBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityTypedef,EIssueTypeRemoval>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}

//	Change,                   
//	ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityTypedef,EIssueTypeChange>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityPossibleBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityTypedef,EIssueTypeChange>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;
    const XMLCh * nodetypeid = current.GetAttribute(KXMLTypeString);
    if (nodetypeid)
	{
		HANodeIterator typenode(current);
		bool ret1=typenode.FindNodeById(nodetypeid);
		if (ret1)
		{
			ignoreinfo = GetTypeName(typenode);
		}
	}
	return ignoreinfo;
}
//Access,                   
//ESeverityInformative,   
template <> TBCSeverity BCseverityAccessible<EIssueIdentityTypedef,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityTypedef,EIssueTypeAccess>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;
	const XMLCh* access = current.GetAttribute(KXMLAccessString);
	if (access)
	{
		ignoreinfo = toString(access);
	}
	return ignoreinfo;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityVariable,
//   Removal,                  
//    {ESeverityPossibleBBCBreak,
template <> TBCSeverity BCseverityAccessible<EIssueIdentityVariable,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityPossibleBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityVariable,EIssueTypeRemoval>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}

//	ChangeInType,             
//	ESeverityBBCBreak,      

template <> TBCSeverity BCseverityAccessible<EIssueIdentityVariable,EIssueTypeChangeInType>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityPossibleBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityVariable,EIssueTypeChangeInType>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;
    const XMLCh * nodetypeid = current.GetAttribute(KXMLTypeString);
    if (nodetypeid)
	{
		HANodeIterator typenode(current);
		bool ret1=typenode.FindNodeById(nodetypeid);
		if (ret1)
		{
			ignoreinfo = GetTypeName(typenode);
		}
	}

	return ignoreinfo;
}

//	ChangeInInitialisation,   ,	
//	ESeverityFCBreak,        ,
template <> TBCSeverity BCseverityAccessible<EIssueIdentityVariable,EIssueTypeChangeInInitialisation>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleFCBreak;
	}
	return ESeverityPossibleFCBreak;
}
template <> string ignoreInfo<EIssueIdentityVariable,EIssueTypeChangeInInitialisation>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ::GetIgnoreInfoFromAttribute(current,KXMLInitString);
}

//Access,                   
//ESeverityInformative,   
template <> TBCSeverity BCseverityAccessible<EIssueIdentityVariable,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityVariable,EIssueTypeAccess>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;
	const XMLCh* access = current.GetAttribute(KXMLAccessString);
	if (access)
	{
		ignoreinfo = toString(access);
	}
	return ignoreinfo;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityField,
//   Removal,                  
//    {ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityField,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityField,EIssueTypeRemoval>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}

//	Addition,                 
//	ESeverityInformative,     
template <> TBCSeverity BCseverityAccessible<EIssueIdentityField,EIssueTypeAddition>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}

template <> string ignoreInfo<EIssueIdentityField,EIssueTypeAddition>(const HANodeIterator& baseline,const HANodeIterator& current)
{
    string ignoreinfo=KIgnoreInfoNone;

    ignoreinfo += toString(current.GetAttribute(KXMLContextString));
    ignoreinfo += ";";
    const XMLCh * nodetypeid = current.GetAttribute(KXMLTypeString);
    if (nodetypeid)
    {
		  HANodeIterator typenode(current);
		  bool ret1=typenode.FindNodeById(nodetypeid);
		  if (ret1)
		  {
			  ignoreinfo += GetTypeName(typenode);
	  	}
    }
    return ignoreinfo;
}

//	Size,                     
//	ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityField,EIssueTypeSize>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityField,EIssueTypeSize>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;
	const XMLCh * size = GetSize(current);
	if (size)
	{
		ignoreinfo += toString( size );
	}

	return ignoreinfo;
}


//	Access,                   
//	ESeverityInformative,     
template <> TBCSeverity BCseverityAccessible<EIssueIdentityField,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityField,EIssueTypeAccess>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;
	const XMLCh* access = current.GetAttribute(KXMLAccessString);
	if (access)
	{
		ignoreinfo = toString(access);
	}
	return ignoreinfo;
}

//	Offset,                   
//	ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityField,EIssueTypeOffset>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityField,EIssueTypeOffset>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ::GetIgnoreInfoFromAttribute(current,KXMLContextString);
}


//	ChangeInType,             
//	ESeverityBBCBreak,        
template <> TBCSeverity BCseverityAccessible<EIssueIdentityField,EIssueTypeChangeInType>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityField,EIssueTypeChangeInType>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo="";

    const XMLCh * nodetypeid = current.GetAttribute(KXMLTypeString);
    if (nodetypeid)
	{
		HANodeIterator typenode(current);
		bool ret1=typenode.FindNodeById(nodetypeid);
		if (ret1)
		{
			ignoreinfo += GetTypeName(typenode);
		}
	}

	return ignoreinfo;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityFieldInaccessible,
//   Removal,                  
//   {ESeverityInformative,     
template <> TBCSeverity BCseverityAccessible<EIssueIdentityFieldInaccessible,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityFieldInaccessible,EIssueTypeRemoval>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityField,EIssueTypeRemoval>(baseline, current);
}

//	Addition,                 
//	ESeverityInformative,     
template <> TBCSeverity BCseverityAccessible<EIssueIdentityFieldInaccessible,EIssueTypeAddition>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityFieldInaccessible,EIssueTypeAddition>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityField,EIssueTypeAddition>(baseline, current);
}


//	Size,                     
//	ESeverityInformative,     
template <> TBCSeverity BCseverityAccessible<EIssueIdentityFieldInaccessible,EIssueTypeSize>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityFieldInaccessible,EIssueTypeSize>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityField,EIssueTypeSize>(baseline, current);
}

//	Access,                   
//	ESeverityInformative,     
template <> TBCSeverity BCseverityAccessible<EIssueIdentityFieldInaccessible,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityFieldInaccessible,EIssueTypeAccess>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityField,EIssueTypeAccess>(baseline, current);
}

//	Offset,                   
//	ESeverityInformative,     
template <> TBCSeverity BCseverityAccessible<EIssueIdentityFieldInaccessible,EIssueTypeOffset>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityFieldInaccessible,EIssueTypeOffset>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityField,EIssueTypeOffset>(baseline, current);
}

//	ChangeInType,             
//	ESeverityInformative,     ,
template <> TBCSeverity BCseverityAccessible<EIssueIdentityFieldInaccessible,EIssueTypeChangeInType>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityFieldInaccessible,EIssueTypeChangeInType>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	return ignoreInfo<EIssueIdentityField,EIssueTypeChangeInType>(baseline, current);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityFile,
//	KIssueNotAnalysed         
//	ESeverityInformative,     
template <> TBCSeverity BCseverityAccessible<EIssueIdentityFile,EIssueTypeEmpty>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityInformative;
	}
	return ESeverityInformative;
}
template <> string ignoreInfo<EIssueIdentityFile,EIssueTypeEmpty>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}

template <> TBCSeverity BCseverityAccessible<EIssueIdentityFile,EIssueTypeUnderConstruction>(bool accessible)
{
	if ( !accessible )
	{
		return ESeverityPossibleBBCBreak;
	}
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityFile,EIssueTypeUnderConstruction>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityVirtualTable,
template <> TBCSeverity BCseverityAccessible<EIssueIdentityVirtualTable,EIssueTypeChange>(bool accessible)
{
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityVirtualTable,EIssueTypeChange>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//KIdentitySubobject
//Offset
//ESeverityBBCBreak
template <> TBCSeverity BCseverityAccessible<EIssueIdentitySubobject,EIssueTypeOffset>(bool accessible)
{
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentitySubobject,EIssueTypeOffset>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}

//Removal
//ESeverityBBCBreak
template <> TBCSeverity BCseverityAccessible<EIssueIdentitySubobject,EIssueTypeRemoval>(bool accessible)
{
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentitySubobject,EIssueTypeRemoval>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityVirtualTablePointer
template <> TBCSeverity BCseverityAccessible<EIssueIdentityVirtualTablePointer,EIssueTypeAddition>(bool accessible)
{
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityVirtualTablePointer,EIssueTypeAddition>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}

template <> TBCSeverity BCseverityAccessible<EIssueIdentityVirtualTablePointer,EIssueTypeRemoval>(bool accessible)
{
	return ESeverityBBCBreak;
}

template <> string ignoreInfo<EIssueIdentityVirtualTablePointer,EIssueTypeRemoval>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}
template <> TBCSeverity BCseverityAccessible<EIssueIdentityVirtualTablePointer,EIssueTypeOffset>(bool accessible)
{
	return ESeverityBBCBreak;
}
template <> string ignoreInfo<EIssueIdentityVirtualTablePointer,EIssueTypeOffset>(const HANodeIterator& baseline,const HANodeIterator& current)
{
	string ignoreinfo=KIgnoreInfoNone;

	return ignoreinfo;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityClass
//Removal
//ESeveritySCBreak
template <> TSCSeverity SCseverityAccessible<EIssueIdentityClass,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//Size,                     
//ESeveritySCNULL,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityClass,EIssueTypeSize>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//Align,                    
//ESeveritySCNULL,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityClass,EIssueTypeAlign>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//Access,                   
//ESeveritySCBreak,     
template <> TSCSeverity SCseverityAccessible<EIssueIdentityClass,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//Inheritance,              
//ESeveritySCNULL,
template <> TSCSeverity SCseverityAccessible<EIssueIdentityClass,EIssueTypeInheritance>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//KIssueNotAnalysed        
//ESeveritySCBreak,    	
template <> TSCSeverity SCseverityAccessible<EIssueIdentityClass,EIssueTypeNotAnalysed>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//EIssueTypeVirtualBases
//ESeveritySCNULL
template <> TSCSeverity SCseverityAccessible<EIssueIdentityClass,EIssueTypeVirtualBases>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//EIssueTypeBaseSize
//ESeveritySCNULL
template <> TSCSeverity SCseverityAccessible<EIssueIdentityClass,EIssueTypeBaseSize>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityEnumeration,
//   Removal,                  
//    {ESeveritySCBreak,
template <> TSCSeverity SCseverityAccessible<EIssueIdentityEnumeration,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//Change,                   
//ESeveritySCNULL, 
template <> TSCSeverity SCseverityAccessible<EIssueIdentityEnumeration,EIssueTypeChange>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//Size,                     
//ESeveritySCNULL,      
template <> TSCSeverity SCseverityAccessible<EIssueIdentityEnumeration,EIssueTypeSize>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//Align,                    
//ESeveritySCNULL,         
template <> TSCSeverity SCseverityAccessible<EIssueIdentityEnumeration,EIssueTypeAlign>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//Access,                   
//ESeveritySCBreak,   
template <> TSCSeverity SCseverityAccessible<EIssueIdentityEnumeration,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityExportedFunction,
//   Removal,                  
//    {ESeveritySCBreak,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityExportedFunction,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Param,                    
//	ESeveritySCBreak,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityExportedFunction,EIssueTypeParam>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Param non-const to const,                    
//	ESeveritySCBreak, 
template <> TSCSeverity SCseverityAccessible<EIssueIdentityExportedFunction,EIssueTypeParamConst>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Param const to non-const,                    
//	ESeveritySCBreak,
template <> TSCSeverity SCseverityAccessible<EIssueIdentityExportedFunction,EIssueTypeParamConst2>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Return,                   
//	ESeveritySCBreak,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityExportedFunction,EIssueTypeReturn>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Return const to non-const,                   
//	ESeveritySCBreak,
template <> TSCSeverity SCseverityAccessible<EIssueIdentityExportedFunction,EIssueTypeReturnConst>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Return non-const to const,                   
//	ESeveritySCBreak,
template <> TSCSeverity SCseverityAccessible<EIssueIdentityExportedFunction,EIssueTypeReturnConst2>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Access,                               	
//	ESeveritySCBreak,                 
template <> TSCSeverity SCseverityAccessible<EIssueIdentityExportedFunction,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityInlineFunction,
//   Removal,                  
//    {ESeveritySCBreak,   
template <> TSCSeverity SCseverityAccessible<EIssueIdentityInlineFunction,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Param,                    
//	ESeverityInformative,     
template <> TSCSeverity SCseverityAccessible<EIssueIdentityInlineFunction,EIssueTypeParam>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Param non-const to const,                    
//	ESeveritySCBreak,
template <> TSCSeverity SCseverityAccessible<EIssueIdentityInlineFunction,EIssueTypeParamConst>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Param const to non-const,                    
//	ESeveritySCBreak,
template <> TSCSeverity SCseverityAccessible<EIssueIdentityInlineFunction,EIssueTypeParamConst2>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Return,                   
//	ESeveritySCBreak,     
template <> TSCSeverity SCseverityAccessible<EIssueIdentityInlineFunction,EIssueTypeReturn>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Return const to non-const,                   
//	ESeveritySCBreak,
template <> TSCSeverity SCseverityAccessible<EIssueIdentityInlineFunction,EIssueTypeReturnConst>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Return non-const to const,                   
//	ESeveritySCBreak,
template <> TSCSeverity SCseverityAccessible<EIssueIdentityInlineFunction,EIssueTypeReturnConst2>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Access,                   
//	ESeveritySCBreak,     
template <> TSCSeverity SCseverityAccessible<EIssueIdentityInlineFunction,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityExportedVirtualFunction,
//   Removal,                  
//    {ESeveritySCBreak,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityExportedVirtualFunction,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityVirtualFunction,
//   Removal,                  
//    {ESeveritySCBreak,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityVirtualFunction,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Addition,                 
//	ESeveritySCBNULL,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityVirtualFunction,EIssueTypeAddition>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//	Param,                    
//	ESeveritySCBreak,  
template <> TSCSeverity SCseverityAccessible<EIssueIdentityVirtualFunction,EIssueTypeParam>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Return,                   
//	ESeveritySCBreak,     
template <> TSCSeverity SCseverityAccessible<EIssueIdentityVirtualFunction,EIssueTypeReturn>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Access,                   
//	ESeveritySCBreak,     
template <> TSCSeverity SCseverityAccessible<EIssueIdentityVirtualFunction,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	OrderChange,              	
//	ESeveritySCNULL,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityVirtualFunction,EIssueTypeOrderChange>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//	KIssueTypeNewOverride,
//	ESeveritySCNULL,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityVirtualFunction,EIssueTypeNewOverride>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityStruct,
//   Removal,                  
//    {ESeveritySCBreak,	       
template <> TSCSeverity SCseverityAccessible<EIssueIdentityStruct,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	BaseSize,                     
//	ESeveritySCNULL,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityStruct,EIssueTypeBaseSize>(bool accessible)
{
	return SCseverityAccessible<EIssueIdentityClass,EIssueTypeBaseSize>(accessible);
}

//EIssueTypeNotAnalysed
//ESeveritySCBreak
template <> TSCSeverity SCseverityAccessible<EIssueIdentityStruct,EIssueTypeNotAnalysed>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Size,                     
//	ESeveritySCNULL,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityStruct,EIssueTypeSize>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//	Align,                    
//	ESeveritySCNULL,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityStruct,EIssueTypeAlign>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//	Access,                   
//	ESeveritySCBreak,     
template <> TSCSeverity SCseverityAccessible<EIssueIdentityStruct,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Inheritance,              
//	ESeveritySCNULL,
template <> TSCSeverity SCseverityAccessible<EIssueIdentityStruct,EIssueTypeInheritance>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//EIssueTypeVirtualBases
//ESeveritySCNULL
template <> TSCSeverity SCseverityAccessible<EIssueIdentityStruct,EIssueTypeVirtualBases>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityUnion,
//   Removal,                  
//    {ESeveritySCBreak,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityUnion,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//   Inheritance,                  
//    {ESeveritySCNULL,  
template <> TSCSeverity SCseverityAccessible<EIssueIdentityUnion,EIssueTypeInheritance>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//	Size,                     
//	ESeveritySCNULL,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityUnion,EIssueTypeSize>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//	BaseSize,                     
//	ESeveritySCNULL,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityUnion,EIssueTypeBaseSize>(bool accessible)
{
	return SCseverityAccessible<EIssueIdentityClass,EIssueTypeBaseSize>(accessible);
}

//	Align,                    
//	ESeveritySCNULL,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityUnion,EIssueTypeAlign>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//	Access,                   
//	ESeveritySCBreak,     
template <> TSCSeverity SCseverityAccessible<EIssueIdentityUnion,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	KIssueNotAnalysed         
//	ESeveritySCBreak,     
template <> TSCSeverity SCseverityAccessible<EIssueIdentityUnion,EIssueTypeNotAnalysed>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//EIssueTypeVirtualBases
//ESeveritySCNULL
template <> TSCSeverity SCseverityAccessible<EIssueIdentityUnion,EIssueTypeVirtualBases>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityEnumerationValue,
//   Removal,                  
//   {ESeveritySCBreak,		   
template <> TSCSeverity SCseverityAccessible<EIssueIdentityEnumerationValue,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	ChangeInInitialisation,   ,	
//	ESeveritySCNULL,        ,
template <> TSCSeverity SCseverityAccessible<EIssueIdentityEnumerationValue,EIssueTypeChangeInInitialisation>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//Access,                   
//ESeveritySCBreak,   
template <> TSCSeverity SCseverityAccessible<EIssueIdentityEnumerationValue,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityTypedef,
//   Removal,                  
//    {ESeveritySCBreak,
template <> TSCSeverity SCseverityAccessible<EIssueIdentityTypedef,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Change,                   
//	ESeveritySCBreak,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityTypedef,EIssueTypeChange>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//Access,                   
//ESeveritySCBreak,   
template <> TSCSeverity SCseverityAccessible<EIssueIdentityTypedef,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityVariable,
//   Removal,                  
//    {ESeveritySCBreak,
template <> TSCSeverity SCseverityAccessible<EIssueIdentityVariable,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	ChangeInType,             
//	ESeveritySCBreak,      
template <> TSCSeverity SCseverityAccessible<EIssueIdentityVariable,EIssueTypeChangeInType>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	ChangeInInitialisation,   ,	
//	ESeveritySCNULL,        ,
template <> TSCSeverity SCseverityAccessible<EIssueIdentityVariable,EIssueTypeChangeInInitialisation>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//Access,                   
//ESeveritySCBreak,   
template <> TSCSeverity SCseverityAccessible<EIssueIdentityVariable,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityField,
//   Removal,                  
//    {ESeveritySCBreak,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityField,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Addition,                 
//	ESeveritySCNULL,     
template <> TSCSeverity SCseverityAccessible<EIssueIdentityField,EIssueTypeAddition>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//	Size,                     
//	ESeveritySCNULL,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityField,EIssueTypeSize>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//	Access,                   
//	ESeveritySCBreak,     
template <> TSCSeverity SCseverityAccessible<EIssueIdentityField,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}

//	Offset,                   
//	ESeveritySCNULL,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityField,EIssueTypeOffset>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//	ChangeInType,             
//	ESeveritySCBreak,        
template <> TSCSeverity SCseverityAccessible<EIssueIdentityField,EIssueTypeChangeInType>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCBreak;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityFieldInaccessible,
//   Removal,                  
//   {ESeveritySCNULL,     
template <> TSCSeverity SCseverityAccessible<EIssueIdentityFieldInaccessible,EIssueTypeRemoval>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//	Addition,                 
//	ESeveritySCNULL,     
template <> TSCSeverity SCseverityAccessible<EIssueIdentityFieldInaccessible,EIssueTypeAddition>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//	Size,                     
//	ESeveritySCNULL,     
template <> TSCSeverity SCseverityAccessible<EIssueIdentityFieldInaccessible,EIssueTypeSize>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//	Access,                   
//	ESeveritySCNULL,     
template <> TSCSeverity SCseverityAccessible<EIssueIdentityFieldInaccessible,EIssueTypeAccess>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//	Offset,                   
//	ESeveritySCNULL,     
template <> TSCSeverity SCseverityAccessible<EIssueIdentityFieldInaccessible,EIssueTypeOffset>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}

//	ChangeInType,             
//	ESeveritySCNULL,     ,
template <> TSCSeverity SCseverityAccessible<EIssueIdentityFieldInaccessible,EIssueTypeChangeInType>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCNULL;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityFile,
//	KIssueNotAnalysed         
//	ESeveritySCInformative,     
template <> TSCSeverity SCseverityAccessible<EIssueIdentityFile,EIssueTypeEmpty>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCInformative;
}

// EIssueTypeUnderConstruction
// ESeveritySCInformative
template <> TSCSeverity SCseverityAccessible<EIssueIdentityFile,EIssueTypeUnderConstruction>(bool accessible)
{
	if ( !accessible )
	{
		return ESeveritySCNULL;
	}
	return ESeveritySCInformative;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityVirtualTable,
template <> TSCSeverity SCseverityAccessible<EIssueIdentityVirtualTable,EIssueTypeChange>(bool accessible)
{
	return ESeveritySCNULL;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//KIdentitySubobject
//Offset
//ESeveritySCNULL
template <> TSCSeverity SCseverityAccessible<EIssueIdentitySubobject,EIssueTypeOffset>(bool accessible)
{
	return ESeveritySCNULL;
}

//Removal
//ESeveritySCBreak
template <> TSCSeverity SCseverityAccessible<EIssueIdentitySubobject,EIssueTypeRemoval>(bool accessible)
{
	return ESeveritySCBreak;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIssueIdentityVirtualTablePointer
//Addition
//ESeveritySCNULL
template <> TSCSeverity SCseverityAccessible<EIssueIdentityVirtualTablePointer,EIssueTypeAddition>(bool accessible)
{
	return ESeveritySCNULL;
}

//Removal
//ESeveritySCNULL
template <> TSCSeverity SCseverityAccessible<EIssueIdentityVirtualTablePointer,EIssueTypeRemoval>(bool accessible)
{
	return ESeveritySCNULL;
}

//Offset
//ESeveritySCNULL
template <> TSCSeverity SCseverityAccessible<EIssueIdentityVirtualTablePointer,EIssueTypeOffset>(bool accessible)
{
	return ESeveritySCNULL;
}


