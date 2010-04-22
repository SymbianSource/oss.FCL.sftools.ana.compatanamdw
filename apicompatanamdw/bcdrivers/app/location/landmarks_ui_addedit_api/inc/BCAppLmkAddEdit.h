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



#ifndef BCAPPLMKADDEDIT_H
#define BCAPPLMKADDEDIT_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>

#include "BCAppLmkEditorEngine.h"


// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
#define TEST_CLASS_VERSION_MAJOR 30
#define TEST_CLASS_VERSION_MINOR 9
#define TEST_CLASS_VERSION_BUILD 38

// Logging path
_LIT( KBCAppLmkAddEditLogPath, "\\logs\\testframework\\BCAppLmkAddEdit\\" ); 
// Log file
_LIT( KBCAppLmkAddEditLogFile, "BCAppLmkAddEdit.txt" ); 
_LIT( KBCAppLmkAddEditLogFileWithTitle, "BCAppLmkAddEdit_[%S].txt" );

// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class CBCAppLmkAddEdit;

// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;

// CLASS DECLARATION

/**
*  CBCAppLmkAddEdit test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CBCAppLmkAddEdit) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CBCAppLmkAddEdit* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CBCAppLmkAddEdit();

    public: // New functions

        /**
        * ?member_description.
        * @since ?Series60_version
        * @param ?arg1 ?description
        * @return ?description
        */
        //?type ?member_function( ?type ?arg1 );

    public: // Functions from base classes

        /**
        * From CScriptBase Runs a script line.
        * @since ?Series60_version
        * @param aItem Script line containing method name and parameters
        * @return Symbian OS error code
        */
        virtual TInt RunMethodL( CStifItemParser& aItem );
        
    protected:  // New functions

        /**
        * ?member_description.
        * @since ?Series60_version
        * @param ?arg1 ?description
        * @return ?description
        */
        //?type ?member_function( ?type ?arg1 );

    protected:  // Functions from base classes

        /**
        * From ?base_class ?member_description
        */
        //?type ?member_function();

    private:

        /**
        * C++ default constructor.
        */
        CBCAppLmkAddEdit( CTestModuleIf& aTestModuleIf );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

        // Prohibit copy constructor if not deriving from CBase.
        // ?classname( const ?classname& );
        // Prohibit assigment operator if not deriving from CBase.
        // ?classname& operator=( const ?classname& );

        /**
        * Frees all resources allocated from test methods.
        * @since ?Series60_version
        */
        void Delete();

        /**
        * Test methods are listed below. 
        */

        /**
        * Example test method.
        * @since ?Series60_version
        * @param aItem Script line containing parameters.
        * @return Symbian OS error code.
        */
        virtual TInt ExampleL( CStifItemParser& aItem );
        virtual TInt TestNewL( CStifItemParser& aItem );
        virtual TInt TestNew2L( CStifItemParser& aItem );
        virtual TInt TestExecuteLD( CStifItemParser& aItem );
        virtual TInt TestSetMopParent( CStifItemParser& aItem );
        virtual TInt TestSetHelpContext( CStifItemParser& aItem );
        virtual TInt TestDisableMapAndNaviOptions( CStifItemParser& aItem );
        
        //virtual TInt TestSetMoParent( CStifItemParser& aItem );
        /**
         * Method used to log version of test class
         */
        void SendTestClassVersion();

        //ADD NEW METHOD DEC HERE
        //[TestMethods] - Do not remove

    public:     // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    protected:  // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    private:    // Data  
    CLmkAddEditEngine* engine;
        // ?one_line_short_description_of_data
        //?data_declaration;

        // Reserved pointer for future extension
        //TAny* iReserved;

    public:     // Friend classes
        //?friend_class_declaration;
    protected:  // Friend classes
        //?friend_class_declaration;
    private:    // Friend classes
        //?friend_class_declaration;

    };

#endif      // BCAPPLMKADDEDIT_H

// End of File
