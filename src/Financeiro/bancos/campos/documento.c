int cad_bancos_doc_fun(){

  cad_bancos_doc_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cad_bancos_doc_entry));

  if( strlen(cad_bancos_doc_gchar) <=0 ){
    popup(NULL,"O documento deve ser preenchido");
    return 1;
  }

  gtk_widget_grab_focus(cad_bancos_saldoini_entry);
  return 0;
}
