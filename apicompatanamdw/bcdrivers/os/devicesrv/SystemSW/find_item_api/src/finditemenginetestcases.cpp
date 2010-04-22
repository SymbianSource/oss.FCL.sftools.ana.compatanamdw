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
* Description:  This module contains the implementation of Cfinditemenginetest class 
*				 member functions that does the actual tests.
*
*/

/* Changed by Vaibhav - 13Aug07 for Removing CodeScanner Warnings - High/medium */


// INCLUDE FILES
#include <e32math.h>
#include "Finditemenginetest.h"
#include <finditemengine.h>

#include    <e32std.h>
#include    <s32file.h>

// EXTERNAL DATA STRUCTURES
// None

// EXTERNAL FUNCTION PROTOTYPES  
// None

// CONSTANTS
// None

// MACROS
// None

// LOCAL CONSTANTS AND MACROS

static const TInt KREADBUFSIZE( 256 );
static const TInt FULLBUFSIZE( 10000 );


// MODULE DATA STRUCTURES
// None

// LOCAL FUNCTION PROTOTYPES
// None

// FORWARD DECLARATIONS
// None

// ==================== LOCAL FUNCTIONS =======================================


// ================= MEMBER FUNCTIONS =========================================
 
// -----------------------------------------------------------------------------
// Cfinditemenginetest::Case
// Returns a test case by number.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
const TCaseInfo Cfinditemenginetest::Case ( 
		const TInt aCaseNumber ) const //test case number
     {

    // To add new test cases, implement new test case function and add new 
    // line to KCases array specify the name of the case and the function 
    // doing the test case
    // In practice, do following
    // 1) Make copy of existing function and change it name
    // 2) Duplicate the last line in cases array 
    // 3) Change case name and function name in case array

    static TCaseInfoInternal const KCases[] =
        {
  
        // To add new test cases, add new items to this array
			{(TText*) L"[FindItemEngine] SearchURLs",			GETPTR SearchURLs},
			{(TText*) L"[FindItemEngine] SearcheEmailAdresses",	GETPTR SearchEMailAddresses},
			{(TText*) L"[FindItemEngine] SearchPhoneNumbers",	GETPTR SearchPhoneNumbers},
			{(TText*) L"[FindItemEngine] SearchAll",			GETPTR SearchAll},
			{(TText*) L"[FindItemEngine] CheckPositions",		GETPTR CheckPositions},
			{(TText*) L"[FindItemEngine] ParseURLFile",			GETPTR ParseURIFile}
        };

    // Verify that case number is valid
    if( (TUint) aCaseNumber >= sizeof( KCases ) / 
                               sizeof( TCaseInfoInternal ) )
        {

        // Invalid case, construct empty object
        TCaseInfo null( (const TText*) L"" );
        null.iMethod = NULL;
        return null;

        } 

    // Construct TCaseInfo object and return it
    TCaseInfo tmp ( KCases[ aCaseNumber ].iCaseName );
    tmp.iMethod = KCases[ aCaseNumber ].iMethod;
    return tmp;
     
    }
    
// -----------------------------------------------------------------------------
// Cfinditemenginetest::SearchURLs
// Searches for URLs in the string.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cfinditemenginetest::SearchURLs( 
		TTestResult& aResult ) // Test case result
    {
     
		aResult.iResult = KErrNone;

		_LIT16(KTextToBeParsed, "tekstii... http://www.google.com jeba jee elvis.presley@hotmail.com 0700-123123 127.0.0.1 roskaa");
		_LIT16(KURL2, "127.0.0.1");
		TBufC<512> str(KTextToBeParsed);
		
		_LIT16(KURL1, "http://www.google.com"); // TeK 23.8.2005: added http:// also when flag defined
		CFindItemEngine* eng;
		TRAPD(err, eng = CFindItemEngine::NewL(KTextToBeParsed, CFindItemEngine::EFindItemSearchURLBin));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}
				
		// Get count of found URL:s
		TInt count( eng->ItemCount() );
		
		TRAP(err, test(count == 2));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

		// Get currently selected URL
		CFindItemEngine::SFoundItem item;
		eng->Item(item);
		TPtrC16 result1(str.Mid(item.iStartPos, item.iLength));
		aResult.iResultDes.Copy( result1);

		// Get next found URL
		eng->NextItem(item);
		TPtrC16 result2(str.Mid(item.iStartPos, item.iLength));
		aResult.iResultDes.Copy( result2);

		delete eng;
		aResult.iResult = test(result1.Compare(KURL1) == 0 && result2.Compare(KURL2) == 0);

		return KErrNone;
    
    }


    
