void receber_cep_code(GtkWidget *button, GtkTreeView *treeview)
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
	gtk_widget_destroy(psq_cep_wnd);
}

int entry_cep_pesquisa(GtkEntry *widget, GtkTreeView *treeview)
{
	enum {
		CEP_COL,
		LOGR_COL,
		BAIRRO_COL,
		CIDADE_COL,
		UF_COL,
		N_COLUMNS
	};

	enum {
		CEP,
		CIDADE,
		LOGRADOURO
	};
	GtkTreeStore *treestore	=	GTK_TREE_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
    g_object_ref(G_OBJECT(treestore));
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),NULL);
    gtk_tree_store_clear(treestore);
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(treestore));
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	int tipo_psq=0;
	gchar *entrada = malloc(MAX_GRP_LEN);
	entrada = (gchar*)gtk_entry_get_text(widget);
	GtkTreeIter colunas, campos;
	GtkTreeStore *modelo = (GtkTreeStore*) gtk_tree_view_get_model(treeview);
	tipo_psq = gtk_combo_box_get_active(GTK_COMBO_BOX(psq_cep_combo_box));
	switch(tipo_psq)
	{
		case CEP:
			sprintf(query,"select l.CEP, l.descricao, l.descricao_bairro ,c.descricao, l.UF from logradouro as l inner join cidade as c  on l.id_cidade = c.code where l.CEP like '%c%s%c' limit 50",37,entrada,37);
			break;

		case CIDADE:
			sprintf(query,"select l.CEP, l.descricao, l.descricao_bairro, c.descricao, l.UF from logradouro as l inner join cidade as c  on l.id_cidade = c.code where c.descricao like '%c%s%c' limit 50",37,entrada,37);
			break;

		case LOGRADOURO:
			sprintf(query,"select l.CEP, l.descricao, l.descricao_bairro, c.descricao, l.UF from logradouro as l inner join cidade as c  on l.id_cidade = c.code where l.descricao like '%c%s%c' limit 50",37,entrada,37);
			break;
	}
	res = consultar(query);
	if(!res){
		return 1;
	}
	int cont=0;
	while((row = mysql_fetch_row(res))!=NULL)
	{
		gtk_tree_store_append(modelo,&campos,NULL);
		g_print("Inserindo codigo: %s nome: %s\n",row[0],row[1]);

		gtk_tree_store_set(modelo,&campos,
		CEP_COL,row[CEP_COL],
		LOGR_COL,row[LOGR_COL],
		BAIRRO_COL,row[BAIRRO_COL],
		CIDADE_COL,row[CIDADE_COL],
		UF_COL,row[UF_COL],
		-1);
	}
	return 0;
}

