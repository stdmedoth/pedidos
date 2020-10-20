int cad_ceps_descr_fun(){
  cad_ceps_descr_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cad_ceps_descr_entry));
  if(!strlen(cad_ceps_descr_gchar)){
    popup(NULL,"Insira o logradouro");
    return 1;
  }
  gtk_widget_grab_focus(cad_ceps_bairro_entry);
  return 0;
}
