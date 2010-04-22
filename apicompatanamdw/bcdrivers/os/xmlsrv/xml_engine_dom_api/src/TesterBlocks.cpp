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
* Description:  ?Description
*
*/



// INCLUDE FILES
#include "DomBCTester.h"
#include "BCTesterDefs.h"

#include <StifParser.h>
#include <Stiftestinterface.h>
#include <Xml\Parser.h>
#include <Xml\ParserFeature.h>
#include <InetProtTextUtils.h>

#include <e32svr.h>
#include <e32math.h>
#include <f32file.h>
#include <libc\string.h>
#include <charconv.h>
#include <UTF.H>

using namespace Xml;

// -----------------------------------------------------------------------------
// CDomBCTester::Delete
// Delete here all resources allocated and opened from test methods.
// Called from destructor.
// -----------------------------------------------------------------------------
//
void CDomBCTester::Delete()
{

}

// -----------------------------------------------------------------------------
// CDomBCTester::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::RunMethodL(CStifItemParser& aItem )
{
    static TStifFunctionInfo const KFunctions[] =
    {
        // TEST
        ENTRY( "CompareFiles", CDomBCTester::CompareFilesL ),

        // DOM
        ENTRY( "ParseFile", CDomBCTester::ParseFileDomL ),
        ENTRY( "SaveDocument", CDomBCTester::DocumentSaveL),
        ENTRY( "SaveXmlToFile", CDomBCTester::SaveXmlToFileDomL ),
        ENTRY( "CheckOuterXml", CDomBCTester::CheckOuterXmlL ),
        ENTRY( "CheckInnerXml", CDomBCTester::CheckInnerXmlL ),
        ENTRY( "CreateDocument", CDomBCTester::CreateDocumentL ),
        ENTRY( "CheckDocumentParameters", CDomBCTester::CheckDocumentParametersL ),
        ENTRY( "CreateDocumentElement", CDomBCTester::CreateDocumentElementL ),
        ENTRY( "CreateDocumentFromNode", CDomBCTester::CreateDocumentFromNodeL ),
        ENTRY( "SaveXmlToUTF16LE", CDomBCTester::SaveXmlToBufferUTF16L ),
        ENTRY( "TestNodeFilter1", CDomBCTester::TestNodeFilterL ),
        ENTRY( "CloneDocument", CDomBCTester::CloneDocumentL ),
        ENTRY( "CheckNotNullElement", CDomBCTester::CheckNotNullElementL ),
        ENTRY( "CheckSiblingFunctions", CDomBCTester::CheckSiblingFunctionsL ),
        ENTRY( "CheckNodeParameters", CDomBCTester::CheckNodeParametersL ),
        ENTRY( "ParentNodes", CDomBCTester::ParentNodesL ),
        ENTRY( "CheckNamespaces", CDomBCTester::CheckNamespacesL ),
        ENTRY( "CheckProcessingInstruction", CDomBCTester::CheckProcessingInstructionL ),
        ENTRY( "CheckComments", CDomBCTester::CheckCommentsL ),
        ENTRY( "CheckCDATA", CDomBCTester::CheckCDATAL ),
        ENTRY( "CheckTextNode", CDomBCTester::CheckTextNodeL ),
        ENTRY( "CheckNodeValue", CDomBCTester::CheckNodeValueL ),
        ENTRY( "NodeNamespacePocessing", CDomBCTester::NodeNamespacePocessingL ),
        ENTRY( "CheckEntityRef", CDomBCTester::CheckEntityRefL ),
        ENTRY( "NodeTreeModification", CDomBCTester::NodeTreeModificationL ),
        ENTRY( "NodeTreeDeleting", CDomBCTester::NodeTreeDeletingL ),
        ENTRY( "CheckNodeList", CDomBCTester::CheckNodeListL ),
        ENTRY( "ElementNamespacePocessing", CDomBCTester::ElementNamespacePocessingL ),
        ENTRY( "CheckAttributes", CDomBCTester::CheckAttributesL ),
        ENTRY( "CheckElementAttributes", CDomBCTester::CheckElementAttributesL ),
        ENTRY( "CheckModifAttributes", CDomBCTester::CheckModifAttributesL ),
        ENTRY( "AddingAttributes", CDomBCTester::AddingAttributesL ),
        ENTRY( "AddingElements", CDomBCTester::AddingElementsL ),
        ENTRY( "CheckModifElement", CDomBCTester::CheckModifElementL ),
        ENTRY( "SetElementText", CDomBCTester::SetElementTextL ),
        ENTRY( "WHAT", CDomBCTester::CheckNextL ),
        ENTRY( "AddXmlId", CDomBCTester::AddXmlIdL ),
        ENTRY( "FindXmlId", CDomBCTester::FindXmlIdL ),
        ENTRY( "SetTextNoEncTest", CDomBCTester::SetTextNoEncTestL),
        ENTRY( "AppendTextNoEncTest", CDomBCTester::AppendTextNoEncTestL),
        ENTRY( "SetValueNoEncTest", CDomBCTester::SetValueNoEncTestL),
        ENTRY( "CreateDocument2", CDomBCTester::CreateDocument2L),
        ENTRY( "CreateEntityReferenceTest", CDomBCTester::CreateEntityReferenceTestL),
        ENTRY( "ParseFileDom2", CDomBCTester::ParseFileDom2L),
        ENTRY( "ParseFileDom3", CDomBCTester::ParseFileDom3L),
        ENTRY( "LookupNamespaceByPrefixTest", CDomBCTester::LookupNamespaceByPrefixTestL),
        ENTRY( "LookupNamespaceByUriTest", CDomBCTester::LookupNamespaceByUriTestL),
        ENTRY( "LookupNamespaceByPrefixTest2", CDomBCTester::LookupNamespaceByPrefixTest2L),
        ENTRY( "LookupNamespaceByUriTest2", CDomBCTester::LookupNamespaceByUriTest2L),
        ENTRY( "RemoveChildrenTest", CDomBCTester::RemoveChildrenTestL),
        ENTRY( "UserDataTest", CDomBCTester::UserDataTestL),
        ENTRY( "BaseUriTest", CDomBCTester::BaseUriTestL),
        ENTRY( "AddXmlIdTest", CDomBCTester::AddXmlIdTestL),
        ENTRY( "AddXmlId2", CDomBCTester::AddXmlId2L),
        ENTRY( "AddXmlId3", CDomBCTester::AddXmlId3L),
		//new functions added for XPath
		
		ENTRY( "ReplaceWithL", CDomBCTester::TestReplaceWithL),
		ENTRY( "CreateDocumentFragmentL", CDomBCTester::TestCreateDocumentFragmentL),
		ENTRY( "ToNumberL", CDomBCTester::TestToNumberL),
		ENTRY( "ToStringL", CDomBCTester::TestToStringL),
		ENTRY( "ToBooleanL", CDomBCTester::TestToBooleanL),
		ENTRY( "ExtensionFunctionL", CDomBCTester::TestExtensionFunctionL),
		ENTRY( "ExtensionVectorFunctionL", CDomBCTester::TestExtensionVectorFunctionL),
		ENTRY( "AddNativeExtensionVectorFunctionL", CDomBCTester::TestAddNativeExtensionVectorFunctionL),
		ENTRY( "ResetExtensionFunctionL", CDomBCTester::TestResetExtensionFunctionsL),
		ENTRY( "RenameElementL", CDomBCTester::TestRenameElementL),
		ENTRY( "SetDataSerializerL", CDomBCTester::TestSetDataSerializerL),
				
        // Chunk parser
        ENTRY( "ParseFileChunk", CDomBCTester::ParseFileChunkL ),

        // Chunk Container
        ENTRY("ChunkContainerGetList",CDomBCTester::ChunkContainer_GetListL),
        ENTRY("ChunkContainerCid",CDomBCTester::ChunkContainer_CidL),
        ENTRY("ChunkContainerCidError",CDomBCTester::ChunkContainer_CidErrorL),
        ENTRY("ChunkContainerChunk",CDomBCTester::ChunkContainer_ChunkL),
        ENTRY("ChunkContainerOffset",CDomBCTester::ChunkContainer_OffsetL),
        ENTRY("ChunkContainerSize",CDomBCTester::ChunkContainer_SizeL),
        ENTRY("ChunkContainerNodeType",CDomBCTester::ChunkContainer_NodeTypeL),
        ENTRY("ChunkContainerRemove",CDomBCTester::ChunkContainer_RemoveL),
        ENTRY("ChunkContainerRemove2",CDomBCTester::ChunkContainer_Remove2L),
        ENTRY("ChunkContainerRemove3",CDomBCTester::ChunkContainer_Remove3L),
        ENTRY("ChunkContainerUnlink",CDomBCTester::ChunkContainer_UnlinkL),
        ENTRY("ChunkContainerReplaceWith",CDomBCTester::ChunkContainer_ReplaceWithL),
        ENTRY("ChunkContainerSubstituteFor",CDomBCTester::ChunkContainer_SubstituteForL),
        ENTRY("ChunkContainerCopy",CDomBCTester::ChunkContainer_CopyL),
        ENTRY("ChunkContainerCopy2",CDomBCTester::ChunkContainer_Copy2L),
        ENTRY("ChunkContainerCopy3",CDomBCTester::ChunkContainer_Copy3L),
        ENTRY("ChunkContainerCopy4",CDomBCTester::ChunkContainer_Copy4L),
        ENTRY("ChunkContainerCopyTo",CDomBCTester::ChunkContainer_CopyToL),
        ENTRY("ChunkContainerClone",CDomBCTester::ChunkContainer_CloneL),
        ENTRY("ChunkContainerAdoptNode",CDomBCTester::ChunkContainer_AdoptNodeL),
        ENTRY("ChunkContainerSetAsFirstSibling",CDomBCTester::ChunkContainer_SetAsFirstSiblingL),
        ENTRY("ChunkContainerSetAsLastSibling",CDomBCTester::ChunkContainer_SetAsLastSiblingL),
        ENTRY("ChunkContainerMoveBeforeSibling",CDomBCTester::ChunkContainer_MoveBeforeSiblingL),
        ENTRY("ChunkContainerMoveAfterSibling",CDomBCTester::ChunkContainer_MoveAfterSiblingL),
        ENTRY("ChunkContainerMoveTo",CDomBCTester::ChunkContainer_MoveToL),
        ENTRY("ChunkContainerReconcileNamespaces",CDomBCTester::ChunkContainer_ReconcileNamespacesL),

        // File Container
        ENTRY("FileContainerGetList",CDomBCTester::FileContainer_GetListL),
        ENTRY("FileContainerCid",CDomBCTester::FileContainer_CidL),
        ENTRY("FileContainerCidError",CDomBCTester::FileContainer_CidErrorL),
        ENTRY("FileContainerSize",CDomBCTester::FileContainer_SizeL),
        ENTRY("FileContainerFile",CDomBCTester::FileContainer_FileL),
        ENTRY("FileContainerNodeType",CDomBCTester::FileContainer_NodeTypeL),
        ENTRY("FileContainerRemove",CDomBCTester::FileContainer_RemoveL),
        ENTRY("FileContainerRemove2",CDomBCTester::FileContainer_Remove2L),
        ENTRY("FileContainerRemove3",CDomBCTester::FileContainer_Remove3L),
        ENTRY("FileContainerUnlink",CDomBCTester::FileContainer_UnlinkL),
        ENTRY("FileContainerReplaceWith",CDomBCTester::FileContainer_ReplaceWithL),
        ENTRY("FileContainerSubstituteFor",CDomBCTester::FileContainer_SubstituteForL),
        ENTRY("FileContainerCopy",CDomBCTester::FileContainer_CopyL),
        ENTRY("FileContainerCopy2",CDomBCTester::FileContainer_Copy2L),
        ENTRY("FileContainerCopy3",CDomBCTester::FileContainer_Copy3L),
        ENTRY("FileContainerCopy4",CDomBCTester::FileContainer_Copy4L),
        ENTRY("FileContainerCopyTo",CDomBCTester::FileContainer_CopyToL),
        ENTRY("FileContainerClone",CDomBCTester::FileContainer_CloneL),
        ENTRY("FileContainerAdoptNode",CDomBCTester::FileContainer_AdoptNodeL),
        ENTRY("FileContainerSetAsFirstSibling",CDomBCTester::FileContainer_SetAsFirstSiblingL),
        ENTRY("FileContainerSetAsLastSibling",CDomBCTester::FileContainer_SetAsLastSiblingL),
        ENTRY("FileContainerMoveBeforeSibling",CDomBCTester::FileContainer_MoveBeforeSiblingL),
        ENTRY("FileContainerMoveAfterSibling",CDomBCTester::FileContainer_MoveAfterSiblingL),
        ENTRY("FileContainerMoveTo",CDomBCTester::FileContainer_MoveToL),
        ENTRY("FileContainerReconcileNamespaces",CDomBCTester::FileContainer_ReconcileNamespacesL),

        // Binary Container
        ENTRY( "BinaryContainer", CDomBCTester::BinaryContainerL),
        ENTRY( "PartialBinaryContainer", CDomBCTester::PartialBinaryContainerL ),
        ENTRY( "TestAppendContents", CDomBCTester::TestAppendContentsL),
        ENTRY("BinaryContainerGetList",CDomBCTester::BinaryContainer_GetListL),
        ENTRY("BinaryContainerGetList2",CDomBCTester::BinaryContainer_GetList2L),
        ENTRY("BinaryContainerCidError",CDomBCTester::BinaryContainer_CidErrorL),
        ENTRY("BinaryContainerRemove",CDomBCTester::BinaryContainer_RemoveL),
        ENTRY("BinaryContainerRemove2",CDomBCTester::BinaryContainer_Remove2L),
        ENTRY("BinaryContainerRemove3",CDomBCTester::BinaryContainer_Remove3L),
        ENTRY("BinaryContainerUnlink",CDomBCTester::BinaryContainer_UnlinkL),
        ENTRY("BinaryContainerReplaceWith",CDomBCTester::BinaryContainer_ReplaceWithL),
        ENTRY("BinaryContainerSubstituteFor",CDomBCTester::BinaryContainer_SubstituteForL),
        ENTRY("BinaryContainerCopy",CDomBCTester::BinaryContainer_CopyL),
        ENTRY("BinaryContainerCopy2",CDomBCTester::BinaryContainer_Copy2L),
        ENTRY("BinaryContainerCopy3",CDomBCTester::BinaryContainer_Copy3L),
        ENTRY("BinaryContainerCopy4",CDomBCTester::BinaryContainer_Copy4L),
        ENTRY("BinaryContainerCopyTo",CDomBCTester::BinaryContainer_CopyToL),
        ENTRY("BinaryContainerClone",CDomBCTester::BinaryContainer_CloneL),
        ENTRY("BinaryContainerAdoptNode",CDomBCTester::BinaryContainer_AdoptNodeL),
        ENTRY("BinaryContainerSetAsFirstSibling",CDomBCTester::BinaryContainer_SetAsFirstSiblingL),
        ENTRY("BinaryContainerSetAsLastSibling",CDomBCTester::BinaryContainer_SetAsLastSiblingL),
        ENTRY("BinaryContainerMoveBeforeSibling",CDomBCTester::BinaryContainer_MoveBeforeSiblingL),
        ENTRY("BinaryContainerMoveAfterSibling",CDomBCTester::BinaryContainer_MoveAfterSiblingL),
        ENTRY("BinaryContainerMoveTo",CDomBCTester::BinaryContainer_MoveToL),
        ENTRY("BinaryContainerReconcileNamespaces",CDomBCTester::BinaryContainer_ReconcileNamespacesL),
    };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );
    return RunInternalL( KFunctions, count, aItem );
}

