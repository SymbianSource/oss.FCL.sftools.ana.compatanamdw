/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description:  Functionality of function analysis 
*
*/


#include "la.hpp"

// ----------------------------------------------------------------------------------------------------------

/**
 * This flags affects to the function comparison policy.
 */
// Default policy (=exact match):
#define COMPARE_FLAG_NONE                       0x00000000

// This flag means that adding a 'const' qualifier to a function
// parameter does not generate BBC break issue:
#define COMPARE_FLAG_ALLOW_CONST_ADDITION       0x00000001

// ----------------------------------------------------------------------------------------------------------

// Forward declaration
class ParameterList;

// ParameterElement class represents a parameter element, which has an actual
// value and optional sub-parameters.
class ParameterElement
{
public:
    // Default constructor and destructor
    ParameterElement();
    virtual ~ParameterElement();

    // Copy constructor
    ParameterElement(const ParameterElement& rhs);
    // Assignment operator
    const ParameterElement& operator= (const ParameterElement& rhs);

    // Methods for getting the element value.
    string& Value() { return val; };
    const string& Value() const { return val; };

    // Methods for getting the sub-parameters.
    ParameterList* SubParameters() { return subPars; };
    const ParameterList* SubParameters() const { return subPars; };

    // Sets the sub-parameters. Takes the ownership to the given 
    // sub-parameter list pointer.
    void SetSubParameters( ParameterList* pPars );

    // Clears the value and sub-parameters.
    void Clear();

private:
    string val;
    ParameterList* subPars;
};

// ----------------------------------------------------------------------------------------------------------

typedef vector<ParameterElement> FunctionParameter;

class ParameterList : public vector<FunctionParameter>
{};

ParameterElement::ParameterElement() 
{
    subPars = new ParameterList(); 
}
ParameterElement::~ParameterElement()
{
    delete subPars;
}
ParameterElement::ParameterElement(const ParameterElement& rhs)
{
    val = rhs.val;
    if( rhs.subPars )
        subPars = new ParameterList(*(rhs.subPars));
    else
        subPars = 0;
}

void ParameterElement::Clear() 
{
    val.clear();
    if( subPars )
        subPars->clear();
}

const ParameterElement& ParameterElement::operator= (const ParameterElement& rhs)
    {
        if( this != &rhs )
        {
            val = rhs.val;
            delete subPars;
            if( rhs.subPars )
                subPars = new ParameterList(*(rhs.subPars));
            else
                subPars = 0;
        }
        return *this;
    }

void ParameterElement::SetSubParameters( ParameterList* pPars )
{
    delete subPars;
    subPars = pPars;
}

// ----------------------------------------------------------------------------------------------------------

/**
 * This structure represents the C++ cv-qualifier.
 */
struct CVQualifier
{
    static const string constQualifier;
    static const string volatileQualifier;
    static const string constVolatileQualifier;

    CVQualifier() { isConst = false; isVolatile = false; };

    /**
     * Set function gets <code>std::string</code> as an input and sets const 
     * and/or volatile flags according to the input.
     * @param cvStr String representing the const and / or volatile qualifier
     * i.e "const", "volatile" or "const volatile".
     */
    void Set(string const& cvStr)
    {
        if( cvStr == constQualifier )
        {
            isConst = true;         
            isVolatile = false;
        }
        else if( cvStr == volatileQualifier )
        {
            isConst = false;
            isVolatile = true;
        }
        else if( cvStr == constVolatileQualifier )
        {
            isConst = true;
            isVolatile = true;
        }        
        else
        {
            isConst = false;
            isVolatile = false;
        }
    };

    /**
     * Sets const and/or volatile flags
     * @param c 'const' qualifier. If TRUE, isConst flag is set to TRUE
     * @param v 'volatile' qualifier. If TRUE, isVolatile flag is set to TRUE
     */
    void Set( bool c, bool v )
    {
        isConst = c;
        isVolatile = v;
    };
    bool isConst;
    bool isVolatile;
};

// ----------------------------------------------------------------------------------------------------------

const string CVQualifier::constQualifier = string("const");
const string CVQualifier::volatileQualifier = string("volatile");
const string CVQualifier::constVolatileQualifier = string("const volatile");

// ----------------------------------------------------------------------------------------------------------


// This represents the function signature
struct FuncSignature
{    
    string nestedName; // name part
    ParameterList parameters; // parameters
    CVQualifier cvQualifier; // cv-qualifier of function
};

// ----------------------------------------------------------------------------------------------------------


