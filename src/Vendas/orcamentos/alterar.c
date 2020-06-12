static int recebendo_prod_orc=0;
int altera_orc()
{
	char *query;
	int cont=1,erro=0;
	char code[MAX_CODE_LEN];
	MYSQL_RES *res;
	MYSQL_ROW row;

	g_print("Iniciando alterar\n");
	alterando_orc=1;
	rec_altera_qnt=1;
	recebendo_prod_orc=1;

	if(codigo_orc()!=0)
		return 1;

	query = malloc(MAX_QUERY_LEN);
	sprintf(query,"select cliente, tipopag, (%s%s), total from orcamentos where code = %s",DATE_QUERY,codigo_orc_gchar,codigo_orc_gchar);

	if((res = consultar(query))==NULL)
	{
		popup(NULL,"Erro ao buscar orçamento");
		return 1;
	}

	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Orçamento não existe para ser alterado");
		return 1;
	}

	gtk_entry_set_text(GTK_ENTRY(cliente_orc_entry),row[0]);
	gtk_combo_box_set_active(GTK_COMBO_BOX(faturado_avista_combo),atoi(row[1]));
	tipo_pag = atoi(row[1]);
	gtk_entry_set_text(GTK_ENTRY(data_orc_entry),row[2]);

	if(codigo_cli_orc()!=0)
		return 1;

	sprintf(query,"select * from Produto_Orcamento where code = %s",codigo_orc_gchar);
	if((res = consultar(query))==NULL)
	{
		popup(NULL,"Erro nos itens do orçamento");
		return 1;
	}

	cont = 0;
	while(cont<MAX_PROD_ORC)
	{
		if(ativos[cont].id==1)
		{
			tirar_linha(cont);
		}
		cont++;
	}

	while((row = mysql_fetch_row(res))!=NULL)
	{
		g_print("\n\nAdicionando item %s à alteração \n", row[1]);
		g_print("Dados:\n");
		g_print("code: %s\n", row[COD_ORC_PROD_COL]);
		g_print("item: %s\n", row[ITM_ORC_PROD_COL]);
		g_print("produto: %s\n", row[PROD_ORC_PROD_COL]);
		g_print("subgrupo: %s\n", row[SUBGRP_ORC_PROD_COL]);
		g_print("unidades: %s\n", row[UND_ORC_PROD_COL]);
		g_print("valor_unit: %s\n", row[VLR_ORC_PROD_COL]);
		g_print("valor_orig: %s\n", row[VLR_ORIG_ORC_PROD_COL]);
		g_print("tipodesc: %s\n", row[TIP_DESC_ORC_PROD_COL]);
		g_print("desconto: %s\n", row[DESC_ORC_PROD_COL]);
		g_print("total: %s\n\n", row[TOTAL_ORC_PROD_COL]);
		g_print("total: %s\n\n", row[OBS_ORC_PROD_COL]);

		itens_qnt = atoi(row[ITM_ORC_PROD_COL]);
		adicionar_linha_orc();

		if(GTK_IS_ENTRY(codigo_prod_orc_entry[atoi(row[ITM_ORC_PROD_COL])]))
		{

			gtk_entry_set_text(GTK_ENTRY(codigo_prod_orc_entry[atoi(row[ITM_ORC_PROD_COL])]),row[PROD_ORC_PROD_COL]);

			gtk_entry_set_text(GTK_ENTRY(subgrp_prod_orc_cod_entry[atoi(row[ITM_ORC_PROD_COL])]),row[SUBGRP_ORC_PROD_COL]);

			valor_orig[atoi(row[ITM_ORC_PROD_COL])] = atoi(row[VLR_ORIG_ORC_PROD_COL]);

			gtk_entry_set_text(GTK_ENTRY(qnt_prod_orc_entry[atoi(row[ITM_ORC_PROD_COL])]),row[UND_ORC_PROD_COL]);

			gtk_combo_box_set_active(GTK_COMBO_BOX(orig_preco_prod_orc_combo[atoi(row[ITM_ORC_PROD_COL])]),valor_orig[atoi(row[ITM_ORC_PROD_COL])]);

			gtk_combo_box_set_active(GTK_COMBO_BOX(tipodesconto_prod_orc_combo[atoi(row[ITM_ORC_PROD_COL])]),atoi(row[TIP_DESC_ORC_PROD_COL]));

			gtk_entry_set_text(GTK_ENTRY(preco_prod_orc_entry[atoi(row[ITM_ORC_PROD_COL])]),row[VLR_ORC_PROD_COL]);

			gtk_entry_set_text(GTK_ENTRY(desconto_prod_orc_entry[atoi(row[ITM_ORC_PROD_COL])]),row[DESC_ORC_PROD_COL]);

			gtk_entry_set_text(GTK_ENTRY(total_prod_orc_entry[atoi(row[ITM_ORC_PROD_COL])]),row[TOTAL_ORC_PROD_COL]);

			if(row[OBS_ORC_PROD_COL])
			{
				strcpy(obs_prod_orc_gchar[atoi(row[ITM_ORC_PROD_COL])],row[OBS_ORC_PROD_COL]);

				obs_prod_orc_buffer[atoi(row[ITM_ORC_PROD_COL])] = gtk_text_view_get_buffer(GTK_TEXT_VIEW(obs_prod_orc_view[atoi(row[ITM_ORC_PROD_COL])]));

				gtk_text_buffer_set_text(GTK_TEXT_BUFFER(obs_prod_orc_buffer[atoi(row[ITM_ORC_PROD_COL])]),

				obs_prod_orc_gchar[atoi(row[ITM_ORC_PROD_COL])],strlen(obs_prod_orc_gchar[atoi(row[ITM_ORC_PROD_COL])]));
			}
		}
		rec_altera_qnt++;
	}

	gtk_widget_activate(botao_orc_mais);

	recebendo_prod_orc=0;

	cont=1;
	while(cont<MAX_PROD_ORC)
	{
		if(ativos[cont].id==1)
		{
			gtk_widget_activate(codigo_prod_orc_entry[cont]);

			gtk_widget_activate(subgrp_prod_orc_cod_entry[cont]);

			gtk_widget_activate(preco_prod_orc_entry[cont]);

			gtk_widget_activate(desconto_prod_orc_entry[cont]);

			gtk_widget_activate(total_prod_orc_entry[cont]);

			obs_prod_orc_fun(NULL,cont);

			gerar_total_geral();
		}
		ativos_qnt++;
		cont++;
	}

	if(rec_altera_qnt==1)
	{
		cont=0;


		popup(NULL,"Não há produtos no orçamento...\ndeletado!");
		sprintf(query,"delete from orcamentos where code = %s",codigo_orc_gchar);
		erro = enviar_query(query);
		if(erro != 0 )
		{
			popup(NULL,"Erro ao tentar excluir orçamento vazio");
			return 1;
		}
		gtk_widget_set_sensitive(cliente_orc_entry,TRUE);
		cancela_orc();
		return 0;
	}


	gtk_widget_set_sensitive(alterar_orc_button,FALSE);
	gtk_widget_set_sensitive(codigo_orc_frame,FALSE);
	return 0;
}
