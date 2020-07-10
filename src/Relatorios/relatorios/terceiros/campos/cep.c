int relat_ter_cep_i1_fun(){
  gtk_entry_set_text(GTK_ENTRY(relat_ter_cep_int2_entry),gtk_entry_get_text(GTK_ENTRY(relat_ter_cep_int1_entry)));
  gtk_widget_grab_focus(relat_ter_cep_int2_entry);
  return 0;
}
