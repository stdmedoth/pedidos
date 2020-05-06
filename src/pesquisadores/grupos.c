void receber_grp_code(GtkWidget *button, GtkTreeView *treeview)
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;
	char *codigo;
	codigo = malloc(MAX_CODE_LEN);
	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview));
	if(!gtk_tree_selection_get_selected(selection, &model, &iter))
		return ;
	gtk_tree_model_get (model, &iter, 0, &codigo, -1);
	gtk_entry_set_text(GTK_ENTRY(pesquisa_global_alvo),codigo);
	gtk_widget_activate(GTK_WIDGET(pesquisa_global_alvo));
	gtk_widget_destroy(psq_grp_wnd);
}

int entry_grp_pesquisa(GtkEntry *widget, GtkTreeView *treeview)
{
	enum {N_COLUMNS=2,COLUMN0=0,COLUMN1=1};
	GtkTreeStore *treestore	=	GTK_TREE_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
    g_object_ref(G_OBJECT(treestore));
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),NULL);
    gtk_tree_store_clear(treestore);
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(treestore));
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	gchar *entrada = malloc(MAX_GRP_LEN);
	entrada = (gchar*)gtk_entry_get_text(widget);
	GtkTreeIter colunas, campos;
	GtkTreeStore *modelo = (GtkTreeStore*) gtk_tree_view_get_model(treeview);
	sprintf(query,"select * from grupos where nome like '%c%s%c'",37,entrada,37);
	res = consultar(query);
	if(res == NULL)
	{
		return 1;
	}
	while((row = mysql_fetch_row(res))!=NULL)
	{
		gtk_tree_store_append(modelo,&campos,NULL);
		g_print("Inserindo codigo: %s nome: %s\n",row[0],row[1]);
		gtk_tree_store_set(modelo,&campos, COLUMN0,row[0],-1);
		
		gtk_tree_store_set(modelo,&campos, COLUMN1,row[1],-1);
	}
	return 0;
}

int pesquisa_grp(GtkWidget *button, GtkEntry *cod_grp_entry)
{
	enum {N_COLUMNS=2,COLUMN0=0,COLUMN1=1};
	GtkWidget *scrollwindow;
	GtkTreeViewColumn *coluna1, *coluna2;
	GtkCellRenderer *celula1, *celula2;
	GtkWidget *treeview;
	GtkTreeStore *modelo;
	GtkTreeIter colunas, campos;
	GtkWidget *pesquisa_entry;
	GtkWidget *caixa_grande;
	
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	
	GtkWidget *escolher_campo_button, *escolher_campo_img, *escolher_campo_fixed;
	
	caixa_grande = gtk_box_new(1,0);
	pesquisa_entry = gtk_entry_new();
	coluna1 = gtk_tree_view_column_new();
	coluna2 = gtk_tree_view_column_new();
	celula1 = gtk_cell_renderer_text_new();
	celula2 = gtk_cell_renderer_text_new();
	treeview = gtk_tree_view_new();
	
	gtk_tree_view_set_enable_tree_lines(GTK_TREE_VIEW(treeview),TRUE);
	gtk_tree_view_set_enable_search(GTK_TREE_VIEW(treeview),TRUE);
	gtk_tree_view_set_search_entry(GTK_TREE_VIEW(treeview),GTK_ENTRY(pesquisa_entry));
	gtk_tree_view_set_search_entry(GTK_TREE_VIEW(treeview),NULL);
	scrollwindow = gtk_scrolled_window_new(NULL,NULL);
	
	psq_grp_wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(psq_grp_wnd),3);
	gtk_window_set_keep_above(GTK_WINDOW(psq_grp_wnd),TRUE);
	gtk_widget_set_size_request(psq_grp_wnd,500,250);
	
	gtk_tree_view_column_pack_start(coluna1,celula1,TRUE);
	gtk_tree_view_column_set_title(coluna1,"Código");
	gtk_tree_view_column_add_attribute(coluna1,celula1,"text",0);
	
	gtk_tree_view_column_pack_start(coluna2,celula2,TRUE);
	gtk_tree_view_column_set_title(coluna2,"Nome");
	gtk_tree_view_column_add_attribute(coluna2,celula2,"text",1);

	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna1);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna2);
	gtk_tree_view_set_search_column(GTK_TREE_VIEW(treeview),1);
	modelo = gtk_tree_store_new(N_COLUMNS,G_TYPE_STRING,G_TYPE_STRING);
	
	sprintf(query,"select * from grupos");
	res = consultar(query);
	if(res == NULL)
	{
		return 1;
	}
	while((row = mysql_fetch_row(res))!=NULL)
	{
		gtk_tree_store_append(modelo,&campos,NULL);
		g_print("Inserindo codigo: %s nome: %s\n",row[0],row[1]);
		gtk_tree_store_set(modelo,&campos, COLUMN0,row[0],-1);
		
		gtk_tree_store_set(modelo,&campos, COLUMN1,row[1],-1);
	}
	
	gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(modelo));
	#ifdef __linux__
	gtk_container_add(GTK_CONTAINER(scrollwindow),treeview);
	#endif
	#ifdef WIN32
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrollwindow),treeview);
	#endif
	
	escolher_campo_button = gtk_button_new_with_label("Escolher");
	escolher_campo_img = gtk_image_new_from_file(IMG_PROCR);
	escolher_campo_fixed = gtk_fixed_new();
	gtk_button_set_image(GTK_BUTTON(escolher_campo_button),escolher_campo_img);
	gtk_fixed_put(GTK_FIXED(escolher_campo_fixed),escolher_campo_button,20,10);

	
	gtk_widget_set_size_request(scrollwindow,450,200);
	//gtk_box_pack_start(GTK_BOX(caixa_grande),pesquisa_entry,0,0,0);
	gtk_container_set_border_width(GTK_CONTAINER(psq_grp_wnd),10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),scrollwindow,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),escolher_campo_fixed,0,0,10);
	gtk_container_add(GTK_CONTAINER(psq_grp_wnd),caixa_grande);
	g_signal_connect(pesquisa_entry,"activate",G_CALLBACK(entry_grp_pesquisa),treeview);
	pesquisa_global_alvo = GTK_ENTRY(cod_grp_entry);
	g_signal_connect(escolher_campo_button,"clicked",G_CALLBACK(receber_grp_code),treeview);
	gtk_widget_show_all(psq_grp_wnd);
	return 0;
}

