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

#define NATIVE(name, signature, func) \
              {name, signature, (void*)func}

#define ENTRY(name, signature, func) \
             {name, signature, (void*)func,}

#define TABLE(name, natives, entries) \
             { name, natives, entries }

struct NativeFunction {
  char* name;
  char* signature;
  void* function;
};

struct NativesTable {
  char*                  name;
  const NativeFunction*  natives;
  const NativeFunction*  entries;
};



extern const NativesTable natives_table[];

