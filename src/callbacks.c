#include "app.h"

G_MODULE_EXPORT void on_imagemenuitem_about_activate (GtkMenuItem *menuitem,
                                                      App *app){
  GET_OBJECT (GtkWindow, aboutdialog);
  gtk_dialog_run(GTK_DIALOG(aboutdialog));
  gtk_widget_hide (GTK_WIDGET(aboutdialog));
}

G_MODULE_EXPORT void on_button_load_clicked(GtkButton *button,
                                             App* app){
  GET_OBJECT(GtkWidget, entry_message);
  const gchar *message = g_settings_get_string(app->settings, "message");
  gtk_entry_set_text(GTK_ENTRY(entry_message), message);
}

G_MODULE_EXPORT void on_button_save_clicked(GtkButton *button,
                                             App* app){
  GET_OBJECT(GtkWidget, entry_message);
  const gchar *message = gtk_entry_get_text(GTK_ENTRY(entry_message));
  g_settings_set_string(app->settings, "message", message);
  g_settings_sync();
}
