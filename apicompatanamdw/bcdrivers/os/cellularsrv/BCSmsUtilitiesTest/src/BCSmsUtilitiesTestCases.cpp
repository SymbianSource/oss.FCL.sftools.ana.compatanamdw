/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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

/* Changed by Vaibhav - 13Aug07 for Removing CodeScanner Warnings - High/medium */

// INCLUDE FILES
#include <e32math.h>
#include "BCSmsUtilitiesTest.h"
#include <gsmunmspacemobmsg.h>
#include <S32file.h>
#include <e32cons.h>
#include <txtrich.h>

#include <gsmuelem.h>
#define KTimeStampSize 32
_LIT(KTestNativeChar, "SmsGsmUtilities");
_LIT8(KTestNativeChar8, "SmsGsmUtilities");
_LIT8(KTestInfo8, "ABCDEFGH");
_LIT8(KTestCommandData8, "CommandData");
_LIT(KTestBuffer1, "ABCDEFGHIJKLMNOPQRSTUVWX");

// ============================= LOCAL FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// Create_Console
// Creates a new Console Window
// -----------------------------------------------------------------------------
LOCAL_C CConsoleBase* Create_ConsoleL(const TDesC& title)
	{
    CConsoleBase* console;
    
    console = Console::NewL(title,TSize( KConsFullScreen, KConsFullScreen));
	CleanupStack::PushL( console );
	return 	console;
	}

// -----------------------------------------------------------------------------
// Print
// Prints the result onto screen
// -----------------------------------------------------------------------------
LOCAL_C void Print(CConsoleBase* base, TInt result, const TDesC& text)
	{
	base->Printf(text);
	if( result == KErrNone)
		{
		base->Printf(_L(" passed\n"));
		}
	else
		{
		base->Printf(_L("::Error code %d\n"), result);
		}
	}
	
// -----------------------------------------------------------------------------
// Remove_Console
// Deletes a new Console Window
// -----------------------------------------------------------------------------
LOCAL_C void Remove_Console(CConsoleBase* base)
	{
	//base->Getch();
	CleanupStack::PopAndDestroy(base);
	}
	
void Check(TInt aValue, TInt aExpected )
	{
	if(aValue != aExpected)
		{
		RDebug::Print(_L("*** Expected value: %d, got: %d\r\n"), aExpected, aValue);
		__ASSERT_ALWAYS(aValue != aExpected, User::Panic(_L("Active object Error"), 1));
		}
	}

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CBCSmsUtilitiesTest::Case
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
const TCaseInfo CBCSmsUtilitiesTest::Case ( 
    const TInt aCaseNumber ) const 
     {


     static TCaseInfoInternal const KCases[] =
        {
        // To add new test cases, add new items to this array
        ENTRY( "CSmsAlphabetConverter", CBCSmsUtilitiesTest::TestSmsAlphabetConverterL ),
        ENTRY( "CSmsBuffer", CBCSmsUtilitiesTest::TestSmsBufferL ),
        ENTRY( "CSmsCommand", CBCSmsUtilitiesTest::TestSmsCommandL ),
        ENTRY( "CSmsDeliver", CBCSmsUtilitiesTest::TestSmsDeliverL ),
        ENTRY( "CSmsDeliverReport", CBCSmsUtilitiesTest::TestSmsDeliverReportL ),
        ENTRY( "CSmsEditorBuffer", CBCSmsUtilitiesTest::TestSmsEditorBufferL ),
        ENTRY( "CSmsInformationElement", CBCSmsUtilitiesTest::TestSmsInformationElementL ),
        ENTRY( "CSmsMessage", CBCSmsUtilitiesTest::TestSmsMessageL ),
        ENTRY( "CSmsPDU", CBCSmsUtilitiesTest::TestSmsPDUL ),
        ENTRY( "CSmsStatusReport", CBCSmsUtilitiesTest::TestSmsStatusReportL ),
        ENTRY( "CSmsSubmit", CBCSmsUtilitiesTest::TestSmsSubmitL ),
        ENTRY( "CSmsSubmitReport", CBCSmsUtilitiesTest::TestSmsSubmitReportL ),
        ENTRY( "CSmsUserData", CBCSmsUtilitiesTest::TestSmsUserDataL ),
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

// -----------------------------------------------------------------------------
// TestGetAlphabet
// Gets the coding scheme alphabet
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetAlphabet( CStifLogger* aLog, CSmsAlphabetConverter& aAlphabetConv)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling Alphabet()"));
	TInt result = KErrNone;
	
	//inline TSmsDataCodingScheme::TSmsAlphabet CSmsAlphabetConverter::Alphabet() const
	TSmsDataCodingScheme::TSmsAlphabet alphabet = aAlphabetConv.Alphabet();
	
	if( alphabet == TSmsDataCodingScheme::ESmsAlphabet8Bit )
		{
		aLog->Log(_L("Alphabet() Completed"));
		aLog->Log(_L("Alphabet fetched"));
		aLog->Log(_L("Get alphabet == PASS"));
		}
	else
		{
		result = KErrGeneral;
		aLog->Log(_L("Get alphabet == FAIL"));
		}
		
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestConvertFromNative
// Converts from the native character set to 
// unpacked user data elements of the desired character set.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestConvertFromNative( CStifLogger* aLog, CSmsAlphabetConverter& aAlphabetConv)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling ConvertFromNativeL()"));
	
	TBufC<24> nativeChar(KTestNativeChar);
	TBufC8<24> UDElements(KTestNativeChar8);
	//IMPORT_C TPtrC8 ConvertFromNativeL(const TDesC& aNativeCharacters);
	TPtrC8 convChar;
	TRAPD( result, convChar.Set(aAlphabetConv.ConvertFromNativeL(nativeChar))) ;

	TPtrC8 UDElementsPtr(UDElements);
	if(convChar.Compare(UDElementsPtr))
		{
		result = KErrGeneral;
		aLog->Log(_L("Convert from native == FAIL"));	
		}
	else
		{
		aLog->Log(_L("ConvertFromNativeL() Completed"));
		aLog->Log(_L("Conversion successfully performoded"));
		aLog->Log(_L("Convert from native == PASS"));
		}

	return result;
	}

LOCAL_C TInt TestConvertFromNative2L( CStifLogger* aLog, CSmsAlphabetConverter& aAlphabetConv)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling ConvertFromNative2L()"));
	
	TBufC<24> nativeChar(KTestNativeChar);
	TBufC8<24> UDElements(KTestNativeChar8);
	
	TInt numUnconvertibleChars;
	TInt numDowngradedChars;
	TPtrC8 convChar;
	TRAPD( result, convChar.Set(aAlphabetConv.ConvertFromNativeL(nativeChar,ESmsEncodingNone,numUnconvertibleChars,numDowngradedChars ))) ;

	TPtrC8 UDElementsPtr(UDElements);
	if(convChar.Compare(UDElementsPtr))
		{
		result = KErrGeneral;
		aLog->Log(_L("Convert from native2 == FAIL"));	
		}
	else
		{
		aLog->Log(_L("ConvertFromNative2L() Completed"));
		aLog->Log(_L("Conversion successfully performoded"));
		aLog->Log(_L("Convert from native2 == PASS"));
		}

	return result;
	}	
// -----------------------------------------------------------------------------
// TestConvertToNative
// Converts the user data elements of the specified character set to 
// the native character set.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestConvertToNative( CStifLogger* aLog, CSmsAlphabetConverter& aAlphabetConv)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling ConvertToNativeL()"));
	
	TBufC<24> nativeChar(KTestNativeChar);
	TBufC8<24> UDElements(KTestNativeChar8);
	//IMPORT_C TPtrC ConvertToNativeL(const TDesC8& aUDElements);
	TPtrC convChar;
	TRAPD( result, convChar.Set(aAlphabetConv.ConvertToNativeL(UDElements)));
	
	TBufC<24> nativeCharPtr(nativeChar);
	if(convChar.Compare(nativeCharPtr))
		{
		result = KErrGeneral;
		aLog->Log(_L("Convert To native == FAIL"));	
		}
	else
		{
		aLog->Log(_L("ConvertToNativeL() Completed"));
		aLog->Log(_L("Conversion successfully performoded"));
		aLog->Log(_L("Convert To native == PASS"));
		}

	return result;
	}

LOCAL_C TInt TestConvertToNative2L( CStifLogger* aLog, CSmsAlphabetConverter& aAlphabetConv)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling ConvertToNative2L()"));
	
	TBufC<24> nativeChar(KTestNativeChar);
	TBufC8<24> UDElements(KTestNativeChar8);
	
	TPtrC convChar;
	TRAPD( result, convChar.Set(aAlphabetConv.ConvertToNativeL(UDElements,ESmsEncodingNone )));
	
	TBufC<24> nativeCharPtr(nativeChar);
	if(convChar.Compare(nativeCharPtr))
		{
		result = KErrGeneral;
		aLog->Log(_L("Convert To native2 == FAIL"));	
		}
	else
		{
		aLog->Log(_L("ConvertToNative2L() Completed"));
		aLog->Log(_L("Conversion successfully performoded"));
		aLog->Log(_L("Convert To native2 == PASS"));
		}

	return result;
	}	
// -----------------------------------------------------------------------------
// TestResetUnconvertedNativeCharacters
// Resets the unconverted native character buffer
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestResetUnconvertedNativeCharacters( CStifLogger* aLog, CSmsAlphabetConverter& aAlphabetConv)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling ResetUnconvertedNativeCharacters()"));

	TInt result = KErrNone;
	
	//inline void ResetUnconvertedNativeCharacters();
	aAlphabetConv.ResetUnconvertedNativeCharacters();
	
	aLog->Log(_L("ResetUnconvertedNativeCharacters() Completed"));
	aLog->Log(_L("Reset performed successfully"));
	aLog->Log(_L("Reset unconverted native characters == PASS"));

	return result;
	}
	
// -----------------------------------------------------------------------------
// TestResetUnconvertedUDElements
// Resets the unconverted user data elements buffer
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestResetUnconvertedUDElements( CStifLogger* aLog, CSmsAlphabetConverter& aAlphabetConv)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling ResetUnconvertedUDElements()"));
	TInt result = KErrNone;
	
	//inline void ResetUnconvertedUDElements();
	aAlphabetConv.ResetUnconvertedUDElements();

	aLog->Log(_L("ResetUnconvertedUDElements() Completed"));
	aLog->Log(_L("Reset performed successfully"));
	aLog->Log(_L("Reset unconverted UD Elements == PASS"));

	return result;
	}
	
// -----------------------------------------------------------------------------
// TestUnconvertedNativeCharacters
// Gets the unconverted native characters
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestUnconvertedNativeCharacters( CStifLogger* aLog, CSmsAlphabetConverter& aAlphabetConv)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling UnconvertedNativeCharacters()"));
	TInt result = KErrNone;
	
	//inline TPtrC UnconvertedNativeCharacters();
	TPtrC nativeCharPtr( aAlphabetConv.UnconvertedNativeCharacters() );
	
	aLog->Log(_L("UnconvertedNativeCharacters() Completed"));
	if(nativeCharPtr != KNullDesC )
		aLog->Log(_L("Result data:Characters: %s"), nativeCharPtr.Ptr());
	else
		aLog->Log(_L("Result data:Characters: NULL "));
	aLog->Log(_L("Get unconverted native characters == PASS"));
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestUnconvertedUDElements
// Gets the unconverted user data elements
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestUnconvertedUDElements( CStifLogger* aLog, CSmsAlphabetConverter& aAlphabetConv)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling UnconvertedUDElements()"));
	TInt result = KErrNone;
	
	//inline TPtrC8 UnconvertedUDElements();
	TPtrC8 UDElementsPtr( aAlphabetConv.UnconvertedUDElements());
	
	aLog->Log(_L("UnconvertedUDElements() Completed"));
	if( UDElementsPtr!= KNullDesC8 )
		aLog->Log(_L("Result data:Characters: %s"), UDElementsPtr.Ptr());
	else
		aLog->Log(_L("Result data:Characters: NULL"));
	aLog->Log(_L("Get unconverted UD Elements == PASS"));
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestDelete
// Deletes data from the buffer
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestDelete( CStifLogger* aLog, CSmsBuffer& aBuffer)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling DeleteL()"));
	
	TInt position = 2;
	TInt length = 2;
	//IMPORT_C void DeleteL(TInt aPos,TInt aLength);
	TRAPD( result, aBuffer.DeleteL( position, length));
	
	if( result == KErrNone )
		{
		aLog->Log(_L("DeleteL() Completed"));
		aLog->Log(_L("Data successfully deleted"));
		aLog->Log(_L("Delete == PASS"));
		}
	else
		aLog->Log(_L("Delete == FAIL"));
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestReset
// Resets the buffer
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestReset( CStifLogger* aLog, CSmsBuffer& aBuffer)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling Reset()"));
	TInt result = KErrNone;
	
	//IMPORT_C void Reset();
	aBuffer.Reset();

	aLog->Log(_L("Reset() Completed"));
	aLog->Log(_L("Data successfully reseted"));
	aLog->Log(_L("Reset == PASS"));
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestExtract
// Extracts buffer data to a descriptor
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestExtract( CStifLogger* aLog, CSmsBuffer& aBuffer)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling Extract()"));
	TInt result = KErrNone;
	
	TBuf<24> buffer;
	TInt position = 2;
	TInt length = 6;
	//IMPORT_C void Extract(TDes& aBuf,TInt aPos,TInt aLength) const;
	aBuffer.Extract(buffer, position, length);
	
	aLog->Log(_L("Extract() Completed"));
	aLog->Log(_L("Data successfully extracted"));
	aLog->Log(_L("Extract == PASS"));
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestInsert
// Inserts data into the buffer
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestInsert( CStifLogger* aLog, CSmsBuffer& aBuffer)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling InsertL()"));
	
	TBufC<24> buffer(KTestBuffer1);
	TInt position = 0;
	//IMPORT_C void InsertL(TInt aPos,const TDesC& aBuf);
	TRAPD( result, aBuffer.InsertL(position, buffer));
	
	if( result == KErrNone )
		{
		aLog->Log(_L("InsertL() Completed"));
		aLog->Log(_L("Data successfully Inserted"));
		aLog->Log(_L("InsertL == PASS"));
		}
	else
		aLog->Log(_L("InsertL == FAIL"));
	
	return result;
	}
	 
// -----------------------------------------------------------------------------
// TestGetLength
// Gets the amount of space currently used in the buffer.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetLength( CStifLogger* aLog, CSmsBuffer& aBuffer)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling Length()"));
	TInt result = KErrNone;
		
	//IMPORT_C TInt Length() const;
	TInt length = aBuffer.Length();
	
	if(length == 22) 
		{
		aLog->Log(_L("Length() Completed"));
		aLog->Log(_L("Result data: Length: %d"), length);
		aLog->Log(_L("Length == PASS"));	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log(_L("Length == FAIL"));
		}
		
	return result;
	}
	 
// -----------------------------------------------------------------------------
// TestExternalize
// Externalises the object.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestExternalizeL( CStifLogger* aLog, CSmsBuffer& aBuffer)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling ExternalizeL()"));
	
	RFs session;
    User::LeaveIfError(session.Connect());
	TBufC<64> storename = _L("C:\\SMSGSMUtilities_CSmsBuffer");
	RFileWriteStream write;
	
	write.Create(session, storename, EFileWrite);
	TInt err = write.Open(session, storename, EFileWrite);
	
	//IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	TRAPD( result, aBuffer.ExternalizeL( write ));
	
	write.CommitL();
	write.Close();
	
	session.Close();
	if( result == KErrNone )
		{
		aLog->Log(_L("ExternalizeL() Completed"));
		aLog->Log(_L("Buffer successfully externalized"));
		aLog->Log(_L("ExternalizeL == PASS"));
		}
	else
		aLog->Log(_L("ExternalizeL == FAIL"));
	
	return result;
	}
	 
// -----------------------------------------------------------------------------
// TestInternalize
// Internalises the object.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestInternalizeL( CStifLogger* aLog, CSmsBuffer& aBuffer)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling InternalizeL()"));
	
	RFs session;
    User::LeaveIfError(session.Connect());
	TBufC<64> storename = _L("C:\\SMSGSMUtilities_CSmsBuffer");
    RFileReadStream read;
		
	TInt erro = read.Open(session, storename, EFileRead);
	
	//IMPORT_C void InternalizeL(RReadStream &aStream)
	TRAPD( result, aBuffer.InternalizeL( read ));
	
	read.Close();
	
	//now delete the store
	TInt err = session.Delete(storename);
	if(err != KErrNone) 
		{
		RDebug::Print(_L("Error %d deleting \"%S\" file.\n"), err, &storename);
		}

	session.Close();
	if( result == KErrNone )	
		{
		aLog->Log(_L("InternalizeL() Completed"));
		aLog->Log(_L("Buffer successfully internalized"));
		aLog->Log(_L("InternalizeL == PASS"));
		}
	else
		aLog->Log(_L("InternalizeL == FAIL"));
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestAddInformationElement
// Adds an Information Element.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestAddInformationElement( CStifLogger* aLog, CSmsCommand& aCommand)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling AddInformationElementL()"));
	
	CSmsInformationElement::TSmsInformationElementIdentifier identifier = CSmsInformationElement::ESmsIEIConcatenatedShortMessages8BitReference;
	TBufC8<24> information(KTestInfo8);
	//IMPORT_C void AddInformationElementL(CSmsInformationElement::TSmsInformationElementIdentifier aIdentifier, TDesC8& aData);
	TRAPD( result, aCommand.AddInformationElementL( identifier, information));
	
	if( result ==KErrNone )
		{
		aLog->Log(_L("AddInformationElementL() completed"));
		aLog->Log(_L("Information element successfully added"));
		aLog->Log(_L("Add information element == PASS"));
		}
	else
		aLog->Log(_L("Add information element == FAIL"));
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestRemoveInformationElement
// Removes an Information Element
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestRemoveInformationElement( CStifLogger* aLog, CSmsCommand& aCommand)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling RemoveInformationElement()"));
	TInt result = KErrNone;
		
	TInt index = 0;
	//IMPORT_C void RemoveInformationElement(TInt aIndex);
	aCommand.RemoveInformationElement( index );
	
	aLog->Log(_L("RemoveInformationElement() completed"));
	aLog->Log(_L("Information element successfully removed"));
	aLog->Log(_L("Remove information element == PASS"));
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestMaxCommandDataLength
// Gets the Maximum Data Length of the Command
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestMaxCommandDataLength( CStifLogger* aLog, CSmsCommand& aCommand)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling MaxCommandDataLength()"));
	TInt result = KErrNone;
		
	//IMPORT_C TInt MaxCommandDataLength() const;
	TInt maxLength = aCommand.MaxCommandDataLength();
	
	aLog->Log(_L("MaxCommandDataLength() completed"));
	aLog->Log(_L("Result data:Max length: %d"),maxLength);
	aLog->Log(_L("Get max command data length == PASS"));
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetCommandData
// Gets the Command Data
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetCommandData( CStifLogger* aLog, CSmsCommand& aCommand)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling CommandData()"));
	TInt result = KErrNone;
	
	//IMPORT_C TPtrC8 CommandData() const;
	TPtrC8 commandPtr = aCommand.CommandData();
	
	if( commandPtr == KTestCommandData8)
		{
		aLog->Log(_L("CommandData() completed"));
		aLog->Log(_L("Result data:Command data: %s"), commandPtr.Ptr());
		aLog->Log(_L("Get command data == PASS"));
		}
	else
		{
		result = KErrGeneral;
		aLog->Log(_L("Get command data == FAIL"));
		}
	return result;
	}
	 
// -----------------------------------------------------------------------------
// TestGetCommandType
// Gets the Command Type
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetCommandType( CStifLogger* aLog, CSmsCommand& aCommand)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling CommandType()"));
	TInt result = KErrNone;
	
	//IMPORT_C TInt CommandType() const;
	TInt commandType = aCommand.CommandType();
	
	if( commandType == TSmsCommandType::ESmsCommandTypeEnableStatusReportRequest)
		{
		aLog->Log(_L("CommandType() completed"));
		aLog->Log(_L("Result data:Command Type: %d"), commandType);
		aLog->Log(_L("Get command Type == PASS"));
		}
	else
		{
		result = KErrGeneral;
		aLog->Log(_L("Get command Type == FAIL"));
		}
	
	return result;
	}
	 
// -----------------------------------------------------------------------------
// TestSetCommandType
// Sets the Command Type
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetCommandType( CStifLogger* aLog, CSmsCommand& aCommand)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetCommandType()"));
	TInt result = KErrNone;
	
	TSmsCommandType::TSmsCommandTypeValue commandType = TSmsCommandType::ESmsCommandTypeEnableStatusReportRequest;
	//IMPORT_C void SetCommandType(TSmsCommandType::TSmsCommandTypeValue aCommandType);
	aCommand.SetCommandType( commandType );
	
	aLog->Log(_L("SetCommandType() completed"));
	aLog->Log(_L("Command type successfully stored"));
	aLog->Log(_L("Set command Type == PASS"));
	return result;
	}
	 

//----------------------------------------------------------------------------
// TestInformationElement
// Gets an Information Element
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestInformationElement( CStifLogger* aLog, CSmsCommand& aCommand)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling InformationElement()"));
	TInt result = KErrNone;
	
	TInt index = 0;
	//IMPORT_C CSmsInformationElement& InformationElement(TInt aIndex) const;
	CSmsInformationElement& element = aCommand.InformationElement(index);	
	
	aLog->Log(_L("InformationElement() completed"));
	aLog->Log(_L("Information element successfully fetched"));
	aLog->Log(_L("Get information element == PASS"));
	 
	return result;
	}
	 
// -----------------------------------------------------------------------------
// TestInformationElementIndex
// Gets index of a specified Information Element.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestInformationElementIndex( CStifLogger* aLog, CSmsCommand& aCommand)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling InformationElementIndex()"));
	TInt result = KErrNone;
	
	CSmsInformationElement::TSmsInformationElementIdentifier identifier = CSmsInformationElement::ESmsIEIConcatenatedShortMessages8BitReference;;
	TInt index;
	//IMPORT_C TBool InformationElementIndex(CSmsInformationElement::TSmsInformationElementIdentifier aIdentifier,
	//	TInt& aIndex) const;
	TInt length = aCommand.InformationElementIndex(identifier, index);
	
	aLog->Log(_L("InformationElementIndex() completed"));
	aLog->Log(_L("Information element index successfully fetched"));
	aLog->Log(_L("Get information element index == PASS"));
	return result;
	}
	 
// -----------------------------------------------------------------------------
// TestGetMessageNumber
// Gets the Message Number
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetMessageNumber( CStifLogger* aLog, CSmsCommand& aCommand)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling MessageNumber()"));
	TInt result = KErrNone;
	
	//IMPORT_C TInt MessageNumber() const;
	TInt number = aCommand.MessageNumber();
	
	if( number == 1 )
		{
		aLog->Log(_L("MessageNumber() completed"));
		aLog->Log(_L("Result data:Message number: %d"),number);
		aLog->Log(_L("Get message number == PASS"));	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log(_L("Get message number == FAIL"));	
		}
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestSetMessageNumber
// Sets the Message Number
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetMessageNumber( CStifLogger* aLog, CSmsCommand& aCommand)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetMessageNumber()"));
	TInt result = KErrNone;
	
	TInt number = 1;
	//IMPORT_C void SetMessageNumber(TInt aMessageNumber);
	aCommand.SetMessageNumber(number);
	
	aLog->Log(_L("SetMessageNumber() completed"));
	aLog->Log(_L("Message number successfully stored"));
	aLog->Log(_L("Set Message Number == PASS"));

	return result;
	}

// -----------------------------------------------------------------------------
// TestGetMessageReference
// Gets the Message Reference
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetMessageReference( CStifLogger* aLog, CSmsCommand& aCommand)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling MessageReference()"));
	TInt result = KErrNone;
	
	//IMPORT_C TInt MessageReference() const;
	TInt getRef = aCommand.MessageReference();
	
	if( getRef == 1 )
		{
		aLog->Log(_L("MessageReference() Completed"));
		aLog->Log(_L("result data:Message reference: %d"), getRef);
		aLog->Log(_L("Get Message Reference == PASS"));
		}
	else
		{
		 result = KErrGeneral;
		 aLog->Log(_L("Get Message Reference == FAIL"));
		}
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestSetMessageReference
// Sets the Message Reference
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetMessageReference( CStifLogger* aLog, CSmsCommand& aCommand)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetMessageReference()"));
	TInt result = KErrNone;
	
	TInt setRef = 1;
	//IMPORT_C void SetMessageReference(TInt aMessageReference);
	aCommand.SetMessageReference(setRef);
	
	aLog->Log(_L("SetMessageReference() Completed"));
	aLog->Log(_L("Message reference successfully stored"));
	aLog->Log(_L("Set Message Reference == PASS"));

	return result;
	}
	
