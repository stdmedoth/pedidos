int cad_bancos_agencia_fun(){

  cad_bancos_agencia_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cad_bancos_agencia_entry));

  if( strlen(cad_bancos_agencia_gchar) <=0 ){
    popup(NULL,"a agencia deve ser preenchida");
    return 1;
  }

  gtk_widget_grab_focus(cad_bancos_usuario_entry);
  return 0;
}
