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



// [INCLUDE FILES] - do not remove
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include "MTPbkEmailAddressSelect.h"
#include "T_AddressAndNumberSelect.h"
#include <CPbkEmailAddressSelect.h>
#include <CPbkContactEngine.h>
#include <CPbkContactItem.h>
#include <eikenv.h>
#include "CSimulateKeyEvents.h"
// EXTERNAL DATA STRUCTURES
//extern  ?external_data;

// EXTERNAL FUNCTION PROTOTYPES  
//extern ?external_function( ?arg_type,?arg_type );

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
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
// CMTPbkEmailAddressSelect::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CMTPbkEmailAddressSelect::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CMTPbkEmailAddressSelect::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CMTPbkEmailAddressSelect::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "Size_of_Class_not_less_than", CMTPbkEmailAddressSelect::RunTest_ClassSizeL ),
        ENTRY( "Test_with_empty_contact_item", CMTPbkEmailAddressSelect::RunExecuteEmptyContactL ),
        ENTRY( "Test_with_empty_contact_itemFocus", CMTPbkEmailAddressSelect::RunExecuteTestCaseFocusNullL ),
        ENTRY( "Test_with_empty_contact_itemDirectly", CMTPbkEmailAddressSelect::RunExecuteTestCaseDirectlyTrueL ),
        ENTRY( "Test_with_contact_item_with_name_fields", CMTPbkEmailAddressSelect::RunExecuteWithContactNameL ),
        ENTRY( "Test_with_contact_item_with_company_name", CMTPbkEmailAddressSelect::RunExecuteWithCompanyNameL ),
        ENTRY( "Test_with_contact_item_with_name_fieldsFocus", CMTPbkEmailAddressSelect::RunExecuteWithOneEmailL ),
        ENTRY( "Test_with_contact_item_with_company_name_fieldFocus_", CMTPbkEmailAddressSelect::RunExecuteTestCaseFocusNull1L ),
        ENTRY( "Test_with_contact_item_with_name_fieldsDirectly_", CMTPbkEmailAddressSelect::RunExecuteTestCaseDirectlyTrue1L ),
        ENTRY( "Test_with_contact_item_with_company_name_fieldDirectly_", CMTPbkEmailAddressSelect::RunExecuteTestCaseDirectlyTrue2L ),
        ENTRY( "Test_with_one_email_address", CMTPbkEmailAddressSelect::RunExecuteWithOneEmail1L ),
        ENTRY( "Test_one_email_addressFocus", CMTPbkEmailAddressSelect::RunExecuteWithOneEmailFocusNullL ),
        ENTRY( "Test_one_email_addressDirectly", CMTPbkEmailAddressSelect::RunExecuteWithOneEmailDirectlyTrueL ),
        ENTRY( "Test_two_email_addresses_and_key_event_simulation_", CMTPbkEmailAddressSelect::RunExecuteWithMultiEmailL ),
        ENTRY( "Test_focus_on_phone_numberFocus", CMTPbkEmailAddressSelect::RunExecuteWithMultiEmailFocusNullL ),
        ENTRY( "Test_two_email_addresses_one_default_email", CMTPbkEmailAddressSelect::RunExecuteWithMultiEmailAndDefaultEmailL ),
        ENTRY( "Test_two_email_addresses_one_default_and_one_focused_email_address_", CMTPbkEmailAddressSelect::RunExecuteMultiEmailWithDefaultEmailAndFocusL ),
        ENTRY( "Test_One_default_no_email_focus_ret_default_address_focused_", CMTPbkEmailAddressSelect::RunExecuteMultiEmailWithFocusL ),
        ENTRY( "Test_One_default_no_focus_ret_default_address_focused_", CMTPbkEmailAddressSelect::RunExecuteMultiEmailWithNoFocusL ),
        ENTRY( "Test_Soft_key_events", CMTPbkEmailAddressSelect::RunExecuteTestSoftKeys1L ),
        ENTRY( "Test_Soft_key_events", CMTPbkEmailAddressSelect::RunExecuteTestSoftKeys2L ),
        
        //ADD NEW ENTRY HERE
        // [test cases entries] - Do not remove

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CMTPbkEmailAddressSelect::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*******************************************************************
*
*	RunTest_ClassSizeL()
*
*******************************************************************/
TInt CMTPbkEmailAddressSelect::RunTest_ClassSizeL()
    {
    SetupContactItemWithNameL();
    static const TInt sizeof_class_CPbkEmailAddressSelect_30 = 32;
    static const TInt sizeof_class_CPbkEmailAddressSelect_TParams = 32;

    RDebug::Printf("Class: sizeof(class CPbkEmailAddressSelect)=%d\n", 
                sizeof(class CPbkEmailAddressSelect));
    RDebug::Printf("Class: sizeof(class CPbkEmailAddressSelect::TParams)=%d\n", 
                sizeof(class CPbkEmailAddressSelect::TParams));

    ASSERT( sizeof(class CPbkEmailAddressSelect) >= 
                sizeof_class_CPbkEmailAddressSelect_30 );
    ASSERT( sizeof(class CPbkEmailAddressSelect::TParams) >= 
                sizeof_class_CPbkEmailAddressSelect_TParams );
	Teardown();
	return KErrNone;
    }

