int relat_fix_est_grp_fun(){
  relat_fix_est_grp_gchar1 =(gchar*)  gtk_entry_get_text(GTK_ENTRY(relat_fix_est_grp_entry1));
  relat_fix_est_grp_gchar2 =(gchar*)  gtk_entry_get_text(GTK_ENTRY(relat_fix_est_grp_entry2));

  gtk_widget_grab_focus(relat_fix_est_est_entry1);
  return 0;
}
