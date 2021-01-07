int altera_grupo()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	grpcode = malloc(MAX_CODE_LEN);
	grpcode = (gchar*) gtk_entry_get_text(GTK_ENTRY(cod_grp_entry));
	char query[MAX_QUERY_LEN];

	sprintf(query,"select nome from grupos where code = %s",grpcode);
	if((res = consultar(query))==NULL)
	{
		return 1;
	}
	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Grupo não existente");
		gtk_widget_grab_focus(cod_grp_entry);
		return 1;
	}
	gtk_entry_set_text(GTK_ENTRY(nome_grp_entry),row[0]);
	gtk_widget_grab_focus(confirma_grp_button);
	gtk_widget_set_sensitive(cod_grp_entry,FALSE);
	gtk_widget_set_sensitive(psq_grp_button,FALSE);
	gtk_widget_set_sensitive(altera_grp_button,FALSE);
	alterando_grp = 1;
	return 0;
}
