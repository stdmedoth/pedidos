int transp_codigo_fun()
{
	char code[10];
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	transp_codigo = (gchar *) gtk_entry_get_text(GTK_ENTRY(transp_codigo_entry));

	vinc_transp();

	if( strlen(transp_codigo)<=0 )
	{
		transp_codigo = strdup("");
		gtk_entry_set_text(GTK_ENTRY(transp_ie_entry), "");
		gtk_entry_set_text(GTK_ENTRY(transp_nome_entry), "");
		gtk_entry_set_text(GTK_ENTRY(transp_cnpj_entry), "");
		return 0;
	}

	sprintf(query,"select * from terceiros where code = %s",transp_codigo);
	res = consultar(query);
	if(res==NULL)
	{
		popup(NULL,"Verifique query de transportador com suporte");
		return 1;
	}
	row = mysql_fetch_row(res);
	if(row==NULL)
	{
		popup(NULL,"Nenhum transportador para o código indicado");
		return 1;
	}
	if(row[RAZ_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(transp_nome_entry),row[RAZ_TER_COL]);

	if(row[DOC_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(transp_cnpj_entry),row[DOC_TER_COL]);

	if(row[IE_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(transp_ie_entry),row[IE_TER_COL]);

	gtk_widget_grab_focus(transp_nome_entry);
	g_print("codigo: %s\n",transp_codigo);
	return 0;
}
