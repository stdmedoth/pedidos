int cad_ceps_excluir_fun(){
  MYSQL_RES *res;
  MYSQL_ROW row;

  char query[MAX_QUERY_LEN];
  if(cad_ceps_code_fun())
    return 0;

  sprintf(query,"select id_logradouro from logradouro where id_logradouro = '%s'",cad_ceps_code_gchar);
  if(!(res= consultar(query))){
    popup(NULL,"Erro ao consultar existencia do cep");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"CEP não existe para ser excluído");
    return 1;
  }
  sprintf(query,"delete from logradouro where id_logradouro = '%s'",cad_ceps_code_gchar);
  if(enviar_query(query)){
    popup(NULL,"Não foi possivel excluir cep");
    return 1;
  }

  popup(NULL,"Excluído com sucesso!");
  cad_ceps_cancelar_fun();
  return 0;
}
