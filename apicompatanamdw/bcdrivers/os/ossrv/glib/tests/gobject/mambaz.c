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

#include "mambaz.h"

extern GType baz_type;

static void
maman_ibaz_base_init (gpointer g_class)
{
  
}

GType
maman_ibaz_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (MamanIbazInterface),
      maman_ibaz_base_init,   /* base_init */
      NULL,   /* base_finalize */
      NULL,   /* class_init */
      NULL,   /* class_finalize */
      NULL,   /* class_data */
      0,
      0,      /* n_preallocs */
      NULL    /* instance_init */
    };
    type = g_type_register_static (G_TYPE_INTERFACE, "MamanIbaz", &info, 0);
  }
  return type;
}

void maman_ibaz_do_action (MamanIbaz *self)
{
 
  MAMAN_IBAZ_GET_INTERFACE (self)->do_action (self);
}

//that was the interface class

static void baz_do_action (MamanBaz *self)
{
  self->instance_member = 10;
}

void
baz_interface_init (gpointer   g_iface,
                    gpointer   iface_data)
{
  MamanIbazInterface *iface = (MamanIbazInterface *)g_iface;
  iface->do_action = (void (*) (MamanIbaz *self))baz_do_action;
}

void
baz_instance_init (GTypeInstance   *instance,
                   gpointer         g_class)
{
  MamanBaz *self = MAMAN_BAZ(instance);
  self->instance_member = 0xdeadbeaf;
}



