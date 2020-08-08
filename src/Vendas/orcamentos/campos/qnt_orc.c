int qnt_prod_orc(GtkWidget *widget,int posicao)
{
	int desconto_prod_orc(GtkWidget*,int);
	char query[MAX_QUERY_LEN];
	int tipodesc;

	MYSQL_RES *vetor;
	MYSQL_ROW campos,row;

	ativos[posicao].qnt_f = 0;

	switch(valor_orig[posicao])
	{

		case 0:
			if(produto_inserido[posicao] == 1)
			{
				popup(NULL,"Selecione a origem do preço");
			}
			gtk_widget_grab_focus(orig_preco_prod_orc_combo[posicao]);
			return 1;

		case 1:
			if(codigo_prod_orc(NULL,posicao)!=0)
				return 1;

			if(subgrp_prod_orc(NULL,posicao)!=0)
				return 1;

			if(tipo_pag==1)
				sprintf(query, "select valor_fat from preco_grupo where produto = %s and grupo = %s", codigo_prod_orc_gchar, subgrp_prod_orc_cod_gchar);
			else
			if(tipo_pag==2)
				sprintf(query, "select valor_vist from preco_grupo where produto = %s and grupo = %s ", codigo_prod_orc_gchar, subgrp_prod_orc_cod_gchar);
			else
			{
				popup(NULL,"Selecione o tipo de pagamento");
				gtk_widget_grab_focus(orc_pag_cond_entry);
				return 1;
			}

			vetor = consultar(query);
			if(vetor == NULL)
			{
				return 1;
			}
			if((campos = mysql_fetch_row(vetor))==NULL)
			{
				popup(NULL,"Produto sem preço vinculado à tabela");
				gtk_widget_grab_focus(orig_preco_prod_orc_combo[posicao]);
				return 1;
			}
			gtk_entry_set_text(GTK_ENTRY(preco_prod_orc_entry[posicao]),campos[0]);
			break;

		case 2:
			if(codigo_cli_orc()!=0)
				return 1;

			if(codigo_prod_orc(NULL,posicao)!=0)
				return 1;

			if(subgrp_prod_orc(NULL,posicao)!=0)
				return 1;

			if(tipo_pag==1)
				sprintf(query, "select valor_fat from preco_cliente where cliente = %s and produto = %s and grupo = %s  ",cliente_orc_gchar , codigo_prod_orc_gchar, subgrp_prod_orc_cod_gchar);
			else
			if(tipo_pag==2)
				sprintf(query, "select valor_vist from preco_cliente where cliente = %s and produto = %s and grupo = %s  ",cliente_orc_gchar , codigo_prod_orc_gchar, subgrp_prod_orc_cod_gchar);
			else
			{
				popup(NULL,"Selecione o tipo de pagamento");
				gtk_widget_grab_focus(orc_pag_cond_entry);
				return 1;
			}

			vetor = consultar(query);
			if(vetor == NULL)
			{
				return 1;
			}

			if((campos = mysql_fetch_row(vetor))==NULL)
			{
				popup(NULL,"Produto sem preço vinculado ao cliente");
				gtk_widget_grab_focus(orig_preco_prod_orc_combo[posicao]);
				return 1;
			}

			gtk_entry_set_text(GTK_ENTRY(preco_prod_orc_entry[posicao]),campos[0]);
			break;

		case 3:
			if(tipo_pag==0)
			{
				popup(NULL,"Selecione o tipo de pagamento");
				gtk_widget_grab_focus(orc_pag_cond_entry);
				return 1;
			}


			break;
	}

	preco_prod_orc(NULL,posicao);

	qnt_prod_orc_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(qnt_prod_orc_entry[posicao]));

	if(strlen(qnt_prod_orc_gchar)<=0)
	{
		popup(NULL,"A quantidade deve ser inserida");
		gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
		return 1;
	}

	if(critica_real(qnt_prod_orc_gchar,qnt_prod_orc_entry[posicao])!=0)
	{
		gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
		return 1;
	}

	if(recebendo_prod_orc == 0)
	{
		operacao_orc_orc();
		sprintf(query,"select SUM(entradas) - SUM(saidas) %c %i from movimento_estoque where produto = %i and subgrupo = %i and estoque = %i",
		sinal_operacao_int,
		atoi(qnt_prod_orc_gchar),
		atoi(codigo_prod_orc_gchar),
		atoi(subgrp_prod_orc_cod_gchar),
		orc_params.est_orc_padrao);

		g_print("query atual %s\n",query);
		if((vetor = consultar(query))==NULL){
			popup(NULL,"Erro ao consultar saldo do estoque");
			return 1;
		}

		if((campos = mysql_fetch_row(vetor))!=NULL){
			if(campos[0]){

				if(atoi(campos[0])<0){

						if(orcamentos.criticar.prod_saldo){
							popup(NULL,"Produto com saldo insuficiente");
							return 1;
						}
				}

				sprintf(query,"select saldo_min from saldo_min_grupo where produto = %i and grupo = %i and estoque = %i",
				atoi(codigo_prod_orc_gchar),
				atoi(subgrp_prod_orc_cod_gchar),
				orc_params.est_orc_padrao);

				if((vetor = consultar(query))==NULL)
					return 1;

				if((row = mysql_fetch_row(vetor))!=NULL){
					saldo_limite = atof(row[0]);

					if(atoi(campos[0])<=saldo_limite && aviso_estoque[posicao] == 0){
							if(orcamentos.criticar.prod_saldo_limite){
								popup(NULL,"Aviso de saldo mínimo");
								aviso_estoque[posicao] = 1;
							}
					}
				}
			}
			else{
				if(orcamentos.criticar.prod_movimento){
					popup(NULL,"Sem nenhum movimento");
						return 1;
				}
			}
		}
	}

	preco_prod_orc(preco_prod_orc_entry[posicao],posicao);

	critica_real(preco_prod_orc_gchar,preco_prod_orc_entry[posicao]);

	critica_real(qnt_prod_orc_gchar,qnt_prod_orc_entry[posicao]);

	tipodesc = gtk_combo_box_get_active(GTK_COMBO_BOX(tipodesconto_prod_orc_combo[posicao]));

	ativos[posicao].qnt_f = atof(qnt_prod_orc_gchar);
	strcpy(ativos[posicao].qnt_c,qnt_prod_orc_gchar);
	critica_real(ativos[posicao].qnt_c,qnt_prod_orc_entry[posicao]);


	ativos[posicao].preco_f = atof(preco_prod_orc_gchar);
	strcpy(ativos[posicao].preco_c,preco_prod_orc_gchar);
	critica_real(ativos[posicao].preco_c,preco_prod_orc_entry[posicao]);

	desconto_prod_orc(desconto_prod_orc_entry[posicao],posicao);

	if(tipodesc==0)
	{
		ativos[posicao].desconto_f = atof(desconto_prod_orc_gchar);
		strcpy(ativos[posicao].desconto_c,desconto_prod_orc_gchar);
		critica_real(&(ativos[posicao].desconto_c[0]),desconto_prod_orc_entry[posicao]);
	}

	if(tipodesc==1)
	{
		ativos[posicao].desconto_f = ((ativos[posicao].qnt_f)*(ativos[posicao].preco_f))*(atof(desconto_prod_orc_gchar)/100);
		strcpy(ativos[posicao].desconto_c,desconto_prod_orc_gchar);
		critica_real(&(ativos[posicao].desconto_c[0]),desconto_prod_orc_entry[posicao]);
	}

	ativos[posicao].total_f = ((ativos[posicao].qnt_f)*(ativos[posicao].preco_f))-ativos[posicao].desconto_f;

	sprintf(total_prod_orc_gchar,"%.2f",ativos[posicao].total_f);
	gtk_entry_set_text(GTK_ENTRY(total_prod_orc_entry[posicao]),total_prod_orc_gchar);

	critica_real(total_prod_orc_gchar,total_prod_orc_entry[posicao]);
	strcpy(ativos[posicao].total_c,total_prod_orc_gchar);

	gerar_total_geral();

	if(ativos[posicao+1].id == 1)
	{
		if(GTK_IS_WIDGET(codigo_prod_orc_entry[posicao+1]))
				gtk_widget_grab_focus(codigo_prod_orc_entry[posicao+1]);
		else
		if(valor_orig[posicao]!=3 || preco_alterado[posicao] == 1)
			gtk_widget_grab_focus(botao_orc_mais);
		else
				gtk_widget_grab_focus(preco_prod_orc_entry[posicao]);
	}
	else
	if(valor_orig[posicao]!=3 || preco_alterado[posicao] == 1)
		gtk_widget_grab_focus(botao_orc_mais);
	else
		gtk_widget_grab_focus(preco_prod_orc_entry[posicao]);

	preco_alterado[posicao] = 1;

	return 0;
}
