int ordem_cmp_excluir_fun(){

  char query[MAX_QUERY_LEN];
  MYSQL_RES *res;
  MYSQL_ROW row;
  if(ordem_cmp_code_fun()){
    return 1;
  }

  sprintf(query, "delete from itens_ordens_compra where ordem_id = %s",ordem_cmp_code_gchar);
  if(enviar_query(query)){
    popup(NULL,"Não foi possível excluir itens da ordem");
    return 1;
  }

  sprintf(query, "delete from ordens_compra where code = %s",ordem_cmp_code_gchar);
  if(enviar_query(query)){
    popup(NULL,"Não foi possível excluir ordem");
    return 1;
  }

  popup(NULL,"Excluído com sucesso");

  ordem_cmp_cancelar_fun();
  return 0;
}
