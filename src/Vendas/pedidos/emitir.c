int emitir_ped()
{
	GDateTime  *gdate;
	GTimeZone *timezone;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int ano,mes,dia;
	char query[MAX_QUERY_LEN];
	char formato_preco1[MAX_PRECO_LEN];
	char valor[MAX_PRECO_LEN];
	float parcela;
	int cont=0, titulo_code=0;

	if(strlen(gtk_entry_get_text(GTK_ENTRY(ped_cod_entry)))<=0)
	{
		gtk_widget_grab_focus(ped_cod_entry);
		popup(NULL,"Insira o código do orcamento");
		return 1;
	}

	ped_infos.ped_code = atoi(gtk_entry_get_text(GTK_ENTRY(ped_cod_entry)));

	//verificando status do pedido
	sprintf(query,"select status from pedidos where code = %i",ped_infos.ped_code);

	res = consultar(query);
	if(res==NULL)
	{
		popup(NULL,"Erro ao buscar valor total nos dados");
		return 1;
	}
	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Pedido não criado");
		return 1;
	}

	if(atoi(row[0])==STATUS_PED_EMIT)
	{
		popup(NULL,"Pedido já emitido");
		return 1;
	}
	if(atoi(row[0])==STATUS_PED_CAN)
	{
		popup(NULL,"Pedido cancelado");
		if(orcamentos.criticar.orc_ped_cancelado == 0)
		{
			return 1;
		}
	}

	if(gtk_combo_box_get_active(GTK_COMBO_BOX(ped_est_combo))<=0)
	{
		popup(NULL,"Selecione um estoque");
		gtk_widget_grab_focus(ped_est_combo);
		return 1;
	}

	sprintf(query,"select cliente,data_mov,tipo_mov,pag_cond from pedidos where code = %i",ped_infos.ped_code);

	if(!(res = consultar(query)))
	{
		popup(NULL,"Erro ao buscar infos do pedido");
		return 1;
	}

	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Sem Informações do pedido");
		return 1;
	}

	if(row[0])
		ped_infos.cliente_code = atoi(row[0]);
	if(row[1])
		strcpy(ped_infos.data_mov,row[1]);
	if(row[2])
		ped_infos.tipo_mov = atoi(row[2]);
	if(row[3])
		ped_parcelas.pagcond_code = atoi(row[3]);

	//calculando financeiro
	sprintf(query,"select SUM(total),SUM(desconto) from Produto_Orcamento where code = %i",ped_infos.ped_code);
	if(!(res = consultar(query)))
	{
		popup(NULL,"Erro ao buscar valor total dos produtos");
		return 1;
	}
	if(!(row = mysql_fetch_row(res)))
	{
		popup(NULL,"Sem valor para faturamento");
		return 1;
	}
	if(row[0])
		ped_valores.valor_prds = atof(row[0]);
	if(row[1])
		ped_valores.valor_prds_desc = atof(row[1]);
	ped_valores.valor_prds_liquido = ped_valores.valor_prds - ped_valores.valor_prds_desc;

	sprintf(query,"select SUM(vlr_frete),SUM(valor_desconto_frete) from servico_transporte where orcamento = %i",ped_infos.ped_code);
	if(!(res = consultar(query)))
	{
		popup(NULL,"Erro ao buscar valor total dos produtos");
		return 1;
	}
	if((row = mysql_fetch_row(res)))
	{
		if(row[0])
			ped_valores.valor_frete = atof(row[0]);
		if(row[1])
			ped_valores.desconto_frete = atof(row[1]);
		ped_valores.valor_frete_liquido = ped_valores.valor_frete - ped_valores.desconto_frete;
	}

	sprintf(query,"select pc.tipo, pc.dia_fixo_flag, pc.init_dia, pc.intervalos, pc.qnt_parcelas from orcamentos as o inner join pag_cond as pc on o.pag_cond = pc.code where o.code = %i",ped_infos.ped_code);
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
	if(row[0])
		ped_parcelas.tipo_parc = atoi(row[0]);
	if(row[1])
		ped_parcelas.dia_inicial_flag = atoi(row[1]);
	if(row[2])
		ped_parcelas.dia_inicial = atoi(row[2]);
	if(row[3])
		ped_parcelas.intervalos = atoi(row[3]);
	if(row[4])
		ped_parcelas.parcelas_qnt = atoi(row[4]);

	if(sscanf(ped_infos.data_mov, "%d-%d-%d", &ano, &mes, &dia) == EOF)
  {
    popup(NULL,"Não foi possivel ler data");
    g_print("Erro no parser de data: %s\n",strerror(errno));
    return 1;
  }

	if(ped_parcelas.dia_inicial_flag == 0)
		ped_parcelas.dia_inicial = dia;

	if(ped_parcelas.dia_inicial<atoi(dia_sys)){
		mes++;
	}

  ped_parcelas.total_geral = 0;

	timezone = g_time_zone_new(NULL);
	gdate = g_date_time_new(timezone,ano,mes,ped_parcelas.dia_inicial,0,0,0);

	gdate = g_date_time_new(timezone,ano,mes,ped_parcelas.dia_inicial,0,0,0);

	if(criar_xml())
		return 1;

	if(ped_infos.tipo_mov == VENDA || ped_infos.tipo_mov == DEV_COMPRA)
		ped_parcelas.tipo_tit = 1;
	if(ped_infos.tipo_mov == DEV_VENDA || ped_infos.tipo_mov == COMPRA)
		ped_parcelas.tipo_tit = 2;

	titulo_code = tasker("titulos"),
	sprintf(query,"insert into titulos(code,cliente,pedido,status,qnt_parcelas,tipo_titulo) values(%i,%i,%i,0,%i,%i)",
	titulo_code,
	ped_infos.cliente_code,
	ped_infos.ped_code,
	ped_parcelas.parcelas_qnt,
	ped_parcelas.tipo_tit);
	if(enviar_query(query)){
		popup(NULL,"Não foi possivel criar título no financeiro");
	}

	if( ped_parcelas.tipo_parc == CONDPAG_DIAS || ped_parcelas.tipo_parc == CONDPAG_MESES ){
			for(int cont=0;cont<ped_parcelas.parcelas_qnt;cont++){

				if(cont==0){
					parcela = (ped_valores.valor_prds_liquido/ped_parcelas.parcelas_qnt) + ped_valores.valor_frete_liquido;
				}else{
					parcela = (ped_valores.valor_prds_liquido/ped_parcelas.parcelas_qnt);
				}

				if(g_date_time_format(gdate,"%Y-%m-%d")){
					ped_parcelas.parcelas_data[cont] = malloc(strlen(g_date_time_format(gdate,"%Y-%m-%d")));
					strcpy(ped_parcelas.parcelas_data[cont],g_date_time_format(gdate,"%Y-%m-%d"));
				}else{
					popup(NULL,"Erro ao calcular datas! Verifique financeiro");
				}

				ped_parcelas.parcelas_vlr[cont] = parcela;
				ped_parcelas.total_geral += ped_parcelas.parcelas_vlr[cont];

				sprintf(valor,"%.2f",ped_parcelas.parcelas_vlr[cont]);
				sprintf(query,"insert into parcelas_tab(parcelas_id, posicao, data_criacao, data_vencimento, valor) values(%i, %i, '%s', '%s', '%s')",
				titulo_code,
				cont,
				ped_infos.data_mov,
				ped_parcelas.parcelas_data[cont],
				valor);
				if(enviar_query(query)){
					popup(NULL,"Não foi possivel criar parcela no financeiro");
				}
				if(ped_parcelas.tipo_parc == CONDPAG_DIAS)
					gdate = g_date_time_add_days(gdate,ped_parcelas.intervalos);
				else
				if(ped_parcelas.tipo_parc == CONDPAG_MESES)
					gdate = g_date_time_add_months(gdate,ped_parcelas.intervalos);
			}
	}
	if( ped_parcelas.tipo_parc == CONDPAG_DT_LVR){
		sprintf(query,"select posicao,DATE_FORMAT(data_vencimento,'%%Y-%%m-%%d'), valor from orc_datas_livres where orcamento = %i",ped_infos.ped_code);
		if(!(res = consultar(query)))
		{
			popup(NULL,"Erro ao buscar datas das parcelas");
		}else{
			if(!mysql_num_rows(res)){
				popup(NULL,"Não há datas de pagamento no orçamento");
			}
			while((row = mysql_fetch_row(res))){
				cont = atoi(row[0]) - 1;
				ped_parcelas.parcelas_data[cont] = malloc(MAX_DATE_LEN);
				strcpy(ped_parcelas.parcelas_data[cont],row[1]);

				ped_parcelas.parcelas_vlr[cont] = atof(row[2]);
				sprintf( valor,"%.2f",ped_parcelas.parcelas_vlr[cont] );

				sprintf(query,"insert into parcelas_tab(parcelas_id, posicao, data_criacao, data_vencimento, valor) values(%i, %i, '%s', '%s', '%s')",
				titulo_code,
				cont,
				ped_infos.data_mov,
				ped_parcelas.parcelas_data[cont],
				valor);
				if(enviar_query(query)){
					popup(NULL,"Não foi possivel criar parcela no financeiro");
				}
			}
		}
	}

	//tipo_mov
	//0 = manual
	//1 = venda
	//2 = compra
	//3 = devolucao venda
	//4 = devolucao compra

	sprintf(formato_preco1,"%.2f",ped_valores.valor_prds_liquido + ped_valores.valor_frete_liquido);

	sprintf(query,"insert into faturamento(pedido,entrada,cliente,data_mov,tipo_mov) values(%i,%s,%i,'%s',2)",
	ped_infos.ped_code,formato_preco1,ped_infos.cliente_code,ped_infos.data_mov);


	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro ao inserir valor total");
		return 1;
	}

	//calculando estoques

	sprintf(query,"select p.produto, p.subgrupo, p.unidades from Produto_Orcamento as p inner join pedidos as o on p.code = o.code where o.code = %i",ped_infos.ped_code);

	res = consultar(query);

	if(res==NULL)
	{
		popup(NULL,"Erro ao buscar estoque para produto nos dados");
		return 1;
	}

	while((row = mysql_fetch_row(res))!=NULL)
	{
		if(ped_infos.tipo_mov == VENDA || ped_infos.tipo_mov == DEV_COMPRA){
			sprintf(query,"insert into movimento_estoque(estoque,pedido, produto, subgrupo, saidas, cliente, data_mov, tipo_mov) values(%i,%i,%s,%s,%s, %i, '%s', %i)",
			gtk_combo_box_get_active(GTK_COMBO_BOX(ped_est_combo)),
			ped_infos.ped_code,
			row[0], row[1], row[2], ped_infos.cliente_code, ped_infos.data_mov, ped_infos.tipo_mov);
		}else
		if(ped_infos.tipo_mov == DEV_VENDA || ped_infos.tipo_mov == COMPRA){
			sprintf(query,"insert into movimento_estoque(estoque,pedido, produto, subgrupo, entradas, cliente, data_mov, tipo_mov) values(%i,%i,%s,%s,%s, %i, '%s', %i)",
			gtk_combo_box_get_active(GTK_COMBO_BOX(ped_est_combo)),
			ped_infos.ped_code,
			row[0], row[1], row[2], ped_infos.cliente_code, ped_infos.data_mov, ped_infos.tipo_mov);
		}
		if(enviar_query(query)!=0)
		{
			popup(NULL,"Erro ao dar entrada no estoque");
			return 1;
		}
		cont++;
	}
	if(cont==0)
	{
		popup(NULL,"Estoque sem nenhuma movimentação");
	}

	sprintf(query,"update pedidos set status = 1 where code = %i",ped_infos.ped_code);

	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro ao inserir dados para fechar o pedido");
		return 1;
	}
	popup(NULL,"Pedido emitido com sucesso!");
	return 0;
}
