#ifndef __APP__
#define __APP__

#include <gtk/gtk.h>
#include <glib/gprintf.h>
#include <gio/gio.h>

#include <string.h>

#include <locale.h>
#include <libintl.h>

#include "config.h"

#define UI_DEFINITION_FILE PROJECT_NAME".ui"

#define GET_OBJECT(TYPE, ELEMENT)   TYPE *ELEMENT = (TYPE *)\
    gtk_builder_get_object(app->definitions, #ELEMENT);

typedef struct app_
{
  GtkBuilder *definitions;
  GSettings * settings;
} App;

void app_init (App * );

gchar* get_file(const gchar* const *dirs, const gchar* rest);

#endif
