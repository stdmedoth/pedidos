void receber_campos_relat_code(GtkWidget *button, GtkTreeView *treeview)
{
	enum{N_COLUNAS=3, COLUNA0=0, COLUNA1=1, COLUNA2=2};
	GtkTreeStore *modelo_campos;
	GtkTreeIter iter_campos;
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;
	char *code = malloc(MAX_CODE_LEN);
	char *nome = malloc(MAX_CAMPO_NOME);
	char *obs = malloc(MAX_OBS_LEN);
	
	gtk_widget_set_sensitive(cad_rel_tabel_combo,FALSE);
	if(relat_campo_atual>=MAX_RELAT_CAMPOS)
	{
		popup(NULL,"Limite de campos excedido");
		return ;
	}
    
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview));
	
	if(!gtk_tree_selection_get_selected(selection, &model, &iter))
		return ;
	
	gtk_tree_model_get (model, &iter, 0, &code, -1);
	gtk_tree_model_get (model, &iter, 1, &nome, -1);
	gtk_tree_model_get (model, &iter, 2, &obs, -1);

	g_print("campo 0: %s\ncampo 1: %s\ncampo 2: %s\n",code,nome,obs);

	int cont=0,repetido;

	while(cont<=MAX_RELAT_CAMPOS)
	{	
		if(relat_struct.status[cont] == TRUE)
		{
			if(relat_struct.campos_code[cont] == atoi(code))
			{
				popup(NULL,"O campo já foi incluido");
				return ;
			}
		}
		cont++;
	}

	relat_struct.campos_code[relat_campo_atual] = atoi(code);
	
	relat_struct.status[relat_campo_atual] = TRUE;
	
	modelo_campos = (GtkTreeStore*) gtk_tree_view_get_model(GTK_TREE_VIEW(cad_relat_treeview));
	//gtk_tree_store_clear(modelo_campos);
	
	gtk_tree_store_append(modelo_campos,&iter_campos,NULL);
	gtk_tree_store_set(modelo_campos,&iter_campos, 
	COLUNA0,relat_struct.campos_code[relat_campo_atual], 
	COLUNA1,nome, 
	COLUNA2,obs,
	-1);
	
	relat_struct.qnt_campos++;
	relat_campo_atual++;

	if(relat_struct.qnt_campos>0)
	{
		gtk_widget_set_sensitive(campos_rel_remover_button,TRUE);
	}

	gtk_widget_destroy(psq_campos_relat_wnd);
	
}

int entry_campos_relat_pesquisa(GtkEntry *widget, GtkTreeView *treeview)
{
	enum {N_COLUMNS=3,COLUMN0=0, COLUMN1=1, COLUMN2=2};
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
	
	if(cad_rel_tabel_fun()!=0)
		return 1;
		
	sprintf(query,"select code, nome, sobre, query from relat_tab_campos where nome like '%c%s%c' and tabela = %i" ,37,entrada,37, cad_rel_tabel_int);
	res = consultar(query);
	if(res == NULL)
	{
		return 1;
	}
	while((row = mysql_fetch_row(res))!=NULL)
	{
		
		gtk_tree_store_append(modelo,&campos,NULL);
		g_print("Inserindo codigo: %s nome: %s\n",row[0],row[1]);
	
		gtk_tree_store_set(modelo,&campos, 		
		COLUMN0,row[0], 
		COLUMN1,row[1],
		COLUMN2,row[2],
		-1);
	}
	return 0;
}