bool AreParametersCompatible(const FunctionParameter& basePar, const FunctionParameter& currPar, unsigned int CompareFlags = COMPARE_FLAG_NONE);
string::const_iterator RemoveSpaces(string::const_iterator start, string::const_iterator end, string::const_iterator& result);
string::size_type ReadCharsInTag(const string& sig, string& argElem, string::size_type startPos, pair<char, char> const& tag);


// ----------------------------------------------------------------------------------------------------------

/**
 * Reads characters inside the given tag. Starts looking for the
 * starting tag at startPos. 
 * @param sig Reference to the string representing the function signature. 
 * @param argElem Reference to the string in which the parameter list is read.
 * @param startPos Tag starting point (e.g. '<' or '(') is startet to be searched
 *        after this location.
 * @param tag This object defines the starting and ending characters of the tag (e.g. '<' and '>').
 * @return Size of the string between the start and end characters of the tag.
 */
string::size_type ReadCharsInTag(const string& sig, string& argElem, string::size_type startPos, pair<char, char> const& tag)
{
    string::size_type sigLen = sig.size();
    if( sigLen == 0 )
    {
        return 0;
    }

    if( sig.at(startPos) != tag.first )
    {
        startPos = sig.find(tag.first, startPos);
    }

    string::size_type currPos = startPos;

    int tagCnt = 0; // This counter will be increased by 1 when tag starts and
                    // decreased by 1 when the tag ends. When it reaches zero,
                    // the tag has been completely read.

    do
    {            
        const char current = sig.at(currPos); // throws, if out of bounds

        if( current == tag.first )
            ++tagCnt; // tag starts
        else if( current == tag.second )
            --tagCnt; // tag ends

        ++currPos;
    }
    while( tagCnt > 0 );

    string::size_type len = currPos - startPos;

    if( len > 0 )
    {
        argElem.append(sig.begin() + startPos, sig.begin() + currPos);
    }

    return len;
}

// ----------------------------------------------------------------------------------------------------------

/**
 * ParseParameterList. Recursively parses the given sub-string into
 * parameter list object.
 * @param funcSignature Reference to the string representing the function 
 *        signature.
 * @param parBegin Location where the parameter list starts.
 * @param parEnd Location where the parameter list ends.
 * @param parameters Parameter list of the function is returned here.
 */
void ParseParameterList(const string& funcSignature, 
                        string::size_type parBegin, 
                        string::size_type parEnd, 
                        ParameterList& parameters)
{    
    FunctionParameter par; // Object holding the current function parameter during parsing
    ParameterElement parElem; // Object holding the current parameter element during parsing
    
    while( parBegin <= parEnd )
    {
        char current = funcSignature.at(parBegin);
        switch( current )
        {
        case '(':
        case '<':
            {
                // Character '(' or '<' means that a new parameter list starts.
                // New parameter list is stored as a sub-parameter list of the current parameter.

                if( parElem.Value().size() > 0 )
                {
                    par.push_back(parElem); // Put the previous element in the list...
                    parElem.Clear(); // ...and clear the object for the next round.
                }

                string parListStr; // String representing the sub-parameterlist is stored here.
                int len = 0;
                char tagEndMark = current == '(' ? ')' : '>';

                // Put the value "<>" or "()"
                parElem.Value().push_back(current);
                parElem.Value().push_back(tagEndMark);

                // Read sub-parameters...
                len += ReadCharsInTag( funcSignature, parListStr, parBegin, make_pair(current, tagEndMark) );
                // ...and parse them
                if( parElem.SubParameters() == 0 )
                {
                    parElem.SetSubParameters(new ParameterList());
                }
                ParseParameterList(parListStr, 1, len-1, *(parElem.SubParameters()) );

                par.push_back(parElem); // Put the current element in the list...
                parElem.Clear(); // ...and clear the object for the next round.

                parBegin += len;
                break;
            }        
        case ' ':        
            {
                // space means that we have a new parameter element

                if( parElem.Value().size() > 0 )
                {
                    par.push_back(parElem); // Put the previous element in the list...
                    parElem.Clear(); // ...and clear the object for the next round.
                }
                ++parBegin;
                break;
            }
        case ',':
        case ')':
        case '>':
            {
                // Parameter completed

                if( parElem.Value().size() > 0 )
                {
                    par.push_back(parElem); // Put the previous element in the list...
                    parElem.Clear(); //...and clear the object for the next round.
                }
                if( par.size() > 0 )
                {
                    // Put the parameter in the parameter list...
                    parameters.push_back(par);
                    par.clear(); //...and clear the object for the next round.
                }
                ++parBegin;
                break;
            }
        case '*':
        case '&':
            {
                // We have a pointer or reference

                if( parElem.Value().size() > 0 )
                {
                    par.push_back(parElem); // Put the previous element in the list...
                    parElem.Clear(); //...and clear the object for the next round.
                }
                // Put also the current element in the list (i.e. '*' or '&')
                parElem.Value().push_back(current);
                par.push_back(parElem);
                parElem.Clear(); // ...and clear the object for the next round.
                ++parBegin;
                break;
            }
        default:
            {
                parElem.Value().push_back(funcSignature.at(parBegin));
                ++parBegin;
                break;
            }
        }        
    }
}

