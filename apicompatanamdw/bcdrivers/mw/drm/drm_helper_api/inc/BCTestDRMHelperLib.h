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



#ifndef BCTESTDRMHELPERLIB_H
#define BCTESTDRMHELPERLIB_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include <TestclassAssert.h>
#include <f32file.h>
#include <apmstd.h>
#include <caf/data.h>
// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
#define TEST_CLASS_VERSION_MAJOR 31
#define TEST_CLASS_VERSION_MINOR 9
#define TEST_CLASS_VERSION_BUILD 40

// Logging path
_LIT( KBCTestDRMHelperLibLogPath, "\\logs\\testframework\\BCTestDRMHelperLib\\" ); 
// Log file
_LIT( KBCTestDRMHelperLibLogFile, "BCTestDRMHelperLib.txt" ); 
_LIT( KBCTestDRMHelperLibLogFileWithTitle, "BCTestDRMHelperLib_[%S].txt" );

// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class CBCTestDRMHelperLib;
class CDRMHelperRightsConstraints;
class CDRMHelper;
//class ContentAccess;
// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;

// CLASS DECLARATION

/**
*  CBCTestDRMHelperLib test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CBCTestDRMHelperLib) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CBCTestDRMHelperLib* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CBCTestDRMHelperLib();

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
        CBCTestDRMHelperLib( CTestModuleIf& aTestModuleIf );

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
        
        void CheckPermissionL( CDRMHelperRightsConstraints* aConstraint );
		void OpenFileL( const TDesC& aFileName, RFile& aFile );
		HBufC8* ConvertTo8BitLC( HBufC* aBuffer );
		HBufC* ContentUriLC( const TDesC& aFileName );
		ContentAccess::CData* CreateContentObjectLC( const TDesC& aFileName );
		
        virtual TInt ExampleL( CStifItemParser& aItem );
        
        
        TInt LaunchRightsManagerUIL();
		TInt LaunchRightsManagerUIContentUriL();
		TInt LaunchRightsManagerUIFileHandleL();
		TInt HandleErrorExpiredFileL();
		TInt HandleErrorNoRightsUriL();
		TInt HandleErrorNoRightsFileHandleL();
		TInt CheckRightsAmountFileL		();
		TInt CheckRightsAmountFileHandleL();
		TInt CheckRightsAmountUriL();
		TInt CheckRightsPercentFileL();
		TInt CheckRightsPercentFileHandleL();
		TInt GetRightsDetailsFileL();
		TInt GetRightsDetailsFileHandleL();
		TInt SetAutomatedFileL();
		TInt SetAutomatedUriL();
		TInt SetAutomatedFileHandleL();
		TInt ShowAutomatedNoteFileL();
		TInt ShowAutomatedNoteUriL();
		TInt ShowAutomatedNoteFileHandleL();
		TInt SetAutomatedPassiveFileL();
		TInt SetAutomatedPassiveUriL();
		TInt SetAutomatedPassiveFileHandleL();
		TInt SetAutomatedSilentFileL();
		TInt SetAutomatedSilentUriL();
		TInt SetAutomatedSilentFileHandleL();
		TInt RemoveAutomatedFileL();
		TInt RemoveAutomatedUriL();
		TInt RemoveAutomatedFileHandleL();
		TInt RemoveAutomatedPassiveFileL();
		TInt RemoveAutomatedPassiveUriL();
		TInt RemoveAutomatedPassiveFileHandleL();
		TInt CanSetAutomatedFileL();
		TInt CanSetAutomatedUriL();
		TInt CanSetAutomatedFileHandleL();
		TInt IndicateIdleL();
		TInt SetCountLimit1L ();
		TInt SetTimeLimit1L();
		TInt SetPercentageLimit1L();
		TInt GetContentUriListL();
		TInt DataTypesCountL();
		TInt SupportedDataTypeL();
		TInt RegisterDataTypeL();
		TInt UnregisterDataTypeL();
		TInt SupportedDrmMethodsL();
		TInt ConsumeUriL();
		TInt ConsumeFileL();
		TInt ConsumeFileHandleL();
		TInt ActivateContentFileL();
		TInt ActivateContentDataL();
		TInt HasPreviewFileL();
		TInt HasPreviewDataL();
		TInt GetPreviewRightsFileL();
		TInt GetPreviewRightsDataL();
		TInt EmbeddedPreviewCompletedFileL();
		TInt EmbeddedPreviewCompletedDataL();
		TInt HasInfoUrlFileL();
		TInt HasInfoUrlDataL();
		TInt OpenInfoUrlFileL();
		TInt OpenInfoUrlDataL();
		TInt SetPreviewMediaTypeL();
		TInt HandleErrorOrPreviewFileL();
		TInt HandleErrorOrPreviewFileHandleL();
		TInt HandleErrorOrPreviewSilentFileL();
		TInt HandleErrorOrPreviewSilentFileHandleL();

        void SetupL();
        void Teardown();
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
        
    CDRMHelper*         iHelper;
    RFs                 iFs;
	HBufC* 				contentUri;
    HBufC8* 			contentUri8;
    RFile 				file;
    TBool				expired;
    CDRMHelperRightsConstraints* play;
    CDRMHelperRightsConstraints* display;
    CDRMHelperRightsConstraints* print;
    CDRMHelperRightsConstraints* execute;
	TBool sendingAllowed;
    TBool automatedUseAllowed;
    RPointerArray<HBufC8> *uriList;
    TInt supportedDataTypes;
	TFileName fileName;
	TInt retval;
    TDataType dataType;
	TInt drmMethod;
	HBufC8* previewUrl;
	TBool buyRights;
    TBool infoUrlExists;
    HBufC8* infoUrl;
    
//	CDRMHelper::TDRMHelperOMALevel omaLevel;	
	//CDRMHelper::TDRMHelperPreviewType previewType;
	//ContentAccess::CData* content;


	
	
    public:     // Friend classes
        //?friend_class_declaration;
    protected:  // Friend classes
        //?friend_class_declaration;
    private:    // Friend classes
        //?friend_class_declaration;

    };

#endif      // BCTESTDRMHELPERLIB_H

// End of File
