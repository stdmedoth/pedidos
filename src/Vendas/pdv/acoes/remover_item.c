int pdv_rem_item_fun(GtkWidget *button, GtkTreeView *treeview){

	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;
	char *codigo;
  gtk_label_set_text(GTK_LABEL(pdv_acaoatual_label), "Removendo Item");

  codigo = malloc(MAX_CODE_LEN);
	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW(treeview));
	if(!gtk_tree_selection_get_selected(selection, &model, &iter))
		return 1;

	if(!get_gestor_perm(NULL, janelas_gerenciadas.vetor_janelas[REG_PDV_WND].janela_pointer))
		return 1;

	gtk_tree_model_get (model, &iter, 0, &codigo, -1);

	GtkTreePath *path = gtk_tree_model_get_path (GTK_TREE_MODEL(model), &iter);
  gint *posP = gtk_tree_path_get_indices(path);
  if(!posP)
    return 1;
  gint pos = *posP;

	pdv_venda_atual->cupom_atual->det->produtos[pos].cProd = inttochar(0);
  pdv_venda_atual->cupom_atual->det->produtos[pos].nItem = inttochar(0);
	pdv_venda_atual->itens_qnt--;

  gtk_tree_store_remove(GTK_TREE_STORE(model), &iter);

  return 0;
}
