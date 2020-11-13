int cotac_code_fun(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  if(!strlen(cotac_code_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(cotac_code_entry)))){
    popup(NULL,"Insira o código");
    return 1;
  }

  sprintf(query,"SELECT * FROM cotacoes WHERE code = %s",cotac_code_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar cotação");
    return 1;
  }

  cotacao_new->code = atoi(cotac_code_gchar);
  if(!(row = mysql_fetch_row(res))){
    gtk_widget_grab_focus(cotac_data_entry);
    return 0;
  }else{
    if(!cotac_alterando)
      cotacao_alterar_fun();
  }

  return 0;
}
