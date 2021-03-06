int est_sld_prod_fun()
{
	char query[MAX_QUERY_LEN];
	MYSQL_RES *estado;
	MYSQL_ROW campo;

	est_sld_prod_cod_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(est_sld_prod_cod_entry));

	if(strlen(est_sld_prod_cod_gchar)<=0)
	{
		popup(NULL,"Insira o código");
		gtk_widget_grab_focus(est_sld_prod_cod_entry);
		return 1;
	}

	sprintf(query,"select nome from produtos where code = %s",est_sld_prod_cod_gchar);
	if((estado = consultar(query))==NULL)
		return 1;
	if((campo = mysql_fetch_row(estado))==NULL)
	{
		popup(NULL,"O produto não existe");
		return 1;
	}

	gtk_entry_set_text(GTK_ENTRY(est_sld_prod_nome_entry),campo[0]);

	if(calcula_saldo())
			return 1;

	return 0;
}
