int produtos_ped_list(GtkEntry *widget, GtkTreeView *treeview)
{
	enum {N_COLUMNS=5,
		COLUMN0=0,
		COLUMN1=1,
		COLUMN2=2,
		COLUMN3=3,
		COLUMN4=4};
	gchar *entrada = malloc(MAX_CODE_LEN);

	entrada = (gchar*) gtk_entry_get_text(GTK_ENTRY(ped_cod_entry));

	if(strlen(entrada)<=0){
		popup(NULL,"Necessário inserir código");
		return 1;
	}

	if(strlen(entrada)>=MAX_CODE_LEN){
		popup(NULL,"Código extenso");
		return 1;
	}

  GtkTreeStore *treestore = (GtkTreeStore*) gtk_tree_view_get_model(treeview);

	g_object_ref(G_OBJECT(treestore));
	gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),NULL);
	gtk_tree_store_clear(treestore);
	gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(treestore));

	GtkTreeStore *modelo = (GtkTreeStore*) gtk_tree_view_get_model(treeview);
  gtk_entry_set_text(GTK_ENTRY(ped_ter_entry),"");
	gtk_entry_set_text(GTK_ENTRY(ped_data_entry),"");

  gchar *formata_preco1 = malloc(MAX_PRECO_LEN);
  gchar *formata_preco2 = malloc(MAX_PRECO_LEN);
  gchar *formata_preco3 = malloc(MAX_PRECO_LEN);

	MYSQL_RES *res, *res2;
	MYSQL_ROW row, row2;
	char origem_preco[50],tipo_pag[50];
	char query[MAX_QUERY_LEN];
	GtkTreeIter campos;

	sprintf(query,"select c.razao, (SELECT DATE_FORMAT(p.data_mov, \"%%d/%%m/%%y\")), p.pag_cond, tipo_mov, p.banco, p.status from pedidos as p inner join terceiros as c on p.cliente = c.code where p.code = %s",entrada);
	if(!(res = consultar(query))){
		return 1;
	}
	if(!(row = mysql_fetch_row(res))){
		popup(NULL,"Pedido não existente");
		return 1;
	}

	gtk_entry_set_text(GTK_ENTRY(ped_ter_entry),row[0]);
	gtk_entry_set_text(GTK_ENTRY(ped_data_entry),row[1]);
	gtk_combo_box_set_active(GTK_COMBO_BOX(ped_tipo_combo),atoi(row[3]));

	sprintf(query,"select code,nome from bancos where code = %s",row[4]);
	if(!(res2 = consultar(query))){
		popup(NULL,"Não foi possível consultar Banco");
		return 1;
	}
	if((row2 = mysql_fetch_row(res2))){
		gtk_entry_set_text(GTK_ENTRY(ped_bancocod_entry),row2[0]);
		gtk_entry_set_text(GTK_ENTRY(ped_banco_entry),row2[1]);
	}
	else{
		gtk_entry_set_text(GTK_ENTRY(ped_banco_entry),"Sem Banco");
	}

	gtk_combo_box_set_active(GTK_COMBO_BOX(emiteped_status_combo),atoi(row[5]));

	sprintf(query,"select * from pag_cond where code = %s",row[2]);

	if(!(res = consultar(query))){
		return 1;
	}

	if(!(row = mysql_fetch_row(res))){
		popup(NULL,"O modelo de datas para o orcamento não existe mais");
		return 1;
	}

	if(atoi(row[6])>1)
		strcpy(tipo_pag,"Faturado");
	else
		strcpy(tipo_pag,"À Vista");

	gtk_entry_set_text(GTK_ENTRY(ped_pag_entry),tipo_pag);

	enum{
		NOME_PRODUTO,
		QUANTIDADE,
		VLR_UNIT,
		TIPO_DESCONTO,
		VLR_DESCONTO,
		VLR_TOTAL,
		ORIGEM_VLR
	};

	sprintf(query,"select p.nome, o.unidades, o.valor_unit, o.tipodesc, o.desconto, o.total, o.valor_orig from Produto_Orcamento as o inner join produtos as p on o.produto = p.code where o.code = %s",entrada);
	if(!(res = consultar(query))){
		return 1;
	}

	while((row = mysql_fetch_row(res))!=NULL)
	{
		if(strlen(row[NOME_PRODUTO])>15){
			row[NOME_PRODUTO][15] = '\0';
		}

		sprintf(formata_preco1,"R$ %.2f",atof(row[2])); //vlr unitario

		switch(atoi(row[TIPO_DESCONTO])){
			case DESCT_EM_REAIS:
				sprintf(formata_preco2,"R$ %.2f",atof(row[VLR_DESCONTO]));//desconto em reais

				break;
			case DESCT_EM_PORCENT:
				sprintf(formata_preco2,"%.2f%%",atof(row[VLR_DESCONTO])); //desconto em porcentagem
				break;
		}
		sprintf(formata_preco3,"R$ %.2f",atof(row[VLR_TOTAL]));
		gtk_tree_store_append(modelo,&campos,NULL);
		g_print("Inserindo nome: %s\n",row[NOME_PRODUTO]);

		gtk_tree_store_set(modelo,&campos,
		COLUMN0,row[NOME_PRODUTO],
		COLUMN1,row[QUANTIDADE],
		COLUMN2,formata_preco1,
		COLUMN3,formata_preco2,
		COLUMN4,formata_preco3,
		-1);

		switch(atoi(row[ORIGEM_VLR])){
			case ORIGPRC_PROD:
				strcpy(origem_preco,"Produto");
				break;
			case ORIGPRC_CLI:
				strcpy(origem_preco,"Cliente");
				break;
			case ORIGPRC_OPER:
				strcpy(origem_preco,"Operador");
				break;
			default:
				sprintf(query,"select nome from precos where code = %i", atoi(row[ORIGEM_VLR]));
				if(!(res = consultar(query))){
					popup(NULL,"Não foi possível consultar precos para o produto");
					return 1;
				}
				if(!(row=mysql_fetch_row(res))){
					strcpy(origem_preco,"Desconhecida");
				}else{
					strcpy(origem_preco,row[0]);
				}
		}
	}

	sprintf(query,"select t.razao,vlr_frete,valor_desconto_frete,(vlr_frete - valor_desconto_frete),observacoes_entrega from servico_transporte as st inner join terceiros as t on st.transportador = t.code where orcamento = %s",entrada);
	if(!(res = consultar(query)))
		return 1;
	if(!(row = mysql_fetch_row(res)))
		return 0;

	sprintf(formata_preco1,"R$ %.2f",atof(row[1])); //vlr_frete
	sprintf(formata_preco2,"R$ %.2f",atof(row[2])); //valor_desconto_frete
	sprintf(formata_preco3,"R$ %.2f",atof(row[3])); //valor_frete liquido

	gtk_tree_store_append(modelo,&campos,NULL);

	gtk_tree_store_set(modelo,&campos,
		COLUMN0,"Frete: ",
		COLUMN1,row[0],
		COLUMN2,formata_preco1,
		COLUMN3,formata_preco2,
		COLUMN4,formata_preco3,
		-1);

	return 0;
}

