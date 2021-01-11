int prod_precos_code_fun(){

  prod_prc_code_gchar = (gchar *) gtk_entry_get_text(GTK_ENTRY(prod_prc_code_entry));

  struct _prod_precos *preco = precos_get_preco(atoi(prod_prc_code_gchar));
  if(preco){
    if(!prod_precos_alterando && !prod_precos_concluindo){
      prod_precos_alterar_fun();
    }
  }

  gtk_widget_grab_focus(prod_prc_prodcode_entry);
  return 0;
}
