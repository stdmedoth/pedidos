int relat_fix_vnd_cli_fun(){

  relat_fix_vnd_cli_gchar1 =(gchar*)  gtk_entry_get_text(GTK_ENTRY(relat_fix_vnd_cli_entry1));
  relat_fix_vnd_cli_gchar2 =(gchar*)  gtk_entry_get_text(GTK_ENTRY(relat_fix_vnd_cli_entry2));

  gtk_widget_grab_focus(relat_fix_vnd_est_entry1);
  return 0;
}
