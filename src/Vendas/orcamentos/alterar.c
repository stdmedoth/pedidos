int altera_orc()
{
	char *query;
	int cont=1,erro=0;
	char code[MAX_CODE_LEN];
	MYSQL_RES *res;
	MYSQL_ROW row;
	if(codigo_orc()!=0)
		return 1;
	query = malloc(MAX_QUERY_LEN);
	sprintf(query,"select cliente,(%s%s),total from orcamentos where code = %s",DATE_QUERY,codigo_orc_gchar,codigo_orc_gchar);
	if((vetor = consultar(query))==NULL)
	{
		popup(NULL,"Erro ao buscar orçamento");
		return 1;
	}
	if((campos = mysql_fetch_row(vetor))==NULL)
	{
		popup(NULL,"Orçamento não existe para ser alterado");
		return 1;
	}
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_entry),campos[0]);
	if(codigo_cli_orc()!=0)
		return 1;
	gtk_entry_set_text(GTK_ENTRY(data_orc_entry),campos[1]);
	sprintf(query,"select * from Produto_Orcamento where code = %s",codigo_orc_gchar);
	if((res = consultar(query))==NULL)
	{
		popup(NULL,"Erro nos itens do orçamento");
		return 1;
	}
	
	while(cont<MAX_PROD_ORC)
	{
		if(ativos[cont].id==1)
		{
			ativos[cont].id = 0;
			excluidos[cont].id = 1;
			tirar_linha(cont);			
		}
		cont++;
	}
	
	itens_qnt = 1;
	alterando_orc=1;
	adicionar_linha_orc();
	g_print("Iniciando alterar\n");
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
		
		
		if(atoi(row[ITM_ORC_PROD_COL])>1)
		{
			if(rec_altera_qnt==1)
			{
				tirar_linha(1);	
			}
			
			itens_qnt = atoi(row[ITM_ORC_PROD_COL]);
			adicionar_linha_orc();
		}
		
		if(GTK_IS_ENTRY(codigo_prod_orc_entry[atoi(row[1])]))
		{
			gtk_entry_set_text(GTK_ENTRY(codigo_prod_orc_entry[atoi(row[ITM_ORC_PROD_COL])]),row[PROD_ORC_PROD_COL]);
			
			gtk_entry_set_text(GTK_ENTRY(subgrp_prod_orc_cod_entry[atoi(row[ITM_ORC_PROD_COL])]),row[SUBGRP_ORC_PROD_COL]);
			
			preco_alterado[atoi(row[ITM_ORC_PROD_COL])] = atoi(row[VLR_ORIG_ORC_PROD_COL]);
			
			switch(preco_alterado[atoi(row[ITM_ORC_PROD_COL])])
			{
				case 1: 
					gtk_entry_set_text(GTK_ENTRY(orig_preco_prod_orc_entry[atoi(row[ITM_ORC_PROD_COL])]),"Tabela");
					break;
				case 2:
					gtk_entry_set_text(GTK_ENTRY(orig_preco_prod_orc_entry[atoi(row[ITM_ORC_PROD_COL])]),"Cliente");
					break;
				case 3:
					gtk_entry_set_text(GTK_ENTRY(orig_preco_prod_orc_entry[atoi(row[ITM_ORC_PROD_COL])]),"Operador");
					break;
			}
			
			orig_preco_prod_orc(orig_preco_prod_orc_entry[atoi(row[ITM_ORC_PROD_COL])], atoi(row[ITM_ORC_PROD_COL]));
			
			gtk_combo_box_set_active(GTK_COMBO_BOX(tipodesconto_prod_orc_combo[atoi(row[ITM_ORC_PROD_COL])]),atoi(row[TIP_DESC_ORC_PROD_COL]));
			
		
			gtk_entry_set_text(GTK_ENTRY(qnt_prod_orc_entry[atoi(row[ITM_ORC_PROD_COL])]),row[UND_ORC_PROD_COL]);
			

			gtk_entry_set_text(GTK_ENTRY(preco_prod_orc_entry[atoi(row[ITM_ORC_PROD_COL])]),row[VLR_ORC_PROD_COL]);
			

			gtk_entry_set_text(GTK_ENTRY(desconto_prod_orc_entry[atoi(row[ITM_ORC_PROD_COL])]),row[DESC_ORC_PROD_COL]);

			gtk_entry_set_text(GTK_ENTRY(total_prod_orc_entry[atoi(row[ITM_ORC_PROD_COL])]),row[TOTAL_ORC_PROD_COL]);

		}
		rec_altera_qnt++;
		
	}
	itens_qnt = rec_altera_qnt;
	adicionar_linha_orc();
	if(rec_altera_qnt==1)
	{
		itens_qnt = 1;
		ativos_qnt= 1;
		
		cont=1;
		rec_altera_qnt = 1;
		alterando_orc = 0;

		gtk_widget_set_sensitive(cliente_orc_entry,TRUE);
		popup(NULL,"Não há produtos no orçamento");
		sprintf(query,"delete from orcamentos where code = %s",codigo_orc_gchar);
		erro = enviar_query(query);
		if(erro != 0 )
		{
			popup(NULL,"Erro ao tentar excluir orçamento vazio");
			return 1;
		}
		return 1;
	}
	return 0;	
}