// -----------------------------------------------------------------------------
// Cfinditemenginetest::SearchEMailAddresses
// Searches for certain email address from the string.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cfinditemenginetest::SearchEMailAddresses( TTestResult& aResult )
    {
		aResult.iResult = KErrGeneral;

		_LIT16(KTextToBeParsed, "tekstii... http://www.google.com jeba jee elvis.presley@hotmail.com 0700-123123 127.0.0.1 roskaa");
		_LIT16(KEMail, "elvis.presley@hotmail.com");
		
		CFindItemEngine* eng;
		TRAPD(err, eng = CFindItemEngine::NewL(KTextToBeParsed, CFindItemEngine::EFindItemSearchMailAddressBin));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}
		
		TBufC<512> str(KTextToBeParsed);
		
		// Get count of found email addresses
		TInt count( eng->ItemCount() );
		aResult.iResultDes = _L("Leaves now if ItemCount is not 1");

		TRAP(err, test(count == 1));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

		// Get currently selected email
		CFindItemEngine::SFoundItem item;
		eng->Item(item);
		TPtrC16 result1(str.Mid(item.iStartPos, item.iLength));
		aResult.iResultDes.Copy(result1);

		// Try to get next email address, should fail
		aResult.iResultDes = _L("Leaves now if finds next item");
		TRAP(err, test(eng->NextItem(item) == EFalse));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

		delete eng;

		aResult.iResult = test(result1.Compare(KEMail) == 0);

		return KErrNone;

	}

     
// -----------------------------------------------------------------------------
// Cfinditemenginetest::SearchPhoneNumbers
// Searches for certain phone numbers from the string.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cfinditemenginetest::SearchPhoneNumbers( TTestResult& aResult )
    {
		aResult.iResult = KErrGeneral;

		_LIT16(KTextToBeParsed, "tekstii... http://www.google.com jeba jee elvis.presley@hotmail.com 0700-123123 habaha 123 45678910? 127.0555.0555 roskaa 1.3.4.5.6.7.8.9 laatikos a");
		_LIT16(KPhoneNro1, "0700-123123");
		_LIT16(KPhoneNro2, "123 45678910");
		_LIT16(KPhoneNro3, "127.0555.0555");
		_LIT16(KPhoneNro4, "1.3.4.5.6.7.8.9");

		CFindItemEngine* eng;
		TRAPD(err, eng = CFindItemEngine::NewL(KTextToBeParsed, CFindItemEngine::EFindItemSearchPhoneNumberBin));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}
		
		TBufC<512> str(KTextToBeParsed);
		
		// Get count of found email addresses
		TInt count( eng->ItemCount() );
		aResult.iResultDes = _L("Leaves now if ItemCount is not 4");
		TRAP(err, test(count == 4));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

		// Get currently selected phone number
		CFindItemEngine::SFoundItem item;
		eng->Item(item);
		TPtrC16 result1(str.Mid(item.iStartPos, item.iLength));
		aResult.iResultDes.Copy(result1);

		// Get next found number
		eng->NextItem(item);
		TPtrC16 result2(str.Mid(item.iStartPos, item.iLength));
		aResult.iResultDes.Copy(result2);

		// Get next found number
		eng->NextItem(item);
		TPtrC16 result3(str.Mid(item.iStartPos, item.iLength));
		aResult.iResultDes.Copy(result3);

		// Get next found number
		eng->NextItem(item);
		TPtrC16 result4(str.Mid(item.iStartPos, item.iLength));
		aResult.iResultDes.Copy(result4);

		// Get last found number again
		eng->PrevItem(item);
		TPtrC16 result5(str.Mid(item.iStartPos, item.iLength));
		aResult.iResultDes.Copy(result5);

		delete eng;

		aResult.iResult = test(result1.Compare(KPhoneNro1) == 0 &&
			result2.Compare(KPhoneNro2) == 0 &&
			result3.Compare(KPhoneNro3) == 0 &&
			result4.Compare(KPhoneNro4) == 0 &&
			result5.Compare(KPhoneNro3) == 0);

		

		return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// Cfinditemenginetest::SearchAll
