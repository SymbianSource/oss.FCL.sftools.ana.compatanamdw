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
#include "TestUserData.h"

#include <StifParser.h>
#include <Stiftestinterface.h>
#include <Xml\Parser.h>
#include <Xml\ParserFeature.h>
//new headers
#include <XmlEngXPathEvaluator.h>
#include <xmlengxpathextensionfunction.h>
#include <xmlengxpathutils.h>
#include <xmlengxpathevaluationcontext.h>
#include <xmlengxpathconfiguration.h>
#include <math.h>

#include <e32svr.h>
#include <libc\string.h>
#include <charconv.h>
#include <UTF.H>

#define INTERNAL_NODEPTR(aNodeObject)   (*reinterpret_cast<xmlNodePtr*>(&(aNodeObject)))

using namespace Xml;


class XPathDate: public MXmlEngXPathExtensionFunction
    {

public:
    TInt MinArity(){return 1;}
		
    TXmlEngEvaluationStatus Evaluate(MXmlEngXPathEvaluationContext* aEvalCtxt)
        {
		
        if (aEvalCtxt->Argument(0).Type() == RXmlEngXPathResult::ENodeset)
            aEvalCtxt->SetResultL(_L8("Nodeset"));
        if (aEvalCtxt->Argument(0).Type() == RXmlEngXPathResult::ENumber)
            aEvalCtxt->SetResultL(_L8("Number"));
        if (aEvalCtxt->Argument(0).Type() == RXmlEngXPathResult::EString)
            aEvalCtxt->SetResultL(_L8("String"));
        if (aEvalCtxt->Argument(0).Type() == RXmlEngXPathResult::EBoolean)
            return EError;
				
        return ESucceeded;
		
        }
	
    };
class XPathDate2: public MXmlEngXPathExtensionFunction
    {
public:
    TInt MinArity(){return 1;}
    TXmlEngEvaluationStatus Evaluate(MXmlEngXPathEvaluationContext* aEvalCtxt)
        {
        if (aEvalCtxt->Argument(0).Type() == RXmlEngXPathResult::ENodeset)
            {
            aEvalCtxt->InitializeNodeSetResult();
            aEvalCtxt->AppendToResult(aEvalCtxt->Argument(0).AsNodeSet());
            if(aEvalCtxt->Result().Type() != RXmlEngXPathResult::ENodeset)
                return EError;
            }
            
        if (aEvalCtxt->Argument(0).Type() == RXmlEngXPathResult::ENumber)
            aEvalCtxt->SetResult(aEvalCtxt->Argument(0).AsNumber());
        if (aEvalCtxt->Argument(0).Type() == RXmlEngXPathResult::EString)
            aEvalCtxt->SetResultL( _L8("String") );
        if (aEvalCtxt->Argument(0).Type() == RXmlEngXPathResult::EBoolean)
            aEvalCtxt->SetResult(ETrue);
        return ESucceeded;
        }
    };

class XPathDate3: public MXmlEngXPathExtensionFunction
    {
public:
    TInt MinArity(){return 2;}
    TXmlEngEvaluationStatus Evaluate(MXmlEngXPathEvaluationContext* aEvalCtxt)
        {
        if(aEvalCtxt->ArgCount() != 2)
            {
            return EInvalidArgumentNumber;
            }
        aEvalCtxt->SetResult(aEvalCtxt->Argument(0).AsNumber() + aEvalCtxt->Argument(1).AsNodeSet().Length());
        return ESucceeded;
        }
    };

class TTestNodeFilter: public MXmlEngNodeFilter
    {
    public:
        TXmlEngNodeFilterResult AcceptNode(TXmlEngNode /*aNode*/)
        {
            return EAccept;
        }
    };


class CBinaryMirrorHandler : public CBase, public MXmlEngDataSerializer
{
    public:
    TPtrC8 SerializeDataL(TXmlEngNode /*aNode*/)
    {
        _LIT8(data1, "the replaced binary data");
        //TPtrC8 data2(_L8("the replaced binary data"));
        return TPtrC8(data1);
    };
};

class MXmlEngTestNodeFilter : public MXmlEngNodeFilter
{
    public:

    TXmlEngNodeFilterResult AcceptNode(TXmlEngNode aNode)
    {
        _LIT8(KNodeName1,"name");
        _LIT8(KNodeName2,"phone");
        _LIT8(KNodeName3,"title");

        TPtrC8 node1=aNode.AsElement().Name();
        if (!aNode.AsElement().Name().Compare(KNodeName2))
        {
            return EReject;
        }
        else if (!aNode.AsElement().Name().Compare(KNodeName1))
        {
            return ESkip;
        }
        else if (!aNode.AsElement().Name().Compare(KNodeName3))
        {
            return ESkipContents;
        }
        else
        return EAccept;
    }
};

class MyOutputStream : public MXmlEngOutputStream
{
    TFileName myFileName;
    public:
    void SetFilename(TPtrC aFilename)
    {
        myFileName.Copy(aFilename);
    }

    TInt Write(const TDesC8 &aBuffer)
    {
        RFs fServer;
        User::LeaveIfError(fServer.Connect());
        CleanupClosePushL(fServer);
        RFile outFile;
        CleanupClosePushL(outFile);

        TInt err = outFile.Open(fServer, myFileName, EFileWrite);
        if (err == KErrNotFound) // file does not exist - create it
        {
            err = outFile.Create(fServer, myFileName, EFileWrite);
        }
        TInt ret = outFile.Write(aBuffer);
        CleanupStack::PopAndDestroy(2); //outFile, fServer
        if(ret == KErrNone)
        {
            return(aBuffer.Size());
        }
        return ret;
    };
    TInt Close()
    {
        return NULL;
    }
};


/************************************** DOM ****************************************/

// -----------------------------------------------------------------------------
// CDomBCTester::ParseFileDOML
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::ParseFileDomL( CStifItemParser& aItem )
{
    _LIT(KSourceFileErrorName,"No source file name.");
    _LIT(KEndParsing,"Parsing end.");

    TPtrC SrcFile;
    TPtrC tmp;
    TBool map = TRUE;
    if ( aItem.GetNextString(SrcFile) != KErrNone )
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME,KSourceFileErrorName);
        iLog->Log((TDesC)KSourceFileErrorName);
        return KErrGeneral;
    }

    if ( aItem.GetNextString(tmp) == KErrNone )
    {
        map = FALSE;
    }
    TFileName srcFileName;
    srcFileName.Copy(SrcFile);

    TInt err;
    TRAP(err, iDoc = parser.ParseFileL(srcFileName));
    if(map && err == KXmlEngErrParsing)
    {
        iLastError = parser.GetLastParsingError();
    }
    else
    {
        iLastError = err;
    }
    TestModuleIf().Printf( infoNum++,KTEST_NAME,KEndParsing);
    iLog->Log((TDesC)KEndParsing);

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::SaveXMLtoFileDomL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::SaveXmlToFileDomL( CStifItemParser& aItem )
{
    _LIT(KOutputFileErrorName,"No output file name.");
    _LIT(KOutputFileError,"Output file error. Error code: %d");
    _LIT(KRootError,"Document has no root element. Error code: %d");
    _LIT(KSaveEnd,"File saved.");

    TPtrC OutputFile;
    if ( aItem.GetNextString(OutputFile) != KErrNone )
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME,KOutputFileErrorName);
        iLog->Log((TDesC)KOutputFileErrorName);
        return KErrGeneral;
    }

    TXmlEngElement root = iDoc.DocumentElement();
    if(root.NotNull())
    {
        iDoc.SaveL(OutputFile);
    }
    else
    {
        TestModuleIf().Printf( infoNum++, KTEST_NAME,KRootError,iLastError);
        iLog->Log(KRootError, iLastError);

        RFs fs;
        User::LeaveIfError(fs.Connect());
        CleanupClosePushL(fs);

        RFile outputFile;
        TFileName outFileName;
        outFileName.Copy(OutputFile);

        // Open output file
        TInt err = outputFile.Replace(fs,outFileName,EFileShareAny|EFileWrite);

        // If output file is correct
        if (err == KErrNone)
        {
            outFileName.Format(KRootError,iLastError);
            HBufC8* buf = NULL;
            buf = HBufC8::NewLC(outFileName.Length());
            buf->Des().Copy(outFileName);
            outputFile.Write(buf->Des());
            outputFile.Close();
            CleanupStack::PopAndDestroy(buf);
        }
        else
        {
            TestModuleIf().Printf( infoNum++,KTEST_NAME, KOutputFileError, err);
            iLog->Log(KOutputFileError, err);
        }

        CleanupStack::PopAndDestroy(&fs);
    }

    TestModuleIf().Printf( infoNum++,KTEST_NAME,KSaveEnd);
    iLog->Log((TDesC)KSaveEnd);

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::SaveXMLtoBufferUTF16L
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::SaveXmlToBufferUTF16L( CStifItemParser& aItem )
{
    _LIT(KOutputFileErrorName,"No output file name.");
    _LIT(KOutputFileError,"Output file error. Error code: %d");
    _LIT(KRootError,"Document has no root element. Error code: %d");
    _LIT(KSaveEnd,"File saved.");

    _LIT8(enc,"UTF-16");

    TPtrC OutputFile;
    if ( aItem.GetNextString(OutputFile) != KErrNone )
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME,KOutputFileErrorName);
        iLog->Log((TDesC)KOutputFileErrorName);
        return KErrGeneral;
    }

    TPtrC flag;
    TBool useFlag = EFalse;
    if ( aItem.GetNextString(flag) == KErrNone )
    {
        useFlag = ETrue;
    }

    RBuf8 buf;
    TXmlEngElement root = iDoc.DocumentElement();
    if(root.NotNull())
    {
        if(useFlag)
        {
            TXmlEngSerializationOptions opt(TXmlEngSerializationOptions::KOptionEncoding | TXmlEngSerializationOptions::KOptionStandalone,enc);
            iDoc.SaveL(buf,iDoc,opt);
            CleanupClosePushL( buf );
        }
        else
        {
            TXmlEngSerializationOptions opt(0,enc);
            iDoc.SaveL(buf,iDoc,opt);
            CleanupClosePushL( buf );
        }
    }
    else
    {
        TestModuleIf().Printf( infoNum++, KTEST_NAME,KRootError,iLastError);
        iLog->Log(KRootError,iLastError);

        TBuf<256> buffer;
        buffer.Format(KRootError,iLastError);
        TBuf8<256> buffer8;
        buffer8.Copy(buffer);
        buf.CreateL(buffer8);
        CleanupClosePushL(buf);
    }

    RFs fs;
    User::LeaveIfError(fs.Connect());
    CleanupClosePushL(fs);

    RFile outputFile;
    TFileName outFileName;
    outFileName.Copy(OutputFile);

    // Open output file
    TInt err = outputFile.Replace(fs,outFileName,EFileShareAny|EFileWrite);

    // If output file is correct
    if (err == KErrNone)
    {
        outputFile.Write(buf);
        outputFile.Close();
    }
    else
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KOutputFileError, err);
        iLog->Log(KOutputFileError, err);
    }

    CleanupStack::PopAndDestroy(&fs);
    CleanupStack::PopAndDestroy(&buf);

    TestModuleIf().Printf( infoNum++,KTEST_NAME,KSaveEnd);
    iLog->Log((TDesC)KSaveEnd);

    return KErrNone;
}
// -----------------------------------------------------------------------------
// CDomBCTester::TestNodeFilterL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::TestNodeFilterL( CStifItemParser& aItem )
{
    _LIT(KOutputFileErrorName,"No output file name.");
    _LIT(KOutputFileError,"Output file error. Error code: %d");
    _LIT(KSaveEnd,"File saved.");

    TPtrC InputFile;
    if ( aItem.GetNextString(InputFile) != KErrNone )
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME,KOutputFileErrorName);
        iLog->Log((TDesC)KOutputFileErrorName);
        return KErrGeneral;
    }

    TPtrC OutputFile;
    if ( aItem.GetNextString(OutputFile) != KErrNone )
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME,KOutputFileErrorName);
        iLog->Log((TDesC)KOutputFileErrorName);
        return KErrGeneral;
    }
    TFileName srcFileName;
    srcFileName.Copy( InputFile);

    RBuf8 buf;
    RXmlEngDocument doc;
    doc=parser.ParseFileL( srcFileName );

    MXmlEngTestNodeFilter* nodefilter = new (ELeave) MXmlEngTestNodeFilter();
    CleanupStack::PushL(nodefilter);
    TXmlEngSerializationOptions options(0);

    TXmlEngElement root = doc.DocumentElement();
    if(root.NotNull())
    {
        options.SetNodeFilter(nodefilter);

        doc.SaveL(buf,doc,options);
        CleanupClosePushL( buf );
    }

    RFs fs;
    User::LeaveIfError(fs.Connect());
    CleanupClosePushL(fs);

    RFile outputFile;
    TFileName outFileName;
    outFileName.Copy(OutputFile);

    // Open output file
    TInt err = outputFile.Replace(fs,outFileName,EFileShareAny|EFileWrite);

    // If output file is correct
    if (err == KErrNone)
    {
        outputFile.Write(buf);
        outputFile.Close();
    }
    else
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KOutputFileError, err);
        iLog->Log(KOutputFileError, err);
    }

    CleanupStack::PopAndDestroy(&fs);
    CleanupStack::PopAndDestroy(&buf);
    doc.Close();
    CleanupStack::PopAndDestroy(); //nodefilter
    TestModuleIf().Printf( infoNum++,KTEST_NAME,KSaveEnd);
    iLog->Log((TDesC)KSaveEnd);

    return KErrNone;
}


