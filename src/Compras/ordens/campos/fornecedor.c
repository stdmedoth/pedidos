int ordem_cmp_fornecedor_fun(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  ordem_cmp_forncode_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(ordem_cmp_forncode_entry));
  if(!strlen(ordem_cmp_forncode_gchar)){
    popup(NULL,"O fornecedor deve ser inserido");
    gtk_widget_grab_focus(ordem_cmp_forncode_entry);
    return 1;
  }

  sprintf(query, "select * from terceiros where code = %s", ordem_cmp_forncode_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar existencia do fornecedor");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL, "Fornecedor não existente");
    return 1;
  }

  gtk_entry_set_text(GTK_ENTRY(ordem_cmp_fornnome_entry), row[RAZ_TER_COL]);

  enum {
    ID_COLUMN,
    PROD_NOME_COLUMN,
    PROD_QNT_COLUMN,
    PROD_VLR_COLUMN,
    N_COLUMNS
  };

  GtkTreeIter campos;
  GtkTreeStore *model =(GtkTreeStore *) gtk_tree_view_get_model(GTK_TREE_VIEW(ordem_cmp_req_treeview));
  if(!model)
    model = gtk_tree_store_new(N_COLUMNS, G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING);

  g_object_ref(G_OBJECT(model));
  gtk_tree_view_set_model(GTK_TREE_VIEW(ordem_cmp_req_treeview),NULL);
  gtk_tree_store_clear(model);
  gtk_tree_view_set_model(GTK_TREE_VIEW(ordem_cmp_req_treeview),GTK_TREE_MODEL(model));

  sprintf(query,"select ct.code, p.nome, ct.qnt, ct.preco, p.code from itens_cotacoes as ct inner join prod_requisicoes as req inner join produtos as p on ct.requisicao = req.code and req.produto = p.code where ct.participante_id = %s", ordem_cmp_forncode_gchar);
  if(!(res = consultar(query))){
    return 1;
  }
  while((row = mysql_fetch_row(res))){

    if(treeview_id_exists(GTK_TREE_VIEW(ordem_cmp_req_treeview), atoi(row[ID_COLUMN])))
      continue;

    if(treeview_id_exists(GTK_TREE_VIEW(ordem_cmp_ordreq_treeview), atoi(row[ID_COLUMN])))
      continue;

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

  gtk_widget_grab_focus(ordem_cmp_dtemissao_entry);
  return 0;
}
