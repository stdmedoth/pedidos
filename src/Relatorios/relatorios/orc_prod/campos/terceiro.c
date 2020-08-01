int relat_orc_prod_int1_ter_fun(){
  gtk_entry_set_text(GTK_ENTRY(relat_orc_prod_int2_ter_entry),gtk_entry_get_text(GTK_ENTRY(relat_orc_prod_int1_ter_entry)));
  gtk_widget_grab_focus(relat_orc_prod_int2_ter_entry);
  return 0;
}
