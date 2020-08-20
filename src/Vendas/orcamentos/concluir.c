static int concluir_orc(){
	int cont=0,erro=0;
	int inseridos_na_alteracao=1;
	char valor[MAX_PRECO_LEN];
	char code[MAX_CODE_LEN];
	char query[MAX_QUERY_LEN];
	MYSQL_RES *res;
	MYSQL_ROW row;
	float parcela=0;

	concluindo_orc=1;
	if(observacoes_orc_get()!=0)
		return 1;

	if(codigo_cli_orc()!=0)
		return 1;

	if(operacao_orc_orc()!=0)
		return 1;

	if(codigo_orc())
	  return 1;

	if(codigo_cli_orc())
	  return 1;

	if(orc_transp_codigo_fun())
	  return 1;

	if(orc_transp_cepc())
	  return 1;

	if(orc_transp_logr_fun())
	  return 1;

	if(orc_transp_estado_fun())
	  return 1;

	if(orc_transp_cidadec())
		return 1;

	if(orc_transp_bairroc())
	 	return 1;

	if(orc_pag_tipo_int == CONDPAG_DT_LVR)
		if(concluir_datas_livres())
			return 1;

	orc_infos.cliente_code = atoi(cliente_orc_gchar);
	if(observacoes_orc_gchar)
		strcpy(orc_infos.observacoes,observacoes_orc_gchar);

	for(cont=1;cont<MAX_PROD_ORC;cont++)
	{
		if( ativos[cont].id == 1 && produto_inserido[cont] == 1 )
		{
			if(codigo_prod_orc(codigo_prod_orc_entry[cont],cont)!=0)
				return 1;
			if(subgrp_prod_orc(subgrp_prod_orc_cod_entry[cont],cont)!=0)
				return 1;
			if(qnt_prod_orc(qnt_prod_orc_entry[cont],cont)!=0)
				return 1;
			if(preco_prod_orc(preco_prod_orc_entry[cont],cont)!=0)
				return 1;
			if(desconto_prod_orc(desconto_prod_orc_entry[cont],cont)!=0)
				return 1;
			if(total_prod_orc(total_prod_orc_entry[cont],cont)!=0)
				return 1;
			if(obs_prod_orc_fun(obs_prod_orc_view[cont],cont)!=0)
				return 1;
		}
	}

	if(alterando_orc==0)
	{
		sprintf(query,"select * from orcamentos where code = %s",codigo_orc_gchar);
		vetor = consultar(query);
		if(vetor==NULL)
		{
			popup(NULL,"Erro na verificação da existencia do orcamento");
			autologger("Erro na verificação da existencia do orcamento");
			return 1;
		}

		campos = mysql_fetch_row(vetor);
		if(campos!=NULL)
		{
			popup(NULL,"Orçamento já existente! verifique o código");
			autologger("Erro na query de codigo no orcamento\nTentou usar código de orcamento já usado\n");
			gtk_widget_grab_focus(codigo_orc_entry);
			return 1;
		}

		sprintf(query,"insert into orcamentos( code, tipo_mov, vendedor, cliente, pag_cond, dia, observacoes) values(%s,%i,1,%s,%i,STR_TO_DATE('%s','%%d/%%m/%%Y'),'%s');",
		codigo_orc_gchar,operacao_orc_int,cliente_orc_gchar,pag_cond ,data_sys,observacoes_orc_gchar);

		erro = enviar_query(query);
		if(erro != 0 )
		{
			popup(NULL,"Erro ao tentar concluir orçamento");
			autologger("Erro ao tentar concluir orçamento");
			return 1;
		}
	}

	for(cont=1;cont<MAX_PROD_ORC;cont++)
	{
		if( ativos[cont].id == 1 && produto_inserido[cont] == 1 )
		{

			if(codigo_cli_orc()!=0)
				return 1;
			if(codigo_prod_orc(codigo_prod_orc_entry[cont],cont)!=0)
				return 1;
			if(subgrp_prod_orc(subgrp_prod_orc_cod_entry[cont],cont)!=0)
				return 1;
			if(qnt_prod_orc(qnt_prod_orc_entry[cont],cont)!=0)
				return 1;
			if(preco_prod_orc(preco_prod_orc_entry[cont],cont)!=0)
				return 1;
			if(desconto_prod_orc(desconto_prod_orc_entry[cont],cont)!=0)
				return 1;
			if(total_prod_orc(total_prod_orc_entry[cont],cont)!=0)
				return 1;
			if(obs_prod_orc_fun(obs_prod_orc_view[cont],cont)!=0)
				return 1;

			if(strlen(ativos[cont].desconto_c)<=0)
			{
				strcpy(ativos[cont].desconto_c,"0.0");
			}

			if(alterando_orc==0)
			{
				sprintf(query,"insert into Produto_Orcamento(code,item,produto,subgrupo,unidades,valor_unit,valor_orig,tipodesc,desconto,total,observacoes) values(%s,%i,%i,%i,%s,%s,%i,%i,%s,%s,'%s');",codigo_orc_gchar, cont,ativos[cont].produto, ativos[cont].subgrupo, ativos[cont].qnt_c, ativos[cont].preco_c, valor_orig[cont], ativos[cont].tipodesc, ativos[cont].desconto_c ,ativos[cont].total_c,obs_prod_orc_gchar[cont]);
				erro = enviar_query(query);
				if(erro != 0 )
				{
					popup(NULL,"Erro ao tentar gerar orçamento");
					autologger("Erro ao tentar gerar orçamento");
					return 1;
				}
			}
			else
			{
				if(inseridos_na_alteracao<rec_altera_qnt)
				{
					g_print("Atualizando %i\n",cont);
					sprintf(query,"update Produto_Orcamento set produto = %i, subgrupo = %i, unidades = %s, valor_unit = %s, valor_orig = %i, tipodesc = %i , desconto = %s, total = %s, observacoes = '%s' where code = %s and item = %i",ativos[cont].produto, ativos[cont].subgrupo, ativos[cont].qnt_c, ativos[cont].preco_c, valor_orig[cont], ativos[cont].tipodesc, ativos[cont].desconto_c ,ativos[cont].total_c,obs_prod_orc_gchar[cont],codigo_orc_gchar,cont);
					erro = enviar_query(query);
					if(erro != 0 )
					{
						popup(NULL,"Erro ao tentar gerar orçamento");
						autologger("Erro ao tentar gerar orçamento");
						return 1;
					}
				}
				else
				{
					sprintf(query,"insert into Produto_Orcamento(code,item,produto,subgrupo,unidades,valor_unit,valor_orig,desconto,total,observacoes) values(%s,%i,%i,%i,%s,%s,%i,%s,%s,'%s');",codigo_orc_gchar,cont,ativos[cont].produto, ativos[cont].subgrupo, ativos[cont].qnt_c, ativos[cont].preco_c, valor_orig[cont], ativos[cont].desconto_c ,ativos[cont].total_c,obs_prod_orc_gchar[cont]);
					erro = enviar_query(query);
				}
				inseridos_na_alteracao++;
			}
		}
	}

	if(orc_com_entrega){
		if(orc_transp_concluir_fun())
			return 1;
	}

	sprintf(query,"select sum(total),sum(desconto) from Produto_Orcamento where code = %s",codigo_orc_gchar);
	if(!(res = consultar(query))){
		popup(NULL,"Não foi possível receber valores");
		return 1;
	}
	if(!(row=mysql_fetch_row(res))){
		popup(NULL,"Não Há valores totais para receber");
		return 1;
	}
	if(row[0])
		orc_valores.valor_prds = atof(row[0]);
	if(row[1])
		orc_valores.valor_prds_desc = atof(row[1]);

	orc_valores.valor_prds_liquido = orc_valores.valor_prds - orc_valores.valor_prds_desc;

	sprintf(query,"select sum(vlr_frete),sum(valor_desconto_frete) from servico_transporte where code = %s",codigo_orc_gchar);
	if(!(res = consultar(query))){
		popup(NULL,"Não foi possível receber valores");
		return 1;
	}
	if(!(row=mysql_fetch_row(res))){
		popup(NULL,"Não Há valores totais para receber");
		return 1;
	}
	if(row[0])
		orc_valores.valor_frete = atof(row[0]);
	if(row[1])
		orc_valores.desconto_frete = atof(row[1]);

	orc_valores.valor_frete_liquido = orc_valores.valor_frete - orc_valores.desconto_frete;

	orc_valores.valor_total  = orc_valores.valor_prds_liquido + orc_valores.valor_frete_liquido;
	orc_valores.desconto_total = orc_valores.valor_prds_desc + orc_valores.desconto_frete;

	sprintf(valor,"%.2f",orc_valores.valor_total);
	sprintf(query,"update orcamentos set tipo_mov = %i, cliente = %i, dia = STR_TO_DATE('%s','%%d/%%m/%%Y'), pag_cond = %i, total = %s, observacoes = '%s' where code = %s",
	operacao_orc_int,
	orc_infos.cliente_code,
	data_sys,
	orc_parcelas.pagcond_code,
	valor,
	orc_infos.observacoes,
	codigo_orc_gchar);

	erro = enviar_query(query);
	if(erro != 0 )
	{

		popup(NULL,"Erro ao tentar calcular total");
		autologger("Erro ao tentar calcular total");
		return 1;
	}

	finalizacao_orc();

	cancela_orc();

	popup(NULL,"Orcamento concluido");

	sprintf(code,"%i",tasker("orcamentos"));

	gtk_entry_set_text(GTK_ENTRY(codigo_orc_entry),code);
	gtk_widget_set_sensitive(cliente_orc_entry,TRUE);
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_entry),"");
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_name_entry),"");
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_end_entry),"");
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_tel_entry),"");

	gtk_widget_grab_focus(cliente_orc_entry);
	return 0;
}
