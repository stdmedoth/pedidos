int mkt_cad_distrib_excluir_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[ MAX_QUERY_LEN ];

  sprintf(query, "select * from distribuicoes where code = %s", distrib_code_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar existencia da distribuicao");
    return 1;
  }
  if(!(mysql_num_rows(res))){
    popup(NULL,"Lista de Distribuição não existente");
    return 1;
  }

  sprintf(query, "delete from PessoasDistribuicao where distribuicao = %s", distrib_code_gchar);
  if(enviar_query(query)){
    popup(NULL,"Não foi possível excluir contatos na distribuição");
    return 1;
  }

  sprintf(query, "delete from distribuicoes where code = %s", distrib_code_gchar);
  if(enviar_query(query)){
    popup(NULL,"Não foi possível excluir distribuição");
    return 1;
  }
  popup(NULL,"Distribuição excluída com sucesso");
  mkt_cad_distrib_cancelar_fun();

  return 0;
}