// -----------------------------------------------------------------------------
// TestNumInformationElements
// Gets the number of Information Elements in the User Data
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestNumInformationElements( CStifLogger* aLog, CSmsCommand& aCommand)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling NumInformationElements()"));
	TInt result = KErrNone;
	
	//IMPORT_C TInt NumInformationElements() const;
	TInt numElements = aCommand.NumInformationElements();
	
	aLog->Log(_L("NumInformationElements() Completed"));
	aLog->Log(_L("result data: Number of elements: %d"), numElements);
	aLog->Log(_L("Get Number Of Information Elements == PASS"));

	return result;
	}
	

// -----------------------------------------------------------------------------
// TestGetStatusReportRequest
// Gets Status Report Request flag
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetStatusReportRequest( CStifLogger* aLog, CSmsCommand& aCommand)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling StatusReportRequest()"));
	TInt result = KErrNone;
	
	//IMPORT_C TBool StatusReportRequest() const;
	TBool reportReq = aCommand.StatusReportRequest();
	
	if( reportReq )
		{
		aLog->Log(_L("SetStatusReportRequest() completed"));
		aLog->Log(_L("Status report request flag successfully fetched"));
		aLog->Log(_L("Get status report request == PASS"));	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log(_L("Get status report request == FAIL"));	
		}
	
	return result;
	}
	 
// -----------------------------------------------------------------------------
// TestSetStatusReportRequest
// Externalises the object.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetStatusReportRequest( CStifLogger* aLog, CSmsCommand& aCommand)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetStatusReportRequest()"));
	TInt result = KErrNone;
	
	TBool reportReq = ETrue;
	//IMPORT_C void SetStatusReportRequest(TBool aRequest);
	aCommand.SetStatusReportRequest(reportReq);
	
	aLog->Log(_L("SetStatusReportRequest() completed"));
	aLog->Log(_L("Status report request flag successfully stored"));
	aLog->Log(_L("Set status report request == PASS"));
	
	return result;
	}
	 
// -----------------------------------------------------------------------------
// TestSetCommandData
// Sets the Command Data
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetCommandData( CStifLogger* aLog, CSmsCommand& aCommand)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetCommandDataL()"));
	
	TBufC8<24> commandData(KTestCommandData8);
	//IMPORT_C void SetCommandDataL(const TDesC8& aData);
	TRAPD( result, aCommand.SetCommandDataL(commandData));
	
	if( result == KErrNone )
		{
		aLog->Log(_L("SetCommandDataL() completed"));
		aLog->Log(_L("Command data successfully stored"));
		aLog->Log(_L("Set command data == PASS"));
		}
	else
		aLog->Log(_L("Set command data == FAIL"));
	
	return result;
	}
// -----------------------------------------------------------------------------
// TestSmsCommandDuplicateL
// Creates a copy of the object
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSmsCommandDuplicateL( CStifLogger* aLog, CSmsCommand& aCommand)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SmsCommandDuplicateL()"));
	
	TInt result = KErrNone;
	
	CSmsCommand* dupObj = aCommand.DuplicateL();
		
		if( dupObj )
			{
		aLog->Log(_L("TestSmsCommandDuplicateL() completed"));
		aLog->Log(_L("Object successfully created"));
		aLog->Log(_L("SmsCommandDuplicateL == PASS"));
		
		}
		else
			{
				result = KErrGeneral;
				aLog->Log(_L("SmsCommandDuplicateL == FAIL"));
			}
			return result;
	}

