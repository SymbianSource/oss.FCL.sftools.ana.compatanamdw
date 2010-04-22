/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:
*
*/


#ifndef __TESTCONDSIGNAL_H__
#define __TESTCONDSIGNAL_H__

#include <test/TestExecuteStepBase.h>
#include <errno.h>
#include <e32svr.h>
#include <stddef.h>
#include <limits.h>
#include <e32def.h>
#include <e32std.h>
#include <stdlib.h>
#include <errno.h>
#include <e32base.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

_LIT(KTestCond439, "TestCond439");
_LIT(KTestCond440, "TestCond440");
_LIT(KTestCond441, "TestCond441");
_LIT(KTestCond442, "TestCond442");
_LIT(KTestCond443, "TestCond443");
_LIT(KTestCond444, "TestCond444");
_LIT(KTestCond445, "TestCond445");
_LIT(KTestCond678, "TestCond678");
_LIT(KTestCond679, "TestCond679");
_LIT(KTestCond680, "TestCond680");


class CTestCondsignal : public CTestStep
	{
public:
	~CTestCondsignal(); 
	CTestCondsignal(const TDesC& aStepName);
	TVerdict doTestStepL();
	TVerdict doTestStepPreambleL();
	TVerdict doTestStepPostambleL();
private:
	//pthread_cond_signal called on statically initialized cond var
	TInt TestCond439();

	//pthread_cond_signal is called on uninitialized cond var
	TInt TestCond440();

	//pthread_cond_signal is called with mutex locked
	TInt TestCond441();

	//pthread_cond_signal is called without mutex locked
	TInt TestCond442();

	//pthread_cond_signal is called with no theards suspended on the cond var
	TInt TestCond443();

	//pthread_cond_signal is called with one thread suspended on cond var
	TInt TestCond444();

	//pthread_cond_signal is called with n threads suspended on cond var
	TInt TestCond445();

	//race between pthread_cond_signal and pthread_cond_signal
	TInt TestCond678();

	//race between pthread_cond_signal and pthread_cond_wait
	TInt TestCond679();

	//race between pthread_cond_signal and pthread_cond_timedwait
	TInt TestCond680();
	
	};
#if 0

#define TRACE(n) \
{ \
	TBuf<255> msg; \
	msg.Format(_L(n)); \
	TestModuleIf().Printf( 0, _L(""),msg); \
} 

#else
#define MSG(n) 
#define TRACE(n)

#endif 



enum ThreadCommand
	{
	ELastCommand,
	EThreadCreate,
	EThreadDestroy,
	EVerifyResult,
	ESetErrno,
	EVerifyErrno,
	ECheckValue,

	EVerifyTimeOutOrPostSignal,

	EStartLog,
	EStopLog,
	ENoOp,

	ELoop,

	EWaitForSignal,
	EPostSignal,
	EWaitTillSuspended,
	
	EBusySpin,
	EVerifySpin,
	EVerifyNoSpin,
	EWaitTillSpin,
	EStopSpin,

    ESemClose,
	ESemDestroy,
	ESemGetValue,
	ESemInit,
	ESemOpen,
	ESemPost,
	ESemTimedWait,
	ESemMicroSleepWait,
	ESemTryWait,
	ESemUnlink,
	ESemWait,
 
	EMutexDestroy,

	EMutexInitNULL,
	EMutexInitDefault,
	EMutexInitErrorCheck,
	EMutexInitRecursive,
		
	EMutexInitStaticDefault,
	EMutexInitStaticErrorCheck,
	EMutexInitStaticRecursive,
	
	EMutexLock,
	EMutexTimedLock,
	EMutexTryLock,
	EMutexUnlock,

	EMutexAttrDestroy,
	EMutexAttrGetType,
	EMutexAttrGetPShared,
	EMutexAttrSetType,
	EMutexAttrSetPShared,
	EMutexAttrInit,

	EOnceInit,
	ECallOnce,
	EMicroSleepTime,
	EErrno,

	ECondBroadcast,
	ECondDestroy,
	ECondInit,
	ECondInitStatic,
	ECondSignal,
	ECondWait,
	ECondTimedWait,
	ECondAttrDestroy,
	ECondAttrInit,

	ESem274Init,
	ESem274Destroy,
	ESem282,
	ESem284B,
	ESem697B,
	ESem698B,
	ESemPostAsNeeded,
	ESem701A,
	ESem701B,

	EMutex330,
	ECond403Init,
	ECond403Destroy,
	ECond452A,
	ECond452B,
	ECond453A,
	ECond453B,
	ECond676A,
	ECond676B,
	ECond677A,
	ECond677B,
	ECond679A,
	ECond679B,
	ECond680A,
	ECond680B,
	ECond681A,
	ECond681B,
	ECond683A,
	ECond683B,



	EPrintSuspendedStatus,
	EFStat,
	EStat,
	EWStat,
	EWriteName,
	EWriteWName,
	EWriteFd,
	EStop,
	ESemPost284
	};

