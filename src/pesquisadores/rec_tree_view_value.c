void receber_tree_code(GtkWidget *button, GtkTreeView *treeview)
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;
	char *codigo;
	codigo = malloc(MAX_CODE_LEN);

	/*if(GTK_TREE_VIEW(button))
	{
		treeview = GTK_TREE_VIEW(button);
	}*/

	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview));
	if(!gtk_tree_selection_get_selected(selection, &model, &iter))
		return ;
	gtk_tree_model_get (model, &iter, 0, &codigo, -1);

	if(pesquisa_global_alvo){
		gtk_entry_set_text(GTK_ENTRY(pesquisa_global_alvo),codigo);
		gtk_widget_activate(GTK_WIDGET(pesquisa_global_alvo));
	}

	gtk_widget_destroy(psq_oper_wnd);
}
void receber_tree_code_space(GtkWidget *button, GtkTreePath *path, GtkTreeViewColumn *column, GtkTreeView *treeview)
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;
	char *codigo;
	codigo = malloc(MAX_CODE_LEN);

	/*if(GTK_TREE_VIEW(button))
	{
		treeview = GTK_TREE_VIEW(button);
	}*/

	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview));
	if(!gtk_tree_selection_get_selected(selection, &model, &iter))
		return ;
	gtk_tree_model_get (model, &iter, 0, &codigo, -1);

	if(pesquisa_global_alvo){
		gtk_entry_set_text(GTK_ENTRY(pesquisa_global_alvo),codigo);
		gtk_widget_activate(GTK_WIDGET(pesquisa_global_alvo));
	}

	gtk_widget_destroy(gtk_widget_get_parent(gtk_widget_get_parent(GTK_WIDGET(treeview))));
}
