int req_prod_prod_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  req_prod_prod_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(req_prod_prod_entry));
  if(!strlen(req_prod_prod_gchar)){
    popup(NULL,"Insira um produto");
    return 1;
  }

  int req_prod = atoi(req_prod_prod_gchar);
  sprintf(query,"select * from produtos where code = %i",req_prod);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar requisição");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Produto não existente");
    return 1;
  }
  gchar *nome_prod = strdup(row[PROD_NOM_COL]);
  gtk_entry_set_text(GTK_ENTRY(req_prod_prodnome_entry),nome_prod);
  gtk_widget_grab_focus(req_prod_qnt_spin);
  return 0;
}
