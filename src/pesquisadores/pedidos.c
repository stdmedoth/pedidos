void receber_ped_code(GtkWidget *button, GtkTreeView *treeview)
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
	gtk_widget_destroy(psq_ped_wnd);
}
void mover_para_escrita(GtkComboBox *combo, GtkWidget *entry)
{
	gtk_widget_grab_focus(entry);
	gtk_widget_activate(GTK_WIDGET(entry));
}

static GtkWidget *ped_status_combo;
int entry_ped_pesquisa(GtkEntry *widget, GtkTreeView *treeview)
{
	enum {N_COLUMNS=4,COLUMN0=0, COLUMN1=1, COLUMN2=2, COLUMN3=3, COLUMN4=4};
	int status=0;
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
	status = gtk_combo_box_get_active(GTK_COMBO_BOX(ped_status_combo));

	if(status!=0)
	{
		status--;
		sprintf(query,"select p.code, t.razao, p.data_mov, p.total from pedidos as p inner join terceiros as t on t.code = p.cliente where t.razao like '%c%s%c' and p.status = %i  order by p.data_mov desc limit 200",37,entrada,37,status);
	}
	else
	{
		sprintf(query,"select p.code, t.razao, p.data_mov, p.total from pedidos as p inner join terceiros as t on t.code = p.cliente where t.razao like '%c%s%c' order by p.data_mov desc limit 200",37,entrada,37);
	}

	res = consultar(query);
	if(res == NULL)
	{
		return 1;
	}
	while((row = mysql_fetch_row(res))!=NULL)
	{
		sprintf(formata_preco,"R$ %.2f",atof(row[3]));
		gtk_tree_store_append(modelo,&campos,NULL);
		g_print("Inserindo codigo: %s nome: %s\n",row[0],row[1]);

		gtk_tree_store_set(modelo,&campos,
		COLUMN0,row[0],
		COLUMN1,row[1],
		COLUMN2,row[2],
		COLUMN3,formata_preco,-1);
	}
	return 0;
}

int psq_ped(GtkWidget *button, GtkEntry *cod_ped_entry)
{
	enum {N_COLUMNS=4,COLUMN0=0, COLUMN1=1, COLUMN2=2, COLUMN3=3, COLUMN4=4};
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
	pesquisa_entry = gtk_search_entry_new();
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
	gtk_tree_view_set_enable_search(GTK_TREE_VIEW(treeview),TRUE);
	gtk_tree_view_set_search_entry(GTK_TREE_VIEW(treeview),GTK_ENTRY(pesquisa_entry));
	gtk_tree_view_set_search_entry(GTK_TREE_VIEW(treeview),NULL);
	scrollwindow = gtk_scrolled_window_new(NULL,NULL);

	psq_ped_wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(psq_ped_wnd),3);
	gtk_window_set_icon_name(GTK_WINDOW(psq_ped_wnd),"system-search");
	if(personalizacao.janela_keep_above==1)
		gtk_window_set_keep_above(GTK_WINDOW(psq_ped_wnd),TRUE);
	gtk_widget_set_size_request(psq_ped_wnd,500,250);

	ped_status_combo = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ped_status_combo),"Todos Status Pedido");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ped_status_combo),"Pendentes");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ped_status_combo),"Emitidos");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ped_status_combo),"Cancelados");
	gtk_combo_box_set_active(GTK_COMBO_BOX(ped_status_combo),1);

	gtk_tree_view_column_pack_start(coluna1,celula1,TRUE);
	gtk_tree_view_column_set_title(coluna1,"Código");
	gtk_tree_view_column_add_attribute(coluna1,celula1,"text",0);

	gtk_tree_view_column_pack_start(coluna2,celula2,TRUE);
	gtk_tree_view_column_set_title(coluna2,"Cliente");
	gtk_tree_view_column_add_attribute(coluna2,celula2,"text",1);

	gtk_tree_view_column_pack_start(coluna3,celula3,TRUE);
	gtk_tree_view_column_set_title(coluna3,"Data");
	gtk_tree_view_column_add_attribute(coluna3,celula3,"text",2);

	gtk_tree_view_column_pack_start(coluna4,celula4,TRUE);
	gtk_tree_view_column_set_title(coluna4,"Total");
	gtk_tree_view_column_add_attribute(coluna4,celula4,"text",3);

	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna1);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna2);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna3);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna4);

	gtk_tree_view_set_search_column(GTK_TREE_VIEW(treeview),1);
	modelo = gtk_tree_store_new(N_COLUMNS,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	sprintf(query,"select p.code, c.razao, p.data_mov, p.total from pedidos as p inner join terceiros as c on c.code = p.cliente and status = 0 order by p.data_mov desc limit 200");
	res = consultar(query);
	if(res == NULL)
	{
		return 1;
	}


	while((row = mysql_fetch_row(res))!=NULL)
	{
		sprintf(formata_preco,"R$ %.2f",atof(row[3]));
		gtk_tree_store_append(modelo,&campos,NULL);
		g_print("Inserindo codigo: %s nome: %s\n",row[0],row[1]);
		gtk_tree_store_set(modelo,&campos,
		COLUMN0,row[0],
		COLUMN1,row[1],
		COLUMN2,row[2],
		COLUMN3,formata_preco,-1);
	}

	gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(modelo));

	gtk_container_add(GTK_CONTAINER(scrollwindow),treeview);


	escolher_campo_button = gtk_button_new_with_label("Selecionar");
	escolher_campo_img = gtk_image_new_from_file(IMG_PROCR);
	escolher_campo_fixed = gtk_fixed_new();
	gtk_button_set_image(GTK_BUTTON(escolher_campo_button),escolher_campo_img);
	gtk_fixed_put(GTK_FIXED(escolher_campo_fixed),escolher_campo_button,20,10);

	gtk_widget_set_size_request(scrollwindow,600,250);

	gtk_container_set_border_width(GTK_CONTAINER(psq_ped_wnd),10);

	gtk_box_pack_start(GTK_BOX(caixa_grande),ped_status_combo,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),pesquisa_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),scrollwindow,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),escolher_campo_fixed,0,0,10);

	gtk_container_add(GTK_CONTAINER(psq_ped_wnd),caixa_grande);

	g_signal_connect(pesquisa_entry,"activate",G_CALLBACK(entry_ped_pesquisa),treeview);
	g_signal_connect(treeview,"row-activated",G_CALLBACK(receber_psq_code_space),psq_ped_wnd);
	g_signal_connect(ped_status_combo,"changed",G_CALLBACK(mover_para_escrita),pesquisa_entry);
	pesquisa_global_alvo = GTK_ENTRY(cod_ped_entry);
	g_signal_connect(escolher_campo_button,"clicked",G_CALLBACK(receber_ped_code),treeview);
	gtk_widget_grab_focus(pesquisa_entry);
	gtk_widget_show_all(psq_ped_wnd);
	return 0;
}
