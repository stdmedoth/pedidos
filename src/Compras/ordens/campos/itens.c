int ordem_cmp_selecionar_req(){
  enum {
		ID_COLUMN,
		PROD_NOME_COLUMN,
		PROD_QNT_COLUMN,
		PROD_VLR_COLUMN,
		N_COLUMNS
	};

  GtkTreeSelection *selection;
  GtkTreeModel *req_model, *ordreq_model;
  GtkTreeIter req_iter, ordreq_iter;
  char *id = malloc(MAX_CODE_LEN);
  char *nome = malloc(MAX_NAME_LEN);
  char *qnt = malloc(20+MAX_NAME_LEN);
  char *vlr = malloc(20);

  selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (ordem_cmp_req_treeview));
  if(!gtk_tree_selection_get_selected(selection, &req_model, &req_iter))
    return 1;

  gtk_tree_model_get (req_model, &req_iter,
    ID_COLUMN, &id,
    PROD_NOME_COLUMN, &nome,
    PROD_QNT_COLUMN, &qnt,
    PROD_VLR_COLUMN, &vlr,
    -1);

  ordreq_model = gtk_tree_view_get_model(GTK_TREE_VIEW(ordem_cmp_ordreq_treeview));
  if(!ordreq_model)
    return 1;

  gtk_tree_store_append(GTK_TREE_STORE(ordreq_model),&ordreq_iter,NULL);
  gtk_tree_store_set(GTK_TREE_STORE(ordreq_model),&ordreq_iter,
    ID_COLUMN,id,
    PROD_NOME_COLUMN,nome,
    PROD_QNT_COLUMN,qnt,
    PROD_VLR_COLUMN,vlr,
    -1);

  gtk_tree_store_remove(GTK_TREE_STORE(req_model),&req_iter);
  return 0;
}

int ordem_cmp_deselecionar_req(){
  enum {
    ID_COLUMN,
    PROD_NOME_COLUMN,
    PROD_QNT_COLUMN,
    PROD_VLR_COLUMN,
    N_COLUMNS
  };

  GtkTreeSelection *selection;
  GtkTreeModel *req_model, *ordreq_model;
  GtkTreeIter req_iter, ordreq_iter;
  char *id = malloc(MAX_CODE_LEN);
  char *nome = malloc(MAX_NAME_LEN);
  char *qnt = malloc(20+MAX_NAME_LEN);
  char *vlr = malloc(20);

  selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (ordem_cmp_ordreq_treeview));
  if(!gtk_tree_selection_get_selected(selection, &ordreq_model, &ordreq_iter))
    return 1;

  gtk_tree_model_get (ordreq_model, &ordreq_iter,
    ID_COLUMN, &id,
    PROD_NOME_COLUMN, &nome,
    PROD_QNT_COLUMN, &qnt,
    PROD_VLR_COLUMN, &vlr,
    -1);

  req_model = gtk_tree_view_get_model(GTK_TREE_VIEW(ordem_cmp_req_treeview));
  if(!req_model)
    return 1;

  gtk_tree_store_append(GTK_TREE_STORE(req_model),&req_iter,NULL);
  gtk_tree_store_set(GTK_TREE_STORE(req_model),&req_iter,
    ID_COLUMN,id,
    PROD_NOME_COLUMN,nome,
    PROD_QNT_COLUMN,qnt,
    PROD_VLR_COLUMN,vlr,
    -1);

  ordem_cmp_excluidos[ordem_cmp_excluido_pos] = atoi(id);
  ordem_cmp_excluido_pos++;
  gtk_tree_store_remove(GTK_TREE_STORE(ordreq_model),&ordreq_iter);
  return 0;
}
