void receber_srv_trsp_code(GtkWidget *button, GtkTreeView *treeview)
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
	gtk_widget_destroy(psq_srv_trsp_wnd);
}

int entry_srv_trsp_pesquisa(GtkEntry *widget, GtkTreeView *treeview)
{
	enum {N_COLUMNS=5,COLUMN0=0, COLUMN1=1, COLUMN2=2, COLUMN3=3, COLUMN4=4};
	GtkTreeStore *treestore	=	GTK_TREE_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
    g_object_ref(G_OBJECT(treestore));
    gchar *formata_preco = malloc(MAX_PRECO_LEN);
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
	sprintf(query,"select s.code, t.razao, c.razao, s.orcamento, s.vlr_frete from servico_transporte as s inner join terceiros as c inner join terceiros as t on c.code = s.cliente and t.code = s.transportador where c.razao like '%c%s%c' order by code desc limit 20",37,entrada,37);
	res = consultar(query);
	if(res == NULL)
	{
		return 1;
	}
	while((row = mysql_fetch_row(res))!=NULL)
	{
		sprintf(formata_preco,"R$ %.2f",atof(row[4]));
		gtk_tree_store_append(modelo,&campos,NULL);
		g_print("Inserindo codigo: %s nome: %s\n",row[0],row[1]);

		gtk_tree_store_set(modelo,&campos,
		COLUMN0,row[0],
		COLUMN1,row[1],
		COLUMN2,row[2],
		COLUMN3,row[3],
		COLUMN4,formata_preco,-1);
	}
	return 0;
}

int psq_srv_trsp(GtkWidget *button, GtkEntry *cod_srv_trsp_entry)
{
	enum {N_COLUMNS=5,COLUMN0=0, COLUMN1=1, COLUMN2=2, COLUMN3=3, COLUMN4=4};
	GtkWidget *scrollwindow;
	GtkTreeViewColumn *coluna1, *coluna2, *coluna3, *coluna4, *coluna5;
	GtkCellRenderer *celula1, *celula2, *celula3, *celula4, *celula5;
	gchar *formata_preco = malloc(MAX_PRECO_LEN);
	GtkWidget *treeview;
	GtkTreeStore *modelo;
	GtkTreeIter colunas, campos;
	GtkWidget *pesquisa_entry;
	GtkWidget *caixa_grande;
	gchar *entrada = malloc(MAX_GRP_LEN);
	GtkWidget *escolher_campo_button, *escolher_campo_img, *escolher_campo_fixed;

	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	caixa_grande = gtk_box_new(1,0);
	pesquisa_entry = gtk_entry_new();
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
	gtk_tree_view_set_enable_search(GTK_TREE_VIEW(treeview),TRUE);
	gtk_tree_view_set_search_entry(GTK_TREE_VIEW(treeview),GTK_ENTRY(pesquisa_entry));
	gtk_tree_view_set_search_entry(GTK_TREE_VIEW(treeview),NULL);
	scrollwindow = gtk_scrolled_window_new(NULL,NULL);

	psq_srv_trsp_wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(psq_srv_trsp_wnd),3);
	gtk_window_set_icon_name(GTK_WINDOW(psq_srv_trsp_wnd),"system-search");
	gtk_window_set_keep_above(GTK_WINDOW(psq_srv_trsp_wnd),TRUE);
	gtk_widget_set_size_request(psq_srv_trsp_wnd,500,250);

	gtk_tree_view_column_pack_start(coluna1,celula1,TRUE);
	gtk_tree_view_column_set_title(coluna1,"Código");
	gtk_tree_view_column_add_attribute(coluna1,celula1,"text",0);

	gtk_tree_view_column_pack_start(coluna2,celula2,TRUE);
	gtk_tree_view_column_set_title(coluna2,"Transportadora");
	gtk_tree_view_column_add_attribute(coluna2,celula2,"text",1);

	gtk_tree_view_column_pack_start(coluna3,celula3,TRUE);
	gtk_tree_view_column_set_title(coluna3,"Cliente");
	gtk_tree_view_column_add_attribute(coluna3,celula3,"text",2);

	gtk_tree_view_column_pack_start(coluna4,celula4,TRUE);
	gtk_tree_view_column_set_title(coluna4,"Orcamento");
	gtk_tree_view_column_add_attribute(coluna4,celula4,"text",3);

	gtk_tree_view_column_pack_start(coluna5,celula5,TRUE);
	gtk_tree_view_column_set_title(coluna5,"Valor");
	gtk_tree_view_column_add_attribute(coluna5,celula5,"text",4);

	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna1);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna2);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna3);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna4);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna5);

	gtk_tree_view_set_search_column(GTK_TREE_VIEW(treeview),1);
	modelo = gtk_tree_store_new(N_COLUMNS,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	sprintf(query,"select s.code, t.razao, c.razao, s.orcamento, s.vlr_frete from servico_transporte as s inner join terceiros as c inner join terceiros as t on c.code = s.cliente and t.code = s.transportador order by code desc limit 20");
	res = consultar(query);
	if(res == NULL)
	{
		return 1;
	}


	while((row = mysql_fetch_row(res))!=NULL)
	{
		sprintf(formata_preco,"R$ %.2f",atof(row[4]));
		gtk_tree_store_append(modelo,&campos,NULL);
		g_print("Inserindo codigo: %s nome: %s\n",row[0],row[1]);
		gtk_tree_store_set(modelo,&campos,
		COLUMN0,row[0],
		COLUMN1,row[1],
		COLUMN2,row[2],
		COLUMN3,row[3],
		COLUMN4,formata_preco,-1);
	}

	gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(modelo));

	gtk_container_add(GTK_CONTAINER(scrollwindow),treeview);


	escolher_campo_button = gtk_button_new_with_label("Selecionar");
	escolher_campo_img = gtk_image_new_from_file(IMG_PROCR);
	escolher_campo_fixed = gtk_fixed_new();
	gtk_button_set_image(GTK_BUTTON(escolher_campo_button),escolher_campo_img);
	gtk_fixed_put(GTK_FIXED(escolher_campo_fixed),escolher_campo_button,20,10);

	gtk_widget_set_size_request(scrollwindow,600,250);
	gtk_box_pack_start(GTK_BOX(caixa_grande),pesquisa_entry,0,0,0);
	gtk_container_set_border_width(GTK_CONTAINER(psq_srv_trsp_wnd),10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),scrollwindow,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),escolher_campo_fixed,0,0,10);
	gtk_container_add(GTK_CONTAINER(psq_srv_trsp_wnd),caixa_grande);
	g_signal_connect(pesquisa_entry,"activate",G_CALLBACK(entry_srv_trsp_pesquisa),treeview);
	pesquisa_global_alvo = GTK_ENTRY(cod_srv_trsp_entry);
		g_signal_connect(treeview,"row-activated",G_CALLBACK(receber_psq_code_space),psq_srv_trsp_wnd);
	g_signal_connect(escolher_campo_button,"clicked",G_CALLBACK(receber_srv_trsp_code),treeview);
	gtk_widget_show_all(psq_srv_trsp_wnd);
	return 0;
}
