void receber_cntrat_code(GtkWidget *button, GtkTreeView *treeview)
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
	if(pesquisa_global_alvo){
		gtk_entry_set_text(GTK_ENTRY(pesquisa_global_alvo),codigo);
		gtk_widget_activate(GTK_WIDGET(pesquisa_global_alvo));
	}
	gtk_widget_destroy(psq_cntrat_wnd);
}

int psq_cntrat(GtkWidget *button, GtkEntry *cod_cntrat_entry)
{
	enum {
		COLUMN0,
		COLUMN1,
		COLUMN2,
		N_COLUMNS
	};

	GtkWidget *scrollwindow;
	GtkTreeViewColumn *coluna1, *coluna2, *coluna3, *coluna4, *coluna5;
	GtkCellRenderer *celula1, *celula2, *celula3, *celula4, *celula5;
	GtkWidget *treeview;
	GtkTreeStore *modelo;
	GtkTreeIter colunas, campos;
	GtkWidget *caixa_grande;
	gchar *entrada = malloc(MAX_GRP_LEN);
	GtkWidget *escolher_campo_button, *escolher_campo_img, *escolher_campo_fixed;

	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	caixa_grande = gtk_box_new(1,0);
	coluna1 = gtk_tree_view_column_new();
	celula1 = gtk_cell_renderer_text_new();

	coluna2 = gtk_tree_view_column_new();
	celula2 = gtk_cell_renderer_text_new();

	coluna3 = gtk_tree_view_column_new();
	celula3 = gtk_cell_renderer_text_new();

	coluna4 = gtk_tree_view_column_new();
	celula4 = gtk_cell_renderer_text_new();

	coluna5 = gtk_tree_view_column_new();
	celula5 = gtk_cell_renderer_text_new();

	treeview = gtk_tree_view_new();

	gtk_tree_view_set_enable_tree_lines(GTK_TREE_VIEW(treeview),TRUE);
	gtk_tree_view_set_level_indentation(GTK_TREE_VIEW(treeview),30);

	gtk_tree_view_set_enable_search(GTK_TREE_VIEW(treeview),TRUE);
	gtk_tree_view_set_search_entry(GTK_TREE_VIEW(treeview),NULL);
	scrollwindow = gtk_scrolled_window_new(NULL,NULL);

	psq_cntrat_wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(psq_cntrat_wnd),3);
	gtk_window_set_icon_name(GTK_WINDOW(psq_cntrat_wnd),"system-search");
	if(personalizacao.janela_keep_above==1)
		gtk_window_set_keep_above(GTK_WINDOW(psq_cntrat_wnd),TRUE);
	gtk_widget_set_size_request(psq_cntrat_wnd,500,250);

	gtk_tree_view_column_pack_start(coluna1,celula1,TRUE);
	gtk_tree_view_column_set_title(coluna1,"Código");
	gtk_tree_view_column_add_attribute(coluna1,celula1,"text",0);
	gtk_tree_view_column_set_visible(coluna1,FALSE);

	gtk_tree_view_column_pack_start(coluna2,celula2,TRUE);
	gtk_tree_view_column_set_title(coluna2,"Ativo?");
	gtk_tree_view_column_add_attribute(coluna2,celula2,"text",1);

	gtk_tree_view_column_pack_start(coluna3,celula3,TRUE);
	gtk_tree_view_column_set_title(coluna3,"Vencimento");
	gtk_tree_view_column_add_attribute(coluna3,celula3,"text",2);

	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna1);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna2);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna3);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna4);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna5);

	gtk_tree_view_set_search_column(GTK_TREE_VIEW(treeview),1);
	modelo = gtk_tree_store_new(N_COLUMNS,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	sprintf(query,"select code, ativo, DATE_FORMAT(data_vencimento, '%%d/%%m/%%Y') from contratos");
	res = consultar(query);
	if(!res){
		return 1;
	}

	int cont=0;

	while((row = mysql_fetch_row(res))){

		if(atoi(row[1]))
			row[1] = strdup("Ativo");
		else
			row[1] = strdup("Inativo");

		gtk_tree_store_append(modelo,&campos,NULL);
		gtk_tree_store_set(modelo,&campos,
		COLUMN0,row[0],
		COLUMN1,row[1],
		COLUMN2,row[2],-1);
		cont++;
	}

	gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(modelo));

	gtk_container_add(GTK_CONTAINER(scrollwindow),treeview);

	escolher_campo_button = gtk_button_new_with_label("Selecionar");
	escolher_campo_img = gtk_image_new_from_file(IMG_PROCR);
	escolher_campo_fixed = gtk_fixed_new();
	gtk_button_set_image(GTK_BUTTON(escolher_campo_button),escolher_campo_img);
	gtk_fixed_put(GTK_FIXED(escolher_campo_fixed),escolher_campo_button,20,10);

	gtk_widget_set_size_request(scrollwindow,600,250);
	gtk_container_set_border_width(GTK_CONTAINER(psq_cntrat_wnd),10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),scrollwindow,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),escolher_campo_fixed,0,0,10);
	gtk_container_add(GTK_CONTAINER(psq_cntrat_wnd),caixa_grande);
	g_signal_connect(treeview,"row-activated",G_CALLBACK(receber_psq_code_space),psq_cntrat_wnd);
	pesquisa_global_alvo = GTK_ENTRY(cod_cntrat_entry);
	g_signal_connect(escolher_campo_button,"clicked",G_CALLBACK(receber_cntrat_code),treeview);
	gtk_widget_show_all(psq_cntrat_wnd);
	return 0;
}