/******************************  TEST  **************************************/

// -----------------------------------------------------------------------------
// CDomBCTester::ReadFileL
// returns HBufC8 pointer to content of file with TDesC filename
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
HBufC8* CDomBCTester::ReadFileL(const TDesC& aFileName)
{
    RFs rfs;
    RFile file;
    User::LeaveIfError(rfs.Connect());
    CleanupClosePushL(rfs);
    User::LeaveIfError(file.Open(rfs, aFileName, EFileRead));
    CleanupClosePushL(file);
    TInt size;
    User::LeaveIfError(file.Size(size));
    HBufC8* buf = HBufC8::NewLC(size);
    TPtr8 bufPtr(buf->Des());
    User::LeaveIfError(file.Read(bufPtr));
    CleanupStack::Pop(); // buf
    CleanupStack::PopAndDestroy(2); // file, rfs
    return buf;
}


// -----------------------------------------------------------------------------
// CDomBCTester::GetHexFromPointerL
// returns TInt from TPtrC(pointer to hexadecimal value)
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::GetHexFromPointerL(TPtrC pSerOpt)
{
    //  get serialization options from file
    TInt serOpt;
    TInt size;
    RFs fServer;
    User::LeaveIfError(fServer.Connect());
    CleanupClosePushL(fServer);
    RFile fileHandle;
    User::LeaveIfError(fileHandle.Open(fServer, pSerOpt, EFileRead | EFileShareReadersOnly ));
    CleanupClosePushL(fileHandle);
    User::LeaveIfError(fileHandle.Size(size));
    HBufC8* optionBuffer = HBufC8::NewLC(size);
    TPtr8 optionPtr = optionBuffer->Des();
    User::LeaveIfError(fileHandle.Read(optionPtr, size));
    InetProtTextUtils::ConvertDescriptorToHex(optionPtr, serOpt);

    // pop and destroy pushed objects
    CleanupStack::PopAndDestroy( 3 );
    return serOpt;
}