/*******************************************************************
*
*	RunExecuteEmptyContact()
*
*******************************************************************/
TInt CMTPbkEmailAddressSelect::RunExecuteEmptyContactL()
	{
	SetupEmptyContactItemL();
	TBool 					callDefaultDirectly = EFalse,
							ret = ETrue;
	TInt 					search = 0;
	TPbkContactItemField* 	focusedField = NULL;

	focusedField = iContactItem->FindField( EPbkFieldIdFirstName, search);
	//ASSERT( focusedField, "Contact's first name wasn't found for focus" );
	ASSERT( focusedField );

	ret = RunExecuteL(*iContactItem,focusedField,callDefaultDirectly );
	ASSERT( !ret );
	Teardown();
	return KErrNone;
	}

/*******************************************************************
*
*	RunExecuteTestCase1FocusNullL()
*
*******************************************************************/
TInt CMTPbkEmailAddressSelect::RunExecuteTestCaseFocusNullL()
	{
	SetupEmptyContactItemL();
	TBool 					callDefaultDirectly = EFalse,
							ret = ETrue;
	TPbkContactItemField* 	focusedField = NULL;

	ret = RunExecuteL(*iContactItem,focusedField,callDefaultDirectly );
	ASSERT( !ret );
	Teardown();
	return KErrNone;
	}

/*******************************************************************
*
*	RunExecuteTestCase1FocusNullL()
*
*******************************************************************/
TInt CMTPbkEmailAddressSelect::RunExecuteTestCaseFocusNull1L()
	{
	SetupContactItemWithCompanyNameL();
	TBool 					callDefaultDirectly = EFalse,
							ret = ETrue;
	TPbkContactItemField* 	focusedField = NULL;

	ret = RunExecuteL(*iContactItem,focusedField,callDefaultDirectly );
	ASSERT( !ret );
	Teardown();
	return KErrNone;
	}

/*******************************************************************
*
*	RunExecuteTestCaseDirectlyTrueL()
*
*******************************************************************/
TInt CMTPbkEmailAddressSelect::RunExecuteTestCaseDirectlyTrueL()
	{
	SetupEmptyContactItemL();
	TPbkContactItemField* 	focusedField = NULL;
	TBool 					callDefaultDirectly = ETrue,
							ret = ETrue;
	
	ret = RunExecuteL(*iContactItem,focusedField,callDefaultDirectly );
	ASSERT( !ret );
	Teardown();
	return KErrNone;
	}
	
/*******************************************************************
*
*	RunExecuteTestCaseDirectlyTrueL()
*
*******************************************************************/
TInt CMTPbkEmailAddressSelect::RunExecuteTestCaseDirectlyTrue1L()
	{
	SetupContactItemWithNameL();
	TPbkContactItemField* 	focusedField = NULL;
	TBool 					callDefaultDirectly = ETrue,
							ret = ETrue;
	
	ret = RunExecuteL(*iContactItem,focusedField,callDefaultDirectly );
	ASSERT( !ret );
	Teardown();
	return KErrNone;
	}

