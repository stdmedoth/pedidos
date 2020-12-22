int prod_precos_code_fun(){

  prod_prc_code_gchar = (gchar *) gtk_entry_get_text(GTK_ENTRY(prod_prc_code_entry));

  if(!prod_precos_alterando && !prod_precos_concluindo){
    prod_precos_alterar_fun();
  }

  gtk_widget_grab_focus(prod_prc_prodcode_entry);
  return 0;
}
