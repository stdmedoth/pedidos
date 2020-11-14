int cotat_itens_prod_fun(GtkEntry *entry, int pos){

  if(cotac_get_participante())
    return 1;

  int cod = cotac_get_participante_index(atoi(cotac_partc_gchar));
  int produto, requisicao;
  char *quantidade, *preco;
  gchar *text = (gchar*)gtk_entry_get_text(entry);

  if( (text == NULL) && !(strlen(text)) ){
    popup(NULL,"Insira a requisição");
    return 1;
  }
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  sprintf(query,"SELECT * FROM prod_requisicoes WHERE code = %i",atoi(text));
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar Requisição");
    gtk_entry_set_text(GTK_ENTRY( cotac_prod_nome_entry[cod][pos]), "" );
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Requisição não existe");
    gtk_entry_set_text(GTK_ENTRY( cotac_prod_nome_entry[cod][pos]), "" );
    return 1;
  }

  requisicao = atoi(row[REQ_CODE_COL]);
  produto = atoi(row[REQ_PROD_COL]);
  quantidade = strdup(row[REQ_QNT_COL]);
  gtk_entry_set_text(GTK_ENTRY(cotac_prod_qnt_entry[cod][pos]),quantidade);

  sprintf(query,"SELECT * FROM produtos WHERE code = %i",produto);

  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar produto");
    gtk_entry_set_text(GTK_ENTRY( cotac_prod_nome_entry[cod][pos]), "" );
    return 1;
  }

  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Produto da requisição não existente");
    gtk_entry_set_text(GTK_ENTRY( cotac_prod_nome_entry[cod][pos]), "" );
    return 1;
  }

  cotacao_new->cotacao_itens[cod][pos].requisicao = requisicao;
  cotacao_new->cotacao_itens[cod][pos].produto = produto;
  cotacao_new->cotacao_itens[cod][pos].quantidade = atof(quantidade);

  cotac_produto_inserido[cod][pos] = 1;

  gtk_entry_set_text(GTK_ENTRY( cotac_prod_nome_entry[cod][pos]), row[ PROD_NOM_COL ] );
  gtk_widget_grab_focus( cotac_prod_qnt_entry[cod][pos] );
  return 0;
}