// -----------------------------------------------------------------------------
// CDomBCTester::CreateDocumentL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CreateDocumentL( CStifItemParser& /*aItem*/ )
{
    _LIT8(name,"doc");
    _LIT8(uri,"http://test.com");
    _LIT8(arg1,"1.1");
    _LIT8(arg2,"http://test2.org");

    iDoc.OpenL(DOM_impl);
    iDoc.CreateDocumentElementL(name);
    iDoc.DocumentElement().SetDefaultNamespaceL(uri);
    iDoc.SetStandalone(TRUE);
    iDoc.SetXmlVersionL(arg1);
    iDoc.SetDocumentUriL(arg2);
    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::CheckDocumentParametersL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CheckDocumentParametersL( CStifItemParser& /*aItem*/ )
{
    _LIT(KStandaloneError,"Standalone checking error.");
    _LIT(KEncodingError,"Encoding checking error");
    _LIT(KVersionError,"Version checking error");
    _LIT(KUriError,"Uri checking error");

    _LIT8(arg,"1.0");
    _LIT8(arg2,"UTF-8");
    _LIT8(KDesNull,"");

    _LIT(KTypeError,"Node type checking error.");
    if(!(iDoc.NodeType() == TXmlEngNode::EDocument))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KTypeError);
        iLog->Log((TDesC)KTypeError);
        return KErrGeneral;
    }

    if(!(iDoc.IsStandalone() == TRUE))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KStandaloneError);
        iLog->Log((TDesC)KStandaloneError);
        return KErrGeneral;
    }

    if(iDoc.XmlVersion().Compare(arg))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KVersionError);
        iLog->Log((TDesC)KVersionError);
        return KErrGeneral;
    }
    if(iDoc.XmlEncoding().Compare(arg2))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KEncodingError);
        iLog->Log((TDesC)KEncodingError);
        return KErrGeneral;
    }

    if(iDoc.DocumentUri().Compare(KDesNull ))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KUriError);
        iLog->Log((TDesC)KUriError);
        return KErrGeneral;
    }

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::CheckNotNullElementL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CheckNotNullElementL( CStifItemParser& /*aItem*/ )
{
    _LIT8(name,"test");
    TXmlEngElement elem;
    _LIT(KNullError,"Is node null checking error.");

    if(!elem.IsNull())
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KNullError);
        iLog->Log((TDesC) KNullError);
        return KErrGeneral;
    }

    iDoc.OpenL(DOM_impl);
    elem = iDoc.CreateElementL(name);

    _LIT(KNotNullError,"Is node not null checking error.");
    if(!elem.NotNull())
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KNotNullError);
        iLog->Log((TDesC) KNotNullError);
        return KErrGeneral;
    }

    iDoc.Close();
    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::CreateDocumentElementL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CreateDocumentElementL( CStifItemParser& /*aItem*/ )
{
    _LIT8(name, "doc");
    _LIT8(uri, "http://test.com");
    _LIT8(ver, "1.0");

    iDoc.OpenL(DOM_impl);
    TXmlEngElement root = iDoc.CreateElementL(name);
    root.SetDefaultNamespaceL(uri);
    iDoc.SetStandalone(TRUE);
    iDoc.SetXmlVersionL(ver);
    iDoc.SetDocumentElement(root);

    _LIT(KNamespaceError,"Namespace checking error.");

    if(iDoc.DocumentElement().DefaultNamespaceL().Uri().Compare(uri))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KNamespaceError);
        iLog->Log((TDesC)KNamespaceError);
        return KErrGeneral;
    }

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::CreateDocumentFromNodeL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CreateDocumentFromNodeL( CStifItemParser& /*aItem*/ )
{
    _LIT8(name,"doc");
    _LIT8(tekst,"test content");
    _LIT8(value,"ATTR_value");
    _LIT8(cdata,"test < test2 & \r\n> ;");

    iDoc.OpenL(DOM_impl);

    TXmlEngTextNode teNode = iDoc.CreateTextNodeL(tekst);
    TXmlEngElement elem = iDoc.CreateElementL(name);
    elem.AppendChildL(teNode);

    TXmlEngCDATASection cdNode = iDoc.CreateCDATASectionL(cdata);
    elem.AppendChildL(cdNode);

    TXmlEngAttr atNode = iDoc.CreateAttributeL(name,value);
    elem.AppendChildL(atNode);

    iDoc.SetDocumentElement(elem);

    RXmlEngDocument doc;
    doc.OpenL(DOM_impl,elem);
    iDoc.Close();
    iDoc = doc.CloneDocumentL();
    doc.Close();

    TXmlEngProcessingInstruction pcNode = iDoc.CreateProcessingInstructionL(name,value);
    iDoc.AppendChildL(pcNode);

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::CloneDocumentL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CloneDocumentL( CStifItemParser& /*aItem*/ )
{
    _LIT8(name,"testdoc");

    RXmlEngDocument doc = iDoc.CloneDocumentL();
    iDoc.Close();
    doc.DocumentElement().AddNewElementL(name);
    iDoc = doc.CloneDocumentL();
    doc.Close();
    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::CheckSiblingFunctionsL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CheckSiblingFunctionsL( CStifItemParser& /*aItem*/ )
{
    TXmlEngElement tmp = iDoc.DocumentElement();
    tmp.FirstChild().SetAsLastSibling();
    tmp.LastChild().PreviousSibling().SetAsFirstSibling();
    tmp.LastChild().PreviousSibling().MoveBeforeSibling(tmp.FirstChild().NextSibling());
    tmp.FirstChild().NextSibling().NextSibling().MoveAfterSibling(tmp.LastChild().PreviousSibling());
    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::CheckInnerXmlL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CheckInnerXmlL( CStifItemParser& aItem )
{
    _LIT(KOutputFileErrorName,"No output file name");
    TPtrC OutputFile;
    if ( aItem.GetNextString(OutputFile) != KErrNone )
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME,KOutputFileErrorName);
        iLog->Log((TDesC)KOutputFileErrorName);
        return KErrGeneral;
    }

    RBuf8 str;
    iDoc.DocumentElement().InnerXmlL(str);

    RFs fs;
    User::LeaveIfError(fs.Connect());
    CleanupClosePushL(fs);

    RFile outputFile;
    TFileName outFileName;
    outFileName.Copy(OutputFile);

    // Open output file
    TInt err = outputFile.Replace(fs,outFileName,EFileShareAny|EFileWrite);

    // If output file is correct
    if (err == KErrNone)
    {
        outputFile.Write(str);
        outputFile.Close();
    }

    if ( aItem.GetNextString(OutputFile) != KErrNone )
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME,KOutputFileErrorName);
        iLog->Log((TDesC)KOutputFileErrorName);
        return KErrGeneral;
    }

    outFileName.Copy(OutputFile);
    err = outputFile.Replace(fs,outFileName,EFileShareAny|EFileWrite);

    // If output file is correct
    if (err == KErrNone)
    {
        iDoc.DocumentElement().FirstChild().NextSibling().InnerXmlL(str);
        outputFile.Write(str);
        outputFile.Close();
    }

    if ( aItem.GetNextString(OutputFile) != KErrNone )
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME,KOutputFileErrorName);
        iLog->Log((TDesC)KOutputFileErrorName);
        return KErrGeneral;
    }

    outFileName.Copy(OutputFile);
    err = outputFile.Replace(fs,outFileName,EFileShareAny|EFileWrite);

    // If output file is correct
    if (err == KErrNone)
    {
        iDoc.DocumentElement().FirstChild().NextSibling().NextSibling().FirstChild().InnerXmlL(str);
        outputFile.Write(str);
        outputFile.Close();
    }
    if ( aItem.GetNextString(OutputFile) != KErrNone )
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME,KOutputFileErrorName);
        iLog->Log((TDesC)KOutputFileErrorName);
        return KErrGeneral;
    }

    outFileName.Copy(OutputFile);
    err = outputFile.Replace(fs,outFileName,EFileShareAny|EFileWrite);

    // If output file is correct
    if (err == KErrNone)
    {
        iDoc.DocumentElement().FirstChild().NextSibling().NextSibling().LastChild().InnerXmlL(str);
        outputFile.Write(str);
        outputFile.Close();
    }

    str.Close();
    CleanupStack::PopAndDestroy();

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::CheckOuterXmlL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CheckOuterXmlL( CStifItemParser& aItem )
{
    _LIT(KOutputFileErrorName,"No output file name");

    TPtrC OutputFile;
    if ( aItem.GetNextString(OutputFile) != KErrNone )
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME,KOutputFileErrorName);
        iLog->Log((TDesC)KOutputFileErrorName);
        return KErrGeneral;
    }

    RBuf8 str;
    iDoc.DocumentElement().OuterXmlL(str);

    RFs fs;
    User::LeaveIfError(fs.Connect());
    CleanupClosePushL(fs);

    RFile outputFile;
    TFileName outFileName;
    outFileName.Copy(OutputFile);

    // Open output file
    TInt err = outputFile.Replace(fs,outFileName,EFileShareAny|EFileWrite);

    // If output file is correct
    if (err == KErrNone)
    {
        outputFile.Write(str);
        outputFile.Close();
    }

    if ( aItem.GetNextString(OutputFile) != KErrNone )
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME,KOutputFileErrorName);
        iLog->Log((TDesC)KOutputFileErrorName);
        return KErrGeneral;
    }

    outFileName.Copy(OutputFile);
    err = outputFile.Replace(fs,outFileName,EFileShareAny|EFileWrite);

    // If output file is correct
    if (err == KErrNone)
    {
        iDoc.DocumentElement().FirstChild().NextSibling().OuterXmlL(str);
        outputFile.Write(str);
        outputFile.Close();
    }

    if ( aItem.GetNextString(OutputFile) != KErrNone )
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME,KOutputFileErrorName);
        iLog->Log((TDesC)KOutputFileErrorName);
        return KErrGeneral;
    }

    outFileName.Copy(OutputFile);
    err = outputFile.Replace(fs,outFileName,EFileShareAny|EFileWrite);

    // If output file is correct
    if (err == KErrNone)
    {
        iDoc.DocumentElement().FirstChild().NextSibling().NextSibling().FirstChild().OuterXmlL(str);
        outputFile.Write(str);
        outputFile.Close();
    }
    if ( aItem.GetNextString(OutputFile) != KErrNone )
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME,KOutputFileErrorName);
        iLog->Log((TDesC)KOutputFileErrorName);
        return KErrGeneral;
    }

    outFileName.Copy(OutputFile);
    err = outputFile.Replace(fs,outFileName,EFileShareAny|EFileWrite);

    // If output file is correct
    if (err == KErrNone)
    {
        iDoc.DocumentElement().FirstChild().NextSibling().NextSibling().LastChild().OuterXmlL(str);
        outputFile.Write(str);
        outputFile.Close();
    }

    str.Close();
    CleanupStack::PopAndDestroy();

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::CheckNodeParametersL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CheckNodeParametersL( CStifItemParser& /*aItem*/)
{

    TXmlEngNode tmp = iDoc.DocumentElement();

    _LIT8(str,"doc");
    _LIT(KNameError,"Name checking error.");
    if(tmp.Name().Compare(str))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KNameError);
        iLog->Log((TDesC)KNameError);
        return KErrGeneral;
    }

    _LIT(KChildError,"Has child nodes checking error.");
    if(!(tmp.HasChildNodes()))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KChildError);
        iLog->Log((TDesC)KChildError);
        return KErrGeneral;
    }

    _LIT(KAttrError,"Has attributes checking error.");
    if(!(tmp.HasAttributes()))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KAttrError);
        iLog->Log((TDesC)KAttrError);
        return KErrGeneral;
    }

    _LIT8(uri,"http://test.pl");
    _LIT(KNamespaceError,"Namespace uri checking error.");
    if(tmp.NamespaceUri().Compare(uri))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KNamespaceError);
        iLog->Log((TDesC)KNamespaceError);
        return KErrGeneral;
    }

    _LIT(KPrefError,"Namespace prefix checking error.");
    if(tmp.Prefix().Compare(KNullDesC8))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KPrefError);
        iLog->Log((TDesC)KPrefError);
        return KErrGeneral;
    }

    tmp = iDoc.DocumentElement().FirstChild().NextSibling();

    _LIT8(str2,"test2");
    if(tmp.Name().Compare(str2))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KNameError);
        iLog->Log((TDesC)KNameError);
        return KErrGeneral;
    }

    if(tmp.HasChildNodes())
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KChildError);
        iLog->Log((TDesC)KChildError);
        return KErrGeneral;
    }

    if(tmp.HasAttributes())
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KAttrError);
        iLog->Log((TDesC)KAttrError);
        return KErrGeneral;
    }

    _LIT8(uri2,"http://test.com");
    if(tmp.NamespaceUri().Compare(uri2))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KNamespaceError);
        iLog->Log((TDesC)KNamespaceError);
        return KErrGeneral;
    }

    _LIT8(pref,"testns");
    if(tmp.Prefix().Compare(pref))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KPrefError);
        iLog->Log((TDesC)KPrefError);
        return KErrGeneral;
    }

    return KErrNone;
}