// Searches for phone number, mail address and url's from the same string
// 
// -----------------------------------------------------------------------------
TInt Cfinditemenginetest::SearchAll( TTestResult& aResult )
    {
		
		aResult.iResult = KErrGeneral;

		//_LIT16(KTextToBeParsed, "tekstii... http://www.google.com jeba jee elvis.presley@hotmail.com 0700-123123 127.0.0.1 roskaa");
		_LIT16(KTextToBeParsed, "tekstii... http://www.google.com jeba jee elvis.presley@hotmail.com 0700-123123 habaha 123 45678910? 127.0.0.1 roskaa");
		_LIT16(KEMail, "elvis.presley@hotmail.com");
		_LIT16(KPhone, "0700-123123");

		_LIT16(KURL, "http://www.google.com"); // TeK 23.8.2005: added http:// also when flag defined
		CFindItemEngine* eng;
		TRAPD(err, eng = CFindItemEngine::NewL(KTextToBeParsed, CFindItemEngine::EFindItemSearchMailAddressBin));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}
		
		TBufC<512> str(KTextToBeParsed);
		
		// Get count of found email addresses
		//TInt count( eng->ItemCount() );
		//aResult.iResultDes = _L("Leaves now if ItemCount is not 1");

		//User::LeaveIfError(test(count == 1));

		// Get currently selected email
		CFindItemEngine::SFoundItem item;
		eng->Item(item);
		TPtrC16 result1(str.Mid(item.iStartPos, item.iLength));
		aResult.iResultDes.Copy(result1);
		
		//make a new search - search for URL
		TRAP(err, eng->DoNewSearchL(KTextToBeParsed, CFindItemEngine::EFindItemSearchURLBin));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}
		
		// Get currently selected phone number
		eng->Item(item);
		TPtrC16 result2(str.Mid(item.iStartPos, item.iLength));
		aResult.iResultDes.Copy(result2);

		//make a new search - search for phone number
		TRAP(err, eng->DoNewSearchL(KTextToBeParsed, CFindItemEngine::EFindItemSearchPhoneNumberBin));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}
		
		
		// Get selected phone number
		eng->Item(item);
		TPtrC16 result3(str.Mid(item.iStartPos, item.iLength));
		aResult.iResultDes.Copy(result3);
	
		delete eng;

		TInt result = result1.Compare(KEMail);
		result = result2.Compare(KURL);
		result = result3.Compare(KPhone);
		aResult.iResult = test(result1.Compare(KEMail) == 0 && result2.Compare(KURL) == 0 && result3.Compare(KPhone) == 0);
			
		return KErrNone;

	}

// -----------------------------------------------------------------------------
// Cfinditemenginetest::CheckPositions
// Searches for email addresses and verifies positions.
// 
// -----------------------------------------------------------------------------
TInt Cfinditemenginetest::CheckPositions( TTestResult& aResult )
    {
		
		aResult.iResult = KErrGeneral;

		_LIT16(KTextToBeParsed, "tekstii... http://www.google.com jeba jee elvis.presley@hotmail.com 0700-123123 habaha@luukku.com 123 45678910? lapalaa vielayksi@yahoo.com 127.0.0.1 roskaa");
		_LIT16(KEMail1, "elvis.presley@hotmail.com");
		_LIT16(KEMail2, "habaha@luukku.com");
		_LIT16(KEMail3, "vielayksi@yahoo.com");
		
		CFindItemEngine* eng;
		TRAPD(err, eng = CFindItemEngine::NewL(KTextToBeParsed, CFindItemEngine::EFindItemSearchMailAddressBin));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}
		
		TBufC<512> str(KTextToBeParsed);
		
		//Get count of found email addresses
		TInt count( eng->ItemCount() );
		aResult.iResultDes = _L("Leaves now if ItemCount is not 3");
