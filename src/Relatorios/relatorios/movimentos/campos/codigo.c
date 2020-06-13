int relat_sld_codigo_fun()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	relat_sld_codigo_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(relat_sld_code_entry));
	if(strlen(relat_sld_codigo_gchar)<=0)
	{
		popup(NULL,"Insira o código do relatório");
		return 1;
	}

	sprintf(query,"select nome from criador_relat where code = %s",relat_sld_codigo_gchar);
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
	gtk_entry_set_text(GTK_ENTRY(relat_sld_nome_entry),row[0]);
	relat_sld_query_fun();
	relat_sld_gerar_fun();
	return 0;
}