enum HarnessThread
	{
	EThread1,
	EThread2,
	EThread3,
	EThread4,
	EThread5,
	EThreadMain,
	ENoThread,
	};

class CTestModuleBase;

#ifdef HARNESS_LOG
struct HarnessBuffer
	{
	bool before;
	struct HarnessCommand iCommand;
	struct HarnessBuffer* iNext;
	};
#endif


struct CommonData
	{
	pthread_mutex_t* iStaticMutex;
	pthread_mutex_t* iErrorCheckMutex;
	pthread_mutex_t* iRecursiveMutex;
	pthread_cond_t*  iStaticCondVar;
	pthread_once_t   iOnceControl;
	
#ifdef HARNESS_LOG		
	FILE*            iFile;
	pthread_mutex_t  iFileMutex;
	HarnessBuffer*   iHead;
#endif	
	CommonData()
	:iStaticMutex(NULL)
	,iErrorCheckMutex(NULL)
	,iRecursiveMutex(NULL)
	,iStaticCondVar(NULL)

#ifdef HARNESS_LOG	
	,iHead(NULL)
#endif	
	{
#ifdef	HARNESS_LOG
		int ret;
		iFile = fopen("C:\\Logs\\testframework\\P_Alone.txt","w");
		if(!iFile)
			{
			printf("Unable to open log file!\n");
			}
		ret = pthread_mutex_init(&iFileMutex,NULL);
		if(ret != 0)
			{
			printf("Unable to init file mutex!\n");
			}
#endif		
	}
	
	~CommonData()
	{
#ifdef HARNESS_LOG	
		char buff[255];
		HarnessBuffer* node = iHead;
		HarnessBuffer* temp;
		while(node)
			{
		
			 sprintf(buff,"thread %d command %d\n",node->iCommand.iThread,node->iCommand.iAction);
			 if(node->before)
				{
		 		if(iFile)
					{
		   	 		fprintf(iFile,"+");
					}
				}
			 else
				{
				if(iFile)
					{
		   			fprintf(iFile,"-");
					}
				}
			if(iFile)
				{
		   		fprintf(iFile,buff);	
				}
		  	
		    temp = node;
		    node = node->iNext;
		    delete temp;
			}
		pthread_mutex_destroy(&iFileMutex);
		if(iFile)
			{
			fclose(iFile);	
			}
#endif		
	}
	};



struct ThreadData
	{
	sem_t* iSignalSemaphore;
	sem_t* iSuspendSemaphore;

	sem_t*                iTestSemaphore;
	pthread_mutex_t*      iTestMutex;
	pthread_mutexattr_t*  iTestMutexAttr;
	pthread_cond_t*       iTestCondVar;
	pthread_mutexattr_t*  iDefaultAttr;
	pthread_mutexattr_t*  iErrorcheckAttr;
	pthread_mutexattr_t*  iRecursiveAttr;

	pthread_condattr_t*   iCondAttr;
	bool                  iSuspending;
	int                   iSpinCounter;
	int                   iCurrentCommand;
	HarnessThread         iSelf;
	int                   iValue;
	int                   iRetValue;
	int                   ierrno;
	int                   iExpectederrno;
	int                   iTimes;
	bool                  iStopped;

	CommonData*           iCommonData;
	void*                 iInitTwiceData;

	ThreadData*           iTDArr[EThreadMain];
	pthread_t             iIdArr[EThreadMain];

	};

void* StartFn(void* arg);


int NewThread(ThreadData* aThreadData, HarnessThread aThreadId);
int DeleteThread(ThreadData* aThreadData, HarnessThread aThreadId);

enum TestReturn
	{
	KUnexpectedResult = 1,
	KPrematureError,
	KNoPermission,
	KNoArgument,
	KNotSupported,
	KIllegalCommand,
	KValueMismatch,
	KNoMemory,
	KSpinChanged,
    KSpinNotChanged,
	};

struct semParam_t
	{
	int pshared;
	int value;
	};


#endif 



