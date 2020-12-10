int mkt_cad_distrib_ult_rem(){
  for(int cont=0;cont<MAX_MAILDISTRIB_CONTTS;cont++){
    if(!mkt_cad_distrib_removidos[cont]){
      return cont;
    }
  }
  return MAX_MAILDISTRIB_CONTTS;
}

int mkt_cad_distrib_rem_fun(GtkTreeView *treeview, GtkTreePath *path,  GtkTreeViewColumn *column){

	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;
	char *codigo;
	codigo = malloc(MAX_CODE_LEN);


	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview));
	if(!gtk_tree_selection_get_selected(selection, &model, &iter))
		return 1;
	gtk_tree_model_get (model, &iter, 0, &codigo, -1);

  int ult_removido = mkt_cad_distrib_ult_rem();
  if(ult_removido > MAX_MAILDISTRIB_CONTTS)
    return 1;
	mkt_cad_distrib_removidos[ult_removido] = atoi(codigo);

  gtk_tree_store_remove(GTK_TREE_STORE(model), &iter);
  return 0;
}
