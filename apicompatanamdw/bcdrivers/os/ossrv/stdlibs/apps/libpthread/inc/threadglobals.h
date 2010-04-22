/*
* Copyright (c) 2005-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Data structures needed for ptherad library
*
*
*
*/

#ifndef THREADGLOBALS_H
#define THREADGLOBALS_H

#include <pthread.h>
#include <e32std.h>
#include <limits.h>
#include "sysif.h"

#include <e32debug.h>

//the semaphore structure 
struct _sem_t
{
	enum sem_state
	{
		EInitialized,
		EDestroyed,
		EInvalid,
	};
	sem_state iState;
	int  iCount; //iCount and iMutex pair needed 
	             //because of need for implementing trywait
	RMutex 	iMutex; 
	RSemaphore iSemaphore;
	/*******************************************************************
	Overloading new and delete operators so that they will
	allocate and deallocare memory from/to the private heap of backend
	********************************************************************/
	inline TAny* operator new(TUint aSize, TAny* aBase) __NO_THROW
		{
		Mem::FillZ(aBase, aSize); return aBase;
		}
		
	inline TAny* operator new(TUint aSize) __NO_THROW
		{
		return Backend()->Alloc(aSize);
		}
		
	inline TAny* operator new(TUint aSize, TLeave)
		{
		TAny* ptr = Backend()->Alloc(aSize);
		if (ptr == NULL)
			{
			User::Leave(KErrNoMemory);
			}
		return ptr;
		}
		
	inline TAny* operator new(TUint aSize, TUint aExtraSize) __NO_THROW
		{
		return Backend()->Alloc(aSize + aExtraSize);
		}
		
	inline TAny* operator new(TUint aSize, TLeave, TUint aExtraSize)
		{
		TAny* ptr = Backend()->Alloc(aSize + aExtraSize);
		if (ptr == NULL)
			{
			User::Leave(KErrNoMemory);
			}
		return ptr;
		}
	
	inline void operator delete(TAny *aPtr) __NO_THROW
		{
		Backend()->Free( aPtr );
		}
};

typedef struct _sem_node
{
    struct _sem_node *next;
    _sem_t *sem;
	/*******************************************************************
	Overloading new and delete operators so that they will
	allocate and deallocare memory from/to the private heap of backend
	********************************************************************/
	inline TAny* operator new(TUint aSize, TAny* aBase) __NO_THROW
		{
		Mem::FillZ(aBase, aSize); return aBase;
		}
		
	inline TAny* operator new(TUint aSize) __NO_THROW
		{
		return Backend()->Alloc(aSize);
		}
		
	inline TAny* operator new(TUint aSize, TLeave)
		{
		TAny* ptr = Backend()->Alloc(aSize);
		if (ptr == NULL)
			{
			User::Leave(KErrNoMemory);
			}
		return ptr;
		}
		
	inline TAny* operator new(TUint aSize, TUint aExtraSize) __NO_THROW
		{
		return Backend()->Alloc(aSize + aExtraSize);
		}
		
	inline TAny* operator new(TUint aSize, TLeave, TUint aExtraSize)
		{
		TAny* ptr = Backend()->Alloc(aSize + aExtraSize);
		if (ptr == NULL)
			{
			User::Leave(KErrNoMemory);
			}
		return ptr;
		}
	
	inline void operator delete(TAny *aPtr) __NO_THROW
		{
		Backend()->Free( aPtr );
		}
}_sem_node_t;


// Thread default attributes
#define DEFAULT_STACK_SIZE   0x2000
#define DEFAULT_DETACH_STATE PTHREAD_CREATE_JOINABLE

#define THR_DISABLE_PTHREAD_TRACE 1

#define DEFAULT_THREAD_PRIORITY 100

#ifdef THR_DISABLE_PTHREAD_TRACE 

#define THR_PRINTF(string) \
{\
}

#else  //THR_DISABLE_PTHREAD_TRACE

#define THR_PRINTF(string) \
{\
    RDebug::Printf(string);\
}

#endif  //THR_DISABLE_PTHREAD_TRACE

#define THR_NULL_ASSERT(x,val,format) \
{ \
    if ( (x) == NULL )  \
    { \
        THR_PRINTF(format); \
        return ((void*)0); \
    } \
} 

#define STAT_FLAG_SIZE (PTHREAD_KEYS_MAX / 32)    

/* thread state.  */
enum 
{
    _THREAD_RUNNING,
    _THREAD_ZOMBIE
};

/* Key status */
enum
{
    _KEY_UNUSED,
    _KEY_USED
};

/* MainFlag */
enum
{
    _MAIN_THREAD=0,
    _NON_MAIN_THREAD
};

typedef struct
{
    destructor_routine destr;
}_pthread_key_node;

