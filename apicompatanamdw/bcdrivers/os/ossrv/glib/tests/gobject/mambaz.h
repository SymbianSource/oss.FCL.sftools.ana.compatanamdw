/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies). 
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


#ifndef __DERIVED_H__
#define __DERIVED_H__

#include <glib-object.h>

#define MAMAN_TYPE_IBAZ                (maman_ibaz_get_type ())
#define MAMAN_IBAZ(obj)                (G_TYPE_CHECK_INSTANCE_CAST ((obj), MAMAN_TYPE_IBAZ, MamanIbaz))
#define MAMAN_IS_IBAZ(obj)             (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MAMAN_TYPE_IBAZ))
#define MAMAN_IBAZ_GET_INTERFACE(inst) (G_TYPE_INSTANCE_GET_INTERFACE ((inst), MAMAN_TYPE_IBAZ, MamanIbazInterface))


typedef struct _MamanIbaz MamanIbaz; /* dummy object */
typedef struct _MamanIbazInterface MamanIbazInterface;

struct _MamanIbazInterface {
  GTypeInterface parent;

  void (*do_action) (MamanIbaz *self);
};

GType maman_ibaz_get_type (void);

void maman_ibaz_do_action (MamanIbaz *self);

//that was the interface class
//now the derived class

#include <glib-object.h>

#define MAMAN_TYPE_BAZ             (baz_type)
#define MAMAN_BAZ(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), MAMAN_TYPE_BAZ, MamanBaz))
#define MAMAN_BAZ_CLASS(vtable)    (G_TYPE_CHECK_CLASS_CAST ((vtable), MAMAN_TYPE_BAZ, MamanbazClass))
#define MAMAN_IS_BAZ(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MAMAN_TYPE_BAZ))
#define MAMAN_IS_BAZ_CLASS(vtable) (G_TYPE_CHECK_CLASS_TYPE ((vtable), MAMAN_TYPE_BAZ))
#define MAMAN_BAZ_GET_CLASS(inst)  (G_TYPE_INSTANCE_GET_CLASS ((inst), MAMAN_TYPE_BAZ, MamanbazClass))


typedef struct _MamanBaz MamanBaz;
typedef struct _MamanBazClass MamanBazClass;

struct _MamanBaz {
  GObject parent;
  int instance_member;
};

struct _MamanBazClass {
  GObjectClass parent;
};

GType maman_baz_get_type (void);

void baz_do_action (MamanBaz *self);
void baz_instance_init (GTypeInstance   *instance, gpointer         g_class);
void baz_interface_init (gpointer   g_iface,gpointer   iface_data);




#endif // __DERIVED_H__