/*******************************************************************
*
*	RunExecuteTestCaseDirectlyTrueL()
*
*******************************************************************/
TInt CMTPbkEmailAddressSelect::RunExecuteTestCaseDirectlyTrue2L()
	{
	SetupContactItemWithCompanyNameL();
	TPbkContactItemField* 	focusedField = NULL;
	TBool 					callDefaultDirectly = ETrue,
							ret = ETrue;
	
	ret = RunExecuteL(*iContactItem,focusedField,callDefaultDirectly );
	ASSERT( !ret );
	Teardown();
	return KErrNone;
	}
	

/*******************************************************************
*
*	RunExecuteWithContactName()
*
*******************************************************************/
TInt CMTPbkEmailAddressSelect::RunExecuteWithContactNameL()
	{
	SetupContactItemWithNameL();
	TBool 					callDefaultDirectly = EFalse,
							ret = ETrue;
	// Focus to first name field
	TInt 					search = 0;
	TPbkContactItemField* 	focusedField = NULL;
	
	//focus on contacts first name
	focusedField = iContactItem->FindField( EPbkFieldIdFirstName, search);
	ASSERT( focusedField );

	ret = RunExecuteL(*iContactItem,focusedField,callDefaultDirectly );	
	ASSERT( !ret );
	Teardown();
	return KErrNone;
	}

/*******************************************************************
*
*	RunExecuteWithCompanyName()
*
*******************************************************************/
TInt CMTPbkEmailAddressSelect::RunExecuteWithCompanyNameL()
	{
	SetupContactItemWithCompanyNameL();
	TBool 					callDefaultDirectly = EFalse,
							ret = EFalse;
	// Focus to company name
	TInt 					search = 0;
	TPbkContactItemField* 	focusedField = NULL;
	
	//focus on company name
	focusedField = iContactItem->FindField( EPbkFieldIdCompanyName, search);
	ASSERT( focusedField );

	// Return value must be EFalse if canceled or no email address found.
	ret = RunExecuteL( *iContactItem, focusedField, callDefaultDirectly );	
	ASSERT(!ret);
	Teardown();
	return KErrNone;
	}

/*******************************************************************
*
*	RunExecuteWithOneEmail()
*
*******************************************************************/
TInt CMTPbkEmailAddressSelect::RunExecuteWithOneEmailL()
	{
	SetupContactItemWithNameL();
	TBool 					callDefaultDirectly = EFalse,
							ret = EFalse;
	TInt 					search = 0;
	TPbkContactItemField* 	focusedField = NULL;
	
	focusedField = iContactItem->FindField( EPbkFieldIdCompanyName, search);
	ASSERT( focusedField );

	ret = RunExecuteL( *iContactItem,focusedField,callDefaultDirectly );	
	ASSERT( !ret );//doubt deviation

	ret = iAddressAndNumberSelect->IsFirstEmailAddressL( *iContactItem );
	ASSERT( !ret );//doubt deviation
	Teardown();
	return KErrNone;
	}

/*******************************************************************
*
*	RunExecuteWithOneEmail()
*
*******************************************************************/
TInt CMTPbkEmailAddressSelect::RunExecuteWithOneEmail1L()
	{
	SetupDefaultContactItemL();
	TBool 					callDefaultDirectly = EFalse,
							ret = EFalse;
	TInt 					search = 0;
	TPbkContactItemField* 	focusedField = NULL;
	
	focusedField = iContactItem->FindField( EPbkFieldIdCompanyName, search);
	ASSERT( focusedField );

	ret = RunExecuteL( *iContactItem,focusedField,callDefaultDirectly );	
	ASSERT( ret );

	ret = iAddressAndNumberSelect->IsFirstEmailAddressL( *iContactItem );
	ASSERT( ret );
	Teardown();
	return KErrNone;
	}

/*******************************************************************
*
*	RunExecuteWithOneEmailFocusNullL()
*
*******************************************************************/
TInt CMTPbkEmailAddressSelect::RunExecuteWithOneEmailFocusNullL()
	{
	SetupDefaultContactItemL();
	TBool 					callDefaultDirectly = EFalse,
							ret = EFalse;
	TPbkContactItemField* 	focusedField = NULL;

	ret = RunExecuteL( *iContactItem, focusedField, callDefaultDirectly );	
	ASSERT( ret );

	ret = iAddressAndNumberSelect->IsFirstEmailAddressL( *iContactItem );
	ASSERT( ret );
	Teardown();
	return KErrNone;
	}

