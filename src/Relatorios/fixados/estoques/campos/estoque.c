int relat_fix_est_est_fun(){
  relat_fix_est_est_gchar1 =(gchar*)  gtk_entry_get_text(GTK_ENTRY(relat_fix_est_est_entry1));
  relat_fix_est_est_gchar2 =(gchar*)  gtk_entry_get_text(GTK_ENTRY(relat_fix_est_est_entry2));

  gtk_widget_grab_focus(relat_fix_est_gerar_button);
  return 0;
}
