int orc_bnc_code_fun(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  orc_bnc_code_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(orc_bnc_code_entry));

  if(!strlen(orc_bnc_code_gchar)){
    popup(NULL,"Insira o Banco");
    gtk_widget_grab_focus(orc_bnc_code_entry);
    return 1;
  }
  sprintf(query,"select nome from bancos where code = %s",orc_bnc_code_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar Banco");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"O Banco não existe");
    return 1;
  }

  gtk_entry_set_text(GTK_ENTRY(orc_bnc_nome_entry),row[0]);
  return 0;
}
