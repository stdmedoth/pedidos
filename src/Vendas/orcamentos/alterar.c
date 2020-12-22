static int altera_orc()
{
	char query[MAX_QUERY_LEN];
	int cont=1,erro=0;
	char code[MAX_CODE_LEN];
	MYSQL_RES *res, *res2;
	MYSQL_ROW row, row2;
	GtkTextBuffer *buffer;
	char tmp_cod_orc[MAX_CODE_LEN],*parc_qnt_gchar;

	g_print("Iniciando alterar\n");

	alterando_orc=1;
	rec_altera_qnt=1;
	recebendo_prod_orc=1;

	if(codigo_orc()){
		cancela_orc();
		return 1;
	}

	strcpy(tmp_cod_orc, codigo_orc_gchar);

	cancela_orc();

	sprintf(query,"select status from pedidos where code = %s",tmp_cod_orc);
	if(!(res = consultar(query))){
		popup(NULL,"Erro ao buscar vinculos de pedidos");
		cancela_orc();
		return 1;
	}

	if((row = mysql_fetch_row(res))){
		popup(NULL,"Existe um pedido para este orçamento");
		gtk_widget_set_sensitive(concluir_orc_button, FALSE);
		gtk_widget_set_sensitive(pedido_orc_button, FALSE);
		gtk_widget_set_sensitive(excluir_orc_button, FALSE);
	}

	alterando_orc=1;
	rec_altera_qnt=1;
	recebendo_prod_orc=1;

	if(observacoes_orc_get()!=0){
		cancela_orc();
		return 1;
	}
	//buscando informações basicas de orçamentos
	sprintf(query,"select cliente, tipo_mov, pag_cond, (%s%s), total, observacoes, banco from orcamentos where code = %s",DATE_QUERY,tmp_cod_orc,tmp_cod_orc);

	if((res = consultar(query))==NULL){
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

	orc_parcelas.condpag.code = atoi(row[2]);

	gtk_widget_activate(cliente_orc_entry);
	gtk_widget_activate(orc_pag_cond_entry);

	if(row[4] && strlen(row[5])){
		buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacoes_orc));
		gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer),row[5],strlen(row[5]));
	}
	gtk_entry_set_text(GTK_ENTRY(orc_bnc_code_entry),row[6]);

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
		alterando_transp = 0;
		orc_com_entrega = 0;
	}else{

		if(row[TRANSP_TRSP_COL]!=NULL)
			if(!atoi(row[TRANSP_TRSP_COL])){
				alterando_transp = 0;
				orc_com_entrega = 0;
				return 1;
			}

		alterando_transp = 1;
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
		gtk_entry_set_text(GTK_ENTRY(orc_transp_valor_frete_entry),row[TRANP_VLR_COL]);
		gtk_entry_set_text(GTK_ENTRY(orc_transp_desconto_frete_entry),row[TRANP_VLR_DESC_COL]);

		gtk_widget_activate(orc_transp_valor_frete_entry);
		gtk_widget_activate(orc_transp_desconto_frete_entry);
	}

	sprintf(query,"select * from Produto_Orcamento where code = %i",atoi(tmp_cod_orc));
	if((res = consultar(query))==NULL){
		popup(NULL,"Erro nos itens do orçamento");
		cancela_orc();
		return 1;
	}

	for(int cont=1;cont<MAX_PROD_ORC;cont++){
		if(ativos[cont].id==1){
			tirar_linha(cont);
		}
	}

	while((row = mysql_fetch_row(res))!=NULL)
	{

		while (g_main_context_pending(NULL))
			g_main_context_iteration(NULL,FALSE);

		if(!row[ORC_PROD_ITM_COL]){
			popup(NULL,"Erro na identificação em um dos itens, verifique");
			continue;
		}

		itens_qnt = atoi(row[ORC_PROD_ITM_COL]);

		adicionar_linha_orc();

		if(GTK_IS_ENTRY(codigo_prod_orc_entry[atoi(row[ORC_PROD_ITM_COL])]))
		{

			loging_alteracao(row);

			if(row[ORC_PROD_PROD_COL]){
				codigo_prod_orc_gchar = malloc(strlen(row[ORC_PROD_PROD_COL]));
				strcpy(codigo_prod_orc_gchar,row[ORC_PROD_PROD_COL]);
				gtk_entry_set_text(GTK_ENTRY(codigo_prod_orc_entry[atoi(row[ORC_PROD_ITM_COL])]),codigo_prod_orc_gchar);
				ativos[atoi(row[ORC_PROD_ITM_COL])].produto = atoi(row[ORC_PROD_PROD_COL]);
			}

			if(row[ORC_PROD_VLR_ORIG_COL]){
				MYSQL_RES *vetor;
				MYSQL_ROW campos;

				gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(orig_preco_prod_orc_combo[atoi(row[ORC_PROD_ITM_COL])]));
				gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(orig_preco_prod_orc_combo[atoi(row[ORC_PROD_ITM_COL])]),ORIGPRC_NUL, ORC_ORIGPRC_NUL,"Origem");
				gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(orig_preco_prod_orc_combo[atoi(row[ORC_PROD_ITM_COL])]),ORIGPRC_CLI, ORC_ORIGPRC_CLI,"Cliente");
				gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(orig_preco_prod_orc_combo[atoi(row[ORC_PROD_ITM_COL])]),ORIGPRC_PROD, ORC_ORIGPRC_PROD,"Produto");
				gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(orig_preco_prod_orc_combo[atoi(row[ORC_PROD_ITM_COL])]),ORIGPRC_OPER, ORC_ORIGPRC_OPER,"Operador");
				sprintf(query,"select * from precos where produto = %s", codigo_prod_orc_gchar);
				if(!(vetor = consultar(query))){
					popup(NULL,"Não foi possível consultar precos para o produto");
					return 1;
				}
				int combo_position = ORIGPRC_COLS_QNT;
				while((campos = mysql_fetch_row(vetor))){
					gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(orig_preco_prod_orc_combo[atoi(row[ORC_PROD_ITM_COL])]), combo_position, campos[PRC_CODE_COL],campos[PRC_NOME_COL]);
					combo_position++;
				}
				gtk_combo_box_set_active(GTK_COMBO_BOX(orig_preco_prod_orc_combo[atoi(row[ORC_PROD_ITM_COL])]),atoi(row[ORC_PROD_VLR_ORIG_COL]));
				valor_orig[atoi(row[ORC_PROD_ITM_COL])] = atoi(row[ORC_PROD_VLR_ORIG_COL]);
			}

			if(row[ORC_PROD_UND_COL]){
				qnt_prod_orc_gchar = malloc(strlen(row[ORC_PROD_UND_COL]));
				strcpy(qnt_prod_orc_gchar,row[ORC_PROD_UND_COL]);
				gtk_entry_set_text(GTK_ENTRY(qnt_prod_orc_entry[atoi(row[ORC_PROD_ITM_COL])]),qnt_prod_orc_gchar);
			}

			if(row[ORC_PROD_TIP_DESC_COL])
				gtk_combo_box_set_active(GTK_COMBO_BOX(tipodesconto_prod_orc_combo[atoi(row[ORC_PROD_ITM_COL])]),atoi(row[ORC_PROD_TIP_DESC_COL]));

			if(row[ORC_PROD_VLR_COL]){
				preco_prod_orc_gchar = malloc(strlen(row[ORC_PROD_VLR_COL]));
				strcpy(preco_prod_orc_gchar,row[ORC_PROD_VLR_COL]);
				gtk_entry_set_text(GTK_ENTRY(preco_prod_orc_entry[atoi(row[ORC_PROD_ITM_COL])]),preco_prod_orc_gchar);
			}

			if(row[ORC_PROD_DESC_COL]){
				desconto_prod_orc_gchar = malloc(strlen(row[ORC_PROD_DESC_COL]));
				strcpy(desconto_prod_orc_gchar,row[ORC_PROD_DESC_COL]);
				gtk_entry_set_text(GTK_ENTRY(desconto_prod_orc_entry[atoi(row[ORC_PROD_ITM_COL])]),desconto_prod_orc_gchar);
			}

			if(row[ORC_PROD_TOTAL_COL]){
				desconto_prod_orc_gchar = malloc(strlen(row[ORC_PROD_TOTAL_COL]));
				strcpy(desconto_prod_orc_gchar,row[ORC_PROD_TOTAL_COL]);
				gtk_entry_set_text(GTK_ENTRY(total_prod_orc_entry[atoi(row[ORC_PROD_ITM_COL])]),desconto_prod_orc_gchar);
			}

			if(row[ORC_PROD_OBS_COL]){
				if(strlen(row[ORC_PROD_OBS_COL])>=MAX_OBS_LEN){
					row[ORC_PROD_OBS_COL][MAX_OBS_LEN] = '\0';
				}
				obs_prod_orc_gchar[atoi(row[ORC_PROD_ITM_COL])] = malloc(MAX_OBS_LEN);
				strcpy(obs_prod_orc_gchar[atoi(row[ORC_PROD_ITM_COL])],row[ORC_PROD_OBS_COL]);
				obs_prod_orc_buffer[atoi(row[ORC_PROD_ITM_COL])] = gtk_text_view_get_buffer(GTK_TEXT_VIEW(obs_prod_orc_view[atoi(row[ORC_PROD_ITM_COL])]));
				gtk_text_buffer_set_text(GTK_TEXT_BUFFER(obs_prod_orc_buffer[atoi(row[ORC_PROD_ITM_COL])]),
				obs_prod_orc_gchar[atoi(row[ORC_PROD_ITM_COL])],strlen(obs_prod_orc_gchar[atoi(row[ORC_PROD_ITM_COL])]));
			}
		}

		rec_altera_qnt++;
	}

	for(int cont=1;cont<MAX_PROD_ORC;cont++)
	{
		while (g_main_context_pending(NULL))
			g_main_context_iteration(NULL,FALSE);

		if(ativos[cont].id==1){

			if(codigo_prod_orc(codigo_prod_orc_entry[cont],cont)){
				g_print("Erro ao receber código do produto\n");
				cancela_orc();
				return 1;
			}

			if(qnt_prod_orc(qnt_prod_orc_entry[cont],cont)){
				g_print("Erro ao receber quantidade do produto\n");
				cancela_orc();
				return 1;
			}

			if(preco_prod_orc(preco_prod_orc_entry[cont],cont)){
				g_print("Erro ao receber preco do produto\n");
				cancela_orc();
				return 1;
			}

			if(desconto_prod_orc(desconto_prod_orc_entry[cont],cont)){
				g_print("Erro ao receber desconto do produto\n");
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

	sprintf(query,"select tipo from pag_cond where code = %i",orc_parcelas.condpag.code);
	if(!(res2 = consultar(query)))
	{
		popup(NULL,"Erro ao buscar condição de pagamentos parcelas");
		cancela_orc();
		return 1;
	}
	if(!(row2 = mysql_fetch_row(res2))){
		popup(NULL,"A condição de pagamento do orçamento não existe");
	}
	else{
		orc_pag_tipo_int = atoi(row2[0]);
		if(orc_pag_tipo_int == CONDPAG_DT_LVR){
			sprintf(query,"select posicao,DATE_FORMAT(data_vencimento,'%%d/%%m/%%y'), valor from orc_datas_livres where orcamento = %s",tmp_cod_orc);
			if(!(res2 = consultar(query)))
			{
				popup(NULL,"Erro ao buscar datas das parcelas");
				return 1;
			}
			while((row2 = mysql_fetch_row(res2))){
				cont = atoi(row2[0]);

				datas_lives_str[cont].datas = malloc(MAX_DATE_LEN);
				strcpy(datas_lives_str[cont].datas,row2[1]);
				datas_lives_str[cont].vlrs = atof(row2[2]);
			}
			orc_parcelas.condpag.parcelas_qnt = mysql_num_rows(res2);
			orc_pag_parc_qnt_int = orc_parcelas.condpag.parcelas_qnt;
			parc_qnt_gchar = malloc(12);
			sprintf(parc_qnt_gchar,"%i",orc_parcelas.condpag.parcelas_qnt);
			gtk_entry_set_text(GTK_ENTRY(orc_pag_datas_parcqnt),parc_qnt_gchar);
			gtk_widget_activate(orc_pag_datas_parcqnt);

			if(!orc_parcelas.condpag.parcelas_qnt){
				popup(NULL,"Não há datas de pagamento no orçamento");
			}
		}
	}

	if(rec_altera_qnt==1)
	{
		cont=0;

		popup(NULL,"Não há produtos no orçamento...\ndeletado!");
		sprintf(query,"delete from orcamentos where code = %s",tmp_cod_orc);
		if( enviar_query(query) ){
			popup(NULL,"Erro ao tentar excluir orçamento vazio");
			cancela_orc();
			return 1;
		}
		cancela_orc();
		return 0;
	}

	adicionar_linha_orc();

	ativos_qnt=1;

	orc_transp_alterar_fun();
	recebendo_prod_orc=0;
	gtk_entry_set_text(GTK_ENTRY(codigo_orc_entry),tmp_cod_orc);

	gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),0);
	gtk_widget_set_sensitive(alterar_orc_button,FALSE);
	gtk_widget_set_sensitive(codigo_orc_entry,FALSE);
	gtk_widget_set_sensitive(pesquisa_orc,FALSE);
	return 0;
}

