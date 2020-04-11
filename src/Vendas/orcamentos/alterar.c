int altera_orc()
{
	char *query;
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
		popup(NULL,"Erro os itens no orçamento");
		return 1;
	}
	while((row = mysql_fetch_row(res))!=NULL)
	{
		g_print("Adicionando item %s\n", row[1]);
		gtk_entry_set_text(GTK_ENTRY(codigo_prod_orc_entry[atoi(row[1])]),row[2]);
		gtk_entry_set_text(GTK_ENTRY(qnt_prod_orc_entry[atoi(row[1])]),row[3]);
		gtk_entry_set_text(GTK_ENTRY(preco_prod_orc_entry[atoi(row[1])]),row[4]);
		gtk_entry_set_text(GTK_ENTRY(orig_preco_prod_orc_entry[atoi(row[1])]),row[3]);
		gtk_entry_set_text(GTK_ENTRY(total_prod_orc_entry[atoi(row[1])]),row[6]);
		adicionar_linha_orc();
		
	}
	
		
	
	
	return 0;	
}