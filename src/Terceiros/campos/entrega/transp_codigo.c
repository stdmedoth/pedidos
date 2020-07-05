int transp_codigo_fun()
{
	char code[10];
	char *query;
	MYSQL_RES *res;
	MYSQL_ROW row;
	query = malloc(MAX_QUERY_LEN);
	transp_codigo = (gchar *) gtk_entry_get_text(GTK_ENTRY(transp_codigo_entry));
	if(strlen(transp_codigo)<=0)
	{
		gtk_widget_grab_focus(GTK_WIDGET(transp_nome_entry));
		return 1;
	}
	if(stoi(transp_codigo)==-1)
	{
		if(strlen(transp_codigo)>8)
		{
			g_print("Codigo terceiro muito grande %s\n",transp_codigo);
			popup(NULL,"Por favor tente com um código menor\nO código do terceiro está enorme");
			return -1;
		}
		else
		{
			g_print("Codigo do terceiro incorreto %s\n",transp_codigo);
			popup(NULL,"Codigo terceiro deve ser numérico\nCaso não seja necessário, não mude o código padrão");
			code[0] = '\0';
			sprintf(code,"%i",tasker("terceiros"));
			gtk_entry_set_text(GTK_ENTRY(transp_codigo_entry),code);
			gtk_entry_set_text(GTK_ENTRY(transp_nome_entry),"");
			gtk_entry_set_text(GTK_ENTRY(transp_cnpj_entry),"");
			gtk_entry_set_text(GTK_ENTRY(transp_logradouro_entry),"");
			gtk_entry_set_text(GTK_ENTRY(transp_cidade_entry),"");
			gtk_entry_set_text(GTK_ENTRY(transp_estado_entry),"");
			gtk_entry_set_text(GTK_ENTRY(transp_cep_entry),"");
			gtk_widget_grab_focus(GTK_WIDGET(transp_codigo_entry));
			return 1;
		}
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
