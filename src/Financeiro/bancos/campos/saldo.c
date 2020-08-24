int cad_bancos_saldoini_fun(){

  cad_bancos_saldoini_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cad_bancos_saldoini_entry));


    if( strlen(cad_bancos_saldoini_gchar) <=0 ){
      popup(NULL,"O saldo deve ser preenchido");
      return 1;
    }
  gtk_widget_grab_focus(cad_bancos_concluir_button);
  return 0;
}
