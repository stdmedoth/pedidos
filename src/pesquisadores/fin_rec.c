void receber_fin_rec_code(GtkWidget *button, GtkTreeView *treeview)
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
	gtk_widget_destroy(psq_fin_rec_wnd);
}

int entry_fin_rec_pesquisa(GtkEntry *widget, GtkTreeView *treeview)
{
	enum {N_COLUMNS=7,COLUMN0=0, COLUMN1=1, COLUMN2=2, COLUMN3=3, COLUMN4=4, COLUMN5=5, COLUMN6=6};
	GtkTreeStore *treestore	=	GTK_TREE_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
  g_object_ref(G_OBJECT(treestore));
  gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),NULL);
  gtk_tree_store_clear(treestore);
  gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(treestore));

	char status[100];
	MYSQL_RES *res;
	MYSQL_ROW row;

	gchar *formata_peso = malloc(MAX_PRECO_LEN);
	char query[MAX_QUERY_LEN];
	gchar *entrada = malloc(MAX_GRP_LEN);
	entrada = (gchar*)gtk_entry_get_text(widget);
	GtkTreeIter colunas, campos;
	GtkTreeStore *modelo = (GtkTreeStore*) gtk_tree_view_get_model(treeview);

	sprintf(query,"select tl.code,t.razao, tl.pedido, tl.status, p.posicao, DATE_FORMAT(p.data_vencimento,'%%d/%%m/%%Y'), p.valor from titulos as tl inner join terceiros as t inner join parcelas_tab as p on tl.code = p.parcelas_id and tl.cliente = t.code and t.razao like '%c%s%c' where tipo_titulo = 1 order by p.data_vencimento desc limit 30",37,entrada,37);
	if(!(res = consultar(query)))
		return 1;

	while((row = mysql_fetch_row(res))){
		switch(atoi(row[3])){
			case STAT_QUITADO:
				strcpy(status,"Tít. Baixado");
				break;
			case STAT_PARC_BAIXA:
				strcpy(status,"Tit. Parc. Baixado");
				break;
			case STAT_PENDENTE:
					strcpy(status,"Tít. Pendente");
					break;
		}

		gtk_tree_store_append(modelo,&campos,NULL);
		gtk_tree_store_set(modelo,&campos,
		COLUMN0,row[0],
		COLUMN1,row[1],
		COLUMN2,row[2],
		COLUMN3,status,
		COLUMN4,row[4],
		COLUMN5,row[5],
		COLUMN6,row[6],
		-1);
	}

	return 0;
}