int psq_cep(GtkWidget *button, GtkEntry *cod_cep_entry)
{
	GtkWidget *scrollwindow;
	GtkTreeViewColumn *coluna1, *coluna2, *coluna3, *coluna4, *coluna5;
	GtkCellRenderer *celula1, *celula2, *celula3, *celula4, *celula5;
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

	enum{
		CEP,
		LOGRADOURO,
		BAIRRO,
		CIDADE,
		UF,
		N_COLUMNS
	};

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

	psq_cep_combo_box = gtk_combo_box_text_new();
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(psq_cep_combo_box),"0","CEP");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(psq_cep_combo_box),"1","Nome Cidade");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(psq_cep_combo_box),"2","Nome Logradouro");
	gtk_combo_box_set_active(GTK_COMBO_BOX(psq_cep_combo_box),0);

	treeview = gtk_tree_view_new();

	gtk_tree_view_set_enable_tree_lines(GTK_TREE_VIEW(treeview),TRUE);
	gtk_tree_view_set_level_indentation(GTK_TREE_VIEW(treeview),30);

	gtk_tree_view_set_enable_search(GTK_TREE_VIEW(treeview),TRUE);
	gtk_tree_view_set_search_entry(GTK_TREE_VIEW(treeview),GTK_ENTRY(pesquisa_entry));
	gtk_tree_view_set_search_entry(GTK_TREE_VIEW(treeview),NULL);
	scrollwindow = gtk_scrolled_window_new(NULL,NULL);

	psq_cep_wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(psq_cep_wnd),3);
	gtk_window_set_icon_name(GTK_WINDOW(psq_cep_wnd),"system-search");
	if(personalizacao.janela_keep_above==1)
		gtk_window_set_keep_above(GTK_WINDOW(psq_cep_wnd),TRUE);
	gtk_widget_set_size_request(psq_cep_wnd,500,250);

	gtk_tree_view_column_pack_start(coluna1,celula1,TRUE);
	gtk_tree_view_column_set_title(coluna1,"CEP");
	gtk_tree_view_column_add_attribute(coluna1,celula1,"text",CEP);
	//gtk_tree_view_column_set_visible(coluna1,FALSE);

	gtk_tree_view_column_pack_start(coluna2,celula2,TRUE);
	gtk_tree_view_column_set_title(coluna2,"Logradouro");
	gtk_tree_view_column_add_attribute(coluna2,celula2,"text",LOGRADOURO);

	gtk_tree_view_column_pack_start(coluna3,celula3,TRUE);
	gtk_tree_view_column_set_title(coluna3,"Bairro");
	gtk_tree_view_column_add_attribute(coluna3,celula3,"text",BAIRRO);

	gtk_tree_view_column_pack_start(coluna4,celula4,TRUE);
	gtk_tree_view_column_set_title(coluna4,"Cidade");
	gtk_tree_view_column_add_attribute(coluna4,celula4,"text",CIDADE);

	gtk_tree_view_column_pack_start(coluna5,celula5,TRUE);
	gtk_tree_view_column_set_title(coluna5,"UF");
	gtk_tree_view_column_add_attribute(coluna5,celula5,"text",UF);

	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna1);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna2);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna3);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna4);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna5);

	gtk_tree_view_set_search_column(GTK_TREE_VIEW(treeview),1);

	modelo = gtk_tree_store_new(
		N_COLUMNS,
		G_TYPE_STRING,
		G_TYPE_STRING,
		G_TYPE_STRING,
		G_TYPE_STRING,
		G_TYPE_STRING
	);

	sprintf(query,"select l.CEP, l.descricao, l.descricao_bairro, c.descricao, l.UF from logradouro as l inner join cidade as c on l.id_cidade = c.code limit 20");
	res = consultar(query);
	if(res == NULL)
	{
		return 1;
	}

	int cont=0;
	while((row = mysql_fetch_row(res))!=NULL)
	{
		gtk_tree_store_append(modelo,&campos,NULL);
		g_print("Inserindo codigo: %s nome: %s\n",row[0],row[1]);
		gtk_tree_store_set(modelo,&campos,
		CEP,row[CEP],
		LOGRADOURO,row[LOGRADOURO],
		BAIRRO,row[BAIRRO],
		CIDADE,row[CIDADE],
		UF,row[UF],
		-1);
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

	gtk_box_pack_start(GTK_BOX(caixa_grande),psq_cep_combo_box,0,0,5);
	gtk_box_pack_start(GTK_BOX(caixa_grande),pesquisa_entry,0,0,5);

	gtk_container_set_border_width(GTK_CONTAINER(psq_cep_wnd),10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),scrollwindow,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),escolher_campo_fixed,0,0,10);
	gtk_container_add(GTK_CONTAINER(psq_cep_wnd),caixa_grande);
	g_signal_connect(treeview,"row-activated",G_CALLBACK(receber_psq_code_space),psq_cep_wnd);
	g_signal_connect(pesquisa_entry,"activate",G_CALLBACK(entry_cep_pesquisa),treeview);
	pesquisa_global_alvo = GTK_ENTRY(cod_cep_entry);
	g_signal_connect(escolher_campo_button,"clicked",G_CALLBACK(receber_cep_code),treeview);
	gtk_widget_grab_focus(pesquisa_entry);
	gtk_widget_show_all(psq_cep_wnd);
	return 0;
}
