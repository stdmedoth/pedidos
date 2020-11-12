int cotat_itens_prod_fun(GtkEntry *entry, int pos){

  gchar *text = (gchar*)gtk_entry_get_text(entry);

  if(!strlen(text)){
    popup(NULL,"Insira o código do produto");
    return 1;
  }

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  sprintf(query,"SELECT * FROM produtos WHERE code = %s",text);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar produto");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Produto não existente");
    return 1;
  }
  cotac_produto_inserido[pos] = 1;
  
  gtk_entry_set_text(GTK_ENTRY(cotac_prod_nome_entry[pos]),row[PROD_NOM_COL]);
  gtk_widget_grab_focus(cotac_prod_qnt_entry[pos]);
  return 0;
}
