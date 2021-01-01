int ordem_cmp_alterar_fun(){
  ordem_cmp_alterando = 1;

  MYSQL_RES *res;
  MYSQL_ROW row;
  char *query = malloc(MAX_QUERY_LEN);
  sprintf(query, "select code, fornecedor, DATE_FORMAT(dtemissao, '%%d/%%m/%%Y'), DATE_FORMAT(dtentrega, '%%d/%%m/%%Y'), condpag, status from ordens_compra where code = %s", ordem_cmp_code_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar existencia da ordem de compra");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL, "Ordem de compra não existente");
    return 1;
  }

  gtk_entry_set_text(GTK_ENTRY(ordem_cmp_forncode_entry),  row[ORD_CMP_FORN] );
  gtk_entry_set_text(GTK_ENTRY(ordem_cmp_dtemissao_entry), row[ORD_CMP_DTEMIT] );
  gtk_entry_set_text(GTK_ENTRY(ordem_cmp_dtentrega_entry), row[ORD_CMP_DTENTR] );
  gtk_entry_set_text(GTK_ENTRY(ordem_cmp_condpag_entry), row[ORD_CMP_CONDPAG] );
  gtk_combo_box_set_active(GTK_COMBO_BOX(ordem_cmp_status_combo),atoi(row[ORD_CMP_STATUS]));
  if(atoi(row[ORD_CMP_STATUS]) != ORDCMP_N_GERADO){
    //gtk_widget_set_sensitive(ordem_cmp_status_combo, TRUE);
    gtk_combo_box_set_button_sensitivity(GTK_COMBO_BOX(ordem_cmp_status_combo), GTK_SENSITIVITY_ON);
  }

  //gtk_entry_set_text(GTK_ENTRY(ordem_cmp_condpag_entry), );

  gtk_widget_set_sensitive(ordem_cmp_code_entry, FALSE);
  gtk_widget_set_sensitive(ordem_cmp_codepsq_button, FALSE);
  gtk_widget_set_sensitive(ordem_cmp_alterar_button, FALSE);

  enum {
    ID_COLUMN,
    PROD_NOME_COLUMN,
    PROD_QNT_COLUMN,
    PROD_VLR_COLUMN,
    N_COLUMNS
  };

  GtkTreeIter campos;
  GtkTreeStore *model =(GtkTreeStore *) gtk_tree_view_get_model(GTK_TREE_VIEW(ordem_cmp_ordreq_treeview));
  if(!model)
    model = gtk_tree_store_new(N_COLUMNS, G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING);

  g_object_ref(G_OBJECT(model));
  gtk_tree_view_set_model(GTK_TREE_VIEW(ordem_cmp_ordreq_treeview),NULL);
  gtk_tree_store_clear(model);
  gtk_tree_view_set_model(GTK_TREE_VIEW(ordem_cmp_ordreq_treeview),GTK_TREE_MODEL(model));

  sprintf(query,"select ct.code, p.nome, ct.qnt, ct.preco, p.code, ict.code from itens_cotacoes as ct inner join prod_requisicoes as req inner join produtos as p inner join itens_ordens_compra as ict on ct.requisicao = req.code and req.produto = p.code and ict.itens_cotacao = ct.code where ict.ordem_id = %s", ordem_cmp_code_gchar);
  if(!(res = consultar(query))){
    return 1;
  }
  while((row = mysql_fetch_row(res))){
    MYSQL_RES *res2;
    MYSQL_ROW row2;
    sprintf(query,"select u.nome from produtos as p inner join unidades as u on p.unidades = u.code where p.code = %s", row[N_COLUMNS]);
    if(!(res2 = consultar(query))){
      popup(NULL,"Não foi possível consultar unidade padrão do produto");
      return 1;
    }
    if(!(row2 = mysql_fetch_row(res2))){
      gchar *msg = malloc(strlen(row[PROD_NOME_COLUMN]) + 100);
      sprintf(msg, "O produto %s está sem unidade", row[PROD_NOME_COLUMN]);
      popup(NULL, msg);
      continue;
    }
    gchar *formatar_quantidade = malloc(strlen(row[PROD_QNT_COLUMN]) + strlen(row2[0]) + 10);
    sprintf(formatar_quantidade, "%s %s", row[PROD_QNT_COLUMN], row2[0]);
    gchar *formatar_valor = malloc(strlen(row[PROD_VLR_COLUMN]) + 10);
    sprintf(formatar_valor, "R$ %.2f", atof(row[PROD_VLR_COLUMN]));

    gtk_tree_store_append(model,&campos,NULL);
    gtk_tree_store_set(model,&campos,
    ID_COLUMN,row[ID_COLUMN],
    PROD_NOME_COLUMN,row[PROD_NOME_COLUMN],
    PROD_QNT_COLUMN, formatar_quantidade,
    PROD_VLR_COLUMN, formatar_valor,
    -1);
  }

  gtk_widget_activate(ordem_cmp_forncode_entry);
  gtk_widget_activate(ordem_cmp_condpag_entry);
  return 0;
}
