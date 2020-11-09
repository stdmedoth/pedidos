int req_prod_code_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  req_prod_code_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(req_prod_code_entry));
  if(!strlen(req_prod_code_gchar)){
    popup(NULL,"Insira um código para a requisição");
    return 1;
  }

  int req_code = atoi(req_prod_code_gchar);
  sprintf(query,"select * from prod_requisicoes where code = %i",req_code);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar requisição");
    return 1;
  }
  if((row = mysql_fetch_row(res))){
    if(!req_prod_alterando && !req_prod_concluindo)
      req_prod_alterar_fun();
    return 0;
  }
  gtk_entry_set_text(GTK_ENTRY(req_prod_dtevent_entry),"00/00/00");
  gtk_widget_grab_focus(req_prod_prod_entry);
  return 0;
}
