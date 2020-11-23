void receber_prod_code(GtkWidget *button, GtkTreeView *treeview)
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
	gtk_widget_destroy(psq_prod_wnd);
}

int entry_prod_pesquisa(GtkEntry *widget, GtkTreeView *treeview)
{
	enum {N_COLUMNS=3,COLUMN0=0, COLUMN1=1, COLUMN2=2, COLUMN3=3};
	GtkTreeStore *treestore	=	GTK_TREE_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
    g_object_ref(G_OBJECT(treestore));
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),NULL);
    gtk_tree_store_clear(treestore);
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(treestore));
	MYSQL_RES *res;
	MYSQL_ROW row;

	gchar *formata_peso = malloc(MAX_PRECO_LEN);
	char query[MAX_QUERY_LEN];
	gchar *entrada = malloc(MAX_GRP_LEN);
	entrada = (gchar*)gtk_entry_get_text(widget);
	GtkTreeIter colunas, campos;
	GtkTreeStore *modelo = (GtkTreeStore*) gtk_tree_view_get_model(treeview);

	sprintf(query,"select p.code, p.nome, p.peso, g.nome from produtos as p inner join grupos as g on g.code = p.grupo where p.nome like '%c%s%c'",37,entrada,37);
	res = consultar(query);
	if(res == NULL){
		return 1;
	}
	while((row = mysql_fetch_row(res))!=NULL)
	{
		sprintf(formata_peso,"%.2f KG",atof(row[2]));
		gtk_tree_store_append(modelo,&campos,NULL);
		g_print("Inserindo codigo: %s nome: %s\n",row[0],row[1]);
		gtk_tree_store_set(modelo,&campos,
		COLUMN0,row[0],
		COLUMN1,row[1],
		COLUMN2,formata_peso,
		COLUMN3,row[3],-1);
	}
	return 0;
}

