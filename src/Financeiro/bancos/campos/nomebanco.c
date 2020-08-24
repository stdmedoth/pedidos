int cad_bancos_nome_fun(){

  cad_bancos_nome_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cad_bancos_nome_entry));

  if( strlen(cad_bancos_nome_gchar) <=0 ){
    popup(NULL,"O nome deve ser preenchido");
    return 1;
  }

  gtk_widget_grab_focus(cad_bancos_conta_entry);
  return 0;
}
