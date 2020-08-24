int cad_bancos_excluir_fun(){

  char query[MAX_QUERY_LEN];
  if(cad_bancos_code_fun())
    return 1;

  sprintf(query,"delete from bancos where code = %s",cad_bancos_code_gchar);
  if(enviar_query(query)){
    popup(NULL,"Não foi possível excluir banco");
    return 1;
  }
  popup(NULL,"Banco excluído com sucesso");
  cad_bancos_cancelar_fun();
  return 0;
}
