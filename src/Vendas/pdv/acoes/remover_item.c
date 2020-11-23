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

	gtk_tree_model_get (model, &iter, 0, &codigo, -1);
  gtk_tree_store_remove(GTK_TREE_STORE(model), &iter);

  return 0;
}