// -----------------------------------------------------------------------------
// CDomBCTester::ParentNodesL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::ParentNodesL( CStifItemParser& /*aItem*/ )
{
    TXmlEngNode tmp = iDoc.DocumentElement();

    _LIT(KDocError,"Document element checking error.");
    if(!(tmp.OwnerDocument().IsSameNode(iDoc)))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KDocError);
        iLog->Log((TDesC)KDocError);
        return KErrGeneral;
    }

    tmp = tmp.FirstChild().NextSibling();

    _LIT(KParError,"Parent element checking error.");
    if(!(tmp.ParentNode().IsSameNode(iDoc.DocumentElement())))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KParError);
        iLog->Log((TDesC)KParError);
        return KErrGeneral;
    }

    return KErrNone;
}


// -----------------------------------------------------------------------------
// CDomBCTester::CheckNamespacesL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CheckNamespacesL( CStifItemParser& /*aItem*/ )
{
    TXmlEngNode tmp = iDoc.DocumentElement();
    TXmlEngNamespace nam = tmp.NamespaceDeclaration();

    _LIT8(arg,"http://test.pl");
    _LIT(KUriError,"Namespace uri checking error.");
    if(nam.Uri().Compare(arg))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KUriError);
        iLog->Log((TDesC)KUriError);
        return KErrGeneral;
    }

    _LIT(KPrefError,"Namespace prefix checking error.");
    if(nam.Prefix().Compare(KNullDesC8))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KPrefError);
        iLog->Log((TDesC)KPrefError);
        return KErrGeneral;
    }

    _LIT(KDefError,"Is default checking error.");
    if(!nam.IsDefault())
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KDefError);
        iLog->Log((TDesC)KDefError);
        return KErrGeneral;
    }

    _LIT(KDecError,"Is declared checking error.");
    if(nam.IsUndefined())
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KDecError);
        iLog->Log((TDesC)KDecError);
        return KErrGeneral;
    }

    _LIT(KTypeError,"Node type checking error.");
    if(!(nam.NodeType() == TXmlEngNode::ENamespaceDeclaration))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KTypeError);
        iLog->Log((TDesC)KTypeError);
        return KErrGeneral;
    }

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::CheckProcessingInstructionL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CheckProcessingInstructionL( CStifItemParser& /*aItem*/ )
{
    _LIT8(target,"testtarget");
    _LIT8(data,"data test data");

    TXmlEngNode tmp = iDoc.DocumentElement();
    TBool i = tmp.HasChildNodes();

    tmp = tmp.FirstChild();

    _LIT(KTypeError,"Node type checking error.");
    if(!(tmp.NodeType() == TXmlEngNode::EProcessingInstruction))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KTypeError);
        iLog->Log((TDesC)KTypeError);
        return KErrGeneral;
    }

    _LIT(KTargetError,"Target checking error.");
    if(tmp.AsProcessingInstruction().Target().Compare(target))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KTargetError);
        iLog->Log((TDesC)KTargetError);
        return KErrGeneral;
    }

    _LIT(KDataError,"Data checking error.");
    if(tmp.AsProcessingInstruction().Data().Compare(data))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KDataError);
        iLog->Log((TDesC)KDataError);
        return KErrGeneral;
    }

    _LIT8(arg, "new data");
    tmp.AsProcessingInstruction().SetDataL(arg);

    return KErrNone;
}


// -----------------------------------------------------------------------------
// CDomBCTester::CheckCommentsL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CheckCommentsL( CStifItemParser& /*aItem*/ )
{

    TText * text = (TText*) L" new comment 1 ";
    TPtrC ptr(text);

    _LIT8(com1, " new comment 1 ");
    _LIT8(com2, "added comment 2 ");

    TXmlEngNode tmp = iDoc.FirstChild();

    _LIT(KTypeError,"Node type checking error.");
    if(!(tmp.NodeType() == TXmlEngNode::EComment))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KTypeError);
        iLog->Log((TDesC)KTypeError);
        return KErrGeneral;
    }

    _LIT8(com3, " comment 1 ");

    _LIT(KContentError,"Content checking error.");
    if(tmp.AsComment().Contents().Compare(com3))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KContentError);
        iLog->Log((TDesC)KContentError);
        return KErrGeneral;
    }

    tmp.AsComment().SetContentsL(com1);


    _LIT(KLengthError,"Length checking error.");
    if(!(tmp.AsComment().Length() == ptr.Length()))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KLengthError);
        iLog->Log((TDesC)KLengthError);
        return KErrGeneral;
    }

    TXmlEngComment com = iDoc.DocumentElement().LastChild().AsComment();

    if(!(com.NodeType() == TXmlEngNode::EComment))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KTypeError);
        iLog->Log((TDesC)KTypeError);
        return KErrGeneral;
    }

    _LIT8(com4, " comment 2 ");
    if(com.AsComment().Contents().Compare(com4))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KContentError);
        iLog->Log((TDesC)KContentError);
        return KErrGeneral;
    }

    com.AppendContentsL(com2);

    TXmlEngComment comm;
    comm = iDoc.CreateCommentL();
    iDoc.AppendChildL(comm);

    return KErrNone;
}


// -----------------------------------------------------------------------------
// CDomBCTester::CheckCDATAL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CheckCDATAL( CStifItemParser& /*aItem*/)
{
    TXmlEngCDATASection tmp;
    tmp = iDoc.DocumentElement().FirstChild().NextSibling().AsCDATASection();

    _LIT8(data, " < & test cdata > --> ");

    _LIT(KTypeError,"Node type checking error.");
    if(!(tmp.NodeType() == TXmlEngNode::ECDATASection))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KTypeError);
        iLog->Log((TDesC)KTypeError);
        return KErrGeneral;
    }

    _LIT(KContentError,"Content checking error.");
    if(tmp.Contents().Compare(data))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KContentError);
        iLog->Log((TDesC)KContentError);
        return KErrGeneral;
    }

    _LIT8(com2, "added comment 2 ");
    tmp.AppendContentsL(com2);

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::CheckTextNodeL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CheckTextNodeL( CStifItemParser& /*aItem*/)
{
    TXmlEngNode tmp;
    tmp = iDoc.DocumentElement().FirstChild();

    _LIT8(data, "\nline content");

    _LIT(KTypeError,"Node type checking error.");
    if(!(tmp.NodeType() == TXmlEngNode::EText))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KTypeError);
        iLog->Log((TDesC)KTypeError);
        return KErrGeneral;
    }

    _LIT(KWhiteError,"Is whitespace checking error.");
    if(!(tmp.AsText().IsElementContentWhitespace()))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KWhiteError);
        iLog->Log((TDesC)KWhiteError);
        return KErrGeneral;
    }

    tmp = iDoc.DocumentElement().LastChild();
    TXmlEngTextNode text = tmp.AsText();

    _LIT(KContentError,"Content checking error.");
    TPtrC8 st = text.Contents();
    if(text.Contents().Compare(data))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KContentError);
        iLog->Log((TDesC)KContentError);
        return KErrGeneral;
    }

    _LIT(KLengthError,"Length checking error.");
    if(!(text.Length() == data().Length()))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KLengthError);
        iLog->Log((TDesC)KLengthError);
        return KErrGeneral;
    }

    _LIT8(com2, " added comment 2 ");
    text.AppendContentsL(com2);

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::CheckNodeValueL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CheckNodeValueL( CStifItemParser& /*aItem*/)
{
    TXmlEngNode tmp;
    tmp = iDoc.DocumentElement().FirstChild();

    _LIT8(data, "test");
    TPtrC8 value = tmp.Value();

    _LIT(KContentError,"Content checking error.");
    if(value.Compare(data))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KContentError);
        iLog->Log((TDesC)KContentError);
        return KErrGeneral;
    }

    _LIT8(val2, "newelem");
    tmp.SetValueL(val2);

    RXmlEngNodeList<TXmlEngAttr> list;
    iDoc.DocumentElement().GetAttributes(list);
    _LIT8(val3, "newattrval");
    if(list.HasNext())
    {
        tmp = list.Next();
        TPtrC8 value = tmp.Value();
        if(value.Compare(data))
        {
            TestModuleIf().Printf( infoNum++,KTEST_NAME, KContentError);
            iLog->Log((TDesC)KContentError);
            return KErrGeneral;
        }

        tmp.SetValueL(val3);
        list.Close();
    }
    else
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KContentError);
        iLog->Log((TDesC)KContentError);
        return KErrGeneral;
    }

    RXmlEngNodeList<TXmlEngNode> nodeList;
    iDoc.DocumentElement().FirstChild().GetChildNodes(nodeList);
    TPtrC8 val4 = nodeList.Next().Value();
    if(val4.Compare(val2))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KContentError);
        iLog->Log((TDesC)KContentError);
        return KErrGeneral;
    }

    nodeList.Close();
    return KErrNone;
}