void loging_alteracao(MYSQL_ROW row){

	//arquivando as informacoes da alteração
	file_logger("\n\nAdicionando item à alteração: ");
	file_logger("Dados:\n");

	file_logger("codigo:\n");
	if(row[ORC_PROD_COD_COL])
		file_logger(row[ORC_PROD_COD_COL]);
	else
		file_logger("Erro no código do orcamento");

	file_logger("item:\n");
	if(row[ORC_PROD_ITM_COL])
		file_logger(row[ORC_PROD_ITM_COL]);
	else
		file_logger("Erro no código do item");

	file_logger("produto:\n");
	if(row[ORC_PROD_PROD_COL])
		file_logger(row[ORC_PROD_PROD_COL]);
	else
		file_logger("Erro no código do produto");

	file_logger("unidades:\n");
	if(row[ORC_PROD_UND_COL])
		file_logger(row[ORC_PROD_UND_COL]);
	else
		file_logger("Erro na unidade do produto");

	file_logger("valor_unit:\n");
	if(row[ORC_PROD_VLR_COL])
		file_logger(row[ORC_PROD_VLR_COL]);
	else
		file_logger("Erro no valor do produto");

	file_logger("valor_orig:\n");
	if(row[ORC_PROD_VLR_ORIG_COL])
		file_logger(row[ORC_PROD_VLR_ORIG_COL]);
	else
		file_logger("Erro no valor origem do produto");

	file_logger("tipodesc:\n");
	if(row[ORC_PROD_TIP_DESC_COL])
		file_logger(row[ORC_PROD_TIP_DESC_COL]);
	else
		file_logger("Erro no tipo de desconto");

	file_logger("desconto:\n");
	if(row[ORC_PROD_DESC_COL])
		file_logger(row[ORC_PROD_DESC_COL]);
	else
		file_logger("Erro no valor do desconto");

	file_logger("total:\n\n");
	if(row[ORC_PROD_TOTAL_COL])
		file_logger(row[ORC_PROD_TOTAL_COL]);
	else
		file_logger("Erro no valor Total");

	file_logger("Observacao:\n\n");
	if(row[ORC_PROD_OBS_COL])
		file_logger(row[ORC_PROD_OBS_COL]);
	else
		file_logger("Erro no campo observacao");

	return ;
}
