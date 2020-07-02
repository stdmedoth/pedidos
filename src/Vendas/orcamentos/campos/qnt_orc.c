int qnt_prod_orc(GtkWidget *widget,int posicao)
{
	int desconto_prod_orc(GtkWidget*,int);
	char query[MAX_QUERY_LEN];
	int tipodesc;

	MYSQL_RES *vetor;
	MYSQL_ROW campos;

	ativos[posicao].qnt_f = 0;
	g_print("Iniciando qnt_prod_orc()\n");

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
//	g_print("Valor qnt %s\n",qnt_prod_orc_gchar);

	if(critica_real(qnt_prod_orc_gchar,qnt_prod_orc_entry[posicao])!=0)
	{
		gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
		return 1;
	}

	if(alterando_orc==0 && concluindo_orc==0 && aviso_estoque[posicao] == 0)
	{
		sprintf(query,"select SUM(entradas) - SUM(saidas) from movimento_estoque where produto = %s and subgrupo = %s",
		codigo_prod_orc_gchar,
		subgrp_prod_orc_cod_gchar);

		if((vetor = consultar(query))==NULL){
			popup(NULL,"Erro ao consultar saldo do estoque");
			return 1;
		}

		if((campos = mysql_fetch_row(vetor))!=NULL){
			if(campos[0]){
				if(atoi(campos[0])<=0){
						if(orcamentos.criticar.prod_saldo){
							popup(NULL,"Sem saldo");
							aviso_estoque[posicao] = 1;
							return 1;
						}
				}

				const int saldo_limite = 3;

				if(atoi(campos[0])==saldo_limite){
						if(orcamentos.criticar.prod_saldo_limite){
							popup(NULL,"Saldo limite usado");
							aviso_estoque[posicao] = 1;
						}
				}
			}
			else{
				if(orcamentos.criticar.prod_movimento){
					popup(NULL,"Sem nenhum movimento");
				}
			}
		}
	}

	g_print("saldo limite: %i\nmovimento: %i\nsem saldo: %i\naviso_estoque: %i",
	orcamentos.criticar.prod_saldo_limite,
	orcamentos.criticar.prod_saldo,
	orcamentos.criticar.prod_movimento,
	aviso_estoque[posicao]);

	g_print("Iniciando verificação de total\n");

	preco_prod_orc(preco_prod_orc_entry[posicao],posicao);

	critica_real(preco_prod_orc_gchar,preco_prod_orc_entry[posicao]);

	critica_real(qnt_prod_orc_gchar,qnt_prod_orc_entry[posicao]);

	tipodesc = gtk_combo_box_get_active(GTK_COMBO_BOX(tipodesconto_prod_orc_combo[posicao]));

	ativos[posicao].qnt_f = atof(qnt_prod_orc_gchar);
	strcpy(ativos[posicao].qnt_c,qnt_prod_orc_gchar);
	critica_real(ativos[posicao].qnt_c,qnt_prod_orc_entry[posicao]);
//	g_print("float qnt %.2f\n",ativos[posicao].qnt_f);


	ativos[posicao].preco_f = atof(preco_prod_orc_gchar);
	strcpy(ativos[posicao].preco_c,preco_prod_orc_gchar);
	critica_real(ativos[posicao].preco_c,preco_prod_orc_entry[posicao]);
//	g_print("float preco %.2f\n",ativos[posicao].preco_f);

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



//	g_print("Total: ");
	ativos[posicao].total_f = ((ativos[posicao].qnt_f)*(ativos[posicao].preco_f))-ativos[posicao].desconto_f;
//	g_print("float: %.2f ",ativos[posicao].total_f);


	sprintf(total_prod_orc_gchar,"%.2f",ativos[posicao].total_f);

//	g_print("string: %s \n",total_prod_orc_gchar);
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

	g_print("Finalizando qnt_prod_orc()\n");

	return 0;
}