// -----------------------------------------------------------------------------
// CDomBCTester::NodeNamespacePocessingL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::NodeNamespacePocessingL( CStifItemParser& /*aItem*/ )
{
    TXmlEngNode tmp = iDoc.DocumentElement().FirstChild();

    _LIT8(uri, "http://test.com");
    _LIT8(uriD, "http://test.pl");
    _LIT8(pref, "testns");
    _LIT(KUriError,"Namespace finding for prefix error.");
    if(tmp.LookupNamespaceUriL(pref).Compare(uri))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KUriError);
        iLog->Log((TDesC)KUriError);
        return KErrGeneral;
    }

    _LIT(KPrefError,"Prefix finding for uri error.");
    if(tmp.LookupPrefixL(uri).Compare(pref))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KPrefError);
        iLog->Log((TDesC)KPrefError);
        return KErrGeneral;
    }

    _LIT(KDefError,"Is default checking error.");
    if(tmp.IsDefaultNamespaceL(uri))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KDefError);
        iLog->Log((TDesC)KDefError);
        return KErrGeneral;
    }

    if(!tmp.IsDefaultNamespaceL(uriD))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KDefError);
        iLog->Log((TDesC)KDefError);
        return KErrGeneral;
    }
    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::ElementNamespacePocessingL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::ElementNamespacePocessingL( CStifItemParser& /*aItem*/ )
{
    TXmlEngElement tmp = iDoc.DocumentElement().FirstChild().AsElement();

    _LIT8(uri, "http://test.com");
    _LIT8(uriD, "http://test.pl");
    _LIT8(pref, "testns");
    _LIT(KUriError,"Namespace finding for prefix error.");
    if(tmp.LookupNamespaceUriL(pref).Compare(uri))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KUriError);
        iLog->Log((TDesC)KUriError);
        return KErrGeneral;
    }

    _LIT(KPrefError,"Prefix finding for uri error.");
    if(tmp.LookupPrefixL(uri).Compare(pref))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KPrefError);
        iLog->Log((TDesC)KPrefError);
        return KErrGeneral;
    }

    _LIT(KDefError,"Default namespace checking error.");
    if(tmp.DefaultNamespaceL().Uri().Compare(uriD))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KDefError);
        iLog->Log((TDesC)KDefError);
        return KErrGeneral;
    }

    _LIT8(xmlU,"http://www.w3.org/XML/1998/namespace");
    _LIT8(xmlP,"xml");
    _LIT(KXMLError,"XML namespace checking error.");
    if(!(!tmp.TheXMLNamespaceL().Uri().Compare(xmlU) && !tmp.TheXMLNamespaceL().Prefix().Compare(xmlP)))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KXMLError);
        iLog->Log((TDesC)KXMLError);
        return KErrGeneral;
    }

    _LIT(KDeclError,"Has namespace declaration function checking error.");
    if(!iDoc.DocumentElement().AsElement().HasNsDeclarationForPrefixL(pref))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KDeclError);
        iLog->Log((TDesC)KDeclError);
        return KErrGeneral;
    }

    _LIT8(str,"wrong");
    _LIT8(str2,"http://wrong.com");
    if(tmp.HasNsDeclarationForPrefixL(str))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KDeclError);
        iLog->Log((TDesC)KDeclError);
        return KErrGeneral;
    }

    tmp.FindOrCreateNsDeclL(str2,str);
    tmp.FindOrCreateNsDeclL(uri);
    _LIT8(str3,"newns");
    _LIT8(str4,"http://newns.com");
    tmp = tmp.NextSibling().AsElement();
    tmp.AddNamespaceDeclarationL (str4,str3);
    tmp.SetNoDefaultNamespaceL();

    return KErrNone;
}