/*******************************************************************
*
*	RunExecuteWithOneEmailDirectlyTrueL()
*
*******************************************************************/
TInt CMTPbkEmailAddressSelect::RunExecuteWithOneEmailDirectlyTrueL()
	{
	SetupDefaultContactItemL();
	TBool 					callDefaultDirectly = ETrue,
							ret = EFalse;
	TPbkContactItemField* 	focusedField = NULL;

	ret = RunExecuteL( *iContactItem, focusedField, callDefaultDirectly );	
	ASSERT( ret );

	ret = iAddressAndNumberSelect->IsFirstEmailAddressL( *iContactItem );
	ASSERT( ret );
	Teardown();
	return KErrNone;
	}

/*******************************************************************
*
*	RunExecuteWithMultiEmail()
*
*******************************************************************/
TInt CMTPbkEmailAddressSelect::RunExecuteWithMultiEmailL()
	{	
	SetupContactItemWithTwoEmailFieldsL();
	// Set call default directly to false.
	TBool 					callDefaultDirectly = EFalse,
							ret = EFalse;
	// Later focus is set to EPbkFieldIdPhoneNumberHome field.
	TPbkContactItemField* 	focusedField = NULL; 
	TInt 					focusSearch = 0,
							focusIndex = 0;
	
	// Give focus to every phone number field
	for (focusIndex = 0; 
		focusIndex < iAddressAndNumberSelect->EmailAddresses(); focusIndex++)
		{
		focusedField= iContactItem->FindField( EPbkFieldIdEmailAddress, focusSearch );		
		ASSERT( focusedField);

		ret = RunExecuteL( *iContactItem, focusedField, callDefaultDirectly );
		ASSERT( ret);

		ret = iAddressAndNumberSelect->IsCorrectEmailAddressL( focusIndex, *iContactItem );
		ASSERT( ret);

		focusSearch++;
		} // focusIndex loop
	Teardown();
	return KErrNone;
	}

/*******************************************************************
*
*	RunExecuteWithMultiEmailFocusNullL()
*
*******************************************************************/
TInt CMTPbkEmailAddressSelect::RunExecuteWithMultiEmailFocusNullL()
	{
	SetupContactItemWithTwoEmailFieldsL();
	TPbkContactItemField* 	focusedField = NULL;
	TBool 					callDefaultDirectly = EFalse,
							ret = EFalse;
	TKeyCode 				selectionKeyCode = EKeyNull;
	TInt 					acceptKeyCounter = 0,
							downKeyCounter = 0,
							findEmailAddress = 0;

	for( acceptKeyCounter=1; acceptKeyCounter < KSelectKeys; acceptKeyCounter++ )
		{
		for ( findEmailAddress = 0; 
			findEmailAddress < iAddressAndNumberSelect->EmailAddresses(); 
			findEmailAddress++)
			{
			for( downKeyCounter = 0; downKeyCounter < findEmailAddress; downKeyCounter++ )
				{
				iSimulateKeyEvents->AddKeyEventCodeL( downCode );	
				}

			iSimulateKeyEvents->EmailSelectKeyCodeL( acceptKeyCounter, selectionKeyCode );
			ASSERT( selectionKeyCode != EKeyNull);

			SendKeyEventsL( selectionKeyCode );	

			ret = RunExecuteL( *iContactItem, focusedField, callDefaultDirectly );
			ASSERT( ret);

			ret = iAddressAndNumberSelect->IsCorrectEmailAddressL( findEmailAddress, *iContactItem );
			ASSERT( ret);

			ASSERT( ret );
			} // Email addresses loop ends
		}// Select keys loop ends
	Teardown();
	return KErrNone;
	}

