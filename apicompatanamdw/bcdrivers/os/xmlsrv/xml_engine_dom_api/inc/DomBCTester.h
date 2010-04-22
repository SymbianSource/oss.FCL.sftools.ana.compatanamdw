/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Header file for XeDomBCTester
*
*/



#ifndef __XE_DOM_BC_TESTER_H_
#define __XE_DOM_BC_TESTER_H_

//  INCLUDES
#include <xmlengdom.h>

#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include <Xml\XmlParserErrors.h>

#include <f32file.h>


// MACROS
_LIT( KXML_TestLogPath, "\\spd_logs\\xml" ); // Logging path
_LIT( KXML_TestLogFile, "XeDomBcTester_log.txt" ); // Log file
_LIT( KTEST_NAME, "XeDomBcTester" );


// FORWARD DECLARATIONS
class CXML_Test;
class RXmlEngXPathResult;

// DATA TYPES

// CLASS DECLARATION

/**
*  CDomBCTester test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CDomBCTester) : public CScriptBase
{
  public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CDomBCTester* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CDomBCTester();

  public: // New functions

    /**
    * ?member_description.
    * @since ?Series60_version
    * @param ?arg1 ?description
    * @return ?description
    */

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

  protected:  // Functions from base classes

    /**
    * From ?base_class ?member_description
    */

  private:

    /**
    * C++ default constructor.
    */
    CDomBCTester( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
    * Frees all resources allocated from test methods.
    * @since ?Series60_version
    */
    void Delete();


    /**
    * Test methods are listed below.
    */
    /**************************** TEST *************************************/
    /**
    * comparing two files ( skip or not skip white space ).
    * @since ?Series60_version
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    TInt CompareFilesL( CStifItemParser& aItem );

    /**
    * comparing two strings;
    * @since ?Series60_version
    * @param aString string.
    * @param aDesc string.
    * @return true if strings are the same.
    */
    TBool CompareDescAndChar(const char* aString, TDesC8& aDesc);

    /**
    * comparing two strings;
    * @since ?Series60_version
    * @param aString string.
    * @param aDesc string.
    * @return true if strings are the same.
    */
    TBool CompareDescAndChar(const TUint8* aString,TDesC8& aDesc);

    /**
    * comparing two strings;
    * @since ?Series60_version
    * @param aString1 string.
    * @param aString2 string.
    * @return true if strings are the same.
    */
    TBool CompareChars(const char* aString1,const char* aString2);


    /******************************* DOM *************************************/
    /**
    * Parsing xml file using SAX. As output is generated xml file.
    * @since ?Series60_version
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt ParseFileDomL( CStifItemParser& aItem );
    virtual TInt SaveXmlToFileDomL( CStifItemParser& aItem );
    virtual TInt CreateDocumentL( CStifItemParser& aItem );
    virtual TInt CheckInnerXmlL( CStifItemParser& );
    virtual TInt CheckOuterXmlL( CStifItemParser& );
    virtual TInt CreateDocumentFromNodeL( CStifItemParser& aItem );
    virtual TInt CheckDocumentParametersL( CStifItemParser& aItem );
    virtual TInt CreateDocumentElementL( CStifItemParser& aItem );
    virtual TInt SaveXmlToBufferUTF16L( CStifItemParser& aItem );
    virtual TInt TestNodeFilterL( CStifItemParser& aItem );
    virtual TInt CloneDocumentL( CStifItemParser& aItem );
    virtual TInt CheckNotNullElementL( CStifItemParser& aItem );
    virtual TInt CheckSiblingFunctionsL( CStifItemParser& aItem );
    virtual TInt CheckNodeParametersL( CStifItemParser& aItem);
    virtual TInt ParentNodesL( CStifItemParser& aItem );
    virtual TInt CheckNamespacesL( CStifItemParser& aItem );
    virtual TInt CheckProcessingInstructionL( CStifItemParser& aItem );
    virtual TInt CheckCommentsL( CStifItemParser& aItem );
    virtual TInt CheckCDATAL( CStifItemParser& aItem);
    virtual TInt CheckTextNodeL( CStifItemParser& aItem);
    virtual TInt CheckNodeValueL(CStifItemParser& aItem);
    virtual TInt NodeNamespacePocessingL( CStifItemParser& aItem );
    virtual TInt CheckEntityRefL( CStifItemParser& aItem );
    virtual TInt NodeTreeModificationL( CStifItemParser& aItem);
    virtual TInt NodeTreeDeletingL( CStifItemParser& aItem);
    virtual TInt CheckNodeListL( CStifItemParser& aItem );
    virtual TInt ElementNamespacePocessingL( CStifItemParser& aItem );
    virtual TInt CheckAttributesL( CStifItemParser& aItem );
    virtual TInt CheckElementAttributesL( CStifItemParser& aItem );
    virtual TInt CheckModifAttributesL( CStifItemParser& aItem );
    virtual TInt AddingAttributesL( CStifItemParser& aItem );
    virtual TInt AddingElementsL( CStifItemParser& aItem );
    virtual TInt CheckModifElementL( CStifItemParser& aItem );
    virtual TInt SetElementTextL( CStifItemParser& aItem );
    virtual TInt CheckNextL( CStifItemParser& aItem );
    virtual TInt AddXmlIdL( CStifItemParser& aItem );
    virtual TInt FindXmlIdL( CStifItemParser& aItem );
    virtual TInt SetValueNoEncTestL(CStifItemParser& aItem);
    virtual TInt CreateDocument2L( CStifItemParser& aItem );
    virtual TInt CreateEntityReferenceTestL(CStifItemParser& aItem);
    virtual TInt ParseFileDom2L( CStifItemParser& aItem );
    virtual TInt ParseFileDom3L( CStifItemParser& aItem );
    virtual TInt LookupNamespaceByPrefixTestL( CStifItemParser& aItem );
    virtual TInt LookupNamespaceByUriTestL( CStifItemParser& aItem );
    virtual TInt LookupNamespaceByPrefixTest2L( CStifItemParser& aItem );
    virtual TInt LookupNamespaceByUriTest2L( CStifItemParser& aItem );
    virtual TInt RemoveChildrenTestL( CStifItemParser& aItem);
    virtual TInt UserDataTestL( CStifItemParser& aItem );
    virtual TInt BaseUriTestL( CStifItemParser& /*aItem*/ );
    virtual TInt AddXmlIdTestL( CStifItemParser& aItem);
    virtual TInt AddXmlId2L( CStifItemParser& aItem );
    virtual TInt AddXmlId3L( CStifItemParser& aItem );
    virtual TInt DocumentSaveL(CStifItemParser& aItem );
	
	//XPath functions
	virtual TInt TestReplaceWithL(CStifItemParser&  /*aItem*/ );
	virtual TInt TestSetDataSerializerL(CStifItemParser&  /*aItem*/ );
	virtual TInt TestCreateDocumentFragmentL(CStifItemParser& /*aItem*/ );
	virtual TInt TestToNumberL(CStifItemParser& /*aItem*/ );
	virtual TInt TestToStringL(CStifItemParser& /*aItem*/ );
	virtual TInt TestToBooleanL(CStifItemParser& /*aItem*/ );
	virtual TInt TestExtensionFunctionL(CStifItemParser& /*aItem*/);
	virtual TInt TestExtensionVectorFunctionL(CStifItemParser& /*aItem*/);
	virtual TInt TestAddNativeExtensionVectorFunctionL(CStifItemParser& /*aItem*/);
	virtual TInt TestResetExtensionFunctionsL(CStifItemParser& /*aItem*/);
	virtual TInt TestRenameElementL(CStifItemParser& /*aItem*/);

    /******************************* BinCont ************************************/
    /**
    * Test binary container function
    * @since ?Series60_version
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt BinaryContainerL(CStifItemParser& aItem);
    virtual TInt PartialBinaryContainerL(CStifItemParser& aItem);
    virtual TInt TestCreateBinaryContainerL( TPtrC8 aCid, TPtrC8 binaryDataPtr, TPtrC pOut);
    virtual TInt TestSizeOfBinaryContainerL( RXmlEngDocument& iDocument, TPtrC8 aCid,TPtrC8 binaryDataPtr, TInt size );
    virtual TInt TestBinaryContainerNodeTypeL( RXmlEngDocument& iDocument, TPtrC8 aCid,TPtrC8 bufferPtr );
    virtual TInt TestContentsOfBinaryContainerL( RXmlEngDocument& iDocument, TPtrC8 aCid,TPtrC8 binaryDataPtr, TPtrC pOut1);
    virtual TInt TestMoveBinaryContainerL( RXmlEngDocument& iDoc1, RXmlEngDocument& iDoc2, TPtrC8 aCid, TPtrC8 binaryDataPtr, TPtrC pOut1, TPtrC pOut2);
    virtual TInt TestRemoveBinaryContainerL( RXmlEngDocument& iDocument, TPtrC8 aCid,TPtrC8 binaryDataPtr, TPtrC pOut1, TPtrC pOut2 );
    virtual TInt TestCopyBinaryContainerL( RXmlEngDocument& iDocument, TPtrC8 aCid, TPtrC8 binaryDataPtr, TPtrC pOut1, TPtrC pOut2 );
    virtual TInt TestReplaceBinaryContainerL( RXmlEngDocument& iDoc1, RXmlEngDocument& iDoc2,
    TPtrC8 aCid, TPtrC8 binaryDataPtr, TPtrC pOut1, TPtrC pOut2);
    virtual TInt TestAppendContentsL(CStifItemParser& aItem);
    virtual TInt BinaryContainer_GetListL( CStifItemParser& aItem );
    virtual TInt BinaryContainer_GetList2L( CStifItemParser& aItem );
    virtual TInt BinaryContainer_CidErrorL( CStifItemParser& aItem );
    virtual TInt BinaryContainer_RemoveL( CStifItemParser& /*aItem*/ );
    virtual TInt BinaryContainer_Remove2L( CStifItemParser& /*aItem*/ );
    virtual TInt BinaryContainer_Remove3L( CStifItemParser& /*aItem*/ );
    virtual TInt BinaryContainer_UnlinkL( CStifItemParser& /*aItem*/ );
    virtual TInt BinaryContainer_ReplaceWithL( CStifItemParser& /*aItem*/ );
    virtual TInt BinaryContainer_SubstituteForL( CStifItemParser& /*aItem*/ );
    virtual TInt BinaryContainer_CopyL( CStifItemParser& /*aItem*/ );
    virtual TInt BinaryContainer_Copy2L( CStifItemParser& /*aItem*/ );
    virtual TInt BinaryContainer_Copy3L( CStifItemParser& /*aItem*/ );
    virtual TInt BinaryContainer_Copy4L( CStifItemParser& /*aItem*/ );
    virtual TInt BinaryContainer_CopyToL( CStifItemParser& /*aItem*/ );
    virtual TInt BinaryContainer_CloneL( CStifItemParser& /*aItem*/ );
    virtual TInt BinaryContainer_AdoptNodeL( CStifItemParser& /*aItem*/ );
    virtual TInt BinaryContainer_SetAsFirstSiblingL( CStifItemParser& /*aItem*/ );
    virtual TInt BinaryContainer_SetAsLastSiblingL( CStifItemParser& /*aItem*/ );
    virtual TInt BinaryContainer_MoveBeforeSiblingL( CStifItemParser& /*aItem*/ );
    virtual TInt BinaryContainer_MoveAfterSiblingL( CStifItemParser& /*aItem*/ );
    virtual TInt BinaryContainer_MoveToL( CStifItemParser& /*aItem*/ );
    virtual TInt BinaryContainer_ReconcileNamespacesL( CStifItemParser& /*aItem*/ );

    /******************************* CHUNK *************************************/
    virtual TInt ParseFileChunkL( CStifItemParser& aItem );
    virtual TInt ChunkContainer_GetListL( CStifItemParser& aItem );
    virtual TInt ChunkContainer_CidL( CStifItemParser& aItem );
    virtual TInt ChunkContainer_CidErrorL( CStifItemParser& aItem );
    virtual TInt ChunkContainer_ChunkL( CStifItemParser& /*aItem*/ );
    virtual TInt ChunkContainer_OffsetL( CStifItemParser& /*aItem*/ );
    virtual TInt ChunkContainer_SizeL( CStifItemParser& /*aItem*/ );
    virtual TInt ChunkContainer_NodeTypeL( CStifItemParser& /*aItem*/ );
    virtual TInt ChunkContainer_RemoveL( CStifItemParser& /*aItem*/ );
    virtual TInt ChunkContainer_Remove2L( CStifItemParser& /*aItem*/ );
    virtual TInt ChunkContainer_Remove3L( CStifItemParser& aItem );
    virtual TInt ChunkContainer_UnlinkL( CStifItemParser& /*aItem*/ );
    virtual TInt ChunkContainer_ReplaceWithL( CStifItemParser& /*aItem*/ );
    virtual TInt ChunkContainer_SubstituteForL( CStifItemParser& /*aItem*/ );
    virtual TInt ChunkContainer_CopyL( CStifItemParser& /*aItem*/ );
    virtual TInt ChunkContainer_Copy2L( CStifItemParser& /*aItem*/ );
    virtual TInt ChunkContainer_Copy3L( CStifItemParser& /*aItem*/ );
    virtual TInt ChunkContainer_Copy4L( CStifItemParser& /*aItem*/ );
    virtual TInt ChunkContainer_CopyToL( CStifItemParser& /*aItem*/ );
    virtual TInt ChunkContainer_CloneL( CStifItemParser& /*aItem*/ );
    virtual TInt ChunkContainer_AdoptNodeL( CStifItemParser& /*aItem*/ );
    virtual TInt ChunkContainer_SetAsFirstSiblingL( CStifItemParser& /*aItem*/ );
    virtual TInt ChunkContainer_SetAsLastSiblingL( CStifItemParser& /*aItem*/ );
    virtual TInt ChunkContainer_MoveBeforeSiblingL( CStifItemParser& /*aItem*/ );
    virtual TInt ChunkContainer_MoveAfterSiblingL( CStifItemParser& /*aItem*/ );
    virtual TInt ChunkContainer_MoveToL( CStifItemParser& /*aItem*/ );
    virtual TInt ChunkContainer_ReconcileNamespacesL( CStifItemParser& /*aItem*/ );

    /******************************* FILE CONTAINER *************************************/
    virtual TInt FileContainer_GetListL( CStifItemParser& /*aItem*/  );
    virtual TInt FileContainer_CidL( CStifItemParser& /*aItem*/  );
    virtual TInt FileContainer_CidErrorL( CStifItemParser& /*aItem*/  );
    virtual TInt FileContainer_SizeL( CStifItemParser& /*aItem*/ );
    virtual TInt FileContainer_FileL( CStifItemParser& /*aItem*/ );
    virtual TInt FileContainer_NodeTypeL( CStifItemParser& /*aItem*/ );
    virtual TInt FileContainer_RemoveL( CStifItemParser& /*aItem*/ );
    virtual TInt FileContainer_Remove2L( CStifItemParser& /*aItem*/ );
    virtual TInt FileContainer_Remove3L( CStifItemParser& /*aItem*/ );
    virtual TInt FileContainer_UnlinkL( CStifItemParser& /*aItem*/ );
    virtual TInt FileContainer_ReplaceWithL( CStifItemParser& /*aItem*/ );
    virtual TInt FileContainer_SubstituteForL( CStifItemParser& /*aItem*/ );
    virtual TInt FileContainer_CopyL( CStifItemParser& /*aItem*/ );
    virtual TInt FileContainer_Copy2L( CStifItemParser& /*aItem*/ );
    virtual TInt FileContainer_Copy3L( CStifItemParser& /*aItem*/ );
    virtual TInt FileContainer_Copy4L( CStifItemParser& /*aItem*/ );
    virtual TInt FileContainer_CopyToL( CStifItemParser& /*aItem*/ );
    virtual TInt FileContainer_CloneL( CStifItemParser& /*aItem*/ );
    virtual TInt FileContainer_AdoptNodeL( CStifItemParser& /*aItem*/ );
    virtual TInt FileContainer_SetAsFirstSiblingL( CStifItemParser& /*aItem*/ );
    virtual TInt FileContainer_SetAsLastSiblingL( CStifItemParser& /*aItem*/ );
    virtual TInt FileContainer_MoveBeforeSiblingL( CStifItemParser& /*aItem*/ );
    virtual TInt FileContainer_MoveAfterSiblingL( CStifItemParser& /*aItem*/ );
    virtual TInt FileContainer_MoveToL( CStifItemParser& /*aItem*/ );
    virtual TInt FileContainer_ReconcileNamespacesL( CStifItemParser& /*aItem*/ );
    virtual TInt SetTextNoEncTestL(CStifItemParser& aItem);
    virtual TInt AppendTextNoEncTestL(CStifItemParser& aItem);


        /**
        * Additinal support fuctions
        */


    /*
    *Write file from RBuf8
    *
    *@ returns void
    */

    void WriteFileFromBufferL(const TDesC& aFile, RBuf8& buffer);

    /*
    *Read aFile to HBufC8
    *
    *@ returns buffer
    */

    HBufC8* ReadFileToBufferL(const TDesC& aFile);

    /**
    * Saving node in XML document
    *
    * @param aCString a c-style string .
    */
    void SaveNode(RFile aFile,TXmlEngNode aNode);

    TInt FindElement(const TDesC8& aElementName, const TXmlEngElement& aParent, TXmlEngElement& aResult); // bug(?)

    /**
    * Saves XML document
    * @since ?Series60_version
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt SaveDocumentL(RXmlEngDocument& iDocument, TPtrC& pOut);

    /**
    * returns HBufC8 pointer to content of file with TDesC filename
    * @since ?Series60_version
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt GetHexFromPointerL(TPtrC pSerOpt);

    /**
    * returns TInt from TPtrC(pointer to hexadecimal value)
    * @since ?Series60_version
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual HBufC8* ReadFileL(const TDesC& aFileName);

    /**
    * creating DOM document
    * @since ?Series60_version
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */

    void SetupDocumentL();


    /**************************** Test function end **************************/

  public:     // Data
  protected:  // Data
  private:    // Data

    // DOM implementation for dom tests
    RXmlEngDOMImplementation DOM_impl;

    // Dom parser
    RXmlEngDOMParser parser;

    // XML document ( dom tree )
    RXmlEngDocument iDoc;

    // XML node ( dom tree )
    TXmlEngNode iNode;

    // XML element
    TXmlEngElement iElement;

    // Log info number
    TInt infoNum;

    // Last error number
    TInt iLastError;

    // cheap resize
    RHeap* he;
    RHeap* oldHeap;
    CTrapCleanup* cleanup;

  public:     // Friend classes
  protected:  // Friend classes
  private:    // Friend classes

};


#endif      // XE_DOM_BC_TESTER_H
// End of File