// -----------------------------------------------------------------------------
// CDomBCTester::SaveDocument
// saves xml document
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

TInt CDomBCTester::SaveDocumentL(RXmlEngDocument& iDocument, TPtrC& pOut)
{
    TInt error(KErrArgument);
    if (pOut.Length()  != 0 )
    {
        //  save xml document to file
        TXmlEngElement root = iDocument.DocumentElement();
        if(root.NotNull())
        {
            error = iDocument.SaveL( pOut);
        }
    }
    return error;
}


// --------------------------------------------------------------------------------------
// Read file to buffer
// --------------------------------------------------------------------------------------
//

HBufC8* CDomBCTester::ReadFileToBufferL(const TDesC& aFile)
{
    RFs fServer;
    User::LeaveIfError(fServer.Connect());
    CleanupClosePushL(fServer);

    TInt dataSize;
    RFile fileHandle;
    User::LeaveIfError(fileHandle.Open(fServer, aFile, EFileRead | EFileShareReadersOnly));
    CleanupClosePushL(fileHandle);
    User::LeaveIfError(fileHandle.Size(dataSize));
    HBufC8* bufferData = HBufC8::NewL(dataSize);
    TPtr8 dataPtr = bufferData->Des();
    User::LeaveIfError(fileHandle.Read(dataPtr, dataSize));

    CleanupStack::PopAndDestroy( 2 );
    return bufferData;
}


