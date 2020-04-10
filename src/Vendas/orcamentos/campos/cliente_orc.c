int codigo_cli_orc()
{
	char query[MAX_QUERY_LEN];
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	cliente_orc_gchar = malloc(MAX_CODE_LEN);
	cliente_orc_gchar =(gchar*) gtk_entry_get_text(GTK_ENTRY(cliente_orc_entry));	
	if(strlen(cliente_orc_gchar)<=0)
	{
		popup(NULL,"O código cliente deve ser inserido");
		vet_erro[CLI_ERR] = 1;
		gtk_widget_grab_focus(cliente_orc_entry);
		return 1;
	}
	if(stoi(cliente_orc_gchar)==-1)
	{
		popup(NULL,"O código do cliente deve ser numérico");
		vet_erro[CLI_ERR] = 1;
		gtk_widget_grab_focus(cliente_orc_entry);
		return 1;
	}
	sprintf(query,"select razao,endereco,telefone from terceiros where code = %s",cliente_orc_gchar);
	vetor = consultar(query);
	if(vetor==NULL)
	{
		popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
		g_print("Erro na query de cliente no orcamento\n");
		autologger("Erro na query de cliente no orcamento\n");
		autologger(query);
		gtk_widget_grab_focus(cliente_orc_entry);
		vet_erro[CLI_ERR] = 1;
		return 1;
	}
	campos = mysql_fetch_row(vetor);
	if(campos == NULL)
	{
		popup(NULL,"Cliente não existente");
		gtk_widget_grab_focus(cliente_orc_entry);
		vet_erro[CLI_ERR] = 1;
		return 1;
	}
	vet_erro[CLI_ERR] = 0;
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_name_entry),campos[0]);
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_end_entry),campos[1]);
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_tel_entry),campos[2]);
	if(GTK_IS_WIDGET(codigo_prod_orc_entry[1]))
		gtk_widget_grab_focus(codigo_prod_orc_entry[1]);
	return 0;
}
