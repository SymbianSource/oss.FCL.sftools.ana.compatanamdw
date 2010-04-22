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



#ifndef BCAPPCONTENTMANAGEMENT_H
#define BCAPPCONTENTMANAGEMENT_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>

#include "BCTestMediaFetch.h"


// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
#define TEST_CLASS_VERSION_MAJOR 30
#define TEST_CLASS_VERSION_MINOR 9
#define TEST_CLASS_VERSION_BUILD 38

// Logging path
_LIT( KBCAppContentManagementLogPath, "\\logs\\testframework\\BCAppContentManagement\\" ); 
// Log file
_LIT( KBCAppContentManagementLogFile, "BCAppContentManagement.txt" ); 
_LIT( KBCAppContentManagementLogFileWithTitle, "BCAppContentManagement_[%S].txt" );

// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class CBCAppContentManagement;

// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;

// CLASS DECLARATION

/**
*  CBCAppContentManagement test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CBCAppContentManagement) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CBCAppContentManagement* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CBCAppContentManagement();

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
        CBCAppContentManagement( CTestModuleIf& aTestModuleIf );

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
        virtual TInt TestRun1L( CStifItemParser& aItem );
        virtual TInt TestRun2L( CStifItemParser& aItem );
        virtual TInt TestRun3L( CStifItemParser& aItem );
        virtual TInt TestRun4L( CStifItemParser& aItem );
        virtual TInt TestRun5L( CStifItemParser& aItem );
        virtual TInt TestRun6L( CStifItemParser& aItem );
        virtual TInt TestRun7L( CStifItemParser& aItem );
        virtual TInt TestRun8L( CStifItemParser& aItem );
        virtual TInt TestRun9L( CStifItemParser& aItem );
        virtual TInt TestRun10L( CStifItemParser& aItem );
        virtual TInt TestRun11L( CStifItemParser& aItem );
        virtual TInt TestRun12L( CStifItemParser& aItem );
		virtual TInt TestRun13L( CStifItemParser& aItem );
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
    
    		BCTestMediaFetch* imFetch;
        
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

#endif      // BCAPPCONTENTMANAGEMENT_H

// End of File