// --------------------------------------------------------------------------------------
// Write file from buffer
// --------------------------------------------------------------------------------------
//
void CDomBCTester::WriteFileFromBufferL(const TDesC& aFile, RBuf8& buffer)
{
    RFs fServer;
    User::LeaveIfError(fServer.Connect());
    CleanupClosePushL(fServer);

    RFile fOut;
    User::LeaveIfError ( fOut.Replace( fServer, aFile, EFileWrite ) );
    CleanupClosePushL( fOut );
    User::LeaveIfError ( fOut.Write(buffer ) );

    CleanupStack::PopAndDestroy( 2 );
    return;
}

// -----------------------------------------------------------------------------
// CDomBCTester::SetupDocumentL
// setup test DOM tree
// (other items were commented in a header).
// -----------------------------------------------------------------------------
void CDomBCTester::SetupDocumentL(  )
{
    _LIT8(KElementName,"doc");
    _LIT8(KTarget,"test");
    _LIT8(KComment,"test comment");
    _LIT8(KValue,"test value");
    _LIT8(KNamespace,"testNamespace");
    _LIT8(KPrefix,"testPref");
    _LIT8(KStringName,"doc");
    _LIT8(KStringValue,"ATTR_value");
    _LIT8(KStringText,"test content");
    _LIT8(KCData,"test < test2 & \r\n> ;");

    iDoc.OpenL(DOM_impl);

    iElement = iDoc.CreateDocumentElementL( KElementName,KNullDesC8 ,KNullDesC8 );
    TXmlEngTextNode textNode = iDoc.CreateTextNodeL(KStringText);
    iElement.AppendChildL(textNode);
    TXmlEngCDATASection cdNode = iDoc.CreateCDATASectionL(KCData);
    iElement.AppendChildL(cdNode);
    TXmlEngAttr atNode = iDoc.CreateAttributeL(KStringName, KStringValue);
    iElement.AppendChildL(atNode);
    TXmlEngComment commentNode = iDoc.CreateCommentL(KComment);
    iElement.AppendChildL(commentNode);
    TXmlEngProcessingInstruction piNode = iDoc.CreateProcessingInstructionL(KTarget, KValue);
    iElement.AppendChildL(piNode);
    TXmlEngElement elementNode = iDoc.CreateElementL(KElementName, KNamespace, KPrefix);
    iElement.AppendChildL(elementNode);
}

