int cad_ceps_bairro_fun(){
  cad_ceps_bairro_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cad_ceps_bairro_entry));
  if(!strlen(cad_ceps_bairro_gchar)){
    gtk_widget_grab_focus(cad_ceps_bairro_entry);
    popup(NULL,"Insira o bairro");
    return 1;
  }
  gtk_widget_grab_focus(cad_ceps_cid_code_entry);
  return 0;
}
