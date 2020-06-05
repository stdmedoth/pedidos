int est_said_ped_fun()
{
	char query[MAX_QUERY_LEN];
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	est_said_ped_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(est_said_ped_entry));
	
	if(strlen(est_said_ped_gchar)<=0)
	{
		est_said_ped_gchar = malloc(strlen("0.0"));
		strcpy(est_said_ped_gchar,"0");
		gtk_widget_grab_focus(est_said_confirma_button);
		return 0;
	}
	
	sprintf(query,"select * from pedidos where code = %s",est_said_ped_gchar);
	if((res = consultar(query))==NULL)
	{
		popup(NULL,"Erro ao buscar pedido para vinculo");
		return 1;
	}
	if((row = mysql_fetch_row(res))==NULL)
	{
		gtk_widget_grab_focus(est_said_ped_entry);
		popup(NULL,"Pedido não existe");
		return 1;
	}
	gtk_widget_grab_focus(est_said_confirma_button);
	
	return 0;
}
