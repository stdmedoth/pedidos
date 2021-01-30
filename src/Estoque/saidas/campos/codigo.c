int est_said_codigo_fun()
{
	char query[MAX_QUERY_LEN];
	MYSQL_RES *estado;
	MYSQL_ROW campo;

	est_said_cod_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(est_said_cod_entry));

	if(strlen(est_said_cod_gchar)<=0)
	{
		popup(NULL,"Insira o código");
		gtk_widget_grab_focus(est_said_cod_entry);
		return 1;
	}
	if(alterando_mov_said_est != 0)
	{
		sprintf(query,"select entradas,saidas from movimento_estoque where code = %s",est_said_cod_gchar);
		if((estado = consultar(query))==NULL)
			return 1;

		if((campo = mysql_fetch_row(estado))==NULL)
		{
			popup(NULL,"O movimento não existe");
			return 1;
		}
		else
		if(atoi(campo[0])>0)
		{
			popup(NULL,"O movimento é uma entrada\nUse a opção de Entradas de estoque");
			return 1;
		}
		else
		if(atoi(campo[1])<=0&&concluindo_mov_said_est==0)
		{
			popup(NULL,"A entrada está zerada");
		}
		return 0;
	}
	else
	if(alterando_mov_said_est==0&&concluindo_mov_said_est==0)
	{
		sprintf(query,"select code from movimento_estoque where code = %s",est_said_cod_gchar);
		if((estado = consultar(query))==NULL)
			return 1;

		if((campo = mysql_fetch_row(estado))==NULL)
		{
			popup(NULL,"O movimento não existe");
			return 1;
		}
		est_said_alterar_fun();
	}


	gtk_widget_grab_focus(est_said_data_entry);
	return 0;
}
