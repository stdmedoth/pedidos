int cotat_itens_prod_fun(GtkEntry *entry, int pos){

  if(cotac_get_participante())
    return 1;

  int cod = cotac_get_participante_index(atoi(cotac_partc_gchar));

  gchar *text = (gchar*)gtk_entry_get_text(entry);

  if(!text || !strlen(text)){
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
  cotacao_new->cotacao_itens[cod][pos].produto = atoi(text);
  cotac_produto_inserido[cod][pos] = 1;

  gtk_entry_set_text(GTK_ENTRY(cotac_prod_nome_entry[cod][pos]),row[PROD_NOM_COL]);
  gtk_widget_grab_focus(cotac_prod_qnt_entry[cod][pos]);
  return 0;
}