//		User::LeaveIfError(test(count == 3));
		TRAP(err, test(count == 3));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}

		// Get currently selected email
		CFindItemEngine::SFoundItem item;
		eng->Item(item);
		TPtrC16 result1(str.Mid(item.iStartPos, item.iLength));
		aResult.iResultDes.Copy(result1);

		//move to next item
		eng->NextItem(item);
		TPtrC16 result2(str.Mid(item.iStartPos, item.iLength));
		aResult.iResultDes.Copy(result2);

		//check that position is correct
		aResult.iResultDes = _L("Leaves now if position is not 1");
		TRAP(err, test(eng->Position() == 1));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}
		
		//move to next item
		eng->NextItem(item);
		TPtrC16 result3(str.Mid(item.iStartPos, item.iLength));
		aResult.iResultDes.Copy(result3);

		//Resets the position to zero 
		eng->ResetPosition();
		//get the first item
		eng->Item(item);
		TPtrC16 reset_result1(str.Mid(item.iStartPos, item.iLength));
		aResult.iResultDes.Copy(reset_result1);

		//verify that we are in first item
		aResult.iResultDes = _L("Leaves now if first items don't match");
		TRAP(err, test(result1 == reset_result1));
		if(err != KErrNone)
		{
			aResult.iResult = err;
			return err;
		}
		
		delete eng;

		TInt result = result1.Compare(KEMail1);
		result = result2.Compare(KEMail2);
		result = result3.Compare(KEMail3);

		
		aResult.iResult = test(result1.Compare(KEMail1) == 0 && result2.Compare(KEMail2) == 0 && result3.Compare(KEMail3) == 0);


		return KErrNone;

	}