GtkWidget *campos_produto_ped()
{
	enum{
		COLUMN0,
		COLUMN1,
		COLUMN2,
		COLUMN3,
		COLUMN4,
		N_COLUMNS
	};

	GtkWidget *treeview;
	GtkTreeStore *modelo;
	GtkTreeIter iter;
	GtkTreeViewColumn *coluna1,*coluna2,*coluna3,*coluna4,*coluna5;
	GtkCellRenderer *celula1, *celula2, *celula3, *celula4, *celula5;

	coluna1 = gtk_tree_view_column_new();
	coluna2 = gtk_tree_view_column_new();
	coluna3 = gtk_tree_view_column_new();
	coluna4 = gtk_tree_view_column_new();
	coluna5 = gtk_tree_view_column_new();

	celula1 = gtk_cell_renderer_accel_new();
	gtk_cell_renderer_set_alignment(GTK_CELL_RENDERER(celula1),1,1);

	celula2 = gtk_cell_renderer_accel_new();
	gtk_cell_renderer_set_alignment(GTK_CELL_RENDERER(celula2),1,1);

	celula3 = gtk_cell_renderer_accel_new();
	gtk_cell_renderer_set_alignment(GTK_CELL_RENDERER(celula3),1,1);

	celula4 = gtk_cell_renderer_accel_new();
	gtk_cell_renderer_set_alignment(GTK_CELL_RENDERER(celula4),1,1);

	celula5 = gtk_cell_renderer_accel_new();
	gtk_cell_renderer_set_alignment(GTK_CELL_RENDERER(celula5),1,1);

	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(coluna1),celula1,TRUE);
	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(coluna2),celula2,TRUE);
	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(coluna3),celula3,TRUE);
	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(coluna4),celula4,TRUE);
	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(coluna5),celula5,TRUE);

	gtk_tree_view_column_add_attribute(GTK_TREE_VIEW_COLUMN(coluna1),celula1,"text",0);
	gtk_tree_view_column_set_title(GTK_TREE_VIEW_COLUMN(coluna1),"Produto");
	gtk_tree_view_column_set_alignment(GTK_TREE_VIEW_COLUMN(coluna1),0.5);

	gtk_tree_view_column_add_attribute(GTK_TREE_VIEW_COLUMN(coluna2),celula2,"text",1);
	gtk_tree_view_column_set_title(GTK_TREE_VIEW_COLUMN(coluna2),"Quantidade");
	gtk_tree_view_column_set_alignment(GTK_TREE_VIEW_COLUMN(coluna2),0.5);

	gtk_tree_view_column_add_attribute(GTK_TREE_VIEW_COLUMN(coluna3),celula3,"text",2);
	gtk_tree_view_column_set_title(GTK_TREE_VIEW_COLUMN(coluna3),"Vlr. Unitário");
	gtk_tree_view_column_set_alignment(GTK_TREE_VIEW_COLUMN(coluna3),0.5);

	gtk_tree_view_column_add_attribute(GTK_TREE_VIEW_COLUMN(coluna4),celula4,"text",3);
	gtk_tree_view_column_set_title(GTK_TREE_VIEW_COLUMN(coluna4),"Desc.");
	gtk_tree_view_column_set_alignment(GTK_TREE_VIEW_COLUMN(coluna4),0.5);

	gtk_tree_view_column_add_attribute(GTK_TREE_VIEW_COLUMN(coluna5),celula5,"text",4);
	gtk_tree_view_column_set_title(GTK_TREE_VIEW_COLUMN(coluna5),"Total");
	gtk_tree_view_column_set_alignment(GTK_TREE_VIEW_COLUMN(coluna5),0.5);

	treeview = gtk_tree_view_new();

	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna1);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna2);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna3);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna4);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna5);

	modelo = gtk_tree_store_new(N_COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(modelo));

	gtk_widget_show_all(treeview);
	return treeview;
}