TBool CDomBCTester::CompareDescAndChar(const char* aString,TDesC8& aDesc)
{
    TInt strLen = strlen(aString);
    TInt desLen = aDesc.Length();
    if (strLen != desLen)
    {
        return FALSE;
    }
    else
    {
        for(TInt i = 0; i < strLen; i++)
        {
            if (aString[i] != aDesc[i])
            return FALSE;
        }
    }
    return TRUE;
}

TBool CDomBCTester::CompareDescAndChar(const TUint8* aString,TDesC8& aDesc)
{
    TInt strLen = strlen((char*)aString);
    TInt desLen = aDesc.Length();
    if (strLen != desLen)
    {
        return FALSE;
    }
    else
    {
        for(TInt i = 0; i < strLen; i++)
        {
            if (aString[i] != aDesc[i])
            return FALSE;
        }
    }
    return TRUE;
}

void CDomBCTester::SaveNode(RFile aFile,TXmlEngNode aNode)
{
    _LIT8(KInfoOnStartEle,"Element: %S \r\n");
    _LIT8(KInfoOnAttribute,"\tAttribute \tname: %S \t value: %S \r\n");
    _LIT8(KInfoOnAttribute2,"Attribute \tname: %S \t value: %S \r\n");
    _LIT8(KInfoOnText,"Text: %S\r\n");

    TBuf8<256> info;
    if(aNode.NodeType() == TXmlEngNode::EElement)
    {
        TPtrC8 wsk = aNode.Name();
        info.Format(KInfoOnStartEle,&wsk);
        aFile.Write(info);

        RXmlEngNodeList <TXmlEngAttr> array;
        if(aNode.HasAttributes())
        {
            aNode.AsElement().GetAttributes(array);
            while(array.HasNext())
            {
                TXmlEngAttr attr = array.Next();
                TPtrC8 wsk1 = attr.Name();
                TPtrC8 wsk2 = attr.Value();
                info.Format(KInfoOnAttribute,&wsk1,&wsk2);
                aFile.Write(info);
            }
            array.Close();
        }
    }
    else if(aNode.NodeType() == TXmlEngNode::EAttribute)
    {
        TPtrC8 wsk1 = aNode.Name();
        TPtrC8 wsk2 = aNode.Value();
        info.Format(KInfoOnAttribute2,&wsk1,&wsk2);
        aFile.Write(info);
    }
    else if(aNode.NodeType() == TXmlEngNode::EText)
    {
        TPtrC8 wsk1 = aNode.AsText().Contents();
        info.Format(KInfoOnText,&wsk1);
        aFile.Write(info);
    }
}

