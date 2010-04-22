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
#include "MTPbkIconId.h"
#include <PbkIconId.hrh>  // Values to be tested

//  INTERNAL INCLUDES
#include "PbkIconId30.hrh"  // Reference values

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
// CMTPbkIconId::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CMTPbkIconId::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CMTPbkIconId::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CMTPbkIconId::RunMethodL( 
    CStifItemParser& aItem ) 
    {

     TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "Enum_values", CMTPbkIconId::CheckEnumValuesL ),
        //ADD NEW ENTRY HERE
        // [test cases entries] - Do not remove

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

//----------------------------------------------------------------------------
void CMTPbkIconId::SetupL(  )
    {
    }

void CMTPbkIconId::Teardown(  )
    {
    }


//----------------------------------------------------------------------------
TInt CMTPbkIconId::CheckEnumValuesL()
    {
    ASSERT(EPbkNullIconId                == EPbkNullIconId_30);
    ASSERT(EPbkqgn_indi_marked_add       == EPbkqgn_indi_marked_add_30);
    ASSERT(EPbkqgn_prop_checkbox_off     == EPbkqgn_prop_checkbox_off_30);
    ASSERT(EPbkqgn_prop_checkbox_on      == EPbkqgn_prop_checkbox_on_30);
    ASSERT(EPbkqgn_prop_nrtyp_phone      == EPbkqgn_prop_nrtyp_phone_30);
    ASSERT(EPbkqgn_prop_nrtyp_home       == EPbkqgn_prop_nrtyp_home_30);
    ASSERT(EPbkqgn_prop_nrtyp_work       == EPbkqgn_prop_nrtyp_work_30);
    ASSERT(EPbkqgn_prop_nrtyp_mobile     == EPbkqgn_prop_nrtyp_mobile_30);
    ASSERT(EPbkqgn_prop_nrtyp_fax        == EPbkqgn_prop_nrtyp_fax_30); 
    ASSERT(EPbkqgn_prop_nrtyp_pager      == EPbkqgn_prop_nrtyp_pager_30);
    ASSERT(EPbkqgn_prop_nrtyp_email      == EPbkqgn_prop_nrtyp_email_30);
    ASSERT(EPbkqgn_prop_nrtyp_address    == EPbkqgn_prop_nrtyp_address_30);
    ASSERT(EPbkqgn_prop_nrtyp_url        == EPbkqgn_prop_nrtyp_url_30);
    ASSERT(EPbkqgn_prop_nrtyp_date       == EPbkqgn_prop_nrtyp_date_30);
    ASSERT(EPbkqgn_prop_nrtyp_note       == EPbkqgn_prop_nrtyp_note_30);
    ASSERT(EPbkqgn_prop_nrtyp_tone       == EPbkqgn_prop_nrtyp_tone_30);
    ASSERT(EPbkqgn_prop_group_open_tab1  == EPbkqgn_prop_group_open_tab1_30);
    ASSERT(EPbkqgn_prop_group_small      == EPbkqgn_prop_group_small_30);
    ASSERT(EPbkqgn_graf_pb_status_backg  == EPbkqgn_graf_pb_status_backg_30);
    ASSERT(EPbkqgn_prop_nrtyp_empty      == EPbkqgn_prop_nrtyp_empty_30);
    ASSERT(EPbkqgn_indi_voice_add        == EPbkqgn_indi_voice_add_30);
    ASSERT(EPbkqgn_indi_qdial_add        == EPbkqgn_indi_qdial_add_30);
    ASSERT(EPbkqgn_prop_nrtyp_video      == EPbkqgn_prop_nrtyp_video_30);
    ASSERT(EPbkqgn_prop_nrtyp_voip       == EPbkqgn_prop_nrtyp_voip_30);
    ASSERT(EPbkqgn_prop_nrtyp_poc        == EPbkqgn_prop_nrtyp_poc_30);
    ASSERT(EPbkqgn_prop_nrtyp_swis       == EPbkqgn_prop_nrtyp_swis_30); 
    ASSERT(EPbkqgn_prop_nrtyp_sip        == EPbkqgn_prop_nrtyp_sip_30);
    ASSERT(EPbkqgn_menu_empty_cxt        == EPbkqgn_menu_empty_cxt_30);
    ASSERT(EPbkqgn_graf_phob_thumbnail_backg
                                               == EPbkqgn_graf_phob_thumbnail_backg_30);
    return KErrNone;
    }

//  [End of File] - Do not remove
