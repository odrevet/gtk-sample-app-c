#include "app.h"

int main( int argc, char **argv )
{
  //internationalization
  const gchar * const * dirs = g_get_system_data_dirs();
  gchar *rest = g_strjoin(G_DIR_SEPARATOR_S, "locale", NULL);
  const gchar* localdir = get_file(dirs, rest);
  g_free(rest);

  bindtextdomain(PROJECT_NAME, localdir);
  textdomain(PROJECT_NAME);

  //new application
  App *app = g_new(App, 1);

  //initialization
  gtk_init (&argc, &argv);
  app_init (app);

  //get main window
  GET_OBJECT (GtkWidget, window);

  //display
  gtk_widget_show_all (window);

  //main loop
  gtk_main ();

  return 0;
}
