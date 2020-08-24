int cad_bancos_usuario_fun(){

  cad_bancos_usuario_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cad_bancos_usuario_entry));

  if( strlen(cad_bancos_usuario_gchar) <=0 ){
    popup(NULL,"O usuario deve ser preenchido");
    return 1;
  }

  gtk_widget_grab_focus(cad_bancos_doc_entry);
  return 0;
}
