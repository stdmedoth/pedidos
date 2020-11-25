int req_prod_excluir_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  if(req_prod_code_fun()){
    gtk_widget_grab_focus(req_prod_code_entry);
    return 1;
  }

  sprintf(query,"select * from prod_requisicoes where code = %s", req_prod_code_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar a solicitação");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Solicitação não existente");
    return 1;
  }

  sprintf(query,"delete from prod_requisicoes where code = %s", req_prod_code_gchar);
  if(enviar_query(query)){
    popup(NULL,"Não foi possível deletar a solicitação");
    return 1;
  }

  popup(NULL,"Solicitação deletada com sucesso");
  req_prod_cancelar_fun();

  return 0;
}
