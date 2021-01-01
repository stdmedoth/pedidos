int prod_precos_prod_fun(){

  prod_prc_prodcode_gchar = (gchar *) gtk_entry_get_text(GTK_ENTRY(prod_prc_prodcode_entry));
  if(!strlen(prod_prc_prodcode_gchar)){
    popup(NULL,"Inserir produto");
    return 1;
  }
  MYSQL_RES *res;
  MYSQL_ROW row;
  char *query = malloc(MAX_QUERY_LEN);
  sprintf(query, "select * from produtos where code = %s", prod_prc_prodcode_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar produto");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Produto não existente");
    return 1;
  }

  gtk_entry_set_text(GTK_ENTRY(prod_prc_prodnome_entry), row[PROD_NOM_COL]);

  gtk_widget_grab_focus(prod_prc_vlrfat_entry);
  return 0;
}