// TLS Keys link list node
typedef struct _pkey_node
{
    int keyNumber;
    struct _pkey_node *next;
    void *tls;    
	/*******************************************************************
	Overloading new and delete operators so that they will
	allocate and deallocare memory from/to the private heap of backend
	********************************************************************/
	inline TAny* operator new(TUint aSize, TAny* aBase) __NO_THROW
		{
		Mem::FillZ(aBase, aSize); return aBase;
		}
		
	inline TAny* operator new(TUint aSize) __NO_THROW
		{
		return Backend()->Alloc(aSize);
		}
		
	inline TAny* operator new(TUint aSize, TLeave)
		{
		TAny* ptr = Backend()->Alloc(aSize);
		if (ptr == NULL)
			{
			User::Leave(KErrNoMemory);
			}
		return ptr;
		}
		
	inline TAny* operator new(TUint aSize, TUint aExtraSize) __NO_THROW
		{
		return Backend()->Alloc(aSize + aExtraSize);
		}
		
	inline TAny* operator new(TUint aSize, TLeave, TUint aExtraSize)
		{
		TAny* ptr = Backend()->Alloc(aSize + aExtraSize);
		if (ptr == NULL)
			{
			User::Leave(KErrNoMemory);
			}
		return ptr;
		}
	
	inline void operator delete(TAny *aPtr) __NO_THROW
		{
		Backend()->Free( aPtr );
		}
}_pkey_node_t;

typedef struct _pthread_node _pthread_node_t;
#ifdef __X86GCC__
// MinGW GCC compiler does not like typedef struct definitions with no tag
typedef struct _global_data_tag
#else
typedef struct 
#endif //__X86GCC__
{
    _pthread_node_t *start;
    unsigned int threadCount;
    RMutex lockThreadTable;
    RMutex globalLockForMutex;
    // TLS Keys
    _pthread_key_node pthread_key_list[PTHREAD_KEYS_MAX];
    unsigned int statusflag[STAT_FLAG_SIZE];
    // Semaphore list
    _sem_node_t *semStart;
    RMutex lockSemTable;
	/*******************************************************************
	Overloading new and delete operators so that they will
	allocate and deallocare memory from/to the private heap of backend
	********************************************************************/
	inline TAny* operator new(TUint aSize, TAny* aBase) __NO_THROW
		{
		Mem::FillZ(aBase, aSize); return aBase;
		}
		
	inline TAny* operator new(TUint aSize) __NO_THROW
		{
		return Backend()->Alloc(aSize);
		}
		
	inline TAny* operator new(TUint aSize, TLeave)
		{
		TAny* ptr = Backend()->Alloc(aSize);
		if (ptr == NULL)
			{
			User::Leave(KErrNoMemory);
			}
		return ptr;
		}
		
	inline TAny* operator new(TUint aSize, TUint aExtraSize) __NO_THROW
		{
		return Backend()->Alloc(aSize + aExtraSize);
		}
		
	inline TAny* operator new(TUint aSize, TLeave, TUint aExtraSize)
		{
		TAny* ptr = Backend()->Alloc(aSize + aExtraSize);
		if (ptr == NULL)
			{
			User::Leave(KErrNoMemory);
			}
		return ptr;
		}
	
	inline void operator delete(TAny *aPtr) __NO_THROW
		{
		Backend()->Free( aPtr );
		}

}_global_data_t;

typedef struct _pthread_node
{
    struct _pthread_node *next;
    RMutex lockNode;
    _global_data_t *glbDataPtr;
    unsigned int detachState;
    unsigned int threadState;
    void *returnValue;
    TBool hasAnyThreadJoined;
    RThread rtHandle;
    unsigned int threadId;
//    void  *tls[PTHREAD_KEYS_MAX];
    _pkey_node_t *tlsHead;
    int priority;
    int mainFlag;
    void *cleanStackPtr;
	/*******************************************************************
	Overloading new and delete operators so that they will
	allocate and deallocare memory from/to the private heap of backend
	********************************************************************/
	inline TAny* operator new(TUint aSize, TAny* aBase) __NO_THROW
		{
		Mem::FillZ(aBase, aSize); return aBase;
		}
		
	inline TAny* operator new(TUint aSize) __NO_THROW
		{
		return Backend()->Alloc(aSize);
		}
		
	inline TAny* operator new(TUint aSize, TLeave)
		{
		TAny* ptr = Backend()->Alloc(aSize);
		if (ptr == NULL)
			{
			User::Leave(KErrNoMemory);
			}
		return ptr;
		}
		
	inline TAny* operator new(TUint aSize, TUint aExtraSize) __NO_THROW
		{
		return Backend()->Alloc(aSize + aExtraSize);
		}
		
	inline TAny* operator new(TUint aSize, TLeave, TUint aExtraSize)
		{
		TAny* ptr = Backend()->Alloc(aSize + aExtraSize);
		if (ptr == NULL)
			{
			User::Leave(KErrNoMemory);
			}
		return ptr;
		}
	
	inline void operator delete(TAny *aPtr) __NO_THROW
		{
		Backend()->Free( aPtr );
		}
}_pthread_node_t;




#endif //THREADGLOBALS_H
