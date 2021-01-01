int prod_precos_excluir_fun(){

  char *query = malloc(MAX_QUERY_LEN);
  if(prod_precos_code_fun()){
    gtk_widget_grab_focus(prod_prc_code_entry);
    return 1;
  }
  sprintf(query,"delete from precos where code = %s", prod_prc_code_gchar);
  if(enviar_query(query)){
    popup(NULL,"Não foi possível excluir preço");
    return 1;
  }

  popup(NULL, "Preço excluído com sucesso");
  prod_precos_cancelar_fun();
  return 0;
}
