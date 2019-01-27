#include "app.h"


static void settings_changed(GSettings *settings,
                               gchar *key,
                               gpointer user_data){

}

void app_init (App * app){
  GError *err = NULL;

  app->definitions = gtk_builder_new ();


  const gchar * const * dirs = g_get_system_data_dirs();
  gchar* rest = g_strjoin(G_DIR_SEPARATOR_S,
			  PROJECT_NAME,
			  "ui",
			  UI_DEFINITION_FILE,
			  NULL);
  gchar* definition_file = get_file(dirs, rest);
  g_free(rest);

  gtk_builder_add_from_file (app->definitions,
                             definition_file, &err);

  if(!definition_file)g_printerr("Cannot find UI definition file '%s'\n", definition_file);
  if (err != NULL) {
    g_printerr
      ("Error while loading UI definitions file: %s\n",
       err->message);
    g_error_free (err);
    gtk_main_quit ();
  }

  gtk_builder_connect_signals (app->definitions, app);

  g_free(definition_file);

  //init gsettings
  app->settings = g_settings_new ("sampleapp");

  g_signal_connect(app->settings,
                   "changed",
                   G_CALLBACK (settings_changed),
                   NULL);

  //set the entry message text
  gchar *message = g_settings_get_string(app->settings, "message");
  GET_OBJECT (GtkWidget, entry_message);
  gtk_entry_set_text(GTK_ENTRY(entry_message), message);

}

gchar* get_file(const gchar* const *dirs, const gchar* rest){
  if(g_file_test(rest, G_FILE_TEST_EXISTS))return g_strdup(rest);
  gchar* res = NULL;
  for (gint i = 0; dirs[i]; i++){
    res = g_strjoin (G_DIR_SEPARATOR_S, dirs[i], rest, NULL);
    if(g_file_test(res, G_FILE_TEST_EXISTS))return res;
    else g_free(res);
  }
  return NULL;
}
