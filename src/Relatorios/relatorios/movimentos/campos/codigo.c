int relat_mov_codigo_fun()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	g_print("Iniciando relat_mov_codigo_fun()\n");
	relat_mov_codigo_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(relat_mov_code_entry));
	if(strlen(relat_mov_codigo_gchar)<=0)
	{
		popup(NULL,"Insira o código do relatório");
		return 1;
	}

	sprintf(query,"select nome from criador_relat where code = %s",relat_mov_codigo_gchar);
	if((res = consultar(query))==NULL)
	{
		popup(NULL,"Erro ao buscar nome do relatorio");
		return 1;
	}

	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Relatório não existente");
		return 1;
	}
	
	gtk_entry_set_text(GTK_ENTRY(relat_mov_nome_entry),row[0]);
	relat_mov_query_fun();
	relat_mov_gerar_fun();

	g_print("Finalizando relat_mov_codigo_fun()\n");
	return 0;
}