/*******************************************************************
*
*	RunExecuteWithMultiEmailAndDefaultEmail()
*
*******************************************************************/
TInt CMTPbkEmailAddressSelect::RunExecuteWithMultiEmailAndDefaultEmailL()
	{	
	SetupContactItemWithTwoEmailFieldsL();
	// Set call default directly to true.
	TBool 					callDefaultDirectly = ETrue,
							ret = EFalse;
	// Set No focused field
	TPbkContactItemField* 	focusedField = NULL;
	TPbkContactItemField* 	noFocusedField = NULL;
	TInt 					focusSearch= 0,
							focusIndex = 0;

	for ( focusIndex = 0; 
			focusIndex < iAddressAndNumberSelect->EmailAddresses(); focusIndex++)
		{
		focusedField= iContactItem->FindField( EPbkFieldIdEmailAddress, focusSearch );		
		ASSERT( focusedField);

		iContactItem->SetDefaultEmailFieldL( focusedField );
		ASSERT( iContactItem->DefaultEmailField() == focusedField ); //doubt

		ret = RunExecuteL( *iContactItem, noFocusedField, callDefaultDirectly );	
		ASSERT( ret);
		
		ret = iAddressAndNumberSelect->IsCorrectEmailAddressL( focusIndex, *iContactItem );
		ASSERT( ret);

		focusSearch++;
		} // focusIndex loop
	Teardown();
	return KErrNone;
	}

/*******************************************************************
*
*	RunExecuteMultiEmailWithDefaultEmailAndFocus()
*
*******************************************************************/
TInt CMTPbkEmailAddressSelect::RunExecuteMultiEmailWithDefaultEmailAndFocusL()
	{	
	SetupContactItemWithTwoEmailFieldsL();
	TInt 					focusSearch = 0,
							defaultSearch = 0,
							focusIndex = 0,
							findEmailAddress = EFalse;
	TBool 					callDefaultDirectly = EFalse,
							ret = EFalse;
	TPbkContactItemField*	focusedField = NULL;
	TPbkContactItemField* 	defaultField = NULL;

	// Give focus to every e-mail address field
	for ( focusIndex = 0; 
		focusIndex < iAddressAndNumberSelect->EmailAddresses(); focusIndex++)
		{
		focusedField= iContactItem->FindField( EPbkFieldIdEmailAddress, focusSearch );		
		ASSERT( focusedField);

		defaultSearch = 0;
		for ( findEmailAddress = 0; 
			findEmailAddress < iAddressAndNumberSelect->EmailAddresses(); 
			findEmailAddress++)
			{
			defaultField = iContactItem->FindField( EPbkFieldIdEmailAddress, defaultSearch );		
			ASSERT( defaultField);

			iContactItem->SetDefaultEmailFieldL( defaultField );
			ASSERT( iContactItem->DefaultEmailField()==defaultField); //doubt
	
			ret = RunExecuteL( *iContactItem, focusedField,	callDefaultDirectly );	
			ASSERT( ret);

			ret = iAddressAndNumberSelect->IsCorrectEmailAddressL( focusIndex, *iContactItem );
			ASSERT( ret);

			defaultSearch++; // Take next e-mail address field.
			} // i loop

		focusSearch++; // update focus for the next possible search round
		} // index loop
		
	Teardown();
	return KErrNone;
	}

/*******************************************************************
*
*	RunExecuteMultiEmailWithFocus()
*
*******************************************************************/
TInt CMTPbkEmailAddressSelect::RunExecuteMultiEmailWithFocusL()
	{
	SetupContactItemWithTwoEmailFieldsL();
	TInt 					search = 0,
							acceptKeyCounter = 0,
							findEmailAddress = 0;
	TBool 					callDefaultDirectly = EFalse,
							ret = EFalse;
	TPbkContactItemField* 	focusedField = NULL;
	TPbkContactItemField* 	defaultField = NULL;
	TKeyCode 				selectionKeyCode = EKeyNull;

	focusedField = iContactItem->FindField( EPbkFieldIdCompanyName, search );		
	ASSERT( focusedField );

	// Go through different kind of accept key events.
	for( acceptKeyCounter=1; acceptKeyCounter < KSelectKeys; acceptKeyCounter++ )
		{
		search=0; 
		
		for ( findEmailAddress = 0; 
			findEmailAddress< iAddressAndNumberSelect->EmailAddresses(); 
			findEmailAddress++)
			{
			defaultField = iContactItem->FindField( EPbkFieldIdEmailAddress, search );		
			ASSERT( defaultField);

			iContactItem->SetDefaultEmailFieldL( defaultField );
			ASSERT( iContactItem->DefaultEmailField() == defaultField); //doubt

			// Simulate enter key code.
			iSimulateKeyEvents->EmailSelectKeyCodeL( acceptKeyCounter, selectionKeyCode );
			ASSERT( selectionKeyCode != EKeyNull );

			SendKeyEventsL( selectionKeyCode );	
	
			ret = RunExecuteL( *iContactItem, focusedField,	callDefaultDirectly );	
			ASSERT( ret);
		
			// Check return values
			ret = iAddressAndNumberSelect->IsCorrectEmailAddressL( findEmailAddress, *iContactItem );
			ASSERT( ret);

			search++; // Take next e-mail address field.
			}// for EmailAddresses
		}// for EmailSelectionKeys
	Teardown();
	return KErrNone;
	}
	