// -----------------------------------------------------------------------------
// CDomBCTester::CheckEntityRefL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CheckEntityRefL( CStifItemParser& /*aItem*/ )
{
    TXmlEngNode tmp = iDoc.DocumentElement().FirstChild();

    _LIT(KSimTextError,"Is simple text checking error.");
    if(!tmp.IsSimpleTextContents())
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KSimTextError);
        iLog->Log((TDesC)KSimTextError);
        return KErrGeneral;
    }

    tmp = iDoc.DocumentElement().LastChild();
    if(tmp.IsSimpleTextContents())
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KSimTextError);
        iLog->Log((TDesC)KSimTextError);
        return KErrGeneral;
    }

    TXmlEngEntityReference ref;
    ref = tmp.FirstChild().AsEntityReference();
    _LIT(KTypeError,"Node type checking error.");
    if(!(ref.NodeType() == TXmlEngNode::EEntityReference))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KTypeError);
        iLog->Log((TDesC)KTypeError);
        return KErrGeneral;
    }

    _LIT8(str, "1.1 test");
    RBuf8 str2;
    tmp.WholeTextContentsCopyL(str2);

    _LIT(KContentError,"Content checking error.");
    if(str2.Compare(str))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KContentError);
        iLog->Log((TDesC)KContentError);
        return KErrGeneral;
    }

    str2.Close();

    tmp = tmp.PreviousSibling();
    _LIT8(str3, "test 1.1 test");
    RBuf8 str4;
    tmp.WholeTextContentsCopyL(str4);

    if(str4.Compare(str3))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KContentError);
        iLog->Log((TDesC)KContentError);
        return KErrGeneral;
    }

    str4.Close();

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::NodeTreeModificationL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::NodeTreeModificationL( CStifItemParser& /*aItem*/)
{
    TXmlEngNode tmp = iDoc.DocumentElement();
    TXmlEngNode tmp2 = tmp.FirstChild().CopyL();
    tmp.AppendChildL(tmp2);
    tmp.FirstChild().NextSibling().CopyToL(tmp.LastChild());
    tmp.LastChild().PreviousSibling().ReplaceWith(tmp.FirstChild().NextSibling());
    tmp.FirstChild().MoveTo(tmp.FirstChild().NextSibling());
    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::NodeTreeDeletingL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::NodeTreeDeletingL( CStifItemParser& /*aItem*/)
{
    TXmlEngNode tmp = iDoc.DocumentElement();
    TXmlEngNode tmp2 = tmp.FirstChild().Unlink();
    tmp2 = tmp.LastChild().SubstituteForL(tmp2);
    tmp2.Remove();
    tmp.FirstChild().Remove();
    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::CheckNodeListL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CheckNodeListL( CStifItemParser& /*aItem*/ )
{
    TXmlEngNode tmp;
    tmp = iDoc.DocumentElement();

    RXmlEngNodeList<TXmlEngElement> nodeList;
    tmp.AsElement().GetChildElements(nodeList);

    _LIT(KChildError,"Child count checking error.");
    if(nodeList.Count() != 4)
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KChildError);
        iLog->Log((TDesC)KChildError);
        return KErrGeneral;
    }

    _LIT(KHasNextError,"Has next checking error.");
    if (!nodeList.HasNext())
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KHasNextError);
        iLog->Log((TDesC)KHasNextError);
        return KErrGeneral;
    }

    TXmlEngElement tmpE;
    tmpE = nodeList.Next();

    nodeList.Next();
    nodeList.Next();
    tmpE = nodeList.Next();
    nodeList.Next();

    if (nodeList.HasNext())
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KHasNextError);
        iLog->Log((TDesC)KHasNextError);
        return KErrGeneral;
    }

    nodeList.Close();

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::CheckAttributesL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CheckAttributesL( CStifItemParser& /*aItem*/ )
{
    TXmlEngElement tmp = iDoc.DocumentElement().FirstChild().AsElement();

    RXmlEngNodeList<TXmlEngAttr> attrList;
    tmp.GetAttributes(attrList);

    TXmlEngAttr tmpA;
    tmpA = attrList.Next();

    _LIT(KTypeError,"Node type checking error.");
    if(!(tmpA.NodeType() == TXmlEngNode::EAttribute))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KTypeError);
        iLog->Log((TDesC)KTypeError);
        return KErrGeneral;
    }

    tmpA = tmpA.CopyL();
    tmp.NextSibling().AppendChildL(tmpA);

    tmpA = attrList.Next();
    tmpA.Remove();

    tmpA = attrList.Next();

    _LIT(KParError,"Parent element checking error.");
    if(!(tmpA.OwnerElement().IsSameNode(tmp)))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KParError);
        iLog->Log((TDesC)KParError);
        return KErrGeneral;
    }

    _LIT8(str,"attr3");
    _LIT8(str1,"test");
    _LIT8(str2,"test&test1;test");
    _LIT(KNameError,"Attribute name checking error.");
    if(tmpA.Name().Compare(str))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KNameError);
        iLog->Log((TDesC)KNameError);
        return KErrGeneral;
    }

    _LIT(KAttrError,"Attribute value checking error.");
    if(tmpA.Value().Compare(str1))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KAttrError);
        iLog->Log((TDesC)KAttrError);
        return KErrGeneral;
    }

    tmpA.SetEscapedValueL(str2);

    tmpA = attrList.Next();
    _LIT8(str3,"1.1tekst");
    RBuf8 tmpS;
    tmpA.WholeValueCopyL(tmpS);
    _LIT(KAttr2Error,"Attribute value with entity checking error.");
    if(tmpS.Compare(str3))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KAttr2Error);
        iLog->Log((TDesC)KAttr2Error);
        return KErrGeneral;
    }
    tmpS.Close();
    attrList.Close();

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::CheckElementAttributesL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CheckElementAttributesL( CStifItemParser& /*aItem*/ )
{
    TXmlEngElement tmp = iDoc.DocumentElement().FirstChild().AsElement();

    _LIT8(str,"attr2");
    _LIT8(str2,"wrong");

    _LIT(KHasAttError,"Has attribute checking error.");
    if(!(tmp.HasAttributeL(str,KNullDesC8)))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KHasAttError);
        iLog->Log((TDesC)KHasAttError);
        return KErrGeneral;
    }

    if(tmp.HasAttributeL(str,str2))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KHasAttError);
        iLog->Log((TDesC)KHasAttError);
        return KErrGeneral;
    }

    if(tmp.HasAttributeL(str2,KNullDesC8))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KHasAttError);
        iLog->Log((TDesC)KHasAttError);
        return KErrGeneral;
    }

    _LIT8(str3,"tewt");
    _LIT(KAttError,"Attribute node function checking error.");
    if(tmp.AttributeNodeL(str,KNullDesC8).Value().Compare(str3))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KAttError);
        iLog->Log((TDesC)KAttError);
        return KErrGeneral;
    }

    _LIT(KAttVError,"Attribute value function checking error.");
    if(tmp.AttributeValueL(str,KNullDesC8).Compare(str3))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KAttVError);
        iLog->Log((TDesC)KAttVError);
        return KErrGeneral;
    }

    if(tmp.AttributeValueL(str2,KNullDesC8).Compare(KNullDesC8))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KAttVError);
        iLog->Log((TDesC)KAttVError);
        return KErrGeneral;
    }

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::CheckModifAttributesL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CheckModifAttributesL( CStifItemParser& /*aItem*/ )
{
    TXmlEngElement tmp = iDoc.DocumentElement().FirstChild().AsElement();

    _LIT8(str,"attr2");
    _LIT8(str2,"wrong");

    _LIT8(str4,"attr3");
    tmp.RemoveAttributeL(str4,KNullDesC8);
    tmp.SetAttributeL(str,str2);

    tmp = tmp.NextSibling().AsElement();
    _LIT8(uri,"test.com");
    _LIT8(pref,"testns");
    tmp.SetAttributeL(str,str2,uri,pref);
    TXmlEngAttr tmpA = iDoc.CreateAttributeL(str4);
    tmpA.SetValueL(str4);
    tmp.SetAttributeNodeL(tmpA);

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::AddingAttributesL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::AddingAttributesL( CStifItemParser& /*aItem*/ )
{
    TXmlEngElement tmp = iDoc.DocumentElement().FirstChild().AsElement();

    _LIT8(str,"attr2");
    _LIT8(str2,"wrong");
    _LIT8(pref,"testns");
    _LIT8(uri, "http://test.com");

    tmp.AddNewAttributeL(str,str2);
    tmp.AddNewAttributeWithNsL(str,str2,uri);

    tmp = tmp.NextSibling().AsElement();
    tmp.AddNewAttributeSameNsL(str,str2);
    tmp.AddNewAttributeUsePrefixL(str2,str,pref);

    _LIT8(str4,"attr3");
    _LIT8(pref2,"testns2");
    _LIT8(uri2, "http://test.com.pl");
    tmp.AddNewAttributeL(str4,str2,uri2,pref2);

    tmp = tmp.NextSibling().NextSibling().AsElement();
    tmp.RemoveAttributes();
    tmp.CopyAttributesL(iDoc.DocumentElement().FirstChild().AsElement());

    tmp = tmp.NextSibling().AsElement();
    TXmlEngNamespace tmpNs = tmp.FindOrCreateNsDeclL(uri2,pref2);
    tmp.AddNewAttributeL(str4,str,tmpNs);

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::AddingElementsL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::AddingElementsL( CStifItemParser& /*aItem*/ )
{
    TXmlEngElement tmp = iDoc.DocumentElement().FirstChild().AsElement();

    _LIT8(str,"element");
    _LIT8(str2,"wrong");
    _LIT8(pref,"testns");
    _LIT8(uri, "http://test.com");

    tmp.AddNewElementL(str);
    tmp.AddNewElementWithNsL(str,uri);

    tmp = tmp.NextSibling().AsElement();
    tmp.AddNewElementSameNsL(str);
    tmp.AddNewElementUsePrefixL(str2,pref);

    _LIT8(str4,"element3");
    _LIT8(pref2,"testns2");
    _LIT8(uri2, "http://test.com.pl");
    tmp.AddNewElementL(str4,uri2,pref2);

    tmp = tmp.NextSibling().NextSibling().AsElement();
    tmp.CopyChildrenL(iDoc.DocumentElement().FirstChild().AsElement());

    tmp = tmp.NextSibling().AsElement();
    TXmlEngNamespace tmpNs = tmp.FindOrCreateNsDeclL(uri2,pref2);
    tmp.AddNewElementL(str4,tmpNs);

    _LIT8(uri3, "http://test.test.pl");
    tmp.AddNewElementAutoPrefixL(str4,uri3,iDoc.DocumentElement());

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::CheckModifElementL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CheckModifElementL( CStifItemParser& /*aItem*/ )
{
    TXmlEngElement tmp = iDoc.DocumentElement().FirstChild().NextSibling().AsElement().CopyL();
    iDoc.DocumentElement().AppendChildL(tmp);
    tmp = iDoc.DocumentElement().FirstChild().NextSibling().AsElement().ElementCopyNoChildrenL(FALSE);
    iDoc.DocumentElement().AppendChildL(tmp);
    iDoc.DocumentElement().FirstChild().NextSibling().AsElement().ClearElement();

    _LIT8(str,"elem1");
    iDoc.DocumentElement().RemoveChildElementsL(str,KNullDesC8);

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::CheckModifElementL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CheckNextL( CStifItemParser& /*aItem*/ )
{
    TPtrC8 tmp = iDoc.DocumentElement().FirstChild().FirstChild().FirstChild().FirstChild().AsCDATASection().Contents();
    HBufC8* test = tmp.AllocL();           //pjj18 leak!!!
    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::SetElementTextL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::SetElementTextL( CStifItemParser& /*aItem*/ )
{
    TXmlEngElement tmp = iDoc.DocumentElement().FirstChild().AsElement();

    _LIT8(str4,"test");
    _LIT(KContentError,"Content checking error.");
    if(tmp.Text().Compare(str4))
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KContentError);
        iLog->Log((TDesC)KContentError);
        return KErrGeneral;
    }

    _LIT8(str,"new text");
    _LIT8(str2," new added text");
    _LIT8(str3,"test&test1;test");
    tmp.SetTextL(str);
    tmp.AddTextL(str2);
    tmp = tmp.NextSibling().AsElement();
    tmp.SetEscapedTextL(str3);

    _LIT8(name,"elem1");
    _LIT8(uri,"http://test.com");
    RXmlEngNodeList<TXmlEngElement> nodeList;
    iDoc.DocumentElement().AsElement().GetElementsByTagNameL(nodeList,name,uri);

    _LIT(KChildError,"GetElementsByTagName checking error.");
    if(nodeList.Count() != 2)
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KChildError);
        iLog->Log((TDesC)KChildError);
        return KErrGeneral;
    }
    nodeList.Close();

    iDoc.DocumentElement().AsElement().GetElementsByTagNameL(nodeList,name,
    iDoc.DocumentElement().AsElement().DefaultNamespaceL().Uri());
    if(nodeList.Count() != 1)
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KChildError);
        iLog->Log((TDesC)KChildError);
        return KErrGeneral;
    }

    iDoc.DocumentElement().AsElement().RemoveNamespaceDeclarations();
    iDoc.DocumentElement().ReconcileNamespacesL();
    nodeList.Close();

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::AddXmlIdL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::AddXmlIdL( CStifItemParser& aItem )
{
    TXmlEngElement root = iDoc.DocumentElement();

    RBuf8 nameS;
    CleanupClosePushL(nameS);
    RBuf8 uriS;
    CleanupClosePushL(uriS);

    TPtrC name;
    User::LeaveIfError( aItem.GetNextString(name) );
    nameS.CreateL( name.Length() );
    nameS.Copy( name );

    TPtrC uri;
    if (aItem.GetNextString(uri) == KErrNone)
    {
        uriS.CreateL( uri.Length() );
        uriS.Copy( uri );
    }

    iDoc.RegisterXmlIdL(nameS,uriS);
    CleanupStack::PopAndDestroy(&uriS);
    CleanupStack::PopAndDestroy(&nameS);

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::AddXmlId2L
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::AddXmlId2L( CStifItemParser& aItem )
{
    TXmlEngElement root = iDoc.DocumentElement();

    RBuf8 nameS;
    CleanupClosePushL(nameS);
    RBuf8 uriS;
    CleanupClosePushL(uriS);
    RBuf8 valueS;
    CleanupClosePushL(valueS);

    TPtrC name;
    User::LeaveIfError( aItem.GetNextString(name) );
    nameS.CreateL( name.Length() );
    nameS.Copy( name );

    TPtrC uri;
    aItem.GetNextString(uri);
    uriS.CreateL( uri.Length() );
    uriS.Copy( uri );

    TPtrC value;
    aItem.GetNextString(value);
    valueS.CreateL( value.Length() );
    valueS.Copy( value );

    iDoc.RegisterXmlIdL(root.FirstChild().NextSibling().AsElement(),nameS,uriS);
    TXmlEngElement element = iDoc.FindElementByXmlIdL(valueS);

    CleanupStack::PopAndDestroy(&valueS);
    CleanupStack::PopAndDestroy(&uriS);
    CleanupStack::PopAndDestroy(&nameS);

    if ( element.NotNull() )
    {
        return KErrNone;
    }
    else
    {
        return KErrNotFound;
    }
}

// -----------------------------------------------------------------------------
// CDomBCTester::AddXmlId3L
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::AddXmlId3L( CStifItemParser& aItem )
{
    TInt nResult = KErrNone;
    TXmlEngElement root = iDoc.DocumentElement();

    RBuf8 uriS;
    CleanupClosePushL(uriS);

    TPtrC uri;
    aItem.GetNextString(uri);
    uriS.CreateL( uri.Length() );
    uriS.Copy( uri );

    TPtrC pDirtyReturn;
    aItem.GetNextString( pDirtyReturn );

    TLex inputNum (pDirtyReturn);
    TInt dirtyReturn;
    inputNum.Val(dirtyReturn);

    TRAPD(trapResult,
    iDoc.RegisterXmlIdL(KNullDesC8,uriS);
    );
    if (trapResult == dirtyReturn ) nResult = KErrNone;
    else if (trapResult != KErrNone) nResult = trapResult;
    else nResult = KErrGeneral;

    CleanupStack::PopAndDestroy(&uriS);
    return nResult;
}
// -----------------------------------------------------------------------------
// CDomBCTester::FindXmlIdL
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::FindXmlIdL( CStifItemParser& aItem )
{
    TBool shouldFind;
    RBuf8 valueS;
    CleanupClosePushL( valueS );

    TPtrC value;
    User::LeaveIfError( aItem.GetNextString(value) );
    valueS.CreateL( value.Length() );
    valueS.Copy(value);

    TPtrC ptr;
    shouldFind = (aItem.GetNextString(ptr)!=KErrNone);

    TXmlEngElement element = iDoc.FindElementByXmlIdL(valueS);

    CleanupStack::PopAndDestroy( &valueS );
    if ( shouldFind!=(element.IsNull()) )
    {
        return KErrNone;
    }
    else
    {
        return KErrNotFound;
    }
}

// -----------------------------------------------------------------------------
// CDomBCTester::SetTextNoEncTestL(CStifItemParser& aItem)
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::SetTextNoEncTestL(CStifItemParser& aItem)
{
    TPtrC pDoc;
    aItem.GetNextString(pDoc);

    TPtrC pData;
    aItem.GetNextString(pData);

    TPtrC pOut;
    aItem.GetNextString(pOut);

    iDoc = parser.ParseFileL(pDoc);

    HBufC8* dataBuffer = ReadFileToBufferL(pData);
    CleanupStack::PushL( dataBuffer );

    RXmlEngNodeList<TXmlEngNode> aList;
    iDoc.GetChildNodes(aList);
    TXmlEngNode current = aList.Next();

    while( current.NotNull() )
    {
        if(current.NodeType() == 1 )
        {
            current.AsElement().SetTextNoEncL(dataBuffer->Des());
        }
        current = aList.Next();
    }

    iDoc.SaveL(pOut);

    CleanupStack::PopAndDestroy( 1 );
    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::AppendTextNoEncTestL(CStifItemParser& aItem)
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

TInt CDomBCTester::AppendTextNoEncTestL(CStifItemParser& aItem)
{
    TPtrC pDoc;
    aItem.GetNextString(pDoc);

    TPtrC pData;
    aItem.GetNextString(pData);

    TPtrC pOut;
    aItem.GetNextString(pOut);

    iDoc = parser.ParseFileL(pDoc);

    HBufC8* dataBuffer = ReadFileToBufferL(pData);
    CleanupStack::PushL( dataBuffer );

    RXmlEngNodeList<TXmlEngNode> aList;
    iDoc.GetChildNodes(aList);
    TXmlEngNode current = aList.Next();

    while( current.NotNull() )
    {
        if(current.NodeType() == 1 )
        {
            current.AsElement().AppendTextNoEncL(dataBuffer->Des());
            break;
        }
        current = aList.Next();
    }

    iDoc.SaveL(pOut);

    CleanupStack::PopAndDestroy( 1 );
    return KErrNone;
}
// -----------------------------------------------------------------------------
// CDomBCTester::SetValueNoEncTestL(CStifItemParser& aItem)
// Check if predefined entities are not converted into characters they represent
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::SetValueNoEncTestL(CStifItemParser& aItem)
{
    TPtrC pDoc;
    aItem.GetNextString(pDoc);

    TPtrC pOut;
    aItem.GetNextString(pOut);

    iDoc = parser.ParseFileL(pDoc);
    TXmlEngElement tmp = iDoc.DocumentElement();

    _LIT8(str,"attr2");
    _LIT8(str2,"wrong");
    _LIT8(uri, "http://test.com");

    tmp.AddNewAttributeL(str,str2);
    tmp.AddNewAttributeWithNsL(str,str2,uri);

    _LIT8(noEnc, "&sup3; &#179;  &#xB3; < > ! @ $ &");
    //TPtrC8 noEnc = _L8("&sup3; &#179;  &#xB3; < > ! @ $ &");
    TXmlEngAttr attr;
    if( tmp.HasAttributeL(str))
    {
        attr = tmp.AttributeNodeL(str);
    }
    else
    {
        return KErrNotFound;
    }

    attr.SetValueNoEncL(noEnc);
    iDoc.SaveL(pOut);

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::CreateDocument2L
// test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CreateDocument2L( CStifItemParser& aItem )
{
    TPtrC pOut;
    aItem.GetNextString( pOut );

    _LIT8(name,"doc");
    _LIT8(uri,"http://test.com");
    _LIT8(arg1,"1.1");
    _LIT8(arg2,"http://test2.org");

    iDoc.OpenL(DOM_impl);
    iDoc.CreateDocumentElementL(name);
    iDoc.DocumentElement().SetDefaultNamespaceL(uri);
    iDoc.SetStandalone(TRUE);
    iDoc.SetXmlVersionL(arg1);
    iDoc.SetDocumentUriL(arg2);

    // test function Implementation()
    RXmlEngDOMImplementation DOM_impl_2 = iDoc.Implementation();
    RXmlEngDocument Doc2;

    Doc2.OpenL(DOM_impl_2, iDoc.DocumentElement());
    Doc2.SaveL(pOut);

    return KErrNone;
}
// -----------------------------------------------------------------------------
// CDomBCTester::CreateEntityReferenceTestL
// Check if entity reference is created correctly
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::CreateEntityReferenceTestL(CStifItemParser& aItem)
{
    TPtrC pDoc;
    aItem.GetNextString(pDoc);

    TPtrC pOut;
    aItem.GetNextString(pOut);

    _LIT8(entity, "#xB3");

    iDoc = parser.ParseFileL(pDoc);
    TXmlEngEntityReference entref = iDoc.CreateEntityReferenceL(entity);
    iDoc.DocumentElement().AppendChildL(entref);
    iDoc.SaveL(pOut);

    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::ParseFileDOM2L
// Parse file with a handle to a file server session
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::ParseFileDom2L( CStifItemParser& aItem )
{

    _LIT(KSourceFileErrorName,"No source file name.");
    _LIT(KEndParsing,"Parsing end.");

    TPtrC SrcFile;
    TPtrC tmp;
    TBool map = TRUE;
    if ( aItem.GetNextString(SrcFile) != KErrNone )
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME,KSourceFileErrorName);
        iLog->Log((TDesC)KSourceFileErrorName);
        return KErrGeneral;
    }

    if ( aItem.GetNextString(tmp) == KErrNone )
    {
        map = FALSE;
    }
    TFileName srcFileName;
    srcFileName.Copy(SrcFile);

    RFs fServer;
    User::LeaveIfError(fServer.Connect());
    CleanupClosePushL( fServer );

    TInt err;
    TRAP(err, iDoc = parser.ParseFileL(fServer,srcFileName));

    if(map && err == KXmlEngErrParsing)
    {
        iLastError = parser.GetLastParsingError();
    }
    else
    {
        iLastError = err;
    }
    TestModuleIf().Printf( infoNum++,KTEST_NAME,KEndParsing);
    iLog->Log((TDesC)KEndParsing);

    CleanupStack::PopAndDestroy( &fServer );
    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::ParseFileDOM3L
// test parse from buffer
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::ParseFileDom3L( CStifItemParser& aItem )
{

    _LIT(KSourceFileErrorName,"No source file name.");
    _LIT(KEndParsing,"Parsing end.");

    TPtrC SrcFile;
    TPtrC tmp;
    TBool map = TRUE;
    if ( aItem.GetNextString(SrcFile) != KErrNone )
    {
        TestModuleIf().Printf( infoNum++,KTEST_NAME,KSourceFileErrorName);
        iLog->Log((TDesC)KSourceFileErrorName);
        return KErrGeneral;
    }

    if ( aItem.GetNextString(tmp) == KErrNone )
    {
        map = FALSE;
    }
    HBufC8* buffer = ReadFileL(SrcFile);
    CleanupStack::PushL(buffer);

    TInt err;
    TRAP(err, iDoc = parser.ParseL(buffer->Des()));

    if(map && err == KXmlEngErrParsing)
    {
        iLastError = parser.GetLastParsingError();
    }
    else
    {
        iLastError = err;
    }
    TestModuleIf().Printf( infoNum++,KTEST_NAME,KEndParsing);
    iLog->Log((TDesC)KEndParsing);

    CleanupStack::PopAndDestroy( buffer );
    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::LookupNamespaceByPrefixTestL
// lookup namespace in node
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::LookupNamespaceByPrefixTestL( CStifItemParser& aItem )
{
    TPtrC pDoc;
    aItem.GetNextString(pDoc);

    _LIT8(pref, "sip");
    _LIT8(uri, "http://schemas.live.com/mws/2005/08/messaging");

    iDoc = parser.ParseFileL( pDoc );
    RXmlEngNodeList<TXmlEngElement> aList;
    iDoc.DocumentElement().FirstChild().NextSibling().LastChild().AsElement().GetChildElements(aList);
    TXmlEngNamespace found;
    TXmlEngElement elem;
    for(TInt i = 0; i < aList.Count(); i++)
    {
        elem = aList.Next();
        found = elem.LookupNamespaceByPrefixL(pref);
        if(found.NotNull()) break;
    }

    TPtrC8 testPtr = found.Uri();
    return found.Uri().Compare(uri);
}

// -----------------------------------------------------------------------------
// CDomBCTester::LookupNamespaceByUriTestL
// lookup namespace in node
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::LookupNamespaceByUriTestL( CStifItemParser& aItem )
{
    TPtrC pDoc;
    aItem.GetNextString(pDoc);

    _LIT8(pref, "sip");
    _LIT8(uri, "http://schemas.live.com/mws/2005/08/messaging");

    iDoc = parser.ParseFileL( pDoc );
    RXmlEngNodeList<TXmlEngElement> aList;
    iDoc.DocumentElement().FirstChild().NextSibling().LastChild().AsElement().GetChildElements(aList);
    TXmlEngNamespace found;
    TXmlEngElement elem;
    for(TInt i = 0; i < aList.Count(); i++)
    {
        elem = aList.Next();
        found = elem.LookupNamespaceByUriL(uri);
        if(found.NotNull()) break;
    }

    TPtrC8 testPtr = found.Uri();
    return found.Prefix().Compare(pref);
}
// -----------------------------------------------------------------------------
// CDomBCTester::LookupNamespaceByPrefixTest2L
// lookup namespace in parent
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::LookupNamespaceByPrefixTest2L( CStifItemParser& aItem )
{
    TPtrC pDoc;
    aItem.GetNextString(pDoc);

    _LIT8(pref, "S");
    _LIT8(uri, "http://www.w3.org/2003/05/soap-envelope");

    iDoc = parser.ParseFileL( pDoc );

    TXmlEngElement elem = iDoc.DocumentElement().FirstChild().NextSibling().LastChild().AsElement();
    TXmlEngNamespace found = elem.LookupNamespaceByPrefixL(pref);

    TPtrC8 testPtr = found.Uri();
    return found.Uri().Compare(uri);
}

// -----------------------------------------------------------------------------
// CDomBCTester::LookupNamespaceByUriTest2L
// lookup namespace in parent
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::LookupNamespaceByUriTest2L( CStifItemParser& aItem )
{
    TPtrC pDoc;
    aItem.GetNextString(pDoc);

    _LIT8(pref, "S");
    _LIT8(uri, "http://www.w3.org/2003/05/soap-envelope");

    iDoc = parser.ParseFileL( pDoc );

    TXmlEngElement elem = iDoc.DocumentElement().FirstChild().NextSibling().LastChild().AsElement();
    TXmlEngNamespace found = elem.LookupNamespaceByUriL(uri);

    TPtrC8 testPtr = found.Uri();
    return found.Prefix().Compare(pref);
}
// -----------------------------------------------------------------------------
// CDomBCTester::RemoveChildrenTestL
// test parse from buffer
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

TInt CDomBCTester::RemoveChildrenTestL( CStifItemParser& aItem)
{
    TPtrC pDoc;
    aItem.GetNextString(pDoc);

    TPtrC pOut;
    aItem.GetNextString( pOut );

    iDoc = parser.ParseFileL( pDoc );
    iDoc.DocumentElement().FirstChild().NextSibling().LastChild().AsElement().RemoveChildren();
    iDoc.SaveL( pOut );

    return KErrNone;

}
// -----------------------------------------------------------------------------
// CDomBCTester::UserDataTestL
// test parse from buffer
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::UserDataTestL( CStifItemParser& aItem )
{
    TPtrC pDoc;
    aItem.GetNextString( pDoc );

    TPtrC pData;
    aItem.GetNextString(pData);

    HBufC8* buffer = ReadFileL(pData);
    CleanupStack::PushL(buffer);

    iDoc = parser.ParseFileL( pDoc );

    CTestUserData* data1 = new(ELeave) CTestUserData();
    CleanupStack::PushL(data1);
    data1->str.Create(buffer->Des());
    iDoc.DocumentElement().AddUserData(data1);

    CTestUserData* data2 = (CTestUserData*)iDoc.DocumentElement().UserData();
    if(buffer->Des().Compare(data2->str))
    {
        return KErrGeneral;
    }
    iDoc.DocumentElement().RemoveUserData();
    if(iDoc.DocumentElement().UserData())
    {
        return KErrGeneral;
    }

    data1->str.Close();
    CleanupStack::PopAndDestroy(data1);

    CleanupStack::PopAndDestroy( buffer );
    return KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::BaseUriTestL
// test base uri
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::BaseUriTestL( CStifItemParser& /*aItem*/)
{
    SetupDocumentL();
    TInt nResult;
    RBuf8 baseuri;
    iElement.LastChild().BaseUriL(baseuri);
    if(baseuri.Compare(KNullDesC8)) nResult = KErrGeneral;
    else nResult = KErrNone;
    baseuri.Close();
    return nResult;
}

// -----------------------------------------------------------------------------
// CDomBCTester::AddXmlIdTestL
// test base uri
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::AddXmlIdTestL( CStifItemParser& aItem)
{
    TPtrC pOut;
    aItem.GetNextString( pOut );

    _LIT8(pName, "ID");
    _LIT8(pValue, "1");
    _LIT8(pName2, "IDD");
    _LIT8(pValue2, "2");

    SetupDocumentL();
    iDoc.DocumentElement().AddXmlIdL(pName , pValue);

    _LIT8(prefix, "pre1");
    _LIT8(uri, "www.test.uri");
    TXmlEngNamespace ns = iDoc.DocumentElement().AddNamespaceDeclarationL(uri(), prefix());
    iDoc.DocumentElement().AddXmlIdL(pName2 , pValue2, ns);
    if (iDoc.FindElementByXmlIdL(pValue).NotNull() )
    {
        iDoc.SaveL( pOut );
        return KErrNone;
    }
    else
    {
        return KErrNotFound;
    }

}

TInt CDomBCTester::DocumentSaveL( CStifItemParser& aItem)
{
    //save document to (file/buffer/stream)
    TPtrC pSaveTo;
    aItem.GetNextString(pSaveTo);

    //input file
    TPtrC pInputFile;
    aItem.GetNextString(pInputFile);

    //output file (for save to file)
    TPtrC pOutputFile;
    aItem.GetNextString(pOutputFile);

    TFileName srcFileName;
    srcFileName.Copy(pInputFile);

    iDoc = parser.ParseFileL(srcFileName);

    TXmlEngSerializationOptions options(0);
    if(!pSaveTo.Compare(SAVE_TO_FILE))
    {
        iDoc.SaveL(pOutputFile, iDoc.DocumentElement(), options);
    }
    else if(!pSaveTo.Compare(SAVE_TO_BUFFER))
    {
        // This tests verifies how binary data can be substituted with client
        // data during the serialization using client specified callback function.
        _LIT8(data, "this is some kind of binary data");
        _LIT8(cid, "123456789@123456789");
        TXmlEngBinaryContainer container = iDoc.CreateBinaryContainerL(cid, data);
        iDoc.DocumentElement().AppendChildL(container);

        CBinaryMirrorHandler* mySer = new(ELeave) CBinaryMirrorHandler;
        CleanupStack::PushL(mySer);
        options.iDataSerializer = mySer;
        RBuf8 buffer;
        TRAPD(err, iDoc.SaveL( buffer, iDoc, options));
        if(err != KErrNone)
        User::Leave(KErrGeneral);

        WriteFileFromBufferL(pOutputFile, buffer);

        CleanupStack::PopAndDestroy(mySer);
        buffer.Close();
    }
    else if(!pSaveTo.Compare(SAVE_TO_STREAM))
    {
        MyOutputStream stream;
        stream.SetFilename(pOutputFile);
        iDoc.SaveL(stream, iDoc.DocumentElement(), options);
    }

    return KErrNone;
}


// -----------------------------------------------------------------------------
// CDomBCTester::TestReplacewith
// 
// 
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::TestReplaceWithL(CStifItemParser& /*aItem*/)
{

 TInt err = KErrNone; 
	_LIT8(KLit1, "asdfds");
	_LIT8(KLit2, "xzcvcv");
	_LIT8(KLit3, "lklklk");
	TBufC8<30> aLocalName(KLit1);
	TBufC8<30> aNamespaceUri(KLit2);
	TBufC8<30> aPrefix(KLit3);
	
	RXmlEngDOMImplementation domImpl;
	domImpl.OpenL(); 
		
	RXmlEngDocument doc;
	doc.OpenL(domImpl);

	TXmlEngElement aElement = doc.CreateElementL(aLocalName, aNamespaceUri, aPrefix);
 	TXmlEngElement bElement = doc.CreateElementL(aNamespaceUri, aLocalName, aPrefix);
	
	//node aElement is replaced with bElement node
	TRAP(err, aElement.ReplaceWithL(bElement));
	User::LeaveIfError(err);
	
	doc.Close();               
	domImpl.Close();
		
	return KErrNone;
	
}


// -----------------------------------------------------------------------------
// CDomBCTester::TestCreateDocumentFragment
// 
// 
// -----------------------------------------------------------------------------
//

TInt CDomBCTester::TestCreateDocumentFragmentL(CStifItemParser& /*aItem*/)
{
	
	TInt err = KErrNone; 
	RXmlEngDOMImplementation domImpl;
	domImpl.OpenL(); 
		
	RXmlEngDocument doc;
	doc.OpenL(domImpl);

	TXmlEngDocumentFragment xmlengDocFragment; 
	
	//Creates a new empty Document Fragment node
	TRAP(err,  xmlengDocFragment = doc.CreateDocumentFragmentL());
	User::LeaveIfError(err);
		
	doc.Close();               
	domImpl.Close();
		

	return KErrNone;
	
	
}



// -----------------------------------------------------------------------------
// CDomBCTester::TestToNumberL
// 
// 
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::TestToNumberL(CStifItemParser& /*aItem*/)
{

    TXmlEngXPathEvaluator eval;

    _LIT8(str1,"number(/test/test1[@attr1='1'])");
    _LIT8(str2,"/test/test1[@attr1='1']");

    RXmlEngXPathResult res1 = eval.EvaluateL(str1,iDoc.DocumentElement());
    RXmlEngXPathResult res2 = eval.EvaluateL(str2,iDoc.DocumentElement());

    _LIT(KNodeToNumber,"Node to number checking error.");
    
    //Converts node to number
    if(res1.AsNumber() != XmlEngXPathUtils::ToNumberL(res2.AsNodeSet()[0]))
    {
    TestModuleIf().Printf( infoNum++,KTEST_NAME, KNodeToNumber);
    iLog->Log((TDesC)KNodeToNumber);
    return KErrGeneral;
    }

    res1.Close();
    res2.Close();
    
    _LIT8(str3,"number(/test/test1)");
     _LIT8(str4,"/test/test1");
     res1 = eval.EvaluateL(str3,iDoc.DocumentElement());
     res2 = eval.EvaluateL(str4,iDoc.DocumentElement());
     
     _LIT(KSetToNumber,"NodeSet to number checking error.");
  
     //Converts nodeset to number
     if(res1.AsNumber() != XmlEngXPathUtils::ToNumberL(res2.AsNodeSet()))
         {
         TestModuleIf().Printf( infoNum++,KTEST_NAME, KSetToNumber);
         iLog->Log((TDesC)KSetToNumber);
         return KErrGeneral;
         }
     
     res1.Close();
     res2.Close();
     
     _LIT8(str5,"number(\"12345.6\")");
     _LIT8(str6,"12345.6");
     res1 = eval.EvaluateL(str5,iDoc.DocumentElement());
  
     _LIT(KStringToNumber,"String to number checking error.");
     
     //Converts a string to a number
     if(res1.AsNumber() != XmlEngXPathUtils::ToNumberL(str6))
         {
         TestModuleIf().Printf( infoNum++,KTEST_NAME, KStringToNumber);
         iLog->Log((TDesC)KStringToNumber);
         return KErrGeneral;
         }
          
     res1.Close();
     
     _LIT(KBoolToNumber,"Boolean to number checking error.");

     //converts bool to number
     if(!(XmlEngXPathUtils::ToNumberL(TRUE) == 1.0 && XmlEngXPathUtils::ToNumberL(FALSE) == 0.0))
         {
         TestModuleIf().Printf( infoNum++,KTEST_NAME, KBoolToNumber);
         iLog->Log((TDesC)KBoolToNumber);
         return KErrGeneral;
         }

     return KErrNone;  

}

// -----------------------------------------------------------------------------
// CDomBCTester::TestToStringL
// 
// 
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::TestToStringL(CStifItemParser& /*aItem*/)
{
	
    TXmlEngXPathEvaluator eval;
    
    _LIT8(str1,"string(/test/test1[@attr1='1'])");
    _LIT8(str2,"/test/test1[@attr1='1']");
    RXmlEngXPathResult res1 = eval.EvaluateL(str1,iDoc.DocumentElement());
    RXmlEngXPathResult res2 = eval.EvaluateL(str2,iDoc.DocumentElement());

    _LIT(KNodeToNumber,"Node to string checking error.");
    RBuf8 tmp;
    res1.AsStringL( tmp );
    CleanupClosePushL( tmp );
    RBuf8 tmp2;
    
    //Converts a node to a string
    XmlEngXPathUtils::ToStringL(res2.AsNodeSet()[0],tmp2);
    CleanupClosePushL( tmp2 );
    
    if(tmp.Compare(tmp2))
        {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KNodeToNumber);
        iLog->Log((TDesC)KNodeToNumber);
        CleanupStack::PopAndDestroy( &tmp2 );
        CleanupStack::PopAndDestroy( &tmp );
        return KErrGeneral;
        }
    
    tmp.Close();
    tmp2.Close();
    res1.Close();
    res2.Close();
    
    _LIT8(str3,"string(/test/test1)");
    _LIT8(str4,"/test/test1");
    res1 = eval.EvaluateL(str3,iDoc.DocumentElement());
    res2 = eval.EvaluateL(str4,iDoc.DocumentElement());
    
    //Converts a nodeset to a string    
    _LIT(KSetToNumber,"NodeSet to string checking error.");
    res1.AsStringL(tmp);
    
        XmlEngXPathUtils::ToStringL(res2.AsNodeSet(),tmp2);
    
    if(tmp.Compare(tmp2))
        {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KSetToNumber);
        iLog->Log((TDesC)KSetToNumber);
        CleanupStack::PopAndDestroy( &tmp2 );
        CleanupStack::PopAndDestroy( &tmp );
        return KErrGeneral;
        }
    
    tmp.Close();
    tmp2.Close();
    res1.Close();
    res2.Close();
    
    _LIT8(str5,"string(12345.6)");
    res1 = eval.EvaluateL(str5,iDoc.DocumentElement());
    
    _LIT(KStringToNumber,"Number to string checking error.");
    res1.AsStringL(tmp);
    
    //Converts a number to a string
    XmlEngXPathUtils::ToStringL((TReal)12345.6,tmp2);
    
    if(tmp.Compare(tmp2))
        {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KStringToNumber);
        iLog->Log((TDesC)KStringToNumber);
        CleanupStack::PopAndDestroy( &tmp2 );
        CleanupStack::PopAndDestroy( &tmp );
        return KErrGeneral;
        }
    res1.Close();
    tmp2.Close();
    CleanupStack::PopAndDestroy( &tmp2 );
    tmp.Close();
    
    //Converts a bool to a string
     XmlEngXPathUtils::ToStringL(TRUE,tmp);
    _LIT(KBoolToNumber,"Boolean checking error.");
    if(tmp.Compare(_L8("true")))
        {
        CleanupStack::PopAndDestroy( &tmp );
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KBoolToNumber);
        iLog->Log((TDesC)KBoolToNumber);
        return KErrGeneral;
        }
    
    CleanupStack::PopAndDestroy(&tmp);
    return KErrNone;  
	
}


// -----------------------------------------------------------------------------
// CDomBCTester::TestToBooleanL
// 
// 
// -----------------------------------------------------------------------------
//

TInt CDomBCTester::TestToBooleanL(CStifItemParser& /*aItem*/)

{
    TXmlEngXPathEvaluator eval;
 
    _LIT8(str1,"boolean(/test/test1[@attr1='1'])");
    _LIT8(str2,"/test/test1[@attr1='1']");
 
    RXmlEngXPathResult res1 = eval.EvaluateL(str1,iDoc.DocumentElement());
    RXmlEngXPathResult res2 = eval.EvaluateL(str2,iDoc.DocumentElement());
 
    _LIT(KNodeToNumber,"Node to bool checking error.");

    //Converts a node to bool
    if(!(res1.AsBoolean() && XmlEngXPathUtils::ToBoolean(res2.AsNodeSet()[0])))
     {
     TestModuleIf().Printf( infoNum++,KTEST_NAME, KNodeToNumber);
     iLog->Log((TDesC)KNodeToNumber);
     return KErrGeneral;
     }
 
    res1.Close();
    res2.Close();

    _LIT8(str3,"boolean(/test/test4)");
    _LIT8(str4,"/test/test4");
    res1 = eval.EvaluateL(str3,iDoc.DocumentElement());
    res2 = eval.EvaluateL(str4,iDoc.DocumentElement());
 
    _LIT(KSetToNumber,"NodeSet to bool checking error.");
 
     //Converts nodeset to bool
     if(!(!res1.AsBoolean() && !XmlEngXPathUtils::ToBoolean(res2.AsNodeSet())))
     {
     TestModuleIf().Printf( infoNum++,KTEST_NAME, KSetToNumber);
     iLog->Log((TDesC)KSetToNumber);
     return KErrGeneral;
     }
 
     res1.Close();
     res2.Close();
 
     _LIT8(str5,"boolean(12345.6)");
     res1 = eval.EvaluateL(str5,iDoc.DocumentElement());
 
     _LIT(KStringToNumber,"Number to bool checking error.");
 
     //Converts a number to bool
     if(!(res1.AsBoolean() && XmlEngXPathUtils::ToBoolean((TReal)12345.6)))
     {
     TestModuleIf().Printf( infoNum++,KTEST_NAME, KStringToNumber);
     iLog->Log((TDesC)KStringToNumber);
     return KErrGeneral;
     }
      
     res1.Close();
 
     _LIT(KBoolToNumber,"String to boolean checking error.");
 
     //Converts string to bool
     if(XmlEngXPathUtils::ToBoolean(KNullDesC8))
     {
     TestModuleIf().Printf( infoNum++,KTEST_NAME, KBoolToNumber);
     iLog->Log((TDesC)KBoolToNumber);
     return KErrGeneral;
     }

    return KErrNone;    
    

}


// -----------------------------------------------------------------------------
// CDomBCTester::TestExtensionFunctionL
// 
// 
// -----------------------------------------------------------------------------
//
TInt CDomBCTester::TestExtensionFunctionL(CStifItemParser& /*aItem*/)
{

	_LIT8(KDataContext,"<doc><test>10</test><test/><test/><test2>data</test2></doc>");
	XPathDate myFunct;
	
    TXmlEngExtensionFunctionDescriptor tExt;
	tExt.iFunc = &myFunct;
	tExt.iName = "MyFunction";
	

	//Registers an extension function at the global scope
    TRAPD(err,XmlEngXPathConfiguration::AddExtensionFunctionL(tExt));
	User::LeaveIfError(err);
    
	_LIT(KTypeError,"Testing AddExtensionFunction");
    if(!(XmlEngXPathConfiguration::IsFunctionSupportedL(_L8("MyFunction"),KNullDesC8)))
	
	 {
		 TestModuleIf().Printf( infoNum++,KTEST_NAME, KTypeError);
		iLog->Log((TDesC)KTypeError);
		return KErrGeneral;
	 }

	RXmlEngDocument contextDoc = parser.ParseL(TPtrC8(KDataContext)); 

    TXmlEngXPathEvaluator eval;

	TRAP(err,eval.EvaluateL(_L8("MyFunction(10)"),contextDoc,NULL));
	User::LeaveIfError(err);
    contextDoc.Close();
	
	//Deregisters an extension function
    XmlEngXPathConfiguration::RemoveExtensionFunction(tExt);

	_LIT(KTypeError1,"Testing RemoveExtensionFunction");
    if(XmlEngXPathConfiguration::IsFunctionSupportedL(_L8("MyFunction"),KNullDesC8))
		
	 {
		 TestModuleIf().Printf( infoNum++,KTEST_NAME, KTypeError1);
		iLog->Log((TDesC)KTypeError);
		return KErrGeneral;
	 }

	return KErrNone;


}


// -----------------------------------------------------------------------------
// CDomBCTester::TestExtensionVectorFunctionL()
// 
// 
// -----------------------------------------------------------------------------
//

TInt CDomBCTester::TestExtensionVectorFunctionL(CStifItemParser& /*aItem*/)
{
	XPathDate myDate;
	XPathDate2 myDate2;
	XPathDate3 myDate3;
	
	TXmlEngExtensionFunctionDescriptor extFunc;
	extFunc.iFunc = &myDate;
	extFunc.iName = "MyDate";
	
	TXmlEngExtensionFunctionDescriptor extFunc2;
	extFunc2.iFunc = &myDate2;
	extFunc2.iName = "MyDate2";
	
	TXmlEngExtensionFunctionDescriptor extFunc3;
	extFunc3.iFunc = &myDate3;
	extFunc3.iName = "MyDate3";
	
	RArray<TXmlEngExtensionFunctionDescriptor> extVect;
	extVect.Append(extFunc);
    extVect.Append(extFunc2);
    extVect.Append(extFunc3);


	_LIT8(KDataContext, "<doc><test>10</test><test/><test/><test2>data</test2></doc>");
	
	//Registers a set of extension functions at the global scope.
    TRAPD(err,XmlEngXPathConfiguration::AddExtensionFunctionVectorL(extVect,extVect.Count()));
	User::LeaveIfError(err);
    
	_LIT(KTypeError,"Testing ExtensionVectorFunction");
    if(!XmlEngXPathConfiguration::IsFunctionSupportedL(_L8("MyDate"),KNullDesC8))
        {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KTypeError);
		iLog->Log((TDesC)KTypeError);
		return KErrGeneral;
        }
	
	RXmlEngDocument contextDoc = parser.ParseL(TPtrC8(KDataContext)); 
	
	TXmlEngXPathEvaluator eval;
    RXmlEngXPathResult result = eval.EvaluateL(_L8("MyDate2(/doc/test)"), contextDoc, NULL);
	
	
    if(result.Type() != RXmlEngXPathResult::ENodeset)
        {
        TestModuleIf().Printf( infoNum++,KTEST_NAME,KTypeError);
		iLog->Log((TDesC)KTypeError);
		return KErrGeneral;
        }

	 RXmlEngNodeSet set = result.AsNodeSet();

    if(set.Length() != 3)
        {
        TestModuleIf().Printf( infoNum++,KTEST_NAME,KTypeError);
		iLog->Log((TDesC)KTypeError);
		return KErrGeneral;
        }
    result.Free();
    
	result = eval.EvaluateL(_L8("MyDate2(10)"), contextDoc, NULL);
	if(result.Type() != RXmlEngXPathResult::ENumber)
        {
        TestModuleIf().Printf( infoNum++,KTEST_NAME, KTypeError);
		iLog->Log((TDesC)KTypeError);
		return KErrGeneral;
        }

	if(result.AsNumber() != 10)
        {
        TestModuleIf().Printf( infoNum++,KTEST_NAME,KTypeError);
		iLog->Log((TDesC)KTypeError);
		return KErrGeneral;;
        }
    result.Free();
    
	
    
    result = eval.EvaluateL(_L8("MyDate3(3,/doc/test)"), contextDoc, NULL);
	if(result.Type() != RXmlEngXPathResult::ENumber)
        {
        TestModuleIf().Printf( infoNum++,KTEST_NAME,KTypeError);
		iLog->Log((TDesC)KTypeError);
		return KErrGeneral;;
        }

	if(result.AsNumber() != 6)
        {
        TestModuleIf().Printf( infoNum++,KTEST_NAME,KTypeError);
		iLog->Log((TDesC)KTypeError);
		return KErrGeneral;;
        }
    result.Free();
    
    if(!XmlEngXPathConfiguration::IsFunctionSupportedL(_L8("MyDate"),KNullDesC8))
        {
        TestModuleIf().Printf( infoNum++,KTEST_NAME,KTypeError);
		iLog->Log((TDesC)KTypeError);
		return KErrGeneral;;
        }
     
	//Deregisters a set of extension functions
    XmlEngXPathConfiguration::RemoveExtensionFunctionVector(extVect,extVect.Count());
		
    if(XmlEngXPathConfiguration::IsFunctionSupportedL(_L8("MyDate2"),KNullDesC8))
        {
        TestModuleIf().Printf(infoNum++,KTEST_NAME,KTypeError);
		iLog->Log((TDesC)KTypeError);
		return KErrGeneral;
        }
        
    if(XmlEngXPathConfiguration::IsFunctionSupportedL(_L8("MyDate"),KNullDesC8))
        {
        TestModuleIf().Printf(infoNum++,KTEST_NAME,KTypeError);
		iLog->Log((TDesC)KTypeError);
		return KErrGeneral;
        }

    contextDoc.Close();
    extVect.Close();
	return KErrNone;
     
}