// -----------------------------------------------------------------------------
// Cfinditemenginetest::ParseURIFile
// Searches for URIs in a file and verifies
// 
// -----------------------------------------------------------------------------
TInt Cfinditemenginetest::ParseURIFile( TTestResult& aResult )
    {
		

		aResult.iResult = 0;
		RDebug::Print(_L("Test begins"));
        __UHEAP_MARK;
        //load test case text to string
        RFs rfs;
        TTime testStart;
        TTime testEnd;
        TInt64 elapsed;
		TInt i(0);

        TInt err = rfs.Connect();
        if ( err != KErrNone) 
			{
			User::InfoPrint(_L("Failed to connect file server session"));
			RDebug::Print(_L("Failed to connect file server session"));
            return err; // not cleaning up properly
            }

     _LIT( PARSETEXTFILE, "c:\\data\\others\\finditemtestappdata.txt" );
     _LIT( PARSETEXTFILE2, "c:\\data\\others\\FindItemTestAppDataReference.txt" );


        _LIT( BUFFERINITIALIZER, "" );
        RFile file;
        HBufC* fullBuf;
        TRAP(err, fullBuf = HBufC::NewMaxL(FULLBUFSIZE));
        if(err != KErrNone)
        {
        	aResult.iResult = err;
        	return err;
        }
        HBufC* fullBuf2;
        TRAP(err, fullBuf2 = HBufC::NewMaxL(FULLBUFSIZE));
        if(err != KErrNone)
        {
        	aResult.iResult = err;
        	return err;
        }
        TPtr fullBufAppend = fullBuf->Des();                  
        TPtr fullBufAppend2 = fullBuf2->Des();                  
        fullBufAppend = BUFFERINITIALIZER;
        fullBufAppend2 = BUFFERINITIALIZER;

		TFileText reader;
        TBuf<KREADBUFSIZE> readBuf;

		if ( file.Open(rfs, PARSETEXTFILE, EFileStreamText|EFileRead|EFileShareAny) == KErrNone )
			{
            // use TFileText for reading file. There is probably better ways to do this tho.
            reader.Set(file);
            if ( reader.Seek(ESeekStart) )
				{
				User::InfoPrint(_L("File corrupted"));
                return KErrGeneral; // not cleaning up properly
                }


            while ( !reader.Read(readBuf) )
            {
            fullBufAppend.Append(readBuf);
            fullBufAppend.Append('\n');   
            }

            file.Close();
            }
        else
            {


			_LIT(KInfo,"c:\\data\\others\\finditemtestappdata.txt not found");
			User::InfoPrint(KInfo);
            RDebug::Print(KInfo);




            }

		if ( file.Open(rfs, PARSETEXTFILE2, EFileStreamText|EFileRead|EFileShareAny) == KErrNone )
			{
            // use TFileText for reading file. There is probably better ways to do this tho.
            reader.Set(file);
            if ( reader.Seek(ESeekStart) )
				{
				User::InfoPrint(_L("File corrupted"));
                return KErrGeneral; // not cleaning up properly
                }

			}
        else
            {


			User::InfoPrint(_L("c:\\data\\others\\finditemtestappdataReference.txt not found"));
            RDebug::Print(_L("c:\\data\\others\\finditemtestappdataReference.txt not found"));


            }

        RDebug::Print(_L("Start searching..."));
                    
                        
		// now do the searches

        // SFoundItem instance
        CFindItemEngine::SFoundItem item;

        // Create an instance of FindItemEngine and search for URL:s.
        CFindItemEngine* eng;
        TRAP(err, eng = CFindItemEngine::NewL(fullBuf->Des(), CFindItemEngine::EFindItemSearchURLBin));
        if(err != KErrNone)
        {
        	aResult.iResult = err;
        	return err;
        }
        // Get count of found items:s
        TInt count(eng->ItemCount());

		RDebug::Print(_L("Found %d URLs:"), count);

        TBool found = eng->Item(item);

        for( i=0; i<count; i++)
			{
            if ( found )
				{
                TPtrC16 result(fullBuf->Des().Mid(item.iStartPos, item.iLength));
				reader.Read(readBuf);

				//Comparing parsed result to what read buffer reads from the file.
				if (!readBuf.Compare(result))
					{
					RDebug::Print(_L("Compare OK"));
					}
				else 
					{
					RDebug::Print(_L("Compare failed"));
					aResult.iResult = 1;
					}
                eng->NextItem(item);
                }
            }

        delete eng;

        // find phone numbers from same text
        testStart.HomeTime();
        TRAP(err, eng = CFindItemEngine::NewL(fullBuf->Des(), CFindItemEngine::EFindItemSearchPhoneNumberBin));
        if(err != KErrNone)
        {
        	aResult.iResult = err;
        	return err;
        }
 
        testEnd.HomeTime();
        elapsed = testEnd.Int64() - testStart.Int64();

        // Get count of found items:s
        TInt count2(eng->ItemCount());

		RDebug::Print(_L("Found %d Phone Numbers:"), count2);

        TBool found2 = eng->Item(item);

        for( i=0; i<count2; i++)
			{
            if ( found2 )
				{
                TPtrC16 result(fullBuf->Des().Mid(item.iStartPos, item.iLength));
				reader.Read(readBuf);

				//Comparing parsed result to what read buffer reads from the file.
				if (!readBuf.Compare(result))
					{
					RDebug::Print(_L("Compare OK"));
					}
				else 
					{
					RDebug::Print(_L("Compare failed"));
					RDebug::Print(readBuf);
					RDebug::Print(result);
					aResult.iResult = 1;
					}
                eng->NextItem(item);
                }
            }

        // test do new search with same instance
        testStart.HomeTime();
        
        TInt count2a;
        TRAP(err, count2a = eng->DoNewSearchL(fullBuf->Des(), CFindItemEngine::EFindItemSearchMailAddressBin));
        if(err != KErrNone)
        {
        	aResult.iResult = err;
        	return err;
        }
        
        testEnd.HomeTime();
        elapsed = testEnd.Int64() - testStart.Int64();
                    
		RDebug::Print(_L("Found %d Mail Addresses:"), count2a);

        TBool found2a = eng->Item(item);

        for( i=0; i<count2a; i++)
			{
            if ( found2a )
				{
                TPtrC16 result(fullBuf->Des().Mid(item.iStartPos, item.iLength));
				reader.Read(readBuf);

				//Comparing parsed result to what read buffer reads from the file.
				if (!readBuf.Compare(result))
					{
					RDebug::Print(_L("Compare OK"));
					}
				else 
					{
					RDebug::Print(_L("Compare failed"));
					aResult.iResult = 1;
					}
                eng->NextItem(item);
                }
            }


        delete eng;
                    
        // find schemed URIs from same text
        testStart.HomeTime();
        TRAP(err, eng = CFindItemEngine::NewL(fullBuf->Des(), CFindItemEngine::EFindItemSearchScheme));
        if(err != KErrNone)
        {
        	aResult.iResult = err;
        	return err;
        }
        testEnd.HomeTime();
        elapsed = testEnd.Int64() - testStart.Int64();
                    
        // Get count of found items:s
        TInt count3(eng->ItemCount());

		RDebug::Print(_L("Found %d URIs:"), count3);

        TBool found3 = eng->Item(item);

        for( i=0; i<count3; i++)
			{
            if ( found3 )
				{
                TPtrC16 result(fullBuf->Des().Mid(item.iStartPos, item.iLength));
				reader.Read(readBuf);

				//Comparing parsed result to what read buffer reads from the file.
				if (!readBuf.Compare(result))
					{
					RDebug::Print(_L("Compare OK"));
					}
				else 
					{
					RDebug::Print(_L("Compare failed"));
					aResult.iResult = 1;
					}
                eng->NextItem(item);
                }
            }

        delete eng;

        // find everything from same text
		RDebug::Print(_L("Mask: %d:"), (CFindItemEngine::EFindItemSearchPhoneNumberBin | CFindItemEngine::EFindItemSearchURLBin | CFindItemEngine::EFindItemSearchMailAddressBin | CFindItemEngine::EFindItemSearchScheme));
        testStart.HomeTime();
        TRAP(err, eng = CFindItemEngine::NewL(fullBuf->Des(), (CFindItemEngine::TFindItemSearchCase)(CFindItemEngine::EFindItemSearchPhoneNumberBin | CFindItemEngine::EFindItemSearchURLBin | CFindItemEngine::EFindItemSearchMailAddressBin | CFindItemEngine::EFindItemSearchScheme)));
        if(err != KErrNone)
        {
        	aResult.iResult = err;
        	return err;
        }
        testEnd.HomeTime();
        elapsed = testEnd.Int64() - testStart.Int64();

        // Get count of found items:s
        TInt count4(eng->ItemCount());

		RDebug::Print(_L("Found %d everything:"), count4);

        //CFindItemEngine::TFindItemSearchCase type = CFindItemEngine::EFindItemSearchPhoneNumberBin;
        TBool found4 = eng->Item(item);
        
        for( i=0; i<count4; i++)
			{
			if ( found4 )
				{
                TPtrC16 result(fullBuf->Des().Mid(item.iStartPos, item.iLength));
				reader.Read(readBuf);

				//Comparing parsed result to what read buffer reads from the file.
				if (!readBuf.Compare(result))
					{
					RDebug::Print(_L("Compare OK"));
					RDebug::Print(_L("  %S"),&readBuf);
					}
				else 
					{
					RDebug::Print(_L("Compare failed"));
					RDebug::Print(_L("  PARSED: %S"),&result);
					RDebug::Print(_L("  FOUND : %S"),&readBuf);
					aResult.iResult = 1;
					}
                eng->NextItem(item);
                }
            }

        delete eng;

        file.Close();
        rfs.Close();
  		delete fullBuf2;
  		delete fullBuf;
        __UHEAP_MARKEND;

		return KErrNone;
	}

// ================= OTHER EXPORTED FUNCTIONS =================================

// End of File

