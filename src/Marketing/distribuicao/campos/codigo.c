int mkt_cad_distrib_code_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[ MAX_QUERY_LEN ];

  distrib_code_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(distrib_code_entry));
  if(!strlen(distrib_code_gchar)){
    popup(NULL,"Insira o código");
    return 1;
  }

  sprintf(query,"select * from distribuicoes where code = %s", distrib_code_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar existencia da lista");
    return 1;
  }

  if(mysql_num_rows(res)){
    if(!mkt_cad_distrib_alterando && !mkt_cad_distrib_concluindo)
    mkt_cad_distrib_alterar_fun();
    return 0;
  }else{
    gtk_widget_grab_focus(distrib_nome_entry);
  }

  return 0;
}
