int ped_emitir()
{
	GDateTime  *gdate;
	GTimeZone *timezone;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int ano,mes,dia;
	char query[MAX_QUERY_LEN];
	char nome_cliente[MAX_NAME_LEN];
	char email_cliente[MAX_EMAIL_LEN];
	char formato_preco1[MAX_PRECO_LEN];
	char valor[MAX_PRECO_LEN];
	float parcela;
	int cont=0, titulo_code=0;
	emitindo_ped = 1;
	struct _pedido *pedidoPtr = malloc(sizeof(struct _pedido));

	pedidoPtr->valores = malloc(sizeof(struct _ped_valores));
	pedidoPtr->infos = malloc(sizeof(struct _ped_infos));
	pedidoPtr->parcelas =  malloc(sizeof(struct _ped_parcelas));

	gchar *ped_code = (gchar*)gtk_entry_get_text(GTK_ENTRY(ped_cod_entry));
	if(!strlen(ped_code)){
		gtk_widget_grab_focus(ped_cod_entry);
		popup(NULL,"Insira o código do pedido");
		return 1;
	}

	pedidoPtr->infos->ped_code = atoi(gtk_entry_get_text(GTK_ENTRY(ped_cod_entry)));

	//verificando status do pedido
	sprintf(query,"select status from pedidos where code = %i",pedidoPtr->infos->ped_code);

	res = consultar(query);
	if(res==NULL){
		popup(NULL,"Erro ao buscar valor total nos dados");
		return 1;
	}
	if((row = mysql_fetch_row(res))==NULL){
		popup(NULL,"Pedido não criado");
		return 1;
	}

	if(atoi(row[0])==STATUS_PED_EMIT){
		popup(NULL,"Pedido já emitido");
		return 1;
	}
	if(atoi(row[0])==STATUS_PED_CAN){
		popup(NULL,"Pedido cancelado");
		if(orcamentos.criticar.orc_ped_cancelado == 0)
		{
			return 1;
		}
	}

	if(gtk_combo_box_get_active(GTK_COMBO_BOX(ped_est_combo))<=0){
		popup(NULL,"Selecione um estoque");
		gtk_widget_grab_focus(ped_est_combo);
		return 1;
	}

	sprintf(query,"select cliente,banco,data_mov,tipo_mov,pag_cond from pedidos where code = %i",pedidoPtr->infos->ped_code);

	if(!(res = consultar(query))){
		popup(NULL,"Erro ao buscar infos do pedido");
		return 1;
	}

	if(!(row = mysql_fetch_row(res))){
		popup(NULL,"Sem Informações do pedido");
		return 1;
	}

	if(row[0])
		pedidoPtr->infos->cliente_code = atoi(row[0]);
	if(row[1])
		pedidoPtr->infos->banco = atoi(row[1]);
	if(row[2])
		strcpy(pedidoPtr->infos->data_mov,row[2]);
	if(row[3])
		pedidoPtr->infos->tipo_mov = atoi(row[3]);
	if(row[4])
		pedidoPtr->parcelas->condpag.code = atoi(row[4]);

	sprintf(query,"select nome, email from contatos where terceiro = %i",pedidoPtr->infos->cliente_code);
	if(!(res = consultar(query))){
		popup(NULL,"Erro ao buscar Informações do cliente");
		return 1;
	}

	if(!(row = mysql_fetch_row(res))){
		popup(NULL,"Cliente sem contatos");
		strcpy(nome_cliente,"");
		strcpy(email_cliente,"");
	}else{
		if(row[0])
			strcpy(nome_cliente,row[0]);
		if(row[1])
			strcpy(email_cliente,row[1]);
	}

	//calculando financeiro
	sprintf(query,"select SUM(total),SUM(desconto) from Produto_Orcamento where code = %i",pedidoPtr->infos->ped_code);
	if(!(res = consultar(query))){
		popup(NULL,"Erro ao buscar valor total dos produtos");
		return 1;
	}
	if(!(row = mysql_fetch_row(res))){
		popup(NULL,"Sem valor para faturamento");
		return 1;
	}
	if(row[0])
		pedidoPtr->valores->valor_prds = atof(row[0]);
	if(row[1])
		pedidoPtr->valores->valor_prds_desc = atof(row[1]);

	pedidoPtr->valores->valor_prds_liquido = pedidoPtr->valores->valor_prds - pedidoPtr->valores->valor_prds_desc;

	sprintf(query,"select SUM(vlr_frete),SUM(valor_desconto_frete) from servico_transporte where orcamento = %i",pedidoPtr->infos->ped_code);
	if(!(res = consultar(query)))
	{
		popup(NULL,"Erro ao buscar valor total dos produtos");
		return 1;
	}
	if((row = mysql_fetch_row(res)))
	{
		if(row[0])
			pedidoPtr->valores->valor_frete = atof(row[0]);
		if(row[1])
			pedidoPtr->valores->desconto_frete = atof(row[1]);

		pedidoPtr->valores->valor_frete_liquido = pedidoPtr->valores->valor_frete - pedidoPtr->valores->desconto_frete;
	}

	sprintf(query,"select pc.* from orcamentos as o inner join pag_cond as pc on o.pag_cond = pc.code where o.code = %i",pedidoPtr->infos->ped_code);
	if(!(res = consultar(query)))
	{
		popup(NULL,"Erro ao buscar configurações de parcelas");
		return 1;
	}

	if(!(row = mysql_fetch_row(res)))
	{
		popup(NULL,"Não foi encontrado configuraçoes de financeiro");
		return 1;
	}
	if(row[PAGCND_TIP_COL])
		pedidoPtr->parcelas->condpag.tipo_parc = atoi(row[PAGCND_TIP_COL]);
	if(row[PAGCND_DIAFLAG_COL])
		pedidoPtr->parcelas->condpag.dia_inicial_flag = atoi(row[PAGCND_DIAFLAG_COL]);
	if(row[PAGCND_DIA_COL])
		pedidoPtr->parcelas->condpag.dia_inicial = atoi(row[PAGCND_DIA_COL]);
	if(row[PAGCND_INT_COL])
		pedidoPtr->parcelas->condpag.intervalos = atoi(row[PAGCND_INT_COL]);
	if(row[PAGCOND_QNT_COL])
		pedidoPtr->parcelas->condpag.parcelas_qnt = atoi(row[PAGCOND_QNT_COL]);

	if(sscanf(pedidoPtr->infos->data_mov, "%d-%d-%d", &ano, &mes, &dia) == EOF){
    popup(NULL,"Não foi possivel ler data");
    autologger("Erro no parser de data: %s\n");
		autologger(strerror(errno));
    return 1;
  }

	if(pedidoPtr->parcelas->condpag.dia_inicial_flag == 0)
		pedidoPtr->parcelas->condpag.dia_inicial = dia;

	if(pedidoPtr->parcelas->condpag.dia_inicial<atoi(dia_sys)){
		mes++;
	}

  pedidoPtr->parcelas->total_geral = 0;

	timezone = g_time_zone_new(NULL);
	gdate = g_date_time_new(timezone,ano,mes,pedidoPtr->parcelas->condpag.dia_inicial,0,0,0);

	//em desenvolvimento para emissao de nfe
	//if(criar_xml())
	//	return 1;

	if(pedidoPtr->infos->tipo_mov == VENDA || pedidoPtr->infos->tipo_mov == DEV_COMPRA)
		pedidoPtr->parcelas->tipo_tit = 1;
	if(pedidoPtr->infos->tipo_mov == DEV_VENDA || pedidoPtr->infos->tipo_mov == COMPRA)
		pedidoPtr->parcelas->tipo_tit = 2;

	if(pedidoPtr->parcelas->condpag.tipo_parc != CONDPAG_S_FIN){
		titulo_code = tasker("titulos"),
		sprintf(query,"insert into titulos(code,cliente,pedido,status,qnt_parcelas,tipo_titulo) values(%i,%i,%i,%i,%i,%i)",
		titulo_code,
		pedidoPtr->infos->cliente_code,
		pedidoPtr->infos->ped_code,
		STAT_PENDENTE,
		pedidoPtr->parcelas->condpag.parcelas_qnt,
		pedidoPtr->parcelas->tipo_tit);
		if(enviar_query(query)){
			popup(NULL,"Não foi possivel criar título no financeiro");
		}

		if( pedidoPtr->parcelas->condpag.tipo_parc == CONDPAG_DIAS || pedidoPtr->parcelas->condpag.tipo_parc == CONDPAG_MESES || pedidoPtr->parcelas->condpag.tipo_parc == CONDPAG_DADATA){
				for(int cont=0;cont<pedidoPtr->parcelas->condpag.parcelas_qnt;cont++){

					if(cont==0){
						parcela = (pedidoPtr->valores->valor_prds_liquido/pedidoPtr->parcelas->condpag.parcelas_qnt) + pedidoPtr->valores->valor_frete_liquido;
					}else{
						parcela = (pedidoPtr->valores->valor_prds_liquido/pedidoPtr->parcelas->condpag.parcelas_qnt);
					}

					if(g_date_time_format(gdate,"%Y-%m-%d")){

						if(pedidoPtr->parcelas->condpag.tipo_parc == CONDPAG_DADATA)
							gdate = g_date_time_add_days(gdate,pedidoPtr->parcelas->condpag.intervalos);

						pedidoPtr->parcelas->parcelas_data[cont] = malloc(sizeof(char) * strlen(g_date_time_format(gdate,"%Y-%m-%d")));
						strcpy(pedidoPtr->parcelas->parcelas_data[cont],g_date_time_format(gdate,"%Y-%m-%d"));

						if(pedidoPtr->parcelas->condpag.tipo_parc == CONDPAG_DIAS)
							gdate = g_date_time_add_days(gdate,pedidoPtr->parcelas->condpag.intervalos);
						if(pedidoPtr->parcelas->condpag.tipo_parc == CONDPAG_MESES)
							gdate = g_date_time_add_months(gdate,pedidoPtr->parcelas->condpag.intervalos);

					}else{
						popup(NULL,"Erro ao calcular datas! Verifique financeiro");
					}

					pedidoPtr->parcelas->parcelas_vlr[cont] = parcela;
					pedidoPtr->parcelas->total_geral += pedidoPtr->parcelas->parcelas_vlr[cont];

					sprintf(valor,"%.2f",pedidoPtr->parcelas->parcelas_vlr[cont]);
					sprintf(query,"insert into parcelas_tab(parcelas_id, posicao, banco, data_criacao, data_vencimento, valor) values(%i, %i, %i, '%s', '%s', '%s')",
					titulo_code,
					cont,
					pedidoPtr->infos->banco,
					pedidoPtr->infos->data_mov,
					pedidoPtr->parcelas->parcelas_data[cont],
					valor);
					if(enviar_query(query)){
						popup(NULL,"Não foi possivel criar parcela no financeiro");
					}
				}
		}
		if( pedidoPtr->parcelas->condpag.tipo_parc == CONDPAG_DT_LVR){
			sprintf(query,"select posicao,DATE_FORMAT(data_vencimento,'%%Y-%%m-%%d'), valor from orc_datas_livres where orcamento = %i",pedidoPtr->infos->ped_code);
			if(!(res = consultar(query)))
			{
				popup(NULL,"Erro ao buscar datas das parcelas");
			}else{
				if(!mysql_num_rows(res)){
					popup(NULL,"Não há datas de pagamento no orçamento");
				}
				while((row = mysql_fetch_row(res))){
					if(row[0])
						cont = atoi(row[0]);
					else{
						popup(NULL,"Erro ao receber posicao das parcelas");
						file_logger("Erro gerando posicao/datas livres/emissao do pedido");
						return 1;
					}

					pedidoPtr->parcelas->parcelas_data[cont] = malloc(sizeof(char) * MAX_DATE_LEN);

					if(row[1]){
						strcpy(pedidoPtr->parcelas->parcelas_data[cont],row[1]);
					}else{
						popup(NULL,"Erro ao receber datas das parcelas");
						file_logger("Erro gerando data/parcelas tipo datas livres/emissao do pedido");
						return 1;
					}

					if(row[2]){
						pedidoPtr->parcelas->parcelas_vlr[cont] = atof(row[2]);
					}else{
						popup(NULL,"Erro ao receber valor das parcelas");
						file_logger("Erro gerando valor/tipo datas livres/emissao do pedido");
						return 1;
					}

					sprintf( valor,"%.2f",pedidoPtr->parcelas->parcelas_vlr[cont] );

					sprintf(query,"insert into parcelas_tab(parcelas_id, posicao, banco, data_criacao, data_vencimento, valor) values(%i, %i, %i, '%s', '%s', '%s')",
					titulo_code,
					cont,
					pedidoPtr->infos->banco,
					pedidoPtr->infos->data_mov,
					pedidoPtr->parcelas->parcelas_data[cont],
					valor);
					if(enviar_query(query)){
						popup(NULL,"Não foi possivel criar parcela no financeiro");
					}
				}
			}
		}
	}

	sprintf(formato_preco1,"%.2f",pedidoPtr->valores->valor_prds_liquido + pedidoPtr->valores->valor_frete_liquido);

	sprintf(query,"insert into faturamento(pedido,entrada,cliente,data_mov,tipo_mov) values(%i,%s,%i,'%s',2)",
	pedidoPtr->infos->ped_code,formato_preco1,pedidoPtr->infos->cliente_code,pedidoPtr->infos->data_mov);


	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro ao inserir valor total");
		return 1;
	}

	//calculando estoques

	sprintf(query,"select p.produto, p.unidades from Produto_Orcamento as p inner join pedidos as o on p.code = o.code where o.code = %i",pedidoPtr->infos->ped_code);

	res = consultar(query);

	if(res==NULL)
	{
		popup(NULL,"Erro ao buscar estoque para produto nos dados");
		return 1;
	}

	while((row = mysql_fetch_row(res))!=NULL)
	{
		if(row[0] && row[1]){
			if(pedidoPtr->infos->tipo_mov == VENDA || pedidoPtr->infos->tipo_mov == DEV_COMPRA){

				sprintf(query,"insert into movimento_estoque(estoque,pedido, produto, saidas, cliente, data_mov, tipo_mov) values(%i,%i,%s,%s, %i, '%s', %i)",
				gtk_combo_box_get_active(GTK_COMBO_BOX(ped_est_combo)),
				pedidoPtr->infos->ped_code,
				row[0], row[1], pedidoPtr->infos->cliente_code, pedidoPtr->infos->data_mov, pedidoPtr->infos->tipo_mov);
			}else
			if(pedidoPtr->infos->tipo_mov == DEV_VENDA || pedidoPtr->infos->tipo_mov == COMPRA){
				sprintf(query,"insert into movimento_estoque(estoque,pedido, produto, entradas, cliente, data_mov, tipo_mov) values(%i,%i,%s,%s, %i, '%s', %i)",
				gtk_combo_box_get_active(GTK_COMBO_BOX(ped_est_combo)),
				pedidoPtr->infos->ped_code,
				row[0], row[1], pedidoPtr->infos->cliente_code, pedidoPtr->infos->data_mov, pedidoPtr->infos->tipo_mov);
			}
		}
		else{
			popup(NULL,"Erro ao receber dados para atualizar estoque");
		}

		if(enviar_query(query)!=0)
		{
			popup(NULL,"Erro ao atualizar no estoque");
			return 1;
		}
		cont++;
	}
	if(cont==0){
		popup(NULL,"Estoque sem nenhuma movimentação");
	}

	/*==========================sendo desenvolvido============================*/

	struct _CFe *cfe = get_cupons_from_ped(pedidoPtr);

	if(!cfe){
		if(PopupBinario("O pedido não pode teve o cupom gerado, Cancelar pedido?", "Sim! cancele o pedido", "Não! mantenha pedido sem cupom")){
			ped_cancelar();
			return 0;
		}
	}else{
		autologger("xml de cupom recebido\n");
		char *cupom_path = malloc( sizeof(char) * strlen(CUPONS_XMLS_DIR) + 30);
		sprintf(cupom_path,"%spedido_%i.xml",CUPONS_XMLS_DIR,pedidoPtr->infos->ped_code);

		FILE *xml = fopen(cupom_path,"w");
		if(xml){
			if(cfe->xml){
				autologger("Exportando\n");
				if(xmlDocDump(xml,	cfe->xml) == -1){
					if(PopupBinario("O pedido não pode teve o cupom emitido, Cancelar pedido?", "Sim! cancele o pedido", "Não! mantenha pedido sem cupom")){
						ped_cancelar();
						return 0;
					}else{
						sprintf(query,"update pedidos set status = %i where code = %i", STATUS_PED_EMIT,pedidoPtr->infos->ped_code);
						if(enviar_query(query)!=0){
							popup(NULL,"Erro ao inserir dados para fechar o pedido");
							return 1;
						}
					}
				}
			}
			xmlFreeDoc(cfe->xml);
			fclose (xml);
		}else{
			popup(NULL,"Erro ao abrir arquivo para Cupom, Cancele!");
			return 1;
		}
	}
	/*==========================sendo desenvolvido============================*/

	g_print("tamanho do orc_path %li\n",strlen(ORC_PATH));
	char *orc_path = malloc(sizeof(char) * strlen(ORC_PATH) + 30);
	sprintf(orc_path,"%simp%i.pdf",ORC_PATH,pedidoPtr->infos->ped_code);

	if(!fopen(orc_path,"rb")){
		if(PopupBinario("O orcamento ainda não foi gerado em PDF, deseja gerar?","Sim, Gerar o PDF", "Não desejo enviar o email")){
			if(!gerar_orcs_html( pedidoPtr->infos->ped_code )){
				sprintf(orc_path,"%simp%i.html",ORC_PATH,pedidoPtr->infos->ped_code);
				if(!desenhar_pdf(orc_path))
					enviar_email_orcamento(nome_cliente,email_cliente,orc_path);
			}
		}
	}else{
		sprintf(orc_path,"%ped%i.pdf",ORC_PATH,pedidoPtr->infos->ped_code);
		enviar_email_orcamento(nome_cliente,email_cliente,orc_path);
	}

	emitindo_ped = 0;
	sprintf(query,"update pedidos set status = %i where code = %i", STATUS_PED_EMIT,pedidoPtr->infos->ped_code);
	if(enviar_query(query)!=0){
		popup(NULL,"Erro ao inserir dados para fechar o pedido");
		return 1;
	}

	popup(NULL,"Pedido emitido com sucesso!");
	ped_get_status();
	return 0;
}
