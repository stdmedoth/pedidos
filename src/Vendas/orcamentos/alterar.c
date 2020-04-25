int altera_orc()
{
	char *query;
	int cont=1;
	int tirar_linha(int);
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
	
	while(cont<=itens_qnt)
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
	adicionar_linha_orc();
	alterando_orc=1;
	
	while((row = mysql_fetch_row(res))!=NULL)
	{
		g_print("Adicionando item %s\n", row[1]);
		
		if(atoi(row[1])>=2)
		{
			if(rec_altera_qnt==1)
			{
				tirar_linha(1);	
			}
			
			itens_qnt = atoi(row[1]);
			adicionar_linha_orc();
		}
		
		if(GTK_IS_ENTRY(codigo_prod_orc_entry[atoi(row[1])]))
		{
			gtk_entry_set_text(GTK_ENTRY(codigo_prod_orc_entry[atoi(row[1])]),row[2]);
			gtk_entry_set_text(GTK_ENTRY(qnt_prod_orc_entry[atoi(row[1])]),row[3]);
			gtk_entry_set_text(GTK_ENTRY(preco_prod_orc_entry[atoi(row[1])]),row[4]);
			gtk_combo_box_set_active(GTK_COMBO_BOX(tipodesconto_prod_orc_combo[atoi(row[1])]),atoi(row[5]));
			gtk_entry_set_text(GTK_ENTRY(desconto_prod_orc_entry[atoi(row[1])]),row[6]);
			gtk_entry_set_text(GTK_ENTRY(total_prod_orc_entry[atoi(row[1])]),row[7]);
			
			//criticar campos
			codigo_prod_orc(codigo_prod_orc_entry[atoi(row[1])],atoi(row[1]));
			qnt_prod_orc(qnt_prod_orc_entry[atoi(row[1])],atoi(row[1]));
			preco_prod_orc(preco_prod_orc_entry[atoi(row[1])],atoi(row[1]));
			total_prod_orc(total_prod_orc_entry[atoi(row[1])],atoi(row[1]));
		}
		rec_altera_qnt++;
	}

	
	return 0;	
}
