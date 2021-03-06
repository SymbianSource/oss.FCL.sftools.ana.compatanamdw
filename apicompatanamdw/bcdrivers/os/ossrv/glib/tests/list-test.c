/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997  Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/*
 * Modified by the GLib Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GLib Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GLib at ftp://ftp.gtk.org/pub/gtk/. 
 */

#undef G_DISABLE_ASSERT
#undef G_LOG_DOMAIN

#include <stdio.h>
#include <string.h>
#include "glib.h"

#ifdef SYMBIAN
#include "mrt2_glib2_test.h"
#endif /*SYMBIAN*/


int array[10000];
gboolean failed = FALSE;

#define	TEST(m,cond)	G_STMT_START { failed = !(cond); \
if (failed) \
  { assert_failed = TRUE;\
  	if (!m) \
      g_print ("\n(%s:%d) failed for: %s\n", __FILE__, __LINE__, ( # cond )); \
    else \
      g_print ("\n(%s:%d) failed for: %s: (%s)\n", __FILE__, __LINE__, ( # cond ), (gchar*)m); \
  } \
else \
  g_print ("."); fflush (stdout); \
} G_STMT_END

#define	C2P(c)		((gpointer) ((long) (c)))
#define	P2C(p)		((gchar) ((long) (p)))

#define GLIB_TEST_STRING "el dorado "
#define GLIB_TEST_STRING_5 "el do"

typedef struct {
	guint age;
	gchar name[40];
} GlibTestInfo;

static gint
my_list_compare_one (gconstpointer a, gconstpointer b)
{
  gint one = *((const gint*)a);
  gint two = *((const gint*)b);
  return one-two;
}

static gint
my_list_compare_two (gconstpointer a, gconstpointer b)
{
  gint one = *((const gint*)a);
  gint two = *((const gint*)b);
  return two-one;
}

int
main (int   argc,
      char *argv[])
{
  GList *list, *t;
  gint nums[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  gint morenums[10] = { 8, 9, 7, 0, 3, 2, 5, 1, 4, 6};
  gint i;

  list = NULL;
  
  #ifdef SYMBIAN
  g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
  g_set_print_handler(mrtPrintHandler);
  #endif /*SYMBIAN*/
	  

  for (i = 0; i < 10; i++)
    list = g_list_append (list, &nums[i]);
  list = g_list_reverse (list);

  for (i = 0; i < 10; i++)
    {
      t = g_list_nth (list, i);
      g_assert (*((gint*) t->data) == (9 - i));
    }

  for (i = 0; i < 10; i++)
    g_assert (g_list_position(list, g_list_nth (list, i)) == i);

  g_list_free (list);
  list = NULL;

  for (i = 0; i < 10; i++)
    list = g_list_insert_sorted (list, &morenums[i], my_list_compare_one);

  /*
  g_print("\n");
  g_list_foreach (list, my_list_print, NULL);
  */

  for (i = 0; i < 10; i++)
    {
      t = g_list_nth (list, i);
      g_assert (*((gint*) t->data) == i);
    }

  g_list_free (list);
  list = NULL;

  for (i = 0; i < 10; i++)
    list = g_list_insert_sorted (list, &morenums[i], my_list_compare_two);

  /*
  g_print("\n");
  g_list_foreach (list, my_list_print, NULL);
  */

  for (i = 0; i < 10; i++)
    {
      t = g_list_nth (list, i);
      g_assert (*((gint*) t->data) == (9 - i));
    }

  g_list_free (list);
  list = NULL;

  for (i = 0; i < 10; i++)
    list = g_list_prepend (list, &morenums[i]);

  list = g_list_sort (list, my_list_compare_two);

  /*
  g_print("\n");
  g_list_foreach (list, my_list_print, NULL);
  */

  for (i = 0; i < 10; i++)
    {
      t = g_list_nth (list, i);
      g_assert (*((gint*) t->data) == (9 - i));
    }

  g_list_free (list);
  
  #ifdef SYMBIAN
  testResultXml("list-test");
  #endif /* EMULATOR */

  return 0;
}