// -----------------------------------------------------------------------------
// TestSetMoreMessagesToSend
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetMoreMessagesToSend( CStifLogger* aLog, CSmsDeliver& aDeliver)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetMoreMessagesToSend()"));
	TInt result = KErrNone;
	
	//void SetMoreMessagesToSend(TBool aMore);
	aDeliver.SetMoreMessagesToSend(EFalse);
	
	aLog->Log(_L("SetMoreMessagesToSend() Completed"));
	aLog->Log(_L("More messages to send - flag successfully stored"));
	aLog->Log(_L("Set more messages to send == PASS"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestGetMoreMessagesToSend
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetMoreMessagesToSend( CStifLogger* aLog, CSmsDeliver& aDeliver)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling MoreMessagesToSend()"));
	TInt result = KErrNone;
	
	//TBool MoreMessagesToSend() const;
	TBool msgs = aDeliver.MoreMessagesToSend();
	
	if( msgs == EFalse)
		{
		aLog->Log(_L("MoreMessagesToSend() Completed"));
		aLog->Log(_L("Result Data:More messages to send flag: %d"), msgs);
		aLog->Log(_L("Get more messages to send == PASS"));
		}
	else
		{
		result =KErrGeneral;
		aLog->Log(_L("Get more messages to send == PASS"));
		}
			
	return result;
	}

// -----------------------------------------------------------------------------
// TestSetReplyPath
// Sets Reply Path flag
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetReplyPath( CStifLogger* aLog, CSmsDeliver& aDeliver)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetReplyPath()"));
	TInt result = KErrNone;
	
	//void SetReplyPath(TBool aReplyPath);
	aDeliver.SetReplyPath(EFalse);
	
	aLog->Log(_L("SetReplyPath() completed"));
	aLog->Log(_L("Reply path - flag successfully stored"));
	aLog->Log(_L("Set reply path == PASS"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestGetReplyPath
// Gets Reply Path flag
// If a Reply Path exists, the recipient of the SMS can reply using the same 
// service center address
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetReplyPath( CStifLogger* aLog, CSmsDeliver& aDeliver)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling ReplyPath()"));
	TInt result = KErrNone;
	
	//TBool ReplyPath() const;
	TBool path = aDeliver.ReplyPath();
	
	if(path == EFalse)
		{
		aLog->Log(_L("ReplyPath() Completed"));
		aLog->Log(_L("Result data:Reply path flag: %d "), path);
		aLog->Log(_L("Get reply path == PASS"));
		}
	else
		{
		result = KErrGeneral;
		aLog->Log(_L("Get reply path == FAIL"));
		}
		
	return result;
	}

// -----------------------------------------------------------------------------
// TestSetStatusReportIndication
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetStatusReportIndication( CStifLogger* aLog, CSmsDeliver& aDeliver)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetStatusReportIndication()"));
	TInt result = KErrNone;
	
	//void SetStatusReportIndication(TBool aIndication);
	aDeliver.SetStatusReportIndication(ETrue);
	
	aLog->Log(_L("SetStatusReportIndication() Completed"));
	aLog->Log(_L("Status report flag successfully stored"));
	aLog->Log(_L("Set status report indication == PASS"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestGetStatusReportIndication
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetStatusReportIndication( CStifLogger* aLog, CSmsDeliver& aDeliver)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling StatusReportIndication()"));
	TInt result = KErrNone;
	
	//TBool StatusReportIndication() const;
	TBool indication = aDeliver.StatusReportIndication();
	
	if( indication )
		{
		aLog->Log(_L("StatusReportIndication() Completed"));
		aLog->Log(_L("Result data:Status report flag: %d "), indication);
		aLog->Log(_L("Get status report indication == PASS"));
		}
	else
		{
		result = KErrGeneral;
		aLog->Log(_L("Get status report indication == FAIL"));
		}	
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestSetServiceCenterTimeStamp
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetServiceCenterTimeStamp( CStifLogger* aLog, CSmsDeliver& aDeliver)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetServiceCenterTimeStamp()"));
	TInt result = KErrNone;
	
	const TTime time(TDateTime(2006,EJanuary,01,12,0,0,0));
	//void SetServiceCenterTimeStamp(const TTime& aTime,TInt aNumQuarterHours=0)
	aDeliver.SetServiceCenterTimeStamp(time);
	
	aLog->Log(_L("SetServiceCenterTimeStamp() Completed"));
	aLog->Log(_L("Time stamp successfully stored"));
	aLog->Log(_L("Set service center time stamp == PASS"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestGetServiceCenterTimeStamp
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetServiceCenterTimeStampL( CStifLogger* aLog, CSmsDeliver& aDeliver)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling ServiceCenterTimeStamp()"));
	TInt result = KErrNone;
	
	TBuf<30> string;
	_LIT( KFormat, "%*E%*D%X%*N%*Y %1 %2 '%3 %H%:1%T%:2%S");
	TTime setTime(TDateTime(2006,EJanuary,01,12,0,0,0));
	TTime getTime;
	TInt numQuarterHrs;
	//void ServiceCenterTimeStamp(TTime& aTime,TInt& aNumQuarterHours);
	aDeliver.ServiceCenterTimeStamp(getTime, numQuarterHrs);
	
	if( getTime == setTime )
		{
		getTime.FormatL(string, KFormat);
		aLog->Log(_L("ServiceCenterTimeStamp() Completed"));
		aLog->Log(_L("Result data:Time stamp: %S"), &string);
		//aLog->Log(_L("Time zone difference: %d"),  );
		aLog->Log(_L("Get service center time stamp == PASS"));
		}
	else
		{
		result = KErrGeneral;
		aLog->Log(_L("Get service center time stamp == FAIL"));
		}
		
	return result;
	}

// -----------------------------------------------------------------------------
// TestGetProtocolIdentifier
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetProtocolIdentifier( CStifLogger* aLog, CSmsDeliver& aDeliver)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling ProtocolIdentifier()"));
	TInt result = KErrNone;
	
	//const TSmsProtocolIdentifier* ProtocolIdentifier() const;
	const TSmsProtocolIdentifier* id = aDeliver.ProtocolIdentifier();
	
	aLog->Log(_L("ProtocolIdentifier() Completed"));
	aLog->Log(_L("Result data:Protocol identifier: %d"), id->operator TInt());
	aLog->Log(_L("Get protocol identifier == PASS"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestSmsDeliverDuplicateL
// Creates a copy of the object
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSmsDeliverDuplicateL( CStifLogger* aLog, CSmsDeliver& aDeliver)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SmsDeliverDuplicateL()"));
	
	TInt result = KErrNone;
	
	CSmsDeliver* dupObj = aDeliver.DuplicateL();
		
		if( dupObj )
			{
		aLog->Log(_L("TestSmsDeliverDuplicateL() completed"));
		aLog->Log(_L("Object successfully created"));
		aLog->Log(_L("SmsDeliverDuplicateL == PASS"));
		
		}
		else
			{
				result = KErrGeneral;
				aLog->Log(_L("SmsDeliverDuplicateL == FAIL"));
			}
			return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetIsRPError
// Gets the Reply Path Error flag 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetIsRPError (CStifLogger* aLog, CSmsDeliverReport& aDeliverReport)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling IsRPError()"));
	
	TInt result = KErrNone;
	
	// TBool IsRPError() const
	TBool checkres = aDeliverReport.IsRPError();
	
	if( checkres )
	{
		aLog->Log( _L("IsRPError() completed"));
		aLog->Log(_L("Result data:is RP error flag: %d"),checkres);
		aLog->Log( _L("Get is RP error == PASS"));
	}
	else
		aLog->Log( _L("Get is RP error == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetIsRPError
// Gets the Reply Path Error flag 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetIsRPError (CStifLogger* aLog, CSmsDeliverReport& aDeliverReport)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetIsRPError()"));
	
	TInt result = KErrNone;
	TBool tempVar = ETrue;
	
	// inline void SetIsRPError(TBool aIsRPError)
	aDeliverReport.SetIsRPError (tempVar);
	
	aLog->Log( _L("SetIsRPError() completed"));
	aLog->Log( _L("Is RP error flag stored successfully"));
	aLog->Log( _L("Set is RP error == PASS"));
	
	return result;
	}
	

// -----------------------------------------------------------------------------
// TestGetFailureCause
// Gets the Failure Cause 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetFailureCause (CStifLogger* aLog, CSmsDeliverReport& aDeliverReport)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling FailureCause()"));
	
	TInt result = KErrNone;
	 
	// IMPORT_C TInt FailureCause() const
	TInt checkres = aDeliverReport.FailureCause ();
	
	if(checkres == TSmsFailureCause::ESmsPIDErrorCannotReplaceShortMessage)
	{
		aLog->Log( _L("FailureCause() completed"));
		_LIT(tempVal,"result data:failure cause: %d");
		aLog->Log(tempVal,checkres);
		aLog->Log( _L("Get failure cause == PASS"));
	}
	else
		aLog->Log( _L("Get failure cause == FAIL"));
	
	return result;
	}
	
	
// -----------------------------------------------------------------------------
// TestSetFailureCause
// Sets the Failure Cause 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetFailureCause (CStifLogger* aLog, CSmsDeliverReport& aDeliverReport)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetFailureCause()"));
	
	TInt result = KErrNone;
	TSmsFailureCause::TSmsFailureCauseError aFailureCause = 
	   TSmsFailureCause::ESmsPIDErrorCannotReplaceShortMessage;
	
	// IMPORT_C void SetFailureCause
	// (TSmsFailureCause::TSmsFailureCauseError aFailureCause)
	aDeliverReport.SetFailureCause (aFailureCause);
	
	if(result == KErrNone)
	{
		aLog->Log( _L("SetFailureCause() completed"));
		aLog->Log( _L("Failure cause stored successfully"));
		aLog->Log( _L("Set failure cause == PASS"));
	}
	else
		aLog->Log( _L("Set failure cause == FAIL"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestSmsDeliverReportDuplicateL
// Creates a copy of the object
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSmsDeliverReportDuplicateL( CStifLogger* aLog, CSmsDeliverReport& aDeliverReport)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SmsDeliverReportDuplicateL()"));
	
	TInt result = KErrNone;
	
	CSmsDeliverReport* dupObj = aDeliverReport.DuplicateL();
		
		if( dupObj )
			{
		aLog->Log(_L("TestSmsDeliverReportDuplicateL() completed"));
		aLog->Log(_L("Object successfully created"));
		aLog->Log(_L("SmsDeliverReportDuplicateL == PASS"));
		
		}
		else
			{
				result = KErrGeneral;
				aLog->Log(_L("SmsDeliverReportDuplicateL == FAIL"));
			}
			return result;
	}

// -----------------------------------------------------------------------------
// TestDelete
// Deletes data from the buffer
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestDelete( CStifLogger* aLog, CSmsEditorBuffer& aBuffer)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling DeleteL()"));
	
	TInt position = 2;
	TInt length = 2;
	//IMPORT_C void DeleteL(TInt aPos,TInt aLength);
	TRAPD( result, aBuffer.DeleteL( position, length));
	
	if( result == KErrNone )
		{
		aLog->Log(_L("DeleteL() Completed"));
		aLog->Log(_L("Data successfully deleted"));
		aLog->Log(_L("Delete == PASS"));
		}
	else
		aLog->Log(_L("Delete == FAIL"));
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestReset
// Resets the buffer
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestReset( CStifLogger* aLog, CSmsEditorBuffer& aBuffer)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling Reset()"));
	TInt result = KErrNone;
	
	//IMPORT_C void Reset();
	aBuffer.Reset();

	aLog->Log(_L("Reset() Completed"));
	aLog->Log(_L("Data successfully reseted"));
	aLog->Log(_L("Reset == PASS"));
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestExtract
// Extracts buffer data to a descriptor
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestExtract( CStifLogger* aLog, CSmsEditorBuffer& aBuffer)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling Extract()"));
	TInt result = KErrNone;
	
	TBuf<24> buffer;
	TInt position = 2;
	TInt length = 6;
	//IMPORT_C void Extract(TDes& aBuf,TInt aPos,TInt aLength) const;
	aBuffer.Extract(buffer, position, length);
	
	aLog->Log(_L("Extract() Completed"));
	aLog->Log(_L("Data successfully extracted"));
	aLog->Log(_L("Extract == PASS"));
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestInsert
// Inserts data into the buffer
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestInsert( CStifLogger* aLog, CSmsEditorBuffer& aBuffer)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling InsertL()"));
	
	TBufC<24> buffer(KTestBuffer1);
	TInt position = 0;
	//IMPORT_C void InsertL(TInt aPos,const TDesC& aBuf);
	TRAPD( result, aBuffer.InsertL(position, buffer));
	
	if( result == KErrNone )
		{
		aLog->Log(_L("InsertL() Completed"));
		aLog->Log(_L("Data successfully Inserted"));
		aLog->Log(_L("Delete == PASS"));
		}
	else
		aLog->Log(_L("Delete == FAIL"));
	
	return result;
	}
	 
// -----------------------------------------------------------------------------
// TestGetLength
// Gets the amount of space currently used in the buffer.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetLength( CStifLogger* aLog, CSmsEditorBuffer& aBuffer)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling Length()"));
	TInt result = KErrNone;
		
	//IMPORT_C TInt Length() const;
	TInt length = aBuffer.Length();
	
	if(length == 22) 
		{
		aLog->Log(_L("Length() Completed"));
		aLog->Log(_L("Result data: Length: %d"), length);
		aLog->Log(_L("Length == PASS"));	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log(_L("Length == FAIL"));
		}
		
	return result;
	}

// -----------------------------------------------------------------------------
// TestGetIdentifier
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetIdentifier( CStifLogger* aLog, CSmsInformationElement& aElement)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling Identifier()"));
	TInt result = KErrNone;
		
	//TSmsInformationElementIdentifier Identifier() const;
	CSmsInformationElement::TSmsInformationElementIdentifier id = aElement.Identifier();
	
	aLog->Log(_L("Identifier() Completed"));
	aLog->Log(_L("Result data: Identifier: %d"),id);
	aLog->Log(_L("Get identifier == PASS"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestGetDataTPtr8
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetDataTPtr8( CStifLogger* aLog, CSmsInformationElement& aElement)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling TPtr8 Data()"));
	TInt result = KErrNone;
	
	//TPtr8 Data();
	TPtr8 data = aElement.Data();
	
	aLog->Log(_L("TPtr8 Data() Completed"));
	aLog->Log(_L("Result data: Data: %s"), data.Ptr());
	aLog->Log(_L("Get data (TPtr8) == PASS"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestGetDataTDesC8
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetDataTDesC8( CStifLogger* aLog, CSmsInformationElement& aElement)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling TDesC8& Data()"));
	TInt result = KErrNone;
	
	//const TDesC8& Data() const;	
	const TBufC8<32> data = aElement.Data();
		
	aLog->Log(_L("TDesC8& Data() Completed"));
	aLog->Log(_L("Result data: Data: %s"), data.Ptr());
	aLog->Log(_L("Get data (TDesC8) == PASS"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestConstructionSmsPDUType
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestConstructionTGsmSms_MessageL(CStifLogger* aLog)	
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling CSmsMessage::NewL(TGsmSms)"));
	TInt result = KErrNone;
	
	RFs session;
	User::LeaveIfError(session.Connect());
	TGsmSms sms;
	CSmsBuffer* buffer = CSmsBuffer::NewL();
	CCnvCharacterSetConverter* characterSetConverter = CCnvCharacterSetConverter::NewL(); 
	//static CSmsPDU* NewL(TSmsPDUType aType,CCnvCharacterSetConverter& aCharacterSetConverter,RFs& aFs,TBool aIsRPError=EFalse);
	CSmsPDU* PDU = CSmsPDU::NewL(CSmsPDU::ESmsDeliver, *characterSetConverter, session);
	PDU->EncodeMessagePDUL( sms );
	
	//static CSmsMessage* NewL(RFs& aFs, const TGsmSms& aGsmSms,CSmsBufferBase* aBuffer, 
	//	TBool aIsRPError=EFalse,TBool aIsMobileTerminated=ETrue);
	CSmsMessage* message = CSmsMessage::NewL(session, sms, buffer);
	CleanupStack::PushL(message);
	
	if(message == NULL )
	   result = KErrGeneral;
	
	CleanupStack::PopAndDestroy();
	session.Close();
   	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetType
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetType(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling Type()"));
	TInt result = KErrNone;
	
	//CSmsPDU::TSmsPDUType Type() const;
	CSmsPDU::TSmsPDUType type = aMessage.Type();
	
	if( type == CSmsPDU::ESmsDeliver )
		{
		aLog->Log(_L("Type() Completed"));
		aLog->Log(_L("Result data: Type: %d"), type);
		aLog->Log(_L("Get type == PASS"));	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log(_L("Get type == FAIL"));	
		}
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetIsComplete
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetIsComplete(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling IsComplete()"));
	TInt result = KErrNone;
	
	//TBool IsComplete() const;
	TBool res = aMessage.IsComplete();
	
	aLog->Log(_L("IsComplete() Completed"));
	aLog->Log(_L("Result data: Is completed: %d"), res);
	aLog->Log(_L("Get is complete == PASS"));
	
	return result;
	}
// -----------------------------------------------------------------------------
// TestIsDecoded
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestIsDecoded(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling IsDecoded()"));
	TInt result = KErrNone;
	
	//TBool IsDecoded() const
	TBool res = aMessage.IsDecoded();
	
	aLog->Log(_L("IsDecoded() Completed"));
	aLog->Log(_L("Result data: IsDecoded: %d"), res);
	aLog->Log(_L("Get is decoded == PASS"));
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestSetStorage
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetStorage(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetStorage()"));
	TInt result = KErrNone;
	
	//void SetStorage(TMobileSmsStorage aStorage)
	CSmsMessage::TMobileSmsStorage storage = CSmsMessage::ESmsNoStorage;
	aMessage.SetStorage(storage);
	
	aLog->Log(_L("SetStorage() Completed"));	
	aLog->Log(_L("Storage successfully set"));	
	aLog->Log(_L("Set storage == PASS"));	

	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetStorage
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetStorage(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling Storage()"));
	TInt result = KErrNone;
	
	//TMobileSmsStorage Storage() const
	CSmsMessage::TMobileSmsStorage storage = aMessage.Storage();

	if( storage == CSmsMessage::ESmsNoStorage)
		{
		aLog->Log(_L("Storage() Completed"));	
		aLog->Log(_L("Result data: storage: %d"), storage);	
		aLog->Log(_L("Get storage == PASS"));	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log(_L("Get storage == FAIL"));	
		}
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestSetStatus
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetStatus(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetStatus()"));
	TInt result = KErrNone;
	
	//void SetStatus(NMobileSmsStore::TMobileSmsStoreStatus aStatus)
	NMobileSmsStore::TMobileSmsStoreStatus status = NMobileSmsStore::EStoredMessageUnknownStatus;
	aMessage.SetStatus(status);
	
	aLog->Log(_L("Status() Completed"));	
	aLog->Log(_L("Result data: status: %d"), status);	
	aLog->Log(_L("Get status == PASS"));	
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetStatus
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetStatus(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling Status()"));
	TInt result = KErrNone;
	
	//NMobileSmsStore::TMobileSmsStoreStatus Status() const
	NMobileSmsStore::TMobileSmsStoreStatus status = aMessage.Status();
	
	if( status == NMobileSmsStore::EStoredMessageUnknownStatus )
		{
		aLog->Log(_L("Status() Completed"));	
		aLog->Log(_L("Result data: status: %d"), status);	
		aLog->Log(_L("Get status == PASS"));	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log(_L("Get status == FAIL"));
		}

	return result;
	}
	
// -----------------------------------------------------------------------------
// TestSetLogServerId
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetLogServerId(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetLogServerId()"));
	TInt result = KErrNone;
	
	//void SetLogServerId(TInt aId)
	TInt id = 1;
	aMessage.SetLogServerId(id);
	
	aLog->Log(_L("SetLogServerId() completed"));	
	aLog->Log(_L("Log server id successfully stored"));	
	aLog->Log(_L("Set log server id == PASS"));	

	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetLogServerId
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetLogServerId(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling LogServerId()"));
	TInt result = KErrNone;
	
	//TInt LogServerId() const
	TInt id = aMessage.LogServerId();
	
	if( id == 1)
		{
		aLog->Log(_L("LogServerId() completed"));	
		aLog->Log(_L("result data: log server id: %d"), id);	
		aLog->Log(_L("Get log server id == PASS"));	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log(_L("Get log server id == FAIL"));	
		}
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestSetTime
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetTime(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetTime()"));
	TInt result = KErrNone;
	
	TTime time(TDateTime(2006,EJanuary,01,12,0,0,0));
	//void SetTime(const TTime &aTime)
	aMessage.SetTime(time);
	
	aLog->Log(_L("SetTime() completed"));	
	aLog->Log(_L("Time successfully stored"));	
	aLog->Log(_L("Set time == PASS"));	

	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetTime
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetTimeL(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling Time()"));
	TInt result = KErrNone;
	
	TBuf<30> string;
	_LIT( KFormat, "%*E%*D%X%*N%*Y %1 %2 '%3 %H%:1%T%:2%S");
	TTime setTime(TDateTime(2006,EJanuary,01,12,0,0,0));
	//const TTime &Time() const
	TTime time = aMessage.Time();
	
	if( time == setTime )
		{
		time.FormatL(string, KFormat);
		aLog->Log(_L("Time() completed"));	
		aLog->Log(_L("result data: time: %S"), &string);	
		aLog->Log(_L("Get time == PASS"));	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log(_L("Get time == FAIL"));			
		}

	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetSMSPDU
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetSMSPduL(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SmsPduL()"));
	TInt result = KErrNone;
	
	//CSmsPDU &SmsPduL()
	CSmsPDU& smspdu = aMessage.SmsPDU();
	
	aLog->Log(_L("SmsPduL() completed"));	
	aLog->Log(_L("result data: PDU type: %d"), smspdu.Type());	
	aLog->Log(_L("Get SMS PDU == PASS"));	

	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetSMSPDUConst
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetSMSPDUConst(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SmsPduL() const"));
	TInt result = KErrNone;
	
	//const CSmsPDU &SmsPduL() const
	const CSmsPDU& smspdu = aMessage.SmsPDU();
	
	aLog->Log(_L("SmsPduL()  const completed"));	
	aLog->Log(_L("result data: PDU type: %d"), smspdu.Type());	
	aLog->Log(_L("Get SMS PDU == PASS"));	

	return result;
	}
	
// -----------------------------------------------------------------------------
// TestSetSeviceCenterAddress
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetServiceCenterAddress(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetServiceCenterAddressL()"));
	
	TPtrC serviceCenter = _L("nokia house");
	//void SetServiceCenterAddressL(const TDesC &aAddress)
	TRAPD( result,aMessage.SetServiceCenterAddressL(serviceCenter));
	
	if( result == KErrNone )
		{
		aLog->Log(_L("SetServiceCenterAddressL() completed"));
		aLog->Log(_L("Service center address successfully stored"));
		aLog->Log(_L("Set service center address == PASS"));
		}
	else
		{
		aLog->Log(_L("Set service center address == FAIL"));
		}	
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetSeviceCenterAddress
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetServiceCenterAddress(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling ServiceCenterAddress()"));
	TInt result = KErrNone;
	
	TPtrC setServiceCenter = _L("nokia house");
	//TPtrC ServiceCenterAddress() const
	TPtrC serviceCenter = aMessage.ServiceCenterAddress();
	
	if( !setServiceCenter.Compare(serviceCenter) )
		{
		aLog->Log(_L("ServiceCenterAddress() completed"));
		aLog->Log(_L("result data: address: %s"), serviceCenter.Ptr());
		aLog->Log(_L("Get service center address == PASS"));
		}
	else
		{
		aLog->Log(_L("Get service center address == FAIL"));
		}
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestSetParsedServiceCenterAddress
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetParsedServiceCenterAddress(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetParsedServiceCenterAddressL()"));
	
	//void SetParsedServiceCenterAddressL(const TGsmSmsTelNumber &aParsedAddress);
	TGsmSmsTelNumber telNumber;
	telNumber.iTelNumber = _L("919886757059");
	TRAPD( result, aMessage.SetParsedServiceCenterAddressL(telNumber));
	
	if( result == KErrNone )
		{
		aLog->Log(_L("SetParsedServiceCenterAddressL() completed"));
		aLog->Log(_L("Parsed address successfully stored"));
		aLog->Log(_L("Set parsed service center address == PASS"));
		}
	else
		{
		aLog->Log(_L("Set parsed service center address == FAIL"));		
		}

	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetParsedServiceCenterAddress
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetParsedServiceCenterAddress(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling ParsedServiceCenterAddress()"));
	TInt result = KErrNone;
	
	TGsmSmsTelNumber setTelNumber;
	setTelNumber.iTelNumber = _L("919886757059");
	//void ParsedServiceCenterAddress(TGsmSmsTelNumber &aParsedAddress) const
	TGsmSmsTelNumber telNumber;
	aMessage.ParsedServiceCenterAddress(telNumber);
	
	if(setTelNumber.iTelNumber == telNumber.iTelNumber)
		{
		aLog->Log(_L("ParsedServiceCenterAddress() completed"));
		aLog->Log(_L("result data: parsed address: %s"), telNumber.iTelNumber.Ptr());
		aLog->Log(_L("Get parsed service center address == PASS"));
		}
	else
		{
		aLog->Log(_L("Get parsed service center address == FAIL"));
		}
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestSetToFromAddress
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetToFromAddress(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetToFromAddressL()"));
	
	TBufC<12> address(_L("nokia house"));
	
	//void SetToFromAddressL(const TDesC &aAddress)
	TRAPD( result, aMessage.SetToFromAddressL(address));
	
	if( result == KErrNone )
		{
		aLog->Log(_L("SetToFromAddressL() completed"));
		aLog->Log(_L("To from addresses successfully stored"));
		aLog->Log(_L("Set to from address == PASS"));
		}
	else
		{
		aLog->Log(_L("Set to from address == FAIL"));		
		}
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetToFromAddress
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetToFromAddress(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling ToFromAddress()"));
	TInt result = KErrNone;
	
	TBufC<12> address(_L("nokia house"));
	//TPtrC ToFromAddress() const
	TPtrC addressPtr = aMessage.ToFromAddress();
		
	if( !addressPtr.Compare(address) )
		{
		aLog->Log(_L("ToFromAddress() completed"));
		aLog->Log(_L("result data: to from address: %s"), addressPtr.Ptr());
		aLog->Log(_L("Get to from address ==  PASS"));
		}
	else
		{
		result = KErrGeneral;
		aLog->Log(_L("Get to from address ==  FAIL"));
		}
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestSetParsedToFromAddress
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetParsedToFromAddress(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetParsedToFromAddressL()"));
	
	//void SetParsedToFromAddressL(const TGsmSmsTelNumber &aParsedAddress)
	TGsmSmsTelNumber address;
	address.iTelNumber = _L("919886757059");
	TRAPD( result, aMessage.SetParsedToFromAddressL(address));

	if( result == KErrNone )
		{
		aLog->Log(_L("SetParsedToFromAddressL() completed"));
		aLog->Log(_L("Parsed to from addresses successfully stored"));
		aLog->Log(_L("Set to from address == PASS"));
		}
	else
		{
		aLog->Log(_L("Set to from address == FAIL"));		
		}
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetParsedToFromAddress
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetParsedToFromAddress(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling ParsedToFromAddress()"));
	TInt result = KErrNone;
	
	TGsmSmsTelNumber setAddress;
	setAddress.iTelNumber = _L("919886757059");
	//void ParsedToFromAddress(TGsmSmsTelNumber &aParsedAddress) const
	TGsmSmsTelNumber address;
	aMessage.ParsedToFromAddress(address);
	
	if(setAddress.iTelNumber == address.iTelNumber)
		{
		aLog->Log(_L("ParsedToFromAddress() completed"));
		aLog->Log(_L("result data: parsed to from address: %s"), address.iTelNumber.Ptr());
		aLog->Log(_L("Get to from address ==  PASS"));
		}
	else
		{
		aLog->Log(_L("Get to from address ==  FAIL"));
		}
		
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestInternalizeWithoutBuffer
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestInternalizeWithoutBufferL(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling InternalizeWithoutBufferL()"));

	RFs session;
    User::LeaveIfError(session.Connect());
	TBufC<64> storename = _L("C:\\SMSGSMUtilities_CSmsMessage");
    RFileReadStream read;
		
	TInt erro = read.Open(session, storename, EFileRead);
	
	//void InternalizeWithoutBufferL(RReadStream &aStream)
	TRAPD( result, aMessage.InternalizeWithoutBufferL(read));
	
	read.Close();
	
	//now delete the store
	TInt err = session.Delete(storename);
	if(err != KErrNone) 
		{
		RDebug::Print(_L("Error %d deleting \"%S\" file.\n"), err, &storename);
		}

	session.Close();
	if( result == KErrNone )	
		{
		aLog->Log(_L("InternalizeWithoutBufferL() completed"));
		aLog->Log(_L("Data internalized successfully"));
		aLog->Log(_L("Internalize without buffer == PASS"));
		}
	else
		aLog->Log(_L("Internalize without buffer == FAIL"));
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestExternalizeWithoutBufferL
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestExternalizeWithoutBufferL(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling ExternalizeWithoutBufferL()"));

	RFs session;
    User::LeaveIfError(session.Connect());
	TBufC<64> storename = _L("C:\\SMSGSMUtilities_CSmsMessage");
	RFileWriteStream write;
	
	write.Create(session, storename, EFileWrite);
	TInt err = write.Open(session, storename, EFileWrite);
	
	//void ExternalizeWithoutBufferL(RWriteStream &aStream) const
	TRAPD( result, aMessage.ExternalizeWithoutBufferL(write));
	
	write.CommitL();
	write.Close();
	
	session.Close();
	if( result == KErrNone )
		{
		aLog->Log(_L("ExternalizeWithoutBufferL() completed"));
		aLog->Log(_L("Data externalized successfully"));
		aLog->Log(_L("Externalize without buffer == PASS"));
		}
	else
		aLog->Log(_L("Externalize without buffer == FAIL"));
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestInternalize
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestInternalizeL(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling InternalizeL()"));
	
	RFs session;
    User::LeaveIfError(session.Connect());
	TBufC<64> storename = _L("C:\\SMSGSMUtilities_CSmsMessage");
    RFileReadStream read;
		
	TInt erro = read.Open(session, storename, EFileRead);
	
	//IMPORT_C void InternalizeL(RReadStream &aStream)
	TRAPD( result, aMessage.InternalizeL( read ));
	
	read.Close();
	
	//now delete the store
	TInt err = session.Delete(storename);
	if(err != KErrNone) 
		{
		RDebug::Print(_L("Error %d deleting \"%S\" file.\n"), err, &storename);
		}

	session.Close();
	if( result == KErrNone )	
		{
		aLog->Log(_L("InternalizeL() completed"));
		aLog->Log(_L("Data internalized successfully"));
		aLog->Log(_L("Internalize == PASS"));
		}
	else
		aLog->Log(_L("Internalize == FAIL"));
	
	return result;
	
	}
	
// -----------------------------------------------------------------------------
// TestExternalize
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestExternalizeL(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling ExternalizeL()"));
	
	RFs session;
    User::LeaveIfError(session.Connect());
	TBufC<64> storename = _L("C:\\SMSGSMUtilities_CSmsMessage");
	RFileWriteStream write;
	
	write.Create(session, storename, EFileWrite);
	TInt err = write.Open(session, storename, EFileWrite);
	
	//IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	TRAPD( result, aMessage.ExternalizeL( write ));
	
	write.CommitL();
	write.Close();
	
	session.Close();
	if( result == KErrNone )
		{
		aLog->Log(_L("ExternalizeL() completed"));
		aLog->Log(_L("Data externalized successfully"));
		aLog->Log(_L("Externalize == PASS"));
		}
	else
		aLog->Log(_L("Externalize == FAIL"));
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetBuffer
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetBufferL(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling Buffer()"));
	TInt result = KErrNone;
	
	//CSmsBufferBase &Buffer()
	CSmsBuffer& buffer = STATIC_CAST(CSmsBuffer&, aMessage.Buffer());
	HBufC* buf = HBufC::NewL(buffer.Length());
	TPtr bufPtr = buf->Des();
	
	aLog->Log(_L("Buffer() completed"));
	buffer.Extract(bufPtr, 0, buffer.Length());
	aLog->Log(_L("result data: buffer: %s"), buf);
	aLog->Log(_L("Get buffer ==  PASS"));
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetBufferConst
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetBufferConstL(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling const Buffer()"));
	TInt result = KErrNone;
	
	//const CSmsBufferBase &Buffer() const
	const CSmsBuffer& buffer = STATIC_CAST(const CSmsBuffer&, aMessage.Buffer());
	HBufC* buf = HBufC::NewL(buffer.Length());
	TPtr bufPtr = buf->Des();
		
	aLog->Log(_L("const Buffer() completed"));
	buffer.Extract(bufPtr, 0, buffer.Length());
	aLog->Log(_L("result data: buffer: %s"), buf);
	aLog->Log(_L("Get buffer const ==  PASS"));
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetTextPresent
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetTextPresent(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling TextPresent()"));
	TInt result = KErrNone;
	
	//TBool TextPresent() const
	TBool res = aMessage.TextPresent();
	
	aLog->Log(_L("TextPresent() completed"));
	aLog->Log(_L("result data: text present: %d"), res);
	aLog->Log(_L("Get text present ==  PASS"));
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetNumberOfMessagePDU
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetNumberOfMessagePduL(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling NumMessagePDUsL()"));
	
	//TInt NumMessagePDUsL()
	TInt res = 0;
	TRAPD(result, res = aMessage.NumMessagePDUsL());
	if(result != KErrNone)
		{
		aLog->Log(_L("Leave occured: error code: %d"), result);
		}
	else
		{
		aLog->Log(_L("NumMessagePDUsL() completed"));
		aLog->Log(_L("result data: number of PDUs: %d"), res);
		aLog->Log(_L("Get number of message PDUs ==  PASS"));
		}
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetMaxLength
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetMaxLength(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling MaxMessageLength()"));
	TInt result = KErrNone;
	
	//TInt MaxMessageLength()
	TInt res = aMessage.MaxMessageLength();
	
	aLog->Log(_L("MaxMessageLength() completed"));
	aLog->Log(_L("result data: max message length: %d"), res);
	aLog->Log(_L("Get max message length ==  PASS"));

	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetMessageLength
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetMessageLength(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling MessageLengthL()"));
	
	//TInt MessageLengthL()
	TInt res = 0;
	TRAPD(result, res = aMessage.MessageLengthL());
	if(result != KErrNone)
		{
		aLog->Log(_L("Leave occured: error code: %d"), result);
		}
	else
		{
		aLog->Log(_L("MessageLengthL() completed"));
		aLog->Log(_L("result data: message length: %d"), res);
		aLog->Log(_L("Get message length ==  PASS"));
		}
		
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestOptimizeSettings
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestOptimizeSettings(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling OptimizeSettingsL()"));
	
	//void OptimizeSettingsL(TInt aOptions)
	TRAPD( result, aMessage.OptimizeSettingsL(CSmsMessage::ESmsFlagOptimizeAlphabet));	
	if(result != KErrNone)
		{
		aLog->Log(_L("Leave occured: error code: %d"), result);
		}
	else
		{
		aLog->Log(_L("OptimizeSettingsL() completed"));
		aLog->Log(_L("User data settings successfully optimized"));
		aLog->Log(_L("Optimize settings == PASS"));
		}
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetIsSupported
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetIsSupported(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling IsSupportedL()"));
	
	//TBool IsSupportedL(const TDesC &aDes, TInt &aNumberOfUnconvertibleCharacters, TInt &aIndexOfFirstUnconvertibleCharacter)
	TBufC<50> testBuffer = _L("Nokia$123has*some%employees");
	TInt numUnconvertable;
	TInt posFirstUnconvertable;
	TBool res = 0;
	TRAPD( result, res = aMessage.IsSupportedL(testBuffer, numUnconvertable, posFirstUnconvertable));
	
	if(result != KErrNone)
		{
		aLog->Log(_L("Leave occured: error code: %d"), result);
		}
	else
		{
		aLog->Log(_L("IsSupportedL() completed"));
		aLog->Log(_L("result data: is supported: %d"), res);
		aLog->Log(_L("Get is supported == PASS"));
		}
	return result;	
	}


// -----------------------------------------------------------------------------
// TestEncodeMessagePDU
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestEncodeMessagePDUL(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling EncodeMessagePDUsL()"));
	
	CArrayFix<TGsmSms>* singlePDU = new (ELeave) CArrayFixFlat<TGsmSms>(10);
	aMessage.EncodeIntoSinglePDUL(*singlePDU);
	CArrayFix<TGsmSms>* encodedPDU = new (ELeave) CArrayFixFlat<TGsmSms>(10);
	//EncodeMessagePDUsL(CArrayFix< TGsmSms > &aSmsArray, TInt aReference=0)
	TRAPD( result, aMessage.EncodeMessagePDUsL(*encodedPDU));	
	if(result != KErrNone)
		{
		aLog->Log(_L("Leave occured: error code: %d"), result);
		}
	else
		{
		aLog->Log(_L("EncodeMessagePDUsL() completed"));
		aLog->Log(_L("Message PDUs encoded successfully"));
		aLog->Log(_L("Encode message PDUs == PASS"));
		}
		
	delete singlePDU;
	delete encodedPDU;
	return result;	
	}
	
// -----------------------------------------------------------------------------
// TestDecodeMessagePDU
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestDecodeMessagePDUL(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling DecodeMessagePDUsL()"));
	
	CArrayFix<TGsmSms>* PDU = new (ELeave) CArrayFixFlat<TGsmSms>(10);
	const TGsmSms* gsmSms = new (ELeave) TGsmSms();
	
	TInt i = 0;
	for(; i<10; i++ )
		{
		  PDU->InsertL(i,*gsmSms);
		}

	//void DecodeMessagePDUsL(const CArrayFix<TGsmSms>& aSmsArray);
	TRAPD( result, aMessage.DecodeMessagePDUsL(*PDU));
	if(result != KErrNone)
		{
		aLog->Log(_L("Leave occured: error code: %d"), result);
		}
	else
		{
		aLog->Log(_L("DecodeMessagePDUsL() completed"));
		aLog->Log(_L("Message PDUs decoded successfully"));
		aLog->Log(_L("Decode message PDUs == PASS"));
		}
	
	delete PDU;	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestAddEMSInformationElements
// 
// -----------------------------------------------------------------------------
/*LOCAL_C TInt TestAddEMSInformationElements(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling AddEMSInformationElementL()"));
	TInt result = KErrNone;
	RFs rfServer; 
    User::LeaveIfError(rfServer.Connect()); 
    
    CCnvCharacterSetConverter* characterSetConverter = CCnvCharacterSetConverter::NewL(); 
    CSmsBuffer* smsBuffer = CSmsBuffer::NewL(); 
	CSmsMessage* smsMessage = CSmsMessage::NewL(rfServer, CSmsPDU::ESmsCommand, smsBuffer ); 	
	CSmsCommand& command = STATIC_CAST(CSmsCommand&, smsMessage->SmsPduL() );
	
	CSmsInformationElement::TSmsInformationElementIdentifier identifier = CSmsInformationElement::ESmsEnhancedVariablePicture;
	TBufC8<24> information(KTestInfo8);
	command.AddInformationElementL( identifier, information);
	
	CEmsInformationElement& element = STATIC_CAST(CEmsInformationElement&, command.InformationElement(0));	
	CleanupStack::PushL(&element);
	
	element.SetStartPosition(0);

//currently not exported
	CEmsSoundIE* element = CEmsSoundIE::NewL();
	CleanupStack::PushL(element);
	
	//void AddEMSInformationElementL(const CEmsInformationElement &aEmsIE)
	TRAPD( result, aMessage.AddEMSInformationElementL(*element));
	
	if(result != KErrNone)
		{
		aLog->Log(_L("Leave occured: error code: %d"), result);
		}
	else
		{
		aLog->Log(_L("AddEMSInformationElementL() completed"));
		aLog->Log(_L("EMS information element added"));
		aLog->Log(_L("Add EMS information elements == PASS"));
		}
	
	CleanupStack::PopAndDestroy(element);
	rfServer.Close();
	return result;	
	}
*/	
// -----------------------------------------------------------------------------
// TestGetEMSInformationElements
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetEMSInformationElements(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling GetEMSInformationElementsL()"));

	//const RPointerArray< const CEmsInformationElement > &GetEMSInformationElementsL() const
	RPointerArray<const CEmsInformationElement> arrayEmsInfo;
	TRAPD( result, arrayEmsInfo = aMessage.GetEMSInformationElementsL());
	
	if(result != KErrNone)
		{
		aLog->Log(_L("Leave occured: error code: %d"), result);
		}
	else
		{
		aLog->Log(_L("GetEMSInformationElementsL() completed"));
		aLog->Log(_L("EMS information elements fetched"));
		aLog->Log(_L("Get EMS information elements ==  PASS"));
		}

	return result;	
	}
	
// -----------------------------------------------------------------------------
// TestRemoveEMSInformationElements
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestRemoveEMSInformationElements(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling RemoveEMSInformationElementsL()"));
	
	//RPointerArray< CEmsInformationElement > *RemoveEMSInformationElementsL(const TUint aStartPosition, const TSmsId aEmsId);
	RPointerArray<CEmsInformationElement>* arrayEmsInfo = new RPointerArray<CEmsInformationElement>(5);
	TRAPD( result, arrayEmsInfo = aMessage.RemoveEMSInformationElementsL(0, CEmsInformationElement::ESmsIEIConcatenatedShortMessages8BitReference));
	
	if(result != KErrNone)
		{
		aLog->Log(_L("Leave occured: error code: %d"), result);
		}
	else
		{
		aLog->Log(_L("RemoveEMSInformationElementsL() completed"));
		aLog->Log(_L("EMS information elements removed"));
		aLog->Log(_L("Remove EMS information elements  PASS"));
		}

	delete arrayEmsInfo;
	return result;	
	}
	
// -----------------------------------------------------------------------------
// TestRemoveEMSInformationElement
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestRemoveEMSInformationElement(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling RemoveEMSInformationElementL()"));

	//CEmsInformationElement *RemoveEMSInformationElementL(const TUint aStartPosition, const TSmsId aEmsId)
	TRAPD( result, CEmsInformationElement* removedElement = aMessage.RemoveEMSInformationElementL(0, CEmsInformationElement::ESmsIEIConcatenatedShortMessages8BitReference));
	
	if(result != KErrNone)
		{
		aLog->Log(_L("Leave occured: error code: %d"), result);
		}
	else
		{
		aLog->Log(_L("RemoveEMSInformationElementL() completed"));
		aLog->Log(_L("EMS information element removed"));
		aLog->Log(_L("Remove EMS information element  PASS"));
		}

	return result;	
	}
	
// -----------------------------------------------------------------------------
// TestResetEMS
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestResetEMS(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling ResetEMSL()"));
	
	//void ResetEMSL();
	TRAPD( result, aMessage.ResetEMSL());
		
	if(result != KErrNone)
		{
		aLog->Log(_L("Leave occured: error code: %d"), result);
		}
	else
		{
		aLog->Log( _L("ResetEMSL() completed"));
		aLog->Log (_L("EMS information element successfully reseted"));
		aLog->Log( _L("Reset EMS == PASS"));
		}
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestCopyEMSElements
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestCopyEMSElementsL(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling CopyEmsElementsL()"));
	
	RFs rfServer; 
    User::LeaveIfError(rfServer.Connect()); 
    
    CCnvCharacterSetConverter* characterSetConverter = CCnvCharacterSetConverter::NewL(); 
    CSmsBuffer* smsBuffer = CSmsBuffer::NewL(); 
	CSmsMessage* message = CSmsMessage::NewL(rfServer, CSmsPDU::ESmsDeliver, smsBuffer ); 	

	//void CopyEmsElementsL(CSmsMessage &aToMessage) const
	TRAPD( result, aMessage.CopyEmsElementsL(*message));
	
	if(result != KErrNone)
		{
		aLog->Log(_L("Leave occured: error code: %d"), result);
		}
	else
		{
		aLog->Log(_L("CopyEmsElementsL() completed"));
		aLog->Log(_L("EMS elements copied successfully"));
		aLog->Log(_L("Copy EMS elements == PASS"));
		}
	
	delete message;
	rfServer.Close();
	
	return result;	
	}
	
// -----------------------------------------------------------------------------
// TestEncodeIntoSinglePDU
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestEncodeIntoSinglePDUL(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling EncodeIntoSinglePDUL()"));
	
	//TBool EncodeIntoSinglePDUL(CArrayFix< TGsmSms > &aSmsArray);
	CArrayFix<TGsmSms>* singlePDU = new (ELeave) CArrayFixFlat<TGsmSms>(10);
	TRAPD( result, TBool res = aMessage.EncodeIntoSinglePDUL(*singlePDU));

	if(result != KErrNone)
		{
		aLog->Log(_L("Leave occured: error code: %d"), result);
		}
	else
		{
		aLog->Log( _L("EncodeIntoSinglePDUL() completed"));
		aLog->Log (_L("Encoded into single PDU successfully"));
		aLog->Log( _L("Get is email header  == PASS"));
		}
	
	delete singlePDU;
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestAddSlot
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestAddSlot(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling AddSlotL()"));
	
	TGsmSmsSlotEntry slotEntry;
	TRAPD( result, aMessage.AddSlotL(slotEntry));
	
	if(result != KErrNone)
		{
		aLog->Log(_L("Leave occured: error code: %d"), result);
		}
	else
		{
		aLog->Log(_L("AddSlotL() completed"));
		aLog->Log(_L("Slot added successfully"));
		aLog->Log(_L("Add slot == PASS"));
		}

	return result;	
	}
	
// -----------------------------------------------------------------------------
// TestMatchSlots
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestMatchSlotsL(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling MatchSlots()"));
	TInt result = KErrNone;
	
	const CArrayFixFlat<TGsmSmsSlotEntry>* slotArray = new(ELeave) CArrayFixFlat<TGsmSmsSlotEntry>(5);
	//TBool MatchSlots(const CArrayFixFlat<TGsmSmsSlotEntry>& aSlotArray);
	TBool match = aMessage.MatchSlots(*slotArray);
	
	aLog->Log(_L("MatchSlots() Completed"));
	aLog->Log(_L("Slots matched successfully"));
	aLog->Log(_L("Match Slots == PASS"));
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestAddEmailHeader
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestAddEmailHeader(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling AddEmailHeader()"));
	
	const TBufC<24> header(_L("EMail Header"));
	TBufC<64> body(_L("EMail Body"));
	//void AddEmailHeaderL(const TDesC& aEmailHeader,const TDesC& aEmailBody);
	TRAPD( result, aMessage.AddEmailHeaderL(header, body));
	if(result != KErrNone)
		{
		aLog->Log(_L("Leave occured: error code: %d"), result);
		}
	else
		{
		aLog->Log(_L("AddEmailHeaderL() completed"));
		aLog->Log(_L("Email header added successfully"));
		aLog->Log(_L("Add email header == PASS"));
		}

	return result;	
	}
	
// -----------------------------------------------------------------------------
// TestGetIsEmailHeader
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetIsEmailHeader(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling IsEmailHeader()"));
	
	TInt result = KErrNone;
	
	//TBool IsEmailHeader() const
	TBool res = aMessage.IsEmailHeader();
	
	aLog->Log( _L("IsEmailHeader() completed"));
	aLog->Log (_L("result data: is e-mail header : %d"), res);
	aLog->Log( _L("Get is email header  == PASS"));

	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetEmailHeader
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetEmailHeaderL(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling GetEmailHeaderL()"));
	
	HBufC* emailHeader	= HBufC::NewL(1024);
	HBufC* emailBody	= HBufC::NewL(1024);
	TBool res;
	//TBool GetEmailHeaderL(HBufC **aEmailHeader, HBufC **aEmailBody);
	TRAPD( result, res = aMessage.GetEmailHeaderL(&emailHeader, &emailBody));
	
	if( res && (result == KErrNone) )
		{
		aLog->Log( _L("GetEmailHeaderL() completed"));
		aLog->Log (_L("result data: e-mail header: %s"), emailHeader);
		aLog->Log (_L("result data: e-mail body: %s"), emailBody);		
		aLog->Log( _L("Get email header == PASS"));
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get email header == FAIL"));
		}
		
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestSetIs16BitConcatenation
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetIs16BitConcatenation(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling Set16BitConcatenation()"));
	
	TInt result = KErrNone;
	
	//void Set16BitConcatenation(TBool aIs16BitConcatenation)
	aMessage.Set16BitConcatenation(ETrue);
	
	if( aMessage.Is16BitConcatenation() )
		{
		aLog->Log( _L("Set16BitConcatenation() completed"));
		aLog->Log (_L("16 bit concatenation flag stored successfully"));
		aLog->Log( _L("Set is 16 bit concatenation  == PASS"));
		}
	else
		{
		aLog->Log( _L("Set is 16 bit concatenation  == FAIL"));		
		}

	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetIs16BitConcatenation
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetIs16BitConcatenation(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling Is16BitConcatenation()"));
	
	TInt result = KErrNone;
	
	//TBool Is16BitConcatenation() const
	TBool res = aMessage.Is16BitConcatenation();
	
	aLog->Log( _L("Is16BitConcatenation() completed"));
	aLog->Log (_L("result data: 16 bit concatenation flag : %d"), res);
	aLog->Log( _L("Get is 16 bit concatenation == PASS"));

	return result;
	}
	
// -----------------------------------------------------------------------------
// TestUpdateSlots
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestUpdateSlotsL(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling UpdateSlotsL()"));

	TInt8 storeid = CSmsMessage::ESmsSIMStorage;
	TBuf8<128> slot_buffer;
	TBufC<32> file(_L("c:\\SmsSlots"));
	CArrayFixFlat<TGsmSmsSlotEntry>* slot = new(ELeave) CArrayFixFlat<TGsmSmsSlotEntry>(5);
	RFs session;
	RFileWriteStream write;
	RFileReadStream read;
	
	User::LeaveIfError( session.Connect() );
	write.Create(session, file, EFileWrite);
	TInt err = write.Open(session, file, EFileWrite);
	
	TInt size = sizeof(slot);
	write.WriteUint8L(storeid);
	write.WriteL((TUint16*)slot, size);
	write.CommitL();
	write.Close();
	TInt erro = read.Open(session, file, EFileRead);
	
	read.ReadL(slot_buffer, size+1);
	//void UpdateSlotsL(TDesC8& aBuf);
	TRAPD( result, aMessage.UpdateSlotsL(slot_buffer));
	
	read.Close();
	session.Delete(file);
	session.Close();
	
	if(result != KErrNone)
		{
		aLog->Log(_L("Leave occured: error code: %d"), result);
		}
	else
		{
		aLog->Log(_L("UpdateSlotsL() completed"));
		aLog->Log(_L("Slot information updated successfully"));
		aLog->Log(_L("Update slots == PASS"));
		}
	return result;
	}

// -----------------------------------------------------------------------------
// TestGetEncodingInfoL
// 
// -----------------------------------------------------------------------------

LOCAL_C TInt TestGetEncodingInfoL(CStifLogger* aLog, CSmsMessage& aMessage)
{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling GetEncodingInfoL()"));
	
	TInt pdus =1;
	TInt unconvertedchars=0;
	TInt downgradedchars = 0;
	TInt freeudunitsinlastfreepdu = 0;
	
	aMessage.GetEncodingInfoL(pdus, unconvertedchars, downgradedchars, freeudunitsinlastfreepdu);
	
	return KErrNone;
}

// -----------------------------------------------------------------------------
// TestSetAlternative7bitEncoding
// 
// -----------------------------------------------------------------------------

LOCAL_C TInt TestSetAlternative7bitEncoding(CStifLogger* aLog, CSmsMessage& aMessage)
{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetAlternative7bitEncoding()"));
	
	
	TInt ret = aMessage.SetAlternative7bitEncoding(ESmsEncodingNone);
	TSmsEncoding id = aMessage.Alternative7bitEncoding();
	
	return ret;
}

LOCAL_C TInt TestGetIsSupported2(CStifLogger* aLog,CSmsMessage& aMessage)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling IsSupported2L()"));
	
	//TBool IsSupportedL(const TDesC &aDes, TInt &aNumberOfUnconvertibleCharacters, TInt &aIndexOfFirstUnconvertibleCharacter)
	TBufC<50> testBuffer = _L("Nokia$123has*some%employees");
	TInt numUnconvertable;
	TInt posFirstUnconvertable;
	TInt numreqAlternativeEncoding;
	TInt numDowngradedChars;
	TBool res = 0;
	TRAPD( result, res = aMessage.IsSupportedL(testBuffer, numUnconvertable, numDowngradedChars, numreqAlternativeEncoding, posFirstUnconvertable));
	
	if(result != KErrNone)
		{
		aLog->Log(_L("Leave occured: error code: %d"), result);
		}
	else
		{
		aLog->Log(_L("IsSupported2L() completed"));
		aLog->Log(_L("result data: is supported: %d"), res);
		aLog->Log(_L("Get is supported == PASS"));
		}
	return result;	
	}
//----------------------------------------------------------------
// TestConstructionTGsmSms
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestConstructionTGsmSms_PduL(CStifLogger* aLog, CSmsPDU& pdu)	
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling CSmsPDU::NewL(TGsmSms)"));
	TInt result = KErrNone;
	
	RFs session;
	User::LeaveIfError(session.Connect());
	TGsmSms sms;
	pdu.EncodeMessagePDUL( sms );
	CCnvCharacterSetConverter* converter = CCnvCharacterSetConverter::NewL();
	CleanupStack::PushL(converter);
	
	//static CSmsPDU* NewL(const TGsmSms& aGsmSms,CCnvCharacterSetConverter& aCharacterSetConverter
	//,RFs& aFs,TBool aIsRPError=EFalse,TBool aIsMobileTerminated=ETrue);
	CSmsPDU* PDU = CSmsPDU::NewL(sms, *converter, session, ETrue, EFalse);
	CleanupStack::PushL(PDU);
	
	if( PDU != NULL)
		{
		aLog->Log(_L("CSmsPDU::NewL(TGsmSms) Completed"));
		aLog->Log(_L("CSmsPDU::NewL(TGsmSms) == PASS"));
		}
	else
		{
		result = KErrGeneral;
		aLog->Log(_L("CSmsPDU::NewL(TGsmSms) == FAIL"));	
		}
	   
	CleanupStack::PopAndDestroy(2);
	session.Close();
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestConstructionStream
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestConstructionStreamL(CStifLogger* aLog, CSmsPDU& PDU)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling CSmsPDU::NewL(RReadStream)"));
	TInt result = KErrNone;
	
	RFs session;
    User::LeaveIfError(session.Connect());
	TBufC<64> storename = _L("C:\\CSmsPDU_Construction");
	RFileWriteStream write;
	RFileReadStream read;
	CCnvCharacterSetConverter* charSet = CCnvCharacterSetConverter::NewL();
	write.Create(session, storename, EFileWrite);
	TInt erro = write.Open(session, storename, EFileWrite);
	PDU.ExternalizeL( write );
	write.CommitL();
	write.Close();
	
	erro = read.Open(session, storename, EFileRead);
	CSmsPDU* aPDU = CSmsPDU::NewL( read, *charSet, session);
	read.Close();
	//now delete the store
	TInt err = session.Delete(storename);
	session.Close();
	
	if( aPDU != NULL)
		{
		aLog->Log(_L("CSmsPDU::NewL(RReadStream) Completed"));
		aLog->Log(_L("CSmsPDU::NewL(RReadStream) == PASS"));
		}
	else
		{
		result = KErrGeneral;
		aLog->Log(_L("CSmsPDU::NewL(RReadStream) == FAIL"));
		}
	
	delete aPDU;
	delete charSet;
	return result;
	}	

// -----------------------------------------------------------------------------
// TestGetType
// Gets the PDU type
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetType (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling Type ()"));
	TInt result = KErrNone;
	 
	// inline TSmsPDUType Type() const
	CSmsPDU::TSmsPDUType checkres = aSmsPdu.Type ();
	
	if( checkres == CSmsPDU::ESmsDeliver)
		{
		aLog->Log( _L("Type() completed"));
		aLog->Log (_L("Result data:type: %d"),checkres);
		aLog->Log( _L("Get type == PASS"));
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get type == FAIL"));	
		}
		
	return result;
	}

// -----------------------------------------------------------------------------
// TestExternalizeL
// Externalises the object
// -----------------------------------------------------------------------------
LOCAL_C TInt TestExternalizeL (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling ExternalizeL()"));
	
	RFs session;
    User::LeaveIfError(session.Connect());
	TBufC<64> storename = _L("C:\\SMSGSMUtilities_CSmsPDU");
	RFileWriteStream write;
	
	write.Create(session, storename, EFileWrite);
	TInt err = write.Open(session, storename, EFileWrite);
	
	//IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	TRAPD( result, aSmsPdu.ExternalizeL( write ));
	
	write.CommitL();
	write.Close();
	
	session.Close();
	if( result == KErrNone )
		{
		aLog->Log( _L("ExternalizeL() completed"));
		aLog->Log( _L("Data externalized successfully"));
		aLog->Log( _L("Externalize == PASS"));
		}
	else
		aLog->Log( _L("Externalize == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestEncodeMessagePDUs
// Encodes a TGsmSms for the given type of CSmsPDU
// -----------------------------------------------------------------------------
LOCAL_C TInt TestEncodeMessagePDUs (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling EncodeMessagePDUsL()"));
	TGsmSms testSms;
	
	// IMPORT_C void EncodeMessagePDUL(TGsmSms &aGsmSms) const
	TRAPD(result, aSmsPdu.EncodeMessagePDUL (testSms));
	
	if( result == KErrNone)
	{
		aLog->Log( _L("EncodeMessagePDUsL() completed"));
		aLog->Log( _L("Message PDUs encoded successfully"));
		aLog->Log( _L("Encode message PDUs == PASS"));
		
	}
	else
		aLog->Log( _L("Encode message PDUs == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestGetServiceCenterAddress
// Gets the service center address
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetServiceCenterAddress (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling ServiceCenterAddress()"));
	
	TInt result = KErrNone;
	TPtrC address = _L("Test String");
				
	// IMPORT_C TPtrC ServiceCenterAddress() const
	TPtrC checkres = aSmsPdu.ServiceCenterAddress ();
	
	if(!checkres.Compare (address))
	{
		aLog->Log( _L("GetServiceCenterAddressL() completed"));
		aLog->Log (_L("Result data:address: %s"),checkres.Ptr());
		aLog->Log( _L("Get service center address == PASS"));
	}
	else
		aLog->Log( _L("Get service center address == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetServiceCenterAddress
// Sets the service center address
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetServiceCenterAddress (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetServiceCenterAddressL()"));

	TPtrC address = _L("Test String");
		
	// IMPORT_C void SetServiceCenterAddressL(const TDesC &aAddress);
	TRAPD(result, aSmsPdu.SetServiceCenterAddressL (address));
	
	if(result == KErrNone)
	{
		aLog->Log( _L("SetServiceCenterAddressL() completed"));
		aLog->Log( _L("Service center address successfully stored"));
		aLog->Log( _L("Set service center address == PASS"));
	}
	else
		aLog->Log( _L("Set service center address == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestGetParsedServiceCenterAddress
// Gets the service center address in a TGsmSmsTelNumber object
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetParsedServiceCenterAddress (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling ParsedServiceCenterAddress()"));
	
	TInt result = KErrNone;
	TGsmSmsTelNumber testTelNo;
	_LIT(str,"9945563472");
	TBuf<20> telno (str);
	
	
	// IMPORT_C void ParsedServiceCenterAddress(TGsmSmsTelNumber 
	//     &aParsedAddress) const
	aSmsPdu.ParsedServiceCenterAddress (testTelNo);
	
	if(!(testTelNo.iTelNumber).Compare (telno))
	{
		aLog->Log( _L("ParsedServiceCenterAddress() completed"));
		aLog->Log (_L("result data:parsed address: %s"),testTelNo.iTelNumber.Ptr());
		aLog->Log( _L("Get parsed service center address == PASS"));
	}
	else
		aLog->Log( _L("Get parsed service center address == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetParsedServiceCenterAddress
// Sets the service center address in a TGsmSmsTelNumber object
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetParsedServiceCenterAddress (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetParsedServiceCenterAddressL()"));
	
	TGsmSmsTelNumber testTelNo;
	_LIT(str,"9945563472");
	TBuf<20> telno (str);
	testTelNo.iTelNumber = telno;

	
	// IMPORT_C void SetParsedServiceCenterAddressL(const TGsmSmsTelNumber
	//    &aParsedAddress);
	TRAPD(result, aSmsPdu.SetParsedServiceCenterAddressL (testTelNo));
	
	if(result == KErrNone)
	{
		aLog->Log( _L("SetParsedServiceCenterAddressL() completed"));
		aLog->Log( _L("Parsed address successfully stored"));
		aLog->Log( _L("Set parsed service center address == PASS"));
	}
	else
		aLog->Log( _L("Set parsed service center address == FAIL"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestGetToFromAddress
// Gets the "to from" address
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetToFromAddress (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling ToFromAddress()"));
	
	TInt result = KErrNone;
	_LIT(str,"TestAddress");
	TBufC<20> testadd (str);
	
	// IMPORT_C TPtrC ToFromAddress() const
	TPtrC checkres = aSmsPdu.ToFromAddress();
	
	if( ! checkres.Compare (testadd))
	{
		aLog->Log( _L("ToFromAddress() completed"));
		aLog->Log(_L("Result data:to from address: %s"),checkres.Ptr());
		aLog->Log( _L("Get to from address == PASS"));
	}
	else
		aLog->Log( _L("Get to from address == FAIL"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestSetToFromAddress
// Gets the "to from" address
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetToFromAddress (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetToFromAddressL()"));
	
	_LIT(str,"TestAddress");
	TBufC<20> testadd (str);
	
	// IMPORT_C void SetToFromAddressL(const TDesC &aAddress)
	TRAPD( result, aSmsPdu.SetToFromAddressL (testadd));
	
	if(result == KErrNone)
	{
		aLog->Log( _L("SetToFromAddressL() completed"));
		aLog->Log( _L("To from addresses successfully stored"));
		aLog->Log( _L("Set to from address == PASS"));
	}
	else
		aLog->Log( _L("Set to from address == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestGetParsedToFromAddress
// Gets the "to from" in a TGsmSmsTelNumber object
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetParsedToFromAddress (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling ParsedToFromAddress()"));
	
	TInt result = KErrNone;	
	TGsmSmsTelNumber testTelNo;
	_LIT(str,"9945563472");
	TBuf<20> telno (str);
	
	// IMPORT_C void ParsedToFromAddress(TGsmSmsTelNumber &aParsedAddress) const
	aSmsPdu.ParsedToFromAddress (testTelNo);
	
	if(!(testTelNo.iTelNumber).Compare (telno))
	{
		aLog->Log( _L("ParsedToFromAddress() completed"));
		_LIT(tempVal,"result data:parsed to from address: %s");
		aLog->Log (tempVal,testTelNo.iTelNumber.Ptr());
		aLog->Log( _L("Get parsed to from address == PASS"));
	}
	else
		aLog->Log( _L("Get parsed to from address == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetParsedToFromAddress
// Sets the "to from" with a TGsmSmsTelNumber object
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetParsedToFromAddress (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetParsedToFromAddressL()"));
	
	TGsmSmsTelNumber testTelNo;
	_LIT(str,"9945563472");
	TBuf<20> telno (str);
	testTelNo.iTelNumber = telno;

	
	// IMPORT_C void SetParsedToFromAddressL(const TGsmSmsTelNumber 
	//     &aParsedAddress);
	TRAPD( result, aSmsPdu.SetParsedToFromAddressL (testTelNo));
	
	if(result == KErrNone)
	{
		aLog->Log( _L("SetParsedToFromAddressL() completed"));
		aLog->Log( _L("Parsed to from addresses successfully stored"));
		aLog->Log( _L("Set parsed to from address == PASS"));
	}
	else
		aLog->Log( _L("Set parsed to from address == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestGetBits7To4
// Gets bits 7 to 4 on the data coding scheme
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetBits7To4 (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling Bits7To4()"));
	
	TInt result = KErrNone;
	TSmsDataCodingScheme::TSmsDCSBits7To4 bitsVal;
	
	// IMPORT_C TSmsDataCodingScheme::TSmsDCSBits7To4 Bits7To4() const
	bitsVal = aSmsPdu.Bits7To4 ();
	
	if(bitsVal == TSmsDataCodingScheme::ESmsDCSTextUncompressedWithNoClassInfo)
	{
		aLog->Log( _L("Bits7To4() completed"));
		_LIT(tempVal,"result data:bits 7 to 4: %d");
		aLog->Log (tempVal,bitsVal);
		aLog->Log( _L("Get bits 7 to 4 == PASS"));
	}
	else
		aLog->Log( _L("Get bits 7 to 4 == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetBits7To4
// Sets bits 7 to 4 on the data coding scheme
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetBits7To4 (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetBits7To4()"));
	
	TInt result = KErrNone;
	TSmsDataCodingScheme::TSmsDCSBits7To4 bitsVal (TSmsDataCodingScheme::
	    ESmsDCSTextUncompressedWithNoClassInfo);
	
	// IMPORT_C void SetBits7To4(TSmsDataCodingScheme::TSmsDCSBits7To4 
	//     aBits7To4)
	aSmsPdu.SetBits7To4 (bitsVal);
	
	aLog->Log( _L("SetBits7To4() completed"));
	aLog->Log( _L("Bits 7 to 4 stored successfully"));
	aLog->Log( _L("Set bits 7 to 4 == PASS"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestGetAlphabet
// Gets the alphabet encoded in the data coding scheme
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetAlphabet (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling Alphabet()"));
	
	TInt result = KErrNone;
	TSmsDataCodingScheme::TSmsAlphabet testAlphabet;
	
	// IMPORT_C TSmsDataCodingScheme::TSmsAlphabet Alphabet() const
	testAlphabet = aSmsPdu.Alphabet();
	
	if(testAlphabet == TSmsDataCodingScheme::ESmsAlphabet7Bit)
	{
		aLog->Log( _L("Alphabet() completed"));
		_LIT(tempVal,"result data:alphabet: %d");
		aLog->Log (tempVal,testAlphabet);
		aLog->Log( _L("Get alphabet == PASS"));
	}
	else
		aLog->Log( _L("Get alphabet == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetAlphabet
// Sets the alphabet encoded in the data coding scheme
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetAlphabet (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetAlphabet()"));
	
	TInt result = KErrNone;
	TSmsDataCodingScheme::TSmsAlphabet testAlphabet (TSmsDataCodingScheme::
	    ESmsAlphabet7Bit);
	
	// IMPORT_C void SetAlphabet(TSmsDataCodingScheme::TSmsAlphabet aAlphabet)
	aSmsPdu.SetAlphabet (testAlphabet);
	
	aLog->Log( _L("SetAlphabet() completed"));
	aLog->Log( _L("Alphabet stored successfully"));
	aLog->Log( _L("Set alphabet == PASS"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestGetClass
// Gets the GSM SMS PDU class in the data coding scheme
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetClass (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling Class()"));
	
	TInt result = KErrNone;
	TSmsDataCodingScheme::TSmsClass testClass (TSmsDataCodingScheme::
	    ESmsClass0);
	
	//TBool Class(TSmsDataCodingScheme::TSmsClass &aClass) const
	TBool checkres = aSmsPdu.Class (testClass);
	
	if( checkres )
	{
		aLog->Log( _L("Class() completed"));
		aLog->Log(_L("Result data:class: %d"),testClass);
		aLog->Log( _L("Get class == PASS"));
	}
	else
		aLog->Log( _L("Get class == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetClass
// Sets the GSM SMS PDU class in the data coding scheme
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetClass (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetClass()"));
	
	TInt result = KErrNone;
	TSmsDataCodingScheme::TSmsClass testClass (TSmsDataCodingScheme::ESmsClass0);
	
	//void SetClass(TBool aClassDefined, TSmsDataCodingScheme::TSmsClass aClass)
	aSmsPdu.SetClass (ETrue, testClass);
	
	aLog->Log( _L("SetClass() completed"));
	aLog->Log( _L("Class stored successfully"));
	aLog->Log( _L("Set class == PASS"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestGetTextCompressed
// True if Text Compressed is encoded in the data coding scheme
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetTextCompressed (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling TextCompressed()"));
	
	TInt result = KErrNone;
	
	// IMPORT_C TBool TextCompressed() const
	TBool checkres = aSmsPdu.TextCompressed ();
	
	if( checkres )
	{
		aLog->Log( _L("TextCompressed() completed"));
		_LIT(tempVal,"result data:text compressed: %d");
		aLog->Log (tempVal,checkres);
		aLog->Log( _L("Get text compresed == PASS"));
	}
	else
		aLog->Log( _L("Get text compresed == FAIL"));
	
	return result;
	}



// -----------------------------------------------------------------------------
// TestSetTextCompressed
// Set to encode Text Compressed in the data coding scheme
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetTextCompressed (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetTextCompressed()"));
	
	TInt result = KErrNone;
	
	// IMPORT_C void SetTextCompressed(TBool aCompressed);
	aSmsPdu.SetTextCompressed (ETrue);
	
	aLog->Log( _L("SetTextCompressed() completed"));
	aLog->Log( _L("Text compressed flag successfully stored"));
	aLog->Log( _L("Set text compresed == PASS"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestGetIndicationState
// Gets the Indication State encoded in the data coding scheme.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetIndicationState (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling IndicationState()"));
	
	TInt result = KErrNone;
	TSmsDataCodingScheme::TSmsIndicationState testState;
	
	// IMPORT_C TSmsDataCodingScheme::TSmsIndicationState IndicationState() const
	testState = aSmsPdu.IndicationState (); 
	
	if(testState == TSmsDataCodingScheme::ESmsIndicationInactive)
	{
		aLog->Log( _L("IndicationState() completed"));
		_LIT(tempVal,"result data:indication state: %d");
		aLog->Log (tempVal,testState);
		aLog->Log( _L("Get indication state == PASS"));
	}
	else
		aLog->Log( _L("Get indication state == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetIndicationState
// Sets the Indication State encoded in the data coding scheme.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetIndicationState (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetIndicationState()"));
	
	TInt result = KErrNone;
	TSmsDataCodingScheme::TSmsIndicationState testState (TSmsDataCodingScheme::
	    ESmsIndicationInactive);
	
	// IMPORT_C void SetIndicationState(TSmsDataCodingScheme::
	//    TSmsIndicationState aState);
	aSmsPdu.SetIndicationState (testState);
	
	aLog->Log( _L("SetIndicationState() completed"));
	aLog->Log( _L("Indication state stored successfully"));
	aLog->Log( _L("Set indication state == PASS"));

	return result;
	}


// -----------------------------------------------------------------------------
// TestGetIndicationType 
// Gets the Indication Type encoded in the data coding scheme.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetIndicationType (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling IndicationType()"));
	
	TInt result = KErrNone;
	TSmsDataCodingScheme::TSmsIndicationType testIndicationType;
	
	//TSmsDataCodingScheme::TSmsIndicationType IndicationType() const
	testIndicationType = aSmsPdu.IndicationType ();
	
	if(testIndicationType == TSmsDataCodingScheme::ESmsVoicemailMessageWaiting)
	{
		aLog->Log( _L("IndicationType() completed"));
		_LIT(tempVal,"result data:indication type: %d");
		aLog->Log (tempVal,testIndicationType);
		aLog->Log( _L("Get indication type == PASS"));
	}
	else
		aLog->Log( _L("Get indication type == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetIndicationType
// Sets the Indication Type encoded in the data coding scheme.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetIndicationType (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetIndicationType()"));
	
	TInt result = KErrNone;
	TSmsDataCodingScheme::TSmsIndicationType testIndicationType (
	   TSmsDataCodingScheme::ESmsVoicemailMessageWaiting);
	
	//void SetIndicationType(TSmsDataCodingScheme::TSmsIndicationType aType);
    aSmsPdu.SetIndicationType (testIndicationType);
    
   	aLog->Log( _L("SetIndicationType() completed"));
   	aLog->Log( _L("Indication type stored successfully"));
   	aLog->Log( _L("Set indication type == PASS"));
    
    return result;
	}


// -----------------------------------------------------------------------------
// TestGetTextConcatenated
// Tests if the PDU is part of a concatenated message
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetTextConcatenated (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling TextConcatenated()"));
	
	TInt result = KErrNone;
	
	// IMPORT_C TBool TextConcatenated(TBool *aIs16Bit=0) const
	TBool checkres = aSmsPdu.TextConcatenated ();
	
	if( checkres )
	{
		aLog->Log( _L("TextConcatenated() completed"));
		_LIT(tempVal,"result data:text concatenated: %d");
		aLog->Log (tempVal,checkres);
		aLog->Log( _L("Get text concatenated == PASS"));
	}
	else
		aLog->Log( _L("Get text concatenated == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetTextConcatenated
// Tests if the PDU is part of a concatenated message.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetTextConcatenated (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetTextConcatenatedL()"));
	
    // IMPORT_C void SetTextConcatenatedL(TBool aConcatenated, 
    //     TBool aIs16Bit=EFalse);
    TRAPD( result, aSmsPdu.SetTextConcatenatedL (ETrue));
    
    if(result == KErrNone)
    {
    	aLog->Log( _L("SetTextConcatenatedL() completed"));
    	aLog->Log( _L("Text concatenated flag successfully stored"));
    	aLog->Log( _L("Set text concatenated == PASS"));
    }
    else
    	aLog->Log( _L("Set text concatenated == FAIL"));
    
    return result;
	}

// -----------------------------------------------------------------------------
// TestGetConcatenatedMessageReference
// Gets the reference contained in the Concatenation Information Element
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetConcatenatedMessageReference (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling ConcatenatedMessageReference()"));
	
	TInt result = KErrNone;
	
	// IMPORT_C TInt ConcatenatedMessageReference() const
	TInt checkres = aSmsPdu.ConcatenatedMessageReference ();
	
	if(checkres == 1)
	{
		aLog->Log( _L("ConcatenatedMessageReference() completed"));
		_LIT(tempVal,"result data:concatenated message reference: %d");
		aLog->Log (tempVal, checkres);
		aLog->Log( _L("Get concatenated message reference == PASS"));
	}
	else
		aLog->Log( _L("Get concatenated message reference == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetConcatenatedMessageReference
// Sets the reference contained in the Concatenation Information Element
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetConcatenatedMessageReference (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetConcatenatedMessageReference()"));
	
	TInt result = KErrNone;
	TInt SetVal = 1;
	
	// IMPORT_C void SetConcatenatedMessageReference(TInt aReference)
	aSmsPdu.SetConcatenatedMessageReference (SetVal);
	
	aLog->Log( _L("SetConcatenatedMessageReference() completed"));
	aLog->Log( _L("Concatenated message reference stored successfully"));
	aLog->Log( _L("Set concatenated message reference == PASS"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestGetNumberOfConcatenatedMessageL
// Gets the number of PDU's in a Concatenated Message.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetNumberOfConcatenatedMessageL (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling NumConcatenatedMessagePDUs()"));
	
	TInt result = KErrNone;
	
	// IMPORT_C TInt NumConcatenatedMessagePDUs() const
	TInt checkres = aSmsPdu.NumConcatenatedMessagePDUs ();
	
	if(checkres == 10)
	{
		aLog->Log( _L("NumConcatenatedMessagePDUs() completed"));
	    _LIT(tempVal,"result data:number of concatenated PDUs: %d");
	    aLog->Log (tempVal,checkres);
	    aLog->Log( _L("Get number of concatenated message PDUs == PASS"));
	}
	else
		aLog->Log( _L("Get number of concatenated message PDUs == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetNumberOfConcatenatedMessageL
// Sets the number of PDU's in a Concatenated Message.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetNumberOfConcatenatedMessageL (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetNumConcatenatedMessagePDUs()"));
	
	TInt result = KErrNone;
	TInt setVal = 10;
	
	// IMPORT_C void SetNumConcatenatedMessagePDUs(TInt aNum);
	aSmsPdu.SetNumConcatenatedMessagePDUs (setVal);
	
	aLog->Log( _L("SetNumConcatenatedMessagePDUs() completed"));
	aLog->Log( _L("Number of concatenated PDUs stored successfully"));
	aLog->Log( _L("Set number of concatenated message PDUs == PASS"));

	return result;
	}


// -----------------------------------------------------------------------------
// TestGetConcatenatedMessagePDUIndex
// Gets the index of the PDU within the Concatenated Message.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetConcatenatedMessagePDUIndex (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling ConcatenatedMessagePDUIndex()"));
	
	TInt result = KErrNone;
	
	// IMPORT_C TInt ConcatenatedMessagePDUIndex() const;
	TInt checkres = aSmsPdu.ConcatenatedMessagePDUIndex ();
	
	if(checkres == 5)
	{
		aLog->Log( _L("ConcatenatedMessagePDUIndex() completed"));
		_LIT(tempVal,"result data:concatenated message PDU index: %d");
		aLog->Log (tempVal, checkres);
		aLog->Log( _L("Get concatenated message PDU index == PASS"));
	}
	else
		aLog->Log( _L("Get concatenated message PDU index == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetConcatenatedMessagePDUIndex
// Sets the index of the PDU within the Concatenated Message.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetConcatenatedMessagePDUIndex (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetConcatenatedMessagePDUIndex()"));
	
	TInt result = KErrNone;
	TInt setVal = 5;
	
	// IMPORT_C void SetConcatenatedMessagePDUIndex(TInt aIndex)
	aSmsPdu.SetConcatenatedMessagePDUIndex (setVal);
	
	aLog->Log( _L("SetConcatenatedMessagePDUIndex() completed"));
	aLog->Log( _L("Concatenated message PDU index stored successfully"));
	aLog->Log( _L("Set concatenated message PDU index == PASS"));

	return result;
	}


// -----------------------------------------------------------------------------
// TestGetApplicationPortAddressing
// Gets application port addressing information in the user data.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetApplicationPortAddressing (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling ApplicationPortAddressing()"));
	
	TInt result = KErrNone;
	TInt aDestination, aOriginator;
	
	// IMPORT_C TBool ApplicationPortAddressing(TInt &aDestination, 
	//     TInt &aOriginator, TBool *aIs16Bit=0) const
	TBool checkres = aSmsPdu.ApplicationPortAddressing (aDestination,aOriginator);
	
	if( checkres )
	{
		aLog->Log( _L("ApplicationPortAddressing() completed"));
		_LIT(tempVal,"result data:destination: %d originator: %d is 16 bit: %d");
		aLog->Log (tempVal, aDestination, aOriginator, checkres);
		aLog->Log( _L("Get application port addressing == PASS"));
	}
	else
		aLog->Log( _L("Get application port addressing == FAIL"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestSetApplicationPortAddressing
// Sets application port addressing information in the user data.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetApplicationPortAddressing (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("SetCalling ApplicationPortAddressingL()"));
	
	// IMPORT_C void SetApplicationPortAddressingL(TBool aAddressing, 
	//     TInt aDestination, TInt aOriginator, TBool aIs16Bit=EFalse)
	TRAPD( result, aSmsPdu.SetApplicationPortAddressingL (ETrue, 240,241));
	
	if(result == KErrNone)
	{
		aLog->Log( _L("SetApplicationPortAddressingL() completed"));
		aLog->Log( _L("Application port addressing settings successfully stored"));
		aLog->Log( _L("Set application port addressing == PASS"));
	}
	else
		aLog->Log( _L("Set application port addressing == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestGetPIDType
// Gets key bits 7 and 6 of the PID field.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetPIDType (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling PIDType()"));
	
	TInt result = KErrNone;
	TSmsProtocolIdentifier::TSmsPIDType testPIDType;
	
	// IMPORT_C TSmsProtocolIdentifier::TSmsPIDType PIDType() const
	testPIDType = aSmsPdu.PIDType ();
	
	if(testPIDType == TSmsProtocolIdentifier::ESmsPIDTelematicInterworking)
	{
		aLog->Log( _L("PIDType() completed"));
		_LIT(tempVal,"result data:PID type: %d");
		aLog->Log (tempVal,testPIDType);
		aLog->Log( _L("Get PID type == PASS"));
	}
	else
		aLog->Log( _L("Get PID type == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetPIDType
// Sets key bits 7 and 6 of the PID field.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetPIDType (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetPIDType()"));
	TInt result = KErrNone;
	
	TSmsProtocolIdentifier::TSmsPIDType testPIDType (TSmsProtocolIdentifier::
	    ESmsPIDShortMessageType);
	
	// IMPORT_C void SetPIDType(TSmsProtocolIdentifier::TSmsPIDType aSmsPIDType)
	aSmsPdu.SetPIDType (testPIDType);
	
	aLog->Log( _L("SetPIDType() completed"));
	aLog->Log( _L("PID type stored successfully"));
	aLog->Log( _L("Set PID type == PASS"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestGetTelematicDeviceIndicator
// Gets the Telematic device indicator from the PID field.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetTelematicDeviceIndicator (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling TelematicDeviceIndicator()"));
	
	TInt result = KErrNone;
	TSmsProtocolIdentifier::TSmsTelematicDeviceIndicator testDeviceIndicator;
	
	// IMPORT_C TSmsProtocolIdentifier::TSmsTelematicDeviceIndicator 
	//    TelematicDeviceIndicator() const
	testDeviceIndicator = aSmsPdu.TelematicDeviceIndicator ();
	
	if(testDeviceIndicator == TSmsProtocolIdentifier::ESmsNoTelematicDevice)
	{
		aLog->Log( _L("TelematicDeviceIndicator() completed"));
		_LIT(tempVal,"result data:telematic device indicator: %d");
		aLog->Log (tempVal, testDeviceIndicator);
		aLog->Log( _L("Get telematic device indicator == PASS"));
	}
	else
		aLog->Log( _L("Get telematic device indicator == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetTelematicDeviceIndicator
// Sets the Telematic device indicator from the PID field.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetTelematicDeviceIndicator (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetTelematicDeviceIndicator()"));
	TInt result = KErrNone;
	
	TSmsProtocolIdentifier::TSmsPIDType testPIDType (TSmsProtocolIdentifier::ESmsPIDTelematicInterworking);
	aSmsPdu.SetPIDType (testPIDType);

	TSmsProtocolIdentifier::TSmsTelematicDeviceIndicator testDeviceIndicator (
	    TSmsProtocolIdentifier::ESmsTelematicDevice);
	
	// IMPORT_C void SetTelematicDeviceIndicator(TSmsProtocolIdentifier::
	//     TSmsTelematicDeviceIndicator aIndicator);
	aSmsPdu.SetTelematicDeviceIndicator (testDeviceIndicator);
	
	aLog->Log( _L("SetTelematicDeviceIndicator() completed"));
    aLog->Log( _L("Telematic device indicator stored successfully"));
	aLog->Log( _L("Set telematic device indicator == PASS"));
		
	return result;
	}


// -----------------------------------------------------------------------------
// TestGetShortMessageType
// Gets the Short Message Type in the PID field.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetShortMessageType (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling ShortMessageType()"));
	
	TInt result = KErrNone;
	TSmsProtocolIdentifier::TSmsShortMessageType testMessageType;
	
	// IMPORT_C TSmsProtocolIdentifier::TSmsShortMessageType 
	//     ShortMessageType() const;
	testMessageType = aSmsPdu.ShortMessageType ();
	
	if(testMessageType == TSmsProtocolIdentifier::ESmsShortMessageType0)
	{
		aLog->Log( _L("ShortMessageType() completed"));
		_LIT(tempVal, "result data:short message type: %d");
		aLog->Log (tempVal, testMessageType);
		aLog->Log( _L("Get short message type == PASS"));
	}
	else
		aLog->Log( _L("Get short message type == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetShortMessageType
// Sets the Short Message Type in the PID field.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetShortMessageType (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetShortMessageType()"));
	TInt result = KErrNone;
	
	TSmsProtocolIdentifier::TSmsShortMessageType testMessageType (
	    TSmsProtocolIdentifier::ESmsShortMessageType0);
	
	// IMPORT_C void SetShortMessageType(TSmsProtocolIdentifier::
	//     TSmsShortMessageType aShortMessageType);
	aSmsPdu.SetShortMessageType (testMessageType);

	aLog->Log( _L("SetShortMessageType() completed"));
	aLog->Log( _L("Short message type stored successfully"));
	aLog->Log( _L("Set short message type == PASS"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestGetTelematicDeviceType
// Gets the Telematic device type in the PID field
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetTelematicDeviceType (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling TelematicDeviceType()"));
	
	TInt result = KErrNone;
	TSmsProtocolIdentifier::TSmsTelematicDeviceType testDeviceType;
	
	// IMPORT_C TSmsProtocolIdentifier::TSmsTelematicDeviceType 
	//     TelematicDeviceType() const
	testDeviceType = aSmsPdu.TelematicDeviceType ();
	
	if(testDeviceType == TSmsProtocolIdentifier::ESmsSCSpecificDevice)
	{
		aLog->Log( _L("TelematicDeviceType() completed"));
		_LIT(tempVal,"result data:telematic device type: %d");
		aLog->Log (tempVal, testDeviceType);
		aLog->Log( _L("Get telematic device type == PASS"));
	}
	else
		aLog->Log( _L("Get telematic device type == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetTelematicDeviceType
// Sets the Telematic device type in the PID field
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetTelematicDeviceType (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetTelematicDeviceType()"));
	
	TInt result = KErrNone;
	TSmsProtocolIdentifier::TSmsTelematicDeviceType testDeviceType (
	   TSmsProtocolIdentifier::ESmsSCSpecificDevice);
	
	// IMPORT_C void SetTelematicDeviceType(TSmsProtocolIdentifier::
	//    TSmsTelematicDeviceType aDeviceType);
	aSmsPdu.SetTelematicDeviceType (testDeviceType);
	
	aLog->Log( _L("SetTelematicDeviceType() completed"));
	aLog->Log( _L("Telematic device type stored successfully"));
	aLog->Log( _L("Set telematic device type == PASS"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestGetUserDataPresent
// Tests if the User Data Header Indicator is set.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetUserDataPresent (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling UserDataPresent()"));
	TInt result = KErrNone;
	
	// IMPORT_C TBool UserDataPresent() const
	TBool checkres = aSmsPdu.UserDataPresent ();
	
	if( checkres )
	{
		aLog->Log( _L("UserDataPresent() completed"));
		aLog->Log( _L("result data:user data present: %d"), checkres);
		aLog->Log( _L("Get user data present == PASS"));
	}
	else
		aLog->Log( _L("Get user data present == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetUserDataPresent
// Sets or unsets the User Data Header Indicator.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetUserDataPresent (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetUserDataPresent()"));
	
	TInt result = KErrNone;
	TBool SetVal = ETrue;
	
	// IMPORT_C void SetUserDataPresent(TBool aPresent);
	aSmsPdu.SetUserDataPresent (SetVal);
	
	aLog->Log( _L("SetUserDataPresent() completed"));
	aLog->Log( _L("User data present flag stored successfully"));
	aLog->Log( _L("Set user data present == PASS"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestGetDataCodingSchemePresent 
// Tests if data coding scheme is present.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetDataCodingSchemePresent (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling DataCodingSchemePresent()"));
	
	TInt result = KErrNone;
	
	// IMPORT_C TBool DataCodingSchemePresent() const;
	TBool checkres = aSmsPdu.DataCodingSchemePresent ();
	
	if( checkres )
	{
		aLog->Log( _L("DataCodingSchemePresent() completed"));
		aLog->Log (_L("result data:data coding scheme present: %d"),checkres);
		aLog->Log (_L("Get data coding scheme present == PASS"));
	}
	else
		aLog->Log( _L("Get data coding scheme present == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetDataCodingSchemePresent 
// Sets if data coding scheme is present.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetDataCodingSchemePresent (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetDataCodingSchemePresent()"));
	
	TInt result = KErrNone;
	TBool SetVal = ETrue;
	
	// IMPORT_C void SetDataCodingSchemePresent(TBool aPresent)
	aSmsPdu.SetDataCodingSchemePresent (SetVal);
	
	aLog->Log( _L("SetDataCodingSchemePresent() completed"));
	aLog->Log( _L("Data coding scheme present flag stored successfully"));
	aLog->Log( _L("Set data coding scheme present == PASS"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestGetProtocolIdentifierPresent
// Tests if Protocol Identifier is present.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetProtocolIdentifierPresent (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling ProtocolIdentifierPresent()"));
	
	TInt result = KErrNone;
	
	// IMPORT_C TBool ProtocolIdentifierPresent() const
	TBool checkres = aSmsPdu.ProtocolIdentifierPresent ();
	
	if( checkres )
	{
		aLog->Log( _L("ProtocolIdentifierPresent() completed"));
		_LIT(tempVal,"result data:protocol identifier present: %d");
		aLog->Log (tempVal, checkres);
		aLog->Log( _L("Get protocol identifier present == PASS"));
	}
	else
		aLog->Log( _L("Get protocol identifier present == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetProtocolIdentifierPresent
// Tests if Protocol Identifier is present.
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetProtocolIdentifierPresent (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetProtocolIdentifierPresent()"));
		
	TInt result = KErrNone;
	TBool SetVal = ETrue;
	
	// IMPORT_C void SetProtocolIdentifierPresent(TBool aPresent);
	aSmsPdu.SetProtocolIdentifierPresent (SetVal);
	
	aLog->Log( _L("SetProtocolIdentifierPresent() completed"));
	aLog->Log( _L("Protocol identifier present flag stored successfully"));
	aLog->Log( _L("Set protocol identifier present == PASS"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestGetUserData
// Gets User Data (non-const).
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetUserData (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling UserData()"));
	
	TInt result = KErrNone;
	
	// IMPORT_C CSmsUserData &UserData();
	CSmsUserData& testUserData = aSmsPdu.UserData ();
	
	aLog->Log(_L("UserData() completed"));
	aLog->Log(_L("result data:user data (body): %s"), testUserData.Body().Ptr());
	aLog->Log(_L("Get user data == PASS"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestGetUserDataConst
// Gets User Data (const).
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetUserDataConst (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling UserData()"));
	
	TInt result = KErrNone;
	
	// IMPORT_C const CSmsUserData &UserData() const
	const CSmsUserData& testUserData = aSmsPdu.UserData ();
	
	aLog->Log( _L("UserData() completed"));
	aLog->Log (_L("result data:user data (body): %s"),testUserData.Body().Ptr());
	aLog->Log( _L("Get user data == PASS"));
	
	return result;
	}

LOCAL_C TInt TestSetNationalLanguageEncodingL (CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetNationalLanguageEncodingL()"));
	
	TInt result = KErrNone;
		
	aSmsPdu.SetNationalLanguageEncodingL (ESmsEncodingNone);
	TSmsEncoding id = aSmsPdu.NationalLanguageEncoding();
	
	aLog->Log( _L("SetDataCodingSchemePresent() completed"));
	aLog->Log( _L("Data coding scheme present flag stored successfully"));
	aLog->Log( _L("Set data coding scheme present == PASS"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestSmsPDUDuplicateL
// Creates a copy of the object
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSmsPDUDuplicateL( CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SmsPDUDuplicateL()"));
	
	TInt result = KErrNone;
	
	CSmsPDU* dupObj = aSmsPdu.DuplicateL();
		
		if( dupObj )
			{
		aLog->Log(_L("TestSmsPDUDuplicateL() completed"));
		aLog->Log(_L("Object successfully created"));
		aLog->Log(_L("SmsPDUDuplicateL == PASS"));
		
		}
		else
			{
				result = KErrGeneral;
				aLog->Log(_L("SmsPDUDuplicateL == FAIL"));
			}
			return result;
	}	

// -----------------------------------------------------------------------------
// TestDecode
// -----------------------------------------------------------------------------
/*LOCAL_C TInt TestDecode(CStifLogger* aLog, CSmsPDU& aSmsPdu)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling DecodeL()"));
	
	TBufC8<16> str(KTestGsmPdu8);
	TGsmuLex8 aPduL(str);
	
	// virtual void DecodeL(TGsmuLex8 &aPdu)=0;
	TRAPD( result, aSmsPdu.DecodeL (aPdu));
	
	if(result == KErrNone)
	{
		aLog->Log( _L("DecodeL() completed"));
		aLog->Log( _L("Decode performed successfully"));
		aLog->Log( _L("Decode == PASS"));
	}
	else
		aLog->Log( _L("Decode == FAIL"));
	
	CleanupStack::Pop();
	return result;
	}
*/
// -----------------------------------------------------------------------------
// TestSetParameterIndicatorPresent
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetParameterIndicatorPresent( CStifLogger* aLog, CSmsStatusReport& aReport)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetParameterIndicatorPresent()"));
	TInt result = KErrNone;
	
	//inline void SetParameterIndicatorPresent(TBool aPresent);
	aReport.SetParameterIndicatorPresent(ETrue);
	
	aLog->Log(_L("SetParameterIndicatorPresent() completed"));
	aLog->Log(_L("Parameter indicator present flag stored successfully"));
	aLog->Log(_L("Set parameter indicator present == PASS"));
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetParameterIndicatorPresent
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetParameterIndicatorPresent( CStifLogger* aLog, CSmsStatusReport& aReport)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling ParameterIndicatorPresent()"));
	TInt result = KErrNone;
	
	//inline TBool ParameterIndicatorPresent() const;
	TBool indicator = aReport.ParameterIndicatorPresent();
	
	if( indicator )
		{
		aLog->Log(_L("ParameterIndicatorPresent() Completed"));
		aLog->Log(_L("Result data: Parameter indicator present: %d"), indicator);
		aLog->Log(_L("Get parameter indicator present == PASS"));
		}
	else
		aLog->Log(_L("Get parameter indicator present == FAIL"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestSetMoreMessagesToSend
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetMoreMessagesToSend( CStifLogger* aLog, CSmsStatusReport& aReport)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetMoreMessagesToSend()"));
	TInt result = KErrNone;
	
	//void SetMoreMessagesToSend(TBool aMore);
	aReport.SetMoreMessagesToSend(ETrue);
	
	aLog->Log(_L("SetMoreMessagesToSend() Completed"));
	aLog->Log(_L("More messages to send - flag successfully stored"));
	aLog->Log(_L("Set more messages to send == PASS"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestGetMoreMessagesToSend
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetMoreMessagesToSend( CStifLogger* aLog, CSmsStatusReport& aReport)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling MoreMessagesToSend()"));
	TInt result = KErrNone;
	
	//TBool MoreMessagesToSend() const;
	TBool msgs = aReport.MoreMessagesToSend();
	
	if(msgs)
		{
		aLog->Log(_L("MoreMessagesToSend() Completed"));
		aLog->Log(_L("Result Data:More messages to send flag: %d"), msgs);
		aLog->Log(_L("Get more messages to send == PASS"));
		}
	else
		{
		result =KErrGeneral;
		aLog->Log(_L("Get more messages to send == PASS"));
		}
			
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestSetStatusReportQualifier
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetStatusReportQualifier( CStifLogger* aLog, CSmsStatusReport& aReport)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetStatusReportQualifier()"));
	TInt result = KErrNone;
	
	TSmsFirstOctet::TSmsStatusReportQualifier qualifier = TSmsFirstOctet::ESmsStatusReportResultOfSubmit;
	//void SetStatusReportQualifier(TSmsFirstOctet::TSmsStatusReportQualifier aQualifier);
	aReport.SetStatusReportQualifier( qualifier );
	
	aLog->Log(_L("SetStatusReportQualifier() Completed"));
	aLog->Log(_L("Status report qualifier stored successfully"));
	aLog->Log(_L("Set status report qualifier == PASS"));
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetStatusReportQualifier
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetStatusReportQualifier( CStifLogger* aLog, CSmsStatusReport& aReport)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling StatusReportQualifier()"));
	TInt result = KErrNone;
	
	//TSmsFirstOctet::TSmsStatusReportQualifier StatusReportQualifier() const;
	TSmsFirstOctet::TSmsStatusReportQualifier qualifier = aReport.StatusReportQualifier();
	
	if( qualifier == TSmsFirstOctet::ESmsStatusReportResultOfSubmit )
		{
		aLog->Log(_L("StatusReportQualifier() Completed"));
		aLog->Log(_L("Result data: Status report qualifier: %d"), qualifier);
		aLog->Log(_L("Get status report qualifier == PASS"));
		}
	else
		aLog->Log(_L("Get status report qualifier == FAIL"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestGetMessageReference
// Gets the Message Reference
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetMessageReference( CStifLogger* aLog, CSmsStatusReport& aReport)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling MessageReference()"));
	TInt result = KErrNone;
	
	//IMPORT_C TInt MessageReference() const;
	TInt getRef = aReport.MessageReference();
	
	aLog->Log(_L("MessageReference() Completed"));
	aLog->Log(_L("result data:Message reference: %d"), getRef);
	aLog->Log(_L("Get Message Reference == PASS"));

	return result;
	}
	
// -----------------------------------------------------------------------------
// TestSetMessageReference
// Sets the Message Reference
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetMessageReference( CStifLogger* aLog, CSmsStatusReport& aReport)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetMessageReference()"));
	TInt result = KErrNone;
	
	TInt setRef = 1;
	//IMPORT_C void SetMessageReference(TInt aMessageReference);
	aReport.SetMessageReference(setRef);
	
	aLog->Log(_L("SetMessageReference() Completed"));
	aLog->Log(_L("Message reference successfully stored"));
	aLog->Log(_L("Set Message Reference == PASS"));

	return result;
	}
	
// -----------------------------------------------------------------------------
// TestSetServiceCenterTimeStamp
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetServiceCenterTimeStamp( CStifLogger* aLog, CSmsStatusReport& aReport)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetServiceCenterTimeStamp()"));
	TInt result = KErrNone;
	
	const TTime time(_L("20060201:000000.000000"));
	TInt numQuarterHours = 1;
	//IMPORT_C void SetServiceCenterTimeStamp(const TTime& aTime,TInt& aNumQuarterHours);
	aReport.SetServiceCenterTimeStamp(time, numQuarterHours);
	
	aLog->Log(_L("SetServiceCenterTimeStamp() Completed"));
	aLog->Log(_L("Time stamp successfully stored"));
	aLog->Log(_L("Set service center time stamp == PASS"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestGetServiceCenterTimeStamp
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetServiceCenterTimeStampL( CStifLogger* aLog, CSmsStatusReport& aReport)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling ServiceCenterTimeStamp()"));
	TInt result = KErrNone;
	
	TBuf<30> string;
	_LIT( KFormat, "%*E%*D%X%*N%*Y %1 %2 '%3 %H%:1%T%:2%S");
	TTime setTime(TDateTime(2006,EJanuary,01,12,0,0,0));
	TTime getTime;
	TInt numQuarterHrs;
	//void ServiceCenterTimeStamp(TTime& aTime,TInt& aNumQuarterHours);
	aReport.ServiceCenterTimeStamp(getTime, numQuarterHrs);
	
	if( getTime == setTime )
		{
		getTime.FormatL(string, KFormat);
		aLog->Log(_L("ServiceCenterTimeStamp() Completed"));
		aLog->Log(_L("Result data:Time stamp: %S"), &string);
		aLog->Log(_L("Get service center time stamp == PASS"));
		}
	else
		{
		result = KErrGeneral;
		aLog->Log(_L("Get service center time stamp == FAIL"));
		}
		
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestSetDischargeTime
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetDischargeTime( CStifLogger* aLog, CSmsStatusReport& aReport)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetDischargeTime()"));
	TInt result = KErrNone;
	
	const TTime time(_L("20060201:000000.000000"));
	TInt numQuarterHrs = 2;
	//void SetDischargeTime(const TTime& aTime,TInt& aNumQuarterHours);	
	aReport.SetDischargeTime(time, numQuarterHrs);
	
	aLog->Log(_L("SetDischargeTime Completed"));
	aLog->Log(_L("Discharge time stored successfully"));
	aLog->Log(_L("Set discharge time == PASS"));
	
	return result;	
	}
	
// -----------------------------------------------------------------------------
// TestGetDischargeTime
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetDischargeTimeL( CStifLogger* aLog, CSmsStatusReport& aReport)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling DischargeTime()"));
	TInt result = KErrNone;
	
	TBuf<30> string;
	_LIT( KFormat, "%*E%*D%X%*N%*Y %1 %2 '%3 %H%:1%T%:2%S");
	TTime setTime(TDateTime(2006,EJanuary,01,12,0,0,0));
	TTime time;
	TInt numQuarterHrs;
	//void DischargeTime(TTime& aTime,TInt& aNumQuarterHours);
	aReport.DischargeTime(time, numQuarterHrs);
	
	if( time == setTime )
		{
		time.FormatL(string, KFormat);
		aLog->Log(_L("DischargeTime() Completed"));
		aLog->Log(_L("Result data: Discharge time: %S"), &string);
		aLog->Log(_L("Get discharge time == PASS"));
		}
	else
		aLog->Log(_L("Get discharge time == FAIL"));
	
	return result;	
	}
	
// -----------------------------------------------------------------------------
// TestSetStatus
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetStatus(CStifLogger* aLog, CSmsStatusReport& aReport)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SetStatus()"));
	TInt result = KErrNone;
	
	//void SetStatus(TSmsStatus::TSmsStatusValue aValue);
	TSmsStatus::TSmsStatusValue status = TSmsStatus::ESmsShortMessageReceivedBySME;
	aReport.SetStatus(status);
	
	aLog->Log(_L("Status() Completed"));	
	aLog->Log(_L("Result data: status: %d"), status);	
	aLog->Log(_L("Get status == PASS"));	
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestGetStatus
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetStatus(CStifLogger* aLog, CSmsStatusReport& aReport)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling Status()"));
	TInt result = KErrNone;
	
	//TSmsStatus::TSmsStatusValue Status() const;
	TSmsStatus::TSmsStatusValue status = aReport.Status();
	
	if( status == TSmsStatus::ESmsShortMessageReceivedBySME )
		{
		aLog->Log(_L("Status() Completed"));	
		aLog->Log(_L("Result data: status: %d"), status);	
		aLog->Log(_L("Get status == PASS"));	
		}
	else
		aLog->Log(_L("Get status == FAIL"));	
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestSmsStatusReportDuplicateL
// Creates a copy of the object
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSmsStatusReportDuplicateL( CStifLogger* aLog, CSmsStatusReport& aReport)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SmsStatusReportDuplicateL()"));
	
	TInt result = KErrNone;
	
	CSmsStatusReport* dupObj = aReport.DuplicateL();
		
		if( dupObj )
			{
		aLog->Log(_L("TestSmsStatusReportDuplicateL() completed"));
		aLog->Log(_L("Object successfully created"));
		aLog->Log(_L("SmsStatusReportDuplicateL == PASS"));
		
		}
		else
			{
				result = KErrGeneral;
				aLog->Log(_L("SmsStatusReportDuplicateL == FAIL"));
			}
			return result;
	}	
// -----------------------------------------------------------------------------
// TestGetRejectDuplicates 
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetRejectDuplicates(CStifLogger* aLog, CSmsSubmit& aSmsSub)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling RejectDuplicates()"));
	
	TInt result = KErrNone;
	
	//TBool RejectDuplicates() const;
	TBool reject = aSmsSub.RejectDuplicates();
	
	if( reject )
		{
		aLog->Log(_L("RejectDuplicates() Completed"));
		aLog->Log(_L("Result data: Reject duplicates: %d"), reject);
		aLog->Log(_L("Get reject duplicates == PASS"));
		}
		
	return result;	
	}
	
// -----------------------------------------------------------------------------
// TestSetRejectDuplicates 
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetRejectDuplicates(CStifLogger* aLog, CSmsSubmit& aSmsSub)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetRejectDuplicates()"));
	
	TInt result = KErrNone;
	TBool reject = ETrue;
	//void SetRejectDuplicates(TBool aRejectDuplicates);
	aSmsSub.SetRejectDuplicates(reject);
	
	aLog->Log(_L("SetRejectDuplicates() Completed"));
	aLog->Log(_L("Reject duplicate flag stored successfully"));
	aLog->Log(_L("Set reject duplicates == PASS"));
	
	return result;	
	}

// -----------------------------------------------------------------------------
// TestGetValidityPeriodFormat 
// Gets the Validity Period Format
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetValidityPeriodFormat (CStifLogger* aLog, CSmsSubmit& aSmsSub)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling ValidityPeriodFormat()"));
	
	TInt result = KErrNone;
	
	// IMPORT_C TSmsFirstOctet::TSmsValidityPeriodFormat ValidityPeriodFormat() const
	TSmsFirstOctet::TSmsValidityPeriodFormat pformat = aSmsSub.ValidityPeriodFormat ();
	
	if(pformat == TSmsFirstOctet::ESmsVPFNone)
		{
		aLog->Log(_L("ValidityPeriodFormat() completed"));
		aLog->Log(_L("Validity period format: %d"),pformat);
		aLog->Log(_L("Get validity period format == PASS"));
		}
	else
		aLog->Log( _L("ValidityPeriodFormat() == FAIL"));
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestSetValidityPeriodFormat
// Sets the Validity Period Format
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetValidityPeriodFormat (CStifLogger* aLog, CSmsSubmit& aSmsSub)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetValidityPeriodFormat()"));
	
	TInt result = KErrNone;
	
	// IMPORT_C void SetValidityPeriodFormat(TSmsFirstOctet::TSmsValidityPeriodFormat aValidityPeriodFormat)
	TSmsFirstOctet::TSmsValidityPeriodFormat aValidityPeriodFormat (TSmsFirstOctet::ESmsVPFNone);
	
	aSmsSub.SetValidityPeriodFormat (aValidityPeriodFormat);
	
	aLog->Log( _L("SetValidityPeriodFormat() completed"));
	aLog->Log( _L("Validity period format stored successfully"));
	aLog->Log( _L("Set validity period format == PASS"));

	return result;
	}


// -----------------------------------------------------------------------------
// TestGetReplyPath
// Gets Reply Path flag
// If a Reply Path exists, the recipient of the SMS can reply using the same 
// service center address
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetReplyPath (CStifLogger* aLog, CSmsSubmit& aSmsSub)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling ReplyPath()"));
	
	TInt result = KErrNone;
	
	// IMPORT_C TBool ReplyPath() const
	TBool checkres = aSmsSub.ReplyPath ();
	
	if( checkres )
	{
		aLog->Log (_L("ReplyPath() completed"));
		aLog->Log (_L("Result data:reply path flag: %d"),checkres);
		aLog->Log (_L("Get reply path == PASS"));
	}
	else
		aLog->Log (_L("Get reply path == FAIL"));
	
	return result;
	}
	

// -----------------------------------------------------------------------------
// TestSetReplyPath
// Sets Reply Path flag
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetReplyPath (CStifLogger* aLog, CSmsSubmit& aSmsSub)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetReplyPath()"));
	
	TInt result = KErrNone;
	TBool tempVar = ETrue;
	
	// IMPORT_C void SetReplyPath (TBool aReplyPath)
	aSmsSub.SetReplyPath (tempVar);
	
	aLog->Log( _L("SetReplyPath() completed"));
	aLog->Log( _L("Reply path flag stored successfully"));
	aLog->Log( _L("Set reply path == PASS"));
	
	return result;	
	}


// -----------------------------------------------------------------------------
// TestGetStatusReportRequest 
// Gets Status Report Request flag
// A sender can request STATUS REPORTs for the SUBMIT being sent
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetStatusReportRequest (CStifLogger* aLog, CSmsSubmit& aSmsSub)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling StatusReportRequest()"));
	TInt result = KErrNone;
	
	// IMPORT_C TBool StatusReportRequest() const
	TBool checkres = aSmsSub.StatusReportRequest();
	
	if( checkres )
	{
		aLog->Log(_L("StatusReportRequest() completed"));
		aLog->Log (_L("result data:status report request flag: %d"),checkres);
		aLog->Log(_L("Get status report request == PASS"));
	}
	else
		aLog->Log( _L("Get status report request == FAIL"));
	
	return result;	
	}


// -----------------------------------------------------------------------------
// TestSetStatusReportRequest 
// Sets Status Report Request flag
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetStatusReportRequest (CStifLogger* aLog, CSmsSubmit& aSmsSub)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetStatusReportRequest()"));
	
	TInt result = KErrNone;
	TBool tempVar = ETrue;
	
	// IMPORT_C void SetStatusReportRequest(TBool aRequest);
	aSmsSub.SetStatusReportRequest (tempVar);
	
	aLog->Log( _L("SetStatusReportRequest() completed"));
	aLog->Log( _L("Status report request flag stored successfully"));
	aLog->Log( _L("Set status report request == PASS"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestGetMessageReference  
// Gets the Message Reference
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetMessageReference (CStifLogger* aLog, CSmsSubmit& aSmsSub)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling MessageReference()"));
	
	TInt result = KErrNone;
	
	// IMPORT_C TInt MessageReference() const
	TInt checkres = aSmsSub.MessageReference();
	
	if(checkres == 10)
	{
		aLog->Log( _L("MessageReference() completed"));
		_LIT(tempStr,"result data:message reference: %d");
		aLog->Log (tempStr,checkres);
		aLog->Log( _L("Get message reference == PASS"));
	}
	else
		aLog->Log( _L("Get message reference == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetMessageReference  
// Sets the Message Reference
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetMessageReference (CStifLogger* aLog, CSmsSubmit& aSmsSub)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetMessageReference()"));
	
	TInt result = KErrNone;
	
	// IMPORT_C void SetMessageReference(TInt aMessageReference)
	aSmsSub.SetMessageReference (10);
	
	aLog->Log( _L("SetMessageReference() completed"));
	aLog->Log( _L("Message reference stored successfully"));
	aLog->Log( _L("Set message reference == PASS"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestGetValidityPeriod   
// Gets the Validity Period for the SUBMIT
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetValidityPeriod (CStifLogger* aLog, CSmsSubmit& aSmsSub)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling ValidityPeriod()"));
	
	TInt result = KErrNone;
	
	// IMPORT_C const TTimeIntervalMinutes &ValidityPeriod() const
	TTimeIntervalMinutes timeinterval;
	timeinterval = aSmsSub.ValidityPeriod ();
	
	if(timeinterval.Int() == 1)
	{
		aLog->Log( _L("ValidityPeriod() completed"));
		_LIT(tempVal,"result data:validity period: %d");
		aLog->Log (tempVal,timeinterval.Int() );
		aLog->Log( _L("Get validity period == PASS"));
	}
	else
		aLog->Log( _L("Get validity period == FAIL"));
		
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetValidityPeriod
// Sets the Validity Period for the SUBMIT
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetValidityPeriod (CStifLogger* aLog, CSmsSubmit& aSmsSub)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetValidityPeriod()"));
	
	TInt result = KErrNone;
	
	// IMPORT_C void SetValidityPeriod(const TTimeIntervalMinutes 
	// &aTimeIntervalMinutes)
	TTimeIntervalMinutes timeinterval = 1;
	aSmsSub.SetValidityPeriod (timeinterval);
	
	aLog->Log( _L("SetValidityPeriod() completed"));
	aLog->Log( _L("Validity period stored successfully"));
	aLog->Log( _L("Set validity period == PASS"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestSmsSubmitDuplicateL
// Creates a copy of the object
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSmsSubmitDuplicateL( CStifLogger* aLog, CSmsSubmit& aSmsSub)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SmsSubmitDuplicateL()"));
	
	TInt result = KErrNone;
	
	CSmsSubmit* dupObj = aSmsSub.DuplicateL();
		
		if( dupObj )
			{
		aLog->Log(_L("TestSmsSubjectDuplicateL() completed"));
		aLog->Log(_L("Object successfully created"));
		aLog->Log(_L("SmsSubmitDuplicateL == PASS"));
			}
		else
			{
				result = KErrGeneral;
				aLog->Log(_L("SmsSubmitDuplicateL == FAIL"));
			}
			return result;
	}

// -----------------------------------------------------------------------------
// TestGetIsRPError
// Gets the Reply Path Error flag 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetIsRPError (CStifLogger* aLog, CSmsSubmitReport& aSmsSubReport)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling IsRPError()"));
	
	TInt result = KErrNone;
	 
	// TBool IsRPError() const
	TBool checkres = aSmsSubReport.IsRPError();
	
	if( checkres )
	{
		aLog->Log(_L("IsRPError() completed"));
		aLog->Log(_L("Result data:is RP error flag: %d"),checkres);
		aLog->Log(_L("Get is RP error == PASS"));
	}
	else
		aLog->Log(_L("Get is RP error == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestSetIsRPError
// Gets the Reply Path Error flag 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetIsRPError (CStifLogger* aLog, CSmsSubmitReport& aSmsSubReport)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetIsRPError()"));
	
	TInt result = KErrNone;
	TBool tempVar = ETrue;
	
	// inline void SetIsRPError(TBool aIsRPError)
	aSmsSubReport.SetIsRPError (tempVar);
	
	aLog->Log( _L("SetIsRPError() completed"));
	aLog->Log( _L("Is RP error flag stored successfully"));
	aLog->Log( _L("Set is RP error == PASS"));
	
	return result;
	}
	

// -----------------------------------------------------------------------------
// TestGetFailureCause
// Gets the Failure Cause 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetFailureCause (CStifLogger* aLog, CSmsSubmitReport& aSmsSubReport)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling FailureCause()"));
	
	TInt result = KErrNone;
	 
	// IMPORT_C TInt FailureCause() const
	TInt checkres = aSmsSubReport.FailureCause ();
	
	if(checkres == TSmsFailureCause::ESmsPIDErrorCannotReplaceShortMessage)
	{
		aLog->Log( _L("FailureCause() completed"));
		_LIT(tempVal,"result data:failure cause: %d");
		aLog->Log(tempVal,checkres);
		aLog->Log( _L("Get failure cause == PASS"));
	}
	else
		aLog->Log( _L("Get failure cause == FAIL"));
	
	return result;
	}
	
	
// -----------------------------------------------------------------------------
// TestSetFailureCause
// Sets the Failure Cause 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetFailureCause (CStifLogger* aLog, CSmsSubmitReport& aSmsSubReport)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetFailureCause()"));
	
	TInt result = KErrNone;
	TSmsFailureCause::TSmsFailureCauseError aFailureCause = 
	   TSmsFailureCause::ESmsPIDErrorCannotReplaceShortMessage;
	
	// IMPORT_C void SetFailureCause
	// (TSmsFailureCause::TSmsFailureCauseError aFailureCause)
	aSmsSubReport.SetFailureCause (aFailureCause);
	
	aLog->Log( _L("SetFailureCause() completed"));
	aLog->Log( _L("Failure cause stored successfully"));
	aLog->Log( _L("Set failure cause == PASS"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestSmsSubmitReportDuplicateL
// Creates a copy of the object
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSmsSubmitReportDuplicateL( CStifLogger* aLog, CSmsSubmitReport& aSmsSubReport)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling SmsSubmitReportDuplicateL()"));
	
	TInt result = KErrNone;
	
	CSmsSubmitReport* dupObj = aSmsSubReport.DuplicateL();
		
		if( dupObj )
			{
		aLog->Log(_L("TestSmsSubmitReportDuplicateL() completed"));
		aLog->Log(_L("Object successfully created"));
		aLog->Log(_L("SmsSubmitReportDuplicateL == PASS"));
		
		}
		else
			{
				result = KErrGeneral;
				aLog->Log(_L("SmsSubmitReportDuplicateL == FAIL"));
			}
			return result;
	}

// -----------------------------------------------------------------------------
// TestGetNumberOfInformationElements 
// Gets the number of information elements
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetNumberOfInformationElements (CStifLogger* aLog, CSmsUserData& aSmsUsr)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling NumInformationElements()"));
	
	TInt result = KErrNone;
	
	// inline TInt NumInformationElements() const
	TInt checkres = aSmsUsr.NumInformationElements();
	
	if( checkres == 0)
	{
		aLog->Log( _L("NumInformationElements() completed"));
		_LIT(tempVal,"result:number of information elements: %d");
		aLog->Log(tempVal, checkres);
		aLog->Log( _L("Get number of information elements == PASS"));
	}
	else
		aLog->Log( _L("Get number of information elements == FAIL"));
	
	return result;	
	}


// -----------------------------------------------------------------------------
// TestGetInformationElement 
// Gets an information element by index
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetInformationElement (CStifLogger* aLog, CSmsUserData& aSmsUsr)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling InformationElement()"));
	
	TInt result = KErrNone;
	TInt index = 0;
	
	// IMPORT_C CSmsInformationElement &InformationElement(TInt aIndex) const
	CSmsInformationElement& infoElem = aSmsUsr.InformationElement (index);
	
	aLog->Log( _L("InformationElement() completed"));
	aLog->Log(_L("Information element (identifier): %d"), infoElem.Identifier());
	aLog->Log( _L("Get information element == PASS"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestGetInformationElementIndex
// Gets the index of an information element
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetInformationElementIndex (CStifLogger* aLog, CSmsUserData& aSmsUsr)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling InformationElementIndex()"));
	
	TInt result = KErrNone;
	TInt index;
	CSmsInformationElement::TSmsInformationElementIdentifier aIdentifier 
	 ( CSmsInformationElement::ESmsIEISpecialSMSMessageIndication);
		
	// IMPORT_C TBool InformationElementIndex(
	// CSmsInformationElement::TSmsInformationElementIdentifier aIdentifier, 
	// TInt &aIndex) const
	TBool checkres = aSmsUsr.InformationElementIndex (aIdentifier,index); 
	
	if( checkres )
		{
		aLog->Log(_L("InformationElementIndex() completed"));
		aLog->Log(_L("Result data:information element index: %d"), checkres);
		aLog->Log(_L("Get information element index == PASS"));
		}
	else
		aLog->Log(_L("Get information element index == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestAddInformationElement 
// Adds an information element
// -----------------------------------------------------------------------------
LOCAL_C TInt TestAddInformationElement (CStifLogger* aLog, CSmsUserData& aSmsUsr)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling AddInformationElementL()"));
	
	_LIT8(str,"test string");
	const TBufC8<20> data (str);
	TSmsId testObject (CSmsInformationElement::ESmsIEISpecialSMSMessageIndication);
	
	// IMPORT_C void AddInformationElementL(TSmsId aIdentifier, 
	// const TDesC8 &aData)
	TRAPD( result, aSmsUsr.AddInformationElementL (testObject,data));
	
	if(result == KErrNone)
		{
		aLog->Log( _L("AddInformationElementL() completed"));
		aLog->Log( _L("Information element added successfully"));
		aLog->Log( _L("Add information element == PASS"));
		}
	else
		aLog->Log( _L("Add information element == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestRemoveInformationElement
// Removes an information element at the specified index
// -----------------------------------------------------------------------------
LOCAL_C TInt TestRemoveInformationElement (CStifLogger* aLog, CSmsUserData& aSmsUsr)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling RemoveInformationElement()"));
	
	TInt result = KErrNone;
	TInt index = 0;
	
	// IMPORT_C void RemoveInformationElement(TInt aIndex)
	aSmsUsr.RemoveInformationElement (index);
	
	aLog->Log( _L("RemoveInformationElement() completed"));
	aLog->Log( _L("Information element removed successfully"));
	aLog->Log( _L("Remove information element == PASS"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestMaxBodyLengthInChars 
// Gets the maximum characters in body length of user data
// -----------------------------------------------------------------------------
LOCAL_C TInt TestMaxBodyLengthInChars (CStifLogger* aLog, CSmsUserData& aSmsUsr)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling MaxBodyLengthInChars()"));
	
	TInt result = KErrNone;
	 	
	// IMPORT_C TInt MaxBodyLengthInChars() const
	TInt charret = aSmsUsr.MaxBodyLengthInChars ();
	
	aLog->Log( _L("MaxBodyLengthInChars() completed"));
	_LIT(tempVal, "result data:max body length in chars: %d");
	aLog->Log(tempVal,charret);
	aLog->Log( _L("Get max body length in chars == PASS"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestGetBody 
// Gets the unpacked User Data Elements
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetBody (CStifLogger* aLog, CSmsUserData& aSmsUsr)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling Body()"));
	
	TInt result = KErrNone;
	_LIT8 (str,"Test String");
	TBufC8<20> tempVar (str);
	
	// IMPORT_C TPtrC8 Body() const
	TPtrC8 checkres( aSmsUsr.Body() );
	
	if(!checkres.Compare (tempVar))
	{
		aLog->Log( _L("Body() completed"));
		aLog->Log(_L("result data:body: %s"),checkres.Ptr());
		aLog->Log( _L("Get body == PASS"));
	}
	else
		aLog->Log( _L("Get body == FAIL"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestSetBody 
// Sets the unpacked User Data Elements
// -----------------------------------------------------------------------------
LOCAL_C TInt TestSetBody (CStifLogger* aLog, CSmsUserData& aSmsUsr)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling SetBodyL()"));
	
	_LIT8 (str,"Test String");
	TBufC8<20> tempVar (str);
	
	// IMPORT_C void SetBodyL(const TDesC8 &aBody)
	TRAPD( result , aSmsUsr.SetBodyL (tempVar));
	
	if(result == KErrNone)
	{
		aLog->Log( _L("SetBodyL() completed"));
		aLog->Log( _L("Body stored successfully"));
		aLog->Log( _L("Set body == PASS"));
	}
	else
		aLog->Log(_L("Set body == FAIL"));
	
	return result;
	}


// -----------------------------------------------------------------------------
// TestGetIsSupported 
// Tests if the User Data supports a specified character
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetIsSupported (CStifLogger* aLog, CSmsUserData& aSmsUsr)
	{
	aLog->Log( _L("--------------------------------------------------------"));
	aLog->Log( _L("Calling IsSupportedL()"));
	
	TChar testChar ('&');
	// IMPORT_C TBool IsSupportedL(TChar aChar)
	TBool checkres;
	TRAPD(result, checkres = aSmsUsr.IsSupportedL (testChar));
	
	if(result == KErrNone)
	{
		aLog->Log( _L("IsSupportedL() completed"));
		_LIT(tempVal,"result data:is supported flag: %d");
		aLog->Log(tempVal, checkres);
		aLog->Log( _L("Get is supported == PASS"));
	}
	else
		aLog->Log( _L("Get is supported == FAIL"));
	
	return result;
	}

// -----------------------------------------------------------------------------
// TestGetIsSupported2
// 
// -----------------------------------------------------------------------------
LOCAL_C TInt TestGetIsSupported2(CStifLogger* aLog,CSmsUserData& aSmsUsr)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling IsSupported2L()"));
	
	
	TBufC<50> testBuffer = _L("Nokia$123has*some%employees");
	TInt numUnconvertable;
	TInt posFirstUnconvertable;
	TInt numDowngradedChars;
	TInt numReqAlternativeEncoding;
	
	TBool res = 0;
	TRAPD( result, res = aSmsUsr.IsSupportedL(testBuffer, ESmsEncodingNone, numUnconvertable, numDowngradedChars, numReqAlternativeEncoding, posFirstUnconvertable));
	
	if(result != KErrNone)
		{
		aLog->Log(_L("Leave occured: error code: %d"), result);
		}
	else
		{
		aLog->Log(_L("IsSupported2L() completed"));
		aLog->Log(_L("result data: is supported: %d"), res);
		aLog->Log(_L("Get is supported == PASS"));
		}
	return result;	
	}
// -----------------------------------------------------------------------------
// TestGetIsSupported3
// 
// -----------------------------------------------------------------------------

LOCAL_C TInt TestGetIsSupported3(CStifLogger* aLog,CSmsUserData& aSmsUsr)
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log(_L("Calling IsSupported3L()"));
	
	
	TBufC<50> testBuffer = _L("Nokia$123has*some%employees");
	TInt numUnconvertable;
	TInt posFirstUnconvertable;
		
	TBool res = 0;
	TRAPD( result, res = aSmsUsr.IsSupportedL(testBuffer, numUnconvertable, posFirstUnconvertable));
	
	if(result != KErrNone)
		{
		aLog->Log(_L("Leave occured: error code: %d"), result);
		}
	else
		{
		aLog->Log(_L("IsSupported3L() completed"));
		aLog->Log(_L("result data: is supported: %d"), res);
		aLog->Log(_L("Get is supported == PASS"));
		}
	return result;	
	}
// -----------------------------------------------------------------------------
// CBCSmsUtilitiesTest::TestSmsAlphabetConverter
// Simple printing to UI test.
// -----------------------------------------------------------------------------
//
TInt CBCSmsUtilitiesTest::TestSmsAlphabetConverterL( 
    TTestResult& aResult )
    {
	_LIT(KSmsAlphabetConverter, "Calling CSmsAlphabetConverter");
	iLog->Log(KSmsAlphabetConverter);
	TInt result = KErrNone;
	
	CCnvCharacterSetConverter* charSet = CCnvCharacterSetConverter::NewLC();
	TSmsDataCodingScheme::TSmsAlphabet smsAlphabet = TSmsDataCodingScheme::ESmsAlphabet8Bit;
	TBool isBinary = EFalse;
	
    CSmsAlphabetConverter* converter = CSmsAlphabetConverter::NewLC(*charSet, iSession, smsAlphabet, isBinary);
	CConsoleBase* console = Create_ConsoleL(_L("CSmsAlphabetConverter"));
//Get alphabet
	result = TestGetAlphabet(iLog, *converter);
	Print(console, result, _L("Alphabet") );

//ConvertFromNative	
	result = TestConvertFromNative(iLog, *converter);
	Print(console, result, _L("ConvertFromNative") );
	
//ConvertToNative
	result = TestConvertToNative(iLog, *converter);
	Print(console, result, _L("ConvertToNative") );

//ConvertFromNative2	
	result = TestConvertFromNative2L(iLog, *converter);
	Print(console, result, _L("ConvertFromNative2") );
	
//ConvertToNative2
	result = TestConvertToNative2L(iLog, *converter);
	Print(console, result, _L("ConvertToNative2") );
	
//UnconvertedNativeCharacters	
	result = TestUnconvertedNativeCharacters(iLog, *converter);
	Print(console, result, _L("UnconvertedUDCharacters") );

//UnconvertedUDElements    
    result = TestUnconvertedUDElements(iLog, *converter);
	Print(console, result, _L("ResetUnconvertedUDElements") );
	
//ResetUnconvertedNativeCharacters	
	result = TestResetUnconvertedNativeCharacters(iLog, *converter);
	Print(console, result, _L("ResetUnconvertedNativeCharacters") );

//ResetUnconvertedUDElements	
	result = TestResetUnconvertedUDElements(iLog, *converter);
	Print(console, result, _L("ResetUnconvertedUDElements") );

	Remove_Console(console);
	CleanupStack::PopAndDestroy(2);
// Case was executed
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CBCSmsUtilitiesTest::TestSmsBuffer
// Simple printing to UI test.
// -----------------------------------------------------------------------------
//
TInt CBCSmsUtilitiesTest::TestSmsBufferL( 
    TTestResult& aResult )
    {
    _LIT(KSmsBuffer, "Calling CSmsBuffer");
	iLog->Log(KSmsBuffer);
	TInt result = KErrNone;
	
	CSmsBuffer* buffer = CSmsBuffer::NewL();
	CleanupStack::PushL(buffer);
	
	CConsoleBase* console = Create_ConsoleL(_L("CSmsBuffer"));
//Construction
//Destruction
//Insert
	result = TestInsert(iLog, *buffer);
	Print(console, result, _L("Insert") );
	
//Delete
	result = TestDelete(iLog, *buffer);
	Print(console, result, _L("DeleteL") );
	
//Extract
	result = TestExtract(iLog, *buffer);
	Print(console, result, _L("Extract") );
	
//GetLength
	result = TestGetLength(iLog, *buffer);
	Print(console, result, _L("Length") );
	
//Externalize
	result = TestExternalizeL(iLog, *buffer);
	Print(console, result, _L("ExternalizeL") );
	
//Internalize
	result = TestInternalizeL(iLog, *buffer);
	Print(console, result, _L("InternalizeL") );

//Reset
	result = TestReset(iLog, *buffer);
	Print(console, result, _L("Reset") );
	
	Remove_Console(console);
	CleanupStack::PopAndDestroy();
// Case was executed
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CBCSmsUtilitiesTest::TestSmsCommand
// Simple printing to UI test.
// -----------------------------------------------------------------------------
//
TInt CBCSmsUtilitiesTest::TestSmsCommandL( 
    TTestResult& aResult )
    {
   _LIT(KSmsBufferBase, "Calling CSmsBufferBase");
	iLog->Log(KSmsBufferBase);
	TInt result = KErrNone;
	
    RFs rfServer; 
    User::LeaveIfError(rfServer.Connect()); 
    
    CCnvCharacterSetConverter* characterSetConverter = CCnvCharacterSetConverter::NewL(); 
    CSmsBuffer* smsBuffer = CSmsBuffer::NewL(); 
	CSmsMessage* smsMessage = CSmsMessage::NewL(rfServer, CSmsPDU::ESmsCommand, smsBuffer ); 	

	CSmsCommand& command = STATIC_CAST(CSmsCommand&, smsMessage->SmsPDU() );
	CSmsCommand * ptrCommand = &command;
	CleanupStack::PushL(ptrCommand);
	
	CConsoleBase* console = Create_ConsoleL(_L("CSmsCommand"));
//Construction
//Add information element
	result = TestAddInformationElement(iLog, command);
	Print(console, result, _L("AddInformationElement") );

//Get information element
	result = TestInformationElement(iLog, command);
	Print(console, result, _L("InformationElement"));
	
//Get information element index
	result = TestInformationElementIndex(iLog, command);
	Print(console, result, _L("InformationElementIndex"));
	
//Get number of information elements
	result = TestNumInformationElements(iLog, command);
	Print(console, result, _L("NumInformationElements"));
	
//Remove information element
	result = TestRemoveInformationElement(iLog, command);
	Print(console, result, _L("RemoveInformationElement") );

//Get max command data length
	result = TestMaxCommandDataLength(iLog, command);
	Print(console, result, _L("MaxCommandDataLength") );
	
//Set command data
	result = TestSetCommandData(iLog, command);
	Print(console, result, _L("SetCommandData"));
	
//Get command data
	result = TestGetCommandData(iLog, command);
	Print(console, result, _L("CommandData") );
	
//Set Command Type
	result = TestSetCommandType(iLog, command);
	Print(console, result, _L("SetCommandType") );
	
//Get Command Type
	result = TestGetCommandType(iLog, command);
	Print(console, result, _L("CommandType") );
	
//Set message number
	result = TestSetMessageNumber(iLog, command);
	Print(console, result, _L("SetMessageNumber"));
	
//Get message number
	result = TestGetMessageNumber(iLog, command);
	Print(console, result, _L("MessageNumber"));
	
//Set Message Reference
	result = TestSetMessageReference(iLog, command);
	Print(console, result, _L("SetMessageReference"));
	
//Get Message Reference
	result = TestGetMessageReference(iLog, command);
	Print(console, result, _L("MessageReference"));
	
//Set status report request
	result = TestSetStatusReportRequest(iLog, command);
	Print(console, result, _L("SetStatusReportRequest"));
	
//Get status report request
	result = TestGetStatusReportRequest(iLog, command);
	Print(console, result, _L("StatusReportRequest"));
	
//DuplicateL
	result = TestSmsCommandDuplicateL(iLog, command);
	Print(console, result, _L("SmsCommandDuplicateL"));
	
	Remove_Console(console);
	CleanupStack::PopAndDestroy(&command);
	rfServer.Close();
   // Case was executed
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CBCSmsUtilitiesTest::TestSmsDeliver
// Simple printing to UI test.
// -----------------------------------------------------------------------------
//
TInt CBCSmsUtilitiesTest::TestSmsDeliverL( 
    TTestResult& aResult )
    {
 	_LIT(KSmsDeliver, "Calling CSmsDeliver");
	iLog->Log(KSmsDeliver);
	TInt result = KErrNone;
	
	RFs rfServer; 
    User::LeaveIfError(rfServer.Connect()); 
    
    CCnvCharacterSetConverter* characterSetConverter = CCnvCharacterSetConverter::NewL(); 
    CSmsBuffer* smsBuffer = CSmsBuffer::NewL(); 
	CSmsMessage* smsMessage = CSmsMessage::NewL(rfServer, CSmsPDU::ESmsDeliver, smsBuffer ); 	

	CSmsDeliver& deliver = STATIC_CAST(CSmsDeliver&, smsMessage->SmsPDU() );
	CSmsDeliver *ptrDeliver = &deliver;
	CleanupStack::PushL(ptrDeliver);
	
	CConsoleBase* console = Create_ConsoleL(_L("CSmsDeliver"));
//Construction
//Set more messages to send
	result = TestSetMoreMessagesToSend(iLog, deliver);
	Print(console, result, _L("SetMoreMessagesToSend"));
	
//Get more messages to send
	result = TestGetMoreMessagesToSend(iLog, deliver);
	Print(console, result, _L("MoreMessagesToSend"));
	
//Set reply path
	result = TestSetReplyPath(iLog, deliver);
	Print(console, result, _L("SetReplyPath"));
	
//Get reply path
	result = TestGetReplyPath(iLog, deliver);
	Print(console, result, _L("ReplyPath"));
	
//Set status report indication
	result = TestSetStatusReportIndication(iLog, deliver);
	Print(console, result, _L("SetStatusReportIndication"));
	
//Get status report indication
	result = TestGetStatusReportIndication(iLog, deliver);
	Print(console, result, _L("StatusReportIndication"));
	
//Set service center time stamp
	result = TestSetServiceCenterTimeStamp(iLog, deliver);
	Print(console, result, _L("SetServiceCenterTimeStamp"));
	
//Get service center time stamp
	result = TestGetServiceCenterTimeStampL(iLog, deliver);
	Print(console, result, _L("ServiceCenterTimeStamp"));
	
//Get protocol identifier
	result = TestGetProtocolIdentifier(iLog, deliver);
	Print(console, result, _L("ProtocolIdentifier"));

//DuplicateL
	result = TestSmsDeliverDuplicateL(iLog, deliver);
	Print(console, result, _L("SmsDeliverDuplicateL"));	
	
	Remove_Console(console);
	CleanupStack::PopAndDestroy(&deliver);
	rfServer.Close();
    // Case was executed
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CBCSmsUtilitiesTest::TestSmsDeliverReport
// Simple printing to UI test.
// -----------------------------------------------------------------------------
//
TInt CBCSmsUtilitiesTest::TestSmsDeliverReportL( 
    TTestResult& aResult )
    {
 	_LIT(KSmsDeliverReport, "Calling CSmsDeliverReport");
	iLog->Log(KSmsDeliverReport);
	TInt result = KErrNone;
	
	RFs rfServer; 
    User::LeaveIfError(rfServer.Connect()); 
    
    CCnvCharacterSetConverter* characterSetConverter = CCnvCharacterSetConverter::NewL(); 
    CSmsBuffer* smsBuffer = CSmsBuffer::NewL(); 
	CSmsMessage* smsMessage = CSmsMessage::NewL(rfServer, CSmsPDU::ESmsDeliverReport, smsBuffer ); 	

	CSmsDeliverReport& deliverReport = STATIC_CAST(CSmsDeliverReport&, smsMessage->SmsPDU() );
	CSmsDeliverReport* ptrDeliverReport = &deliverReport;
	CleanupStack::PushL(ptrDeliverReport);
	
	CConsoleBase* console = Create_ConsoleL(_L("CSmsDeliverReport"));
//Construction
//Set is RP error
	result = TestSetIsRPError(iLog, deliverReport);
	Print(console, result, _L("SetIsRPError"));
	
//Get is RP error
	result = TestGetIsRPError(iLog, deliverReport);
	Print(console, result, _L("IsRPError"));
	
//Set failure cause
	result = TestSetFailureCause(iLog, deliverReport);
	Print(console, result, _L("SetFailureCause"));
	
//Get failure cause
	result = TestGetFailureCause(iLog, deliverReport);
	Print(console, result, _L("FailureCause"));
	
//DuplicateL
	result = TestSmsDeliverReportDuplicateL(iLog, deliverReport);
	Print(console, result, _L("SmsDeliverReportDuplicateL"));
	
	Remove_Console(console);
	CleanupStack::PopAndDestroy(&deliverReport);
	rfServer.Close();
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CBCSmsUtilitiesTest::TestSmsEditorBuffer
// 
// -----------------------------------------------------------------------------
//
TInt CBCSmsUtilitiesTest::TestSmsEditorBufferL( 
    TTestResult& aResult )
    {
	_LIT(KSmsEditorBuffer, "Calling CSmsEditorBuffer");
	iLog->Log(KSmsEditorBuffer);
	TInt result = KErrNone;
	
	CParaFormatLayer* para = CParaFormatLayer::NewL();
	CCharFormatLayer* charlayer = CCharFormatLayer::NewL();
	
	CRichText* text = CRichText::NewL(para, charlayer);
	CSmsEditorBuffer* editor = CSmsEditorBuffer::NewL(*text);
	CleanupStack::PushL(editor);
	
	CConsoleBase* console = Create_ConsoleL(_L("CSmsEditorBuffer"));
//Construction
//Destruction
//Insert
	result = TestInsert(iLog, *editor);
	Print(console, result, _L("Insert") );
	
//Delete
	result = TestDelete(iLog, *editor);
	Print(console, result, _L("DeleteL") );
	
//Extract
	result = TestExtract(iLog, *editor);
	Print(console, result, _L("Extract") );
	
//GetLength
	result = TestGetLength(iLog, *editor);
	Print(console, result, _L("Length") );
	
//Reset
	result = TestReset(iLog, *editor);
	Print(console, result, _L("Reset") );
	
	Remove_Console(console);
	CleanupStack::PopAndDestroy(editor);
    // Case was executed
    return result;

    }

// -----------------------------------------------------------------------------
// CBCSmsUtilitiesTest::TestSmsInformationElement
// 
// -----------------------------------------------------------------------------
//
TInt CBCSmsUtilitiesTest::TestSmsInformationElementL( 
    TTestResult& aResult )
    {
	_LIT(KSmsInformationElement, "Calling CSmsInformationElement");
	iLog->Log(KSmsInformationElement);
	TInt result = KErrNone;
	RFs rfServer; 
    User::LeaveIfError(rfServer.Connect()); 
    
    CCnvCharacterSetConverter* characterSetConverter = CCnvCharacterSetConverter::NewL(); 
    CSmsBuffer* smsBuffer = CSmsBuffer::NewL(); 
	CSmsMessage* smsMessage = CSmsMessage::NewL(rfServer, CSmsPDU::ESmsCommand, smsBuffer ); 	
	CSmsCommand& command = STATIC_CAST(CSmsCommand&, smsMessage->SmsPDU() );
	
	CSmsInformationElement::TSmsInformationElementIdentifier identifier = CSmsInformationElement::ESmsIEIConcatenatedShortMessages8BitReference;
	TBufC8<24> information(KTestInfo8);
	command.AddInformationElementL( identifier, information);
	
	CSmsInformationElement& element = command.InformationElement(0);	
	CSmsInformationElement *ptrElement = &element;
	CleanupStack::PushL(ptrElement);
	
	CConsoleBase* console = Create_ConsoleL(_L("CSmsInformationElement"));
//Construction
//Get Identifier
	result = TestGetIdentifier(iLog, element);
	Print(console, result, _L("Identifier") );
	
//Get data (TPtr8)
	result = TestGetDataTPtr8(iLog, element);
	Print(console, result, _L("TPtr8 Data") );
	
//Get data (TDesC8)
	result = TestGetDataTDesC8(iLog, element);
	Print(console, result, _L("TDesC8 Data") );
	
	Remove_Console(console);
	CleanupStack::PopAndDestroy(&element);
	rfServer.Close();
	
	// Case was executed
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CBCSmsUtilitiesTest::TestSmsMessage
// Simple printing to UI test.
// -----------------------------------------------------------------------------
//
TInt CBCSmsUtilitiesTest::TestSmsMessageL( 
    TTestResult& aResult )
    {
 	_LIT(KSmsMessage, "Calling CSmsMessage");
	iLog->Log(KSmsMessage);
	TInt result = KErrNone;
	
	RFs rfServer; 
    User::LeaveIfError(rfServer.Connect()); 
    
    CCnvCharacterSetConverter* characterSetConverter = CCnvCharacterSetConverter::NewL(); 
    CSmsBuffer* smsBuffer = CSmsBuffer::NewL(); 
  
  	//static CSmsMessage* NewL(RFs& aFs, CSmsPDU::TSmsPDUType aType,CSmsBufferBase* aBuffer
	//,TBool aIsRPError=EFalse);    
	CSmsMessage* message = CSmsMessage::NewL(rfServer, CSmsPDU::ESmsDeliver, smsBuffer ); 	
	CleanupStack::PushL( message ); 
	
	CConsoleBase* console = Create_ConsoleL(_L("CSmsMessage"));
	
//Construction (TGsmSms)
	result = TestConstructionTGsmSms_MessageL(iLog);
		
//Destruction
//Get type
	result = TestGetType(iLog, *message);
	Print(console, result, _L("Type") );
		
//Get is complete
	result = TestGetIsComplete(iLog, *message);
	Print(console, result, _L("IsComplete") );
	
//Get is decoded
	result = TestIsDecoded(iLog, *message);
	Print(console, result, _L("IsDecoded") );
	
//Set storage
	result = TestSetStorage(iLog, *message);
	Print(console, result, _L("SetStorage") );
		
//Get storage
	result = TestGetStorage(iLog, *message);
	Print(console, result, _L("Storage") );
		
//Set status
	result = TestSetStatus(iLog, *message);
	Print(console, result, _L("SetStatus") );
		
//Get status
	result = TestGetStatus(iLog, *message);
	Print(console, result, _L("Status") );
		
//Set log server id
	result = TestSetLogServerId(iLog, *message);
	Print(console, result, _L("SetLogServerId") );
		
//Get log server id
	result = TestGetLogServerId(iLog, *message);
	Print(console, result, _L("LogServerId") );
	
//Set time
	result = TestSetTime(iLog, *message);
	Print(console, result, _L("SetTime") );
			
//Get time
	result = TestGetTimeL(iLog, *message);
	Print(console, result, _L("Time") );
		
//Get SMS PDU
	result = TestGetSMSPduL(iLog, *message);
	Print(console, result, _L("SmsPDU") );
		
//Get SMS PDU const
	result = TestGetSMSPDUConst(iLog, *message);
	Print(console, result, _L("SmsPDU const") );
		
//Set service center address
	result = TestSetServiceCenterAddress(iLog, *message);
	Print(console, result, _L("SetSeviceCenterAddress") );
		
//Get service center address
	result = TestGetServiceCenterAddress(iLog, *message);
	Print(console, result, _L("SeviceCenterAddress") );
	
//Set parsed service center address
	result = TestSetParsedServiceCenterAddress(iLog, *message);
	Print(console, result, _L("SetParsedServiceCenterAddress") );
		
//Get parsed service center address
	result = TestGetParsedServiceCenterAddress(iLog, *message);
	Print(console, result, _L("ParsedServiceCenterAddress") );
		
//Set to from address
	result = TestSetToFromAddress(iLog, *message);
	Print(console, result, _L("SetToFromAddressL") );
		
//Get to from address
	result = TestGetToFromAddress(iLog, *message);
	Print(console, result, _L("ToFromAddress") );
		
//Set parsed to from address
	result = TestSetParsedToFromAddress(iLog, *message);
	Print(console, result, _L("SetParsedToFromAddressL") );
		
//Get parsed to from address
	result = TestGetParsedToFromAddress(iLog, *message);
	Print(console, result, _L("ParsedToFromAddress") );
		
//Externalize without buffer
	result = TestExternalizeWithoutBufferL(iLog, *message);
	Print(console, result, _L("ExternalizeWithoutBuffer") );
		
//Internalize without buffer
	result = TestInternalizeWithoutBufferL(iLog, *message);
	Print(console, result, _L("InternalizeWithoutBuffer") );
		
//Externalize
	result = TestExternalizeL(iLog, *message);
	Print(console, result, _L("Externalize") );
		
//Internalize
	result = TestInternalizeL(iLog, *message);
	Print(console, result, _L("Internalize") );
		
//Get buffer
	result = TestGetBufferL(iLog, *message);
	Print(console, result, _L("Buffer") );
		
//Get buffer const
	result = TestGetBufferConstL(iLog, *message);
	Print(console, result, _L("Buffer const") );
		
//Get text present
	result = TestGetTextPresent(iLog, *message);
	Print(console, result, _L("TextPresent") );
		
//Get number of message PDUs
	result = TestGetNumberOfMessagePduL(iLog, *message);
	Print(console, result, _L("NumMessagePDUsL") );
		
//Get max message length
	result = TestGetMaxLength(iLog, *message);
	Print(console, result, _L("MaxMessagelength") );
		
//Get message length
	result = TestGetMessageLength(iLog, *message);
	Print(console, result, _L("MessageLengthL") );
		
//Set user data settings
//Get user data settings
//Cannot be executed

//Optimize settings
	result = TestOptimizeSettings(iLog, *message);
	Print(console, result, _L("OptimizeSettings") );
		
//Get is supported
	result = TestGetIsSupported(iLog, *message);
	Print(console, result, _L("IsSupported") );
		
//Encode message PDUs
	result = TestEncodeMessagePDUL(iLog, *message);
	Print(console, result, _L("EncodeMessagePDUsL") );
		
//Decode message PDUs
	result = TestDecodeMessagePDUL(iLog, *message);
	Print(console, result, _L("DecodeMessagePDUsL") );
		
//Add EMS information elements
//This currently does not work, changes in build required
/*	result = TestAddEMSInformationElements(iLog, *message);
	Print(console, result, _L("AddEMSInformationElements") );
*/		
//Copy EMS elements
	result = TestCopyEMSElementsL(iLog, *message);
	Print(console, result, _L("CopyEMSElements") );
		
//Get EMS information elements
	result = TestGetEMSInformationElements(iLog, *message);
	Print(console, result, _L("EMSInformationElements") );
		
//Remove EMS information elements
	result = TestRemoveEMSInformationElements(iLog, *message);
	Print(console, result, _L("RemoveEMSInformationElements") );
		
//Remove EMS information element
	result = TestRemoveEMSInformationElement(iLog, *message);
	Print(console, result, _L("RemoveEMSInformationElement") );
		
//Reset EMS
	result = TestResetEMS(iLog, *message);
	Print(console, result, _L("ResetEMS") );
		
//Encode into single PDU
	result = TestEncodeIntoSinglePDUL(iLog, *message);
	Print(console, result, _L("EncodeIntoSinglePDU") );
		
//Add slot
	result = TestAddSlot(iLog, *message);
	Print(console, result, _L("AddSlot") );
		
//Match slots
	result = TestMatchSlotsL(iLog, *message);
	Print(console, result, _L("MatchSlots") );
		
//Add email header
	result = TestAddEmailHeader(iLog, *message);
	Print(console, result, _L("AddEmailHeader") );
		
//Get is email header
	result = TestGetIsEmailHeader(iLog, *message);
	Print(console, result, _L("IsEmailHeader") );
		
//Get email header
	result = TestGetEmailHeaderL(iLog, *message);
	Print(console, result, _L("EmailHeader") );
		
//Set is 16 bit concatenation
	result = TestSetIs16BitConcatenation(iLog, *message);
	Print(console, result, _L("Is16BitConcatenation") );
		
//Get is 16 bit concatenation
	result = TestGetIs16BitConcatenation(iLog, *message);
	Print(console, result, _L("Is16BitConcatenation") );
		
//Update slots
	result = TestUpdateSlotsL(iLog, *message);
	Print(console, result, _L("UpdateSlots") );

//GetEncodingInfoL	
	result = TestGetEncodingInfoL(iLog, *message);
	Print(console, result, _L("GetEncodingInfoL") );

//SetAlternative7bitEncoding	
	result = TestSetAlternative7bitEncoding(iLog, *message);
	Print(console, result, _L("SetAlternative7bitEncoding") );
	
//Get is supported2
	result = TestGetIsSupported2(iLog, *message);
	Print(console, result, _L("IsSupported2") );

	Remove_Console(console);
	CleanupStack::PopAndDestroy(message);
	rfServer.Close();
    // Case was executed
    return result;

    }

// -----------------------------------------------------------------------------
// CBCSmsUtilitiesTest::TestSmsPDU
// Simple printing to UI test.
// -----------------------------------------------------------------------------
//
TInt CBCSmsUtilitiesTest::TestSmsPDUL( 
    TTestResult& aResult )
    {
    _LIT(KSmsPDU, "Calling CSmsPDU");
	iLog->Log(KSmsPDU);
	TInt result = KErrNone;
	CCnvCharacterSetConverter* characterSetConverter = CCnvCharacterSetConverter::NewL(); 
	CleanupStack::PushL(characterSetConverter);
		
	//static CSmsPDU* NewL(TSmsPDUType aType,CCnvCharacterSetConverter& aCharacterSetConverter,RFs& aFs,TBool aIsRPError=EFalse);
	CSmsPDU* PDU = CSmsPDU::NewL(CSmsPDU::ESmsDeliver, *characterSetConverter, iSession);
	CleanupStack::PushL(PDU);	
	
	//static CSmsPDU* NewL(TSmsPDUType aType,CCnvCharacterSetConverter& aCharacterSetConverter,RFs& aFs,TBool aIsRPError=EFalse);
	CSmsPDU* PDUReport = CSmsPDU::NewL(CSmsPDU::ESmsDeliverReport, *characterSetConverter, iSession);
	CleanupStack::PushL(PDUReport);

	CConsoleBase* console = Create_ConsoleL(_L("CSmsPDU"));
//Construction (RReadStream)
	result = TestConstructionStreamL(iLog, *PDU);
	
//Construction (TGsmSms)
	result = TestConstructionTGsmSms_PduL(iLog, *PDU);

//Get type
	result = TestGetType(iLog, *PDU);
	Print(console, result, _L("Type") );

//Externalize
	result = TestExternalizeL(iLog, *PDU);
	Print(console, result, _L("Externalize") );
	
//Encode message PDUs	
	result = TestEncodeMessagePDUs(iLog, *PDU);
	Print(console, result, _L("EncodeMessagePDUs") );
	
//Set service center address
	result = TestSetServiceCenterAddress(iLog, *PDU);
	Print(console, result, _L("SetServiceCenterAddress") );
	
//Get service center address
	result = TestGetServiceCenterAddress(iLog, *PDU);
	Print(console, result, _L("ServiceCenterAddress") );
	
//Set parsed service center address
	result = TestSetParsedServiceCenterAddress(iLog, *PDU);
	Print(console, result, _L("SetParsedServiceCenterAddress") );
	
//Get parsed service center address
	result = TestGetParsedServiceCenterAddress(iLog, *PDU);
	Print(console, result, _L("ParsedServiceCenterAddress") );
	
//Set to from address
	result = TestSetToFromAddress(iLog, *PDU);
	Print(console, result, _L("SetToFromAddress") );
	
//Get to from address
	result = TestGetToFromAddress(iLog, *PDU);
	Print(console, result, _L("ToFromAddress") );
	
//Set parsed to from address
	result = TestSetParsedToFromAddress(iLog, *PDU);
	Print(console, result, _L("SetParsedToFromAddress") );

//Get parsed to from address	
	result = TestGetParsedToFromAddress(iLog, *PDU);
	Print(console, result, _L("ParsedToFromAddress") );
	
//Set bits 7 to 4
	result = TestSetBits7To4(iLog, *PDU);
	Print(console, result, _L("SetBits7To4") );

//Get bits 7 to 4
	result = TestGetBits7To4(iLog, *PDU);
	Print(console, result, _L("Bits7To4") );
	
//Set alphabet
	result = TestSetAlphabet(iLog, *PDU);
	Print(console, result, _L("SetAlphabet") );
	
//Get alphabet
	result = TestGetAlphabet(iLog, *PDU);
	Print(console, result, _L("Alphabet") );
	
//Set class
	result = TestSetClass(iLog, *PDU);
	Print(console, result, _L("SetClass") );
	
//Get class
	result = TestGetClass(iLog, *PDU);
	Print(console, result, _L("Class") );
	
//Set text compressed
	result = TestSetTextCompressed(iLog, *PDU);
	Print(console, result, _L("SetTextCompressed") );
	
//Get text compressed
	result = TestGetTextCompressed(iLog, *PDU);
	Print(console, result, _L("TextCompressed") );
	
//Set indication state
	result = TestSetIndicationState(iLog, *PDU);
	Print(console, result, _L("SetIndicationState") );
	
//Get indication state	
	result = TestGetIndicationState(iLog, *PDU);
	Print(console, result, _L("IndicationState") );
	
//Set indication type
	result = TestSetIndicationType(iLog, *PDU);
	Print(console, result, _L("SetIndicationType") );
	
//Get indication type
	result = TestGetIndicationType(iLog, *PDU);
	Print(console, result, _L("IndicationType") );
	
//Set text concatenated
	result = TestSetTextConcatenated(iLog, *PDU);
	Print(console, result, _L("SetTextConcatenated") );
	
//Get text concatenated
	result = TestGetTextConcatenated(iLog, *PDU);
	Print(console, result, _L("TextConcatenated") );
	
//Set concatenated message reference
	result = TestSetConcatenatedMessageReference(iLog, *PDU);
	Print(console, result, _L("SetConcatenatedMessageReference") );
	
//Get concatenated message reference
	result = TestGetConcatenatedMessageReference(iLog, *PDU);
	Print(console, result, _L("ConcatenatedMessageReference") );
	
//Set number of concatenated message PDUs
	result = TestSetNumberOfConcatenatedMessageL(iLog, *PDU);
	Print(console, result, _L("SetNumberOfConcatenatedMessage") );
	
//Get number of concatenated message PDUs
	result = TestGetNumberOfConcatenatedMessageL(iLog, *PDU);
	Print(console, result, _L("NumberOfConcatenatedMessage") );
	
//Set concatenated message PDU index	
	result = TestSetConcatenatedMessagePDUIndex(iLog, *PDU);
	Print(console, result, _L("SetConcatenatedMessagePDUIndex") );
	
//Get concatenated message PDU index
	result = TestGetConcatenatedMessagePDUIndex(iLog, *PDU);
	Print(console, result, _L("ConcatenatedMessagePDUIndex") );
	
//set application port addressing
	result = TestSetApplicationPortAddressing(iLog, *PDU);
	Print(console, result, _L("SetApplicationPortAddressing") );
	
//Get application port addressing
	result = TestGetApplicationPortAddressing(iLog, *PDU);
	Print(console, result, _L("ApplicationPortAddressing") );
	
//set PID type
	result = TestSetPIDType(iLog, *PDU);
	Print(console, result, _L("SetPIDType") );
	
//Get PID type
	result = TestGetPIDType(iLog, *PDU);
	Print(console, result, _L("PIDType") );
	
//Set short message type
	result = TestSetShortMessageType(iLog, *PDU);
	Print(console, result, _L("SetShortMessageType") );
	
//Get short message type
	result = TestGetShortMessageType(iLog, *PDU);
	Print(console, result, _L("ShortMessageType") );
	
//Set telematic device indicator
	result = TestSetTelematicDeviceIndicator(iLog, *PDU);
	Print(console, result, _L("SetTelematicDeviceIndicator") );
	
//Get telematic device indicator
	result = TestGetTelematicDeviceIndicator(iLog, *PDU);
	Print(console, result, _L("TelematicDeviceIndicator") );
	
//Set telematic device type
	result = TestSetTelematicDeviceType(iLog, *PDU);
	Print(console, result, _L("SetTelematicDeviceType") );
	
//Get telematic device type
	result = TestGetTelematicDeviceType(iLog, *PDU);
	Print(console, result, _L("TelematicDeviceType") );
	
//Get user data
	result = TestGetUserData(iLog, *PDU);
	Print(console, result, _L("UserData") );
	
//Get user data const
	result = TestGetUserDataConst(iLog, *PDU);
	Print(console, result, _L("UserDataConst") );

//Set user data present
	result = TestSetUserDataPresent(iLog, *PDUReport);
	Print(console, result, _L("SetUserDataPresent") );	
	
//Get user data present
	result = TestGetUserDataPresent(iLog, *PDUReport);
	Print(console, result, _L("UserDataPresent") );
	
//Set data coding scheme present
	result = TestSetDataCodingSchemePresent(iLog, *PDUReport);
	Print(console, result, _L("SetDataCodingSchemePresent") );
	
//Get data coding scheme present
	result = TestGetDataCodingSchemePresent(iLog, *PDUReport);
	Print(console, result, _L("DataCodingSchemePresent") );
	
//Set protocol identifier present
	result = TestSetProtocolIdentifierPresent(iLog, *PDUReport);
	Print(console, result, _L("SetProtocolIdentifierPresent") );
	
//Get protocol identifier present
	result = TestGetProtocolIdentifierPresent(iLog, *PDUReport);
	Print(console, result, _L("ProtocolIdentifierPresent") );

//Set national language encoding
	result = TestSetNationalLanguageEncodingL(iLog, *PDUReport);
	Print(console, result, _L("SetNationalLanguageEncodingL") );
		
//DuplicateL
	result = TestSmsPDUDuplicateL(iLog, *PDUReport);
	Print(console, result, _L("SmsPDUDuplicateL"));
	
	Remove_Console(console);
	CleanupStack::PopAndDestroy(3);
	return KErrNone;
    }

// -----------------------------------------------------------------------------
// CBCSmsUtilitiesTest::TestSmsStatusReport
// Simple printing to UI test.
// -----------------------------------------------------------------------------
//
TInt CBCSmsUtilitiesTest::TestSmsStatusReportL( 
    TTestResult& aResult )
    {
  	_LIT(KSmsStatusReport, "Calling CSmsStatusReport");
	iLog->Log(KSmsStatusReport);
	TInt result = KErrNone;
		
	RFs rfServer; 
    User::LeaveIfError(rfServer.Connect()); 
    
    CCnvCharacterSetConverter* characterSetConverter = CCnvCharacterSetConverter::NewL(); 
    CSmsBuffer* smsBuffer = CSmsBuffer::NewL(); 
	CSmsMessage* smsMessage = CSmsMessage::NewL(rfServer, CSmsPDU::ESmsStatusReport, smsBuffer ); 	

	CSmsStatusReport& statusReport = STATIC_CAST(CSmsStatusReport&, smsMessage->SmsPDU() );
	CSmsStatusReport *ptrStatusReport = &statusReport;
	CleanupStack::PushL(ptrStatusReport);

	CConsoleBase* console = Create_ConsoleL(_L("CSmsStatusReport"));
//Construction
//Set parameter indicator present
	result = TestSetParameterIndicatorPresent(iLog, statusReport);
	Print(console, result, _L("SetIsRPError"));
	
//Get parameter indicator present
	result = TestGetParameterIndicatorPresent(iLog, statusReport);
	Print(console, result, _L("IsRPError"));
	
//Set more messages to send
	result = TestSetMoreMessagesToSend(iLog, statusReport);
	Print(console, result, _L("SetFailureCause"));
	
//Get more messages to send
	result = TestGetMoreMessagesToSend(iLog, statusReport);
	Print(console, result, _L("FailureCause"));
	
//Set status report qualifier
	result = TestSetStatusReportQualifier(iLog, statusReport);
	Print(console, result, _L("DataCodingScheme"));
	
//Get status report qualifier
	result = TestGetStatusReportQualifier(iLog, statusReport);
	Print(console, result, _L("ProtocolIdentifier"));
	
//Set message reference
	result = TestSetMessageReference(iLog, statusReport);
	Print(console, result, _L("SetMessageReference"));
	
//Get message reference
	result = TestGetMessageReference(iLog, statusReport);
	Print(console, result, _L("MessageReference"));
	
//Set service center time stamp
	result = TestSetServiceCenterTimeStamp(iLog, statusReport);
	Print(console, result, _L("UserDataPointer"));
	
//Get service center time stamp
	result = TestGetServiceCenterTimeStampL(iLog, statusReport);
	Print(console, result, _L("Encode"));
	
//Set discharge time
	result = TestSetDischargeTime(iLog, statusReport);
	Print(console, result, _L("Decode"));
	
//Get discharge time
	result = TestGetDischargeTimeL(iLog, statusReport);
	Print(console, result, _L("Decode"));
	
//Set status
	result = TestSetStatus(iLog, statusReport);
	Print(console, result, _L("SetStatus"));
	
//Get status
	result = TestGetStatus(iLog, statusReport);
	Print(console, result, _L("Status"));
	
//DuplicateL
	result = TestSmsStatusReportDuplicateL(iLog, statusReport);
	Print(console, result, _L("SmsStatusReportDuplicateL"));
	
	Remove_Console(console);
	CleanupStack::PopAndDestroy(&statusReport);
	rfServer.Close();
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CBCSmsUtilitiesTest::TestSmsSubmit
// Simple printing to UI test.
// -----------------------------------------------------------------------------
//
TInt CBCSmsUtilitiesTest::TestSmsSubmitL( 
    TTestResult& aResult )
    {
    _LIT(KSmsSubmit, "Calling CSmsSubmit");
	iLog->Log(KSmsSubmit);
	TInt result = KErrNone;
		
	RFs rfServer; 
    User::LeaveIfError(rfServer.Connect()); 
    
    CCnvCharacterSetConverter* characterSetConverter = CCnvCharacterSetConverter::NewL(); 
    CSmsBuffer* smsBuffer = CSmsBuffer::NewL(); 
	CSmsMessage* smsMessage = CSmsMessage::NewL(rfServer, CSmsPDU::ESmsSubmit, smsBuffer ); 	

	CSmsSubmit& submit = STATIC_CAST(CSmsSubmit&, smsMessage->SmsPDU() );
	CSmsSubmit *ptrSubmit = &submit;
	CleanupStack::PushL(ptrSubmit);
	
	CConsoleBase* console = Create_ConsoleL(_L("CSmsSubmit"));
//Construction
//Set reject duplicates
	result = TestSetRejectDuplicates(iLog, submit);
	Print(console, result, _L("SetRejectDuplicates"));
	
//Get reject duplicates
	result = TestGetRejectDuplicates(iLog, submit);
	Print(console, result, _L("RejectDuplicates"));
	
//Set validity period format
	result = TestSetValidityPeriodFormat(iLog, submit);
	Print(console, result, _L("SetValidityPeriodFormat"));
	
//Get validity period format
	result = TestGetValidityPeriodFormat(iLog, submit);
	Print(console, result, _L("ValidityPeriodFormat"));
	
//Set reply path
	result = TestSetReplyPath(iLog, submit);
	Print(console, result, _L("SetReplyPath"));
	
//Get reply path
	result = TestGetReplyPath(iLog, submit);
	Print(console, result, _L("ReplyPath"));
	
//Set status report request	
	result = TestSetStatusReportRequest(iLog, submit);
	Print(console, result, _L("SetStatusReportRequest"));
	
//Get status report request	
	result = TestGetStatusReportRequest(iLog, submit);
	Print(console, result, _L("StatusReportRequest"));
	
//Set message reference
	result = TestSetMessageReference(iLog, submit);
	Print(console, result, _L("SetMessageReferenc"));
	
//Get message reference
	result = TestGetMessageReference(iLog, submit);
	Print(console, result, _L("MessageReference"));
	
//Set validity period
	result = TestSetValidityPeriod(iLog, submit);
	Print(console, result, _L("SetValidityPeriod"));
	
//Get validity period
	result = TestGetValidityPeriod(iLog, submit);
	Print(console, result, _L("ValidityPeriod"));

//DuplicateL
	result = TestSmsSubmitDuplicateL(iLog, submit);
	Print(console, result, _L("SmsSubmitDuplicateL"));
	
	Remove_Console(console);
	CleanupStack::PopAndDestroy(&submit);
	rfServer.Close();
// Case was executed
   return KErrNone;

    }

// -----------------------------------------------------------------------------
// CBCSmsUtilitiesTest::TestSmsSubmitReport
// Simple printing to UI test.
// -----------------------------------------------------------------------------
//
TInt CBCSmsUtilitiesTest::TestSmsSubmitReportL( 
    TTestResult& aResult )
    {
    _LIT(KSmsSubmitReport, "Calling CSmsSubmitReport");
	iLog->Log(KSmsSubmitReport);
	TInt result = KErrNone;
		
	RFs rfServer; 
    User::LeaveIfError(rfServer.Connect()); 
    
    CCnvCharacterSetConverter* characterSetConverter = CCnvCharacterSetConverter::NewL(); 
    CSmsBuffer* smsBuffer = CSmsBuffer::NewL(); 
	CSmsMessage* smsMessage = CSmsMessage::NewL(rfServer, CSmsPDU::ESmsSubmitReport, smsBuffer ); 	

	CSmsSubmitReport& submitReport = STATIC_CAST(CSmsSubmitReport&, smsMessage->SmsPDU() );
	CSmsSubmitReport *ptrSubmitReport = &submitReport;
	CleanupStack::PushL(ptrSubmitReport);

	CConsoleBase* console = Create_ConsoleL(_L("CSmsSubmitReport"));
//Construction
//Set is RP error
	result = TestSetIsRPError(iLog, submitReport);
	Print(console, result, _L("SetIsRPError"));
	
//Get is RP error
	result = TestGetIsRPError(iLog, submitReport);
	Print(console, result, _L("IsRPError"));
	
//Set failure cause
	result = TestSetFailureCause(iLog, submitReport);
	Print(console, result, _L("SetFailureCause"));
	
//Get failure cause
	result = TestGetFailureCause(iLog, submitReport);
	Print(console, result, _L("FailureCause"));
	
//DuplicateL
	result = TestSmsSubmitReportDuplicateL(iLog, submitReport);
	Print(console, result, _L("SmsSubmitReportDuplicateL"));
	
	Remove_Console(console);
	CleanupStack::PopAndDestroy(&submitReport);
	rfServer.Close();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CBCSmsUtilitiesTest::TestSmsUserData
// Simple printing to UI test.
// -----------------------------------------------------------------------------
//
TInt CBCSmsUtilitiesTest::TestSmsUserDataL( 
    TTestResult& aResult )
    {
    _LIT(KSmsUserData, "Calling CSmsUserData");
	iLog->Log(KSmsUserData);
	TInt result = KErrNone;
	
	CCnvCharacterSetConverter* characterSetConverter = CCnvCharacterSetConverter::NewL(); 
	//static CSmsPDU* NewL(TSmsPDUType aType,CCnvCharacterSetConverter& aCharacterSetConverter,RFs& aFs,TBool aIsRPError=EFalse);
	CSmsPDU* PDU = CSmsPDU::NewL(CSmsPDU::ESmsDeliver, *characterSetConverter, iSession);
		
	CSmsUserData& userData = STATIC_CAST(CSmsUserData&, PDU->UserData() );
	CSmsUserData *ptrUserData = &userData;
	CleanupStack::PushL(ptrUserData);

	CConsoleBase* console = Create_ConsoleL(_L("CSmsUserData"));
	
//Add information element
	result = TestAddInformationElement(iLog, userData);
	Print(console, result, _L("AddInformationElement"));
   		
//Get number of information elements
  result = TestGetNumberOfInformationElements(iLog, userData);
 	Print(console, result, _L("NumInformationElement"));
   	
//Get information element   	
	result = TestGetInformationElement(iLog, userData);
	Print(console, result, _L("InformationElement"));
   		
//Get information element index
	result = TestGetInformationElementIndex(iLog, userData);
	Print(console, result, _L("InformationElementIndex"));
	

//Remove information element
	result = TestRemoveInformationElement(iLog, userData);
	Print(console, result, _L("RemoveInformationElement"));
   		
//Get max body length in chars
	result = TestMaxBodyLengthInChars(iLog, userData);
	Print(console, result, _L("MaxBodyLengthInChars"));
   		
//Set body
	result = TestSetBody(iLog, userData);
	Print(console, result, _L("SetBody"));
   		
//Get is supported
	result = TestGetIsSupported(iLog, userData);
	Print(console, result, _L("IsSupported"));

//Get is supported2
	result = TestGetIsSupported2(iLog, userData);
	Print(console, result, _L("IsSupported2"));   

//Get is supported3
	result = TestGetIsSupported3(iLog, userData);
	Print(console, result, _L("IsSupported3")); 
			
//Get body
	result = TestGetBody(iLog, userData);
	Print(console, result, _L("GetBody"));
   		
    Remove_Console(console);
	CleanupStack::PopAndDestroy(&userData);
    // Case was executed
    return KErrNone;

    }

//  End of File
