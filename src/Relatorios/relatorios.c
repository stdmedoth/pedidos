void cad_relat()
{
	GtkWidget *janela, *caixa_grande,
	*caixa_campos_box, *caixa_campos_scroll, *caixa_campos_frame, *caixa_campos_fixed,
	*caixa_opcoes_box, *caixa_opcoes_fixed;

	GtkWidget *grid;
	GtkWidget *cad_rel_code_frame, *cad_rel_code_fixed, *cad_rel_code_box,
	*cad_rel_nome_frame, *cad_rel_nome_fixed,
	*cad_rel_tabel_frame, *cad_rel_tabel_fixed;

	GtkWidget *cad_rel_confirmar_button,
	*cad_rel_cancelar_button,
	*cad_rel_excluir_button;

	GtkWidget *juncao_campos_opt;
	GtkWidget *campos_rel_remover_fixed;

	GtkWidget *cad_rel_psqrow_fixed;

	MYSQL_ROW row;
	MYSQL_RES *res;
	char query[MAX_QUERY_LEN],code[MAX_CODE_LEN];

	enum {N_COLUNAS=3, COLUNA0=0, COLUNA1=1, COLUNA2=2};
	GtkTreeViewColumn *coluna0, *coluna1, *coluna2;
	GtkCellRenderer *celula0, *celula1, *celula2;
	GtkTreeIter iter1, iter2;
	GtkTreeStore *modelo;

	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(janela),"Relatorios");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_container_set_border_width(GTK_CONTAINER(janela),5);
	gtk_window_set_icon_name(GTK_WINDOW(janela),"x-office-document-template");
	gtk_widget_set_size_request(GTK_WIDGET(janela),940,400);
	if(personalizacao.janela_keep_above==1)
		gtk_window_set_keep_above(GTK_WINDOW(janela),TRUE);

	janelas_gerenciadas.vetor_janelas[REG_CAD_RELAT].reg_id = REG_CAD_RELAT;
	janelas_gerenciadas.vetor_janelas[REG_CAD_RELAT].aberta = 1;
	if(ger_janela_aberta(janela_grupo, &janelas_gerenciadas.vetor_janelas[REG_CAD_RELAT]))
		return ;
	janelas_gerenciadas.vetor_janelas[REG_CAD_RELAT].janela_pointer = janela;


	coluna0 = gtk_tree_view_column_new();
	celula0 = gtk_cell_renderer_accel_new();

	coluna1 = gtk_tree_view_column_new();
	celula1 = gtk_cell_renderer_accel_new();

	coluna2 = gtk_tree_view_column_new();
	celula2 = gtk_cell_renderer_accel_new();

	gtk_tree_view_column_pack_start(coluna0,celula0,TRUE);
	gtk_tree_view_column_set_title(coluna0,"Id");
	gtk_tree_view_column_add_attribute(coluna0,celula0,"text",0);

	gtk_tree_view_column_pack_start(coluna1,celula1,TRUE);
	gtk_tree_view_column_set_title(coluna1,"Nome Campo");
	gtk_tree_view_column_add_attribute(coluna1,celula1,"text",1);

	gtk_tree_view_column_pack_start(coluna2,celula2,TRUE);
	gtk_tree_view_column_set_title(coluna2,"Funcao");
	gtk_tree_view_column_add_attribute(coluna2,celula2,"text",2);

	modelo = gtk_tree_store_new(N_COLUNAS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);
	gtk_tree_store_append(modelo,&iter1,NULL);
	gtk_tree_store_set(modelo,&iter1,COLUMN0,0,COLUMN1,"",COLUMN2,"",-1);
	cad_relat_treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(modelo));

	gtk_tree_view_append_column(GTK_TREE_VIEW(cad_relat_treeview),coluna0);
	gtk_tree_view_append_column(GTK_TREE_VIEW(cad_relat_treeview),coluna1);
	gtk_tree_view_append_column(GTK_TREE_VIEW(cad_relat_treeview),coluna2);

	juncao_campos_opt = gtk_box_new(1,0);
	campos_rel_remover_button = gtk_button_new_with_label("Remover campo");
	gtk_button_set_image(GTK_BUTTON(campos_rel_remover_button),gtk_image_new_from_file(IMG_EXCLUI));
	campos_rel_remover_fixed = gtk_fixed_new();
	gtk_fixed_put(GTK_FIXED(campos_rel_remover_fixed),campos_rel_remover_button,380,0);

	psq_cad_rel_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(psq_cad_rel_button),gtk_image_new_from_file(IMG_PESQ));

	cad_rel_code_box = gtk_box_new(0,0);
	caixa_opcoes_box = gtk_box_new(0,0);
	caixa_opcoes_fixed = gtk_fixed_new();

	cad_rel_confirmar_button = gtk_button_new_with_label("Cocluir");
	gtk_button_set_image(GTK_BUTTON(cad_rel_confirmar_button),gtk_image_new_from_file(IMG_OK));
	cad_rel_alterar_button = gtk_button_new_with_label("Alterar");
	 gtk_button_set_image(GTK_BUTTON(cad_rel_alterar_button),gtk_image_new_from_file(IMG_ALTER));
	cad_rel_cancelar_button = gtk_button_new_with_label("Cancelar");
	gtk_button_set_image(GTK_BUTTON(cad_rel_cancelar_button),gtk_image_new_from_file(IMG_CANCEL));
	cad_rel_excluir_button = gtk_button_new_with_label("Excluir");
	gtk_button_set_image(GTK_BUTTON(cad_rel_excluir_button),gtk_image_new_from_file(IMG_EXCLUI));

	gtk_box_pack_start(GTK_BOX(caixa_opcoes_box),cad_rel_confirmar_button,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes_box),cad_rel_alterar_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes_box),cad_rel_cancelar_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes_box),cad_rel_excluir_button,0,0,5);
	gtk_fixed_put(GTK_FIXED(caixa_opcoes_fixed),caixa_opcoes_box,20,50);

	cad_rel_psqrow_button = gtk_button_new_with_label("Pesquisar campos");
	cad_rel_psqrow_fixed =  gtk_fixed_new();
	gtk_fixed_put(GTK_FIXED(cad_rel_psqrow_fixed),cad_rel_psqrow_button,20,20);

	caixa_grande = gtk_box_new(0,0);

	caixa_campos_box = gtk_box_new(1,0);
	caixa_campos_scroll = gtk_scrolled_window_new(NULL,NULL);
	caixa_campos_frame = gtk_frame_new("Campos");
	gtk_frame_set_shadow_type(GTK_FRAME(caixa_campos_frame),GTK_SHADOW_ETCHED_OUT);
	caixa_campos_fixed = gtk_fixed_new();
	gtk_widget_set_size_request(caixa_campos_box,500,330);
	gtk_widget_set_size_request(caixa_campos_scroll,500,300);

	gtk_box_pack_start(GTK_BOX(caixa_campos_box),cad_relat_treeview,0,0,10);

	gtk_container_add(GTK_CONTAINER(caixa_campos_scroll),caixa_campos_box);
	gtk_container_add(GTK_CONTAINER(caixa_campos_frame),caixa_campos_scroll);
	gtk_fixed_put(GTK_FIXED(caixa_campos_fixed),caixa_campos_frame,30,20);

	grid = gtk_grid_new();

	cad_rel_code_frame = gtk_frame_new("Código");
	cad_rel_code_fixed = gtk_fixed_new();
	cad_rel_code_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(cad_rel_code_entry),10);
	gtk_box_pack_start(GTK_BOX(cad_rel_code_box),cad_rel_code_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(cad_rel_code_box),psq_cad_rel_button,0,0,5);
	gtk_container_add(GTK_CONTAINER(cad_rel_code_frame),cad_rel_code_box);
	gtk_fixed_put(GTK_FIXED(cad_rel_code_fixed),cad_rel_code_frame,20,20);

	cad_rel_nome_frame = gtk_frame_new("Nome");
	cad_rel_nome_fixed = gtk_fixed_new();
	cad_rel_nome_entry = gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(cad_rel_nome_frame),cad_rel_nome_entry);
	gtk_fixed_put(GTK_FIXED(cad_rel_nome_fixed),cad_rel_nome_frame,20,20);

	cad_rel_tabel_frame = gtk_frame_new("Tabelas");
	cad_rel_tabel_fixed = gtk_fixed_new();
	cad_rel_tabel_combo = gtk_combo_box_text_new();

	sprintf(query,"select * from relat_tabelas_id");
	if((res = consultar(query))==NULL)
	{
		popup(NULL,"Erro buscando as tabelas disponiveis para o relatorio");
		return ;
	}
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(cad_rel_tabel_combo),"Selecione a Tabela do Relatório");
	gtk_combo_box_set_active(GTK_COMBO_BOX(cad_rel_tabel_combo),0);
	while((row = mysql_fetch_row(res))!=NULL)
	{
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(cad_rel_tabel_combo),row[1]);
	}

	gtk_container_add(GTK_CONTAINER(cad_rel_tabel_frame),cad_rel_tabel_combo);
	gtk_fixed_put(GTK_FIXED(cad_rel_tabel_fixed),cad_rel_tabel_frame,20,20);

	gtk_grid_attach(GTK_GRID(grid),cad_rel_code_fixed,0,0,1,1);
	gtk_grid_attach(GTK_GRID(grid),cad_rel_nome_fixed,0,1,1,1);
	gtk_grid_attach(GTK_GRID(grid),cad_rel_tabel_fixed,0,2,1,1);
	gtk_grid_attach(GTK_GRID(grid),cad_rel_psqrow_fixed,0,3,1,1);
	gtk_grid_attach(GTK_GRID(grid),caixa_opcoes_fixed,0,4,1,1);
	gtk_box_pack_start(GTK_BOX(caixa_grande),grid,0,0,0);
	gtk_widget_show_all(caixa_grande);

	gtk_box_pack_start(GTK_BOX(juncao_campos_opt),caixa_campos_fixed,0,0,5);
	gtk_box_pack_start(GTK_BOX(juncao_campos_opt),campos_rel_remover_fixed,0,0,5);

	gtk_box_pack_start(GTK_BOX(caixa_grande),juncao_campos_opt,0,0,0);

	g_signal_connect(psq_cad_rel_button,"clicked",G_CALLBACK(psq_cad_relat),cad_rel_code_entry);

	g_signal_connect(cad_rel_code_entry,"activate",G_CALLBACK(cad_relat_code),NULL);
	g_signal_connect(cad_rel_nome_entry,"activate",G_CALLBACK(cad_relat_nome),NULL);

	g_signal_connect(cad_rel_confirmar_button,"clicked",G_CALLBACK(cad_relat_concluir),NULL);
	g_signal_connect(cad_rel_alterar_button,"clicked",G_CALLBACK(cad_relat_alterar),NULL);
	g_signal_connect(cad_rel_cancelar_button,"clicked",G_CALLBACK(cad_relat_cancelar),NULL);
	g_signal_connect(cad_rel_excluir_button,"clicked",G_CALLBACK(cad_relat_excluir),NULL);

	g_signal_connect(campos_rel_remover_button,"clicked",G_CALLBACK(cad_rel_rem_row_fun),cad_relat_treeview);

	g_signal_connect(cad_rel_psqrow_button,"clicked",G_CALLBACK(psq_relat_campos),NULL);

	g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_CAD_RELAT]);

	cont=0;
	while(cont<MAX_RELAT_CAMPOS)
	{
		relat_struct.status[cont] = 0;
		relat_struct.campos_code_bkp[cont] =  0;
		cont++;
	}

	relat_struct.qnt_campos = 0;
	relat_campo_atual=1;

	sprintf(code,"%i",tasker("criador_relat"));
	gtk_entry_set_text(GTK_ENTRY(cad_rel_code_entry),code);
	gtk_container_add(GTK_CONTAINER(janela),caixa_grande);

	gtk_widget_grab_focus(cad_rel_nome_entry);
	gtk_widget_show_all(janela);


	return ;
}