// ----------------------------------------------------------------------------------------------------------

/**
 * ParseFunctionSignature
 * Parses function signature and returns following elements for the given 
 * function: 
 *  - name
 *  - parameters, which are splitted in elements and sub-parameters
 *  - cv-qualifier of the function
 *
 * Parameters are splitted in following elements: 
 *  - type (int, char, etc...)
 *  - cv-qualifier (const and/or volatile)
 *  - pointer symbol (*)
 *  - reference symbol (&)
 *  - parameter list "()" 
 *  - template parameter list "<>".
 *
 * Parameter lists are further splitted into sub-parameters, which also consists
 * of elements and sub-parameters.
 *
 * @param funcSignature Reference to the string representing the function signature
 * @param signature Parsed function signature is returned in this object.
 */
void ParseFunctionSignature( const string& funcSignature, FuncSignature& signature )
{    
    // Find the start and end positions of the "main" parameter list
    string::size_type openBracketIndex = funcSignature.find_first_of('(');
    string::size_type closeBracketIndex = funcSignature.find_last_of(')');
        
    if(openBracketIndex == string::npos || closeBracketIndex == string::npos )
    {     
        // No parameter list, so the given string may be for example 
        // "virtual table for MyClass"
        signature.nestedName = funcSignature;
        return;
    }

    // Remove preceding and trailing spaces from the function name part:
    string::const_iterator start;
    string::const_iterator end = RemoveSpaces(  
                                    funcSignature.begin(), 
                                    funcSignature.begin() + openBracketIndex,
                                    start);

    // Store the name part
    signature.nestedName.append(start, end); 

    // Parse function parameters
    ParseParameterList(funcSignature, openBracketIndex+1, closeBracketIndex, signature.parameters);

    // Parse the cv-qualifier of the function.
    end = RemoveSpaces(funcSignature.begin() + (closeBracketIndex+1), funcSignature.end(), start);
    signature.cvQualifier.Set(string(start,end));
}

// ----------------------------------------------------------------------------------------------------------

/**
 * AreFunctionsCompatible
 * Compares two function signatures for backward binary compatibility. 
 * This function first parses the function signature into name, parameter list
 * and cv-qualifier parts. The name part is compared first and if names don't 
 * match, return false. Then parameter lists are given to 
 * <code>AreParametersCompatible</code> function for comparison. 
 * And finally cv-qualifiers of functions are compared. This comparison function
 * allows changing non-const function to const (i.e adding 'const'-qualifier for 
 * a function).
 * @param baselineFunc Reference to the string representing the baseline 
 *        platform's function signature
 * @param currentFunc Reference to the string representing the current
 *        platform's function signature
 * @return bool value indicating whether the two functions are backward binary
 *         compatible.
 */
TypeOfSeverity AreFunctionsCompatible(const string& baselineFunc, const string& currentFunc)
{ 
	TypeOfSeverity retSeverity = NO_BREAK;
    // First split functions into name part, parameter list and possible cv-qualifier:
    FuncSignature baseFunc;
    FuncSignature currFunc;

    ParseFunctionSignature(baselineFunc, baseFunc);
    ParseFunctionSignature(currentFunc, currFunc);
    
      // Check the const qualifier of the function:
    if( baseFunc.cvQualifier.isConst != currFunc.cvQualifier.isConst )
	  {        
		    // const qualifier of the function has been removed(either const to non-const or vise versa)
		    // Results in SC break    
		    retSeverity = CONFIRMED_SC_BREAK;
		goto EXIT_POINT;
	  }
	  
	  // Check the number of parameters:
    if( baseFunc.parameters.size() != currFunc.parameters.size() )
    {
        retSeverity = POSSIBLE_BC_CONFIRMED_SC_BREAK; // Number of parameters does not match.
		goto EXIT_POINT;
    }

    // Then check name part:
    if( baseFunc.nestedName.compare(currFunc.nestedName) != 0 )
    {     
        retSeverity = POSSIBLE_BC_SC_BREAK; // Names do not match.
		goto EXIT_POINT;
    }

    // Check the parameters:       
    for( unsigned int i = 0; i < baseFunc.parameters.size(); ++i )
    {
        if( AreParametersCompatible(baseFunc.parameters[i], currFunc.parameters[i], COMPARE_FLAG_ALLOW_CONST_ADDITION) == false )
        {            
            retSeverity = POSSIBLE_BC_SC_BREAK; // Parameters do not match
			goto EXIT_POINT;
        }
    }

    if( baseFunc.cvQualifier.isVolatile != currFunc.cvQualifier.isVolatile )
    {
        retSeverity = POSSIBLE_SC_BREAK; // volatile qualifier does not match
		goto EXIT_POINT;
    }

EXIT_POINT:
    return retSeverity;
}