int psq_fin_rec(GtkWidget *button, GtkEntry *entry)
{
	enum {N_COLUMNS=7,COLUMN0=0, COLUMN1=1, COLUMN2=2, COLUMN3=3, COLUMN4=4, COLUMN5=5, COLUMN6=6};
	GtkWidget *scrollwindow;
	GtkTreeViewColumn *coluna0,*coluna1, *coluna2, *coluna3, *coluna4, *coluna5, *coluna6;
	GtkCellRenderer *celula0,*celula1, *celula2, *celula3, *celula4, *celula5, *celula6;
	GtkWidget *treeview;
	GtkTreeStore *modelo;
	GtkTreeIter colunas, campos;
	GtkWidget *caixa_grande;

	gchar *entrada = malloc(MAX_GRP_LEN);
	GtkWidget *escolher_campo_button, *escolher_campo_img, *escolher_campo_fixed;

	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	char status[100];

	caixa_grande = gtk_box_new(1,0);
	fin_rec_psq_entry = gtk_entry_new();
	coluna0 = gtk_tree_view_column_new();
	celula0 = gtk_cell_renderer_text_new();
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
	coluna6 = gtk_tree_view_column_new();
	celula6 = gtk_cell_renderer_text_new();

	treeview = gtk_tree_view_new();

	gtk_tree_view_set_enable_tree_lines(GTK_TREE_VIEW(treeview),TRUE);
	gtk_tree_view_set_level_indentation(GTK_TREE_VIEW(treeview),30);
	gtk_tree_view_set_enable_search(GTK_TREE_VIEW(treeview),TRUE);
	gtk_tree_view_set_search_entry(GTK_TREE_VIEW(treeview),GTK_ENTRY(fin_rec_psq_entry));
	gtk_tree_view_set_search_entry(GTK_TREE_VIEW(treeview),NULL);
	scrollwindow = gtk_scrolled_window_new(NULL,NULL);

	psq_fin_rec_wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(psq_fin_rec_wnd),3);
	gtk_window_set_icon_name(GTK_WINDOW(psq_fin_rec_wnd),"system-search");
	gtk_window_set_keep_above(GTK_WINDOW(psq_fin_rec_wnd),TRUE);
	gtk_widget_set_size_request(psq_fin_rec_wnd,500,250);

	gtk_tree_view_column_pack_start(coluna0,celula0,TRUE);
	gtk_tree_view_column_set_title(coluna0,"Código");
	gtk_tree_view_column_set_spacing(coluna0,5);
	//gtk_tree_view_column_set_visible(coluna0,FALSE);
	gtk_tree_view_column_add_attribute(coluna0,celula0,"text",0);

	gtk_tree_view_column_pack_start(coluna1,celula1,TRUE);
	gtk_tree_view_column_set_title(coluna1,"Cliente");
	gtk_tree_view_column_set_spacing(coluna1,5);
	gtk_tree_view_column_add_attribute(coluna1,celula1,"text",1);

	gtk_tree_view_column_pack_start(coluna2,celula2,TRUE);
	gtk_tree_view_column_set_title(coluna2,"Pedido");
	gtk_tree_view_column_set_spacing(coluna2,5);
	gtk_tree_view_column_add_attribute(coluna2,celula2,"text",2);

	gtk_tree_view_column_pack_start(coluna3,celula3,TRUE);
	gtk_tree_view_column_set_title(coluna3,"Status");
	gtk_tree_view_column_set_spacing(coluna3,5);
	gtk_tree_view_column_add_attribute(coluna3,celula3,"text",3);

	gtk_tree_view_column_pack_start(coluna4,celula4,TRUE);
	gtk_tree_view_column_set_title(coluna4,"Parcela");
	gtk_tree_view_column_set_spacing(coluna4,5);
	gtk_tree_view_column_add_attribute(coluna4,celula4,"text",4);

	gtk_tree_view_column_pack_start(coluna5,celula5,TRUE);
	gtk_tree_view_column_set_title(coluna5,"Vencimento");
	gtk_tree_view_column_set_spacing(coluna5,5);
	gtk_tree_view_column_add_attribute(coluna5,celula5,"text",5);

	gtk_tree_view_column_pack_start(coluna6,celula6,TRUE);
	gtk_tree_view_column_set_title(coluna6,"Valor");
	gtk_tree_view_column_set_spacing(coluna6,6);
	gtk_tree_view_column_add_attribute(coluna6,celula6,"text",6);

	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna0);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna1);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna2);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna3);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna4);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna5);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna6);

	gtk_tree_view_set_enable_search(GTK_TREE_VIEW(treeview),TRUE);
	gtk_tree_view_set_search_column(GTK_TREE_VIEW(treeview),1);
	modelo = gtk_tree_store_new(N_COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	sprintf(query,"select tl.code,t.razao, tl.pedido, tl.status, p.posicao, DATE_FORMAT(p.data_vencimento,'%%d/%%m/%%Y'), p.valor from titulos as tl inner join terceiros as t inner join parcelas_tab as p on tl.code = p.parcelas_id and tl.cliente = t.code where tipo_titulo = 1 order by p.data_vencimento desc limit 30");
	res = consultar(query);
	if(res == NULL)
	{
		return 1;
	}

	while((row = mysql_fetch_row(res))!=NULL)
	{

		switch(atoi(row[3])){
			case STAT_QUITADO:
				strcpy(status,"Tít. Baixado");
				break;
			case STAT_PARC_BAIXA:
				strcpy(status,"Tit. Parc. Baixado");
				break;
			case STAT_PENDENTE:
					strcpy(status,"Tít. Pendente");
					break;
		}

		gtk_tree_store_append(modelo,&campos,NULL);
		gtk_tree_store_set(modelo,&campos,
		COLUMN0,row[0],
		COLUMN1,row[1],
		COLUMN2,row[2],
		COLUMN3,status,
		COLUMN4,row[4],
		COLUMN5,row[5],
		COLUMN6,row[6],
		-1);
	}

	gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(modelo));

	gtk_container_add(GTK_CONTAINER(scrollwindow),treeview);

	escolher_campo_button = gtk_button_new_with_label("Selecionar");
	escolher_campo_img = gtk_image_new_from_file(IMG_PROCR);
	escolher_campo_fixed = gtk_fixed_new();
	gtk_button_set_image(GTK_BUTTON(escolher_campo_button),escolher_campo_img);
	gtk_fixed_put(GTK_FIXED(escolher_campo_fixed),escolher_campo_button,20,10);

	gtk_widget_set_size_request(scrollwindow,600,250);
	gtk_box_pack_start(GTK_BOX(caixa_grande),fin_rec_psq_entry,0,0,0);
	gtk_container_set_border_width(GTK_CONTAINER(psq_fin_rec_wnd),10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),scrollwindow,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),escolher_campo_fixed,0,0,10);
	gtk_container_add(GTK_CONTAINER(psq_fin_rec_wnd),caixa_grande);

	pesquisa_global_alvo = GTK_ENTRY(entry);

	g_signal_connect(treeview,"row-activated",G_CALLBACK(receber_psq_code_space),psq_fin_rec_wnd);
	g_signal_connect(fin_rec_psq_entry,"activate",G_CALLBACK(entry_fin_rec_pesquisa),treeview);
	g_signal_connect(escolher_campo_button,"clicked",G_CALLBACK(receber_fin_rec_code),treeview);

	gtk_widget_show_all(psq_fin_rec_wnd);
	return 0;
}
