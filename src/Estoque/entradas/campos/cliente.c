int est_ent_client_fun()
{
	char query[MAX_QUERY_LEN];
	MYSQL_RES *estado;
	MYSQL_ROW campo;

	est_ent_client_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(est_ent_client_entry));
	
	if(strlen(est_ent_client_gchar)<=0)
	{
		popup(NULL,"Insira o código");
		gtk_entry_set_text(GTK_ENTRY(est_ent_campo_nome_client),"");
		gtk_widget_grab_focus(est_ent_client_entry);
		return 1;
	}
	sprintf(query,"select razao from terceiros where code = %s",est_ent_client_gchar);
	if((estado = consultar(query))==NULL)
		return 1;
	if((campo = mysql_fetch_row(estado))==NULL)
	{
		popup(NULL,"O terceiro não existe");
		gtk_entry_set_text(GTK_ENTRY(est_ent_campo_nome_client),"");
		return 1;
	}
	gtk_entry_set_text(GTK_ENTRY(est_ent_campo_nome_client),campo[0]);
	
	gtk_widget_grab_focus(est_ent_prod_entry);
	
	return 0;
}
