int pdv_codprod_fun(){
  enum{
    COLUMN0,
    COLUMN1,
    COLUMN2,
    COLUMN3,
    COLUMN4,
    COLUMN5,
    N_COLUMNS
  };

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  gchar *codprod = (gchar*)gtk_entry_get_text(GTK_ENTRY(pdv_codprod_entry));
  if(!strlen(codprod)){
    return 1;
  }

  if(pdv_venda_atual->operacao_atual == PDV_PSQ_ITEM_OPER){
    if(pdv_prod_antes_psq && strlen(pdv_prod_antes_psq)){
      gchar *codprod2 = malloc(strlen(codprod) + strlen(pdv_prod_antes_psq));
      sprintf(codprod2 , "%s%s", pdv_prod_antes_psq, codprod);
      gtk_entry_set_text(GTK_ENTRY(pdv_codprod_entry), codprod2 );
      codprod = realloc(codprod, strlen(codprod2));
      strcpy(codprod, codprod2);

    }
  }

  int int_codprod=0;
  int int_qntprod=0;
  gchar *char_nomeprod = malloc(MAX_NAME_LEN);

  //produtos com a quantidade
  if(sscanf(codprod, "%d*%d", &int_qntprod, &int_codprod)==2){
    g_print("%d produtos de código %d\n", int_qntprod, int_codprod );
    sprintf(query, "SELECT * FROM produtos WHERE code = '%i'", int_codprod);
    if(!(res = consultar(query))){
      popup(NULL,"Não foi possível consultar item");
      return 1;
    }
    if(!(row = mysql_fetch_row(res))){
      popup(NULL,"Item não existente");
      return 1;
    }
  }else
  if(sscanf(codprod, "%d*%s", &int_qntprod, char_nomeprod)==2){
    g_print("%d produtos %s\n", int_qntprod, char_nomeprod);
    sprintf(query, "SELECT * FROM produtos WHERE nome like '%c%s%c'",37,char_nomeprod,37);
    if(!(res = consultar(query))){
      popup(NULL,"Não foi possível consultar item");
      return 1;
    }
    if(!(row = mysql_fetch_row(res))){
      popup(NULL,"Item não existente");
      return 1;
    }
    if(mysql_num_rows(res) == 1){
      int_codprod = atoi(row[PROD_COD_COL]);
      g_print("1 produtos de código %d\n",  int_codprod );
    }else{
      gtk_label_set_text(GTK_LABEL(pdv_acaoatual_label), "Pesquisando Item");
      if(!psq_prod( NULL , GTK_ENTRY(pdv_codprod_entry))){
        gtk_entry_set_text(GTK_ENTRY(psq_prod_pesquisa_entry), char_nomeprod);
        return 0;
      }
    }
  }else
  //produtos sem a quantidade
  if(sscanf(codprod, "%d", &int_codprod)==1){
    g_print("1 produtos %i\n", int_codprod);
    int_qntprod = 1;
    sprintf(query, "SELECT * FROM produtos WHERE code = %i",int_codprod);
    if(!(res = consultar(query))){
      popup(NULL,"Não foi possível consultar item");
      return 1;
    }
    if(!(row = mysql_fetch_row(res))){
      popup(NULL,"Item não existente");
      return 1;
    }
  }else
  if(sscanf(codprod, "%s", char_nomeprod)==1){
    g_print("1 produtos %s\n", char_nomeprod);
    int_qntprod = 1;
    sprintf(query, "SELECT * FROM produtos WHERE nome like '%c%s%c'",37,char_nomeprod,37);
    if(!(res = consultar(query))){
      popup(NULL,"Não foi possível consultar item");
      return 1;
    }
    if(!(row = mysql_fetch_row(res))){
      popup(NULL,"Item não existente");
      return 1;
    }
  }else{
    return 1;
  }

  gchar *formata_qnt = malloc(MAX_PRECO_LEN);
  gchar *formata_preco = malloc(MAX_PRECO_LEN);
  gchar *formata_desconto = malloc(MAX_PRECO_LEN);
  gchar *formata_total = malloc(MAX_PRECO_LEN);
  float preco=0, qnt=0, desconto=0, total=0;
  GtkTreeStore *modelo	=	GTK_TREE_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(pdv_itens_treeview)));
  GtkTreeIter colunas, campos;
  gtk_tree_store_append(modelo,&campos,NULL);
  qnt = int_qntprod;
  sprintf(formata_qnt,"%d",int_qntprod);
  preco = atof(row[PROD_PRC_COL]);
  sprintf(formata_preco,"R$ %.2f",preco);
  sprintf(formata_desconto,"R$ %.2f",desconto);
  total = preco * qnt;
  sprintf(formata_total,"R$ %.2f",total);

  pdv_venda_atual->pdv_item_atual->produto = atoi(row[PROD_COD_COL]);
  pdv_venda_atual->pdv_item_atual->qnt = qnt;
  pdv_venda_atual->pdv_item_atual->vlr_unit = preco;
  pdv_venda_atual->pdv_item_atual->total = total;
  pdv_venda_atual->itens_qnt++;

  gtk_tree_store_set(modelo,&campos,
	COLUMN0,row[PROD_COD_COL],
	COLUMN1,row[PROD_NOM_COL],
  COLUMN2,formata_qnt,
	COLUMN3,formata_preco,
	COLUMN4,formata_desconto,
  COLUMN5,formata_total,
  -1);

  gchar *formulacao = malloc(strlen(row[PROD_NOM_COL]) + strlen(formata_qnt));
  sprintf(formulacao, "%s * %s",formata_qnt, row[PROD_NOM_COL]);
  gtk_label_set_text(GTK_LABEL(pdv_prodcod_label), formulacao);
  pdv_add_item_fun();
  return 0;
}

int pdv_add_item_fun(){
  pdv_venda_atual->status_atual = PDV_EM_VENDA;
  pdv_venda_atual->operacao_atual = PDV_ADD_ITEM_OPER;
  gtk_label_set_text(GTK_LABEL(pdv_acaoatual_label), "Adicionando Item");
  gtk_entry_set_text(GTK_ENTRY(pdv_codprod_entry), "");
  gtk_widget_grab_focus(pdv_codprod_entry);
  return 0;
}
