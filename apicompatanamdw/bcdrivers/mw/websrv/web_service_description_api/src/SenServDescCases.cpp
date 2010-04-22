/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/



// INCLUDE FILES
#include <e32math.h>
#include <flogger.h>
#include "SenServDescBCTest.h"


// EXTERNAL DATA STRUCTURES
//extern  ?external_data;

// EXTERNAL FUNCTION PROTOTYPES  
//extern ?external_function( ?arg_type,?arg_type );

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
#define LOCAL_ASSERT(expression)	{if(!(expression)){return KErrArgument;}}

//#define ?macro ?macro_def

// LOCAL CONSTANTS AND MACROS
//const ?type ?constant_var = ?constant;
//#define ?macro_name ?macro_def

// MODULE DATA STRUCTURES
//enum ?declaration
//typedef ?declaration

// LOCAL FUNCTION PROTOTYPES
//?type ?function_name( ?arg_type, ?arg_type );

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;

// ============================= LOCAL FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// ?function_name ?description.
// ?description
// Returns: ?value_1: ?description
//          ?value_n: ?description_line1
//                    ?description_line2
// -----------------------------------------------------------------------------
//
/*
?type ?function_name(
    ?arg_type arg,  // ?description
    ?arg_type arg)  // ?description
    {

    ?code  // ?comment

    // ?comment
    ?code
    }
*/

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CSenServDesc::Case
// Returns a test case by number.
//
// This function contains an array of all available test cases 
// i.e pair of case name and test function. If case specified by parameter
// aCaseNumber is found from array, then that item is returned.
// 
// The reason for this rather complicated function is to specify all the
// test cases only in one place. It is not necessary to understand how
// function pointers to class member functions works when adding new test
// cases. See function body for instructions how to add new test case.
// -----------------------------------------------------------------------------
//
const TCaseInfo CSenServDesc::Case ( 
    const TInt aCaseNumber ) const 
     {

    /**
    * To add new test cases, implement new test case function and add new 
    * line to KCases array specify the name of the case and the function 
    * doing the test case
    * In practice, do following
    * 1) Make copy of existing test case function and change its name
    *    and functionality. Note that the function must be added to 
    *    SenServDesc.cpp file and to SenServDesc.h 
    *    header file.
    *
    * 2) Add entry to following KCases array either by using:
    *
    * 2.1: FUNCENTRY or ENTRY macro
    * ENTRY macro takes two parameters: test case name and test case 
    * function name.
    *
    * FUNCENTRY macro takes only test case function name as a parameter and
    * uses that as a test case name and test case function name.
    *
    * Or
    *
    * 2.2: OOM_FUNCENTRY or OOM_ENTRY macro. Note that these macros are used
    * only with OOM (Out-Of-Memory) testing!
    *
    * OOM_ENTRY macro takes five parameters: test case name, test case 
    * function name, TBool which specifies is method supposed to be run using
    * OOM conditions, TInt value for first heap memory allocation failure and 
    * TInt value for last heap memory allocation failure.
    * 
    * OOM_FUNCENTRY macro takes test case function name as a parameter and uses
    * that as a test case name, TBool which specifies is method supposed to be
    * run using OOM conditions, TInt value for first heap memory allocation 
    * failure and TInt value for last heap memory allocation failure. 
    */ 

    static TCaseInfoInternal const KCases[] =
        {
        // To add new test cases, add new items to this array
        
        // NOTE: When compiled to GCCE, there must be Classname::
        // declaration in front of the method name, e.g. 
        // CSenServDesc::PrintTest. Otherwise the compiler
        // gives errors.
        
  //      FUNCENTRY( CSenServDesc::PrintTest ),
  //    ENTRY( "Loop test", CSenServDesc::LoopTest ),
		ENTRY("NewL - CSenCredential",  CSenServDesc::MT_CSenCredential_NewLL),
		ENTRY("NewLC - CSenCredential",  CSenServDesc::MT_CSenCredential_NewLCL),
		ENTRY("NewL - CSenCredential baseElement",  CSenServDesc::MT_CSenCredential_NewL_1L),
		ENTRY("NewLC - CSenCredential baseElement",  CSenServDesc::MT_CSenCredential_NewLC_1L),
		ENTRY("NewL - CSenCredential copy",  CSenServDesc::MT_CSenCredential_NewL_2L),
		ENTRY("NewLC - CSenCredential copy",  CSenServDesc::MT_CSenCredential_NewLC_2L),
		ENTRY("NewL - CSenFacet",  CSenServDesc::MT_CSenFacet_NewLL),
		ENTRY("NewL - CSenFacet copy",  CSenServDesc::MT_CSenFacet_NewL_1L),
		ENTRY("NewL - CSenFacet attribute",  CSenServDesc::MT_CSenFacet_NewL_2L),
		ENTRY("SetNameL - CSenFacet",  CSenServDesc::MT_CSenFacet_SetNameLL),
		ENTRY("SetTypeL - CSenFacet",  CSenServDesc::MT_CSenFacet_SetTypeLL),
		ENTRY("SetValueL - CSenFacet",  CSenServDesc::MT_CSenFacet_SetValueLL),
		ENTRY("Name - CSenFacet",  CSenServDesc::MT_CSenFacet_NameL),
		ENTRY("Type - CSenFacet",  CSenServDesc::MT_CSenFacet_TypeL),
		ENTRY("Value - CSenFacet",  CSenServDesc::MT_CSenFacet_ValueL),
		ENTRY("NewLC - Endpoint",  CSenServDesc::MT_CSenIdentityProvider_NewLCL),
		ENTRY("NewL - Enpoint + Contract",  CSenServDesc::MT_CSenIdentityProvider_NewL_1L),
		ENTRY("NewLC - Enpoint + Contract",  CSenServDesc::MT_CSenIdentityProvider_NewLC_1L),
		ENTRY("NewL - Provider + Contract+ Endpoint",  CSenServDesc::MT_CSenIdentityProvider_NewL_2L),
		ENTRY("NewLC - Provider + Contract+ Endpoint",  CSenServDesc::MT_CSenIdentityProvider_NewLC_2L),
		ENTRY("NewL - ServiceID + Provider + Contract+ Endpoint",  CSenServDesc::MT_CSenIdentityProvider_NewL_3L),
		ENTRY("NewLC - ServiceID + Provider + Contract+ Endpoint",  CSenServDesc::MT_CSenIdentityProvider_NewLC_3L),
		ENTRY("AuthzID - IdentityProvider",  CSenServDesc::MT_CSenIdentityProvider_AuthzIDL),
		ENTRY("AdvisoryAuthnID - IdentityProvider",  CSenServDesc::MT_CSenIdentityProvider_AdvisoryAuthnIDL),
		ENTRY("ProviderID - IdentityProvider",  CSenServDesc::MT_CSenIdentityProvider_ProviderIDL),
		ENTRY("Password - IdentityProvider",  CSenServDesc::MT_CSenIdentityProvider_PasswordL),
		ENTRY("IMEI - IdentityProvider",  CSenServDesc::MT_CSenIdentityProvider_IMEIL),
		ENTRY("UserName - IdentityProvider",  CSenServDesc::MT_CSenIdentityProvider_UserNameL),
		ENTRY("SetProviderID - IdentityProvider",  CSenServDesc::MT_CSenIdentityProvider_SetProviderIDL),
		ENTRY("SetServiceID - IdentityProvider",  CSenServDesc::MT_CSenIdentityProvider_SetServiceIDL),
		ENTRY("HttpCredentialsL - IdentityProvider",  CSenServDesc::MT_CSenIdentityProvider_HttpCredentialsLL),
		ENTRY("NewElementName - IdentityProvider",  CSenServDesc::MT_CSenIdentityProvider_NewElementNameL),

		ENTRY("NewL - CSenIdentityProviderIdArray8",  CSenServDesc::MT_CSenIdentityProviderIdArray8_NewLL),
		ENTRY("NewLC - CSenIdentityProviderIdArray8",  CSenServDesc::MT_CSenIdentityProviderIdArray8_NewLCL),
		ENTRY("NewL - CSenIdentityProviderIdArray8",  CSenServDesc::MT_CSenIdentityProviderIdArray8_NewL_1L),
		ENTRY("NewLC - CSenIdentityProviderIdArray8",  CSenServDesc::MT_CSenIdentityProviderIdArray8_NewLC_1L),
		ENTRY("IsStrict - CSenIdentityProviderIdArray8",  CSenServDesc::MT_CSenIdentityProviderIdArray8_IsStrictL),
		ENTRY("SetStrict - CSenIdentityProviderIdArray8",  CSenServDesc::MT_CSenIdentityProviderIdArray8_SetStrictL),
		ENTRY("NewL - CSenServicePattern",  CSenServDesc::MT_CSenServicePattern_NewLL),
		ENTRY("NewLC - CSenServicePattern",  CSenServDesc::MT_CSenServicePattern_NewLCL),
		ENTRY("NewL - CSenServicePattern",  CSenServDesc::MT_CSenServicePattern_NewL_1L),
		ENTRY("NewLC - CSenServicePattern",  CSenServDesc::MT_CSenServicePattern_NewLC_1L),
		ENTRY("NewL - CSenServicePattern",  CSenServDesc::MT_CSenServicePattern_NewL_2L),
		ENTRY("NewLC - CSenServicePattern",  CSenServDesc::MT_CSenServicePattern_NewLC_2L),
		ENTRY("SetConsumerIapIdL - CSenServicePattern",  CSenServDesc::MT_CSenServicePattern_SetConsumerIapIdLL),
		ENTRY("ConsumerIapId - CSenServicePattern",  CSenServDesc::MT_CSenServicePattern_ConsumerIapIdL),
		ENTRY("SetConsumerSnapId - CSenServicePattern",  CSenServDesc::MT_CSenServicePattern_SetConsumerSnapIdLL),
		ENTRY("ConsumerSnapId - CSenServicePattern",  CSenServDesc::MT_CSenServicePattern_ConsumerSnapIdL),
		ENTRY("SetConsumerIdentityProviderIdsL - CSenServicePattern",  CSenServDesc::MT_CSenServicePattern_SetConsumerIdentityProviderIdsLL),
		ENTRY("AddConsumerIdentityProviderIdL - CSenServicePattern",  CSenServDesc::MT_CSenServicePattern_AddConsumerIdentityProviderIdLL),
		ENTRY("ConsumerIdentityProviderIds8L - CSenServicePattern",  CSenServDesc::MT_CSenServicePattern_ConsumerIdentityProviderIds8LL),
		ENTRY("AcceptsConsumerPolicy - CSenServicePattern",  CSenServDesc::MT_CSenServicePattern_AcceptsConsumerPolicyL),
		ENTRY("RebuildFromConsumerPolicy - CSenServicePattern",  CSenServDesc::MT_CSenServicePattern_RebuildFromConsumerPolicyL),
		ENTRY("NewL - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_NewLL),
		ENTRY("NewLC - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_NewLCL),
		ENTRY("NewL - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_NewL_1L),
		ENTRY("NewLC - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_NewLC_1L),
		ENTRY("NewL - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_NewL_2L),
		ENTRY("NewLC - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_NewLC_2L),
		ENTRY("SetFrameworkIdL - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_SetFrameworkIdLL),
		ENTRY("NewElementName - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_NewElementNameL),
		ENTRY("SetIapIdL - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_SetIapIdLL),
		ENTRY("IapId - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_IapIdL),
		ENTRY("SetSnapIdL - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_SetSnapIdLL),
		ENTRY("SnapId - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_SnapIdL),
		ENTRY("SetIdentityProviderIdsL - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_SetIdentityProviderIdsLL),
		ENTRY("AddIdentityProviderIdL - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_AddIdentityProviderIdLL),
		ENTRY("RebuildFrom - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_RebuildFromL),
		ENTRY("IdentityProviderIds8L - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_IdentityProviderIds8LL),
		ENTRY("Accepts - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_AcceptsL),
		ENTRY("DescriptionClassType - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_DescriptionClassTypeL),
		ENTRY("Contract - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_ContractL),
		ENTRY("HasFacetL - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_HasFacetLL),
		ENTRY("FacetValue - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_FacetValueL),
		ENTRY("AddFacetL - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_AddFacetLL),
		ENTRY("SetFacetL - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_SetFacetLL),
		ENTRY("RemoveFacet - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_RemoveFacetL),
		ENTRY("FacetsL - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_FacetsLL),
		ENTRY("ScoreMatchL - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_ScoreMatchLL),
		ENTRY("Endpoint - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_EndpointL),
		ENTRY("FrameworkId - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_FrameworkIdL),
		ENTRY("FrameworkVersion - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_FrameworkVersionL),
		ENTRY("SetContractL - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_SetContractLL),
		ENTRY("SetEndPointL - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_SetEndPointLL),
		ENTRY("SetAttributesL - CSenXmlServiceDescription",  CSenServDesc::MT_CSenXmlServiceDescription_SetAttributesLL),
		ENTRY("TransportPropertiesL - CSenXmlServiceDescription ", CSenServDesc::MT_CSenXmlServiceDescription_TransportPropertiesL),
		ENTRY("SetTransportPropertiesL - CSenXmlServiceDescription ", CSenServDesc::MT_CSenXmlServiceDescription_SetTransportPropertiesL),

        // Example how to use OOM functionality
        //OOM_ENTRY( "Loop test with OOM", CSenServDesc::LoopTest, ETrue, 2, 3),
        //OOM_FUNCENTRY( CSenServDesc::PrintTest, ETrue, 1, 3 ),
        };

    // Verify that case number is valid
    if( (TUint) aCaseNumber >= sizeof( KCases ) / 
                               sizeof( TCaseInfoInternal ) )
        {
        // Invalid case, construct empty object
        TCaseInfo null( (const TText*) L"" );
        null.iMethod = NULL;
        null.iIsOOMTest = EFalse;
        null.iFirstMemoryAllocation = 0;
        null.iLastMemoryAllocation = 0;
        return null;
        } 

    // Construct TCaseInfo object and return it
    TCaseInfo tmp ( KCases[ aCaseNumber ].iCaseName );
    tmp.iMethod = KCases[ aCaseNumber ].iMethod;
    tmp.iIsOOMTest = KCases[ aCaseNumber ].iIsOOMTest;
    tmp.iFirstMemoryAllocation = KCases[ aCaseNumber ].iFirstMemoryAllocation;
    tmp.iLastMemoryAllocation = KCases[ aCaseNumber ].iLastMemoryAllocation;
    return tmp;

    }

//  METHODS



void CSenServDesc::SetupL(  )
    {

    } 

void CSenServDesc::Teardown(  )
    {

    }
TPtr16 CSenServDesc::ConvertToPtr16LC(CSenBaseFragment &fragment){
    HBufC16* xmlBuffer = fragment.AsElement().AsXmlUnicodeL();//Parent()->
    CleanupStack::PushL( xmlBuffer );
    TPtr16 ptr = xmlBuffer->Des();
    if (ptr.Length() > 0){
        RDebug::Print( _L( "WSModTester: xmlBuffer [%S]"),&ptr);
    }
    else
        RDebug::Print( _L( "WSModTester: xmlBuffer empty"));
    return ptr;
}
TPtr16 CSenServDesc::ConvertToPtr16LC(CSenBaseElement &element){
    HBufC16* xmlBuffer = element.AsXmlUnicodeL();//Parent()->
    CleanupStack::PushL( xmlBuffer );
    TPtr16 ptr = xmlBuffer->Des();
    if (ptr.Length() > 0){
        RDebug::Print( _L( "WSModTester: xmlBuffer [%S]"),&ptr);
    }
    else
        RDebug::Print( _L( "WSModTester: xmlBuffer empty"));
    return ptr;
}

TInt CSenServDesc::MT_CSenCredential_NewLL( TTestResult& aResult )
    {
    SetupL();
    
    RAttributeArray attributeArray;
    CSenCredential* senCredential = CSenCredential::NewL(KText, KText, KText, attributeArray);
    TL(senCredential != (CSenCredential*)NULL);
  
    _LIT16(KRef, "<text xmlns=\"text\"/>");
    //checking xml
    TL(ConvertToPtr16LC(*senCredential) == KRef);
    
    CleanupStack::PopAndDestroy();//Ptr
    
    __ASSERT_ALWAYS_NO_LEAVE(delete senCredential);
   
    senCredential = NULL;

	{TRAPD(err, CSenCredential::NewL(KText, KNullDesC8, KText, attributeArray));if(err != (KErrSenZeroLengthDescriptor))return err;}
 
	{TRAPD(err, CSenCredential::NewL(KText, KText, KNullDesC8, attributeArray));if(err != (KErrSenZeroLengthDescriptor))return err;}

 	{TRAPD(err, CSenCredential::NewL(KText, KNullDesC8, KNullDesC8, attributeArray));if(err != (KErrSenZeroLengthDescriptor))return err;}
   
 	{TRAPD(err, CSenCredential::NewL(KText, KXmlSpecific, KText, attributeArray));if(err != (KErrSenInvalidCharacters))return err;}

 	{TRAPD(err, CSenCredential::NewL(KText, KText, KXmlSpecific, attributeArray));if(err != (KErrSenInvalidCharacters))return err;}

 	{TRAPD(err, CSenCredential::NewL(KText, KXmlSpecific, KXmlSpecific, attributeArray));if(err != (KErrSenInvalidCharacters))return err;}

    attributeArray.Reset();
    attributeArray.Close();
    
    Teardown();
    return KErrNone;
    }




TInt CSenServDesc::MT_CSenCredential_NewLCL( TTestResult& aResult )
    {
    SetupL();
    
    RAttributeArray attributeArray;
    CSenCredential* senCredential = CSenCredential::NewLC(KText, KText, KText, attributeArray);
    TL(senCredential != (CSenCredential*)NULL);
  
    //checking xml
    _LIT16(KRef, "<text xmlns=\"text\"/>");
    TL(ConvertToPtr16LC(*senCredential) == KRef);
    CleanupStack::PopAndDestroy();//Ptr
    
    CleanupStack::Pop();
    __ASSERT_ALWAYS_NO_LEAVE(delete senCredential);
    senCredential = NULL;

	  {TRAPD(err, CSenCredential::NewLC(KText, KNullDesC8, KText, attributeArray));if(err != (KErrSenZeroLengthDescriptor))return err;}

 		{TRAPD(err, CSenCredential::NewLC(KText, KText, KNullDesC8, attributeArray));if(err != (KErrSenZeroLengthDescriptor))return err;}

 		{TRAPD(err, CSenCredential::NewLC(KText, KNullDesC8, KNullDesC8, attributeArray));if(err != (KErrSenZeroLengthDescriptor))return err;}

	 	{TRAPD(err, CSenCredential::NewLC(KText, KXmlSpecific, KText, attributeArray));if(err != (KErrSenInvalidCharacters))return err;}

	 	{TRAPD(err, CSenCredential::NewLC(KText, KText, KXmlSpecific, attributeArray));if(err != (KErrSenInvalidCharacters))return err;}

	 	{TRAPD(err, CSenCredential::NewLC(KText, KXmlSpecific, KXmlSpecific, attributeArray));if(err != (KErrSenInvalidCharacters))return err;}

    attributeArray.Reset();
    attributeArray.Close();
     Teardown();
    return KErrNone;
   }


TInt CSenServDesc::MT_CSenCredential_NewL_1L( TTestResult& aResult )
    {
    SetupL();
    
    RAttributeArray attributeArray;
    CSenBaseElement* senBaseElement = CSenBaseElement::NewL(KText);
    CSenCredential* senCredential = CSenCredential::NewL(KText, KText, KText, attributeArray, *senBaseElement);
    TL(senCredential != (CSenCredential*)NULL);

    //checking xml, parent we will not see so ref the same as previous NewL ctr 
    _LIT16(KRef, "<text xmlns=\"text\"/>");
    TL(ConvertToPtr16LC(*senCredential) == KRef);

    CleanupStack::PopAndDestroy();//Ptr
    
    __ASSERT_ALWAYS_NO_LEAVE(delete senCredential);
    senCredential = NULL;
    delete senBaseElement;
    senBaseElement = NULL;

    senBaseElement = CSenBaseElement::NewL(KText);
	 	{TRAPD(err, CSenCredential::NewL(KText, KNullDesC8, KText, attributeArray, *senBaseElement));if(err != (KErrSenZeroLengthDescriptor))return err;}

	 	{TRAPD(err, CSenCredential::NewL(KText, KText, KNullDesC8, attributeArray, *senBaseElement));if(err != (KErrSenZeroLengthDescriptor))return err;}

	 	{TRAPD(err, CSenCredential::NewL(KText, KNullDesC8, KNullDesC8, attributeArray, *senBaseElement));if(err != (KErrSenZeroLengthDescriptor))return err;}

	 	{TRAPD(err, CSenCredential::NewL(KText, KXmlSpecific, KText, attributeArray, *senBaseElement));if(err != (KErrSenInvalidCharacters))return err;}

	 	{TRAPD(err, CSenCredential::NewL(KText, KText, KXmlSpecific, attributeArray, *senBaseElement));if(err != (KErrSenInvalidCharacters))return err;}

	 	{TRAPD(err, CSenCredential::NewL(KText, KXmlSpecific, KXmlSpecific, attributeArray, *senBaseElement));if(err != (KErrSenInvalidCharacters))return err;}

    delete senBaseElement;
    senBaseElement = NULL;
    attributeArray.Reset();
    attributeArray.Close();
    Teardown();
    return KErrNone;
   }

TInt CSenServDesc::MT_CSenCredential_NewLC_1L( TTestResult& aResult )
    {
    SetupL();
    
    RAttributeArray attributeArray;
    CSenBaseElement* senBaseElement = CSenBaseElement::NewL(KText);
    CSenCredential* senCredential = CSenCredential::NewLC(KText, KText, KText, attributeArray, *senBaseElement);
    TL(senCredential != (CSenCredential*)NULL);
   
    //checking xml, parent we will not see so ref the same as previous Newl ctr
    _LIT16(KRef, "<text xmlns=\"text\"/>");
    TL(ConvertToPtr16LC(*senCredential)== KRef);

    CleanupStack::PopAndDestroy();//Ptr
    
    CleanupStack::Pop();
    __ASSERT_ALWAYS_NO_LEAVE(delete senCredential);
    senCredential = NULL;
    delete senBaseElement;
    senBaseElement = NULL;

    senBaseElement = CSenBaseElement::NewL(KText);
	 	{TRAPD(err, CSenCredential::NewLC(KText, KNullDesC8, KText, attributeArray, *senBaseElement));if(err != (KErrSenZeroLengthDescriptor))return err;}

	 	{TRAPD(err, CSenCredential::NewLC(KText, KText, KNullDesC8, attributeArray, *senBaseElement));if(err != (KErrSenZeroLengthDescriptor))return err;}

	 	{TRAPD(err, CSenCredential::NewLC(KText, KNullDesC8, KNullDesC8, attributeArray, *senBaseElement));if(err != (KErrSenZeroLengthDescriptor))return err;}

	 	{TRAPD(err, CSenCredential::NewLC(KText, KXmlSpecific, KText, attributeArray, *senBaseElement));if(err != (KErrSenInvalidCharacters))return err;}

	 	{TRAPD(err, CSenCredential::NewLC(KText, KText, KXmlSpecific, attributeArray, *senBaseElement));if(err != (KErrSenInvalidCharacters))return err;}

	 	{TRAPD(err, CSenCredential::NewLC(KText, KXmlSpecific, KXmlSpecific, attributeArray, *senBaseElement));if(err != (KErrSenInvalidCharacters))return err;}

    delete senBaseElement;
    senBaseElement = NULL;
    attributeArray.Reset();
    attributeArray.Close();
    Teardown();
    return KErrNone;
   }

TInt CSenServDesc::MT_CSenCredential_NewL_2L( TTestResult& aResult )
    {
    SetupL();
    
    RAttributeArray attributeArray;
    CSenCredential* senCredential, *orgSenCredential = CSenCredential::NewL(KText, KText, KText, attributeArray);
    
    senCredential = CSenCredential::NewL(*orgSenCredential);
    
    //checking xml
    _LIT16(KRef, "<text xmlns=\"text\"/>");
    TL(ConvertToPtr16LC(*senCredential) == KRef);
    CleanupStack::PopAndDestroy();//Ptr
    
    TL(senCredential != (CSenCredential*)NULL);
    
   __ASSERT_ALWAYS_NO_LEAVE(delete senCredential);
    senCredential = NULL;
    delete orgSenCredential;
    orgSenCredential = NULL;
    attributeArray.Reset();
    attributeArray.Close();
    Teardown();
    return KErrNone;
   }

TInt CSenServDesc::MT_CSenCredential_NewLC_2L( TTestResult& aResult )
    {
    SetupL();
    
    RAttributeArray attributeArray;
    CSenCredential* senCredential, *orgSenCredential = CSenCredential::NewL(KText, KText, KText, attributeArray);
    
    senCredential = CSenCredential::NewLC(*orgSenCredential);
    TL(senCredential != (CSenCredential*)NULL);
    
    //checking xml
    _LIT16(KRef, "<text xmlns=\"text\"/>");
    TL(ConvertToPtr16LC(*senCredential) == KRef);
    
    CleanupStack::PopAndDestroy();//Ptr
    
    CleanupStack::Pop();
    __ASSERT_ALWAYS_NO_LEAVE(delete senCredential);
    senCredential = NULL;
    delete orgSenCredential;
    orgSenCredential = NULL;
    attributeArray.Reset();
    attributeArray.Close();
    Teardown();
    return KErrNone;
   }

TInt CSenServDesc::MT_CSenFacet_NewLL( TTestResult& aResult )
    {
    SetupL();
    
    RAttributeArray attributeArray;
    CSenFacet* senFacet = CSenFacet::NewL();
    TL(senFacet != (CSenFacet*)NULL);

    //checking xml
    _LIT16(KRef, "<Facet/>");
    TL(ConvertToPtr16LC(*senFacet) == KRef);

    CleanupStack::PopAndDestroy();//Ptr
    
    __ASSERT_ALWAYS_NO_LEAVE(delete senFacet);
    senFacet = NULL;
    attributeArray.Reset();
    attributeArray.Close();
    Teardown();
    return KErrNone;
   }

TInt CSenServDesc::MT_CSenFacet_NewL_1L(TTestResult& aResult)
    {
    SetupL();
    
    CSenFacet* senFacet, *senFacetOrg = CSenFacet::NewL();
    senFacet = CSenFacet::NewL(*senFacetOrg);
    TL(senFacet != (CSenFacet*)NULL);

    //checking xml
    _LIT16(KRef, "<Facet/>");
    TL(ConvertToPtr16LC(*senFacet) == KRef);
    
    CleanupStack::PopAndDestroy();//Ptr
    
    __ASSERT_ALWAYS_NO_LEAVE(delete senFacet);
    senFacet = NULL;
    delete senFacetOrg;
    senFacetOrg = NULL;
    Teardown();
    return KErrNone;
   }

TInt CSenServDesc::MT_CSenFacet_NewL_2L( TTestResult& aResult )
    {
    SetupL();
    
    RAttributeArray attributeArray;
    CSenFacet* senFacet = CSenFacet::NewL(KText, KText, KText, attributeArray);
    TL(senFacet != (CSenFacet*)NULL);

    //checking xml
    _LIT16(KRef, "<text xmlns=\"text\"/>");
    TL(ConvertToPtr16LC(*senFacet) == KRef);
    
    CleanupStack::PopAndDestroy();//Ptr
    
    __ASSERT_ALWAYS_NO_LEAVE(delete senFacet);
    senFacet = NULL;

	 	{TRAPD(err, CSenFacet::NewL(KText, KNullDesC8, KText, attributeArray));if(err != (KErrSenZeroLengthDescriptor))return err;}

	 	{TRAPD(err, CSenFacet::NewL(KText, KText, KNullDesC8, attributeArray));if(err != (KErrSenZeroLengthDescriptor))return err;}

	 	{TRAPD(err, CSenFacet::NewL(KText, KNullDesC8, KNullDesC8, attributeArray));if(err != (KErrSenZeroLengthDescriptor))return err;}

	 	{TRAPD(err, CSenFacet::NewL(KText, KXmlSpecific, KText, attributeArray));if(err != (KErrSenInvalidCharacters))return err;}

	 	{TRAPD(err, CSenFacet::NewL(KText, KText, KXmlSpecific, attributeArray));if(err != (KErrSenInvalidCharacters))return err;}

	 	{TRAPD(err, CSenFacet::NewL(KText, KXmlSpecific, KXmlSpecific, attributeArray));if(err != (KErrSenInvalidCharacters))return err;}

    attributeArray.Reset();
    attributeArray.Close();
    Teardown();
    return KErrNone;
   }

TInt CSenServDesc::MT_CSenFacet_SetNameLL( TTestResult& aResult )
    {
    SetupL();
    
    CSenFacet* senFacet = CSenFacet::NewL();
    if(!(senFacet->Name() == KNullDesC8))return KErrArgument;
    
    senFacet->SetNameL(KText);
    if(!(senFacet->Name() == KText))return KErrArgument;
    
    //checking xml
    _LIT16(KRef, "<Facet name=\"text\"/>");
    TL(ConvertToPtr16LC(*senFacet) == KRef);
    
    CleanupStack::PopAndDestroy();//Ptr
    
     if(!(senFacet->Name() == KText))return KErrArgument;

   __ASSERT_ALWAYS_NO_LEAVE(delete senFacet);
    senFacet = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenFacet_SetTypeLL( TTestResult& aResult )
    {
    SetupL();
    
    CSenFacet* senFacet = CSenFacet::NewL();
    if(!(senFacet->Type() == KNullDesC8))return KErrArgument;

    senFacet->SetTypeL(KText);
    if(!(senFacet->Type() == KText))return KErrArgument;
   
    //checking xml
    _LIT16(KRef, "<Facet type=\"text\"/>");
    TL(ConvertToPtr16LC(*senFacet) == KRef);
    
    CleanupStack::PopAndDestroy();//Ptr
    
    if(!(senFacet->Type() == KText))return KErrArgument;

    delete senFacet;
    senFacet = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenFacet_SetValueLL( TTestResult& aResult )
    {
    SetupL();
    
    CSenFacet* senFacet = CSenFacet::NewL();
    if(!(senFacet->Value() == KNullDesC8))return KErrArgument;

    senFacet->SetValueL(KText);
    if(!(senFacet->Value() == KText))return KErrArgument;

    
    //checking xml
    _LIT16(KRef, "<Facet>text</Facet>");
    TL(ConvertToPtr16LC(*senFacet) == KRef);
    
    CleanupStack::PopAndDestroy();//Ptr
    
    if(!(senFacet->Value() == KText))return KErrArgument;

    delete senFacet;
    senFacet = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenFacet_NameL( TTestResult& aResult )
    {
    return MT_CSenFacet_SetNameLL(aResult);
    }

TInt CSenServDesc::MT_CSenFacet_TypeL( TTestResult& aResult )
    {
    return MT_CSenFacet_SetTypeLL(aResult);
    }

TInt CSenServDesc::MT_CSenFacet_ValueL( TTestResult& aResult )
    {
    return MT_CSenFacet_SetValueLL(aResult);
    }

TInt CSenServDesc::MT_CSenIdentityProvider_NewLCL( TTestResult& aResult )
    {
    SetupL();
    
    CSenIdentityProvider* idProvider = CSenIdentityProvider::NewLC(KText);
    TL(idProvider != (CSenIdentityProvider*)NULL);

    //checking xml
    //_LIT16(KRef, "<IdentityProvider framework=\"ID-WSF\"><Endpoint>text</Endpoint><Contract>urn:liberty:as:2004-04</Contract><ProviderPolicy/><ServicePolicy/></IdentityProvider>");

    //TL(ConvertToPtr16LC(*idProvider) == KRef);
    
    //CleanupStack::PopAndDestroy();//Ptr
    
    CleanupStack::Pop();
    __ASSERT_ALWAYS_NO_LEAVE(delete idProvider);
    idProvider = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenIdentityProvider_NewL_1L( TTestResult& aResult )
    {
    SetupL();
    
    CSenIdentityProvider* idProvider = CSenIdentityProvider::NewL(KText, KText);
    TL(idProvider != (CSenIdentityProvider*)NULL);

    //checking xml
    //_LIT16(KRef, "<IdentityProvider><Endpoint>text</Endpoint><Contract>text</Contract><ProviderPolicy/><ServicePolicy/></IdentityProvider>");
    //TL(ConvertToPtr16LC(*idProvider) == KRef);
    
    //CleanupStack::PopAndDestroy();//Ptr
    
    __ASSERT_ALWAYS_NO_LEAVE(delete idProvider);
    idProvider = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenIdentityProvider_NewLC_1L( TTestResult& aResult )
    {
    SetupL();
    
    CSenIdentityProvider* idProvider = CSenIdentityProvider::NewLC(KText, KText);
    TL(idProvider != (CSenIdentityProvider*)NULL);

    //checking xml
    //_LIT16(KRef, "<IdentityProvider><Endpoint>text</Endpoint><Contract>text</Contract><ProviderPolicy/><ServicePolicy/></IdentityProvider>");
    //TL(ConvertToPtr16LC(*idProvider) == KRef);
    
    //CleanupStack::PopAndDestroy();//Ptr
    CleanupStack::Pop();
    __ASSERT_ALWAYS_NO_LEAVE(delete idProvider);
    idProvider = NULL;    
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenIdentityProvider_NewL_2L( TTestResult& aResult )
    {
    SetupL();
    
    CSenIdentityProvider* idProvider = CSenIdentityProvider::NewL(KText, KText, KText);
    TL(idProvider != (CSenIdentityProvider*)NULL);

    //checking xml
    //_LIT16(KRef, "<IdentityProvider><Endpoint>text</Endpoint><Contract>text</Contract><ProviderPolicy/><ServicePolicy/><ProviderID>text</ProviderID></IdentityProvider>");
    //TL(ConvertToPtr16LC(*idProvider) == KRef);
    
    //CleanupStack::PopAndDestroy();//Ptr
    __ASSERT_ALWAYS_NO_LEAVE(delete idProvider);
    idProvider = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenIdentityProvider_NewLC_2L( TTestResult& aResult )
    {
    SetupL();
    
    CSenIdentityProvider* idProvider = CSenIdentityProvider::NewLC(KText, KText, KText);
    TL(idProvider != (CSenIdentityProvider*)NULL);

    //checking xml
    //_LIT16(KRef, "<IdentityProvider><Endpoint>text</Endpoint><Contract>text</Contract><ProviderPolicy/><ServicePolicy/><ProviderID>text</ProviderID></IdentityProvider>");
    //TL(ConvertToPtr16LC(*idProvider) == KRef);
    
    //CleanupStack::PopAndDestroy();//Ptr
    CleanupStack::Pop();
    __ASSERT_ALWAYS_NO_LEAVE(delete idProvider);
    idProvider = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenIdentityProvider_NewL_3L( TTestResult& aResult )
    {
    SetupL();
    
    CSenIdentityProvider* idProvider = CSenIdentityProvider::NewL(KText, KText, KText, KText);
    TL(idProvider != (CSenIdentityProvider*)NULL);

    //checking xml
    //_LIT16(KRef, "<IdentityProvider><Endpoint>text</Endpoint><Contract>text</Contract><ProviderPolicy/><ServicePolicy/><ProviderID>text</ProviderID><ServiceID>text</ServiceID></IdentityProvider>");
    //TL(ConvertToPtr16LC(*idProvider) == KRef);
    
    //CleanupStack::PopAndDestroy();//Ptr
    __ASSERT_ALWAYS_NO_LEAVE(delete idProvider);
    idProvider = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenIdentityProvider_NewLC_3L( TTestResult& aResult )
    {
    SetupL();
    
    CSenIdentityProvider* idProvider = CSenIdentityProvider::NewLC(KText, KText, KText, KText);
    TL(idProvider != (CSenIdentityProvider*)NULL);

    //checking xml
    //_LIT16(KRef, "<IdentityProvider><Endpoint>text</Endpoint><Contract>text</Contract><ProviderPolicy/><ServicePolicy/><ProviderID>text</ProviderID><ServiceID>text</ServiceID></IdentityProvider>");
    //TL(ConvertToPtr16LC(*idProvider) == KRef);
    
    //CleanupStack::PopAndDestroy();//Ptr
    CleanupStack::Pop();
    __ASSERT_ALWAYS_NO_LEAVE(delete idProvider);
    idProvider = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenIdentityProvider_AuthzIDL( TTestResult& aResult )
    {
    SetupL();
    
    CSenIdentityProvider* idProvider = CSenIdentityProvider::NewL(KText);
    TL(idProvider->AuthzID() == KNullDesC8);
    
    __ASSERT_ALWAYS_NO_LEAVE(idProvider->AuthzID());
    idProvider->SetUserInfoL(KText2, KNullDesC8, KNullDesC8);
    idProvider->SetUserInfoL(KText, KNullDesC8, KNullDesC8);
    
    //checking xml
    _LIT16(KRef, "<IdentityProvider framework=\"ID-WSF\"><Endpoint>text</Endpoint><Contract>urn:liberty:as:2004-04</Contract><ProviderPolicy/><ServicePolicy/><AuthzID>text</AuthzID></IdentityProvider>");

    TPtr16 ptr = ConvertToPtr16LC(*idProvider);
	TInt posId(-1);
    TPtrC16 messageToParse;
    messageToParse.Set(ptr);
    posId = messageToParse.Find(_L("<AuthzID>"));
    TL(posId != -1);
    CleanupStack::PopAndDestroy();//Ptr
    
    TL(idProvider->AuthzID() == KText);
    

    __ASSERT_ALWAYS_NO_LEAVE(delete idProvider);
    idProvider = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenIdentityProvider_AdvisoryAuthnIDL( TTestResult& aResult )
    {
    SetupL();
    
    CSenIdentityProvider* idProvider = CSenIdentityProvider::NewL(KText);
    TL(idProvider->AdvisoryAuthnID() == KNullDesC8);
    
    __ASSERT_ALWAYS_NO_LEAVE(idProvider->AdvisoryAuthnID());
    idProvider->SetUserInfoL(KNullDesC8, KText2, KNullDesC8);
    idProvider->SetUserInfoL(KNullDesC8, KText, KNullDesC8);
    
    //checking xml
    _LIT16(KRef, "<IdentityProvider framework=\"ID-WSF\"><Endpoint>text</Endpoint><Contract>urn:liberty:as:2004-04</Contract><ProviderPolicy/><ServicePolicy/><AdvisoryAuthnID>text</AdvisoryAuthnID></IdentityProvider>");

   // TL(ConvertToPtr16LC(*idProvider) == KRef);

    //CleanupStack::PopAndDestroy();//Ptr
    
    TPtr16 ptr = ConvertToPtr16LC(*idProvider);
	TInt posId(-1);
    TPtrC16 messageToParse;
    messageToParse.Set(ptr);
    posId = messageToParse.Find(_L("<AdvisoryAuthnID>"));
    TL(posId != -1);
    CleanupStack::PopAndDestroy();//Ptr
    
    TL(idProvider->AdvisoryAuthnID() == KText);


    __ASSERT_ALWAYS_NO_LEAVE(delete idProvider);
    idProvider = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenIdentityProvider_ProviderIDL( TTestResult& aResult )
    {
    SetupL();
    
    CSenIdentityProvider* idProvider = CSenIdentityProvider::NewL(KText, KText, KText2);
    __ASSERT_ALWAYS_NO_LEAVE(idProvider->ProviderID());
    TL(idProvider->ProviderID() == KText2);

    delete idProvider;
    idProvider = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenIdentityProvider_PasswordL( TTestResult& aResult )
    {

    SetupL();
    
    logger.Write(_L("MT_CSenIdentityProvider_PasswordL Entry"));
    
    CSenIdentityProvider* idProvider = CSenIdentityProvider::NewL(KText);
    __ASSERT_ALWAYS_NO_LEAVE(idProvider->Password());
    TL(idProvider->Password() == KNullDesC8);
    logger.Write(_L("TL(idProvider->Password() == KNullDesC8)"));
    
    
    idProvider->SetUserInfoL(KNullDesC8, KNullDesC8, KText2);
   logger.Write(_L("dProvider->SetUserInfoL(KNullDesC8, KNullDesC8, KText2)"));
    
    idProvider->SetUserInfoL(KNullDesC8, KNullDesC8, KText);
    logger.Write(_L("idProvider->SetUserInfoL(KNullDesC8, KNullDesC8, KText)"));
    //checking xml
    _LIT16(KRef, "<IdentityProvider framework=\"ID-WSF\"><Endpoint>text</Endpoint><Contract>urn:liberty:as:2004-04</Contract><ProviderPolicy/><ServicePolicy/><Password>text</Password></IdentityProvider>");
    //TL(ConvertToPtr16LC(*idProvider) == KRef);

   //CleanupStack::PopAndDestroy();//Ptr
    TPtr16 ptr = ConvertToPtr16LC(*idProvider);
   logger.Write(_L("TPtr16 ptr = ConvertToPtr16LC(*idProvider"));
    
	TInt posId(-1);
    TPtrC16 messageToParse;
    messageToParse.Set(ptr);
    posId = messageToParse.Find(_L("<Password>"));
    logger.Write(_L("messageToParse"));
    
    TL(posId != -1);
   CleanupStack::PopAndDestroy();//Ptr
    
    TL(idProvider->Password() == KText);
   logger.Write(_L("TL(idProvider->Password() == KText)"));


    __ASSERT_ALWAYS_NO_LEAVE(delete idProvider);
    idProvider = NULL;
    
    logger.CloseLog();
    
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenIdentityProvider_IMEIL( TTestResult& aResult )
    {
    SetupL();
    
    CSenIdentityProvider* idProvider = CSenIdentityProvider::NewL(KText);
    __ASSERT_ALWAYS_NO_LEAVE(idProvider->IMEI());
    idProvider->IMEI();

    __ASSERT_ALWAYS_NO_LEAVE(delete idProvider);
    idProvider = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenIdentityProvider_UserNameL( TTestResult& aResult )
    {
    SetupL();
    
    CSenIdentityProvider* idProvider = CSenIdentityProvider::NewL(KText);
    __ASSERT_ALWAYS_NO_LEAVE(idProvider->UserName());
    TL(idProvider->UserName() == KNullDesC8);

    idProvider->SetUserInfoL(KNullDesC8, KText, KNullDesC8);
    TL(idProvider->UserName()== KText);

    idProvider->SetUserInfoL(KText, KNullDesC8, KNullDesC8);
    TL(idProvider->UserName() == KText);

    idProvider->SetUserInfoL(KNullDesC8, KNullDesC8, KText);

    __ASSERT_ALWAYS_NO_LEAVE(delete idProvider);
    idProvider = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenIdentityProvider_SetProviderIDL( TTestResult& aResult )
    {
    SetupL();
    
    CSenIdentityProvider* idProvider = CSenIdentityProvider::NewL(KText);
    __ASSERT_ALWAYS_NO_LEAVE(idProvider->SetProviderID(KText2)); 
    __ASSERT_ALWAYS_NO_LEAVE(idProvider->SetProviderID(KText)); 
    //checking xml
    _LIT16(KRef, "<IdentityProvider framework=\"ID-WSF\"><Endpoint>text</Endpoint><Contract>urn:liberty:as:2004-04</Contract><ProviderPolicy/><ServicePolicy/><ProviderID>text</ProviderID></IdentityProvider>");
    //TL(ConvertToPtr16LC(*idProvider) == KRef);
	TPtr16 ptr = ConvertToPtr16LC(*idProvider);
	TInt posId(-1);
    TPtrC16 messageToParse;
    messageToParse.Set(ptr);
    posId = messageToParse.Find(_L("<ProviderID>"));
    TL(posId != -1);
    CleanupStack::PopAndDestroy();//Ptr
    __ASSERT_ALWAYS_NO_LEAVE(delete idProvider);
    idProvider = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenIdentityProvider_SetServiceIDL( TTestResult& aResult )
    {
    SetupL();
    
    CSenIdentityProvider* idProvider = CSenIdentityProvider::NewL(KText);
    __ASSERT_ALWAYS_NO_LEAVE(idProvider->SetServiceID(KText2)); 
    __ASSERT_ALWAYS_NO_LEAVE(idProvider->SetServiceID(KText)); 
    //checking xml
    _LIT16(KRef, "<IdentityProvider framework=\"ID-WSF\"><Endpoint>text</Endpoint><Contract>urn:liberty:as:2004-04</Contract><ProviderPolicy/><ServicePolicy/><ServiceID>text</ServiceID></IdentityProvider>");
    //TL(ConvertToPtr16LC(*idProvider) == KRef);

	TPtr16 ptr = ConvertToPtr16LC(*idProvider);
	TInt posId(-1);
    TPtrC16 messageToParse;
    messageToParse.Set(ptr);
    posId = messageToParse.Find(_L("<ServiceID>"));
    TL(posId != -1);
    CleanupStack::PopAndDestroy();//Ptr
    
    __ASSERT_ALWAYS_NO_LEAVE(delete idProvider);
    idProvider = NULL;
    Teardown();
    return KErrNone;
    }


TInt CSenServDesc::MT_CSenIdentityProvider_HttpCredentialsLL( TTestResult& aResult )
    {
    SetupL();
    
    CSenIdentityProvider* idProvider = CSenIdentityProvider::NewL(KText);
    //retVal = idProvider->HttpCredentialsL(); 

    
    __ASSERT_ALWAYS_NO_LEAVE(delete idProvider);
    idProvider = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenIdentityProvider_NewElementNameL( TTestResult& aResult )
    {
    SetupL();
    
    CSenIdentityProvider* idProvider = CSenIdentityProvider::NewL(KText);
    TL(idProvider->NewElementName() == _L8("IdentityProvider"));

    __ASSERT_ALWAYS_NO_LEAVE(idProvider->NewElementName());
    __ASSERT_ALWAYS_NO_LEAVE(delete idProvider);
    idProvider = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenIdentityProviderIdArray8_NewLL( TTestResult& aResult )
    {
    SetupL();
    
    CSenIdentityProviderIdArray8* array = CSenIdentityProviderIdArray8::NewL();
    TL(array->IsStrict() == FALSE);

    __ASSERT_ALWAYS_NO_LEAVE(delete array);
    array = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenIdentityProviderIdArray8_NewLCL( TTestResult& aResult )
    {
    SetupL();
    
    CSenIdentityProviderIdArray8* array = CSenIdentityProviderIdArray8::NewLC();
    TL(array->IsStrict() == FALSE);

    __ASSERT_ALWAYS_NO_LEAVE(delete array);
    CleanupStack::Pop();
    array = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenIdentityProviderIdArray8_NewL_1L( TTestResult& aResult )
    {
    SetupL();
    
    CSenIdentityProviderIdArray8* array = CSenIdentityProviderIdArray8::NewL(FALSE);
    TL(array->IsStrict() == FALSE);

    __ASSERT_ALWAYS_NO_LEAVE(delete array);
    array = NULL;
    
    array = CSenIdentityProviderIdArray8::NewL(TRUE);
    TL(array->IsStrict() == TRUE);

    __ASSERT_ALWAYS_NO_LEAVE(delete array);
    array = NULL;
        
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenIdentityProviderIdArray8_NewLC_1L( TTestResult& aResult )
    {
    SetupL();
    
    CSenIdentityProviderIdArray8* array = CSenIdentityProviderIdArray8::NewLC(FALSE);
    TL(array->IsStrict() == FALSE);

    __ASSERT_ALWAYS_NO_LEAVE(delete array);
    CleanupStack::Pop();
    array = NULL;
    
    array = CSenIdentityProviderIdArray8::NewLC(TRUE);
    TL(array->IsStrict() == TRUE);

    __ASSERT_ALWAYS_NO_LEAVE(delete array);
    CleanupStack::Pop();
    array = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenIdentityProviderIdArray8_IsStrictL( TTestResult& aResult )
    {
    SetupL();
    
    CSenIdentityProviderIdArray8* array = CSenIdentityProviderIdArray8::NewL();
    __ASSERT_ALWAYS_NO_LEAVE(array->SetStrict(TRUE));
    TL(array->IsStrict() == TRUE);

    __ASSERT_ALWAYS_NO_LEAVE(array->SetStrict(FALSE));
    TL(array->IsStrict() == FALSE);

    __ASSERT_ALWAYS_NO_LEAVE(delete array);
    array = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenIdentityProviderIdArray8_SetStrictL( TTestResult& aResult )
    {
    return MT_CSenIdentityProviderIdArray8_IsStrictL(aResult);
    }

TInt CSenServDesc::MT_CSenServicePattern_NewLL( TTestResult& aResult )
    {
    SetupL();
    
    CSenServicePattern* pattern = CSenServicePattern::NewL();
    //checking xml
    //_LIT16(KRef, "<ServiceDescription><ProviderPolicy/><ServicePolicy/></ServiceDescription>");
    //TL(ConvertToPtr16LC(*pattern) == KRef);

    //CleanupStack::PopAndDestroy();//Ptr
    __ASSERT_ALWAYS_NO_LEAVE(delete pattern);
    pattern = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenServicePattern_NewLCL( TTestResult& aResult )
    {
    SetupL();
    
    CSenServicePattern* pattern = CSenServicePattern::NewLC();
    //checking xml
    //_LIT16(KRef, "<ServiceDescription><ProviderPolicy/><ServicePolicy/></ServiceDescription>");
    //TL(ConvertToPtr16LC(*pattern) == KRef);

    //CleanupStack::PopAndDestroy();//Ptr
    CleanupStack::Pop();
    __ASSERT_ALWAYS_NO_LEAVE(delete pattern);
    pattern = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenServicePattern_NewL_1L( TTestResult& aResult )
    {
    SetupL();
    
    CSenServicePattern* pattern = CSenServicePattern::NewL(KText);
    //checking xml
    //_LIT16(KRef, "<ServiceDescription xmlns=\"text\"><ProviderPolicy/><ServicePolicy/></ServiceDescription>");
    //TL(ConvertToPtr16LC(*pattern) == KRef);

    //CleanupStack::PopAndDestroy();//Ptr
    __ASSERT_ALWAYS_NO_LEAVE(delete pattern);
    pattern = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenServicePattern_NewLC_1L( TTestResult& aResult )
    {
    SetupL();
    
    CSenServicePattern* pattern = CSenServicePattern::NewLC(KText);
    //checking xml
    //_LIT16(KRef, "<ServiceDescription xmlns=\"text\"><ProviderPolicy/><ServicePolicy/></ServiceDescription>");
    //TL(ConvertToPtr16LC(*pattern) == KRef);

    //CleanupStack::PopAndDestroy();//Ptr
    CleanupStack::Pop();
    __ASSERT_ALWAYS_NO_LEAVE(delete pattern);
    pattern = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenServicePattern_NewL_2L( TTestResult& aResult )
    {
    SetupL();
    
    CSenServicePattern* pattern = CSenServicePattern::NewL(KText, KText);
    
    //_LIT16(KRef, "<ServiceDescription><Endpoint>text</Endpoint><Contract>text</Contract><ProviderPolicy/><ServicePolicy/></ServiceDescription>");
    //TL(ConvertToPtr16LC(*pattern) == KRef);

    //CleanupStack::PopAndDestroy();//Ptr
    __ASSERT_ALWAYS_NO_LEAVE(delete pattern);
    pattern = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenServicePattern_NewLC_2L( TTestResult& aResult )
    {
    SetupL();
    
    CSenServicePattern* pattern = CSenServicePattern::NewLC(KText, KText);
    
    //_LIT16(KRef, "<ServiceDescription><Endpoint>text</Endpoint><Contract>text</Contract><ProviderPolicy/><ServicePolicy/></ServiceDescription>");
    //TL(ConvertToPtr16LC(*pattern) == KRef);

    //CleanupStack::PopAndDestroy();//Ptr
    CleanupStack::Pop();
    __ASSERT_ALWAYS_NO_LEAVE(delete pattern);
    pattern = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenServicePattern_SetConsumerIapIdLL( TTestResult& aResult )
    {
    SetupL();
    
    CSenServicePattern* pattern = CSenServicePattern::NewL();
    //checking xml
    
    TUint32 iap(0);
    TL(pattern->ConsumerIapId(iap) == KErrNotFound);

    
    pattern->SetConsumerIapIdL(1);
    __ASSERT_ALWAYS_NO_LEAVE(pattern->ConsumerIapId(iap));
    TL(pattern->ConsumerIapId(iap) == KErrNone);

    TL(iap == 1);

    pattern->SetConsumerIapIdL(0);
    __ASSERT_ALWAYS_NO_LEAVE(pattern->ConsumerIapId(iap));
    TL(pattern->ConsumerIapId(iap) == KErrNotFound);

    //TL(iap == 0);

    __ASSERT_ALWAYS_NO_LEAVE(delete pattern);
    pattern = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenServicePattern_ConsumerIapIdL( TTestResult& aResult )
    {
    SetupL();
    
    MT_CSenServicePattern_SetConsumerIapIdLL(aResult);
    Teardown();
    return KErrNone;
    }
TInt CSenServDesc::MT_CSenServicePattern_SetConsumerSnapIdLL( TTestResult& aResult )
    {
    SetupL();
    
    CSenServicePattern* pattern = CSenServicePattern::NewL();
    //checking xml
    
    TUint32 iap(0);
    TL(pattern->ConsumerSnapId(iap) == KErrNotFound);

    
    pattern->SetConsumerSnapIdL(1);
    __ASSERT_ALWAYS_NO_LEAVE(pattern->ConsumerSnapId(iap));
    TL(pattern->ConsumerSnapId(iap) == KErrNone);

    TL(iap == 1);

    pattern->SetConsumerSnapIdL(0);
    __ASSERT_ALWAYS_NO_LEAVE(pattern->ConsumerSnapId(iap));
    TL(pattern->ConsumerSnapId(iap) == KErrNotFound);

   // TL(iap == 0);

    __ASSERT_ALWAYS_NO_LEAVE(delete pattern);
    pattern = NULL;
    Teardown();
    
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenServicePattern_ConsumerSnapIdL( TTestResult& aResult )
    {
    
    SetupL();
    
    MT_CSenServicePattern_SetConsumerSnapIdLL(aResult);
    Teardown();
    
    return KErrNone;
    }


TInt CSenServDesc::MT_CSenServicePattern_SetConsumerIdentityProviderIdsLL( TTestResult& aResult )
    {
    SetupL();
    
    CSenServicePattern* pattern = CSenServicePattern::NewL();
    CSenIdentityProviderIdArray8* array = CSenIdentityProviderIdArray8::NewL();
    
    
    __ASSERT_ALWAYS_NO_LEAVE(pattern->SetConsumerIdentityProviderIdsL(*array));
    pattern->AddConsumerIdentityProviderIdL(KText);
    __ASSERT_ALWAYS_NO_LEAVE(pattern->SetConsumerIdentityProviderIdsL(*array));
    array->AppendL(KText);
    __ASSERT_ALWAYS_NO_LEAVE(pattern->SetConsumerIdentityProviderIdsL(*array));
    array->AppendL(KText2);
    __ASSERT_ALWAYS_NO_LEAVE(pattern->SetConsumerIdentityProviderIdsL(*array));
    
    TL((pattern->ConsumerIdentityProviderIds8L()).Count() == 2);

    TInt pos(0);
    if(!((pattern->ConsumerIdentityProviderIds8L()).Find(KText, pos)==KErrNone))return KErrArgument;

    if(!((pattern->ConsumerIdentityProviderIds8L()).Find(KText2, pos)==KErrNone))return KErrArgument;

    __ASSERT_ALWAYS_NO_LEAVE(delete array);
    array = NULL;
    __ASSERT_ALWAYS_NO_LEAVE(delete pattern);
    pattern = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenServicePattern_AddConsumerIdentityProviderIdLL( TTestResult& aResult )
    {
    SetupL();
    
    CSenServicePattern* pattern = CSenServicePattern::NewL();
    

    if(!(pattern->AddConsumerIdentityProviderIdL(KNullDesC8) == KErrArgument))return KErrArgument;

    if(!(pattern->AddConsumerIdentityProviderIdL(KText) == KErrNone))return KErrArgument;

    if(!(pattern->AddConsumerIdentityProviderIdL(KText) == KErrAlreadyExists))return KErrArgument;

    if(!(pattern->AddConsumerIdentityProviderIdL(KText2) == KErrNone))return KErrArgument;

    _LIT16(KRef, "<ServiceDescription><ProviderPolicy/><ServicePolicy/></ServiceDescription>");
    //TL(ConvertToPtr16LC(*pattern) == KRef);

    //CleanupStack::PopAndDestroy();//Ptr
    
    __ASSERT_ALWAYS_NO_LEAVE(delete pattern);
    pattern = NULL;    
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenServicePattern_ConsumerIdentityProviderIds8LL( TTestResult& aResult )
    {
    return MT_CSenServicePattern_SetConsumerIdentityProviderIdsLL(aResult);
    }

TInt CSenServDesc::MT_CSenServicePattern_AcceptsConsumerPolicyL( TTestResult& aResult )
    {
    SetupL();
    
    CSenServicePattern* pattern = CSenServicePattern::NewL();
    CSenIdentityProviderIdArray8* array = CSenIdentityProviderIdArray8::NewL();
    
    pattern->SetConsumerIapIdL(1);
    array->AppendL(KText);
    
    CSenServicePattern* pattern2 = CSenServicePattern::NewL();
    if(!(pattern2->RebuildFromConsumerPolicy(*pattern)==KErrNone))return KErrArgument;

    if(!(pattern2->AcceptsConsumerPolicy(*pattern)==TRUE))return KErrArgument;

    __ASSERT_ALWAYS_NO_LEAVE(delete array);
    __ASSERT_ALWAYS_NO_LEAVE(delete pattern2);
    array = NULL;
    pattern2 = NULL;
//false
    pattern2 = CSenServicePattern::NewL();
    pattern2->SetConsumerIapIdL(2);
    if(!(pattern2->AcceptsConsumerPolicy(*pattern)==FALSE))return KErrArgument;

    __ASSERT_ALWAYS_NO_LEAVE(delete pattern2);
    __ASSERT_ALWAYS_NO_LEAVE(delete pattern);
    pattern2 = NULL;
    pattern = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenServicePattern_RebuildFromConsumerPolicyL( TTestResult& aResult )
    {
    return MT_CSenServicePattern_AcceptsConsumerPolicyL(aResult);
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_NewLL( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewL();
    if(xmlService == NULL)
     return KErrNoMemory;
    //checking xml
    //_LIT16(KRef, "<ServiceDescription><ProviderPolicy/><ServicePolicy/></ServiceDescription>");
    //TL(ConvertToPtr16LC(*xmlService) == KRef);

    //CleanupStack::PopAndDestroy();//Ptr
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_NewLCL( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewLC();
    if(xmlService == NULL)
     return KErrNoMemory;
    //checking xml
    //_LIT16(KRef, "<ServiceDescription><ProviderPolicy/><ServicePolicy/></ServiceDescription>");
    //TL(ConvertToPtr16LC(*xmlService) == KRef);

    //CleanupStack::PopAndDestroy();//Ptr
    CleanupStack::Pop();
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_NewL_1L( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewL(KText);
    if(xmlService == NULL)
     return KErrNoMemory;
    //checking xml
    //_LIT16(KRef, "<ServiceDescription xmlns=\"text\"><ProviderPolicy/><ServicePolicy/></ServiceDescription>");
    //TL(ConvertToPtr16LC(*xmlService) == KRef);

    //CleanupStack::PopAndDestroy();//Ptr
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_NewLC_1L( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewLC(KText);
    if(xmlService == NULL)
     return KErrNoMemory;
     //checking xml
    //_LIT16(KRef, "<ServiceDescription xmlns=\"text\"><ProviderPolicy/><ServicePolicy/></ServiceDescription>");
    //TL(ConvertToPtr16LC(*xmlService) == KRef);

    //CleanupStack::PopAndDestroy();//Ptr
    CleanupStack::Pop();
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_NewL_2L( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewL(KText, KText);
    if(xmlService == NULL)
     return KErrNoMemory;
     //checking xml
    //_LIT16(KRef, "<ServiceDescription><Endpoint>text</Endpoint><Contract>text</Contract><ProviderPolicy/><ServicePolicy/></ServiceDescription>");
    //TL(ConvertToPtr16LC(*xmlService) == KRef);

    //CleanupStack::PopAndDestroy();//Ptr
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_NewLC_2L( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewLC(KText, KText);
    if(xmlService == NULL)
     return KErrNoMemory;
     //checking xml
    //_LIT16(KRef, "<ServiceDescription><Endpoint>text</Endpoint><Contract>text</Contract><ProviderPolicy/><ServicePolicy/></ServiceDescription>");
    //TL(ConvertToPtr16LC(*xmlService) == KRef);

    //CleanupStack::PopAndDestroy();//Ptr
    CleanupStack::Pop();
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_SetFrameworkIdLL( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewL();

    TL(xmlService->FrameworkId() == KNullDesC8);

    _LIT8(KFr, "ID-WSF");
    xmlService->SetFrameworkIdL(KFr);
    //checking xml
    _LIT16(KRef1, "<ServiceDescription framework=\"ID-WSF\"><ProviderPolicy/><ServicePolicy/></ServiceDescription>");
    //TL(ConvertToPtr16LC(*xmlService) == KRef1);

	TPtr16 ptr = ConvertToPtr16LC(*xmlService);
	TInt posId(-1);
    TPtrC16 messageToParse;
    messageToParse.Set(ptr);
    posId = messageToParse.Find(_L("framework=\"ID-WSF\""));
	TL(posId != -1);
    CleanupStack::PopAndDestroy();//Ptr
    TL(xmlService->FrameworkId() == KFr);

    //again
    xmlService->SetFrameworkIdL(KFr);
    //checking xml
    //_LIT16(KRef2, "<ServiceDescription framework=\"ID-WSF\"><ProviderPolicy/><ServicePolicy/></ServiceDescription>");
    //TL(ConvertToPtr16LC(*xmlService) == KRef2);

	TPtr16 ptr1 = ConvertToPtr16LC(*xmlService);
	posId = -1;
    messageToParse.Set(ptr1);
	posId = messageToParse.Find(_L("framework=\"ID-WSF\""));
	TL(posId != -1);
    CleanupStack::PopAndDestroy();//Ptr1
    TL(xmlService->FrameworkId() == KFr);

    //again
    xmlService->SetFrameworkIdL(KText);
    //checking xml
    //_LIT16(KRef3, "<ServiceDescription framework=\"text\"><ProviderPolicy/><ServicePolicy/></ServiceDescription>");
    //TL(ConvertToPtr16LC(*xmlService) == KRef3);
	TPtr16 ptr2 = ConvertToPtr16LC(*xmlService);
	posId =-1;
    messageToParse.Set(ptr2);
    posId = messageToParse.Find(_L("framework=\"text\""));
    TL(posId != -1);
    CleanupStack::PopAndDestroy();//Ptr2
    TL(xmlService->FrameworkId() == KText);

    //clear
    xmlService->SetFrameworkIdL(KNullDesC8);
    //checking xml
    //_LIT16(KRef4, "<ServiceDescription><ProviderPolicy/><ServicePolicy/></ServiceDescription>");
    //TL(ConvertToPtr16LC(*xmlService) == KRef4);
	TPtr16 ptr3 = ConvertToPtr16LC(*xmlService);
	posId = -1;
    messageToParse.Set(ptr3);
    posId = messageToParse.Find(_L("ServiceDescription"));
    TL(posId != -1);
    CleanupStack::PopAndDestroy();//Ptr3
    TL(xmlService->FrameworkId() == KNullDesC8);

    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_NewElementNameL( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewL();
    _LIT8(KRef, "ServiceDescription");
    if(!(xmlService ->NewElementName() == KRef))return KErrArgument;

    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_SetIapIdLL( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewL();
    TUint32 iap(0);
    if(!((xmlService ->IapId(iap)) == KErrNotFound))return KErrArgument;

    xmlService ->SetIapIdL(1);
    if(!(xmlService ->IapId(iap) == KErrNone))return KErrArgument;

    if(!(1))return KErrArgument;

    xmlService ->SetIapIdL(2);
    if(!(xmlService ->IapId(iap) == KErrNone))return KErrArgument;

    if(!(2))return KErrArgument;

    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_IapIdL( TTestResult& aResult )
    {
    return MT_CSenXmlServiceDescription_SetIapIdLL(aResult);
    }
    
TInt CSenServDesc::MT_CSenXmlServiceDescription_SetSnapIdLL( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewL();
    TUint32 iap(0);
    if(!((xmlService ->SnapId(iap)) == KErrNotFound))return KErrArgument;

    xmlService ->SetSnapIdL(1);
    if(!(xmlService ->SnapId(iap) == KErrNone))return KErrArgument;

    if(!(1))return KErrArgument;

    xmlService ->SetSnapIdL(2);
    if(!(xmlService ->SnapId(iap) == KErrNone))return KErrArgument;

    if(!(2))return KErrArgument;

    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_SnapIdL( TTestResult& aResult )
    {
    return MT_CSenXmlServiceDescription_SetSnapIdLL(aResult);
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_SetIdentityProviderIdsLL( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewL();
    CSenIdentityProviderIdArray8* array = CSenIdentityProviderIdArray8::NewL();
    
    
    __ASSERT_ALWAYS_NO_LEAVE(xmlService->SetIdentityProviderIdsL(*array));
    
    TPtrC8 ptrText = KText();
    xmlService->AddIdentityProviderIdL(ptrText);

    __ASSERT_ALWAYS_NO_LEAVE(xmlService->SetIdentityProviderIdsL(*array));
    array->AppendL(KText);
    __ASSERT_ALWAYS_NO_LEAVE(xmlService->SetIdentityProviderIdsL(*array));
    array->AppendL(KText2);
    __ASSERT_ALWAYS_NO_LEAVE(xmlService->SetIdentityProviderIdsL(*array));
    
    TL((xmlService->IdentityProviderIds8L()).Count() == 2);

    TInt pos(0);
    if(!((xmlService->IdentityProviderIds8L()).Find(KText, pos)==KErrNone))return KErrArgument;

    if(!((xmlService->IdentityProviderIds8L()).Find(KText2, pos)==KErrNone))return KErrArgument;

    __ASSERT_ALWAYS_NO_LEAVE(delete array);
    array = NULL;
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_AddIdentityProviderIdLL( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewL();
    TPtrC8 ptr = KNullDesC8();
    if(!(xmlService->AddIdentityProviderIdL(ptr) == KErrArgument))return KErrArgument;

    ptr.Set(KText);
    if(!(xmlService->AddIdentityProviderIdL(ptr) == KErrNone))return KErrArgument;

    if(!(xmlService->AddIdentityProviderIdL(ptr) == KErrAlreadyExists))return KErrArgument;

    ptr.Set(KText2);
    if(!(xmlService->AddIdentityProviderIdL(ptr) == KErrNone))return KErrArgument;


    _LIT16(KRef, "<ServiceDescription><ProviderPolicy><IdentityProviderIDs><IdentityProviderID>text</IdentityProviderID><IdentityProviderID>text2</IdentityProviderID></IdentityProviderIDs></ProviderPolicy><ServicePolicy/></ServiceDescription>");
    //TL(ConvertToPtr16LC(*xmlService) == KRef);

    //CleanupStack::PopAndDestroy();//Ptr
    
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_RebuildFromL( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewL();
    CSenIdentityProviderIdArray8* array = CSenIdentityProviderIdArray8::NewL();
    
    xmlService->SetIapIdL(1);
    array->AppendL(KText);
    
    CSenXmlServiceDescription* xmlService2 = CSenXmlServiceDescription::NewL();
    if(!(xmlService2->RebuildFrom(*xmlService)==KErrNone))return KErrArgument;

    if(!(xmlService2->Accepts(*xmlService)==TRUE))return KErrArgument;

    __ASSERT_ALWAYS_NO_LEAVE(delete array);
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService2);
    array = NULL;
    xmlService2 = NULL;
//false
    xmlService2 = CSenServicePattern::NewL();
    xmlService2->SetIapIdL(2);
    if(!(xmlService2->Accepts(*xmlService)==FALSE))return KErrArgument;

    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService2);
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService2 = NULL;
    xmlService = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_IdentityProviderIds8LL( TTestResult& aResult )
    {
    return MT_CSenXmlServiceDescription_SetIdentityProviderIdsLL(aResult);
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_AcceptsL( TTestResult& aResult )
    {
    return MT_CSenXmlServiceDescription_RebuildFromL(aResult);
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_DescriptionClassTypeL( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewL();
    if(!(xmlService ->DescriptionClassType() == MSenServiceDescription::EXmlServiceDescription))return KErrArgument;

    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_ContractL( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewL();
    xmlService ->SetContractL(KText);
     //checking xml
    _LIT16(KRef, "<ServiceDescription><ProviderPolicy/><ServicePolicy/><Contract>text</Contract></ServiceDescription>");
    
    //TL(ConvertToPtr16LC(*xmlService) == KRef);
	TPtr16 ptr = ConvertToPtr16LC(*xmlService);
	TInt posId(-1);
    TPtrC16 messageToParse;
    messageToParse.Set(ptr);
    posId = messageToParse.Find(_L("<Contract>"));
    TL(posId != -1);
    CleanupStack::PopAndDestroy();//Ptr
    TL(xmlService->Contract() == KText);

    //CleanupStack::PopAndDestroy();//Ptr
   
    //2nd time
    xmlService ->SetContractL(KText);
     //checking xml
    //TL(ConvertToPtr16LC(*xmlService) == KRef);
	ptr = ConvertToPtr16LC(*xmlService);
	posId = -1;
    messageToParse.Set(ptr);
    posId = messageToParse.Find(_L("<Contract>"));
    TL(posId != -1);
    CleanupStack::PopAndDestroy();//Ptr
    TL(xmlService->Contract() == KText);

    //CleanupStack::PopAndDestroy();//Ptr
   
    xmlService ->SetContractL(KText2);
     //checking xml
    _LIT16(KRef2, "<ServiceDescription><ProviderPolicy/><ServicePolicy/><Contract>text2</Contract></ServiceDescription>");
    //TL(ConvertToPtr16LC(*xmlService) == KRef2);

    TL(xmlService->Contract() == KText2);

    //CleanupStack::PopAndDestroy();//Ptr
   
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    Teardown();
    return KErrNone;
    }
//================Facets
TInt CSenServDesc::MT_CSenXmlServiceDescription_HasFacetLL( TTestResult& aResult )
    {
    return MT_CSenXmlServiceDescription_RemoveFacetL(aResult);
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_FacetValueL( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewL();
    CSenFacet* senFacet;
    senFacet = CSenFacet::NewL();
    senFacet->SetNameL(KText);
    senFacet->SetValueL(KText2);
    

    xmlService->AddFacetL(*senFacet);
    TPtrC8 ptr=KText();
    HBufC8* valueTo = NULL;
    
    if(!(xmlService->FacetValue(ptr, valueTo)==KErrNone))return KErrArgument;

    TL(*valueTo == KText2);

    __ASSERT_ALWAYS_NO_LEAVE(delete valueTo );
    valueTo = NULL;
    
    if(!(xmlService->FacetValue(ptr, valueTo)==KErrNone))return KErrArgument;

    TL(*valueTo == KText2);

    __ASSERT_ALWAYS_NO_LEAVE(delete valueTo );
    valueTo = NULL;
    
    ptr.Set(KText2);
    if(!(xmlService->FacetValue(ptr, valueTo)==KErrNotFound))return KErrArgument;

     __ASSERT_ALWAYS_NO_LEAVE(delete senFacet);
    senFacet = NULL;
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_AddFacetLL( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewL();
    CSenFacet *senFacet;
    CSenFacet *senFacet2;
    
    senFacet = CSenFacet::NewL();
    senFacet2 = CSenFacet::NewL();
    senFacet->SetNameL(KText);
    senFacet2->SetNameL(KText2);
    RFacetArray array;

    if(!(xmlService->AddFacetL(*senFacet) == KErrNone))return KErrArgument;

    if(!(xmlService->AddFacetL(*senFacet) == KErrAlreadyExists))return KErrArgument;

    if(!(xmlService->AddFacetL(*senFacet2) == KErrNone))return KErrArgument;

    //_LIT16(KRef, "<ServiceDescription><ProviderPolicy/><ServicePolicy/><Facet name=\"text\"/><Facet name=\"text2\"/></ServiceDescription>");
    //TPtrC16 ptrRef = KRef();
    //TL(ConvertToPtr16LC(*xmlService) == ptrRef);

    //CleanupStack::PopAndDestroy();//Ptr
   	TPtr16 ptr = ConvertToPtr16LC(*xmlService);
	TInt posId(-1);
    TPtrC16 messageToParse;
    messageToParse.Set(ptr);
    posId = messageToParse.Find(_L("<Facet name=\"text\"/><Facet name=\"text2\"/>"));
    TL(posId != -1);
    CleanupStack::PopAndDestroy();//Ptr
   
    if(!(xmlService->FacetsL(array) == KErrNone))return KErrArgument;

    if(!(array.Count() == 2))return KErrArgument;

    __ASSERT_ALWAYS_NO_LEAVE(delete senFacet);
    senFacet = NULL;
    __ASSERT_ALWAYS_NO_LEAVE(delete senFacet2);
    senFacet2 = NULL;
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    array.ResetAndDestroy();
    array.Close();
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_SetFacetLL( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewL();
    CSenFacet* senFacet;
    senFacet = CSenFacet::NewL();
    senFacet->SetNameL(KText);
    senFacet->SetValueL(KText);
    
    RFacetArray array;
    if(!(xmlService->SetFacetL(*senFacet) == KErrNone))return KErrArgument;

    if(!(xmlService->SetFacetL(*senFacet) == KErrNone))return KErrArgument;

    senFacet->SetValueL(KText2);
    if(!(xmlService->SetFacetL(*senFacet) == KErrNone))return KErrArgument;

    _LIT16(KRef, "<ServiceDescription><ProviderPolicy/><ServicePolicy/><Facet name=\"text\">text2</Facet></ServiceDescription>");
    //TPtrC16 ptrRef = KRef();
    //TL(ConvertToPtr16LC(*xmlService) == ptrRef);
    
    //CleanupStack::PopAndDestroy();//Ptr
	TPtr16 ptr = ConvertToPtr16LC(*xmlService);
	 TInt posId(-1);
    TPtrC16 messageToParse;
    messageToParse.Set(ptr);
    posId = messageToParse.Find(_L("<Facet name=\"text\">text2</Facet>"));
    TL(posId != -1);
    CleanupStack::PopAndDestroy();//Ptr

    if(!(xmlService->FacetsL(array) == KErrNone))return KErrArgument;

    if(!(array.Count() == 1))return KErrArgument;

    __ASSERT_ALWAYS_NO_LEAVE(delete senFacet);
    senFacet = NULL;
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    array.ResetAndDestroy();
    array.Close();
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_RemoveFacetL( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewL();
    CSenFacet *senFacet;
    CSenFacet *senFacet2;
    
    senFacet = CSenFacet::NewL();
    senFacet2 = CSenFacet::NewL();
    senFacet->SetNameL(KText);
    senFacet2->SetNameL(KText2);
    RFacetArray array;


    if(!(xmlService->AddFacetL(*senFacet) == KErrNone))return KErrArgument;

    if(!(xmlService->AddFacetL(*senFacet) == KErrAlreadyExists))return KErrArgument;

    if(!(xmlService->AddFacetL(*senFacet2) == KErrNone))return KErrArgument;

    if(!(xmlService->FacetsL(array) == KErrNone))return KErrArgument;

    if(!(array.Count() == 2))return KErrArgument;

    array.ResetAndDestroy();
//removing, haFacet
    TBool has(FALSE);
    if(!(xmlService->HasFacetL(KText, has) == KErrNone))return KErrArgument;

    if(!(has == TRUE))return KErrArgument;

    if(!(xmlService->HasFacetL(KText2, has) == KErrNone))return KErrArgument;

    if(!(has == TRUE))return KErrArgument;

    if(!(xmlService->RemoveFacet(KText2) == KErrNone))return KErrArgument;

    __ASSERT_ALWAYS_NO_LEAVE(xmlService->RemoveFacet(KText2));
    if(!(xmlService->HasFacetL(KText2, has) == KErrNone))return KErrArgument;

    if(!(has == FALSE))return KErrArgument;

    if(!(xmlService->RemoveFacet(KText2) == KErrNotFound))return KErrArgument;

    if(!(xmlService->HasFacetL(KText2, has) == KErrNone))return KErrArgument;

    if(!(has == FALSE))return KErrArgument;

    if(!(xmlService->FacetsL(array) == KErrNone))return KErrArgument;

    if(!(array.Count() == 1))return KErrArgument;

    __ASSERT_ALWAYS_NO_LEAVE(delete senFacet);
    senFacet = NULL;
    __ASSERT_ALWAYS_NO_LEAVE(delete senFacet2);
    senFacet2 = NULL;
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    array.ResetAndDestroy();
    array.Close();
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_FacetsLL( TTestResult& aResult )
    {
    return MT_CSenXmlServiceDescription_AddFacetLL(aResult);
    }
//------------end facet

TInt CSenServDesc::MT_CSenXmlServiceDescription_SetTransportPropertiesL( TTestResult& aResult )
    {  
    return MT_CSenXmlServiceDescription_TransportPropertiesL(aResult);
    //return KErrNone;
    }
    
TInt CSenServDesc::MT_CSenXmlServiceDescription_TransportPropertiesL( TTestResult& aResult )
    {

    SetupL();
    
    _LIT8(KRef,"<Properties><DeviceID>123</DeviceID></Properties>");
   
    TInt posId ;

     CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewL(KText, KText);
     CleanupStack::PushL(xmlService);
    
     xmlService->SetTransportPropertiesL(KRef);

     HBufC8* retBuf;
     xmlService->TransportPropertiesL(retBuf);
     TPtrC8 messageToParse;
     messageToParse.Set(retBuf->Des());
     
     posId = messageToParse.Find(_L8("<Properties><DeviceID>123</DeviceID></Properties>"));
     CleanupStack::PopAndDestroy(xmlService);
     //TL(retBuf->Des()==KRef1);
     TL(posId != -1);
     
    Teardown();
    return KErrNone ;
    }    

TInt CSenServDesc::MT_CSenXmlServiceDescription_ScoreMatchLL( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription *xmlService;
    CSenXmlServiceDescription *xmlService2;
    
    xmlService = CSenXmlServiceDescription::NewL();
    xmlService2 = CSenXmlServiceDescription::NewL();

    if(!(xmlService->ScoreMatchL(*xmlService2) == 0))return KErrArgument;

    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService2);
    xmlService2 = NULL;
//---------------
    xmlService = CSenXmlServiceDescription::NewL(KText, KText2);
    xmlService2 = CSenXmlServiceDescription::NewL(KText, KText2);

    if(!(xmlService->ScoreMatchL(*xmlService2) == 2))return KErrArgument;

    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService2);
    xmlService2 = NULL;
//---------------
    xmlService = CSenXmlServiceDescription::NewL(KText2, KText);
    xmlService2 = CSenXmlServiceDescription::NewL(KText, KText2);

    if(!(xmlService->ScoreMatchL(*xmlService2) == 0))return KErrArgument;

   __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService2);
    xmlService2 = NULL;
//---------------
    xmlService = CSenXmlServiceDescription::NewL(KText2, KText);
    xmlService2 = CSenXmlServiceDescription::NewL(KText, KText2);
    CSenFacet* senFacet = CSenFacet::NewL();
    senFacet->SetNameL(KText);
    xmlService->AddFacetL(*senFacet);
    xmlService2->AddFacetL(*senFacet);
    
    if(!(xmlService->ScoreMatchL(*xmlService2) == 1))return KErrArgument;

    __ASSERT_ALWAYS_NO_LEAVE(delete senFacet);
    senFacet = NULL;
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService2);
    xmlService2 = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_EndpointL( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewL();
    
    xmlService ->SetEndPointL(KText);
     //checking xml
    _LIT16(KRef, "<ServiceDescription><ProviderPolicy/><ServicePolicy/><Endpoint>text</Endpoint></ServiceDescription>");
    //TL(ConvertToPtr16LC(*xmlService) == KRef);

    TL(xmlService->Endpoint() == KText);
	TPtr16 ptr = ConvertToPtr16LC(*xmlService);
	TInt posId(-1);
    TPtrC16 messageToParse;
    messageToParse.Set(ptr);
    posId = messageToParse.Find(_L("<Endpoint>"));
    TL(posId != -1);
    CleanupStack::PopAndDestroy();//Ptr
   
    //2nd time
    xmlService ->SetEndPointL(KText);
     //checking xml
    //TL(ConvertToPtr16LC(*xmlService) == KRef);
	ptr = ConvertToPtr16LC(*xmlService);
	posId = -1;
    messageToParse.Set(ptr);
    posId = messageToParse.Find(_L("<Endpoint>"));
    TL(posId != -1);
    TL(xmlService->Endpoint() == KText);

    CleanupStack::PopAndDestroy();//Ptr
   

    xmlService ->SetEndPointL(KText2);
     //checking xml
    _LIT16(KRef2, "<ServiceDescription><ProviderPolicy/><ServicePolicy/><Endpoint>text2</Endpoint></ServiceDescription>");
    //TL(ConvertToPtr16LC(*xmlService) == KRef2);

    TL(xmlService->Endpoint() == KText2);
	ptr = ConvertToPtr16LC(*xmlService);
	posId = -1;
    messageToParse.Set(ptr);
    posId = messageToParse.Find(_L("<Endpoint>"));
    TL(posId != -1);
    CleanupStack::PopAndDestroy();//Ptr
   
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_FrameworkIdL( TTestResult& aResult )
    {
    return MT_CSenXmlServiceDescription_SetFrameworkIdLL(aResult);
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_FrameworkVersionL( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewL();
    __ASSERT_ALWAYS_NO_LEAVE(xmlService ->FrameworkVersion());
    if(!(xmlService ->FrameworkVersion() == KNullDesC8))return KErrArgument;

    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    Teardown();
    return KErrNone;
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_SetContractLL( TTestResult& aResult )
    {
    return MT_CSenXmlServiceDescription_ContractL(aResult);
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_SetEndPointLL( TTestResult& aResult )
    {
    return MT_CSenXmlServiceDescription_EndpointL(aResult);
    }

TInt CSenServDesc::MT_CSenXmlServiceDescription_SetAttributesLL( TTestResult& aResult )
    {
    SetupL();
    
    CSenXmlServiceDescription* xmlService = CSenXmlServiceDescription::NewL();
    RAttributeArray attributeArray;
    xmlService->SetAttributesL(attributeArray);
    __ASSERT_ALWAYS_NO_LEAVE(delete xmlService);
    xmlService = NULL;
    attributeArray.Reset();
    attributeArray.Close();
    Teardown();
    return KErrNone;
    }



// -----------------------------------------------------------------------------
// ?classname::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
?type ?classname::?member_function(
   ?arg_type arg,
   ?arg_type arg )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================

// -----------------------------------------------------------------------------
// ?function_name implements...
// ?implementation_description.
// Returns: ?value_1: ?description
//          ?value_n: ?description
//                    ?description
// -----------------------------------------------------------------------------
//
/*
?type  ?function_name(
    ?arg_type arg,  // ?description
    ?arg_type arg )  // ?description
    {

    ?code

    }
*/
//  End of File
