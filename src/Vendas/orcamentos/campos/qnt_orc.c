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
				gtk_widget_grab_focus(faturado_avista_combo);
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
				gtk_widget_grab_focus(faturado_avista_combo);
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
	g_print("Valor qnt %s\n",qnt_prod_orc_gchar);
	
	if(critica_real(qnt_prod_orc_gchar,qnt_prod_orc_entry[posicao])!=0)
	{
		gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
		return 1;
	}
	g_print("Iniciando verificação de total\n");

	preco_prod_orc(preco_prod_orc_entry[posicao],posicao);
	
	for(int pos=0;pos<=strlen(preco_prod_orc_gchar);pos++)
	{
		if(preco_prod_orc_gchar[pos]==46||preco_prod_orc_gchar[pos]==44)
		{	
			#ifdef __linux__
			preco_prod_orc_gchar[pos] = 46;
			#endif
			#ifdef WIN32
			preco_prod_orc_gchar[pos] = 44;
			#endif
		}
	}
	
	for(int pos=0;pos<=strlen(qnt_prod_orc_gchar);pos++)
	{
		if(qnt_prod_orc_gchar[pos]==46||qnt_prod_orc_gchar[pos]==44)
		{	
			#ifdef __linux__
			qnt_prod_orc_gchar[pos] = 46;
			#endif
			#ifdef WIN32
			qnt_prod_orc_gchar[pos] = 44;
			#endif
		}
	}

	tipodesc = gtk_combo_box_get_active(GTK_COMBO_BOX(tipodesconto_prod_orc_combo[posicao]));
	
	ativos[posicao].qnt_f = atof(qnt_prod_orc_gchar);
	strcpy(ativos[posicao].qnt_c,qnt_prod_orc_gchar);
	critica_real(ativos[posicao].qnt_c,qnt_prod_orc_entry[posicao]);
	g_print("float qnt %.2f\n",ativos[posicao].qnt_f);


	ativos[posicao].preco_f = atof(preco_prod_orc_gchar);
	strcpy(ativos[posicao].preco_c,preco_prod_orc_gchar);
	critica_real(ativos[posicao].preco_c,preco_prod_orc_entry[posicao]);
	g_print("float preco %.2f\n",ativos[posicao].preco_f);

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
	


	g_print("Total: ");
	ativos[posicao].total_f = ((ativos[posicao].qnt_f)*(ativos[posicao].preco_f))-ativos[posicao].desconto_f;
	g_print("float: %.2f ",ativos[posicao].total_f);

	
	sprintf(total_prod_orc_gchar,"%.2f",ativos[posicao].total_f);
	
	g_print("string: %s \n",total_prod_orc_gchar);
	critica_real(total_prod_orc_gchar,total_prod_orc_entry[posicao]);
	strcpy(ativos[posicao].total_c,total_prod_orc_gchar);
	
	gerar_total_geral();
	
	if(ativos[posicao+1].id == 1)
	{
		if(GTK_IS_WIDGET(codigo_prod_orc_entry[posicao+1]))
			gtk_widget_grab_focus(codigo_prod_orc_entry[posicao+1]);
		else
			gtk_widget_grab_focus(botao_orc_mais);
	}
	else
		gtk_widget_grab_focus(botao_orc_mais);
	
	g_print("Finalizando qnt_prod_orc()\n");
	
	return 0;
}
