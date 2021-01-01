int prod_precos_nome_fun(){

  prod_prc_nome_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(prod_prc_nome_entry));

  if(strlen(prod_prc_nome_gchar)>=20){
    popup(NULL,"Nome muito grande");
    return 1;
  }
  if(!strlen(prod_prc_nome_gchar)){
    popup(NULL,"Inserir nome");
    return 1;
  }


  MYSQL_RES *res;
  MYSQL_ROW row;
  char *query = malloc(MAX_QUERY_LEN);
  sprintf(query, "select * from precos where nome = '%s' and code != %s", prod_prc_nome_gchar, prod_prc_code_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar existencia do nome");
    return 1;
  }
  if((row = mysql_fetch_row(res))){
    popup(NULL,"Nome já utilizado");
    return 1;
  }

  gtk_widget_grab_focus(prod_prc_prodcode_entry);
  return 0;
}