// -----------------------------------------------------------------------------
// CDomBCTester::TestAddNativeExtensionVectorFunctionL()
// 
// 
// -----------------------------------------------------------------------------
//

TInt CDomBCTester::TestAddNativeExtensionVectorFunctionL(CStifItemParser& /*aItem*/)
{
	XPathDate myDate;
	XPathDate2 myDate2;
	XPathDate3 myDate3;
	
	TXmlEngExtensionFunctionDescriptor extFunc;
	extFunc.iFunc = &myDate;
	extFunc.iName = "MyDate";
	
	TXmlEngExtensionFunctionDescriptor extFunc2;
	extFunc2.iFunc = &myDate2;
	extFunc2.iName = "MyDate2";
	
	TXmlEngExtensionFunctionDescriptor extFunc3;
	extFunc3.iFunc = &myDate3;
	extFunc3.iName = "MyDate3";
	
	RArray<TXmlEngExtensionFunctionDescriptor> extVect;
	extVect.Append(extFunc);
    extVect.Append(extFunc2);
    extVect.Append(extFunc3);

	
	// Registers a set of native extension function at the global scope
	TRAPD(err,XmlEngXPathConfiguration::AddNativeExtensionFunctionVectorL(extVect,extVect.Count()));
	User::LeaveIfError(err);
	
	_LIT(KTypeError,"Testing AddNativeExtensionFunctionVector");
    if(!XmlEngXPathConfiguration::IsFunctionSupportedL(_L8("MyDate"),KNullDesC8))
        {
		TestModuleIf().Printf( infoNum++,KTEST_NAME, KTypeError);
		iLog->Log((TDesC)KTypeError);
		return KErrGeneral;
        }
      
 
	return KErrNone;

}