int psq_prod(GtkWidget *button, GtkEntry *cod_prod_entry)
{
	enum {N_COLUMNS=4,COLUMN0=0, COLUMN1=1, COLUMN2=2, COLUMN3=3};
	GtkWidget *scrollwindow;
	GtkTreeViewColumn *coluna1, *coluna2, *coluna3, *coluna4;
	GtkCellRenderer *celula1, *celula2, *celula3, *celula4;
	GtkWidget *treeview;
	GtkTreeStore *modelo;
	GtkTreeIter colunas, campos;

	GtkWidget *caixa_grande;

	gchar *entrada = malloc(MAX_GRP_LEN);
	GtkWidget *escolher_campo_button, *escolher_campo_img, *escolher_campo_fixed;

	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	gchar *formata_peso = malloc(MAX_PRECO_LEN);

	caixa_grande = gtk_box_new(1,0);
	psq_prod_pesquisa_entry = gtk_entry_new();
	coluna1 = gtk_tree_view_column_new();
	celula1 = gtk_cell_renderer_text_new();
	coluna2 = gtk_tree_view_column_new();
	celula2 = gtk_cell_renderer_text_new();
	coluna3 = gtk_tree_view_column_new();
	celula3 = gtk_cell_renderer_text_new();
	coluna4 = gtk_tree_view_column_new();
	celula4 = gtk_cell_renderer_text_new();

	treeview = gtk_tree_view_new();

	gtk_tree_view_set_enable_tree_lines(GTK_TREE_VIEW(treeview),TRUE);
	gtk_tree_view_set_level_indentation(GTK_TREE_VIEW(treeview),30);
	gtk_tree_view_set_enable_search(GTK_TREE_VIEW(treeview),TRUE);
	gtk_tree_view_set_search_entry(GTK_TREE_VIEW(treeview),GTK_ENTRY(psq_prod_pesquisa_entry));
	gtk_tree_view_set_search_entry(GTK_TREE_VIEW(treeview),NULL);
	scrollwindow = gtk_scrolled_window_new(NULL,NULL);

	psq_prod_wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(psq_prod_wnd),3);
	gtk_window_set_icon_name(GTK_WINDOW(psq_prod_wnd),"system-search");
	if(personalizacao.janela_keep_above==1)
		gtk_window_set_keep_above(GTK_WINDOW(psq_prod_wnd),TRUE);
	gtk_widget_set_size_request(psq_prod_wnd,500,250);

	gtk_tree_view_column_pack_start(coluna1,celula1,TRUE);
	gtk_tree_view_column_set_title(coluna1,"Código");
	gtk_tree_view_column_set_spacing(coluna1,5);
	gtk_tree_view_column_set_visible(coluna1,FALSE);
	gtk_tree_view_column_add_attribute(coluna1,celula1,"text",0);

	gtk_tree_view_column_pack_start(coluna2,celula2,TRUE);
	gtk_tree_view_column_set_title(coluna2,"Nome");
	gtk_tree_view_column_set_spacing(coluna2,5);
	gtk_tree_view_column_add_attribute(coluna2,celula2,"text",1);

	gtk_tree_view_column_pack_start(coluna3,celula3,TRUE);
	gtk_tree_view_column_set_title(coluna3,"Peso");
	gtk_tree_view_column_set_spacing(coluna3,5);
	gtk_tree_view_column_add_attribute(coluna3,celula3,"text",2);

	gtk_tree_view_column_pack_start(coluna4,celula4,TRUE);
	gtk_tree_view_column_set_title(coluna4,"Grupo");
	gtk_tree_view_column_set_spacing(coluna4,5);
	gtk_tree_view_column_add_attribute(coluna4,celula4,"text",3);

	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna1);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna2);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna3);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna4);
	gtk_tree_view_set_enable_search(GTK_TREE_VIEW(treeview),TRUE);
	gtk_tree_view_set_search_column(GTK_TREE_VIEW(treeview),1);
	modelo = gtk_tree_store_new(N_COLUMNS,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	sprintf(query,"select p.code, p.nome, p.peso, g.nome from produtos as p inner join grupos as g on g.code = p.grupo");
	res = consultar(query);
	if(res == NULL)
	{
		return 1;
	}


	while((row = mysql_fetch_row(res))!=NULL)
	{
		int cont=0;
		sprintf(formata_peso,"%.2f KG",atof(row[2]));
		gtk_tree_store_append(modelo,&campos,NULL);
		g_print("Inserindo codigo: %s nome: %s\n",row[0],row[1]);
		gtk_tree_store_set(modelo,&campos,
		COLUMN0,row[0],
		COLUMN1,row[1],
		COLUMN2,formata_peso,
		COLUMN3,row[3],-1);
	}

	gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(modelo));

	gtk_container_add(GTK_CONTAINER(scrollwindow),treeview);

	escolher_campo_button = gtk_button_new_with_label("Selecionar");
	escolher_campo_img = gtk_image_new_from_file(IMG_PROCR);
	escolher_campo_fixed = gtk_fixed_new();
	gtk_button_set_image(GTK_BUTTON(escolher_campo_button),escolher_campo_img);
	gtk_fixed_put(GTK_FIXED(escolher_campo_fixed),escolher_campo_button,20,10);

	gtk_widget_set_size_request(scrollwindow,600,250);
	gtk_box_pack_start(GTK_BOX(caixa_grande),psq_prod_pesquisa_entry,0,0,0);
	gtk_container_set_border_width(GTK_CONTAINER(psq_prod_wnd),10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),scrollwindow,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),escolher_campo_fixed,0,0,10);
	gtk_container_add(GTK_CONTAINER(psq_prod_wnd),caixa_grande);
	g_signal_connect(psq_prod_pesquisa_entry,"activate",G_CALLBACK(entry_prod_pesquisa),treeview);
	pesquisa_global_alvo = GTK_ENTRY(cod_prod_entry);

	g_signal_connect(treeview,"row-activated",G_CALLBACK(receber_psq_code_space),psq_prod_wnd);

	g_signal_connect(escolher_campo_button,"clicked",G_CALLBACK(receber_prod_code),treeview);
	gtk_widget_show_all(psq_prod_wnd);
	return 0;
}
