void cad_rel_rem_row_fun(GtkWidget *button, GtkTreeView *treeview)
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	int id;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview));

	if(!gtk_tree_selection_get_selected(selection, &model, &iter))
		return ;

	gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, 0, &id, -1);

	g_print("removendo campo %i\n",id);
	sprintf(query,"delete from criador_relat where code = %s and campos = %i",cad_rel_code_gchar,id);
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Não foi possivel remover campo");
		return ;
	}
	cont=0;
	while(cont<=MAX_RELAT_CAMPOS)
	{
		if(relat_struct.status[cont] == TRUE)
		{
			if(relat_struct.campos_code[cont] == id)
			{
				relat_struct.status[cont] = FALSE;
			}
		}
		cont++;
	}

	relat_struct.qnt_campos--;

	if(relat_struct.qnt_campos<=0)
	{
		gtk_widget_set_sensitive(campos_rel_remover_button,FALSE);
	}
	relat_campo_atual--;
	gtk_tree_store_remove(GTK_TREE_STORE(model),&iter);

}