int vnd_ped(){

	MYSQL_RES *res;
	MYSQL_ROW row;
	char nome_estoque[MAX_EST_NOME+MAX_CODE_LEN];
	char query[MAX_QUERY_LEN];
	int cont=0;

	g_print("Entrando na opcao de pedidos\n");
	GtkWidget *ped_cod_fixed, *ped_cod_box, *ped_cod_frame;
	GtkWidget *ped_ter_fixed, *ped_ter_box, *ped_ter_frame;
	GtkWidget *ped_data_fixed, *ped_data_box, *ped_data_frame;
	GtkWidget *ped_opcoes_fixed, *ped_opcoes_box, *ped_opcoes_frame;
	GtkWidget *ped_emitir_button, *ped_cancelar_button, *ped_excluir_button, *ped_regerar_button, *ped_enviar_button;
	GtkWidget *ped_pag_fixed, *ped_pag_box, *ped_pag_frame;
	GtkWidget *ped_est_fixed, *ped_est_box, *ped_est_frame;
	GtkWidget *ped_tipo_fixed, *ped_tipo_box, *ped_tipo_frame;
	GtkWidget *ped_status_fixed,*ped_status_box, *ped_status_frame;
	GtkWidget *ped_banco_fixed, *ped_banco_box, *ped_banco_frame;

	GtkWidget *treeview;
	GtkWidget *caixa_grande;
	GtkWidget *caixa_scroll, *caixa_produtos, *caixa_fixed;
	GtkWidget *linha1,*linha2,*linha3,*linha4;

	emitindo_ped = 0;
	janela_pedidos = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(janela_pedidos),"Pedidos");
	gtk_window_set_icon_name(GTK_WINDOW(janela_pedidos),"format-justify-fill");
	gtk_window_set_transient_for(GTK_WINDOW(janela_pedidos),GTK_WINDOW(janela_principal));
	gtk_window_set_position(GTK_WINDOW(janela_pedidos),3);
	gtk_widget_set_size_request(janela_pedidos,820,480);

	caixa_grande = gtk_box_new(1,0);
	caixa_scroll = gtk_scrolled_window_new(NULL,NULL);
	caixa_fixed = gtk_fixed_new();
	caixa_produtos = gtk_box_new(1,0);
	gtk_widget_set_size_request(caixa_scroll,800,200);
	gtk_widget_set_size_request(caixa_grande,800,200);

	ped_est_fixed = gtk_fixed_new();
	ped_est_box = gtk_box_new(1,0);
	ped_est_frame = gtk_frame_new("Estoque");
	ped_est_combo = gtk_combo_box_text_new();
	gtk_box_pack_start(GTK_BOX(ped_est_box),ped_est_combo,0,0,0);
	gtk_container_add(GTK_CONTAINER(ped_est_frame),ped_est_box);
	gtk_fixed_put(GTK_FIXED(ped_est_fixed),ped_est_frame,10,10);
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ped_est_combo),"Escolha o estoque");

	cont=0;
	sprintf(query,"select code,nome from estoques");
	if((res = consultar(query))==NULL){
		popup(NULL,"Erro ao buscar estoques");
		return 1;
	}
	while((row = mysql_fetch_row(res))!=NULL){
		sprintf(nome_estoque,"%s - %s",row[0],row[1]);
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ped_est_combo),nome_estoque);

		cont++;
	}
	if(!cont){
		popup(NULL,"Sem nenhum estoque cadastrado");
		if(cad_est())
			return 1;

		return 1;
	}

	janelas_gerenciadas.vetor_janelas[REG_CAD_PED].reg_id = REG_CAD_PED;
	janelas_gerenciadas.vetor_janelas[REG_CAD_PED].aberta = 1;
	if(ger_janela_aberta(janela_pedidos, &janelas_gerenciadas.vetor_janelas[REG_CAD_PED]))
		return 1;

	janelas_gerenciadas.vetor_janelas[REG_CAD_PED].janela_pointer = janela_pedidos;

	gtk_combo_box_set_active(GTK_COMBO_BOX(ped_est_combo),1);

	ped_emitir_button = gtk_button_new_with_label("Emitir");
	gtk_button_set_image(GTK_BUTTON(ped_emitir_button),gtk_image_new_from_icon_name("emblem-ok",GTK_ICON_SIZE_LARGE_TOOLBAR));
	ped_cancelar_button = gtk_button_new_with_label("Cancelar");
	gtk_button_set_image(GTK_BUTTON(ped_cancelar_button),gtk_image_new_from_icon_name("emblem-unreadable",GTK_ICON_SIZE_LARGE_TOOLBAR));
	ped_excluir_button = gtk_button_new_with_label("Excluir");
	gtk_button_set_image(GTK_BUTTON(ped_excluir_button),gtk_image_new_from_icon_name("user-trash",GTK_ICON_SIZE_LARGE_TOOLBAR));
	ped_regerar_button = gtk_button_new_with_label("Reemprimir");
	gtk_button_set_image(GTK_BUTTON(ped_regerar_button),gtk_image_new_from_icon_name("printer-printing",GTK_ICON_SIZE_LARGE_TOOLBAR));
	ped_enviar_button = gtk_button_new_with_label("Enviar Email");
	gtk_button_set_image(GTK_BUTTON(ped_enviar_button),gtk_image_new_from_icon_name("mail-forward",GTK_ICON_SIZE_LARGE_TOOLBAR));

	ped_opcoes_fixed = gtk_fixed_new();
	ped_opcoes_box = gtk_box_new(0,0);
	ped_opcoes_frame = gtk_frame_new("Opções");

	gtk_box_pack_start(GTK_BOX(ped_opcoes_box),ped_emitir_button,0,0,10);
	gtk_box_pack_start(GTK_BOX(ped_opcoes_box),ped_cancelar_button,0,0,10);
	gtk_box_pack_start(GTK_BOX(ped_opcoes_box),ped_excluir_button,0,0,10);
	gtk_box_pack_start(GTK_BOX(ped_opcoes_box),ped_regerar_button,0,0,10);
	gtk_box_pack_start(GTK_BOX(ped_opcoes_box),ped_enviar_button,0,0,10);

	gtk_container_add(GTK_CONTAINER(ped_opcoes_frame),ped_opcoes_box);
	gtk_fixed_put(GTK_FIXED(ped_opcoes_fixed),ped_opcoes_frame,40,20);

	ped_tipo_combo = gtk_combo_box_text_new();
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(ped_tipo_combo),0,"Venda");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ped_tipo_combo),"Devolução Venda");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ped_tipo_combo),"Compra");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ped_tipo_combo),"Devolução Compra");
	gtk_combo_box_set_active(GTK_COMBO_BOX(ped_tipo_combo),0);
	ped_tipo_fixed = gtk_fixed_new();
	ped_tipo_box = gtk_box_new(0,0);
	ped_tipo_frame = gtk_frame_new("Tipo Operação");
	gtk_box_pack_start(GTK_BOX(ped_tipo_box),ped_tipo_combo,0,0,10);
	gtk_container_add(GTK_CONTAINER(ped_tipo_frame),ped_tipo_box);
	gtk_fixed_put(GTK_FIXED(ped_tipo_fixed),ped_tipo_frame,10,10);
	gtk_widget_set_sensitive(ped_tipo_combo,FALSE);

	linha1 = gtk_box_new(0,0);
	linha2 = gtk_box_new(0,0);
	linha3 = gtk_box_new(1,0);
	linha4 = gtk_box_new(0,0);

	ped_psq_cod_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(ped_psq_cod_button),gtk_image_new_from_file(IMG_PESQ));
	ped_cod_entry = gtk_entry_new();
	ped_cod_fixed = gtk_fixed_new();
	ped_cod_box = gtk_box_new(0,0);
	ped_cod_frame = gtk_frame_new("Pedido:");
	gtk_box_pack_start(GTK_BOX(ped_cod_box),ped_cod_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(ped_cod_box),ped_psq_cod_button,0,0,5);
	gtk_container_add(GTK_CONTAINER(ped_cod_frame),ped_cod_box);
	gtk_fixed_put(GTK_FIXED(ped_cod_fixed),ped_cod_frame,10,10);
	gtk_entry_set_width_chars(GTK_ENTRY(ped_cod_entry),8);

	ped_data_entry = gtk_entry_new();
	ped_data_fixed = gtk_fixed_new();
	ped_data_box = gtk_box_new(1,0);
	ped_data_frame = gtk_frame_new("Data");
	gtk_box_pack_start(GTK_BOX(ped_data_box),ped_data_entry,0,0,0);
	gtk_container_add(GTK_CONTAINER(ped_data_frame),ped_data_box);
	gtk_fixed_put(GTK_FIXED(ped_data_fixed),ped_data_frame,10,10);
	gtk_entry_set_width_chars(GTK_ENTRY(ped_data_entry),10);
	gtk_editable_set_editable(GTK_EDITABLE(ped_data_entry),FALSE);

	ped_ter_entry = gtk_entry_new();
	ped_ter_fixed = gtk_fixed_new();
	ped_ter_box = gtk_box_new(1,0);
	ped_ter_frame = gtk_frame_new("Cliente");
	gtk_box_pack_start(GTK_BOX(ped_ter_box),ped_ter_entry,0,0,0);
	gtk_container_add(GTK_CONTAINER(ped_ter_frame),ped_ter_box);
	gtk_fixed_put(GTK_FIXED(ped_ter_fixed),ped_ter_frame,10,10);
	gtk_entry_set_width_chars(GTK_ENTRY(ped_ter_entry),40);
	gtk_editable_set_editable(GTK_EDITABLE(ped_ter_entry),FALSE);

	ped_pag_entry = gtk_entry_new();
	ped_pag_fixed = gtk_fixed_new();
	ped_pag_box = gtk_box_new(1,0);
	ped_pag_frame = gtk_frame_new("Tipo Pagamento");
	gtk_box_pack_start(GTK_BOX(ped_pag_box),ped_pag_entry,0,0,0);
	gtk_container_add(GTK_CONTAINER(ped_pag_frame),ped_pag_box);
	gtk_fixed_put(GTK_FIXED(ped_pag_fixed),ped_pag_frame,10,10);
	gtk_entry_set_width_chars(GTK_ENTRY(ped_pag_entry),15);
	gtk_editable_set_editable(GTK_EDITABLE(ped_pag_entry),FALSE);

	emiteped_status_combo = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(emiteped_status_combo),"Pendentes");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(emiteped_status_combo),"Emitidos");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(emiteped_status_combo),"Cancelados");
	gtk_combo_box_set_active(GTK_COMBO_BOX(emiteped_status_combo),0);
	ped_status_fixed = gtk_fixed_new();
	ped_status_box = gtk_box_new(0,0);
	ped_status_frame = gtk_frame_new("Status");
	gtk_box_pack_start(GTK_BOX(ped_status_box),emiteped_status_combo,0,0,0);
	gtk_container_add(GTK_CONTAINER(ped_status_frame),ped_status_box);
	gtk_fixed_put(GTK_FIXED(ped_status_fixed),ped_status_frame,10,10);
	gtk_widget_set_sensitive(emiteped_status_combo,FALSE);

	ped_banco_entry = gtk_entry_new();
	ped_bancocod_entry = gtk_entry_new();
	ped_banco_fixed  = gtk_fixed_new();
	ped_banco_box = gtk_box_new(0,0);
	ped_banco_frame = gtk_frame_new("Banco");
	gtk_entry_set_width_chars(GTK_ENTRY(ped_bancocod_entry),5);
	gtk_box_pack_start(GTK_BOX(ped_banco_box),ped_bancocod_entry,0,0,5);
	gtk_box_pack_start(GTK_BOX(ped_banco_box),ped_banco_entry,0,0,0);
	gtk_container_add(GTK_CONTAINER(ped_banco_frame),ped_banco_box);
	gtk_fixed_put(GTK_FIXED(ped_banco_fixed),ped_banco_frame,10,10);
	gtk_editable_set_editable(GTK_EDITABLE(ped_banco_entry),FALSE);

	treeview = campos_produto_ped();

	gtk_box_pack_start(GTK_BOX(caixa_produtos),treeview,0,0,0);

	gtk_container_add(GTK_CONTAINER(caixa_scroll),caixa_produtos);

	gtk_fixed_put(GTK_FIXED(caixa_fixed),caixa_scroll,10,20);

	gtk_box_pack_start(GTK_BOX(linha1),ped_cod_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linha1),ped_data_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linha1),ped_pag_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linha1),ped_tipo_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linha1),ped_status_fixed,0,0,0);

	gtk_box_pack_start(GTK_BOX(linha2),ped_ter_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linha2),ped_est_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linha2),ped_banco_fixed,0,0,0);

	gtk_box_pack_start(GTK_BOX(linha3),caixa_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linha4),ped_opcoes_fixed,0,0,0);

	gtk_box_pack_start(GTK_BOX(caixa_grande),linha1,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),linha2,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),linha3,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),linha4,0,0,0);

	gtk_container_add(GTK_CONTAINER(janela_pedidos),caixa_grande);

	g_signal_connect(ped_psq_cod_button,"clicked",G_CALLBACK(psq_ped),ped_cod_entry);
	g_signal_connect(ped_emitir_button,"clicked",G_CALLBACK(ped_emitir),NULL);
	g_signal_connect(ped_cancelar_button,"clicked",G_CALLBACK(ped_cancelar),NULL);
	g_signal_connect(ped_regerar_button,"clicked",G_CALLBACK(ped_gerar),NULL);
	g_signal_connect(ped_enviar_button,"clicked",G_CALLBACK(ped_enviar),NULL);
	g_signal_connect(ped_excluir_button,"clicked",G_CALLBACK(ped_excluir),NULL);

	g_signal_connect(ped_cod_entry,"activate",G_CALLBACK(produtos_ped_list),treeview);
	g_signal_connect(janela_pedidos,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_CAD_PED]);

	gtk_widget_show_all(janela_pedidos);
	return 0;
}