TBool CDomBCTester::CompareChars(const char* aString1,const char* aString2)
{
    TInt strLen = strlen(aString1);
    TInt desLen = strlen(aString2);
    if (strLen != desLen)
    {
        return FALSE;
    }
    else
    {
        for(TInt i = 0; i < strLen; i++)
        {
            if (aString1[i] != aString2[i])
            return FALSE;
        }
    }
    return TRUE;
}

// -----------------------------------------------------------------------------
// CDomBCTester::CompareFilesL
// Comapare two files return true if the same
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CompareFilesL( CStifItemParser& aItem )
{
    _LIT(KSourceFileErrorName,"No source file name.");
    _LIT(KPatternFileErrorName,"No pattern file name.");
    _LIT(KSkipWhiteSpace,"Skipping white spaces in files.");
    _LIT(KCompareFilesInfo,"Comparing files: %S and %S");
    _LIT(KSourceFileError,"Source file error.");
    _LIT(KPatternFileError,"Pattern file error.");
    _LIT(KComparePassed,"Files compare test PASSED.");
    _LIT(KCompareFailed,"Files compare test FAILED.");

    TInt nResult = KErrNone;
    TBool skipWhite = FALSE;
    TBool foundRes = FALSE;
    TBool foundRef = FALSE;

    RFs fs;
    User::LeaveIfError(fs.Connect());
    CleanupClosePushL(fs);

    RFile srcFile;
    RFile referenceFile;

    TFileName srcFileName;
    TFileName referenceFileName;

    TPtrC SrcFile;
    if ( aItem.GetNextString(SrcFile) != KErrNone )
    {
        TestModuleIf().Printf( infoNum++, KTEST_NAME,
        KSourceFileErrorName);
        iLog->Log((TDesC) KSourceFileErrorName);
        nResult = KErrGeneral;
    }

    TPtrC ReferenceFile;
    if ( aItem.GetNextString(ReferenceFile) != KErrNone )
    {
        TestModuleIf().Printf( infoNum++, KTEST_NAME,
        KPatternFileErrorName);
        iLog->Log((TDesC)KPatternFileErrorName);
        nResult = KErrGeneral;
    }

    TPtrC string;
    if ( aItem.GetNextString(string) == KErrNone )
    {
        TestModuleIf().Printf( infoNum++, KTEST_NAME,
        KSkipWhiteSpace);
        iLog->Log((TDesC)KSkipWhiteSpace);
        skipWhite = TRUE;
    }

    if ( nResult == KErrNone )
    {
        srcFileName.Copy(SrcFile);
        referenceFileName.Copy(ReferenceFile);

        TestModuleIf().Printf( infoNum++, KTEST_NAME,
        KCompareFilesInfo, &SrcFile, &ReferenceFile);
        iLog->Log(KCompareFilesInfo, &SrcFile, &ReferenceFile);

        if(srcFile.Open(fs, srcFileName, EFileStream|EFileRead) == KErrNone)
        {
            // Does reference file exist.
            if(referenceFile.Open(fs, referenceFileName, EFileStream|EFileRead) == KErrNone)
            {
                // Integer variables for compare to length of files (result and reference).
                TInt resSize;
                TInt refSize;

                srcFile.Size(resSize);
                referenceFile.Size(refSize);

                // Next compare one letter at the time, but only if files have same length.
                if(skipWhite)
                {
                    TBuf8<1> resBuf;
                    TBuf8<1> refBuf;
                    nResult = KErrNone;
                    TInt j = 0;
                    TInt i = 0;

                    //for(TInt i = 0; i < Size; i++)
                    while (TRUE)
                    {
                        foundRes = FALSE;
                        foundRef = FALSE;
                        // Read result file
                        while(i < (resSize + 1))
                        {
                            i++;
                            srcFile.Read(resBuf);
                            resBuf.Trim();
                            if ( resBuf.Length() > 0)
                            {
                                foundRes = TRUE;
                                break;
                            }
                        }

                        // Read reference file
                        while(j < (refSize + 1))
                        {
                            j++;
                            referenceFile.Read(refBuf);
                            refBuf.Trim();
                            if ( refBuf.Length() > 0)
                            {
                                foundRef = TRUE;
                                break;
                            }
                        }

                        // Compare single letter at the time.
                        if( ( i < resSize ) && ( j < refSize ) && (resBuf[0] != refBuf[0]) )
                        {
                            nResult = KErrGeneral;
                            break;
                        }
                        if( (i == (resSize + 1)) && (j < refSize) && foundRef)
                        {
                            nResult = KErrGeneral;
                            break;
                        }
                        if( (i < resSize) && (j == (refSize + 1)) && foundRes)
                        {
                            nResult = KErrGeneral;
                            break;
                        }
                        if ((i > resSize) && (j > refSize))
                        break;
                    }
                }
                else
                {
                    if (resSize != refSize)
                    nResult = KErrGeneral;
                    else
                    {
                        TBuf8<1> resBuf;
                        TBuf8<1> refBuf;
                        nResult = KErrNone;
                        for(TInt i = 0; i < resSize; i++)
                        {
                            // Read result file
                            srcFile.Read(resBuf);

                            // Read reference file
                            referenceFile.Read(refBuf);

                            // Compare single letter at the time.

                            if(resBuf[0] != refBuf[0])
                            {
                                nResult = KErrGeneral;
                                break;
                            }
                        }
                    }
                }
                referenceFile.Close();
                srcFile.Close();
            }
            else
            {
                nResult = KErrGeneral;
                TestModuleIf().Printf( infoNum++, KTEST_NAME, KPatternFileError);
                iLog->Log((TDesC)KPatternFileError);
            }
            srcFile.Close();
        }
        else
        {
            nResult = KErrGeneral;
            TestModuleIf().Printf( infoNum++, KTEST_NAME, KSourceFileError);
            iLog->Log((TDesC)KSourceFileError);
        }

    }

    CleanupStack::PopAndDestroy(&fs);

    if ( nResult == KErrNone)
    {
        TestModuleIf().Printf( infoNum++, KTEST_NAME,KComparePassed);
        iLog->Log((TDesC)KComparePassed);
    }
    else
    {
        TestModuleIf().Printf( infoNum++, KTEST_NAME, KCompareFailed);
        iLog->Log((TDesC)KCompareFailed);
    }

    return nResult;
}