// -----------------------------------------------------------------------------
// CDomBCTester::TestResetExtensionFunctionsL()
// 
// 
// -----------------------------------------------------------------------------
//

TInt CDomBCTester::TestResetExtensionFunctionsL(CStifItemParser& /*aItem*/)
{
	XPathDate myDate;
	XPathDate2 myDate2;
	XPathDate3 myDate3;
	
	TXmlEngExtensionFunctionDescriptor extFunc;
	extFunc.iFunc = &myDate;
	extFunc.iName = "MyDate";
	
	TXmlEngExtensionFunctionDescriptor extFunc2;
	extFunc2.iFunc = &myDate2;
	extFunc2.iName = "MyDate2";
	
	TXmlEngExtensionFunctionDescriptor extFunc3;
	extFunc3.iFunc = &myDate3;
	extFunc3.iName = "MyDate3";
	
	RArray<TXmlEngExtensionFunctionDescriptor> extVect;
	extVect.Append(extFunc);
    extVect.Append(extFunc2);
    extVect.Append(extFunc3);



	TRAPD(err,XmlEngXPathConfiguration::AddExtensionFunctionVectorL(extVect,extVect.Count()));
	User::LeaveIfError(err);

	//Disables support of any previously registered extension functions
	TRAP(err, XmlEngXPathConfiguration::ResetExtensionFunctionsL());
	User::LeaveIfError(err);

	_LIT(KTypeError,"Testing ResetExtensionFunctionsL");
	
    if(XmlEngXPathConfiguration::IsFunctionSupportedL(_L8("MyDate"),KNullDesC8))
        {
			TestModuleIf().Printf( infoNum++,KTEST_NAME, KTypeError);
			iLog->Log((TDesC)KTypeError);
			return KErrGeneral;
        }
	return KErrNone;
      
}
// -----------------------------------------------------------------------------
// CDomBCTester::TestRenameElementL()
// 
// 
// -----------------------------------------------------------------------------
//

