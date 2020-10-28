int est_said_produto_fun()
{
	char query[MAX_QUERY_LEN];
	MYSQL_RES *estado;
	MYSQL_ROW campo;

	est_said_prod_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(est_said_prod_entry));

	if(strlen(est_said_prod_gchar)<=0)
	{
		popup(NULL,"Insira o código");
		gtk_widget_grab_focus(est_said_prod_entry);
		return 1;
	}

	sprintf(query,"select nome from produtos where code = %i",atoi(est_said_prod_gchar));

	if(!(estado = consultar(query))){
		popup(NULL,"Erro ao consultar produto");
		return 1;
	}

	if(!(campo = mysql_fetch_row(estado))){
		popup(NULL,"Este código para produto não existe\n\tUse a pesquisa");
		return 1;
	}

	gtk_entry_set_text(GTK_ENTRY(est_said_campo_nome_prod),campo[0]);

	gtk_widget_grab_focus(est_said_qnt_entry);

	return 0;
}