int psq_relat_campos(GtkWidget *button, gpointer gobject)
{
	enum {N_COLUMNS=3,COLUMN0=0, COLUMN1=1, COLUMN2=2};
	GtkWidget *scrollwindow;
	GtkTreeViewColumn *coluna1, *coluna2, *coluna3;
	GtkCellRenderer *celula1, *celula2, *celula3;
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
	
	treeview = gtk_tree_view_new();
	if(cad_rel_tabel_fun()!=0)
		return 1;
	
	gtk_tree_view_set_enable_tree_lines(GTK_TREE_VIEW(treeview),TRUE);
	gtk_tree_view_set_enable_search(GTK_TREE_VIEW(treeview),TRUE);
	gtk_tree_view_set_search_entry(GTK_TREE_VIEW(treeview),GTK_ENTRY(pesquisa_entry));
	scrollwindow = gtk_scrolled_window_new(NULL,NULL);
	
	psq_campos_relat_wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(psq_campos_relat_wnd),3);
	gtk_window_set_icon_name(GTK_WINDOW(psq_campos_relat_wnd),"system-search");
	if(personalizacao.janela_keep_above==1)	
		gtk_window_set_keep_above(GTK_WINDOW(psq_campos_relat_wnd),TRUE);
	gtk_widget_set_size_request(psq_campos_relat_wnd,500,250);
	
	gtk_tree_view_column_pack_start(coluna1,celula1,TRUE);
	gtk_tree_view_column_set_title(coluna1,"Cód. Campo");
	gtk_tree_view_column_add_attribute(coluna1,celula1,"text",0);
	
	gtk_tree_view_column_pack_start(coluna2,celula2,TRUE);
	gtk_tree_view_column_set_title(coluna2,"Nome Campo");
	gtk_tree_view_column_add_attribute(coluna2,celula2,"text",1);
	
	gtk_tree_view_column_pack_start(coluna3,celula3,TRUE);
	gtk_tree_view_column_set_title(coluna3,"Utilidade");
	gtk_tree_view_column_add_attribute(coluna3,celula3,"text",2);
	
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna1);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna2);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna3);
	
	gtk_tree_view_set_search_column(GTK_TREE_VIEW(treeview),2);
	modelo = gtk_tree_store_new(N_COLUMNS,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	
	sprintf(query,"select code, nome, sobre, query from relat_tab_campos where tabela = %i",cad_rel_tabel_int);
	res = consultar(query);
	if(res == NULL)
	{
		return 1;
	}

	while((row = mysql_fetch_row(res))!=NULL)
	{
		gtk_tree_store_append(modelo,&campos,NULL);
		g_print("Inserindo codigo: %s nome: %s\n",row[0],row[1]);
		gtk_tree_store_set(modelo,&campos, 
		COLUMN0,row[0], 
		COLUMN1,row[1],
		COLUMN2,row[2],
		-1);
	}
	
	gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(modelo));
	
	gtk_container_add(GTK_CONTAINER(scrollwindow),treeview);

	escolher_campo_button = gtk_button_new_with_label("Escolher");
	escolher_campo_img = gtk_image_new_from_file(IMG_PROCR);
	escolher_campo_fixed = gtk_fixed_new();
	gtk_button_set_image(GTK_BUTTON(escolher_campo_button),escolher_campo_img);
	gtk_fixed_put(GTK_FIXED(escolher_campo_fixed),escolher_campo_button,20,10);
	
	gtk_widget_set_size_request(scrollwindow,600,250);
	
	//gtk_box_pack_start(GTK_BOX(caixa_grande),pesquisa_entry,0,0,0);
	
	gtk_container_set_border_width(GTK_CONTAINER(psq_campos_relat_wnd),10);
	
	gtk_box_pack_start(GTK_BOX(caixa_grande),scrollwindow,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),escolher_campo_fixed,0,0,10);
	gtk_container_add(GTK_CONTAINER(psq_campos_relat_wnd),caixa_grande);
	
	g_signal_connect(pesquisa_entry,"activate",G_CALLBACK(entry_campos_relat_pesquisa),treeview);
	g_signal_connect(escolher_campo_button,"clicked",G_CALLBACK(receber_campos_relat_code),treeview);
	
	gtk_widget_show_all(psq_campos_relat_wnd);
	return 0;
}

