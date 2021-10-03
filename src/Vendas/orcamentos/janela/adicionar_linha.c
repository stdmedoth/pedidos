int orc_scrolled_item(GtkScrolledWindow *scrolled_window, GtkPositionType pos, gpointer user_data)
{
	if(g_signal_handler_is_connected(user_data,orc_auto_mover_signal)){
		g_signal_handler_disconnect(user_data,orc_auto_mover_signal);
	}

	return 0;
}


static int adicionar_linha_orc()
{
	GtkAdjustment *ajustar;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query = malloc(MAX_QUERY_LEN);

	if(!g_signal_handler_is_connected(prod_scroll_window,orc_auto_mover_signal)){
		orc_auto_mover_signal = g_signal_connect(itens_orc_box,"size-allocate",G_CALLBACK(auto_vmover_scroll),prod_scroll_window);
	}

	if(!alterando_orc){

		if(codigo_orc())
			return 1;

		sprintf(query,"select * from Produto_Orcamento where code = %s",codigo_orc_gchar);
		res = consultar(query);

		if(!res){
			if((row = mysql_fetch_row(res))!=NULL)
				popup(NULL,"O código de Orcamento usado já existe\nDeseja alterar?");
		}

	}

	if(!recebendo_prod_orc && orc_contem_ped){
		popup(NULL,"Não é possível alterar orçamento processado");
		return 1;
	}

	int itens_pos = itens_qnt -1;
	if(ativos[itens_pos].id == 1){

		int cont=0;

		if(codigo_orc()!=0)
			return 1;

		if(codigo_cli_orc()!=0)
			return 1;


		if( !codigo_prod_orc_entry[itens_pos] ||
				!qnt_prod_orc_entry[itens_pos] ||
				!preco_prod_orc_entry[itens_pos] ||
				!obs_prod_orc_view[itens_pos] ){
					popup(NULL,"Provável corrupção de memória ao adicionar novo item");
					file_logger("adicionar_linha_orc() -> Provável corrupção de memória ao adicionar novo item");
					return 1;
				}

		if( GTK_IS_WIDGET(codigo_prod_orc_entry[itens_pos])){
			if(codigo_prod_orc(codigo_prod_orc_entry[itens_pos],itens_pos))
				return 1;
		}

		if( GTK_IS_WIDGET(qnt_prod_orc_entry[itens_pos]) ){
			if(qnt_prod_orc(qnt_prod_orc_entry[itens_pos],itens_pos))
				return 1;
		}

		if( GTK_IS_WIDGET(preco_prod_orc_entry[itens_pos]) ){
			if(preco_prod_orc(preco_prod_orc_entry[itens_pos],itens_pos))
				return 1;
		}

		if( GTK_IS_WIDGET(obs_prod_orc_view[itens_pos]) ){
			if(obs_prod_orc_fun(obs_prod_orc_view[itens_pos],itens_pos))
				return 1;
		}
	}

	if(itens_qnt>=MAX_PROD_ORC){
		popup(NULL,"Limite de itens");
		return 1;
	}

	if(gerar_total_geral())
		return 1;

	codigo_orc_prod_box[itens_qnt] = gtk_box_new(0,0);
	sprintf(item_frame_char,"Item %i",itens_qnt);
	linhas_prod_orc_frame[itens_qnt] =  gtk_frame_new(item_frame_char);
	gtk_widget_set_name(linhas_prod_orc_frame[itens_qnt],"frame2");
	linhas_prod_orc_box[itens_qnt] = gtk_box_new(0,0);
	linhas2_prod_orc_box[itens_qnt] = gtk_box_new(0,0);
	juncao_linha_prod_orc_box[itens_qnt] = gtk_box_new(1,0);
	obs_prod_orc_gchar[itens_qnt] = malloc(MAX_OBS_LEN);
	codigo_prod_orc_label[itens_qnt] = gtk_label_new("Cód");
	codigo_prod_orc_entry[itens_qnt] = gtk_entry_new();
	pesquisa_prod[itens_qnt] = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(pesquisa_prod[itens_qnt]), gtk_image_new_from_file(IMG_PESQ));

	codigo_prod_orc_frame[itens_qnt] = gtk_frame_new("Código Produto");
	desconto_prod_orc_frame[itens_qnt] = gtk_frame_new("Desconto");
	desconto_prod_orc_box[itens_qnt] = gtk_box_new(0,0);

	preco_prod_orc_frame[itens_qnt] = gtk_frame_new("Preço");
	preco_prod_orc_box[itens_qnt] = gtk_box_new(0,0);

	qnt_prod_orc_frame[itens_qnt] = gtk_frame_new("Quantidade:");
	qnt_prod_orc_box[itens_qnt] = gtk_box_new(0,0);

	descricao_prod_orc_label[itens_qnt] = gtk_label_new("Descr.");
	descricao_prod_orc_entry[itens_qnt] = gtk_entry_new();

	qnt_prod_orc_label[itens_qnt] = gtk_label_new("Qnt:");
	qnt_prod_orc_entry[itens_qnt] = gtk_entry_new();

	saldo_prod_orc_frame[itens_qnt] = gtk_frame_new("Saldo:");
	saldo_prod_orc_box[itens_qnt] = gtk_box_new(0,0);
	saldo_prod_orc_entry[itens_qnt] = gtk_entry_new();
	gtk_editable_set_editable(GTK_EDITABLE(saldo_prod_orc_entry[itens_qnt]),FALSE);

	preco_prod_orc_label[itens_qnt] = gtk_label_new("Vlr:");
	preco_prod_orc_entry[itens_qnt] = gtk_entry_new();

	orig_preco_prod_orc_combo[itens_qnt] = gtk_combo_box_text_new();
	resetar_orig_preco(itens_qnt);

	tipodesconto_prod_orc_combo[itens_qnt] = gtk_combo_box_text_new();
	desconto_prod_orc_label[itens_qnt] = gtk_label_new("Desconto");
	desconto_prod_orc_entry[itens_qnt] = gtk_entry_new();

	total_prod_orc_fixed[itens_qnt] = gtk_fixed_new();
	total_prod_orc_frame[itens_qnt] = gtk_frame_new("Total");
	total_prod_orc_box[itens_qnt] = gtk_box_new(1,0);
	total_prod_orc_entry[itens_qnt] = gtk_entry_new();

	obs_prod_orc_view[itens_qnt] = gtk_text_view_new();
	obs_prod_orc_frame[itens_qnt] = gtk_frame_new("Observações");
	obs_prod_orc_scroll[itens_qnt] = gtk_scrolled_window_new(NULL,NULL);
	obs_prod_orc_fixed[itens_qnt] = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(obs_prod_orc_scroll[itens_qnt]),obs_prod_orc_view[itens_qnt]);
	gtk_container_add(GTK_CONTAINER(obs_prod_orc_frame[itens_qnt]),obs_prod_orc_scroll[itens_qnt]);
	gtk_fixed_put(GTK_FIXED(obs_prod_orc_fixed[itens_qnt]),obs_prod_orc_frame[itens_qnt],10,0);
	gtk_widget_set_size_request(obs_prod_orc_scroll[itens_qnt],500,20);
	gtk_widget_set_size_request(obs_prod_orc_view[itens_qnt],500,20);


	gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(tipodesconto_prod_orc_combo[itens_qnt]),DESCT_EM_REAIS,"0","R$");
	gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(tipodesconto_prod_orc_combo[itens_qnt]),DESCT_EM_PORCENT,"1","%");

	//verifica o tipo de calculo de desconto anterior
	if(ativos_qnt>1){
		int itens_pos = itens_qnt -1;
		if(ativos[itens_pos].id == 1)
			gtk_combo_box_set_active(GTK_COMBO_BOX(tipodesconto_prod_orc_combo[itens_qnt]),
			gtk_combo_box_get_active(GTK_COMBO_BOX(tipodesconto_prod_orc_combo[itens_pos])));
		else
			gtk_combo_box_set_active(GTK_COMBO_BOX(tipodesconto_prod_orc_combo[itens_qnt]),0);
	}
	else{
		gtk_combo_box_set_active(GTK_COMBO_BOX(tipodesconto_prod_orc_combo[itens_qnt]),0);
	}

	if(GTK_IS_WIDGET(botao_orc_mais)){
		gtk_widget_destroy(botao_orc_mais);
	}

	img_botao_orc_mais = gtk_image_new_from_file(IMG_MAIS);
	botao_orc_mais  = gtk_button_new();
	g_object_ref(botao_orc_mais);
	g_object_ref_sink(botao_orc_mais);
	gtk_button_set_image(GTK_BUTTON(botao_orc_mais),img_botao_orc_mais);

	botao_menos[itens_qnt] = gtk_button_new();
	img_botao_menos[itens_qnt] = gtk_image_new_from_file(IMG_MENOS);
	gtk_button_set_image(GTK_BUTTON(botao_menos[itens_qnt]),img_botao_menos[itens_qnt]);

	//gtk_box_pack_start(GTK_BOX(codigo_orc_prod_box[itens_qnt]),codigo_prod_orc_label[itens_qnt],0,0,2);
	gtk_box_pack_start(GTK_BOX(codigo_orc_prod_box[itens_qnt]),codigo_prod_orc_entry[itens_qnt],0,0,2);
	gtk_entry_set_width_chars(GTK_ENTRY(codigo_prod_orc_entry[itens_qnt]),5);
	gtk_box_pack_start(GTK_BOX(codigo_orc_prod_box[itens_qnt]),pesquisa_prod[itens_qnt],0,0,2);
	//gtk_box_pack_start(GTK_BOX(codigo_orc_prod_box[itens_qnt]),descricao_prod_orc_label[itens_qnt],0,0,2);
	gtk_box_pack_start(GTK_BOX(codigo_orc_prod_box[itens_qnt]),descricao_prod_orc_entry[itens_qnt],0,0,2);
	gtk_editable_set_editable(GTK_EDITABLE(descricao_prod_orc_entry[itens_qnt]),FALSE);
	gtk_entry_set_width_chars(GTK_ENTRY(descricao_prod_orc_entry[itens_qnt]),20);
	gtk_container_add(GTK_CONTAINER(codigo_prod_orc_frame[itens_qnt]),codigo_orc_prod_box[itens_qnt]);

	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),codigo_prod_orc_frame[itens_qnt],0,0,15);

	gtk_box_pack_start(GTK_BOX(qnt_prod_orc_box[itens_qnt]),qnt_prod_orc_label[itens_qnt],0,0,2);
	gtk_box_pack_start(GTK_BOX(qnt_prod_orc_box[itens_qnt]),qnt_prod_orc_entry[itens_qnt],0,0,2);
	gtk_container_add(GTK_CONTAINER(qnt_prod_orc_frame[itens_qnt]),qnt_prod_orc_box[itens_qnt]);
	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),qnt_prod_orc_frame[itens_qnt],0,0,2);
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(qnt_prod_orc_entry[itens_qnt]), GTK_ENTRY_ICON_PRIMARY, "system-software-install");
	gtk_entry_set_width_chars(GTK_ENTRY(qnt_prod_orc_entry[itens_qnt]),10);

	gtk_box_pack_start(GTK_BOX(saldo_prod_orc_box[itens_qnt]),saldo_prod_orc_entry[itens_qnt],0,0,2);
	gtk_container_add(GTK_CONTAINER(saldo_prod_orc_frame[itens_qnt]),saldo_prod_orc_box[itens_qnt]);
	gtk_entry_set_width_chars(GTK_ENTRY(saldo_prod_orc_entry[itens_qnt]),8);
	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),saldo_prod_orc_frame[itens_qnt],0,0,2);

	gtk_box_pack_start(GTK_BOX(preco_prod_orc_box[itens_qnt]),orig_preco_prod_orc_combo[itens_qnt],0,0,2);
	gtk_box_pack_start(GTK_BOX(preco_prod_orc_box[itens_qnt]),preco_prod_orc_label[itens_qnt],0,0,2);
	gtk_box_pack_start(GTK_BOX(preco_prod_orc_box[itens_qnt]),preco_prod_orc_entry[itens_qnt],0,0,2);
	gtk_container_add(GTK_CONTAINER(preco_prod_orc_frame[itens_qnt]),preco_prod_orc_box[itens_qnt]);
	gtk_entry_set_width_chars(GTK_ENTRY(preco_prod_orc_entry[itens_qnt]),10);

	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),preco_prod_orc_frame[itens_qnt],0,0,2);
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(preco_prod_orc_entry[itens_qnt]),GTK_ENTRY_ICON_PRIMARY,"money");
	//gtk_box_pack_start(GTK_BOX(desconto_prod_orc_box[itens_qnt]),desconto_prod_orc_label[itens_qnt],0,0,2);
	gtk_box_pack_start(GTK_BOX(desconto_prod_orc_box[itens_qnt]),desconto_prod_orc_entry[itens_qnt],0,0,2);
	gtk_box_pack_start(GTK_BOX(desconto_prod_orc_box[itens_qnt]),tipodesconto_prod_orc_combo[itens_qnt],0,0,2);
	gtk_container_add(GTK_CONTAINER(desconto_prod_orc_frame[itens_qnt]),desconto_prod_orc_box[itens_qnt]);
	gtk_entry_set_width_chars(GTK_ENTRY(desconto_prod_orc_entry[itens_qnt]),10);

	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),desconto_prod_orc_frame[itens_qnt],0,0,2);

	gtk_box_pack_start(GTK_BOX(total_prod_orc_box[itens_qnt]),total_prod_orc_entry[itens_qnt],0,0,2);
	gtk_container_add(GTK_CONTAINER(total_prod_orc_frame[itens_qnt]),total_prod_orc_box[itens_qnt]);
	gtk_fixed_put(GTK_FIXED(total_prod_orc_fixed[itens_qnt]),total_prod_orc_frame[itens_qnt],0,0);
	gtk_entry_set_width_chars(GTK_ENTRY(total_prod_orc_entry[itens_qnt]),10);

	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),total_prod_orc_fixed[itens_qnt],0,0,2);


	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),botao_menos[itens_qnt],0,0,2);
	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),botao_orc_mais,0,0,2);

	gtk_box_pack_start(GTK_BOX(linhas2_prod_orc_box[itens_qnt]),obs_prod_orc_fixed[itens_qnt],0,0,2);

	gtk_box_pack_start(GTK_BOX(juncao_linha_prod_orc_box[itens_qnt]),linhas_prod_orc_box[itens_qnt],0,0,2);
	gtk_box_pack_start(GTK_BOX(juncao_linha_prod_orc_box[itens_qnt]),linhas2_prod_orc_box[itens_qnt],0,0,2);

	gtk_container_add(GTK_CONTAINER(linhas_prod_orc_frame[itens_qnt]),juncao_linha_prod_orc_box[itens_qnt]);

	//gtk_widget_set_size_request(linhas_prod_orc_frame[itens_qnt],1100,25);

	gtk_grid_attach(GTK_GRID(orc_prods_grid),linhas_prod_orc_frame[itens_qnt],0,itens_qnt,1,1);

	id_vetor[itens_qnt] = itens_qnt;
	ativos[itens_qnt].id = 1;
	excluidos[itens_qnt].id = 0;
	preco_alterado[itens_qnt] = 0;
	valor_orig[itens_qnt] = 0;
	aviso_estoque[itens_qnt] = 0;
	ativos_qnt++;

	for(int pos=1;pos<MAX_PROD_ORC;pos++){
		if(ativos[pos].id == 1){
			gtk_widget_set_sensitive(botao_menos[pos],TRUE);
		}
	}
	if(itens_qnt<MAX_PROD_ORC)
		gtk_widget_set_sensitive(botao_menos[itens_qnt],FALSE);

	if(ativos_qnt>2){
		gtk_widget_set_sensitive(cliente_orc_entry,FALSE);
	}
	else{
		gtk_widget_set_sensitive(cliente_orc_entry,TRUE);
	}

	#pragma GCC diagnostic ignored "-Wint-conversion"

	if(param_funcionalidades.retirar_orc_linha_item)
		g_signal_connect(botao_menos[itens_qnt],"clicked",G_CALLBACK(remover_linha_orc),id_vetor[itens_qnt]);

	g_signal_connect(codigo_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(codigo_prod_orc),id_vetor[itens_qnt]);
	g_signal_connect(pesquisa_prod[itens_qnt],"clicked",G_CALLBACK(psq_prod),codigo_prod_orc_entry[id_vetor[itens_qnt]]);
	g_signal_connect(qnt_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(qnt_prod_orc),id_vetor[itens_qnt]);
	g_signal_connect(orig_preco_prod_orc_combo[itens_qnt],"changed",G_CALLBACK(calcula_prod_orc),id_vetor[itens_qnt]);
	g_signal_connect(preco_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(preco_prod_orc),id_vetor[itens_qnt]);
	g_signal_connect(desconto_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(desconto_prod_orc),id_vetor[itens_qnt]);
	g_signal_connect(tipodesconto_prod_orc_combo[itens_qnt],"changed",G_CALLBACK(desconto_prod_orc),id_vetor[itens_qnt]);
	g_signal_connect(total_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(total_prod_orc),id_vetor[itens_qnt]);

	g_signal_connect(codigo_prod_orc_entry[itens_qnt], "key-press-event", G_CALLBACK(only_number_entry), NULL);
	g_signal_connect(qnt_prod_orc_entry[itens_qnt], "key-press-event", G_CALLBACK(only_number_entry), NULL);
	g_signal_connect(preco_prod_orc_entry[itens_qnt], "key-press-event", G_CALLBACK(only_number_entry), NULL);
	g_signal_connect(desconto_prod_orc_entry[itens_qnt], "key-press-event", G_CALLBACK(only_number_entry), NULL);
	g_signal_connect(total_prod_orc_entry[itens_qnt], "key-press-event", G_CALLBACK(only_number_entry), NULL);

	#pragma GCC diagnostic warning "-Wint-conversion"

	g_signal_connect(botao_orc_mais,"clicked",G_CALLBACK(adicionar_linha_orc),NULL);

	gtk_widget_grab_focus(codigo_prod_orc_entry[itens_qnt]);

	gtk_widget_show_all(linhas_prod_orc_frame[itens_qnt]);



	itens_qnt++;


	return 0;
}
