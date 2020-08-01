static int altera_orc()
{
	char query[MAX_QUERY_LEN];
	int cont=1,erro=0;
	char code[MAX_CODE_LEN];
	MYSQL_RES *res, *res2;
	MYSQL_ROW row, row2;
	GtkTextBuffer *buffer;
	char tmp_cod_orc[MAX_CODE_LEN];

	g_print("Iniciando alterar\n");
	alterando_orc=1;
	rec_altera_qnt=1;
	recebendo_prod_orc=1;

	if(codigo_orc()!=0){
		cancela_orc();
		return 1;
	}

	sprintf(query,"select status from pedidos where code = %s",codigo_orc_gchar);
	if((res = consultar(query))==NULL)
	{
		popup(NULL,"Erro ao buscar vinculos de pedidos");
		cancela_orc();
		return 1;
	}

	if((row = mysql_fetch_row(res))!=NULL)
	{
		if(atoi(row[0]) == STATUS_PED_EMIT){
			popup(NULL,"Existe um pedido emitido para este orçamento");
			cancela_orc();
			return 1;
		}
	}

	strcpy(tmp_cod_orc, codigo_orc_gchar);

	cancela_orc();

	alterando_orc=1;
	rec_altera_qnt=1;
	recebendo_prod_orc=1;

	if(observacoes_orc_get()!=0){
		cancela_orc();
		return 1;
	}
	//buscando informações basicas de orçamentos
	sprintf(query,"select cliente, tipo_mov, pag_cond, (%s%s), total, observacoes from orcamentos where code = %s",DATE_QUERY,tmp_cod_orc,tmp_cod_orc);

	if((res = consultar(query))==NULL)
	{
		popup(NULL,"Erro ao buscar orçamento");
		cancela_orc();
		return 1;
	}

	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Orçamento não existe para ser alterado");
		cancela_orc();
		return 1;
	}

	gtk_entry_set_text(GTK_ENTRY(cliente_orc_entry),row[0]);
	gtk_combo_box_set_active(GTK_COMBO_BOX(operacao_orc_combo),atoi(row[1]));
	gtk_entry_set_text(GTK_ENTRY(orc_pag_cond_entry),row[2]);
	gtk_entry_set_text(GTK_ENTRY(data_orc_entry),row[3]);

	gtk_widget_activate(cliente_orc_entry);
	gtk_widget_activate(orc_pag_cond_entry);

	if(row[4] && strlen(row[5])){
		buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacoes_orc));
		gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer),row[5],strlen(row[5]));
	}

	if(codigo_cli_orc()!=0){
		autologger("Erro no código do cliente durante alteracao");
		cancela_orc();
		return 1;
	}
	//buscando informações basicas de transporte
	sprintf(query,"select * from servico_transporte where orcamento = %s",tmp_cod_orc);
	if((res = consultar(query))==NULL)
	{
		popup(NULL,"Erro ao buscar serviço de transporte");
		cancela_orc();
		return 1;
	}
	if((row = mysql_fetch_row(res))==NULL)
	{
		orc_com_entrega = 0;
	}else{
		sprintf(query,"select razao,doc,ie from terceiros where code = %s",row[TRANSP_TRSP_COL]);
		if((res2 = consultar(query))==NULL)
		{
			popup(NULL,"Erro ao buscar serviço de transporte");
			cancela_orc();
			return 1;
		}
		if((row2 = mysql_fetch_row(res2))==NULL)
		{
			popup(NULL,"Transportadora da entrega não existe, verifique o cadastro");
		}else{
			gtk_entry_set_text(GTK_ENTRY(orc_transp_nome_entry),row2[0]);
			gtk_entry_set_text(GTK_ENTRY(orc_transp_cnpj_entry),row2[1]);
			gtk_entry_set_text(GTK_ENTRY(orc_transp_ie_entry),row2[2]);
		}
		gtk_entry_set_text(GTK_ENTRY(orc_transp_codigo_entry),row[TRANSP_TRSP_COL]);
		gtk_entry_set_text(GTK_ENTRY(orc_transp_cep_entry),row[TRANSP_CEP2_COL]);
		gtk_entry_set_text(GTK_ENTRY(orc_transp_num_entry),row[TRANSP_NUM_COL]);
	}


	sprintf(query,"select * from Produto_Orcamento where code = %i",atoi(tmp_cod_orc));
	if((res = consultar(query))==NULL){
		popup(NULL,"Erro nos itens do orçamento");
		cancela_orc();
		return 1;
	}

	for(int cont=1;cont<=MAX_PROD_ORC;cont++){
		if(ativos[cont].id==1)
		{
			tirar_linha(cont);
		}
	}

	while((row = mysql_fetch_row(res))!=NULL)
	{
		//arquivando as informacoes da alteração
		file_logger("\n\nAdicionando item %s à alteração \n");
		file_logger(row[1]);
		file_logger("Dados:\n");
		file_logger("code: %s\n");
		file_logger(row[COD_ORC_PROD_COL]);
		file_logger("item: %s\n");
		file_logger(row[ITM_ORC_PROD_COL]);
		file_logger("produto: %s\n");
		file_logger(row[PROD_ORC_PROD_COL]);
		file_logger("subgrupo: %s\n");
		file_logger(row[SUBGRP_ORC_PROD_COL]);
		file_logger("unidades: %s\n");
		file_logger(row[UND_ORC_PROD_COL]);
		file_logger("valor_unit: %s\n");
		file_logger(row[VLR_ORC_PROD_COL]);
		file_logger("valor_orig: %s\n");
		file_logger(row[VLR_ORIG_ORC_PROD_COL]);
		file_logger("tipodesc: %s\n");
		file_logger(row[TIP_DESC_ORC_PROD_COL]);
		file_logger("desconto: %s\n");
		file_logger(row[DESC_ORC_PROD_COL]);
		file_logger("total: %s\n\n");
		file_logger(row[TOTAL_ORC_PROD_COL]);
		file_logger("Observacao: %s\n\n");
		file_logger(row[OBS_ORC_PROD_COL]);

		itens_qnt = atoi(row[ITM_ORC_PROD_COL]);

		adicionar_linha_orc();

		if(GTK_IS_ENTRY(codigo_prod_orc_entry[atoi(row[ITM_ORC_PROD_COL])]))
		{
			codigo_prod_orc_gchar = malloc(strlen(row[PROD_ORC_PROD_COL]));
			strcpy(codigo_prod_orc_gchar,row[PROD_ORC_PROD_COL]);
			gtk_entry_set_text(GTK_ENTRY(codigo_prod_orc_entry[atoi(row[ITM_ORC_PROD_COL])]),codigo_prod_orc_gchar);
			ativos[atoi(row[ITM_ORC_PROD_COL])].produto = atoi(row[PROD_ORC_PROD_COL]);

			subgrp_prod_orc_cod_gchar = malloc(strlen(row[SUBGRP_ORC_PROD_COL]));
			strcpy(subgrp_prod_orc_cod_gchar,row[SUBGRP_ORC_PROD_COL]);
			gtk_entry_set_text(GTK_ENTRY(subgrp_prod_orc_cod_entry[atoi(row[ITM_ORC_PROD_COL])]),subgrp_prod_orc_cod_gchar);
			ativos[atoi(row[ITM_ORC_PROD_COL])].subgrupo = atoi(row[SUBGRP_ORC_PROD_COL]);

			valor_orig[atoi(row[ITM_ORC_PROD_COL])] = atoi(row[VLR_ORIG_ORC_PROD_COL]);

			qnt_prod_orc_gchar = malloc(strlen(row[UND_ORC_PROD_COL]));
			strcpy(qnt_prod_orc_gchar,row[UND_ORC_PROD_COL]);
			gtk_entry_set_text(GTK_ENTRY(qnt_prod_orc_entry[atoi(row[ITM_ORC_PROD_COL])]),qnt_prod_orc_gchar);

			gtk_combo_box_set_active(GTK_COMBO_BOX(orig_preco_prod_orc_combo[atoi(row[ITM_ORC_PROD_COL])]),valor_orig[atoi(row[ITM_ORC_PROD_COL])]);

			gtk_combo_box_set_active(GTK_COMBO_BOX(tipodesconto_prod_orc_combo[atoi(row[ITM_ORC_PROD_COL])]),atoi(row[TIP_DESC_ORC_PROD_COL]));

			preco_prod_orc_gchar = malloc(strlen(row[VLR_ORC_PROD_COL]));
			strcpy(preco_prod_orc_gchar,row[VLR_ORC_PROD_COL]);
			gtk_entry_set_text(GTK_ENTRY(preco_prod_orc_entry[atoi(row[ITM_ORC_PROD_COL])]),preco_prod_orc_gchar);

			desconto_prod_orc_gchar = malloc(strlen(row[DESC_ORC_PROD_COL]));
			strcpy(desconto_prod_orc_gchar,row[DESC_ORC_PROD_COL]);
			gtk_entry_set_text(GTK_ENTRY(desconto_prod_orc_entry[atoi(row[ITM_ORC_PROD_COL])]),desconto_prod_orc_gchar);

			desconto_prod_orc_gchar = malloc(strlen(row[TOTAL_ORC_PROD_COL]));
			strcpy(desconto_prod_orc_gchar,row[TOTAL_ORC_PROD_COL]);
			gtk_entry_set_text(GTK_ENTRY(total_prod_orc_entry[atoi(row[ITM_ORC_PROD_COL])]),desconto_prod_orc_gchar);

			if(strlen(row[OBS_ORC_PROD_COL])>=MAX_OBS_LEN){
				row[OBS_ORC_PROD_COL][MAX_OBS_LEN] = '\0';
			}

			obs_prod_orc_gchar[atoi(row[ITM_ORC_PROD_COL])] = malloc(MAX_OBS_LEN);

			strcpy(obs_prod_orc_gchar[atoi(row[ITM_ORC_PROD_COL])],row[OBS_ORC_PROD_COL]);

			obs_prod_orc_buffer[atoi(row[ITM_ORC_PROD_COL])] = gtk_text_view_get_buffer(GTK_TEXT_VIEW(obs_prod_orc_view[atoi(row[ITM_ORC_PROD_COL])]));

			gtk_text_buffer_set_text(GTK_TEXT_BUFFER(obs_prod_orc_buffer[atoi(row[ITM_ORC_PROD_COL])]),

			obs_prod_orc_gchar[atoi(row[ITM_ORC_PROD_COL])],strlen(obs_prod_orc_gchar[atoi(row[ITM_ORC_PROD_COL])]));

		}

		rec_altera_qnt++;
	}

	for(int cont=1;cont<=MAX_PROD_ORC;cont++)
	{
		if(ativos[cont].id==1)
		{
			if(codigo_prod_orc(codigo_prod_orc_entry[cont],cont)){
				cancela_orc();
				return 1;
			}

			if(subgrp_prod_orc(subgrp_prod_orc_cod_entry[cont],cont)){
				cancela_orc();
				return 1;
			}
			if(qnt_prod_orc(qnt_prod_orc_entry[cont],cont)){
				cancela_orc();
				return 1;
			}

			if(preco_prod_orc(preco_prod_orc_entry[cont],cont)){
				cancela_orc();
				return 1;
			}

			if(desconto_prod_orc(desconto_prod_orc_entry[cont],cont)){
				cancela_orc();
				return 1;
			}

			if(obs_prod_orc_fun(NULL,cont)){
				cancela_orc();
				return 1;
			}

			gerar_total_geral();
			ativos_qnt++;
		}

	}
	adicionar_linha_orc();

	recebendo_prod_orc=0;
	ativos_qnt=1;

	if(rec_altera_qnt==1)
	{
		cont=0;

		popup(NULL,"Não há produtos no orçamento...\ndeletado!");
		sprintf(query,"delete from orcamentos where code = %s",tmp_cod_orc);
		erro = enviar_query(query);

		if( erro != 0 )
		{
			popup(NULL,"Erro ao tentar excluir orçamento vazio");
			cancela_orc();
			return 1;
		}

		gtk_widget_set_sensitive(cliente_orc_entry,TRUE);

		return 0;
	}

	gtk_entry_set_text(GTK_ENTRY(codigo_orc_entry),tmp_cod_orc);

	orc_transp_alterar_fun();

	gtk_widget_set_sensitive(alterar_orc_button,FALSE);
	gtk_widget_set_sensitive(codigo_orc_entry,FALSE);
	gtk_widget_set_sensitive(pesquisa_orc,FALSE);
	return 0;
}