/*******************************************************************
*
*	RunExecuteMultiEmailWithNoFocus()
*
*******************************************************************/
TInt CMTPbkEmailAddressSelect::RunExecuteMultiEmailWithNoFocusL()
	{
	SetupContactItemWithTwoEmailFieldsL();
	// This test case is almost like previous 7.
	// Set call default directly to false.
	TBool 					callDefaultDirectly = EFalse,
							ret = EFalse;
	// Set No focused field
	TPbkContactItemField* 	focusedField = NULL;
	TPbkContactItemField* 	noFocusedField = NULL;
	TInt 					focusSearch = 0,
							acceptKeyCounter = 0,
							focusIndex = 0;
	TKeyCode 				selectionKeyCode = EKeyNull;

	for( acceptKeyCounter = 1; acceptKeyCounter < KSelectKeys; acceptKeyCounter++ )
		{
		focusSearch=0;
		for ( focusIndex = 0; 
			focusIndex < iAddressAndNumberSelect->EmailAddresses(); focusIndex++)
			{
			focusedField= iContactItem->FindField( EPbkFieldIdEmailAddress, focusSearch );
			ASSERT( focusedField);
		
			iContactItem->SetDefaultEmailFieldL( focusedField );
			ASSERT( iContactItem->DefaultEmailField() == focusedField );//doubt

			iSimulateKeyEvents->EmailSelectKeyCodeL( acceptKeyCounter, selectionKeyCode );
			ASSERT( selectionKeyCode != EKeyNull);

			SendKeyEventsL( selectionKeyCode );	
			
			ret = RunExecuteL( *iContactItem, noFocusedField, callDefaultDirectly );	
			ASSERT( ret );
		
			ret = iAddressAndNumberSelect->IsCorrectEmailAddressL( focusIndex, *iContactItem );
			ASSERT( ret);

			focusSearch++;
			} // focusIndex loop ends
		} // acceptKeyCounter loop ends
	Teardown();
	return KErrNone;
	}

/*******************************************************************
*
*	RunExecuteTestSoftKeys1L()
*
*******************************************************************/
TInt CMTPbkEmailAddressSelect::RunExecuteTestSoftKeys1L()
	{
	SetupContactItemWithTwoEmailFieldsL();
	TKeyCode 				testedSoftKeyCode = rightSoftKeyCode;
	TInt 					defaultSearch = 0,
							focusIndex = 0;
	
	// Give focus to every e-mail address field
	for ( focusIndex=0; 
		  focusIndex < iAddressAndNumberSelect->EmailAddresses(); focusIndex++ )
		{			
    	TPbkContactItemField* defaultField = iContactItem->FindField( 
    	                EPbkFieldIdEmailAddress, defaultSearch );		
		ASSERT( defaultField);

		iContactItem->SetDefaultEmailFieldL( defaultField );
		ASSERT( iContactItem->DefaultEmailField() ==  defaultField); //doubt
						

		SendKeyEventsL( testedSoftKeyCode );	

    	// Set call default directly to false.
    	TBool 					callDefaultDirectly = EFalse,
    							ret = EFalse;
    	TPbkContactItemField* 	noFocusedField = NULL;

		ret = RunExecuteL( *iContactItem, noFocusedField, callDefaultDirectly );	
			
		ASSERT( !ret );
			
		defaultSearch++;
		} // focusIndex loop
	Teardown();
	return KErrNone;
	}

