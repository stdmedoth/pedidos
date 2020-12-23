int prod_precos_alterar_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char *query = malloc(MAX_QUERY_LEN);
  prod_precos_alterando = 1;

  if(prod_precos_code_fun()){
    gtk_widget_grab_focus(prod_prc_code_entry);
    return 1;
  }

  sprintf(query,"select * from precos where code = %s", prod_prc_code_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar preço");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Preço não existente");
    return 1;
  }

  gtk_entry_set_text(GTK_ENTRY(prod_prc_nome_entry),row[PRC_NOME_COL]);
  gtk_entry_set_text(GTK_ENTRY(prod_prc_prodcode_entry),row[PRC_PROD_COL]);
  gtk_widget_activate(prod_prc_prodcode_entry);
  gtk_entry_set_text(GTK_ENTRY(prod_prc_vlrfat_entry),row[PRC_VLRFAT_COL]);
  gtk_widget_activate(prod_prc_vlrfat_entry);
  gtk_entry_set_text(GTK_ENTRY(prod_prc_vlrvist_entry),row[PRC_VLRVIST_COL]);
  gtk_widget_activate(prod_prc_vlrvist_entry);
  gtk_widget_set_sensitive(prod_prc_alterar_button, FALSE);
  gtk_widget_set_sensitive(prod_prc_codepsq_button, FALSE);
  gtk_widget_set_sensitive(prod_prc_code_entry, FALSE);
  gtk_widget_grab_focus(prod_prc_nome_entry);

  return 0;
}
