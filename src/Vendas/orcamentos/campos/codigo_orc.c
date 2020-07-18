int codigo_orc()
{
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	char query[MAX_QUERY_LEN];

	codigo_orc_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(codigo_orc_entry));
	if(strlen(codigo_orc_gchar)<=0)
	{
		popup(NULL,"O código do orcamento deve ser inserido");
		gtk_widget_grab_focus(codigo_orc_entry);
		return 1;
	}
	if(stoi(codigo_orc_gchar)==-1)
	{
		popup(NULL,"O código do orcamento deve ser numérico");
		gtk_widget_grab_focus(codigo_orc_entry);
		return 1;
	}

	if(alterando_orc==0 && concluindo_orc==0 && copiando_orc==0 && excluindo_orc == 0 )
	{
		sprintf(query,"select code from orcamentos where code = '%s'",codigo_orc_gchar);
		vetor = consultar(query);
		if(vetor==NULL)
		{
			return 1;
		}

		if((campos = mysql_fetch_row(vetor))!=NULL)
		{
			altera_orc();
		}

	}

	gtk_widget_grab_focus(operacao_orc_combo);
	return 0;
}