// ----------------------------------------------------------------------------------------------------------

/**
 * Removes preceding and trailing spaces from the given string
 * @return iterator to the end of the trimmed string.
 * @param start Iterator to the beginning of the string.
 * @param end Iterator to the end of the string.
 * @param result Iterator to the beginning of the trimmed string. 
 */
string::const_iterator RemoveSpaces(string::const_iterator start, 
                                    string::const_iterator end, 
                                    string::const_iterator& result)
{
    // Remove spaces from the beginning of the string:
    result = start;
    while( result != end && *result == ' ' )
    {
        ++result;
    }

    // Remove spaces from the end of the string:
    string::const_iterator resultEnd = end;
    while( resultEnd != result && *(resultEnd-1) == ' ' )
    {
        --resultEnd;
    }

    return resultEnd;
}

// ----------------------------------------------------------------------------------------------------------

/**
 * AreParametersCompatible
 * Checks if two function parameters are compatible with each other. 
 * Allows added const qualifiers in current version of the parameter.
 * This function loops through parameters, that are splitted into elements,
 * and compares them element by element. If the elements differ and current 
 * platform's element is 'const' qualifier, skip the current platform's element
 * and compare next one to the baseline platform's element. 
 * @param basePar Reference to the parameter object representing the parameter
 *        of the baseline platform's function.
 * @param currPar Reference to the parameter object representing the parameter
 *        of the current platform's function.
 * @param compareFlags Comparison policy flags that should be used when comparing
 *        the parameters. 
 * @return bool value indicating if the two parameters are backward binary compatible.
 */
bool AreParametersCompatible(   const FunctionParameter& basePar,
                                const FunctionParameter& currPar,
                                unsigned int compareFlags )
{      
    const string cvQualConst("const"); // const qualifier
    const string ptrStr("*"); // pointer
    const string refStr("&"); // reference
    if( basePar.size() > currPar.size() )
    {
        // Something has been removed:
        return false;
    }

    vector<ParameterElement>::const_iterator baseElem = basePar.begin();
    vector<ParameterElement>::const_iterator currElem = currPar.begin();
    while( baseElem != basePar.end() && currElem != currPar.end() )
    {
        if( baseElem->Value().compare(currElem->Value()) != 0 )
        {
            if( currElem->Value().compare(cvQualConst) == 0 &&
                (compareFlags & COMPARE_FLAG_ALLOW_CONST_ADDITION) )
            {       
                // COMPARE_FLAG_ALLOW_CONST_ADDITION used, so it is acceptable that
                // 'const' qualifier has been added to current parameter. So let's skip
                // the 'const' qualifier -element and compare next elements to see if 
                // the parameter is otherwise compatible.
                ++currElem;             
                continue;
            }
            else
            {
                return false; // Parameter elements do not match
            }
        }
        
        // Now, lets take the sub-parameters (if any) and call this function recursively:
        const ParameterList* baseSubPars = baseElem->SubParameters();
        const ParameterList* currSubPars = currElem->SubParameters();
        if( baseSubPars != 0 &&  currSubPars != 0 )
        {
            if( baseSubPars->size() != currSubPars->size() )
                return false; // Number of sub-parameters do not match

            for( unsigned int subI = 0; subI < baseSubPars->size(); ++subI )
            {
                // Here we are dealing with sub-parameters (e.g parameter list of a function 
                // pointer parameter), and no 'const addition' flags etc. are used anymore.
                if( AreParametersCompatible( baseSubPars->at(subI), currSubPars->at(subI)) == false )
                    return false;
            }
        }
        else if( baseSubPars != currSubPars )
        {
            return false; // Other one's subparameter list pointer is NULL
        }

        ++baseElem;
        ++currElem;
    }

    // Check for the const pointer. Actually in this case the 'const' qualifier
    // is left out from the mangled/demangled signature, but just to be sure...
    // For example: 'int *' changed to 'int * const'
    if( baseElem == basePar.end() && currElem != currPar.end() )
    {
        if( currElem->Value().compare(cvQualConst) == 0 )
        {            
            ++currElem;
        }
    }

    // Check that all the elements have been "consumed":
    return baseElem == basePar.end() && currElem == currPar.end();
}

// ----------------------------------------------------------------------------------------------------------
