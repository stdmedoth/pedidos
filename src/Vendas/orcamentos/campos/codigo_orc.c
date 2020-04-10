int codigo_orc()
{
	char query[MAX_QUERY_LEN];
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	codigo_orc_gchar = malloc(MAX_CODE_LEN);
	codigo_orc_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(codigo_orc_entry));
	if(strlen(codigo_orc_gchar)<=0)
	{
		popup(NULL,"O código do orcamento deve ser inserido");
		gtk_widget_grab_focus(codigo_orc_entry);
		vet_erro[COD_ERR] = 0;
		return 1;
	}
	if(stoi(codigo_orc_gchar)==-1)
	{
		popup(NULL,"O código do orcamento deve ser numérico");
		gtk_widget_grab_focus(codigo_orc_entry);
		vet_erro[COD_ERR] = 0;
		return 1;
	}
	vet_erro[COD_ERR] = 0;
	gtk_widget_grab_focus(operacao_orc_entry);
	return 0;
}