/*******************************************************************
*
*	RunExecuteTestSoftKeys2L()
*
*******************************************************************/
TInt CMTPbkEmailAddressSelect::RunExecuteTestSoftKeys2L()
	{
	SetupContactItemWithTwoEmailFieldsL();
	TKeyCode 				testedSoftKeyCode = leftSoftKeyCode;
	TInt 					defaultSearch = 0,
							focusIndex = 0;
	
	// Give focus to every e-mail address field
	for ( focusIndex=0; 
		  focusIndex < iAddressAndNumberSelect->EmailAddresses(); focusIndex++ )
		{			
    	TPbkContactItemField* defaultField = iContactItem->FindField( 
    	                EPbkFieldIdEmailAddress, defaultSearch );		
		ASSERT( defaultField);

		iContactItem->SetDefaultEmailFieldL( defaultField );
		ASSERT( iContactItem->DefaultEmailField() ==  defaultField);//doubt
		SendKeyEventsL( testedSoftKeyCode );	

    	// Set call default directly to false.
    	TBool 					callDefaultDirectly = EFalse,
    							ret = EFalse;
    							
    	TPbkContactItemField* 	noFocusedField = NULL;

		ret = RunExecuteL( *iContactItem, noFocusedField, callDefaultDirectly );	
			
		ASSERT( ret);

		ret = iAddressAndNumberSelect->IsCorrectEmailAddressL( focusIndex, *iContactItem );
		ASSERT( ret);
			
		defaultSearch++;
		} // focusIndex loop
	Teardown();
	return KErrNone;
	}

/*******************************************************************
*
*	RunExecuteL ()
*
*******************************************************************/
TBool CMTPbkEmailAddressSelect::RunExecuteL(
				const CPbkContactItem& aItem, 
                const TPbkContactItemField* aFocusedField,
                const TBool& aCallDefaultDirectly)
	{
	TBool	ret = EFalse;

	iEmailAddressSelect = new(ELeave) CPbkEmailAddressSelect;

	CPbkEmailAddressSelect::TParams params(aItem);
	params.SetFocusedField(aFocusedField);
	params.SetUseDefaultDirectly(aCallDefaultDirectly);

	ret = iEmailAddressSelect->ExecuteLD(params);
	//ExecuteLD deletes iEmailAddressSelect but it has to be zeroed also
	iEmailAddressSelect = NULL;

	return ret;
	}

/*********************** SETUP **************************************/

void CMTPbkEmailAddressSelect::SetupEmptyContactItemL()
	{    
    iContactItem = iContactEngine->CreateEmptyContactL();
    }

void CMTPbkEmailAddressSelect::SetupContactItemWithCompanyNameL()
	{    
    iContactItem = iContactEngine->CreateEmptyContactL();
	iAddressAndNumberSelect->FillContactCompanyNameFieldL( *iContactItem, iContactEngine );
    }

void CMTPbkEmailAddressSelect::SetupContactItemWithNameL()
	{
	iContactItem = iContactEngine->CreateEmptyContactL();
	iAddressAndNumberSelect->FillContactNameFieldL( *iContactItem, iContactEngine );
	}

void CMTPbkEmailAddressSelect::SetupDefaultContactItemL()
	{    
    iContactItem = iContactEngine->CreateEmptyContactL();
    iAddressAndNumberSelect->FillContactFieldsL( *iContactItem );
    }

void CMTPbkEmailAddressSelect::SetupContactItemWithTwoEmailFieldsL()
	{    
    iContactItem = iContactEngine->CreateEmptyContactL();
    
    iAddressAndNumberSelect->FillContactWithMultipleFieldsL(
			*iContactItem, iContactEngine, ETrue,
			EFalse, EFalse, EFalse);				
	}

void CMTPbkEmailAddressSelect::SendKeyEventsL( TKeyCode& aTestedSoftKeyCode )
	{

	iSimulateKeyEvents->ClearAllKeyEventsL();
	iSimulateKeyEvents->AddKeyEventCodeL( aTestedSoftKeyCode );	
	iSimulateKeyEvents->CallBackStartL();

	}

/*********************** TEARDOWN ***********************************/

void CMTPbkEmailAddressSelect::Teardown(  )
    {
	delete iContactItem;
	iContactItem = NULL;
	
    }


//  [End of File] - Do not remove