TInt CDomBCTester::TestRenameElementL(CStifItemParser& /*aItem*/)
{
	_LIT8(localName,"testName");
    _LIT8(namespaceUri,"testURI");
    _LIT8(prefix,"testPref");
    _LIT8(localName1,"testName1");
    _LIT8(namespaceUri1,"testURI1");
    _LIT8(prefix1,"testPref1"); 
    
    iDoc.OpenL(DOM_impl);
	TXmlEngElement elementNode = iDoc.CreateElementL(localName, namespaceUri, prefix);

	//Renames the element with the given name, namespace URI, and namespace prefix.
	TRAPD(err,elementNode.RenameElementL(localName1,namespaceUri1,prefix1));
	User::LeaveIfError(err);

	_LIT(KTypeError,"Renaming the node Failed");

	if( elementNode.Name().Compare(localName1) || elementNode.NamespaceUri().Compare(namespaceUri1) || elementNode.Prefix().Compare(prefix1))
    {
		TestModuleIf().Printf( infoNum++,KTEST_NAME, KTypeError);
		iLog->Log((TDesC)KTypeError);
		return KErrGeneral;
	}
	 iDoc.Close();
	return KErrNone;

}

TInt CDomBCTester::TestSetDataSerializerL(CStifItemParser& /*aItem*/)
{
    RXmlEngDOMImplementation domImpl;
    domImpl.OpenL(); 
    RXmlEngDocument doc;
    doc.OpenL(domImpl);
    _LIT8(name,"document");
    
    TPtrC8 data(_L8("this is some kind of binary data") );
    doc.CreateDocumentElementL(name);
    
    TXmlEngBinaryContainer container = doc.CreateBinaryContainerL(data,_L8("123456789@123456789"));
    doc.DocumentElement().AppendChildL(container); 
    
    TXmlEngSerializationOptions options(0);
    TInt err(0);
    
    CBinaryMirrorHandler* mySer = new(ELeave) CBinaryMirrorHandler;
    CleanupStack::PushL(mySer);
    options.SetDataSerializer(mySer);
    
    TTestNodeFilter dummyFilter;
    options.SetNodeFilter(&dummyFilter);
    RBuf8 buffer2;
    
    TRAP(err, doc.SaveL( buffer2, doc, options));
    User::LeaveIfError(err);
    
    CleanupStack::PopAndDestroy(1); // mySer
    buffer2.Close();
    doc.Close();
    domImpl.Close();
    return KErrNone;

}
    

// End of file
